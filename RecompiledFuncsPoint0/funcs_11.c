#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void AudioHeap_ResetPool(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B7838: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800B783C: sw          $zero, 0xC($a0)
    MEM_W(0XC, ctx->r4) = 0;
    // 0x800B7840: jr          $ra
    // 0x800B7844: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    return;
    // 0x800B7844: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
;}
RECOMP_FUNC void AudioHeap_InitMainPools(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B7848: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800B784C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800B7850: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800B7854: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7858: lui         $a1, 0x8000
    ctx->r5 = S32(0X8000 << 16);
    // 0x800B785C: addiu       $a1, $a1, 0x1000
    ctx->r5 = ADD32(ctx->r5, 0X1000);
    // 0x800B7860: addiu       $a0, $a0, -0x1AA0
    ctx->r4 = ADD32(ctx->r4, -0X1AA0);
    // 0x800B7864: jal         0x800B77D4
    // 0x800B7868: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    AudioHeap_InitPool(rdram, ctx);
        goto after_0;
    // 0x800B7868: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    after_0:
    // 0x800B786C: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x800B7870: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800B7874: lw          $t7, -0x1D08($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1D08);
    // 0x800B7878: lui         $t6, 0x8000
    ctx->r14 = S32(0X8000 << 16);
    // 0x800B787C: addiu       $t6, $t6, 0x1000
    ctx->r14 = ADD32(ctx->r14, 0X1000);
    // 0x800B7880: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7884: addiu       $a0, $a0, -0x1AB0
    ctx->r4 = ADD32(ctx->r4, -0X1AB0);
    // 0x800B7888: addu        $a1, $a3, $t6
    ctx->r5 = ADD32(ctx->r7, ctx->r14);
    // 0x800B788C: jal         0x800B77D4
    // 0x800B7890: subu        $a2, $t7, $a3
    ctx->r6 = SUB32(ctx->r15, ctx->r7);
    AudioHeap_InitPool(rdram, ctx);
        goto after_1;
    // 0x800B7890: subu        $a2, $t7, $a3
    ctx->r6 = SUB32(ctx->r15, ctx->r7);
    after_1:
    // 0x800B7894: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800B7898: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800B789C: jr          $ra
    // 0x800B78A0: nop

    return;
    // 0x800B78A0: nop

;}
RECOMP_FUNC void AudioHeap_InitSessionPools(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B78A4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800B78A8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800B78AC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B78B0: addiu       $a0, $a0, -0x1AB0
    ctx->r4 = ADD32(ctx->r4, -0X1AB0);
    // 0x800B78B4: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800B78B8: lw          $t7, 0x18($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X18);
    // 0x800B78BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800B78C0: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x800B78C4: jal         0x800B7760
    // 0x800B78C8: lw          $a1, 0x0($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X0);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B78C8: lw          $a1, 0x0($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X0);
    after_0:
    // 0x800B78CC: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x800B78D0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B78D4: addiu       $a0, $a0, -0x1A90
    ctx->r4 = ADD32(ctx->r4, -0X1A90);
    // 0x800B78D8: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B78DC: jal         0x800B77D4
    // 0x800B78E0: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    AudioHeap_InitPool(rdram, ctx);
        goto after_1;
    // 0x800B78E0: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    after_1:
    // 0x800B78E4: lw          $t9, 0x18($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X18);
    // 0x800B78E8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B78EC: addiu       $a0, $a0, -0x1AB0
    ctx->r4 = ADD32(ctx->r4, -0X1AB0);
    // 0x800B78F0: jal         0x800B7760
    // 0x800B78F4: lw          $a1, 0xC($t9)
    ctx->r5 = MEM_W(ctx->r25, 0XC);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_2;
    // 0x800B78F4: lw          $a1, 0xC($t9)
    ctx->r5 = MEM_W(ctx->r25, 0XC);
    after_2:
    // 0x800B78F8: lw          $t0, 0x18($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X18);
    // 0x800B78FC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7900: addiu       $a0, $a0, -0x1A60
    ctx->r4 = ADD32(ctx->r4, -0X1A60);
    // 0x800B7904: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7908: jal         0x800B77D4
    // 0x800B790C: lw          $a2, 0xC($t0)
    ctx->r6 = MEM_W(ctx->r8, 0XC);
    AudioHeap_InitPool(rdram, ctx);
        goto after_3;
    // 0x800B790C: lw          $a2, 0xC($t0)
    ctx->r6 = MEM_W(ctx->r8, 0XC);
    after_3:
    // 0x800B7910: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800B7914: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800B7918: jr          $ra
    // 0x800B791C: nop

    return;
    // 0x800B791C: nop

;}
RECOMP_FUNC void AudioHeap_InitCachePools(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B7920: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800B7924: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800B7928: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B792C: addiu       $a0, $a0, -0x1A60
    ctx->r4 = ADD32(ctx->r4, -0X1A60);
    // 0x800B7930: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800B7934: lw          $t7, 0x18($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X18);
    // 0x800B7938: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800B793C: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x800B7940: jal         0x800B7760
    // 0x800B7944: lw          $a1, 0x0($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X0);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B7944: lw          $a1, 0x0($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X0);
    after_0:
    // 0x800B7948: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x800B794C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7950: addiu       $a0, $a0, -0x1A50
    ctx->r4 = ADD32(ctx->r4, -0X1A50);
    // 0x800B7954: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7958: jal         0x800B77D4
    // 0x800B795C: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    AudioHeap_InitPool(rdram, ctx);
        goto after_1;
    // 0x800B795C: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    after_1:
    // 0x800B7960: lw          $t9, 0x18($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X18);
    // 0x800B7964: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7968: addiu       $a0, $a0, -0x1A60
    ctx->r4 = ADD32(ctx->r4, -0X1A60);
    // 0x800B796C: jal         0x800B7760
    // 0x800B7970: lw          $a1, 0x4($t9)
    ctx->r5 = MEM_W(ctx->r25, 0X4);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_2;
    // 0x800B7970: lw          $a1, 0x4($t9)
    ctx->r5 = MEM_W(ctx->r25, 0X4);
    after_2:
    // 0x800B7974: lw          $t0, 0x18($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X18);
    // 0x800B7978: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B797C: addiu       $a0, $a0, -0x1A40
    ctx->r4 = ADD32(ctx->r4, -0X1A40);
    // 0x800B7980: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7984: jal         0x800B77D4
    // 0x800B7988: lw          $a2, 0x4($t0)
    ctx->r6 = MEM_W(ctx->r8, 0X4);
    AudioHeap_InitPool(rdram, ctx);
        goto after_3;
    // 0x800B7988: lw          $a2, 0x4($t0)
    ctx->r6 = MEM_W(ctx->r8, 0X4);
    after_3:
    // 0x800B798C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800B7990: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800B7994: jr          $ra
    // 0x800B7998: nop

    return;
    // 0x800B7998: nop

;}
RECOMP_FUNC void AudioHeap_InitPersistentPoolsAndCaches(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B799C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800B79A0: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B79A4: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800B79A8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B79AC: addiu       $a0, $a0, -0x1A50
    ctx->r4 = ADD32(ctx->r4, -0X1A50);
    // 0x800B79B0: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800B79B4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B79B8: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x800B79BC: jal         0x800B7760
    // 0x800B79C0: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B79C0: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
    after_0:
    // 0x800B79C4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B79C8: addiu       $a0, $a0, -0x1A2C
    ctx->r4 = ADD32(ctx->r4, -0X1A2C);
    // 0x800B79CC: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B79D0: jal         0x800B77D4
    // 0x800B79D4: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    AudioHeap_InitPool(rdram, ctx);
        goto after_1;
    // 0x800B79D4: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    after_1:
    // 0x800B79D8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B79DC: addiu       $a0, $a0, -0x1A50
    ctx->r4 = ADD32(ctx->r4, -0X1A50);
    // 0x800B79E0: jal         0x800B7760
    // 0x800B79E4: lw          $a1, 0x4($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X4);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_2;
    // 0x800B79E4: lw          $a1, 0x4($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x800B79E8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B79EC: addiu       $a0, $a0, -0x185C
    ctx->r4 = ADD32(ctx->r4, -0X185C);
    // 0x800B79F0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B79F4: jal         0x800B77D4
    // 0x800B79F8: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    AudioHeap_InitPool(rdram, ctx);
        goto after_3;
    // 0x800B79F8: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    after_3:
    // 0x800B79FC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A00: addiu       $a0, $a0, -0x1A50
    ctx->r4 = ADD32(ctx->r4, -0X1A50);
    // 0x800B7A04: jal         0x800B7760
    // 0x800B7A08: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_4;
    // 0x800B7A08: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    after_4:
    // 0x800B7A0C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A10: addiu       $a0, $a0, -0x168C
    ctx->r4 = ADD32(ctx->r4, -0X168C);
    // 0x800B7A14: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7A18: jal         0x800B77D4
    // 0x800B7A1C: lw          $a2, 0x8($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X8);
    AudioHeap_InitPool(rdram, ctx);
        goto after_5;
    // 0x800B7A1C: lw          $a2, 0x8($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X8);
    after_5:
    // 0x800B7A20: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A24: jal         0x800B77F4
    // 0x800B7A28: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    AudioHeap_InitPersistentCache(rdram, ctx);
        goto after_6;
    // 0x800B7A28: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    after_6:
    // 0x800B7A2C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A30: jal         0x800B77F4
    // 0x800B7A34: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    AudioHeap_InitPersistentCache(rdram, ctx);
        goto after_7;
    // 0x800B7A34: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    after_7:
    // 0x800B7A38: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A3C: jal         0x800B77F4
    // 0x800B7A40: addiu       $a0, $a0, -0x1690
    ctx->r4 = ADD32(ctx->r4, -0X1690);
    AudioHeap_InitPersistentCache(rdram, ctx);
        goto after_8;
    // 0x800B7A40: addiu       $a0, $a0, -0x1690
    ctx->r4 = ADD32(ctx->r4, -0X1690);
    after_8:
    // 0x800B7A44: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800B7A48: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B7A4C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800B7A50: jr          $ra
    // 0x800B7A54: nop

    return;
    // 0x800B7A54: nop

;}
RECOMP_FUNC void AudioHeap_InitTemporaryPoolsAndCaches(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B7A58: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800B7A5C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B7A60: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800B7A64: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A68: addiu       $a0, $a0, -0x1A40
    ctx->r4 = ADD32(ctx->r4, -0X1A40);
    // 0x800B7A6C: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x800B7A70: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B7A74: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x800B7A78: jal         0x800B7760
    // 0x800B7A7C: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B7A7C: lw          $a1, 0x0($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X0);
    after_0:
    // 0x800B7A80: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A84: addiu       $a0, $a0, -0x1898
    ctx->r4 = ADD32(ctx->r4, -0X1898);
    // 0x800B7A88: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7A8C: jal         0x800B77D4
    // 0x800B7A90: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    AudioHeap_InitPool(rdram, ctx);
        goto after_1;
    // 0x800B7A90: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    after_1:
    // 0x800B7A94: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7A98: addiu       $a0, $a0, -0x1A40
    ctx->r4 = ADD32(ctx->r4, -0X1A40);
    // 0x800B7A9C: jal         0x800B7760
    // 0x800B7AA0: lw          $a1, 0x4($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X4);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_2;
    // 0x800B7AA0: lw          $a1, 0x4($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x800B7AA4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7AA8: addiu       $a0, $a0, -0x16C8
    ctx->r4 = ADD32(ctx->r4, -0X16C8);
    // 0x800B7AAC: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7AB0: jal         0x800B77D4
    // 0x800B7AB4: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    AudioHeap_InitPool(rdram, ctx);
        goto after_3;
    // 0x800B7AB4: lw          $a2, 0x4($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X4);
    after_3:
    // 0x800B7AB8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7ABC: addiu       $a0, $a0, -0x1A40
    ctx->r4 = ADD32(ctx->r4, -0X1A40);
    // 0x800B7AC0: jal         0x800B7760
    // 0x800B7AC4: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_4;
    // 0x800B7AC4: lw          $a1, 0x8($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X8);
    after_4:
    // 0x800B7AC8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7ACC: addiu       $a0, $a0, -0x14F8
    ctx->r4 = ADD32(ctx->r4, -0X14F8);
    // 0x800B7AD0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B7AD4: jal         0x800B77D4
    // 0x800B7AD8: lw          $a2, 0x8($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X8);
    AudioHeap_InitPool(rdram, ctx);
        goto after_5;
    // 0x800B7AD8: lw          $a2, 0x8($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X8);
    after_5:
    // 0x800B7ADC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7AE0: jal         0x800B7808
    // 0x800B7AE4: addiu       $a0, $a0, -0x189C
    ctx->r4 = ADD32(ctx->r4, -0X189C);
    AudioHeap_InitTemporaryCache(rdram, ctx);
        goto after_6;
    // 0x800B7AE4: addiu       $a0, $a0, -0x189C
    ctx->r4 = ADD32(ctx->r4, -0X189C);
    after_6:
    // 0x800B7AE8: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7AEC: jal         0x800B7808
    // 0x800B7AF0: addiu       $a0, $a0, -0x16CC
    ctx->r4 = ADD32(ctx->r4, -0X16CC);
    AudioHeap_InitTemporaryCache(rdram, ctx);
        goto after_7;
    // 0x800B7AF0: addiu       $a0, $a0, -0x16CC
    ctx->r4 = ADD32(ctx->r4, -0X16CC);
    after_7:
    // 0x800B7AF4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B7AF8: jal         0x800B7808
    // 0x800B7AFC: addiu       $a0, $a0, -0x14FC
    ctx->r4 = ADD32(ctx->r4, -0X14FC);
    AudioHeap_InitTemporaryCache(rdram, ctx);
        goto after_8;
    // 0x800B7AFC: addiu       $a0, $a0, -0x14FC
    ctx->r4 = ADD32(ctx->r4, -0X14FC);
    after_8:
    // 0x800B7B00: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800B7B04: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B7B08: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800B7B0C: jr          $ra
    // 0x800B7B10: nop

    return;
    // 0x800B7B10: nop

;}
RECOMP_FUNC void AudioHeap_AllocCached(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B7B14: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x800B7B18: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B7B1C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800B7B20: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800B7B24: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800B7B28: or          $s1, $a2, $zero
    ctx->r17 = ctx->r6 | 0;
    // 0x800B7B2C: lw          $ra, 0x60($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X60);
    // 0x800B7B30: sw          $a1, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r5;
    // 0x800B7B34: addiu       $t4, $zero, 0xC
    ctx->r12 = ADD32(0, 0XC);
    // 0x800B7B38: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800B7B3C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
L_800B7B40:
    // 0x800B7B40: bne         $a3, $zero, L_800B805C
    if (ctx->r7 != 0) {
        // 0x800B7B44: lw          $t7, 0x54($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X54);
            goto L_800B805C;
    }
    // 0x800B7B44: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x800B7B48: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B7B4C: addiu       $t6, $t6, -0x1A30
    ctx->r14 = ADD32(ctx->r14, -0X1A30);
    // 0x800B7B50: bne         $s0, $t6, L_800B7B6C
    if (ctx->r16 != ctx->r14) {
        // 0x800B7B54: addiu       $a3, $s0, 0x194
        ctx->r7 = ADD32(ctx->r16, 0X194);
            goto L_800B7B6C;
    }
    // 0x800B7B54: addiu       $a3, $s0, 0x194
    ctx->r7 = ADD32(ctx->r16, 0X194);
    // 0x800B7B58: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800B7B5C: addiu       $t7, $t7, -0x1448
    ctx->r15 = ADD32(ctx->r15, -0X1448);
    // 0x800B7B60: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x800B7B64: b           L_800B7B8C
    // 0x800B7B68: sb          $zero, 0x33($sp)
    MEM_B(0X33, ctx->r29) = 0;
        goto L_800B7B8C;
    // 0x800B7B68: sb          $zero, 0x33($sp)
    MEM_B(0X33, ctx->r29) = 0;
L_800B7B6C:
    // 0x800B7B6C: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800B7B70: addiu       $t8, $t8, -0x1860
    ctx->r24 = ADD32(ctx->r24, -0X1860);
    // 0x800B7B74: bne         $s0, $t8, L_800B7B8C
    if (ctx->r16 != ctx->r24) {
        // 0x800B7B78: lui         $t5, 0x8004
        ctx->r13 = S32(0X8004 << 16);
            goto L_800B7B8C;
    }
    // 0x800B7B78: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B7B7C: addiu       $t5, $t5, -0x1488
    ctx->r13 = ADD32(ctx->r13, -0X1488);
    // 0x800B7B80: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800B7B84: sb          $t9, 0x33($sp)
    MEM_B(0X33, ctx->r29) = ctx->r25;
    // 0x800B7B88: sw          $t5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r13;
L_800B7B8C:
    // 0x800B7B8C: lw          $a2, 0x1C($a3)
    ctx->r6 = MEM_W(ctx->r7, 0X1C);
    // 0x800B7B90: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B7B94: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B7B98: bne         $a2, $at, L_800B7BA8
    if (ctx->r6 != ctx->r1) {
        // 0x800B7B9C: addiu       $t5, $t5, -0x1488
        ctx->r13 = ADD32(ctx->r13, -0X1488);
            goto L_800B7BA8;
    }
    // 0x800B7B9C: addiu       $t5, $t5, -0x1488
    ctx->r13 = ADD32(ctx->r13, -0X1488);
    // 0x800B7BA0: b           L_800B7BB4
    // 0x800B7BA4: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
        goto L_800B7BB4;
    // 0x800B7BA4: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
L_800B7BA8:
    // 0x800B7BA8: lw          $t6, 0x34($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X34);
    // 0x800B7BAC: addu        $t7, $a2, $t6
    ctx->r15 = ADD32(ctx->r6, ctx->r14);
    // 0x800B7BB0: lbu         $t1, 0x0($t7)
    ctx->r9 = MEM_BU(ctx->r15, 0X0);
L_800B7BB4:
    // 0x800B7BB4: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
    // 0x800B7BB8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B7BBC: lw          $t8, 0x34($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X34);
    // 0x800B7BC0: bne         $a0, $at, L_800B7BD0
    if (ctx->r4 != ctx->r1) {
        // 0x800B7BC4: lbu         $t6, 0x33($sp)
        ctx->r14 = MEM_BU(ctx->r29, 0X33);
            goto L_800B7BD0;
    }
    // 0x800B7BC4: lbu         $t6, 0x33($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X33);
    // 0x800B7BC8: b           L_800B7BD8
    // 0x800B7BCC: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
        goto L_800B7BD8;
    // 0x800B7BCC: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
L_800B7BD0:
    // 0x800B7BD0: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x800B7BD4: lbu         $t2, 0x0($t9)
    ctx->r10 = MEM_BU(ctx->r25, 0X0);
L_800B7BD8:
    // 0x800B7BD8: bne         $t3, $t6, L_800B7C8C
    if (ctx->r11 != ctx->r14) {
        // 0x800B7BDC: sw          $t6, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r14;
            goto L_800B7C8C;
    }
    // 0x800B7BDC: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x800B7BE0: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x800B7BE4: bne         $a0, $t1, L_800B7C30
    if (ctx->r4 != ctx->r9) {
        // 0x800B7BE8: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800B7C30;
    }
    // 0x800B7BE8: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B7BEC: lw          $a1, 0x5548($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X5548);
    // 0x800B7BF0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B7BF4: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7BF8: blez        $a1, L_800B7C20
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800B7BFC: addiu       $t8, $zero, 0x3
        ctx->r24 = ADD32(0, 0X3);
            goto L_800B7C20;
    }
    // 0x800B7BFC: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x800B7C00: lw          $v0, -0x340($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X340);
L_800B7C04:
    // 0x800B7C04: lbu         $t7, 0xB2($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0XB2);
    // 0x800B7C08: beq         $t7, $a2, L_800B7C20
    if (ctx->r15 == ctx->r6) {
        // 0x800B7C0C: nop
    
            goto L_800B7C20;
    }
    // 0x800B7C0C: nop

    // 0x800B7C10: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800B7C14: slt         $at, $v1, $a1
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800B7C18: bne         $at, $zero, L_800B7C04
    if (ctx->r1 != 0) {
        // 0x800B7C1C: addiu       $v0, $v0, 0xC0
        ctx->r2 = ADD32(ctx->r2, 0XC0);
            goto L_800B7C04;
    }
    // 0x800B7C1C: addiu       $v0, $v0, 0xC0
    ctx->r2 = ADD32(ctx->r2, 0XC0);
L_800B7C20:
    // 0x800B7C20: bne         $v1, $a1, L_800B7C30
    if (ctx->r3 != ctx->r5) {
        // 0x800B7C24: addu        $t9, $t5, $a2
        ctx->r25 = ADD32(ctx->r13, ctx->r6);
            goto L_800B7C30;
    }
    // 0x800B7C24: addu        $t9, $t5, $a2
    ctx->r25 = ADD32(ctx->r13, ctx->r6);
    // 0x800B7C28: sb          $t8, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r24;
    // 0x800B7C2C: addiu       $t1, $zero, 0x3
    ctx->r9 = ADD32(0, 0X3);
L_800B7C30:
    // 0x800B7C30: bne         $a0, $t2, L_800B7C8C
    if (ctx->r4 != ctx->r10) {
        // 0x800B7C34: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800B7C8C;
    }
    // 0x800B7C34: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B7C38: lw          $a1, 0x5548($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X5548);
    // 0x800B7C3C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B7C40: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7C44: blez        $a1, L_800B7C70
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800B7C48: nop
    
            goto L_800B7C70;
    }
    // 0x800B7C48: nop

    // 0x800B7C4C: lw          $v0, -0x340($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X340);
    // 0x800B7C50: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
L_800B7C54:
    // 0x800B7C54: lbu         $t6, 0xB2($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0XB2);
    // 0x800B7C58: beq         $t6, $a0, L_800B7C70
    if (ctx->r14 == ctx->r4) {
        // 0x800B7C5C: nop
    
            goto L_800B7C70;
    }
    // 0x800B7C5C: nop

    // 0x800B7C60: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800B7C64: slt         $at, $v1, $a1
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800B7C68: bne         $at, $zero, L_800B7C54
    if (ctx->r1 != 0) {
        // 0x800B7C6C: addiu       $v0, $v0, 0xC0
        ctx->r2 = ADD32(ctx->r2, 0XC0);
            goto L_800B7C54;
    }
    // 0x800B7C6C: addiu       $v0, $v0, 0xC0
    ctx->r2 = ADD32(ctx->r2, 0XC0);
L_800B7C70:
    // 0x800B7C70: bne         $v1, $a1, L_800B7C8C
    if (ctx->r3 != ctx->r5) {
        // 0x800B7C74: nop
    
            goto L_800B7C8C;
    }
    // 0x800B7C74: nop

    // 0x800B7C78: lw          $t8, 0x28($a3)
    ctx->r24 = MEM_W(ctx->r7, 0X28);
    // 0x800B7C7C: addiu       $t7, $zero, 0x3
    ctx->r15 = ADD32(0, 0X3);
    // 0x800B7C80: addiu       $t2, $zero, 0x3
    ctx->r10 = ADD32(0, 0X3);
    // 0x800B7C84: addu        $t9, $t5, $t8
    ctx->r25 = ADD32(ctx->r13, ctx->r24);
    // 0x800B7C88: sb          $t7, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r15;
L_800B7C8C:
    // 0x800B7C8C: bne         $t1, $zero, L_800B7C9C
    if (ctx->r9 != 0) {
        // 0x800B7C90: or          $t5, $t1, $zero
        ctx->r13 = ctx->r9 | 0;
            goto L_800B7C9C;
    }
    // 0x800B7C90: or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    // 0x800B7C94: b           L_800B7E74
    // 0x800B7C98: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_800B7E74;
    // 0x800B7C98: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_800B7C9C:
    // 0x800B7C9C: bne         $t2, $zero, L_800B7CB0
    if (ctx->r10 != 0) {
        // 0x800B7CA0: or          $t1, $t2, $zero
        ctx->r9 = ctx->r10 | 0;
            goto L_800B7CB0;
    }
    // 0x800B7CA0: or          $t1, $t2, $zero
    ctx->r9 = ctx->r10 | 0;
    // 0x800B7CA4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800B7CA8: b           L_800B7E74
    // 0x800B7CAC: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
        goto L_800B7E74;
    // 0x800B7CAC: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
L_800B7CB0:
    // 0x800B7CB0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
    // 0x800B7CB4: bne         $v0, $t5, L_800B7CC4
    if (ctx->r2 != ctx->r13) {
        // 0x800B7CB8: nop
    
            goto L_800B7CC4;
    }
    // 0x800B7CB8: nop

    // 0x800B7CBC: beql        $v0, $t1, L_800B7E78
    if (ctx->r2 == ctx->r9) {
        // 0x800B7CC0: lw          $t9, 0x0($a3)
        ctx->r25 = MEM_W(ctx->r7, 0X0);
            goto L_800B7E78;
    }
    goto skip_0;
    // 0x800B7CC0: lw          $t9, 0x0($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X0);
    skip_0:
L_800B7CC4:
    // 0x800B7CC4: bne         $v0, $t5, L_800B7CD4
    if (ctx->r2 != ctx->r13) {
        // 0x800B7CC8: nop
    
            goto L_800B7CD4;
    }
    // 0x800B7CC8: nop

    // 0x800B7CCC: b           L_800B7E74
    // 0x800B7CD0: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_800B7E74;
    // 0x800B7CD0: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_800B7CD4:
    // 0x800B7CD4: bne         $v0, $t1, L_800B7CE8
    if (ctx->r2 != ctx->r9) {
        // 0x800B7CD8: lw          $t7, 0x20($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X20);
            goto L_800B7CE8;
    }
    // 0x800B7CD8: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
    // 0x800B7CDC: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800B7CE0: b           L_800B7E74
    // 0x800B7CE4: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
        goto L_800B7E74;
    // 0x800B7CE4: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
L_800B7CE8:
    // 0x800B7CE8: bnel        $t7, $zero, L_800B7DA4
    if (ctx->r15 != 0) {
        // 0x800B7CEC: lw          $t7, 0x20($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X20);
            goto L_800B7DA4;
    }
    goto skip_1;
    // 0x800B7CEC: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
    skip_1:
    // 0x800B7CF0: bne         $t0, $t5, L_800B7D48
    if (ctx->r8 != ctx->r13) {
        // 0x800B7CF4: lui         $v0, 0x8004
        ctx->r2 = S32(0X8004 << 16);
            goto L_800B7D48;
    }
    // 0x800B7CF4: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7CF8: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B7CFC: addiu       $v1, $v1, 0x1C8
    ctx->r3 = ADD32(ctx->r3, 0X1C8);
    // 0x800B7D00: addiu       $v0, $v0, -0x338
    ctx->r2 = ADD32(ctx->r2, -0X338);
    // 0x800B7D04: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
L_800B7D08:
    // 0x800B7D08: srl         $t6, $t9, 31
    ctx->r14 = S32(U32(ctx->r25) >> 31);
    // 0x800B7D0C: beql        $t6, $zero, L_800B7D28
    if (ctx->r14 == 0) {
        // 0x800B7D10: addiu       $v0, $v0, 0x140
        ctx->r2 = ADD32(ctx->r2, 0X140);
            goto L_800B7D28;
    }
    goto skip_2;
    // 0x800B7D10: addiu       $v0, $v0, 0x140
    ctx->r2 = ADD32(ctx->r2, 0X140);
    skip_2:
    // 0x800B7D14: lbu         $t8, 0x4($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X4);
    // 0x800B7D18: lw          $t7, 0x1C($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X1C);
    // 0x800B7D1C: beq         $t8, $t7, L_800B7D30
    if (ctx->r24 == ctx->r15) {
        // 0x800B7D20: nop
    
            goto L_800B7D30;
    }
    // 0x800B7D20: nop

    // 0x800B7D24: addiu       $v0, $v0, 0x140
    ctx->r2 = ADD32(ctx->r2, 0X140);
L_800B7D28:
    // 0x800B7D28: bnel        $v0, $v1, L_800B7D08
    if (ctx->r2 != ctx->r3) {
        // 0x800B7D2C: lw          $t9, 0x0($v0)
        ctx->r25 = MEM_W(ctx->r2, 0X0);
            goto L_800B7D08;
    }
    goto skip_3;
    // 0x800B7D2C: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    skip_3:
L_800B7D30:
    // 0x800B7D30: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800B7D34: addiu       $t9, $t9, 0x1C8
    ctx->r25 = ADD32(ctx->r25, 0X1C8);
    // 0x800B7D38: bne         $v0, $t9, L_800B7D48
    if (ctx->r2 != ctx->r25) {
        // 0x800B7D3C: nop
    
            goto L_800B7D48;
    }
    // 0x800B7D3C: nop

    // 0x800B7D40: b           L_800B7E74
    // 0x800B7D44: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_800B7E74;
    // 0x800B7D44: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_800B7D48:
    // 0x800B7D48: bne         $t0, $t1, L_800B7E4C
    if (ctx->r8 != ctx->r9) {
        // 0x800B7D4C: lui         $v0, 0x8004
        ctx->r2 = S32(0X8004 << 16);
            goto L_800B7E4C;
    }
    // 0x800B7D4C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7D50: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B7D54: addiu       $v1, $v1, 0x1C8
    ctx->r3 = ADD32(ctx->r3, 0X1C8);
    // 0x800B7D58: addiu       $v0, $v0, -0x338
    ctx->r2 = ADD32(ctx->r2, -0X338);
    // 0x800B7D5C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
L_800B7D60:
    // 0x800B7D60: srl         $t8, $t6, 31
    ctx->r24 = S32(U32(ctx->r14) >> 31);
    // 0x800B7D64: beql        $t8, $zero, L_800B7D80
    if (ctx->r24 == 0) {
        // 0x800B7D68: addiu       $v0, $v0, 0x140
        ctx->r2 = ADD32(ctx->r2, 0X140);
            goto L_800B7D80;
    }
    goto skip_4;
    // 0x800B7D68: addiu       $v0, $v0, 0x140
    ctx->r2 = ADD32(ctx->r2, 0X140);
    skip_4:
    // 0x800B7D6C: lbu         $t7, 0x4($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X4);
    // 0x800B7D70: lw          $t9, 0x28($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X28);
    // 0x800B7D74: beq         $t7, $t9, L_800B7D88
    if (ctx->r15 == ctx->r25) {
        // 0x800B7D78: nop
    
            goto L_800B7D88;
    }
    // 0x800B7D78: nop

    // 0x800B7D7C: addiu       $v0, $v0, 0x140
    ctx->r2 = ADD32(ctx->r2, 0X140);
L_800B7D80:
    // 0x800B7D80: bnel        $v0, $v1, L_800B7D60
    if (ctx->r2 != ctx->r3) {
        // 0x800B7D84: lw          $t6, 0x0($v0)
        ctx->r14 = MEM_W(ctx->r2, 0X0);
            goto L_800B7D60;
    }
    goto skip_5;
    // 0x800B7D84: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    skip_5:
L_800B7D88:
    // 0x800B7D88: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B7D8C: addiu       $t6, $t6, 0x1C8
    ctx->r14 = ADD32(ctx->r14, 0X1C8);
    // 0x800B7D90: bne         $v0, $t6, L_800B7E4C
    if (ctx->r2 != ctx->r14) {
        // 0x800B7D94: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_800B7E4C;
    }
    // 0x800B7D94: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800B7D98: b           L_800B7E74
    // 0x800B7D9C: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
        goto L_800B7E74;
    // 0x800B7D9C: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x800B7DA0: lw          $t7, 0x20($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X20);
L_800B7DA4:
    // 0x800B7DA4: bne         $t3, $t7, L_800B7E4C
    if (ctx->r11 != ctx->r15) {
        // 0x800B7DA8: nop
    
            goto L_800B7E4C;
    }
    // 0x800B7DA8: nop

    // 0x800B7DAC: bne         $t0, $t5, L_800B7DFC
    if (ctx->r8 != ctx->r13) {
        // 0x800B7DB0: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800B7DFC;
    }
    // 0x800B7DB0: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B7DB4: lw          $a1, 0x5548($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X5548);
    // 0x800B7DB8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B7DBC: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7DC0: blez        $a1, L_800B7DEC
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800B7DC4: nop
    
            goto L_800B7DEC;
    }
    // 0x800B7DC4: nop

    // 0x800B7DC8: lw          $v0, -0x340($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X340);
    // 0x800B7DCC: lw          $a2, 0x1C($a3)
    ctx->r6 = MEM_W(ctx->r7, 0X1C);
L_800B7DD0:
    // 0x800B7DD0: lbu         $t9, 0xB2($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0XB2);
    // 0x800B7DD4: beq         $t9, $a2, L_800B7DEC
    if (ctx->r25 == ctx->r6) {
        // 0x800B7DD8: nop
    
            goto L_800B7DEC;
    }
    // 0x800B7DD8: nop

    // 0x800B7DDC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800B7DE0: slt         $at, $v1, $a1
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800B7DE4: bne         $at, $zero, L_800B7DD0
    if (ctx->r1 != 0) {
        // 0x800B7DE8: addiu       $v0, $v0, 0xC0
        ctx->r2 = ADD32(ctx->r2, 0XC0);
            goto L_800B7DD0;
    }
    // 0x800B7DE8: addiu       $v0, $v0, 0xC0
    ctx->r2 = ADD32(ctx->r2, 0XC0);
L_800B7DEC:
    // 0x800B7DEC: bne         $v1, $a1, L_800B7DFC
    if (ctx->r3 != ctx->r5) {
        // 0x800B7DF0: nop
    
            goto L_800B7DFC;
    }
    // 0x800B7DF0: nop

    // 0x800B7DF4: b           L_800B7E74
    // 0x800B7DF8: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_800B7E74;
    // 0x800B7DF8: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_800B7DFC:
    // 0x800B7DFC: bne         $t0, $t1, L_800B7E4C
    if (ctx->r8 != ctx->r9) {
        // 0x800B7E00: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800B7E4C;
    }
    // 0x800B7E00: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B7E04: lw          $a1, 0x5548($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X5548);
    // 0x800B7E08: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B7E0C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B7E10: blez        $a1, L_800B7E3C
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800B7E14: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_800B7E3C;
    }
    // 0x800B7E14: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800B7E18: lw          $v0, -0x340($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X340);
    // 0x800B7E1C: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
L_800B7E20:
    // 0x800B7E20: lbu         $t6, 0xB2($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0XB2);
    // 0x800B7E24: beq         $t6, $a0, L_800B7E3C
    if (ctx->r14 == ctx->r4) {
        // 0x800B7E28: nop
    
            goto L_800B7E3C;
    }
    // 0x800B7E28: nop

    // 0x800B7E2C: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800B7E30: slt         $at, $v1, $a1
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800B7E34: bne         $at, $zero, L_800B7E20
    if (ctx->r1 != 0) {
        // 0x800B7E38: addiu       $v0, $v0, 0xC0
        ctx->r2 = ADD32(ctx->r2, 0XC0);
            goto L_800B7E20;
    }
    // 0x800B7E38: addiu       $v0, $v0, 0xC0
    ctx->r2 = ADD32(ctx->r2, 0XC0);
L_800B7E3C:
    // 0x800B7E3C: bne         $v1, $a1, L_800B7E4C
    if (ctx->r3 != ctx->r5) {
        // 0x800B7E40: nop
    
            goto L_800B7E4C;
    }
    // 0x800B7E40: nop

    // 0x800B7E44: b           L_800B7E74
    // 0x800B7E48: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
        goto L_800B7E74;
    // 0x800B7E48: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
L_800B7E4C:
    // 0x800B7E4C: beq         $t3, $t5, L_800B7E5C
    if (ctx->r11 == ctx->r13) {
        // 0x800B7E50: nop
    
            goto L_800B7E5C;
    }
    // 0x800B7E50: nop

    // 0x800B7E54: b           L_800B7E74
    // 0x800B7E58: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_800B7E74;
    // 0x800B7E58: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_800B7E5C:
    // 0x800B7E5C: beq         $t3, $t1, L_800B7E6C
    if (ctx->r11 == ctx->r9) {
        // 0x800B7E60: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_800B7E6C;
    }
    // 0x800B7E60: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800B7E64: b           L_800B7E74
    // 0x800B7E68: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
        goto L_800B7E74;
    // 0x800B7E68: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
L_800B7E6C:
    // 0x800B7E6C: b           L_800B8108
    // 0x800B7E70: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B8108;
    // 0x800B7E70: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B7E74:
    // 0x800B7E74: lw          $t9, 0x0($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X0);
L_800B7E78:
    // 0x800B7E78: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B7E7C: lw          $t7, 0x34($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X34);
    // 0x800B7E80: multu       $t9, $t4
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B7E84: mflo        $t6
    ctx->r14 = lo;
    // 0x800B7E88: addu        $t8, $a3, $t6
    ctx->r24 = ADD32(ctx->r7, ctx->r14);
    // 0x800B7E8C: lw          $v0, 0x1C($t8)
    ctx->r2 = MEM_W(ctx->r24, 0X1C);
    // 0x800B7E90: beql        $v0, $at, L_800B7EDC
    if (ctx->r2 == ctx->r1) {
        // 0x800B7E94: lw          $a0, 0x0($a3)
        ctx->r4 = MEM_W(ctx->r7, 0X0);
            goto L_800B7EDC;
    }
    goto skip_6;
    // 0x800B7E94: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
    skip_6:
    // 0x800B7E98: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x800B7E9C: addu        $t9, $t7, $v0
    ctx->r25 = ADD32(ctx->r15, ctx->r2);
    // 0x800B7EA0: sb          $zero, 0x0($t9)
    MEM_B(0X0, ctx->r25) = 0;
    // 0x800B7EA4: bnel        $t3, $a1, L_800B7EDC
    if (ctx->r11 != ctx->r5) {
        // 0x800B7EA8: lw          $a0, 0x0($a3)
        ctx->r4 = MEM_W(ctx->r7, 0X0);
            goto L_800B7EDC;
    }
    goto skip_7;
    // 0x800B7EA8: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
    skip_7:
    // 0x800B7EAC: lw          $t6, 0x0($a3)
    ctx->r14 = MEM_W(ctx->r7, 0X0);
    // 0x800B7EB0: multu       $t6, $t4
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B7EB4: mflo        $t8
    ctx->r24 = lo;
    // 0x800B7EB8: addu        $t7, $a3, $t8
    ctx->r15 = ADD32(ctx->r7, ctx->r24);
    // 0x800B7EBC: lw          $a0, 0x1C($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X1C);
    // 0x800B7EC0: sw          $ra, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r31;
    // 0x800B7EC4: jal         0x800B760C
    // 0x800B7EC8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    AudioHeap_DiscardFont(rdram, ctx);
        goto after_0;
    // 0x800B7EC8: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    after_0:
    // 0x800B7ECC: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B7ED0: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800B7ED4: lw          $ra, 0x60($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X60);
    // 0x800B7ED8: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
L_800B7EDC:
    // 0x800B7EDC: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x800B7EE0: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800B7EE4: beq         $a0, $zero, L_800B7EFC
    if (ctx->r4 == 0) {
        // 0x800B7EE8: addiu       $v1, $s0, 0x198
        ctx->r3 = ADD32(ctx->r16, 0X198);
            goto L_800B7EFC;
    }
    // 0x800B7EE8: addiu       $v1, $s0, 0x198
    ctx->r3 = ADD32(ctx->r16, 0X198);
    // 0x800B7EEC: beq         $a0, $at, L_800B7FB0
    if (ctx->r4 == ctx->r1) {
        // 0x800B7EF0: addiu       $v1, $s0, 0x198
        ctx->r3 = ADD32(ctx->r16, 0X198);
            goto L_800B7FB0;
    }
    // 0x800B7EF0: addiu       $v1, $s0, 0x198
    ctx->r3 = ADD32(ctx->r16, 0X198);
    // 0x800B7EF4: b           L_800B8108
    // 0x800B7EF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B8108;
    // 0x800B7EF8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B7EFC:
    // 0x800B7EFC: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x800B7F00: sw          $ra, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = ctx->r31;
    // 0x800B7F04: sw          $s1, 0x18($a3)
    MEM_W(0X18, ctx->r7) = ctx->r17;
    // 0x800B7F08: sw          $t9, 0x14($a3)
    MEM_W(0X14, ctx->r7) = ctx->r25;
    // 0x800B7F0C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x800B7F10: addu        $v0, $t6, $s1
    ctx->r2 = ADD32(ctx->r14, ctx->r17);
    // 0x800B7F14: sw          $v0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r2;
    // 0x800B7F18: lw          $t8, 0x20($a3)
    ctx->r24 = MEM_W(ctx->r7, 0X20);
    // 0x800B7F1C: lw          $t7, 0x34($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X34);
    // 0x800B7F20: sltu        $at, $t8, $v0
    ctx->r1 = ctx->r24 < ctx->r2 ? 1 : 0;
    // 0x800B7F24: beql        $at, $zero, L_800B7F9C
    if (ctx->r1 == 0) {
        // 0x800B7F28: lw          $v1, 0x14($a3)
        ctx->r3 = MEM_W(ctx->r7, 0X14);
            goto L_800B7F9C;
    }
    goto skip_8;
    // 0x800B7F28: lw          $v1, 0x14($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X14);
    skip_8:
    // 0x800B7F2C: lw          $t9, 0x28($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X28);
    // 0x800B7F30: addu        $t6, $t7, $t9
    ctx->r14 = ADD32(ctx->r15, ctx->r25);
    // 0x800B7F34: beq         $a1, $zero, L_800B7F4C
    if (ctx->r5 == 0) {
        // 0x800B7F38: sb          $zero, 0x0($t6)
        MEM_B(0X0, ctx->r14) = 0;
            goto L_800B7F4C;
    }
    // 0x800B7F38: sb          $zero, 0x0($t6)
    MEM_B(0X0, ctx->r14) = 0;
    // 0x800B7F3C: beql        $a1, $t3, L_800B7F6C
    if (ctx->r5 == ctx->r11) {
        // 0x800B7F40: lw          $a0, 0x28($a3)
        ctx->r4 = MEM_W(ctx->r7, 0X28);
            goto L_800B7F6C;
    }
    goto skip_9;
    // 0x800B7F40: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
    skip_9:
    // 0x800B7F44: b           L_800B7F84
    // 0x800B7F48: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
        goto L_800B7F84;
    // 0x800B7F48: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
L_800B7F4C:
    // 0x800B7F4C: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
    // 0x800B7F50: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800B7F54: jal         0x800B76F0
    // 0x800B7F58: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    AudioHeap_DiscardSequence(rdram, ctx);
        goto after_1;
    // 0x800B7F58: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    after_1:
    // 0x800B7F5C: lw          $v1, 0x24($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X24);
    // 0x800B7F60: b           L_800B7F80
    // 0x800B7F64: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
        goto L_800B7F80;
    // 0x800B7F64: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B7F68: lw          $a0, 0x28($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X28);
L_800B7F6C:
    // 0x800B7F6C: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800B7F70: jal         0x800B760C
    // 0x800B7F74: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    AudioHeap_DiscardFont(rdram, ctx);
        goto after_2;
    // 0x800B7F74: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    after_2:
    // 0x800B7F78: lw          $v1, 0x24($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X24);
    // 0x800B7F7C: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
L_800B7F80:
    // 0x800B7F80: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
L_800B7F84:
    // 0x800B7F84: sw          $t8, 0x28($a3)
    MEM_W(0X28, ctx->r7) = ctx->r24;
    // 0x800B7F88: lw          $t9, 0x8($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X8);
    // 0x800B7F8C: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800B7F90: addu        $t6, $t7, $t9
    ctx->r14 = ADD32(ctx->r15, ctx->r25);
    // 0x800B7F94: sw          $t6, 0x20($a3)
    MEM_W(0X20, ctx->r7) = ctx->r14;
    // 0x800B7F98: lw          $v1, 0x14($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X14);
L_800B7F9C:
    // 0x800B7F9C: lw          $t8, 0x0($a3)
    ctx->r24 = MEM_W(ctx->r7, 0X0);
    // 0x800B7FA0: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800B7FA4: xori        $t7, $t8, 0x1
    ctx->r15 = ctx->r24 ^ 0X1;
    // 0x800B7FA8: b           L_800B8108
    // 0x800B7FAC: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
        goto L_800B8108;
    // 0x800B7FAC: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
L_800B7FB0:
    // 0x800B7FB0: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x800B7FB4: lw          $t6, 0x8($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X8);
    // 0x800B7FB8: sw          $ra, 0x28($a3)
    MEM_W(0X28, ctx->r7) = ctx->r31;
    // 0x800B7FBC: sw          $s1, 0x24($a3)
    MEM_W(0X24, ctx->r7) = ctx->r17;
    // 0x800B7FC0: addu        $t8, $t9, $t6
    ctx->r24 = ADD32(ctx->r25, ctx->r14);
    // 0x800B7FC4: subu        $t7, $t8, $s1
    ctx->r15 = SUB32(ctx->r24, ctx->r17);
    // 0x800B7FC8: addiu       $v0, $t7, -0x10
    ctx->r2 = ADD32(ctx->r15, -0X10);
    // 0x800B7FCC: sw          $v0, 0x20($a3)
    MEM_W(0X20, ctx->r7) = ctx->r2;
    // 0x800B7FD0: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x800B7FD4: lw          $t8, 0x34($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X34);
    // 0x800B7FD8: sltu        $at, $v0, $t6
    ctx->r1 = ctx->r2 < ctx->r14 ? 1 : 0;
    // 0x800B7FDC: beq         $at, $zero, L_800B804C
    if (ctx->r1 == 0) {
        // 0x800B7FE0: nop
    
            goto L_800B804C;
    }
    // 0x800B7FE0: nop

    // 0x800B7FE4: lw          $t7, 0x1C($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X1C);
    // 0x800B7FE8: addu        $t9, $t8, $t7
    ctx->r25 = ADD32(ctx->r24, ctx->r15);
    // 0x800B7FEC: beq         $a1, $zero, L_800B8004
    if (ctx->r5 == 0) {
        // 0x800B7FF0: sb          $zero, 0x0($t9)
        MEM_B(0X0, ctx->r25) = 0;
            goto L_800B8004;
    }
    // 0x800B7FF0: sb          $zero, 0x0($t9)
    MEM_B(0X0, ctx->r25) = 0;
    // 0x800B7FF4: beql        $a1, $t3, L_800B8024
    if (ctx->r5 == ctx->r11) {
        // 0x800B7FF8: lw          $a0, 0x1C($a3)
        ctx->r4 = MEM_W(ctx->r7, 0X1C);
            goto L_800B8024;
    }
    goto skip_10;
    // 0x800B7FF8: lw          $a0, 0x1C($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X1C);
    skip_10:
    // 0x800B7FFC: b           L_800B803C
    // 0x800B8000: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
        goto L_800B803C;
    // 0x800B8000: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
L_800B8004:
    // 0x800B8004: lw          $a0, 0x1C($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X1C);
    // 0x800B8008: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800B800C: jal         0x800B76F0
    // 0x800B8010: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    AudioHeap_DiscardSequence(rdram, ctx);
        goto after_3;
    // 0x800B8010: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    after_3:
    // 0x800B8014: lw          $v1, 0x24($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X24);
    // 0x800B8018: b           L_800B8038
    // 0x800B801C: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
        goto L_800B8038;
    // 0x800B801C: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B8020: lw          $a0, 0x1C($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X1C);
L_800B8024:
    // 0x800B8024: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800B8028: jal         0x800B760C
    // 0x800B802C: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    AudioHeap_DiscardFont(rdram, ctx);
        goto after_4;
    // 0x800B802C: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    after_4:
    // 0x800B8030: lw          $v1, 0x24($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X24);
    // 0x800B8034: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
L_800B8038:
    // 0x800B8038: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
L_800B803C:
    // 0x800B803C: sw          $t6, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = ctx->r14;
    // 0x800B8040: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x800B8044: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x800B8048: lw          $v0, 0x20($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X20);
L_800B804C:
    // 0x800B804C: b           L_800B7F9C
    // 0x800B8050: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_800B7F9C;
    // 0x800B8050: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800B8054: b           L_800B8108
    // 0x800B8058: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B8108;
    // 0x800B8058: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B805C:
    // 0x800B805C: multu       $t7, $s1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r17)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8060: sw          $ra, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r31;
    // 0x800B8064: addiu       $a0, $s0, 0x4
    ctx->r4 = ADD32(ctx->r16, 0X4);
    // 0x800B8068: sw          $a3, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r7;
    // 0x800B806C: mflo        $a1
    ctx->r5 = lo;
    // 0x800B8070: jal         0x800B7760
    // 0x800B8074: nop

    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_5;
    // 0x800B8074: nop

    after_5:
    // 0x800B8078: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x800B807C: addiu       $t4, $zero, 0xC
    ctx->r12 = ADD32(0, 0XC);
    // 0x800B8080: lw          $a3, 0x5C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X5C);
    // 0x800B8084: multu       $t9, $t4
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8088: lw          $ra, 0x60($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X60);
    // 0x800B808C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x800B8090: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800B8094: mflo        $t6
    ctx->r14 = lo;
    // 0x800B8098: addu        $t8, $s0, $t6
    ctx->r24 = ADD32(ctx->r16, ctx->r14);
    // 0x800B809C: bne         $v0, $zero, L_800B80C4
    if (ctx->r2 != 0) {
        // 0x800B80A0: sw          $v0, 0x14($t8)
        MEM_W(0X14, ctx->r24) = ctx->r2;
            goto L_800B80C4;
    }
    // 0x800B80A0: sw          $v0, 0x14($t8)
    MEM_W(0X14, ctx->r24) = ctx->r2;
    // 0x800B80A4: beq         $a3, $t3, L_800B80BC
    if (ctx->r7 == ctx->r11) {
        // 0x800B80A8: nop
    
            goto L_800B80BC;
    }
    // 0x800B80A8: nop

    // 0x800B80AC: bnel        $a3, $t0, L_800B80C8
    if (ctx->r7 != ctx->r8) {
        // 0x800B80B0: lw          $t7, 0x0($s0)
        ctx->r15 = MEM_W(ctx->r16, 0X0);
            goto L_800B80C8;
    }
    goto skip_11;
    // 0x800B80B0: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    skip_11:
    // 0x800B80B4: b           L_800B7B40
    // 0x800B80B8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
        goto L_800B7B40;
    // 0x800B80B8: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
L_800B80BC:
    // 0x800B80BC: b           L_800B8108
    // 0x800B80C0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B8108;
    // 0x800B80C0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B80C4:
    // 0x800B80C4: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
L_800B80C8:
    // 0x800B80C8: multu       $t7, $t4
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B80CC: mflo        $t9
    ctx->r25 = lo;
    // 0x800B80D0: addu        $t6, $s0, $t9
    ctx->r14 = ADD32(ctx->r16, ctx->r25);
    // 0x800B80D4: sw          $ra, 0x1C($t6)
    MEM_W(0X1C, ctx->r14) = ctx->r31;
    // 0x800B80D8: lw          $t8, 0x0($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X0);
    // 0x800B80DC: multu       $t8, $t4
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B80E0: mflo        $t7
    ctx->r15 = lo;
    // 0x800B80E4: addu        $t9, $s0, $t7
    ctx->r25 = ADD32(ctx->r16, ctx->r15);
    // 0x800B80E8: sw          $s1, 0x18($t9)
    MEM_W(0X18, ctx->r25) = ctx->r17;
    // 0x800B80EC: lw          $v1, 0x0($s0)
    ctx->r3 = MEM_W(ctx->r16, 0X0);
    // 0x800B80F0: multu       $v1, $t4
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B80F4: addiu       $t7, $v1, 0x1
    ctx->r15 = ADD32(ctx->r3, 0X1);
    // 0x800B80F8: mflo        $t6
    ctx->r14 = lo;
    // 0x800B80FC: addu        $t8, $s0, $t6
    ctx->r24 = ADD32(ctx->r16, ctx->r14);
    // 0x800B8100: lw          $v0, 0x14($t8)
    ctx->r2 = MEM_W(ctx->r24, 0X14);
    // 0x800B8104: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
L_800B8108:
    // 0x800B8108: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800B810C: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800B8110: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800B8114: jr          $ra
    // 0x800B8118: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x800B8118: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void AudioHeap_SearchRegularCaches(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B811C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
L_800B8120:
    // 0x800B8120: bne         $a1, $zero, L_800B8168
    if (ctx->r5 != 0) {
        // 0x800B8124: or          $a3, $a0, $zero
        ctx->r7 = ctx->r4 | 0;
            goto L_800B8168;
    }
    // 0x800B8124: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800B8128: addiu       $v1, $a0, 0x194
    ctx->r3 = ADD32(ctx->r4, 0X194);
    // 0x800B812C: lw          $t6, 0x1C($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X1C);
    // 0x800B8130: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800B8134: bnel        $a2, $t6, L_800B814C
    if (ctx->r6 != ctx->r14) {
        // 0x800B8138: lw          $t8, 0x28($v1)
        ctx->r24 = MEM_W(ctx->r3, 0X28);
            goto L_800B814C;
    }
    goto skip_0;
    // 0x800B8138: lw          $t8, 0x28($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X28);
    skip_0:
    // 0x800B813C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x800B8140: jr          $ra
    // 0x800B8144: lw          $v0, 0x14($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X14);
    return;
    // 0x800B8144: lw          $v0, 0x14($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X14);
    // 0x800B8148: lw          $t8, 0x28($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X28);
L_800B814C:
    // 0x800B814C: bne         $a2, $t8, L_800B8160
    if (ctx->r6 != ctx->r24) {
        // 0x800B8150: nop
    
            goto L_800B8160;
    }
    // 0x800B8150: nop

    // 0x800B8154: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    // 0x800B8158: jr          $ra
    // 0x800B815C: lw          $v0, 0x20($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X20);
    return;
    // 0x800B815C: lw          $v0, 0x20($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X20);
L_800B8160:
    // 0x800B8160: jr          $ra
    // 0x800B8164: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800B8164: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B8168:
    // 0x800B8168: lw          $t9, 0x0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X0);
    // 0x800B816C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800B8170: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B8174: beq         $t9, $zero, L_800B81A8
    if (ctx->r25 == 0) {
        // 0x800B8178: nop
    
            goto L_800B81A8;
    }
    // 0x800B8178: nop

    // 0x800B817C: lw          $t1, 0x1C($a3)
    ctx->r9 = MEM_W(ctx->r7, 0X1C);
L_800B8180:
    // 0x800B8180: bnel        $a2, $t1, L_800B8194
    if (ctx->r6 != ctx->r9) {
        // 0x800B8184: lw          $t2, 0x0($v0)
        ctx->r10 = MEM_W(ctx->r2, 0X0);
            goto L_800B8194;
    }
    goto skip_1;
    // 0x800B8184: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
    skip_1:
    // 0x800B8188: jr          $ra
    // 0x800B818C: lw          $v0, 0x14($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X14);
    return;
    // 0x800B818C: lw          $v0, 0x14($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X14);
    // 0x800B8190: lw          $t2, 0x0($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X0);
L_800B8194:
    // 0x800B8194: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800B8198: addiu       $a3, $a3, 0xC
    ctx->r7 = ADD32(ctx->r7, 0XC);
    // 0x800B819C: sltu        $at, $v1, $t2
    ctx->r1 = ctx->r3 < ctx->r10 ? 1 : 0;
    // 0x800B81A0: bnel        $at, $zero, L_800B8180
    if (ctx->r1 != 0) {
        // 0x800B81A4: lw          $t1, 0x1C($a3)
        ctx->r9 = MEM_W(ctx->r7, 0X1C);
            goto L_800B8180;
    }
    goto skip_2;
    // 0x800B81A4: lw          $t1, 0x1C($a3)
    ctx->r9 = MEM_W(ctx->r7, 0X1C);
    skip_2:
L_800B81A8:
    // 0x800B81A8: bnel        $a1, $t0, L_800B81BC
    if (ctx->r5 != ctx->r8) {
        // 0x800B81AC: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800B81BC;
    }
    goto skip_3;
    // 0x800B81AC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_3:
    // 0x800B81B0: b           L_800B8120
    // 0x800B81B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
        goto L_800B8120;
    // 0x800B81B4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800B81B8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B81BC:
    // 0x800B81BC: jr          $ra
    // 0x800B81C0: nop

    return;
    // 0x800B81C0: nop

;}
RECOMP_FUNC void func_800B81C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B81C4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800B81C8: lwc1        $f0, -0x43D8($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X43D8);
    // 0x800B81CC: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x800B81D0: addiu       $a0, $sp, 0x14
    ctx->r4 = ADD32(ctx->r29, 0X14);
    // 0x800B81D4: mul.s       $f4, $f14, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800B81D8: addiu       $v0, $sp, 0x2C
    ctx->r2 = ADD32(ctx->r29, 0X2C);
    // 0x800B81DC: addiu       $v1, $a2, 0x4
    ctx->r3 = ADD32(ctx->r6, 0X4);
    // 0x800B81E0: mul.s       $f6, $f12, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x800B81E4: nop

    // 0x800B81E8: mul.s       $f8, $f14, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f12.fl);
    // 0x800B81EC: swc1        $f4, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f4.u32l;
    // 0x800B81F0: swc1        $f6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f6.u32l;
    // 0x800B81F4: mul.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800B81F8: nop

    // 0x800B81FC: mul.s       $f16, $f12, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x800B8200: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    // 0x800B8204: add.s       $f18, $f16, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = ctx->f16.fl + ctx->f14.fl;
    // 0x800B8208: mul.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800B820C: swc1        $f4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f4.u32l;
L_800B8210:
    // 0x800B8210: lwc1        $f6, -0x4($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, -0X4);
    // 0x800B8214: lwc1        $f10, -0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, -0X8);
    // 0x800B8218: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800B821C: mul.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x800B8220: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800B8224: mul.s       $f16, $f14, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x800B8228: add.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x800B822C: cfc1        $t6, $FpcCsr
    ctx->r14 = get_cop1_cs();
    // 0x800B8230: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x800B8234: nop

    // 0x800B8238: cvt.w.s     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = CVT_W_S(ctx->f18.fl);
    // 0x800B823C: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x800B8240: nop

    // 0x800B8244: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x800B8248: beql        $t7, $zero, L_800B8298
    if (ctx->r15 == 0) {
        // 0x800B824C: mfc1        $t7, $f4
        ctx->r15 = (int32_t)ctx->f4.u32l;
            goto L_800B8298;
    }
    goto skip_0;
    // 0x800B824C: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    skip_0:
    // 0x800B8250: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800B8254: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800B8258: sub.s       $f4, $f18, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x800B825C: ctc1        $t7, $FpcCsr
    set_cop1_cs(ctx->r15);
    // 0x800B8260: nop

    // 0x800B8264: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x800B8268: cfc1        $t7, $FpcCsr
    ctx->r15 = get_cop1_cs();
    // 0x800B826C: nop

    // 0x800B8270: andi        $t7, $t7, 0x78
    ctx->r15 = ctx->r15 & 0X78;
    // 0x800B8274: bne         $t7, $zero, L_800B828C
    if (ctx->r15 != 0) {
        // 0x800B8278: nop
    
            goto L_800B828C;
    }
    // 0x800B8278: nop

    // 0x800B827C: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
    // 0x800B8280: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B8284: b           L_800B82A4
    // 0x800B8288: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
        goto L_800B82A4;
    // 0x800B8288: or          $t7, $t7, $at
    ctx->r15 = ctx->r15 | ctx->r1;
L_800B828C:
    // 0x800B828C: b           L_800B82A4
    // 0x800B8290: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
        goto L_800B82A4;
    // 0x800B8290: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x800B8294: mfc1        $t7, $f4
    ctx->r15 = (int32_t)ctx->f4.u32l;
L_800B8298:
    // 0x800B8298: nop

    // 0x800B829C: bltz        $t7, L_800B828C
    if (SIGNED(ctx->r15) < 0) {
        // 0x800B82A0: nop
    
            goto L_800B828C;
    }
    // 0x800B82A0: nop

L_800B82A4:
    // 0x800B82A4: sh          $t7, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r15;
    // 0x800B82A8: ctc1        $t6, $FpcCsr
    set_cop1_cs(ctx->r14);
    // 0x800B82AC: lwc1        $f6, 0x1C($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X1C);
    // 0x800B82B0: lwc1        $f8, 0x18($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X18);
    // 0x800B82B4: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800B82B8: mul.s       $f10, $f6, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x800B82BC: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800B82C0: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800B82C4: mul.s       $f16, $f14, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f8.fl);
    // 0x800B82C8: add.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f16.fl;
    // 0x800B82CC: cfc1        $t8, $FpcCsr
    ctx->r24 = get_cop1_cs();
    // 0x800B82D0: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x800B82D4: nop

    // 0x800B82D8: cvt.w.s     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = CVT_W_S(ctx->f18.fl);
    // 0x800B82DC: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x800B82E0: nop

    // 0x800B82E4: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x800B82E8: beql        $t9, $zero, L_800B8338
    if (ctx->r25 == 0) {
        // 0x800B82EC: mfc1        $t9, $f4
        ctx->r25 = (int32_t)ctx->f4.u32l;
            goto L_800B8338;
    }
    goto skip_1;
    // 0x800B82EC: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    skip_1:
    // 0x800B82F0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800B82F4: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800B82F8: sub.s       $f4, $f18, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f4.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x800B82FC: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x800B8300: nop

    // 0x800B8304: cvt.w.s     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.u32l = CVT_W_S(ctx->f4.fl);
    // 0x800B8308: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x800B830C: nop

    // 0x800B8310: andi        $t9, $t9, 0x78
    ctx->r25 = ctx->r25 & 0X78;
    // 0x800B8314: bne         $t9, $zero, L_800B832C
    if (ctx->r25 != 0) {
        // 0x800B8318: nop
    
            goto L_800B832C;
    }
    // 0x800B8318: nop

    // 0x800B831C: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
    // 0x800B8320: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B8324: b           L_800B8344
    // 0x800B8328: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
        goto L_800B8344;
    // 0x800B8328: or          $t9, $t9, $at
    ctx->r25 = ctx->r25 | ctx->r1;
L_800B832C:
    // 0x800B832C: b           L_800B8344
    // 0x800B8330: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
        goto L_800B8344;
    // 0x800B8330: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x800B8334: mfc1        $t9, $f4
    ctx->r25 = (int32_t)ctx->f4.u32l;
L_800B8338:
    // 0x800B8338: nop

    // 0x800B833C: bltz        $t9, L_800B832C
    if (SIGNED(ctx->r25) < 0) {
        // 0x800B8340: nop
    
            goto L_800B832C;
    }
    // 0x800B8340: nop

L_800B8344:
    // 0x800B8344: sltu        $at, $a0, $v0
    ctx->r1 = ctx->r4 < ctx->r2 ? 1 : 0;
    // 0x800B8348: ctc1        $t8, $FpcCsr
    set_cop1_cs(ctx->r24);
    // 0x800B834C: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x800B8350: bne         $at, $zero, L_800B8210
    if (ctx->r1 != 0) {
        // 0x800B8354: sh          $t9, 0xE($v1)
        MEM_H(0XE, ctx->r3) = ctx->r25;
            goto L_800B8210;
    }
    // 0x800B8354: sh          $t9, 0xE($v1)
    MEM_H(0XE, ctx->r3) = ctx->r25;
    // 0x800B8358: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800B835C: addiu       $a0, $sp, 0xC
    ctx->r4 = ADD32(ctx->r29, 0XC);
    // 0x800B8360: addiu       $v0, $sp, 0x4C
    ctx->r2 = ADD32(ctx->r29, 0X4C);
L_800B8364:
    // 0x800B8364: cfc1        $t0, $FpcCsr
    ctx->r8 = get_cop1_cs();
    // 0x800B8368: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800B836C: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x800B8370: lwc1        $f6, 0x0($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800B8374: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800B8378: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800B837C: cvt.w.s     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = CVT_W_S(ctx->f6.fl);
    // 0x800B8380: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x800B8384: nop

    // 0x800B8388: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x800B838C: beql        $t1, $zero, L_800B83DC
    if (ctx->r9 == 0) {
        // 0x800B8390: mfc1        $t1, $f8
        ctx->r9 = (int32_t)ctx->f8.u32l;
            goto L_800B83DC;
    }
    goto skip_2;
    // 0x800B8390: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    skip_2:
    // 0x800B8394: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800B8398: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800B839C: sub.s       $f8, $f6, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f8.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800B83A0: ctc1        $t1, $FpcCsr
    set_cop1_cs(ctx->r9);
    // 0x800B83A4: nop

    // 0x800B83A8: cvt.w.s     $f8, $f8
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    ctx->f8.u32l = CVT_W_S(ctx->f8.fl);
    // 0x800B83AC: cfc1        $t1, $FpcCsr
    ctx->r9 = get_cop1_cs();
    // 0x800B83B0: nop

    // 0x800B83B4: andi        $t1, $t1, 0x78
    ctx->r9 = ctx->r9 & 0X78;
    // 0x800B83B8: bne         $t1, $zero, L_800B83D0
    if (ctx->r9 != 0) {
        // 0x800B83BC: nop
    
            goto L_800B83D0;
    }
    // 0x800B83BC: nop

    // 0x800B83C0: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
    // 0x800B83C4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B83C8: b           L_800B83E8
    // 0x800B83CC: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
        goto L_800B83E8;
    // 0x800B83CC: or          $t1, $t1, $at
    ctx->r9 = ctx->r9 | ctx->r1;
L_800B83D0:
    // 0x800B83D0: b           L_800B83E8
    // 0x800B83D4: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
        goto L_800B83E8;
    // 0x800B83D4: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
    // 0x800B83D8: mfc1        $t1, $f8
    ctx->r9 = (int32_t)ctx->f8.u32l;
L_800B83DC:
    // 0x800B83DC: nop

    // 0x800B83E0: bltz        $t1, L_800B83D0
    if (SIGNED(ctx->r9) < 0) {
        // 0x800B83E4: nop
    
            goto L_800B83D0;
    }
    // 0x800B83E4: nop

L_800B83E8:
    // 0x800B83E8: sltu        $at, $a0, $v0
    ctx->r1 = ctx->r4 < ctx->r2 ? 1 : 0;
    // 0x800B83EC: ctc1        $t0, $FpcCsr
    set_cop1_cs(ctx->r8);
    // 0x800B83F0: addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // 0x800B83F4: bne         $at, $zero, L_800B8364
    if (ctx->r1 != 0) {
        // 0x800B83F8: sh          $t1, -0x2($v1)
        MEM_H(-0X2, ctx->r3) = ctx->r9;
            goto L_800B8364;
    }
    // 0x800B83F8: sh          $t1, -0x2($v1)
    MEM_H(-0X2, ctx->r3) = ctx->r9;
    // 0x800B83FC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800B8400: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_800B8404:
    // 0x800B8404: slti        $at, $v0, 0x8
    ctx->r1 = SIGNED(ctx->r2) < 0X8 ? 1 : 0;
    // 0x800B8408: bnel        $at, $zero, L_800B8404
    if (ctx->r1 != 0) {
        // 0x800B840C: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_800B8404;
    }
    goto skip_3;
    // 0x800B840C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    skip_3:
    // 0x800B8410: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x800B8414: addiu       $v1, $zero, 0x10
    ctx->r3 = ADD32(0, 0X10);
    // 0x800B8418: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
L_800B841C:
    // 0x800B841C: bnel        $v0, $v1, L_800B841C
    if (ctx->r2 != ctx->r3) {
        // 0x800B8420: addiu       $v0, $v0, 0x4
        ctx->r2 = ADD32(ctx->r2, 0X4);
            goto L_800B841C;
    }
    goto skip_4;
    // 0x800B8420: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    skip_4:
    // 0x800B8424: jr          $ra
    // 0x800B8428: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x800B8428: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void AudioHeap_UpdateReverbs(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B842C: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B8430: lb          $v1, -0x7ABD($v1)
    ctx->r3 = MEM_B(ctx->r3, -0X7ABD);
    // 0x800B8434: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B8438: addiu       $v0, $t6, -0x7EF0
    ctx->r2 = ADD32(ctx->r14, -0X7EF0);
    // 0x800B843C: blez        $v1, L_800B8478
    if (SIGNED(ctx->r3) <= 0) {
        // 0x800B8440: sll         $t7, $v1, 5
        ctx->r15 = S32(ctx->r3 << 5);
            goto L_800B8478;
    }
    // 0x800B8440: sll         $t7, $v1, 5
    ctx->r15 = S32(ctx->r3 << 5);
    // 0x800B8444: addu        $t7, $t7, $v1
    ctx->r15 = ADD32(ctx->r15, ctx->r3);
    // 0x800B8448: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x800B844C: addu        $a0, $t7, $v0
    ctx->r4 = ADD32(ctx->r15, ctx->r2);
L_800B8450:
    // 0x800B8450: lhu         $v1, 0x8($v0)
    ctx->r3 = MEM_HU(ctx->r2, 0X8);
    // 0x800B8454: addiu       $v0, $v0, 0x108
    ctx->r2 = ADD32(ctx->r2, 0X108);
    // 0x800B8458: bgez        $v1, L_800B8468
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800B845C: sra         $t8, $v1, 2
        ctx->r24 = S32(SIGNED(ctx->r3) >> 2);
            goto L_800B8468;
    }
    // 0x800B845C: sra         $t8, $v1, 2
    ctx->r24 = S32(SIGNED(ctx->r3) >> 2);
    // 0x800B8460: addiu       $at, $v1, 0x3
    ctx->r1 = ADD32(ctx->r3, 0X3);
    // 0x800B8464: sra         $t8, $at, 2
    ctx->r24 = S32(SIGNED(ctx->r1) >> 2);
L_800B8468:
    // 0x800B8468: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x800B846C: subu        $t9, $v1, $t8
    ctx->r25 = SUB32(ctx->r3, ctx->r24);
    // 0x800B8470: bne         $at, $zero, L_800B8450
    if (ctx->r1 != 0) {
        // 0x800B8474: sh          $t9, -0x100($v0)
        MEM_H(-0X100, ctx->r2) = ctx->r25;
            goto L_800B8450;
    }
    // 0x800B8474: sh          $t9, -0x100($v0)
    MEM_H(-0X100, ctx->r2) = ctx->r25;
L_800B8478:
    // 0x800B8478: jr          $ra
    // 0x800B847C: nop

    return;
    // 0x800B847C: nop

;}
RECOMP_FUNC void AudioHeap_ResetStep(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8480: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800B8484: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800B8488: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800B848C: addiu       $s2, $s2, -0x1348
    ctx->r18 = ADD32(ctx->r18, -0X1348);
    // 0x800B8490: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
    // 0x800B8494: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800B8498: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800B849C: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x800B84A0: sltiu       $at, $t7, 0x5
    ctx->r1 = ctx->r15 < 0X5 ? 1 : 0;
    // 0x800B84A4: beq         $at, $zero, L_800B8690
    if (ctx->r1 == 0) {
        // 0x800B84A8: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_800B8690;
    }
    // 0x800B84A8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B84AC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800B84B0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800B84B4: addu        $at, $at, $t7
    gpr jr_addend_800B84BC = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800B84B8: lw          $t7, -0x43D4($at)
    ctx->r15 = ADD32(ctx->r1, -0X43D4);
    // 0x800B84BC: jr          $t7
    // 0x800B84C0: nop

    switch (jr_addend_800B84BC >> 2) {
        case 0: goto L_800B8684; break;
        case 1: goto L_800B8658; break;
        case 2: goto L_800B85C0; break;
        case 3: goto L_800B8508; break;
        case 4: goto L_800B84C4; break;
        default: switch_error(__func__, 0x800B84BC, 0x800EBC2C);
    }
    // 0x800B84C0: nop

L_800B84C4:
    // 0x800B84C4: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800B84C8: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800B84CC: addiu       $s1, $s1, 0x1C8
    ctx->r17 = ADD32(ctx->r17, 0X1C8);
    // 0x800B84D0: addiu       $s0, $s0, -0x338
    ctx->r16 = ADD32(ctx->r16, -0X338);
L_800B84D4:
    // 0x800B84D4: jal         0x800BCEE0
    // 0x800B84D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_0;
    // 0x800B84D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800B84DC: addiu       $s0, $s0, 0x140
    ctx->r16 = ADD32(ctx->r16, 0X140);
    // 0x800B84E0: bne         $s0, $s1, L_800B84D4
    if (ctx->r16 != ctx->r17) {
        // 0x800B84E4: nop
    
            goto L_800B84D4;
    }
    // 0x800B84E4: nop

    // 0x800B84E8: lbu         $v0, 0x0($s2)
    ctx->r2 = MEM_BU(ctx->r18, 0X0);
    // 0x800B84EC: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B84F0: addiu       $t0, $t0, -0x1344
    ctx->r8 = ADD32(ctx->r8, -0X1344);
    // 0x800B84F4: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x800B84F8: addiu       $t9, $v0, -0x1
    ctx->r25 = ADD32(ctx->r2, -0X1);
    // 0x800B84FC: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x800B8500: b           L_800B8690
    // 0x800B8504: sb          $t9, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r25;
        goto L_800B8690;
    // 0x800B8504: sb          $t9, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r25;
L_800B8508:
    // 0x800B8508: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B850C: addiu       $t0, $t0, -0x1344
    ctx->r8 = ADD32(ctx->r8, -0X1344);
    // 0x800B8510: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800B8514: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B8518: beq         $v0, $zero, L_800B8530
    if (ctx->r2 == 0) {
        // 0x800B851C: addiu       $t1, $v0, -0x1
        ctx->r9 = ADD32(ctx->r2, -0X1);
            goto L_800B8530;
    }
    // 0x800B851C: addiu       $t1, $v0, -0x1
    ctx->r9 = ADD32(ctx->r2, -0X1);
    // 0x800B8520: jal         0x800B842C
    // 0x800B8524: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    AudioHeap_UpdateReverbs(rdram, ctx);
        goto after_1;
    // 0x800B8524: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    after_1:
    // 0x800B8528: b           L_800B8694
    // 0x800B852C: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
        goto L_800B8694;
    // 0x800B852C: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
L_800B8530:
    // 0x800B8530: lw          $a2, 0x5548($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X5548);
    // 0x800B8534: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800B8538: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B853C: blez        $a2, L_800B85A8
    if (SIGNED(ctx->r6) <= 0) {
        // 0x800B8540: lui         $a3, 0x8004
        ctx->r7 = S32(0X8004 << 16);
            goto L_800B85A8;
    }
    // 0x800B8540: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800B8544: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B8548: addiu       $a1, $a1, -0x340
    ctx->r5 = ADD32(ctx->r5, -0X340);
    // 0x800B854C: addiu       $a3, $a3, 0x5520
    ctx->r7 = ADD32(ctx->r7, 0X5520);
L_800B8550:
    // 0x800B8550: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
    // 0x800B8554: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800B8558: addu        $v0, $t2, $v1
    ctx->r2 = ADD32(ctx->r10, ctx->r3);
    // 0x800B855C: lw          $t3, 0xB0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0XB0);
    // 0x800B8560: srl         $t4, $t3, 31
    ctx->r12 = S32(U32(ctx->r11) >> 31);
    // 0x800B8564: beql        $t4, $zero, L_800B85A0
    if (ctx->r12 == 0) {
        // 0x800B8568: slt         $at, $a0, $a2
        ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r6) ? 1 : 0;
            goto L_800B85A0;
    }
    goto skip_0;
    // 0x800B8568: slt         $at, $a0, $a2
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r6) ? 1 : 0;
    skip_0:
    // 0x800B856C: lbu         $t5, 0x59($v0)
    ctx->r13 = MEM_BU(ctx->r2, 0X59);
    // 0x800B8570: beql        $t5, $zero, L_800B85A0
    if (ctx->r13 == 0) {
        // 0x800B8574: slt         $at, $a0, $a2
        ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r6) ? 1 : 0;
            goto L_800B85A0;
    }
    goto skip_1;
    // 0x800B8574: slt         $at, $a0, $a2
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r6) ? 1 : 0;
    skip_1:
    // 0x800B8578: lwc1        $f4, 0x18($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X18);
    // 0x800B857C: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B8580: swc1        $f4, 0x68($v0)
    MEM_W(0X68, ctx->r2) = ctx->f4.u32l;
    // 0x800B8584: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x800B8588: addu        $v0, $t6, $v1
    ctx->r2 = ADD32(ctx->r14, ctx->r3);
    // 0x800B858C: lbu         $t7, 0x58($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X58);
    // 0x800B8590: ori         $t8, $t7, 0x10
    ctx->r24 = ctx->r15 | 0X10;
    // 0x800B8594: sb          $t8, 0x58($v0)
    MEM_B(0X58, ctx->r2) = ctx->r24;
    // 0x800B8598: lw          $a2, 0x5548($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X5548);
    // 0x800B859C: slt         $at, $a0, $a2
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r6) ? 1 : 0;
L_800B85A0:
    // 0x800B85A0: bne         $at, $zero, L_800B8550
    if (ctx->r1 != 0) {
        // 0x800B85A4: addiu       $v1, $v1, 0xC0
        ctx->r3 = ADD32(ctx->r3, 0XC0);
            goto L_800B8550;
    }
    // 0x800B85A4: addiu       $v1, $v1, 0xC0
    ctx->r3 = ADD32(ctx->r3, 0XC0);
L_800B85A8:
    // 0x800B85A8: lbu         $v0, 0x0($s2)
    ctx->r2 = MEM_BU(ctx->r18, 0X0);
    // 0x800B85AC: addiu       $t9, $zero, 0x10
    ctx->r25 = ADD32(0, 0X10);
    // 0x800B85B0: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x800B85B4: addiu       $t1, $v0, -0x1
    ctx->r9 = ADD32(ctx->r2, -0X1);
    // 0x800B85B8: b           L_800B8690
    // 0x800B85BC: sb          $t1, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r9;
        goto L_800B8690;
    // 0x800B85BC: sb          $t1, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r9;
L_800B85C0:
    // 0x800B85C0: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B85C4: addiu       $t0, $t0, -0x1344
    ctx->r8 = ADD32(ctx->r8, -0X1344);
    // 0x800B85C8: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800B85CC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B85D0: addiu       $v1, $v1, 0x5618
    ctx->r3 = ADD32(ctx->r3, 0X5618);
    // 0x800B85D4: beq         $v0, $zero, L_800B85F0
    if (ctx->r2 == 0) {
        // 0x800B85D8: lui         $a2, 0x8004
        ctx->r6 = S32(0X8004 << 16);
            goto L_800B85F0;
    }
    // 0x800B85D8: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B85DC: addiu       $t2, $v0, -0x1
    ctx->r10 = ADD32(ctx->r2, -0X1);
    // 0x800B85E0: jal         0x800B842C
    // 0x800B85E4: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    AudioHeap_UpdateReverbs(rdram, ctx);
        goto after_2;
    // 0x800B85E4: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    after_2:
    // 0x800B85E8: b           L_800B8694
    // 0x800B85EC: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
        goto L_800B8694;
    // 0x800B85EC: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
L_800B85F0:
    // 0x800B85F0: addiu       $a2, $a2, 0x5624
    ctx->r6 = ADD32(ctx->r6, 0X5624);
    // 0x800B85F4: addiu       $a0, $zero, 0xA00
    ctx->r4 = ADD32(0, 0XA00);
    // 0x800B85F8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B85FC:
    // 0x800B85FC: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x800B8600: addu        $t4, $t3, $v0
    ctx->r12 = ADD32(ctx->r11, ctx->r2);
    // 0x800B8604: sh          $zero, 0x0($t4)
    MEM_H(0X0, ctx->r12) = 0;
    // 0x800B8608: lw          $t5, 0x0($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X0);
    // 0x800B860C: addu        $t6, $t5, $v0
    ctx->r14 = ADD32(ctx->r13, ctx->r2);
    // 0x800B8610: sh          $zero, 0x2($t6)
    MEM_H(0X2, ctx->r14) = 0;
    // 0x800B8614: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800B8618: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800B861C: sh          $zero, 0x4($t8)
    MEM_H(0X4, ctx->r24) = 0;
    // 0x800B8620: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x800B8624: addu        $t1, $t9, $v0
    ctx->r9 = ADD32(ctx->r25, ctx->r2);
    // 0x800B8628: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x800B862C: bne         $v0, $a0, L_800B85FC
    if (ctx->r2 != ctx->r4) {
        // 0x800B8630: sh          $zero, 0x6($t1)
        MEM_H(0X6, ctx->r9) = 0;
            goto L_800B85FC;
    }
    // 0x800B8630: sh          $zero, 0x6($t1)
    MEM_H(0X6, ctx->r9) = 0;
    // 0x800B8634: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800B8638: bnel        $v1, $a2, L_800B85FC
    if (ctx->r3 != ctx->r6) {
        // 0x800B863C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800B85FC;
    }
    goto skip_2;
    // 0x800B863C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_2:
    // 0x800B8640: lbu         $v0, 0x0($s2)
    ctx->r2 = MEM_BU(ctx->r18, 0X0);
    // 0x800B8644: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    // 0x800B8648: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x800B864C: addiu       $t3, $v0, -0x1
    ctx->r11 = ADD32(ctx->r2, -0X1);
    // 0x800B8650: b           L_800B8690
    // 0x800B8654: sb          $t3, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r11;
        goto L_800B8690;
    // 0x800B8654: sb          $t3, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r11;
L_800B8658:
    // 0x800B8658: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B865C: addiu       $t0, $t0, -0x1344
    ctx->r8 = ADD32(ctx->r8, -0X1344);
    // 0x800B8660: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800B8664: beq         $v0, $zero, L_800B8674
    if (ctx->r2 == 0) {
        // 0x800B8668: addiu       $t4, $v0, -0x1
        ctx->r12 = ADD32(ctx->r2, -0X1);
            goto L_800B8674;
    }
    // 0x800B8668: addiu       $t4, $v0, -0x1
    ctx->r12 = ADD32(ctx->r2, -0X1);
    // 0x800B866C: b           L_800B8690
    // 0x800B8670: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
        goto L_800B8690;
    // 0x800B8670: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
L_800B8674:
    // 0x800B8674: lbu         $v0, 0x0($s2)
    ctx->r2 = MEM_BU(ctx->r18, 0X0);
    // 0x800B8678: addiu       $t5, $v0, -0x1
    ctx->r13 = ADD32(ctx->r2, -0X1);
    // 0x800B867C: b           L_800B8690
    // 0x800B8680: sb          $t5, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r13;
        goto L_800B8690;
    // 0x800B8680: sb          $t5, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r13;
L_800B8684:
    // 0x800B8684: jal         0x800B86C4
    // 0x800B8688: nop

    AudioHeap_Init(rdram, ctx);
        goto after_3;
    // 0x800B8688: nop

    after_3:
    // 0x800B868C: sb          $zero, 0x0($s2)
    MEM_B(0X0, ctx->r18) = 0;
L_800B8690:
    // 0x800B8690: lbu         $t6, 0x0($s2)
    ctx->r14 = MEM_BU(ctx->r18, 0X0);
L_800B8694:
    // 0x800B8694: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B8698: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800B869C: slti        $at, $t6, 0x3
    ctx->r1 = SIGNED(ctx->r14) < 0X3 ? 1 : 0;
    // 0x800B86A0: beql        $at, $zero, L_800B86B4
    if (ctx->r1 == 0) {
        // 0x800B86A4: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_800B86B4;
    }
    goto skip_3;
    // 0x800B86A4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    skip_3:
    // 0x800B86A8: b           L_800B86B4
    // 0x800B86AC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B86B4;
    // 0x800B86AC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800B86B0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_800B86B4:
    // 0x800B86B4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800B86B8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800B86BC: jr          $ra
    // 0x800B86C0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x800B86C0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void AudioHeap_Init(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B86C4: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800B86C8: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B86CC: lbu         $t6, -0x1347($t6)
    ctx->r14 = MEM_BU(ctx->r14, -0X1347);
    // 0x800B86D0: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800B86D4: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800B86D8: addiu       $t8, $t8, -0x377C
    ctx->r24 = ADD32(ctx->r24, -0X377C);
    // 0x800B86DC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B86E0: sll         $t7, $t6, 5
    ctx->r15 = S32(ctx->r14 << 5);
    // 0x800B86E4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800B86E8: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800B86EC: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800B86F0: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800B86F4: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800B86F8: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800B86FC: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800B8700: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800B8704: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B8708: addu        $s6, $t7, $t8
    ctx->r22 = ADD32(ctx->r15, ctx->r24);
    // 0x800B870C: sw          $zero, 0x52F0($at)
    MEM_W(0X52F0, ctx->r1) = 0;
    // 0x800B8710: lw          $t9, 0x0($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X0);
    // 0x800B8714: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800B8718: addiu       $s4, $s4, 0x5520
    ctx->r20 = ADD32(ctx->r20, 0X5520);
    // 0x800B871C: sh          $t9, 0x2($s4)
    MEM_H(0X2, ctx->r20) = ctx->r25;
    // 0x800B8720: jal         0x800CA5A0
    // 0x800B8724: andi        $a0, $t9, 0xFFFF
    ctx->r4 = ctx->r25 & 0XFFFF;
    osAiSetFrequency_recomp(rdram, ctx);
        goto after_0;
    // 0x800B8724: andi        $a0, $t9, 0xFFFF
    ctx->r4 = ctx->r25 & 0XFFFF;
    after_0:
    // 0x800B8728: sh          $v0, 0x4($s4)
    MEM_H(0X4, ctx->r20) = ctx->r2;
    // 0x800B872C: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B8730: lw          $t5, 0x5614($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X5614);
    // 0x800B8734: lhu         $a3, 0x2($s4)
    ctx->r7 = MEM_HU(ctx->r20, 0X2);
    // 0x800B8738: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800B873C: addiu       $t4, $t4, 0x5548
    ctx->r12 = ADD32(ctx->r12, 0X5548);
    // 0x800B8740: div         $zero, $a3, $t5
    lo = S32(S64(S32(ctx->r7)) / S64(S32(ctx->r13))); hi = S32(S64(S32(ctx->r7)) % S64(S32(ctx->r13)));
    // 0x800B8744: mflo        $t6
    ctx->r14 = lo;
    // 0x800B8748: addiu       $t7, $t6, 0xF
    ctx->r15 = ADD32(ctx->r14, 0XF);
    // 0x800B874C: andi        $t8, $t7, 0xFFF0
    ctx->r24 = ctx->r15 & 0XFFF0;
    // 0x800B8750: sh          $t8, 0x6($s4)
    MEM_H(0X6, ctx->r20) = ctx->r24;
    // 0x800B8754: lh          $v1, 0x6($s4)
    ctx->r3 = MEM_H(ctx->r20, 0X6);
    // 0x800B8758: mtc1        $a3, $f6
    ctx->f6.u32l = ctx->r7;
    // 0x800B875C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8760: addiu       $t0, $v1, 0x10
    ctx->r8 = ADD32(ctx->r3, 0X10);
    // 0x800B8764: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800B8768: addiu       $t9, $v1, -0x10
    ctx->r25 = ADD32(ctx->r3, -0X10);
    // 0x800B876C: sh          $t9, 0xA($s4)
    MEM_H(0XA, ctx->r20) = ctx->r25;
    // 0x800B8770: sh          $t0, 0x8($s4)
    MEM_H(0X8, ctx->r20) = ctx->r8;
    // 0x800B8774: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800B8778: addiu       $s2, $s2, 0x5544
    ctx->r18 = ADD32(ctx->r18, 0X5544);
    // 0x800B877C: addiu       $a0, $a0, -0x14C0
    ctx->r4 = ADD32(ctx->r4, -0X14C0);
    // 0x800B8780: bne         $t5, $zero, L_800B878C
    if (ctx->r13 != 0) {
        // 0x800B8784: nop
    
            goto L_800B878C;
    }
    // 0x800B8784: nop

    // 0x800B8788: break       7
    do_break(2148239240);
L_800B878C:
    // 0x800B878C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B8790: bne         $t5, $at, L_800B87A4
    if (ctx->r13 != ctx->r1) {
        // 0x800B8794: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800B87A4;
    }
    // 0x800B8794: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B8798: bne         $a3, $at, L_800B87A4
    if (ctx->r7 != ctx->r1) {
        // 0x800B879C: nop
    
            goto L_800B87A4;
    }
    // 0x800B879C: nop

    // 0x800B87A0: break       6
    do_break(2148239264);
L_800B87A4:
    // 0x800B87A4: addiu       $at, $zero, 0xA0
    ctx->r1 = ADD32(0, 0XA0);
    // 0x800B87A8: div         $zero, $t0, $at
    lo = S32(S64(S32(ctx->r8)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r8)) % S64(S32(ctx->r1)));
    // 0x800B87AC: mflo        $t5
    ctx->r13 = lo;
    // 0x800B87B0: addiu       $t6, $t5, 0x1
    ctx->r14 = ADD32(ctx->r13, 0X1);
    // 0x800B87B4: sh          $t6, 0xC($s4)
    MEM_H(0XC, ctx->r20) = ctx->r14;
    // 0x800B87B8: lh          $a2, 0xC($s4)
    ctx->r6 = MEM_H(ctx->r20, 0XC);
    // 0x800B87BC: div         $zero, $v1, $a2
    lo = S32(S64(S32(ctx->r3)) / S64(S32(ctx->r6))); hi = S32(S64(S32(ctx->r3)) % S64(S32(ctx->r6)));
    // 0x800B87C0: bne         $a2, $zero, L_800B87CC
    if (ctx->r6 != 0) {
        // 0x800B87C4: nop
    
            goto L_800B87CC;
    }
    // 0x800B87C4: nop

    // 0x800B87C8: break       7
    do_break(2148239304);
L_800B87CC:
    // 0x800B87CC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B87D0: bne         $a2, $at, L_800B87E4
    if (ctx->r6 != ctx->r1) {
        // 0x800B87D4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800B87E4;
    }
    // 0x800B87D4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B87D8: bne         $v1, $at, L_800B87E4
    if (ctx->r3 != ctx->r1) {
        // 0x800B87DC: nop
    
            goto L_800B87E4;
    }
    // 0x800B87DC: nop

    // 0x800B87E0: break       6
    do_break(2148239328);
L_800B87E4:
    // 0x800B87E4: lui         $at, 0x46FA
    ctx->r1 = S32(0X46FA << 16);
    // 0x800B87E8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800B87EC: mflo        $t7
    ctx->r15 = lo;
    // 0x800B87F0: andi        $t8, $t7, 0xFFF8
    ctx->r24 = ctx->r15 & 0XFFF8;
    // 0x800B87F4: div.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f4.fl, ctx->f8.fl);
    // 0x800B87F8: sh          $t8, 0xE($s4)
    MEM_H(0XE, ctx->r20) = ctx->r24;
    // 0x800B87FC: lh          $t1, 0xE($s4)
    ctx->r9 = MEM_H(ctx->r20, 0XE);
    // 0x800B8800: mtc1        $a2, $f16
    ctx->f16.u32l = ctx->r6;
    // 0x800B8804: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800B8808: addiu       $t9, $t1, 0x8
    ctx->r25 = ADD32(ctx->r9, 0X8);
    // 0x800B880C: cvt.s.w     $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    ctx->f0.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800B8810: addiu       $t5, $t1, -0x8
    ctx->r13 = ADD32(ctx->r9, -0X8);
    // 0x800B8814: sh          $t9, 0x10($s4)
    MEM_H(0X10, ctx->r20) = ctx->r25;
    // 0x800B8818: sh          $t5, 0x12($s4)
    MEM_H(0X12, ctx->r20) = ctx->r13;
    // 0x800B881C: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800B8820: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x800B8824: swc1        $f10, 0x14($s4)
    MEM_W(0X14, ctx->r20) = ctx->f10.u32l;
    // 0x800B8828: lwc1        $f18, -0x43C0($at)
    ctx->f18.u32l = MEM_W(ctx->r1, -0X43C0);
    // 0x800B882C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800B8830: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800B8834: div.s       $f6, $f18, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800B8838: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B883C: div.s       $f8, $f4, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800B8840: swc1        $f6, 0x1C($s4)
    MEM_W(0X1C, ctx->r20) = ctx->f6.u32l;
    // 0x800B8844: swc1        $f8, 0x18($s4)
    MEM_W(0X18, ctx->r20) = ctx->f8.u32l;
    // 0x800B8848: lbu         $t6, 0x5($s6)
    ctx->r14 = MEM_BU(ctx->r22, 0X5);
    // 0x800B884C: sw          $t6, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r14;
    // 0x800B8850: lhu         $t7, 0xC($s6)
    ctx->r15 = MEM_HU(ctx->r22, 0XC);
    // 0x800B8854: lh          $t8, -0x1D10($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X1D10);
    // 0x800B8858: sh          $t7, -0x7AC0($at)
    MEM_H(-0X7AC0, ctx->r1) = ctx->r15;
    // 0x800B885C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800B8860: lwc1        $f10, -0x43BC($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X43BC);
    // 0x800B8864: mtc1        $t8, $f18
    ctx->f18.u32l = ctx->r24;
    // 0x800B8868: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B886C: mul.s       $f16, $f0, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x800B8870: lwc1        $f8, 0x5610($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X5610);
    // 0x800B8874: cvt.s.w     $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    ctx->f6.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800B8878: div.s       $f4, $f16, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = DIV_S(ctx->f16.fl, ctx->f6.fl);
    // 0x800B887C: div.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f4.fl, ctx->f8.fl);
    // 0x800B8880: cfc1        $t9, $FpcCsr
    ctx->r25 = get_cop1_cs();
    // 0x800B8884: ctc1        $t5, $FpcCsr
    set_cop1_cs(ctx->r13);
    // 0x800B8888: nop

    // 0x800B888C: cvt.w.s     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.u32l = CVT_W_S(ctx->f10.fl);
    // 0x800B8890: cfc1        $t5, $FpcCsr
    ctx->r13 = get_cop1_cs();
    // 0x800B8894: nop

    // 0x800B8898: andi        $at, $t5, 0x4
    ctx->r1 = ctx->r13 & 0X4;
    // 0x800B889C: andi        $t5, $t5, 0x78
    ctx->r13 = ctx->r13 & 0X78;
    // 0x800B88A0: beq         $t5, $zero, L_800B88EC
    if (ctx->r13 == 0) {
        // 0x800B88A4: lui         $at, 0x4F00
        ctx->r1 = S32(0X4F00 << 16);
            goto L_800B88EC;
    }
    // 0x800B88A4: lui         $at, 0x4F00
    ctx->r1 = S32(0X4F00 << 16);
    // 0x800B88A8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x800B88AC: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x800B88B0: sub.s       $f18, $f10, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f18.fl;
    // 0x800B88B4: ctc1        $t5, $FpcCsr
    set_cop1_cs(ctx->r13);
    // 0x800B88B8: nop

    // 0x800B88BC: cvt.w.s     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.u32l = CVT_W_S(ctx->f18.fl);
    // 0x800B88C0: cfc1        $t5, $FpcCsr
    ctx->r13 = get_cop1_cs();
    // 0x800B88C4: nop

    // 0x800B88C8: andi        $t5, $t5, 0x78
    ctx->r13 = ctx->r13 & 0X78;
    // 0x800B88CC: bne         $t5, $zero, L_800B88E4
    if (ctx->r13 != 0) {
        // 0x800B88D0: nop
    
            goto L_800B88E4;
    }
    // 0x800B88D0: nop

    // 0x800B88D4: mfc1        $t5, $f18
    ctx->r13 = (int32_t)ctx->f18.u32l;
    // 0x800B88D8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B88DC: b           L_800B88FC
    // 0x800B88E0: or          $t5, $t5, $at
    ctx->r13 = ctx->r13 | ctx->r1;
        goto L_800B88FC;
    // 0x800B88E0: or          $t5, $t5, $at
    ctx->r13 = ctx->r13 | ctx->r1;
L_800B88E4:
    // 0x800B88E4: b           L_800B88FC
    // 0x800B88E8: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
        goto L_800B88FC;
    // 0x800B88E8: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
L_800B88EC:
    // 0x800B88EC: mfc1        $t5, $f18
    ctx->r13 = (int32_t)ctx->f18.u32l;
    // 0x800B88F0: nop

    // 0x800B88F4: bltz        $t5, L_800B88E4
    if (SIGNED(ctx->r13) < 0) {
        // 0x800B88F8: nop
    
            goto L_800B88E4;
    }
    // 0x800B88F8: nop

L_800B88FC:
    // 0x800B88FC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B8900: sh          $t5, 0x554C($at)
    MEM_H(0X554C, ctx->r1) = ctx->r13;
    // 0x800B8904: lbu         $t6, 0x4($s6)
    ctx->r14 = MEM_BU(ctx->r22, 0X4);
    // 0x800B8908: lh          $t8, 0x8($s4)
    ctx->r24 = MEM_H(ctx->r20, 0X8);
    // 0x800B890C: ctc1        $t9, $FpcCsr
    set_cop1_cs(ctx->r25);
    // 0x800B8910: sh          $t6, 0x0($s4)
    MEM_H(0X0, ctx->r20) = ctx->r14;
    // 0x800B8914: lh          $a1, 0x0($s4)
    ctx->r5 = MEM_H(ctx->r20, 0X0);
    // 0x800B8918: lh          $t5, 0xA($s4)
    ctx->r13 = MEM_H(ctx->r20, 0XA);
    // 0x800B891C: multu       $v1, $a1
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8920: mflo        $t7
    ctx->r15 = lo;
    // 0x800B8924: sh          $t7, 0x6($s4)
    MEM_H(0X6, ctx->r20) = ctx->r15;
    // 0x800B8928: nop

    // 0x800B892C: multu       $t8, $a1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8930: lw          $t8, 0x0($t4)
    ctx->r24 = MEM_W(ctx->r12, 0X0);
    // 0x800B8934: mflo        $t9
    ctx->r25 = lo;
    // 0x800B8938: sh          $t9, 0x8($s4)
    MEM_H(0X8, ctx->r20) = ctx->r25;
    // 0x800B893C: sll         $t9, $t8, 4
    ctx->r25 = S32(ctx->r24 << 4);
    // 0x800B8940: multu       $t5, $a1
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8944: mflo        $t6
    ctx->r14 = lo;
    // 0x800B8948: sh          $t6, 0xA($s4)
    MEM_H(0XA, ctx->r20) = ctx->r14;
    // 0x800B894C: nop

    // 0x800B8950: multu       $a2, $a1
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8954: mflo        $t7
    ctx->r15 = lo;
    // 0x800B8958: sh          $t7, 0xC($s4)
    MEM_H(0XC, ctx->r20) = ctx->r15;
    // 0x800B895C: lh          $t5, 0xC($s4)
    ctx->r13 = MEM_H(ctx->r20, 0XC);
    // 0x800B8960: lbu         $t7, 0x6($s6)
    ctx->r15 = MEM_BU(ctx->r22, 0X6);
    // 0x800B8964: multu       $t9, $t5
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8968: sll         $t8, $t7, 5
    ctx->r24 = S32(ctx->r15 << 5);
    // 0x800B896C: mflo        $t6
    ctx->r14 = lo;
    // 0x800B8970: addu        $t9, $t6, $t8
    ctx->r25 = ADD32(ctx->r14, ctx->r24);
    // 0x800B8974: addiu       $t5, $t9, 0x3C8
    ctx->r13 = ADD32(ctx->r25, 0X3C8);
    // 0x800B8978: sw          $t5, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r13;
    // 0x800B897C: lw          $t6, 0x14($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X14);
    // 0x800B8980: lw          $t7, 0x10($s6)
    ctx->r15 = MEM_W(ctx->r22, 0X10);
    // 0x800B8984: lw          $t9, 0x1C($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X1C);
    // 0x800B8988: lw          $t8, 0x18($s6)
    ctx->r24 = MEM_W(ctx->r22, 0X18);
    // 0x800B898C: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B8990: lw          $t5, -0x1AA8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X1AA8);
    // 0x800B8994: addu        $s0, $t7, $t6
    ctx->r16 = ADD32(ctx->r15, ctx->r14);
    // 0x800B8998: addu        $s1, $t8, $t9
    ctx->r17 = ADD32(ctx->r24, ctx->r25);
    // 0x800B899C: addu        $t2, $s0, $s1
    ctx->r10 = ADD32(ctx->r16, ctx->r17);
    // 0x800B89A0: subu        $t3, $t5, $t2
    ctx->r11 = SUB32(ctx->r13, ctx->r10);
    // 0x800B89A4: addiu       $t3, $t3, -0x100
    ctx->r11 = ADD32(ctx->r11, -0X100);
    // 0x800B89A8: sw          $t3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r11;
    // 0x800B89AC: jal         0x800B78A4
    // 0x800B89B0: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
    AudioHeap_InitSessionPools(rdram, ctx);
        goto after_1;
    // 0x800B89B0: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
    after_1:
    // 0x800B89B4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B89B8: addiu       $a0, $a0, -0x14B0
    ctx->r4 = ADD32(ctx->r4, -0X14B0);
    // 0x800B89BC: sw          $s0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r16;
    // 0x800B89C0: jal         0x800B7920
    // 0x800B89C4: sw          $s1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r17;
    AudioHeap_InitCachePools(rdram, ctx);
        goto after_2;
    // 0x800B89C4: sw          $s1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r17;
    after_2:
    // 0x800B89C8: lw          $t7, 0x10($s6)
    ctx->r15 = MEM_W(ctx->r22, 0X10);
    // 0x800B89CC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B89D0: addiu       $a0, $a0, -0x14A8
    ctx->r4 = ADD32(ctx->r4, -0X14A8);
    // 0x800B89D4: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x800B89D8: lw          $t6, 0x14($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X14);
    // 0x800B89DC: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
    // 0x800B89E0: jal         0x800B799C
    // 0x800B89E4: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    AudioHeap_InitPersistentPoolsAndCaches(rdram, ctx);
        goto after_3;
    // 0x800B89E4: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    after_3:
    // 0x800B89E8: lw          $t8, 0x18($s6)
    ctx->r24 = MEM_W(ctx->r22, 0X18);
    // 0x800B89EC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B89F0: addiu       $a0, $a0, -0x1498
    ctx->r4 = ADD32(ctx->r4, -0X1498);
    // 0x800B89F4: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x800B89F8: lw          $t9, 0x1C($s6)
    ctx->r25 = MEM_W(ctx->r22, 0X1C);
    // 0x800B89FC: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
    // 0x800B8A00: jal         0x800B7A58
    // 0x800B8A04: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    AudioHeap_InitTemporaryPoolsAndCaches(rdram, ctx);
        goto after_4;
    // 0x800B8A04: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    after_4:
    // 0x800B8A08: jal         0x800B75BC
    // 0x800B8A0C: nop

    AudioHeap_ResetLoadStatus(rdram, ctx);
        goto after_5;
    // 0x800B8A0C: nop

    after_5:
    // 0x800B8A10: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B8A14: lw          $a1, 0x5548($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X5548);
    // 0x800B8A18: lui         $s3, 0x8004
    ctx->r19 = S32(0X8004 << 16);
    // 0x800B8A1C: addiu       $s3, $s3, -0x1A90
    ctx->r19 = ADD32(ctx->r19, -0X1A90);
    // 0x800B8A20: sll         $t5, $a1, 2
    ctx->r13 = S32(ctx->r5 << 2);
    // 0x800B8A24: subu        $t5, $t5, $a1
    ctx->r13 = SUB32(ctx->r13, ctx->r5);
    // 0x800B8A28: sll         $a1, $t5, 6
    ctx->r5 = S32(ctx->r13 << 6);
    // 0x800B8A2C: jal         0x800B7760
    // 0x800B8A30: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_6;
    // 0x800B8A30: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_6:
    // 0x800B8A34: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B8A38: jal         0x800BBD1C
    // 0x800B8A3C: sw          $v0, -0x340($at)
    MEM_W(-0X340, ctx->r1) = ctx->r2;
    Audio_NoteInitAll(rdram, ctx);
        goto after_7;
    // 0x800B8A3C: sw          $v0, -0x340($at)
    MEM_W(-0X340, ctx->r1) = ctx->r2;
    after_7:
    // 0x800B8A40: jal         0x800BB350
    // 0x800B8A44: nop

    Audio_InitNoteFreeList(rdram, ctx);
        goto after_8;
    // 0x800B8A44: nop

    after_8:
    // 0x800B8A48: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B8A4C: lw          $t6, 0x5548($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5548);
    // 0x800B8A50: lh          $t7, 0xC($s4)
    ctx->r15 = MEM_H(ctx->r20, 0XC);
    // 0x800B8A54: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8A58: multu       $t7, $t6
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B8A5C: mflo        $a1
    ctx->r5 = lo;
    // 0x800B8A60: sll         $t8, $a1, 4
    ctx->r24 = S32(ctx->r5 << 4);
    // 0x800B8A64: jal         0x800B7760
    // 0x800B8A68: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_9;
    // 0x800B8A68: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
    after_9:
    // 0x800B8A6C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B8A70: lui         $s0, 0x8004
    ctx->r16 = S32(0X8004 << 16);
    // 0x800B8A74: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800B8A78: sw          $v0, -0x7ABC($at)
    MEM_W(-0X7ABC, ctx->r1) = ctx->r2;
    // 0x800B8A7C: addiu       $s1, $s1, 0x5568
    ctx->r17 = ADD32(ctx->r17, 0X5568);
    // 0x800B8A80: addiu       $s0, $s0, 0x5560
    ctx->r16 = ADD32(ctx->r16, 0X5560);
L_800B8A84:
    // 0x800B8A84: lw          $a1, 0x0($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X0);
    // 0x800B8A88: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8A8C: sll         $t9, $a1, 3
    ctx->r25 = S32(ctx->r5 << 3);
    // 0x800B8A90: jal         0x800B7760
    // 0x800B8A94: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_10;
    // 0x800B8A94: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    after_10:
    // 0x800B8A98: addiu       $s0, $s0, 0x4
    ctx->r16 = ADD32(ctx->r16, 0X4);
    // 0x800B8A9C: bne         $s0, $s1, L_800B8A84
    if (ctx->r16 != ctx->r17) {
        // 0x800B8AA0: sw          $v0, -0x4($s0)
        MEM_W(-0X4, ctx->r16) = ctx->r2;
            goto L_800B8A84;
    }
    // 0x800B8AA0: sw          $v0, -0x4($s0)
    MEM_W(-0X4, ctx->r16) = ctx->r2;
    // 0x800B8AA4: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800B8AA8: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B8AAC: addiu       $v0, $v0, -0x7AD0
    ctx->r2 = ADD32(ctx->r2, -0X7AD0);
    // 0x800B8AB0: addiu       $s2, $s2, -0x7EF0
    ctx->r18 = ADD32(ctx->r18, -0X7EF0);
L_800B8AB4:
    // 0x800B8AB4: addiu       $s2, $s2, 0x108
    ctx->r18 = ADD32(ctx->r18, 0X108);
    // 0x800B8AB8: sltu        $at, $s2, $v0
    ctx->r1 = ctx->r18 < ctx->r2 ? 1 : 0;
    // 0x800B8ABC: bne         $at, $zero, L_800B8AB4
    if (ctx->r1 != 0) {
        // 0x800B8AC0: sb          $zero, -0x107($s2)
        MEM_B(-0X107, ctx->r18) = 0;
            goto L_800B8AB4;
    }
    // 0x800B8AC0: sb          $zero, -0x107($s2)
    MEM_B(-0X107, ctx->r18) = 0;
    // 0x800B8AC4: lbu         $t5, 0x6($s6)
    ctx->r13 = MEM_BU(ctx->r22, 0X6);
    // 0x800B8AC8: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800B8ACC: addiu       $s7, $s7, -0x7ABD
    ctx->r23 = ADD32(ctx->r23, -0X7ABD);
    // 0x800B8AD0: sb          $t5, 0x0($s7)
    MEM_B(0X0, ctx->r23) = ctx->r13;
    // 0x800B8AD4: lb          $t7, 0x0($s7)
    ctx->r15 = MEM_B(ctx->r23, 0X0);
    // 0x800B8AD8: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800B8ADC: addiu       $s2, $s2, -0x7EF0
    ctx->r18 = ADD32(ctx->r18, -0X7EF0);
    // 0x800B8AE0: blez        $t7, L_800B8C60
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800B8AE4: or          $s5, $zero, $zero
        ctx->r21 = 0 | 0;
            goto L_800B8C60;
    }
    // 0x800B8AE4: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x800B8AE8: addiu       $fp, $zero, 0x8
    ctx->r30 = ADD32(0, 0X8);
    // 0x800B8AEC: lw          $t6, 0x8($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X8);
L_800B8AF0:
    // 0x800B8AF0: sll         $t8, $s5, 2
    ctx->r24 = S32(ctx->r21 << 2);
    // 0x800B8AF4: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8AF8: addu        $v0, $t6, $t8
    ctx->r2 = ADD32(ctx->r14, ctx->r24);
    // 0x800B8AFC: lbu         $t9, 0x1($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X1);
    // 0x800B8B00: sll         $t5, $t9, 6
    ctx->r13 = S32(ctx->r25 << 6);
    // 0x800B8B04: sh          $t5, 0x6($s2)
    MEM_H(0X6, ctx->r18) = ctx->r13;
    // 0x800B8B08: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    // 0x800B8B0C: andi        $a1, $t5, 0xFFFF
    ctx->r5 = ctx->r13 & 0XFFFF;
    // 0x800B8B10: sll         $t8, $a1, 1
    ctx->r24 = S32(ctx->r5 << 1);
    // 0x800B8B14: sb          $t7, 0x4($s2)
    MEM_B(0X4, ctx->r18) = ctx->r15;
    // 0x800B8B18: lhu         $t6, 0x2($v0)
    ctx->r14 = MEM_HU(ctx->r2, 0X2);
    // 0x800B8B1C: sb          $fp, 0x1($s2)
    MEM_B(0X1, ctx->r18) = ctx->r30;
    // 0x800B8B20: or          $a1, $t8, $zero
    ctx->r5 = ctx->r24 | 0;
    // 0x800B8B24: jal         0x800B7760
    // 0x800B8B28: sh          $t6, 0x8($s2)
    MEM_H(0X8, ctx->r18) = ctx->r14;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_11;
    // 0x800B8B28: sh          $t6, 0x8($s2)
    MEM_H(0X8, ctx->r18) = ctx->r14;
    after_11:
    // 0x800B8B2C: lhu         $a1, 0x6($s2)
    ctx->r5 = MEM_HU(ctx->r18, 0X6);
    // 0x800B8B30: sw          $v0, 0x18($s2)
    MEM_W(0X18, ctx->r18) = ctx->r2;
    // 0x800B8B34: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8B38: sll         $t9, $a1, 1
    ctx->r25 = S32(ctx->r5 << 1);
    // 0x800B8B3C: jal         0x800B7760
    // 0x800B8B40: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_12;
    // 0x800B8B40: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    after_12:
    // 0x800B8B44: lbu         $v1, 0x4($s2)
    ctx->r3 = MEM_BU(ctx->r18, 0X4);
    // 0x800B8B48: lhu         $t5, 0x6($s2)
    ctx->r13 = MEM_HU(ctx->r18, 0X6);
    // 0x800B8B4C: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x800B8B50: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800B8B54: sw          $v0, 0x1C($s2)
    MEM_W(0X1C, ctx->r18) = ctx->r2;
    // 0x800B8B58: sw          $zero, 0xC($s2)
    MEM_W(0XC, ctx->r18) = 0;
    // 0x800B8B5C: sw          $zero, 0x10($s2)
    MEM_W(0X10, ctx->r18) = 0;
    // 0x800B8B60: sb          $zero, 0x3($s2)
    MEM_B(0X3, ctx->r18) = 0;
    // 0x800B8B64: sb          $t7, 0x2($s2)
    MEM_B(0X2, ctx->r18) = ctx->r15;
    // 0x800B8B68: beq         $v1, $at, L_800B8C48
    if (ctx->r3 == ctx->r1) {
        // 0x800B8B6C: sw          $t5, 0x14($s2)
        MEM_W(0X14, ctx->r18) = ctx->r13;
            goto L_800B8C48;
    }
    // 0x800B8B6C: sw          $t5, 0x14($s2)
    MEM_W(0X14, ctx->r18) = ctx->r13;
    // 0x800B8B70: ori         $t8, $zero, 0x8000
    ctx->r24 = 0 | 0X8000;
    // 0x800B8B74: div         $zero, $t8, $v1
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r3))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r3)));
    // 0x800B8B78: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800B8B7C: mflo        $t9
    ctx->r25 = lo;
    // 0x800B8B80: sb          $t6, 0x0($s2)
    MEM_B(0X0, ctx->r18) = ctx->r14;
    // 0x800B8B84: bne         $v1, $zero, L_800B8B90
    if (ctx->r3 != 0) {
        // 0x800B8B88: nop
    
            goto L_800B8B90;
    }
    // 0x800B8B88: nop

    // 0x800B8B8C: break       7
    do_break(2148240268);
L_800B8B90:
    // 0x800B8B90: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800B8B94: bne         $v1, $at, L_800B8BA8
    if (ctx->r3 != ctx->r1) {
        // 0x800B8B98: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800B8BA8;
    }
    // 0x800B8B98: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800B8B9C: bne         $t8, $at, L_800B8BA8
    if (ctx->r24 != ctx->r1) {
        // 0x800B8BA0: nop
    
            goto L_800B8BA8;
    }
    // 0x800B8BA0: nop

    // 0x800B8BA4: break       6
    do_break(2148240292);
L_800B8BA8:
    // 0x800B8BA8: sh          $t9, 0xA($s2)
    MEM_H(0XA, ctx->r18) = ctx->r25;
    // 0x800B8BAC: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8BB0: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    // 0x800B8BB4: jal         0x800B7760
    // 0x800B8BB8: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_13;
    // 0x800B8BB8: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    after_13:
    // 0x800B8BBC: sw          $v0, 0x20($s2)
    MEM_W(0X20, ctx->r18) = ctx->r2;
    // 0x800B8BC0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8BC4: jal         0x800B7760
    // 0x800B8BC8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_14;
    // 0x800B8BC8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_14:
    // 0x800B8BCC: sw          $v0, 0x24($s2)
    MEM_W(0X24, ctx->r18) = ctx->r2;
    // 0x800B8BD0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8BD4: jal         0x800B7760
    // 0x800B8BD8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_15;
    // 0x800B8BD8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_15:
    // 0x800B8BDC: sw          $v0, 0x28($s2)
    MEM_W(0X28, ctx->r18) = ctx->r2;
    // 0x800B8BE0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8BE4: jal         0x800B7760
    // 0x800B8BE8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_16;
    // 0x800B8BE8: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_16:
    // 0x800B8BEC: lh          $t5, 0xC($s4)
    ctx->r13 = MEM_H(ctx->r20, 0XC);
    // 0x800B8BF0: sw          $v0, 0x2C($s2)
    MEM_W(0X2C, ctx->r18) = ctx->r2;
    // 0x800B8BF4: blezl       $t5, L_800B8C4C
    if (SIGNED(ctx->r13) <= 0) {
        // 0x800B8BF8: lb          $t9, 0x0($s7)
        ctx->r25 = MEM_B(ctx->r23, 0X0);
            goto L_800B8C4C;
    }
    goto skip_0;
    // 0x800B8BF8: lb          $t9, 0x0($s7)
    ctx->r25 = MEM_B(ctx->r23, 0X0);
    skip_0:
    // 0x800B8BFC: or          $s0, $s2, $zero
    ctx->r16 = ctx->r18 | 0;
    // 0x800B8C00: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
L_800B8C04:
    // 0x800B8C04: jal         0x800B7760
    // 0x800B8C08: addiu       $a1, $zero, 0x280
    ctx->r5 = ADD32(0, 0X280);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_17;
    // 0x800B8C08: addiu       $a1, $zero, 0x280
    ctx->r5 = ADD32(0, 0X280);
    after_17:
    // 0x800B8C0C: addiu       $t7, $v0, 0x140
    ctx->r15 = ADD32(ctx->r2, 0X140);
    // 0x800B8C10: sw          $v0, 0x34($s0)
    MEM_W(0X34, ctx->r16) = ctx->r2;
    // 0x800B8C14: sw          $t7, 0x38($s0)
    MEM_W(0X38, ctx->r16) = ctx->r15;
    // 0x800B8C18: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800B8C1C: jal         0x800B7760
    // 0x800B8C20: addiu       $a1, $zero, 0x280
    ctx->r5 = ADD32(0, 0X280);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_18;
    // 0x800B8C20: addiu       $a1, $zero, 0x280
    ctx->r5 = ADD32(0, 0X280);
    after_18:
    // 0x800B8C24: addiu       $t6, $v0, 0x140
    ctx->r14 = ADD32(ctx->r2, 0X140);
    // 0x800B8C28: sw          $v0, 0x98($s0)
    MEM_W(0X98, ctx->r16) = ctx->r2;
    // 0x800B8C2C: sw          $t6, 0x9C($s0)
    MEM_W(0X9C, ctx->r16) = ctx->r14;
    // 0x800B8C30: lh          $t8, 0xC($s4)
    ctx->r24 = MEM_H(ctx->r20, 0XC);
    // 0x800B8C34: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800B8C38: addiu       $s0, $s0, 0x14
    ctx->r16 = ADD32(ctx->r16, 0X14);
    // 0x800B8C3C: slt         $at, $s1, $t8
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x800B8C40: bnel        $at, $zero, L_800B8C04
    if (ctx->r1 != 0) {
        // 0x800B8C44: or          $a0, $s3, $zero
        ctx->r4 = ctx->r19 | 0;
            goto L_800B8C04;
    }
    goto skip_1;
    // 0x800B8C44: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    skip_1:
L_800B8C48:
    // 0x800B8C48: lb          $t9, 0x0($s7)
    ctx->r25 = MEM_B(ctx->r23, 0X0);
L_800B8C4C:
    // 0x800B8C4C: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
    // 0x800B8C50: addiu       $s2, $s2, 0x108
    ctx->r18 = ADD32(ctx->r18, 0X108);
    // 0x800B8C54: slt         $at, $s5, $t9
    ctx->r1 = SIGNED(ctx->r21) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800B8C58: bnel        $at, $zero, L_800B8AF0
    if (ctx->r1 != 0) {
        // 0x800B8C5C: lw          $t6, 0x8($s6)
        ctx->r14 = MEM_W(ctx->r22, 0X8);
            goto L_800B8AF0;
    }
    goto skip_2;
    // 0x800B8C5C: lw          $t6, 0x8($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X8);
    skip_2:
L_800B8C60:
    // 0x800B8C60: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8C64: jal         0x800B9244
    // 0x800B8C68: lw          $a0, 0x5548($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5548);
    AudioLoad_InitSampleDmaBuffers(rdram, ctx);
        goto after_19;
    // 0x800B8C68: lw          $a0, 0x5548($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5548);
    after_19:
    // 0x800B8C6C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800B8C70: jal         0x800B7450
    // 0x800B8C74: lh          $a1, 0xE($s4)
    ctx->r5 = MEM_H(ctx->r20, 0XE);
    BuildVolRampingsTBL(rdram, ctx);
        goto after_20;
    // 0x800B8C74: lh          $a1, 0xE($s4)
    ctx->r5 = MEM_H(ctx->r20, 0XE);
    after_20:
    // 0x800B8C78: jal         0x800C6740
    // 0x800B8C7C: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_21;
    // 0x800B8C7C: nop

    after_21:
    // 0x800B8C80: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800B8C84: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B8C88: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800B8C8C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800B8C90: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800B8C94: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800B8C98: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800B8C9C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800B8CA0: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800B8CA4: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800B8CA8: jr          $ra
    // 0x800B8CAC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800B8CAC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void Audio_DmaCopyImmediate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8CB0: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800B8CB4: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800B8CB8: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800B8CBC: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800B8CC0: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x800B8CC4: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x800B8CC8: jal         0x800CA2C0
    // 0x800B8CCC: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    osInvalDCache_recomp(rdram, ctx);
        goto after_0;
    // 0x800B8CCC: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    after_0:
    // 0x800B8CD0: lw          $t6, 0x2C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X2C);
    // 0x800B8CD4: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800B8CD8: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800B8CDC: addiu       $t8, $t8, 0x4DB8
    ctx->r24 = ADD32(ctx->r24, 0X4DB8);
    // 0x800B8CE0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8CE4: addiu       $a0, $a0, 0x4DD8
    ctx->r4 = ADD32(ctx->r4, 0X4DD8);
    // 0x800B8CE8: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    // 0x800B8CEC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800B8CF0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800B8CF4: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B8CF8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x800B8CFC: jal         0x800CA370
    // 0x800B8D00: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    osPiStartDma_recomp(rdram, ctx);
        goto after_1;
    // 0x800B8D00: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    after_1:
    // 0x800B8D04: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8D08: addiu       $a0, $a0, 0x4DB8
    ctx->r4 = ADD32(ctx->r4, 0X4DB8);
    // 0x800B8D0C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800B8D10: jal         0x800C5C60
    // 0x800B8D14: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_2;
    // 0x800B8D14: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800B8D18: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800B8D1C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800B8D20: jr          $ra
    // 0x800B8D24: nop

    return;
    // 0x800B8D24: nop

;}
RECOMP_FUNC void Audio_DmaCopyAsync(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8D28: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800B8D2C: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800B8D30: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800B8D34: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800B8D38: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x800B8D3C: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x800B8D40: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
    // 0x800B8D44: jal         0x800CA2C0
    // 0x800B8D48: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    osInvalDCache_recomp(rdram, ctx);
        goto after_0;
    // 0x800B8D48: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    after_0:
    // 0x800B8D4C: lw          $t6, 0x2C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X2C);
    // 0x800B8D50: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800B8D54: lw          $t8, 0x34($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X34);
    // 0x800B8D58: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    // 0x800B8D5C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800B8D60: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800B8D64: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B8D68: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x800B8D6C: sw          $t7, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r15;
    // 0x800B8D70: jal         0x800CA370
    // 0x800B8D74: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    osPiStartDma_recomp(rdram, ctx);
        goto after_1;
    // 0x800B8D74: sw          $t8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r24;
    after_1:
    // 0x800B8D78: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800B8D7C: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800B8D80: jr          $ra
    // 0x800B8D84: nop

    return;
    // 0x800B8D84: nop

;}
RECOMP_FUNC void Audio_DmaPartialCopyAsync(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8D88: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800B8D8C: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800B8D90: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x800B8D94: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x800B8D98: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x800B8D9C: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    // 0x800B8DA0: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    // 0x800B8DA4: slti        $at, $v0, 0x1000
    ctx->r1 = SIGNED(ctx->r2) < 0X1000 ? 1 : 0;
    // 0x800B8DA8: bne         $at, $zero, L_800B8DB8
    if (ctx->r1 != 0) {
        // 0x800B8DAC: or          $s0, $v0, $zero
        ctx->r16 = ctx->r2 | 0;
            goto L_800B8DB8;
    }
    // 0x800B8DAC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x800B8DB0: b           L_800B8DB8
    // 0x800B8DB4: addiu       $s0, $zero, 0x1000
    ctx->r16 = ADD32(0, 0X1000);
        goto L_800B8DB8;
    // 0x800B8DB4: addiu       $s0, $zero, 0x1000
    ctx->r16 = ADD32(0, 0X1000);
L_800B8DB8:
    // 0x800B8DB8: subu        $t6, $v0, $s0
    ctx->r14 = SUB32(ctx->r2, ctx->r16);
    // 0x800B8DBC: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x800B8DC0: lw          $t7, 0x34($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X34);
    // 0x800B8DC4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800B8DC8: jal         0x800CA2C0
    // 0x800B8DCC: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    osInvalDCache_recomp(rdram, ctx);
        goto after_0;
    // 0x800B8DCC: lw          $a0, 0x0($t7)
    ctx->r4 = MEM_W(ctx->r15, 0X0);
    after_0:
    // 0x800B8DD0: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800B8DD4: lw          $t9, 0x34($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X34);
    // 0x800B8DD8: lw          $t1, 0x3C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X3C);
    // 0x800B8DDC: lw          $a3, 0x0($t8)
    ctx->r7 = MEM_W(ctx->r24, 0X0);
    // 0x800B8DE0: lw          $t0, 0x0($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X0);
    // 0x800B8DE4: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800B8DE8: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800B8DEC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800B8DF0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800B8DF4: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x800B8DF8: jal         0x800CA370
    // 0x800B8DFC: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    osPiStartDma_recomp(rdram, ctx);
        goto after_1;
    // 0x800B8DFC: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    after_1:
    // 0x800B8E00: lw          $v1, 0x30($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X30);
    // 0x800B8E04: lw          $v0, 0x34($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X34);
    // 0x800B8E08: lw          $t2, 0x0($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X0);
    // 0x800B8E0C: addu        $t3, $t2, $s0
    ctx->r11 = ADD32(ctx->r10, ctx->r16);
    // 0x800B8E10: sw          $t3, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r11;
    // 0x800B8E14: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x800B8E18: addu        $t5, $t4, $s0
    ctx->r13 = ADD32(ctx->r12, ctx->r16);
    // 0x800B8E1C: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x800B8E20: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800B8E24: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x800B8E28: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800B8E2C: jr          $ra
    // 0x800B8E30: nop

    return;
    // 0x800B8E30: nop

;}
RECOMP_FUNC void AudioLoad_DecreaseSampleDmaTtls(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8E34: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B8E38: addiu       $a1, $a1, 0x52F4
    ctx->r5 = ADD32(ctx->r5, 0X52F4);
    // 0x800B8E3C: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x800B8E40: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8E44: addiu       $a0, $a0, 0x4DF0
    ctx->r4 = ADD32(ctx->r4, 0X4DF0);
    // 0x800B8E48: beq         $v1, $zero, L_800B8EAC
    if (ctx->r3 == 0) {
        // 0x800B8E4C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800B8EAC;
    }
    // 0x800B8E4C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800B8E50: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800B8E54: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B8E58: addiu       $a2, $a2, 0x5502
    ctx->r6 = ADD32(ctx->r6, 0X5502);
    // 0x800B8E5C: addiu       $a3, $a3, 0x5300
    ctx->r7 = ADD32(ctx->r7, 0X5300);
    // 0x800B8E60: lbu         $v1, 0xE($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0XE);
L_800B8E64:
    // 0x800B8E64: beq         $v1, $zero, L_800B8E94
    if (ctx->r3 == 0) {
        // 0x800B8E68: addiu       $t6, $v1, -0x1
        ctx->r14 = ADD32(ctx->r3, -0X1);
            goto L_800B8E94;
    }
    // 0x800B8E68: addiu       $t6, $v1, -0x1
    ctx->r14 = ADD32(ctx->r3, -0X1);
    // 0x800B8E6C: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x800B8E70: bne         $t7, $zero, L_800B8E94
    if (ctx->r15 != 0) {
        // 0x800B8E74: sb          $t6, 0xE($a0)
        MEM_B(0XE, ctx->r4) = ctx->r14;
            goto L_800B8E94;
    }
    // 0x800B8E74: sb          $t6, 0xE($a0)
    MEM_B(0XE, ctx->r4) = ctx->r14;
    // 0x800B8E78: lbu         $v1, 0x0($a2)
    ctx->r3 = MEM_BU(ctx->r6, 0X0);
    // 0x800B8E7C: lbu         $t8, 0x0($a2)
    ctx->r24 = MEM_BU(ctx->r6, 0X0);
    // 0x800B8E80: addu        $t9, $a3, $v1
    ctx->r25 = ADD32(ctx->r7, ctx->r3);
    // 0x800B8E84: sb          $v0, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r2;
    // 0x800B8E88: addiu       $t0, $v1, 0x1
    ctx->r8 = ADD32(ctx->r3, 0X1);
    // 0x800B8E8C: sb          $t0, 0x0($a2)
    MEM_B(0X0, ctx->r6) = ctx->r8;
    // 0x800B8E90: sb          $t8, 0xD($a0)
    MEM_B(0XD, ctx->r4) = ctx->r24;
L_800B8E94:
    // 0x800B8E94: lw          $v1, 0x0($a1)
    ctx->r3 = MEM_W(ctx->r5, 0X0);
    // 0x800B8E98: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B8E9C: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x800B8EA0: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x800B8EA4: bnel        $at, $zero, L_800B8E64
    if (ctx->r1 != 0) {
        // 0x800B8EA8: lbu         $v1, 0xE($a0)
        ctx->r3 = MEM_BU(ctx->r4, 0XE);
            goto L_800B8E64;
    }
    goto skip_0;
    // 0x800B8EA8: lbu         $v1, 0xE($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0XE);
    skip_0:
L_800B8EAC:
    // 0x800B8EAC: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B8EB0: addiu       $a1, $a1, 0x52F0
    ctx->r5 = ADD32(ctx->r5, 0X52F0);
    // 0x800B8EB4: lw          $t1, 0x0($a1)
    ctx->r9 = MEM_W(ctx->r5, 0X0);
    // 0x800B8EB8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800B8EBC: sll         $t2, $v1, 4
    ctx->r10 = S32(ctx->r3 << 4);
    // 0x800B8EC0: sltu        $at, $v1, $t1
    ctx->r1 = ctx->r3 < ctx->r9 ? 1 : 0;
    // 0x800B8EC4: beq         $at, $zero, L_800B8F30
    if (ctx->r1 == 0) {
        // 0x800B8EC8: lui         $t3, 0x8004
        ctx->r11 = S32(0X8004 << 16);
            goto L_800B8F30;
    }
    // 0x800B8EC8: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800B8ECC: addiu       $t3, $t3, 0x4DF0
    ctx->r11 = ADD32(ctx->r11, 0X4DF0);
    // 0x800B8ED0: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800B8ED4: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B8ED8: addiu       $a2, $a2, 0x5503
    ctx->r6 = ADD32(ctx->r6, 0X5503);
    // 0x800B8EDC: addiu       $a3, $a3, 0x5400
    ctx->r7 = ADD32(ctx->r7, 0X5400);
    // 0x800B8EE0: addu        $a0, $t2, $t3
    ctx->r4 = ADD32(ctx->r10, ctx->r11);
    // 0x800B8EE4: lbu         $v1, 0xE($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0XE);
L_800B8EE8:
    // 0x800B8EE8: beq         $v1, $zero, L_800B8F18
    if (ctx->r3 == 0) {
        // 0x800B8EEC: addiu       $t4, $v1, -0x1
        ctx->r12 = ADD32(ctx->r3, -0X1);
            goto L_800B8F18;
    }
    // 0x800B8EEC: addiu       $t4, $v1, -0x1
    ctx->r12 = ADD32(ctx->r3, -0X1);
    // 0x800B8EF0: andi        $t5, $t4, 0xFF
    ctx->r13 = ctx->r12 & 0XFF;
    // 0x800B8EF4: bne         $t5, $zero, L_800B8F18
    if (ctx->r13 != 0) {
        // 0x800B8EF8: sb          $t4, 0xE($a0)
        MEM_B(0XE, ctx->r4) = ctx->r12;
            goto L_800B8F18;
    }
    // 0x800B8EF8: sb          $t4, 0xE($a0)
    MEM_B(0XE, ctx->r4) = ctx->r12;
    // 0x800B8EFC: lbu         $v1, 0x0($a2)
    ctx->r3 = MEM_BU(ctx->r6, 0X0);
    // 0x800B8F00: lbu         $t6, 0x0($a2)
    ctx->r14 = MEM_BU(ctx->r6, 0X0);
    // 0x800B8F04: addu        $t7, $a3, $v1
    ctx->r15 = ADD32(ctx->r7, ctx->r3);
    // 0x800B8F08: sb          $v0, 0x0($t7)
    MEM_B(0X0, ctx->r15) = ctx->r2;
    // 0x800B8F0C: addiu       $t8, $v1, 0x1
    ctx->r24 = ADD32(ctx->r3, 0X1);
    // 0x800B8F10: sb          $t8, 0x0($a2)
    MEM_B(0X0, ctx->r6) = ctx->r24;
    // 0x800B8F14: sb          $t6, 0xD($a0)
    MEM_B(0XD, ctx->r4) = ctx->r14;
L_800B8F18:
    // 0x800B8F18: lw          $t9, 0x0($a1)
    ctx->r25 = MEM_W(ctx->r5, 0X0);
    // 0x800B8F1C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B8F20: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x800B8F24: sltu        $at, $v0, $t9
    ctx->r1 = ctx->r2 < ctx->r25 ? 1 : 0;
    // 0x800B8F28: bnel        $at, $zero, L_800B8EE8
    if (ctx->r1 != 0) {
        // 0x800B8F2C: lbu         $v1, 0xE($a0)
        ctx->r3 = MEM_BU(ctx->r4, 0XE);
            goto L_800B8EE8;
    }
    goto skip_1;
    // 0x800B8F2C: lbu         $v1, 0xE($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0XE);
    skip_1:
L_800B8F30:
    // 0x800B8F30: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B8F34: jr          $ra
    // 0x800B8F38: sw          $zero, 0x52F8($at)
    MEM_W(0X52F8, ctx->r1) = 0;
    return;
    // 0x800B8F38: sw          $zero, 0x52F8($at)
    MEM_W(0X52F8, ctx->r1) = 0;
;}
RECOMP_FUNC void AudioLoad_DmaSampleData(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B8F3C: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x800B8F40: sw          $s1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r17;
    // 0x800B8F44: sw          $s0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r16;
    // 0x800B8F48: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x800B8F4C: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800B8F50: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800B8F54: sw          $a3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r7;
    // 0x800B8F58: bne         $a2, $zero, L_800B8F80
    if (ctx->r6 != 0) {
        // 0x800B8F5C: or          $t1, $zero, $zero
        ctx->r9 = 0 | 0;
            goto L_800B8F80;
    }
    // 0x800B8F5C: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x800B8F60: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800B8F64: lw          $t7, 0x52F4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X52F4);
    // 0x800B8F68: lbu         $v1, 0x0($a3)
    ctx->r3 = MEM_BU(ctx->r7, 0X0);
    // 0x800B8F6C: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800B8F70: addiu       $t4, $t4, 0x4DF0
    ctx->r12 = ADD32(ctx->r12, 0X4DF0);
    // 0x800B8F74: sltu        $at, $v1, $t7
    ctx->r1 = ctx->r3 < ctx->r15 ? 1 : 0;
    // 0x800B8F78: bne         $at, $zero, L_800B90D0
    if (ctx->r1 != 0) {
        // 0x800B8F7C: sll         $t6, $v1, 4
        ctx->r14 = S32(ctx->r3 << 4);
            goto L_800B90D0;
    }
    // 0x800B8F7C: sll         $t6, $v1, 4
    ctx->r14 = S32(ctx->r3 << 4);
L_800B8F80:
    // 0x800B8F80: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B8F84: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B8F88: lw          $a1, 0x52F0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X52F0);
    // 0x800B8F8C: lw          $a0, 0x52F4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X52F4);
    // 0x800B8F90: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800B8F94: addiu       $t9, $t9, 0x4DF0
    ctx->r25 = ADD32(ctx->r25, 0X4DF0);
    // 0x800B8F98: sltu        $at, $a0, $a1
    ctx->r1 = ctx->r4 < ctx->r5 ? 1 : 0;
    // 0x800B8F9C: beq         $at, $zero, L_800B9070
    if (ctx->r1 == 0) {
        // 0x800B8FA0: sll         $t8, $a0, 4
        ctx->r24 = S32(ctx->r4 << 4);
            goto L_800B9070;
    }
    // 0x800B8FA0: sll         $t8, $a0, 4
    ctx->r24 = S32(ctx->r4 << 4);
    // 0x800B8FA4: addu        $v1, $t8, $t9
    ctx->r3 = ADD32(ctx->r24, ctx->r25);
L_800B8FA8:
    // 0x800B8FA8: lw          $t5, 0x4($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X4);
    // 0x800B8FAC: or          $t0, $v1, $zero
    ctx->r8 = ctx->r3 | 0;
    // 0x800B8FB0: subu        $v0, $s1, $t5
    ctx->r2 = SUB32(ctx->r17, ctx->r13);
    // 0x800B8FB4: bltzl       $v0, L_800B9060
    if (SIGNED(ctx->r2) < 0) {
        // 0x800B8FB8: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_800B9060;
    }
    goto skip_0;
    // 0x800B8FB8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    skip_0:
    // 0x800B8FBC: lhu         $t6, 0xA($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0XA);
    // 0x800B8FC0: subu        $t7, $t6, $s0
    ctx->r15 = SUB32(ctx->r14, ctx->r16);
    // 0x800B8FC4: sltu        $at, $t7, $v0
    ctx->r1 = ctx->r15 < ctx->r2 ? 1 : 0;
    // 0x800B8FC8: bnel        $at, $zero, L_800B9060
    if (ctx->r1 != 0) {
        // 0x800B8FCC: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_800B9060;
    }
    goto skip_1;
    // 0x800B8FCC: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    skip_1:
    // 0x800B8FD0: lbu         $t8, 0xE($v1)
    ctx->r24 = MEM_BU(ctx->r3, 0XE);
    // 0x800B8FD4: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800B8FD8: addiu       $a3, $a3, 0x5501
    ctx->r7 = ADD32(ctx->r7, 0X5501);
    // 0x800B8FDC: bne         $t8, $zero, L_800B9038
    if (ctx->r24 != 0) {
        // 0x800B8FE0: lui         $t9, 0x8004
        ctx->r25 = S32(0X8004 << 16);
            goto L_800B9038;
    }
    // 0x800B8FE0: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800B8FE4: lbu         $a1, 0x0($a3)
    ctx->r5 = MEM_BU(ctx->r7, 0X0);
    // 0x800B8FE8: lbu         $t9, 0x5503($t9)
    ctx->r25 = MEM_BU(ctx->r25, 0X5503);
    // 0x800B8FEC: beql        $t9, $a1, L_800B903C
    if (ctx->r25 == ctx->r5) {
        // 0x800B8FF0: lw          $t9, 0x54($sp)
        ctx->r25 = MEM_W(ctx->r29, 0X54);
            goto L_800B903C;
    }
    goto skip_2;
    // 0x800B8FF0: lw          $t9, 0x54($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X54);
    skip_2:
    // 0x800B8FF4: lbu         $a2, 0xD($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0XD);
    // 0x800B8FF8: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800B8FFC: addiu       $t3, $t3, 0x5400
    ctx->r11 = ADD32(ctx->r11, 0X5400);
    // 0x800B9000: beq         $a1, $a2, L_800B9030
    if (ctx->r5 == ctx->r6) {
        // 0x800B9004: addu        $v0, $t3, $a1
        ctx->r2 = ADD32(ctx->r11, ctx->r5);
            goto L_800B9030;
    }
    // 0x800B9004: addu        $v0, $t3, $a1
    ctx->r2 = ADD32(ctx->r11, ctx->r5);
    // 0x800B9008: lbu         $t5, 0x0($v0)
    ctx->r13 = MEM_BU(ctx->r2, 0X0);
    // 0x800B900C: addu        $t6, $t3, $a2
    ctx->r14 = ADD32(ctx->r11, ctx->r6);
    // 0x800B9010: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800B9014: sb          $t5, 0x0($t6)
    MEM_B(0X0, ctx->r14) = ctx->r13;
    // 0x800B9018: lbu         $t8, 0x0($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X0);
    // 0x800B901C: lbu         $t7, 0xD($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0XD);
    // 0x800B9020: addiu       $t4, $t4, 0x4DF0
    ctx->r12 = ADD32(ctx->r12, 0X4DF0);
    // 0x800B9024: sll         $t9, $t8, 4
    ctx->r25 = S32(ctx->r24 << 4);
    // 0x800B9028: addu        $t5, $t4, $t9
    ctx->r13 = ADD32(ctx->r12, ctx->r25);
    // 0x800B902C: sb          $t7, 0xD($t5)
    MEM_B(0XD, ctx->r13) = ctx->r15;
L_800B9030:
    // 0x800B9030: addiu       $t6, $a1, 0x1
    ctx->r14 = ADD32(ctx->r5, 0X1);
    // 0x800B9034: sb          $t6, 0x0($a3)
    MEM_B(0X0, ctx->r7) = ctx->r14;
L_800B9038:
    // 0x800B9038: lw          $t9, 0x54($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X54);
L_800B903C:
    // 0x800B903C: addiu       $t8, $zero, 0x3C
    ctx->r24 = ADD32(0, 0X3C);
    // 0x800B9040: sb          $t8, 0xE($v1)
    MEM_B(0XE, ctx->r3) = ctx->r24;
    // 0x800B9044: sb          $a0, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r4;
    // 0x800B9048: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800B904C: lw          $t6, 0x4($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X4);
    // 0x800B9050: addu        $t5, $t7, $s1
    ctx->r13 = ADD32(ctx->r15, ctx->r17);
    // 0x800B9054: b           L_800B9230
    // 0x800B9058: subu        $v0, $t5, $t6
    ctx->r2 = SUB32(ctx->r13, ctx->r14);
        goto L_800B9230;
    // 0x800B9058: subu        $v0, $t5, $t6
    ctx->r2 = SUB32(ctx->r13, ctx->r14);
    // 0x800B905C: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
L_800B9060:
    // 0x800B9060: sltu        $at, $a0, $a1
    ctx->r1 = ctx->r4 < ctx->r5 ? 1 : 0;
    // 0x800B9064: bne         $at, $zero, L_800B8FA8
    if (ctx->r1 != 0) {
        // 0x800B9068: addiu       $v1, $v1, 0x10
        ctx->r3 = ADD32(ctx->r3, 0X10);
            goto L_800B8FA8;
    }
    // 0x800B9068: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800B906C: sw          $t0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r8;
L_800B9070:
    // 0x800B9070: lui         $a3, 0x8004
    ctx->r7 = S32(0X8004 << 16);
    // 0x800B9074: addiu       $a3, $a3, 0x5501
    ctx->r7 = ADD32(ctx->r7, 0X5501);
    // 0x800B9078: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800B907C: lbu         $t8, 0x5503($t8)
    ctx->r24 = MEM_BU(ctx->r24, 0X5503);
    // 0x800B9080: lbu         $a1, 0x0($a3)
    ctx->r5 = MEM_BU(ctx->r7, 0X0);
    // 0x800B9084: lw          $t0, 0x40($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X40);
    // 0x800B9088: beq         $t8, $a1, L_800B90C4
    if (ctx->r24 == ctx->r5) {
        // 0x800B908C: nop
    
            goto L_800B90C4;
    }
    // 0x800B908C: nop

    // 0x800B9090: beq         $a2, $zero, L_800B90C4
    if (ctx->r6 == 0) {
        // 0x800B9094: lui         $t3, 0x8004
        ctx->r11 = S32(0X8004 << 16);
            goto L_800B90C4;
    }
    // 0x800B9094: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800B9098: addiu       $t3, $t3, 0x5400
    ctx->r11 = ADD32(ctx->r11, 0X5400);
    // 0x800B909C: addu        $t9, $t3, $a1
    ctx->r25 = ADD32(ctx->r11, ctx->r5);
    // 0x800B90A0: lbu         $t2, 0x0($t9)
    ctx->r10 = MEM_BU(ctx->r25, 0X0);
    // 0x800B90A4: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800B90A8: addiu       $t4, $t4, 0x4DF0
    ctx->r12 = ADD32(ctx->r12, 0X4DF0);
    // 0x800B90AC: addiu       $t7, $a1, 0x1
    ctx->r15 = ADD32(ctx->r5, 0X1);
    // 0x800B90B0: sll         $t5, $t2, 4
    ctx->r13 = S32(ctx->r10 << 4);
    // 0x800B90B4: sb          $t7, 0x0($a3)
    MEM_B(0X0, ctx->r7) = ctx->r15;
    // 0x800B90B8: addu        $t0, $t4, $t5
    ctx->r8 = ADD32(ctx->r12, ctx->r13);
    // 0x800B90BC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800B90C0: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
L_800B90C4:
    // 0x800B90C4: lui         $t4, 0x8004
    ctx->r12 = S32(0X8004 << 16);
    // 0x800B90C8: b           L_800B9168
    // 0x800B90CC: addiu       $t4, $t4, 0x4DF0
    ctx->r12 = ADD32(ctx->r12, 0X4DF0);
        goto L_800B9168;
    // 0x800B90CC: addiu       $t4, $t4, 0x4DF0
    ctx->r12 = ADD32(ctx->r12, 0X4DF0);
L_800B90D0:
    // 0x800B90D0: addu        $t0, $t4, $t6
    ctx->r8 = ADD32(ctx->r12, ctx->r14);
    // 0x800B90D4: lw          $a0, 0x4($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X4);
    // 0x800B90D8: subu        $v0, $s1, $a0
    ctx->r2 = SUB32(ctx->r17, ctx->r4);
    // 0x800B90DC: bltz        $v0, L_800B9168
    if (SIGNED(ctx->r2) < 0) {
        // 0x800B90E0: nop
    
            goto L_800B9168;
    }
    // 0x800B90E0: nop

    // 0x800B90E4: lhu         $t8, 0xA($t0)
    ctx->r24 = MEM_HU(ctx->r8, 0XA);
    // 0x800B90E8: subu        $t9, $t8, $s0
    ctx->r25 = SUB32(ctx->r24, ctx->r16);
    // 0x800B90EC: sltu        $at, $t9, $v0
    ctx->r1 = ctx->r25 < ctx->r2 ? 1 : 0;
    // 0x800B90F0: bne         $at, $zero, L_800B9168
    if (ctx->r1 != 0) {
        // 0x800B90F4: nop
    
            goto L_800B9168;
    }
    // 0x800B90F4: nop

    // 0x800B90F8: lbu         $t7, 0xE($t0)
    ctx->r15 = MEM_BU(ctx->r8, 0XE);
    // 0x800B90FC: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B9100: addiu       $a1, $a1, 0x5500
    ctx->r5 = ADD32(ctx->r5, 0X5500);
    // 0x800B9104: bnel        $t7, $zero, L_800B9154
    if (ctx->r15 != 0) {
        // 0x800B9108: lw          $t7, 0x0($t0)
        ctx->r15 = MEM_W(ctx->r8, 0X0);
            goto L_800B9154;
    }
    goto skip_3;
    // 0x800B9108: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    skip_3:
    // 0x800B910C: lbu         $v1, 0x0($a1)
    ctx->r3 = MEM_BU(ctx->r5, 0X0);
    // 0x800B9110: lbu         $a0, 0xD($t0)
    ctx->r4 = MEM_BU(ctx->r8, 0XD);
    // 0x800B9114: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B9118: addiu       $a2, $a2, 0x5300
    ctx->r6 = ADD32(ctx->r6, 0X5300);
    // 0x800B911C: beq         $v1, $a0, L_800B9144
    if (ctx->r3 == ctx->r4) {
        // 0x800B9120: addu        $v0, $a2, $v1
        ctx->r2 = ADD32(ctx->r6, ctx->r3);
            goto L_800B9144;
    }
    // 0x800B9120: addu        $v0, $a2, $v1
    ctx->r2 = ADD32(ctx->r6, ctx->r3);
    // 0x800B9124: lbu         $t5, 0x0($v0)
    ctx->r13 = MEM_BU(ctx->r2, 0X0);
    // 0x800B9128: addu        $t6, $a2, $a0
    ctx->r14 = ADD32(ctx->r6, ctx->r4);
    // 0x800B912C: sb          $t5, 0x0($t6)
    MEM_B(0X0, ctx->r14) = ctx->r13;
    // 0x800B9130: lbu         $t9, 0x0($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X0);
    // 0x800B9134: lbu         $t8, 0xD($t0)
    ctx->r24 = MEM_BU(ctx->r8, 0XD);
    // 0x800B9138: sll         $t7, $t9, 4
    ctx->r15 = S32(ctx->r25 << 4);
    // 0x800B913C: addu        $t5, $t4, $t7
    ctx->r13 = ADD32(ctx->r12, ctx->r15);
    // 0x800B9140: sb          $t8, 0xD($t5)
    MEM_B(0XD, ctx->r13) = ctx->r24;
L_800B9144:
    // 0x800B9144: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    // 0x800B9148: sb          $t6, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r14;
    // 0x800B914C: lw          $a0, 0x4($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X4);
    // 0x800B9150: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
L_800B9154:
    // 0x800B9154: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x800B9158: sb          $t9, 0xE($t0)
    MEM_B(0XE, ctx->r8) = ctx->r25;
    // 0x800B915C: addu        $t8, $t7, $s1
    ctx->r24 = ADD32(ctx->r15, ctx->r17);
    // 0x800B9160: b           L_800B9230
    // 0x800B9164: subu        $v0, $t8, $a0
    ctx->r2 = SUB32(ctx->r24, ctx->r4);
        goto L_800B9230;
    // 0x800B9164: subu        $v0, $t8, $a0
    ctx->r2 = SUB32(ctx->r24, ctx->r4);
L_800B9168:
    // 0x800B9168: bne         $t1, $zero, L_800B919C
    if (ctx->r9 != 0) {
        // 0x800B916C: lw          $t2, 0x30($sp)
        ctx->r10 = MEM_W(ctx->r29, 0X30);
            goto L_800B919C;
    }
    // 0x800B916C: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800B9170: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800B9174: addiu       $a1, $a1, 0x5500
    ctx->r5 = ADD32(ctx->r5, 0X5500);
    // 0x800B9178: lbu         $v1, 0x0($a1)
    ctx->r3 = MEM_BU(ctx->r5, 0X0);
    // 0x800B917C: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B9180: addiu       $a2, $a2, 0x5300
    ctx->r6 = ADD32(ctx->r6, 0X5300);
    // 0x800B9184: addu        $t5, $a2, $v1
    ctx->r13 = ADD32(ctx->r6, ctx->r3);
    // 0x800B9188: lbu         $t2, 0x0($t5)
    ctx->r10 = MEM_BU(ctx->r13, 0X0);
    // 0x800B918C: addiu       $t6, $v1, 0x1
    ctx->r14 = ADD32(ctx->r3, 0X1);
    // 0x800B9190: sb          $t6, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r14;
    // 0x800B9194: sll         $t9, $t2, 4
    ctx->r25 = S32(ctx->r10 << 4);
    // 0x800B9198: addu        $t0, $t4, $t9
    ctx->r8 = ADD32(ctx->r12, ctx->r25);
L_800B919C:
    // 0x800B919C: lhu         $v0, 0xA($t0)
    ctx->r2 = MEM_HU(ctx->r8, 0XA);
    // 0x800B91A0: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800B91A4: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800B91A8: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x800B91AC: and         $s0, $s1, $at
    ctx->r16 = ctx->r17 & ctx->r1;
    // 0x800B91B0: addiu       $t1, $t1, 0x5554
    ctx->r9 = ADD32(ctx->r9, 0X5554);
    // 0x800B91B4: sb          $t7, 0xE($t0)
    MEM_B(0XE, ctx->r8) = ctx->r15;
    // 0x800B91B8: sw          $s0, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r16;
    // 0x800B91BC: sh          $v0, 0x8($t0)
    MEM_H(0X8, ctx->r8) = ctx->r2;
    // 0x800B91C0: lw          $v1, 0x0($t1)
    ctx->r3 = MEM_W(ctx->r9, 0X0);
    // 0x800B91C4: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x800B91C8: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B91CC: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x800B91D0: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800B91D4: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x800B91D8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x800B91DC: addiu       $t9, $t9, 0x47A0
    ctx->r25 = ADD32(ctx->r25, 0X47A0);
    // 0x800B91E0: addiu       $t5, $t5, 0x48B8
    ctx->r13 = ADD32(ctx->r13, 0X48B8);
    // 0x800B91E4: addiu       $t7, $v1, 0x1
    ctx->r15 = ADD32(ctx->r3, 0X1);
    // 0x800B91E8: sw          $t7, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r15;
    // 0x800B91EC: addu        $a0, $t8, $t5
    ctx->r4 = ADD32(ctx->r24, ctx->r13);
    // 0x800B91F0: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x800B91F4: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
    // 0x800B91F8: sw          $t0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r8;
    // 0x800B91FC: or          $a3, $s0, $zero
    ctx->r7 = ctx->r16 | 0;
    // 0x800B9200: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800B9204: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800B9208: sw          $v0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r2;
    // 0x800B920C: jal         0x800CA370
    // 0x800B9210: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    osPiStartDma_recomp(rdram, ctx);
        goto after_0;
    // 0x800B9210: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_0:
    // 0x800B9214: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800B9218: lw          $t8, 0x54($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X54);
    // 0x800B921C: lw          $t0, 0x40($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X40);
    // 0x800B9220: subu        $t5, $s1, $s0
    ctx->r13 = SUB32(ctx->r17, ctx->r16);
    // 0x800B9224: sb          $t2, 0x0($t8)
    MEM_B(0X0, ctx->r24) = ctx->r10;
    // 0x800B9228: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x800B922C: addu        $v0, $t5, $t6
    ctx->r2 = ADD32(ctx->r13, ctx->r14);
L_800B9230:
    // 0x800B9230: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9234: lw          $s0, 0x24($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X24);
    // 0x800B9238: lw          $s1, 0x28($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X28);
    // 0x800B923C: jr          $ra
    // 0x800B9240: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800B9240: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void AudioLoad_InitSampleDmaBuffers(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9244: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800B9248: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800B924C: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800B9250: addiu       $s5, $s5, 0x5548
    ctx->r21 = ADD32(ctx->r21, 0X5548);
    // 0x800B9254: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x800B9258: lw          $a0, 0x0($s5)
    ctx->r4 = MEM_W(ctx->r21, 0X0);
    // 0x800B925C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800B9260: addiu       $s2, $zero, 0x3
    ctx->r18 = ADD32(0, 0X3);
    // 0x800B9264: multu       $a0, $s2
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B9268: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800B926C: lui         $s3, 0x8004
    ctx->r19 = S32(0X8004 << 16);
    // 0x800B9270: addiu       $s3, $s3, 0x5520
    ctx->r19 = ADD32(ctx->r19, 0X5520);
    // 0x800B9274: lh          $t8, 0x0($s3)
    ctx->r24 = MEM_H(ctx->r19, 0X0);
    // 0x800B9278: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800B927C: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800B9280: sw          $s7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r23;
    // 0x800B9284: sw          $s6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r22;
    // 0x800B9288: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800B928C: mflo        $t7
    ctx->r15 = lo;
    // 0x800B9290: addiu       $s4, $s4, 0x5540
    ctx->r20 = ADD32(ctx->r20, 0X5540);
    // 0x800B9294: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800B9298: multu       $t7, $t8
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B929C: addiu       $t6, $zero, 0x2D0
    ctx->r14 = ADD32(0, 0X2D0);
    // 0x800B92A0: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800B92A4: lui         $s6, 0x8004
    ctx->r22 = S32(0X8004 << 16);
    // 0x800B92A8: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800B92AC: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800B92B0: sw          $t6, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r14;
    // 0x800B92B4: addiu       $s7, $s7, 0x4DF0
    ctx->r23 = ADD32(ctx->r23, 0X4DF0);
    // 0x800B92B8: addiu       $s6, $s6, -0x1A90
    ctx->r22 = ADD32(ctx->r22, -0X1A90);
    // 0x800B92BC: addiu       $s1, $s1, 0x52F0
    ctx->r17 = ADD32(ctx->r17, 0X52F0);
    // 0x800B92C0: mflo        $t9
    ctx->r25 = lo;
    // 0x800B92C4: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800B92C8: blez        $t9, L_800B934C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800B92CC: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800B934C;
    }
    // 0x800B92CC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_800B92D0:
    // 0x800B92D0: jal         0x800B7760
    // 0x800B92D4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B92D4: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    after_0:
    // 0x800B92D8: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x800B92DC: sll         $t0, $a2, 4
    ctx->r8 = S32(ctx->r6 << 4);
    // 0x800B92E0: addu        $v1, $s7, $t0
    ctx->r3 = ADD32(ctx->r23, ctx->r8);
    // 0x800B92E4: bne         $v0, $zero, L_800B92F8
    if (ctx->r2 != 0) {
        // 0x800B92E8: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_800B92F8;
    }
    // 0x800B92E8: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800B92EC: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800B92F0: b           L_800B934C
    // 0x800B92F4: lw          $a0, 0x0($s5)
    ctx->r4 = MEM_W(ctx->r21, 0X0);
        goto L_800B934C;
    // 0x800B92F4: lw          $a0, 0x0($s5)
    ctx->r4 = MEM_W(ctx->r21, 0X0);
L_800B92F8:
    // 0x800B92F8: lw          $a0, 0x0($s5)
    ctx->r4 = MEM_W(ctx->r21, 0X0);
    // 0x800B92FC: lh          $t3, 0x0($s3)
    ctx->r11 = MEM_H(ctx->r19, 0X0);
    // 0x800B9300: lw          $a1, 0x0($s4)
    ctx->r5 = MEM_W(ctx->r20, 0X0);
    // 0x800B9304: multu       $a0, $s2
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B9308: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800B930C: addiu       $t1, $a2, 0x1
    ctx->r9 = ADD32(ctx->r6, 0X1);
    // 0x800B9310: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x800B9314: sh          $zero, 0x8($v1)
    MEM_H(0X8, ctx->r3) = 0;
    // 0x800B9318: sb          $zero, 0xC($v1)
    MEM_B(0XC, ctx->r3) = 0;
    // 0x800B931C: sb          $zero, 0xE($v1)
    MEM_B(0XE, ctx->r3) = 0;
    // 0x800B9320: sw          $t1, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r9;
    // 0x800B9324: sh          $a1, 0xA($v1)
    MEM_H(0XA, ctx->r3) = ctx->r5;
    // 0x800B9328: mflo        $t2
    ctx->r10 = lo;
    // 0x800B932C: nop

    // 0x800B9330: nop

    // 0x800B9334: multu       $t2, $t3
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800B9338: mflo        $t4
    ctx->r12 = lo;
    // 0x800B933C: slt         $at, $s0, $t4
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r12) ? 1 : 0;
    // 0x800B9340: bne         $at, $zero, L_800B92D0
    if (ctx->r1 != 0) {
        // 0x800B9344: nop
    
            goto L_800B92D0;
    }
    // 0x800B9344: nop

    // 0x800B9348: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
L_800B934C:
    // 0x800B934C: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800B9350: addiu       $s1, $s1, 0x52F0
    ctx->r17 = ADD32(ctx->r17, 0X52F0);
    // 0x800B9354: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x800B9358: lui         $s6, 0x8004
    ctx->r22 = S32(0X8004 << 16);
    // 0x800B935C: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800B9360: addiu       $s7, $s7, 0x4DF0
    ctx->r23 = ADD32(ctx->r23, 0X4DF0);
    // 0x800B9364: beq         $a2, $zero, L_800B9398
    if (ctx->r6 == 0) {
        // 0x800B9368: addiu       $s6, $s6, -0x1A90
        ctx->r22 = ADD32(ctx->r22, -0X1A90);
            goto L_800B9398;
    }
    // 0x800B9368: addiu       $s6, $s6, -0x1A90
    ctx->r22 = ADD32(ctx->r22, -0X1A90);
    // 0x800B936C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B9370: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B9374: addiu       $v1, $v1, 0x4DF0
    ctx->r3 = ADD32(ctx->r3, 0X4DF0);
    // 0x800B9378: addiu       $v0, $v0, 0x5300
    ctx->r2 = ADD32(ctx->r2, 0X5300);
L_800B937C:
    // 0x800B937C: sb          $s0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r16;
    // 0x800B9380: sb          $s0, 0xD($v1)
    MEM_B(0XD, ctx->r3) = ctx->r16;
    // 0x800B9384: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800B9388: sltu        $at, $s0, $a2
    ctx->r1 = ctx->r16 < ctx->r6 ? 1 : 0;
    // 0x800B938C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B9390: bne         $at, $zero, L_800B937C
    if (ctx->r1 != 0) {
        // 0x800B9394: addiu       $v1, $v1, 0x10
        ctx->r3 = ADD32(ctx->r3, 0X10);
            goto L_800B937C;
    }
    // 0x800B9394: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
L_800B9398:
    // 0x800B9398: slti        $at, $a2, 0x100
    ctx->r1 = SIGNED(ctx->r6) < 0X100 ? 1 : 0;
    // 0x800B939C: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x800B93A0: beq         $at, $zero, L_800B93CC
    if (ctx->r1 == 0) {
        // 0x800B93A4: or          $s0, $a2, $zero
        ctx->r16 = ctx->r6 | 0;
            goto L_800B93CC;
    }
    // 0x800B93A4: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x800B93A8: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800B93AC: addiu       $t5, $t5, 0x5300
    ctx->r13 = ADD32(ctx->r13, 0X5300);
    // 0x800B93B0: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B93B4: addiu       $v1, $v1, 0x5400
    ctx->r3 = ADD32(ctx->r3, 0X5400);
    // 0x800B93B8: addu        $v0, $s0, $t5
    ctx->r2 = ADD32(ctx->r16, ctx->r13);
L_800B93BC:
    // 0x800B93BC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B93C0: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x800B93C4: bne         $at, $zero, L_800B93BC
    if (ctx->r1 != 0) {
        // 0x800B93C8: sb          $zero, -0x1($v0)
        MEM_B(-0X1, ctx->r2) = 0;
            goto L_800B93BC;
    }
    // 0x800B93C8: sb          $zero, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = 0;
L_800B93CC:
    // 0x800B93CC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B93D0: sb          $zero, 0x5500($at)
    MEM_B(0X5500, ctx->r1) = 0;
    // 0x800B93D4: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800B93D8: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B93DC: addiu       $s2, $s2, 0x52F4
    ctx->r18 = ADD32(ctx->r18, 0X52F4);
    // 0x800B93E0: sb          $a2, 0x5502($at)
    MEM_B(0X5502, ctx->r1) = ctx->r6;
    // 0x800B93E4: addiu       $t6, $zero, 0x400
    ctx->r14 = ADD32(0, 0X400);
    // 0x800B93E8: sw          $a2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r6;
    // 0x800B93EC: sw          $t6, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r14;
    // 0x800B93F0: blez        $a0, L_800B945C
    if (SIGNED(ctx->r4) <= 0) {
        // 0x800B93F4: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800B945C;
    }
    // 0x800B93F4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800B93F8: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
L_800B93FC:
    // 0x800B93FC: jal         0x800B7760
    // 0x800B9400: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_1;
    // 0x800B9400: or          $a0, $s6, $zero
    ctx->r4 = ctx->r22 | 0;
    after_1:
    // 0x800B9404: lw          $a2, 0x0($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X0);
    // 0x800B9408: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800B940C: sll         $t7, $a2, 4
    ctx->r15 = S32(ctx->r6 << 4);
    // 0x800B9410: addu        $v1, $s7, $t7
    ctx->r3 = ADD32(ctx->r23, ctx->r15);
    // 0x800B9414: bne         $v0, $zero, L_800B9424
    if (ctx->r2 != 0) {
        // 0x800B9418: sw          $v0, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->r2;
            goto L_800B9424;
    }
    // 0x800B9418: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800B941C: b           L_800B945C
    // 0x800B9420: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
        goto L_800B945C;
    // 0x800B9420: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
L_800B9424:
    // 0x800B9424: lw          $t9, 0x0($s5)
    ctx->r25 = MEM_W(ctx->r21, 0X0);
    // 0x800B9428: lw          $a1, 0x0($s4)
    ctx->r5 = MEM_W(ctx->r20, 0X0);
    // 0x800B942C: addiu       $t8, $a2, 0x1
    ctx->r24 = ADD32(ctx->r6, 0X1);
    // 0x800B9430: slt         $at, $s0, $t9
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800B9434: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x800B9438: sh          $zero, 0x8($v1)
    MEM_H(0X8, ctx->r3) = 0;
    // 0x800B943C: sb          $zero, 0xC($v1)
    MEM_B(0XC, ctx->r3) = 0;
    // 0x800B9440: sb          $zero, 0xE($v1)
    MEM_B(0XE, ctx->r3) = 0;
    // 0x800B9444: sw          $t8, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r24;
    // 0x800B9448: bne         $at, $zero, L_800B93FC
    if (ctx->r1 != 0) {
        // 0x800B944C: sh          $a1, 0xA($v1)
        MEM_H(0XA, ctx->r3) = ctx->r5;
            goto L_800B93FC;
    }
    // 0x800B944C: sh          $a1, 0xA($v1)
    MEM_H(0XA, ctx->r3) = ctx->r5;
    // 0x800B9450: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800B9454: lw          $a2, 0x52F0($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X52F0);
    // 0x800B9458: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
L_800B945C:
    // 0x800B945C: lw          $a1, 0x0($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X0);
    // 0x800B9460: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800B9464: addiu       $t1, $t1, 0x4DF0
    ctx->r9 = ADD32(ctx->r9, 0X4DF0);
    // 0x800B9468: sltu        $at, $a1, $a2
    ctx->r1 = ctx->r5 < ctx->r6 ? 1 : 0;
    // 0x800B946C: beq         $at, $zero, L_800B94AC
    if (ctx->r1 == 0) {
        // 0x800B9470: or          $s0, $a1, $zero
        ctx->r16 = ctx->r5 | 0;
            goto L_800B94AC;
    }
    // 0x800B9470: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x800B9474: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800B9478: addiu       $t2, $t2, 0x5400
    ctx->r10 = ADD32(ctx->r10, 0X5400);
    // 0x800B947C: sll         $t0, $s0, 4
    ctx->r8 = S32(ctx->r16 << 4);
    // 0x800B9480: subu        $v0, $s0, $a1
    ctx->r2 = SUB32(ctx->r16, ctx->r5);
    // 0x800B9484: addu        $a0, $v0, $t2
    ctx->r4 = ADD32(ctx->r2, ctx->r10);
    // 0x800B9488: addu        $v1, $t0, $t1
    ctx->r3 = ADD32(ctx->r8, ctx->r9);
L_800B948C:
    // 0x800B948C: sb          $s0, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r16;
    // 0x800B9490: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800B9494: sltu        $at, $s0, $a2
    ctx->r1 = ctx->r16 < ctx->r6 ? 1 : 0;
    // 0x800B9498: sb          $v0, 0xD($v1)
    MEM_B(0XD, ctx->r3) = ctx->r2;
    // 0x800B949C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B94A0: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800B94A4: bne         $at, $zero, L_800B948C
    if (ctx->r1 != 0) {
        // 0x800B94A8: addiu       $a0, $a0, 0x1
        ctx->r4 = ADD32(ctx->r4, 0X1);
            goto L_800B948C;
    }
    // 0x800B94A8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
L_800B94AC:
    // 0x800B94AC: slti        $at, $a3, 0x100
    ctx->r1 = SIGNED(ctx->r7) < 0X100 ? 1 : 0;
    // 0x800B94B0: beq         $at, $zero, L_800B94DC
    if (ctx->r1 == 0) {
        // 0x800B94B4: subu        $t4, $a2, $a1
        ctx->r12 = SUB32(ctx->r6, ctx->r5);
            goto L_800B94DC;
    }
    // 0x800B94B4: subu        $t4, $a2, $a1
    ctx->r12 = SUB32(ctx->r6, ctx->r5);
    // 0x800B94B8: lui         $t3, 0x8004
    ctx->r11 = S32(0X8004 << 16);
    // 0x800B94BC: addiu       $t3, $t3, 0x5400
    ctx->r11 = ADD32(ctx->r11, 0X5400);
    // 0x800B94C0: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B94C4: addiu       $v1, $v1, 0x5500
    ctx->r3 = ADD32(ctx->r3, 0X5500);
    // 0x800B94C8: addu        $v0, $a3, $t3
    ctx->r2 = ADD32(ctx->r7, ctx->r11);
L_800B94CC:
    // 0x800B94CC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800B94D0: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x800B94D4: bne         $at, $zero, L_800B94CC
    if (ctx->r1 != 0) {
        // 0x800B94D8: sb          $a1, -0x1($v0)
        MEM_B(-0X1, ctx->r2) = ctx->r5;
            goto L_800B94CC;
    }
    // 0x800B94D8: sb          $a1, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = ctx->r5;
L_800B94DC:
    // 0x800B94DC: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800B94E0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B94E4: sb          $zero, 0x5501($at)
    MEM_B(0X5501, ctx->r1) = 0;
    // 0x800B94E8: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B94EC: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800B94F0: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800B94F4: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800B94F8: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800B94FC: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800B9500: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800B9504: lw          $s6, 0x2C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9508: lw          $s7, 0x30($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X30);
    // 0x800B950C: sb          $t4, 0x5503($at)
    MEM_B(0X5503, ctx->r1) = ctx->r12;
    // 0x800B9510: jr          $ra
    // 0x800B9514: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800B9514: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void Audio_PatchSound(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9518: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800B951C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B9520: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B9524: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x800B9528: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800B952C: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x800B9530: beq         $v0, $zero, L_800B9604
    if (ctx->r2 == 0) {
        // 0x800B9534: addu        $a3, $v0, $a1
        ctx->r7 = ADD32(ctx->r2, ctx->r5);
            goto L_800B9604;
    }
    // 0x800B9534: addu        $a3, $v0, $a1
    ctx->r7 = ADD32(ctx->r2, ctx->r5);
    // 0x800B9538: sw          $a3, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r7;
    // 0x800B953C: lbu         $a0, 0x1($a3)
    ctx->r4 = MEM_BU(ctx->r7, 0X1);
    // 0x800B9540: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x800B9544: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800B9548: bne         $a0, $zero, L_800B957C
    if (ctx->r4 != 0) {
        // 0x800B954C: addiu       $at, $zero, 0x80
        ctx->r1 = ADD32(0, 0X80);
            goto L_800B957C;
    }
    // 0x800B954C: addiu       $at, $zero, 0x80
    ctx->r1 = ADD32(0, 0X80);
    // 0x800B9550: lw          $t7, 0x4($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X4);
    // 0x800B9554: lw          $t8, 0x8($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X8);
    // 0x800B9558: lw          $t9, 0xC($v1)
    ctx->r25 = MEM_W(ctx->r3, 0XC);
    // 0x800B955C: addu        $a3, $t7, $a2
    ctx->r7 = ADD32(ctx->r15, ctx->r6);
    // 0x800B9560: sw          $a3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r7;
    // 0x800B9564: addu        $a3, $t8, $a1
    ctx->r7 = ADD32(ctx->r24, ctx->r5);
    // 0x800B9568: sw          $a3, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r7;
    // 0x800B956C: addu        $a3, $t9, $a1
    ctx->r7 = ADD32(ctx->r25, ctx->r5);
    // 0x800B9570: sw          $a3, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r7;
    // 0x800B9574: b           L_800B9604
    // 0x800B9578: sb          $t0, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r8;
        goto L_800B9604;
    // 0x800B9578: sb          $t0, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r8;
L_800B957C:
    // 0x800B957C: bnel        $a0, $at, L_800B9608
    if (ctx->r4 != ctx->r1) {
        // 0x800B9580: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_800B9608;
    }
    goto skip_0;
    // 0x800B9580: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_0:
    // 0x800B9584: lw          $t1, 0x4($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X4);
    // 0x800B9588: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B958C: lw          $a1, 0x10($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X10);
    // 0x800B9590: addu        $a3, $t1, $a2
    ctx->r7 = ADD32(ctx->r9, ctx->r6);
    // 0x800B9594: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x800B9598: sw          $v1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r3;
    // 0x800B959C: jal         0x800B7760
    // 0x800B95A0: addiu       $a0, $a0, -0x1A90
    ctx->r4 = ADD32(ctx->r4, -0X1A90);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_0;
    // 0x800B95A0: addiu       $a0, $a0, -0x1A90
    ctx->r4 = ADD32(ctx->r4, -0X1A90);
    after_0:
    // 0x800B95A4: lw          $v1, 0x2C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X2C);
    // 0x800B95A8: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800B95AC: bne         $v0, $zero, L_800B95C4
    if (ctx->r2 != 0) {
        // 0x800B95B0: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800B95C4;
    }
    // 0x800B95B0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B95B4: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x800B95B8: sw          $a3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r7;
    // 0x800B95BC: b           L_800B95EC
    // 0x800B95C0: sb          $t2, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r10;
        goto L_800B95EC;
    // 0x800B95C0: sb          $t2, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r10;
L_800B95C4:
    // 0x800B95C4: lw          $a2, 0x10($v1)
    ctx->r6 = MEM_W(ctx->r3, 0X10);
    // 0x800B95C8: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800B95CC: sw          $v1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r3;
    // 0x800B95D0: jal         0x800B8CB0
    // 0x800B95D4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_1;
    // 0x800B95D4: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    after_1:
    // 0x800B95D8: lw          $v1, 0x2C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X2C);
    // 0x800B95DC: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x800B95E0: addiu       $t3, $zero, 0x81
    ctx->r11 = ADD32(0, 0X81);
    // 0x800B95E4: sb          $t3, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r11;
    // 0x800B95E8: sw          $a1, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r5;
L_800B95EC:
    // 0x800B95EC: lw          $t4, 0x8($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X8);
    // 0x800B95F0: lw          $t5, 0xC($v1)
    ctx->r13 = MEM_W(ctx->r3, 0XC);
    // 0x800B95F4: addu        $a3, $t4, $s0
    ctx->r7 = ADD32(ctx->r12, ctx->r16);
    // 0x800B95F8: sw          $a3, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r7;
    // 0x800B95FC: addu        $a3, $t5, $s0
    ctx->r7 = ADD32(ctx->r13, ctx->r16);
    // 0x800B9600: sw          $a3, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r7;
L_800B9604:
    // 0x800B9604: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_800B9608:
    // 0x800B9608: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B960C: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800B9610: jr          $ra
    // 0x800B9614: nop

    return;
    // 0x800B9614: nop

;}
RECOMP_FUNC void Audio_PatchBank(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9618: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800B961C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800B9620: sw          $s7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r23;
    // 0x800B9624: sw          $s6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r22;
    // 0x800B9628: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800B962C: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800B9630: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800B9634: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800B9638: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800B963C: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800B9640: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x800B9644: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800B9648: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x800B964C: or          $s5, $a1, $zero
    ctx->r21 = ctx->r5 | 0;
    // 0x800B9650: beq         $v0, $zero, L_800B96C4
    if (ctx->r2 == 0) {
        // 0x800B9654: or          $s7, $a3, $zero
        ctx->r23 = ctx->r7 | 0;
            goto L_800B96C4;
    }
    // 0x800B9654: or          $s7, $a3, $zero
    ctx->r23 = ctx->r7 | 0;
    // 0x800B9658: beq         $a3, $zero, L_800B96C4
    if (ctx->r7 == 0) {
        // 0x800B965C: addu        $t6, $v0, $a0
        ctx->r14 = ADD32(ctx->r2, ctx->r4);
            goto L_800B96C4;
    }
    // 0x800B965C: addu        $t6, $v0, $a0
    ctx->r14 = ADD32(ctx->r2, ctx->r4);
    // 0x800B9660: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x800B9664: beq         $a3, $zero, L_800B96C4
    if (ctx->r7 == 0) {
        // 0x800B9668: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_800B96C4;
    }
    // 0x800B9668: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x800B966C: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x800B9670: addiu       $s6, $zero, 0x1
    ctx->r22 = ADD32(0, 0X1);
L_800B9674:
    // 0x800B9674: lw          $t7, 0x0($s3)
    ctx->r15 = MEM_W(ctx->r19, 0X0);
    // 0x800B9678: addu        $v0, $t7, $s4
    ctx->r2 = ADD32(ctx->r15, ctx->r20);
    // 0x800B967C: lw          $s0, 0x0($v0)
    ctx->r16 = MEM_W(ctx->r2, 0X0);
    // 0x800B9680: beq         $s0, $zero, L_800B96B8
    if (ctx->r16 == 0) {
        // 0x800B9684: addu        $s0, $s0, $s3
        ctx->r16 = ADD32(ctx->r16, ctx->r19);
            goto L_800B96B8;
    }
    // 0x800B9684: addu        $s0, $s0, $s3
    ctx->r16 = ADD32(ctx->r16, ctx->r19);
    // 0x800B9688: sw          $s0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r16;
    // 0x800B968C: lbu         $t8, 0x2($s0)
    ctx->r24 = MEM_BU(ctx->r16, 0X2);
    // 0x800B9690: or          $s1, $s0, $zero
    ctx->r17 = ctx->r16 | 0;
    // 0x800B9694: addiu       $a0, $s0, 0x4
    ctx->r4 = ADD32(ctx->r16, 0X4);
    // 0x800B9698: bne         $t8, $zero, L_800B96B8
    if (ctx->r24 != 0) {
        // 0x800B969C: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_800B96B8;
    }
    // 0x800B969C: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x800B96A0: jal         0x800B9518
    // 0x800B96A4: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    Audio_PatchSound(rdram, ctx);
        goto after_0;
    // 0x800B96A4: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_0:
    // 0x800B96A8: lw          $s0, 0xC($s1)
    ctx->r16 = MEM_W(ctx->r17, 0XC);
    // 0x800B96AC: sb          $s6, 0x2($s1)
    MEM_B(0X2, ctx->r17) = ctx->r22;
    // 0x800B96B0: addu        $t9, $s0, $s3
    ctx->r25 = ADD32(ctx->r16, ctx->r19);
    // 0x800B96B4: sw          $t9, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->r25;
L_800B96B8:
    // 0x800B96B8: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x800B96BC: bne         $s2, $s7, L_800B9674
    if (ctx->r18 != ctx->r23) {
        // 0x800B96C0: addiu       $s4, $s4, 0x4
        ctx->r20 = ADD32(ctx->r20, 0X4);
            goto L_800B9674;
    }
    // 0x800B96C0: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
L_800B96C4:
    // 0x800B96C4: lw          $t0, 0x40($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X40);
    // 0x800B96C8: addiu       $s6, $zero, 0x1
    ctx->r22 = ADD32(0, 0X1);
    // 0x800B96CC: addiu       $s2, $s3, 0x4
    ctx->r18 = ADD32(ctx->r19, 0X4);
    // 0x800B96D0: beq         $t0, $zero, L_800B9748
    if (ctx->r8 == 0) {
        // 0x800B96D4: sll         $t1, $t0, 2
        ctx->r9 = S32(ctx->r8 << 2);
            goto L_800B9748;
    }
    // 0x800B96D4: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x800B96D8: addu        $s4, $t1, $s3
    ctx->r20 = ADD32(ctx->r9, ctx->r19);
    // 0x800B96DC: addiu       $s4, $s4, 0x4
    ctx->r20 = ADD32(ctx->r20, 0X4);
    // 0x800B96E0: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
L_800B96E4:
    // 0x800B96E4: beq         $v0, $zero, L_800B973C
    if (ctx->r2 == 0) {
        // 0x800B96E8: addu        $t2, $v0, $s3
        ctx->r10 = ADD32(ctx->r2, ctx->r19);
            goto L_800B973C;
    }
    // 0x800B96E8: addu        $t2, $v0, $s3
    ctx->r10 = ADD32(ctx->r2, ctx->r19);
    // 0x800B96EC: sw          $t2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r10;
    // 0x800B96F0: lbu         $t3, 0x0($t2)
    ctx->r11 = MEM_BU(ctx->r10, 0X0);
    // 0x800B96F4: or          $s1, $t2, $zero
    ctx->r17 = ctx->r10 | 0;
    // 0x800B96F8: addiu       $a0, $t2, 0x8
    ctx->r4 = ADD32(ctx->r10, 0X8);
    // 0x800B96FC: bne         $t3, $zero, L_800B973C
    if (ctx->r11 != 0) {
        // 0x800B9700: or          $a1, $s3, $zero
        ctx->r5 = ctx->r19 | 0;
            goto L_800B973C;
    }
    // 0x800B9700: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x800B9704: jal         0x800B9518
    // 0x800B9708: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    Audio_PatchSound(rdram, ctx);
        goto after_1;
    // 0x800B9708: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_1:
    // 0x800B970C: addiu       $a0, $s1, 0x10
    ctx->r4 = ADD32(ctx->r17, 0X10);
    // 0x800B9710: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x800B9714: jal         0x800B9518
    // 0x800B9718: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    Audio_PatchSound(rdram, ctx);
        goto after_2;
    // 0x800B9718: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_2:
    // 0x800B971C: addiu       $a0, $s1, 0x18
    ctx->r4 = ADD32(ctx->r17, 0X18);
    // 0x800B9720: or          $a1, $s3, $zero
    ctx->r5 = ctx->r19 | 0;
    // 0x800B9724: jal         0x800B9518
    // 0x800B9728: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    Audio_PatchSound(rdram, ctx);
        goto after_3;
    // 0x800B9728: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    after_3:
    // 0x800B972C: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x800B9730: sb          $s6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r22;
    // 0x800B9734: addu        $t4, $s0, $s3
    ctx->r12 = ADD32(ctx->r16, ctx->r19);
    // 0x800B9738: sw          $t4, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->r12;
L_800B973C:
    // 0x800B973C: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x800B9740: bnel        $s4, $s2, L_800B96E4
    if (ctx->r20 != ctx->r18) {
        // 0x800B9744: lw          $v0, 0x0($s2)
        ctx->r2 = MEM_W(ctx->r18, 0X0);
            goto L_800B96E4;
    }
    goto skip_0;
    // 0x800B9744: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
    skip_0:
L_800B9748:
    // 0x800B9748: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800B974C: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800B9750: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800B9754: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800B9758: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800B975C: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800B9760: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800B9764: lw          $s6, 0x2C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9768: lw          $s7, 0x30($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X30);
    // 0x800B976C: jr          $ra
    // 0x800B9770: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800B9770: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void Audio_BankLoadImmediate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9774: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B9778: lw          $t6, 0x5508($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5508);
    // 0x800B977C: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x800B9780: sll         $v1, $a0, 3
    ctx->r3 = S32(ctx->r4 << 3);
    // 0x800B9784: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800B9788: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x800B978C: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x800B9790: addu        $v0, $t6, $v1
    ctx->r2 = ADD32(ctx->r14, ctx->r3);
    // 0x800B9794: lw          $s0, 0x8($v0)
    ctx->r16 = MEM_W(ctx->r2, 0X8);
    // 0x800B9798: lw          $t8, 0x4($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X4);
    // 0x800B979C: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800B97A0: addiu       $s0, $s0, 0x1E
    ctx->r16 = ADD32(ctx->r16, 0X1E);
    // 0x800B97A4: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800B97A8: and         $t7, $s0, $at
    ctx->r15 = ctx->r16 & ctx->r1;
    // 0x800B97AC: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800B97B0: addiu       $s0, $t7, -0x10
    ctx->r16 = ADD32(ctx->r15, -0X10);
    // 0x800B97B4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B97B8: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    // 0x800B97BC: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800B97C0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800B97C4: sw          $s1, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r17;
    // 0x800B97C8: sw          $s1, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r17;
    // 0x800B97CC: sw          $v1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r3;
    // 0x800B97D0: jal         0x800B7B14
    // 0x800B97D4: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    AudioHeap_AllocCached(rdram, ctx);
        goto after_0;
    // 0x800B97D4: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    after_0:
    // 0x800B97D8: bne         $v0, $zero, L_800B97E8
    if (ctx->r2 != 0) {
        // 0x800B97DC: or          $s1, $v0, $zero
        ctx->r17 = ctx->r2 | 0;
            goto L_800B97E8;
    }
    // 0x800B97DC: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x800B97E0: b           L_800B98AC
    // 0x800B97E4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B98AC;
    // 0x800B97E4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B97E8:
    // 0x800B97E8: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    // 0x800B97EC: addiu       $a1, $sp, 0x48
    ctx->r5 = ADD32(ctx->r29, 0X48);
    // 0x800B97F0: jal         0x800B8CB0
    // 0x800B97F4: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_1;
    // 0x800B97F4: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    after_1:
    // 0x800B97F8: lw          $t9, 0x48($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X48);
    // 0x800B97FC: lw          $t0, 0x4C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X4C);
    // 0x800B9800: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    // 0x800B9804: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x800B9808: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800B980C: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
    // 0x800B9810: sw          $t0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r8;
    // 0x800B9814: jal         0x800B8CB0
    // 0x800B9818: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_2;
    // 0x800B9818: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    after_2:
    // 0x800B981C: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800B9820: lw          $t1, 0x550C($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X550C);
    // 0x800B9824: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800B9828: lw          $s0, 0x44($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X44);
    // 0x800B982C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800B9830: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x800B9834: lw          $a1, 0x4($t3)
    ctx->r5 = MEM_W(ctx->r11, 0X4);
    // 0x800B9838: lw          $a3, 0x40($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X40);
    // 0x800B983C: jal         0x800B9618
    // 0x800B9840: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    Audio_PatchBank(rdram, ctx);
        goto after_3;
    // 0x800B9840: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_3:
    // 0x800B9844: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    // 0x800B9848: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B984C: addiu       $a0, $a0, 0x5518
    ctx->r4 = ADD32(ctx->r4, 0X5518);
    // 0x800B9850: lw          $t4, 0x0($a0)
    ctx->r12 = MEM_W(ctx->r4, 0X0);
    // 0x800B9854: sll         $v1, $a1, 2
    ctx->r3 = S32(ctx->r5 << 2);
    // 0x800B9858: subu        $v1, $v1, $a1
    ctx->r3 = SUB32(ctx->r3, ctx->r5);
    // 0x800B985C: sll         $v1, $v1, 2
    ctx->r3 = S32(ctx->r3 << 2);
    // 0x800B9860: addu        $t5, $t4, $v1
    ctx->r13 = ADD32(ctx->r12, ctx->r3);
    // 0x800B9864: sb          $s0, 0x1($t5)
    MEM_B(0X1, ctx->r13) = ctx->r16;
    // 0x800B9868: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x800B986C: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x800B9870: addiu       $t9, $s1, 0x4
    ctx->r25 = ADD32(ctx->r17, 0X4);
    // 0x800B9874: addu        $t8, $t7, $v1
    ctx->r24 = ADD32(ctx->r15, ctx->r3);
    // 0x800B9878: sb          $t6, 0x2($t8)
    MEM_B(0X2, ctx->r24) = ctx->r14;
    // 0x800B987C: lw          $t0, 0x0($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X0);
    // 0x800B9880: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B9884: addiu       $t5, $zero, 0x2
    ctx->r13 = ADD32(0, 0X2);
    // 0x800B9888: addu        $t1, $t0, $v1
    ctx->r9 = ADD32(ctx->r8, ctx->r3);
    // 0x800B988C: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
    // 0x800B9890: lw          $t3, 0x0($a0)
    ctx->r11 = MEM_W(ctx->r4, 0X0);
    // 0x800B9894: lw          $t2, 0x0($s1)
    ctx->r10 = MEM_W(ctx->r17, 0X0);
    // 0x800B9898: addu        $at, $at, $a1
    ctx->r1 = ADD32(ctx->r1, ctx->r5);
    // 0x800B989C: addu        $t4, $t3, $v1
    ctx->r12 = ADD32(ctx->r11, ctx->r3);
    // 0x800B98A0: sw          $t2, 0x8($t4)
    MEM_W(0X8, ctx->r12) = ctx->r10;
    // 0x800B98A4: sb          $t5, -0x1488($at)
    MEM_B(-0X1488, ctx->r1) = ctx->r13;
    // 0x800B98A8: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_800B98AC:
    // 0x800B98AC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800B98B0: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800B98B4: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800B98B8: jr          $ra
    // 0x800B98BC: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    return;
    // 0x800B98BC: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
;}
RECOMP_FUNC void Audio_BankLoadAsync(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B98C0: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x800B98C4: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B98C8: lw          $t6, 0x5508($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5508);
    // 0x800B98CC: sll         $t7, $a0, 3
    ctx->r15 = S32(ctx->r4 << 3);
    // 0x800B98D0: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800B98D4: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x800B98D8: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x800B98DC: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x800B98E0: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800B98E4: lw          $s1, 0x8($v0)
    ctx->r17 = MEM_W(ctx->r2, 0X8);
    // 0x800B98E8: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800B98EC: lw          $t9, 0x4($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X4);
    // 0x800B98F0: addiu       $s1, $s1, 0x1E
    ctx->r17 = ADD32(ctx->r17, 0X1E);
    // 0x800B98F4: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800B98F8: and         $t8, $s1, $at
    ctx->r24 = ctx->r17 & ctx->r1;
    // 0x800B98FC: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x800B9900: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800B9904: addiu       $s1, $t8, -0x10
    ctx->r17 = ADD32(ctx->r24, -0X10);
    // 0x800B9908: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B990C: addiu       $a0, $a0, -0x1860
    ctx->r4 = ADD32(ctx->r4, -0X1860);
    // 0x800B9910: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
    // 0x800B9914: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800B9918: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x800B991C: jal         0x800B7B14
    // 0x800B9920: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    AudioHeap_AllocCached(rdram, ctx);
        goto after_0;
    // 0x800B9920: sw          $t9, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r25;
    after_0:
    // 0x800B9924: bne         $v0, $zero, L_800B9934
    if (ctx->r2 != 0) {
        // 0x800B9928: or          $t0, $v0, $zero
        ctx->r8 = ctx->r2 | 0;
            goto L_800B9934;
    }
    // 0x800B9928: or          $t0, $v0, $zero
    ctx->r8 = ctx->r2 | 0;
    // 0x800B992C: b           L_800B9A0C
    // 0x800B9930: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B9A0C;
    // 0x800B9930: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B9934:
    // 0x800B9934: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800B9938: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x800B993C: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    // 0x800B9940: jal         0x800B8CB0
    // 0x800B9944: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_1;
    // 0x800B9944: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    after_1:
    // 0x800B9948: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800B994C: lw          $a0, 0x50($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X50);
    // 0x800B9950: lw          $a1, 0x54($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X54);
    // 0x800B9954: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800B9958: addiu       $v1, $v1, 0x5518
    ctx->r3 = ADD32(ctx->r3, 0X5518);
    // 0x800B995C: sb          $s2, 0x6($s0)
    MEM_B(0X6, ctx->r16) = ctx->r18;
    // 0x800B9960: lw          $t1, 0x0($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X0);
    // 0x800B9964: sll         $v0, $s2, 2
    ctx->r2 = S32(ctx->r18 << 2);
    // 0x800B9968: subu        $v0, $v0, $s2
    ctx->r2 = SUB32(ctx->r2, ctx->r18);
    // 0x800B996C: sll         $v0, $v0, 2
    ctx->r2 = S32(ctx->r2 << 2);
    // 0x800B9970: addu        $t2, $t1, $v0
    ctx->r10 = ADD32(ctx->r9, ctx->r2);
    // 0x800B9974: sb          $a0, 0x1($t2)
    MEM_B(0X1, ctx->r10) = ctx->r4;
    // 0x800B9978: lw          $t3, 0x0($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X0);
    // 0x800B997C: addiu       $t5, $t0, 0x4
    ctx->r13 = ADD32(ctx->r8, 0X4);
    // 0x800B9980: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800B9984: addu        $t4, $t3, $v0
    ctx->r12 = ADD32(ctx->r11, ctx->r2);
    // 0x800B9988: sb          $a1, 0x2($t4)
    MEM_B(0X2, ctx->r12) = ctx->r5;
    // 0x800B998C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x800B9990: addiu       $a1, $s0, 0x11C
    ctx->r5 = ADD32(ctx->r16, 0X11C);
    // 0x800B9994: addu        $t7, $t6, $v0
    ctx->r15 = ADD32(ctx->r14, ctx->r2);
    // 0x800B9998: sw          $t5, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->r13;
    // 0x800B999C: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x800B99A0: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x800B99A4: addu        $t1, $t9, $v0
    ctx->r9 = ADD32(ctx->r25, ctx->r2);
    // 0x800B99A8: sw          $t8, 0x8($t1)
    MEM_W(0X8, ctx->r9) = ctx->r24;
    // 0x800B99AC: sw          $t0, 0x134($s0)
    MEM_W(0X134, ctx->r16) = ctx->r8;
    // 0x800B99B0: lw          $t2, 0x40($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X40);
    // 0x800B99B4: sw          $s1, 0x13C($s0)
    MEM_W(0X13C, ctx->r16) = ctx->r17;
    // 0x800B99B8: addiu       $s1, $s0, 0x104
    ctx->r17 = ADD32(ctx->r16, 0X104);
    // 0x800B99BC: addiu       $t3, $t2, 0x10
    ctx->r11 = ADD32(ctx->r10, 0X10);
    // 0x800B99C0: sw          $t3, 0x138($s0)
    MEM_W(0X138, ctx->r16) = ctx->r11;
    // 0x800B99C4: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800B99C8: jal         0x800C6310
    // 0x800B99CC: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_2;
    // 0x800B99CC: sw          $t0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r8;
    after_2:
    // 0x800B99D0: lbu         $t6, 0x0($s0)
    ctx->r14 = MEM_BU(ctx->r16, 0X0);
    // 0x800B99D4: addiu       $t7, $s0, 0x120
    ctx->r15 = ADD32(ctx->r16, 0X120);
    // 0x800B99D8: addiu       $a0, $s0, 0x138
    ctx->r4 = ADD32(ctx->r16, 0X138);
    // 0x800B99DC: ori         $t5, $t6, 0x8
    ctx->r13 = ctx->r14 | 0X8;
    // 0x800B99E0: sb          $t5, 0x0($s0)
    MEM_B(0X0, ctx->r16) = ctx->r13;
    // 0x800B99E4: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x800B99E8: addiu       $a1, $s0, 0x134
    ctx->r5 = ADD32(ctx->r16, 0X134);
    // 0x800B99EC: addiu       $a2, $s0, 0x13C
    ctx->r6 = ADD32(ctx->r16, 0X13C);
    // 0x800B99F0: jal         0x800B8D88
    // 0x800B99F4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    Audio_DmaPartialCopyAsync(rdram, ctx);
        goto after_3;
    // 0x800B99F4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_3:
    // 0x800B99F8: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B99FC: addu        $at, $at, $s2
    ctx->r1 = ADD32(ctx->r1, ctx->r18);
    // 0x800B9A00: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800B9A04: lw          $v0, 0x44($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X44);
    // 0x800B9A08: sb          $t9, -0x1488($at)
    MEM_B(-0X1488, ctx->r1) = ctx->r25;
L_800B9A0C:
    // 0x800B9A0C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9A10: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x800B9A14: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x800B9A18: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x800B9A1C: jr          $ra
    // 0x800B9A20: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x800B9A20: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void AudioLoad_SequenceDmaImmediate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9A24: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B9A28: lw          $t6, 0x5504($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5504);
    // 0x800B9A2C: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800B9A30: sll         $t8, $a0, 3
    ctx->r24 = S32(ctx->r4 << 3);
    // 0x800B9A34: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B9A38: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x800B9A3C: addu        $v0, $t6, $t8
    ctx->r2 = ADD32(ctx->r14, ctx->r24);
    // 0x800B9A40: lw          $a2, 0x8($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X8);
    // 0x800B9A44: lw          $t0, 0x4($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X4);
    // 0x800B9A48: or          $t7, $a0, $zero
    ctx->r15 = ctx->r4 | 0;
    // 0x800B9A4C: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800B9A50: addiu       $a2, $a2, 0x1E
    ctx->r6 = ADD32(ctx->r6, 0X1E);
    // 0x800B9A54: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800B9A58: and         $t9, $a2, $at
    ctx->r25 = ctx->r6 & ctx->r1;
    // 0x800B9A5C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B9A60: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800B9A64: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    // 0x800B9A68: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x800B9A6C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800B9A70: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x800B9A74: jal         0x800B7B14
    // 0x800B9A78: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    AudioHeap_AllocCached(rdram, ctx);
        goto after_0;
    // 0x800B9A78: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    after_0:
    // 0x800B9A7C: lw          $a2, 0x2C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9A80: bne         $v0, $zero, L_800B9A90
    if (ctx->r2 != 0) {
        // 0x800B9A84: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800B9A90;
    }
    // 0x800B9A84: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800B9A88: b           L_800B9AB4
    // 0x800B9A8C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B9AB4;
    // 0x800B9A8C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B9A90:
    // 0x800B9A90: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x800B9A94: jal         0x800B8CB0
    // 0x800B9A98: sw          $a1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r5;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_1;
    // 0x800B9A98: sw          $a1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r5;
    after_1:
    // 0x800B9A9C: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800B9AA0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B9AA4: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x800B9AA8: addu        $at, $at, $t2
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x800B9AAC: lw          $v0, 0x28($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X28);
    // 0x800B9AB0: sb          $t1, -0x1448($at)
    MEM_B(-0X1448, ctx->r1) = ctx->r9;
L_800B9AB4:
    // 0x800B9AB4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800B9AB8: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800B9ABC: jr          $ra
    // 0x800B9AC0: nop

    return;
    // 0x800B9AC0: nop

;}
RECOMP_FUNC void AudioLoad_SequenceDmaAsync(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9AC4: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x800B9AC8: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800B9ACC: lw          $t6, 0x5504($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5504);
    // 0x800B9AD0: sll         $t7, $a0, 3
    ctx->r15 = S32(ctx->r4 << 3);
    // 0x800B9AD4: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800B9AD8: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x800B9ADC: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x800B9AE0: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x800B9AE4: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800B9AE8: lw          $s0, 0x8($v0)
    ctx->r16 = MEM_W(ctx->r2, 0X8);
    // 0x800B9AEC: lw          $t9, 0x4($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X4);
    // 0x800B9AF0: or          $s1, $a2, $zero
    ctx->r17 = ctx->r6 | 0;
    // 0x800B9AF4: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800B9AF8: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800B9AFC: addiu       $s0, $s0, 0x1E
    ctx->r16 = ADD32(ctx->r16, 0X1E);
    // 0x800B9B00: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800B9B04: and         $a2, $s0, $at
    ctx->r6 = ctx->r16 & ctx->r1;
    // 0x800B9B08: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B9B0C: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x800B9B10: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    // 0x800B9B14: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800B9B18: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x800B9B1C: sw          $s2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r18;
    // 0x800B9B20: jal         0x800B7B14
    // 0x800B9B24: sw          $t9, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r25;
    AudioHeap_AllocCached(rdram, ctx);
        goto after_0;
    // 0x800B9B24: sw          $t9, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r25;
    after_0:
    // 0x800B9B28: bne         $v0, $zero, L_800B9B38
    if (ctx->r2 != 0) {
        // 0x800B9B2C: or          $s2, $v0, $zero
        ctx->r18 = ctx->r2 | 0;
            goto L_800B9B38;
    }
    // 0x800B9B2C: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x800B9B30: b           L_800B9BD4
    // 0x800B9B34: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800B9BD4;
    // 0x800B9B34: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800B9B38:
    // 0x800B9B38: slti        $at, $s0, 0x41
    ctx->r1 = SIGNED(ctx->r16) < 0X41 ? 1 : 0;
    // 0x800B9B3C: beq         $at, $zero, L_800B9B6C
    if (ctx->r1 == 0) {
        // 0x800B9B40: lw          $a0, 0x3C($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X3C);
            goto L_800B9B6C;
    }
    // 0x800B9B40: lw          $a0, 0x3C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X3C);
    // 0x800B9B44: lw          $a0, 0x3C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X3C);
    // 0x800B9B48: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x800B9B4C: jal         0x800B8CB0
    // 0x800B9B50: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_1;
    // 0x800B9B50: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_1:
    // 0x800B9B54: lw          $t1, 0x48($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X48);
    // 0x800B9B58: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B9B5C: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x800B9B60: addu        $at, $at, $t1
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x800B9B64: b           L_800B9BD0
    // 0x800B9B68: sb          $t0, -0x1448($at)
    MEM_B(-0X1448, ctx->r1) = ctx->r8;
        goto L_800B9BD0;
    // 0x800B9B68: sb          $t0, -0x1448($at)
    MEM_B(-0X1448, ctx->r1) = ctx->r8;
L_800B9B6C:
    // 0x800B9B6C: or          $a1, $s2, $zero
    ctx->r5 = ctx->r18 | 0;
    // 0x800B9B70: jal         0x800B8CB0
    // 0x800B9B74: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_2;
    // 0x800B9B74: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    after_2:
    // 0x800B9B78: addiu       $a3, $s1, 0xD4
    ctx->r7 = ADD32(ctx->r17, 0XD4);
    // 0x800B9B7C: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x800B9B80: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
    // 0x800B9B84: addiu       $a1, $s1, 0xEC
    ctx->r5 = ADD32(ctx->r17, 0XEC);
    // 0x800B9B88: jal         0x800C6310
    // 0x800B9B8C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_3;
    // 0x800B9B8C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800B9B90: lbu         $t3, 0x0($s1)
    ctx->r11 = MEM_BU(ctx->r17, 0X0);
    // 0x800B9B94: lw          $a3, 0x34($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X34);
    // 0x800B9B98: addiu       $t5, $s1, 0xF0
    ctx->r13 = ADD32(ctx->r17, 0XF0);
    // 0x800B9B9C: ori         $t4, $t3, 0x10
    ctx->r12 = ctx->r11 | 0X10;
    // 0x800B9BA0: sb          $t4, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r12;
    // 0x800B9BA4: lw          $a0, 0x3C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X3C);
    // 0x800B9BA8: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x800B9BAC: addiu       $a1, $s2, 0x40
    ctx->r5 = ADD32(ctx->r18, 0X40);
    // 0x800B9BB0: addiu       $a2, $s0, -0x40
    ctx->r6 = ADD32(ctx->r16, -0X40);
    // 0x800B9BB4: jal         0x800B8D28
    // 0x800B9BB8: addiu       $a0, $a0, 0x40
    ctx->r4 = ADD32(ctx->r4, 0X40);
    Audio_DmaCopyAsync(rdram, ctx);
        goto after_4;
    // 0x800B9BB8: addiu       $a0, $a0, 0x40
    ctx->r4 = ADD32(ctx->r4, 0X40);
    after_4:
    // 0x800B9BBC: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x800B9BC0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800B9BC4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800B9BC8: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800B9BCC: sb          $t6, -0x1448($at)
    MEM_B(-0X1448, ctx->r1) = ctx->r14;
L_800B9BD0:
    // 0x800B9BD0: or          $v0, $s2, $zero
    ctx->r2 = ctx->r18 | 0;
L_800B9BD4:
    // 0x800B9BD4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9BD8: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x800B9BDC: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x800B9BE0: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x800B9BE4: jr          $ra
    // 0x800B9BE8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800B9BE8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void AudioLoad_GetMissingBank(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9BEC: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800B9BF0: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800B9BF4: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800B9BF8: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800B9BFC: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800B9C00: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800B9C04: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800B9C08: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800B9C0C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800B9C10: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800B9C14: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B9C18: sw          $zero, 0x0($a2)
    MEM_W(0X0, ctx->r6) = 0;
    // 0x800B9C1C: sw          $zero, 0x0($a1)
    MEM_W(0X0, ctx->r5) = 0;
    // 0x800B9C20: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800B9C24: lw          $v0, 0x5510($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X5510);
    // 0x800B9C28: sll         $t6, $a0, 1
    ctx->r14 = S32(ctx->r4 << 1);
    // 0x800B9C2C: or          $s3, $a2, $zero
    ctx->r19 = ctx->r6 | 0;
    // 0x800B9C30: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x800B9C34: lhu         $s1, 0x0($t7)
    ctx->r17 = MEM_HU(ctx->r15, 0X0);
    // 0x800B9C38: or          $s4, $a1, $zero
    ctx->r20 = ctx->r5 | 0;
    // 0x800B9C3C: or          $fp, $zero, $zero
    ctx->r30 = 0 | 0;
    // 0x800B9C40: addu        $t8, $s1, $v0
    ctx->r24 = ADD32(ctx->r17, ctx->r2);
    // 0x800B9C44: lbu         $s2, 0x0($t8)
    ctx->r18 = MEM_BU(ctx->r24, 0X0);
    // 0x800B9C48: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800B9C4C: andi        $t9, $s1, 0xFFFF
    ctx->r25 = ctx->r17 & 0XFFFF;
    // 0x800B9C50: beq         $s2, $zero, L_800B9CF0
    if (ctx->r18 == 0) {
        // 0x800B9C54: or          $s1, $t9, $zero
        ctx->r17 = ctx->r25 | 0;
            goto L_800B9CF0;
    }
    // 0x800B9C54: or          $s1, $t9, $zero
    ctx->r17 = ctx->r25 | 0;
    // 0x800B9C58: lui         $s7, 0x8004
    ctx->r23 = S32(0X8004 << 16);
    // 0x800B9C5C: lui         $s6, 0x8004
    ctx->r22 = S32(0X8004 << 16);
    // 0x800B9C60: addiu       $s6, $s6, -0x1488
    ctx->r22 = ADD32(ctx->r22, -0X1488);
    // 0x800B9C64: addiu       $s7, $s7, -0x1860
    ctx->r23 = ADD32(ctx->r23, -0X1860);
    // 0x800B9C68: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
L_800B9C6C:
    // 0x800B9C6C: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B9C70: lw          $t0, 0x5510($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X5510);
    // 0x800B9C74: or          $a0, $s7, $zero
    ctx->r4 = ctx->r23 | 0;
    // 0x800B9C78: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800B9C7C: addu        $t1, $s1, $t0
    ctx->r9 = ADD32(ctx->r17, ctx->r8);
    // 0x800B9C80: lbu         $s0, 0x0($t1)
    ctx->r16 = MEM_BU(ctx->r9, 0X0);
    // 0x800B9C84: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800B9C88: andi        $t2, $s1, 0xFFFF
    ctx->r10 = ctx->r17 & 0XFFFF;
    // 0x800B9C8C: addu        $t3, $s6, $s0
    ctx->r11 = ADD32(ctx->r22, ctx->r16);
    // 0x800B9C90: lbu         $t4, 0x0($t3)
    ctx->r12 = MEM_BU(ctx->r11, 0X0);
    // 0x800B9C94: or          $s1, $t2, $zero
    ctx->r17 = ctx->r10 | 0;
    // 0x800B9C98: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B9C9C: slti        $t5, $t4, 0x2
    ctx->r13 = SIGNED(ctx->r12) < 0X2 ? 1 : 0;
    // 0x800B9CA0: xori        $t5, $t5, 0x1
    ctx->r13 = ctx->r13 ^ 0X1;
    // 0x800B9CA4: bne         $s5, $t5, L_800B9CBC
    if (ctx->r21 != ctx->r13) {
        // 0x800B9CA8: nop
    
            goto L_800B9CBC;
    }
    // 0x800B9CA8: nop

    // 0x800B9CAC: jal         0x800B811C
    // 0x800B9CB0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_0;
    // 0x800B9CB0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_0:
    // 0x800B9CB4: b           L_800B9CBC
    // 0x800B9CB8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_800B9CBC;
    // 0x800B9CB8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800B9CBC:
    // 0x800B9CBC: bne         $v1, $zero, L_800B9CD8
    if (ctx->r3 != 0) {
        // 0x800B9CC0: addiu       $s2, $s2, -0x1
        ctx->r18 = ADD32(ctx->r18, -0X1);
            goto L_800B9CD8;
    }
    // 0x800B9CC0: addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // 0x800B9CC4: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x800B9CC8: andi        $fp, $s0, 0xFF
    ctx->r30 = ctx->r16 & 0XFF;
    // 0x800B9CCC: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x800B9CD0: b           L_800B9CE4
    // 0x800B9CD4: sw          $t7, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r15;
        goto L_800B9CE4;
    // 0x800B9CD4: sw          $t7, 0x0($s3)
    MEM_W(0X0, ctx->r19) = ctx->r15;
L_800B9CD8:
    // 0x800B9CD8: lw          $t8, 0x0($s4)
    ctx->r24 = MEM_W(ctx->r20, 0X0);
    // 0x800B9CDC: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x800B9CE0: sw          $t9, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r25;
L_800B9CE4:
    // 0x800B9CE4: andi        $t0, $s2, 0xFF
    ctx->r8 = ctx->r18 & 0XFF;
    // 0x800B9CE8: bne         $t0, $zero, L_800B9C6C
    if (ctx->r8 != 0) {
        // 0x800B9CEC: or          $s2, $t0, $zero
        ctx->r18 = ctx->r8 | 0;
            goto L_800B9C6C;
    }
    // 0x800B9CEC: or          $s2, $t0, $zero
    ctx->r18 = ctx->r8 | 0;
L_800B9CF0:
    // 0x800B9CF0: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800B9CF4: or          $v0, $fp, $zero
    ctx->r2 = ctx->r30 | 0;
    // 0x800B9CF8: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800B9CFC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B9D00: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800B9D04: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800B9D08: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800B9D0C: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800B9D10: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9D14: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800B9D18: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800B9D1C: jr          $ra
    // 0x800B9D20: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800B9D20: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void Audio_LoadBanksImmediate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9D24: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800B9D28: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800B9D2C: lui         $s6, 0x8004
    ctx->r22 = S32(0X8004 << 16);
    // 0x800B9D30: addiu       $s6, $s6, 0x5510
    ctx->r22 = ADD32(ctx->r22, 0X5510);
    // 0x800B9D34: lw          $v0, 0x0($s6)
    ctx->r2 = MEM_W(ctx->r22, 0X0);
    // 0x800B9D38: sll         $t6, $a0, 1
    ctx->r14 = S32(ctx->r4 << 1);
    // 0x800B9D3C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800B9D40: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800B9D44: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800B9D48: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800B9D4C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800B9D50: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800B9D54: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B9D58: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x800B9D5C: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x800B9D60: lhu         $s1, 0x0($t7)
    ctx->r17 = MEM_HU(ctx->r15, 0X0);
    // 0x800B9D64: lui         $s5, 0x8004
    ctx->r21 = S32(0X8004 << 16);
    // 0x800B9D68: addiu       $s5, $s5, -0x1860
    ctx->r21 = ADD32(ctx->r21, -0X1860);
    // 0x800B9D6C: addu        $t8, $s1, $v0
    ctx->r24 = ADD32(ctx->r17, ctx->r2);
    // 0x800B9D70: lbu         $s2, 0x0($t8)
    ctx->r18 = MEM_BU(ctx->r24, 0X0);
    // 0x800B9D74: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800B9D78: andi        $t9, $s1, 0xFFFF
    ctx->r25 = ctx->r17 & 0XFFFF;
    // 0x800B9D7C: beq         $s2, $zero, L_800B9E08
    if (ctx->r18 == 0) {
        // 0x800B9D80: or          $s1, $t9, $zero
        ctx->r17 = ctx->r25 | 0;
            goto L_800B9E08;
    }
    // 0x800B9D80: or          $s1, $t9, $zero
    ctx->r17 = ctx->r25 | 0;
    // 0x800B9D84: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800B9D88: addiu       $s4, $s4, -0x1488
    ctx->r20 = ADD32(ctx->r20, -0X1488);
    // 0x800B9D8C: addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
L_800B9D90:
    // 0x800B9D90: lw          $t0, 0x0($s6)
    ctx->r8 = MEM_W(ctx->r22, 0X0);
    // 0x800B9D94: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x800B9D98: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800B9D9C: addu        $t1, $s1, $t0
    ctx->r9 = ADD32(ctx->r17, ctx->r8);
    // 0x800B9DA0: lbu         $s0, 0x0($t1)
    ctx->r16 = MEM_BU(ctx->r9, 0X0);
    // 0x800B9DA4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800B9DA8: andi        $t2, $s1, 0xFFFF
    ctx->r10 = ctx->r17 & 0XFFFF;
    // 0x800B9DAC: addu        $t3, $s4, $s0
    ctx->r11 = ADD32(ctx->r20, ctx->r16);
    // 0x800B9DB0: lbu         $t4, 0x0($t3)
    ctx->r12 = MEM_BU(ctx->r11, 0X0);
    // 0x800B9DB4: or          $s1, $t2, $zero
    ctx->r17 = ctx->r10 | 0;
    // 0x800B9DB8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B9DBC: slti        $t5, $t4, 0x2
    ctx->r13 = SIGNED(ctx->r12) < 0X2 ? 1 : 0;
    // 0x800B9DC0: xori        $t5, $t5, 0x1
    ctx->r13 = ctx->r13 ^ 0X1;
    // 0x800B9DC4: bne         $s3, $t5, L_800B9DDC
    if (ctx->r19 != ctx->r13) {
        // 0x800B9DC8: nop
    
            goto L_800B9DDC;
    }
    // 0x800B9DC8: nop

    // 0x800B9DCC: jal         0x800B811C
    // 0x800B9DD0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_0;
    // 0x800B9DD0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_0:
    // 0x800B9DD4: b           L_800B9DDC
    // 0x800B9DD8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_800B9DDC;
    // 0x800B9DD8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800B9DDC:
    // 0x800B9DDC: bne         $v1, $zero, L_800B9DF0
    if (ctx->r3 != 0) {
        // 0x800B9DE0: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_800B9DF0;
    }
    // 0x800B9DE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800B9DE4: jal         0x800B9774
    // 0x800B9DE8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    Audio_BankLoadImmediate(rdram, ctx);
        goto after_1;
    // 0x800B9DE8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_1:
    // 0x800B9DEC: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800B9DF0:
    // 0x800B9DF0: addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // 0x800B9DF4: andi        $t6, $s2, 0xFF
    ctx->r14 = ctx->r18 & 0XFF;
    // 0x800B9DF8: bne         $t6, $zero, L_800B9D90
    if (ctx->r14 != 0) {
        // 0x800B9DFC: or          $s2, $t6, $zero
        ctx->r18 = ctx->r14 | 0;
            goto L_800B9D90;
    }
    // 0x800B9DFC: or          $s2, $t6, $zero
    ctx->r18 = ctx->r14 | 0;
    // 0x800B9E00: sw          $v1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r3;
    // 0x800B9E04: sw          $s0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r16;
L_800B9E08:
    // 0x800B9E08: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x800B9E0C: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x800B9E10: lw          $v0, 0x3C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X3C);
    // 0x800B9E14: sb          $s0, 0x0($t7)
    MEM_B(0X0, ctx->r15) = ctx->r16;
    // 0x800B9E18: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800B9E1C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800B9E20: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800B9E24: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800B9E28: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800B9E2C: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800B9E30: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800B9E34: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800B9E38: jr          $ra
    // 0x800B9E3C: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800B9E3C: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void Audio_PreLoadSequence(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9E40: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800B9E44: lhu         $t7, 0x5514($t7)
    ctx->r15 = MEM_HU(ctx->r15, 0X5514);
    // 0x800B9E48: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800B9E4C: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800B9E50: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800B9E54: sltu        $at, $a0, $t7
    ctx->r1 = ctx->r4 < ctx->r15 ? 1 : 0;
    // 0x800B9E58: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800B9E5C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800B9E60: beq         $at, $zero, L_800B9F2C
    if (ctx->r1 == 0) {
        // 0x800B9E64: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_800B9F2C;
    }
    // 0x800B9E64: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800B9E68: lui         $t8, 0x1971
    ctx->r24 = S32(0X1971 << 16);
    // 0x800B9E6C: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800B9E70: addiu       $t9, $t9, -0x1D00
    ctx->r25 = ADD32(ctx->r25, -0X1D00);
    // 0x800B9E74: ori         $t8, $t8, 0x515
    ctx->r24 = ctx->r24 | 0X515;
    // 0x800B9E78: andi        $t0, $a1, 0x2
    ctx->r8 = ctx->r5 & 0X2;
    // 0x800B9E7C: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
    // 0x800B9E80: beq         $t0, $zero, L_800B9EA4
    if (ctx->r8 == 0) {
        // 0x800B9E84: or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
            goto L_800B9EA4;
    }
    // 0x800B9E84: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x800B9E88: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800B9E8C: addiu       $a1, $sp, 0x23
    ctx->r5 = ADD32(ctx->r29, 0X23);
    // 0x800B9E90: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    // 0x800B9E94: jal         0x800B9D24
    // 0x800B9E98: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    Audio_LoadBanksImmediate(rdram, ctx);
        goto after_0;
    // 0x800B9E98: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    after_0:
    // 0x800B9E9C: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
    // 0x800B9EA0: lw          $a2, 0x28($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X28);
L_800B9EA4:
    // 0x800B9EA4: andi        $t1, $v1, 0x1
    ctx->r9 = ctx->r3 & 0X1;
    // 0x800B9EA8: beq         $t1, $zero, L_800B9F18
    if (ctx->r9 == 0) {
        // 0x800B9EAC: lui         $t2, 0x8004
        ctx->r10 = S32(0X8004 << 16);
            goto L_800B9F18;
    }
    // 0x800B9EAC: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800B9EB0: addu        $t2, $t2, $a2
    ctx->r10 = ADD32(ctx->r10, ctx->r6);
    // 0x800B9EB4: lbu         $t2, -0x1488($t2)
    ctx->r10 = MEM_BU(ctx->r10, -0X1488);
    // 0x800B9EB8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800B9EBC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800B9EC0: slti        $t3, $t2, 0x2
    ctx->r11 = SIGNED(ctx->r10) < 0X2 ? 1 : 0;
    // 0x800B9EC4: xori        $t3, $t3, 0x1
    ctx->r11 = ctx->r11 ^ 0X1;
    // 0x800B9EC8: bne         $t3, $at, L_800B9EEC
    if (ctx->r11 != ctx->r1) {
        // 0x800B9ECC: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_800B9EEC;
    }
    // 0x800B9ECC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800B9ED0: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    // 0x800B9ED4: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800B9ED8: jal         0x800B811C
    // 0x800B9EDC: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_1;
    // 0x800B9EDC: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    after_1:
    // 0x800B9EE0: lw          $a2, 0x28($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X28);
    // 0x800B9EE4: b           L_800B9EEC
    // 0x800B9EE8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_800B9EEC;
    // 0x800B9EE8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800B9EEC:
    // 0x800B9EEC: bne         $v1, $zero, L_800B9F18
    if (ctx->r3 != 0) {
        // 0x800B9EF0: or          $a0, $a2, $zero
        ctx->r4 = ctx->r6 | 0;
            goto L_800B9F18;
    }
    // 0x800B9EF0: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800B9EF4: jal         0x800B9A24
    // 0x800B9EF8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    AudioLoad_SequenceDmaImmediate(rdram, ctx);
        goto after_2;
    // 0x800B9EF8: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_2:
    // 0x800B9EFC: bne         $v0, $zero, L_800B9F18
    if (ctx->r2 != 0) {
        // 0x800B9F00: lui         $t4, 0x7655
        ctx->r12 = S32(0X7655 << 16);
            goto L_800B9F18;
    }
    // 0x800B9F00: lui         $t4, 0x7655
    ctx->r12 = S32(0X7655 << 16);
    // 0x800B9F04: lui         $t5, 0x800F
    ctx->r13 = S32(0X800F << 16);
    // 0x800B9F08: addiu       $t5, $t5, -0x1D00
    ctx->r13 = ADD32(ctx->r13, -0X1D00);
    // 0x800B9F0C: ori         $t4, $t4, 0x7364
    ctx->r12 = ctx->r12 | 0X7364;
    // 0x800B9F10: b           L_800B9F2C
    // 0x800B9F14: sw          $t4, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r12;
        goto L_800B9F2C;
    // 0x800B9F14: sw          $t4, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r12;
L_800B9F18:
    // 0x800B9F18: lui         $t6, 0x7655
    ctx->r14 = S32(0X7655 << 16);
    // 0x800B9F1C: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800B9F20: addiu       $t7, $t7, -0x1D00
    ctx->r15 = ADD32(ctx->r15, -0X1D00);
    // 0x800B9F24: ori         $t6, $t6, 0x7364
    ctx->r14 = ctx->r14 | 0X7364;
    // 0x800B9F28: sw          $t6, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r14;
L_800B9F2C:
    // 0x800B9F2C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800B9F30: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800B9F34: jr          $ra
    // 0x800B9F38: nop

    return;
    // 0x800B9F38: nop

;}
RECOMP_FUNC void Audio_LoadSequence(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9F3C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800B9F40: bne         $a2, $zero, L_800B9F5C
    if (ctx->r6 != 0) {
        // 0x800B9F44: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800B9F5C;
    }
    // 0x800B9F44: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800B9F48: lui         $t6, 0x1971
    ctx->r14 = S32(0X1971 << 16);
    // 0x800B9F4C: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800B9F50: addiu       $t7, $t7, -0x1D00
    ctx->r15 = ADD32(ctx->r15, -0X1D00);
    // 0x800B9F54: ori         $t6, $t6, 0x515
    ctx->r14 = ctx->r14 | 0X515;
    // 0x800B9F58: sw          $t6, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r14;
L_800B9F5C:
    // 0x800B9F5C: jal         0x800B9F90
    // 0x800B9F60: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    Audio_LoadSequenceInternal(rdram, ctx);
        goto after_0;
    // 0x800B9F60: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    after_0:
    // 0x800B9F64: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x800B9F68: lui         $t8, 0x7655
    ctx->r24 = S32(0X7655 << 16);
    // 0x800B9F6C: ori         $t8, $t8, 0x7364
    ctx->r24 = ctx->r24 | 0X7364;
    // 0x800B9F70: bne         $a2, $zero, L_800B9F80
    if (ctx->r6 != 0) {
        // 0x800B9F74: lui         $t9, 0x800F
        ctx->r25 = S32(0X800F << 16);
            goto L_800B9F80;
    }
    // 0x800B9F74: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800B9F78: addiu       $t9, $t9, -0x1D00
    ctx->r25 = ADD32(ctx->r25, -0X1D00);
    // 0x800B9F7C: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
L_800B9F80:
    // 0x800B9F80: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800B9F84: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800B9F88: jr          $ra
    // 0x800B9F8C: nop

    return;
    // 0x800B9F8C: nop

;}
RECOMP_FUNC void Audio_LoadSequenceInternal(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800B9F90: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800B9F94: lhu         $t7, 0x5514($t7)
    ctx->r15 = MEM_HU(ctx->r15, 0X5514);
    // 0x800B9F98: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800B9F9C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800B9FA0: sltu        $at, $a1, $t7
    ctx->r1 = ctx->r5 < ctx->r15 ? 1 : 0;
    // 0x800B9FA4: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800B9FA8: sw          $a0, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r4;
    // 0x800B9FAC: sw          $a1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r5;
    // 0x800B9FB0: beq         $at, $zero, L_800BA0EC
    if (ctx->r1 == 0) {
        // 0x800B9FB4: sw          $a2, 0x48($sp)
        MEM_W(0X48, ctx->r29) = ctx->r6;
            goto L_800BA0EC;
    }
    // 0x800B9FB4: sw          $a2, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r6;
    // 0x800B9FB8: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x800B9FBC: addu        $t9, $t9, $a0
    ctx->r25 = ADD32(ctx->r25, ctx->r4);
    // 0x800B9FC0: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800B9FC4: addiu       $t0, $t0, -0x338
    ctx->r8 = ADD32(ctx->r8, -0X338);
    // 0x800B9FC8: sll         $t9, $t9, 6
    ctx->r25 = S32(ctx->r25 << 6);
    // 0x800B9FCC: addu        $s0, $t9, $t0
    ctx->r16 = ADD32(ctx->r25, ctx->r8);
    // 0x800B9FD0: jal         0x800BCEE0
    // 0x800B9FD4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_0;
    // 0x800B9FD4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800B9FD8: lw          $t1, 0x48($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X48);
    // 0x800B9FDC: addiu       $a1, $sp, 0x28
    ctx->r5 = ADD32(ctx->r29, 0X28);
    // 0x800B9FE0: addiu       $a2, $sp, 0x2C
    ctx->r6 = ADD32(ctx->r29, 0X2C);
    // 0x800B9FE4: beq         $t1, $zero, L_800BA048
    if (ctx->r9 == 0) {
        // 0x800B9FE8: lw          $a0, 0x44($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X44);
            goto L_800BA048;
    }
    // 0x800B9FE8: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    // 0x800B9FEC: sw          $zero, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = 0;
    // 0x800B9FF0: sw          $zero, 0x28($sp)
    MEM_W(0X28, ctx->r29) = 0;
    // 0x800B9FF4: jal         0x800B9BEC
    // 0x800B9FF8: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    AudioLoad_GetMissingBank(rdram, ctx);
        goto after_1;
    // 0x800B9FF8: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    after_1:
    // 0x800B9FFC: lw          $t2, 0x2C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X2C);
    // 0x800BA000: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BA004: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x800BA008: bne         $t2, $at, L_800BA030
    if (ctx->r10 != ctx->r1) {
        // 0x800BA00C: addiu       $a1, $s0, 0x5
        ctx->r5 = ADD32(ctx->r16, 0X5);
            goto L_800BA030;
    }
    // 0x800BA00C: addiu       $a1, $s0, 0x5
    ctx->r5 = ADD32(ctx->r16, 0X5);
    // 0x800BA010: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800BA014: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800BA018: jal         0x800B98C0
    // 0x800BA01C: sw          $v0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r2;
    Audio_BankLoadAsync(rdram, ctx);
        goto after_2;
    // 0x800BA01C: sw          $v0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r2;
    after_2:
    // 0x800BA020: beq         $v0, $zero, L_800BA0EC
    if (ctx->r2 == 0) {
        // 0x800BA024: lw          $a0, 0x24($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X24);
            goto L_800BA0EC;
    }
    // 0x800BA024: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x800BA028: b           L_800BA058
    // 0x800BA02C: sb          $a0, 0x5($s0)
    MEM_B(0X5, ctx->r16) = ctx->r4;
        goto L_800BA058;
    // 0x800BA02C: sb          $a0, 0x5($s0)
    MEM_B(0X5, ctx->r16) = ctx->r4;
L_800BA030:
    // 0x800BA030: jal         0x800B9D24
    // 0x800BA034: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    Audio_LoadBanksImmediate(rdram, ctx);
        goto after_3;
    // 0x800BA034: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    after_3:
    // 0x800BA038: bnel        $v0, $zero, L_800BA05C
    if (ctx->r2 != 0) {
        // 0x800BA03C: lw          $a2, 0x44($sp)
        ctx->r6 = MEM_W(ctx->r29, 0X44);
            goto L_800BA05C;
    }
    goto skip_0;
    // 0x800BA03C: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    skip_0:
    // 0x800BA040: b           L_800BA0F0
    // 0x800BA044: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_800BA0F0;
    // 0x800BA044: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_800BA048:
    // 0x800BA048: jal         0x800B9D24
    // 0x800BA04C: addiu       $a1, $s0, 0x5
    ctx->r5 = ADD32(ctx->r16, 0X5);
    Audio_LoadBanksImmediate(rdram, ctx);
        goto after_4;
    // 0x800BA04C: addiu       $a1, $s0, 0x5
    ctx->r5 = ADD32(ctx->r16, 0X5);
    after_4:
    // 0x800BA050: beql        $v0, $zero, L_800BA0F0
    if (ctx->r2 == 0) {
        // 0x800BA054: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_800BA0F0;
    }
    goto skip_1;
    // 0x800BA054: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_1:
L_800BA058:
    // 0x800BA058: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
L_800BA05C:
    // 0x800BA05C: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA060: addiu       $a0, $a0, -0x1A30
    ctx->r4 = ADD32(ctx->r4, -0X1A30);
    // 0x800BA064: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800BA068: jal         0x800B811C
    // 0x800BA06C: sb          $a2, 0x4($s0)
    MEM_B(0X4, ctx->r16) = ctx->r6;
    AudioHeap_SearchRegularCaches(rdram, ctx);
        goto after_5;
    // 0x800BA06C: sb          $a2, 0x4($s0)
    MEM_B(0X4, ctx->r16) = ctx->r6;
    after_5:
    // 0x800BA070: bne         $v0, $zero, L_800BA0C0
    if (ctx->r2 != 0) {
        // 0x800BA074: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800BA0C0;
    }
    // 0x800BA074: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800BA078: lw          $t3, 0x0($s0)
    ctx->r11 = MEM_W(ctx->r16, 0X0);
    // 0x800BA07C: lw          $t6, 0x48($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X48);
    // 0x800BA080: sll         $t5, $t3, 3
    ctx->r13 = S32(ctx->r11 << 3);
    // 0x800BA084: bltzl       $t5, L_800BA0F0
    if (SIGNED(ctx->r13) < 0) {
        // 0x800BA088: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_800BA0F0;
    }
    goto skip_2;
    // 0x800BA088: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_2:
    // 0x800BA08C: beq         $t6, $zero, L_800BA0AC
    if (ctx->r14 == 0) {
        // 0x800BA090: lw          $a0, 0x44($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X44);
            goto L_800BA0AC;
    }
    // 0x800BA090: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    // 0x800BA094: lw          $a0, 0x44($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X44);
    // 0x800BA098: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    // 0x800BA09C: jal         0x800B9AC4
    // 0x800BA0A0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    AudioLoad_SequenceDmaAsync(rdram, ctx);
        goto after_6;
    // 0x800BA0A0: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_6:
    // 0x800BA0A4: b           L_800BA0B8
    // 0x800BA0A8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
        goto L_800BA0B8;
    // 0x800BA0A8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800BA0AC:
    // 0x800BA0AC: jal         0x800B9A24
    // 0x800BA0B0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    AudioLoad_SequenceDmaImmediate(rdram, ctx);
        goto after_7;
    // 0x800BA0B0: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
    after_7:
    // 0x800BA0B4: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
L_800BA0B8:
    // 0x800BA0B8: beql        $v0, $zero, L_800BA0F0
    if (ctx->r2 == 0) {
        // 0x800BA0BC: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_800BA0F0;
    }
    goto skip_3;
    // 0x800BA0BC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_3:
L_800BA0C0:
    // 0x800BA0C0: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800BA0C4: jal         0x800BF13C
    // 0x800BA0C8: sw          $v1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r3;
    AudioSeq_ResetSequencePlayer(rdram, ctx);
        goto after_8;
    // 0x800BA0C8: sw          $v1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r3;
    after_8:
    // 0x800BA0CC: lw          $v1, 0x3C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X3C);
    // 0x800BA0D0: lbu         $t8, 0x0($s0)
    ctx->r24 = MEM_BU(ctx->r16, 0X0);
    // 0x800BA0D4: sb          $zero, 0x88($s0)
    MEM_B(0X88, ctx->r16) = 0;
    // 0x800BA0D8: sh          $zero, 0xE($s0)
    MEM_H(0XE, ctx->r16) = 0;
    // 0x800BA0DC: ori         $t9, $t8, 0x80
    ctx->r25 = ctx->r24 | 0X80;
    // 0x800BA0E0: sb          $t9, 0x0($s0)
    MEM_B(0X0, ctx->r16) = ctx->r25;
    // 0x800BA0E4: sw          $v1, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r3;
    // 0x800BA0E8: sw          $v1, 0x70($s0)
    MEM_W(0X70, ctx->r16) = ctx->r3;
L_800BA0EC:
    // 0x800BA0EC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_800BA0F0:
    // 0x800BA0F0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BA0F4: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x800BA0F8: jr          $ra
    // 0x800BA0FC: nop

    return;
    // 0x800BA0FC: nop

;}
RECOMP_FUNC void AudioLoad_Init(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BA100: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x800BA104: lui         $t6, 0x800F
    ctx->r14 = S32(0X800F << 16);
    // 0x800BA108: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800BA10C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800BA110: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800BA114: addiu       $t6, $t6, -0x1D00
    ctx->r14 = ADD32(ctx->r14, -0X1D00);
    // 0x800BA118: sw          $zero, 0x0($t6)
    MEM_W(0X0, ctx->r14) = 0;
    // 0x800BA11C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800BA120: lw          $a0, -0x1D08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1D08);
    // 0x800BA124: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BA128: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BA12C: bgez        $a0, L_800BA13C
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800BA130: sra         $t7, $a0, 3
        ctx->r15 = S32(SIGNED(ctx->r4) >> 3);
            goto L_800BA13C;
    }
    // 0x800BA130: sra         $t7, $a0, 3
    ctx->r15 = S32(SIGNED(ctx->r4) >> 3);
    // 0x800BA134: addiu       $at, $a0, 0x7
    ctx->r1 = ADD32(ctx->r4, 0X7);
    // 0x800BA138: sra         $t7, $at, 3
    ctx->r15 = S32(SIGNED(ctx->r1) >> 3);
L_800BA13C:
    // 0x800BA13C: blez        $t7, L_800BA170
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800BA140: lui         $a0, 0x8004
        ctx->r4 = S32(0X8004 << 16);
            goto L_800BA170;
    }
    // 0x800BA140: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA144: lui         $t8, 0x8000
    ctx->r24 = S32(0X8000 << 16);
    // 0x800BA148: addiu       $v0, $t8, 0x1000
    ctx->r2 = ADD32(ctx->r24, 0X1000);
    // 0x800BA14C: sll         $t9, $t7, 3
    ctx->r25 = S32(ctx->r15 << 3);
    // 0x800BA150: addu        $v1, $t9, $v0
    ctx->r3 = ADD32(ctx->r25, ctx->r2);
L_800BA154:
    // 0x800BA154: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x800BA158: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x800BA15C: addiu       $t0, $zero, 0x0
    ctx->r8 = ADD32(0, 0X0);
    // 0x800BA160: addiu       $t1, $zero, 0x0
    ctx->r9 = ADD32(0, 0X0);
    // 0x800BA164: sw          $t1, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->r9;
    // 0x800BA168: bne         $at, $zero, L_800BA154
    if (ctx->r1 != 0) {
        // 0x800BA16C: sw          $t0, -0x8($v0)
        MEM_W(-0X8, ctx->r2) = ctx->r8;
            goto L_800BA154;
    }
    // 0x800BA16C: sw          $t0, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->r8;
L_800BA170:
    // 0x800BA170: addiu       $v0, $a0, -0x7F00
    ctx->r2 = ADD32(ctx->r4, -0X7F00);
    // 0x800BA174: addiu       $t2, $t2, 0x5638
    ctx->r10 = ADD32(ctx->r10, 0X5638);
    // 0x800BA178: subu        $v1, $t2, $v0
    ctx->r3 = SUB32(ctx->r10, ctx->r2);
    // 0x800BA17C: srl         $s0, $v1, 3
    ctx->r16 = S32(U32(ctx->r3) >> 3);
    // 0x800BA180: bltz        $s0, L_800BA1A0
    if (SIGNED(ctx->r16) < 0) {
        // 0x800BA184: addiu       $s0, $s0, -0x1
        ctx->r16 = ADD32(ctx->r16, -0X1);
            goto L_800BA1A0;
    }
L_800BA184:
    // 0x800BA184: addiu       $s0, $s0, -0x1
    ctx->r16 = ADD32(ctx->r16, -0X1);
    // 0x800BA188: addiu       $t4, $zero, 0x0
    ctx->r12 = ADD32(0, 0X0);
    // 0x800BA18C: addiu       $t5, $zero, 0x0
    ctx->r13 = ADD32(0, 0X0);
    // 0x800BA190: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x800BA194: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x800BA198: bgez        $s0, L_800BA184
    if (SIGNED(ctx->r16) >= 0) {
        // 0x800BA19C: addiu       $v0, $v0, 0x8
        ctx->r2 = ADD32(ctx->r2, 0X8);
            goto L_800BA184;
    }
    // 0x800BA19C: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
L_800BA1A0:
    // 0x800BA1A0: lui         $v0, 0x8000
    ctx->r2 = S32(0X8000 << 16);
    // 0x800BA1A4: lw          $v0, 0x300($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X300);
    // 0x800BA1A8: beq         $v0, $zero, L_800BA1C8
    if (ctx->r2 == 0) {
        // 0x800BA1AC: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_800BA1C8;
    }
    // 0x800BA1AC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BA1B0: beq         $v0, $at, L_800BA208
    if (ctx->r2 == ctx->r1) {
        // 0x800BA1B4: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800BA208;
    }
    // 0x800BA1B4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800BA1B8: beq         $v0, $at, L_800BA1E8
    if (ctx->r2 == ctx->r1) {
        // 0x800BA1BC: nop
    
            goto L_800BA1E8;
    }
    // 0x800BA1BC: nop

    // 0x800BA1C0: b           L_800BA208
    // 0x800BA1C4: nop

        goto L_800BA208;
    // 0x800BA1C4: nop

L_800BA1C8:
    // 0x800BA1C8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA1CC: lwc1        $f4, -0x43B0($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X43B0);
    // 0x800BA1D0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA1D4: addiu       $t6, $zero, 0x32
    ctx->r14 = ADD32(0, 0X32);
    // 0x800BA1D8: swc1        $f4, 0x5610($at)
    MEM_W(0X5610, ctx->r1) = ctx->f4.u32l;
    // 0x800BA1DC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA1E0: b           L_800BA224
    // 0x800BA1E4: sw          $t6, 0x5614($at)
    MEM_W(0X5614, ctx->r1) = ctx->r14;
        goto L_800BA224;
    // 0x800BA1E4: sw          $t6, 0x5614($at)
    MEM_W(0X5614, ctx->r1) = ctx->r14;
L_800BA1E8:
    // 0x800BA1E8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA1EC: lwc1        $f6, -0x43AC($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X43AC);
    // 0x800BA1F0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA1F4: addiu       $t7, $zero, 0x3C
    ctx->r15 = ADD32(0, 0X3C);
    // 0x800BA1F8: swc1        $f6, 0x5610($at)
    MEM_W(0X5610, ctx->r1) = ctx->f6.u32l;
    // 0x800BA1FC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA200: b           L_800BA224
    // 0x800BA204: sw          $t7, 0x5614($at)
    MEM_W(0X5614, ctx->r1) = ctx->r15;
        goto L_800BA224;
    // 0x800BA204: sw          $t7, 0x5614($at)
    MEM_W(0X5614, ctx->r1) = ctx->r15;
L_800BA208:
    // 0x800BA208: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA20C: lwc1        $f8, -0x43A8($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X43A8);
    // 0x800BA210: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA214: addiu       $t9, $zero, 0x3C
    ctx->r25 = ADD32(0, 0X3C);
    // 0x800BA218: swc1        $f8, 0x5610($at)
    MEM_W(0X5610, ctx->r1) = ctx->f8.u32l;
    // 0x800BA21C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA220: sw          $t9, 0x5614($at)
    MEM_W(0X5614, ctx->r1) = ctx->r25;
L_800BA224:
    // 0x800BA224: jal         0x800C56F4
    // 0x800BA228: nop

    AudioThread_Init(rdram, ctx);
        goto after_0;
    // 0x800BA228: nop

    after_0:
    // 0x800BA22C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BA230: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA234: addiu       $a0, $a0, 0x562A
    ctx->r4 = ADD32(ctx->r4, 0X562A);
    // 0x800BA238: addiu       $v0, $v0, 0x5624
    ctx->r2 = ADD32(ctx->r2, 0X5624);
    // 0x800BA23C: addiu       $v1, $zero, 0xA0
    ctx->r3 = ADD32(0, 0XA0);
L_800BA240:
    // 0x800BA240: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x800BA244: sltu        $at, $v0, $a0
    ctx->r1 = ctx->r2 < ctx->r4 ? 1 : 0;
    // 0x800BA248: bne         $at, $zero, L_800BA240
    if (ctx->r1 != 0) {
        // 0x800BA24C: sh          $v1, -0x2($v0)
        MEM_H(-0X2, ctx->r2) = ctx->r3;
            goto L_800BA240;
    }
    // 0x800BA24C: sh          $v1, -0x2($v0)
    MEM_H(-0X2, ctx->r2) = ctx->r3;
    // 0x800BA250: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800BA254: addiu       $t8, $t8, 0x5550
    ctx->r24 = ADD32(ctx->r24, 0X5550);
    // 0x800BA258: sw          $zero, 0x0($t8)
    MEM_W(0X0, ctx->r24) = 0;
    // 0x800BA25C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA260: sw          $zero, 0x5558($at)
    MEM_W(0X5558, ctx->r1) = 0;
    // 0x800BA264: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA268: sw          $zero, 0x555C($at)
    MEM_W(0X555C, ctx->r1) = 0;
    // 0x800BA26C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA270: sb          $zero, 0x554E($at)
    MEM_B(0X554E, ctx->r1) = 0;
    // 0x800BA274: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BA278: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA27C: addiu       $v0, $v0, 0x5570
    ctx->r2 = ADD32(ctx->r2, 0X5570);
    // 0x800BA280: sw          $zero, 0x556C($at)
    MEM_W(0X556C, ctx->r1) = 0;
    // 0x800BA284: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA288: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800BA28C: sw          $zero, 0x34($v0)
    MEM_W(0X34, ctx->r2) = 0;
    // 0x800BA290: sw          $zero, 0x84($v0)
    MEM_W(0X84, ctx->r2) = 0;
    // 0x800BA294: addiu       $a1, $a1, 0x4DD0
    ctx->r5 = ADD32(ctx->r5, 0X4DD0);
    // 0x800BA298: addiu       $a0, $a0, 0x4DB8
    ctx->r4 = ADD32(ctx->r4, 0X4DB8);
    // 0x800BA29C: jal         0x800C6310
    // 0x800BA2A0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_1;
    // 0x800BA2A0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_1:
    // 0x800BA2A4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA2A8: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800BA2AC: addiu       $a1, $a1, 0x47B8
    ctx->r5 = ADD32(ctx->r5, 0X47B8);
    // 0x800BA2B0: addiu       $a0, $a0, 0x47A0
    ctx->r4 = ADD32(ctx->r4, 0X47A0);
    // 0x800BA2B4: jal         0x800C6310
    // 0x800BA2B8: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_2;
    // 0x800BA2B8: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    after_2:
    // 0x800BA2BC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA2C0: sw          $zero, 0x5554($at)
    MEM_W(0X5554, ctx->r1) = 0;
    // 0x800BA2C4: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA2C8: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800BA2CC: sw          $zero, 0x52F0($at)
    MEM_W(0X52F0, ctx->r1) = 0;
    // 0x800BA2D0: jal         0x800B7848
    // 0x800BA2D4: lw          $a0, -0x1D04($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1D04);
    AudioHeap_InitMainPools(rdram, ctx);
        goto after_3;
    // 0x800BA2D4: lw          $a0, -0x1D04($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X1D04);
    after_3:
    // 0x800BA2D8: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800BA2DC: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BA2E0: addiu       $s1, $s1, -0x1AA0
    ctx->r17 = ADD32(ctx->r17, -0X1AA0);
    // 0x800BA2E4: addiu       $a2, $a2, 0x5618
    ctx->r6 = ADD32(ctx->r6, 0X5618);
    // 0x800BA2E8: addiu       $s0, $zero, 0xA00
    ctx->r16 = ADD32(0, 0XA00);
    // 0x800BA2EC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
L_800BA2F0:
    // 0x800BA2F0: addiu       $a1, $zero, 0xA00
    ctx->r5 = ADD32(0, 0XA00);
    // 0x800BA2F4: jal         0x800B7760
    // 0x800BA2F8: sw          $a2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r6;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_4;
    // 0x800BA2F8: sw          $a2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r6;
    after_4:
    // 0x800BA2FC: lw          $a2, 0x2C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X2C);
    // 0x800BA300: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800BA304: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800BA308: sw          $v0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r2;
L_800BA30C:
    // 0x800BA30C: lw          $t0, 0x0($a2)
    ctx->r8 = MEM_W(ctx->r6, 0X0);
    // 0x800BA310: addu        $t1, $t0, $v1
    ctx->r9 = ADD32(ctx->r8, ctx->r3);
    // 0x800BA314: sh          $zero, 0x0($t1)
    MEM_H(0X0, ctx->r9) = 0;
    // 0x800BA318: lw          $t2, 0x0($a2)
    ctx->r10 = MEM_W(ctx->r6, 0X0);
    // 0x800BA31C: addu        $t3, $t2, $v1
    ctx->r11 = ADD32(ctx->r10, ctx->r3);
    // 0x800BA320: sh          $zero, 0x2($t3)
    MEM_H(0X2, ctx->r11) = 0;
    // 0x800BA324: lw          $t4, 0x0($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X0);
    // 0x800BA328: addu        $t5, $t4, $v1
    ctx->r13 = ADD32(ctx->r12, ctx->r3);
    // 0x800BA32C: sh          $zero, 0x4($t5)
    MEM_H(0X4, ctx->r13) = 0;
    // 0x800BA330: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x800BA334: addu        $t7, $t6, $v1
    ctx->r15 = ADD32(ctx->r14, ctx->r3);
    // 0x800BA338: addiu       $v1, $v1, 0x8
    ctx->r3 = ADD32(ctx->r3, 0X8);
    // 0x800BA33C: bne         $v1, $s0, L_800BA30C
    if (ctx->r3 != ctx->r16) {
        // 0x800BA340: sh          $zero, 0x6($t7)
        MEM_H(0X6, ctx->r15) = 0;
            goto L_800BA30C;
    }
    // 0x800BA340: sh          $zero, 0x6($t7)
    MEM_H(0X6, ctx->r15) = 0;
    // 0x800BA344: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x800BA348: addiu       $t9, $t9, 0x5624
    ctx->r25 = ADD32(ctx->r25, 0X5624);
    // 0x800BA34C: bnel        $a2, $t9, L_800BA2F0
    if (ctx->r6 != ctx->r25) {
        // 0x800BA350: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_800BA2F0;
    }
    goto skip_0;
    // 0x800BA350: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    skip_0:
    // 0x800BA354: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA358: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800BA35C: sb          $zero, -0x1347($at)
    MEM_B(-0X1347, ctx->r1) = 0;
    // 0x800BA360: addiu       $t0, $t0, -0x1348
    ctx->r8 = ADD32(ctx->r8, -0X1348);
    // 0x800BA364: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800BA368: jal         0x800B8480
    // 0x800BA36C: sb          $t8, 0x0($t0)
    MEM_B(0X0, ctx->r8) = ctx->r24;
    AudioHeap_ResetStep(rdram, ctx);
        goto after_5;
    // 0x800BA36C: sb          $t8, 0x0($t0)
    MEM_B(0X0, ctx->r8) = ctx->r24;
    after_5:
    // 0x800BA370: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA374: addiu       $v1, $v1, 0x5504
    ctx->r3 = ADD32(ctx->r3, 0X5504);
    // 0x800BA378: addiu       $a1, $sp, 0x48
    ctx->r5 = ADD32(ctx->r29, 0X48);
    // 0x800BA37C: lui         $a0, 0x7B
    ctx->r4 = S32(0X7B << 16);
    // 0x800BA380: sw          $a1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r5;
    // 0x800BA384: addiu       $a0, $a0, -0x1750
    ctx->r4 = ADD32(ctx->r4, -0X1750);
    // 0x800BA388: jal         0x800B8CB0
    // 0x800BA38C: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_6;
    // 0x800BA38C: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    after_6:
    // 0x800BA390: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BA394: lw          $t2, 0x5504($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X5504);
    // 0x800BA398: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BA39C: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800BA3A0: lh          $t3, 0x2($t2)
    ctx->r11 = MEM_H(ctx->r10, 0X2);
    // 0x800BA3A4: addiu       $v0, $v0, 0x5514
    ctx->r2 = ADD32(ctx->r2, 0X5514);
    // 0x800BA3A8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BA3AC: andi        $s0, $t3, 0xFFFF
    ctx->r16 = ctx->r11 & 0XFFFF;
    // 0x800BA3B0: sll         $t4, $s0, 3
    ctx->r12 = S32(ctx->r16 << 3);
    // 0x800BA3B4: or          $s0, $t4, $zero
    ctx->r16 = ctx->r12 | 0;
    // 0x800BA3B8: addiu       $s0, $s0, 0x13
    ctx->r16 = ADD32(ctx->r16, 0X13);
    // 0x800BA3BC: and         $a1, $s0, $at
    ctx->r5 = ctx->r16 & ctx->r1;
    // 0x800BA3C0: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x800BA3C4: jal         0x800B7760
    // 0x800BA3C8: sh          $t3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r11;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_7;
    // 0x800BA3C8: sh          $t3, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r11;
    after_7:
    // 0x800BA3CC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA3D0: addiu       $v1, $v1, 0x5504
    ctx->r3 = ADD32(ctx->r3, 0X5504);
    // 0x800BA3D4: lui         $a0, 0x7B
    ctx->r4 = S32(0X7B << 16);
    // 0x800BA3D8: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800BA3DC: addiu       $a0, $a0, -0x1750
    ctx->r4 = ADD32(ctx->r4, -0X1750);
    // 0x800BA3E0: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BA3E4: jal         0x800B8CB0
    // 0x800BA3E8: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_8;
    // 0x800BA3E8: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_8:
    // 0x800BA3EC: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA3F0: lui         $a1, 0x7B
    ctx->r5 = S32(0X7B << 16);
    // 0x800BA3F4: addiu       $a1, $a1, -0x1750
    ctx->r5 = ADD32(ctx->r5, -0X1750);
    // 0x800BA3F8: jal         0x800CA908
    // 0x800BA3FC: lw          $a0, 0x5504($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5504);
    alSeqFileNew(rdram, ctx);
        goto after_9;
    // 0x800BA3FC: lw          $a0, 0x5504($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5504);
    after_9:
    // 0x800BA400: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BA404: addiu       $v0, $v0, 0x5508
    ctx->r2 = ADD32(ctx->r2, 0X5508);
    // 0x800BA408: addiu       $a1, $sp, 0x48
    ctx->r5 = ADD32(ctx->r29, 0X48);
    // 0x800BA40C: lui         $a0, 0x41
    ctx->r4 = S32(0X41 << 16);
    // 0x800BA410: sw          $a1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r5;
    // 0x800BA414: addiu       $a0, $a0, -0x4AD0
    ctx->r4 = ADD32(ctx->r4, -0X4AD0);
    // 0x800BA418: jal         0x800B8CB0
    // 0x800BA41C: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_10;
    // 0x800BA41C: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    after_10:
    // 0x800BA420: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800BA424: lw          $t7, 0x5508($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X5508);
    // 0x800BA428: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800BA42C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BA430: lh          $v0, 0x2($t7)
    ctx->r2 = MEM_H(ctx->r15, 0X2);
    // 0x800BA434: sll         $s0, $v0, 3
    ctx->r16 = S32(ctx->r2 << 3);
    // 0x800BA438: addiu       $s0, $s0, 0x13
    ctx->r16 = ADD32(ctx->r16, 0X13);
    // 0x800BA43C: sll         $a1, $v0, 2
    ctx->r5 = S32(ctx->r2 << 2);
    // 0x800BA440: and         $t9, $s0, $at
    ctx->r25 = ctx->r16 & ctx->r1;
    // 0x800BA444: subu        $a1, $a1, $v0
    ctx->r5 = SUB32(ctx->r5, ctx->r2);
    // 0x800BA448: or          $s0, $t9, $zero
    ctx->r16 = ctx->r25 | 0;
    // 0x800BA44C: jal         0x800B7760
    // 0x800BA450: sll         $a1, $a1, 2
    ctx->r5 = S32(ctx->r5 << 2);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_11;
    // 0x800BA450: sll         $a1, $a1, 2
    ctx->r5 = S32(ctx->r5 << 2);
    after_11:
    // 0x800BA454: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA458: sw          $v0, 0x5518($at)
    MEM_W(0X5518, ctx->r1) = ctx->r2;
    // 0x800BA45C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BA460: jal         0x800B7760
    // 0x800BA464: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_12;
    // 0x800BA464: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_12:
    // 0x800BA468: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA46C: addiu       $v1, $v1, 0x5508
    ctx->r3 = ADD32(ctx->r3, 0X5508);
    // 0x800BA470: lui         $a0, 0x41
    ctx->r4 = S32(0X41 << 16);
    // 0x800BA474: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800BA478: addiu       $a0, $a0, -0x4AD0
    ctx->r4 = ADD32(ctx->r4, -0X4AD0);
    // 0x800BA47C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BA480: jal         0x800B8CB0
    // 0x800BA484: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_13;
    // 0x800BA484: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_13:
    // 0x800BA488: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA48C: lui         $a1, 0x41
    ctx->r5 = S32(0X41 << 16);
    // 0x800BA490: addiu       $a1, $a1, -0x4AD0
    ctx->r5 = ADD32(ctx->r5, -0X4AD0);
    // 0x800BA494: jal         0x800CA908
    // 0x800BA498: lw          $a0, 0x5508($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5508);
    alSeqFileNew(rdram, ctx);
        goto after_14;
    // 0x800BA498: lw          $a0, 0x5508($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5508);
    after_14:
    // 0x800BA49C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BA4A0: addiu       $v0, $v0, 0x550C
    ctx->r2 = ADD32(ctx->r2, 0X550C);
    // 0x800BA4A4: addiu       $a1, $sp, 0x48
    ctx->r5 = ADD32(ctx->r29, 0X48);
    // 0x800BA4A8: lui         $a0, 0x43
    ctx->r4 = S32(0X43 << 16);
    // 0x800BA4AC: sw          $a1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r5;
    // 0x800BA4B0: addiu       $a0, $a0, -0x73D0
    ctx->r4 = ADD32(ctx->r4, -0X73D0);
    // 0x800BA4B4: jal         0x800B8CB0
    // 0x800BA4B8: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_15;
    // 0x800BA4B8: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    after_15:
    // 0x800BA4BC: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800BA4C0: lw          $t0, 0x550C($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X550C);
    // 0x800BA4C4: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800BA4C8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BA4CC: lh          $s0, 0x2($t0)
    ctx->r16 = MEM_H(ctx->r8, 0X2);
    // 0x800BA4D0: sll         $t1, $s0, 3
    ctx->r9 = S32(ctx->r16 << 3);
    // 0x800BA4D4: or          $s0, $t1, $zero
    ctx->r16 = ctx->r9 | 0;
    // 0x800BA4D8: addiu       $s0, $s0, 0x13
    ctx->r16 = ADD32(ctx->r16, 0X13);
    // 0x800BA4DC: and         $a1, $s0, $at
    ctx->r5 = ctx->r16 & ctx->r1;
    // 0x800BA4E0: jal         0x800B7760
    // 0x800BA4E4: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_16;
    // 0x800BA4E4: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    after_16:
    // 0x800BA4E8: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA4EC: addiu       $v1, $v1, 0x550C
    ctx->r3 = ADD32(ctx->r3, 0X550C);
    // 0x800BA4F0: lui         $a0, 0x43
    ctx->r4 = S32(0X43 << 16);
    // 0x800BA4F4: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800BA4F8: addiu       $a0, $a0, -0x73D0
    ctx->r4 = ADD32(ctx->r4, -0X73D0);
    // 0x800BA4FC: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BA500: jal         0x800B8CB0
    // 0x800BA504: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_17;
    // 0x800BA504: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    after_17:
    // 0x800BA508: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800BA50C: lui         $a1, 0x43
    ctx->r5 = S32(0X43 << 16);
    // 0x800BA510: addiu       $a1, $a1, -0x73D0
    ctx->r5 = ADD32(ctx->r5, -0X73D0);
    // 0x800BA514: jal         0x800CA908
    // 0x800BA518: lw          $a0, 0x550C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X550C);
    alSeqFileNew(rdram, ctx);
        goto after_18;
    // 0x800BA518: lw          $a0, 0x550C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X550C);
    after_18:
    // 0x800BA51C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800BA520: jal         0x800B7760
    // 0x800BA524: addiu       $a1, $zero, 0x100
    ctx->r5 = ADD32(0, 0X100);
    AudioHeap_AllocZeroed(rdram, ctx);
        goto after_19;
    // 0x800BA524: addiu       $a1, $zero, 0x100
    ctx->r5 = ADD32(0, 0X100);
    after_19:
    // 0x800BA528: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA52C: addiu       $v1, $v1, 0x5510
    ctx->r3 = ADD32(ctx->r3, 0X5510);
    // 0x800BA530: lui         $a0, 0x7C
    ctx->r4 = S32(0X7C << 16);
    // 0x800BA534: sw          $v0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r2;
    // 0x800BA538: addiu       $a0, $a0, 0x4B70
    ctx->r4 = ADD32(ctx->r4, 0X4B70);
    // 0x800BA53C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BA540: jal         0x800B8CB0
    // 0x800BA544: addiu       $a2, $zero, 0x100
    ctx->r6 = ADD32(0, 0X100);
    Audio_DmaCopyImmediate(rdram, ctx);
        goto after_20;
    // 0x800BA544: addiu       $a2, $zero, 0x100
    ctx->r6 = ADD32(0, 0X100);
    after_20:
    // 0x800BA548: jal         0x800BF1F4
    // 0x800BA54C: nop

    AudioSeq_InitSequencePlayers(rdram, ctx);
        goto after_21;
    // 0x800BA54C: nop

    after_21:
    // 0x800BA550: lui         $t3, 0x7655
    ctx->r11 = S32(0X7655 << 16);
    // 0x800BA554: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x800BA558: addiu       $t4, $t4, -0x1D00
    ctx->r12 = ADD32(ctx->r12, -0X1D00);
    // 0x800BA55C: ori         $t3, $t3, 0x7364
    ctx->r11 = ctx->r11 | 0X7364;
    // 0x800BA560: sw          $t3, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r11;
    // 0x800BA564: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800BA568: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800BA56C: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800BA570: jr          $ra
    // 0x800BA574: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    return;
    // 0x800BA574: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x800BA578: nop

    // 0x800BA57C: nop

;}
RECOMP_FUNC void Audio_InitNoteSub(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BA580: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x800BA584: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x800BA588: lw          $t9, 0xB0($a0)
    ctx->r25 = MEM_W(ctx->r4, 0XB0);
    // 0x800BA58C: or          $t7, $a2, $zero
    ctx->r15 = ctx->r6 | 0;
    // 0x800BA590: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x800BA594: andi        $t8, $t7, 0x7F
    ctx->r24 = ctx->r15 & 0X7F;
    // 0x800BA598: sll         $t1, $t9, 6
    ctx->r9 = S32(ctx->r25 << 6);
    // 0x800BA59C: bgez        $t1, L_800BA638
    if (SIGNED(ctx->r9) >= 0) {
        // 0x800BA5A0: or          $a2, $t8, $zero
        ctx->r6 = ctx->r24 | 0;
            goto L_800BA638;
    }
    // 0x800BA5A0: or          $a2, $t8, $zero
    ctx->r6 = ctx->r24 | 0;
    // 0x800BA5A4: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800BA5A8: lb          $t2, 0x554E($t2)
    ctx->r10 = MEM_B(ctx->r10, 0X554E);
    // 0x800BA5AC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BA5B0: sra         $a1, $t8, 3
    ctx->r5 = S32(SIGNED(ctx->r24) >> 3);
    // 0x800BA5B4: bne         $t2, $at, L_800BA638
    if (ctx->r10 != ctx->r1) {
        // 0x800BA5B8: addiu       $v0, $a0, 0xB0
        ctx->r2 = ADD32(ctx->r4, 0XB0);
            goto L_800BA638;
    }
    // 0x800BA5B8: addiu       $v0, $a0, 0xB0
    ctx->r2 = ADD32(ctx->r4, 0XB0);
    // 0x800BA5BC: slti        $at, $a1, 0x10
    ctx->r1 = SIGNED(ctx->r5) < 0X10 ? 1 : 0;
    // 0x800BA5C0: bne         $at, $zero, L_800BA5CC
    if (ctx->r1 != 0) {
        // 0x800BA5C4: or          $v1, $t8, $zero
        ctx->r3 = ctx->r24 | 0;
            goto L_800BA5CC;
    }
    // 0x800BA5C4: or          $v1, $t8, $zero
    ctx->r3 = ctx->r24 | 0;
    // 0x800BA5C8: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
L_800BA5CC:
    // 0x800BA5CC: sll         $a3, $a1, 1
    ctx->r7 = S32(ctx->r5 << 1);
    // 0x800BA5D0: lui         $t3, 0x800F
    ctx->r11 = S32(0X800F << 16);
    // 0x800BA5D4: addu        $t3, $t3, $a3
    ctx->r11 = ADD32(ctx->r11, ctx->r7);
    // 0x800BA5D8: lhu         $t3, -0x23B4($t3)
    ctx->r11 = MEM_HU(ctx->r11, -0X23B4);
    // 0x800BA5DC: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
    // 0x800BA5E0: negu        $t4, $a3
    ctx->r12 = SUB32(0, ctx->r7);
    // 0x800BA5E4: lui         $t5, 0x800F
    ctx->r13 = S32(0X800F << 16);
    // 0x800BA5E8: addu        $t5, $t5, $t4
    ctx->r13 = ADD32(ctx->r13, ctx->r12);
    // 0x800BA5EC: sb          $t3, 0x4($v0)
    MEM_B(0X4, ctx->r2) = ctx->r11;
    // 0x800BA5F0: lhu         $t5, -0x2396($t5)
    ctx->r13 = MEM_HU(ctx->r13, -0X2396);
    // 0x800BA5F4: andi        $t8, $t6, 0xFFF7
    ctx->r24 = ctx->r14 & 0XFFF7;
    // 0x800BA5F8: andi        $t1, $t8, 0xFB
    ctx->r9 = ctx->r24 & 0XFB;
    // 0x800BA5FC: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
    // 0x800BA600: sb          $t1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r9;
    // 0x800BA604: ori         $t2, $t1, 0x1
    ctx->r10 = ctx->r9 | 0X1;
    // 0x800BA608: sll         $t3, $a2, 2
    ctx->r11 = S32(ctx->r6 << 2);
    // 0x800BA60C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA610: sb          $t2, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r10;
    // 0x800BA614: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x800BA618: sb          $t5, 0x3($v0)
    MEM_B(0X3, ctx->r2) = ctx->r13;
    // 0x800BA61C: lwc1        $f0, -0x2310($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X2310);
    // 0x800BA620: sll         $t4, $v1, 2
    ctx->r12 = S32(ctx->r3 << 2);
    // 0x800BA624: negu        $t5, $t4
    ctx->r13 = SUB32(0, ctx->r12);
    // 0x800BA628: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA62C: addu        $at, $at, $t5
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x800BA630: b           L_800BA724
    // 0x800BA634: lwc1        $f2, -0x2114($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X2114);
        goto L_800BA724;
    // 0x800BA634: lwc1        $f2, -0x2114($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X2114);
L_800BA638:
    // 0x800BA638: addiu       $v0, $a0, 0xB0
    ctx->r2 = ADD32(ctx->r4, 0XB0);
    // 0x800BA63C: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x800BA640: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BA644: lb          $v1, 0x554E($v1)
    ctx->r3 = MEM_B(ctx->r3, 0X554E);
    // 0x800BA648: sll         $t8, $t6, 6
    ctx->r24 = S32(ctx->r14 << 6);
    // 0x800BA64C: bgez        $t8, L_800BA6EC
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800BA650: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800BA6EC;
    }
    // 0x800BA650: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800BA654: bne         $v1, $zero, L_800BA6EC
    if (ctx->r3 != 0) {
        // 0x800BA658: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_800BA6EC;
    }
    // 0x800BA658: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800BA65C: lbu         $t9, 0x0($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X0);
    // 0x800BA660: sll         $t1, $a2, 2
    ctx->r9 = S32(ctx->r6 << 2);
    // 0x800BA664: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA668: andi        $t0, $t9, 0xFFFE
    ctx->r8 = ctx->r25 & 0XFFFE;
    // 0x800BA66C: sb          $zero, 0x4($v0)
    MEM_B(0X4, ctx->r2) = 0;
    // 0x800BA670: sb          $zero, 0x3($v0)
    MEM_B(0X3, ctx->r2) = 0;
    // 0x800BA674: sb          $t0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r8;
    // 0x800BA678: addu        $at, $at, $t1
    ctx->r1 = ADD32(ctx->r1, ctx->r9);
    // 0x800BA67C: lwc1        $f0, -0x2110($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X2110);
    // 0x800BA680: sll         $t2, $a2, 2
    ctx->r10 = S32(ctx->r6 << 2);
    // 0x800BA684: negu        $t3, $t2
    ctx->r11 = SUB32(0, ctx->r10);
    // 0x800BA688: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA68C: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x800BA690: lwc1        $f2, -0x1F14($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X1F14);
    // 0x800BA694: slti        $at, $a2, 0x20
    ctx->r1 = SIGNED(ctx->r6) < 0X20 ? 1 : 0;
    // 0x800BA698: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800BA69C: beq         $at, $zero, L_800BA6AC
    if (ctx->r1 == 0) {
        // 0x800BA6A0: or          $v1, $a2, $zero
        ctx->r3 = ctx->r6 | 0;
            goto L_800BA6AC;
    }
    // 0x800BA6A0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800BA6A4: b           L_800BA6BC
    // 0x800BA6A8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_800BA6BC;
    // 0x800BA6A8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_800BA6AC:
    // 0x800BA6AC: slti        $at, $v1, 0x61
    ctx->r1 = SIGNED(ctx->r3) < 0X61 ? 1 : 0;
    // 0x800BA6B0: bnel        $at, $zero, L_800BA6C0
    if (ctx->r1 != 0) {
        // 0x800BA6B4: lbu         $t7, 0x0($v0)
        ctx->r15 = MEM_BU(ctx->r2, 0X0);
            goto L_800BA6C0;
    }
    goto skip_0;
    // 0x800BA6B4: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    skip_0:
    // 0x800BA6B8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_800BA6BC:
    // 0x800BA6BC: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
L_800BA6C0:
    // 0x800BA6C0: sll         $t5, $a1, 3
    ctx->r13 = S32(ctx->r5 << 3);
    // 0x800BA6C4: andi        $t6, $t5, 0x8
    ctx->r14 = ctx->r13 & 0X8;
    // 0x800BA6C8: andi        $t8, $t7, 0xFFF7
    ctx->r24 = ctx->r15 & 0XFFF7;
    // 0x800BA6CC: or          $t3, $t6, $t8
    ctx->r11 = ctx->r14 | ctx->r24;
    // 0x800BA6D0: sll         $t1, $a0, 2
    ctx->r9 = S32(ctx->r4 << 2);
    // 0x800BA6D4: andi        $t2, $t1, 0x4
    ctx->r10 = ctx->r9 & 0X4;
    // 0x800BA6D8: andi        $t4, $t3, 0xFB
    ctx->r12 = ctx->r11 & 0XFB;
    // 0x800BA6DC: sb          $t3, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r11;
    // 0x800BA6E0: or          $t5, $t2, $t4
    ctx->r13 = ctx->r10 | ctx->r12;
    // 0x800BA6E4: b           L_800BA724
    // 0x800BA6E8: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
        goto L_800BA724;
    // 0x800BA6E8: sb          $t5, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r13;
L_800BA6EC:
    // 0x800BA6EC: bne         $v1, $at, L_800BA704
    if (ctx->r3 != ctx->r1) {
        // 0x800BA6F0: sll         $t7, $a2, 2
        ctx->r15 = S32(ctx->r6 << 2);
            goto L_800BA704;
    }
    // 0x800BA6F0: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x800BA6F4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA6F8: lwc1        $f2, -0x43A0($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X43A0);
    // 0x800BA6FC: b           L_800BA724
    // 0x800BA700: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
        goto L_800BA724;
    // 0x800BA700: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_800BA704:
    // 0x800BA704: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA708: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800BA70C: lwc1        $f0, -0x1F10($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X1F10);
    // 0x800BA710: sll         $t6, $a2, 2
    ctx->r14 = S32(ctx->r6 << 2);
    // 0x800BA714: negu        $t8, $t6
    ctx->r24 = SUB32(0, ctx->r14);
    // 0x800BA718: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA71C: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x800BA720: lwc1        $f2, -0x1D14($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X1D14);
L_800BA724:
    // 0x800BA724: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x800BA728: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA72C: c.lt.s      $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    c1cs = ctx->f12.fl < ctx->f14.fl;
    // 0x800BA730: nop

    // 0x800BA734: bc1f        L_800BA740
    if (!c1cs) {
        // 0x800BA738: nop
    
            goto L_800BA740;
    }
    // 0x800BA738: nop

    // 0x800BA73C: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
L_800BA740:
    // 0x800BA740: lwc1        $f14, -0x439C($at)
    ctx->f14.u32l = MEM_W(ctx->r1, -0X439C);
    // 0x800BA744: c.lt.s      $f14, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f14.fl < ctx->f12.fl;
    // 0x800BA748: nop

    // 0x800BA74C: bc1f        L_800BA758
    if (!c1cs) {
        // 0x800BA750: nop
    
            goto L_800BA758;
    }
    // 0x800BA750: nop

    // 0x800BA754: mov.s       $f12, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    ctx->f12.fl = ctx->f14.fl;
L_800BA758:
    // 0x800BA758: mul.s       $f4, $f12, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f12.fl, ctx->f0.fl);
    // 0x800BA75C: lbu         $t8, 0x5($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X5);
    // 0x800BA760: mul.s       $f8, $f12, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // 0x800BA764: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800BA768: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800BA76C: mfc1        $t0, $f6
    ctx->r8 = (int32_t)ctx->f6.u32l;
    // 0x800BA770: mfc1        $t4, $f10
    ctx->r12 = (int32_t)ctx->f10.u32l;
    // 0x800BA774: andi        $t1, $t0, 0xFFFF
    ctx->r9 = ctx->r8 & 0XFFFF;
    // 0x800BA778: sra         $t3, $t1, 5
    ctx->r11 = S32(SIGNED(ctx->r9) >> 5);
    // 0x800BA77C: andi        $t5, $t4, 0xFFFF
    ctx->r13 = ctx->r12 & 0XFFFF;
    // 0x800BA780: sra         $t7, $t5, 5
    ctx->r15 = S32(SIGNED(ctx->r13) >> 5);
    // 0x800BA784: sh          $t3, 0x6($v0)
    MEM_H(0X6, ctx->r2) = ctx->r11;
    // 0x800BA788: sh          $t7, 0x8($v0)
    MEM_H(0X8, ctx->r2) = ctx->r15;
    // 0x800BA78C: lbu         $t6, 0xF($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0XF);
    // 0x800BA790: beql        $t6, $t8, L_800BA7B0
    if (ctx->r14 == ctx->r24) {
        // 0x800BA794: lw          $t3, 0x0($v0)
        ctx->r11 = MEM_W(ctx->r2, 0X0);
            goto L_800BA7B0;
    }
    goto skip_1;
    // 0x800BA794: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    skip_1:
    // 0x800BA798: lbu         $t0, 0x0($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X0);
    // 0x800BA79C: sb          $t6, 0x5($v0)
    MEM_B(0X5, ctx->r2) = ctx->r14;
    // 0x800BA7A0: ori         $t1, $t0, 0x10
    ctx->r9 = ctx->r8 | 0X10;
    // 0x800BA7A4: jr          $ra
    // 0x800BA7A8: sb          $t1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r9;
    return;
    // 0x800BA7A8: sb          $t1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r9;
    // 0x800BA7AC: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
L_800BA7B0:
    // 0x800BA7B0: sll         $t4, $t3, 1
    ctx->r12 = S32(ctx->r11 << 1);
    // 0x800BA7B4: bgezl       $t4, L_800BA7D0
    if (SIGNED(ctx->r12) >= 0) {
        // 0x800BA7B8: lbu         $t6, 0x0($v0)
        ctx->r14 = MEM_BU(ctx->r2, 0X0);
            goto L_800BA7D0;
    }
    goto skip_2;
    // 0x800BA7B8: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
    skip_2:
    // 0x800BA7BC: lbu         $t7, 0x0($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X0);
    // 0x800BA7C0: ori         $t8, $t7, 0x10
    ctx->r24 = ctx->r15 | 0X10;
    // 0x800BA7C4: jr          $ra
    // 0x800BA7C8: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
    return;
    // 0x800BA7C8: sb          $t8, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r24;
    // 0x800BA7CC: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
L_800BA7D0:
    // 0x800BA7D0: andi        $t9, $t6, 0xFFEF
    ctx->r25 = ctx->r14 & 0XFFEF;
    // 0x800BA7D4: sb          $t9, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r25;
    // 0x800BA7D8: jr          $ra
    // 0x800BA7DC: nop

    return;
    // 0x800BA7DC: nop

;}
RECOMP_FUNC void Audio_NoteSetResamplingRate(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BA7E0: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x800BA7E4: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800BA7E8: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800BA7EC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BA7F0: c.lt.s      $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f12.fl < ctx->f0.fl;
    // 0x800BA7F4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA7F8: addiu       $v0, $a0, 0xB0
    ctx->r2 = ADD32(ctx->r4, 0XB0);
    // 0x800BA7FC: bc1fl       L_800BA80C
    if (!c1cs) {
        // 0x800BA800: c.lt.s      $f12, $f4
        CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
            goto L_800BA80C;
    }
    goto skip_0;
    // 0x800BA800: c.lt.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
    skip_0:
    // 0x800BA804: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x800BA808: c.lt.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
L_800BA80C:
    // 0x800BA80C: nop

    // 0x800BA810: bc1fl       L_800BA84C
    if (!c1cs) {
        // 0x800BA814: lbu         $t9, 0x1($v0)
        ctx->r25 = MEM_BU(ctx->r2, 0X1);
            goto L_800BA84C;
    }
    goto skip_1;
    // 0x800BA814: lbu         $t9, 0x1($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X1);
    skip_1:
    // 0x800BA818: lwc1        $f2, -0x4398($at)
    ctx->f2.u32l = MEM_W(ctx->r1, -0X4398);
    // 0x800BA81C: addiu       $v0, $a0, 0xB0
    ctx->r2 = ADD32(ctx->r4, 0XB0);
    // 0x800BA820: lbu         $t6, 0x1($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X1);
    // 0x800BA824: c.lt.s      $f2, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f2.fl < ctx->f12.fl;
    // 0x800BA828: andi        $t7, $t6, 0xFFFE
    ctx->r15 = ctx->r14 & 0XFFFE;
    // 0x800BA82C: sb          $t7, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r15;
    // 0x800BA830: bc1f        L_800BA840
    if (!c1cs) {
        // 0x800BA834: nop
    
            goto L_800BA840;
    }
    // 0x800BA834: nop

    // 0x800BA838: b           L_800BA88C
    // 0x800BA83C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
        goto L_800BA88C;
    // 0x800BA83C: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
L_800BA840:
    // 0x800BA840: b           L_800BA88C
    // 0x800BA844: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
        goto L_800BA88C;
    // 0x800BA844: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    // 0x800BA848: lbu         $t9, 0x1($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X1);
L_800BA84C:
    // 0x800BA84C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA850: ori         $t0, $t9, 0x1
    ctx->r8 = ctx->r25 | 0X1;
    // 0x800BA854: sb          $t0, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r8;
    // 0x800BA858: lwc1        $f6, -0x4394($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X4394);
    // 0x800BA85C: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x800BA860: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x800BA864: nop

    // 0x800BA868: bc1fl       L_800BA880
    if (!c1cs) {
        // 0x800BA86C: mtc1        $at, $f8
        ctx->f8.u32l = ctx->r1;
            goto L_800BA880;
    }
    goto skip_2;
    // 0x800BA86C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    skip_2:
    // 0x800BA870: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BA874: b           L_800BA88C
    // 0x800BA878: lwc1        $f0, -0x4390($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4390);
        goto L_800BA88C;
    // 0x800BA878: lwc1        $f0, -0x4390($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4390);
    // 0x800BA87C: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
L_800BA880:
    // 0x800BA880: nop

    // 0x800BA884: mul.s       $f0, $f12, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x800BA888: nop

L_800BA88C:
    // 0x800BA88C: lui         $at, 0x4700
    ctx->r1 = S32(0X4700 << 16);
    // 0x800BA890: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800BA894: nop

    // 0x800BA898: mul.s       $f16, $f0, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x800BA89C: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x800BA8A0: mfc1        $t2, $f18
    ctx->r10 = (int32_t)ctx->f18.u32l;
    // 0x800BA8A4: jr          $ra
    // 0x800BA8A8: sh          $t2, 0xBA($a0)
    MEM_H(0XBA, ctx->r4) = ctx->r10;
    return;
    // 0x800BA8A8: sh          $t2, 0xBA($a0)
    MEM_H(0XBA, ctx->r4) = ctx->r10;
;}
RECOMP_FUNC void Audio_GetInstrumentTunedSample(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BA8AC: lbu         $t6, 0x1($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X1);
    // 0x800BA8B0: slt         $at, $a1, $t6
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x800BA8B4: beql        $at, $zero, L_800BA8C8
    if (ctx->r1 == 0) {
        // 0x800BA8B8: lbu         $t7, 0x2($a0)
        ctx->r15 = MEM_BU(ctx->r4, 0X2);
            goto L_800BA8C8;
    }
    goto skip_0;
    // 0x800BA8B8: lbu         $t7, 0x2($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X2);
    skip_0:
    // 0x800BA8BC: jr          $ra
    // 0x800BA8C0: addiu       $v0, $a0, 0x8
    ctx->r2 = ADD32(ctx->r4, 0X8);
    return;
    // 0x800BA8C0: addiu       $v0, $a0, 0x8
    ctx->r2 = ADD32(ctx->r4, 0X8);
    // 0x800BA8C4: lbu         $t7, 0x2($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X2);
L_800BA8C8:
    // 0x800BA8C8: addiu       $v1, $a0, 0x18
    ctx->r3 = ADD32(ctx->r4, 0X18);
    // 0x800BA8CC: slt         $at, $t7, $a1
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x800BA8D0: bne         $at, $zero, L_800BA8E0
    if (ctx->r1 != 0) {
        // 0x800BA8D4: nop
    
            goto L_800BA8E0;
    }
    // 0x800BA8D4: nop

    // 0x800BA8D8: jr          $ra
    // 0x800BA8DC: addiu       $v0, $a0, 0x10
    ctx->r2 = ADD32(ctx->r4, 0X10);
    return;
    // 0x800BA8DC: addiu       $v0, $a0, 0x10
    ctx->r2 = ADD32(ctx->r4, 0X10);
L_800BA8E0:
    // 0x800BA8E0: jr          $ra
    // 0x800BA8E4: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800BA8E4: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void Audio_GetInstrument(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BA8E8: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BA8EC: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800BA8F0: lbu         $t6, -0x1488($t6)
    ctx->r14 = MEM_BU(ctx->r14, -0X1488);
    // 0x800BA8F4: lui         $at, 0x1000
    ctx->r1 = S32(0X1000 << 16);
    // 0x800BA8F8: lui         $t9, 0x8004
    ctx->r25 = S32(0X8004 << 16);
    // 0x800BA8FC: slti        $t7, $t6, 0x2
    ctx->r15 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
    // 0x800BA900: beq         $t7, $zero, L_800BA91C
    if (ctx->r15 == 0) {
        // 0x800BA904: sll         $t0, $a0, 2
        ctx->r8 = S32(ctx->r4 << 2);
            goto L_800BA91C;
    }
    // 0x800BA904: sll         $t0, $a0, 2
    ctx->r8 = S32(ctx->r4 << 2);
    // 0x800BA908: addu        $t8, $a0, $at
    ctx->r24 = ADD32(ctx->r4, ctx->r1);
    // 0x800BA90C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA910: sw          $t8, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r24;
    // 0x800BA914: jr          $ra
    // 0x800BA918: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800BA918: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BA91C:
    // 0x800BA91C: lw          $t9, 0x5518($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X5518);
    // 0x800BA920: subu        $t0, $t0, $a0
    ctx->r8 = SUB32(ctx->r8, ctx->r4);
    // 0x800BA924: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x800BA928: addu        $v0, $t9, $t0
    ctx->r2 = ADD32(ctx->r25, ctx->r8);
    // 0x800BA92C: lbu         $t1, 0x1($v0)
    ctx->r9 = MEM_BU(ctx->r2, 0X1);
    // 0x800BA930: sll         $t2, $a0, 8
    ctx->r10 = S32(ctx->r4 << 8);
    // 0x800BA934: addu        $t3, $t2, $a1
    ctx->r11 = ADD32(ctx->r10, ctx->r5);
    // 0x800BA938: slt         $at, $a1, $t1
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x800BA93C: bne         $at, $zero, L_800BA958
    if (ctx->r1 != 0) {
        // 0x800BA940: lui         $at, 0x300
        ctx->r1 = S32(0X300 << 16);
            goto L_800BA958;
    }
    // 0x800BA940: lui         $at, 0x300
    ctx->r1 = S32(0X300 << 16);
    // 0x800BA944: addu        $t4, $t3, $at
    ctx->r12 = ADD32(ctx->r11, ctx->r1);
    // 0x800BA948: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA94C: sw          $t4, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r12;
    // 0x800BA950: jr          $ra
    // 0x800BA954: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800BA954: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BA958:
    // 0x800BA958: lw          $t5, 0x4($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X4);
    // 0x800BA95C: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x800BA960: sll         $t8, $a0, 8
    ctx->r24 = S32(ctx->r4 << 8);
    // 0x800BA964: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x800BA968: lw          $v1, 0x0($t7)
    ctx->r3 = MEM_W(ctx->r15, 0X0);
    // 0x800BA96C: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800BA970: addu        $t9, $t8, $a1
    ctx->r25 = ADD32(ctx->r24, ctx->r5);
    // 0x800BA974: bne         $v1, $zero, L_800BA994
    if (ctx->r3 != 0) {
        // 0x800BA978: addiu       $a2, $a2, -0x1860
        ctx->r6 = ADD32(ctx->r6, -0X1860);
            goto L_800BA994;
    }
    // 0x800BA978: addiu       $a2, $a2, -0x1860
    ctx->r6 = ADD32(ctx->r6, -0X1860);
    // 0x800BA97C: lui         $at, 0x100
    ctx->r1 = S32(0X100 << 16);
    // 0x800BA980: addu        $t0, $t9, $at
    ctx->r8 = ADD32(ctx->r25, ctx->r1);
    // 0x800BA984: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA988: sw          $t0, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r8;
    // 0x800BA98C: jr          $ra
    // 0x800BA990: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800BA990: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_800BA994:
    // 0x800BA994: lw          $v0, 0x4($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X4);
    // 0x800BA998: sltu        $at, $v1, $v0
    ctx->r1 = ctx->r3 < ctx->r2 ? 1 : 0;
    // 0x800BA99C: bnel        $at, $zero, L_800BA9BC
    if (ctx->r1 != 0) {
        // 0x800BA9A0: lw          $v0, 0x198($a2)
        ctx->r2 = MEM_W(ctx->r6, 0X198);
            goto L_800BA9BC;
    }
    goto skip_0;
    // 0x800BA9A0: lw          $v0, 0x198($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X198);
    skip_0:
    // 0x800BA9A4: lw          $t1, 0xC($a2)
    ctx->r9 = MEM_W(ctx->r6, 0XC);
    // 0x800BA9A8: addu        $t2, $v0, $t1
    ctx->r10 = ADD32(ctx->r2, ctx->r9);
    // 0x800BA9AC: sltu        $at, $t2, $v1
    ctx->r1 = ctx->r10 < ctx->r3 ? 1 : 0;
    // 0x800BA9B0: beq         $at, $zero, L_800BA9E4
    if (ctx->r1 == 0) {
        // 0x800BA9B4: nop
    
            goto L_800BA9E4;
    }
    // 0x800BA9B4: nop

    // 0x800BA9B8: lw          $v0, 0x198($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X198);
L_800BA9BC:
    // 0x800BA9BC: sll         $t5, $a0, 8
    ctx->r13 = S32(ctx->r4 << 8);
    // 0x800BA9C0: addu        $t6, $t5, $a1
    ctx->r14 = ADD32(ctx->r13, ctx->r5);
    // 0x800BA9C4: sltu        $at, $v1, $v0
    ctx->r1 = ctx->r3 < ctx->r2 ? 1 : 0;
    // 0x800BA9C8: bnel        $at, $zero, L_800BA9F0
    if (ctx->r1 != 0) {
        // 0x800BA9CC: lui         $at, 0x200
        ctx->r1 = S32(0X200 << 16);
            goto L_800BA9F0;
    }
    goto skip_1;
    // 0x800BA9CC: lui         $at, 0x200
    ctx->r1 = S32(0X200 << 16);
    skip_1:
    // 0x800BA9D0: lw          $t3, 0x1A0($a2)
    ctx->r11 = MEM_W(ctx->r6, 0X1A0);
    // 0x800BA9D4: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x800BA9D8: sltu        $at, $t4, $v1
    ctx->r1 = ctx->r12 < ctx->r3 ? 1 : 0;
    // 0x800BA9DC: bnel        $at, $zero, L_800BA9F0
    if (ctx->r1 != 0) {
        // 0x800BA9E0: lui         $at, 0x200
        ctx->r1 = S32(0X200 << 16);
            goto L_800BA9F0;
    }
    goto skip_2;
    // 0x800BA9E0: lui         $at, 0x200
    ctx->r1 = S32(0X200 << 16);
    skip_2:
L_800BA9E4:
    // 0x800BA9E4: jr          $ra
    // 0x800BA9E8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800BA9E8: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800BA9EC: lui         $at, 0x200
    ctx->r1 = S32(0X200 << 16);
L_800BA9F0:
    // 0x800BA9F0: addu        $t7, $t6, $at
    ctx->r15 = ADD32(ctx->r14, ctx->r1);
    // 0x800BA9F4: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BA9F8: sw          $t7, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r15;
    // 0x800BA9FC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800BAA00: jr          $ra
    // 0x800BAA04: nop

    return;
    // 0x800BAA04: nop

;}
RECOMP_FUNC void Audio_GetDrum(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BAA08: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BAA0C: lw          $t6, 0x5518($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5518);
    // 0x800BAA10: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x800BAA14: subu        $t7, $t7, $a0
    ctx->r15 = SUB32(ctx->r15, ctx->r4);
    // 0x800BAA18: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800BAA1C: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800BAA20: lbu         $t8, 0x2($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X2);
    // 0x800BAA24: sll         $t9, $a0, 8
    ctx->r25 = S32(ctx->r4 << 8);
    // 0x800BAA28: addu        $t0, $t9, $a1
    ctx->r8 = ADD32(ctx->r25, ctx->r5);
    // 0x800BAA2C: slt         $at, $a1, $t8
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x800BAA30: bne         $at, $zero, L_800BAA4C
    if (ctx->r1 != 0) {
        // 0x800BAA34: lui         $at, 0x400
        ctx->r1 = S32(0X400 << 16);
            goto L_800BAA4C;
    }
    // 0x800BAA34: lui         $at, 0x400
    ctx->r1 = S32(0X400 << 16);
    // 0x800BAA38: addu        $t1, $t0, $at
    ctx->r9 = ADD32(ctx->r8, ctx->r1);
    // 0x800BAA3C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BAA40: sw          $t1, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r9;
    // 0x800BAA44: jr          $ra
    // 0x800BAA48: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800BAA48: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800BAA4C:
    // 0x800BAA4C: lw          $t2, 0x8($v0)
    ctx->r10 = MEM_W(ctx->r2, 0X8);
    // 0x800BAA50: sll         $t3, $a1, 2
    ctx->r11 = S32(ctx->r5 << 2);
    // 0x800BAA54: sll         $t5, $a0, 8
    ctx->r13 = S32(ctx->r4 << 8);
    // 0x800BAA58: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x800BAA5C: lw          $v1, 0x0($t4)
    ctx->r3 = MEM_W(ctx->r12, 0X0);
    // 0x800BAA60: addu        $t6, $t5, $a1
    ctx->r14 = ADD32(ctx->r13, ctx->r5);
    // 0x800BAA64: lui         $at, 0x500
    ctx->r1 = S32(0X500 << 16);
    // 0x800BAA68: bne         $v1, $zero, L_800BAA7C
    if (ctx->r3 != 0) {
        // 0x800BAA6C: or          $v0, $v1, $zero
        ctx->r2 = ctx->r3 | 0;
            goto L_800BAA7C;
    }
    // 0x800BAA6C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800BAA70: addu        $t7, $t6, $at
    ctx->r15 = ADD32(ctx->r14, ctx->r1);
    // 0x800BAA74: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BAA78: sw          $t7, 0x5630($at)
    MEM_W(0X5630, ctx->r1) = ctx->r15;
L_800BAA7C:
    // 0x800BAA7C: jr          $ra
    // 0x800BAA80: nop

    return;
    // 0x800BAA80: nop

;}
RECOMP_FUNC void Audio_NoteInit(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BAA84: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BAA88: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BAA8C: lw          $v0, 0x44($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X44);
    // 0x800BAA90: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800BAA94: addiu       $a2, $a3, 0x34
    ctx->r6 = ADD32(ctx->r7, 0X34);
    // 0x800BAA98: lbu         $t6, 0x18($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X18);
    // 0x800BAA9C: bnel        $t6, $zero, L_800BAAC8
    if (ctx->r14 != 0) {
        // 0x800BAAA0: lw          $a1, 0x1C($v0)
        ctx->r5 = MEM_W(ctx->r2, 0X1C);
            goto L_800BAAC8;
    }
    goto skip_0;
    // 0x800BAAA0: lw          $a1, 0x1C($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X1C);
    skip_0:
    // 0x800BAAA4: lw          $t7, 0x4C($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X4C);
    // 0x800BAAA8: addiu       $a0, $a0, 0x58
    ctx->r4 = ADD32(ctx->r4, 0X58);
    // 0x800BAAAC: addiu       $a2, $a3, 0x34
    ctx->r6 = ADD32(ctx->r7, 0X34);
    // 0x800BAAB0: lw          $a1, 0x80($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X80);
    // 0x800BAAB4: jal         0x800BC598
    // 0x800BAAB8: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    Audio_AdsrInit(rdram, ctx);
        goto after_0;
    // 0x800BAAB8: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_0:
    // 0x800BAABC: b           L_800BAAD8
    // 0x800BAAC0: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
        goto L_800BAAD8;
    // 0x800BAAC0: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x800BAAC4: lw          $a1, 0x1C($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X1C);
L_800BAAC8:
    // 0x800BAAC8: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    // 0x800BAACC: jal         0x800BC598
    // 0x800BAAD0: addiu       $a0, $a3, 0x58
    ctx->r4 = ADD32(ctx->r7, 0X58);
    Audio_AdsrInit(rdram, ctx);
        goto after_1;
    // 0x800BAAD0: addiu       $a0, $a3, 0x58
    ctx->r4 = ADD32(ctx->r7, 0X58);
    after_1:
    // 0x800BAAD4: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
L_800BAAD8:
    // 0x800BAAD8: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800BAADC: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800BAAE0: sb          $t8, 0x59($a3)
    MEM_B(0X59, ctx->r7) = ctx->r24;
    // 0x800BAAE4: addiu       $t9, $t9, -0x2FE0
    ctx->r25 = ADD32(ctx->r25, -0X2FE0);
    // 0x800BAAE8: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x800BAAEC: sw          $at, 0xB0($a3)
    MEM_W(0XB0, ctx->r7) = ctx->r1;
    // 0x800BAAF0: lw          $t1, 0x4($t9)
    ctx->r9 = MEM_W(ctx->r25, 0X4);
    // 0x800BAAF4: sw          $t1, 0xB4($a3)
    MEM_W(0XB4, ctx->r7) = ctx->r9;
    // 0x800BAAF8: lw          $at, 0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X8);
    // 0x800BAAFC: sw          $at, 0xB8($a3)
    MEM_W(0XB8, ctx->r7) = ctx->r1;
    // 0x800BAB00: lw          $t1, 0xC($t9)
    ctx->r9 = MEM_W(ctx->r25, 0XC);
    // 0x800BAB04: sw          $t1, 0xBC($a3)
    MEM_W(0XBC, ctx->r7) = ctx->r9;
    // 0x800BAB08: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BAB0C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BAB10: jr          $ra
    // 0x800BAB14: nop

    return;
    // 0x800BAB14: nop

;}
RECOMP_FUNC void Audio_NoteDisable(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BAB18: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BAB1C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BAB20: lw          $t6, 0xB0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0XB0);
    // 0x800BAB24: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800BAB28: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x800BAB2C: sll         $t7, $t6, 1
    ctx->r15 = S32(ctx->r14 << 1);
    // 0x800BAB30: srl         $t8, $t7, 31
    ctx->r24 = S32(U32(ctx->r15) >> 31);
    // 0x800BAB34: bne         $t8, $at, L_800BAB4C
    if (ctx->r24 != ctx->r1) {
        // 0x800BAB38: addiu       $a2, $zero, 0x40
        ctx->r6 = ADD32(0, 0X40);
            goto L_800BAB4C;
    }
    // 0x800BAB38: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    // 0x800BAB3C: lbu         $t9, 0xB0($a0)
    ctx->r25 = MEM_BU(ctx->r4, 0XB0);
    // 0x800BAB40: andi        $t0, $t9, 0xFFBF
    ctx->r8 = ctx->r25 & 0XFFBF;
    // 0x800BAB44: b           L_800BAB5C
    // 0x800BAB48: sb          $t0, 0xB0($a0)
    MEM_B(0XB0, ctx->r4) = ctx->r8;
        goto L_800BAB5C;
    // 0x800BAB48: sb          $t0, 0xB0($a0)
    MEM_B(0XB0, ctx->r4) = ctx->r8;
L_800BAB4C:
    // 0x800BAB4C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x800BAB50: jal         0x800BA580
    // 0x800BAB54: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    Audio_InitNoteSub(rdram, ctx);
        goto after_0;
    // 0x800BAB54: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800BAB58: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
L_800BAB5C:
    // 0x800BAB5C: lbu         $t1, 0xB0($a0)
    ctx->r9 = MEM_BU(ctx->r4, 0XB0);
    // 0x800BAB60: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x800BAB64: sb          $zero, 0x30($a0)
    MEM_B(0X30, ctx->r4) = 0;
    // 0x800BAB68: andi        $t2, $t1, 0xFF7F
    ctx->r10 = ctx->r9 & 0XFF7F;
    // 0x800BAB6C: sb          $t2, 0xB0($a0)
    MEM_B(0XB0, ctx->r4) = ctx->r10;
    // 0x800BAB70: lbu         $t3, 0xB0($a0)
    ctx->r11 = MEM_BU(ctx->r4, 0XB0);
    // 0x800BAB74: sw          $v0, 0x44($a0)
    MEM_W(0X44, ctx->r4) = ctx->r2;
    // 0x800BAB78: sw          $v0, 0x40($a0)
    MEM_W(0X40, ctx->r4) = ctx->r2;
    // 0x800BAB7C: andi        $t4, $t3, 0xFFDF
    ctx->r12 = ctx->r11 & 0XFFDF;
    // 0x800BAB80: sb          $t4, 0xB0($a0)
    MEM_B(0XB0, ctx->r4) = ctx->r12;
    // 0x800BAB84: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BAB88: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BAB8C: jr          $ra
    // 0x800BAB90: nop

    return;
    // 0x800BAB90: nop

;}
RECOMP_FUNC void Audio_ProcessNotes(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BAB94: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x800BAB98: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BAB9C: lw          $v1, 0x5548($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5548);
    // 0x800BABA0: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x800BABA4: sw          $s7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r23;
    // 0x800BABA8: sw          $s6, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r22;
    // 0x800BABAC: sw          $s5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r21;
    // 0x800BABB0: sw          $s4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r20;
    // 0x800BABB4: sw          $s3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r19;
    // 0x800BABB8: sw          $s2, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r18;
    // 0x800BABBC: sw          $s1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r17;
    // 0x800BABC0: sw          $s0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r16;
    // 0x800BABC4: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x800BABC8: blez        $v1, L_800BAEF8
    if (SIGNED(ctx->r3) <= 0) {
        // 0x800BABCC: sdc1        $f20, 0x10($sp)
        CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
            goto L_800BAEF8;
    }
    // 0x800BABCC: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x800BABD0: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x800BABD4: addiu       $s7, $zero, 0x1
    ctx->r23 = ADD32(0, 0X1);
    // 0x800BABD8: addiu       $s6, $zero, 0x1
    ctx->r22 = ADD32(0, 0X1);
    // 0x800BABDC: addiu       $s4, $zero, -0x1
    ctx->r20 = ADD32(0, -0X1);
L_800BABE0:
    // 0x800BABE0: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800BABE4: lw          $t6, -0x340($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X340);
    // 0x800BABE8: addu        $s0, $s5, $t6
    ctx->r16 = ADD32(ctx->r21, ctx->r14);
    // 0x800BABEC: lw          $t7, 0x44($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X44);
    // 0x800BABF0: addiu       $s1, $s0, 0x30
    ctx->r17 = ADD32(ctx->r16, 0X30);
    // 0x800BABF4: beql        $s4, $t7, L_800BACD0
    if (ctx->r20 == ctx->r15) {
        // 0x800BABF8: lbu         $v0, 0x0($s1)
        ctx->r2 = MEM_BU(ctx->r17, 0X0);
            goto L_800BACD0;
    }
    goto skip_0;
    // 0x800BABF8: lbu         $v0, 0x0($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X0);
    skip_0:
    // 0x800BABFC: addiu       $s1, $s0, 0x30
    ctx->r17 = ADD32(ctx->r16, 0X30);
    // 0x800BAC00: lw          $a1, 0x14($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X14);
    // 0x800BAC04: lui         $at, 0x7FFF
    ctx->r1 = S32(0X7FFF << 16);
    // 0x800BAC08: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x800BAC0C: sltu        $at, $a1, $at
    ctx->r1 = ctx->r5 < ctx->r1 ? 1 : 0;
    // 0x800BAC10: beq         $at, $zero, L_800BAC24
    if (ctx->r1 == 0) {
        // 0x800BAC14: sll         $v0, $v1, 2
        ctx->r2 = S32(ctx->r3 << 2);
            goto L_800BAC24;
    }
    // 0x800BAC14: sll         $v0, $v1, 2
    ctx->r2 = S32(ctx->r3 << 2);
    // 0x800BAC18: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x800BAC1C: b           L_800BAEE8
    // 0x800BAC20: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
        goto L_800BAEE8;
    // 0x800BAC20: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
L_800BAC24:
    // 0x800BAC24: lw          $t8, 0x0($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X0);
    // 0x800BAC28: srl         $t9, $t8, 31
    ctx->r25 = S32(U32(ctx->r24) >> 31);
    // 0x800BAC2C: bnel        $t9, $zero, L_800BAC48
    if (ctx->r25 != 0) {
        // 0x800BAC30: lw          $a0, 0x4C($a1)
        ctx->r4 = MEM_W(ctx->r5, 0X4C);
            goto L_800BAC48;
    }
    goto skip_1;
    // 0x800BAC30: lw          $a0, 0x4C($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X4C);
    skip_1:
    // 0x800BAC34: lbu         $t0, 0x0($s1)
    ctx->r8 = MEM_BU(ctx->r17, 0X0);
    // 0x800BAC38: slti        $at, $t0, 0x2
    ctx->r1 = SIGNED(ctx->r8) < 0X2 ? 1 : 0;
    // 0x800BAC3C: beq         $at, $zero, L_800BACA0
    if (ctx->r1 == 0) {
        // 0x800BAC40: nop
    
            goto L_800BACA0;
    }
    // 0x800BAC40: nop

    // 0x800BAC44: lw          $a0, 0x4C($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X4C);
L_800BAC48:
    // 0x800BAC48: lw          $v0, 0x44($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X44);
    // 0x800BAC4C: bnel        $v0, $zero, L_800BAC7C
    if (ctx->r2 != 0) {
        // 0x800BAC50: lw          $t1, 0x0($v0)
        ctx->r9 = MEM_W(ctx->r2, 0X0);
            goto L_800BAC7C;
    }
    goto skip_2;
    // 0x800BAC50: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
    skip_2:
    // 0x800BAC54: jal         0x800BCB34
    // 0x800BAC58: nop

    AudioSeq_SequenceChannelDisable(rdram, ctx);
        goto after_0;
    // 0x800BAC58: nop

    after_0:
    // 0x800BAC5C: sb          $s6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r22;
    // 0x800BAC60: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BAC64: lw          $v1, 0x5548($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5548);
    // 0x800BAC68: sll         $v0, $v1, 2
    ctx->r2 = S32(ctx->r3 << 2);
    // 0x800BAC6C: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x800BAC70: b           L_800BAEE8
    // 0x800BAC74: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
        goto L_800BAEE8;
    // 0x800BAC74: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
    // 0x800BAC78: lw          $t1, 0x0($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X0);
L_800BAC7C:
    // 0x800BAC7C: sll         $t3, $t1, 2
    ctx->r11 = S32(ctx->r9 << 2);
    // 0x800BAC80: bgez        $t3, L_800BAC98
    if (SIGNED(ctx->r11) >= 0) {
        // 0x800BAC84: nop
    
            goto L_800BAC98;
    }
    // 0x800BAC84: nop

    // 0x800BAC88: lbu         $t4, 0x3($a0)
    ctx->r12 = MEM_BU(ctx->r4, 0X3);
    // 0x800BAC8C: andi        $t5, $t4, 0xC0
    ctx->r13 = ctx->r12 & 0XC0;
    // 0x800BAC90: bne         $t5, $zero, L_800BACA0
    if (ctx->r13 != 0) {
        // 0x800BAC94: nop
    
            goto L_800BACA0;
    }
    // 0x800BAC94: nop

L_800BAC98:
    // 0x800BAC98: b           L_800BACEC
    // 0x800BAC9C: lbu         $v0, 0x0($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X0);
        goto L_800BACEC;
    // 0x800BAC9C: lbu         $v0, 0x0($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X0);
L_800BACA0:
    // 0x800BACA0: jal         0x800BB128
    // 0x800BACA4: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    Audio_SeqLayerNoteRelease(rdram, ctx);
        goto after_1;
    // 0x800BACA4: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    after_1:
    // 0x800BACA8: jal         0x800BB6DC
    // 0x800BACAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_2;
    // 0x800BACAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_2:
    // 0x800BACB0: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800BACB4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BACB8: jal         0x800BB69C
    // 0x800BACBC: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    Audio_AudioListPushFront(rdram, ctx);
        goto after_3;
    // 0x800BACBC: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    after_3:
    // 0x800BACC0: sb          $s6, 0x0($s1)
    MEM_B(0X0, ctx->r17) = ctx->r22;
    // 0x800BACC4: b           L_800BACEC
    // 0x800BACC8: andi        $v0, $s6, 0xFF
    ctx->r2 = ctx->r22 & 0XFF;
        goto L_800BACEC;
    // 0x800BACC8: andi        $v0, $s6, 0xFF
    ctx->r2 = ctx->r22 & 0XFF;
    // 0x800BACCC: lbu         $v0, 0x0($s1)
    ctx->r2 = MEM_BU(ctx->r17, 0X0);
L_800BACD0:
    // 0x800BACD0: slti        $at, $v0, 0x2
    ctx->r1 = SIGNED(ctx->r2) < 0X2 ? 1 : 0;
    // 0x800BACD4: bne         $at, $zero, L_800BACEC
    if (ctx->r1 != 0) {
        // 0x800BACD8: nop
    
            goto L_800BACEC;
    }
    // 0x800BACD8: nop

    // 0x800BACDC: sll         $v0, $v1, 2
    ctx->r2 = S32(ctx->r3 << 2);
    // 0x800BACE0: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x800BACE4: b           L_800BAEE8
    // 0x800BACE8: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
        goto L_800BAEE8;
    // 0x800BACE8: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
L_800BACEC:
    // 0x800BACEC: beq         $v0, $zero, L_800BAED4
    if (ctx->r2 == 0) {
        // 0x800BACF0: nop
    
            goto L_800BAED4;
    }
    // 0x800BACF0: nop

    // 0x800BACF4: beq         $s7, $v0, L_800BAD0C
    if (ctx->r23 == ctx->r2) {
        // 0x800BACF8: addiu       $s3, $s0, 0xB0
        ctx->r19 = ADD32(ctx->r16, 0XB0);
            goto L_800BAD0C;
    }
    // 0x800BACF8: addiu       $s3, $s0, 0xB0
    ctx->r19 = ADD32(ctx->r16, 0XB0);
    // 0x800BACFC: lw          $t6, 0x0($s3)
    ctx->r14 = MEM_W(ctx->r19, 0X0);
    // 0x800BAD00: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x800BAD04: bgezl       $t8, L_800BADD0
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800BAD08: lbu         $t5, 0x29($s1)
        ctx->r13 = MEM_BU(ctx->r17, 0X29);
            goto L_800BADD0;
    }
    goto skip_3;
    // 0x800BAD08: lbu         $t5, 0x29($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X29);
    skip_3:
L_800BAD0C:
    // 0x800BAD0C: lbu         $t9, 0x29($s1)
    ctx->r25 = MEM_BU(ctx->r17, 0X29);
    // 0x800BAD10: addiu       $s3, $s0, 0xB0
    ctx->r19 = ADD32(ctx->r16, 0XB0);
    // 0x800BAD14: beql        $t9, $zero, L_800BAD30
    if (ctx->r25 == 0) {
        // 0x800BAD18: lw          $t3, 0x18($s1)
        ctx->r11 = MEM_W(ctx->r17, 0X18);
            goto L_800BAD30;
    }
    goto skip_4;
    // 0x800BAD18: lw          $t3, 0x18($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X18);
    skip_4:
    // 0x800BAD1C: lw          $t0, 0x0($s3)
    ctx->r8 = MEM_W(ctx->r19, 0X0);
    // 0x800BAD20: sll         $t2, $t0, 2
    ctx->r10 = S32(ctx->r8 << 2);
    // 0x800BAD24: bgez        $t2, L_800BADFC
    if (SIGNED(ctx->r10) >= 0) {
        // 0x800BAD28: nop
    
            goto L_800BADFC;
    }
    // 0x800BAD28: nop

    // 0x800BAD2C: lw          $t3, 0x18($s1)
    ctx->r11 = MEM_W(ctx->r17, 0X18);
L_800BAD30:
    // 0x800BAD30: beq         $s4, $t3, L_800BADA8
    if (ctx->r20 == ctx->r11) {
        // 0x800BAD34: nop
    
            goto L_800BADA8;
    }
    // 0x800BAD34: nop

    // 0x800BAD38: jal         0x800BAB18
    // 0x800BAD3C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteDisable(rdram, ctx);
        goto after_4;
    // 0x800BAD3C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_4:
    // 0x800BAD40: lw          $a1, 0x18($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X18);
    // 0x800BAD44: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800BAD48: lw          $t4, 0x4C($a1)
    ctx->r12 = MEM_W(ctx->r5, 0X4C);
    // 0x800BAD4C: beq         $t4, $zero, L_800BAD84
    if (ctx->r12 == 0) {
        // 0x800BAD50: nop
    
            goto L_800BAD84;
    }
    // 0x800BAD50: nop

    // 0x800BAD54: jal         0x800BB7A8
    // 0x800BAD58: addiu       $s3, $s0, 0xB0
    ctx->r19 = ADD32(ctx->r16, 0XB0);
    Audio_NoteInitForLayer(rdram, ctx);
        goto after_5;
    // 0x800BAD58: addiu       $s3, $s0, 0xB0
    ctx->r19 = ADD32(ctx->r16, 0XB0);
    after_5:
    // 0x800BAD5C: jal         0x800BC4B0
    // 0x800BAD60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteVibratoInit(rdram, ctx);
        goto after_6;
    // 0x800BAD60: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_6:
    // 0x800BAD64: jal         0x800BB6DC
    // 0x800BAD68: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_7;
    // 0x800BAD68: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_7:
    // 0x800BAD6C: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800BAD70: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800BAD74: jal         0x800BCFAC
    // 0x800BAD78: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_8;
    // 0x800BAD78: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    after_8:
    // 0x800BAD7C: b           L_800BADFC
    // 0x800BAD80: sw          $s4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->r20;
        goto L_800BADFC;
    // 0x800BAD80: sw          $s4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->r20;
L_800BAD84:
    // 0x800BAD84: jal         0x800BAB18
    // 0x800BAD88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteDisable(rdram, ctx);
        goto after_9;
    // 0x800BAD88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_9:
    // 0x800BAD8C: jal         0x800BB6DC
    // 0x800BAD90: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_10;
    // 0x800BAD90: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_10:
    // 0x800BAD94: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800BAD98: jal         0x800BCFAC
    // 0x800BAD9C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_11;
    // 0x800BAD9C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_11:
    // 0x800BADA0: b           L_800BAED4
    // 0x800BADA4: sw          $s4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->r20;
        goto L_800BAED4;
    // 0x800BADA4: sw          $s4, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->r20;
L_800BADA8:
    // 0x800BADA8: jal         0x800BAB18
    // 0x800BADAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteDisable(rdram, ctx);
        goto after_12;
    // 0x800BADAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_12:
    // 0x800BADB0: jal         0x800BB6DC
    // 0x800BADB4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_13;
    // 0x800BADB4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_13:
    // 0x800BADB8: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800BADBC: jal         0x800BCFAC
    // 0x800BADC0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_14;
    // 0x800BADC0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_14:
    // 0x800BADC4: b           L_800BAED4
    // 0x800BADC8: nop

        goto L_800BAED4;
    // 0x800BADC8: nop

    // 0x800BADCC: lbu         $t5, 0x29($s1)
    ctx->r13 = MEM_BU(ctx->r17, 0X29);
L_800BADD0:
    // 0x800BADD0: bne         $t5, $zero, L_800BADFC
    if (ctx->r13 != 0) {
        // 0x800BADD4: nop
    
            goto L_800BADFC;
    }
    // 0x800BADD4: nop

    // 0x800BADD8: jal         0x800BAB18
    // 0x800BADDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteDisable(rdram, ctx);
        goto after_15;
    // 0x800BADDC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_15:
    // 0x800BADE0: jal         0x800BB6DC
    // 0x800BADE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_16;
    // 0x800BADE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_16:
    // 0x800BADE8: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    // 0x800BADEC: jal         0x800BCFAC
    // 0x800BADF0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_17;
    // 0x800BADF0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_17:
    // 0x800BADF4: b           L_800BAED4
    // 0x800BADF8: nop

        goto L_800BAED4;
    // 0x800BADF8: nop

L_800BADFC:
    // 0x800BADFC: jal         0x800BC5B8
    // 0x800BAE00: addiu       $a0, $s1, 0x28
    ctx->r4 = ADD32(ctx->r17, 0X28);
    Audio_AdsrUpdate(rdram, ctx);
        goto after_18;
    // 0x800BAE00: addiu       $a0, $s1, 0x28
    ctx->r4 = ADD32(ctx->r17, 0X28);
    after_18:
    // 0x800BAE04: mov.s       $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    ctx->f22.fl = ctx->f0.fl;
    // 0x800BAE08: jal         0x800BC444
    // 0x800BAE0C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_NoteVibratoUpdate(rdram, ctx);
        goto after_19;
    // 0x800BAE0C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_19:
    // 0x800BAE10: lbu         $t6, 0x0($s1)
    ctx->r14 = MEM_BU(ctx->r17, 0X0);
    // 0x800BAE14: addiu       $v0, $s1, 0x1C
    ctx->r2 = ADD32(ctx->r17, 0X1C);
    // 0x800BAE18: bnel        $s7, $t6, L_800BAE48
    if (ctx->r23 != ctx->r14) {
        // 0x800BAE1C: lw          $a1, 0x14($s1)
        ctx->r5 = MEM_W(ctx->r17, 0X14);
            goto L_800BAE48;
    }
    goto skip_5;
    // 0x800BAE1C: lw          $a1, 0x14($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X14);
    skip_5:
    // 0x800BAE20: lw          $s2, 0x0($s3)
    ctx->r18 = MEM_W(ctx->r19, 0X0);
    // 0x800BAE24: lwc1        $f0, 0x4($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X4);
    // 0x800BAE28: lwc1        $f20, 0x8($v0)
    ctx->f20.u32l = MEM_W(ctx->r2, 0X8);
    // 0x800BAE2C: sll         $t7, $s2, 11
    ctx->r15 = S32(ctx->r18 << 11);
    // 0x800BAE30: srl         $t8, $t7, 29
    ctx->r24 = S32(U32(ctx->r15) >> 29);
    // 0x800BAE34: lbu         $a2, 0x1($v0)
    ctx->r6 = MEM_BU(ctx->r2, 0X1);
    // 0x800BAE38: lbu         $a3, 0x0($v0)
    ctx->r7 = MEM_BU(ctx->r2, 0X0);
    // 0x800BAE3C: b           L_800BAE64
    // 0x800BAE40: andi        $s2, $t8, 0xFF
    ctx->r18 = ctx->r24 & 0XFF;
        goto L_800BAE64;
    // 0x800BAE40: andi        $s2, $t8, 0xFF
    ctx->r18 = ctx->r24 & 0XFF;
    // 0x800BAE44: lw          $a1, 0x14($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X14);
L_800BAE48:
    // 0x800BAE48: lw          $a0, 0x4C($a1)
    ctx->r4 = MEM_W(ctx->r5, 0X4C);
    // 0x800BAE4C: lwc1        $f0, 0x30($a1)
    ctx->f0.u32l = MEM_W(ctx->r5, 0X30);
    // 0x800BAE50: lwc1        $f20, 0x2C($a1)
    ctx->f20.u32l = MEM_W(ctx->r5, 0X2C);
    // 0x800BAE54: lbu         $t0, 0x8($a0)
    ctx->r8 = MEM_BU(ctx->r4, 0X8);
    // 0x800BAE58: lbu         $a2, 0x6($a1)
    ctx->r6 = MEM_BU(ctx->r5, 0X6);
    // 0x800BAE5C: lbu         $a3, 0x4($a0)
    ctx->r7 = MEM_BU(ctx->r4, 0X4);
    // 0x800BAE60: andi        $s2, $t0, 0x7
    ctx->r18 = ctx->r8 & 0X7;
L_800BAE64:
    // 0x800BAE64: lwc1        $f4, 0xC($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0XC);
    // 0x800BAE68: lwc1        $f6, 0x8($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X8);
    // 0x800BAE6C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BAE70: lwc1        $f10, 0x5534($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X5534);
    // 0x800BAE74: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x800BAE78: sb          $a3, 0x4B($sp)
    MEM_B(0X4B, ctx->r29) = ctx->r7;
    // 0x800BAE7C: sb          $a2, 0x49($sp)
    MEM_B(0X49, ctx->r29) = ctx->r6;
    // 0x800BAE80: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x800BAE84: mul.s       $f0, $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x800BAE88: nop

    // 0x800BAE8C: mul.s       $f0, $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f10.fl);
    // 0x800BAE90: nop

    // 0x800BAE94: mul.s       $f16, $f20, $f22
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f16.fl = MUL_S(ctx->f20.fl, ctx->f22.fl);
    // 0x800BAE98: mfc1        $a1, $f0
    ctx->r5 = (int32_t)ctx->f0.u32l;
    // 0x800BAE9C: mul.s       $f20, $f16, $f22
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f20.fl = MUL_S(ctx->f16.fl, ctx->f22.fl);
    // 0x800BAEA0: jal         0x800BA7E0
    // 0x800BAEA4: nop

    Audio_NoteSetResamplingRate(rdram, ctx);
        goto after_20;
    // 0x800BAEA4: nop

    after_20:
    // 0x800BAEA8: mfc1        $a1, $f20
    ctx->r5 = (int32_t)ctx->f20.u32l;
    // 0x800BAEAC: lbu         $a2, 0x49($sp)
    ctx->r6 = MEM_BU(ctx->r29, 0X49);
    // 0x800BAEB0: lbu         $a3, 0x4B($sp)
    ctx->r7 = MEM_BU(ctx->r29, 0X4B);
    // 0x800BAEB4: jal         0x800BA580
    // 0x800BAEB8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_InitNoteSub(rdram, ctx);
        goto after_21;
    // 0x800BAEB8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_21:
    // 0x800BAEBC: lbu         $t5, 0x1($s3)
    ctx->r13 = MEM_BU(ctx->r19, 0X1);
    // 0x800BAEC0: sll         $t3, $s2, 2
    ctx->r11 = S32(ctx->r18 << 2);
    // 0x800BAEC4: andi        $t4, $t3, 0x1C
    ctx->r12 = ctx->r11 & 0X1C;
    // 0x800BAEC8: andi        $t6, $t5, 0xFFE3
    ctx->r14 = ctx->r13 & 0XFFE3;
    // 0x800BAECC: or          $t7, $t4, $t6
    ctx->r15 = ctx->r12 | ctx->r14;
    // 0x800BAED0: sb          $t7, 0x1($s3)
    MEM_B(0X1, ctx->r19) = ctx->r15;
L_800BAED4:
    // 0x800BAED4: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BAED8: lw          $v1, 0x5548($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5548);
    // 0x800BAEDC: sll         $v0, $v1, 2
    ctx->r2 = S32(ctx->r3 << 2);
    // 0x800BAEE0: subu        $v0, $v0, $v1
    ctx->r2 = SUB32(ctx->r2, ctx->r3);
    // 0x800BAEE4: sll         $v0, $v0, 6
    ctx->r2 = S32(ctx->r2 << 6);
L_800BAEE8:
    // 0x800BAEE8: addiu       $s5, $s5, 0xC0
    ctx->r21 = ADD32(ctx->r21, 0XC0);
    // 0x800BAEEC: slt         $at, $s5, $v0
    ctx->r1 = SIGNED(ctx->r21) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800BAEF0: bne         $at, $zero, L_800BABE0
    if (ctx->r1 != 0) {
        // 0x800BAEF4: nop
    
            goto L_800BABE0;
    }
    // 0x800BAEF4: nop

L_800BAEF8:
    // 0x800BAEF8: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x800BAEFC: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x800BAF00: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x800BAF04: lw          $s0, 0x24($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X24);
    // 0x800BAF08: lw          $s1, 0x28($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X28);
    // 0x800BAF0C: lw          $s2, 0x2C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X2C);
    // 0x800BAF10: lw          $s3, 0x30($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X30);
    // 0x800BAF14: lw          $s4, 0x34($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X34);
    // 0x800BAF18: lw          $s5, 0x38($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X38);
    // 0x800BAF1C: lw          $s6, 0x3C($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X3C);
    // 0x800BAF20: lw          $s7, 0x40($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X40);
    // 0x800BAF24: jr          $ra
    // 0x800BAF28: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x800BAF28: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void Audio_SeqLayerDecayRelease(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BAF2C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BAF30: addiu       $a2, $zero, -0x1
    ctx->r6 = ADD32(0, -0X1);
    // 0x800BAF34: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BAF38: beq         $a0, $a2, L_800BB0F8
    if (ctx->r4 == ctx->r6) {
        // 0x800BAF3C: or          $a3, $a1, $zero
        ctx->r7 = ctx->r5 | 0;
            goto L_800BB0F8;
    }
    // 0x800BAF3C: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800BAF40: lw          $v0, 0x40($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X40);
    // 0x800BAF44: beql        $v0, $zero, L_800BB0FC
    if (ctx->r2 == 0) {
        // 0x800BAF48: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BB0FC;
    }
    goto skip_0;
    // 0x800BAF48: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800BAF4C: lw          $t6, 0x48($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X48);
    // 0x800BAF50: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BAF54: bnel        $a0, $t6, L_800BAF64
    if (ctx->r4 != ctx->r14) {
        // 0x800BAF58: lw          $v0, 0x44($a1)
        ctx->r2 = MEM_W(ctx->r5, 0X44);
            goto L_800BAF64;
    }
    goto skip_1;
    // 0x800BAF58: lw          $v0, 0x44($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X44);
    skip_1:
    // 0x800BAF5C: sw          $a2, 0x48($v0)
    MEM_W(0X48, ctx->r2) = ctx->r6;
    // 0x800BAF60: lw          $v0, 0x44($a1)
    ctx->r2 = MEM_W(ctx->r5, 0X44);
L_800BAF64:
    // 0x800BAF64: beql        $a0, $v0, L_800BAFB8
    if (ctx->r4 == ctx->r2) {
        // 0x800BAF68: sb          $zero, 0x2($a0)
        MEM_B(0X2, ctx->r4) = 0;
            goto L_800BAFB8;
    }
    goto skip_2;
    // 0x800BAF68: sb          $zero, 0x2($a0)
    MEM_B(0X2, ctx->r4) = 0;
    skip_2:
    // 0x800BAF6C: bnel        $a2, $v0, L_800BB0FC
    if (ctx->r6 != ctx->r2) {
        // 0x800BAF70: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BB0FC;
    }
    goto skip_3;
    // 0x800BAF70: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_3:
    // 0x800BAF74: lw          $t7, 0x48($a1)
    ctx->r15 = MEM_W(ctx->r5, 0X48);
    // 0x800BAF78: bnel        $a2, $t7, L_800BB0FC
    if (ctx->r6 != ctx->r15) {
        // 0x800BAF7C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BB0FC;
    }
    goto skip_4;
    // 0x800BAF7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x800BAF80: lw          $t8, 0x40($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X40);
    // 0x800BAF84: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x800BAF88: bnel        $a0, $t8, L_800BB0FC
    if (ctx->r4 != ctx->r24) {
        // 0x800BAF8C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BB0FC;
    }
    goto skip_5;
    // 0x800BAF8C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_5:
    // 0x800BAF90: beql        $a3, $t0, L_800BB0FC
    if (ctx->r7 == ctx->r8) {
        // 0x800BAF94: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800BB0FC;
    }
    goto skip_6;
    // 0x800BAF94: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_6:
    // 0x800BAF98: lbu         $t9, 0x58($a1)
    ctx->r25 = MEM_BU(ctx->r5, 0X58);
    // 0x800BAF9C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BAFA0: lwc1        $f4, 0x5538($at)
    ctx->f4.u32l = MEM_W(ctx->r1, 0X5538);
    // 0x800BAFA4: ori         $t1, $t9, 0x10
    ctx->r9 = ctx->r25 | 0X10;
    // 0x800BAFA8: sb          $t1, 0x58($a1)
    MEM_B(0X58, ctx->r5) = ctx->r9;
    // 0x800BAFAC: b           L_800BB0F8
    // 0x800BAFB0: swc1        $f4, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f4.u32l;
        goto L_800BB0F8;
    // 0x800BAFB0: swc1        $f4, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f4.u32l;
    // 0x800BAFB4: sb          $zero, 0x2($a0)
    MEM_B(0X2, ctx->r4) = 0;
L_800BAFB8:
    // 0x800BAFB8: lbu         $t2, 0x59($a1)
    ctx->r10 = MEM_BU(ctx->r5, 0X59);
    // 0x800BAFBC: addiu       $t0, $zero, 0x6
    ctx->r8 = ADD32(0, 0X6);
    // 0x800BAFC0: addiu       $t5, $zero, 0x1
    ctx->r13 = ADD32(0, 0X1);
    // 0x800BAFC4: beq         $t0, $t2, L_800BB0D8
    if (ctx->r8 == ctx->r10) {
        // 0x800BAFC8: addiu       $at, $zero, 0x7
        ctx->r1 = ADD32(0, 0X7);
            goto L_800BB0D8;
    }
    // 0x800BAFC8: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800BAFCC: lwc1        $f6, 0x30($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X30);
    // 0x800BAFD0: addiu       $v0, $a1, 0x4C
    ctx->r2 = ADD32(ctx->r5, 0X4C);
    // 0x800BAFD4: swc1        $f6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f6.u32l;
    // 0x800BAFD8: lwc1        $f8, 0x2C($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X2C);
    // 0x800BAFDC: swc1        $f8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f8.u32l;
    // 0x800BAFE0: lbu         $t3, 0x6($a0)
    ctx->r11 = MEM_BU(ctx->r4, 0X6);
    // 0x800BAFE4: sb          $t3, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r11;
    // 0x800BAFE8: lw          $v1, 0x4C($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X4C);
    // 0x800BAFEC: beql        $v1, $zero, L_800BB000
    if (ctx->r3 == 0) {
        // 0x800BAFF0: lw          $t6, 0x44($a1)
        ctx->r14 = MEM_W(ctx->r5, 0X44);
            goto L_800BB000;
    }
    goto skip_7;
    // 0x800BAFF0: lw          $t6, 0x44($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X44);
    skip_7:
    // 0x800BAFF4: lbu         $t4, 0x4($v1)
    ctx->r12 = MEM_BU(ctx->r3, 0X4);
    // 0x800BAFF8: sb          $t4, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r12;
    // 0x800BAFFC: lw          $t6, 0x44($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X44);
L_800BB000:
    // 0x800BB000: sb          $t5, 0x30($a1)
    MEM_B(0X30, ctx->r5) = ctx->r13;
    // 0x800BB004: sw          $a2, 0x44($a1)
    MEM_W(0X44, ctx->r5) = ctx->r6;
    // 0x800BB008: bne         $a3, $at, L_800BB02C
    if (ctx->r7 != ctx->r1) {
        // 0x800BB00C: sw          $t6, 0x40($a1)
        MEM_W(0X40, ctx->r5) = ctx->r14;
            goto L_800BB02C;
    }
    // 0x800BB00C: sw          $t6, 0x40($a1)
    MEM_W(0X40, ctx->r5) = ctx->r14;
    // 0x800BB010: lbu         $t7, 0x58($a1)
    ctx->r15 = MEM_BU(ctx->r5, 0X58);
    // 0x800BB014: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BB018: lwc1        $f10, 0x5538($at)
    ctx->f10.u32l = MEM_W(ctx->r1, 0X5538);
    // 0x800BB01C: ori         $t8, $t7, 0x10
    ctx->r24 = ctx->r15 | 0X10;
    // 0x800BB020: sb          $t8, 0x58($a1)
    MEM_B(0X58, ctx->r5) = ctx->r24;
    // 0x800BB024: b           L_800BB0D8
    // 0x800BB028: swc1        $f10, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f10.u32l;
        goto L_800BB0D8;
    // 0x800BB028: swc1        $f10, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f10.u32l;
L_800BB02C:
    // 0x800BB02C: lbu         $t9, 0x58($a1)
    ctx->r25 = MEM_BU(ctx->r5, 0X58);
    // 0x800BB030: ori         $t1, $t9, 0x20
    ctx->r9 = ctx->r25 | 0X20;
    // 0x800BB034: sb          $t1, 0x58($a1)
    MEM_B(0X58, ctx->r5) = ctx->r9;
    // 0x800BB038: lbu         $v0, 0x18($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X18);
    // 0x800BB03C: bnel        $v0, $zero, L_800BB080
    if (ctx->r2 != 0) {
        // 0x800BB040: mtc1        $v0, $f10
        ctx->f10.u32l = ctx->r2;
            goto L_800BB080;
    }
    goto skip_8;
    // 0x800BB040: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    skip_8:
    // 0x800BB044: lw          $t2, 0x4C($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X4C);
    // 0x800BB048: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x800BB04C: lbu         $t3, 0x7C($t2)
    ctx->r11 = MEM_BU(ctx->r10, 0X7C);
    // 0x800BB050: mtc1        $t3, $f16
    ctx->f16.u32l = ctx->r11;
    // 0x800BB054: bgez        $t3, L_800BB068
    if (SIGNED(ctx->r11) >= 0) {
        // 0x800BB058: cvt.s.w     $f18, $f16
        CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
            goto L_800BB068;
    }
    // 0x800BB058: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800BB05C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BB060: nop

    // 0x800BB064: add.s       $f18, $f18, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = ctx->f18.fl + ctx->f4.fl;
L_800BB068:
    // 0x800BB068: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BB06C: lwc1        $f6, 0x553C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, 0X553C);
    // 0x800BB070: mul.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f6.fl);
    // 0x800BB074: b           L_800BB0A8
    // 0x800BB078: swc1        $f8, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f8.u32l;
        goto L_800BB0A8;
    // 0x800BB078: swc1        $f8, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f8.u32l;
    // 0x800BB07C: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
L_800BB080:
    // 0x800BB080: lui         $at, 0x4F80
    ctx->r1 = S32(0X4F80 << 16);
    // 0x800BB084: bgez        $v0, L_800BB098
    if (SIGNED(ctx->r2) >= 0) {
        // 0x800BB088: cvt.s.w     $f16, $f10
        CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
            goto L_800BB098;
    }
    // 0x800BB088: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800BB08C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800BB090: nop

    // 0x800BB094: add.s       $f16, $f16, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = ctx->f16.fl + ctx->f4.fl;
L_800BB098:
    // 0x800BB098: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800BB09C: lwc1        $f18, 0x553C($at)
    ctx->f18.u32l = MEM_W(ctx->r1, 0X553C);
    // 0x800BB0A0: mul.s       $f6, $f16, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x800BB0A4: swc1        $f6, 0x68($a1)
    MEM_W(0X68, ctx->r5) = ctx->f6.u32l;
L_800BB0A8:
    // 0x800BB0A8: lw          $t4, 0x4C($a0)
    ctx->r12 = MEM_W(ctx->r4, 0X4C);
    // 0x800BB0AC: lwc1        $f4, 0x6C($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X6C);
    // 0x800BB0B0: lui         $at, 0x3B80
    ctx->r1 = S32(0X3B80 << 16);
    // 0x800BB0B4: lbu         $t5, 0x7D($t4)
    ctx->r13 = MEM_BU(ctx->r12, 0X7D);
    // 0x800BB0B8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x800BB0BC: mtc1        $t5, $f8
    ctx->f8.u32l = ctx->r13;
    // 0x800BB0C0: nop

    // 0x800BB0C4: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800BB0C8: mul.s       $f16, $f10, $f4
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x800BB0CC: nop

    // 0x800BB0D0: mul.s       $f6, $f16, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x800BB0D4: swc1        $f6, 0x60($a1)
    MEM_W(0X60, ctx->r5) = ctx->f6.u32l;
L_800BB0D8:
    // 0x800BB0D8: bne         $a3, $t0, L_800BB0F8
    if (ctx->r7 != ctx->r8) {
        // 0x800BB0DC: or          $a0, $a1, $zero
        ctx->r4 = ctx->r5 | 0;
            goto L_800BB0F8;
    }
    // 0x800BB0DC: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x800BB0E0: jal         0x800BB6DC
    // 0x800BB0E4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    Audio_AudioListRemove(rdram, ctx);
        goto after_0;
    // 0x800BB0E4: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    after_0:
    // 0x800BB0E8: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB0EC: lw          $a0, 0xC($a1)
    ctx->r4 = MEM_W(ctx->r5, 0XC);
    // 0x800BB0F0: jal         0x800BB69C
    // 0x800BB0F4: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    Audio_AudioListPushFront(rdram, ctx);
        goto after_1;
    // 0x800BB0F4: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    after_1:
L_800BB0F8:
    // 0x800BB0F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800BB0FC:
    // 0x800BB0FC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB100: jr          $ra
    // 0x800BB104: nop

    return;
    // 0x800BB104: nop

;}
RECOMP_FUNC void Audio_SeqLayerNoteDecay(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB108: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BB10C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB110: jal         0x800BAF2C
    // 0x800BB114: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    Audio_SeqLayerDecayRelease(rdram, ctx);
        goto after_0;
    // 0x800BB114: addiu       $a1, $zero, 0x6
    ctx->r5 = ADD32(0, 0X6);
    after_0:
    // 0x800BB118: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB11C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BB120: jr          $ra
    // 0x800BB124: nop

    return;
    // 0x800BB124: nop

;}
RECOMP_FUNC void Audio_SeqLayerNoteRelease(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB128: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800BB12C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB130: jal         0x800BAF2C
    // 0x800BB134: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    Audio_SeqLayerDecayRelease(rdram, ctx);
        goto after_0;
    // 0x800BB134: addiu       $a1, $zero, 0x7
    ctx->r5 = ADD32(0, 0X7);
    after_0:
    // 0x800BB138: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB13C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800BB140: jr          $ra
    // 0x800BB144: nop

    return;
    // 0x800BB144: nop

;}
RECOMP_FUNC void Audio_BuildSyntheticWave(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB148: slti        $at, $a2, 0x80
    ctx->r1 = SIGNED(ctx->r6) < 0X80 ? 1 : 0;
    // 0x800BB14C: beq         $at, $zero, L_800BB158
    if (ctx->r1 == 0) {
        // 0x800BB150: or          $v1, $zero, $zero
        ctx->r3 = 0 | 0;
            goto L_800BB158;
    }
    // 0x800BB150: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800BB154: addiu       $a2, $zero, 0x80
    ctx->r6 = ADD32(0, 0X80);
L_800BB158:
    // 0x800BB158: lbu         $t6, 0x8($a1)
    ctx->r14 = MEM_BU(ctx->r5, 0X8);
    // 0x800BB15C: lwc1        $f2, 0x24($a1)
    ctx->f2.u32l = MEM_W(ctx->r5, 0X24);
    // 0x800BB160: beq         $t6, $zero, L_800BB198
    if (ctx->r14 == 0) {
        // 0x800BB164: mov.s       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
            goto L_800BB198;
    }
    // 0x800BB164: mov.s       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.fl = ctx->f2.fl;
    // 0x800BB168: lwc1        $f12, 0x14($a1)
    ctx->f12.u32l = MEM_W(ctx->r5, 0X14);
    // 0x800BB16C: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800BB170: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800BB174: c.lt.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl < ctx->f12.fl;
    // 0x800BB178: nop

    // 0x800BB17C: bc1fl       L_800BB19C
    if (!c1cs) {
        // 0x800BB180: lui         $at, 0x3F80
        ctx->r1 = S32(0X3F80 << 16);
            goto L_800BB19C;
    }
    goto skip_0;
    // 0x800BB180: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    skip_0:
    // 0x800BB184: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800BB188: nop

    // 0x800BB18C: add.s       $f8, $f12, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f12.fl + ctx->f6.fl;
    // 0x800BB190: mul.s       $f0, $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x800BB194: nop

L_800BB198:
    // 0x800BB198: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
L_800BB19C:
    // 0x800BB19C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800BB1A0: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800BB1A4: c.lt.s      $f0, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f0.fl < ctx->f10.fl;
    // 0x800BB1A8: nop

    // 0x800BB1AC: bc1fl       L_800BB1C4
    if (!c1cs) {
        // 0x800BB1B0: mtc1        $at, $f16
        ctx->f16.u32l = ctx->r1;
            goto L_800BB1C4;
    }
    goto skip_1;
    // 0x800BB1B0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    skip_1:
    // 0x800BB1B4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BB1B8: b           L_800BB218
    // 0x800BB1BC: lwc1        $f0, -0x438C($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X438C);
        goto L_800BB218;
    // 0x800BB1BC: lwc1        $f0, -0x438C($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X438C);
    // 0x800BB1C0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
L_800BB1C4:
    // 0x800BB1C4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800BB1C8: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x800BB1CC: c.lt.s      $f0, $f16
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f0.fl < ctx->f16.fl;
    // 0x800BB1D0: nop

    // 0x800BB1D4: bc1fl       L_800BB1EC
    if (!c1cs) {
        // 0x800BB1D8: mtc1        $at, $f18
        ctx->f18.u32l = ctx->r1;
            goto L_800BB1EC;
    }
    goto skip_2;
    // 0x800BB1D8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    skip_2:
    // 0x800BB1DC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BB1E0: b           L_800BB218
    // 0x800BB1E4: lwc1        $f0, -0x4388($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4388);
        goto L_800BB218;
    // 0x800BB1E4: lwc1        $f0, -0x4388($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4388);
    // 0x800BB1E8: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
L_800BB1EC:
    // 0x800BB1EC: addiu       $v1, $zero, 0x3
    ctx->r3 = ADD32(0, 0X3);
    // 0x800BB1F0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BB1F4: c.lt.s      $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    c1cs = ctx->f0.fl < ctx->f18.fl;
    // 0x800BB1F8: nop

    // 0x800BB1FC: bc1f        L_800BB214
    if (!c1cs) {
        // 0x800BB200: nop
    
            goto L_800BB214;
    }
    // 0x800BB200: nop

    // 0x800BB204: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800BB208: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
    // 0x800BB20C: b           L_800BB218
    // 0x800BB210: lwc1        $f0, -0x4384($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4384);
        goto L_800BB218;
    // 0x800BB210: lwc1        $f0, -0x4384($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4384);
L_800BB214:
    // 0x800BB214: lwc1        $f0, -0x4380($at)
    ctx->f0.u32l = MEM_W(ctx->r1, -0X4380);
L_800BB218:
    // 0x800BB218: mul.s       $f4, $f2, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // 0x800BB21C: sll         $t7, $a2, 2
    ctx->r15 = S32(ctx->r6 << 2);
    // 0x800BB220: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800BB224: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x800BB228: sll         $t0, $v1, 7
    ctx->r8 = S32(ctx->r3 << 7);
    // 0x800BB22C: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    // 0x800BB230: swc1        $f4, 0x24($a1)
    MEM_W(0X24, ctx->r5) = ctx->f4.u32l;
    // 0x800BB234: sb          $a2, 0x31($a0)
    MEM_B(0X31, ctx->r4) = ctx->r6;
    // 0x800BB238: sb          $v1, 0x32($a0)
    MEM_B(0X32, ctx->r4) = ctx->r3;
    // 0x800BB23C: lw          $t8, -0x25D0($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X25D0);
    // 0x800BB240: addu        $t1, $t8, $t0
    ctx->r9 = ADD32(ctx->r24, ctx->r8);
    // 0x800BB244: jr          $ra
    // 0x800BB248: sw          $t1, 0xBC($a0)
    MEM_W(0XBC, ctx->r4) = ctx->r9;
    return;
    // 0x800BB248: sw          $t1, 0xBC($a0)
    MEM_W(0XBC, ctx->r4) = ctx->r9;
;}
RECOMP_FUNC void Audio_InitSyntheticWave(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB24C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB250: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800BB254: lbu         $a2, 0x1($a1)
    ctx->r6 = MEM_BU(ctx->r5, 0X1);
    // 0x800BB258: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800BB25C: bnel        $a2, $at, L_800BB270
    if (ctx->r6 != ctx->r1) {
        // 0x800BB260: lbu         $t7, 0x32($a0)
        ctx->r15 = MEM_BU(ctx->r4, 0X32);
            goto L_800BB270;
    }
    goto skip_0;
    // 0x800BB260: lbu         $t7, 0x32($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X32);
    skip_0:
    // 0x800BB264: lw          $t6, 0x4C($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X4C);
    // 0x800BB268: lh          $a2, 0x1C($t6)
    ctx->r6 = MEM_H(ctx->r14, 0X1C);
    // 0x800BB26C: lbu         $t7, 0x32($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X32);
L_800BB270:
    // 0x800BB270: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800BB274: jal         0x800BB148
    // 0x800BB278: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    Audio_BuildSyntheticWave(rdram, ctx);
        goto after_0;
    // 0x800BB278: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    after_0:
    // 0x800BB27C: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800BB280: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800BB284: addiu       $v1, $v1, -0x23B8
    ctx->r3 = ADD32(ctx->r3, -0X23B8);
    // 0x800BB288: addu        $t9, $v1, $v0
    ctx->r25 = ADD32(ctx->r3, ctx->r2);
    // 0x800BB28C: lbu         $t0, 0x0($t9)
    ctx->r8 = MEM_BU(ctx->r25, 0X0);
    // 0x800BB290: lw          $t8, 0x18($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X18);
    // 0x800BB294: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB298: multu       $t8, $t0
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800BB29C: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x800BB2A0: lbu         $t4, 0x0($t3)
    ctx->r12 = MEM_BU(ctx->r11, 0X0);
    // 0x800BB2A4: mflo        $t1
    ctx->r9 = lo;
    // 0x800BB2A8: nop

    // 0x800BB2AC: nop

    // 0x800BB2B0: div         $zero, $t1, $t4
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r12))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r12)));
    // 0x800BB2B4: mflo        $t5
    ctx->r13 = lo;
    // 0x800BB2B8: sw          $t5, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->r13;
    // 0x800BB2BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800BB2C0: bne         $t4, $zero, L_800BB2CC
    if (ctx->r12 != 0) {
        // 0x800BB2C4: nop
    
            goto L_800BB2CC;
    }
    // 0x800BB2C4: nop

    // 0x800BB2C8: break       7
    do_break(2148250312);
L_800BB2CC:
    // 0x800BB2CC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800BB2D0: bne         $t4, $at, L_800BB2E4
    if (ctx->r12 != ctx->r1) {
        // 0x800BB2D4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800BB2E4;
    }
    // 0x800BB2D4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800BB2D8: bne         $t1, $at, L_800BB2E4
    if (ctx->r9 != ctx->r1) {
        // 0x800BB2DC: nop
    
            goto L_800BB2E4;
    }
    // 0x800BB2DC: nop

    // 0x800BB2E0: break       6
    do_break(2148250336);
L_800BB2E4:
    // 0x800BB2E4: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB2E8: jr          $ra
    // 0x800BB2EC: nop

    return;
    // 0x800BB2EC: nop

;}
RECOMP_FUNC void Audio_InitNoteList(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB2F0: sw          $a0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r4;
    // 0x800BB2F4: sw          $a0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r4;
    // 0x800BB2F8: jr          $ra
    // 0x800BB2FC: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
    return;
    // 0x800BB2FC: sw          $zero, 0x8($a0)
    MEM_W(0X8, ctx->r4) = 0;
;}
RECOMP_FUNC void Audio_InitNoteLists(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB300: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800BB304: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800BB308: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BB30C: jal         0x800BB2F0
    // 0x800BB310: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    Audio_InitNoteList(rdram, ctx);
        goto after_0;
    // 0x800BB310: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    after_0:
    // 0x800BB314: jal         0x800BB2F0
    // 0x800BB318: addiu       $a0, $s0, 0x10
    ctx->r4 = ADD32(ctx->r16, 0X10);
    Audio_InitNoteList(rdram, ctx);
        goto after_1;
    // 0x800BB318: addiu       $a0, $s0, 0x10
    ctx->r4 = ADD32(ctx->r16, 0X10);
    after_1:
    // 0x800BB31C: jal         0x800BB2F0
    // 0x800BB320: addiu       $a0, $s0, 0x20
    ctx->r4 = ADD32(ctx->r16, 0X20);
    Audio_InitNoteList(rdram, ctx);
        goto after_2;
    // 0x800BB320: addiu       $a0, $s0, 0x20
    ctx->r4 = ADD32(ctx->r16, 0X20);
    after_2:
    // 0x800BB324: jal         0x800BB2F0
    // 0x800BB328: addiu       $a0, $s0, 0x30
    ctx->r4 = ADD32(ctx->r16, 0X30);
    Audio_InitNoteList(rdram, ctx);
        goto after_3;
    // 0x800BB328: addiu       $a0, $s0, 0x30
    ctx->r4 = ADD32(ctx->r16, 0X30);
    after_3:
    // 0x800BB32C: sw          $s0, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r16;
    // 0x800BB330: sw          $s0, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->r16;
    // 0x800BB334: sw          $s0, 0x2C($s0)
    MEM_W(0X2C, ctx->r16) = ctx->r16;
    // 0x800BB338: sw          $s0, 0x3C($s0)
    MEM_W(0X3C, ctx->r16) = ctx->r16;
    // 0x800BB33C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB340: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BB344: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800BB348: jr          $ra
    // 0x800BB34C: nop

    return;
    // 0x800BB34C: nop

;}
RECOMP_FUNC void Audio_InitNoteFreeList(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB350: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800BB354: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BB358: lui         $s3, 0x8004
    ctx->r19 = S32(0X8004 << 16);
    // 0x800BB35C: addiu       $s3, $s3, 0x4760
    ctx->r19 = ADD32(ctx->r19, 0X4760);
    // 0x800BB360: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800BB364: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BB368: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BB36C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BB370: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BB374: jal         0x800BB300
    // 0x800BB378: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    Audio_InitNoteLists(rdram, ctx);
        goto after_0;
    // 0x800BB378: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_0:
    // 0x800BB37C: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800BB380: addiu       $s4, $s4, 0x5548
    ctx->r20 = ADD32(ctx->r20, 0X5548);
    // 0x800BB384: lw          $t6, 0x0($s4)
    ctx->r14 = MEM_W(ctx->r20, 0X0);
    // 0x800BB388: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x800BB38C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BB390: blez        $t6, L_800BB3E0
    if (SIGNED(ctx->r14) <= 0) {
        // 0x800BB394: lui         $s2, 0x8004
        ctx->r18 = S32(0X8004 << 16);
            goto L_800BB3E0;
    }
    // 0x800BB394: lui         $s2, 0x8004
    ctx->r18 = S32(0X8004 << 16);
    // 0x800BB398: addiu       $s2, $s2, -0x340
    ctx->r18 = ADD32(ctx->r18, -0X340);
    // 0x800BB39C: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
L_800BB3A0:
    // 0x800BB3A0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x800BB3A4: addu        $t7, $s0, $v0
    ctx->r15 = ADD32(ctx->r16, ctx->r2);
    // 0x800BB3A8: addu        $t8, $v0, $s0
    ctx->r24 = ADD32(ctx->r2, ctx->r16);
    // 0x800BB3AC: sw          $t7, 0x8($t8)
    MEM_W(0X8, ctx->r24) = ctx->r15;
    // 0x800BB3B0: lw          $t9, 0x0($s2)
    ctx->r25 = MEM_W(ctx->r18, 0X0);
    // 0x800BB3B4: addu        $t0, $t9, $s0
    ctx->r8 = ADD32(ctx->r25, ctx->r16);
    // 0x800BB3B8: sw          $zero, 0x0($t0)
    MEM_W(0X0, ctx->r8) = 0;
    // 0x800BB3BC: lw          $t1, 0x0($s2)
    ctx->r9 = MEM_W(ctx->r18, 0X0);
    // 0x800BB3C0: jal         0x800BCFAC
    // 0x800BB3C4: addu        $a1, $s0, $t1
    ctx->r5 = ADD32(ctx->r16, ctx->r9);
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_1;
    // 0x800BB3C4: addu        $a1, $s0, $t1
    ctx->r5 = ADD32(ctx->r16, ctx->r9);
    after_1:
    // 0x800BB3C8: lw          $t2, 0x0($s4)
    ctx->r10 = MEM_W(ctx->r20, 0X0);
    // 0x800BB3CC: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800BB3D0: addiu       $s0, $s0, 0xC0
    ctx->r16 = ADD32(ctx->r16, 0XC0);
    // 0x800BB3D4: slt         $at, $s1, $t2
    ctx->r1 = SIGNED(ctx->r17) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x800BB3D8: bnel        $at, $zero, L_800BB3A0
    if (ctx->r1 != 0) {
        // 0x800BB3DC: lw          $v0, 0x0($s2)
        ctx->r2 = MEM_W(ctx->r18, 0X0);
            goto L_800BB3A0;
    }
    goto skip_0;
    // 0x800BB3DC: lw          $v0, 0x0($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X0);
    skip_0:
L_800BB3E0:
    // 0x800BB3E0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800BB3E4: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BB3E8: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB3EC: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BB3F0: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BB3F4: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BB3F8: jr          $ra
    // 0x800BB3FC: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x800BB3FC: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void Audio_NotePoolClear(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB400: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x800BB404: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800BB408: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800BB40C: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800BB410: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800BB414: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BB418: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BB41C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BB420: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BB424: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800BB428: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800BB42C: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BB430: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BB434: or          $s4, $a0, $zero
    ctx->r20 = ctx->r4 | 0;
    // 0x800BB438: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800BB43C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800BB440: addiu       $v0, $v0, 0x4790
    ctx->r2 = ADD32(ctx->r2, 0X4790);
    // 0x800BB444: addiu       $v1, $v1, 0x4780
    ctx->r3 = ADD32(ctx->r3, 0X4780);
    // 0x800BB448: addiu       $a1, $a1, 0x4770
    ctx->r5 = ADD32(ctx->r5, 0X4770);
    // 0x800BB44C: addiu       $a2, $a2, 0x4760
    ctx->r6 = ADD32(ctx->r6, 0X4760);
    // 0x800BB450: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
    // 0x800BB454: lw          $s2, 0x40($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X40);
    // 0x800BB458: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x800BB45C: addiu       $s5, $zero, 0x1
    ctx->r21 = ADD32(0, 0X1);
    // 0x800BB460: addiu       $s6, $zero, 0x2
    ctx->r22 = ADD32(0, 0X2);
    // 0x800BB464: addiu       $s7, $zero, 0x3
    ctx->r23 = ADD32(0, 0X3);
    // 0x800BB468: addiu       $fp, $zero, 0x4
    ctx->r30 = ADD32(0, 0X4);
L_800BB46C:
    // 0x800BB46C: beql        $s3, $zero, L_800BB498
    if (ctx->r19 == 0) {
        // 0x800BB470: or          $s1, $s4, $zero
        ctx->r17 = ctx->r20 | 0;
            goto L_800BB498;
    }
    goto skip_0;
    // 0x800BB470: or          $s1, $s4, $zero
    ctx->r17 = ctx->r20 | 0;
    skip_0:
    // 0x800BB474: beql        $s3, $s5, L_800BB4A8
    if (ctx->r19 == ctx->r21) {
        // 0x800BB478: addiu       $s1, $s4, 0x10
        ctx->r17 = ADD32(ctx->r20, 0X10);
            goto L_800BB4A8;
    }
    goto skip_1;
    // 0x800BB478: addiu       $s1, $s4, 0x10
    ctx->r17 = ADD32(ctx->r20, 0X10);
    skip_1:
    // 0x800BB47C: beql        $s3, $s6, L_800BB4B8
    if (ctx->r19 == ctx->r22) {
        // 0x800BB480: addiu       $s1, $s4, 0x20
        ctx->r17 = ADD32(ctx->r20, 0X20);
            goto L_800BB4B8;
    }
    goto skip_2;
    // 0x800BB480: addiu       $s1, $s4, 0x20
    ctx->r17 = ADD32(ctx->r20, 0X20);
    skip_2:
    // 0x800BB484: beql        $s3, $s7, L_800BB4C8
    if (ctx->r19 == ctx->r23) {
        // 0x800BB488: addiu       $s1, $s4, 0x30
        ctx->r17 = ADD32(ctx->r20, 0X30);
            goto L_800BB4C8;
    }
    goto skip_3;
    // 0x800BB488: addiu       $s1, $s4, 0x30
    ctx->r17 = ADD32(ctx->r20, 0X30);
    skip_3:
    // 0x800BB48C: b           L_800BB4D0
    // 0x800BB490: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
        goto L_800BB4D0;
    // 0x800BB490: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x800BB494: or          $s1, $s4, $zero
    ctx->r17 = ctx->r20 | 0;
L_800BB498:
    // 0x800BB498: or          $s2, $a2, $zero
    ctx->r18 = ctx->r6 | 0;
    // 0x800BB49C: b           L_800BB4D0
    // 0x800BB4A0: lw          $s0, 0x4($s4)
    ctx->r16 = MEM_W(ctx->r20, 0X4);
        goto L_800BB4D0;
    // 0x800BB4A0: lw          $s0, 0x4($s4)
    ctx->r16 = MEM_W(ctx->r20, 0X4);
    // 0x800BB4A4: addiu       $s1, $s4, 0x10
    ctx->r17 = ADD32(ctx->r20, 0X10);
L_800BB4A8:
    // 0x800BB4A8: or          $s2, $a1, $zero
    ctx->r18 = ctx->r5 | 0;
    // 0x800BB4AC: b           L_800BB4D0
    // 0x800BB4B0: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
        goto L_800BB4D0;
    // 0x800BB4B0: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x800BB4B4: addiu       $s1, $s4, 0x20
    ctx->r17 = ADD32(ctx->r20, 0X20);
L_800BB4B8:
    // 0x800BB4B8: or          $s2, $v1, $zero
    ctx->r18 = ctx->r3 | 0;
    // 0x800BB4BC: b           L_800BB4D0
    // 0x800BB4C0: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
        goto L_800BB4D0;
    // 0x800BB4C0: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x800BB4C4: addiu       $s1, $s4, 0x30
    ctx->r17 = ADD32(ctx->r20, 0X30);
L_800BB4C8:
    // 0x800BB4C8: or          $s2, $v0, $zero
    ctx->r18 = ctx->r2 | 0;
    // 0x800BB4CC: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
L_800BB4D0:
    // 0x800BB4D0: beql        $s0, $s1, L_800BB520
    if (ctx->r16 == ctx->r17) {
        // 0x800BB4D4: addiu       $s3, $s3, 0x1
        ctx->r19 = ADD32(ctx->r19, 0X1);
            goto L_800BB520;
    }
    goto skip_4;
    // 0x800BB4D4: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    skip_4:
L_800BB4D8:
    // 0x800BB4D8: beql        $s0, $zero, L_800BB520
    if (ctx->r16 == 0) {
        // 0x800BB4DC: addiu       $s3, $s3, 0x1
        ctx->r19 = ADD32(ctx->r19, 0X1);
            goto L_800BB520;
    }
    goto skip_5;
    // 0x800BB4DC: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    skip_5:
    // 0x800BB4E0: jal         0x800BB6DC
    // 0x800BB4E4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Audio_AudioListRemove(rdram, ctx);
        goto after_0;
    // 0x800BB4E4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800BB4E8: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800BB4EC: jal         0x800BCFAC
    // 0x800BB4F0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_1;
    // 0x800BB4F0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_1:
    // 0x800BB4F4: lw          $s0, 0x4($s1)
    ctx->r16 = MEM_W(ctx->r17, 0X4);
    // 0x800BB4F8: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800BB4FC: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800BB500: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800BB504: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800BB508: addiu       $v0, $v0, 0x4790
    ctx->r2 = ADD32(ctx->r2, 0X4790);
    // 0x800BB50C: addiu       $v1, $v1, 0x4780
    ctx->r3 = ADD32(ctx->r3, 0X4780);
    // 0x800BB510: addiu       $a1, $a1, 0x4770
    ctx->r5 = ADD32(ctx->r5, 0X4770);
    // 0x800BB514: bne         $s0, $s1, L_800BB4D8
    if (ctx->r16 != ctx->r17) {
        // 0x800BB518: addiu       $a2, $a2, 0x4760
        ctx->r6 = ADD32(ctx->r6, 0X4760);
            goto L_800BB4D8;
    }
    // 0x800BB518: addiu       $a2, $a2, 0x4760
    ctx->r6 = ADD32(ctx->r6, 0X4760);
    // 0x800BB51C: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
L_800BB520:
    // 0x800BB520: bne         $s3, $fp, L_800BB46C
    if (ctx->r19 != ctx->r30) {
        // 0x800BB524: nop
    
            goto L_800BB46C;
    }
    // 0x800BB524: nop

    // 0x800BB528: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800BB52C: sw          $s2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r18;
    // 0x800BB530: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
    // 0x800BB534: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB538: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BB53C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BB540: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BB544: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BB548: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800BB54C: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800BB550: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800BB554: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800BB558: jr          $ra
    // 0x800BB55C: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x800BB55C: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void Audio_NotePoolFill(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB560: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x800BB564: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800BB568: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800BB56C: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800BB570: or          $s3, $a1, $zero
    ctx->r19 = ctx->r5 | 0;
    // 0x800BB574: or          $s5, $a0, $zero
    ctx->r21 = ctx->r4 | 0;
    // 0x800BB578: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800BB57C: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800BB580: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800BB584: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800BB588: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800BB58C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800BB590: jal         0x800BB400
    // 0x800BB594: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    Audio_NotePoolClear(rdram, ctx);
        goto after_0;
    // 0x800BB594: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    after_0:
    // 0x800BB598: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x800BB59C: blez        $s3, L_800BB66C
    if (SIGNED(ctx->r19) <= 0) {
        // 0x800BB5A0: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800BB66C;
    }
    // 0x800BB5A0: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800BB5A4: addiu       $fp, $zero, 0x2
    ctx->r30 = ADD32(0, 0X2);
    // 0x800BB5A8: addiu       $s7, $zero, 0x1
    ctx->r23 = ADD32(0, 0X1);
    // 0x800BB5AC: addiu       $s6, $zero, 0x4
    ctx->r22 = ADD32(0, 0X4);
    // 0x800BB5B0: lw          $s2, 0x44($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X44);
    // 0x800BB5B4: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
L_800BB5B8:
    // 0x800BB5B8: beql        $s4, $s6, L_800BB670
    if (ctx->r20 == ctx->r22) {
        // 0x800BB5BC: lw          $ra, 0x3C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X3C);
            goto L_800BB670;
    }
    goto skip_0;
    // 0x800BB5BC: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    skip_0:
    // 0x800BB5C0: beq         $s4, $zero, L_800BB5E8
    if (ctx->r20 == 0) {
        // 0x800BB5C4: nop
    
            goto L_800BB5E8;
    }
    // 0x800BB5C4: nop

    // 0x800BB5C8: beq         $s4, $s7, L_800BB5F8
    if (ctx->r20 == ctx->r23) {
        // 0x800BB5CC: nop
    
            goto L_800BB5F8;
    }
    // 0x800BB5CC: nop

    // 0x800BB5D0: beq         $s4, $fp, L_800BB608
    if (ctx->r20 == ctx->r30) {
        // 0x800BB5D4: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800BB608;
    }
    // 0x800BB5D4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800BB5D8: beq         $s4, $at, L_800BB618
    if (ctx->r20 == ctx->r1) {
        // 0x800BB5DC: nop
    
            goto L_800BB618;
    }
    // 0x800BB5DC: nop

    // 0x800BB5E0: b           L_800BB628
    // 0x800BB5E4: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
        goto L_800BB628;
    // 0x800BB5E4: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
L_800BB5E8:
    // 0x800BB5E8: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BB5EC: addiu       $s1, $s1, 0x4760
    ctx->r17 = ADD32(ctx->r17, 0X4760);
    // 0x800BB5F0: b           L_800BB624
    // 0x800BB5F4: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
        goto L_800BB624;
    // 0x800BB5F4: or          $s2, $s5, $zero
    ctx->r18 = ctx->r21 | 0;
L_800BB5F8:
    // 0x800BB5F8: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BB5FC: addiu       $s1, $s1, 0x4770
    ctx->r17 = ADD32(ctx->r17, 0X4770);
    // 0x800BB600: b           L_800BB624
    // 0x800BB604: addiu       $s2, $s5, 0x10
    ctx->r18 = ADD32(ctx->r21, 0X10);
        goto L_800BB624;
    // 0x800BB604: addiu       $s2, $s5, 0x10
    ctx->r18 = ADD32(ctx->r21, 0X10);
L_800BB608:
    // 0x800BB608: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BB60C: addiu       $s1, $s1, 0x4780
    ctx->r17 = ADD32(ctx->r17, 0X4780);
    // 0x800BB610: b           L_800BB624
    // 0x800BB614: addiu       $s2, $s5, 0x20
    ctx->r18 = ADD32(ctx->r21, 0X20);
        goto L_800BB624;
    // 0x800BB614: addiu       $s2, $s5, 0x20
    ctx->r18 = ADD32(ctx->r21, 0X20);
L_800BB618:
    // 0x800BB618: lui         $s1, 0x8004
    ctx->r17 = S32(0X8004 << 16);
    // 0x800BB61C: addiu       $s1, $s1, 0x4790
    ctx->r17 = ADD32(ctx->r17, 0X4790);
    // 0x800BB620: addiu       $s2, $s5, 0x30
    ctx->r18 = ADD32(ctx->r21, 0X30);
L_800BB624:
    // 0x800BB624: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
L_800BB628:
    // 0x800BB628: beql        $at, $zero, L_800BB65C
    if (ctx->r1 == 0) {
        // 0x800BB62C: slt         $at, $s0, $s3
        ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
            goto L_800BB65C;
    }
    goto skip_1;
    // 0x800BB62C: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
    skip_1:
L_800BB630:
    // 0x800BB630: jal         0x800BCFEC
    // 0x800BB634: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    AudioSeq_AudioListPopBack(rdram, ctx);
        goto after_1;
    // 0x800BB634: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_1:
    // 0x800BB638: beq         $v0, $zero, L_800BB658
    if (ctx->r2 == 0) {
        // 0x800BB63C: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800BB658;
    }
    // 0x800BB63C: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800BB640: jal         0x800BCFAC
    // 0x800BB644: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    AudioSeq_AudioListPushBack(rdram, ctx);
        goto after_2;
    // 0x800BB644: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    after_2:
    // 0x800BB648: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800BB64C: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
    // 0x800BB650: bne         $at, $zero, L_800BB630
    if (ctx->r1 != 0) {
        // 0x800BB654: nop
    
            goto L_800BB630;
    }
    // 0x800BB654: nop

L_800BB658:
    // 0x800BB658: slt         $at, $s0, $s3
    ctx->r1 = SIGNED(ctx->r16) < SIGNED(ctx->r19) ? 1 : 0;
L_800BB65C:
    // 0x800BB65C: bne         $at, $zero, L_800BB5B8
    if (ctx->r1 != 0) {
        // 0x800BB660: addiu       $s4, $s4, 0x1
        ctx->r20 = ADD32(ctx->r20, 0X1);
            goto L_800BB5B8;
    }
    // 0x800BB660: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x800BB664: sw          $s2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r18;
    // 0x800BB668: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
L_800BB66C:
    // 0x800BB66C: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_800BB670:
    // 0x800BB670: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800BB674: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800BB678: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800BB67C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800BB680: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800BB684: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800BB688: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800BB68C: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800BB690: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800BB694: jr          $ra
    // 0x800BB698: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x800BB698: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void Audio_AudioListPushFront(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB69C: lw          $t6, 0x0($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X0);
    // 0x800BB6A0: bne         $t6, $zero, L_800BB6D4
    if (ctx->r14 != 0) {
        // 0x800BB6A4: nop
    
            goto L_800BB6D4;
    }
    // 0x800BB6A4: nop

    // 0x800BB6A8: sw          $a0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r4;
    // 0x800BB6AC: lw          $t7, 0x4($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X4);
    // 0x800BB6B0: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x800BB6B4: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x800BB6B8: sw          $a1, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r5;
    // 0x800BB6BC: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x800BB6C0: lw          $t1, 0xC($a0)
    ctx->r9 = MEM_W(ctx->r4, 0XC);
    // 0x800BB6C4: sw          $a1, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r5;
    // 0x800BB6C8: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x800BB6CC: sw          $t0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r8;
    // 0x800BB6D0: sw          $t1, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r9;
L_800BB6D4:
    // 0x800BB6D4: jr          $ra
    // 0x800BB6D8: nop

    return;
    // 0x800BB6D8: nop

;}
RECOMP_FUNC void Audio_AudioListRemove(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800BB6DC: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800BB6E0: beq         $v0, $zero, L_800BB700
    if (ctx->r2 == 0) {
        // 0x800BB6E4: nop
    
            goto L_800BB700;
    }
    // 0x800BB6E4: nop

    // 0x800BB6E8: lw          $t6, 0x4($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X4);
    // 0x800BB6EC: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x800BB6F0: lw          $t7, 0x0($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X0);
    // 0x800BB6F4: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x800BB6F8: sw          $t7, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r15;
    // 0x800BB6FC: sw          $zero, 0x0($a0)
    MEM_W(0X0, ctx->r4) = 0;
L_800BB700:
    // 0x800BB700: jr          $ra
    // 0x800BB704: nop

    return;
    // 0x800BB704: nop

;}
