#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void AudioThread_QueueCmdS32(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C53B0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C53B4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C53B8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C53BC: jal         0x800C5354
    // 0x800C53C0: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    AudioThread_QueueCmd(rdram, ctx);
        goto after_0;
    // 0x800C53C0: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    after_0:
    // 0x800C53C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C53C8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C53CC: jr          $ra
    // 0x800C53D0: nop

    return;
    // 0x800C53D0: nop

;}
RECOMP_FUNC void AudioThread_QueueCmdS8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern int wr64_free_ride_skip_audio(const uint8_t*, uint32_t); if (wr64_free_ride_skip_audio(rdram, (uint32_t)ctx->r4)) return; }
    // 0x800C53D4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C53D8: or          $t6, $a1, $zero
    ctx->r14 = ctx->r5 | 0;
    // 0x800C53DC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C53E0: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800C53E4: sll         $t7, $t6, 24
    ctx->r15 = S32(ctx->r14 << 24);
    // 0x800C53E8: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x800C53EC: jal         0x800C5354
    // 0x800C53F0: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    AudioThread_QueueCmd(rdram, ctx);
        goto after_0;
    // 0x800C53F0: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    after_0:
    // 0x800C53F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C53F8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C53FC: jr          $ra
    // 0x800C5400: nop

    return;
    // 0x800C5400: nop

;}
RECOMP_FUNC void AudioThread_ScheduleProcessCmds(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C5404: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x800C5408: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800C540C: lbu         $v1, -0x7A0C($v1)
    ctx->r3 = MEM_BU(ctx->r3, -0X7A0C);
    // 0x800C5410: lbu         $v0, -0x7A10($v0)
    ctx->r2 = MEM_BU(ctx->r2, -0X7A10);
    // 0x800C5414: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800C5418: lw          $t7, -0x7950($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X7950);
    // 0x800C541C: subu        $a0, $v0, $v1
    ctx->r4 = SUB32(ctx->r2, ctx->r3);
    // 0x800C5420: addiu       $a0, $a0, 0x100
    ctx->r4 = ADD32(ctx->r4, 0X100);
    // 0x800C5424: andi        $t6, $a0, 0xFF
    ctx->r14 = ctx->r4 & 0XFF;
    // 0x800C5428: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C542C: slt         $at, $t7, $t6
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x800C5430: beq         $at, $zero, L_800C5440
    if (ctx->r1 == 0) {
        // 0x800C5434: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C5440;
    }
    // 0x800C5434: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C5438: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C543C: sw          $t6, -0x7950($at)
    MEM_W(-0X7950, ctx->r1) = ctx->r14;
L_800C5440:
    // 0x800C5440: andi        $t8, $v1, 0xFF
    ctx->r24 = ctx->r3 & 0XFF;
    // 0x800C5444: sll         $t9, $t8, 8
    ctx->r25 = S32(ctx->r24 << 8);
    // 0x800C5448: andi        $t0, $v0, 0xFF
    ctx->r8 = ctx->r2 & 0XFF;
    // 0x800C544C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C5450: or          $a1, $t9, $t0
    ctx->r5 = ctx->r25 | ctx->r8;
    // 0x800C5454: lw          $a0, -0x7A04($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A04);
    // 0x800C5458: jal         0x800C57A0
    // 0x800C545C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osSendMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x800C545C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_0:
    // 0x800C5460: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C5464: lui         $t1, 0x800F
    ctx->r9 = S32(0X800F << 16);
    // 0x800C5468: lbu         $t1, -0x7A10($t1)
    ctx->r9 = MEM_BU(ctx->r9, -0X7A10);
    // 0x800C546C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C5470: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C5474: jr          $ra
    // 0x800C5478: sb          $t1, -0x7A0C($at)
    MEM_B(-0X7A0C, ctx->r1) = ctx->r9;
    return;
    // 0x800C5478: sb          $t1, -0x7A0C($at)
    MEM_B(-0X7A0C, ctx->r1) = ctx->r9;
;}
RECOMP_FUNC void AudioThread_ProcessCmds(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C547C: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800C5480: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800C5484: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800C5488: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800C548C: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800C5490: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800C5494: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800C5498: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800C549C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800C54A0: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800C54A4: srl         $t6, $a0, 8
    ctx->r14 = S32(U32(ctx->r4) >> 8);
    // 0x800C54A8: andi        $t8, $s2, 0xFF
    ctx->r24 = ctx->r18 & 0XFF;
    // 0x800C54AC: lui         $s3, 0x801D
    ctx->r19 = S32(0X801D << 16);
    // 0x800C54B0: lui         $s4, 0x8004
    ctx->r20 = S32(0X8004 << 16);
    // 0x800C54B4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800C54B8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C54BC: andi        $s1, $t6, 0xFF
    ctx->r17 = ctx->r14 & 0XFF;
    // 0x800C54C0: addiu       $s4, $s4, -0x338
    ctx->r20 = ADD32(ctx->r20, -0X338);
    // 0x800C54C4: addiu       $s3, $s3, 0x7E90
    ctx->r19 = ADD32(ctx->r19, 0X7E90);
    // 0x800C54C8: or          $s2, $t8, $zero
    ctx->r18 = ctx->r24 | 0;
    // 0x800C54CC: addiu       $s5, $zero, 0x140
    ctx->r21 = ADD32(0, 0X140);
    // 0x800C54D0: addiu       $s6, $zero, 0x41
    ctx->r22 = ADD32(0, 0X41);
    // 0x800C54D4: addiu       $s7, $zero, 0x46
    ctx->r23 = ADD32(0, 0X46);
    // 0x800C54D8: addiu       $fp, $zero, 0x47
    ctx->r30 = ADD32(0, 0X47);
    // 0x800C54DC: beq         $s2, $s1, L_800C56C4
    if (ctx->r18 == ctx->r17) {
        // 0x800C54E0: or          $v0, $s1, $zero
        ctx->r2 = ctx->r17 | 0;
            goto L_800C56C4;
    }
    // 0x800C54E0: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_800C54E4:
    // 0x800C54E4: andi        $t9, $v0, 0xFF
    ctx->r25 = ctx->r2 & 0XFF;
    // 0x800C54E8: sll         $t0, $t9, 3
    ctx->r8 = S32(ctx->r25 << 3);
    // 0x800C54EC: addu        $s0, $s3, $t0
    ctx->r16 = ADD32(ctx->r19, ctx->r8);
    // 0x800C54F0: lbu         $a1, 0x1($s0)
    ctx->r5 = MEM_BU(ctx->r16, 0X1);
    // 0x800C54F4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800C54F8: andi        $t1, $s1, 0xFF
    ctx->r9 = ctx->r17 & 0XFF;
    // 0x800C54FC: slti        $at, $a1, 0x4
    ctx->r1 = SIGNED(ctx->r5) < 0X4 ? 1 : 0;
    // 0x800C5500: beq         $at, $zero, L_800C56B8
    if (ctx->r1 == 0) {
        // 0x800C5504: or          $s1, $t1, $zero
        ctx->r17 = ctx->r9 | 0;
            goto L_800C56B8;
    }
    // 0x800C5504: or          $s1, $t1, $zero
    ctx->r17 = ctx->r9 | 0;
    // 0x800C5508: multu       $a1, $s5
    result = U64(U32(ctx->r5)) * U64(U32(ctx->r21)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800C550C: lbu         $a0, 0x0($s0)
    ctx->r4 = MEM_BU(ctx->r16, 0X0);
    // 0x800C5510: andi        $t3, $a0, 0x80
    ctx->r11 = ctx->r4 & 0X80;
    // 0x800C5514: andi        $t4, $a0, 0x40
    ctx->r12 = ctx->r4 & 0X40;
    // 0x800C5518: mflo        $t2
    ctx->r10 = lo;
    // 0x800C551C: addu        $v1, $s4, $t2
    ctx->r3 = ADD32(ctx->r20, ctx->r10);
    // 0x800C5520: beq         $t3, $zero, L_800C5538
    if (ctx->r11 == 0) {
        // 0x800C5524: nop
    
            goto L_800C5538;
    }
    // 0x800C5524: nop

    // 0x800C5528: jal         0x800C5088
    // 0x800C552C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    AudioThread_ProcessGlobalCmd(rdram, ctx);
        goto after_0;
    // 0x800C552C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x800C5530: b           L_800C56BC
    // 0x800C5534: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
        goto L_800C56BC;
    // 0x800C5534: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_800C5538:
    // 0x800C5538: beql        $t4, $zero, L_800C55BC
    if (ctx->r12 == 0) {
        // 0x800C553C: lw          $t4, 0x0($v1)
        ctx->r12 = MEM_W(ctx->r3, 0X0);
            goto L_800C55BC;
    }
    goto skip_0;
    // 0x800C553C: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    skip_0:
    // 0x800C5540: beql        $a0, $s6, L_800C556C
    if (ctx->r4 == ctx->r22) {
        // 0x800C5544: lbu         $t6, 0x0($v1)
        ctx->r14 = MEM_BU(ctx->r3, 0X0);
            goto L_800C556C;
    }
    goto skip_1;
    // 0x800C5544: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    skip_1:
    // 0x800C5548: beql        $a0, $s7, L_800C55A8
    if (ctx->r4 == ctx->r23) {
        // 0x800C554C: lbu         $t2, 0x3($s0)
        ctx->r10 = MEM_BU(ctx->r16, 0X3);
            goto L_800C55A8;
    }
    goto skip_2;
    // 0x800C554C: lbu         $t2, 0x3($s0)
    ctx->r10 = MEM_BU(ctx->r16, 0X3);
    skip_2:
    // 0x800C5550: beq         $a0, $fp, L_800C5580
    if (ctx->r4 == ctx->r30) {
        // 0x800C5554: addiu       $at, $zero, 0x48
        ctx->r1 = ADD32(0, 0X48);
            goto L_800C5580;
    }
    // 0x800C5554: addiu       $at, $zero, 0x48
    ctx->r1 = ADD32(0, 0X48);
    // 0x800C5558: beql        $a0, $at, L_800C559C
    if (ctx->r4 == ctx->r1) {
        // 0x800C555C: lb          $t0, 0x4($s0)
        ctx->r8 = MEM_B(ctx->r16, 0X4);
            goto L_800C559C;
    }
    goto skip_3;
    // 0x800C555C: lb          $t0, 0x4($s0)
    ctx->r8 = MEM_B(ctx->r16, 0X4);
    skip_3:
    // 0x800C5560: b           L_800C56BC
    // 0x800C5564: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
        goto L_800C56BC;
    // 0x800C5564: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x800C5568: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
L_800C556C:
    // 0x800C556C: lwc1        $f4, 0x4($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X4);
    // 0x800C5570: ori         $t7, $t6, 0x4
    ctx->r15 = ctx->r14 | 0X4;
    // 0x800C5574: sb          $t7, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r15;
    // 0x800C5578: b           L_800C56B8
    // 0x800C557C: swc1        $f4, 0x28($v1)
    MEM_W(0X28, ctx->r3) = ctx->f4.u32l;
        goto L_800C56B8;
    // 0x800C557C: swc1        $f4, 0x28($v1)
    MEM_W(0X28, ctx->r3) = ctx->f4.u32l;
L_800C5580:
    // 0x800C5580: lw          $t8, 0x4($s0)
    ctx->r24 = MEM_W(ctx->r16, 0X4);
    // 0x800C5584: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x800C5588: subu        $t9, $t9, $t8
    ctx->r25 = SUB32(ctx->r25, ctx->r24);
    // 0x800C558C: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x800C5590: b           L_800C56B8
    // 0x800C5594: sh          $t9, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r25;
        goto L_800C56B8;
    // 0x800C5594: sh          $t9, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r25;
    // 0x800C5598: lb          $t0, 0x4($s0)
    ctx->r8 = MEM_B(ctx->r16, 0X4);
L_800C559C:
    // 0x800C559C: b           L_800C56B8
    // 0x800C55A0: sh          $t0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r8;
        goto L_800C56B8;
    // 0x800C55A0: sh          $t0, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r8;
    // 0x800C55A4: lbu         $t2, 0x3($s0)
    ctx->r10 = MEM_BU(ctx->r16, 0X3);
L_800C55A8:
    // 0x800C55A8: lb          $t1, 0x4($s0)
    ctx->r9 = MEM_B(ctx->r16, 0X4);
    // 0x800C55AC: addu        $t3, $v1, $t2
    ctx->r11 = ADD32(ctx->r3, ctx->r10);
    // 0x800C55B0: b           L_800C56B8
    // 0x800C55B4: sb          $t1, 0x7($t3)
    MEM_B(0X7, ctx->r11) = ctx->r9;
        goto L_800C56B8;
    // 0x800C55B4: sb          $t1, 0x7($t3)
    MEM_B(0X7, ctx->r11) = ctx->r9;
    // 0x800C55B8: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
L_800C55BC:
    // 0x800C55BC: srl         $t5, $t4, 31
    ctx->r13 = S32(U32(ctx->r12) >> 31);
    // 0x800C55C0: beql        $t5, $zero, L_800C56BC
    if (ctx->r13 == 0) {
        // 0x800C55C4: or          $v0, $s1, $zero
        ctx->r2 = ctx->r17 | 0;
            goto L_800C56BC;
    }
    goto skip_4;
    // 0x800C55C4: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    skip_4:
    // 0x800C55C8: lbu         $a1, 0x2($s0)
    ctx->r5 = MEM_BU(ctx->r16, 0X2);
    // 0x800C55CC: slti        $at, $a1, 0x10
    ctx->r1 = SIGNED(ctx->r5) < 0X10 ? 1 : 0;
    // 0x800C55D0: beq         $at, $zero, L_800C56B8
    if (ctx->r1 == 0) {
        // 0x800C55D4: sll         $t6, $a1, 2
        ctx->r14 = S32(ctx->r5 << 2);
            goto L_800C56B8;
    }
    // 0x800C55D4: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x800C55D8: addu        $t7, $v1, $t6
    ctx->r15 = ADD32(ctx->r3, ctx->r14);
    // 0x800C55DC: lw          $v0, 0x30($t7)
    ctx->r2 = MEM_W(ctx->r15, 0X30);
    // 0x800C55E0: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C55E4: addiu       $t8, $t8, 0x4688
    ctx->r24 = ADD32(ctx->r24, 0X4688);
    // 0x800C55E8: beq         $v0, $t8, L_800C56B8
    if (ctx->r2 == ctx->r24) {
        // 0x800C55EC: addiu       $t9, $a0, -0x1
        ctx->r25 = ADD32(ctx->r4, -0X1);
            goto L_800C56B8;
    }
    // 0x800C55EC: addiu       $t9, $a0, -0x1
    ctx->r25 = ADD32(ctx->r4, -0X1);
    // 0x800C55F0: sltiu       $at, $t9, 0x8
    ctx->r1 = ctx->r25 < 0X8 ? 1 : 0;
    // 0x800C55F4: beq         $at, $zero, L_800C56B8
    if (ctx->r1 == 0) {
        // 0x800C55F8: sll         $t9, $t9, 2
        ctx->r25 = S32(ctx->r25 << 2);
            goto L_800C56B8;
    }
    // 0x800C55F8: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x800C55FC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C5600: addu        $at, $at, $t9
    gpr jr_addend_800C5608 = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x800C5604: lw          $t9, -0x3A50($at)
    ctx->r25 = ADD32(ctx->r1, -0X3A50);
    // 0x800C5608: jr          $t9
    // 0x800C560C: nop

    switch (jr_addend_800C5608 >> 2) {
        case 0: goto L_800C5610; break;
        case 1: goto L_800C5628; break;
        case 2: goto L_800C5640; break;
        case 3: goto L_800C5658; break;
        case 4: goto L_800C5670; break;
        case 5: goto L_800C567C; break;
        case 6: goto L_800C56B8; break;
        case 7: goto L_800C569C; break;
        default: switch_error(__func__, 0x800C5608, 0x800EC5B0);
    }
    // 0x800C560C: nop

L_800C5610:
    // 0x800C5610: lbu         $t2, 0x1($v0)
    ctx->r10 = MEM_BU(ctx->r2, 0X1);
    // 0x800C5614: lwc1        $f6, 0x4($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X4);
    // 0x800C5618: ori         $t1, $t2, 0x40
    ctx->r9 = ctx->r10 | 0X40;
    // 0x800C561C: sb          $t1, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r9;
    // 0x800C5620: b           L_800C56B8
    // 0x800C5624: swc1        $f6, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f6.u32l;
        goto L_800C56B8;
    // 0x800C5624: swc1        $f6, 0x20($v0)
    MEM_W(0X20, ctx->r2) = ctx->f6.u32l;
L_800C5628:
    // 0x800C5628: lbu         $t4, 0x1($v0)
    ctx->r12 = MEM_BU(ctx->r2, 0X1);
    // 0x800C562C: lwc1        $f8, 0x4($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X4);
    // 0x800C5630: ori         $t5, $t4, 0x40
    ctx->r13 = ctx->r12 | 0X40;
    // 0x800C5634: sb          $t5, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r13;
    // 0x800C5638: b           L_800C56B8
    // 0x800C563C: swc1        $f8, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f8.u32l;
        goto L_800C56B8;
    // 0x800C563C: swc1        $f8, 0x24($v0)
    MEM_W(0X24, ctx->r2) = ctx->f8.u32l;
L_800C5640:
    // 0x800C5640: lbu         $t8, 0x1($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X1);
    // 0x800C5644: lb          $t6, 0x4($s0)
    ctx->r14 = MEM_B(ctx->r16, 0X4);
    // 0x800C5648: ori         $t9, $t8, 0x20
    ctx->r25 = ctx->r24 | 0X20;
    // 0x800C564C: sb          $t9, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r25;
    // 0x800C5650: b           L_800C56B8
    // 0x800C5654: sb          $t6, 0x9($v0)
    MEM_B(0X9, ctx->r2) = ctx->r14;
        goto L_800C56B8;
    // 0x800C5654: sb          $t6, 0x9($v0)
    MEM_B(0X9, ctx->r2) = ctx->r14;
L_800C5658:
    // 0x800C5658: lbu         $t2, 0x1($v0)
    ctx->r10 = MEM_BU(ctx->r2, 0X1);
    // 0x800C565C: lwc1        $f10, 0x4($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X4);
    // 0x800C5660: ori         $t1, $t2, 0x80
    ctx->r9 = ctx->r10 | 0X80;
    // 0x800C5664: sb          $t1, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r9;
    // 0x800C5668: b           L_800C56B8
    // 0x800C566C: swc1        $f10, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f10.u32l;
        goto L_800C56B8;
    // 0x800C566C: swc1        $f10, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f10.u32l;
L_800C5670:
    // 0x800C5670: lb          $t3, 0x4($s0)
    ctx->r11 = MEM_B(ctx->r16, 0X4);
    // 0x800C5674: b           L_800C56B8
    // 0x800C5678: sb          $t3, 0x4($v0)
    MEM_B(0X4, ctx->r2) = ctx->r11;
        goto L_800C56B8;
    // 0x800C5678: sb          $t3, 0x4($v0)
    MEM_B(0X4, ctx->r2) = ctx->r11;
L_800C567C:
    // 0x800C567C: lbu         $v1, 0x3($s0)
    ctx->r3 = MEM_BU(ctx->r16, 0X3);
    // 0x800C5680: slti        $at, $v1, 0x8
    ctx->r1 = SIGNED(ctx->r3) < 0X8 ? 1 : 0;
    // 0x800C5684: beql        $at, $zero, L_800C56BC
    if (ctx->r1 == 0) {
        // 0x800C5688: or          $v0, $s1, $zero
        ctx->r2 = ctx->r17 | 0;
            goto L_800C56BC;
    }
    goto skip_5;
    // 0x800C5688: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    skip_5:
    // 0x800C568C: lb          $t4, 0x4($s0)
    ctx->r12 = MEM_B(ctx->r16, 0X4);
    // 0x800C5690: addu        $t5, $v0, $v1
    ctx->r13 = ADD32(ctx->r2, ctx->r3);
    // 0x800C5694: b           L_800C56B8
    // 0x800C5698: sb          $t4, 0x58($t5)
    MEM_B(0X58, ctx->r13) = ctx->r12;
        goto L_800C56B8;
    // 0x800C5698: sb          $t4, 0x58($t5)
    MEM_B(0X58, ctx->r13) = ctx->r12;
L_800C569C:
    // 0x800C569C: lb          $t7, 0x4($s0)
    ctx->r15 = MEM_B(ctx->r16, 0X4);
    // 0x800C56A0: lbu         $t0, 0x0($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X0);
    // 0x800C56A4: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x800C56A8: andi        $t9, $t8, 0x10
    ctx->r25 = ctx->r24 & 0X10;
    // 0x800C56AC: andi        $t2, $t0, 0xFFEF
    ctx->r10 = ctx->r8 & 0XFFEF;
    // 0x800C56B0: or          $t1, $t9, $t2
    ctx->r9 = ctx->r25 | ctx->r10;
    // 0x800C56B4: sb          $t1, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r9;
L_800C56B8:
    // 0x800C56B8: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
L_800C56BC:
    // 0x800C56BC: bne         $s2, $s1, L_800C54E4
    if (ctx->r18 != ctx->r17) {
        // 0x800C56C0: sb          $zero, 0x0($s0)
        MEM_B(0X0, ctx->r16) = 0;
            goto L_800C54E4;
    }
    // 0x800C56C0: sb          $zero, 0x0($s0)
    MEM_B(0X0, ctx->r16) = 0;
L_800C56C4:
    // 0x800C56C4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800C56C8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C56CC: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800C56D0: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800C56D4: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800C56D8: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800C56DC: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800C56E0: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800C56E4: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800C56E8: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800C56EC: jr          $ra
    // 0x800C56F0: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800C56F0: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void AudioThread_Init(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C56F4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C56F8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C56FC: jal         0x800C52CC
    // 0x800C5700: nop

    AudioThread_InitQueues(rdram, ctx);
        goto after_0;
    // 0x800C5700: nop

    after_0:
    // 0x800C5704: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C5708: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C570C: jr          $ra
    // 0x800C5710: nop

    return;
    // 0x800C5710: nop

    // 0x800C5714: nop

    // 0x800C5718: nop

    // 0x800C571C: nop

;}
RECOMP_FUNC void _VirtualToPhysicalTask(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C6040: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C6044: lui         $t6, 0x801E
    ctx->r14 = S32(0X801E << 16);
    // 0x800C6048: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C604C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800C6050: addiu       $t6, $t6, -0x7950
    ctx->r14 = ADD32(ctx->r14, -0X7950);
    // 0x800C6054: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x800C6058: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x800C605C: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800C6060: jal         0x800CBA80
    // 0x800C6064: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    bcopy_recomp(rdram, ctx);
        goto after_0;
    // 0x800C6064: addiu       $a2, $zero, 0x40
    ctx->r6 = ADD32(0, 0X40);
    after_0:
    // 0x800C6068: lw          $t7, 0x1C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1C);
    // 0x800C606C: lw          $t8, 0x10($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X10);
    // 0x800C6070: beq         $t8, $zero, L_800C6088
    if (ctx->r24 == 0) {
        // 0x800C6074: nop
    
            goto L_800C6088;
    }
    // 0x800C6074: nop

    // 0x800C6078: jal         0x800C5720
    // 0x800C607C: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_1;
    // 0x800C607C: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    after_1:
    // 0x800C6080: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x800C6084: sw          $v0, 0x10($t9)
    MEM_W(0X10, ctx->r25) = ctx->r2;
L_800C6088:
    // 0x800C6088: lw          $t0, 0x1C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X1C);
    // 0x800C608C: lw          $t1, 0x18($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X18);
    // 0x800C6090: beq         $t1, $zero, L_800C60A8
    if (ctx->r9 == 0) {
        // 0x800C6094: nop
    
            goto L_800C60A8;
    }
    // 0x800C6094: nop

    // 0x800C6098: jal         0x800C5720
    // 0x800C609C: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_2;
    // 0x800C609C: or          $a0, $t1, $zero
    ctx->r4 = ctx->r9 | 0;
    after_2:
    // 0x800C60A0: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60A4: sw          $v0, 0x18($t2)
    MEM_W(0X18, ctx->r10) = ctx->r2;
L_800C60A8:
    // 0x800C60A8: lw          $t3, 0x1C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60AC: lw          $t4, 0x20($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X20);
    // 0x800C60B0: beq         $t4, $zero, L_800C60C8
    if (ctx->r12 == 0) {
        // 0x800C60B4: nop
    
            goto L_800C60C8;
    }
    // 0x800C60B4: nop

    // 0x800C60B8: jal         0x800C5720
    // 0x800C60BC: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_3;
    // 0x800C60BC: or          $a0, $t4, $zero
    ctx->r4 = ctx->r12 | 0;
    after_3:
    // 0x800C60C0: lw          $t5, 0x1C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60C4: sw          $v0, 0x20($t5)
    MEM_W(0X20, ctx->r13) = ctx->r2;
L_800C60C8:
    // 0x800C60C8: lw          $t6, 0x1C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60CC: lw          $t7, 0x28($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X28);
    // 0x800C60D0: beq         $t7, $zero, L_800C60E8
    if (ctx->r15 == 0) {
        // 0x800C60D4: nop
    
            goto L_800C60E8;
    }
    // 0x800C60D4: nop

    // 0x800C60D8: jal         0x800C5720
    // 0x800C60DC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_4;
    // 0x800C60DC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    after_4:
    // 0x800C60E0: lw          $t8, 0x1C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60E4: sw          $v0, 0x28($t8)
    MEM_W(0X28, ctx->r24) = ctx->r2;
L_800C60E8:
    // 0x800C60E8: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x800C60EC: lw          $t0, 0x2C($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X2C);
    // 0x800C60F0: beq         $t0, $zero, L_800C6108
    if (ctx->r8 == 0) {
        // 0x800C60F4: nop
    
            goto L_800C6108;
    }
    // 0x800C60F4: nop

    // 0x800C60F8: jal         0x800C5720
    // 0x800C60FC: or          $a0, $t0, $zero
    ctx->r4 = ctx->r8 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_5;
    // 0x800C60FC: or          $a0, $t0, $zero
    ctx->r4 = ctx->r8 | 0;
    after_5:
    // 0x800C6100: lw          $t1, 0x1C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X1C);
    // 0x800C6104: sw          $v0, 0x2C($t1)
    MEM_W(0X2C, ctx->r9) = ctx->r2;
L_800C6108:
    // 0x800C6108: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
    // 0x800C610C: lw          $t3, 0x30($t2)
    ctx->r11 = MEM_W(ctx->r10, 0X30);
    // 0x800C6110: beq         $t3, $zero, L_800C6128
    if (ctx->r11 == 0) {
        // 0x800C6114: nop
    
            goto L_800C6128;
    }
    // 0x800C6114: nop

    // 0x800C6118: jal         0x800C5720
    // 0x800C611C: or          $a0, $t3, $zero
    ctx->r4 = ctx->r11 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_6;
    // 0x800C611C: or          $a0, $t3, $zero
    ctx->r4 = ctx->r11 | 0;
    after_6:
    // 0x800C6120: lw          $t4, 0x1C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X1C);
    // 0x800C6124: sw          $v0, 0x30($t4)
    MEM_W(0X30, ctx->r12) = ctx->r2;
L_800C6128:
    // 0x800C6128: lw          $t5, 0x1C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X1C);
    // 0x800C612C: lw          $t6, 0x38($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X38);
    // 0x800C6130: beq         $t6, $zero, L_800C6148
    if (ctx->r14 == 0) {
        // 0x800C6134: nop
    
            goto L_800C6148;
    }
    // 0x800C6134: nop

    // 0x800C6138: jal         0x800C5720
    // 0x800C613C: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_7;
    // 0x800C613C: or          $a0, $t6, $zero
    ctx->r4 = ctx->r14 | 0;
    after_7:
    // 0x800C6140: lw          $t7, 0x1C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1C);
    // 0x800C6144: sw          $v0, 0x38($t7)
    MEM_W(0X38, ctx->r15) = ctx->r2;
L_800C6148:
    // 0x800C6148: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C614C: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800C6150: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C6154: jr          $ra
    // 0x800C6158: nop

    return;
    // 0x800C6158: nop

;}
RECOMP_FUNC void _nsqrtf(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C7010: jr          $ra
    // 0x800C7014: sqrt.s      $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = sqrtf(ctx->f12.fl);
    return;
    // 0x800C7014: sqrt.s      $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = sqrtf(ctx->f12.fl);
    // 0x800C7018: nop

    // 0x800C701C: nop

;}
RECOMP_FUNC void func_800C7380(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C7380: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C7384: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C7388: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C738C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C7390: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x800C7394: jal         0x800CCC00
    // 0x800C7398: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800CCC00(rdram, ctx);
        goto after_0;
    // 0x800C7398: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800C739C: lwc1        $f4, 0x20($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800C73A0: lwc1        $f6, 0x1C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800C73A4: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800C73A8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C73AC: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800C73B0: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x800C73B4: lwc1        $f14, 0x28($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X28);
    // 0x800C73B8: lwc1        $f16, 0x30($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X30);
    // 0x800C73BC: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800C73C0: lwc1        $f18, 0x2C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x800C73C4: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C73C8: lui         $at, 0xC000
    ctx->r1 = S32(0XC000 << 16);
    // 0x800C73CC: sub.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x800C73D0: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800C73D4: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x800C73D8: swc1        $f10, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f10.u32l;
    // 0x800C73DC: lwc1        $f4, 0x24($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800C73E0: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800C73E4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C73E8: sub.s       $f2, $f14, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f14.fl - ctx->f4.fl;
    // 0x800C73EC: div.s       $f4, $f10, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f12.fl);
    // 0x800C73F0: div.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800C73F4: swc1        $f4, 0x28($v0)
    MEM_W(0X28, ctx->r2) = ctx->f4.u32l;
    // 0x800C73F8: swc1        $f8, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->f8.u32l;
    // 0x800C73FC: lwc1        $f8, 0x1C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800C7400: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800C7404: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7408: neg.s       $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = -ctx->f10.fl;
    // 0x800C740C: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800C7410: swc1        $f6, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->f6.u32l;
    // 0x800C7414: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800C7418: add.s       $f10, $f14, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f14.fl + ctx->f8.fl;
    // 0x800C741C: add.s       $f8, $f16, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x800C7420: neg.s       $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = -ctx->f10.fl;
    // 0x800C7424: neg.s       $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = -ctx->f8.fl;
    // 0x800C7428: div.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800C742C: div.s       $f4, $f10, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = DIV_S(ctx->f10.fl, ctx->f12.fl);
    // 0x800C7430: swc1        $f6, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->f6.u32l;
    // 0x800C7434: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C7438: nop

    // 0x800C743C: swc1        $f6, 0x3C($v0)
    MEM_W(0X3C, ctx->r2) = ctx->f6.u32l;
    // 0x800C7440: swc1        $f4, 0x38($v0)
    MEM_W(0X38, ctx->r2) = ctx->f4.u32l;
    // 0x800C7444: lwc1        $f0, 0x34($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X34);
    // 0x800C7448: lwc1        $f8, 0x0($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X0);
    // 0x800C744C: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800C7450: lwc1        $f18, 0x4($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X4);
    // 0x800C7454: mul.s       $f12, $f8, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800C7458: lwc1        $f14, 0x8($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X8);
    // 0x800C745C: beq         $v1, $a0, L_800C74A0
    if (ctx->r3 == ctx->r4) {
        // 0x800C7460: lwc1        $f16, 0xC($v0)
        ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
            goto L_800C74A0;
    }
    // 0x800C7460: lwc1        $f16, 0xC($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0XC);
L_800C7464:
    // 0x800C7464: mul.s       $f10, $f18, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800C7468: lwc1        $f8, 0x10($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X10);
    // 0x800C746C: lwc1        $f18, 0x14($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0X14);
    // 0x800C7470: mul.s       $f6, $f14, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800C7474: lwc1        $f14, 0x18($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X18);
    // 0x800C7478: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800C747C: mul.s       $f4, $f16, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x800C7480: lwc1        $f16, 0x1C($v0)
    ctx->f16.u32l = MEM_W(ctx->r2, 0X1C);
    // 0x800C7484: swc1        $f12, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->f12.u32l;
    // 0x800C7488: mul.s       $f12, $f8, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f12.fl = MUL_S(ctx->f8.fl, ctx->f0.fl);
    // 0x800C748C: swc1        $f10, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->f10.u32l;
    // 0x800C7490: swc1        $f6, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->f6.u32l;
    // 0x800C7494: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x800C7498: bne         $v1, $a0, L_800C7464
    if (ctx->r3 != ctx->r4) {
        // 0x800C749C: swc1        $f4, -0x4($v0)
        MEM_W(-0X4, ctx->r2) = ctx->f4.u32l;
            goto L_800C7464;
    }
    // 0x800C749C: swc1        $f4, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f4.u32l;
L_800C74A0:
    // 0x800C74A0: mul.s       $f10, $f18, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800C74A4: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x800C74A8: swc1        $f12, -0x10($v0)
    MEM_W(-0X10, ctx->r2) = ctx->f12.u32l;
    // 0x800C74AC: mul.s       $f6, $f14, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800C74B0: nop

    // 0x800C74B4: mul.s       $f4, $f16, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f0.fl);
    // 0x800C74B8: swc1        $f10, -0xC($v0)
    MEM_W(-0XC, ctx->r2) = ctx->f10.u32l;
    // 0x800C74BC: swc1        $f6, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = ctx->f6.u32l;
    // 0x800C74C0: swc1        $f4, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->f4.u32l;
    // 0x800C74C4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C74C8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C74CC: jr          $ra
    // 0x800C74D0: nop

    return;
    // 0x800C74D0: nop

;}
RECOMP_FUNC void func_800C74D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C74D4: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x800C74D8: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x800C74DC: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x800C74E0: mtc1        $a3, $f16
    ctx->f16.u32l = ctx->r7;
    // 0x800C74E4: lwc1        $f4, 0x78($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X78);
    // 0x800C74E8: lwc1        $f6, 0x7C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x800C74EC: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x800C74F0: lwc1        $f10, 0x84($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X84);
    // 0x800C74F4: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800C74F8: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x800C74FC: mfc1        $a1, $f12
    ctx->r5 = (int32_t)ctx->f12.u32l;
    // 0x800C7500: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x800C7504: mfc1        $a3, $f16
    ctx->r7 = (int32_t)ctx->f16.u32l;
    // 0x800C7508: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x800C750C: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x800C7510: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x800C7514: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x800C7518: jal         0x800C7380
    // 0x800C751C: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    func_800C7380(rdram, ctx);
        goto after_0;
    // 0x800C751C: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    after_0:
    // 0x800C7520: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x800C7524: jal         0x800CCB00
    // 0x800C7528: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    func_800CCB00(rdram, ctx);
        goto after_1;
    // 0x800C7528: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    after_1:
    // 0x800C752C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800C7530: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x800C7534: jr          $ra
    // 0x800C7538: nop

    return;
    // 0x800C7538: nop

    // 0x800C753C: nop

    // 0x800C7540: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C7544: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C7548: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C754C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C7550: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x800C7554: jal         0x800CCC00
    // 0x800C7558: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800CCC00(rdram, ctx);
        goto after_2;
    // 0x800C7558: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_2:
    // 0x800C755C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C7560: lwc1        $f4, 0x1C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800C7564: swc1        $f4, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f4.u32l;
    // 0x800C7568: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800C756C: swc1        $f6, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f6.u32l;
    // 0x800C7570: lwc1        $f8, 0x24($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800C7574: swc1        $f8, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f8.u32l;
    // 0x800C7578: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C757C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C7580: jr          $ra
    // 0x800C7584: nop

    return;
    // 0x800C7584: nop

;}
RECOMP_FUNC void func_800C7588(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C7588: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x800C758C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C7590: sw          $a0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r4;
    // 0x800C7594: sw          $a1, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r5;
    // 0x800C7598: sw          $a2, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r6;
    // 0x800C759C: sw          $a3, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r7;
    // 0x800C75A0: jal         0x800CCC00
    // 0x800C75A4: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    func_800CCC00(rdram, ctx);
        goto after_0;
    // 0x800C75A4: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    after_0:
    // 0x800C75A8: lwc1        $f4, 0x6C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x800C75AC: lwc1        $f6, 0x70($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800C75B0: lwc1        $f8, 0x74($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X74);
    // 0x800C75B4: addiu       $a0, $sp, 0x28
    ctx->r4 = ADD32(ctx->r29, 0X28);
    // 0x800C75B8: lw          $a1, 0x68($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X68);
    // 0x800C75BC: swc1        $f4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f4.u32l;
    // 0x800C75C0: swc1        $f6, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f6.u32l;
    // 0x800C75C4: jal         0x800CCB00
    // 0x800C75C8: swc1        $f8, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f8.u32l;
    func_800CCB00(rdram, ctx);
        goto after_1;
    // 0x800C75C8: swc1        $f8, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f8.u32l;
    after_1:
    // 0x800C75CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C75D0: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x800C75D4: jr          $ra
    // 0x800C75D8: nop

    return;
    // 0x800C75D8: nop

    // 0x800C75DC: nop

;}
RECOMP_FUNC void func_800C75E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C75E0: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x800C75E4: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x800C75E8: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x800C75EC: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x800C75F0: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x800C75F4: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x800C75F8: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x800C75FC: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x800C7600: sw          $a2, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r6;
    // 0x800C7604: sw          $a3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r7;
    // 0x800C7608: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x800C760C: jal         0x800CCC00
    // 0x800C7610: sw          $a1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r5;
    func_800CCC00(rdram, ctx);
        goto after_0;
    // 0x800C7610: sw          $a1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r5;
    after_0:
    // 0x800C7614: lwc1        $f4, 0x5C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x800C7618: lwc1        $f6, 0x50($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800C761C: lwc1        $f8, 0x60($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X60);
    // 0x800C7620: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800C7624: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800C7628: lwc1        $f6, 0x58($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800C762C: lwc1        $f4, 0x64($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X64);
    // 0x800C7630: sub.s       $f22, $f8, $f10
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f22.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C7634: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800C7638: mov.s       $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    ctx->f20.fl = ctx->f0.fl;
    // 0x800C763C: sub.s       $f24, $f4, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f24.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800C7640: mul.s       $f10, $f22, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x800C7644: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800C7648: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x800C764C: jal         0x800C7010
    // 0x800C7650: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x800C7650: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_1:
    // 0x800C7654: lui         $at, 0xBFF0
    ctx->r1 = S32(0XBFF0 << 16);
    // 0x800C7658: mtc1        $at, $f9
    ctx->f_odd[(9 - 1) * 2] = ctx->r1;
    // 0x800C765C: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x800C7660: cvt.d.s     $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f10.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7664: lwc1        $f6, 0x6C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x800C7668: div.d       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f10.d); 
    ctx->f4.d = DIV_D(ctx->f8.d, ctx->f10.d);
    // 0x800C766C: lwc1        $f10, 0x70($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800C7670: cvt.s.d     $f2, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.d); 
    ctx->f2.fl = CVT_S_D(ctx->f4.d);
    // 0x800C7674: mul.s       $f20, $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x800C7678: nop

    // 0x800C767C: mul.s       $f22, $f22, $f2
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f22.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x800C7680: nop

    // 0x800C7684: mul.s       $f24, $f24, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f24.fl = MUL_S(ctx->f24.fl, ctx->f2.fl);
    // 0x800C7688: nop

    // 0x800C768C: mul.s       $f8, $f6, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f24.fl);
    // 0x800C7690: nop

    // 0x800C7694: mul.s       $f4, $f10, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x800C7698: sub.s       $f26, $f8, $f4
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x800C769C: mul.s       $f8, $f10, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f20.fl);
    // 0x800C76A0: lwc1        $f4, 0x68($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X68);
    // 0x800C76A4: mul.s       $f10, $f4, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f24.fl);
    // 0x800C76A8: sub.s       $f28, $f8, $f10
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f28.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C76AC: mul.s       $f8, $f4, $f22
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f22.fl);
    // 0x800C76B0: nop

    // 0x800C76B4: mul.s       $f10, $f6, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f20.fl);
    // 0x800C76B8: sub.s       $f30, $f8, $f10
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f30.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C76BC: mul.s       $f4, $f26, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x800C76C0: nop

    // 0x800C76C4: mul.s       $f6, $f28, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f6.fl = MUL_S(ctx->f28.fl, ctx->f28.fl);
    // 0x800C76C8: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800C76CC: mul.s       $f10, $f30, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f30.fl);
    // 0x800C76D0: jal         0x800C7010
    // 0x800C76D4: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x800C76D4: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_2:
    // 0x800C76D8: lui         $at, 0x3FF0
    ctx->r1 = S32(0X3FF0 << 16);
    // 0x800C76DC: mtc1        $at, $f5
    ctx->f_odd[(5 - 1) * 2] = ctx->r1;
    // 0x800C76E0: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800C76E4: cvt.d.s     $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f6.d = CVT_D_S(ctx->f0.fl);
    // 0x800C76E8: div.d       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = DIV_D(ctx->f4.d, ctx->f6.d);
    // 0x800C76EC: cvt.s.d     $f14, $f8
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f14.fl = CVT_S_D(ctx->f8.d);
    // 0x800C76F0: mul.s       $f26, $f26, $f14
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f26.fl = MUL_S(ctx->f26.fl, ctx->f14.fl);
    // 0x800C76F4: nop

    // 0x800C76F8: mul.s       $f28, $f28, $f14
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f28.fl = MUL_S(ctx->f28.fl, ctx->f14.fl);
    // 0x800C76FC: nop

    // 0x800C7700: mul.s       $f30, $f30, $f14
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f30.fl = MUL_S(ctx->f30.fl, ctx->f14.fl);
    // 0x800C7704: nop

    // 0x800C7708: mul.s       $f10, $f22, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = MUL_S(ctx->f22.fl, ctx->f30.fl);
    // 0x800C770C: nop

    // 0x800C7710: mul.s       $f4, $f24, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f4.fl = MUL_S(ctx->f24.fl, ctx->f28.fl);
    // 0x800C7714: nop

    // 0x800C7718: mul.s       $f6, $f24, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f26.fl);
    // 0x800C771C: nop

    // 0x800C7720: mul.s       $f8, $f20, $f30
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f8.fl = MUL_S(ctx->f20.fl, ctx->f30.fl);
    // 0x800C7724: sub.s       $f2, $f10, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x800C7728: mul.s       $f10, $f20, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f28.fl);
    // 0x800C772C: nop

    // 0x800C7730: mul.s       $f4, $f22, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f26.fl);
    // 0x800C7734: swc1        $f2, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f2.u32l;
    // 0x800C7738: sub.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C773C: mul.s       $f6, $f2, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x800C7740: nop

    // 0x800C7744: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x800C7748: swc1        $f16, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f16.u32l;
    // 0x800C774C: sub.s       $f18, $f10, $f4
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x800C7750: mul.s       $f4, $f18, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x800C7754: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7758: swc1        $f18, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f18.u32l;
    // 0x800C775C: jal         0x800C7010
    // 0x800C7760: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x800C7760: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    after_3:
    // 0x800C7764: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C7768: ldc1        $f2, -0x3A30($at)
    CHECK_FR(ctx, 2);
    ctx->f2.u64 = LD(ctx->r1, -0X3A30);
    // 0x800C776C: lui         $at, 0x4060
    ctx->r1 = S32(0X4060 << 16);
    // 0x800C7770: mtc1        $at, $f17
    ctx->f_odd[(17 - 1) * 2] = ctx->r1;
    // 0x800C7774: lui         $at, 0x3FF0
    ctx->r1 = S32(0X3FF0 << 16);
    // 0x800C7778: mtc1        $at, $f7
    ctx->f_odd[(7 - 1) * 2] = ctx->r1;
    // 0x800C777C: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x800C7780: cvt.d.s     $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f8.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7784: lwc1        $f4, 0x68($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X68);
    // 0x800C7788: div.d       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f8.d); 
    ctx->f10.d = DIV_D(ctx->f6.d, ctx->f8.d);
    // 0x800C778C: lwc1        $f8, 0x6C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x800C7790: mtc1        $zero, $f16
    ctx->f16.u32l = 0;
    // 0x800C7794: lw          $a0, 0x48($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X48);
    // 0x800C7798: lw          $a1, 0x4C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X4C);
    // 0x800C779C: addiu       $v0, $zero, 0x80
    ctx->r2 = ADD32(0, 0X80);
    // 0x800C77A0: cvt.s.d     $f14, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.d); 
    ctx->f14.fl = CVT_S_D(ctx->f10.d);
    // 0x800C77A4: mul.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x800C77A8: lwc1        $f4, 0x70($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800C77AC: mul.s       $f10, $f8, $f14
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f14.fl);
    // 0x800C77B0: cvt.d.s     $f8, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); 
    ctx->f8.d = CVT_D_S(ctx->f26.fl);
    // 0x800C77B4: swc1        $f6, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f6.u32l;
    // 0x800C77B8: mul.s       $f6, $f4, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f14.fl);
    // 0x800C77BC: swc1        $f10, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f10.u32l;
    // 0x800C77C0: mul.d       $f12, $f8, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f8.d, ctx->f16.d);
    // 0x800C77C4: swc1        $f6, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f6.u32l;
    // 0x800C77C8: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C77CC: nop

    // 0x800C77D0: bc1fl       L_800C77E4
    if (!c1cs) {
        // 0x800C77D4: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C77E4;
    }
    goto skip_0;
    // 0x800C77D4: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_0:
    // 0x800C77D8: b           L_800C77E4
    // 0x800C77DC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C77E4;
    // 0x800C77DC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C77E0: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C77E4:
    // 0x800C77E4: cvt.d.s     $f4, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f28.fl); 
    ctx->f4.d = CVT_D_S(ctx->f28.fl);
    // 0x800C77E8: trunc.w.d   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C77EC: mul.d       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f4.d, ctx->f16.d);
    // 0x800C77F0: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x800C77F4: nop

    // 0x800C77F8: sb          $t8, 0x8($a1)
    MEM_B(0X8, ctx->r5) = ctx->r24;
    // 0x800C77FC: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C7800: nop

    // 0x800C7804: bc1fl       L_800C7818
    if (!c1cs) {
        // 0x800C7808: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C7818;
    }
    goto skip_1;
    // 0x800C7808: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_1:
    // 0x800C780C: b           L_800C7818
    // 0x800C7810: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C7818;
    // 0x800C7810: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C7814: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C7818:
    // 0x800C7818: cvt.d.s     $f8, $f30
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); 
    ctx->f8.d = CVT_D_S(ctx->f30.fl);
    // 0x800C781C: trunc.w.d   $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    ctx->f6.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C7820: mul.d       $f12, $f8, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f8.d, ctx->f16.d);
    // 0x800C7824: mfc1        $t1, $f6
    ctx->r9 = (int32_t)ctx->f6.u32l;
    // 0x800C7828: nop

    // 0x800C782C: sb          $t1, 0x9($a1)
    MEM_B(0X9, ctx->r5) = ctx->r9;
    // 0x800C7830: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C7834: nop

    // 0x800C7838: bc1fl       L_800C784C
    if (!c1cs) {
        // 0x800C783C: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C784C;
    }
    goto skip_2;
    // 0x800C783C: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_2:
    // 0x800C7840: b           L_800C784C
    // 0x800C7844: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C784C;
    // 0x800C7844: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C7848: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C784C:
    // 0x800C784C: trunc.w.d   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C7850: mfc1        $t4, $f10
    ctx->r12 = (int32_t)ctx->f10.u32l;
    // 0x800C7854: nop

    // 0x800C7858: sb          $t4, 0xA($a1)
    MEM_B(0XA, ctx->r5) = ctx->r12;
    // 0x800C785C: lwc1        $f4, 0x68($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X68);
    // 0x800C7860: cvt.d.s     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f6.d = CVT_D_S(ctx->f4.fl);
    // 0x800C7864: mul.d       $f12, $f6, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f6.d, ctx->f16.d);
    // 0x800C7868: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C786C: nop

    // 0x800C7870: bc1fl       L_800C7884
    if (!c1cs) {
        // 0x800C7874: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C7884;
    }
    goto skip_3;
    // 0x800C7874: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_3:
    // 0x800C7878: b           L_800C7884
    // 0x800C787C: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C7884;
    // 0x800C787C: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C7880: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C7884:
    // 0x800C7884: trunc.w.d   $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    ctx->f8.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C7888: mfc1        $t7, $f8
    ctx->r15 = (int32_t)ctx->f8.u32l;
    // 0x800C788C: nop

    // 0x800C7890: sb          $t7, 0x18($a1)
    MEM_B(0X18, ctx->r5) = ctx->r15;
    // 0x800C7894: lwc1        $f10, 0x6C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x800C7898: cvt.d.s     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f4.d = CVT_D_S(ctx->f10.fl);
    // 0x800C789C: mul.d       $f12, $f4, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f4.d, ctx->f16.d);
    // 0x800C78A0: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C78A4: nop

    // 0x800C78A8: bc1fl       L_800C78BC
    if (!c1cs) {
        // 0x800C78AC: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C78BC;
    }
    goto skip_4;
    // 0x800C78AC: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_4:
    // 0x800C78B0: b           L_800C78BC
    // 0x800C78B4: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C78BC;
    // 0x800C78B4: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C78B8: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C78BC:
    // 0x800C78BC: trunc.w.d   $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    ctx->f6.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C78C0: mfc1        $t0, $f6
    ctx->r8 = (int32_t)ctx->f6.u32l;
    // 0x800C78C4: nop

    // 0x800C78C8: sb          $t0, 0x19($a1)
    MEM_B(0X19, ctx->r5) = ctx->r8;
    // 0x800C78CC: lwc1        $f8, 0x70($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800C78D0: cvt.d.s     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f10.d = CVT_D_S(ctx->f8.fl);
    // 0x800C78D4: mul.d       $f12, $f10, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f16.d); 
    ctx->f12.d = MUL_D(ctx->f10.d, ctx->f16.d);
    // 0x800C78D8: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C78DC: nop

    // 0x800C78E0: bc1fl       L_800C78F4
    if (!c1cs) {
        // 0x800C78E4: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C78F4;
    }
    goto skip_5;
    // 0x800C78E4: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_5:
    // 0x800C78E8: b           L_800C78F4
    // 0x800C78EC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C78F4;
    // 0x800C78EC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C78F0: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C78F4:
    // 0x800C78F4: trunc.w.d   $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    ctx->f4.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C78F8: sb          $zero, 0x0($a1)
    MEM_B(0X0, ctx->r5) = 0;
    // 0x800C78FC: sb          $zero, 0x1($a1)
    MEM_B(0X1, ctx->r5) = 0;
    // 0x800C7900: sb          $zero, 0x2($a1)
    MEM_B(0X2, ctx->r5) = 0;
    // 0x800C7904: mfc1        $t3, $f4
    ctx->r11 = (int32_t)ctx->f4.u32l;
    // 0x800C7908: sb          $zero, 0x3($a1)
    MEM_B(0X3, ctx->r5) = 0;
    // 0x800C790C: sb          $zero, 0x4($a1)
    MEM_B(0X4, ctx->r5) = 0;
    // 0x800C7910: sb          $zero, 0x5($a1)
    MEM_B(0X5, ctx->r5) = 0;
    // 0x800C7914: sb          $zero, 0x6($a1)
    MEM_B(0X6, ctx->r5) = 0;
    // 0x800C7918: sb          $zero, 0x7($a1)
    MEM_B(0X7, ctx->r5) = 0;
    // 0x800C791C: sb          $zero, 0x10($a1)
    MEM_B(0X10, ctx->r5) = 0;
    // 0x800C7920: sb          $v0, 0x11($a1)
    MEM_B(0X11, ctx->r5) = ctx->r2;
    // 0x800C7924: sb          $zero, 0x12($a1)
    MEM_B(0X12, ctx->r5) = 0;
    // 0x800C7928: sb          $zero, 0x13($a1)
    MEM_B(0X13, ctx->r5) = 0;
    // 0x800C792C: sb          $zero, 0x14($a1)
    MEM_B(0X14, ctx->r5) = 0;
    // 0x800C7930: sb          $v0, 0x15($a1)
    MEM_B(0X15, ctx->r5) = ctx->r2;
    // 0x800C7934: sb          $zero, 0x16($a1)
    MEM_B(0X16, ctx->r5) = 0;
    // 0x800C7938: sb          $zero, 0x17($a1)
    MEM_B(0X17, ctx->r5) = 0;
    // 0x800C793C: sb          $t3, 0x1A($a1)
    MEM_B(0X1A, ctx->r5) = ctx->r11;
    // 0x800C7940: swc1        $f26, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f26.u32l;
    // 0x800C7944: lwc1        $f18, 0x50($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800C7948: lwc1        $f16, 0x54($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800C794C: lwc1        $f14, 0x58($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800C7950: mul.s       $f6, $f18, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f26.fl);
    // 0x800C7954: lwc1        $f0, 0x68($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0X68);
    // 0x800C7958: lwc1        $f12, 0x6C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X6C);
    // 0x800C795C: mul.s       $f8, $f16, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f28.fl);
    // 0x800C7960: lwc1        $f2, 0x70($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X70);
    // 0x800C7964: swc1        $f28, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f28.u32l;
    // 0x800C7968: mul.s       $f4, $f14, $f30
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f30.fl);
    // 0x800C796C: swc1        $f30, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f30.u32l;
    // 0x800C7970: swc1        $f20, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f20.u32l;
    // 0x800C7974: swc1        $f22, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f22.u32l;
    // 0x800C7978: swc1        $f24, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f24.u32l;
    // 0x800C797C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7980: swc1        $f0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f0.u32l;
    // 0x800C7984: swc1        $f12, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f12.u32l;
    // 0x800C7988: swc1        $f2, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f2.u32l;
    // 0x800C798C: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800C7990: mul.s       $f10, $f18, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800C7994: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800C7998: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C799C: mul.s       $f4, $f16, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f12.fl);
    // 0x800C79A0: neg.s       $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = -ctx->f6.fl;
    // 0x800C79A4: swc1        $f8, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f8.u32l;
    // 0x800C79A8: mul.s       $f8, $f14, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x800C79AC: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800C79B0: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C79B4: neg.s       $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = -ctx->f10.fl;
    // 0x800C79B8: swc1        $f4, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f4.u32l;
    // 0x800C79BC: lwc1        $f6, 0x50($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X50);
    // 0x800C79C0: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800C79C4: mul.s       $f8, $f6, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f20.fl);
    // 0x800C79C8: nop

    // 0x800C79CC: mul.s       $f4, $f10, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x800C79D0: lwc1        $f10, 0x58($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800C79D4: swc1        $f0, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->f0.u32l;
    // 0x800C79D8: swc1        $f0, 0x1C($a0)
    MEM_W(0X1C, ctx->r4) = ctx->f0.u32l;
    // 0x800C79DC: swc1        $f0, 0x2C($a0)
    MEM_W(0X2C, ctx->r4) = ctx->f0.u32l;
    // 0x800C79E0: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C79E4: mul.s       $f8, $f10, $f24
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f24.fl);
    // 0x800C79E8: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C79EC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C79F0: neg.s       $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = -ctx->f4.fl;
    // 0x800C79F4: swc1        $f6, 0x3C($a0)
    MEM_W(0X3C, ctx->r4) = ctx->f6.u32l;
    // 0x800C79F8: swc1        $f10, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f10.u32l;
    // 0x800C79FC: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x800C7A00: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x800C7A04: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x800C7A08: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x800C7A0C: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x800C7A10: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x800C7A14: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x800C7A18: jr          $ra
    // 0x800C7A1C: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800C7A1C: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_800C7A20(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C7A20: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x800C7A24: lwc1        $f4, 0x88($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C7A28: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x800C7A2C: mtc1        $a3, $f14
    ctx->f14.u32l = ctx->r7;
    // 0x800C7A30: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x800C7A34: lwc1        $f4, 0xA0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA0);
    // 0x800C7A38: lwc1        $f6, 0x8C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X8C);
    // 0x800C7A3C: lwc1        $f8, 0x90($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X90);
    // 0x800C7A40: lwc1        $f10, 0x94($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X94);
    // 0x800C7A44: lwc1        $f16, 0x98($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X98);
    // 0x800C7A48: lwc1        $f18, 0x9C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X9C);
    // 0x800C7A4C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800C7A50: sw          $a0, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r4;
    // 0x800C7A54: mfc1        $a2, $f12
    ctx->r6 = (int32_t)ctx->f12.u32l;
    // 0x800C7A58: mfc1        $a3, $f14
    ctx->r7 = (int32_t)ctx->f14.u32l;
    // 0x800C7A5C: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    // 0x800C7A60: swc1        $f4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f4.u32l;
    // 0x800C7A64: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x800C7A68: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x800C7A6C: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    // 0x800C7A70: swc1        $f16, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f16.u32l;
    // 0x800C7A74: jal         0x800C75E0
    // 0x800C7A78: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    func_800C75E0(rdram, ctx);
        goto after_0;
    // 0x800C7A78: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    after_0:
    // 0x800C7A7C: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    // 0x800C7A80: jal         0x800CCB00
    // 0x800C7A84: lw          $a1, 0x78($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X78);
    func_800CCB00(rdram, ctx);
        goto after_1;
    // 0x800C7A84: lw          $a1, 0x78($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X78);
    after_1:
    // 0x800C7A88: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800C7A8C: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x800C7A90: jr          $ra
    // 0x800C7A94: nop

    return;
    // 0x800C7A94: nop

    // 0x800C7A98: nop

    // 0x800C7A9C: nop

;}
RECOMP_FUNC void func_800C7AA0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C7AA0: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x800C7AA4: sw          $ra, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r31;
    // 0x800C7AA8: sw          $s1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r17;
    // 0x800C7AAC: sw          $s0, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r16;
    // 0x800C7AB0: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x800C7AB4: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800C7AB8: sdc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X38, ctx->r29);
    // 0x800C7ABC: sdc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X30, ctx->r29);
    // 0x800C7AC0: sdc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X28, ctx->r29);
    // 0x800C7AC4: sdc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X20, ctx->r29);
    // 0x800C7AC8: sdc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X18, ctx->r29);
    // 0x800C7ACC: sdc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X10, ctx->r29);
    // 0x800C7AD0: sw          $a2, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r6;
    // 0x800C7AD4: jal         0x800CCC00
    // 0x800C7AD8: sw          $a3, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r7;
    func_800CCC00(rdram, ctx);
        goto after_0;
    // 0x800C7AD8: sw          $a3, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r7;
    after_0:
    // 0x800C7ADC: lwc1        $f4, 0xB0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XB0);
    // 0x800C7AE0: lwc1        $f6, 0xA4($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800C7AE4: lwc1        $f8, 0xB4($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB4);
    // 0x800C7AE8: lwc1        $f10, 0xA8($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x800C7AEC: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800C7AF0: lwc1        $f6, 0xAC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XAC);
    // 0x800C7AF4: lwc1        $f4, 0xB8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x800C7AF8: sub.s       $f30, $f8, $f10
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f30.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C7AFC: mul.s       $f8, $f0, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800C7B00: mov.s       $f28, $f0
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    ctx->f28.fl = ctx->f0.fl;
    // 0x800C7B04: sub.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x800C7B08: mul.s       $f10, $f30, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f30.fl);
    // 0x800C7B0C: swc1        $f14, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->f14.u32l;
    // 0x800C7B10: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800C7B14: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800C7B18: jal         0x800C7010
    // 0x800C7B1C: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x800C7B1C: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_1:
    // 0x800C7B20: lui         $at, 0xBFF0
    ctx->r1 = S32(0XBFF0 << 16);
    // 0x800C7B24: mtc1        $at, $f9
    ctx->f_odd[(9 - 1) * 2] = ctx->r1;
    // 0x800C7B28: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x800C7B2C: cvt.d.s     $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f10.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7B30: lwc1        $f20, 0x88($sp)
    ctx->f20.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C7B34: div.d       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f10.d); 
    ctx->f4.d = DIV_D(ctx->f8.d, ctx->f10.d);
    // 0x800C7B38: lwc1        $f6, 0xC0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C7B3C: lwc1        $f10, 0xC4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C7B40: cvt.s.d     $f2, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.d); 
    ctx->f2.fl = CVT_S_D(ctx->f4.d);
    // 0x800C7B44: mul.s       $f28, $f28, $f2
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f28.fl = MUL_S(ctx->f28.fl, ctx->f2.fl);
    // 0x800C7B48: nop

    // 0x800C7B4C: mul.s       $f30, $f30, $f2
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f30.fl = MUL_S(ctx->f30.fl, ctx->f2.fl);
    // 0x800C7B50: nop

    // 0x800C7B54: mul.s       $f20, $f20, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f2.fl);
    // 0x800C7B58: nop

    // 0x800C7B5C: mul.s       $f8, $f6, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f20.fl);
    // 0x800C7B60: swc1        $f20, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->f20.u32l;
    // 0x800C7B64: mul.s       $f4, $f10, $f30
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f30.fl);
    // 0x800C7B68: sub.s       $f22, $f8, $f4
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f22.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x800C7B6C: mul.s       $f8, $f10, $f28
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f28.fl);
    // 0x800C7B70: lwc1        $f4, 0xBC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C7B74: mul.s       $f10, $f4, $f20
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 20);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f20.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f20.fl);
    // 0x800C7B78: sub.s       $f24, $f8, $f10
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f24.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C7B7C: mul.s       $f8, $f4, $f30
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f30.fl);
    // 0x800C7B80: nop

    // 0x800C7B84: mul.s       $f10, $f6, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f28.fl);
    // 0x800C7B88: sub.s       $f26, $f8, $f10
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f26.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x800C7B8C: mul.s       $f4, $f22, $f22
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f4.fl = MUL_S(ctx->f22.fl, ctx->f22.fl);
    // 0x800C7B90: nop

    // 0x800C7B94: mul.s       $f6, $f24, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f24.fl, ctx->f24.fl);
    // 0x800C7B98: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800C7B9C: mul.s       $f10, $f26, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f26.fl, ctx->f26.fl);
    // 0x800C7BA0: jal         0x800C7010
    // 0x800C7BA4: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x800C7BA4: add.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl + ctx->f10.fl;
    after_2:
    // 0x800C7BA8: lui         $at, 0x3FF0
    ctx->r1 = S32(0X3FF0 << 16);
    // 0x800C7BAC: mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // 0x800C7BB0: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x800C7BB4: cvt.d.s     $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f4.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7BB8: lwc1        $f10, 0x88($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C7BBC: div.d       $f6, $f20, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f4.d); 
    ctx->f6.d = DIV_D(ctx->f20.d, ctx->f4.d);
    // 0x800C7BC0: cvt.s.d     $f2, $f6
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f2.fl = CVT_S_D(ctx->f6.d);
    // 0x800C7BC4: mul.s       $f22, $f22, $f2
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f22.fl = MUL_S(ctx->f22.fl, ctx->f2.fl);
    // 0x800C7BC8: nop

    // 0x800C7BCC: mul.s       $f24, $f24, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f24.fl = MUL_S(ctx->f24.fl, ctx->f2.fl);
    // 0x800C7BD0: nop

    // 0x800C7BD4: mul.s       $f26, $f26, $f2
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f26.fl = MUL_S(ctx->f26.fl, ctx->f2.fl);
    // 0x800C7BD8: nop

    // 0x800C7BDC: mul.s       $f8, $f30, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f8.fl = MUL_S(ctx->f30.fl, ctx->f26.fl);
    // 0x800C7BE0: nop

    // 0x800C7BE4: mul.s       $f4, $f10, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f24.fl);
    // 0x800C7BE8: sub.s       $f14, $f8, $f4
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f14.fl = ctx->f8.fl - ctx->f4.fl;
    // 0x800C7BEC: mul.s       $f6, $f10, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f22.fl);
    // 0x800C7BF0: nop

    // 0x800C7BF4: mul.s       $f8, $f28, $f26
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f8.fl = MUL_S(ctx->f28.fl, ctx->f26.fl);
    // 0x800C7BF8: swc1        $f14, 0xBC($sp)
    MEM_W(0XBC, ctx->r29) = ctx->f14.u32l;
    // 0x800C7BFC: mul.s       $f4, $f28, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f28.fl, ctx->f24.fl);
    // 0x800C7C00: nop

    // 0x800C7C04: mul.s       $f10, $f30, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f30.fl, ctx->f22.fl);
    // 0x800C7C08: sub.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C7C0C: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800C7C10: nop

    // 0x800C7C14: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x800C7C18: swc1        $f16, 0xC0($sp)
    MEM_W(0XC0, ctx->r29) = ctx->f16.u32l;
    // 0x800C7C1C: sub.s       $f18, $f4, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x800C7C20: mul.s       $f10, $f18, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x800C7C24: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7C28: swc1        $f18, 0xC4($sp)
    MEM_W(0XC4, ctx->r29) = ctx->f18.u32l;
    // 0x800C7C2C: jal         0x800C7010
    // 0x800C7C30: add.s       $f12, $f4, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_3;
    // 0x800C7C30: add.s       $f12, $f4, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f10.fl;
    after_3:
    // 0x800C7C34: cvt.d.s     $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f6.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7C38: lwc1        $f4, 0xBC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C7C3C: div.d       $f8, $f20, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = DIV_D(ctx->f20.d, ctx->f6.d);
    // 0x800C7C40: lwc1        $f6, 0xC0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C7C44: lwc1        $f14, 0xC8($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0XC8);
    // 0x800C7C48: lwc1        $f16, 0xCC($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XCC);
    // 0x800C7C4C: lwc1        $f18, 0xD0($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0XD0);
    // 0x800C7C50: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
    // 0x800C7C54: mul.s       $f10, $f4, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800C7C58: lwc1        $f4, 0xC4($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C7C5C: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800C7C60: swc1        $f10, 0xBC($sp)
    MEM_W(0XBC, ctx->r29) = ctx->f10.u32l;
    // 0x800C7C64: mul.s       $f10, $f4, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800C7C68: swc1        $f8, 0xC0($sp)
    MEM_W(0XC0, ctx->r29) = ctx->f8.u32l;
    // 0x800C7C6C: mul.s       $f6, $f14, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800C7C70: nop

    // 0x800C7C74: mul.s       $f8, $f16, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f16.fl);
    // 0x800C7C78: swc1        $f10, 0xC4($sp)
    MEM_W(0XC4, ctx->r29) = ctx->f10.u32l;
    // 0x800C7C7C: mul.s       $f10, $f18, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f18.fl);
    // 0x800C7C80: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7C84: jal         0x800C7010
    // 0x800C7C88: add.s       $f12, $f4, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f10.fl;
    _nsqrtf(rdram, ctx);
        goto after_4;
    // 0x800C7C88: add.s       $f12, $f4, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f10.fl;
    after_4:
    // 0x800C7C8C: cvt.d.s     $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f6.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7C90: lwc1        $f4, 0xC8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC8);
    // 0x800C7C94: div.d       $f8, $f20, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = DIV_D(ctx->f20.d, ctx->f6.d);
    // 0x800C7C98: lwc1        $f6, 0xCC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XCC);
    // 0x800C7C9C: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
    // 0x800C7CA0: mul.s       $f10, $f4, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800C7CA4: lwc1        $f4, 0xD0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XD0);
    // 0x800C7CA8: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800C7CAC: swc1        $f10, 0xC8($sp)
    MEM_W(0XC8, ctx->r29) = ctx->f10.u32l;
    // 0x800C7CB0: mul.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f2.fl);
    // 0x800C7CB4: add.s       $f4, $f10, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f28.fl;
    // 0x800C7CB8: swc1        $f8, 0xCC($sp)
    MEM_W(0XCC, ctx->r29) = ctx->f8.u32l;
    // 0x800C7CBC: add.s       $f10, $f8, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f30.fl;
    // 0x800C7CC0: lwc1        $f8, 0x88($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C7CC4: swc1        $f6, 0xD0($sp)
    MEM_W(0XD0, ctx->r29) = ctx->f6.u32l;
    // 0x800C7CC8: swc1        $f4, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f4.u32l;
    // 0x800C7CCC: add.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7CD0: mul.s       $f8, $f4, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x800C7CD4: swc1        $f10, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f10.u32l;
    // 0x800C7CD8: mul.s       $f4, $f10, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x800C7CDC: swc1        $f6, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f6.u32l;
    // 0x800C7CE0: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C7CE4: mul.s       $f8, $f6, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f6.fl);
    // 0x800C7CE8: jal         0x800C7010
    // 0x800C7CEC: add.s       $f12, $f10, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_5;
    // 0x800C7CEC: add.s       $f12, $f10, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f8.fl;
    after_5:
    // 0x800C7CF0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C7CF4: ldc1        $f4, -0x3A20($at)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r1, -0X3A20);
    // 0x800C7CF8: cvt.d.s     $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f2.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7CFC: lw          $v1, 0xE4($sp)
    ctx->r3 = MEM_W(ctx->r29, 0XE4);
    // 0x800C7D00: c.lt.d      $f4, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f4.d < ctx->f2.d;
    // 0x800C7D04: lw          $v0, 0xE0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XE0);
    // 0x800C7D08: lw          $t4, 0xA0($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA0);
    // 0x800C7D0C: sll         $t5, $v1, 1
    ctx->r13 = S32(ctx->r3 << 1);
    // 0x800C7D10: bc1fl       L_800C7DFC
    if (!c1cs) {
        // 0x800C7D14: sll         $t3, $v0, 1
        ctx->r11 = S32(ctx->r2 << 1);
            goto L_800C7DFC;
    }
    goto skip_0;
    // 0x800C7D14: sll         $t3, $v0, 1
    ctx->r11 = S32(ctx->r2 << 1);
    skip_0:
    // 0x800C7D18: div.d       $f6, $f20, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f2.d); 
    ctx->f6.d = DIV_D(ctx->f20.d, ctx->f2.d);
    // 0x800C7D1C: lwc1        $f10, 0x5C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x800C7D20: lwc1        $f8, 0x58($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800C7D24: lwc1        $f4, 0x54($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800C7D28: lw          $v0, 0xE0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XE0);
    // 0x800C7D2C: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800C7D30: lw          $t9, 0xA0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XA0);
    // 0x800C7D34: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x800C7D38: lw          $v1, 0xE4($sp)
    ctx->r3 = MEM_W(ctx->r29, 0XE4);
    // 0x800C7D3C: sll         $t0, $v1, 2
    ctx->r8 = S32(ctx->r3 << 2);
    // 0x800C7D40: cvt.s.d     $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f12.fl = CVT_S_D(ctx->f6.d);
    // 0x800C7D44: mul.s       $f14, $f10, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x800C7D48: nop

    // 0x800C7D4C: mul.s       $f16, $f8, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x800C7D50: nop

    // 0x800C7D54: mul.s       $f18, $f4, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x800C7D58: nop

    // 0x800C7D5C: mul.s       $f6, $f14, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f22.fl);
    // 0x800C7D60: nop

    // 0x800C7D64: mul.s       $f10, $f16, $f24
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f24.fl);
    // 0x800C7D68: add.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x800C7D6C: mul.s       $f4, $f18, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f26.fl);
    // 0x800C7D70: mtc1        $v0, $f10
    ctx->f10.u32l = ctx->r2;
    // 0x800C7D74: add.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C7D78: cvt.s.w     $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800C7D7C: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800C7D80: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C7D84: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x800C7D88: mul.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x800C7D8C: cvt.s.w     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    ctx->f4.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800C7D90: add.s       $f10, $f4, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800C7D94: trunc.w.s   $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    ctx->f8.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800C7D98: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x800C7D9C: nop

    // 0x800C7DA0: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
    // 0x800C7DA4: lwc1        $f4, 0xBC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C7DA8: lwc1        $f10, 0xC0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C7DAC: mul.s       $f6, $f14, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f4.fl);
    // 0x800C7DB0: nop

    // 0x800C7DB4: mul.s       $f8, $f16, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // 0x800C7DB8: lwc1        $f10, 0xC4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C7DBC: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7DC0: mul.s       $f6, $f18, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f10.fl);
    // 0x800C7DC4: mtc1        $v1, $f10
    ctx->f10.u32l = ctx->r3;
    // 0x800C7DC8: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x800C7DCC: cvt.s.w     $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800C7DD0: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800C7DD4: mul.s       $f6, $f8, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x800C7DD8: mtc1        $t0, $f4
    ctx->f4.u32l = ctx->r8;
    // 0x800C7DDC: mul.s       $f8, $f6, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x800C7DE0: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C7DE4: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7DE8: trunc.w.s   $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    ctx->f4.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800C7DEC: mfc1        $t2, $f4
    ctx->r10 = (int32_t)ctx->f4.u32l;
    // 0x800C7DF0: b           L_800C7E04
    // 0x800C7DF4: sw          $t2, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r10;
        goto L_800C7E04;
    // 0x800C7DF4: sw          $t2, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r10;
    // 0x800C7DF8: sll         $t3, $v0, 1
    ctx->r11 = S32(ctx->r2 << 1);
L_800C7DFC:
    // 0x800C7DFC: sw          $t3, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r11;
    // 0x800C7E00: sw          $t5, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r13;
L_800C7E04:
    // 0x800C7E04: lwc1        $f0, 0xD4($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0XD4);
    // 0x800C7E08: lwc1        $f2, 0xD8($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0XD8);
    // 0x800C7E0C: lwc1        $f14, 0xDC($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0XDC);
    // 0x800C7E10: mul.s       $f6, $f0, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x800C7E14: nop

    // 0x800C7E18: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x800C7E1C: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7E20: mul.s       $f4, $f14, $f14
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x800C7E24: jal         0x800C7010
    // 0x800C7E28: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    _nsqrtf(rdram, ctx);
        goto after_6;
    // 0x800C7E28: add.s       $f12, $f10, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f4.fl;
    after_6:
    // 0x800C7E2C: cvt.d.s     $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f6.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7E30: lwc1        $f10, 0xD4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XD4);
    // 0x800C7E34: div.d       $f8, $f20, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f6.d); 
    ctx->f8.d = DIV_D(ctx->f20.d, ctx->f6.d);
    // 0x800C7E38: lwc1        $f6, 0xD8($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XD8);
    // 0x800C7E3C: cvt.s.d     $f2, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.d); 
    ctx->f2.fl = CVT_S_D(ctx->f8.d);
    // 0x800C7E40: mul.s       $f4, $f10, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x800C7E44: lwc1        $f10, 0xDC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XDC);
    // 0x800C7E48: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800C7E4C: swc1        $f4, 0xD4($sp)
    MEM_W(0XD4, ctx->r29) = ctx->f4.u32l;
    // 0x800C7E50: mul.s       $f6, $f10, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // 0x800C7E54: add.s       $f10, $f4, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f28.fl;
    // 0x800C7E58: swc1        $f8, 0xD8($sp)
    MEM_W(0XD8, ctx->r29) = ctx->f8.u32l;
    // 0x800C7E5C: add.s       $f4, $f8, $f30
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f30.fl;
    // 0x800C7E60: lwc1        $f8, 0x88($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C7E64: swc1        $f6, 0xDC($sp)
    MEM_W(0XDC, ctx->r29) = ctx->f6.u32l;
    // 0x800C7E68: swc1        $f10, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f10.u32l;
    // 0x800C7E6C: add.s       $f6, $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7E70: mul.s       $f8, $f10, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f10.fl);
    // 0x800C7E74: swc1        $f4, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->f4.u32l;
    // 0x800C7E78: mul.s       $f10, $f4, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f4.fl, ctx->f4.fl);
    // 0x800C7E7C: swc1        $f6, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->f6.u32l;
    // 0x800C7E80: add.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800C7E84: mul.s       $f8, $f6, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f6.fl);
    // 0x800C7E88: jal         0x800C7010
    // 0x800C7E8C: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    _nsqrtf(rdram, ctx);
        goto after_7;
    // 0x800C7E8C: add.s       $f12, $f4, $f8
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f8.fl;
    after_7:
    // 0x800C7E90: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C7E94: ldc1        $f10, -0x3A18($at)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r1, -0X3A18);
    // 0x800C7E98: cvt.d.s     $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); 
    ctx->f2.d = CVT_D_S(ctx->f0.fl);
    // 0x800C7E9C: lw          $v0, 0xE0($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XE0);
    // 0x800C7EA0: c.lt.d      $f10, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f10.d < ctx->f2.d;
    // 0x800C7EA4: lw          $v1, 0xE4($sp)
    ctx->r3 = MEM_W(ctx->r29, 0XE4);
    // 0x800C7EA8: lw          $a0, 0xA0($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XA0);
    // 0x800C7EAC: sll         $t9, $v0, 1
    ctx->r25 = S32(ctx->r2 << 1);
    // 0x800C7EB0: bc1f        L_800C7F90
    if (!c1cs) {
        // 0x800C7EB4: sll         $t3, $v1, 1
        ctx->r11 = S32(ctx->r3 << 1);
            goto L_800C7F90;
    }
    // 0x800C7EB4: sll         $t3, $v1, 1
    ctx->r11 = S32(ctx->r3 << 1);
    // 0x800C7EB8: div.d       $f6, $f20, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f20.d); NAN_CHECK(ctx->f2.d); 
    ctx->f6.d = DIV_D(ctx->f20.d, ctx->f2.d);
    // 0x800C7EBC: lwc1        $f4, 0x5C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X5C);
    // 0x800C7EC0: lwc1        $f8, 0x58($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X58);
    // 0x800C7EC4: lwc1        $f10, 0x54($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X54);
    // 0x800C7EC8: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x800C7ECC: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x800C7ED0: lw          $a0, 0xA0($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XA0);
    // 0x800C7ED4: sll         $t0, $v1, 2
    ctx->r8 = S32(ctx->r3 << 2);
    // 0x800C7ED8: cvt.s.d     $f12, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f12.fl = CVT_S_D(ctx->f6.d);
    // 0x800C7EDC: mul.s       $f14, $f4, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x800C7EE0: nop

    // 0x800C7EE4: mul.s       $f16, $f8, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x800C7EE8: nop

    // 0x800C7EEC: mul.s       $f18, $f10, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x800C7EF0: nop

    // 0x800C7EF4: mul.s       $f6, $f14, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f22.fl);
    // 0x800C7EF8: nop

    // 0x800C7EFC: mul.s       $f4, $f16, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f24.fl);
    // 0x800C7F00: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x800C7F04: mul.s       $f10, $f18, $f26
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f26.fl);
    // 0x800C7F08: mtc1        $v0, $f4
    ctx->f4.u32l = ctx->r2;
    // 0x800C7F0C: add.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800C7F10: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C7F14: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C7F18: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800C7F1C: mtc1        $t6, $f8
    ctx->f8.u32l = ctx->r14;
    // 0x800C7F20: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x800C7F24: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800C7F28: add.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800C7F2C: trunc.w.s   $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800C7F30: mfc1        $t8, $f8
    ctx->r24 = (int32_t)ctx->f8.u32l;
    // 0x800C7F34: nop

    // 0x800C7F38: sw          $t8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r24;
    // 0x800C7F3C: lwc1        $f10, 0xBC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C7F40: lwc1        $f4, 0xC0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C7F44: mul.s       $f6, $f14, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x800C7F48: nop

    // 0x800C7F4C: mul.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f4.fl);
    // 0x800C7F50: lwc1        $f4, 0xC4($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C7F54: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7F58: mul.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800C7F5C: mtc1        $v1, $f4
    ctx->f4.u32l = ctx->r3;
    // 0x800C7F60: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800C7F64: cvt.s.w     $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C7F68: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C7F6C: mul.s       $f6, $f8, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800C7F70: mtc1        $t0, $f10
    ctx->f10.u32l = ctx->r8;
    // 0x800C7F74: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x800C7F78: cvt.s.w     $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    ctx->f6.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800C7F7C: add.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x800C7F80: trunc.w.s   $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800C7F84: mfc1        $t2, $f10
    ctx->r10 = (int32_t)ctx->f10.u32l;
    // 0x800C7F88: b           L_800C7F98
    // 0x800C7F8C: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
        goto L_800C7F98;
    // 0x800C7F8C: sw          $t2, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r10;
L_800C7F90:
    // 0x800C7F90: sw          $t9, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->r25;
    // 0x800C7F94: sw          $t3, 0xC($a0)
    MEM_W(0XC, ctx->r4) = ctx->r11;
L_800C7F98:
    // 0x800C7F98: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C7F9C: ldc1        $f2, -0x3A10($at)
    CHECK_FR(ctx, 2);
    ctx->f2.u64 = LD(ctx->r1, -0X3A10);
    // 0x800C7FA0: lui         $at, 0x4060
    ctx->r1 = S32(0X4060 << 16);
    // 0x800C7FA4: mtc1        $at, $f15
    ctx->f_odd[(15 - 1) * 2] = ctx->r1;
    // 0x800C7FA8: mtc1        $zero, $f14
    ctx->f14.u32l = 0;
    // 0x800C7FAC: cvt.d.s     $f6, $f22
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f22.fl); 
    ctx->f6.d = CVT_D_S(ctx->f22.fl);
    // 0x800C7FB0: addiu       $v0, $zero, 0x80
    ctx->r2 = ADD32(0, 0X80);
    // 0x800C7FB4: mul.d       $f12, $f6, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f6.d, ctx->f14.d);
    // 0x800C7FB8: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C7FBC: nop

    // 0x800C7FC0: bc1fl       L_800C7FD4
    if (!c1cs) {
        // 0x800C7FC4: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C7FD4;
    }
    goto skip_1;
    // 0x800C7FC4: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_1:
    // 0x800C7FC8: b           L_800C7FD4
    // 0x800C7FCC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C7FD4;
    // 0x800C7FCC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C7FD0: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C7FD4:
    // 0x800C7FD4: cvt.d.s     $f4, $f24
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f24.fl); 
    ctx->f4.d = CVT_D_S(ctx->f24.fl);
    // 0x800C7FD8: trunc.w.d   $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    ctx->f8.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C7FDC: mul.d       $f12, $f4, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f4.d, ctx->f14.d);
    // 0x800C7FE0: mfc1        $t6, $f8
    ctx->r14 = (int32_t)ctx->f8.u32l;
    // 0x800C7FE4: nop

    // 0x800C7FE8: sb          $t6, 0x8($s0)
    MEM_B(0X8, ctx->r16) = ctx->r14;
    // 0x800C7FEC: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C7FF0: nop

    // 0x800C7FF4: bc1fl       L_800C8008
    if (!c1cs) {
        // 0x800C7FF8: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C8008;
    }
    goto skip_2;
    // 0x800C7FF8: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_2:
    // 0x800C7FFC: b           L_800C8008
    // 0x800C8000: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C8008;
    // 0x800C8000: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C8004: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C8008:
    // 0x800C8008: cvt.d.s     $f6, $f26
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f26.fl); 
    ctx->f6.d = CVT_D_S(ctx->f26.fl);
    // 0x800C800C: trunc.w.d   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C8010: mul.d       $f12, $f6, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f6.d, ctx->f14.d);
    // 0x800C8014: mfc1        $t0, $f10
    ctx->r8 = (int32_t)ctx->f10.u32l;
    // 0x800C8018: nop

    // 0x800C801C: sb          $t0, 0x9($s0)
    MEM_B(0X9, ctx->r16) = ctx->r8;
    // 0x800C8020: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C8024: nop

    // 0x800C8028: bc1fl       L_800C803C
    if (!c1cs) {
        // 0x800C802C: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C803C;
    }
    goto skip_3;
    // 0x800C802C: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_3:
    // 0x800C8030: b           L_800C803C
    // 0x800C8034: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C803C;
    // 0x800C8034: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C8038: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C803C:
    // 0x800C803C: trunc.w.d   $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    ctx->f8.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C8040: mfc1        $t9, $f8
    ctx->r25 = (int32_t)ctx->f8.u32l;
    // 0x800C8044: nop

    // 0x800C8048: sb          $t9, 0xA($s0)
    MEM_B(0XA, ctx->r16) = ctx->r25;
    // 0x800C804C: lwc1        $f4, 0xBC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C8050: cvt.d.s     $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f4.fl); 
    ctx->f10.d = CVT_D_S(ctx->f4.fl);
    // 0x800C8054: mul.d       $f12, $f10, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f10.d, ctx->f14.d);
    // 0x800C8058: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C805C: nop

    // 0x800C8060: bc1fl       L_800C8074
    if (!c1cs) {
        // 0x800C8064: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C8074;
    }
    goto skip_4;
    // 0x800C8064: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_4:
    // 0x800C8068: b           L_800C8074
    // 0x800C806C: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C8074;
    // 0x800C806C: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C8070: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C8074:
    // 0x800C8074: trunc.w.d   $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    ctx->f6.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C8078: mfc1        $t4, $f6
    ctx->r12 = (int32_t)ctx->f6.u32l;
    // 0x800C807C: nop

    // 0x800C8080: sb          $t4, 0x18($s0)
    MEM_B(0X18, ctx->r16) = ctx->r12;
    // 0x800C8084: lwc1        $f8, 0xC0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C8088: cvt.d.s     $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f4.d = CVT_D_S(ctx->f8.fl);
    // 0x800C808C: mul.d       $f12, $f4, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f4.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f4.d, ctx->f14.d);
    // 0x800C8090: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C8094: nop

    // 0x800C8098: bc1fl       L_800C80AC
    if (!c1cs) {
        // 0x800C809C: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C80AC;
    }
    goto skip_5;
    // 0x800C809C: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_5:
    // 0x800C80A0: b           L_800C80AC
    // 0x800C80A4: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C80AC;
    // 0x800C80A4: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C80A8: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C80AC:
    // 0x800C80AC: trunc.w.d   $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    ctx->f10.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C80B0: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x800C80B4: nop

    // 0x800C80B8: sb          $t8, 0x19($s0)
    MEM_B(0X19, ctx->r16) = ctx->r24;
    // 0x800C80BC: lwc1        $f6, 0xC4($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C80C0: cvt.d.s     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.fl); 
    ctx->f8.d = CVT_D_S(ctx->f6.fl);
    // 0x800C80C4: mul.d       $f12, $f8, $f14
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f8.d); NAN_CHECK(ctx->f14.d); 
    ctx->f12.d = MUL_D(ctx->f8.d, ctx->f14.d);
    // 0x800C80C8: c.lt.d      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.d < ctx->f2.d;
    // 0x800C80CC: nop

    // 0x800C80D0: bc1fl       L_800C80E4
    if (!c1cs) {
        // 0x800C80D4: mov.d       $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
            goto L_800C80E4;
    }
    goto skip_6;
    // 0x800C80D4: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
    skip_6:
    // 0x800C80D8: b           L_800C80E4
    // 0x800C80DC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
        goto L_800C80E4;
    // 0x800C80DC: mov.d       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.d = ctx->f12.d;
    // 0x800C80E0: mov.d       $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    ctx->f0.d = ctx->f2.d;
L_800C80E4:
    // 0x800C80E4: trunc.w.d   $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    ctx->f4.u32l = TRUNC_W_D(ctx->f0.d);
    // 0x800C80E8: sb          $zero, 0x0($s0)
    MEM_B(0X0, ctx->r16) = 0;
    // 0x800C80EC: sb          $zero, 0x1($s0)
    MEM_B(0X1, ctx->r16) = 0;
    // 0x800C80F0: sb          $zero, 0x2($s0)
    MEM_B(0X2, ctx->r16) = 0;
    // 0x800C80F4: mfc1        $t2, $f4
    ctx->r10 = (int32_t)ctx->f4.u32l;
    // 0x800C80F8: sb          $zero, 0x3($s0)
    MEM_B(0X3, ctx->r16) = 0;
    // 0x800C80FC: sb          $zero, 0x4($s0)
    MEM_B(0X4, ctx->r16) = 0;
    // 0x800C8100: sb          $zero, 0x5($s0)
    MEM_B(0X5, ctx->r16) = 0;
    // 0x800C8104: sb          $zero, 0x6($s0)
    MEM_B(0X6, ctx->r16) = 0;
    // 0x800C8108: sb          $zero, 0x7($s0)
    MEM_B(0X7, ctx->r16) = 0;
    // 0x800C810C: sb          $zero, 0x10($s0)
    MEM_B(0X10, ctx->r16) = 0;
    // 0x800C8110: sb          $v0, 0x11($s0)
    MEM_B(0X11, ctx->r16) = ctx->r2;
    // 0x800C8114: sb          $zero, 0x12($s0)
    MEM_B(0X12, ctx->r16) = 0;
    // 0x800C8118: sb          $zero, 0x13($s0)
    MEM_B(0X13, ctx->r16) = 0;
    // 0x800C811C: sb          $zero, 0x14($s0)
    MEM_B(0X14, ctx->r16) = 0;
    // 0x800C8120: sb          $v0, 0x15($s0)
    MEM_B(0X15, ctx->r16) = ctx->r2;
    // 0x800C8124: sb          $zero, 0x16($s0)
    MEM_B(0X16, ctx->r16) = 0;
    // 0x800C8128: sb          $zero, 0x17($s0)
    MEM_B(0X17, ctx->r16) = 0;
    // 0x800C812C: sb          $t2, 0x1A($s0)
    MEM_B(0X1A, ctx->r16) = ctx->r10;
    // 0x800C8130: swc1        $f22, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->f22.u32l;
    // 0x800C8134: lwc1        $f18, 0xA4($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0XA4);
    // 0x800C8138: lwc1        $f16, 0xA8($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x800C813C: lwc1        $f14, 0xAC($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0XAC);
    // 0x800C8140: mul.s       $f10, $f18, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 22);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f22.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f22.fl);
    // 0x800C8144: lwc1        $f0, 0xBC($sp)
    ctx->f0.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C8148: lwc1        $f12, 0xC0($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C814C: mul.s       $f6, $f16, $f24
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f24.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f24.fl);
    // 0x800C8150: lwc1        $f2, 0xC4($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C8154: swc1        $f24, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f24.u32l;
    // 0x800C8158: mul.s       $f4, $f14, $f26
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f26.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f26.fl);
    // 0x800C815C: swc1        $f26, 0x20($s1)
    MEM_W(0X20, ctx->r17) = ctx->f26.u32l;
    // 0x800C8160: swc1        $f0, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->f0.u32l;
    // 0x800C8164: swc1        $f12, 0x14($s1)
    MEM_W(0X14, ctx->r17) = ctx->f12.u32l;
    // 0x800C8168: swc1        $f2, 0x24($s1)
    MEM_W(0X24, ctx->r17) = ctx->f2.u32l;
    // 0x800C816C: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800C8170: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800C8174: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C8178: mul.s       $f8, $f18, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800C817C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800C8180: mul.s       $f4, $f16, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f12.fl);
    // 0x800C8184: neg.s       $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = -ctx->f10.fl;
    // 0x800C8188: swc1        $f6, 0x30($s1)
    MEM_W(0X30, ctx->r17) = ctx->f6.u32l;
    // 0x800C818C: mul.s       $f6, $f14, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x800C8190: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C8194: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800C8198: mul.s       $f10, $f18, $f28
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f28.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f28.fl);
    // 0x800C819C: neg.s       $f4, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = -ctx->f8.fl;
    // 0x800C81A0: mul.s       $f6, $f16, $f30
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 30);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f30.fl); 
    ctx->f6.fl = MUL_S(ctx->f16.fl, ctx->f30.fl);
    // 0x800C81A4: swc1        $f4, 0x34($s1)
    MEM_W(0X34, ctx->r17) = ctx->f4.u32l;
    // 0x800C81A8: lwc1        $f2, 0x88($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X88);
    // 0x800C81AC: swc1        $f28, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->f28.u32l;
    // 0x800C81B0: swc1        $f30, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->f30.u32l;
    // 0x800C81B4: mul.s       $f4, $f14, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f2.fl);
    // 0x800C81B8: swc1        $f0, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f0.u32l;
    // 0x800C81BC: add.s       $f8, $f10, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800C81C0: swc1        $f0, 0x1C($s1)
    MEM_W(0X1C, ctx->r17) = ctx->f0.u32l;
    // 0x800C81C4: swc1        $f0, 0x2C($s1)
    MEM_W(0X2C, ctx->r17) = ctx->f0.u32l;
    // 0x800C81C8: swc1        $f2, 0x28($s1)
    MEM_W(0X28, ctx->r17) = ctx->f2.u32l;
    // 0x800C81CC: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800C81D0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x800C81D4: neg.s       $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = -ctx->f10.fl;
    // 0x800C81D8: swc1        $f8, 0x3C($s1)
    MEM_W(0X3C, ctx->r17) = ctx->f8.u32l;
    // 0x800C81DC: swc1        $f6, 0x38($s1)
    MEM_W(0X38, ctx->r17) = ctx->f6.u32l;
    // 0x800C81E0: lw          $ra, 0x4C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X4C);
    // 0x800C81E4: lw          $s1, 0x48($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X48);
    // 0x800C81E8: lw          $s0, 0x44($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X44);
    // 0x800C81EC: ldc1        $f30, 0x38($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X38);
    // 0x800C81F0: ldc1        $f28, 0x30($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X30);
    // 0x800C81F4: ldc1        $f26, 0x28($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X28);
    // 0x800C81F8: ldc1        $f24, 0x20($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X20);
    // 0x800C81FC: ldc1        $f22, 0x18($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X18);
    // 0x800C8200: ldc1        $f20, 0x10($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X10);
    // 0x800C8204: jr          $ra
    // 0x800C8208: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    return;
    // 0x800C8208: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
;}
RECOMP_FUNC void func_800C820C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C820C: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x800C8210: lwc1        $f4, 0xA8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XA8);
    // 0x800C8214: lwc1        $f6, 0xAC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XAC);
    // 0x800C8218: lwc1        $f8, 0xB0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XB0);
    // 0x800C821C: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x800C8220: swc1        $f6, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f6.u32l;
    // 0x800C8224: lwc1        $f6, 0xC4($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XC4);
    // 0x800C8228: lwc1        $f4, 0xC0($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC0);
    // 0x800C822C: lwc1        $f10, 0xB4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XB4);
    // 0x800C8230: lwc1        $f16, 0xB8($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XB8);
    // 0x800C8234: lwc1        $f18, 0xBC($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0XBC);
    // 0x800C8238: mtc1        $a3, $f12
    ctx->f12.u32l = ctx->r7;
    // 0x800C823C: swc1        $f8, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f8.u32l;
    // 0x800C8240: swc1        $f6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f6.u32l;
    // 0x800C8244: swc1        $f4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f4.u32l;
    // 0x800C8248: swc1        $f10, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f10.u32l;
    // 0x800C824C: swc1        $f16, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f16.u32l;
    // 0x800C8250: swc1        $f18, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f18.u32l;
    // 0x800C8254: lwc1        $f18, 0xD4($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0XD4);
    // 0x800C8258: lwc1        $f16, 0xD0($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0XD0);
    // 0x800C825C: lwc1        $f10, 0xCC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XCC);
    // 0x800C8260: lwc1        $f4, 0xD8($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XD8);
    // 0x800C8264: lwc1        $f6, 0xDC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XDC);
    // 0x800C8268: lwc1        $f8, 0xC8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC8);
    // 0x800C826C: lw          $t6, 0xE0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XE0);
    // 0x800C8270: lw          $t7, 0xE4($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XE4);
    // 0x800C8274: sw          $ra, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r31;
    // 0x800C8278: sw          $a0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r4;
    // 0x800C827C: mfc1        $a3, $f12
    ctx->r7 = (int32_t)ctx->f12.u32l;
    // 0x800C8280: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    // 0x800C8284: swc1        $f18, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->f18.u32l;
    // 0x800C8288: swc1        $f16, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->f16.u32l;
    // 0x800C828C: swc1        $f10, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->f10.u32l;
    // 0x800C8290: swc1        $f4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->f4.u32l;
    // 0x800C8294: swc1        $f6, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->f6.u32l;
    // 0x800C8298: swc1        $f8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f8.u32l;
    // 0x800C829C: sw          $t6, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r14;
    // 0x800C82A0: jal         0x800C7AA0
    // 0x800C82A4: sw          $t7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r15;
    func_800C7AA0(rdram, ctx);
        goto after_0;
    // 0x800C82A4: sw          $t7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r15;
    after_0:
    // 0x800C82A8: addiu       $a0, $sp, 0x58
    ctx->r4 = ADD32(ctx->r29, 0X58);
    // 0x800C82AC: jal         0x800CCB00
    // 0x800C82B0: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    func_800CCB00(rdram, ctx);
        goto after_1;
    // 0x800C82B0: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    after_1:
    // 0x800C82B4: lw          $ra, 0x54($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X54);
    // 0x800C82B8: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    // 0x800C82BC: jr          $ra
    // 0x800C82C0: nop

    return;
    // 0x800C82C0: nop

    // 0x800C82C4: nop

    // 0x800C82C8: nop

    // 0x800C82CC: nop

;}
RECOMP_FUNC void __osPfsDeclearPage(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C9604: addiu       $sp, $sp, -0x80
    ctx->r29 = ADD32(ctx->r29, -0X80);
    // 0x800C9608: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800C960C: lbu         $s4, 0x93($sp)
    ctx->r20 = MEM_BU(ctx->r29, 0X93);
    // 0x800C9610: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800C9614: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800C9618: or          $s7, $a2, $zero
    ctx->r23 = ctx->r6 | 0;
    // 0x800C961C: or          $fp, $a1, $zero
    ctx->r30 = ctx->r5 | 0;
    // 0x800C9620: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800C9624: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800C9628: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800C962C: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800C9630: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800C9634: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800C9638: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C963C: sw          $a0, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r4;
    // 0x800C9640: sw          $a3, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->r7;
    // 0x800C9644: blez        $s4, L_800C9654
    if (SIGNED(ctx->r20) <= 0) {
        // 0x800C9648: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_800C9654;
    }
    // 0x800C9648: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x800C964C: b           L_800C9664
    // 0x800C9650: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_800C9664;
    // 0x800C9650: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_800C9654:
    // 0x800C9654: lw          $t6, 0x80($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X80);
    // 0x800C9658: nop

    // 0x800C965C: lw          $v0, 0x60($t6)
    ctx->r2 = MEM_W(ctx->r14, 0X60);
    // 0x800C9660: nop

L_800C9664:
    // 0x800C9664: slti        $at, $v0, 0x80
    ctx->r1 = SIGNED(ctx->r2) < 0X80 ? 1 : 0;
    // 0x800C9668: beq         $at, $zero, L_800C969C
    if (ctx->r1 == 0) {
        // 0x800C966C: or          $s1, $v0, $zero
        ctx->r17 = ctx->r2 | 0;
            goto L_800C969C;
    }
    // 0x800C966C: or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // 0x800C9670: sll         $t7, $v0, 1
    ctx->r15 = S32(ctx->r2 << 1);
    // 0x800C9674: addu        $s0, $fp, $t7
    ctx->r16 = ADD32(ctx->r30, ctx->r15);
    // 0x800C9678: addiu       $s6, $zero, 0x80
    ctx->r22 = ADD32(0, 0X80);
    // 0x800C967C: addiu       $s3, $zero, 0x3
    ctx->r19 = ADD32(0, 0X3);
L_800C9680:
    // 0x800C9680: lhu         $t8, 0x0($s0)
    ctx->r24 = MEM_HU(ctx->r16, 0X0);
    // 0x800C9684: nop

    // 0x800C9688: beq         $s3, $t8, L_800C969C
    if (ctx->r19 == ctx->r24) {
        // 0x800C968C: nop
    
            goto L_800C969C;
    }
    // 0x800C968C: nop

    // 0x800C9690: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800C9694: bne         $s1, $s6, L_800C9680
    if (ctx->r17 != ctx->r22) {
        // 0x800C9698: addiu       $s0, $s0, 0x2
        ctx->r16 = ADD32(ctx->r16, 0X2);
            goto L_800C9680;
    }
    // 0x800C9698: addiu       $s0, $s0, 0x2
    ctx->r16 = ADD32(ctx->r16, 0X2);
L_800C969C:
    // 0x800C969C: addiu       $s6, $zero, 0x80
    ctx->r22 = ADD32(0, 0X80);
    // 0x800C96A0: bne         $s1, $s6, L_800C96BC
    if (ctx->r17 != ctx->r22) {
        // 0x800C96A4: addiu       $s3, $zero, 0x3
        ctx->r19 = ADD32(0, 0X3);
            goto L_800C96BC;
    }
    // 0x800C96A4: addiu       $s3, $zero, 0x3
    ctx->r19 = ADD32(0, 0X3);
    // 0x800C96A8: lw          $t1, 0x8C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X8C);
    // 0x800C96AC: addiu       $t9, $zero, -0x1
    ctx->r25 = ADD32(0, -0X1);
    // 0x800C96B0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800C96B4: b           L_800C97D4
    // 0x800C96B8: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
        goto L_800C97D4;
    // 0x800C96B8: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
L_800C96BC:
    // 0x800C96BC: addiu       $v0, $sp, 0x54
    ctx->r2 = ADD32(ctx->r29, 0X54);
    // 0x800C96C0: addiu       $v1, $sp, 0x74
    ctx->r3 = ADD32(ctx->r29, 0X74);
L_800C96C4:
    // 0x800C96C4: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800C96C8: sb          $zero, -0x3($v0)
    MEM_B(-0X3, ctx->r2) = 0;
    // 0x800C96CC: sb          $zero, -0x2($v0)
    MEM_B(-0X2, ctx->r2) = 0;
    // 0x800C96D0: sb          $zero, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = 0;
    // 0x800C96D4: bne         $v0, $v1, L_800C96C4
    if (ctx->r2 != ctx->r3) {
        // 0x800C96D8: sb          $zero, -0x4($v0)
        MEM_B(-0X4, ctx->r2) = 0;
            goto L_800C96C4;
    }
    // 0x800C96D8: sb          $zero, -0x4($v0)
    MEM_B(-0X4, ctx->r2) = 0;
    // 0x800C96DC: lw          $s2, 0x94($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X94);
    // 0x800C96E0: sw          $s1, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r17;
    // 0x800C96E4: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x800C96E8: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x800C96EC: slti        $at, $s7, 0x2
    ctx->r1 = SIGNED(ctx->r23) < 0X2 ? 1 : 0;
    // 0x800C96F0: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800C96F4: bne         $at, $zero, L_800C9778
    if (ctx->r1 != 0) {
        // 0x800C96F8: sw          $t2, 0x0($s2)
        MEM_W(0X0, ctx->r18) = ctx->r10;
            goto L_800C9778;
    }
    // 0x800C96F8: sw          $t2, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r10;
    // 0x800C96FC: slti        $at, $s1, 0x80
    ctx->r1 = SIGNED(ctx->r17) < 0X80 ? 1 : 0;
    // 0x800C9700: beq         $at, $zero, L_800C9778
    if (ctx->r1 == 0) {
        // 0x800C9704: sll         $t3, $s1, 1
        ctx->r11 = S32(ctx->r17 << 1);
            goto L_800C9778;
    }
    // 0x800C9704: sll         $t3, $s1, 1
    ctx->r11 = S32(ctx->r17 << 1);
    // 0x800C9708: addu        $s0, $fp, $t3
    ctx->r16 = ADD32(ctx->r30, ctx->r11);
    // 0x800C970C: addiu       $s5, $sp, 0x54
    ctx->r21 = ADD32(ctx->r29, 0X54);
L_800C9710:
    // 0x800C9710: lhu         $t4, 0x0($s0)
    ctx->r12 = MEM_HU(ctx->r16, 0X0);
    // 0x800C9714: sll         $t5, $a1, 1
    ctx->r13 = S32(ctx->r5 << 1);
    // 0x800C9718: bne         $s3, $t4, L_800C9758
    if (ctx->r19 != ctx->r12) {
        // 0x800C971C: addu        $v0, $fp, $t5
        ctx->r2 = ADD32(ctx->r30, ctx->r13);
            goto L_800C9758;
    }
    // 0x800C971C: addu        $v0, $fp, $t5
    ctx->r2 = ADD32(ctx->r30, ctx->r13);
    // 0x800C9720: sb          $s4, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r20;
    // 0x800C9724: sb          $s1, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r17;
    // 0x800C9728: lw          $a0, 0x80($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X80);
    // 0x800C972C: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x800C9730: jal         0x800C9804
    // 0x800C9734: andi        $a3, $s4, 0xFF
    ctx->r7 = ctx->r20 & 0XFF;
    __osClearPage(rdram, ctx);
        goto after_0;
    // 0x800C9734: andi        $a3, $s4, 0xFF
    ctx->r7 = ctx->r20 & 0XFF;
    after_0:
    // 0x800C9738: beq         $v0, $zero, L_800C9748
    if (ctx->r2 == 0) {
        // 0x800C973C: or          $t0, $v0, $zero
        ctx->r8 = ctx->r2 | 0;
            goto L_800C9748;
    }
    // 0x800C973C: or          $t0, $v0, $zero
    ctx->r8 = ctx->r2 | 0;
    // 0x800C9740: b           L_800C97D8
    // 0x800C9744: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
        goto L_800C97D8;
    // 0x800C9744: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_800C9748:
    // 0x800C9748: lw          $t6, 0x0($s2)
    ctx->r14 = MEM_W(ctx->r18, 0X0);
    // 0x800C974C: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x800C9750: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x800C9754: sw          $t7, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r15;
L_800C9758:
    // 0x800C9758: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    // 0x800C975C: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800C9760: slt         $at, $t8, $s7
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r23) ? 1 : 0;
    // 0x800C9764: beq         $at, $zero, L_800C9778
    if (ctx->r1 == 0) {
        // 0x800C9768: addiu       $s0, $s0, 0x2
        ctx->r16 = ADD32(ctx->r16, 0X2);
            goto L_800C9778;
    }
    // 0x800C9768: addiu       $s0, $s0, 0x2
    ctx->r16 = ADD32(ctx->r16, 0X2);
    // 0x800C976C: slti        $at, $s1, 0x80
    ctx->r1 = SIGNED(ctx->r17) < 0X80 ? 1 : 0;
    // 0x800C9770: bne         $at, $zero, L_800C9710
    if (ctx->r1 != 0) {
        // 0x800C9774: nop
    
            goto L_800C9710;
    }
    // 0x800C9774: nop

L_800C9778:
    // 0x800C9778: lw          $t9, 0x78($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X78);
    // 0x800C977C: lw          $t1, 0x8C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X8C);
    // 0x800C9780: addiu       $s5, $sp, 0x54
    ctx->r21 = ADD32(ctx->r29, 0X54);
    // 0x800C9784: bne         $s1, $s6, L_800C97A8
    if (ctx->r17 != ctx->r22) {
        // 0x800C9788: sw          $t9, 0x0($t1)
        MEM_W(0X0, ctx->r9) = ctx->r25;
            goto L_800C97A8;
    }
    // 0x800C9788: sw          $t9, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r25;
    // 0x800C978C: lw          $t2, 0x0($s2)
    ctx->r10 = MEM_W(ctx->r18, 0X0);
    // 0x800C9790: lw          $t3, 0x98($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X98);
    // 0x800C9794: slt         $at, $t2, $s7
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r23) ? 1 : 0;
    // 0x800C9798: beq         $at, $zero, L_800C97A8
    if (ctx->r1 == 0) {
        // 0x800C979C: or          $v0, $t0, $zero
        ctx->r2 = ctx->r8 | 0;
            goto L_800C97A8;
    }
    // 0x800C979C: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
    // 0x800C97A0: b           L_800C97D4
    // 0x800C97A4: sw          $a1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r5;
        goto L_800C97D4;
    // 0x800C97A4: sw          $a1, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r5;
L_800C97A8:
    // 0x800C97A8: sll         $t5, $a1, 1
    ctx->r13 = S32(ctx->r5 << 1);
    // 0x800C97AC: addu        $t6, $fp, $t5
    ctx->r14 = ADD32(ctx->r30, ctx->r13);
    // 0x800C97B0: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
    // 0x800C97B4: sh          $t4, 0x0($t6)
    MEM_H(0X0, ctx->r14) = ctx->r12;
    // 0x800C97B8: lw          $a0, 0x80($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X80);
    // 0x800C97BC: or          $a2, $s5, $zero
    ctx->r6 = ctx->r21 | 0;
    // 0x800C97C0: jal         0x800C9804
    // 0x800C97C4: andi        $a3, $s4, 0xFF
    ctx->r7 = ctx->r20 & 0XFF;
    __osClearPage(rdram, ctx);
        goto after_1;
    // 0x800C97C4: andi        $a3, $s4, 0xFF
    ctx->r7 = ctx->r20 & 0XFF;
    after_1:
    // 0x800C97C8: lw          $t7, 0x98($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X98);
    // 0x800C97CC: nop

    // 0x800C97D0: sw          $zero, 0x0($t7)
    MEM_W(0X0, ctx->r15) = 0;
L_800C97D4:
    // 0x800C97D4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
L_800C97D8:
    // 0x800C97D8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C97DC: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800C97E0: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800C97E4: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800C97E8: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800C97EC: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800C97F0: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800C97F4: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800C97F8: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800C97FC: jr          $ra
    // 0x800C9800: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
    return;
    // 0x800C9800: addiu       $sp, $sp, 0x80
    ctx->r29 = ADD32(ctx->r29, 0X80);
;}
RECOMP_FUNC void __osClearPage(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C9804: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800C9808: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800C980C: sw          $s4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r20;
    // 0x800C9810: sw          $s3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r19;
    // 0x800C9814: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x800C9818: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x800C981C: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x800C9820: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    // 0x800C9824: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800C9828: or          $s3, $a1, $zero
    ctx->r19 = ctx->r5 | 0;
    // 0x800C982C: or          $s4, $a2, $zero
    ctx->r20 = ctx->r6 | 0;
    // 0x800C9830: jal         0x800CE130
    // 0x800C9834: sb          $a3, 0x65($a0)
    MEM_B(0X65, ctx->r4) = ctx->r7;
    __osPfsSelectBank_recomp(rdram, ctx);
        goto after_0;
    // 0x800C9834: sb          $a3, 0x65($a0)
    MEM_B(0X65, ctx->r4) = ctx->r7;
    after_0:
    // 0x800C9838: beq         $v0, $zero, L_800C9848
    if (ctx->r2 == 0) {
        // 0x800C983C: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800C9848;
    }
    // 0x800C983C: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800C9840: b           L_800C9888
    // 0x800C9844: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_800C9888;
    // 0x800C9844: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_800C9848:
    // 0x800C9848: sll         $s1, $s3, 3
    ctx->r17 = S32(ctx->r19 << 3);
    // 0x800C984C: addiu       $s3, $zero, 0x8
    ctx->r19 = ADD32(0, 0X8);
L_800C9850:
    // 0x800C9850: lw          $a0, 0x4($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X4);
    // 0x800C9854: lw          $a1, 0x8($s2)
    ctx->r5 = MEM_W(ctx->r18, 0X8);
    // 0x800C9858: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x800C985C: andi        $a2, $s1, 0xFFFF
    ctx->r6 = ctx->r17 & 0XFFFF;
    // 0x800C9860: jal         0x800CEFA0
    // 0x800C9864: or          $a3, $s4, $zero
    ctx->r7 = ctx->r20 | 0;
    __osContRamWrite_recomp(rdram, ctx);
        goto after_1;
    // 0x800C9864: or          $a3, $s4, $zero
    ctx->r7 = ctx->r20 | 0;
    after_1:
    // 0x800C9868: bne         $v0, $zero, L_800C9878
    if (ctx->r2 != 0) {
        // 0x800C986C: addiu       $s0, $s0, 0x1
        ctx->r16 = ADD32(ctx->r16, 0X1);
            goto L_800C9878;
    }
    // 0x800C986C: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800C9870: bne         $s0, $s3, L_800C9850
    if (ctx->r16 != ctx->r19) {
        // 0x800C9874: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_800C9850;
    }
    // 0x800C9874: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
L_800C9878:
    // 0x800C9878: sb          $zero, 0x65($s2)
    MEM_B(0X65, ctx->r18) = 0;
    // 0x800C987C: jal         0x800CE130
    // 0x800C9880: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    __osPfsSelectBank_recomp(rdram, ctx);
        goto after_2;
    // 0x800C9880: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    after_2:
    // 0x800C9884: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_800C9888:
    // 0x800C9888: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x800C988C: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x800C9890: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x800C9894: lw          $s3, 0x2C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X2C);
    // 0x800C9898: lw          $s4, 0x30($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X30);
    // 0x800C989C: jr          $ra
    // 0x800C98A0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800C98A0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800C98A4: nop

    // 0x800C98A8: nop

    // 0x800C98AC: nop

;}
RECOMP_FUNC void __osPfsReleasePages(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C9B30: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x800C9B34: sw          $a2, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r6;
    // 0x800C9B38: lbu         $t6, 0x5B($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X5B);
    // 0x800C9B3C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x800C9B40: sll         $t7, $t6, 1
    ctx->r15 = S32(ctx->r14 << 1);
    // 0x800C9B44: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800C9B48: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800C9B4C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800C9B50: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800C9B54: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800C9B58: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800C9B5C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C9B60: addu        $v1, $a1, $t7
    ctx->r3 = ADD32(ctx->r5, ctx->r15);
    // 0x800C9B64: lhu         $at, 0x0($v1)
    ctx->r1 = MEM_HU(ctx->r3, 0X0);
    // 0x800C9B68: addiu       $s4, $sp, 0x4C
    ctx->r20 = ADD32(ctx->r29, 0X4C);
    // 0x800C9B6C: sh          $at, 0x0($s4)
    MEM_H(0X0, ctx->r20) = ctx->r1;
    // 0x800C9B70: lhu         $t1, 0x4C($sp)
    ctx->r9 = MEM_HU(ctx->r29, 0X4C);
    // 0x800C9B74: addiu       $s0, $zero, 0x1
    ctx->r16 = ADD32(0, 0X1);
    // 0x800C9B78: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800C9B7C: or          $s3, $a1, $zero
    ctx->r19 = ctx->r5 | 0;
    // 0x800C9B80: beq         $s0, $t1, L_800C9BB0
    if (ctx->r16 == ctx->r9) {
        // 0x800C9B84: or          $s6, $a3, $zero
        ctx->r22 = ctx->r7 | 0;
            goto L_800C9BB0;
    }
    // 0x800C9B84: or          $s6, $a3, $zero
    ctx->r22 = ctx->r7 | 0;
    // 0x800C9B88: lbu         $t2, 0x4C($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X4C);
    // 0x800C9B8C: lbu         $s1, 0x63($sp)
    ctx->r17 = MEM_BU(ctx->r29, 0X63);
    // 0x800C9B90: blez        $t2, L_800C9BA0
    if (SIGNED(ctx->r10) <= 0) {
        // 0x800C9B94: nop
    
            goto L_800C9BA0;
    }
    // 0x800C9B94: nop

    // 0x800C9B98: b           L_800C9BA8
    // 0x800C9B9C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_800C9BA8;
    // 0x800C9B9C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_800C9BA0:
    // 0x800C9BA0: lw          $v0, 0x60($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X60);
    // 0x800C9BA4: nop

L_800C9BA8:
    // 0x800C9BA8: b           L_800C9BD4
    // 0x800C9BAC: lbu         $t3, 0x4D($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X4D);
        goto L_800C9BD4;
    // 0x800C9BAC: lbu         $t3, 0x4D($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X4D);
L_800C9BB0:
    // 0x800C9BB0: lbu         $s1, 0x63($sp)
    ctx->r17 = MEM_BU(ctx->r29, 0X63);
    // 0x800C9BB4: nop

    // 0x800C9BB8: blez        $s1, L_800C9BC8
    if (SIGNED(ctx->r17) <= 0) {
        // 0x800C9BBC: nop
    
            goto L_800C9BC8;
    }
    // 0x800C9BBC: nop

    // 0x800C9BC0: b           L_800C9BD0
    // 0x800C9BC4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_800C9BD0;
    // 0x800C9BC4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_800C9BC8:
    // 0x800C9BC8: lw          $v0, 0x60($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X60);
    // 0x800C9BCC: nop

L_800C9BD0:
    // 0x800C9BD0: lbu         $t3, 0x4D($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X4D);
L_800C9BD4:
    // 0x800C9BD4: lhu         $t4, 0x4C($sp)
    ctx->r12 = MEM_HU(ctx->r29, 0X4C);
    // 0x800C9BD8: slt         $at, $t3, $v0
    ctx->r1 = SIGNED(ctx->r11) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800C9BDC: beq         $at, $zero, L_800C9BF4
    if (ctx->r1 == 0) {
        // 0x800C9BE0: or          $a0, $s2, $zero
        ctx->r4 = ctx->r18 | 0;
            goto L_800C9BF4;
    }
    // 0x800C9BE0: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800C9BE4: beq         $s0, $t4, L_800C9BF8
    if (ctx->r16 == ctx->r12) {
        // 0x800C9BE8: lw          $t5, 0x64($sp)
        ctx->r13 = MEM_W(ctx->r29, 0X64);
            goto L_800C9BF8;
    }
    // 0x800C9BE8: lw          $t5, 0x64($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X64);
    // 0x800C9BEC: b           L_800C9D0C
    // 0x800C9BF0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
        goto L_800C9D0C;
    // 0x800C9BF0: addiu       $v0, $zero, 0x3
    ctx->r2 = ADD32(0, 0X3);
L_800C9BF4:
    // 0x800C9BF4: lw          $t5, 0x64($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X64);
L_800C9BF8:
    // 0x800C9BF8: lhu         $at, 0x0($s4)
    ctx->r1 = MEM_HU(ctx->r20, 0X0);
    // 0x800C9BFC: addiu       $s5, $zero, 0x3
    ctx->r21 = ADD32(0, 0X3);
    // 0x800C9C00: sh          $at, 0x0($t5)
    MEM_H(0X0, ctx->r13) = ctx->r1;
    // 0x800C9C04: lw          $t9, 0x68($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X68);
    // 0x800C9C08: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x800C9C0C: bne         $t9, $s0, L_800C9C18
    if (ctx->r25 != ctx->r16) {
        // 0x800C9C10: andi        $a3, $s1, 0xFF
        ctx->r7 = ctx->r17 & 0XFF;
            goto L_800C9C18;
    }
    // 0x800C9C10: andi        $a3, $s1, 0xFF
    ctx->r7 = ctx->r17 & 0XFF;
    // 0x800C9C14: sh          $s5, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r21;
L_800C9C18:
    // 0x800C9C18: lbu         $a1, 0x5B($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X5B);
    // 0x800C9C1C: jal         0x800C9D34
    // 0x800C9C20: addiu       $s5, $zero, 0x3
    ctx->r21 = ADD32(0, 0X3);
    __osBlockSum(rdram, ctx);
        goto after_0;
    // 0x800C9C20: addiu       $s5, $zero, 0x3
    ctx->r21 = ADD32(0, 0X3);
    after_0:
    // 0x800C9C24: beq         $v0, $zero, L_800C9C38
    if (ctx->r2 == 0) {
        // 0x800C9C28: lhu         $t8, 0x4C($sp)
        ctx->r24 = MEM_HU(ctx->r29, 0X4C);
            goto L_800C9C38;
    }
    // 0x800C9C28: lhu         $t8, 0x4C($sp)
    ctx->r24 = MEM_HU(ctx->r29, 0X4C);
    // 0x800C9C2C: b           L_800C9D10
    // 0x800C9C30: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_800C9D10;
    // 0x800C9C30: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800C9C34: lhu         $t8, 0x4C($sp)
    ctx->r24 = MEM_HU(ctx->r29, 0X4C);
L_800C9C38:
    // 0x800C9C38: lhu         $t0, 0x4C($sp)
    ctx->r8 = MEM_HU(ctx->r29, 0X4C);
    // 0x800C9C3C: bne         $s0, $t8, L_800C9C4C
    if (ctx->r16 != ctx->r24) {
        // 0x800C9C40: nop
    
            goto L_800C9C4C;
    }
    // 0x800C9C40: nop

    // 0x800C9C44: b           L_800C9D0C
    // 0x800C9C48: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800C9D0C;
    // 0x800C9C48: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800C9C4C:
    // 0x800C9C4C: lw          $v0, 0x60($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X60);
    // 0x800C9C50: addiu       $s0, $sp, 0x48
    ctx->r16 = ADD32(ctx->r29, 0X48);
    // 0x800C9C54: slt         $at, $t0, $v0
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800C9C58: bne         $at, $zero, L_800C9CE4
    if (ctx->r1 != 0) {
        // 0x800C9C5C: lhu         $t3, 0x4C($sp)
        ctx->r11 = MEM_HU(ctx->r29, 0X4C);
            goto L_800C9CE4;
    }
    // 0x800C9C5C: lhu         $t3, 0x4C($sp)
    ctx->r11 = MEM_HU(ctx->r29, 0X4C);
L_800C9C60:
    // 0x800C9C60: lhu         $at, 0x0($s4)
    ctx->r1 = MEM_HU(ctx->r20, 0X0);
    // 0x800C9C64: or          $a0, $s2, $zero
    ctx->r4 = ctx->r18 | 0;
    // 0x800C9C68: sh          $at, 0x0($s0)
    MEM_H(0X0, ctx->r16) = ctx->r1;
    // 0x800C9C6C: lbu         $t3, 0x4D($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X4D);
    // 0x800C9C70: or          $a2, $s6, $zero
    ctx->r6 = ctx->r22 | 0;
    // 0x800C9C74: sll         $t4, $t3, 1
    ctx->r12 = S32(ctx->r11 << 1);
    // 0x800C9C78: addu        $t6, $s3, $t4
    ctx->r14 = ADD32(ctx->r19, ctx->r12);
    // 0x800C9C7C: lhu         $at, 0x0($t6)
    ctx->r1 = MEM_HU(ctx->r14, 0X0);
    // 0x800C9C80: andi        $a3, $s1, 0xFF
    ctx->r7 = ctx->r17 & 0XFF;
    // 0x800C9C84: sh          $at, 0x0($s4)
    MEM_H(0X0, ctx->r20) = ctx->r1;
    // 0x800C9C88: lbu         $a1, 0x49($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X49);
    // 0x800C9C8C: nop

    // 0x800C9C90: sll         $t8, $a1, 1
    ctx->r24 = S32(ctx->r5 << 1);
    // 0x800C9C94: addu        $t0, $s3, $t8
    ctx->r8 = ADD32(ctx->r19, ctx->r24);
    // 0x800C9C98: jal         0x800C9D34
    // 0x800C9C9C: sh          $s5, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r21;
    __osBlockSum(rdram, ctx);
        goto after_1;
    // 0x800C9C9C: sh          $s5, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r21;
    after_1:
    // 0x800C9CA0: beq         $v0, $zero, L_800C9CB4
    if (ctx->r2 == 0) {
        // 0x800C9CA4: lbu         $t1, 0x4C($sp)
        ctx->r9 = MEM_BU(ctx->r29, 0X4C);
            goto L_800C9CB4;
    }
    // 0x800C9CA4: lbu         $t1, 0x4C($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X4C);
    // 0x800C9CA8: b           L_800C9D10
    // 0x800C9CAC: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
        goto L_800C9D10;
    // 0x800C9CAC: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x800C9CB0: lbu         $t1, 0x4C($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X4C);
L_800C9CB4:
    // 0x800C9CB4: lhu         $t2, 0x4C($sp)
    ctx->r10 = MEM_HU(ctx->r29, 0X4C);
    // 0x800C9CB8: beq         $s1, $t1, L_800C9CCC
    if (ctx->r17 == ctx->r9) {
        // 0x800C9CBC: nop
    
            goto L_800C9CCC;
    }
    // 0x800C9CBC: nop

    // 0x800C9CC0: lw          $v0, 0x60($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X60);
    // 0x800C9CC4: b           L_800C9CE4
    // 0x800C9CC8: lhu         $t3, 0x4C($sp)
    ctx->r11 = MEM_HU(ctx->r29, 0X4C);
        goto L_800C9CE4;
    // 0x800C9CC8: lhu         $t3, 0x4C($sp)
    ctx->r11 = MEM_HU(ctx->r29, 0X4C);
L_800C9CCC:
    // 0x800C9CCC: lw          $v0, 0x60($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X60);
    // 0x800C9CD0: nop

    // 0x800C9CD4: slt         $at, $t2, $v0
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800C9CD8: beq         $at, $zero, L_800C9C60
    if (ctx->r1 == 0) {
        // 0x800C9CDC: nop
    
            goto L_800C9C60;
    }
    // 0x800C9CDC: nop

    // 0x800C9CE0: lhu         $t3, 0x4C($sp)
    ctx->r11 = MEM_HU(ctx->r29, 0X4C);
L_800C9CE4:
    // 0x800C9CE4: lbu         $t4, 0x4D($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X4D);
    // 0x800C9CE8: slt         $at, $t3, $v0
    ctx->r1 = SIGNED(ctx->r11) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800C9CEC: bne         $at, $zero, L_800C9CFC
    if (ctx->r1 != 0) {
        // 0x800C9CF0: sll         $t5, $t4, 1
        ctx->r13 = S32(ctx->r12 << 1);
            goto L_800C9CFC;
    }
    // 0x800C9CF0: sll         $t5, $t4, 1
    ctx->r13 = S32(ctx->r12 << 1);
    // 0x800C9CF4: addu        $t6, $s3, $t5
    ctx->r14 = ADD32(ctx->r19, ctx->r13);
    // 0x800C9CF8: sh          $s5, 0x0($t6)
    MEM_H(0X0, ctx->r14) = ctx->r21;
L_800C9CFC:
    // 0x800C9CFC: lw          $t7, 0x64($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X64);
    // 0x800C9D00: lhu         $at, 0x0($s4)
    ctx->r1 = MEM_HU(ctx->r20, 0X0);
    // 0x800C9D04: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800C9D08: sh          $at, 0x0($t7)
    MEM_H(0X0, ctx->r15) = ctx->r1;
L_800C9D0C:
    // 0x800C9D0C: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
L_800C9D10:
    // 0x800C9D10: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C9D14: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800C9D18: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800C9D1C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800C9D20: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800C9D24: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800C9D28: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800C9D2C: jr          $ra
    // 0x800C9D30: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x800C9D30: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void __osBlockSum(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C9D34: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x800C9D38: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800C9D3C: sw          $s5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r21;
    // 0x800C9D40: sw          $s4, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r20;
    // 0x800C9D44: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800C9D48: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800C9D4C: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800C9D50: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800C9D54: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x800C9D58: sw          $a3, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r7;
    // 0x800C9D5C: andi        $s1, $a1, 0xFF
    ctx->r17 = ctx->r5 & 0XFF;
    // 0x800C9D60: or          $s2, $a2, $zero
    ctx->r18 = ctx->r6 | 0;
    // 0x800C9D64: or          $s3, $a0, $zero
    ctx->r19 = ctx->r4 | 0;
    // 0x800C9D68: jal         0x800CE130
    // 0x800C9D6C: sb          $a3, 0x65($a0)
    MEM_B(0X65, ctx->r4) = ctx->r7;
    __osPfsSelectBank_recomp(rdram, ctx);
        goto after_0;
    // 0x800C9D6C: sb          $a3, 0x65($a0)
    MEM_B(0X65, ctx->r4) = ctx->r7;
    after_0:
    // 0x800C9D70: beq         $v0, $zero, L_800C9D80
    if (ctx->r2 == 0) {
        // 0x800C9D74: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_800C9D80;
    }
    // 0x800C9D74: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800C9D78: b           L_800C9DF8
    // 0x800C9D7C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800C9DF8;
    // 0x800C9D7C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800C9D80:
    // 0x800C9D80: sll         $s4, $s1, 3
    ctx->r20 = S32(ctx->r17 << 3);
    // 0x800C9D84: addiu       $s1, $sp, 0x38
    ctx->r17 = ADD32(ctx->r29, 0X38);
    // 0x800C9D88: addiu       $s5, $zero, 0x8
    ctx->r21 = ADD32(0, 0X8);
L_800C9D8C:
    // 0x800C9D8C: addu        $a2, $s4, $s0
    ctx->r6 = ADD32(ctx->r20, ctx->r16);
    // 0x800C9D90: andi        $t7, $a2, 0xFFFF
    ctx->r15 = ctx->r6 & 0XFFFF;
    // 0x800C9D94: lw          $a0, 0x4($s3)
    ctx->r4 = MEM_W(ctx->r19, 0X4);
    // 0x800C9D98: lw          $a1, 0x8($s3)
    ctx->r5 = MEM_W(ctx->r19, 0X8);
    // 0x800C9D9C: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x800C9DA0: jal         0x800CEC10
    // 0x800C9DA4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    __osContRamRead_recomp(rdram, ctx);
        goto after_1;
    // 0x800C9DA4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_1:
    // 0x800C9DA8: beq         $v0, $zero, L_800C9DCC
    if (ctx->r2 == 0) {
        // 0x800C9DAC: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_800C9DCC;
    }
    // 0x800C9DAC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800C9DB0: sb          $zero, 0x65($s3)
    MEM_B(0X65, ctx->r19) = 0;
    // 0x800C9DB4: sw          $v0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r2;
    // 0x800C9DB8: jal         0x800CE130
    // 0x800C9DBC: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    __osPfsSelectBank_recomp(rdram, ctx);
        goto after_2;
    // 0x800C9DBC: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_2:
    // 0x800C9DC0: lw          $v0, 0x58($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X58);
    // 0x800C9DC4: b           L_800C9DF8
    // 0x800C9DC8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
        goto L_800C9DF8;
    // 0x800C9DC8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800C9DCC:
    // 0x800C9DCC: jal         0x800CD550
    // 0x800C9DD0: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    __osSumcalc(rdram, ctx);
        goto after_3;
    // 0x800C9DD0: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_3:
    // 0x800C9DD4: lhu         $t8, 0x0($s2)
    ctx->r24 = MEM_HU(ctx->r18, 0X0);
    // 0x800C9DD8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x800C9DDC: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x800C9DE0: bne         $s0, $s5, L_800C9D8C
    if (ctx->r16 != ctx->r21) {
        // 0x800C9DE4: sh          $t9, 0x0($s2)
        MEM_H(0X0, ctx->r18) = ctx->r25;
            goto L_800C9D8C;
    }
    // 0x800C9DE4: sh          $t9, 0x0($s2)
    MEM_H(0X0, ctx->r18) = ctx->r25;
    // 0x800C9DE8: sb          $zero, 0x65($s3)
    MEM_B(0X65, ctx->r19) = 0;
    // 0x800C9DEC: jal         0x800CE130
    // 0x800C9DF0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    __osPfsSelectBank_recomp(rdram, ctx);
        goto after_4;
    // 0x800C9DF0: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_4:
    // 0x800C9DF4: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
L_800C9DF8:
    // 0x800C9DF8: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800C9DFC: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800C9E00: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800C9E04: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800C9E08: lw          $s4, 0x24($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X24);
    // 0x800C9E0C: lw          $s5, 0x28($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X28);
    // 0x800C9E10: jr          $ra
    // 0x800C9E14: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x800C9E14: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    // 0x800C9E18: nop

    // 0x800C9E1C: nop

;}
RECOMP_FUNC void osPhysicalToVirtual(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C9E20: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800C9E24: jr          $ra
    // 0x800C9E28: or          $v0, $a0, $at
    ctx->r2 = ctx->r4 | ctx->r1;
    return;
    // 0x800C9E28: or          $v0, $a0, $at
    ctx->r2 = ctx->r4 | ctx->r1;
    // 0x800C9E2C: nop

;}
RECOMP_FUNC void func_800CA210(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA210: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800CA214: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800CA218: addiu       $t6, $sp, 0x24
    ctx->r14 = ADD32(ctx->r29, 0X24);
    // 0x800CA21C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800CA220: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800CA224: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x800CA228: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    // 0x800CA22C: addiu       $t7, $t6, 0x4
    ctx->r15 = ADD32(ctx->r14, 0X4);
    // 0x800CA230: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x800CA234: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x800CA238: addiu       $a0, $a0, -0x5D84
    ctx->r4 = ADD32(ctx->r4, -0X5D84);
    // 0x800CA23C: or          $a3, $t7, $zero
    ctx->r7 = ctx->r15 | 0;
    // 0x800CA240: lw          $a2, 0x24($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X24);
    // 0x800CA244: jal         0x800CF330
    // 0x800CA248: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    _Printf(rdram, ctx);
        goto after_0;
    // 0x800CA248: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    after_0:
    // 0x800CA24C: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800CA250: lw          $t8, 0x1C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X1C);
    // 0x800CA254: bltz        $t8, L_800CA268
    if (SIGNED(ctx->r24) < 0) {
        // 0x800CA258: nop
    
            goto L_800CA268;
    }
    // 0x800CA258: nop

    // 0x800CA25C: lw          $t9, 0x20($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X20);
    // 0x800CA260: addu        $t0, $t9, $t8
    ctx->r8 = ADD32(ctx->r25, ctx->r24);
    // 0x800CA264: sb          $zero, 0x0($t0)
    MEM_B(0X0, ctx->r8) = 0;
L_800CA268:
    // 0x800CA268: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800CA26C: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800CA270: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800CA274: jr          $ra
    // 0x800CA278: nop

    return;
    // 0x800CA278: nop

;}
RECOMP_FUNC void proutSprintf(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA27C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800CA280: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800CA284: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800CA288: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800CA28C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800CA290: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x800CA294: lw          $a1, 0x1C($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1C);
    // 0x800CA298: jal         0x800D04C0
    // 0x800CA29C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    memcpy_recomp(rdram, ctx);
        goto after_0;
    // 0x800CA29C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_0:
    // 0x800CA2A0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800CA2A4: lw          $t6, 0x20($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X20);
    // 0x800CA2A8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800CA2AC: jr          $ra
    // 0x800CA2B0: addu        $v0, $v0, $t6
    ctx->r2 = ADD32(ctx->r2, ctx->r14);
    return;
    // 0x800CA2B0: addu        $v0, $v0, $t6
    ctx->r2 = ADD32(ctx->r2, ctx->r14);
    // 0x800CA2B4: nop

    // 0x800CA2B8: nop

    // 0x800CA2BC: nop

;}
RECOMP_FUNC void bzero_recomp(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA500: slti        $at, $a1, 0xC
    ctx->r1 = SIGNED(ctx->r5) < 0XC ? 1 : 0;
    // 0x800CA504: bne         $at, $zero, L_800CA57C
    if (ctx->r1 != 0) {
        // 0x800CA508: negu        $v1, $a0
        ctx->r3 = SUB32(0, ctx->r4);
            goto L_800CA57C;
    }
    // 0x800CA508: negu        $v1, $a0
    ctx->r3 = SUB32(0, ctx->r4);
    // 0x800CA50C: andi        $v1, $v1, 0x3
    ctx->r3 = ctx->r3 & 0X3;
    // 0x800CA510: beq         $v1, $zero, L_800CA520
    if (ctx->r3 == 0) {
        // 0x800CA514: subu        $a1, $a1, $v1
        ctx->r5 = SUB32(ctx->r5, ctx->r3);
            goto L_800CA520;
    }
    // 0x800CA514: subu        $a1, $a1, $v1
    ctx->r5 = SUB32(ctx->r5, ctx->r3);
    // 0x800CA518: swl         $zero, 0x0($a0)
    do_swl(rdram, 0X0, ctx->r4, 0);
    // 0x800CA51C: addu        $a0, $a0, $v1
    ctx->r4 = ADD32(ctx->r4, ctx->r3);
L_800CA520:
    // 0x800CA520: addiu       $at, $zero, -0x20
    ctx->r1 = ADD32(0, -0X20);
    // 0x800CA524: and         $a3, $a1, $at
    ctx->r7 = ctx->r5 & ctx->r1;
    // 0x800CA528: beq         $a3, $zero, L_800CA55C
    if (ctx->r7 == 0) {
        // 0x800CA52C: subu        $a1, $a1, $a3
        ctx->r5 = SUB32(ctx->r5, ctx->r7);
            goto L_800CA55C;
    }
    // 0x800CA52C: subu        $a1, $a1, $a3
    ctx->r5 = SUB32(ctx->r5, ctx->r7);
    // 0x800CA530: addu        $a3, $a3, $a0
    ctx->r7 = ADD32(ctx->r7, ctx->r4);
L_800CA534:
    // 0x800CA534: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    // 0x800CA538: sw          $zero, -0x20($a0)
    MEM_W(-0X20, ctx->r4) = 0;
    // 0x800CA53C: sw          $zero, -0x1C($a0)
    MEM_W(-0X1C, ctx->r4) = 0;
    // 0x800CA540: sw          $zero, -0x18($a0)
    MEM_W(-0X18, ctx->r4) = 0;
    // 0x800CA544: sw          $zero, -0x14($a0)
    MEM_W(-0X14, ctx->r4) = 0;
    // 0x800CA548: sw          $zero, -0x10($a0)
    MEM_W(-0X10, ctx->r4) = 0;
    // 0x800CA54C: sw          $zero, -0xC($a0)
    MEM_W(-0XC, ctx->r4) = 0;
    // 0x800CA550: sw          $zero, -0x8($a0)
    MEM_W(-0X8, ctx->r4) = 0;
    // 0x800CA554: bne         $a0, $a3, L_800CA534
    if (ctx->r4 != ctx->r7) {
        // 0x800CA558: sw          $zero, -0x4($a0)
        MEM_W(-0X4, ctx->r4) = 0;
            goto L_800CA534;
    }
    // 0x800CA558: sw          $zero, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = 0;
L_800CA55C:
    // 0x800CA55C: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CA560: and         $a3, $a1, $at
    ctx->r7 = ctx->r5 & ctx->r1;
    // 0x800CA564: beq         $a3, $zero, L_800CA57C
    if (ctx->r7 == 0) {
        // 0x800CA568: subu        $a1, $a1, $a3
        ctx->r5 = SUB32(ctx->r5, ctx->r7);
            goto L_800CA57C;
    }
    // 0x800CA568: subu        $a1, $a1, $a3
    ctx->r5 = SUB32(ctx->r5, ctx->r7);
    // 0x800CA56C: addu        $a3, $a3, $a0
    ctx->r7 = ADD32(ctx->r7, ctx->r4);
L_800CA570:
    // 0x800CA570: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800CA574: bne         $a0, $a3, L_800CA570
    if (ctx->r4 != ctx->r7) {
        // 0x800CA578: sw          $zero, -0x4($a0)
        MEM_W(-0X4, ctx->r4) = 0;
            goto L_800CA570;
    }
    // 0x800CA578: sw          $zero, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = 0;
L_800CA57C:
    // 0x800CA57C: blez        $a1, L_800CA594
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800CA580: nop
    
            goto L_800CA594;
    }
    // 0x800CA580: nop

    // 0x800CA584: addu        $a1, $a1, $a0
    ctx->r5 = ADD32(ctx->r5, ctx->r4);
L_800CA588:
    // 0x800CA588: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CA58C: bne         $a0, $a1, L_800CA588
    if (ctx->r4 != ctx->r5) {
        // 0x800CA590: sb          $zero, -0x1($a0)
        MEM_B(-0X1, ctx->r4) = 0;
            goto L_800CA588;
    }
    // 0x800CA590: sb          $zero, -0x1($a0)
    MEM_B(-0X1, ctx->r4) = 0;
L_800CA594:
    // 0x800CA594: jr          $ra
    // 0x800CA598: nop

    return;
    // 0x800CA598: nop

    // 0x800CA59C: nop

;}
RECOMP_FUNC void bnkf_stub(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA700: jr          $ra
    // 0x800CA704: nop

    return;
    // 0x800CA704: nop

    // 0x800CA708: jr          $ra
    // 0x800CA70C: nop

    return;
    // 0x800CA70C: nop

;}
RECOMP_FUNC void _bnkfPatchBank(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA710: lbu         $t6, 0x3($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X3);
    // 0x800CA714: bne         $t6, $zero, L_800CA7F4
    if (ctx->r14 != 0) {
        // 0x800CA718: nop
    
            goto L_800CA7F4;
    }
    // 0x800CA718: nop

    // 0x800CA71C: lh          $t7, 0xE($a0)
    ctx->r15 = MEM_H(ctx->r4, 0XE);
    // 0x800CA720: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800CA724: sb          $t1, 0x3($a0)
    MEM_B(0X3, ctx->r4) = ctx->r9;
    // 0x800CA728: blez        $t7, L_800CA7F4
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800CA72C: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800CA7F4;
    }
    // 0x800CA72C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800CA730: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800CA734: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x800CA738: lw          $t8, 0x10($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X10);
L_800CA73C:
    // 0x800CA73C: addu        $t9, $t8, $a1
    ctx->r25 = ADD32(ctx->r24, ctx->r5);
    // 0x800CA740: sw          $t9, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r25;
    // 0x800CA744: lbu         $t6, 0xE($t9)
    ctx->r14 = MEM_BU(ctx->r25, 0XE);
    // 0x800CA748: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800CA74C: bnel        $t6, $zero, L_800CA7E0
    if (ctx->r14 != 0) {
        // 0x800CA750: lh          $t8, 0xE($a0)
        ctx->r24 = MEM_H(ctx->r4, 0XE);
            goto L_800CA7E0;
    }
    goto skip_0;
    // 0x800CA750: lh          $t8, 0xE($a0)
    ctx->r24 = MEM_H(ctx->r4, 0XE);
    skip_0:
    // 0x800CA754: lw          $t7, 0x0($t9)
    ctx->r15 = MEM_W(ctx->r25, 0X0);
    // 0x800CA758: sb          $t1, 0xE($t9)
    MEM_B(0XE, ctx->r25) = ctx->r9;
    // 0x800CA75C: addu        $t8, $t7, $a1
    ctx->r24 = ADD32(ctx->r15, ctx->r5);
    // 0x800CA760: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
    // 0x800CA764: lw          $t9, 0x4($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X4);
    // 0x800CA768: lw          $t7, 0x8($a2)
    ctx->r15 = MEM_W(ctx->r6, 0X8);
    // 0x800CA76C: addu        $t6, $t9, $a1
    ctx->r14 = ADD32(ctx->r25, ctx->r5);
    // 0x800CA770: addu        $t8, $t7, $a1
    ctx->r24 = ADD32(ctx->r15, ctx->r5);
    // 0x800CA774: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x800CA778: sw          $t8, 0x8($a2)
    MEM_W(0X8, ctx->r6) = ctx->r24;
    // 0x800CA77C: lbu         $t9, 0x9($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X9);
    // 0x800CA780: or          $t0, $t8, $zero
    ctx->r8 = ctx->r24 | 0;
    // 0x800CA784: bnel        $t9, $zero, L_800CA7E0
    if (ctx->r25 != 0) {
        // 0x800CA788: lh          $t8, 0xE($a0)
        ctx->r24 = MEM_H(ctx->r4, 0XE);
            goto L_800CA7E0;
    }
    goto skip_1;
    // 0x800CA788: lh          $t8, 0xE($a0)
    ctx->r24 = MEM_H(ctx->r4, 0XE);
    skip_1:
    // 0x800CA78C: lw          $t6, 0x0($t8)
    ctx->r14 = MEM_W(ctx->r24, 0X0);
    // 0x800CA790: lbu         $a2, 0x8($t8)
    ctx->r6 = MEM_BU(ctx->r24, 0X8);
    // 0x800CA794: sb          $t1, 0x9($t8)
    MEM_B(0X9, ctx->r24) = ctx->r9;
    // 0x800CA798: addu        $t7, $t6, $a3
    ctx->r15 = ADD32(ctx->r14, ctx->r7);
    // 0x800CA79C: bne         $a2, $zero, L_800CA7C4
    if (ctx->r6 != 0) {
        // 0x800CA7A0: sw          $t7, 0x0($t8)
        MEM_W(0X0, ctx->r24) = ctx->r15;
            goto L_800CA7C4;
    }
    // 0x800CA7A0: sw          $t7, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r15;
    // 0x800CA7A4: lw          $t8, 0x10($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X10);
    // 0x800CA7A8: lw          $a2, 0xC($t0)
    ctx->r6 = MEM_W(ctx->r8, 0XC);
    // 0x800CA7AC: addu        $t9, $t8, $a1
    ctx->r25 = ADD32(ctx->r24, ctx->r5);
    // 0x800CA7B0: beq         $a2, $zero, L_800CA7DC
    if (ctx->r6 == 0) {
        // 0x800CA7B4: sw          $t9, 0x10($t0)
        MEM_W(0X10, ctx->r8) = ctx->r25;
            goto L_800CA7DC;
    }
    // 0x800CA7B4: sw          $t9, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->r25;
    // 0x800CA7B8: addu        $t6, $a2, $a1
    ctx->r14 = ADD32(ctx->r6, ctx->r5);
    // 0x800CA7BC: b           L_800CA7DC
    // 0x800CA7C0: sw          $t6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r14;
        goto L_800CA7DC;
    // 0x800CA7C0: sw          $t6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r14;
L_800CA7C4:
    // 0x800CA7C4: bnel        $t2, $a2, L_800CA7E0
    if (ctx->r10 != ctx->r6) {
        // 0x800CA7C8: lh          $t8, 0xE($a0)
        ctx->r24 = MEM_H(ctx->r4, 0XE);
            goto L_800CA7E0;
    }
    goto skip_2;
    // 0x800CA7C8: lh          $t8, 0xE($a0)
    ctx->r24 = MEM_H(ctx->r4, 0XE);
    skip_2:
    // 0x800CA7CC: lw          $a2, 0xC($t0)
    ctx->r6 = MEM_W(ctx->r8, 0XC);
    // 0x800CA7D0: beq         $a2, $zero, L_800CA7DC
    if (ctx->r6 == 0) {
        // 0x800CA7D4: addu        $t7, $a2, $a1
        ctx->r15 = ADD32(ctx->r6, ctx->r5);
            goto L_800CA7DC;
    }
    // 0x800CA7D4: addu        $t7, $a2, $a1
    ctx->r15 = ADD32(ctx->r6, ctx->r5);
    // 0x800CA7D8: sw          $t7, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r15;
L_800CA7DC:
    // 0x800CA7DC: lh          $t8, 0xE($a0)
    ctx->r24 = MEM_H(ctx->r4, 0XE);
L_800CA7E0:
    // 0x800CA7E0: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800CA7E4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800CA7E8: slt         $at, $v0, $t8
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x800CA7EC: bnel        $at, $zero, L_800CA73C
    if (ctx->r1 != 0) {
        // 0x800CA7F0: lw          $t8, 0x10($v1)
        ctx->r24 = MEM_W(ctx->r3, 0X10);
            goto L_800CA73C;
    }
    goto skip_3;
    // 0x800CA7F0: lw          $t8, 0x10($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X10);
    skip_3:
L_800CA7F4:
    // 0x800CA7F4: jr          $ra
    // 0x800CA7F8: nop

    return;
    // 0x800CA7F8: nop

    // 0x800CA7FC: jr          $ra
    // 0x800CA800: nop

    return;
    // 0x800CA800: nop

;}
RECOMP_FUNC void alBnkfNew(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA804: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800CA808: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800CA80C: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800CA810: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800CA814: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800CA818: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800CA81C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800CA820: lh          $t6, 0x0($a0)
    ctx->r14 = MEM_H(ctx->r4, 0X0);
    // 0x800CA824: addiu       $at, $zero, 0x4231
    ctx->r1 = ADD32(0, 0X4231);
    // 0x800CA828: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800CA82C: bne         $t6, $at, L_800CA8E8
    if (ctx->r14 != ctx->r1) {
        // 0x800CA830: or          $s1, $a1, $zero
        ctx->r17 = ctx->r5 | 0;
            goto L_800CA8E8;
    }
    // 0x800CA830: or          $s1, $a1, $zero
    ctx->r17 = ctx->r5 | 0;
    // 0x800CA834: lh          $t7, 0x2($a0)
    ctx->r15 = MEM_H(ctx->r4, 0X2);
    // 0x800CA838: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x800CA83C: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x800CA840: blez        $t7, L_800CA8E8
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800CA844: addiu       $s4, $zero, 0x1
        ctx->r20 = ADD32(0, 0X1);
            goto L_800CA8E8;
    }
    // 0x800CA844: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
    // 0x800CA848: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
L_800CA84C:
    // 0x800CA84C: addu        $t9, $t8, $s0
    ctx->r25 = ADD32(ctx->r24, ctx->r16);
    // 0x800CA850: beq         $t9, $zero, L_800CA8D0
    if (ctx->r25 == 0) {
        // 0x800CA854: sw          $t9, 0x4($s2)
        MEM_W(0X4, ctx->r18) = ctx->r25;
            goto L_800CA8D0;
    }
    // 0x800CA854: sw          $t9, 0x4($s2)
    MEM_W(0X4, ctx->r18) = ctx->r25;
    // 0x800CA858: lbu         $t6, 0x2($t9)
    ctx->r14 = MEM_BU(ctx->r25, 0X2);
    // 0x800CA85C: or          $t5, $t9, $zero
    ctx->r13 = ctx->r25 | 0;
    // 0x800CA860: bnel        $t6, $zero, L_800CA8D4
    if (ctx->r14 != 0) {
        // 0x800CA864: lh          $t8, 0x2($s0)
        ctx->r24 = MEM_H(ctx->r16, 0X2);
            goto L_800CA8D4;
    }
    goto skip_0;
    // 0x800CA864: lh          $t8, 0x2($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X2);
    skip_0:
    // 0x800CA868: lw          $v0, 0x8($t9)
    ctx->r2 = MEM_W(ctx->r25, 0X8);
    // 0x800CA86C: sb          $s4, 0x2($t9)
    MEM_B(0X2, ctx->r25) = ctx->r20;
    // 0x800CA870: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x800CA874: beq         $v0, $zero, L_800CA88C
    if (ctx->r2 == 0) {
        // 0x800CA878: addu        $a0, $v0, $s0
        ctx->r4 = ADD32(ctx->r2, ctx->r16);
            goto L_800CA88C;
    }
    // 0x800CA878: addu        $a0, $v0, $s0
    ctx->r4 = ADD32(ctx->r2, ctx->r16);
    // 0x800CA87C: sw          $a0, 0x8($t9)
    MEM_W(0X8, ctx->r25) = ctx->r4;
    // 0x800CA880: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800CA884: jal         0x800CA710
    // 0x800CA888: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    _bnkfPatchBank(rdram, ctx);
        goto after_0;
    // 0x800CA888: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_0:
L_800CA88C:
    // 0x800CA88C: lh          $t8, 0x0($t5)
    ctx->r24 = MEM_H(ctx->r13, 0X0);
    // 0x800CA890: or          $t3, $t5, $zero
    ctx->r11 = ctx->r13 | 0;
    // 0x800CA894: blezl       $t8, L_800CA8D4
    if (SIGNED(ctx->r24) <= 0) {
        // 0x800CA898: lh          $t8, 0x2($s0)
        ctx->r24 = MEM_H(ctx->r16, 0X2);
            goto L_800CA8D4;
    }
    goto skip_1;
    // 0x800CA898: lh          $t8, 0x2($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X2);
    skip_1:
    // 0x800CA89C: lw          $t9, 0xC($t3)
    ctx->r25 = MEM_W(ctx->r11, 0XC);
L_800CA8A0:
    // 0x800CA8A0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800CA8A4: addu        $a0, $t9, $s0
    ctx->r4 = ADD32(ctx->r25, ctx->r16);
    // 0x800CA8A8: beq         $a0, $zero, L_800CA8B8
    if (ctx->r4 == 0) {
        // 0x800CA8AC: sw          $a0, 0xC($t3)
        MEM_W(0XC, ctx->r11) = ctx->r4;
            goto L_800CA8B8;
    }
    // 0x800CA8AC: sw          $a0, 0xC($t3)
    MEM_W(0XC, ctx->r11) = ctx->r4;
    // 0x800CA8B0: jal         0x800CA710
    // 0x800CA8B4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    _bnkfPatchBank(rdram, ctx);
        goto after_1;
    // 0x800CA8B4: or          $a3, $s1, $zero
    ctx->r7 = ctx->r17 | 0;
    after_1:
L_800CA8B8:
    // 0x800CA8B8: lh          $t7, 0x0($t5)
    ctx->r15 = MEM_H(ctx->r13, 0X0);
    // 0x800CA8BC: addiu       $t4, $t4, 0x1
    ctx->r12 = ADD32(ctx->r12, 0X1);
    // 0x800CA8C0: addiu       $t3, $t3, 0x4
    ctx->r11 = ADD32(ctx->r11, 0X4);
    // 0x800CA8C4: slt         $at, $t4, $t7
    ctx->r1 = SIGNED(ctx->r12) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800CA8C8: bnel        $at, $zero, L_800CA8A0
    if (ctx->r1 != 0) {
        // 0x800CA8CC: lw          $t9, 0xC($t3)
        ctx->r25 = MEM_W(ctx->r11, 0XC);
            goto L_800CA8A0;
    }
    goto skip_2;
    // 0x800CA8CC: lw          $t9, 0xC($t3)
    ctx->r25 = MEM_W(ctx->r11, 0XC);
    skip_2:
L_800CA8D0:
    // 0x800CA8D0: lh          $t8, 0x2($s0)
    ctx->r24 = MEM_H(ctx->r16, 0X2);
L_800CA8D4:
    // 0x800CA8D4: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x800CA8D8: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x800CA8DC: slt         $at, $s3, $t8
    ctx->r1 = SIGNED(ctx->r19) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x800CA8E0: bnel        $at, $zero, L_800CA84C
    if (ctx->r1 != 0) {
        // 0x800CA8E4: lw          $t8, 0x4($s2)
        ctx->r24 = MEM_W(ctx->r18, 0X4);
            goto L_800CA84C;
    }
    goto skip_3;
    // 0x800CA8E4: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
    skip_3:
L_800CA8E8:
    // 0x800CA8E8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800CA8EC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800CA8F0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800CA8F4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800CA8F8: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800CA8FC: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800CA900: jr          $ra
    // 0x800CA904: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x800CA904: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void alSeqFileNew(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CA908: lh          $t6, 0x2($a0)
    ctx->r14 = MEM_H(ctx->r4, 0X2);
    // 0x800CA90C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800CA910: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800CA914: blez        $t6, L_800CA940
    if (SIGNED(ctx->r14) <= 0) {
        // 0x800CA918: nop
    
            goto L_800CA940;
    }
    // 0x800CA918: nop

    // 0x800CA91C: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
L_800CA920:
    // 0x800CA920: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800CA924: addiu       $v1, $v1, 0x8
    ctx->r3 = ADD32(ctx->r3, 0X8);
    // 0x800CA928: addu        $t8, $t7, $a1
    ctx->r24 = ADD32(ctx->r15, ctx->r5);
    // 0x800CA92C: sw          $t8, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r24;
    // 0x800CA930: lh          $t9, 0x2($a0)
    ctx->r25 = MEM_H(ctx->r4, 0X2);
    // 0x800CA934: slt         $at, $v0, $t9
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800CA938: bnel        $at, $zero, L_800CA920
    if (ctx->r1 != 0) {
        // 0x800CA93C: lw          $t7, 0x4($v1)
        ctx->r15 = MEM_W(ctx->r3, 0X4);
            goto L_800CA920;
    }
    goto skip_0;
    // 0x800CA93C: lw          $t7, 0x4($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4);
    skip_0:
L_800CA940:
    // 0x800CA940: jr          $ra
    // 0x800CA944: nop

    return;
    // 0x800CA944: nop

    // 0x800CA948: nop

    // 0x800CA94C: nop

;}
RECOMP_FUNC void bcopy_recomp(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CBA80: beq         $a2, $zero, L_800CBAEC
    if (ctx->r6 == 0) {
        // 0x800CBA84: or          $a3, $a1, $zero
        ctx->r7 = ctx->r5 | 0;
            goto L_800CBAEC;
    }
    // 0x800CBA84: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800CBA88: beq         $a0, $a1, L_800CBAEC
    if (ctx->r4 == ctx->r5) {
        // 0x800CBA8C: slt         $at, $a1, $a0
        ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r4) ? 1 : 0;
            goto L_800CBAEC;
    }
    // 0x800CBA8C: slt         $at, $a1, $a0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x800CBA90: bnel        $at, $zero, L_800CBAB4
    if (ctx->r1 != 0) {
        // 0x800CBA94: slti        $at, $a2, 0x10
        ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
            goto L_800CBAB4;
    }
    goto skip_0;
    // 0x800CBA94: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
    skip_0:
    // 0x800CBA98: add         $v0, $a0, $a2
    ctx->r2 = ADD32(ctx->r4, ctx->r6);
    // 0x800CBA9C: slt         $at, $a1, $v0
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x800CBAA0: beql        $at, $zero, L_800CBAB4
    if (ctx->r1 == 0) {
        // 0x800CBAA4: slti        $at, $a2, 0x10
        ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
            goto L_800CBAB4;
    }
    goto skip_1;
    // 0x800CBAA4: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
    skip_1:
    // 0x800CBAA8: b           L_800CBC18
    // 0x800CBAAC: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
        goto L_800CBC18;
    // 0x800CBAAC: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
    // 0x800CBAB0: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
L_800CBAB4:
    // 0x800CBAB4: bne         $at, $zero, L_800CBACC
    if (ctx->r1 != 0) {
        // 0x800CBAB8: nop
    
            goto L_800CBACC;
    }
    // 0x800CBAB8: nop

    // 0x800CBABC: andi        $v0, $a0, 0x3
    ctx->r2 = ctx->r4 & 0X3;
    // 0x800CBAC0: andi        $v1, $a1, 0x3
    ctx->r3 = ctx->r5 & 0X3;
    // 0x800CBAC4: beq         $v0, $v1, L_800CBAF4
    if (ctx->r2 == ctx->r3) {
        // 0x800CBAC8: nop
    
            goto L_800CBAF4;
    }
    // 0x800CBAC8: nop

L_800CBACC:
    // 0x800CBACC: beq         $a2, $zero, L_800CBAEC
    if (ctx->r6 == 0) {
        // 0x800CBAD0: nop
    
            goto L_800CBAEC;
    }
    // 0x800CBAD0: nop

    // 0x800CBAD4: addu        $v1, $a0, $a2
    ctx->r3 = ADD32(ctx->r4, ctx->r6);
L_800CBAD8:
    // 0x800CBAD8: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    // 0x800CBADC: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CBAE0: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x800CBAE4: bne         $a0, $v1, L_800CBAD8
    if (ctx->r4 != ctx->r3) {
        // 0x800CBAE8: sb          $v0, -0x1($a1)
        MEM_B(-0X1, ctx->r5) = ctx->r2;
            goto L_800CBAD8;
    }
    // 0x800CBAE8: sb          $v0, -0x1($a1)
    MEM_B(-0X1, ctx->r5) = ctx->r2;
L_800CBAEC:
    // 0x800CBAEC: jr          $ra
    // 0x800CBAF0: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    return;
    // 0x800CBAF0: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
L_800CBAF4:
    // 0x800CBAF4: beq         $v0, $zero, L_800CBB58
    if (ctx->r2 == 0) {
        // 0x800CBAF8: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_800CBB58;
    }
    // 0x800CBAF8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800CBAFC: beq         $v0, $at, L_800CBB3C
    if (ctx->r2 == ctx->r1) {
        // 0x800CBB00: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800CBB3C;
    }
    // 0x800CBB00: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800CBB04: beql        $v0, $at, L_800CBB28
    if (ctx->r2 == ctx->r1) {
        // 0x800CBB08: lh          $v0, 0x0($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X0);
            goto L_800CBB28;
    }
    goto skip_2;
    // 0x800CBB08: lh          $v0, 0x0($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X0);
    skip_2:
    // 0x800CBB0C: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    // 0x800CBB10: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CBB14: addiu       $a1, $a1, 0x1
    ctx->r5 = ADD32(ctx->r5, 0X1);
    // 0x800CBB18: addiu       $a2, $a2, -0x1
    ctx->r6 = ADD32(ctx->r6, -0X1);
    // 0x800CBB1C: b           L_800CBB58
    // 0x800CBB20: sb          $v0, -0x1($a1)
    MEM_B(-0X1, ctx->r5) = ctx->r2;
        goto L_800CBB58;
    // 0x800CBB20: sb          $v0, -0x1($a1)
    MEM_B(-0X1, ctx->r5) = ctx->r2;
    // 0x800CBB24: lh          $v0, 0x0($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X0);
L_800CBB28:
    // 0x800CBB28: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    // 0x800CBB2C: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    // 0x800CBB30: addiu       $a2, $a2, -0x2
    ctx->r6 = ADD32(ctx->r6, -0X2);
    // 0x800CBB34: b           L_800CBB58
    // 0x800CBB38: sh          $v0, -0x2($a1)
    MEM_H(-0X2, ctx->r5) = ctx->r2;
        goto L_800CBB58;
    // 0x800CBB38: sh          $v0, -0x2($a1)
    MEM_H(-0X2, ctx->r5) = ctx->r2;
L_800CBB3C:
    // 0x800CBB3C: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    // 0x800CBB40: lh          $v1, 0x1($a0)
    ctx->r3 = MEM_H(ctx->r4, 0X1);
    // 0x800CBB44: addiu       $a0, $a0, 0x3
    ctx->r4 = ADD32(ctx->r4, 0X3);
    // 0x800CBB48: addiu       $a1, $a1, 0x3
    ctx->r5 = ADD32(ctx->r5, 0X3);
    // 0x800CBB4C: addiu       $a2, $a2, -0x3
    ctx->r6 = ADD32(ctx->r6, -0X3);
    // 0x800CBB50: sb          $v0, -0x3($a1)
    MEM_B(-0X3, ctx->r5) = ctx->r2;
    // 0x800CBB54: sh          $v1, -0x2($a1)
    MEM_H(-0X2, ctx->r5) = ctx->r3;
L_800CBB58:
    // 0x800CBB58: slti        $at, $a2, 0x20
    ctx->r1 = SIGNED(ctx->r6) < 0X20 ? 1 : 0;
    // 0x800CBB5C: bnel        $at, $zero, L_800CBBB8
    if (ctx->r1 != 0) {
        // 0x800CBB60: slti        $at, $a2, 0x10
        ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
            goto L_800CBBB8;
    }
    goto skip_3;
    // 0x800CBB60: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
    skip_3:
    // 0x800CBB64: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800CBB68: lw          $v1, 0x4($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X4);
    // 0x800CBB6C: lw          $t0, 0x8($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X8);
    // 0x800CBB70: lw          $t1, 0xC($a0)
    ctx->r9 = MEM_W(ctx->r4, 0XC);
    // 0x800CBB74: lw          $t2, 0x10($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X10);
    // 0x800CBB78: lw          $t3, 0x14($a0)
    ctx->r11 = MEM_W(ctx->r4, 0X14);
    // 0x800CBB7C: lw          $t4, 0x18($a0)
    ctx->r12 = MEM_W(ctx->r4, 0X18);
    // 0x800CBB80: lw          $t5, 0x1C($a0)
    ctx->r13 = MEM_W(ctx->r4, 0X1C);
    // 0x800CBB84: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    // 0x800CBB88: addiu       $a1, $a1, 0x20
    ctx->r5 = ADD32(ctx->r5, 0X20);
    // 0x800CBB8C: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    // 0x800CBB90: sw          $v0, -0x20($a1)
    MEM_W(-0X20, ctx->r5) = ctx->r2;
    // 0x800CBB94: sw          $v1, -0x1C($a1)
    MEM_W(-0X1C, ctx->r5) = ctx->r3;
    // 0x800CBB98: sw          $t0, -0x18($a1)
    MEM_W(-0X18, ctx->r5) = ctx->r8;
    // 0x800CBB9C: sw          $t1, -0x14($a1)
    MEM_W(-0X14, ctx->r5) = ctx->r9;
    // 0x800CBBA0: sw          $t2, -0x10($a1)
    MEM_W(-0X10, ctx->r5) = ctx->r10;
    // 0x800CBBA4: sw          $t3, -0xC($a1)
    MEM_W(-0XC, ctx->r5) = ctx->r11;
    // 0x800CBBA8: sw          $t4, -0x8($a1)
    MEM_W(-0X8, ctx->r5) = ctx->r12;
    // 0x800CBBAC: b           L_800CBB58
    // 0x800CBBB0: sw          $t5, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r13;
        goto L_800CBB58;
    // 0x800CBBB0: sw          $t5, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r13;
L_800CBBB4:
    // 0x800CBBB4: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
L_800CBBB8:
    // 0x800CBBB8: bnel        $at, $zero, L_800CBBF4
    if (ctx->r1 != 0) {
        // 0x800CBBBC: slti        $at, $a2, 0x4
        ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
            goto L_800CBBF4;
    }
    goto skip_4;
    // 0x800CBBBC: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
    skip_4:
    // 0x800CBBC0: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800CBBC4: lw          $v1, 0x4($a0)
    ctx->r3 = MEM_W(ctx->r4, 0X4);
    // 0x800CBBC8: lw          $t0, 0x8($a0)
    ctx->r8 = MEM_W(ctx->r4, 0X8);
    // 0x800CBBCC: lw          $t1, 0xC($a0)
    ctx->r9 = MEM_W(ctx->r4, 0XC);
    // 0x800CBBD0: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x800CBBD4: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x800CBBD8: addiu       $a2, $a2, -0x10
    ctx->r6 = ADD32(ctx->r6, -0X10);
    // 0x800CBBDC: sw          $v0, -0x10($a1)
    MEM_W(-0X10, ctx->r5) = ctx->r2;
    // 0x800CBBE0: sw          $v1, -0xC($a1)
    MEM_W(-0XC, ctx->r5) = ctx->r3;
    // 0x800CBBE4: sw          $t0, -0x8($a1)
    MEM_W(-0X8, ctx->r5) = ctx->r8;
    // 0x800CBBE8: b           L_800CBBB4
    // 0x800CBBEC: sw          $t1, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r9;
        goto L_800CBBB4;
    // 0x800CBBEC: sw          $t1, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r9;
L_800CBBF0:
    // 0x800CBBF0: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
L_800CBBF4:
    // 0x800CBBF4: bne         $at, $zero, L_800CBACC
    if (ctx->r1 != 0) {
        // 0x800CBBF8: nop
    
            goto L_800CBACC;
    }
    // 0x800CBBF8: nop

    // 0x800CBBFC: lw          $v0, 0x0($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X0);
    // 0x800CBC00: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800CBC04: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
    // 0x800CBC08: addiu       $a2, $a2, -0x4
    ctx->r6 = ADD32(ctx->r6, -0X4);
    // 0x800CBC0C: b           L_800CBBF0
    // 0x800CBC10: sw          $v0, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r2;
        goto L_800CBBF0;
    // 0x800CBC10: sw          $v0, -0x4($a1)
    MEM_W(-0X4, ctx->r5) = ctx->r2;
    // 0x800CBC14: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
L_800CBC18:
    // 0x800CBC18: add         $a0, $a0, $a2
    ctx->r4 = ADD32(ctx->r4, ctx->r6);
    // 0x800CBC1C: bne         $at, $zero, L_800CBC34
    if (ctx->r1 != 0) {
        // 0x800CBC20: add         $a1, $a1, $a2
        ctx->r5 = ADD32(ctx->r5, ctx->r6);
            goto L_800CBC34;
    }
    // 0x800CBC20: add         $a1, $a1, $a2
    ctx->r5 = ADD32(ctx->r5, ctx->r6);
    // 0x800CBC24: andi        $v0, $a0, 0x3
    ctx->r2 = ctx->r4 & 0X3;
    // 0x800CBC28: andi        $v1, $a1, 0x3
    ctx->r3 = ctx->r5 & 0X3;
    // 0x800CBC2C: beq         $v0, $v1, L_800CBC64
    if (ctx->r2 == ctx->r3) {
        // 0x800CBC30: nop
    
            goto L_800CBC64;
    }
    // 0x800CBC30: nop

L_800CBC34:
    // 0x800CBC34: beq         $a2, $zero, L_800CBAEC
    if (ctx->r6 == 0) {
        // 0x800CBC38: nop
    
            goto L_800CBAEC;
    }
    // 0x800CBC38: nop

    // 0x800CBC3C: addiu       $a0, $a0, -0x1
    ctx->r4 = ADD32(ctx->r4, -0X1);
    // 0x800CBC40: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x800CBC44: subu        $v1, $a0, $a2
    ctx->r3 = SUB32(ctx->r4, ctx->r6);
L_800CBC48:
    // 0x800CBC48: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    // 0x800CBC4C: addiu       $a0, $a0, -0x1
    ctx->r4 = ADD32(ctx->r4, -0X1);
    // 0x800CBC50: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x800CBC54: bne         $a0, $v1, L_800CBC48
    if (ctx->r4 != ctx->r3) {
        // 0x800CBC58: sb          $v0, 0x1($a1)
        MEM_B(0X1, ctx->r5) = ctx->r2;
            goto L_800CBC48;
    }
    // 0x800CBC58: sb          $v0, 0x1($a1)
    MEM_B(0X1, ctx->r5) = ctx->r2;
    // 0x800CBC5C: jr          $ra
    // 0x800CBC60: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    return;
    // 0x800CBC60: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
L_800CBC64:
    // 0x800CBC64: beq         $v0, $zero, L_800CBCC8
    if (ctx->r2 == 0) {
        // 0x800CBC68: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800CBCC8;
    }
    // 0x800CBC68: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800CBC6C: beq         $v0, $at, L_800CBCAC
    if (ctx->r2 == ctx->r1) {
        // 0x800CBC70: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800CBCAC;
    }
    // 0x800CBC70: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800CBC74: beql        $v0, $at, L_800CBC98
    if (ctx->r2 == ctx->r1) {
        // 0x800CBC78: lh          $v0, -0x2($a0)
        ctx->r2 = MEM_H(ctx->r4, -0X2);
            goto L_800CBC98;
    }
    goto skip_5;
    // 0x800CBC78: lh          $v0, -0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, -0X2);
    skip_5:
    // 0x800CBC7C: lb          $v0, -0x1($a0)
    ctx->r2 = MEM_B(ctx->r4, -0X1);
    // 0x800CBC80: addiu       $a0, $a0, -0x1
    ctx->r4 = ADD32(ctx->r4, -0X1);
    // 0x800CBC84: addiu       $a1, $a1, -0x1
    ctx->r5 = ADD32(ctx->r5, -0X1);
    // 0x800CBC88: addiu       $a2, $a2, -0x1
    ctx->r6 = ADD32(ctx->r6, -0X1);
    // 0x800CBC8C: b           L_800CBCC8
    // 0x800CBC90: sb          $v0, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r2;
        goto L_800CBCC8;
    // 0x800CBC90: sb          $v0, 0x0($a1)
    MEM_B(0X0, ctx->r5) = ctx->r2;
    // 0x800CBC94: lh          $v0, -0x2($a0)
    ctx->r2 = MEM_H(ctx->r4, -0X2);
L_800CBC98:
    // 0x800CBC98: addiu       $a0, $a0, -0x2
    ctx->r4 = ADD32(ctx->r4, -0X2);
    // 0x800CBC9C: addiu       $a1, $a1, -0x2
    ctx->r5 = ADD32(ctx->r5, -0X2);
    // 0x800CBCA0: addiu       $a2, $a2, -0x2
    ctx->r6 = ADD32(ctx->r6, -0X2);
    // 0x800CBCA4: b           L_800CBCC8
    // 0x800CBCA8: sh          $v0, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r2;
        goto L_800CBCC8;
    // 0x800CBCA8: sh          $v0, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r2;
L_800CBCAC:
    // 0x800CBCAC: lb          $v0, -0x1($a0)
    ctx->r2 = MEM_B(ctx->r4, -0X1);
    // 0x800CBCB0: lh          $v1, -0x3($a0)
    ctx->r3 = MEM_H(ctx->r4, -0X3);
    // 0x800CBCB4: addiu       $a0, $a0, -0x3
    ctx->r4 = ADD32(ctx->r4, -0X3);
    // 0x800CBCB8: addiu       $a1, $a1, -0x3
    ctx->r5 = ADD32(ctx->r5, -0X3);
    // 0x800CBCBC: addiu       $a2, $a2, -0x3
    ctx->r6 = ADD32(ctx->r6, -0X3);
    // 0x800CBCC0: sb          $v0, 0x2($a1)
    MEM_B(0X2, ctx->r5) = ctx->r2;
    // 0x800CBCC4: sh          $v1, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r3;
L_800CBCC8:
    // 0x800CBCC8: slti        $at, $a2, 0x20
    ctx->r1 = SIGNED(ctx->r6) < 0X20 ? 1 : 0;
    // 0x800CBCCC: bnel        $at, $zero, L_800CBD28
    if (ctx->r1 != 0) {
        // 0x800CBCD0: slti        $at, $a2, 0x10
        ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
            goto L_800CBD28;
    }
    goto skip_6;
    // 0x800CBCD0: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
    skip_6:
    // 0x800CBCD4: lw          $v0, -0x4($a0)
    ctx->r2 = MEM_W(ctx->r4, -0X4);
    // 0x800CBCD8: lw          $v1, -0x8($a0)
    ctx->r3 = MEM_W(ctx->r4, -0X8);
    // 0x800CBCDC: lw          $t0, -0xC($a0)
    ctx->r8 = MEM_W(ctx->r4, -0XC);
    // 0x800CBCE0: lw          $t1, -0x10($a0)
    ctx->r9 = MEM_W(ctx->r4, -0X10);
    // 0x800CBCE4: lw          $t2, -0x14($a0)
    ctx->r10 = MEM_W(ctx->r4, -0X14);
    // 0x800CBCE8: lw          $t3, -0x18($a0)
    ctx->r11 = MEM_W(ctx->r4, -0X18);
    // 0x800CBCEC: lw          $t4, -0x1C($a0)
    ctx->r12 = MEM_W(ctx->r4, -0X1C);
    // 0x800CBCF0: lw          $t5, -0x20($a0)
    ctx->r13 = MEM_W(ctx->r4, -0X20);
    // 0x800CBCF4: addiu       $a0, $a0, -0x20
    ctx->r4 = ADD32(ctx->r4, -0X20);
    // 0x800CBCF8: addiu       $a1, $a1, -0x20
    ctx->r5 = ADD32(ctx->r5, -0X20);
    // 0x800CBCFC: addiu       $a2, $a2, -0x20
    ctx->r6 = ADD32(ctx->r6, -0X20);
    // 0x800CBD00: sw          $v0, 0x1C($a1)
    MEM_W(0X1C, ctx->r5) = ctx->r2;
    // 0x800CBD04: sw          $v1, 0x18($a1)
    MEM_W(0X18, ctx->r5) = ctx->r3;
    // 0x800CBD08: sw          $t0, 0x14($a1)
    MEM_W(0X14, ctx->r5) = ctx->r8;
    // 0x800CBD0C: sw          $t1, 0x10($a1)
    MEM_W(0X10, ctx->r5) = ctx->r9;
    // 0x800CBD10: sw          $t2, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r10;
    // 0x800CBD14: sw          $t3, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r11;
    // 0x800CBD18: sw          $t4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r12;
    // 0x800CBD1C: b           L_800CBCC8
    // 0x800CBD20: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
        goto L_800CBCC8;
    // 0x800CBD20: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
L_800CBD24:
    // 0x800CBD24: slti        $at, $a2, 0x10
    ctx->r1 = SIGNED(ctx->r6) < 0X10 ? 1 : 0;
L_800CBD28:
    // 0x800CBD28: bnel        $at, $zero, L_800CBD64
    if (ctx->r1 != 0) {
        // 0x800CBD2C: slti        $at, $a2, 0x4
        ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
            goto L_800CBD64;
    }
    goto skip_7;
    // 0x800CBD2C: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
    skip_7:
    // 0x800CBD30: lw          $v0, -0x4($a0)
    ctx->r2 = MEM_W(ctx->r4, -0X4);
    // 0x800CBD34: lw          $v1, -0x8($a0)
    ctx->r3 = MEM_W(ctx->r4, -0X8);
    // 0x800CBD38: lw          $t0, -0xC($a0)
    ctx->r8 = MEM_W(ctx->r4, -0XC);
    // 0x800CBD3C: lw          $t1, -0x10($a0)
    ctx->r9 = MEM_W(ctx->r4, -0X10);
    // 0x800CBD40: addiu       $a0, $a0, -0x10
    ctx->r4 = ADD32(ctx->r4, -0X10);
    // 0x800CBD44: addiu       $a1, $a1, -0x10
    ctx->r5 = ADD32(ctx->r5, -0X10);
    // 0x800CBD48: addiu       $a2, $a2, -0x10
    ctx->r6 = ADD32(ctx->r6, -0X10);
    // 0x800CBD4C: sw          $v0, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r2;
    // 0x800CBD50: sw          $v1, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r3;
    // 0x800CBD54: sw          $t0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r8;
    // 0x800CBD58: b           L_800CBD24
    // 0x800CBD5C: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
        goto L_800CBD24;
    // 0x800CBD5C: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
L_800CBD60:
    // 0x800CBD60: slti        $at, $a2, 0x4
    ctx->r1 = SIGNED(ctx->r6) < 0X4 ? 1 : 0;
L_800CBD64:
    // 0x800CBD64: bne         $at, $zero, L_800CBC34
    if (ctx->r1 != 0) {
        // 0x800CBD68: nop
    
            goto L_800CBC34;
    }
    // 0x800CBD68: nop

    // 0x800CBD6C: lw          $v0, -0x4($a0)
    ctx->r2 = MEM_W(ctx->r4, -0X4);
    // 0x800CBD70: addiu       $a0, $a0, -0x4
    ctx->r4 = ADD32(ctx->r4, -0X4);
    // 0x800CBD74: addiu       $a1, $a1, -0x4
    ctx->r5 = ADD32(ctx->r5, -0X4);
    // 0x800CBD78: addiu       $a2, $a2, -0x4
    ctx->r6 = ADD32(ctx->r6, -0X4);
    // 0x800CBD7C: b           L_800CBD60
    // 0x800CBD80: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
        goto L_800CBD60;
    // 0x800CBD80: sw          $v0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r2;
    // 0x800CBD84: nop

    // 0x800CBD88: nop

    // 0x800CBD8C: nop

;}
RECOMP_FUNC void __osGetActiveQueue(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CBF40: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x800CBF44: jr          $ra
    // 0x800CBF48: lw          $v0, -0x6F50($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6F50);
    return;
    // 0x800CBF48: lw          $v0, -0x6F50($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X6F50);
    // 0x800CBF4C: nop

;}
RECOMP_FUNC void func_800CCB00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CCB00: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x800CCB04: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800CCB08: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x800CCB0C: addiu       $v1, $a1, 0x20
    ctx->r3 = ADD32(ctx->r5, 0X20);
    // 0x800CCB10: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800CCB14: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800CCB18: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x800CCB1C: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x800CCB20: lui         $t2, 0xFFFF
    ctx->r10 = S32(0XFFFF << 16);
L_800CCB24:
    // 0x800CCB24: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800CCB28: or          $t0, $a3, $zero
    ctx->r8 = ctx->r7 | 0;
    // 0x800CCB2C: lwc1        $f14, 0x4($t0)
    ctx->f14.u32l = MEM_W(ctx->r8, 0X4);
    // 0x800CCB30: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CCB34: lwc1        $f18, 0x0($t0)
    ctx->f18.u32l = MEM_W(ctx->r8, 0X0);
    // 0x800CCB38: mul.s       $f16, $f14, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800CCB3C: beq         $a0, $t3, L_800CCBA4
    if (ctx->r4 == ctx->r11) {
        // 0x800CCB40: nop
    
            goto L_800CCBA4;
    }
    // 0x800CCB40: nop

L_800CCB44:
    // 0x800CCB44: mul.s       $f14, $f18, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800CCB48: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CCB4C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800CCB50: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800CCB54: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x800CCB58: trunc.w.s   $f12, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    ctx->f12.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x800CCB5C: trunc.w.s   $f14, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    ctx->f14.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800CCB60: mfc1        $t1, $f12
    ctx->r9 = (int32_t)ctx->f12.u32l;
    // 0x800CCB64: mfc1        $a1, $f14
    ctx->r5 = (int32_t)ctx->f14.u32l;
    // 0x800CCB68: sra         $t9, $t1, 16
    ctx->r25 = S32(SIGNED(ctx->r9) >> 16);
    // 0x800CCB6C: andi        $t5, $t9, 0xFFFF
    ctx->r13 = ctx->r25 & 0XFFFF;
    // 0x800CCB70: and         $t8, $a1, $t2
    ctx->r24 = ctx->r5 & ctx->r10;
    // 0x800CCB74: or          $t6, $t8, $t5
    ctx->r14 = ctx->r24 | ctx->r13;
    // 0x800CCB78: sll         $t7, $a1, 16
    ctx->r15 = S32(ctx->r5 << 16);
    // 0x800CCB7C: and         $t9, $t7, $t2
    ctx->r25 = ctx->r15 & ctx->r10;
    // 0x800CCB80: sw          $t6, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->r14;
    // 0x800CCB84: andi        $t8, $t1, 0xFFFF
    ctx->r24 = ctx->r9 & 0XFFFF;
    // 0x800CCB88: or          $t5, $t9, $t8
    ctx->r13 = ctx->r25 | ctx->r24;
    // 0x800CCB8C: sw          $t5, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r13;
    // 0x800CCB90: lwc1        $f14, 0x4($t0)
    ctx->f14.u32l = MEM_W(ctx->r8, 0X4);
    // 0x800CCB94: lwc1        $f18, 0x0($t0)
    ctx->f18.u32l = MEM_W(ctx->r8, 0X0);
    // 0x800CCB98: mul.s       $f16, $f14, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800CCB9C: bne         $a0, $t3, L_800CCB44
    if (ctx->r4 != ctx->r11) {
        // 0x800CCBA0: nop
    
            goto L_800CCB44;
    }
    // 0x800CCBA0: nop

L_800CCBA4:
    // 0x800CCBA4: mul.s       $f14, $f18, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f14.fl = MUL_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800CCBA8: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    // 0x800CCBAC: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800CCBB0: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800CCBB4: trunc.w.s   $f12, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    ctx->f12.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x800CCBB8: trunc.w.s   $f14, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    ctx->f14.u32l = TRUNC_W_S(ctx->f14.fl);
    // 0x800CCBBC: mfc1        $t1, $f12
    ctx->r9 = (int32_t)ctx->f12.u32l;
    // 0x800CCBC0: mfc1        $a1, $f14
    ctx->r5 = (int32_t)ctx->f14.u32l;
    // 0x800CCBC4: sra         $t9, $t1, 16
    ctx->r25 = S32(SIGNED(ctx->r9) >> 16);
    // 0x800CCBC8: andi        $t5, $t9, 0xFFFF
    ctx->r13 = ctx->r25 & 0XFFFF;
    // 0x800CCBCC: and         $t8, $a1, $t2
    ctx->r24 = ctx->r5 & ctx->r10;
    // 0x800CCBD0: or          $t6, $t8, $t5
    ctx->r14 = ctx->r24 | ctx->r13;
    // 0x800CCBD4: sll         $t7, $a1, 16
    ctx->r15 = S32(ctx->r5 << 16);
    // 0x800CCBD8: and         $t9, $t7, $t2
    ctx->r25 = ctx->r15 & ctx->r10;
    // 0x800CCBDC: andi        $t8, $t1, 0xFFFF
    ctx->r24 = ctx->r9 & 0XFFFF;
    // 0x800CCBE0: sw          $t6, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = ctx->r14;
    // 0x800CCBE4: or          $t5, $t9, $t8
    ctx->r13 = ctx->r25 | ctx->r24;
    // 0x800CCBE8: sw          $t5, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r13;
    // 0x800CCBEC: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x800CCBF0: bne         $a2, $t4, L_800CCB24
    if (ctx->r6 != ctx->r12) {
        // 0x800CCBF4: addiu       $a3, $a3, 0x10
        ctx->r7 = ADD32(ctx->r7, 0X10);
            goto L_800CCB24;
    }
    // 0x800CCBF4: addiu       $a3, $a3, 0x10
    ctx->r7 = ADD32(ctx->r7, 0X10);
    // 0x800CCBF8: jr          $ra
    // 0x800CCBFC: nop

    return;
    // 0x800CCBFC: nop

;}
RECOMP_FUNC void func_800CCC00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CCC00: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x800CCC04: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800CCC08: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800CCC0C: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x800CCC10: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x800CCC14: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800CCC18: addiu       $a3, $zero, 0x4
    ctx->r7 = ADD32(0, 0X4);
    // 0x800CCC1C: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x800CCC20: addiu       $a1, $zero, 0x2
    ctx->r5 = ADD32(0, 0X2);
L_800CCC24:
    // 0x800CCC24: bnel        $v0, $zero, L_800CCC38
    if (ctx->r2 != 0) {
        // 0x800CCC28: swc1        $f2, 0x0($v1)
        MEM_W(0X0, ctx->r3) = ctx->f2.u32l;
            goto L_800CCC38;
    }
    goto skip_0;
    // 0x800CCC28: swc1        $f2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f2.u32l;
    skip_0:
    // 0x800CCC2C: b           L_800CCC38
    // 0x800CCC30: swc1        $f0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f0.u32l;
        goto L_800CCC38;
    // 0x800CCC30: swc1        $f0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f0.u32l;
    // 0x800CCC34: swc1        $f2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f2.u32l;
L_800CCC38:
    // 0x800CCC38: bnel        $v0, $a0, L_800CCC4C
    if (ctx->r2 != ctx->r4) {
        // 0x800CCC3C: swc1        $f2, 0x4($v1)
        MEM_W(0X4, ctx->r3) = ctx->f2.u32l;
            goto L_800CCC4C;
    }
    goto skip_1;
    // 0x800CCC3C: swc1        $f2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->f2.u32l;
    skip_1:
    // 0x800CCC40: b           L_800CCC4C
    // 0x800CCC44: swc1        $f0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->f0.u32l;
        goto L_800CCC4C;
    // 0x800CCC44: swc1        $f0, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->f0.u32l;
    // 0x800CCC48: swc1        $f2, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->f2.u32l;
L_800CCC4C:
    // 0x800CCC4C: bnel        $v0, $a1, L_800CCC60
    if (ctx->r2 != ctx->r5) {
        // 0x800CCC50: swc1        $f2, 0x8($v1)
        MEM_W(0X8, ctx->r3) = ctx->f2.u32l;
            goto L_800CCC60;
    }
    goto skip_2;
    // 0x800CCC50: swc1        $f2, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f2.u32l;
    skip_2:
    // 0x800CCC54: b           L_800CCC60
    // 0x800CCC58: swc1        $f0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f0.u32l;
        goto L_800CCC60;
    // 0x800CCC58: swc1        $f0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f0.u32l;
    // 0x800CCC5C: swc1        $f2, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->f2.u32l;
L_800CCC60:
    // 0x800CCC60: bnel        $v0, $a2, L_800CCC74
    if (ctx->r2 != ctx->r6) {
        // 0x800CCC64: swc1        $f2, 0xC($v1)
        MEM_W(0XC, ctx->r3) = ctx->f2.u32l;
            goto L_800CCC74;
    }
    goto skip_3;
    // 0x800CCC64: swc1        $f2, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f2.u32l;
    skip_3:
    // 0x800CCC68: b           L_800CCC74
    // 0x800CCC6C: swc1        $f0, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f0.u32l;
        goto L_800CCC74;
    // 0x800CCC6C: swc1        $f0, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f0.u32l;
    // 0x800CCC70: swc1        $f2, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->f2.u32l;
L_800CCC74:
    // 0x800CCC74: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800CCC78: bne         $v0, $a3, L_800CCC24
    if (ctx->r2 != ctx->r7) {
        // 0x800CCC7C: addiu       $v1, $v1, 0x10
        ctx->r3 = ADD32(ctx->r3, 0X10);
            goto L_800CCC24;
    }
    // 0x800CCC7C: addiu       $v1, $v1, 0x10
    ctx->r3 = ADD32(ctx->r3, 0X10);
    // 0x800CCC80: jr          $ra
    // 0x800CCC84: nop

    return;
    // 0x800CCC84: nop

    // 0x800CCC88: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x800CCC8C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800CCC90: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
    // 0x800CCC94: jal         0x800CCC00
    // 0x800CCC98: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_800CCC00(rdram, ctx);
        goto after_0;
    // 0x800CCC98: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_0:
    // 0x800CCC9C: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    // 0x800CCCA0: jal         0x800CCB00
    // 0x800CCCA4: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    func_800CCB00(rdram, ctx);
        goto after_1;
    // 0x800CCCA4: lw          $a1, 0x58($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X58);
    after_1:
    // 0x800CCCA8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800CCCAC: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    // 0x800CCCB0: jr          $ra
    // 0x800CCCB4: nop

    return;
    // 0x800CCCB4: nop

    // 0x800CCCB8: lui         $at, 0x4780
    ctx->r1 = S32(0X4780 << 16);
    // 0x800CCCBC: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800CCCC0: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x800CCCC4: or          $v0, $a1, $zero
    ctx->r2 = ctx->r5 | 0;
    // 0x800CCCC8: addiu       $v1, $a1, 0x20
    ctx->r3 = ADD32(ctx->r5, 0X20);
    // 0x800CCCCC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800CCCD0: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x800CCCD4: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x800CCCD8: addiu       $t3, $zero, 0x2
    ctx->r11 = ADD32(0, 0X2);
    // 0x800CCCDC: lui         $t2, 0xFFFF
    ctx->r10 = S32(0XFFFF << 16);
L_800CCCE0:
    // 0x800CCCE0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800CCCE4: or          $t1, $t0, $zero
    ctx->r9 = ctx->r8 | 0;
L_800CCCE8:
    // 0x800CCCE8: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x800CCCEC: lw          $t9, 0x0($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X0);
    // 0x800CCCF0: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800CCCF4: srl         $t7, $t6, 16
    ctx->r15 = S32(U32(ctx->r14) >> 16);
    // 0x800CCCF8: andi        $t8, $t7, 0xFFFF
    ctx->r24 = ctx->r15 & 0XFFFF;
    // 0x800CCCFC: and         $t5, $t9, $t2
    ctx->r13 = ctx->r25 & ctx->r10;
    // 0x800CCD00: or          $t6, $t8, $t5
    ctx->r14 = ctx->r24 | ctx->r13;
    // 0x800CCD04: sw          $t6, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r14;
    // 0x800CCD08: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800CCD0C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x800CCD10: lw          $a1, 0x4($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X4);
    // 0x800CCD14: andi        $t9, $t7, 0xFFFF
    ctx->r25 = ctx->r15 & 0XFFFF;
    // 0x800CCD18: sll         $t5, $t8, 16
    ctx->r13 = S32(ctx->r24 << 16);
    // 0x800CCD1C: mtc1        $a1, $f18
    ctx->f18.u32l = ctx->r5;
    // 0x800CCD20: and         $t6, $t5, $t2
    ctx->r14 = ctx->r13 & ctx->r10;
    // 0x800CCD24: or          $a3, $t9, $t6
    ctx->r7 = ctx->r25 | ctx->r14;
    // 0x800CCD28: cvt.s.w     $f18, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    ctx->f18.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800CCD2C: mtc1        $a3, $f16
    ctx->f16.u32l = ctx->r7;
    // 0x800CCD30: sw          $a3, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r7;
    // 0x800CCD34: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x800CCD38: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800CCD3C: cvt.s.w     $f16, $f16
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    ctx->f16.fl = CVT_S_W(ctx->f16.u32l);
    // 0x800CCD40: addiu       $t1, $t1, 0x8
    ctx->r9 = ADD32(ctx->r9, 0X8);
    // 0x800CCD44: div.s       $f18, $f18, $f0
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f18.fl = DIV_S(ctx->f18.fl, ctx->f0.fl);
    // 0x800CCD48: div.s       $f16, $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f16.fl, ctx->f0.fl);
    // 0x800CCD4C: swc1        $f18, -0x8($t1)
    MEM_W(-0X8, ctx->r9) = ctx->f18.u32l;
    // 0x800CCD50: bne         $a0, $t3, L_800CCCE8
    if (ctx->r4 != ctx->r11) {
        // 0x800CCD54: swc1        $f16, -0x4($t1)
        MEM_W(-0X4, ctx->r9) = ctx->f16.u32l;
            goto L_800CCCE8;
    }
    // 0x800CCD54: swc1        $f16, -0x4($t1)
    MEM_W(-0X4, ctx->r9) = ctx->f16.u32l;
    // 0x800CCD58: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x800CCD5C: bne         $a2, $t4, L_800CCCE0
    if (ctx->r6 != ctx->r12) {
        // 0x800CCD60: addiu       $t0, $t0, 0x10
        ctx->r8 = ADD32(ctx->r8, 0X10);
            goto L_800CCCE0;
    }
    // 0x800CCD60: addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // 0x800CCD64: jr          $ra
    // 0x800CCD68: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x800CCD68: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    // 0x800CCD6C: nop

;}
RECOMP_FUNC void __osSumcalc(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CD550: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800CD554: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800CD558: blez        $a1, L_800CD5C4
    if (SIGNED(ctx->r5) <= 0) {
        // 0x800CD55C: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_800CD5C4;
    }
    // 0x800CD55C: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800CD560: andi        $a3, $a1, 0x3
    ctx->r7 = ctx->r5 & 0X3;
    // 0x800CD564: beq         $a3, $zero, L_800CD590
    if (ctx->r7 == 0) {
        // 0x800CD568: or          $a0, $a3, $zero
        ctx->r4 = ctx->r7 | 0;
            goto L_800CD590;
    }
    // 0x800CD568: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
L_800CD56C:
    // 0x800CD56C: lbu         $t6, 0x0($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X0);
    // 0x800CD570: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x800CD574: addu        $v1, $v1, $t6
    ctx->r3 = ADD32(ctx->r3, ctx->r14);
    // 0x800CD578: andi        $t7, $v1, 0xFFFF
    ctx->r15 = ctx->r3 & 0XFFFF;
    // 0x800CD57C: or          $v1, $t7, $zero
    ctx->r3 = ctx->r15 | 0;
    // 0x800CD580: bne         $a0, $a2, L_800CD56C
    if (ctx->r4 != ctx->r6) {
        // 0x800CD584: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_800CD56C;
    }
    // 0x800CD584: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800CD588: beq         $a2, $a1, L_800CD5C4
    if (ctx->r6 == ctx->r5) {
        // 0x800CD58C: nop
    
            goto L_800CD5C4;
    }
    // 0x800CD58C: nop

L_800CD590:
    // 0x800CD590: lbu         $t8, 0x0($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X0);
    // 0x800CD594: lbu         $t0, 0x1($v0)
    ctx->r8 = MEM_BU(ctx->r2, 0X1);
    // 0x800CD598: lbu         $t2, 0x2($v0)
    ctx->r10 = MEM_BU(ctx->r2, 0X2);
    // 0x800CD59C: addu        $t9, $v1, $t8
    ctx->r25 = ADD32(ctx->r3, ctx->r24);
    // 0x800CD5A0: lbu         $t4, 0x3($v0)
    ctx->r12 = MEM_BU(ctx->r2, 0X3);
    // 0x800CD5A4: addu        $t1, $t9, $t0
    ctx->r9 = ADD32(ctx->r25, ctx->r8);
    // 0x800CD5A8: addu        $t3, $t1, $t2
    ctx->r11 = ADD32(ctx->r9, ctx->r10);
    // 0x800CD5AC: addu        $v1, $t3, $t4
    ctx->r3 = ADD32(ctx->r11, ctx->r12);
    // 0x800CD5B0: andi        $t5, $v1, 0xFFFF
    ctx->r13 = ctx->r3 & 0XFFFF;
    // 0x800CD5B4: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x800CD5B8: or          $v1, $t5, $zero
    ctx->r3 = ctx->r13 | 0;
    // 0x800CD5BC: bne         $a2, $a1, L_800CD590
    if (ctx->r6 != ctx->r5) {
        // 0x800CD5C0: addiu       $v0, $v0, 0x4
        ctx->r2 = ADD32(ctx->r2, 0X4);
            goto L_800CD590;
    }
    // 0x800CD5C0: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
L_800CD5C4:
    // 0x800CD5C4: jr          $ra
    // 0x800CD5C8: andi        $v0, $v1, 0xFFFF
    ctx->r2 = ctx->r3 & 0XFFFF;
    return;
    // 0x800CD5C8: andi        $v0, $v1, 0xFFFF
    ctx->r2 = ctx->r3 & 0XFFFF;
;}
RECOMP_FUNC void __osIdCheckSum(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CD5CC: sh          $zero, 0x0($a2)
    MEM_H(0X0, ctx->r6) = 0;
    // 0x800CD5D0: sh          $zero, 0x0($a1)
    MEM_H(0X0, ctx->r5) = 0;
    // 0x800CD5D4: lhu         $v0, 0x0($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X0);
    // 0x800CD5D8: addiu       $a3, $a0, 0x4
    ctx->r7 = ADD32(ctx->r4, 0X4);
    // 0x800CD5DC: addu        $t8, $zero, $v0
    ctx->r24 = ADD32(0, ctx->r2);
    // 0x800CD5E0: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD5E4: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD5E8: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD5EC: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD5F0: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD5F4: lhu         $t7, 0x0($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X0);
    // 0x800CD5F8: lhu         $v0, 0x2($a0)
    ctx->r2 = MEM_HU(ctx->r4, 0X2);
    // 0x800CD5FC: addiu       $a0, $zero, 0x1C
    ctx->r4 = ADD32(0, 0X1C);
    // 0x800CD600: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800CD604: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD608: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD60C: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD610: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD614: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD618: addiu       $t1, $a3, 0x2
    ctx->r9 = ADD32(ctx->r7, 0X2);
    // 0x800CD61C: addiu       $t2, $a3, 0x4
    ctx->r10 = ADD32(ctx->r7, 0X4);
    // 0x800CD620: addiu       $t3, $a3, 0x6
    ctx->r11 = ADD32(ctx->r7, 0X6);
    // 0x800CD624: addiu       $v1, $zero, 0x4
    ctx->r3 = ADD32(0, 0X4);
L_800CD628:
    // 0x800CD628: lhu         $v0, 0x0($a3)
    ctx->r2 = MEM_HU(ctx->r7, 0X0);
    // 0x800CD62C: lhu         $t7, 0x0($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X0);
    // 0x800CD630: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD634: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800CD638: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD63C: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD640: addiu       $v1, $v1, 0x8
    ctx->r3 = ADD32(ctx->r3, 0X8);
    // 0x800CD644: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD648: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD64C: lhu         $t7, 0x0($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X0);
    // 0x800CD650: lhu         $v0, 0x0($t1)
    ctx->r2 = MEM_HU(ctx->r9, 0X0);
    // 0x800CD654: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x800CD658: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800CD65C: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD660: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD664: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD668: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD66C: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD670: lhu         $t7, 0x0($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X0);
    // 0x800CD674: lhu         $v0, 0x0($t2)
    ctx->r2 = MEM_HU(ctx->r10, 0X0);
    // 0x800CD678: addiu       $t1, $t1, 0x8
    ctx->r9 = ADD32(ctx->r9, 0X8);
    // 0x800CD67C: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800CD680: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD684: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD688: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD68C: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD690: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD694: lhu         $t7, 0x0($a1)
    ctx->r15 = MEM_HU(ctx->r5, 0X0);
    // 0x800CD698: lhu         $v0, 0x0($t3)
    ctx->r2 = MEM_HU(ctx->r11, 0X0);
    // 0x800CD69C: addiu       $t2, $t2, 0x8
    ctx->r10 = ADD32(ctx->r10, 0X8);
    // 0x800CD6A0: addu        $t8, $t7, $v0
    ctx->r24 = ADD32(ctx->r15, ctx->r2);
    // 0x800CD6A4: sh          $t8, 0x0($a1)
    MEM_H(0X0, ctx->r5) = ctx->r24;
    // 0x800CD6A8: lhu         $t9, 0x0($a2)
    ctx->r25 = MEM_HU(ctx->r6, 0X0);
    // 0x800CD6AC: nor         $t5, $v0, $zero
    ctx->r13 = ~(ctx->r2 | 0);
    // 0x800CD6B0: addu        $t6, $t9, $t5
    ctx->r14 = ADD32(ctx->r25, ctx->r13);
    // 0x800CD6B4: sh          $t6, 0x0($a2)
    MEM_H(0X0, ctx->r6) = ctx->r14;
    // 0x800CD6B8: bne         $v1, $a0, L_800CD628
    if (ctx->r3 != ctx->r4) {
        // 0x800CD6BC: addiu       $t3, $t3, 0x8
        ctx->r11 = ADD32(ctx->r11, 0X8);
            goto L_800CD628;
    }
    // 0x800CD6BC: addiu       $t3, $t3, 0x8
    ctx->r11 = ADD32(ctx->r11, 0X8);
    // 0x800CD6C0: jr          $ra
    // 0x800CD6C4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800CD6C4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
;}
RECOMP_FUNC void _Printf(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CF330: addiu       $sp, $sp, -0xB0
    ctx->r29 = ADD32(ctx->r29, -0XB0);
    // 0x800CF334: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800CF338: sw          $a0, 0xB0($sp)
    MEM_W(0XB0, ctx->r29) = ctx->r4;
    // 0x800CF33C: sw          $a1, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r5;
    // 0x800CF340: sw          $a2, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r6;
    // 0x800CF344: sw          $a3, 0xBC($sp)
    MEM_W(0XBC, ctx->r29) = ctx->r7;
    // 0x800CF348: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800CF34C: sw          $zero, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = 0;
L_800CF350:
    // 0x800CF350: lw          $t6, 0xB8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XB8);
    // 0x800CF354: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800CF358: lbu         $t7, 0x0($t6)
    ctx->r15 = MEM_BU(ctx->r14, 0X0);
    // 0x800CF35C: addiu       $t8, $t6, 0x1
    ctx->r24 = ADD32(ctx->r14, 0X1);
    // 0x800CF360: sw          $t8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r24;
    // 0x800CF364: slt         $s0, $zero, $t7
    ctx->r16 = SIGNED(0) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800CF368: beq         $s0, $zero, L_800CF3AC
    if (ctx->r16 == 0) {
        // 0x800CF36C: sb          $t7, 0x73($sp)
        MEM_B(0X73, ctx->r29) = ctx->r15;
            goto L_800CF3AC;
    }
    // 0x800CF36C: sb          $t7, 0x73($sp)
    MEM_B(0X73, ctx->r29) = ctx->r15;
L_800CF370:
    // 0x800CF370: lbu         $t9, 0x73($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X73);
    // 0x800CF374: addiu       $at, $zero, 0x25
    ctx->r1 = ADD32(0, 0X25);
    // 0x800CF378: bne         $t9, $at, L_800CF390
    if (ctx->r25 != ctx->r1) {
        // 0x800CF37C: nop
    
            goto L_800CF390;
    }
    // 0x800CF37C: nop

    // 0x800CF380: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x800CF384: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x800CF388: b           L_800CF3AC
    // 0x800CF38C: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
        goto L_800CF3AC;
    // 0x800CF38C: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
L_800CF390:
    // 0x800CF390: lw          $t2, 0x74($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X74);
    // 0x800CF394: lbu         $t3, 0x0($t2)
    ctx->r11 = MEM_BU(ctx->r10, 0X0);
    // 0x800CF398: addiu       $t4, $t2, 0x1
    ctx->r12 = ADD32(ctx->r10, 0X1);
    // 0x800CF39C: sw          $t4, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r12;
    // 0x800CF3A0: slt         $s0, $zero, $t3
    ctx->r16 = SIGNED(0) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x800CF3A4: bne         $s0, $zero, L_800CF370
    if (ctx->r16 != 0) {
        // 0x800CF3A8: sb          $t3, 0x73($sp)
        MEM_B(0X73, ctx->r29) = ctx->r11;
            goto L_800CF370;
    }
    // 0x800CF3A8: sb          $t3, 0x73($sp)
    MEM_B(0X73, ctx->r29) = ctx->r11;
L_800CF3AC:
    // 0x800CF3AC: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800CF3B0: lw          $t7, 0xB8($sp)
    ctx->r15 = MEM_W(ctx->r29, 0XB8);
    // 0x800CF3B4: subu        $t6, $t5, $t7
    ctx->r14 = SUB32(ctx->r13, ctx->r15);
    // 0x800CF3B8: blez        $t6, L_800CF408
    if (SIGNED(ctx->r14) <= 0) {
        // 0x800CF3BC: nop
    
            goto L_800CF408;
    }
    // 0x800CF3BC: nop

    // 0x800CF3C0: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF3C4: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF3C8: or          $a1, $t7, $zero
    ctx->r5 = ctx->r15 | 0;
    // 0x800CF3CC: jalr        $t9
    // 0x800CF3D0: or          $a2, $t6, $zero
    ctx->r6 = ctx->r14 | 0;
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_0;
    // 0x800CF3D0: or          $a2, $t6, $zero
    ctx->r6 = ctx->r14 | 0;
    after_0:
    // 0x800CF3D4: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF3D8: lw          $t8, 0xB4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF3DC: beq         $t8, $zero, L_800CF400
    if (ctx->r24 == 0) {
        // 0x800CF3E0: nop
    
            goto L_800CF400;
    }
    // 0x800CF3E0: nop

    // 0x800CF3E4: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x800CF3E8: lw          $t1, 0xB8($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XB8);
    // 0x800CF3EC: lw          $t2, 0xA4($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF3F0: subu        $t3, $t0, $t1
    ctx->r11 = SUB32(ctx->r8, ctx->r9);
    // 0x800CF3F4: addu        $t4, $t2, $t3
    ctx->r12 = ADD32(ctx->r10, ctx->r11);
    // 0x800CF3F8: b           L_800CF408
    // 0x800CF3FC: sw          $t4, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r12;
        goto L_800CF408;
    // 0x800CF3FC: sw          $t4, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r12;
L_800CF400:
    // 0x800CF400: b           L_800CFB48
    // 0x800CF404: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF404: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF408:
    // 0x800CF408: lbu         $t5, 0x73($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X73);
    // 0x800CF40C: bne         $t5, $zero, L_800CF41C
    if (ctx->r13 != 0) {
        // 0x800CF410: nop
    
            goto L_800CF41C;
    }
    // 0x800CF410: nop

    // 0x800CF414: b           L_800CFB48
    // 0x800CF418: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF418: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF41C:
    // 0x800CF41C: lw          $t7, 0x74($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X74);
    // 0x800CF420: sw          $zero, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = 0;
    // 0x800CF424: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800CF428: addiu       $t6, $t7, 0x1
    ctx->r14 = ADD32(ctx->r15, 0X1);
    // 0x800CF42C: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800CF430: sw          $t6, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r14;
    // 0x800CF434: lbu         $a1, 0x0($t6)
    ctx->r5 = MEM_BU(ctx->r14, 0X0);
    // 0x800CF438: jal         0x800D0514
    // 0x800CF43C: addiu       $a0, $a0, -0x39AC
    ctx->r4 = ADD32(ctx->r4, -0X39AC);
    func_800D0514(rdram, ctx);
        goto after_1;
    // 0x800CF43C: addiu       $a0, $a0, -0x39AC
    ctx->r4 = ADD32(ctx->r4, -0X39AC);
    after_1:
    // 0x800CF440: sw          $v0, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r2;
    // 0x800CF444: lw          $t9, 0x6C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X6C);
    // 0x800CF448: beq         $t9, $zero, L_800CF4A8
    if (ctx->r25 == 0) {
        // 0x800CF44C: nop
    
            goto L_800CF4A8;
    }
    // 0x800CF44C: nop

L_800CF450:
    // 0x800CF450: lw          $t0, 0x6C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X6C);
    // 0x800CF454: lui         $t1, 0x800F
    ctx->r9 = S32(0X800F << 16);
    // 0x800CF458: addiu       $t1, $t1, -0x39AC
    ctx->r9 = ADD32(ctx->r9, -0X39AC);
    // 0x800CF45C: subu        $t2, $t0, $t1
    ctx->r10 = SUB32(ctx->r8, ctx->r9);
    // 0x800CF460: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x800CF464: lui         $t4, 0x800F
    ctx->r12 = S32(0X800F << 16);
    // 0x800CF468: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x800CF46C: lw          $t7, 0x74($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X74);
    // 0x800CF470: lw          $t4, -0x39A4($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X39A4);
    // 0x800CF474: lw          $t8, 0xA8($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XA8);
    // 0x800CF478: addiu       $t6, $t7, 0x1
    ctx->r14 = ADD32(ctx->r15, 0X1);
    // 0x800CF47C: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800CF480: or          $t5, $t8, $t4
    ctx->r13 = ctx->r24 | ctx->r12;
    // 0x800CF484: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800CF488: sw          $t5, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r13;
    // 0x800CF48C: lbu         $a1, 0x0($t6)
    ctx->r5 = MEM_BU(ctx->r14, 0X0);
    // 0x800CF490: jal         0x800D0514
    // 0x800CF494: addiu       $a0, $a0, -0x39AC
    ctx->r4 = ADD32(ctx->r4, -0X39AC);
    func_800D0514(rdram, ctx);
        goto after_2;
    // 0x800CF494: addiu       $a0, $a0, -0x39AC
    ctx->r4 = ADD32(ctx->r4, -0X39AC);
    after_2:
    // 0x800CF498: sw          $v0, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->r2;
    // 0x800CF49C: lw          $t9, 0x6C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X6C);
    // 0x800CF4A0: bne         $t9, $zero, L_800CF450
    if (ctx->r25 != 0) {
        // 0x800CF4A4: nop
    
            goto L_800CF450;
    }
    // 0x800CF4A4: nop

L_800CF4A8:
    // 0x800CF4A8: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x800CF4AC: addiu       $at, $zero, 0x2A
    ctx->r1 = ADD32(0, 0X2A);
    // 0x800CF4B0: lbu         $t1, 0x0($t0)
    ctx->r9 = MEM_BU(ctx->r8, 0X0);
    // 0x800CF4B4: bne         $t1, $at, L_800CF504
    if (ctx->r9 != ctx->r1) {
        // 0x800CF4B8: nop
    
            goto L_800CF504;
    }
    // 0x800CF4B8: nop

    // 0x800CF4BC: lw          $t2, 0xBC($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XBC);
    // 0x800CF4C0: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CF4C4: addiu       $t3, $t2, 0x3
    ctx->r11 = ADD32(ctx->r10, 0X3);
    // 0x800CF4C8: and         $t8, $t3, $at
    ctx->r24 = ctx->r11 & ctx->r1;
    // 0x800CF4CC: addiu       $t4, $t8, 0x4
    ctx->r12 = ADD32(ctx->r24, 0X4);
    // 0x800CF4D0: sw          $t4, 0xBC($sp)
    MEM_W(0XBC, ctx->r29) = ctx->r12;
    // 0x800CF4D4: lw          $t5, 0x0($t8)
    ctx->r13 = MEM_W(ctx->r24, 0X0);
    // 0x800CF4D8: bgez        $t5, L_800CF4F4
    if (SIGNED(ctx->r13) >= 0) {
        // 0x800CF4DC: sw          $t5, 0xA0($sp)
        MEM_W(0XA0, ctx->r29) = ctx->r13;
            goto L_800CF4F4;
    }
    // 0x800CF4DC: sw          $t5, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r13;
    // 0x800CF4E0: lw          $t6, 0xA8($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XA8);
    // 0x800CF4E4: negu        $t7, $t5
    ctx->r15 = SUB32(0, ctx->r13);
    // 0x800CF4E8: sw          $t7, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r15;
    // 0x800CF4EC: ori         $t9, $t6, 0x4
    ctx->r25 = ctx->r14 | 0X4;
    // 0x800CF4F0: sw          $t9, 0xA8($sp)
    MEM_W(0XA8, ctx->r29) = ctx->r25;
L_800CF4F4:
    // 0x800CF4F4: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x800CF4F8: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x800CF4FC: b           L_800CF578
    // 0x800CF500: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
        goto L_800CF578;
    // 0x800CF500: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
L_800CF504:
    // 0x800CF504: lw          $t2, 0x74($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X74);
    // 0x800CF508: sw          $zero, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = 0;
    // 0x800CF50C: lbu         $t3, 0x0($t2)
    ctx->r11 = MEM_BU(ctx->r10, 0X0);
    // 0x800CF510: slti        $at, $t3, 0x30
    ctx->r1 = SIGNED(ctx->r11) < 0X30 ? 1 : 0;
    // 0x800CF514: bne         $at, $zero, L_800CF578
    if (ctx->r1 != 0) {
        // 0x800CF518: slti        $at, $t3, 0x3A
        ctx->r1 = SIGNED(ctx->r11) < 0X3A ? 1 : 0;
            goto L_800CF578;
    }
    // 0x800CF518: slti        $at, $t3, 0x3A
    ctx->r1 = SIGNED(ctx->r11) < 0X3A ? 1 : 0;
    // 0x800CF51C: beq         $at, $zero, L_800CF578
    if (ctx->r1 == 0) {
        // 0x800CF520: nop
    
            goto L_800CF578;
    }
    // 0x800CF520: nop

L_800CF524:
    // 0x800CF524: lw          $t4, 0xA0($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA0);
    // 0x800CF528: slti        $at, $t4, 0x3E7
    ctx->r1 = SIGNED(ctx->r12) < 0X3E7 ? 1 : 0;
    // 0x800CF52C: beq         $at, $zero, L_800CF554
    if (ctx->r1 == 0) {
        // 0x800CF530: nop
    
            goto L_800CF554;
    }
    // 0x800CF530: nop

    // 0x800CF534: lw          $t8, 0x74($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X74);
    // 0x800CF538: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x800CF53C: addu        $t7, $t7, $t4
    ctx->r15 = ADD32(ctx->r15, ctx->r12);
    // 0x800CF540: lbu         $t5, 0x0($t8)
    ctx->r13 = MEM_BU(ctx->r24, 0X0);
    // 0x800CF544: sll         $t7, $t7, 1
    ctx->r15 = S32(ctx->r15 << 1);
    // 0x800CF548: addu        $t6, $t5, $t7
    ctx->r14 = ADD32(ctx->r13, ctx->r15);
    // 0x800CF54C: addiu       $t9, $t6, -0x30
    ctx->r25 = ADD32(ctx->r14, -0X30);
    // 0x800CF550: sw          $t9, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r25;
L_800CF554:
    // 0x800CF554: lw          $t0, 0x74($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X74);
    // 0x800CF558: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x800CF55C: sw          $t1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r9;
    // 0x800CF560: lbu         $t2, 0x0($t1)
    ctx->r10 = MEM_BU(ctx->r9, 0X0);
    // 0x800CF564: slti        $at, $t2, 0x30
    ctx->r1 = SIGNED(ctx->r10) < 0X30 ? 1 : 0;
    // 0x800CF568: bne         $at, $zero, L_800CF578
    if (ctx->r1 != 0) {
        // 0x800CF56C: slti        $at, $t2, 0x3A
        ctx->r1 = SIGNED(ctx->r10) < 0X3A ? 1 : 0;
            goto L_800CF578;
    }
    // 0x800CF56C: slti        $at, $t2, 0x3A
    ctx->r1 = SIGNED(ctx->r10) < 0X3A ? 1 : 0;
    // 0x800CF570: bne         $at, $zero, L_800CF524
    if (ctx->r1 != 0) {
        // 0x800CF574: nop
    
            goto L_800CF524;
    }
    // 0x800CF574: nop

L_800CF578:
    // 0x800CF578: lw          $t3, 0x74($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X74);
    // 0x800CF57C: addiu       $at, $zero, 0x2E
    ctx->r1 = ADD32(0, 0X2E);
    // 0x800CF580: lbu         $t8, 0x0($t3)
    ctx->r24 = MEM_BU(ctx->r11, 0X0);
    // 0x800CF584: beq         $t8, $at, L_800CF598
    if (ctx->r24 == ctx->r1) {
        // 0x800CF588: nop
    
            goto L_800CF598;
    }
    // 0x800CF588: nop

    // 0x800CF58C: addiu       $t4, $zero, -0x1
    ctx->r12 = ADD32(0, -0X1);
    // 0x800CF590: b           L_800CF654
    // 0x800CF594: sw          $t4, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r12;
        goto L_800CF654;
    // 0x800CF594: sw          $t4, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r12;
L_800CF598:
    // 0x800CF598: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800CF59C: addiu       $at, $zero, 0x2A
    ctx->r1 = ADD32(0, 0X2A);
    // 0x800CF5A0: addiu       $t7, $t5, 0x1
    ctx->r15 = ADD32(ctx->r13, 0X1);
    // 0x800CF5A4: sw          $t7, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r15;
    // 0x800CF5A8: lbu         $t6, 0x0($t7)
    ctx->r14 = MEM_BU(ctx->r15, 0X0);
    // 0x800CF5AC: bne         $t6, $at, L_800CF5E0
    if (ctx->r14 != ctx->r1) {
        // 0x800CF5B0: nop
    
            goto L_800CF5E0;
    }
    // 0x800CF5B0: nop

    // 0x800CF5B4: lw          $t9, 0xBC($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XBC);
    // 0x800CF5B8: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CF5BC: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x800CF5C0: addiu       $t0, $t9, 0x3
    ctx->r8 = ADD32(ctx->r25, 0X3);
    // 0x800CF5C4: and         $t1, $t0, $at
    ctx->r9 = ctx->r8 & ctx->r1;
    // 0x800CF5C8: addiu       $t2, $t1, 0x4
    ctx->r10 = ADD32(ctx->r9, 0X4);
    // 0x800CF5CC: sw          $t2, 0xBC($sp)
    MEM_W(0XBC, ctx->r29) = ctx->r10;
    // 0x800CF5D0: lw          $t3, 0x0($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X0);
    // 0x800CF5D4: sw          $t8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r24;
    // 0x800CF5D8: b           L_800CF654
    // 0x800CF5DC: sw          $t3, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r11;
        goto L_800CF654;
    // 0x800CF5DC: sw          $t3, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r11;
L_800CF5E0:
    // 0x800CF5E0: lw          $t4, 0x74($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X74);
    // 0x800CF5E4: sw          $zero, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = 0;
    // 0x800CF5E8: lbu         $t5, 0x0($t4)
    ctx->r13 = MEM_BU(ctx->r12, 0X0);
    // 0x800CF5EC: slti        $at, $t5, 0x30
    ctx->r1 = SIGNED(ctx->r13) < 0X30 ? 1 : 0;
    // 0x800CF5F0: bne         $at, $zero, L_800CF654
    if (ctx->r1 != 0) {
        // 0x800CF5F4: slti        $at, $t5, 0x3A
        ctx->r1 = SIGNED(ctx->r13) < 0X3A ? 1 : 0;
            goto L_800CF654;
    }
    // 0x800CF5F4: slti        $at, $t5, 0x3A
    ctx->r1 = SIGNED(ctx->r13) < 0X3A ? 1 : 0;
    // 0x800CF5F8: beq         $at, $zero, L_800CF654
    if (ctx->r1 == 0) {
        // 0x800CF5FC: nop
    
            goto L_800CF654;
    }
    // 0x800CF5FC: nop

L_800CF600:
    // 0x800CF600: lw          $t6, 0x9C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X9C);
    // 0x800CF604: slti        $at, $t6, 0x3E7
    ctx->r1 = SIGNED(ctx->r14) < 0X3E7 ? 1 : 0;
    // 0x800CF608: beq         $at, $zero, L_800CF630
    if (ctx->r1 == 0) {
        // 0x800CF60C: nop
    
            goto L_800CF630;
    }
    // 0x800CF60C: nop

    // 0x800CF610: lw          $t9, 0x74($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X74);
    // 0x800CF614: sll         $t2, $t6, 2
    ctx->r10 = S32(ctx->r14 << 2);
    // 0x800CF618: addu        $t2, $t2, $t6
    ctx->r10 = ADD32(ctx->r10, ctx->r14);
    // 0x800CF61C: lbu         $t0, 0x0($t9)
    ctx->r8 = MEM_BU(ctx->r25, 0X0);
    // 0x800CF620: sll         $t2, $t2, 1
    ctx->r10 = S32(ctx->r10 << 1);
    // 0x800CF624: addu        $t1, $t0, $t2
    ctx->r9 = ADD32(ctx->r8, ctx->r10);
    // 0x800CF628: addiu       $t3, $t1, -0x30
    ctx->r11 = ADD32(ctx->r9, -0X30);
    // 0x800CF62C: sw          $t3, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r11;
L_800CF630:
    // 0x800CF630: lw          $t7, 0x74($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X74);
    // 0x800CF634: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x800CF638: sw          $t8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r24;
    // 0x800CF63C: lbu         $t4, 0x0($t8)
    ctx->r12 = MEM_BU(ctx->r24, 0X0);
    // 0x800CF640: slti        $at, $t4, 0x30
    ctx->r1 = SIGNED(ctx->r12) < 0X30 ? 1 : 0;
    // 0x800CF644: bne         $at, $zero, L_800CF654
    if (ctx->r1 != 0) {
        // 0x800CF648: slti        $at, $t4, 0x3A
        ctx->r1 = SIGNED(ctx->r12) < 0X3A ? 1 : 0;
            goto L_800CF654;
    }
    // 0x800CF648: slti        $at, $t4, 0x3A
    ctx->r1 = SIGNED(ctx->r12) < 0X3A ? 1 : 0;
    // 0x800CF64C: bne         $at, $zero, L_800CF600
    if (ctx->r1 != 0) {
        // 0x800CF650: nop
    
            goto L_800CF600;
    }
    // 0x800CF650: nop

L_800CF654:
    // 0x800CF654: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800CF658: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800CF65C: addiu       $a0, $a0, -0x39B0
    ctx->r4 = ADD32(ctx->r4, -0X39B0);
    // 0x800CF660: jal         0x800D0514
    // 0x800CF664: lbu         $a1, 0x0($t5)
    ctx->r5 = MEM_BU(ctx->r13, 0X0);
    func_800D0514(rdram, ctx);
        goto after_3;
    // 0x800CF664: lbu         $a1, 0x0($t5)
    ctx->r5 = MEM_BU(ctx->r13, 0X0);
    after_3:
    // 0x800CF668: beq         $v0, $zero, L_800CF688
    if (ctx->r2 == 0) {
        // 0x800CF66C: nop
    
            goto L_800CF688;
    }
    // 0x800CF66C: nop

    // 0x800CF670: lw          $t9, 0x74($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X74);
    // 0x800CF674: lbu         $t6, 0x0($t9)
    ctx->r14 = MEM_BU(ctx->r25, 0X0);
    // 0x800CF678: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x800CF67C: sw          $t0, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r8;
    // 0x800CF680: b           L_800CF68C
    // 0x800CF684: sb          $t6, 0xAC($sp)
    MEM_B(0XAC, ctx->r29) = ctx->r14;
        goto L_800CF68C;
    // 0x800CF684: sb          $t6, 0xAC($sp)
    MEM_B(0XAC, ctx->r29) = ctx->r14;
L_800CF688:
    // 0x800CF688: sb          $zero, 0xAC($sp)
    MEM_B(0XAC, ctx->r29) = 0;
L_800CF68C:
    // 0x800CF68C: lbu         $t2, 0xAC($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0XAC);
    // 0x800CF690: addiu       $at, $zero, 0x6C
    ctx->r1 = ADD32(0, 0X6C);
    // 0x800CF694: bne         $t2, $at, L_800CF6C0
    if (ctx->r10 != ctx->r1) {
        // 0x800CF698: nop
    
            goto L_800CF6C0;
    }
    // 0x800CF698: nop

    // 0x800CF69C: lw          $t1, 0x74($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X74);
    // 0x800CF6A0: addiu       $at, $zero, 0x6C
    ctx->r1 = ADD32(0, 0X6C);
    // 0x800CF6A4: lbu         $t3, 0x0($t1)
    ctx->r11 = MEM_BU(ctx->r9, 0X0);
    // 0x800CF6A8: bne         $t3, $at, L_800CF6C0
    if (ctx->r11 != ctx->r1) {
        // 0x800CF6AC: nop
    
            goto L_800CF6C0;
    }
    // 0x800CF6AC: nop

    // 0x800CF6B0: addiu       $t7, $zero, 0x4C
    ctx->r15 = ADD32(0, 0X4C);
    // 0x800CF6B4: addiu       $t8, $t1, 0x1
    ctx->r24 = ADD32(ctx->r9, 0X1);
    // 0x800CF6B8: sb          $t7, 0xAC($sp)
    MEM_B(0XAC, ctx->r29) = ctx->r15;
    // 0x800CF6BC: sw          $t8, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r24;
L_800CF6C0:
    // 0x800CF6C0: lw          $t4, 0x74($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X74);
    // 0x800CF6C4: addiu       $a0, $sp, 0x78
    ctx->r4 = ADD32(ctx->r29, 0X78);
    // 0x800CF6C8: addiu       $a1, $sp, 0xBC
    ctx->r5 = ADD32(ctx->r29, 0XBC);
    // 0x800CF6CC: addiu       $a3, $sp, 0x4C
    ctx->r7 = ADD32(ctx->r29, 0X4C);
    // 0x800CF6D0: jal         0x800CFB5C
    // 0x800CF6D4: lbu         $a2, 0x0($t4)
    ctx->r6 = MEM_BU(ctx->r12, 0X0);
    _Putfld(rdram, ctx);
        goto after_4;
    // 0x800CF6D4: lbu         $a2, 0x0($t4)
    ctx->r6 = MEM_BU(ctx->r12, 0X0);
    after_4:
    // 0x800CF6D8: lw          $t5, 0x84($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X84);
    // 0x800CF6DC: lw          $t6, 0x88($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X88);
    // 0x800CF6E0: lw          $t0, 0x8C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X8C);
    // 0x800CF6E4: lw          $t3, 0x90($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X90);
    // 0x800CF6E8: addu        $t9, $t5, $t6
    ctx->r25 = ADD32(ctx->r13, ctx->r14);
    // 0x800CF6EC: lw          $t1, 0x94($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X94);
    // 0x800CF6F0: addu        $t2, $t9, $t0
    ctx->r10 = ADD32(ctx->r25, ctx->r8);
    // 0x800CF6F4: lw          $t4, 0x98($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X98);
    // 0x800CF6F8: lw          $t6, 0xA0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XA0);
    // 0x800CF6FC: lw          $t0, 0xA8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XA8);
    // 0x800CF700: addu        $t7, $t2, $t3
    ctx->r15 = ADD32(ctx->r10, ctx->r11);
    // 0x800CF704: addu        $t8, $t7, $t1
    ctx->r24 = ADD32(ctx->r15, ctx->r9);
    // 0x800CF708: addu        $t5, $t8, $t4
    ctx->r13 = ADD32(ctx->r24, ctx->r12);
    // 0x800CF70C: subu        $t9, $t6, $t5
    ctx->r25 = SUB32(ctx->r14, ctx->r13);
    // 0x800CF710: andi        $t2, $t0, 0x4
    ctx->r10 = ctx->r8 & 0X4;
    // 0x800CF714: bne         $t2, $zero, L_800CF7B8
    if (ctx->r10 != 0) {
        // 0x800CF718: sw          $t9, 0xA0($sp)
        MEM_W(0XA0, ctx->r29) = ctx->r25;
            goto L_800CF7B8;
    }
    // 0x800CF718: sw          $t9, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r25;
    // 0x800CF71C: slt         $t3, $zero, $t9
    ctx->r11 = SIGNED(0) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800CF720: beq         $t3, $zero, L_800CF7B8
    if (ctx->r11 == 0) {
        // 0x800CF724: nop
    
            goto L_800CF7B8;
    }
    // 0x800CF724: nop

    // 0x800CF728: beq         $t3, $zero, L_800CF7B8
    if (ctx->r11 == 0) {
        // 0x800CF72C: sw          $t9, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r25;
            goto L_800CF7B8;
    }
    // 0x800CF72C: sw          $t9, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r25;
L_800CF730:
    // 0x800CF730: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x800CF734: sltiu       $at, $t7, 0x21
    ctx->r1 = ctx->r15 < 0X21 ? 1 : 0;
    // 0x800CF738: bne         $at, $zero, L_800CF74C
    if (ctx->r1 != 0) {
        // 0x800CF73C: nop
    
            goto L_800CF74C;
    }
    // 0x800CF73C: nop

    // 0x800CF740: addiu       $t1, $zero, 0x20
    ctx->r9 = ADD32(0, 0X20);
    // 0x800CF744: b           L_800CF754
    // 0x800CF748: sw          $t1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r9;
        goto L_800CF754;
    // 0x800CF748: sw          $t1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r9;
L_800CF74C:
    // 0x800CF74C: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x800CF750: sw          $t8, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r24;
L_800CF754:
    // 0x800CF754: lw          $t4, 0x48($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X48);
    // 0x800CF758: blez        $t4, L_800CF7A4
    if (SIGNED(ctx->r12) <= 0) {
        // 0x800CF75C: nop
    
            goto L_800CF7A4;
    }
    // 0x800CF75C: nop

    // 0x800CF760: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF764: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x800CF768: addiu       $a1, $a1, -0x6F20
    ctx->r5 = ADD32(ctx->r5, -0X6F20);
    // 0x800CF76C: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF770: jalr        $t9
    // 0x800CF774: or          $a2, $t4, $zero
    ctx->r6 = ctx->r12 | 0;
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_5;
    // 0x800CF774: or          $a2, $t4, $zero
    ctx->r6 = ctx->r12 | 0;
    after_5:
    // 0x800CF778: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF77C: lw          $t6, 0xB4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF780: beq         $t6, $zero, L_800CF79C
    if (ctx->r14 == 0) {
        // 0x800CF784: nop
    
            goto L_800CF79C;
    }
    // 0x800CF784: nop

    // 0x800CF788: lw          $t5, 0xA4($sp)
    ctx->r13 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF78C: lw          $t0, 0x48($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X48);
    // 0x800CF790: addu        $t2, $t5, $t0
    ctx->r10 = ADD32(ctx->r13, ctx->r8);
    // 0x800CF794: b           L_800CF7A4
    // 0x800CF798: sw          $t2, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r10;
        goto L_800CF7A4;
    // 0x800CF798: sw          $t2, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r10;
L_800CF79C:
    // 0x800CF79C: b           L_800CFB48
    // 0x800CF7A0: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF7A0: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF7A4:
    // 0x800CF7A4: lw          $t3, 0x44($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X44);
    // 0x800CF7A8: lw          $t7, 0x48($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X48);
    // 0x800CF7AC: subu        $t1, $t3, $t7
    ctx->r9 = SUB32(ctx->r11, ctx->r15);
    // 0x800CF7B0: bgtz        $t1, L_800CF730
    if (SIGNED(ctx->r9) > 0) {
        // 0x800CF7B4: sw          $t1, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r9;
            goto L_800CF730;
    }
    // 0x800CF7B4: sw          $t1, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r9;
L_800CF7B8:
    // 0x800CF7B8: lw          $t8, 0x84($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X84);
    // 0x800CF7BC: blez        $t8, L_800CF804
    if (SIGNED(ctx->r24) <= 0) {
        // 0x800CF7C0: nop
    
            goto L_800CF804;
    }
    // 0x800CF7C0: nop

    // 0x800CF7C4: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF7C8: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF7CC: addiu       $a1, $sp, 0x4C
    ctx->r5 = ADD32(ctx->r29, 0X4C);
    // 0x800CF7D0: jalr        $t9
    // 0x800CF7D4: or          $a2, $t8, $zero
    ctx->r6 = ctx->r24 | 0;
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_6;
    // 0x800CF7D4: or          $a2, $t8, $zero
    ctx->r6 = ctx->r24 | 0;
    after_6:
    // 0x800CF7D8: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF7DC: lw          $t4, 0xB4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF7E0: beq         $t4, $zero, L_800CF7FC
    if (ctx->r12 == 0) {
        // 0x800CF7E4: nop
    
            goto L_800CF7FC;
    }
    // 0x800CF7E4: nop

    // 0x800CF7E8: lw          $t6, 0xA4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF7EC: lw          $t5, 0x84($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X84);
    // 0x800CF7F0: addu        $t0, $t6, $t5
    ctx->r8 = ADD32(ctx->r14, ctx->r13);
    // 0x800CF7F4: b           L_800CF804
    // 0x800CF7F8: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
        goto L_800CF804;
    // 0x800CF7F8: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
L_800CF7FC:
    // 0x800CF7FC: b           L_800CFB48
    // 0x800CF800: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF800: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF804:
    // 0x800CF804: lw          $t2, 0x88($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X88);
    // 0x800CF808: slt         $t3, $zero, $t2
    ctx->r11 = SIGNED(0) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x800CF80C: beq         $t3, $zero, L_800CF8A4
    if (ctx->r11 == 0) {
        // 0x800CF810: nop
    
            goto L_800CF8A4;
    }
    // 0x800CF810: nop

    // 0x800CF814: beq         $t3, $zero, L_800CF8A4
    if (ctx->r11 == 0) {
        // 0x800CF818: sw          $t2, 0x3C($sp)
        MEM_W(0X3C, ctx->r29) = ctx->r10;
            goto L_800CF8A4;
    }
    // 0x800CF818: sw          $t2, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r10;
L_800CF81C:
    // 0x800CF81C: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x800CF820: sltiu       $at, $t7, 0x21
    ctx->r1 = ctx->r15 < 0X21 ? 1 : 0;
    // 0x800CF824: bne         $at, $zero, L_800CF838
    if (ctx->r1 != 0) {
        // 0x800CF828: nop
    
            goto L_800CF838;
    }
    // 0x800CF828: nop

    // 0x800CF82C: addiu       $t1, $zero, 0x20
    ctx->r9 = ADD32(0, 0X20);
    // 0x800CF830: b           L_800CF840
    // 0x800CF834: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
        goto L_800CF840;
    // 0x800CF834: sw          $t1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r9;
L_800CF838:
    // 0x800CF838: lw          $t8, 0x3C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X3C);
    // 0x800CF83C: sw          $t8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r24;
L_800CF840:
    // 0x800CF840: lw          $t9, 0x40($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X40);
    // 0x800CF844: blez        $t9, L_800CF890
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800CF848: nop
    
            goto L_800CF890;
    }
    // 0x800CF848: nop

    // 0x800CF84C: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800CF850: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF854: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x800CF858: addiu       $a1, $a1, -0x6EFC
    ctx->r5 = ADD32(ctx->r5, -0X6EFC);
    // 0x800CF85C: jalr        $t9
    // 0x800CF860: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_7;
    // 0x800CF860: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    after_7:
    // 0x800CF864: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF868: lw          $t4, 0xB4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF86C: beq         $t4, $zero, L_800CF888
    if (ctx->r12 == 0) {
        // 0x800CF870: nop
    
            goto L_800CF888;
    }
    // 0x800CF870: nop

    // 0x800CF874: lw          $t6, 0xA4($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF878: lw          $t5, 0x40($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X40);
    // 0x800CF87C: addu        $t0, $t6, $t5
    ctx->r8 = ADD32(ctx->r14, ctx->r13);
    // 0x800CF880: b           L_800CF890
    // 0x800CF884: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
        goto L_800CF890;
    // 0x800CF884: sw          $t0, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r8;
L_800CF888:
    // 0x800CF888: b           L_800CFB48
    // 0x800CF88C: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF88C: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF890:
    // 0x800CF890: lw          $t2, 0x3C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X3C);
    // 0x800CF894: lw          $t3, 0x40($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X40);
    // 0x800CF898: subu        $t7, $t2, $t3
    ctx->r15 = SUB32(ctx->r10, ctx->r11);
    // 0x800CF89C: bgtz        $t7, L_800CF81C
    if (SIGNED(ctx->r15) > 0) {
        // 0x800CF8A0: sw          $t7, 0x3C($sp)
        MEM_W(0X3C, ctx->r29) = ctx->r15;
            goto L_800CF81C;
    }
    // 0x800CF8A0: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
L_800CF8A4:
    // 0x800CF8A4: lw          $t1, 0x8C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X8C);
    // 0x800CF8A8: blez        $t1, L_800CF8F0
    if (SIGNED(ctx->r9) <= 0) {
        // 0x800CF8AC: nop
    
            goto L_800CF8F0;
    }
    // 0x800CF8AC: nop

    // 0x800CF8B0: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF8B4: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF8B8: lw          $a1, 0x80($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X80);
    // 0x800CF8BC: jalr        $t9
    // 0x800CF8C0: or          $a2, $t1, $zero
    ctx->r6 = ctx->r9 | 0;
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_8;
    // 0x800CF8C0: or          $a2, $t1, $zero
    ctx->r6 = ctx->r9 | 0;
    after_8:
    // 0x800CF8C4: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF8C8: lw          $t8, 0xB4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF8CC: beq         $t8, $zero, L_800CF8E8
    if (ctx->r24 == 0) {
        // 0x800CF8D0: nop
    
            goto L_800CF8E8;
    }
    // 0x800CF8D0: nop

    // 0x800CF8D4: lw          $t4, 0xA4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF8D8: lw          $t6, 0x8C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X8C);
    // 0x800CF8DC: addu        $t5, $t4, $t6
    ctx->r13 = ADD32(ctx->r12, ctx->r14);
    // 0x800CF8E0: b           L_800CF8F0
    // 0x800CF8E4: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
        goto L_800CF8F0;
    // 0x800CF8E4: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
L_800CF8E8:
    // 0x800CF8E8: b           L_800CFB48
    // 0x800CF8EC: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF8EC: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF8F0:
    // 0x800CF8F0: lw          $t0, 0x90($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X90);
    // 0x800CF8F4: slt         $t2, $zero, $t0
    ctx->r10 = SIGNED(0) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x800CF8F8: beq         $t2, $zero, L_800CF990
    if (ctx->r10 == 0) {
        // 0x800CF8FC: nop
    
            goto L_800CF990;
    }
    // 0x800CF8FC: nop

    // 0x800CF900: beq         $t2, $zero, L_800CF990
    if (ctx->r10 == 0) {
        // 0x800CF904: sw          $t0, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r8;
            goto L_800CF990;
    }
    // 0x800CF904: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
L_800CF908:
    // 0x800CF908: lw          $t3, 0x34($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X34);
    // 0x800CF90C: sltiu       $at, $t3, 0x21
    ctx->r1 = ctx->r11 < 0X21 ? 1 : 0;
    // 0x800CF910: bne         $at, $zero, L_800CF924
    if (ctx->r1 != 0) {
        // 0x800CF914: nop
    
            goto L_800CF924;
    }
    // 0x800CF914: nop

    // 0x800CF918: addiu       $t7, $zero, 0x20
    ctx->r15 = ADD32(0, 0X20);
    // 0x800CF91C: b           L_800CF92C
    // 0x800CF920: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
        goto L_800CF92C;
    // 0x800CF920: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
L_800CF924:
    // 0x800CF924: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x800CF928: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
L_800CF92C:
    // 0x800CF92C: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800CF930: blez        $t9, L_800CF97C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800CF934: nop
    
            goto L_800CF97C;
    }
    // 0x800CF934: nop

    // 0x800CF938: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800CF93C: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF940: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x800CF944: addiu       $a1, $a1, -0x6EFC
    ctx->r5 = ADD32(ctx->r5, -0X6EFC);
    // 0x800CF948: jalr        $t9
    // 0x800CF94C: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_9;
    // 0x800CF94C: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    after_9:
    // 0x800CF950: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF954: lw          $t8, 0xB4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF958: beq         $t8, $zero, L_800CF974
    if (ctx->r24 == 0) {
        // 0x800CF95C: nop
    
            goto L_800CF974;
    }
    // 0x800CF95C: nop

    // 0x800CF960: lw          $t4, 0xA4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF964: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800CF968: addu        $t5, $t4, $t6
    ctx->r13 = ADD32(ctx->r12, ctx->r14);
    // 0x800CF96C: b           L_800CF97C
    // 0x800CF970: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
        goto L_800CF97C;
    // 0x800CF970: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
L_800CF974:
    // 0x800CF974: b           L_800CFB48
    // 0x800CF978: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF978: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF97C:
    // 0x800CF97C: lw          $t0, 0x34($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X34);
    // 0x800CF980: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800CF984: subu        $t3, $t0, $t2
    ctx->r11 = SUB32(ctx->r8, ctx->r10);
    // 0x800CF988: bgtz        $t3, L_800CF908
    if (SIGNED(ctx->r11) > 0) {
        // 0x800CF98C: sw          $t3, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r11;
            goto L_800CF908;
    }
    // 0x800CF98C: sw          $t3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r11;
L_800CF990:
    // 0x800CF990: lw          $t7, 0x94($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X94);
    // 0x800CF994: blez        $t7, L_800CF9E8
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800CF998: nop
    
            goto L_800CF9E8;
    }
    // 0x800CF998: nop

    // 0x800CF99C: lw          $t1, 0x80($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X80);
    // 0x800CF9A0: lw          $t9, 0x8C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X8C);
    // 0x800CF9A4: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF9A8: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x800CF9AC: addu        $a1, $t1, $t9
    ctx->r5 = ADD32(ctx->r9, ctx->r25);
    // 0x800CF9B0: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CF9B4: jalr        $t9
    // 0x800CF9B8: nop

    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_10;
    // 0x800CF9B8: nop

    after_10:
    // 0x800CF9BC: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CF9C0: lw          $t8, 0xB4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XB4);
    // 0x800CF9C4: beq         $t8, $zero, L_800CF9E0
    if (ctx->r24 == 0) {
        // 0x800CF9C8: nop
    
            goto L_800CF9E0;
    }
    // 0x800CF9C8: nop

    // 0x800CF9CC: lw          $t4, 0xA4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA4);
    // 0x800CF9D0: lw          $t6, 0x94($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X94);
    // 0x800CF9D4: addu        $t5, $t4, $t6
    ctx->r13 = ADD32(ctx->r12, ctx->r14);
    // 0x800CF9D8: b           L_800CF9E8
    // 0x800CF9DC: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
        goto L_800CF9E8;
    // 0x800CF9DC: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
L_800CF9E0:
    // 0x800CF9E0: b           L_800CFB48
    // 0x800CF9E4: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CF9E4: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CF9E8:
    // 0x800CF9E8: lw          $t0, 0x98($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X98);
    // 0x800CF9EC: slt         $t2, $zero, $t0
    ctx->r10 = SIGNED(0) < SIGNED(ctx->r8) ? 1 : 0;
    // 0x800CF9F0: beq         $t2, $zero, L_800CFA88
    if (ctx->r10 == 0) {
        // 0x800CF9F4: nop
    
            goto L_800CFA88;
    }
    // 0x800CF9F4: nop

    // 0x800CF9F8: beq         $t2, $zero, L_800CFA88
    if (ctx->r10 == 0) {
        // 0x800CF9FC: sw          $t0, 0x2C($sp)
        MEM_W(0X2C, ctx->r29) = ctx->r8;
            goto L_800CFA88;
    }
    // 0x800CF9FC: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
L_800CFA00:
    // 0x800CFA00: lw          $t3, 0x2C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X2C);
    // 0x800CFA04: sltiu       $at, $t3, 0x21
    ctx->r1 = ctx->r11 < 0X21 ? 1 : 0;
    // 0x800CFA08: bne         $at, $zero, L_800CFA1C
    if (ctx->r1 != 0) {
        // 0x800CFA0C: nop
    
            goto L_800CFA1C;
    }
    // 0x800CFA0C: nop

    // 0x800CFA10: addiu       $t1, $zero, 0x20
    ctx->r9 = ADD32(0, 0X20);
    // 0x800CFA14: b           L_800CFA24
    // 0x800CFA18: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
        goto L_800CFA24;
    // 0x800CFA18: sw          $t1, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r9;
L_800CFA1C:
    // 0x800CFA1C: lw          $t7, 0x2C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X2C);
    // 0x800CFA20: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
L_800CFA24:
    // 0x800CFA24: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800CFA28: blez        $t9, L_800CFA74
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800CFA2C: nop
    
            goto L_800CFA74;
    }
    // 0x800CFA2C: nop

    // 0x800CFA30: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x800CFA34: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CFA38: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x800CFA3C: addiu       $a1, $a1, -0x6EFC
    ctx->r5 = ADD32(ctx->r5, -0X6EFC);
    // 0x800CFA40: jalr        $t9
    // 0x800CFA44: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_11;
    // 0x800CFA44: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    after_11:
    // 0x800CFA48: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CFA4C: lw          $t8, 0xB4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XB4);
    // 0x800CFA50: beq         $t8, $zero, L_800CFA6C
    if (ctx->r24 == 0) {
        // 0x800CFA54: nop
    
            goto L_800CFA6C;
    }
    // 0x800CFA54: nop

    // 0x800CFA58: lw          $t4, 0xA4($sp)
    ctx->r12 = MEM_W(ctx->r29, 0XA4);
    // 0x800CFA5C: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800CFA60: addu        $t5, $t4, $t6
    ctx->r13 = ADD32(ctx->r12, ctx->r14);
    // 0x800CFA64: b           L_800CFA74
    // 0x800CFA68: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
        goto L_800CFA74;
    // 0x800CFA68: sw          $t5, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r13;
L_800CFA6C:
    // 0x800CFA6C: b           L_800CFB48
    // 0x800CFA70: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CFA70: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CFA74:
    // 0x800CFA74: lw          $t0, 0x2C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X2C);
    // 0x800CFA78: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800CFA7C: subu        $t3, $t0, $t2
    ctx->r11 = SUB32(ctx->r8, ctx->r10);
    // 0x800CFA80: bgtz        $t3, L_800CFA00
    if (SIGNED(ctx->r11) > 0) {
        // 0x800CFA84: sw          $t3, 0x2C($sp)
        MEM_W(0X2C, ctx->r29) = ctx->r11;
            goto L_800CFA00;
    }
    // 0x800CFA84: sw          $t3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r11;
L_800CFA88:
    // 0x800CFA88: lw          $t1, 0xA8($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XA8);
    // 0x800CFA8C: andi        $t7, $t1, 0x4
    ctx->r15 = ctx->r9 & 0X4;
    // 0x800CFA90: beq         $t7, $zero, L_800CFB38
    if (ctx->r15 == 0) {
        // 0x800CFA94: nop
    
            goto L_800CFB38;
    }
    // 0x800CFA94: nop

    // 0x800CFA98: lw          $t9, 0xA0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XA0);
    // 0x800CFA9C: slt         $t8, $zero, $t9
    ctx->r24 = SIGNED(0) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800CFAA0: beq         $t8, $zero, L_800CFB38
    if (ctx->r24 == 0) {
        // 0x800CFAA4: nop
    
            goto L_800CFB38;
    }
    // 0x800CFAA4: nop

    // 0x800CFAA8: beq         $t8, $zero, L_800CFB38
    if (ctx->r24 == 0) {
        // 0x800CFAAC: sw          $t9, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r25;
            goto L_800CFB38;
    }
    // 0x800CFAAC: sw          $t9, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r25;
L_800CFAB0:
    // 0x800CFAB0: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
    // 0x800CFAB4: sltiu       $at, $t4, 0x21
    ctx->r1 = ctx->r12 < 0X21 ? 1 : 0;
    // 0x800CFAB8: bne         $at, $zero, L_800CFACC
    if (ctx->r1 != 0) {
        // 0x800CFABC: nop
    
            goto L_800CFACC;
    }
    // 0x800CFABC: nop

    // 0x800CFAC0: addiu       $t6, $zero, 0x20
    ctx->r14 = ADD32(0, 0X20);
    // 0x800CFAC4: b           L_800CFAD4
    // 0x800CFAC8: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
        goto L_800CFAD4;
    // 0x800CFAC8: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
L_800CFACC:
    // 0x800CFACC: lw          $t5, 0x24($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X24);
    // 0x800CFAD0: sw          $t5, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r13;
L_800CFAD4:
    // 0x800CFAD4: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x800CFAD8: blez        $t0, L_800CFB24
    if (SIGNED(ctx->r8) <= 0) {
        // 0x800CFADC: nop
    
            goto L_800CFB24;
    }
    // 0x800CFADC: nop

    // 0x800CFAE0: lw          $t9, 0xB0($sp)
    ctx->r25 = MEM_W(ctx->r29, 0XB0);
    // 0x800CFAE4: lui         $a1, 0x800F
    ctx->r5 = S32(0X800F << 16);
    // 0x800CFAE8: addiu       $a1, $a1, -0x6F20
    ctx->r5 = ADD32(ctx->r5, -0X6F20);
    // 0x800CFAEC: lw          $a0, 0xB4($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XB4);
    // 0x800CFAF0: jalr        $t9
    // 0x800CFAF4: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_12;
    // 0x800CFAF4: or          $a2, $t0, $zero
    ctx->r6 = ctx->r8 | 0;
    after_12:
    // 0x800CFAF8: sw          $v0, 0xB4($sp)
    MEM_W(0XB4, ctx->r29) = ctx->r2;
    // 0x800CFAFC: lw          $t2, 0xB4($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XB4);
    // 0x800CFB00: beq         $t2, $zero, L_800CFB1C
    if (ctx->r10 == 0) {
        // 0x800CFB04: nop
    
            goto L_800CFB1C;
    }
    // 0x800CFB04: nop

    // 0x800CFB08: lw          $t3, 0xA4($sp)
    ctx->r11 = MEM_W(ctx->r29, 0XA4);
    // 0x800CFB0C: lw          $t1, 0x28($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X28);
    // 0x800CFB10: addu        $t7, $t3, $t1
    ctx->r15 = ADD32(ctx->r11, ctx->r9);
    // 0x800CFB14: b           L_800CFB24
    // 0x800CFB18: sw          $t7, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r15;
        goto L_800CFB24;
    // 0x800CFB18: sw          $t7, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r15;
L_800CFB1C:
    // 0x800CFB1C: b           L_800CFB48
    // 0x800CFB20: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
        goto L_800CFB48;
    // 0x800CFB20: lw          $v0, 0xA4($sp)
    ctx->r2 = MEM_W(ctx->r29, 0XA4);
L_800CFB24:
    // 0x800CFB24: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
    // 0x800CFB28: lw          $t4, 0x28($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X28);
    // 0x800CFB2C: subu        $t6, $t8, $t4
    ctx->r14 = SUB32(ctx->r24, ctx->r12);
    // 0x800CFB30: bgtz        $t6, L_800CFAB0
    if (SIGNED(ctx->r14) > 0) {
        // 0x800CFB34: sw          $t6, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r14;
            goto L_800CFAB0;
    }
    // 0x800CFB34: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
L_800CFB38:
    // 0x800CFB38: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800CFB3C: addiu       $t0, $t5, 0x1
    ctx->r8 = ADD32(ctx->r13, 0X1);
    // 0x800CFB40: b           L_800CF350
    // 0x800CFB44: sw          $t0, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r8;
        goto L_800CF350;
    // 0x800CFB44: sw          $t0, 0xB8($sp)
    MEM_W(0XB8, ctx->r29) = ctx->r8;
L_800CFB48:
    // 0x800CFB48: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800CFB4C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800CFB50: addiu       $sp, $sp, 0xB0
    ctx->r29 = ADD32(ctx->r29, 0XB0);
    // 0x800CFB54: jr          $ra
    // 0x800CFB58: nop

    return;
    // 0x800CFB58: nop

;}
RECOMP_FUNC void _Putfld(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800CFB5C: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800CFB60: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x800CFB64: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800CFB68: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800CFB6C: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x800CFB70: sw          $a2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r6;
    // 0x800CFB74: sw          $a3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r7;
    // 0x800CFB78: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x800CFB7C: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x800CFB80: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x800CFB84: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x800CFB88: sw          $zero, 0x20($t6)
    MEM_W(0X20, ctx->r14) = 0;
    // 0x800CFB8C: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800CFB90: lw          $s3, 0x20($t7)
    ctx->r19 = MEM_W(ctx->r15, 0X20);
    // 0x800CFB94: sw          $s3, 0x1C($t7)
    MEM_W(0X1C, ctx->r15) = ctx->r19;
    // 0x800CFB98: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800CFB9C: or          $s2, $s3, $zero
    ctx->r18 = ctx->r19 | 0;
    // 0x800CFBA0: or          $s1, $s2, $zero
    ctx->r17 = ctx->r18 | 0;
    // 0x800CFBA4: sw          $s2, 0x18($t8)
    MEM_W(0X18, ctx->r24) = ctx->r18;
    // 0x800CFBA8: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800CFBAC: or          $s0, $s1, $zero
    ctx->r16 = ctx->r17 | 0;
    // 0x800CFBB0: sw          $s1, 0x14($t9)
    MEM_W(0X14, ctx->r25) = ctx->r17;
    // 0x800CFBB4: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800CFBB8: sw          $s0, 0x10($t0)
    MEM_W(0X10, ctx->r8) = ctx->r16;
    // 0x800CFBBC: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFBC0: sw          $s0, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->r16;
    // 0x800CFBC4: lbu         $s0, 0x43($sp)
    ctx->r16 = MEM_BU(ctx->r29, 0X43);
    // 0x800CFBC8: slti        $at, $s0, 0x26
    ctx->r1 = SIGNED(ctx->r16) < 0X26 ? 1 : 0;
    // 0x800CFBCC: bne         $at, $zero, L_800CFBFC
    if (ctx->r1 != 0) {
        // 0x800CFBD0: nop
    
            goto L_800CFBFC;
    }
    // 0x800CFBD0: nop

    // 0x800CFBD4: addiu       $t2, $s0, -0x45
    ctx->r10 = ADD32(ctx->r16, -0X45);
    // 0x800CFBD8: sltiu       $at, $t2, 0x34
    ctx->r1 = ctx->r10 < 0X34 ? 1 : 0;
    // 0x800CFBDC: beq         $at, $zero, L_800D0470
    if (ctx->r1 == 0) {
        // 0x800CFBE0: nop
    
            goto L_800D0470;
    }
    // 0x800CFBE0: nop

    // 0x800CFBE4: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x800CFBE8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800CFBEC: addu        $at, $at, $t2
    gpr jr_addend_800CFBF4 = ctx->r10;
    ctx->r1 = ADD32(ctx->r1, ctx->r10);
    // 0x800CFBF0: lw          $t2, -0x398C($at)
    ctx->r10 = ADD32(ctx->r1, -0X398C);
    // 0x800CFBF4: jr          $t2
    // 0x800CFBF8: nop

    switch (jr_addend_800CFBF4 >> 2) {
        case 0: goto L_800D0044; break;
        case 1: goto L_800D0470; break;
        case 2: goto L_800D0044; break;
        case 3: goto L_800D0470; break;
        case 4: goto L_800D0470; break;
        case 5: goto L_800D0470; break;
        case 6: goto L_800D0470; break;
        case 7: goto L_800D0470; break;
        case 8: goto L_800D0470; break;
        case 9: goto L_800D0470; break;
        case 10: goto L_800D0470; break;
        case 11: goto L_800D0470; break;
        case 12: goto L_800D0470; break;
        case 13: goto L_800D0470; break;
        case 14: goto L_800D0470; break;
        case 15: goto L_800D0470; break;
        case 16: goto L_800D0470; break;
        case 17: goto L_800D0470; break;
        case 18: goto L_800D0470; break;
        case 19: goto L_800CFE60; break;
        case 20: goto L_800D0470; break;
        case 21: goto L_800D0470; break;
        case 22: goto L_800D0470; break;
        case 23: goto L_800D0470; break;
        case 24: goto L_800D0470; break;
        case 25: goto L_800D0470; break;
        case 26: goto L_800D0470; break;
        case 27: goto L_800D0470; break;
        case 28: goto L_800D0470; break;
        case 29: goto L_800D0470; break;
        case 30: goto L_800CFC10; break;
        case 31: goto L_800CFC60; break;
        case 32: goto L_800D0044; break;
        case 33: goto L_800D0044; break;
        case 34: goto L_800D0044; break;
        case 35: goto L_800D0470; break;
        case 36: goto L_800CFC60; break;
        case 37: goto L_800D0470; break;
        case 38: goto L_800D0470; break;
        case 39: goto L_800D0470; break;
        case 40: goto L_800D0470; break;
        case 41: goto L_800D024C; break;
        case 42: goto L_800CFE60; break;
        case 43: goto L_800D0374; break;
        case 44: goto L_800D0470; break;
        case 45: goto L_800D0470; break;
        case 46: goto L_800D03D8; break;
        case 47: goto L_800D0470; break;
        case 48: goto L_800CFE60; break;
        case 49: goto L_800D0470; break;
        case 50: goto L_800D0470; break;
        case 51: goto L_800CFE60; break;
        default: switch_error(__func__, 0x800CFBF4, 0x800EC674);
    }
    // 0x800CFBF8: nop

L_800CFBFC:
    // 0x800CFBFC: addiu       $at, $zero, 0x25
    ctx->r1 = ADD32(0, 0X25);
    // 0x800CFC00: beq         $s0, $at, L_800D0444
    if (ctx->r16 == ctx->r1) {
        // 0x800CFC04: nop
    
            goto L_800D0444;
    }
    // 0x800CFC04: nop

    // 0x800CFC08: b           L_800D0470
    // 0x800CFC0C: nop

        goto L_800D0470;
    // 0x800CFC0C: nop

L_800CFC10:
    // 0x800CFC10: lw          $t3, 0x3C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFC14: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CFC18: lw          $t4, 0x0($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X0);
    // 0x800CFC1C: addiu       $t5, $t4, 0x3
    ctx->r13 = ADD32(ctx->r12, 0X3);
    // 0x800CFC20: and         $t6, $t5, $at
    ctx->r14 = ctx->r13 & ctx->r1;
    // 0x800CFC24: addiu       $t7, $t6, 0x4
    ctx->r15 = ADD32(ctx->r14, 0X4);
    // 0x800CFC28: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
    // 0x800CFC2C: lw          $t8, 0x3C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFC30: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800CFC34: lw          $t1, 0x44($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X44);
    // 0x800CFC38: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x800CFC3C: lw          $t4, 0xC($t2)
    ctx->r12 = MEM_W(ctx->r10, 0XC);
    // 0x800CFC40: lw          $t0, -0x4($t9)
    ctx->r8 = MEM_W(ctx->r25, -0X4);
    // 0x800CFC44: addu        $t5, $t1, $t4
    ctx->r13 = ADD32(ctx->r9, ctx->r12);
    // 0x800CFC48: sb          $t0, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r8;
    // 0x800CFC4C: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800CFC50: lw          $t7, 0xC($t6)
    ctx->r15 = MEM_W(ctx->r14, 0XC);
    // 0x800CFC54: addiu       $t3, $t7, 0x1
    ctx->r11 = ADD32(ctx->r15, 0X1);
    // 0x800CFC58: b           L_800D0498
    // 0x800CFC5C: sw          $t3, 0xC($t6)
    MEM_W(0XC, ctx->r14) = ctx->r11;
        goto L_800D0498;
    // 0x800CFC5C: sw          $t3, 0xC($t6)
    MEM_W(0XC, ctx->r14) = ctx->r11;
L_800CFC60:
    // 0x800CFC60: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800CFC64: addiu       $at, $zero, 0x6C
    ctx->r1 = ADD32(0, 0X6C);
    // 0x800CFC68: lbu         $t9, 0x34($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X34);
    // 0x800CFC6C: bne         $t9, $at, L_800CFCB4
    if (ctx->r25 != ctx->r1) {
        // 0x800CFC70: nop
    
            goto L_800CFCB4;
    }
    // 0x800CFC70: nop

    // 0x800CFC74: lw          $t2, 0x3C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFC78: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CFC7C: lw          $t1, 0x0($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X0);
    // 0x800CFC80: addiu       $t4, $t1, 0x3
    ctx->r12 = ADD32(ctx->r9, 0X3);
    // 0x800CFC84: and         $t0, $t4, $at
    ctx->r8 = ctx->r12 & ctx->r1;
    // 0x800CFC88: addiu       $t5, $t0, 0x4
    ctx->r13 = ADD32(ctx->r8, 0X4);
    // 0x800CFC8C: sw          $t5, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r13;
    // 0x800CFC90: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFC94: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFC98: lw          $t3, 0x0($t7)
    ctx->r11 = MEM_W(ctx->r15, 0X0);
    // 0x800CFC9C: lw          $t6, -0x4($t3)
    ctx->r14 = MEM_W(ctx->r11, -0X4);
    // 0x800CFCA0: or          $t9, $t6, $zero
    ctx->r25 = ctx->r14 | 0;
    // 0x800CFCA4: sra         $t8, $t6, 31
    ctx->r24 = S32(SIGNED(ctx->r14) >> 31);
    // 0x800CFCA8: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x800CFCAC: b           L_800CFD40
    // 0x800CFCB0: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
        goto L_800CFD40;
    // 0x800CFCB0: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
L_800CFCB4:
    // 0x800CFCB4: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800CFCB8: addiu       $at, $zero, 0x4C
    ctx->r1 = ADD32(0, 0X4C);
    // 0x800CFCBC: lbu         $t0, 0x34($t4)
    ctx->r8 = MEM_BU(ctx->r12, 0X34);
    // 0x800CFCC0: bne         $t0, $at, L_800CFD04
    if (ctx->r8 != ctx->r1) {
        // 0x800CFCC4: nop
    
            goto L_800CFD04;
    }
    // 0x800CFCC4: nop

    // 0x800CFCC8: lw          $t5, 0x3C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFCCC: addiu       $at, $zero, -0x8
    ctx->r1 = ADD32(0, -0X8);
    // 0x800CFCD0: lw          $t2, 0x0($t5)
    ctx->r10 = MEM_W(ctx->r13, 0X0);
    // 0x800CFCD4: addiu       $t7, $t2, 0x7
    ctx->r15 = ADD32(ctx->r10, 0X7);
    // 0x800CFCD8: and         $t3, $t7, $at
    ctx->r11 = ctx->r15 & ctx->r1;
    // 0x800CFCDC: addiu       $t6, $t3, 0x8
    ctx->r14 = ADD32(ctx->r11, 0X8);
    // 0x800CFCE0: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x800CFCE4: lw          $t8, 0x3C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFCE8: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFCEC: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x800CFCF0: lw          $t4, -0x8($t9)
    ctx->r12 = MEM_W(ctx->r25, -0X8);
    // 0x800CFCF4: lw          $t5, -0x4($t9)
    ctx->r13 = MEM_W(ctx->r25, -0X4);
    // 0x800CFCF8: sw          $t4, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r12;
    // 0x800CFCFC: b           L_800CFD40
    // 0x800CFD00: sw          $t5, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r13;
        goto L_800CFD40;
    // 0x800CFD00: sw          $t5, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r13;
L_800CFD04:
    // 0x800CFD04: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFD08: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CFD0C: lw          $t2, 0x0($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X0);
    // 0x800CFD10: addiu       $t7, $t2, 0x3
    ctx->r15 = ADD32(ctx->r10, 0X3);
    // 0x800CFD14: and         $t3, $t7, $at
    ctx->r11 = ctx->r15 & ctx->r1;
    // 0x800CFD18: addiu       $t6, $t3, 0x4
    ctx->r14 = ADD32(ctx->r11, 0X4);
    // 0x800CFD1C: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x800CFD20: lw          $t8, 0x3C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFD24: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800CFD28: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x800CFD2C: lw          $t4, -0x4($t9)
    ctx->r12 = MEM_W(ctx->r25, -0X4);
    // 0x800CFD30: or          $t3, $t4, $zero
    ctx->r11 = ctx->r12 | 0;
    // 0x800CFD34: sra         $t2, $t4, 31
    ctx->r10 = S32(SIGNED(ctx->r12) >> 31);
    // 0x800CFD38: sw          $t2, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r10;
    // 0x800CFD3C: sw          $t3, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r11;
L_800CFD40:
    // 0x800CFD40: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFD44: addiu       $at, $zero, 0x68
    ctx->r1 = ADD32(0, 0X68);
    // 0x800CFD48: lbu         $t7, 0x34($t1)
    ctx->r15 = MEM_BU(ctx->r9, 0X34);
    // 0x800CFD4C: bne         $t7, $at, L_800CFD78
    if (ctx->r15 != ctx->r1) {
        // 0x800CFD50: nop
    
            goto L_800CFD78;
    }
    // 0x800CFD50: nop

    // 0x800CFD54: lw          $t7, 0x4($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X4);
    // 0x800CFD58: lw          $t6, 0x0($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X0);
    // 0x800CFD5C: or          $t0, $t7, $zero
    ctx->r8 = ctx->r15 | 0;
    // 0x800CFD60: sll         $t8, $t0, 16
    ctx->r24 = S32(ctx->r8 << 16);
    // 0x800CFD64: sra         $t9, $t8, 16
    ctx->r25 = S32(SIGNED(ctx->r24) >> 16);
    // 0x800CFD68: or          $t5, $t9, $zero
    ctx->r13 = ctx->r25 | 0;
    // 0x800CFD6C: sra         $t4, $t9, 31
    ctx->r12 = S32(SIGNED(ctx->r25) >> 31);
    // 0x800CFD70: sw          $t4, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r12;
    // 0x800CFD74: sw          $t5, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r13;
L_800CFD78:
    // 0x800CFD78: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800CFD7C: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x800CFD80: lw          $t7, 0x4($t2)
    ctx->r15 = MEM_W(ctx->r10, 0X4);
    // 0x800CFD84: bgtz        $t6, L_800CFDC4
    if (SIGNED(ctx->r14) > 0) {
        // 0x800CFD88: nop
    
            goto L_800CFDC4;
    }
    // 0x800CFD88: nop

    // 0x800CFD8C: bltz        $t6, L_800CFD9C
    if (SIGNED(ctx->r14) < 0) {
        // 0x800CFD90: nop
    
            goto L_800CFD9C;
    }
    // 0x800CFD90: nop

    // 0x800CFD94: b           L_800CFDC4
    // 0x800CFD98: nop

        goto L_800CFDC4;
    // 0x800CFD98: nop

L_800CFD9C:
    // 0x800CFD9C: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800CFDA0: lw          $t8, 0xC($t2)
    ctx->r24 = MEM_W(ctx->r10, 0XC);
    // 0x800CFDA4: addiu       $t3, $zero, 0x2D
    ctx->r11 = ADD32(0, 0X2D);
    // 0x800CFDA8: addu        $t9, $t0, $t8
    ctx->r25 = ADD32(ctx->r8, ctx->r24);
    // 0x800CFDAC: sb          $t3, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r11;
    // 0x800CFDB0: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800CFDB4: lw          $t5, 0xC($t4)
    ctx->r13 = MEM_W(ctx->r12, 0XC);
    // 0x800CFDB8: addiu       $t1, $t5, 0x1
    ctx->r9 = ADD32(ctx->r13, 0X1);
    // 0x800CFDBC: b           L_800CFE38
    // 0x800CFDC0: sw          $t1, 0xC($t4)
    MEM_W(0XC, ctx->r12) = ctx->r9;
        goto L_800CFE38;
    // 0x800CFDC0: sw          $t1, 0xC($t4)
    MEM_W(0XC, ctx->r12) = ctx->r9;
L_800CFDC4:
    // 0x800CFDC4: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800CFDC8: lw          $t7, 0x30($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X30);
    // 0x800CFDCC: andi        $t2, $t7, 0x2
    ctx->r10 = ctx->r15 & 0X2;
    // 0x800CFDD0: beq         $t2, $zero, L_800CFE00
    if (ctx->r10 == 0) {
        // 0x800CFDD4: nop
    
            goto L_800CFE00;
    }
    // 0x800CFDD4: nop

    // 0x800CFDD8: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x800CFDDC: lw          $t3, 0xC($t6)
    ctx->r11 = MEM_W(ctx->r14, 0XC);
    // 0x800CFDE0: addiu       $t0, $zero, 0x2B
    ctx->r8 = ADD32(0, 0X2B);
    // 0x800CFDE4: addu        $t9, $t8, $t3
    ctx->r25 = ADD32(ctx->r24, ctx->r11);
    // 0x800CFDE8: sb          $t0, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r8;
    // 0x800CFDEC: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800CFDF0: lw          $t1, 0xC($t5)
    ctx->r9 = MEM_W(ctx->r13, 0XC);
    // 0x800CFDF4: addiu       $t4, $t1, 0x1
    ctx->r12 = ADD32(ctx->r9, 0X1);
    // 0x800CFDF8: b           L_800CFE38
    // 0x800CFDFC: sw          $t4, 0xC($t5)
    MEM_W(0XC, ctx->r13) = ctx->r12;
        goto L_800CFE38;
    // 0x800CFDFC: sw          $t4, 0xC($t5)
    MEM_W(0XC, ctx->r13) = ctx->r12;
L_800CFE00:
    // 0x800CFE00: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800CFE04: lw          $t2, 0x30($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X30);
    // 0x800CFE08: andi        $t6, $t2, 0x1
    ctx->r14 = ctx->r10 & 0X1;
    // 0x800CFE0C: beq         $t6, $zero, L_800CFE38
    if (ctx->r14 == 0) {
        // 0x800CFE10: nop
    
            goto L_800CFE38;
    }
    // 0x800CFE10: nop

    // 0x800CFE14: lw          $t3, 0x44($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X44);
    // 0x800CFE18: lw          $t0, 0xC($t7)
    ctx->r8 = MEM_W(ctx->r15, 0XC);
    // 0x800CFE1C: addiu       $t8, $zero, 0x20
    ctx->r24 = ADD32(0, 0X20);
    // 0x800CFE20: addu        $t9, $t3, $t0
    ctx->r25 = ADD32(ctx->r11, ctx->r8);
    // 0x800CFE24: sb          $t8, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r24;
    // 0x800CFE28: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFE2C: lw          $t4, 0xC($t1)
    ctx->r12 = MEM_W(ctx->r9, 0XC);
    // 0x800CFE30: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x800CFE34: sw          $t5, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->r13;
L_800CFE38:
    // 0x800CFE38: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800CFE3C: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x800CFE40: lw          $t6, 0xC($t2)
    ctx->r14 = MEM_W(ctx->r10, 0XC);
    // 0x800CFE44: addu        $t3, $t6, $t7
    ctx->r11 = ADD32(ctx->r14, ctx->r15);
    // 0x800CFE48: sw          $t3, 0x8($t2)
    MEM_W(0X8, ctx->r10) = ctx->r11;
    // 0x800CFE4C: lbu         $a1, 0x43($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X43);
    // 0x800CFE50: jal         0x800D0FE0
    // 0x800CFE54: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    _Litob(rdram, ctx);
        goto after_0;
    // 0x800CFE54: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    after_0:
    // 0x800CFE58: b           L_800D0498
    // 0x800CFE5C: nop

        goto L_800D0498;
    // 0x800CFE5C: nop

L_800CFE60:
    // 0x800CFE60: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800CFE64: addiu       $at, $zero, 0x6C
    ctx->r1 = ADD32(0, 0X6C);
    // 0x800CFE68: lbu         $t8, 0x34($t0)
    ctx->r24 = MEM_BU(ctx->r8, 0X34);
    // 0x800CFE6C: bne         $t8, $at, L_800CFEB4
    if (ctx->r24 != ctx->r1) {
        // 0x800CFE70: nop
    
            goto L_800CFEB4;
    }
    // 0x800CFE70: nop

    // 0x800CFE74: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFE78: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CFE7C: lw          $t4, 0x0($t9)
    ctx->r12 = MEM_W(ctx->r25, 0X0);
    // 0x800CFE80: addiu       $t5, $t4, 0x3
    ctx->r13 = ADD32(ctx->r12, 0X3);
    // 0x800CFE84: and         $t1, $t5, $at
    ctx->r9 = ctx->r13 & ctx->r1;
    // 0x800CFE88: addiu       $t6, $t1, 0x4
    ctx->r14 = ADD32(ctx->r9, 0X4);
    // 0x800CFE8C: sw          $t6, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r14;
    // 0x800CFE90: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFE94: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800CFE98: lw          $t3, 0x0($t7)
    ctx->r11 = MEM_W(ctx->r15, 0X0);
    // 0x800CFE9C: lw          $t2, -0x4($t3)
    ctx->r10 = MEM_W(ctx->r11, -0X4);
    // 0x800CFEA0: or          $t1, $t2, $zero
    ctx->r9 = ctx->r10 | 0;
    // 0x800CFEA4: sra         $t0, $t2, 31
    ctx->r8 = S32(SIGNED(ctx->r10) >> 31);
    // 0x800CFEA8: sw          $t0, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r8;
    // 0x800CFEAC: b           L_800CFF40
    // 0x800CFEB0: sw          $t1, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r9;
        goto L_800CFF40;
    // 0x800CFEB0: sw          $t1, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r9;
L_800CFEB4:
    // 0x800CFEB4: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800CFEB8: addiu       $at, $zero, 0x4C
    ctx->r1 = ADD32(0, 0X4C);
    // 0x800CFEBC: lbu         $t5, 0x34($t4)
    ctx->r13 = MEM_BU(ctx->r12, 0X34);
    // 0x800CFEC0: bne         $t5, $at, L_800CFF04
    if (ctx->r13 != ctx->r1) {
        // 0x800CFEC4: nop
    
            goto L_800CFF04;
    }
    // 0x800CFEC4: nop

    // 0x800CFEC8: lw          $t6, 0x3C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFECC: addiu       $at, $zero, -0x8
    ctx->r1 = ADD32(0, -0X8);
    // 0x800CFED0: lw          $t9, 0x0($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X0);
    // 0x800CFED4: addiu       $t7, $t9, 0x7
    ctx->r15 = ADD32(ctx->r25, 0X7);
    // 0x800CFED8: and         $t3, $t7, $at
    ctx->r11 = ctx->r15 & ctx->r1;
    // 0x800CFEDC: addiu       $t2, $t3, 0x8
    ctx->r10 = ADD32(ctx->r11, 0X8);
    // 0x800CFEE0: sw          $t2, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r10;
    // 0x800CFEE4: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFEE8: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800CFEEC: lw          $t1, 0x0($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X0);
    // 0x800CFEF0: lw          $t8, -0x8($t1)
    ctx->r24 = MEM_W(ctx->r9, -0X8);
    // 0x800CFEF4: lw          $t9, -0x4($t1)
    ctx->r25 = MEM_W(ctx->r9, -0X4);
    // 0x800CFEF8: sw          $t8, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r24;
    // 0x800CFEFC: b           L_800CFF40
    // 0x800CFF00: sw          $t9, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r25;
        goto L_800CFF40;
    // 0x800CFF00: sw          $t9, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r25;
L_800CFF04:
    // 0x800CFF04: lw          $t5, 0x3C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFF08: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800CFF0C: lw          $t7, 0x0($t5)
    ctx->r15 = MEM_W(ctx->r13, 0X0);
    // 0x800CFF10: addiu       $t3, $t7, 0x3
    ctx->r11 = ADD32(ctx->r15, 0X3);
    // 0x800CFF14: and         $t2, $t3, $at
    ctx->r10 = ctx->r11 & ctx->r1;
    // 0x800CFF18: addiu       $t6, $t2, 0x4
    ctx->r14 = ADD32(ctx->r10, 0X4);
    // 0x800CFF1C: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x800CFF20: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800CFF24: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800CFF28: lw          $t1, 0x0($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X0);
    // 0x800CFF2C: lw          $t8, -0x4($t1)
    ctx->r24 = MEM_W(ctx->r9, -0X4);
    // 0x800CFF30: or          $t5, $t8, $zero
    ctx->r13 = ctx->r24 | 0;
    // 0x800CFF34: sra         $t4, $t8, 31
    ctx->r12 = S32(SIGNED(ctx->r24) >> 31);
    // 0x800CFF38: sw          $t4, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r12;
    // 0x800CFF3C: sw          $t5, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r13;
L_800CFF40:
    // 0x800CFF40: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800CFF44: addiu       $at, $zero, 0x68
    ctx->r1 = ADD32(0, 0X68);
    // 0x800CFF48: lbu         $t3, 0x34($t7)
    ctx->r11 = MEM_BU(ctx->r15, 0X34);
    // 0x800CFF4C: bne         $t3, $at, L_800CFF78
    if (ctx->r11 != ctx->r1) {
        // 0x800CFF50: nop
    
            goto L_800CFF78;
    }
    // 0x800CFF50: nop

    // 0x800CFF54: lw          $t3, 0x4($t7)
    ctx->r11 = MEM_W(ctx->r15, 0X4);
    // 0x800CFF58: lw          $t2, 0x0($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X0);
    // 0x800CFF5C: addiu       $t8, $zero, 0x0
    ctx->r24 = ADD32(0, 0X0);
    // 0x800CFF60: or          $t6, $t3, $zero
    ctx->r14 = ctx->r11 | 0;
    // 0x800CFF64: andi        $t0, $t6, 0xFFFF
    ctx->r8 = ctx->r14 & 0XFFFF;
    // 0x800CFF68: or          $t9, $t0, $zero
    ctx->r25 = ctx->r8 | 0;
    // 0x800CFF6C: sw          $t9, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->r25;
    // 0x800CFF70: b           L_800CFFA4
    // 0x800CFF74: sw          $t8, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r24;
        goto L_800CFFA4;
    // 0x800CFF74: sw          $t8, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r24;
L_800CFF78:
    // 0x800CFF78: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800CFF7C: lbu         $t4, 0x34($t1)
    ctx->r12 = MEM_BU(ctx->r9, 0X34);
    // 0x800CFF80: bne         $t4, $zero, L_800CFFA4
    if (ctx->r12 != 0) {
        // 0x800CFF84: nop
    
            goto L_800CFFA4;
    }
    // 0x800CFF84: nop

    // 0x800CFF88: lw          $t3, 0x4($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X4);
    // 0x800CFF8C: lw          $t2, 0x0($t1)
    ctx->r10 = MEM_W(ctx->r9, 0X0);
    // 0x800CFF90: addiu       $t6, $zero, 0x0
    ctx->r14 = ADD32(0, 0X0);
    // 0x800CFF94: or          $t5, $t3, $zero
    ctx->r13 = ctx->r11 | 0;
    // 0x800CFF98: or          $t7, $t5, $zero
    ctx->r15 = ctx->r13 | 0;
    // 0x800CFF9C: sw          $t7, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r15;
    // 0x800CFFA0: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
L_800CFFA4:
    // 0x800CFFA4: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800CFFA8: lw          $t8, 0x30($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X30);
    // 0x800CFFAC: andi        $t9, $t8, 0x8
    ctx->r25 = ctx->r24 & 0X8;
    // 0x800CFFB0: beq         $t9, $zero, L_800D001C
    if (ctx->r25 == 0) {
        // 0x800CFFB4: nop
    
            goto L_800D001C;
    }
    // 0x800CFFB4: nop

    // 0x800CFFB8: lw          $t2, 0x44($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X44);
    // 0x800CFFBC: lw          $t3, 0xC($t0)
    ctx->r11 = MEM_W(ctx->r8, 0XC);
    // 0x800CFFC0: addiu       $t4, $zero, 0x30
    ctx->r12 = ADD32(0, 0X30);
    // 0x800CFFC4: addiu       $at, $zero, 0x78
    ctx->r1 = ADD32(0, 0X78);
    // 0x800CFFC8: addu        $t5, $t2, $t3
    ctx->r13 = ADD32(ctx->r10, ctx->r11);
    // 0x800CFFCC: sb          $t4, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r12;
    // 0x800CFFD0: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800CFFD4: lw          $t7, 0xC($t6)
    ctx->r15 = MEM_W(ctx->r14, 0XC);
    // 0x800CFFD8: addiu       $t1, $t7, 0x1
    ctx->r9 = ADD32(ctx->r15, 0X1);
    // 0x800CFFDC: sw          $t1, 0xC($t6)
    MEM_W(0XC, ctx->r14) = ctx->r9;
    // 0x800CFFE0: lbu         $t8, 0x43($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X43);
    // 0x800CFFE4: beq         $t8, $at, L_800CFFF4
    if (ctx->r24 == ctx->r1) {
        // 0x800CFFE8: addiu       $at, $zero, 0x58
        ctx->r1 = ADD32(0, 0X58);
            goto L_800CFFF4;
    }
    // 0x800CFFE8: addiu       $at, $zero, 0x58
    ctx->r1 = ADD32(0, 0X58);
    // 0x800CFFEC: bne         $t8, $at, L_800D001C
    if (ctx->r24 != ctx->r1) {
        // 0x800CFFF0: nop
    
            goto L_800D001C;
    }
    // 0x800CFFF0: nop

L_800CFFF4:
    // 0x800CFFF4: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800CFFF8: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800CFFFC: lbu         $t9, 0x43($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X43);
    // 0x800D0000: lw          $t3, 0xC($t2)
    ctx->r11 = MEM_W(ctx->r10, 0XC);
    // 0x800D0004: addu        $t4, $t0, $t3
    ctx->r12 = ADD32(ctx->r8, ctx->r11);
    // 0x800D0008: sb          $t9, 0x0($t4)
    MEM_B(0X0, ctx->r12) = ctx->r25;
    // 0x800D000C: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800D0010: lw          $t7, 0xC($t5)
    ctx->r15 = MEM_W(ctx->r13, 0XC);
    // 0x800D0014: addiu       $t1, $t7, 0x1
    ctx->r9 = ADD32(ctx->r15, 0X1);
    // 0x800D0018: sw          $t1, 0xC($t5)
    MEM_W(0XC, ctx->r13) = ctx->r9;
L_800D001C:
    // 0x800D001C: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D0020: lw          $t2, 0x44($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X44);
    // 0x800D0024: lw          $t8, 0xC($t6)
    ctx->r24 = MEM_W(ctx->r14, 0XC);
    // 0x800D0028: addu        $t0, $t8, $t2
    ctx->r8 = ADD32(ctx->r24, ctx->r10);
    // 0x800D002C: sw          $t0, 0x8($t6)
    MEM_W(0X8, ctx->r14) = ctx->r8;
    // 0x800D0030: lbu         $a1, 0x43($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X43);
    // 0x800D0034: jal         0x800D0FE0
    // 0x800D0038: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    _Litob(rdram, ctx);
        goto after_1;
    // 0x800D0038: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    after_1:
    // 0x800D003C: b           L_800D0498
    // 0x800D0040: nop

        goto L_800D0498;
    // 0x800D0040: nop

L_800D0044:
    // 0x800D0044: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800D0048: addiu       $at, $zero, 0x4C
    ctx->r1 = ADD32(0, 0X4C);
    // 0x800D004C: lbu         $t9, 0x34($t3)
    ctx->r25 = MEM_BU(ctx->r11, 0X34);
    // 0x800D0050: bne         $t9, $at, L_800D00E8
    if (ctx->r25 != ctx->r1) {
        // 0x800D0054: nop
    
            goto L_800D00E8;
    }
    // 0x800D0054: nop

    // 0x800D0058: lw          $t4, 0x3C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X3C);
    // 0x800D005C: lw          $t7, 0x0($t4)
    ctx->r15 = MEM_W(ctx->r12, 0X0);
    // 0x800D0060: andi        $t1, $t7, 0x1
    ctx->r9 = ctx->r15 & 0X1;
    // 0x800D0064: beq         $t1, $zero, L_800D0084
    if (ctx->r9 == 0) {
        // 0x800D0068: nop
    
            goto L_800D0084;
    }
    // 0x800D0068: nop

    // 0x800D006C: addiu       $t5, $t7, 0x7
    ctx->r13 = ADD32(ctx->r15, 0X7);
    // 0x800D0070: sw          $t5, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r13;
    // 0x800D0074: lw          $t8, 0x3C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0078: lw          $s0, 0x0($t8)
    ctx->r16 = MEM_W(ctx->r24, 0X0);
    // 0x800D007C: b           L_800D00D8
    // 0x800D0080: addiu       $s0, $s0, -0x16
    ctx->r16 = ADD32(ctx->r16, -0X16);
        goto L_800D00D8;
    // 0x800D0080: addiu       $s0, $s0, -0x16
    ctx->r16 = ADD32(ctx->r16, -0X16);
L_800D0084:
    // 0x800D0084: lw          $t2, 0x3C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0088: lw          $t0, 0x0($t2)
    ctx->r8 = MEM_W(ctx->r10, 0X0);
    // 0x800D008C: andi        $t6, $t0, 0x2
    ctx->r14 = ctx->r8 & 0X2;
    // 0x800D0090: beq         $t6, $zero, L_800D00B0
    if (ctx->r14 == 0) {
        // 0x800D0094: nop
    
            goto L_800D00B0;
    }
    // 0x800D0094: nop

    // 0x800D0098: addiu       $t3, $t0, 0xA
    ctx->r11 = ADD32(ctx->r8, 0XA);
    // 0x800D009C: sw          $t3, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r11;
    // 0x800D00A0: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x800D00A4: lw          $s1, 0x0($t9)
    ctx->r17 = MEM_W(ctx->r25, 0X0);
    // 0x800D00A8: b           L_800D00D4
    // 0x800D00AC: addiu       $s1, $s1, -0x28
    ctx->r17 = ADD32(ctx->r17, -0X28);
        goto L_800D00D4;
    // 0x800D00AC: addiu       $s1, $s1, -0x28
    ctx->r17 = ADD32(ctx->r17, -0X28);
L_800D00B0:
    // 0x800D00B0: lw          $t1, 0x3C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X3C);
    // 0x800D00B4: addiu       $at, $zero, -0x8
    ctx->r1 = ADD32(0, -0X8);
    // 0x800D00B8: lw          $t7, 0x0($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X0);
    // 0x800D00BC: addiu       $t5, $t7, 0x7
    ctx->r13 = ADD32(ctx->r15, 0X7);
    // 0x800D00C0: and         $t4, $t5, $at
    ctx->r12 = ctx->r13 & ctx->r1;
    // 0x800D00C4: addiu       $t8, $t4, 0x8
    ctx->r24 = ADD32(ctx->r12, 0X8);
    // 0x800D00C8: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x800D00CC: lw          $t6, 0x3C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X3C);
    // 0x800D00D0: lw          $s1, 0x0($t6)
    ctx->r17 = MEM_W(ctx->r14, 0X0);
L_800D00D4:
    // 0x800D00D4: or          $s0, $s1, $zero
    ctx->r16 = ctx->r17 | 0;
L_800D00D8:
    // 0x800D00D8: ldc1        $f4, -0x8($s0)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r16, -0X8);
    // 0x800D00DC: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800D00E0: b           L_800D0174
    // 0x800D00E4: sdc1        $f4, 0x0($t0)
    CHECK_FR(ctx, 4);
    SD(ctx->f4.u64, 0X0, ctx->r8);
        goto L_800D0174;
    // 0x800D00E4: sdc1        $f4, 0x0($t0)
    CHECK_FR(ctx, 4);
    SD(ctx->f4.u64, 0X0, ctx->r8);
L_800D00E8:
    // 0x800D00E8: lw          $t3, 0x3C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X3C);
    // 0x800D00EC: lw          $t2, 0x0($t3)
    ctx->r10 = MEM_W(ctx->r11, 0X0);
    // 0x800D00F0: andi        $t9, $t2, 0x1
    ctx->r25 = ctx->r10 & 0X1;
    // 0x800D00F4: beq         $t9, $zero, L_800D0114
    if (ctx->r25 == 0) {
        // 0x800D00F8: nop
    
            goto L_800D0114;
    }
    // 0x800D00F8: nop

    // 0x800D00FC: addiu       $t7, $t2, 0x7
    ctx->r15 = ADD32(ctx->r10, 0X7);
    // 0x800D0100: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
    // 0x800D0104: lw          $t5, 0x3C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0108: lw          $s2, 0x0($t5)
    ctx->r18 = MEM_W(ctx->r13, 0X0);
    // 0x800D010C: b           L_800D0168
    // 0x800D0110: addiu       $s2, $s2, -0x16
    ctx->r18 = ADD32(ctx->r18, -0X16);
        goto L_800D0168;
    // 0x800D0110: addiu       $s2, $s2, -0x16
    ctx->r18 = ADD32(ctx->r18, -0X16);
L_800D0114:
    // 0x800D0114: lw          $t4, 0x3C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0118: lw          $t8, 0x0($t4)
    ctx->r24 = MEM_W(ctx->r12, 0X0);
    // 0x800D011C: andi        $t1, $t8, 0x2
    ctx->r9 = ctx->r24 & 0X2;
    // 0x800D0120: beq         $t1, $zero, L_800D0140
    if (ctx->r9 == 0) {
        // 0x800D0124: nop
    
            goto L_800D0140;
    }
    // 0x800D0124: nop

    // 0x800D0128: addiu       $t6, $t8, 0xA
    ctx->r14 = ADD32(ctx->r24, 0XA);
    // 0x800D012C: sw          $t6, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r14;
    // 0x800D0130: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0134: lw          $s3, 0x0($t0)
    ctx->r19 = MEM_W(ctx->r8, 0X0);
    // 0x800D0138: b           L_800D0164
    // 0x800D013C: addiu       $s3, $s3, -0x28
    ctx->r19 = ADD32(ctx->r19, -0X28);
        goto L_800D0164;
    // 0x800D013C: addiu       $s3, $s3, -0x28
    ctx->r19 = ADD32(ctx->r19, -0X28);
L_800D0140:
    // 0x800D0140: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0144: addiu       $at, $zero, -0x8
    ctx->r1 = ADD32(0, -0X8);
    // 0x800D0148: lw          $t2, 0x0($t9)
    ctx->r10 = MEM_W(ctx->r25, 0X0);
    // 0x800D014C: addiu       $t7, $t2, 0x7
    ctx->r15 = ADD32(ctx->r10, 0X7);
    // 0x800D0150: and         $t3, $t7, $at
    ctx->r11 = ctx->r15 & ctx->r1;
    // 0x800D0154: addiu       $t5, $t3, 0x8
    ctx->r13 = ADD32(ctx->r11, 0X8);
    // 0x800D0158: sw          $t5, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r13;
    // 0x800D015C: lw          $t1, 0x3C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0160: lw          $s3, 0x0($t1)
    ctx->r19 = MEM_W(ctx->r9, 0X0);
L_800D0164:
    // 0x800D0164: or          $s2, $s3, $zero
    ctx->r18 = ctx->r19 | 0;
L_800D0168:
    // 0x800D0168: ldc1        $f6, -0x8($s2)
    CHECK_FR(ctx, 6);
    ctx->f6.u64 = LD(ctx->r18, -0X8);
    // 0x800D016C: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800D0170: sdc1        $f6, 0x0($t8)
    CHECK_FR(ctx, 6);
    SD(ctx->f6.u64, 0X0, ctx->r24);
L_800D0174:
    // 0x800D0174: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D0178: lhu         $t4, 0x0($t6)
    ctx->r12 = MEM_HU(ctx->r14, 0X0);
    // 0x800D017C: andi        $t0, $t4, 0x8000
    ctx->r8 = ctx->r12 & 0X8000;
    // 0x800D0180: beq         $t0, $zero, L_800D01B0
    if (ctx->r8 == 0) {
        // 0x800D0184: nop
    
            goto L_800D01B0;
    }
    // 0x800D0184: nop

    // 0x800D0188: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x800D018C: lw          $t3, 0xC($t6)
    ctx->r11 = MEM_W(ctx->r14, 0XC);
    // 0x800D0190: addiu       $t2, $zero, 0x2D
    ctx->r10 = ADD32(0, 0X2D);
    // 0x800D0194: addu        $t5, $t7, $t3
    ctx->r13 = ADD32(ctx->r15, ctx->r11);
    // 0x800D0198: sb          $t2, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r10;
    // 0x800D019C: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800D01A0: lw          $t1, 0xC($t9)
    ctx->r9 = MEM_W(ctx->r25, 0XC);
    // 0x800D01A4: addiu       $t8, $t1, 0x1
    ctx->r24 = ADD32(ctx->r9, 0X1);
    // 0x800D01A8: b           L_800D0224
    // 0x800D01AC: sw          $t8, 0xC($t9)
    MEM_W(0XC, ctx->r25) = ctx->r24;
        goto L_800D0224;
    // 0x800D01AC: sw          $t8, 0xC($t9)
    MEM_W(0XC, ctx->r25) = ctx->r24;
L_800D01B0:
    // 0x800D01B0: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800D01B4: lw          $t0, 0x30($t4)
    ctx->r8 = MEM_W(ctx->r12, 0X30);
    // 0x800D01B8: andi        $t6, $t0, 0x2
    ctx->r14 = ctx->r8 & 0X2;
    // 0x800D01BC: beq         $t6, $zero, L_800D01EC
    if (ctx->r14 == 0) {
        // 0x800D01C0: nop
    
            goto L_800D01EC;
    }
    // 0x800D01C0: nop

    // 0x800D01C4: lw          $t3, 0x44($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X44);
    // 0x800D01C8: lw          $t2, 0xC($t4)
    ctx->r10 = MEM_W(ctx->r12, 0XC);
    // 0x800D01CC: addiu       $t7, $zero, 0x2B
    ctx->r15 = ADD32(0, 0X2B);
    // 0x800D01D0: addu        $t5, $t3, $t2
    ctx->r13 = ADD32(ctx->r11, ctx->r10);
    // 0x800D01D4: sb          $t7, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r15;
    // 0x800D01D8: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800D01DC: lw          $t8, 0xC($t1)
    ctx->r24 = MEM_W(ctx->r9, 0XC);
    // 0x800D01E0: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x800D01E4: b           L_800D0224
    // 0x800D01E8: sw          $t9, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->r25;
        goto L_800D0224;
    // 0x800D01E8: sw          $t9, 0xC($t1)
    MEM_W(0XC, ctx->r9) = ctx->r25;
L_800D01EC:
    // 0x800D01EC: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800D01F0: lw          $t6, 0x30($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X30);
    // 0x800D01F4: andi        $t4, $t6, 0x1
    ctx->r12 = ctx->r14 & 0X1;
    // 0x800D01F8: beq         $t4, $zero, L_800D0224
    if (ctx->r12 == 0) {
        // 0x800D01FC: nop
    
            goto L_800D0224;
    }
    // 0x800D01FC: nop

    // 0x800D0200: lw          $t2, 0x44($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X44);
    // 0x800D0204: lw          $t7, 0xC($t0)
    ctx->r15 = MEM_W(ctx->r8, 0XC);
    // 0x800D0208: addiu       $t3, $zero, 0x20
    ctx->r11 = ADD32(0, 0X20);
    // 0x800D020C: addu        $t5, $t2, $t7
    ctx->r13 = ADD32(ctx->r10, ctx->r15);
    // 0x800D0210: sb          $t3, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r11;
    // 0x800D0214: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800D0218: lw          $t9, 0xC($t8)
    ctx->r25 = MEM_W(ctx->r24, 0XC);
    // 0x800D021C: addiu       $t1, $t9, 0x1
    ctx->r9 = ADD32(ctx->r25, 0X1);
    // 0x800D0220: sw          $t1, 0xC($t8)
    MEM_W(0XC, ctx->r24) = ctx->r9;
L_800D0224:
    // 0x800D0224: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D0228: lw          $t0, 0x44($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X44);
    // 0x800D022C: lw          $t4, 0xC($t6)
    ctx->r12 = MEM_W(ctx->r14, 0XC);
    // 0x800D0230: addu        $t2, $t4, $t0
    ctx->r10 = ADD32(ctx->r12, ctx->r8);
    // 0x800D0234: sw          $t2, 0x8($t6)
    MEM_W(0X8, ctx->r14) = ctx->r10;
    // 0x800D0238: lbu         $a1, 0x43($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X43);
    // 0x800D023C: jal         0x800D12E0
    // 0x800D0240: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    _Ldtob(rdram, ctx);
        goto after_2;
    // 0x800D0240: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    after_2:
    // 0x800D0244: b           L_800D0498
    // 0x800D0248: nop

        goto L_800D0498;
    // 0x800D0248: nop

L_800D024C:
    // 0x800D024C: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800D0250: addiu       $at, $zero, 0x68
    ctx->r1 = ADD32(0, 0X68);
    // 0x800D0254: lbu         $t3, 0x34($t7)
    ctx->r11 = MEM_BU(ctx->r15, 0X34);
    // 0x800D0258: bne         $t3, $at, L_800D0298
    if (ctx->r11 != ctx->r1) {
        // 0x800D025C: nop
    
            goto L_800D0298;
    }
    // 0x800D025C: nop

    // 0x800D0260: lw          $t5, 0x3C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0264: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D0268: lw          $t9, 0x0($t5)
    ctx->r25 = MEM_W(ctx->r13, 0X0);
    // 0x800D026C: addiu       $t1, $t9, 0x3
    ctx->r9 = ADD32(ctx->r25, 0X3);
    // 0x800D0270: and         $t8, $t1, $at
    ctx->r24 = ctx->r9 & ctx->r1;
    // 0x800D0274: addiu       $t4, $t8, 0x4
    ctx->r12 = ADD32(ctx->r24, 0X4);
    // 0x800D0278: sw          $t4, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r12;
    // 0x800D027C: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0280: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800D0284: lw          $s0, 0x0($t0)
    ctx->r16 = MEM_W(ctx->r8, 0X0);
    // 0x800D0288: lw          $t6, 0x2C($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X2C);
    // 0x800D028C: lw          $t7, -0x4($s0)
    ctx->r15 = MEM_W(ctx->r16, -0X4);
    // 0x800D0290: b           L_800D0498
    // 0x800D0294: sh          $t6, 0x0($t7)
    MEM_H(0X0, ctx->r15) = ctx->r14;
        goto L_800D0498;
    // 0x800D0294: sh          $t6, 0x0($t7)
    MEM_H(0X0, ctx->r15) = ctx->r14;
L_800D0298:
    // 0x800D0298: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800D029C: addiu       $at, $zero, 0x6C
    ctx->r1 = ADD32(0, 0X6C);
    // 0x800D02A0: lbu         $t9, 0x34($t3)
    ctx->r25 = MEM_BU(ctx->r11, 0X34);
    // 0x800D02A4: bne         $t9, $at, L_800D02E4
    if (ctx->r25 != ctx->r1) {
        // 0x800D02A8: nop
    
            goto L_800D02E4;
    }
    // 0x800D02A8: nop

    // 0x800D02AC: lw          $t1, 0x3C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X3C);
    // 0x800D02B0: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D02B4: lw          $t8, 0x0($t1)
    ctx->r24 = MEM_W(ctx->r9, 0X0);
    // 0x800D02B8: addiu       $t4, $t8, 0x3
    ctx->r12 = ADD32(ctx->r24, 0X3);
    // 0x800D02BC: and         $t5, $t4, $at
    ctx->r13 = ctx->r12 & ctx->r1;
    // 0x800D02C0: addiu       $t0, $t5, 0x4
    ctx->r8 = ADD32(ctx->r13, 0X4);
    // 0x800D02C4: sw          $t0, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r8;
    // 0x800D02C8: lw          $t2, 0x3C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X3C);
    // 0x800D02CC: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D02D0: lw          $s0, 0x0($t2)
    ctx->r16 = MEM_W(ctx->r10, 0X0);
    // 0x800D02D4: lw          $t7, 0x2C($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X2C);
    // 0x800D02D8: lw          $t3, -0x4($s0)
    ctx->r11 = MEM_W(ctx->r16, -0X4);
    // 0x800D02DC: b           L_800D0498
    // 0x800D02E0: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
        goto L_800D0498;
    // 0x800D02E0: sw          $t7, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r15;
L_800D02E4:
    // 0x800D02E4: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800D02E8: addiu       $at, $zero, 0x4C
    ctx->r1 = ADD32(0, 0X4C);
    // 0x800D02EC: lbu         $t8, 0x34($t9)
    ctx->r24 = MEM_BU(ctx->r25, 0X34);
    // 0x800D02F0: bne         $t8, $at, L_800D033C
    if (ctx->r24 != ctx->r1) {
        // 0x800D02F4: nop
    
            goto L_800D033C;
    }
    // 0x800D02F4: nop

    // 0x800D02F8: lw          $t4, 0x3C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X3C);
    // 0x800D02FC: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D0300: addiu       $t8, $zero, 0x0
    ctx->r24 = ADD32(0, 0X0);
    // 0x800D0304: lw          $t5, 0x0($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X0);
    // 0x800D0308: addiu       $t0, $t5, 0x3
    ctx->r8 = ADD32(ctx->r13, 0X3);
    // 0x800D030C: and         $t1, $t0, $at
    ctx->r9 = ctx->r8 & ctx->r1;
    // 0x800D0310: addiu       $t2, $t1, 0x4
    ctx->r10 = ADD32(ctx->r9, 0X4);
    // 0x800D0314: sw          $t2, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r10;
    // 0x800D0318: lw          $t6, 0x3C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X3C);
    // 0x800D031C: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800D0320: lw          $s0, 0x0($t6)
    ctx->r16 = MEM_W(ctx->r14, 0X0);
    // 0x800D0324: lw          $t3, 0x2C($t7)
    ctx->r11 = MEM_W(ctx->r15, 0X2C);
    // 0x800D0328: lw          $t5, -0x4($s0)
    ctx->r13 = MEM_W(ctx->r16, -0X4);
    // 0x800D032C: or          $t9, $t3, $zero
    ctx->r25 = ctx->r11 | 0;
    // 0x800D0330: sw          $t9, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r25;
    // 0x800D0334: b           L_800D0498
    // 0x800D0338: sw          $t8, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r24;
        goto L_800D0498;
    // 0x800D0338: sw          $t8, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r24;
L_800D033C:
    // 0x800D033C: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0340: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D0344: lw          $t1, 0x0($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X0);
    // 0x800D0348: addiu       $t2, $t1, 0x3
    ctx->r10 = ADD32(ctx->r9, 0X3);
    // 0x800D034C: and         $t4, $t2, $at
    ctx->r12 = ctx->r10 & ctx->r1;
    // 0x800D0350: addiu       $t6, $t4, 0x4
    ctx->r14 = ADD32(ctx->r12, 0X4);
    // 0x800D0354: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x800D0358: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x800D035C: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800D0360: lw          $s0, 0x0($t7)
    ctx->r16 = MEM_W(ctx->r15, 0X0);
    // 0x800D0364: lw          $t8, 0x2C($t3)
    ctx->r24 = MEM_W(ctx->r11, 0X2C);
    // 0x800D0368: lw          $t9, -0x4($s0)
    ctx->r25 = MEM_W(ctx->r16, -0X4);
    // 0x800D036C: b           L_800D0498
    // 0x800D0370: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
        goto L_800D0498;
    // 0x800D0370: sw          $t8, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r24;
L_800D0374:
    // 0x800D0374: lw          $t5, 0x3C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0378: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D037C: addiu       $a1, $zero, 0x78
    ctx->r5 = ADD32(0, 0X78);
    // 0x800D0380: lw          $t1, 0x0($t5)
    ctx->r9 = MEM_W(ctx->r13, 0X0);
    // 0x800D0384: addiu       $t2, $t1, 0x3
    ctx->r10 = ADD32(ctx->r9, 0X3);
    // 0x800D0388: and         $t4, $t2, $at
    ctx->r12 = ctx->r10 & ctx->r1;
    // 0x800D038C: addiu       $t6, $t4, 0x4
    ctx->r14 = ADD32(ctx->r12, 0X4);
    // 0x800D0390: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x800D0394: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800D0398: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800D039C: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x800D03A0: lw          $t3, -0x4($t7)
    ctx->r11 = MEM_W(ctx->r15, -0X4);
    // 0x800D03A4: or          $t9, $t3, $zero
    ctx->r25 = ctx->r11 | 0;
    // 0x800D03A8: sra         $t8, $t3, 31
    ctx->r24 = S32(SIGNED(ctx->r11) >> 31);
    // 0x800D03AC: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x800D03B0: sw          $t9, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r25;
    // 0x800D03B4: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800D03B8: lw          $t6, 0x44($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X44);
    // 0x800D03BC: lw          $t4, 0xC($t2)
    ctx->r12 = MEM_W(ctx->r10, 0XC);
    // 0x800D03C0: addu        $t5, $t4, $t6
    ctx->r13 = ADD32(ctx->r12, ctx->r14);
    // 0x800D03C4: sw          $t5, 0x8($t2)
    MEM_W(0X8, ctx->r10) = ctx->r13;
    // 0x800D03C8: jal         0x800D0FE0
    // 0x800D03CC: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    _Litob(rdram, ctx);
        goto after_3;
    // 0x800D03CC: lw          $a0, 0x38($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X38);
    after_3:
    // 0x800D03D0: b           L_800D0498
    // 0x800D03D4: nop

        goto L_800D0498;
    // 0x800D03D4: nop

L_800D03D8:
    // 0x800D03D8: lw          $t0, 0x3C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X3C);
    // 0x800D03DC: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D03E0: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x800D03E4: addiu       $t3, $t7, 0x3
    ctx->r11 = ADD32(ctx->r15, 0X3);
    // 0x800D03E8: and         $t8, $t3, $at
    ctx->r24 = ctx->r11 & ctx->r1;
    // 0x800D03EC: addiu       $t9, $t8, 0x4
    ctx->r25 = ADD32(ctx->r24, 0X4);
    // 0x800D03F0: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x800D03F4: lw          $t1, 0x3C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X3C);
    // 0x800D03F8: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800D03FC: lw          $t4, 0x0($t1)
    ctx->r12 = MEM_W(ctx->r9, 0X0);
    // 0x800D0400: lw          $t6, -0x4($t4)
    ctx->r14 = MEM_W(ctx->r12, -0X4);
    // 0x800D0404: sw          $t6, 0x8($t5)
    MEM_W(0X8, ctx->r13) = ctx->r14;
    // 0x800D0408: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800D040C: jal         0x800D04EC
    // 0x800D0410: lw          $a0, 0x8($t2)
    ctx->r4 = MEM_W(ctx->r10, 0X8);
    func_800D04EC(rdram, ctx);
        goto after_4;
    // 0x800D0410: lw          $a0, 0x8($t2)
    ctx->r4 = MEM_W(ctx->r10, 0X8);
    after_4:
    // 0x800D0414: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800D0418: sw          $v0, 0x14($t7)
    MEM_W(0X14, ctx->r15) = ctx->r2;
    // 0x800D041C: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800D0420: lw          $t8, 0x24($t3)
    ctx->r24 = MEM_W(ctx->r11, 0X24);
    // 0x800D0424: bltz        $t8, L_800D0498
    if (SIGNED(ctx->r24) < 0) {
        // 0x800D0428: nop
    
            goto L_800D0498;
    }
    // 0x800D0428: nop

    // 0x800D042C: lw          $t9, 0x14($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X14);
    // 0x800D0430: slt         $at, $t8, $t9
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800D0434: beq         $at, $zero, L_800D0498
    if (ctx->r1 == 0) {
        // 0x800D0438: nop
    
            goto L_800D0498;
    }
    // 0x800D0438: nop

    // 0x800D043C: b           L_800D0498
    // 0x800D0440: sw          $t8, 0x14($t3)
    MEM_W(0X14, ctx->r11) = ctx->r24;
        goto L_800D0498;
    // 0x800D0440: sw          $t8, 0x14($t3)
    MEM_W(0X14, ctx->r11) = ctx->r24;
L_800D0444:
    // 0x800D0444: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800D0448: lw          $t1, 0x44($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X44);
    // 0x800D044C: addiu       $t0, $zero, 0x25
    ctx->r8 = ADD32(0, 0X25);
    // 0x800D0450: lw          $t6, 0xC($t4)
    ctx->r14 = MEM_W(ctx->r12, 0XC);
    // 0x800D0454: addu        $t5, $t1, $t6
    ctx->r13 = ADD32(ctx->r9, ctx->r14);
    // 0x800D0458: sb          $t0, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r8;
    // 0x800D045C: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800D0460: lw          $t7, 0xC($t2)
    ctx->r15 = MEM_W(ctx->r10, 0XC);
    // 0x800D0464: addiu       $t9, $t7, 0x1
    ctx->r25 = ADD32(ctx->r15, 0X1);
    // 0x800D0468: b           L_800D0498
    // 0x800D046C: sw          $t9, 0xC($t2)
    MEM_W(0XC, ctx->r10) = ctx->r25;
        goto L_800D0498;
    // 0x800D046C: sw          $t9, 0xC($t2)
    MEM_W(0XC, ctx->r10) = ctx->r25;
L_800D0470:
    // 0x800D0470: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800D0474: lw          $t3, 0x44($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X44);
    // 0x800D0478: lbu         $t8, 0x43($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X43);
    // 0x800D047C: lw          $t1, 0xC($t4)
    ctx->r9 = MEM_W(ctx->r12, 0XC);
    // 0x800D0480: addu        $t6, $t3, $t1
    ctx->r14 = ADD32(ctx->r11, ctx->r9);
    // 0x800D0484: sb          $t8, 0x0($t6)
    MEM_B(0X0, ctx->r14) = ctx->r24;
    // 0x800D0488: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800D048C: lw          $t5, 0xC($t0)
    ctx->r13 = MEM_W(ctx->r8, 0XC);
    // 0x800D0490: addiu       $t7, $t5, 0x1
    ctx->r15 = ADD32(ctx->r13, 0X1);
    // 0x800D0494: sw          $t7, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r15;
L_800D0498:
    // 0x800D0498: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800D049C: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x800D04A0: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x800D04A4: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x800D04A8: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x800D04AC: jr          $ra
    // 0x800D04B0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x800D04B0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800D04B4: nop

    // 0x800D04B8: nop

    // 0x800D04BC: nop

;}
RECOMP_FUNC void memcpy_recomp(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D04C0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800D04C4: beq         $a2, $zero, L_800D04E4
    if (ctx->r6 == 0) {
        // 0x800D04C8: or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
            goto L_800D04E4;
    }
    // 0x800D04C8: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
L_800D04CC:
    // 0x800D04CC: lbu         $t6, 0x0($v1)
    ctx->r14 = MEM_BU(ctx->r3, 0X0);
    // 0x800D04D0: addiu       $a2, $a2, -0x1
    ctx->r6 = ADD32(ctx->r6, -0X1);
    // 0x800D04D4: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x800D04D8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800D04DC: bne         $a2, $zero, L_800D04CC
    if (ctx->r6 != 0) {
        // 0x800D04E0: sb          $t6, -0x1($v0)
        MEM_B(-0X1, ctx->r2) = ctx->r14;
            goto L_800D04CC;
    }
    // 0x800D04E0: sb          $t6, -0x1($v0)
    MEM_B(-0X1, ctx->r2) = ctx->r14;
L_800D04E4:
    // 0x800D04E4: jr          $ra
    // 0x800D04E8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x800D04E8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_800D04EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D04EC: lbu         $t6, 0x0($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X0);
    // 0x800D04F0: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800D04F4: beq         $t6, $zero, L_800D050C
    if (ctx->r14 == 0) {
        // 0x800D04F8: nop
    
            goto L_800D050C;
    }
    // 0x800D04F8: nop

    // 0x800D04FC: lbu         $t7, 0x1($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X1);
L_800D0500:
    // 0x800D0500: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800D0504: bnel        $t7, $zero, L_800D0500
    if (ctx->r15 != 0) {
        // 0x800D0508: lbu         $t7, 0x1($v1)
        ctx->r15 = MEM_BU(ctx->r3, 0X1);
            goto L_800D0500;
    }
    goto skip_0;
    // 0x800D0508: lbu         $t7, 0x1($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X1);
    skip_0:
L_800D050C:
    // 0x800D050C: jr          $ra
    // 0x800D0510: subu        $v0, $v1, $a0
    ctx->r2 = SUB32(ctx->r3, ctx->r4);
    return;
    // 0x800D0510: subu        $v0, $v1, $a0
    ctx->r2 = SUB32(ctx->r3, ctx->r4);
;}
RECOMP_FUNC void func_800D0514(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0514: lbu         $v1, 0x0($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0X0);
    // 0x800D0518: andi        $t6, $a1, 0xFF
    ctx->r14 = ctx->r5 & 0XFF;
    // 0x800D051C: andi        $v0, $a1, 0xFF
    ctx->r2 = ctx->r5 & 0XFF;
    // 0x800D0520: beql        $t6, $v1, L_800D054C
    if (ctx->r14 == ctx->r3) {
        // 0x800D0524: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_800D054C;
    }
    goto skip_0;
    // 0x800D0524: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_0:
L_800D0528:
    // 0x800D0528: bnel        $v1, $zero, L_800D053C
    if (ctx->r3 != 0) {
        // 0x800D052C: lbu         $v1, 0x1($a0)
        ctx->r3 = MEM_BU(ctx->r4, 0X1);
            goto L_800D053C;
    }
    goto skip_1;
    // 0x800D052C: lbu         $v1, 0x1($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0X1);
    skip_1:
    // 0x800D0530: jr          $ra
    // 0x800D0534: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800D0534: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800D0538: lbu         $v1, 0x1($a0)
    ctx->r3 = MEM_BU(ctx->r4, 0X1);
L_800D053C:
    // 0x800D053C: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800D0540: bne         $v0, $v1, L_800D0528
    if (ctx->r2 != ctx->r3) {
        // 0x800D0544: nop
    
            goto L_800D0528;
    }
    // 0x800D0544: nop

    // 0x800D0548: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_800D054C:
    // 0x800D054C: jr          $ra
    // 0x800D0550: nop

    return;
    // 0x800D0550: nop

    // 0x800D0554: nop

    // 0x800D0558: nop

    // 0x800D055C: nop

;}
RECOMP_FUNC void MusPtrBankGetCurrent(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D06C8: lui         $v0, 0x800F
    ctx->r2 = S32(0X800F << 16);
    // 0x800D06CC: lw          $v0, -0x7048($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7048);
    // 0x800D06D0: jr          $ra
    // 0x800D06D4: nop

    return;
    // 0x800D06D4: nop

    // 0x800D06D8: nop

    // 0x800D06DC: nop

;}
RECOMP_FUNC void func_800D0740(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0740: lbu         $t6, 0x0($a0)
    ctx->r14 = MEM_BU(ctx->r4, 0X0);
    // 0x800D0744: addiu       $sp, $sp, -0x8
    ctx->r29 = ADD32(ctx->r29, -0X8);
    // 0x800D0748: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x800D074C: sll         $t8, $t7, 24
    ctx->r24 = S32(ctx->r15 << 24);
    // 0x800D0750: sw          $t8, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r24;
    // 0x800D0754: lbu         $t9, 0x1($a0)
    ctx->r25 = MEM_BU(ctx->r4, 0X1);
    // 0x800D0758: andi        $t0, $t9, 0xFF
    ctx->r8 = ctx->r25 & 0XFF;
    // 0x800D075C: sll         $t1, $t0, 16
    ctx->r9 = S32(ctx->r8 << 16);
    // 0x800D0760: or          $t2, $t8, $t1
    ctx->r10 = ctx->r24 | ctx->r9;
    // 0x800D0764: sw          $t2, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r10;
    // 0x800D0768: lbu         $t3, 0x2($a0)
    ctx->r11 = MEM_BU(ctx->r4, 0X2);
    // 0x800D076C: andi        $t4, $t3, 0xFF
    ctx->r12 = ctx->r11 & 0XFF;
    // 0x800D0770: sll         $t5, $t4, 8
    ctx->r13 = S32(ctx->r12 << 8);
    // 0x800D0774: or          $t6, $t2, $t5
    ctx->r14 = ctx->r10 | ctx->r13;
    // 0x800D0778: sw          $t6, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r14;
    // 0x800D077C: lbu         $t7, 0x3($a0)
    ctx->r15 = MEM_BU(ctx->r4, 0X3);
    // 0x800D0780: andi        $t9, $t7, 0xFF
    ctx->r25 = ctx->r15 & 0XFF;
    // 0x800D0784: or          $t0, $t6, $t9
    ctx->r8 = ctx->r14 | ctx->r25;
    // 0x800D0788: sw          $t0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r8;
    // 0x800D078C: addiu       $sp, $sp, 0x8
    ctx->r29 = ADD32(ctx->r29, 0X8);
    // 0x800D0790: jr          $ra
    // 0x800D0794: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
    return;
    // 0x800D0794: or          $v0, $t0, $zero
    ctx->r2 = ctx->r8 | 0;
;}
RECOMP_FUNC void func_800D0798(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0798: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800D079C: lbu         $t6, 0x1C($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X1C);
    // 0x800D07A0: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800D07A4: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    // 0x800D07A8: andi        $t7, $t6, 0xFF3F
    ctx->r15 = ctx->r14 & 0XFF3F;
    // 0x800D07AC: ori         $t8, $t7, 0x80
    ctx->r24 = ctx->r15 | 0X80;
    // 0x800D07B0: andi        $t2, $t8, 0xFF
    ctx->r10 = ctx->r24 & 0XFF;
    // 0x800D07B4: andi        $t0, $t9, 0x3
    ctx->r8 = ctx->r25 & 0X3;
    // 0x800D07B8: andi        $t1, $t0, 0x3
    ctx->r9 = ctx->r8 & 0X3;
    // 0x800D07BC: andi        $t3, $t2, 0xFFFC
    ctx->r11 = ctx->r10 & 0XFFFC;
    // 0x800D07C0: sb          $t8, 0x1C($sp)
    MEM_B(0X1C, ctx->r29) = ctx->r24;
    // 0x800D07C4: or          $t4, $t1, $t3
    ctx->r12 = ctx->r9 | ctx->r11;
    // 0x800D07C8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D07CC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x800D07D0: sb          $t4, 0x1C($sp)
    MEM_B(0X1C, ctx->r29) = ctx->r12;
    // 0x800D07D4: blez        $t9, L_800D080C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800D07D8: sw          $zero, 0x18($sp)
        MEM_W(0X18, ctx->r29) = 0;
            goto L_800D080C;
    }
    // 0x800D07D8: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
L_800D07DC:
    // 0x800D07DC: lw          $t5, 0x20($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X20);
    // 0x800D07E0: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x800D07E4: addu        $t7, $t5, $t6
    ctx->r15 = ADD32(ctx->r13, ctx->r14);
    // 0x800D07E8: lbu         $t0, 0x0($t7)
    ctx->r8 = MEM_BU(ctx->r15, 0X0);
    // 0x800D07EC: addu        $t8, $sp, $t6
    ctx->r24 = ADD32(ctx->r29, ctx->r14);
    // 0x800D07F0: sb          $t0, 0x1D($t8)
    MEM_B(0X1D, ctx->r24) = ctx->r8;
    // 0x800D07F4: lw          $t2, 0x18($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X18);
    // 0x800D07F8: lw          $t3, 0x24($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X24);
    // 0x800D07FC: addiu       $t1, $t2, 0x1
    ctx->r9 = ADD32(ctx->r10, 0X1);
    // 0x800D0800: slt         $at, $t1, $t3
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x800D0804: bne         $at, $zero, L_800D07DC
    if (ctx->r1 != 0) {
        // 0x800D0808: sw          $t1, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r9;
            goto L_800D07DC;
    }
    // 0x800D0808: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
L_800D080C:
    // 0x800D080C: addiu       $t4, $sp, 0x1C
    ctx->r12 = ADD32(ctx->r29, 0X1C);
    // 0x800D0810: lw          $t9, 0x0($t4)
    ctx->r25 = MEM_W(ctx->r12, 0X0);
    // 0x800D0814: lui         $t5, 0xC000
    ctx->r13 = S32(0XC000 << 16);
    // 0x800D0818: jal         0x800D20B0
    // 0x800D081C: sw          $t9, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r25;
    __osGetCause_recomp(rdram, ctx);
        goto after_0;
    // 0x800D081C: sw          $t9, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r25;
    after_0:
    // 0x800D0820: andi        $t7, $v0, 0x2000
    ctx->r15 = ctx->r2 & 0X2000;
    // 0x800D0824: bne         $t7, $zero, L_800D0840
    if (ctx->r15 != 0) {
        // 0x800D0828: nop
    
            goto L_800D0840;
    }
    // 0x800D0828: nop

L_800D082C:
    // 0x800D082C: jal         0x800D20B0
    // 0x800D0830: nop

    __osGetCause_recomp(rdram, ctx);
        goto after_1;
    // 0x800D0830: nop

    after_1:
    // 0x800D0834: andi        $t0, $v0, 0x2000
    ctx->r8 = ctx->r2 & 0X2000;
    // 0x800D0838: beq         $t0, $zero, L_800D082C
    if (ctx->r8 == 0) {
        // 0x800D083C: nop
    
            goto L_800D082C;
    }
    // 0x800D083C: nop

L_800D0840:
    // 0x800D0840: lui         $t6, 0xC000
    ctx->r14 = S32(0XC000 << 16);
    // 0x800D0844: sw          $zero, 0xC($t6)
    MEM_W(0XC, ctx->r14) = 0;
    // 0x800D0848: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D084C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800D0850: jr          $ra
    // 0x800D0854: nop

    return;
    // 0x800D0854: nop

;}
RECOMP_FUNC void func_800D0858(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0858: lui         $t6, 0x800F
    ctx->r14 = S32(0X800F << 16);
    // 0x800D085C: lw          $t6, -0x6EBC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X6EBC);
    // 0x800D0860: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800D0864: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D0868: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800D086C: bne         $t6, $zero, L_800D08B0
    if (ctx->r14 != 0) {
        // 0x800D0870: sw          $a1, 0x2C($sp)
        MEM_W(0X2C, ctx->r29) = ctx->r5;
            goto L_800D08B0;
    }
    // 0x800D0870: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800D0874: jal         0x800D20B0
    // 0x800D0878: nop

    __osGetCause_recomp(rdram, ctx);
        goto after_0;
    // 0x800D0878: nop

    after_0:
    // 0x800D087C: andi        $t7, $v0, 0x2000
    ctx->r15 = ctx->r2 & 0X2000;
    // 0x800D0880: bne         $t7, $zero, L_800D089C
    if (ctx->r15 != 0) {
        // 0x800D0884: nop
    
            goto L_800D089C;
    }
    // 0x800D0884: nop

L_800D0888:
    // 0x800D0888: jal         0x800D20B0
    // 0x800D088C: nop

    __osGetCause_recomp(rdram, ctx);
        goto after_1;
    // 0x800D088C: nop

    after_1:
    // 0x800D0890: andi        $t8, $v0, 0x2000
    ctx->r24 = ctx->r2 & 0X2000;
    // 0x800D0894: beq         $t8, $zero, L_800D0888
    if (ctx->r24 == 0) {
        // 0x800D0898: nop
    
            goto L_800D0888;
    }
    // 0x800D0898: nop

L_800D089C:
    // 0x800D089C: lui         $t9, 0xC000
    ctx->r25 = S32(0XC000 << 16);
    // 0x800D08A0: sw          $zero, 0xC($t9)
    MEM_W(0XC, ctx->r25) = 0;
    // 0x800D08A4: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800D08A8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800D08AC: sw          $t0, -0x6EBC($at)
    MEM_W(-0X6EBC, ctx->r1) = ctx->r8;
L_800D08B0:
    // 0x800D08B0: lw          $t1, 0x2C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X2C);
    // 0x800D08B4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800D08B8: sw          $zero, 0x24($sp)
    MEM_W(0X24, ctx->r29) = 0;
    // 0x800D08BC: div         $zero, $t1, $at
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r1)));
    // 0x800D08C0: mfhi        $t2
    ctx->r10 = hi;
    // 0x800D08C4: subu        $t3, $t1, $t2
    ctx->r11 = SUB32(ctx->r9, ctx->r10);
    // 0x800D08C8: sw          $t2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r10;
    // 0x800D08CC: blez        $t3, L_800D0900
    if (SIGNED(ctx->r11) <= 0) {
        // 0x800D08D0: sw          $t3, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r11;
            goto L_800D0900;
    }
    // 0x800D08D0: sw          $t3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r11;
L_800D08D4:
    // 0x800D08D4: lw          $t4, 0x28($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X28);
    // 0x800D08D8: lw          $t5, 0x24($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X24);
    // 0x800D08DC: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x800D08E0: jal         0x800D0798
    // 0x800D08E4: addu        $a0, $t4, $t5
    ctx->r4 = ADD32(ctx->r12, ctx->r13);
    func_800D0798(rdram, ctx);
        goto after_2;
    // 0x800D08E4: addu        $a0, $t4, $t5
    ctx->r4 = ADD32(ctx->r12, ctx->r13);
    after_2:
    // 0x800D08E8: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
    // 0x800D08EC: lw          $t8, 0x20($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X20);
    // 0x800D08F0: addiu       $t7, $t6, 0x3
    ctx->r15 = ADD32(ctx->r14, 0X3);
    // 0x800D08F4: slt         $at, $t7, $t8
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x800D08F8: bne         $at, $zero, L_800D08D4
    if (ctx->r1 != 0) {
        // 0x800D08FC: sw          $t7, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r15;
            goto L_800D08D4;
    }
    // 0x800D08FC: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
L_800D0900:
    // 0x800D0900: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x800D0904: blez        $t9, L_800D0920
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800D0908: nop
    
            goto L_800D0920;
    }
    // 0x800D0908: nop

    // 0x800D090C: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x800D0910: lw          $t1, 0x20($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X20);
    // 0x800D0914: or          $a1, $t9, $zero
    ctx->r5 = ctx->r25 | 0;
    // 0x800D0918: jal         0x800D0798
    // 0x800D091C: addu        $a0, $t0, $t1
    ctx->r4 = ADD32(ctx->r8, ctx->r9);
    func_800D0798(rdram, ctx);
        goto after_3;
    // 0x800D091C: addu        $a0, $t0, $t1
    ctx->r4 = ADD32(ctx->r8, ctx->r9);
    after_3:
L_800D0920:
    // 0x800D0920: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D0924: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800D0928: jr          $ra
    // 0x800D092C: nop

    return;
    // 0x800D092C: nop

;}
RECOMP_FUNC void kdebugserver_text_0220(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0930: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800D0934: lui         $a0, 0x801E
    ctx->r4 = S32(0X801E << 16);
    // 0x800D0938: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D093C: addiu       $a0, $a0, -0x5310
    ctx->r4 = ADD32(ctx->r4, -0X5310);
    // 0x800D0940: jal         0x800D0740
    // 0x800D0944: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    func_800D0740(rdram, ctx);
        goto after_0;
    // 0x800D0944: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    after_0:
    // 0x800D0948: lui         $a0, 0x801E
    ctx->r4 = S32(0X801E << 16);
    // 0x800D094C: addiu       $a0, $a0, -0x5310
    ctx->r4 = ADD32(ctx->r4, -0X5310);
    // 0x800D0950: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800D0954: jal         0x800D0740
    // 0x800D0958: addiu       $a0, $a0, 0x5
    ctx->r4 = ADD32(ctx->r4, 0X5);
    func_800D0740(rdram, ctx);
        goto after_1;
    // 0x800D0958: addiu       $a0, $a0, 0x5
    ctx->r4 = ADD32(ctx->r4, 0X5);
    after_1:
    // 0x800D095C: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800D0960: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x800D0964: jal         0x800D0858
    // 0x800D0968: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    func_800D0858(rdram, ctx);
        goto after_2;
    // 0x800D0968: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    after_2:
    // 0x800D096C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D0970: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800D0974: jr          $ra
    // 0x800D0978: nop

    return;
    // 0x800D0978: nop

;}
RECOMP_FUNC void kdebugserver_text_026C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D097C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800D0980: lui         $a0, 0x801E
    ctx->r4 = S32(0X801E << 16);
    // 0x800D0984: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D0988: addiu       $a0, $a0, -0x5210
    ctx->r4 = ADD32(ctx->r4, -0X5210);
    // 0x800D098C: addiu       $a0, $a0, 0x20
    ctx->r4 = ADD32(ctx->r4, 0X20);
    // 0x800D0990: jal         0x800D0858
    // 0x800D0994: addiu       $a1, $zero, 0x190
    ctx->r5 = ADD32(0, 0X190);
    func_800D0858(rdram, ctx);
        goto after_0;
    // 0x800D0994: addiu       $a1, $zero, 0x190
    ctx->r5 = ADD32(0, 0X190);
    after_0:
    // 0x800D0998: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D099C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800D09A0: jr          $ra
    // 0x800D09A4: nop

    return;
    // 0x800D09A4: nop

;}
RECOMP_FUNC void __osSyncPutChars(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0B90: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800D0B94: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x800D0B98: lw          $t6, 0x28($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X28);
    // 0x800D0B9C: lbu         $t0, 0x24($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X24);
    // 0x800D0BA0: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x800D0BA4: andi        $t7, $t6, 0x3
    ctx->r15 = ctx->r14 & 0X3;
    // 0x800D0BA8: lw          $t3, 0x2C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X2C);
    // 0x800D0BAC: sll         $t8, $t7, 6
    ctx->r24 = S32(ctx->r15 << 6);
    // 0x800D0BB0: andi        $t9, $t8, 0xC0
    ctx->r25 = ctx->r24 & 0XC0;
    // 0x800D0BB4: andi        $t1, $t0, 0xFF3F
    ctx->r9 = ctx->r8 & 0XFF3F;
    // 0x800D0BB8: or          $t2, $t9, $t1
    ctx->r10 = ctx->r25 | ctx->r9;
    // 0x800D0BBC: andi        $t6, $t2, 0xFF
    ctx->r14 = ctx->r10 & 0XFF;
    // 0x800D0BC0: andi        $t4, $t3, 0x3
    ctx->r12 = ctx->r11 & 0X3;
    // 0x800D0BC4: andi        $t5, $t4, 0x3
    ctx->r13 = ctx->r12 & 0X3;
    // 0x800D0BC8: andi        $t7, $t6, 0xFFFC
    ctx->r15 = ctx->r14 & 0XFFFC;
    // 0x800D0BCC: sb          $t2, 0x24($sp)
    MEM_B(0X24, ctx->r29) = ctx->r10;
    // 0x800D0BD0: or          $t8, $t5, $t7
    ctx->r24 = ctx->r13 | ctx->r15;
    // 0x800D0BD4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D0BD8: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x800D0BDC: sb          $t8, 0x24($sp)
    MEM_B(0X24, ctx->r29) = ctx->r24;
    // 0x800D0BE0: blez        $t3, L_800D0C18
    if (SIGNED(ctx->r11) <= 0) {
        // 0x800D0BE4: sw          $zero, 0x20($sp)
        MEM_W(0X20, ctx->r29) = 0;
            goto L_800D0C18;
    }
    // 0x800D0BE4: sw          $zero, 0x20($sp)
    MEM_W(0X20, ctx->r29) = 0;
L_800D0BE8:
    // 0x800D0BE8: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D0BEC: lw          $t9, 0x20($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X20);
    // 0x800D0BF0: addu        $t1, $t0, $t9
    ctx->r9 = ADD32(ctx->r8, ctx->r25);
    // 0x800D0BF4: lbu         $t4, 0x0($t1)
    ctx->r12 = MEM_BU(ctx->r9, 0X0);
    // 0x800D0BF8: addu        $t2, $sp, $t9
    ctx->r10 = ADD32(ctx->r29, ctx->r25);
    // 0x800D0BFC: sb          $t4, 0x25($t2)
    MEM_B(0X25, ctx->r10) = ctx->r12;
    // 0x800D0C00: lw          $t6, 0x20($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X20);
    // 0x800D0C04: lw          $t7, 0x2C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X2C);
    // 0x800D0C08: addiu       $t5, $t6, 0x1
    ctx->r13 = ADD32(ctx->r14, 0X1);
    // 0x800D0C0C: slt         $at, $t5, $t7
    ctx->r1 = SIGNED(ctx->r13) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800D0C10: bne         $at, $zero, L_800D0BE8
    if (ctx->r1 != 0) {
        // 0x800D0C14: sw          $t5, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r13;
            goto L_800D0BE8;
    }
    // 0x800D0C14: sw          $t5, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r13;
L_800D0C18:
    // 0x800D0C18: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800D0C1C: jal         0x800D20C0
    // 0x800D0C20: addiu       $a0, $a0, -0x6EBC
    ctx->r4 = ADD32(ctx->r4, -0X6EBC);
    __osAtomicDec(rdram, ctx);
        goto after_0;
    // 0x800D0C20: addiu       $a0, $a0, -0x6EBC
    ctx->r4 = ADD32(ctx->r4, -0X6EBC);
    after_0:
    // 0x800D0C24: bne         $v0, $zero, L_800D0C40
    if (ctx->r2 != 0) {
        // 0x800D0C28: nop
    
            goto L_800D0C40;
    }
    // 0x800D0C28: nop

L_800D0C2C:
    // 0x800D0C2C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800D0C30: jal         0x800D20C0
    // 0x800D0C34: addiu       $a0, $a0, -0x6EBC
    ctx->r4 = ADD32(ctx->r4, -0X6EBC);
    __osAtomicDec(rdram, ctx);
        goto after_1;
    // 0x800D0C34: addiu       $a0, $a0, -0x6EBC
    ctx->r4 = ADD32(ctx->r4, -0X6EBC);
    after_1:
    // 0x800D0C38: beq         $v0, $zero, L_800D0C2C
    if (ctx->r2 == 0) {
        // 0x800D0C3C: nop
    
            goto L_800D0C2C;
    }
    // 0x800D0C3C: nop

L_800D0C40:
    // 0x800D0C40: jal         0x800CAAD0
    // 0x800D0C44: nop

    __osDisableInt_recomp(rdram, ctx);
        goto after_2;
    // 0x800D0C44: nop

    after_2:
    // 0x800D0C48: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800D0C4C: addiu       $t8, $sp, 0x24
    ctx->r24 = ADD32(ctx->r29, 0X24);
    // 0x800D0C50: lw          $t3, 0x0($t8)
    ctx->r11 = MEM_W(ctx->r24, 0X0);
    // 0x800D0C54: lui         $t0, 0xC000
    ctx->r8 = S32(0XC000 << 16);
    // 0x800D0C58: jal         0x800D20B0
    // 0x800D0C5C: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    __osGetCause_recomp(rdram, ctx);
        goto after_3;
    // 0x800D0C5C: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    after_3:
    // 0x800D0C60: andi        $t1, $v0, 0x2000
    ctx->r9 = ctx->r2 & 0X2000;
    // 0x800D0C64: bne         $t1, $zero, L_800D0C80
    if (ctx->r9 != 0) {
        // 0x800D0C68: nop
    
            goto L_800D0C80;
    }
    // 0x800D0C68: nop

L_800D0C6C:
    // 0x800D0C6C: jal         0x800D20B0
    // 0x800D0C70: nop

    __osGetCause_recomp(rdram, ctx);
        goto after_4;
    // 0x800D0C70: nop

    after_4:
    // 0x800D0C74: andi        $t4, $v0, 0x2000
    ctx->r12 = ctx->r2 & 0X2000;
    // 0x800D0C78: beq         $t4, $zero, L_800D0C6C
    if (ctx->r12 == 0) {
        // 0x800D0C7C: nop
    
            goto L_800D0C6C;
    }
    // 0x800D0C7C: nop

L_800D0C80:
    // 0x800D0C80: lui         $t9, 0xC000
    ctx->r25 = S32(0XC000 << 16);
    // 0x800D0C84: sw          $zero, 0xC($t9)
    MEM_W(0XC, ctx->r25) = 0;
    // 0x800D0C88: lui         $t2, 0x800F
    ctx->r10 = S32(0X800F << 16);
    // 0x800D0C8C: lw          $t2, -0x6EBC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X6EBC);
    // 0x800D0C90: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800D0C94: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    // 0x800D0C98: addiu       $t6, $t2, 0x1
    ctx->r14 = ADD32(ctx->r10, 0X1);
    // 0x800D0C9C: jal         0x800CAAF0
    // 0x800D0CA0: sw          $t6, -0x6EBC($at)
    MEM_W(-0X6EBC, ctx->r1) = ctx->r14;
    __osRestoreInt_recomp(rdram, ctx);
        goto after_5;
    // 0x800D0CA0: sw          $t6, -0x6EBC($at)
    MEM_W(-0X6EBC, ctx->r1) = ctx->r14;
    after_5:
    // 0x800D0CA4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D0CA8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800D0CAC: jr          $ra
    // 0x800D0CB0: nop

    return;
    // 0x800D0CB0: nop

    // 0x800D0CB4: nop

    // 0x800D0CB8: nop

    // 0x800D0CBC: nop

;}
RECOMP_FUNC void _Litob(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D0FE0: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x800D0FE4: sw          $a1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r5;
    // 0x800D0FE8: lbu         $t6, 0x77($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X77);
    // 0x800D0FEC: addiu       $at, $zero, 0x58
    ctx->r1 = ADD32(0, 0X58);
    // 0x800D0FF0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800D0FF4: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x800D0FF8: bne         $t6, $at, L_800D1010
    if (ctx->r14 != ctx->r1) {
        // 0x800D0FFC: sw          $s0, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r16;
            goto L_800D1010;
    }
    // 0x800D0FFC: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x800D1000: lui         $t7, 0x800F
    ctx->r15 = S32(0X800F << 16);
    // 0x800D1004: addiu       $t7, $t7, -0x6DFC
    ctx->r15 = ADD32(ctx->r15, -0X6DFC);
    // 0x800D1008: b           L_800D101C
    // 0x800D100C: sw          $t7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r15;
        goto L_800D101C;
    // 0x800D100C: sw          $t7, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r15;
L_800D1010:
    // 0x800D1010: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800D1014: addiu       $t8, $t8, -0x6E10
    ctx->r24 = ADD32(ctx->r24, -0X6E10);
    // 0x800D1018: sw          $t8, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r24;
L_800D101C:
    // 0x800D101C: lbu         $t9, 0x77($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X77);
    // 0x800D1020: addiu       $at, $zero, 0x6F
    ctx->r1 = ADD32(0, 0X6F);
    // 0x800D1024: bne         $t9, $at, L_800D1038
    if (ctx->r25 != ctx->r1) {
        // 0x800D1028: nop
    
            goto L_800D1038;
    }
    // 0x800D1028: nop

    // 0x800D102C: addiu       $t0, $zero, 0x8
    ctx->r8 = ADD32(0, 0X8);
    // 0x800D1030: b           L_800D1060
    // 0x800D1034: sw          $t0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r8;
        goto L_800D1060;
    // 0x800D1034: sw          $t0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r8;
L_800D1038:
    // 0x800D1038: lbu         $t1, 0x77($sp)
    ctx->r9 = MEM_BU(ctx->r29, 0X77);
    // 0x800D103C: addiu       $at, $zero, 0x78
    ctx->r1 = ADD32(0, 0X78);
    // 0x800D1040: beq         $t1, $at, L_800D1058
    if (ctx->r9 == ctx->r1) {
        // 0x800D1044: addiu       $at, $zero, 0x58
        ctx->r1 = ADD32(0, 0X58);
            goto L_800D1058;
    }
    // 0x800D1044: addiu       $at, $zero, 0x58
    ctx->r1 = ADD32(0, 0X58);
    // 0x800D1048: beq         $t1, $at, L_800D1058
    if (ctx->r9 == ctx->r1) {
        // 0x800D104C: nop
    
            goto L_800D1058;
    }
    // 0x800D104C: nop

    // 0x800D1050: b           L_800D105C
    // 0x800D1054: addiu       $s0, $zero, 0xA
    ctx->r16 = ADD32(0, 0XA);
        goto L_800D105C;
    // 0x800D1054: addiu       $s0, $zero, 0xA
    ctx->r16 = ADD32(0, 0XA);
L_800D1058:
    // 0x800D1058: addiu       $s0, $zero, 0x10
    ctx->r16 = ADD32(0, 0X10);
L_800D105C:
    // 0x800D105C: sw          $s0, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r16;
L_800D1060:
    // 0x800D1060: lw          $t3, 0x70($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X70);
    // 0x800D1064: addiu       $t2, $zero, 0x18
    ctx->r10 = ADD32(0, 0X18);
    // 0x800D1068: sw          $t2, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r10;
    // 0x800D106C: lbu         $t6, 0x77($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X77);
    // 0x800D1070: lw          $t5, 0x4($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X4);
    // 0x800D1074: lw          $t4, 0x0($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X0);
    // 0x800D1078: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x800D107C: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x800D1080: beq         $t6, $at, L_800D1094
    if (ctx->r14 == ctx->r1) {
        // 0x800D1084: sw          $t4, 0x40($sp)
        MEM_W(0X40, ctx->r29) = ctx->r12;
            goto L_800D1094;
    }
    // 0x800D1084: sw          $t4, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r12;
    // 0x800D1088: addiu       $at, $zero, 0x69
    ctx->r1 = ADD32(0, 0X69);
    // 0x800D108C: bne         $t6, $at, L_800D10D8
    if (ctx->r14 != ctx->r1) {
        // 0x800D1090: nop
    
            goto L_800D10D8;
    }
    // 0x800D1090: nop

L_800D1094:
    // 0x800D1094: lw          $t7, 0x70($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X70);
    // 0x800D1098: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x800D109C: lw          $t9, 0x4($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X4);
    // 0x800D10A0: bgtz        $t8, L_800D10D8
    if (SIGNED(ctx->r24) > 0) {
        // 0x800D10A4: nop
    
            goto L_800D10D8;
    }
    // 0x800D10A4: nop

    // 0x800D10A8: bltz        $t8, L_800D10B8
    if (SIGNED(ctx->r24) < 0) {
        // 0x800D10AC: nop
    
            goto L_800D10B8;
    }
    // 0x800D10AC: nop

    // 0x800D10B0: b           L_800D10D8
    // 0x800D10B4: nop

        goto L_800D10D8;
    // 0x800D10B4: nop

L_800D10B8:
    // 0x800D10B8: lw          $t0, 0x40($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X40);
    // 0x800D10BC: lw          $t1, 0x44($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X44);
    // 0x800D10C0: nor         $t2, $t0, $zero
    ctx->r10 = ~(ctx->r8 | 0);
    // 0x800D10C4: sltiu       $at, $t1, 0x1
    ctx->r1 = ctx->r9 < 0X1 ? 1 : 0;
    // 0x800D10C8: addu        $t2, $t2, $at
    ctx->r10 = ADD32(ctx->r10, ctx->r1);
    // 0x800D10CC: negu        $t3, $t1
    ctx->r11 = SUB32(0, ctx->r9);
    // 0x800D10D0: sw          $t3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r11;
    // 0x800D10D4: sw          $t2, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r10;
L_800D10D8:
    // 0x800D10D8: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x800D10DC: lw          $t5, 0x44($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X44);
    // 0x800D10E0: bne         $t4, $zero, L_800D1100
    if (ctx->r12 != 0) {
        // 0x800D10E4: nop
    
            goto L_800D1100;
    }
    // 0x800D10E4: nop

    // 0x800D10E8: bne         $t5, $zero, L_800D1100
    if (ctx->r13 != 0) {
        // 0x800D10EC: nop
    
            goto L_800D1100;
    }
    // 0x800D10EC: nop

    // 0x800D10F0: lw          $t6, 0x70($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X70);
    // 0x800D10F4: lw          $t7, 0x24($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X24);
    // 0x800D10F8: beq         $t7, $zero, L_800D113C
    if (ctx->r15 == 0) {
        // 0x800D10FC: nop
    
            goto L_800D113C;
    }
    // 0x800D10FC: nop

L_800D1100:
    // 0x800D1100: lw          $s0, 0x4C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1104: lw          $t8, 0x50($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X50);
    // 0x800D1108: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800D110C: addiu       $s0, $s0, -0x1
    ctx->r16 = ADD32(ctx->r16, -0X1);
    // 0x800D1110: sw          $s0, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r16;
    // 0x800D1114: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x800D1118: or          $a3, $t8, $zero
    ctx->r7 = ctx->r24 | 0;
    // 0x800D111C: jal         0x800CC78C
    // 0x800D1120: sra         $a2, $t8, 31
    ctx->r6 = S32(SIGNED(ctx->r24) >> 31);
    __ull_rem_recomp(rdram, ctx);
        goto after_0;
    // 0x800D1120: sra         $a2, $t8, 31
    ctx->r6 = S32(SIGNED(ctx->r24) >> 31);
    after_0:
    // 0x800D1124: lw          $t0, 0x54($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X54);
    // 0x800D1128: or          $t9, $v1, $zero
    ctx->r25 = ctx->r3 | 0;
    // 0x800D112C: addu        $t3, $sp, $s0
    ctx->r11 = ADD32(ctx->r29, ctx->r16);
    // 0x800D1130: addu        $t1, $t9, $t0
    ctx->r9 = ADD32(ctx->r25, ctx->r8);
    // 0x800D1134: lbu         $t2, 0x0($t1)
    ctx->r10 = MEM_BU(ctx->r9, 0X0);
    // 0x800D1138: sb          $t2, 0x58($t3)
    MEM_B(0X58, ctx->r11) = ctx->r10;
L_800D113C:
    // 0x800D113C: lw          $t4, 0x50($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X50);
    // 0x800D1140: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800D1144: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x800D1148: or          $a3, $t4, $zero
    ctx->r7 = ctx->r12 | 0;
    // 0x800D114C: jal         0x800CC7C8
    // 0x800D1150: sra         $a2, $t4, 31
    ctx->r6 = S32(SIGNED(ctx->r12) >> 31);
    __ull_div_recomp(rdram, ctx);
        goto after_1;
    // 0x800D1150: sra         $a2, $t4, 31
    ctx->r6 = S32(SIGNED(ctx->r12) >> 31);
    after_1:
    // 0x800D1154: lw          $t5, 0x70($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X70);
    // 0x800D1158: sw          $v0, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r2;
    // 0x800D115C: sw          $v1, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r3;
    // 0x800D1160: lw          $t6, 0x70($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X70);
    // 0x800D1164: lw          $t8, 0x0($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X0);
    // 0x800D1168: lw          $t9, 0x4($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X4);
    // 0x800D116C: bltz        $t8, L_800D1228
    if (SIGNED(ctx->r24) < 0) {
        // 0x800D1170: nop
    
            goto L_800D1228;
    }
    // 0x800D1170: nop

    // 0x800D1174: bgtz        $t8, L_800D1184
    if (SIGNED(ctx->r24) > 0) {
        // 0x800D1178: nop
    
            goto L_800D1184;
    }
    // 0x800D1178: nop

    // 0x800D117C: beq         $t9, $zero, L_800D1228
    if (ctx->r25 == 0) {
        // 0x800D1180: nop
    
            goto L_800D1228;
    }
    // 0x800D1180: nop

L_800D1184:
    // 0x800D1184: lw          $t7, 0x4C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1188: blez        $t7, L_800D1228
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800D118C: nop
    
            goto L_800D1228;
    }
    // 0x800D118C: nop

L_800D1190:
    // 0x800D1190: lw          $t0, 0x70($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X70);
    // 0x800D1194: lw          $t1, 0x50($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X50);
    // 0x800D1198: addiu       $a0, $sp, 0x30
    ctx->r4 = ADD32(ctx->r29, 0X30);
    // 0x800D119C: lw          $a2, 0x0($t0)
    ctx->r6 = MEM_W(ctx->r8, 0X0);
    // 0x800D11A0: lw          $a3, 0x4($t0)
    ctx->r7 = MEM_W(ctx->r8, 0X4);
    // 0x800D11A4: or          $t3, $t1, $zero
    ctx->r11 = ctx->r9 | 0;
    // 0x800D11A8: sra         $t2, $t1, 31
    ctx->r10 = S32(SIGNED(ctx->r9) >> 31);
    // 0x800D11AC: sw          $t2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r10;
    // 0x800D11B0: jal         0x800D2120
    // 0x800D11B4: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    lldiv_recomp(rdram, ctx);
        goto after_2;
    // 0x800D11B4: sw          $t3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r11;
    after_2:
    // 0x800D11B8: lw          $t6, 0x70($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X70);
    // 0x800D11BC: lw          $t4, 0x30($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X30);
    // 0x800D11C0: lw          $t5, 0x34($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X34);
    // 0x800D11C4: sw          $t4, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r12;
    // 0x800D11C8: sw          $t5, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r13;
    // 0x800D11CC: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x800D11D0: lw          $s0, 0x4C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4C);
    // 0x800D11D4: lw          $t0, 0x54($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X54);
    // 0x800D11D8: or          $t7, $t9, $zero
    ctx->r15 = ctx->r25 | 0;
    // 0x800D11DC: addiu       $s0, $s0, -0x1
    ctx->r16 = ADD32(ctx->r16, -0X1);
    // 0x800D11E0: sw          $s0, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r16;
    // 0x800D11E4: addu        $t1, $t7, $t0
    ctx->r9 = ADD32(ctx->r15, ctx->r8);
    // 0x800D11E8: lbu         $t2, 0x0($t1)
    ctx->r10 = MEM_BU(ctx->r9, 0X0);
    // 0x800D11EC: addu        $t3, $sp, $s0
    ctx->r11 = ADD32(ctx->r29, ctx->r16);
    // 0x800D11F0: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800D11F4: sb          $t2, 0x58($t3)
    MEM_B(0X58, ctx->r11) = ctx->r10;
    // 0x800D11F8: lw          $t4, 0x70($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X70);
    // 0x800D11FC: lw          $t6, 0x0($t4)
    ctx->r14 = MEM_W(ctx->r12, 0X0);
    // 0x800D1200: lw          $t7, 0x4($t4)
    ctx->r15 = MEM_W(ctx->r12, 0X4);
    // 0x800D1204: bltz        $t6, L_800D1228
    if (SIGNED(ctx->r14) < 0) {
        // 0x800D1208: nop
    
            goto L_800D1228;
    }
    // 0x800D1208: nop

    // 0x800D120C: bgtz        $t6, L_800D121C
    if (SIGNED(ctx->r14) > 0) {
        // 0x800D1210: nop
    
            goto L_800D121C;
    }
    // 0x800D1210: nop

    // 0x800D1214: beq         $t7, $zero, L_800D1228
    if (ctx->r15 == 0) {
        // 0x800D1218: nop
    
            goto L_800D1228;
    }
    // 0x800D1218: nop

L_800D121C:
    // 0x800D121C: lw          $t5, 0x4C($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1220: bgtz        $t5, L_800D1190
    if (SIGNED(ctx->r13) > 0) {
        // 0x800D1224: nop
    
            goto L_800D1190;
    }
    // 0x800D1224: nop

L_800D1228:
    // 0x800D1228: lw          $t8, 0x4C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4C);
    // 0x800D122C: lw          $t1, 0x70($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X70);
    // 0x800D1230: addiu       $t9, $zero, 0x18
    ctx->r25 = ADD32(0, 0X18);
    // 0x800D1234: subu        $t0, $t9, $t8
    ctx->r8 = SUB32(ctx->r25, ctx->r24);
    // 0x800D1238: sw          $t0, 0x14($t1)
    MEM_W(0X14, ctx->r9) = ctx->r8;
    // 0x800D123C: lw          $t2, 0x70($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X70);
    // 0x800D1240: lw          $t3, 0x4C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1244: addiu       $t4, $sp, 0x58
    ctx->r12 = ADD32(ctx->r29, 0X58);
    // 0x800D1248: lw          $a0, 0x8($t2)
    ctx->r4 = MEM_W(ctx->r10, 0X8);
    // 0x800D124C: lw          $a2, 0x14($t2)
    ctx->r6 = MEM_W(ctx->r10, 0X14);
    // 0x800D1250: jal         0x800D04C0
    // 0x800D1254: addu        $a1, $t3, $t4
    ctx->r5 = ADD32(ctx->r11, ctx->r12);
    memcpy_recomp(rdram, ctx);
        goto after_3;
    // 0x800D1254: addu        $a1, $t3, $t4
    ctx->r5 = ADD32(ctx->r11, ctx->r12);
    after_3:
    // 0x800D1258: lw          $t6, 0x70($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X70);
    // 0x800D125C: lw          $t7, 0x14($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X14);
    // 0x800D1260: lw          $t5, 0x24($t6)
    ctx->r13 = MEM_W(ctx->r14, 0X24);
    // 0x800D1264: slt         $at, $t7, $t5
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r13) ? 1 : 0;
    // 0x800D1268: beq         $at, $zero, L_800D1278
    if (ctx->r1 == 0) {
        // 0x800D126C: nop
    
            goto L_800D1278;
    }
    // 0x800D126C: nop

    // 0x800D1270: subu        $t9, $t5, $t7
    ctx->r25 = SUB32(ctx->r13, ctx->r15);
    // 0x800D1274: sw          $t9, 0x10($t6)
    MEM_W(0X10, ctx->r14) = ctx->r25;
L_800D1278:
    // 0x800D1278: lw          $t8, 0x70($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X70);
    // 0x800D127C: lw          $t0, 0x24($t8)
    ctx->r8 = MEM_W(ctx->r24, 0X24);
    // 0x800D1280: bgez        $t0, L_800D12CC
    if (SIGNED(ctx->r8) >= 0) {
        // 0x800D1284: nop
    
            goto L_800D12CC;
    }
    // 0x800D1284: nop

    // 0x800D1288: lw          $t1, 0x30($t8)
    ctx->r9 = MEM_W(ctx->r24, 0X30);
    // 0x800D128C: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x800D1290: andi        $t3, $t1, 0x14
    ctx->r11 = ctx->r9 & 0X14;
    // 0x800D1294: bne         $t3, $at, L_800D12CC
    if (ctx->r11 != ctx->r1) {
        // 0x800D1298: nop
    
            goto L_800D12CC;
    }
    // 0x800D1298: nop

    // 0x800D129C: lw          $t4, 0x28($t8)
    ctx->r12 = MEM_W(ctx->r24, 0X28);
    // 0x800D12A0: lw          $t2, 0xC($t8)
    ctx->r10 = MEM_W(ctx->r24, 0XC);
    // 0x800D12A4: lw          $t7, 0x10($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X10);
    // 0x800D12A8: lw          $t6, 0x14($t8)
    ctx->r14 = MEM_W(ctx->r24, 0X14);
    // 0x800D12AC: subu        $t5, $t4, $t2
    ctx->r13 = SUB32(ctx->r12, ctx->r10);
    // 0x800D12B0: subu        $t9, $t5, $t7
    ctx->r25 = SUB32(ctx->r13, ctx->r15);
    // 0x800D12B4: subu        $t0, $t9, $t6
    ctx->r8 = SUB32(ctx->r25, ctx->r14);
    // 0x800D12B8: blez        $t0, L_800D12CC
    if (SIGNED(ctx->r8) <= 0) {
        // 0x800D12BC: sw          $t0, 0x4C($sp)
        MEM_W(0X4C, ctx->r29) = ctx->r8;
            goto L_800D12CC;
    }
    // 0x800D12BC: sw          $t0, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r8;
    // 0x800D12C0: lw          $t1, 0x10($t8)
    ctx->r9 = MEM_W(ctx->r24, 0X10);
    // 0x800D12C4: addu        $t3, $t1, $t0
    ctx->r11 = ADD32(ctx->r9, ctx->r8);
    // 0x800D12C8: sw          $t3, 0x10($t8)
    MEM_W(0X10, ctx->r24) = ctx->r11;
L_800D12CC:
    // 0x800D12CC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800D12D0: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x800D12D4: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    // 0x800D12D8: jr          $ra
    // 0x800D12DC: nop

    return;
    // 0x800D12DC: nop

;}
RECOMP_FUNC void _Ldtob(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D12E0: addiu       $sp, $sp, -0x98
    ctx->r29 = ADD32(ctx->r29, -0X98);
    // 0x800D12E4: sw          $a0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r4;
    // 0x800D12E8: lw          $t7, 0x98($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X98);
    // 0x800D12EC: addiu       $t6, $sp, 0x78
    ctx->r14 = ADD32(ctx->r29, 0X78);
    // 0x800D12F0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x800D12F4: sw          $a1, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r5;
    // 0x800D12F8: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x800D12FC: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x800D1300: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800D1304: ldc1        $f4, 0x0($t7)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r15, 0X0);
    // 0x800D1308: sdc1        $f4, 0x68($sp)
    CHECK_FR(ctx, 4);
    SD(ctx->f4.u64, 0X68, ctx->r29);
    // 0x800D130C: lw          $t8, 0x24($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X24);
    // 0x800D1310: bgez        $t8, L_800D1324
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800D1314: nop
    
            goto L_800D1324;
    }
    // 0x800D1314: nop

    // 0x800D1318: addiu       $t9, $zero, 0x6
    ctx->r25 = ADD32(0, 0X6);
    // 0x800D131C: b           L_800D1358
    // 0x800D1320: sw          $t9, 0x24($t7)
    MEM_W(0X24, ctx->r15) = ctx->r25;
        goto L_800D1358;
    // 0x800D1320: sw          $t9, 0x24($t7)
    MEM_W(0X24, ctx->r15) = ctx->r25;
L_800D1324:
    // 0x800D1324: lw          $t0, 0x98($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X98);
    // 0x800D1328: lw          $t1, 0x24($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X24);
    // 0x800D132C: bne         $t1, $zero, L_800D1358
    if (ctx->r9 != 0) {
        // 0x800D1330: nop
    
            goto L_800D1358;
    }
    // 0x800D1330: nop

    // 0x800D1334: lbu         $t2, 0x9F($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X9F);
    // 0x800D1338: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x800D133C: beq         $t2, $at, L_800D134C
    if (ctx->r10 == ctx->r1) {
        // 0x800D1340: addiu       $at, $zero, 0x47
        ctx->r1 = ADD32(0, 0X47);
            goto L_800D134C;
    }
    // 0x800D1340: addiu       $at, $zero, 0x47
    ctx->r1 = ADD32(0, 0X47);
    // 0x800D1344: bne         $t2, $at, L_800D1358
    if (ctx->r10 != ctx->r1) {
        // 0x800D1348: nop
    
            goto L_800D1358;
    }
    // 0x800D1348: nop

L_800D134C:
    // 0x800D134C: lw          $t4, 0x98($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X98);
    // 0x800D1350: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800D1354: sw          $t3, 0x24($t4)
    MEM_W(0X24, ctx->r12) = ctx->r11;
L_800D1358:
    // 0x800D1358: addiu       $a0, $sp, 0x62
    ctx->r4 = ADD32(ctx->r29, 0X62);
    // 0x800D135C: jal         0x800D18E0
    // 0x800D1360: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    xldtob_text_0600(rdram, ctx);
        goto after_0;
    // 0x800D1360: lw          $a1, 0x98($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X98);
    after_0:
    // 0x800D1364: sh          $v0, 0x66($sp)
    MEM_H(0X66, ctx->r29) = ctx->r2;
    // 0x800D1368: lh          $t5, 0x66($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X66);
    // 0x800D136C: blez        $t5, L_800D13B8
    if (SIGNED(ctx->r13) <= 0) {
        // 0x800D1370: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800D13B8;
    }
    // 0x800D1370: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800D1374: bne         $t5, $at, L_800D1388
    if (ctx->r13 != ctx->r1) {
        // 0x800D1378: nop
    
            goto L_800D1388;
    }
    // 0x800D1378: nop

    // 0x800D137C: lui         $s0, 0x800F
    ctx->r16 = S32(0X800F << 16);
    // 0x800D1380: b           L_800D1390
    // 0x800D1384: addiu       $s0, $s0, -0x37E8
    ctx->r16 = ADD32(ctx->r16, -0X37E8);
        goto L_800D1390;
    // 0x800D1384: addiu       $s0, $s0, -0x37E8
    ctx->r16 = ADD32(ctx->r16, -0X37E8);
L_800D1388:
    // 0x800D1388: lui         $s0, 0x800F
    ctx->r16 = S32(0X800F << 16);
    // 0x800D138C: addiu       $s0, $s0, -0x37E4
    ctx->r16 = ADD32(ctx->r16, -0X37E4);
L_800D1390:
    // 0x800D1390: lw          $t6, 0x98($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X98);
    // 0x800D1394: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x800D1398: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800D139C: sw          $t8, 0x14($t6)
    MEM_W(0X14, ctx->r14) = ctx->r24;
    // 0x800D13A0: lw          $t9, 0x98($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X98);
    // 0x800D13A4: lw          $a0, 0x8($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X8);
    // 0x800D13A8: jal         0x800D04C0
    // 0x800D13AC: lw          $a2, 0x14($t9)
    ctx->r6 = MEM_W(ctx->r25, 0X14);
    memcpy_recomp(rdram, ctx);
        goto after_1;
    // 0x800D13AC: lw          $a2, 0x14($t9)
    ctx->r6 = MEM_W(ctx->r25, 0X14);
    after_1:
    // 0x800D13B0: b           L_800D18CC
    // 0x800D13B4: nop

        goto L_800D18CC;
    // 0x800D13B4: nop

L_800D13B8:
    // 0x800D13B8: lh          $t7, 0x66($sp)
    ctx->r15 = MEM_H(ctx->r29, 0X66);
    // 0x800D13BC: bne         $t7, $zero, L_800D13D0
    if (ctx->r15 != 0) {
        // 0x800D13C0: nop
    
            goto L_800D13D0;
    }
    // 0x800D13C0: nop

    // 0x800D13C4: sh          $zero, 0x64($sp)
    MEM_H(0X64, ctx->r29) = 0;
    // 0x800D13C8: b           L_800D18B0
    // 0x800D13CC: sh          $zero, 0x62($sp)
    MEM_H(0X62, ctx->r29) = 0;
        goto L_800D18B0;
    // 0x800D13CC: sh          $zero, 0x62($sp)
    MEM_H(0X62, ctx->r29) = 0;
L_800D13D0:
    // 0x800D13D0: ldc1        $f6, 0x68($sp)
    CHECK_FR(ctx, 6);
    ctx->f6.u64 = LD(ctx->r29, 0X68);
    // 0x800D13D4: mtc1        $zero, $f9
    ctx->f_odd[(9 - 1) * 2] = 0;
    // 0x800D13D8: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x800D13DC: nop

    // 0x800D13E0: c.lt.d      $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f6.d < ctx->f8.d;
    // 0x800D13E4: nop

    // 0x800D13E8: bc1f        L_800D13F8
    if (!c1cs) {
        // 0x800D13EC: nop
    
            goto L_800D13F8;
    }
    // 0x800D13EC: nop

    // 0x800D13F0: neg.d       $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f6.d); 
    ctx->f10.d = -ctx->f6.d;
    // 0x800D13F4: sdc1        $f10, 0x68($sp)
    CHECK_FR(ctx, 10);
    SD(ctx->f10.u64, 0X68, ctx->r29);
L_800D13F8:
    // 0x800D13F8: lh          $t0, 0x62($sp)
    ctx->r8 = MEM_H(ctx->r29, 0X62);
    // 0x800D13FC: addiu       $at, $zero, 0x7597
    ctx->r1 = ADD32(0, 0X7597);
    // 0x800D1400: multu       $t0, $at
    result = U64(U32(ctx->r8)) * U64(U32(ctx->r1)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800D1404: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x800D1408: ori         $at, $at, 0x86A0
    ctx->r1 = ctx->r1 | 0X86A0;
    // 0x800D140C: mflo        $t1
    ctx->r9 = lo;
    // 0x800D1410: nop

    // 0x800D1414: nop

    // 0x800D1418: div         $zero, $t1, $at
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r1)));
    // 0x800D141C: mflo        $t2
    ctx->r10 = lo;
    // 0x800D1420: addiu       $t3, $t2, -0x4
    ctx->r11 = ADD32(ctx->r10, -0X4);
    // 0x800D1424: sll         $t4, $t3, 16
    ctx->r12 = S32(ctx->r11 << 16);
    // 0x800D1428: sra         $t5, $t4, 16
    ctx->r13 = S32(SIGNED(ctx->r12) >> 16);
    // 0x800D142C: bgez        $t5, L_800D14B8
    if (SIGNED(ctx->r13) >= 0) {
        // 0x800D1430: sh          $t3, 0x62($sp)
        MEM_H(0X62, ctx->r29) = ctx->r11;
            goto L_800D14B8;
    }
    // 0x800D1430: sh          $t3, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r11;
    // 0x800D1434: sll         $t6, $t3, 16
    ctx->r14 = S32(ctx->r11 << 16);
    // 0x800D1438: sra         $t9, $t6, 16
    ctx->r25 = S32(SIGNED(ctx->r14) >> 16);
    // 0x800D143C: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x800D1440: subu        $t7, $t8, $t9
    ctx->r15 = SUB32(ctx->r24, ctx->r25);
    // 0x800D1444: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D1448: and         $t0, $t7, $at
    ctx->r8 = ctx->r15 & ctx->r1;
    // 0x800D144C: sw          $t0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r8;
    // 0x800D1450: lw          $t2, 0x58($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X58);
    // 0x800D1454: negu        $t1, $t0
    ctx->r9 = SUB32(0, ctx->r8);
    // 0x800D1458: sh          $t1, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r9;
    // 0x800D145C: blez        $t2, L_800D154C
    if (SIGNED(ctx->r10) <= 0) {
        // 0x800D1460: sw          $zero, 0x5C($sp)
        MEM_W(0X5C, ctx->r29) = 0;
            goto L_800D154C;
    }
    // 0x800D1460: sw          $zero, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = 0;
L_800D1464:
    // 0x800D1464: lw          $t4, 0x58($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X58);
    // 0x800D1468: andi        $t5, $t4, 0x1
    ctx->r13 = ctx->r12 & 0X1;
    // 0x800D146C: beq         $t5, $zero, L_800D1494
    if (ctx->r13 == 0) {
        // 0x800D1470: nop
    
            goto L_800D1494;
    }
    // 0x800D1470: nop

    // 0x800D1474: lw          $t3, 0x5C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X5C);
    // 0x800D1478: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800D147C: ldc1        $f16, 0x68($sp)
    CHECK_FR(ctx, 16);
    ctx->f16.u64 = LD(ctx->r29, 0X68);
    // 0x800D1480: sll         $t6, $t3, 3
    ctx->r14 = S32(ctx->r11 << 3);
    // 0x800D1484: addu        $at, $at, $t6
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800D1488: ldc1        $f18, -0x3830($at)
    CHECK_FR(ctx, 18);
    ctx->f18.u64 = LD(ctx->r1, -0X3830);
    // 0x800D148C: mul.d       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f18.d); 
    ctx->f4.d = MUL_D(ctx->f16.d, ctx->f18.d);
    // 0x800D1490: sdc1        $f4, 0x68($sp)
    CHECK_FR(ctx, 4);
    SD(ctx->f4.u64, 0X68, ctx->r29);
L_800D1494:
    // 0x800D1494: lw          $t8, 0x58($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X58);
    // 0x800D1498: lw          $t7, 0x5C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X5C);
    // 0x800D149C: sra         $t9, $t8, 1
    ctx->r25 = S32(SIGNED(ctx->r24) >> 1);
    // 0x800D14A0: addiu       $t0, $t7, 0x1
    ctx->r8 = ADD32(ctx->r15, 0X1);
    // 0x800D14A4: sw          $t0, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r8;
    // 0x800D14A8: bgtz        $t9, L_800D1464
    if (SIGNED(ctx->r25) > 0) {
        // 0x800D14AC: sw          $t9, 0x58($sp)
        MEM_W(0X58, ctx->r29) = ctx->r25;
            goto L_800D1464;
    }
    // 0x800D14AC: sw          $t9, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r25;
    // 0x800D14B0: b           L_800D154C
    // 0x800D14B4: nop

        goto L_800D154C;
    // 0x800D14B4: nop

L_800D14B8:
    // 0x800D14B8: lh          $t1, 0x62($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X62);
    // 0x800D14BC: blez        $t1, L_800D154C
    if (SIGNED(ctx->r9) <= 0) {
        // 0x800D14C0: lui         $at, 0x3FF0
        ctx->r1 = S32(0X3FF0 << 16);
            goto L_800D154C;
    }
    // 0x800D14C0: lui         $at, 0x3FF0
    ctx->r1 = S32(0X3FF0 << 16);
    // 0x800D14C4: mtc1        $at, $f9
    ctx->f_odd[(9 - 1) * 2] = ctx->r1;
    // 0x800D14C8: addiu       $at, $zero, -0x4
    ctx->r1 = ADD32(0, -0X4);
    // 0x800D14CC: and         $t2, $t1, $at
    ctx->r10 = ctx->r9 & ctx->r1;
    // 0x800D14D0: mtc1        $zero, $f8
    ctx->f8.u32l = 0;
    // 0x800D14D4: sll         $t4, $t2, 16
    ctx->r12 = S32(ctx->r10 << 16);
    // 0x800D14D8: sra         $t5, $t4, 16
    ctx->r13 = S32(SIGNED(ctx->r12) >> 16);
    // 0x800D14DC: sh          $t2, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r10;
    // 0x800D14E0: sw          $t5, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r13;
    // 0x800D14E4: sw          $zero, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = 0;
    // 0x800D14E8: blez        $t5, L_800D153C
    if (SIGNED(ctx->r13) <= 0) {
        // 0x800D14EC: sdc1        $f8, 0x50($sp)
        CHECK_FR(ctx, 8);
    SD(ctx->f8.u64, 0X50, ctx->r29);
            goto L_800D153C;
    }
    // 0x800D14EC: sdc1        $f8, 0x50($sp)
    CHECK_FR(ctx, 8);
    SD(ctx->f8.u64, 0X50, ctx->r29);
L_800D14F0:
    // 0x800D14F0: lw          $t3, 0x58($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X58);
    // 0x800D14F4: andi        $t6, $t3, 0x1
    ctx->r14 = ctx->r11 & 0X1;
    // 0x800D14F8: beq         $t6, $zero, L_800D1520
    if (ctx->r14 == 0) {
        // 0x800D14FC: nop
    
            goto L_800D1520;
    }
    // 0x800D14FC: nop

    // 0x800D1500: lw          $t8, 0x5C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X5C);
    // 0x800D1504: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800D1508: ldc1        $f6, 0x50($sp)
    CHECK_FR(ctx, 6);
    ctx->f6.u64 = LD(ctx->r29, 0X50);
    // 0x800D150C: sll         $t7, $t8, 3
    ctx->r15 = S32(ctx->r24 << 3);
    // 0x800D1510: addu        $at, $at, $t7
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800D1514: ldc1        $f10, -0x3830($at)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r1, -0X3830);
    // 0x800D1518: mul.d       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f10.d); 
    ctx->f16.d = MUL_D(ctx->f6.d, ctx->f10.d);
    // 0x800D151C: sdc1        $f16, 0x50($sp)
    CHECK_FR(ctx, 16);
    SD(ctx->f16.u64, 0X50, ctx->r29);
L_800D1520:
    // 0x800D1520: lw          $t0, 0x58($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X58);
    // 0x800D1524: lw          $t1, 0x5C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X5C);
    // 0x800D1528: sra         $t9, $t0, 1
    ctx->r25 = S32(SIGNED(ctx->r8) >> 1);
    // 0x800D152C: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x800D1530: sw          $t2, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r10;
    // 0x800D1534: bgtz        $t9, L_800D14F0
    if (SIGNED(ctx->r25) > 0) {
        // 0x800D1538: sw          $t9, 0x58($sp)
        MEM_W(0X58, ctx->r29) = ctx->r25;
            goto L_800D14F0;
    }
    // 0x800D1538: sw          $t9, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r25;
L_800D153C:
    // 0x800D153C: ldc1        $f18, 0x68($sp)
    CHECK_FR(ctx, 18);
    ctx->f18.u64 = LD(ctx->r29, 0X68);
    // 0x800D1540: ldc1        $f4, 0x50($sp)
    CHECK_FR(ctx, 4);
    ctx->f4.u64 = LD(ctx->r29, 0X50);
    // 0x800D1544: div.d       $f8, $f18, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.d); NAN_CHECK(ctx->f4.d); 
    ctx->f8.d = DIV_D(ctx->f18.d, ctx->f4.d);
    // 0x800D1548: sdc1        $f8, 0x68($sp)
    CHECK_FR(ctx, 8);
    SD(ctx->f8.u64, 0X68, ctx->r29);
L_800D154C:
    // 0x800D154C: lbu         $t4, 0x9F($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X9F);
    // 0x800D1550: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x800D1554: bne         $t4, $at, L_800D1568
    if (ctx->r12 != ctx->r1) {
        // 0x800D1558: nop
    
            goto L_800D1568;
    }
    // 0x800D1558: nop

    // 0x800D155C: lh          $s0, 0x62($sp)
    ctx->r16 = MEM_H(ctx->r29, 0X62);
    // 0x800D1560: b           L_800D156C
    // 0x800D1564: addiu       $s0, $s0, 0xA
    ctx->r16 = ADD32(ctx->r16, 0XA);
        goto L_800D156C;
    // 0x800D1564: addiu       $s0, $s0, 0xA
    ctx->r16 = ADD32(ctx->r16, 0XA);
L_800D1568:
    // 0x800D1568: addiu       $s0, $zero, 0x6
    ctx->r16 = ADD32(0, 0X6);
L_800D156C:
    // 0x800D156C: lw          $t5, 0x98($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X98);
    // 0x800D1570: lw          $t3, 0x24($t5)
    ctx->r11 = MEM_W(ctx->r13, 0X24);
    // 0x800D1574: addu        $t6, $s0, $t3
    ctx->r14 = ADD32(ctx->r16, ctx->r11);
    // 0x800D1578: sw          $t6, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r14;
    // 0x800D157C: lw          $t8, 0x4C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1580: slti        $at, $t8, 0x14
    ctx->r1 = SIGNED(ctx->r24) < 0X14 ? 1 : 0;
    // 0x800D1584: bne         $at, $zero, L_800D1594
    if (ctx->r1 != 0) {
        // 0x800D1588: nop
    
            goto L_800D1594;
    }
    // 0x800D1588: nop

    // 0x800D158C: addiu       $t7, $zero, 0x13
    ctx->r15 = ADD32(0, 0X13);
    // 0x800D1590: sw          $t7, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r15;
L_800D1594:
    // 0x800D1594: lw          $t1, 0x74($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X74);
    // 0x800D1598: addiu       $t0, $zero, 0x30
    ctx->r8 = ADD32(0, 0X30);
    // 0x800D159C: sb          $t0, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r8;
    // 0x800D15A0: lw          $t2, 0x74($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X74);
    // 0x800D15A4: lw          $t4, 0x4C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X4C);
    // 0x800D15A8: addiu       $t9, $t2, 0x1
    ctx->r25 = ADD32(ctx->r10, 0X1);
    // 0x800D15AC: blez        $t4, L_800D16E0
    if (SIGNED(ctx->r12) <= 0) {
        // 0x800D15B0: sw          $t9, 0x74($sp)
        MEM_W(0X74, ctx->r29) = ctx->r25;
            goto L_800D16E0;
    }
    // 0x800D15B0: sw          $t9, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r25;
    // 0x800D15B4: mtc1        $zero, $f7
    ctx->f_odd[(7 - 1) * 2] = 0;
    // 0x800D15B8: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x800D15BC: ldc1        $f10, 0x68($sp)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r29, 0X68);
    // 0x800D15C0: c.lt.d      $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f6.d < ctx->f10.d;
    // 0x800D15C4: nop

    // 0x800D15C8: bc1f        L_800D16E0
    if (!c1cs) {
        // 0x800D15CC: nop
    
            goto L_800D16E0;
    }
    // 0x800D15CC: nop

L_800D15D0:
    // 0x800D15D0: ldc1        $f16, 0x68($sp)
    CHECK_FR(ctx, 16);
    ctx->f16.u64 = LD(ctx->r29, 0X68);
    // 0x800D15D4: lw          $t6, 0x4C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X4C);
    // 0x800D15D8: trunc.w.d   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_D(ctx->f16.d);
    // 0x800D15DC: addiu       $t8, $t6, -0x8
    ctx->r24 = ADD32(ctx->r14, -0X8);
    // 0x800D15E0: sw          $t8, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r24;
    // 0x800D15E4: mfc1        $t3, $f18
    ctx->r11 = (int32_t)ctx->f18.u32l;
    // 0x800D15E8: blez        $t8, L_800D160C
    if (SIGNED(ctx->r24) <= 0) {
        // 0x800D15EC: sw          $t3, 0x44($sp)
        MEM_W(0X44, ctx->r29) = ctx->r11;
            goto L_800D160C;
    }
    // 0x800D15EC: sw          $t3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r11;
    // 0x800D15F0: mtc1        $t3, $f4
    ctx->f4.u32l = ctx->r11;
    // 0x800D15F4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800D15F8: ldc1        $f10, -0x37D8($at)
    CHECK_FR(ctx, 10);
    ctx->f10.u64 = LD(ctx->r1, -0X37D8);
    // 0x800D15FC: cvt.d.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.d = CVT_D_W(ctx->f4.u32l);
    // 0x800D1600: sub.d       $f6, $f16, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.d); NAN_CHECK(ctx->f8.d); 
    ctx->f6.d = ctx->f16.d - ctx->f8.d;
    // 0x800D1604: mul.d       $f18, $f6, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.d); NAN_CHECK(ctx->f10.d); 
    ctx->f18.d = MUL_D(ctx->f6.d, ctx->f10.d);
    // 0x800D1608: sdc1        $f18, 0x68($sp)
    CHECK_FR(ctx, 18);
    SD(ctx->f18.u64, 0X68, ctx->r29);
L_800D160C:
    // 0x800D160C: lw          $t7, 0x74($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X74);
    // 0x800D1610: lw          $t2, 0x44($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X44);
    // 0x800D1614: addiu       $t1, $zero, 0x8
    ctx->r9 = ADD32(0, 0X8);
    // 0x800D1618: addiu       $t0, $t7, 0x8
    ctx->r8 = ADD32(ctx->r15, 0X8);
    // 0x800D161C: sw          $t0, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r8;
    // 0x800D1620: blez        $t2, L_800D167C
    if (SIGNED(ctx->r10) <= 0) {
        // 0x800D1624: sw          $t1, 0x48($sp)
        MEM_W(0X48, ctx->r29) = ctx->r9;
            goto L_800D167C;
    }
    // 0x800D1624: sw          $t1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r9;
    // 0x800D1628: addiu       $t9, $zero, 0x7
    ctx->r25 = ADD32(0, 0X7);
    // 0x800D162C: sw          $t9, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r25;
L_800D1630:
    // 0x800D1630: addiu       $a0, $sp, 0x3C
    ctx->r4 = ADD32(ctx->r29, 0X3C);
    // 0x800D1634: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x800D1638: jal         0x800D2220
    // 0x800D163C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    ldiv_recomp(rdram, ctx);
        goto after_2;
    // 0x800D163C: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_2:
    // 0x800D1640: lw          $t4, 0x74($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X74);
    // 0x800D1644: lw          $t6, 0x40($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X40);
    // 0x800D1648: addiu       $t5, $t4, -0x1
    ctx->r13 = ADD32(ctx->r12, -0X1);
    // 0x800D164C: sw          $t5, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r13;
    // 0x800D1650: addiu       $t8, $t6, 0x30
    ctx->r24 = ADD32(ctx->r14, 0X30);
    // 0x800D1654: sb          $t8, 0x0($t5)
    MEM_B(0X0, ctx->r13) = ctx->r24;
    // 0x800D1658: lw          $t3, 0x3C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X3C);
    // 0x800D165C: sw          $t3, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r11;
    // 0x800D1660: lw          $t7, 0x44($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X44);
    // 0x800D1664: blez        $t7, L_800D167C
    if (SIGNED(ctx->r15) <= 0) {
        // 0x800D1668: nop
    
            goto L_800D167C;
    }
    // 0x800D1668: nop

    // 0x800D166C: lw          $t0, 0x48($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X48);
    // 0x800D1670: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x800D1674: bgez        $t1, L_800D1630
    if (SIGNED(ctx->r9) >= 0) {
        // 0x800D1678: sw          $t1, 0x48($sp)
        MEM_W(0X48, ctx->r29) = ctx->r9;
            goto L_800D1630;
    }
    // 0x800D1678: sw          $t1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r9;
L_800D167C:
    // 0x800D167C: lw          $t2, 0x48($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X48);
    // 0x800D1680: addiu       $t9, $t2, -0x1
    ctx->r25 = ADD32(ctx->r10, -0X1);
    // 0x800D1684: bltz        $t9, L_800D16B0
    if (SIGNED(ctx->r25) < 0) {
        // 0x800D1688: sw          $t9, 0x48($sp)
        MEM_W(0X48, ctx->r29) = ctx->r25;
            goto L_800D16B0;
    }
    // 0x800D1688: sw          $t9, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r25;
L_800D168C:
    // 0x800D168C: lw          $t4, 0x74($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X74);
    // 0x800D1690: addiu       $t8, $zero, 0x30
    ctx->r24 = ADD32(0, 0X30);
    // 0x800D1694: addiu       $t6, $t4, -0x1
    ctx->r14 = ADD32(ctx->r12, -0X1);
    // 0x800D1698: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800D169C: sb          $t8, 0x0($t6)
    MEM_B(0X0, ctx->r14) = ctx->r24;
    // 0x800D16A0: lw          $t5, 0x48($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X48);
    // 0x800D16A4: addiu       $t3, $t5, -0x1
    ctx->r11 = ADD32(ctx->r13, -0X1);
    // 0x800D16A8: bgez        $t3, L_800D168C
    if (SIGNED(ctx->r11) >= 0) {
        // 0x800D16AC: sw          $t3, 0x48($sp)
        MEM_W(0X48, ctx->r29) = ctx->r11;
            goto L_800D168C;
    }
    // 0x800D16AC: sw          $t3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r11;
L_800D16B0:
    // 0x800D16B0: lw          $t7, 0x74($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X74);
    // 0x800D16B4: lw          $t1, 0x4C($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X4C);
    // 0x800D16B8: addiu       $t0, $t7, 0x8
    ctx->r8 = ADD32(ctx->r15, 0X8);
    // 0x800D16BC: blez        $t1, L_800D16E0
    if (SIGNED(ctx->r9) <= 0) {
        // 0x800D16C0: sw          $t0, 0x74($sp)
        MEM_W(0X74, ctx->r29) = ctx->r8;
            goto L_800D16E0;
    }
    // 0x800D16C0: sw          $t0, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r8;
    // 0x800D16C4: mtc1        $zero, $f5
    ctx->f_odd[(5 - 1) * 2] = 0;
    // 0x800D16C8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800D16CC: ldc1        $f16, 0x68($sp)
    CHECK_FR(ctx, 16);
    ctx->f16.u64 = LD(ctx->r29, 0X68);
    // 0x800D16D0: c.lt.d      $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f4.d < ctx->f16.d;
    // 0x800D16D4: nop

    // 0x800D16D8: bc1t        L_800D15D0
    if (c1cs) {
        // 0x800D16DC: nop
    
            goto L_800D15D0;
    }
    // 0x800D16DC: nop

L_800D16E0:
    // 0x800D16E0: lw          $t2, 0x74($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X74);
    // 0x800D16E4: lh          $t5, 0x62($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X62);
    // 0x800D16E8: addiu       $t9, $sp, 0x78
    ctx->r25 = ADD32(ctx->r29, 0X78);
    // 0x800D16EC: subu        $t4, $t2, $t9
    ctx->r12 = SUB32(ctx->r10, ctx->r25);
    // 0x800D16F0: addiu       $t8, $t4, -0x1
    ctx->r24 = ADD32(ctx->r12, -0X1);
    // 0x800D16F4: addiu       $t6, $t9, 0x1
    ctx->r14 = ADD32(ctx->r25, 0X1);
    // 0x800D16F8: addiu       $t3, $t5, 0x7
    ctx->r11 = ADD32(ctx->r13, 0X7);
    // 0x800D16FC: sw          $t8, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r24;
    // 0x800D1700: sh          $t3, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r11;
    // 0x800D1704: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800D1708: lbu         $t7, 0x1($t9)
    ctx->r15 = MEM_BU(ctx->r25, 0X1);
    // 0x800D170C: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x800D1710: bne         $t7, $at, L_800D174C
    if (ctx->r15 != ctx->r1) {
        // 0x800D1714: nop
    
            goto L_800D174C;
    }
    // 0x800D1714: nop

L_800D1718:
    // 0x800D1718: lw          $t8, 0x74($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X74);
    // 0x800D171C: lw          $t0, 0x4C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1720: lh          $t2, 0x62($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X62);
    // 0x800D1724: addiu       $t6, $t8, 0x1
    ctx->r14 = ADD32(ctx->r24, 0X1);
    // 0x800D1728: addiu       $t1, $t0, -0x1
    ctx->r9 = ADD32(ctx->r8, -0X1);
    // 0x800D172C: addiu       $t4, $t2, -0x1
    ctx->r12 = ADD32(ctx->r10, -0X1);
    // 0x800D1730: sw          $t6, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r14;
    // 0x800D1734: sh          $t4, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r12;
    // 0x800D1738: sw          $t1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r9;
    // 0x800D173C: lbu         $t5, 0x0($t6)
    ctx->r13 = MEM_BU(ctx->r14, 0X0);
    // 0x800D1740: addiu       $at, $zero, 0x30
    ctx->r1 = ADD32(0, 0X30);
    // 0x800D1744: beq         $t5, $at, L_800D1718
    if (ctx->r13 == ctx->r1) {
        // 0x800D1748: nop
    
            goto L_800D1718;
    }
    // 0x800D1748: nop

L_800D174C:
    // 0x800D174C: lbu         $t3, 0x9F($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X9F);
    // 0x800D1750: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x800D1754: bne         $t3, $at, L_800D1768
    if (ctx->r11 != ctx->r1) {
        // 0x800D1758: nop
    
            goto L_800D1768;
    }
    // 0x800D1758: nop

    // 0x800D175C: lh          $s0, 0x62($sp)
    ctx->r16 = MEM_H(ctx->r29, 0X62);
    // 0x800D1760: b           L_800D1790
    // 0x800D1764: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
        goto L_800D1790;
    // 0x800D1764: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_800D1768:
    // 0x800D1768: lbu         $t9, 0x9F($sp)
    ctx->r25 = MEM_BU(ctx->r29, 0X9F);
    // 0x800D176C: addiu       $at, $zero, 0x65
    ctx->r1 = ADD32(0, 0X65);
    // 0x800D1770: beq         $t9, $at, L_800D1780
    if (ctx->r25 == ctx->r1) {
        // 0x800D1774: addiu       $at, $zero, 0x45
        ctx->r1 = ADD32(0, 0X45);
            goto L_800D1780;
    }
    // 0x800D1774: addiu       $at, $zero, 0x45
    ctx->r1 = ADD32(0, 0X45);
    // 0x800D1778: bne         $t9, $at, L_800D1788
    if (ctx->r25 != ctx->r1) {
        // 0x800D177C: nop
    
            goto L_800D1788;
    }
    // 0x800D177C: nop

L_800D1780:
    // 0x800D1780: b           L_800D178C
    // 0x800D1784: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
        goto L_800D178C;
    // 0x800D1784: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
L_800D1788:
    // 0x800D1788: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
L_800D178C:
    // 0x800D178C: or          $s0, $s1, $zero
    ctx->r16 = ctx->r17 | 0;
L_800D1790:
    // 0x800D1790: lw          $t7, 0x98($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X98);
    // 0x800D1794: lw          $t2, 0x4C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X4C);
    // 0x800D1798: lw          $t0, 0x24($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X24);
    // 0x800D179C: addu        $t1, $s0, $t0
    ctx->r9 = ADD32(ctx->r16, ctx->r8);
    // 0x800D17A0: sh          $t1, 0x64($sp)
    MEM_H(0X64, ctx->r29) = ctx->r9;
    // 0x800D17A4: lh          $t4, 0x64($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X64);
    // 0x800D17A8: slt         $at, $t2, $t4
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r12) ? 1 : 0;
    // 0x800D17AC: beq         $at, $zero, L_800D17B8
    if (ctx->r1 == 0) {
        // 0x800D17B0: nop
    
            goto L_800D17B8;
    }
    // 0x800D17B0: nop

    // 0x800D17B4: sh          $t2, 0x64($sp)
    MEM_H(0X64, ctx->r29) = ctx->r10;
L_800D17B8:
    // 0x800D17B8: lh          $t8, 0x64($sp)
    ctx->r24 = MEM_H(ctx->r29, 0X64);
    // 0x800D17BC: blez        $t8, L_800D18B0
    if (SIGNED(ctx->r24) <= 0) {
        // 0x800D17C0: nop
    
            goto L_800D18B0;
    }
    // 0x800D17C0: nop

    // 0x800D17C4: lw          $t6, 0x4C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X4C);
    // 0x800D17C8: slt         $at, $t8, $t6
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x800D17CC: beq         $at, $zero, L_800D17F8
    if (ctx->r1 == 0) {
        // 0x800D17D0: nop
    
            goto L_800D17F8;
    }
    // 0x800D17D0: nop

    // 0x800D17D4: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800D17D8: addu        $t3, $t8, $t5
    ctx->r11 = ADD32(ctx->r24, ctx->r13);
    // 0x800D17DC: lbu         $t9, 0x0($t3)
    ctx->r25 = MEM_BU(ctx->r11, 0X0);
    // 0x800D17E0: slti        $at, $t9, 0x35
    ctx->r1 = SIGNED(ctx->r25) < 0X35 ? 1 : 0;
    // 0x800D17E4: bne         $at, $zero, L_800D17F8
    if (ctx->r1 != 0) {
        // 0x800D17E8: nop
    
            goto L_800D17F8;
    }
    // 0x800D17E8: nop

    // 0x800D17EC: addiu       $t7, $zero, 0x39
    ctx->r15 = ADD32(0, 0X39);
    // 0x800D17F0: b           L_800D1800
    // 0x800D17F4: sb          $t7, 0x3B($sp)
    MEM_B(0X3B, ctx->r29) = ctx->r15;
        goto L_800D1800;
    // 0x800D17F4: sb          $t7, 0x3B($sp)
    MEM_B(0X3B, ctx->r29) = ctx->r15;
L_800D17F8:
    // 0x800D17F8: addiu       $t0, $zero, 0x30
    ctx->r8 = ADD32(0, 0X30);
    // 0x800D17FC: sb          $t0, 0x3B($sp)
    MEM_B(0X3B, ctx->r29) = ctx->r8;
L_800D1800:
    // 0x800D1800: lh          $t1, 0x64($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X64);
    // 0x800D1804: lw          $t2, 0x74($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X74);
    // 0x800D1808: lbu         $t5, 0x3B($sp)
    ctx->r13 = MEM_BU(ctx->r29, 0X3B);
    // 0x800D180C: addiu       $t4, $t1, -0x1
    ctx->r12 = ADD32(ctx->r9, -0X1);
    // 0x800D1810: sw          $t1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r9;
    // 0x800D1814: sw          $t4, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r12;
    // 0x800D1818: addu        $t6, $t4, $t2
    ctx->r14 = ADD32(ctx->r12, ctx->r10);
    // 0x800D181C: lbu         $t8, 0x0($t6)
    ctx->r24 = MEM_BU(ctx->r14, 0X0);
    // 0x800D1820: bne         $t8, $t5, L_800D1858
    if (ctx->r24 != ctx->r13) {
        // 0x800D1824: nop
    
            goto L_800D1858;
    }
    // 0x800D1824: nop

L_800D1828:
    // 0x800D1828: lw          $t7, 0x34($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X34);
    // 0x800D182C: lh          $t3, 0x64($sp)
    ctx->r11 = MEM_H(ctx->r29, 0X64);
    // 0x800D1830: lw          $t1, 0x74($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X74);
    // 0x800D1834: addiu       $t0, $t7, -0x1
    ctx->r8 = ADD32(ctx->r15, -0X1);
    // 0x800D1838: addiu       $t9, $t3, -0x1
    ctx->r25 = ADD32(ctx->r11, -0X1);
    // 0x800D183C: sw          $t0, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r8;
    // 0x800D1840: sh          $t9, 0x64($sp)
    MEM_H(0X64, ctx->r29) = ctx->r25;
    // 0x800D1844: addu        $t4, $t0, $t1
    ctx->r12 = ADD32(ctx->r8, ctx->r9);
    // 0x800D1848: lbu         $t2, 0x0($t4)
    ctx->r10 = MEM_BU(ctx->r12, 0X0);
    // 0x800D184C: lbu         $t6, 0x3B($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X3B);
    // 0x800D1850: beq         $t2, $t6, L_800D1828
    if (ctx->r10 == ctx->r14) {
        // 0x800D1854: nop
    
            goto L_800D1828;
    }
    // 0x800D1854: nop

L_800D1858:
    // 0x800D1858: lbu         $t8, 0x3B($sp)
    ctx->r24 = MEM_BU(ctx->r29, 0X3B);
    // 0x800D185C: addiu       $at, $zero, 0x39
    ctx->r1 = ADD32(0, 0X39);
    // 0x800D1860: bne         $t8, $at, L_800D1880
    if (ctx->r24 != ctx->r1) {
        // 0x800D1864: nop
    
            goto L_800D1880;
    }
    // 0x800D1864: nop

    // 0x800D1868: lw          $t5, 0x74($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X74);
    // 0x800D186C: lw          $t3, 0x34($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X34);
    // 0x800D1870: addu        $t9, $t5, $t3
    ctx->r25 = ADD32(ctx->r13, ctx->r11);
    // 0x800D1874: lbu         $t7, 0x0($t9)
    ctx->r15 = MEM_BU(ctx->r25, 0X0);
    // 0x800D1878: addiu       $t0, $t7, 0x1
    ctx->r8 = ADD32(ctx->r15, 0X1);
    // 0x800D187C: sb          $t0, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r8;
L_800D1880:
    // 0x800D1880: lw          $t1, 0x34($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X34);
    // 0x800D1884: bgez        $t1, L_800D18B0
    if (SIGNED(ctx->r9) >= 0) {
        // 0x800D1888: nop
    
            goto L_800D18B0;
    }
    // 0x800D1888: nop

    // 0x800D188C: lw          $t4, 0x74($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X74);
    // 0x800D1890: lh          $t6, 0x64($sp)
    ctx->r14 = MEM_H(ctx->r29, 0X64);
    // 0x800D1894: lh          $t5, 0x62($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X62);
    // 0x800D1898: addiu       $t2, $t4, -0x1
    ctx->r10 = ADD32(ctx->r12, -0X1);
    // 0x800D189C: addiu       $t8, $t6, 0x1
    ctx->r24 = ADD32(ctx->r14, 0X1);
    // 0x800D18A0: addiu       $t3, $t5, 0x1
    ctx->r11 = ADD32(ctx->r13, 0X1);
    // 0x800D18A4: sh          $t3, 0x62($sp)
    MEM_H(0X62, ctx->r29) = ctx->r11;
    // 0x800D18A8: sh          $t8, 0x64($sp)
    MEM_H(0X64, ctx->r29) = ctx->r24;
    // 0x800D18AC: sw          $t2, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r10;
L_800D18B0:
    // 0x800D18B0: lh          $t7, 0x62($sp)
    ctx->r15 = MEM_H(ctx->r29, 0X62);
    // 0x800D18B4: lw          $a0, 0x98($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X98);
    // 0x800D18B8: lbu         $a1, 0x9F($sp)
    ctx->r5 = MEM_BU(ctx->r29, 0X9F);
    // 0x800D18BC: lw          $a2, 0x74($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X74);
    // 0x800D18C0: lh          $a3, 0x64($sp)
    ctx->r7 = MEM_H(ctx->r29, 0X64);
    // 0x800D18C4: jal         0x800D19C0
    // 0x800D18C8: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    xldtob_text_06E0(rdram, ctx);
        goto after_3;
    // 0x800D18C8: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_3:
L_800D18CC:
    // 0x800D18CC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800D18D0: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800D18D4: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800D18D8: jr          $ra
    // 0x800D18DC: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
    return;
    // 0x800D18DC: addiu       $sp, $sp, 0x98
    ctx->r29 = ADD32(ctx->r29, 0X98);
;}
RECOMP_FUNC void xldtob_text_0600(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D18E0: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x800D18E4: sw          $a1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r5;
    // 0x800D18E8: lw          $t6, 0xC($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XC);
    // 0x800D18EC: addiu       $at, $zero, 0x7FF
    ctx->r1 = ADD32(0, 0X7FF);
    // 0x800D18F0: lhu         $t7, 0x0($t6)
    ctx->r15 = MEM_HU(ctx->r14, 0X0);
    // 0x800D18F4: andi        $t8, $t7, 0x7FF0
    ctx->r24 = ctx->r15 & 0X7FF0;
    // 0x800D18F8: sra         $t9, $t8, 4
    ctx->r25 = S32(SIGNED(ctx->r24) >> 4);
    // 0x800D18FC: sll         $t0, $t9, 16
    ctx->r8 = S32(ctx->r25 << 16);
    // 0x800D1900: sra         $t1, $t0, 16
    ctx->r9 = S32(SIGNED(ctx->r8) >> 16);
    // 0x800D1904: bne         $t1, $at, L_800D1964
    if (ctx->r9 != ctx->r1) {
        // 0x800D1908: sh          $t9, 0xA($sp)
        MEM_H(0XA, ctx->r29) = ctx->r25;
            goto L_800D1964;
    }
    // 0x800D1908: sh          $t9, 0xA($sp)
    MEM_H(0XA, ctx->r29) = ctx->r25;
    // 0x800D190C: sh          $zero, 0x0($a0)
    MEM_H(0X0, ctx->r4) = 0;
    // 0x800D1910: lw          $t2, 0xC($sp)
    ctx->r10 = MEM_W(ctx->r29, 0XC);
    // 0x800D1914: lhu         $t3, 0x0($t2)
    ctx->r11 = MEM_HU(ctx->r10, 0X0);
    // 0x800D1918: andi        $t4, $t3, 0xF
    ctx->r12 = ctx->r11 & 0XF;
    // 0x800D191C: bne         $t4, $zero, L_800D1948
    if (ctx->r12 != 0) {
        // 0x800D1920: nop
    
            goto L_800D1948;
    }
    // 0x800D1920: nop

    // 0x800D1924: lhu         $t5, 0x2($t2)
    ctx->r13 = MEM_HU(ctx->r10, 0X2);
    // 0x800D1928: bne         $t5, $zero, L_800D1948
    if (ctx->r13 != 0) {
        // 0x800D192C: nop
    
            goto L_800D1948;
    }
    // 0x800D192C: nop

    // 0x800D1930: lhu         $t6, 0x4($t2)
    ctx->r14 = MEM_HU(ctx->r10, 0X4);
    // 0x800D1934: bne         $t6, $zero, L_800D1948
    if (ctx->r14 != 0) {
        // 0x800D1938: nop
    
            goto L_800D1948;
    }
    // 0x800D1938: nop

    // 0x800D193C: lhu         $t7, 0x6($t2)
    ctx->r15 = MEM_HU(ctx->r10, 0X6);
    // 0x800D1940: beq         $t7, $zero, L_800D1950
    if (ctx->r15 == 0) {
        // 0x800D1944: nop
    
            goto L_800D1950;
    }
    // 0x800D1944: nop

L_800D1948:
    // 0x800D1948: b           L_800D1954
    // 0x800D194C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
        goto L_800D1954;
    // 0x800D194C: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
L_800D1950:
    // 0x800D1950: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_800D1954:
    // 0x800D1954: sll         $v0, $a2, 16
    ctx->r2 = S32(ctx->r6 << 16);
    // 0x800D1958: sra         $t8, $v0, 16
    ctx->r24 = S32(SIGNED(ctx->r2) >> 16);
    // 0x800D195C: b           L_800D19B8
    // 0x800D1960: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
        goto L_800D19B8;
    // 0x800D1960: or          $v0, $t8, $zero
    ctx->r2 = ctx->r24 | 0;
L_800D1964:
    // 0x800D1964: lh          $t9, 0xA($sp)
    ctx->r25 = MEM_H(ctx->r29, 0XA);
    // 0x800D1968: blez        $t9, L_800D199C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x800D196C: nop
    
            goto L_800D199C;
    }
    // 0x800D196C: nop

    // 0x800D1970: lw          $t0, 0xC($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XC);
    // 0x800D1974: addiu       $at, $zero, -0x7FF1
    ctx->r1 = ADD32(0, -0X7FF1);
    // 0x800D1978: addiu       $v0, $zero, -0x1
    ctx->r2 = ADD32(0, -0X1);
    // 0x800D197C: lhu         $t1, 0x0($t0)
    ctx->r9 = MEM_HU(ctx->r8, 0X0);
    // 0x800D1980: and         $t3, $t1, $at
    ctx->r11 = ctx->r9 & ctx->r1;
    // 0x800D1984: ori         $t4, $t3, 0x3FF0
    ctx->r12 = ctx->r11 | 0X3FF0;
    // 0x800D1988: sh          $t4, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r12;
    // 0x800D198C: lh          $t5, 0xA($sp)
    ctx->r13 = MEM_H(ctx->r29, 0XA);
    // 0x800D1990: addiu       $t6, $t5, -0x3FE
    ctx->r14 = ADD32(ctx->r13, -0X3FE);
    // 0x800D1994: b           L_800D19B8
    // 0x800D1998: sh          $t6, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r14;
        goto L_800D19B8;
    // 0x800D1998: sh          $t6, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r14;
L_800D199C:
    // 0x800D199C: lh          $t2, 0xA($sp)
    ctx->r10 = MEM_H(ctx->r29, 0XA);
    // 0x800D19A0: bgez        $t2, L_800D19B0
    if (SIGNED(ctx->r10) >= 0) {
        // 0x800D19A4: nop
    
            goto L_800D19B0;
    }
    // 0x800D19A4: nop

    // 0x800D19A8: b           L_800D19B8
    // 0x800D19AC: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
        goto L_800D19B8;
    // 0x800D19AC: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
L_800D19B0:
    // 0x800D19B0: sh          $zero, 0x0($a0)
    MEM_H(0X0, ctx->r4) = 0;
    // 0x800D19B4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800D19B8:
    // 0x800D19B8: jr          $ra
    // 0x800D19BC: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x800D19BC: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
;}
RECOMP_FUNC void xldtob_text_06E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D19C0: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800D19C4: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    // 0x800D19C8: lh          $t7, 0x3E($sp)
    ctx->r15 = MEM_H(ctx->r29, 0X3E);
    // 0x800D19CC: addiu       $t6, $zero, 0x2E
    ctx->r14 = ADD32(0, 0X2E);
    // 0x800D19D0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800D19D4: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x800D19D8: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x800D19DC: sw          $a2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r6;
    // 0x800D19E0: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800D19E4: bgtz        $t7, L_800D1A00
    if (SIGNED(ctx->r15) > 0) {
        // 0x800D19E8: sb          $t6, 0x2F($sp)
        MEM_B(0X2F, ctx->r29) = ctx->r14;
            goto L_800D1A00;
    }
    // 0x800D19E8: sb          $t6, 0x2F($sp)
    MEM_B(0X2F, ctx->r29) = ctx->r14;
    // 0x800D19EC: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800D19F0: addiu       $t9, $t9, -0x37E0
    ctx->r25 = ADD32(ctx->r25, -0X37E0);
    // 0x800D19F4: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800D19F8: sh          $t8, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r24;
    // 0x800D19FC: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
L_800D1A00:
    // 0x800D1A00: lbu         $t0, 0x37($sp)
    ctx->r8 = MEM_BU(ctx->r29, 0X37);
    // 0x800D1A04: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x800D1A08: beq         $t0, $at, L_800D1A44
    if (ctx->r8 == ctx->r1) {
        // 0x800D1A0C: addiu       $at, $zero, 0x67
        ctx->r1 = ADD32(0, 0X67);
            goto L_800D1A44;
    }
    // 0x800D1A0C: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x800D1A10: beq         $t0, $at, L_800D1A20
    if (ctx->r8 == ctx->r1) {
        // 0x800D1A14: addiu       $at, $zero, 0x47
        ctx->r1 = ADD32(0, 0X47);
            goto L_800D1A20;
    }
    // 0x800D1A14: addiu       $at, $zero, 0x47
    ctx->r1 = ADD32(0, 0X47);
    // 0x800D1A18: bne         $t0, $at, L_800D1D70
    if (ctx->r8 != ctx->r1) {
        // 0x800D1A1C: nop
    
            goto L_800D1D70;
    }
    // 0x800D1A1C: nop

L_800D1A20:
    // 0x800D1A20: lh          $t1, 0x42($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X42);
    // 0x800D1A24: slti        $at, $t1, -0x4
    ctx->r1 = SIGNED(ctx->r9) < -0X4 ? 1 : 0;
    // 0x800D1A28: bne         $at, $zero, L_800D1D70
    if (ctx->r1 != 0) {
        // 0x800D1A2C: nop
    
            goto L_800D1D70;
    }
    // 0x800D1A2C: nop

    // 0x800D1A30: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800D1A34: lw          $t3, 0x24($t2)
    ctx->r11 = MEM_W(ctx->r10, 0X24);
    // 0x800D1A38: slt         $at, $t1, $t3
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x800D1A3C: beq         $at, $zero, L_800D1D70
    if (ctx->r1 == 0) {
        // 0x800D1A40: nop
    
            goto L_800D1D70;
    }
    // 0x800D1A40: nop

L_800D1A44:
    // 0x800D1A44: lh          $t4, 0x42($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X42);
    // 0x800D1A48: lbu         $t6, 0x37($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X37);
    // 0x800D1A4C: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x800D1A50: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x800D1A54: beq         $t6, $at, L_800D1AB0
    if (ctx->r14 == ctx->r1) {
        // 0x800D1A58: sh          $t5, 0x42($sp)
        MEM_H(0X42, ctx->r29) = ctx->r13;
            goto L_800D1AB0;
    }
    // 0x800D1A58: sh          $t5, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r13;
    // 0x800D1A5C: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800D1A60: lw          $t8, 0x30($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X30);
    // 0x800D1A64: andi        $t9, $t8, 0x8
    ctx->r25 = ctx->r24 & 0X8;
    // 0x800D1A68: bne         $t9, $zero, L_800D1A88
    if (ctx->r25 != 0) {
        // 0x800D1A6C: nop
    
            goto L_800D1A88;
    }
    // 0x800D1A6C: nop

    // 0x800D1A70: lh          $t0, 0x3E($sp)
    ctx->r8 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1A74: lw          $t2, 0x24($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X24);
    // 0x800D1A78: slt         $at, $t0, $t2
    ctx->r1 = SIGNED(ctx->r8) < SIGNED(ctx->r10) ? 1 : 0;
    // 0x800D1A7C: beq         $at, $zero, L_800D1A88
    if (ctx->r1 == 0) {
        // 0x800D1A80: nop
    
            goto L_800D1A88;
    }
    // 0x800D1A80: nop

    // 0x800D1A84: sw          $t0, 0x24($t7)
    MEM_W(0X24, ctx->r15) = ctx->r8;
L_800D1A88:
    // 0x800D1A88: lw          $t1, 0x30($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X30);
    // 0x800D1A8C: lh          $t4, 0x42($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X42);
    // 0x800D1A90: lw          $t3, 0x24($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X24);
    // 0x800D1A94: subu        $t5, $t3, $t4
    ctx->r13 = SUB32(ctx->r11, ctx->r12);
    // 0x800D1A98: sw          $t5, 0x24($t1)
    MEM_W(0X24, ctx->r9) = ctx->r13;
    // 0x800D1A9C: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1AA0: lw          $t8, 0x24($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X24);
    // 0x800D1AA4: bgez        $t8, L_800D1AB0
    if (SIGNED(ctx->r24) >= 0) {
        // 0x800D1AA8: nop
    
            goto L_800D1AB0;
    }
    // 0x800D1AA8: nop

    // 0x800D1AAC: sw          $zero, 0x24($t6)
    MEM_W(0X24, ctx->r14) = 0;
L_800D1AB0:
    // 0x800D1AB0: lh          $t9, 0x42($sp)
    ctx->r25 = MEM_H(ctx->r29, 0X42);
    // 0x800D1AB4: bgtz        $t9, L_800D1BCC
    if (SIGNED(ctx->r25) > 0) {
        // 0x800D1AB8: nop
    
            goto L_800D1BCC;
    }
    // 0x800D1AB8: nop

    // 0x800D1ABC: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1AC0: addiu       $t2, $zero, 0x30
    ctx->r10 = ADD32(0, 0X30);
    // 0x800D1AC4: lw          $t7, 0x8($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X8);
    // 0x800D1AC8: lw          $t3, 0x14($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X14);
    // 0x800D1ACC: addu        $t4, $t7, $t3
    ctx->r12 = ADD32(ctx->r15, ctx->r11);
    // 0x800D1AD0: sb          $t2, 0x0($t4)
    MEM_B(0X0, ctx->r12) = ctx->r10;
    // 0x800D1AD4: lw          $t5, 0x30($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X30);
    // 0x800D1AD8: lw          $t1, 0x14($t5)
    ctx->r9 = MEM_W(ctx->r13, 0X14);
    // 0x800D1ADC: addiu       $t8, $t1, 0x1
    ctx->r24 = ADD32(ctx->r9, 0X1);
    // 0x800D1AE0: sw          $t8, 0x14($t5)
    MEM_W(0X14, ctx->r13) = ctx->r24;
    // 0x800D1AE4: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1AE8: lw          $t9, 0x24($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X24);
    // 0x800D1AEC: bgtz        $t9, L_800D1B04
    if (SIGNED(ctx->r25) > 0) {
        // 0x800D1AF0: nop
    
            goto L_800D1B04;
    }
    // 0x800D1AF0: nop

    // 0x800D1AF4: lw          $t0, 0x30($t6)
    ctx->r8 = MEM_W(ctx->r14, 0X30);
    // 0x800D1AF8: andi        $t7, $t0, 0x8
    ctx->r15 = ctx->r8 & 0X8;
    // 0x800D1AFC: beq         $t7, $zero, L_800D1B2C
    if (ctx->r15 == 0) {
        // 0x800D1B00: nop
    
            goto L_800D1B2C;
    }
    // 0x800D1B00: nop

L_800D1B04:
    // 0x800D1B04: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B08: lbu         $t3, 0x2F($sp)
    ctx->r11 = MEM_BU(ctx->r29, 0X2F);
    // 0x800D1B0C: lw          $t4, 0x8($t2)
    ctx->r12 = MEM_W(ctx->r10, 0X8);
    // 0x800D1B10: lw          $t1, 0x14($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X14);
    // 0x800D1B14: addu        $t8, $t4, $t1
    ctx->r24 = ADD32(ctx->r12, ctx->r9);
    // 0x800D1B18: sb          $t3, 0x0($t8)
    MEM_B(0X0, ctx->r24) = ctx->r11;
    // 0x800D1B1C: lw          $t5, 0x30($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B20: lw          $t9, 0x14($t5)
    ctx->r25 = MEM_W(ctx->r13, 0X14);
    // 0x800D1B24: addiu       $t6, $t9, 0x1
    ctx->r14 = ADD32(ctx->r25, 0X1);
    // 0x800D1B28: sw          $t6, 0x14($t5)
    MEM_W(0X14, ctx->r13) = ctx->r14;
L_800D1B2C:
    // 0x800D1B2C: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B30: lh          $t2, 0x42($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X42);
    // 0x800D1B34: lw          $t7, 0x24($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X24);
    // 0x800D1B38: negu        $t4, $t2
    ctx->r12 = SUB32(0, ctx->r10);
    // 0x800D1B3C: slt         $at, $t7, $t4
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r12) ? 1 : 0;
    // 0x800D1B40: beq         $at, $zero, L_800D1B50
    if (ctx->r1 == 0) {
        // 0x800D1B44: nop
    
            goto L_800D1B50;
    }
    // 0x800D1B44: nop

    // 0x800D1B48: negu        $t1, $t7
    ctx->r9 = SUB32(0, ctx->r15);
    // 0x800D1B4C: sh          $t1, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r9;
L_800D1B50:
    // 0x800D1B50: lh          $t3, 0x42($sp)
    ctx->r11 = MEM_H(ctx->r29, 0X42);
    // 0x800D1B54: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B58: negu        $t8, $t3
    ctx->r24 = SUB32(0, ctx->r11);
    // 0x800D1B5C: sw          $t8, 0x18($t9)
    MEM_W(0X18, ctx->r25) = ctx->r24;
    // 0x800D1B60: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B64: lh          $t0, 0x42($sp)
    ctx->r8 = MEM_H(ctx->r29, 0X42);
    // 0x800D1B68: lw          $t5, 0x24($t6)
    ctx->r13 = MEM_W(ctx->r14, 0X24);
    // 0x800D1B6C: addu        $t2, $t5, $t0
    ctx->r10 = ADD32(ctx->r13, ctx->r8);
    // 0x800D1B70: sw          $t2, 0x24($t6)
    MEM_W(0X24, ctx->r14) = ctx->r10;
    // 0x800D1B74: lw          $t4, 0x30($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B78: lh          $t1, 0x3E($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1B7C: lw          $t7, 0x24($t4)
    ctx->r15 = MEM_W(ctx->r12, 0X24);
    // 0x800D1B80: slt         $at, $t7, $t1
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x800D1B84: beq         $at, $zero, L_800D1B90
    if (ctx->r1 == 0) {
        // 0x800D1B88: nop
    
            goto L_800D1B90;
    }
    // 0x800D1B88: nop

    // 0x800D1B8C: sh          $t7, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r15;
L_800D1B90:
    // 0x800D1B90: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1B94: lh          $s0, 0x3E($sp)
    ctx->r16 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1B98: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x800D1B9C: lw          $t8, 0x8($t3)
    ctx->r24 = MEM_W(ctx->r11, 0X8);
    // 0x800D1BA0: lw          $t9, 0x14($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X14);
    // 0x800D1BA4: sw          $s0, 0x1C($t3)
    MEM_W(0X1C, ctx->r11) = ctx->r16;
    // 0x800D1BA8: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x800D1BAC: jal         0x800D04C0
    // 0x800D1BB0: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    memcpy_recomp(rdram, ctx);
        goto after_0;
    // 0x800D1BB0: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    after_0:
    // 0x800D1BB4: lw          $t5, 0x30($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X30);
    // 0x800D1BB8: lh          $t2, 0x3E($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1BBC: lw          $t0, 0x24($t5)
    ctx->r8 = MEM_W(ctx->r13, 0X24);
    // 0x800D1BC0: subu        $t6, $t0, $t2
    ctx->r14 = SUB32(ctx->r8, ctx->r10);
    // 0x800D1BC4: b           L_800D2040
    // 0x800D1BC8: sw          $t6, 0x20($t5)
    MEM_W(0X20, ctx->r13) = ctx->r14;
        goto L_800D2040;
    // 0x800D1BC8: sw          $t6, 0x20($t5)
    MEM_W(0X20, ctx->r13) = ctx->r14;
L_800D1BCC:
    // 0x800D1BCC: lh          $t4, 0x3E($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1BD0: lh          $t1, 0x42($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X42);
    // 0x800D1BD4: slt         $at, $t4, $t1
    ctx->r1 = SIGNED(ctx->r12) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x800D1BD8: beq         $at, $zero, L_800D1C7C
    if (ctx->r1 == 0) {
        // 0x800D1BDC: nop
    
            goto L_800D1C7C;
    }
    // 0x800D1BDC: nop

    // 0x800D1BE0: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800D1BE4: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x800D1BE8: or          $a2, $t4, $zero
    ctx->r6 = ctx->r12 | 0;
    // 0x800D1BEC: lw          $t8, 0x8($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X8);
    // 0x800D1BF0: lw          $t9, 0x14($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X14);
    // 0x800D1BF4: jal         0x800D04C0
    // 0x800D1BF8: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    memcpy_recomp(rdram, ctx);
        goto after_1;
    // 0x800D1BF8: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    after_1:
    // 0x800D1BFC: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C00: lh          $t2, 0x3E($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1C04: lw          $t0, 0x14($t3)
    ctx->r8 = MEM_W(ctx->r11, 0X14);
    // 0x800D1C08: addu        $t6, $t0, $t2
    ctx->r14 = ADD32(ctx->r8, ctx->r10);
    // 0x800D1C0C: sw          $t6, 0x14($t3)
    MEM_W(0X14, ctx->r11) = ctx->r14;
    // 0x800D1C10: lh          $t1, 0x3E($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1C14: lh          $t5, 0x42($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X42);
    // 0x800D1C18: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C1C: subu        $t7, $t5, $t1
    ctx->r15 = SUB32(ctx->r13, ctx->r9);
    // 0x800D1C20: sw          $t7, 0x18($t8)
    MEM_W(0X18, ctx->r24) = ctx->r15;
    // 0x800D1C24: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C28: lw          $t4, 0x24($t9)
    ctx->r12 = MEM_W(ctx->r25, 0X24);
    // 0x800D1C2C: bgtz        $t4, L_800D1C44
    if (SIGNED(ctx->r12) > 0) {
        // 0x800D1C30: nop
    
            goto L_800D1C44;
    }
    // 0x800D1C30: nop

    // 0x800D1C34: lw          $t0, 0x30($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X30);
    // 0x800D1C38: andi        $t2, $t0, 0x8
    ctx->r10 = ctx->r8 & 0X8;
    // 0x800D1C3C: beq         $t2, $zero, L_800D1C6C
    if (ctx->r10 == 0) {
        // 0x800D1C40: nop
    
            goto L_800D1C6C;
    }
    // 0x800D1C40: nop

L_800D1C44:
    // 0x800D1C44: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C48: lbu         $t6, 0x2F($sp)
    ctx->r14 = MEM_BU(ctx->r29, 0X2F);
    // 0x800D1C4C: lw          $t5, 0x8($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X8);
    // 0x800D1C50: lw          $t1, 0x14($t3)
    ctx->r9 = MEM_W(ctx->r11, 0X14);
    // 0x800D1C54: addu        $t7, $t5, $t1
    ctx->r15 = ADD32(ctx->r13, ctx->r9);
    // 0x800D1C58: sb          $t6, 0x0($t7)
    MEM_B(0X0, ctx->r15) = ctx->r14;
    // 0x800D1C5C: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C60: lw          $t4, 0x1C($t8)
    ctx->r12 = MEM_W(ctx->r24, 0X1C);
    // 0x800D1C64: addiu       $t9, $t4, 0x1
    ctx->r25 = ADD32(ctx->r12, 0X1);
    // 0x800D1C68: sw          $t9, 0x1C($t8)
    MEM_W(0X1C, ctx->r24) = ctx->r25;
L_800D1C6C:
    // 0x800D1C6C: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C70: lw          $t2, 0x24($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X24);
    // 0x800D1C74: b           L_800D2040
    // 0x800D1C78: sw          $t2, 0x20($t0)
    MEM_W(0X20, ctx->r8) = ctx->r10;
        goto L_800D2040;
    // 0x800D1C78: sw          $t2, 0x20($t0)
    MEM_W(0X20, ctx->r8) = ctx->r10;
L_800D1C7C:
    // 0x800D1C7C: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C80: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x800D1C84: lh          $a2, 0x42($sp)
    ctx->r6 = MEM_H(ctx->r29, 0X42);
    // 0x800D1C88: lw          $t5, 0x8($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X8);
    // 0x800D1C8C: lw          $t1, 0x14($t3)
    ctx->r9 = MEM_W(ctx->r11, 0X14);
    // 0x800D1C90: jal         0x800D04C0
    // 0x800D1C94: addu        $a0, $t5, $t1
    ctx->r4 = ADD32(ctx->r13, ctx->r9);
    memcpy_recomp(rdram, ctx);
        goto after_2;
    // 0x800D1C94: addu        $a0, $t5, $t1
    ctx->r4 = ADD32(ctx->r13, ctx->r9);
    after_2:
    // 0x800D1C98: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1C9C: lh          $t4, 0x42($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X42);
    // 0x800D1CA0: lw          $t7, 0x14($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X14);
    // 0x800D1CA4: addu        $t9, $t7, $t4
    ctx->r25 = ADD32(ctx->r15, ctx->r12);
    // 0x800D1CA8: sw          $t9, 0x14($t6)
    MEM_W(0X14, ctx->r14) = ctx->r25;
    // 0x800D1CAC: lh          $t8, 0x3E($sp)
    ctx->r24 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1CB0: lh          $t2, 0x42($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X42);
    // 0x800D1CB4: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1CB8: subu        $t0, $t8, $t2
    ctx->r8 = SUB32(ctx->r24, ctx->r10);
    // 0x800D1CBC: sh          $t0, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r8;
    // 0x800D1CC0: lw          $t5, 0x24($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X24);
    // 0x800D1CC4: bgtz        $t5, L_800D1CDC
    if (SIGNED(ctx->r13) > 0) {
        // 0x800D1CC8: nop
    
            goto L_800D1CDC;
    }
    // 0x800D1CC8: nop

    // 0x800D1CCC: lw          $t1, 0x30($t3)
    ctx->r9 = MEM_W(ctx->r11, 0X30);
    // 0x800D1CD0: andi        $t7, $t1, 0x8
    ctx->r15 = ctx->r9 & 0X8;
    // 0x800D1CD4: beq         $t7, $zero, L_800D1D04
    if (ctx->r15 == 0) {
        // 0x800D1CD8: nop
    
            goto L_800D1D04;
    }
    // 0x800D1CD8: nop

L_800D1CDC:
    // 0x800D1CDC: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800D1CE0: lbu         $t4, 0x2F($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X2F);
    // 0x800D1CE4: lw          $t6, 0x8($t9)
    ctx->r14 = MEM_W(ctx->r25, 0X8);
    // 0x800D1CE8: lw          $t8, 0x14($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X14);
    // 0x800D1CEC: addu        $t2, $t6, $t8
    ctx->r10 = ADD32(ctx->r14, ctx->r24);
    // 0x800D1CF0: sb          $t4, 0x0($t2)
    MEM_B(0X0, ctx->r10) = ctx->r12;
    // 0x800D1CF4: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1CF8: lw          $t5, 0x14($t0)
    ctx->r13 = MEM_W(ctx->r8, 0X14);
    // 0x800D1CFC: addiu       $t3, $t5, 0x1
    ctx->r11 = ADD32(ctx->r13, 0X1);
    // 0x800D1D00: sw          $t3, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->r11;
L_800D1D04:
    // 0x800D1D04: lw          $t1, 0x30($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X30);
    // 0x800D1D08: lh          $t9, 0x3E($sp)
    ctx->r25 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1D0C: lw          $t7, 0x24($t1)
    ctx->r15 = MEM_W(ctx->r9, 0X24);
    // 0x800D1D10: slt         $at, $t7, $t9
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800D1D14: beq         $at, $zero, L_800D1D20
    if (ctx->r1 == 0) {
        // 0x800D1D18: nop
    
            goto L_800D1D20;
    }
    // 0x800D1D18: nop

    // 0x800D1D1C: sh          $t7, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r15;
L_800D1D20:
    // 0x800D1D20: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1D24: lh          $t2, 0x42($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X42);
    // 0x800D1D28: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800D1D2C: lw          $t8, 0x8($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X8);
    // 0x800D1D30: lw          $t4, 0x14($t6)
    ctx->r12 = MEM_W(ctx->r14, 0X14);
    // 0x800D1D34: lh          $a2, 0x3E($sp)
    ctx->r6 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1D38: addu        $a1, $t2, $t5
    ctx->r5 = ADD32(ctx->r10, ctx->r13);
    // 0x800D1D3C: jal         0x800D04C0
    // 0x800D1D40: addu        $a0, $t8, $t4
    ctx->r4 = ADD32(ctx->r24, ctx->r12);
    memcpy_recomp(rdram, ctx);
        goto after_3;
    // 0x800D1D40: addu        $a0, $t8, $t4
    ctx->r4 = ADD32(ctx->r24, ctx->r12);
    after_3:
    // 0x800D1D44: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1D48: lh          $t1, 0x3E($sp)
    ctx->r9 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1D4C: lw          $t0, 0x14($t3)
    ctx->r8 = MEM_W(ctx->r11, 0X14);
    // 0x800D1D50: addu        $t9, $t0, $t1
    ctx->r25 = ADD32(ctx->r8, ctx->r9);
    // 0x800D1D54: sw          $t9, 0x14($t3)
    MEM_W(0X14, ctx->r11) = ctx->r25;
    // 0x800D1D58: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800D1D5C: lh          $t8, 0x3E($sp)
    ctx->r24 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1D60: lw          $t6, 0x24($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X24);
    // 0x800D1D64: subu        $t4, $t6, $t8
    ctx->r12 = SUB32(ctx->r14, ctx->r24);
    // 0x800D1D68: b           L_800D2040
    // 0x800D1D6C: sw          $t4, 0x18($t7)
    MEM_W(0X18, ctx->r15) = ctx->r12;
        goto L_800D2040;
    // 0x800D1D6C: sw          $t4, 0x18($t7)
    MEM_W(0X18, ctx->r15) = ctx->r12;
L_800D1D70:
    // 0x800D1D70: lbu         $t2, 0x37($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X37);
    // 0x800D1D74: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x800D1D78: beq         $t2, $at, L_800D1D88
    if (ctx->r10 == ctx->r1) {
        // 0x800D1D7C: addiu       $at, $zero, 0x47
        ctx->r1 = ADD32(0, 0X47);
            goto L_800D1D88;
    }
    // 0x800D1D7C: addiu       $at, $zero, 0x47
    ctx->r1 = ADD32(0, 0X47);
    // 0x800D1D80: bne         $t2, $at, L_800D1DEC
    if (ctx->r10 != ctx->r1) {
        // 0x800D1D84: nop
    
            goto L_800D1DEC;
    }
    // 0x800D1D84: nop

L_800D1D88:
    // 0x800D1D88: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1D8C: lh          $t5, 0x3E($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1D90: lw          $t1, 0x24($t0)
    ctx->r9 = MEM_W(ctx->r8, 0X24);
    // 0x800D1D94: slt         $at, $t5, $t1
    ctx->r1 = SIGNED(ctx->r13) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x800D1D98: beq         $at, $zero, L_800D1DA4
    if (ctx->r1 == 0) {
        // 0x800D1D9C: nop
    
            goto L_800D1DA4;
    }
    // 0x800D1D9C: nop

    // 0x800D1DA0: sw          $t5, 0x24($t0)
    MEM_W(0X24, ctx->r8) = ctx->r13;
L_800D1DA4:
    // 0x800D1DA4: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800D1DA8: lw          $t3, 0x24($t9)
    ctx->r11 = MEM_W(ctx->r25, 0X24);
    // 0x800D1DAC: addiu       $t6, $t3, -0x1
    ctx->r14 = ADD32(ctx->r11, -0X1);
    // 0x800D1DB0: sw          $t6, 0x24($t9)
    MEM_W(0X24, ctx->r25) = ctx->r14;
    // 0x800D1DB4: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800D1DB8: lw          $t4, 0x24($t8)
    ctx->r12 = MEM_W(ctx->r24, 0X24);
    // 0x800D1DBC: bgez        $t4, L_800D1DC8
    if (SIGNED(ctx->r12) >= 0) {
        // 0x800D1DC0: nop
    
            goto L_800D1DC8;
    }
    // 0x800D1DC0: nop

    // 0x800D1DC4: sw          $zero, 0x24($t8)
    MEM_W(0X24, ctx->r24) = 0;
L_800D1DC8:
    // 0x800D1DC8: lbu         $t7, 0x37($sp)
    ctx->r15 = MEM_BU(ctx->r29, 0X37);
    // 0x800D1DCC: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x800D1DD0: bne         $t7, $at, L_800D1DE4
    if (ctx->r15 != ctx->r1) {
        // 0x800D1DD4: nop
    
            goto L_800D1DE4;
    }
    // 0x800D1DD4: nop

    // 0x800D1DD8: addiu       $t2, $zero, 0x65
    ctx->r10 = ADD32(0, 0X65);
    // 0x800D1DDC: b           L_800D1DEC
    // 0x800D1DE0: sb          $t2, 0x37($sp)
    MEM_B(0X37, ctx->r29) = ctx->r10;
        goto L_800D1DEC;
    // 0x800D1DE0: sb          $t2, 0x37($sp)
    MEM_B(0X37, ctx->r29) = ctx->r10;
L_800D1DE4:
    // 0x800D1DE4: addiu       $t1, $zero, 0x45
    ctx->r9 = ADD32(0, 0X45);
    // 0x800D1DE8: sb          $t1, 0x37($sp)
    MEM_B(0X37, ctx->r29) = ctx->r9;
L_800D1DEC:
    // 0x800D1DEC: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1DF0: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800D1DF4: lw          $t6, 0x8($t3)
    ctx->r14 = MEM_W(ctx->r11, 0X8);
    // 0x800D1DF8: lw          $t9, 0x14($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X14);
    // 0x800D1DFC: lbu         $t0, 0x0($t5)
    ctx->r8 = MEM_BU(ctx->r13, 0X0);
    // 0x800D1E00: addu        $t4, $t6, $t9
    ctx->r12 = ADD32(ctx->r14, ctx->r25);
    // 0x800D1E04: sb          $t0, 0x0($t4)
    MEM_B(0X0, ctx->r12) = ctx->r8;
    // 0x800D1E08: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800D1E0C: lw          $t7, 0x14($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X14);
    // 0x800D1E10: addiu       $t2, $t7, 0x1
    ctx->r10 = ADD32(ctx->r15, 0X1);
    // 0x800D1E14: sw          $t2, 0x14($t8)
    MEM_W(0X14, ctx->r24) = ctx->r10;
    // 0x800D1E18: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800D1E1C: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1E20: addiu       $t5, $t1, 0x1
    ctx->r13 = ADD32(ctx->r9, 0X1);
    // 0x800D1E24: sw          $t5, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r13;
    // 0x800D1E28: lw          $t6, 0x24($t3)
    ctx->r14 = MEM_W(ctx->r11, 0X24);
    // 0x800D1E2C: bgtz        $t6, L_800D1E44
    if (SIGNED(ctx->r14) > 0) {
        // 0x800D1E30: nop
    
            goto L_800D1E44;
    }
    // 0x800D1E30: nop

    // 0x800D1E34: lw          $t9, 0x30($t3)
    ctx->r25 = MEM_W(ctx->r11, 0X30);
    // 0x800D1E38: andi        $t0, $t9, 0x8
    ctx->r8 = ctx->r25 & 0X8;
    // 0x800D1E3C: beq         $t0, $zero, L_800D1E6C
    if (ctx->r8 == 0) {
        // 0x800D1E40: nop
    
            goto L_800D1E6C;
    }
    // 0x800D1E40: nop

L_800D1E44:
    // 0x800D1E44: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800D1E48: lbu         $t4, 0x2F($sp)
    ctx->r12 = MEM_BU(ctx->r29, 0X2F);
    // 0x800D1E4C: lw          $t2, 0x8($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X8);
    // 0x800D1E50: lw          $t8, 0x14($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X14);
    // 0x800D1E54: addu        $t1, $t2, $t8
    ctx->r9 = ADD32(ctx->r10, ctx->r24);
    // 0x800D1E58: sb          $t4, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r12;
    // 0x800D1E5C: lw          $t5, 0x30($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X30);
    // 0x800D1E60: lw          $t6, 0x14($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X14);
    // 0x800D1E64: addiu       $t3, $t6, 0x1
    ctx->r11 = ADD32(ctx->r14, 0X1);
    // 0x800D1E68: sw          $t3, 0x14($t5)
    MEM_W(0X14, ctx->r13) = ctx->r11;
L_800D1E6C:
    // 0x800D1E6C: lw          $t9, 0x30($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X30);
    // 0x800D1E70: lw          $t0, 0x24($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X24);
    // 0x800D1E74: blez        $t0, L_800D1EE8
    if (SIGNED(ctx->r8) <= 0) {
        // 0x800D1E78: nop
    
            goto L_800D1EE8;
    }
    // 0x800D1E78: nop

    // 0x800D1E7C: lh          $t7, 0x3E($sp)
    ctx->r15 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1E80: addiu       $t2, $t7, -0x1
    ctx->r10 = ADD32(ctx->r15, -0X1);
    // 0x800D1E84: sh          $t2, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r10;
    // 0x800D1E88: lw          $t8, 0x24($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X24);
    // 0x800D1E8C: sll         $t4, $t2, 16
    ctx->r12 = S32(ctx->r10 << 16);
    // 0x800D1E90: sra         $t1, $t4, 16
    ctx->r9 = S32(SIGNED(ctx->r12) >> 16);
    // 0x800D1E94: slt         $at, $t8, $t1
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r9) ? 1 : 0;
    // 0x800D1E98: beq         $at, $zero, L_800D1EA4
    if (ctx->r1 == 0) {
        // 0x800D1E9C: nop
    
            goto L_800D1EA4;
    }
    // 0x800D1E9C: nop

    // 0x800D1EA0: sh          $t8, 0x3E($sp)
    MEM_H(0X3E, ctx->r29) = ctx->r24;
L_800D1EA4:
    // 0x800D1EA4: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x800D1EA8: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x800D1EAC: lh          $a2, 0x3E($sp)
    ctx->r6 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1EB0: lw          $t3, 0x8($t6)
    ctx->r11 = MEM_W(ctx->r14, 0X8);
    // 0x800D1EB4: lw          $t5, 0x14($t6)
    ctx->r13 = MEM_W(ctx->r14, 0X14);
    // 0x800D1EB8: jal         0x800D04C0
    // 0x800D1EBC: addu        $a0, $t3, $t5
    ctx->r4 = ADD32(ctx->r11, ctx->r13);
    memcpy_recomp(rdram, ctx);
        goto after_4;
    // 0x800D1EBC: addu        $a0, $t3, $t5
    ctx->r4 = ADD32(ctx->r11, ctx->r13);
    after_4:
    // 0x800D1EC0: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800D1EC4: lh          $t9, 0x3E($sp)
    ctx->r25 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1EC8: lw          $t7, 0x14($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X14);
    // 0x800D1ECC: addu        $t2, $t7, $t9
    ctx->r10 = ADD32(ctx->r15, ctx->r25);
    // 0x800D1ED0: sw          $t2, 0x14($t0)
    MEM_W(0X14, ctx->r8) = ctx->r10;
    // 0x800D1ED4: lw          $t4, 0x30($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X30);
    // 0x800D1ED8: lh          $t8, 0x3E($sp)
    ctx->r24 = MEM_H(ctx->r29, 0X3E);
    // 0x800D1EDC: lw          $t1, 0x24($t4)
    ctx->r9 = MEM_W(ctx->r12, 0X24);
    // 0x800D1EE0: subu        $t6, $t1, $t8
    ctx->r14 = SUB32(ctx->r9, ctx->r24);
    // 0x800D1EE4: sw          $t6, 0x18($t4)
    MEM_W(0X18, ctx->r12) = ctx->r14;
L_800D1EE8:
    // 0x800D1EE8: lw          $t3, 0x30($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X30);
    // 0x800D1EEC: lbu         $t2, 0x37($sp)
    ctx->r10 = MEM_BU(ctx->r29, 0X37);
    // 0x800D1EF0: lw          $t5, 0x8($t3)
    ctx->r13 = MEM_W(ctx->r11, 0X8);
    // 0x800D1EF4: lw          $t7, 0x14($t3)
    ctx->r15 = MEM_W(ctx->r11, 0X14);
    // 0x800D1EF8: addu        $t9, $t5, $t7
    ctx->r25 = ADD32(ctx->r13, ctx->r15);
    // 0x800D1EFC: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
    // 0x800D1F00: sb          $t2, 0x0($t9)
    MEM_B(0X0, ctx->r25) = ctx->r10;
    // 0x800D1F04: lw          $t0, 0x38($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F08: lh          $t8, 0x42($sp)
    ctx->r24 = MEM_H(ctx->r29, 0X42);
    // 0x800D1F0C: addiu       $t1, $t0, 0x1
    ctx->r9 = ADD32(ctx->r8, 0X1);
    // 0x800D1F10: bltz        $t8, L_800D1F30
    if (SIGNED(ctx->r24) < 0) {
        // 0x800D1F14: sw          $t1, 0x38($sp)
        MEM_W(0X38, ctx->r29) = ctx->r9;
            goto L_800D1F30;
    }
    // 0x800D1F14: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    // 0x800D1F18: addiu       $t6, $zero, 0x2B
    ctx->r14 = ADD32(0, 0X2B);
    // 0x800D1F1C: sb          $t6, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r14;
    // 0x800D1F20: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F24: addiu       $t3, $t4, 0x1
    ctx->r11 = ADD32(ctx->r12, 0X1);
    // 0x800D1F28: b           L_800D1F54
    // 0x800D1F2C: sw          $t3, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r11;
        goto L_800D1F54;
    // 0x800D1F2C: sw          $t3, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r11;
L_800D1F30:
    // 0x800D1F30: lw          $t7, 0x38($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F34: addiu       $t5, $zero, 0x2D
    ctx->r13 = ADD32(0, 0X2D);
    // 0x800D1F38: sb          $t5, 0x0($t7)
    MEM_B(0X0, ctx->r15) = ctx->r13;
    // 0x800D1F3C: lw          $t2, 0x38($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F40: lh          $t0, 0x42($sp)
    ctx->r8 = MEM_H(ctx->r29, 0X42);
    // 0x800D1F44: addiu       $t9, $t2, 0x1
    ctx->r25 = ADD32(ctx->r10, 0X1);
    // 0x800D1F48: negu        $t8, $t0
    ctx->r24 = SUB32(0, ctx->r8);
    // 0x800D1F4C: sw          $t9, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r25;
    // 0x800D1F50: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
L_800D1F54:
    // 0x800D1F54: lh          $t6, 0x42($sp)
    ctx->r14 = MEM_H(ctx->r29, 0X42);
    // 0x800D1F58: slti        $at, $t6, 0x64
    ctx->r1 = SIGNED(ctx->r14) < 0X64 ? 1 : 0;
    // 0x800D1F5C: bne         $at, $zero, L_800D1FD4
    if (ctx->r1 != 0) {
        // 0x800D1F60: slti        $at, $t6, 0x3E8
        ctx->r1 = SIGNED(ctx->r14) < 0X3E8 ? 1 : 0;
            goto L_800D1FD4;
    }
    // 0x800D1F60: slti        $at, $t6, 0x3E8
    ctx->r1 = SIGNED(ctx->r14) < 0X3E8 ? 1 : 0;
    // 0x800D1F64: bne         $at, $zero, L_800D1F9C
    if (ctx->r1 != 0) {
        // 0x800D1F68: addiu       $at, $zero, 0x3E8
        ctx->r1 = ADD32(0, 0X3E8);
            goto L_800D1F9C;
    }
    // 0x800D1F68: addiu       $at, $zero, 0x3E8
    ctx->r1 = ADD32(0, 0X3E8);
    // 0x800D1F6C: div         $zero, $t6, $at
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r1)));
    // 0x800D1F70: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F74: mflo        $t1
    ctx->r9 = lo;
    // 0x800D1F78: addiu       $t4, $t1, 0x30
    ctx->r12 = ADD32(ctx->r9, 0X30);
    // 0x800D1F7C: sb          $t4, 0x0($t3)
    MEM_B(0X0, ctx->r11) = ctx->r12;
    // 0x800D1F80: lh          $t2, 0x42($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X42);
    // 0x800D1F84: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800D1F88: div         $zero, $t2, $at
    lo = S32(S64(S32(ctx->r10)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r10)) % S64(S32(ctx->r1)));
    // 0x800D1F8C: mfhi        $t9
    ctx->r25 = hi;
    // 0x800D1F90: addiu       $t7, $t5, 0x1
    ctx->r15 = ADD32(ctx->r13, 0X1);
    // 0x800D1F94: sw          $t7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r15;
    // 0x800D1F98: sh          $t9, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r25;
L_800D1F9C:
    // 0x800D1F9C: lh          $t0, 0x42($sp)
    ctx->r8 = MEM_H(ctx->r29, 0X42);
    // 0x800D1FA0: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x800D1FA4: lw          $t1, 0x38($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X38);
    // 0x800D1FA8: div         $zero, $t0, $at
    lo = S32(S64(S32(ctx->r8)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r8)) % S64(S32(ctx->r1)));
    // 0x800D1FAC: mflo        $t8
    ctx->r24 = lo;
    // 0x800D1FB0: addiu       $t6, $t8, 0x30
    ctx->r14 = ADD32(ctx->r24, 0X30);
    // 0x800D1FB4: sb          $t6, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r14;
    // 0x800D1FB8: lh          $t5, 0x42($sp)
    ctx->r13 = MEM_H(ctx->r29, 0X42);
    // 0x800D1FBC: lw          $t4, 0x38($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X38);
    // 0x800D1FC0: div         $zero, $t5, $at
    lo = S32(S64(S32(ctx->r13)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r13)) % S64(S32(ctx->r1)));
    // 0x800D1FC4: mfhi        $t7
    ctx->r15 = hi;
    // 0x800D1FC8: addiu       $t3, $t4, 0x1
    ctx->r11 = ADD32(ctx->r12, 0X1);
    // 0x800D1FCC: sw          $t3, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r11;
    // 0x800D1FD0: sh          $t7, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r15;
L_800D1FD4:
    // 0x800D1FD4: lh          $t2, 0x42($sp)
    ctx->r10 = MEM_H(ctx->r29, 0X42);
    // 0x800D1FD8: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800D1FDC: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x800D1FE0: div         $zero, $t2, $at
    lo = S32(S64(S32(ctx->r10)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r10)) % S64(S32(ctx->r1)));
    // 0x800D1FE4: mflo        $t9
    ctx->r25 = lo;
    // 0x800D1FE8: addiu       $t0, $t9, 0x30
    ctx->r8 = ADD32(ctx->r25, 0X30);
    // 0x800D1FEC: sb          $t0, 0x0($t8)
    MEM_B(0X0, ctx->r24) = ctx->r8;
    // 0x800D1FF0: lh          $t4, 0x42($sp)
    ctx->r12 = MEM_H(ctx->r29, 0X42);
    // 0x800D1FF4: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D1FF8: div         $zero, $t4, $at
    lo = S32(S64(S32(ctx->r12)) / S64(S32(ctx->r1))); hi = S32(S64(S32(ctx->r12)) % S64(S32(ctx->r1)));
    // 0x800D1FFC: mfhi        $t3
    ctx->r11 = hi;
    // 0x800D2000: sll         $t5, $t3, 16
    ctx->r13 = S32(ctx->r11 << 16);
    // 0x800D2004: sra         $t7, $t5, 16
    ctx->r15 = S32(SIGNED(ctx->r13) >> 16);
    // 0x800D2008: addiu       $t1, $t6, 0x1
    ctx->r9 = ADD32(ctx->r14, 0X1);
    // 0x800D200C: sw          $t1, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r9;
    // 0x800D2010: sh          $t3, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r11;
    // 0x800D2014: addiu       $t2, $t7, 0x30
    ctx->r10 = ADD32(ctx->r15, 0X30);
    // 0x800D2018: sb          $t2, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r10;
    // 0x800D201C: lw          $t9, 0x38($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X38);
    // 0x800D2020: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x800D2024: addiu       $t0, $t9, 0x1
    ctx->r8 = ADD32(ctx->r25, 0X1);
    // 0x800D2028: sw          $t0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r8;
    // 0x800D202C: lw          $t4, 0x14($t8)
    ctx->r12 = MEM_W(ctx->r24, 0X14);
    // 0x800D2030: lw          $t6, 0x8($t8)
    ctx->r14 = MEM_W(ctx->r24, 0X8);
    // 0x800D2034: addu        $t3, $t6, $t4
    ctx->r11 = ADD32(ctx->r14, ctx->r12);
    // 0x800D2038: subu        $t5, $t0, $t3
    ctx->r13 = SUB32(ctx->r8, ctx->r11);
    // 0x800D203C: sw          $t5, 0x1C($t8)
    MEM_W(0X1C, ctx->r24) = ctx->r13;
L_800D2040:
    // 0x800D2040: lw          $t7, 0x30($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X30);
    // 0x800D2044: addiu       $at, $zero, 0x10
    ctx->r1 = ADD32(0, 0X10);
    // 0x800D2048: lw          $t2, 0x30($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X30);
    // 0x800D204C: andi        $t1, $t2, 0x14
    ctx->r9 = ctx->r10 & 0X14;
    // 0x800D2050: bne         $t1, $at, L_800D209C
    if (ctx->r9 != ctx->r1) {
        // 0x800D2054: nop
    
            goto L_800D209C;
    }
    // 0x800D2054: nop

    // 0x800D2058: lw          $t9, 0xC($t7)
    ctx->r25 = MEM_W(ctx->r15, 0XC);
    // 0x800D205C: lw          $t6, 0x14($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X14);
    // 0x800D2060: lw          $t0, 0x18($t7)
    ctx->r8 = MEM_W(ctx->r15, 0X18);
    // 0x800D2064: lw          $t5, 0x1C($t7)
    ctx->r13 = MEM_W(ctx->r15, 0X1C);
    // 0x800D2068: lw          $t2, 0x20($t7)
    ctx->r10 = MEM_W(ctx->r15, 0X20);
    // 0x800D206C: addu        $t4, $t9, $t6
    ctx->r12 = ADD32(ctx->r25, ctx->r14);
    // 0x800D2070: addu        $t3, $t4, $t0
    ctx->r11 = ADD32(ctx->r12, ctx->r8);
    // 0x800D2074: addu        $t8, $t3, $t5
    ctx->r24 = ADD32(ctx->r11, ctx->r13);
    // 0x800D2078: addu        $t1, $t8, $t2
    ctx->r9 = ADD32(ctx->r24, ctx->r10);
    // 0x800D207C: sw          $t1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r9;
    // 0x800D2080: lw          $t9, 0x28($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X28);
    // 0x800D2084: slt         $at, $t1, $t9
    ctx->r1 = SIGNED(ctx->r9) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x800D2088: beq         $at, $zero, L_800D209C
    if (ctx->r1 == 0) {
        // 0x800D208C: nop
    
            goto L_800D209C;
    }
    // 0x800D208C: nop

    // 0x800D2090: lw          $t6, 0x28($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X28);
    // 0x800D2094: subu        $t4, $t6, $t1
    ctx->r12 = SUB32(ctx->r14, ctx->r9);
    // 0x800D2098: sw          $t4, 0x10($t7)
    MEM_W(0X10, ctx->r15) = ctx->r12;
L_800D209C:
    // 0x800D209C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800D20A0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800D20A4: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800D20A8: jr          $ra
    // 0x800D20AC: nop

    return;
    // 0x800D20AC: nop

;}
RECOMP_FUNC void __osAtomicDec(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D20C0: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800D20C4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D20C8: jal         0x800CAAD0
    // 0x800D20CC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    __osDisableInt_recomp(rdram, ctx);
        goto after_0;
    // 0x800D20CC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    after_0:
    // 0x800D20D0: lw          $t6, 0x20($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X20);
    // 0x800D20D4: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800D20D8: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x800D20DC: beq         $t7, $zero, L_800D20F8
    if (ctx->r15 == 0) {
        // 0x800D20E0: nop
    
            goto L_800D20F8;
    }
    // 0x800D20E0: nop

    // 0x800D20E4: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x800D20E8: sw          $t8, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r24;
    // 0x800D20EC: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800D20F0: b           L_800D20FC
    // 0x800D20F4: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
        goto L_800D20FC;
    // 0x800D20F4: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
L_800D20F8:
    // 0x800D20F8: sw          $zero, 0x18($sp)
    MEM_W(0X18, ctx->r29) = 0;
L_800D20FC:
    // 0x800D20FC: jal         0x800CAAF0
    // 0x800D2100: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    __osRestoreInt_recomp(rdram, ctx);
        goto after_1;
    // 0x800D2100: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
    after_1:
    // 0x800D2104: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D2108: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x800D210C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800D2110: jr          $ra
    // 0x800D2114: nop

    return;
    // 0x800D2114: nop

    // 0x800D2118: nop

    // 0x800D211C: nop

;}
RECOMP_FUNC void lldiv_recomp(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800D2120: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x800D2124: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x800D2128: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800D212C: sw          $a2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r6;
    // 0x800D2130: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    // 0x800D2134: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800D2138: or          $a1, $a3, $zero
    ctx->r5 = ctx->r7 | 0;
    // 0x800D213C: lw          $a3, 0x44($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X44);
    // 0x800D2140: jal         0x800CC86C
    // 0x800D2144: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    __ll_div_recomp(rdram, ctx);
        goto after_0;
    // 0x800D2144: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    after_0:
    // 0x800D2148: sw          $v0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r2;
    // 0x800D214C: sw          $v1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r3;
    // 0x800D2150: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x800D2154: lw          $a1, 0x44($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X44);
    // 0x800D2158: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x800D215C: jal         0x800CC8C8
    // 0x800D2160: or          $a3, $v1, $zero
    ctx->r7 = ctx->r3 | 0;
    __ll_mul_recomp(rdram, ctx);
        goto after_1;
    // 0x800D2160: or          $a3, $v1, $zero
    ctx->r7 = ctx->r3 | 0;
    after_1:
    // 0x800D2164: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x800D2168: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x800D216C: lw          $t0, 0x20($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X20);
    // 0x800D2170: subu        $t8, $t6, $v0
    ctx->r24 = SUB32(ctx->r14, ctx->r2);
    // 0x800D2174: sltu        $at, $t7, $v1
    ctx->r1 = ctx->r15 < ctx->r3 ? 1 : 0;
    // 0x800D2178: subu        $t8, $t8, $at
    ctx->r24 = SUB32(ctx->r24, ctx->r1);
    // 0x800D217C: subu        $t9, $t7, $v1
    ctx->r25 = SUB32(ctx->r15, ctx->r3);
    // 0x800D2180: sw          $t9, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r25;
    // 0x800D2184: sw          $t8, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r24;
    // 0x800D2188: bgtz        $t0, L_800D21E8
    if (SIGNED(ctx->r8) > 0) {
        // 0x800D218C: lw          $t1, 0x24($sp)
        ctx->r9 = MEM_W(ctx->r29, 0X24);
            goto L_800D21E8;
    }
    // 0x800D218C: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x800D2190: bltz        $t0, L_800D21A0
    if (SIGNED(ctx->r8) < 0) {
        // 0x800D2194: nop
    
            goto L_800D21A0;
    }
    // 0x800D2194: nop

    // 0x800D2198: b           L_800D21EC
    // 0x800D219C: addiu       $t0, $sp, 0x20
    ctx->r8 = ADD32(ctx->r29, 0X20);
        goto L_800D21EC;
    // 0x800D219C: addiu       $t0, $sp, 0x20
    ctx->r8 = ADD32(ctx->r29, 0X20);
L_800D21A0:
    // 0x800D21A0: bltzl       $t8, L_800D21EC
    if (SIGNED(ctx->r24) < 0) {
        // 0x800D21A4: addiu       $t0, $sp, 0x20
        ctx->r8 = ADD32(ctx->r29, 0X20);
            goto L_800D21EC;
    }
    goto skip_0;
    // 0x800D21A4: addiu       $t0, $sp, 0x20
    ctx->r8 = ADD32(ctx->r29, 0X20);
    skip_0:
    // 0x800D21A8: bgtz        $t8, L_800D21B8
    if (SIGNED(ctx->r24) > 0) {
        // 0x800D21AC: addiu       $t3, $t1, 0x1
        ctx->r11 = ADD32(ctx->r9, 0X1);
            goto L_800D21B8;
    }
    // 0x800D21AC: addiu       $t3, $t1, 0x1
    ctx->r11 = ADD32(ctx->r9, 0X1);
    // 0x800D21B0: beql        $t9, $zero, L_800D21EC
    if (ctx->r25 == 0) {
        // 0x800D21B4: addiu       $t0, $sp, 0x20
        ctx->r8 = ADD32(ctx->r29, 0X20);
            goto L_800D21EC;
    }
    goto skip_1;
    // 0x800D21B4: addiu       $t0, $sp, 0x20
    ctx->r8 = ADD32(ctx->r29, 0X20);
    skip_1:
L_800D21B8:
    // 0x800D21B8: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x800D21BC: lw          $t5, 0x44($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X44);
    // 0x800D21C0: sltiu       $at, $t3, 0x1
    ctx->r1 = ctx->r11 < 0X1 ? 1 : 0;
    // 0x800D21C4: addu        $t2, $t0, $at
    ctx->r10 = ADD32(ctx->r8, ctx->r1);
    // 0x800D21C8: subu        $t6, $t8, $t4
    ctx->r14 = SUB32(ctx->r24, ctx->r12);
    // 0x800D21CC: sltu        $at, $t9, $t5
    ctx->r1 = ctx->r25 < ctx->r13 ? 1 : 0;
    // 0x800D21D0: subu        $t6, $t6, $at
    ctx->r14 = SUB32(ctx->r14, ctx->r1);
    // 0x800D21D4: subu        $t7, $t9, $t5
    ctx->r15 = SUB32(ctx->r25, ctx->r13);
    // 0x800D21D8: sw          $t2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r10;
    // 0x800D21DC: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x800D21E0: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x800D21E4: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
L_800D21E8:
    // 0x800D21E8: addiu       $t0, $sp, 0x20
    ctx->r8 = ADD32(ctx->r29, 0X20);
L_800D21EC:
    // 0x800D21EC: lw          $v0, 0x30($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X30);
    // 0x800D21F0: lw          $at, 0x0($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X0);
    // 0x800D21F4: sw          $at, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r1;
    // 0x800D21F8: lw          $t3, 0x4($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X4);
    // 0x800D21FC: sw          $t3, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r11;
    // 0x800D2200: lw          $at, 0x8($t0)
    ctx->r1 = MEM_W(ctx->r8, 0X8);
    // 0x800D2204: sw          $at, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r1;
    // 0x800D2208: lw          $t3, 0xC($t0)
    ctx->r11 = MEM_W(ctx->r8, 0XC);
    // 0x800D220C: sw          $t3, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r11;
    // 0x800D2210: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800D2214: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800D2218: jr          $ra
    // 0x800D221C: nop

    return;
    // 0x800D221C: nop

;}
