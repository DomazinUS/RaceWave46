#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_8008FB74(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8008FB74: addiu       $sp, $sp, -0x1C0
    ctx->r29 = ADD32(ctx->r29, -0X1C0);
    // 0x8008FB78: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8008FB7C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8008FB80: addiu       $t7, $t7, -0x574C
    ctx->r15 = ADD32(ctx->r15, -0X574C);
    // 0x8008FB84: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x8008FB88: addiu       $t6, $sp, 0x1B0
    ctx->r14 = ADD32(ctx->r29, 0X1B0);
    // 0x8008FB8C: lw          $t9, 0x4($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X4);
    // 0x8008FB90: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x8008FB94: lw          $at, 0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X8);
    // 0x8008FB98: lui         $t8, 0x8012
    ctx->r24 = S32(0X8012 << 16);
    // 0x8008FB9C: sw          $t9, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r25;
    // 0x8008FBA0: sw          $at, 0x8($t6)
    MEM_W(0X8, ctx->r14) = ctx->r1;
    // 0x8008FBA4: lw          $t8, -0x720($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X720);
    // 0x8008FBA8: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8008FBAC: addiu       $t7, $t7, 0x43F8
    ctx->r15 = ADD32(ctx->r15, 0X43F8);
    // 0x8008FBB0: sll         $t6, $t8, 3
    ctx->r14 = S32(ctx->r24 << 3);
    // 0x8008FBB4: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FBB8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FBBC: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FBC0: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x8008FBC4: addu        $t6, $t6, $t8
    ctx->r14 = ADD32(ctx->r14, ctx->r24);
    // 0x8008FBC8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FBCC: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FBD0: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x8008FBD4: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8008FBD8: addu        $a1, $t6, $t7
    ctx->r5 = ADD32(ctx->r14, ctx->r15);
    // 0x8008FBDC: sw          $a1, 0x1A8($sp)
    MEM_W(0X1A8, ctx->r29) = ctx->r5;
    // 0x8008FBE0: sw          $a2, 0x1C0($sp)
    MEM_W(0X1C0, ctx->r29) = ctx->r6;
    // 0x8008FBE4: jal         0x8004C998
    // 0x8008FBE8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_8004C998(rdram, ctx);
        goto after_0;
    // 0x8008FBE8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x8008FBEC: lw          $a1, 0x1A8($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1A8);
    // 0x8008FBF0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    { extern void wr64_sunny_sky_cloud_camera(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_camera(rdram, ctx); }
    // 0x8008FBF4: jal         0x8004C1D0
    // 0x8008FBF8: addiu       $a1, $a1, 0x1C0
    ctx->r5 = ADD32(ctx->r5, 0X1C0);
    func_8004C1D0(rdram, ctx);
        goto after_1;
    // 0x8008FBF8: addiu       $a1, $a1, 0x1C0
    ctx->r5 = ADD32(ctx->r5, 0X1C0);
    after_1:
    // 0x8008FBFC: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x8008FC00: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x8008FC04: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x8008FC08: lw          $a2, 0x1C0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C0);
    // 0x8008FC0C: bne         $t9, $at, L_8008FC38
    if (ctx->r25 != ctx->r1) {
        // 0x8008FC10: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_8008FC38;
    }
    // 0x8008FC10: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8008FC14: lw          $t8, -0x7E90($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E90);
    // 0x8008FC18: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x8008FC1C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8008FC20: bne         $t8, $at, L_8008FC38
    if (ctx->r24 != ctx->r1) {
        // 0x8008FC24: lw          $a1, 0x1A8($sp)
        ctx->r5 = MEM_W(ctx->r29, 0X1A8);
            goto L_8008FC38;
    }
    // 0x8008FC24: lw          $a1, 0x1A8($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X1A8);
    // 0x8008FC28: addiu       $a1, $a1, 0x70
    ctx->r5 = ADD32(ctx->r5, 0X70);
    // 0x8008FC2C: jal         0x8004C998
    // 0x8008FC30: sw          $a2, 0x1C0($sp)
    MEM_W(0X1C0, ctx->r29) = ctx->r6;
    func_8004C998(rdram, ctx);
        goto after_2;
    // 0x8008FC30: sw          $a2, 0x1C0($sp)
    MEM_W(0X1C0, ctx->r29) = ctx->r6;
    after_2:
    // 0x8008FC34: lw          $a2, 0x1C0($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C0);
L_8008FC38:
    // 0x8008FC38: lui         $t6, 0xBC00
    ctx->r14 = S32(0XBC00 << 16);
    // 0x8008FC3C: ori         $t6, $t6, 0x1806
    ctx->r14 = ctx->r14 | 0X1806;
    // 0x8008FC40: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x8008FC44: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x8008FC48: lui         $t7, 0x8012
    ctx->r15 = S32(0X8012 << 16);
    // 0x8008FC4C: lw          $t7, -0x720($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X720);
    // 0x8008FC50: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    // 0x8008FC54: addiu       $t8, $t8, 0x43F8
    ctx->r24 = ADD32(ctx->r24, 0X43F8);
    // 0x8008FC58: sll         $t9, $t7, 3
    ctx->r25 = S32(ctx->r15 << 3);
    // 0x8008FC5C: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x8008FC60: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x8008FC64: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x8008FC68: sll         $t9, $t9, 3
    ctx->r25 = S32(ctx->r25 << 3);
    // 0x8008FC6C: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x8008FC70: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x8008FC74: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x8008FC78: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x8008FC7C: addu        $t6, $t9, $t8
    ctx->r14 = ADD32(ctx->r25, ctx->r24);
    // 0x8008FC80: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x8008FC84: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x8008FC88: lw          $v1, -0x19C8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C8);
    // 0x8008FC8C: addiu       $t0, $zero, 0x4
    ctx->r8 = ADD32(0, 0X4);
    // 0x8008FC90: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FC94: beq         $t0, $v1, L_8008FCA8
    if (ctx->r8 == ctx->r3) {
        // 0x8008FC98: lui         $ra, 0x600
        ctx->r31 = S32(0X600 << 16);
            goto L_8008FCA8;
    }
    // 0x8008FC98: lui         $ra, 0x600
    ctx->r31 = S32(0X600 << 16);
    // 0x8008FC9C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x8008FCA0: bne         $v1, $at, L_8008FEA4
    if (ctx->r3 != ctx->r1) {
        // 0x8008FCA4: lui         $t9, 0x800E
        ctx->r25 = S32(0X800E << 16);
            goto L_8008FEA4;
    }
    // 0x8008FCA4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
L_8008FCA8:
    // 0x8008FCA8: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8008FCAC: lh          $t7, -0x19F4($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19F4);
    // 0x8008FCB0: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x8008FCB4: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FCB8: bne         $t3, $t7, L_8008FD58
    if (ctx->r11 != ctx->r15) {
        // 0x8008FCBC: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_8008FD58;
    }
    // 0x8008FCBC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FCC0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FCC4: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x8008FCC8: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x8008FCCC: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x8008FCD0: lw          $t8, 0x3930($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3930);
    // 0x8008FCD4: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x8008FCD8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FCDC: sll         $t6, $t8, 4
    ctx->r14 = S32(ctx->r24 << 4);
    // 0x8008FCE0: addu        $t6, $t6, $t8
    ctx->r14 = ADD32(ctx->r14, ctx->r24);
    // 0x8008FCE4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FCE8: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FCEC: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FCF0: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8008FCF4: lhu         $t7, 0x7D64($t7)
    ctx->r15 = MEM_HU(ctx->r15, 0X7D64);
    // 0x8008FCF8: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8008FCFC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FD00: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x8008FD04: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8008FD08: lui         $t9, 0x380
    ctx->r25 = S32(0X380 << 16);
    // 0x8008FD0C: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x8008FD10: addiu       $t8, $t8, -0x5710
    ctx->r24 = ADD32(ctx->r24, -0X5710);
    // 0x8008FD14: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    { extern void wr64_watercraft_preview_viewport(uint8_t*, recomp_context*); wr64_watercraft_preview_viewport(rdram, ctx); }
    // 0x8008FD18: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x8008FD1C: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x8008FD20: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FD24: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8008FD28: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x8008FD2C: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x8008FD30: lui         $t6, 0xED42
    ctx->r14 = S32(0XED42 << 16);
    // 0x8008FD34: addiu       $t6, $t6, 0x4180
    ctx->r14 = ADD32(ctx->r14, 0X4180);
    // 0x8008FD38: lui         $t7, 0x63
    ctx->r15 = S32(0X63 << 16);
    // 0x8008FD3C: addiu       $t7, $t7, -0x7CA4
    ctx->r15 = ADD32(ctx->r15, -0X7CA4);
    { extern uint32_t wr64_watercraft_preview_scissor(uint32_t); ctx->r14 = S32(wr64_watercraft_preview_scissor((uint32_t)ctx->r14)); }
    // 0x8008FD40: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x8008FD44: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x8008FD48: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FD4C: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
    // 0x8008FD50: b           L_8009008C
    // 0x8008FD54: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_8009008C;
    // 0x8008FD54: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_8008FD58:
    // 0x8008FD58: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
    // 0x8008FD5C: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FD60: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FD64: beq         $v0, $zero, L_8008FD7C
    if (ctx->r2 == 0) {
        // 0x8008FD68: lui         $t9, 0xB400
        ctx->r25 = S32(0XB400 << 16);
            goto L_8008FD7C;
    }
    // 0x8008FD68: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x8008FD6C: beq         $v0, $t3, L_8008FE0C
    if (ctx->r2 == ctx->r11) {
        // 0x8008FD70: lui         $t2, 0xE700
        ctx->r10 = S32(0XE700 << 16);
            goto L_8008FE0C;
    }
    // 0x8008FD70: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FD74: b           L_8009008C
    // 0x8008FD78: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
        goto L_8009008C;
    // 0x8008FD78: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
L_8008FD7C:
    // 0x8008FD7C: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x8008FD80: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x8008FD84: lw          $t8, 0x3930($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3930);
    // 0x8008FD88: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x8008FD8C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FD90: sll         $t6, $t8, 4
    ctx->r14 = S32(ctx->r24 << 4);
    // 0x8008FD94: addu        $t6, $t6, $t8
    ctx->r14 = ADD32(ctx->r14, ctx->r24);
    // 0x8008FD98: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FD9C: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FDA0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FDA4: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8008FDA8: lhu         $t7, 0x7D64($t7)
    ctx->r15 = MEM_HU(ctx->r15, 0X7D64);
    // 0x8008FDAC: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8008FDB0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FDB4: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x8008FDB8: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8008FDBC: lui         $t9, 0x380
    ctx->r25 = S32(0X380 << 16);
    // 0x8008FDC0: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x8008FDC4: addiu       $t8, $t8, -0x5700
    ctx->r24 = ADD32(ctx->r24, -0X5700);
    // 0x8008FDC8: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    { extern void wr64_two_player_preview_viewport(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_viewport(rdram, ctx, 0); }
    // 0x8008FDCC: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x8008FDD0: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x8008FDD4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FDD8: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8008FDDC: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x8008FDE0: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x8008FDE4: lui         $t6, 0xED06
    ctx->r14 = S32(0XED06 << 16);
    // 0x8008FDE8: addiu       $t6, $t6, 0x180
    ctx->r14 = ADD32(ctx->r14, 0X180);
    // 0x8008FDEC: lui         $t7, 0x27
    ctx->r15 = S32(0X27 << 16);
    // 0x8008FDF0: addiu       $t7, $t7, 0x35C
    ctx->r15 = ADD32(ctx->r15, 0X35C);
    { extern void wr64_two_player_preview_scissor(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_scissor(rdram, ctx, 0); }
    // 0x8008FDF4: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x8008FDF8: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x8008FDFC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FE00: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FE04: b           L_8009008C
    // 0x8008FE08: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
        goto L_8009008C;
    // 0x8008FE08: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
L_8008FE0C:
    // 0x8008FE0C: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FE10: lui         $t9, 0xB400
    ctx->r25 = S32(0XB400 << 16);
    // 0x8008FE14: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x8008FE18: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x8008FE1C: lw          $t8, 0x3934($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3934);
    // 0x8008FE20: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x8008FE24: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FE28: sll         $t6, $t8, 4
    ctx->r14 = S32(ctx->r24 << 4);
    // 0x8008FE2C: addu        $t6, $t6, $t8
    ctx->r14 = ADD32(ctx->r14, ctx->r24);
    // 0x8008FE30: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FE34: subu        $t6, $t6, $t8
    ctx->r14 = SUB32(ctx->r14, ctx->r24);
    // 0x8008FE38: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x8008FE3C: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8008FE40: lhu         $t7, 0x7D64($t7)
    ctx->r15 = MEM_HU(ctx->r15, 0X7D64);
    // 0x8008FE44: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8008FE48: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FE4C: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x8008FE50: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8008FE54: lui         $t9, 0x380
    ctx->r25 = S32(0X380 << 16);
    // 0x8008FE58: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x8008FE5C: addiu       $t8, $t8, -0x5710
    ctx->r24 = ADD32(ctx->r24, -0X5710);
    // 0x8008FE60: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    { extern void wr64_two_player_preview_viewport(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_viewport(rdram, ctx, 1); }
    // 0x8008FE64: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x8008FE68: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x8008FE6C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FE70: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8008FE74: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x8008FE78: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x8008FE7C: lui         $t6, 0xED42
    ctx->r14 = S32(0XED42 << 16);
    // 0x8008FE80: addiu       $t6, $t6, 0x4180
    ctx->r14 = ADD32(ctx->r14, 0X4180);
    // 0x8008FE84: lui         $t7, 0x63
    ctx->r15 = S32(0X63 << 16);
    // 0x8008FE88: addiu       $t7, $t7, -0x7CA4
    ctx->r15 = ADD32(ctx->r15, -0X7CA4);
    { extern void wr64_two_player_preview_scissor(uint8_t*, recomp_context*, uint32_t); wr64_two_player_preview_scissor(rdram, ctx, 1); }
    // 0x8008FE8C: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x8008FE90: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x8008FE94: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FE98: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FE9C: b           L_8009008C
    // 0x8008FEA0: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
        goto L_8009008C;
    // 0x8008FEA0: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
L_8008FEA4:
    // 0x8008FEA4: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x8008FEA8: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x8008FEAC: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FEB0: bne         $t3, $t9, L_8008FF50
    if (ctx->r11 != ctx->r25) {
        // 0x8008FEB4: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_8008FF50;
    }
    // 0x8008FEB4: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8008FEB8: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FEBC: lui         $t8, 0xB400
    ctx->r24 = S32(0XB400 << 16);
    // 0x8008FEC0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x8008FEC4: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x8008FEC8: lw          $t6, 0x3930($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X3930);
    // 0x8008FECC: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x8008FED0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FED4: sll         $t7, $t6, 4
    ctx->r15 = S32(ctx->r14 << 4);
    // 0x8008FED8: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x8008FEDC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8008FEE0: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8008FEE4: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8008FEE8: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x8008FEEC: lhu         $t9, 0x7D64($t9)
    ctx->r25 = MEM_HU(ctx->r25, 0X7D64);
    // 0x8008FEF0: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8008FEF4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FEF8: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x8008FEFC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8008FF00: lui         $t8, 0x380
    ctx->r24 = S32(0X380 << 16);
    // 0x8008FF04: ori         $t8, $t8, 0x10
    ctx->r24 = ctx->r24 | 0X10;
    // 0x8008FF08: addiu       $t6, $t6, -0x5740
    ctx->r14 = ADD32(ctx->r14, -0X5740);
    // 0x8008FF0C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x8008FF10: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x8008FF14: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x8008FF18: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FF1C: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8008FF20: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x8008FF24: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x8008FF28: lui         $t7, 0xED02
    ctx->r15 = S32(0XED02 << 16);
    // 0x8008FF2C: addiu       $t7, $t7, 0x50
    ctx->r15 = ADD32(ctx->r15, 0X50);
    // 0x8008FF30: lui         $t9, 0x68
    ctx->r25 = S32(0X68 << 16);
    // 0x8008FF34: addiu       $t9, $t9, -0x3C94
    ctx->r25 = ADD32(ctx->r25, -0X3C94);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r15 = 0xED000000U; ctx->r25 = 0x006A03C0U; } }
    // 0x8008FF38: sw          $t9, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r25;
    // 0x8008FF3C: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x8008FF40: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FF44: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
    // 0x8008FF48: b           L_8009008C
    // 0x8008FF4C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_8009008C;
    // 0x8008FF4C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_8008FF50:
    // 0x8008FF50: lw          $t8, -0x54D4($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D4);
    // 0x8008FF54: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FF58: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FF5C: bne         $t8, $zero, L_80090000
    if (ctx->r24 != 0) {
        // 0x8008FF60: lui         $t6, 0xB400
        ctx->r14 = S32(0XB400 << 16);
            goto L_80090000;
    }
    // 0x8008FF60: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
    // 0x8008FF64: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8008FF68: lui         $t6, 0xB400
    ctx->r14 = S32(0XB400 << 16);
    // 0x8008FF6C: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x8008FF70: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x8008FF74: lw          $t7, 0x3930($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3930);
    // 0x8008FF78: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x8008FF7C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FF80: sll         $t9, $t7, 4
    ctx->r25 = S32(ctx->r15 << 4);
    // 0x8008FF84: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x8008FF88: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x8008FF8C: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x8008FF90: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x8008FF94: addu        $t8, $t8, $t9
    ctx->r24 = ADD32(ctx->r24, ctx->r25);
    // 0x8008FF98: lhu         $t8, 0x7D64($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X7D64);
    // 0x8008FF9C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8008FFA0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FFA4: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x8008FFA8: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8008FFAC: lui         $t6, 0x380
    ctx->r14 = S32(0X380 << 16);
    // 0x8008FFB0: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x8008FFB4: addiu       $t7, $t7, -0x5730
    ctx->r15 = ADD32(ctx->r15, -0X5730);
    // 0x8008FFB8: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x8008FFBC: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x8008FFC0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x8008FFC4: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x8008FFC8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8008FFCC: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x8008FFD0: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8008FFD4: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x8008FFD8: lui         $t9, 0xED02
    ctx->r25 = S32(0XED02 << 16);
    // 0x8008FFDC: addiu       $t9, $t9, 0x30
    ctx->r25 = ADD32(ctx->r25, 0X30);
    // 0x8008FFE0: lui         $t8, 0x68
    ctx->r24 = S32(0X68 << 16);
    // 0x8008FFE4: addiu       $t8, $t8, -0x3E20
    ctx->r24 = ADD32(ctx->r24, -0X3E20);
    // 0x8008FFE8: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x8008FFEC: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x8008FFF0: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8008FFF4: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
    // 0x8008FFF8: b           L_8009008C
    // 0x8008FFFC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_8009008C;
    // 0x8008FFFC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090000:
    // 0x80090000: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x80090004: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x80090008: lw          $t7, 0x3934($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3934);
    // 0x8009000C: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80090010: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090014: sll         $t9, $t7, 4
    ctx->r25 = S32(ctx->r15 << 4);
    // 0x80090018: addu        $t9, $t9, $t7
    ctx->r25 = ADD32(ctx->r25, ctx->r15);
    // 0x8009001C: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x80090020: subu        $t9, $t9, $t7
    ctx->r25 = SUB32(ctx->r25, ctx->r15);
    // 0x80090024: sll         $t9, $t9, 2
    ctx->r25 = S32(ctx->r25 << 2);
    // 0x80090028: addu        $t8, $t8, $t9
    ctx->r24 = ADD32(ctx->r24, ctx->r25);
    // 0x8009002C: lhu         $t8, 0x7D64($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X7D64);
    // 0x80090030: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090034: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090038: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x8009003C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80090040: lui         $t6, 0x380
    ctx->r14 = S32(0X380 << 16);
    // 0x80090044: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x80090048: addiu       $t7, $t7, -0x5720
    ctx->r15 = ADD32(ctx->r15, -0X5720);
    // 0x8009004C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090050: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80090054: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80090058: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009005C: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80090060: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x80090064: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090068: lui         $t9, 0xED02
    ctx->r25 = S32(0XED02 << 16);
    // 0x8009006C: addiu       $t9, $t9, 0x1E8
    ctx->r25 = ADD32(ctx->r25, 0X1E8);
    // 0x80090070: lui         $t8, 0x68
    ctx->r24 = S32(0X68 << 16);
    // 0x80090074: addiu       $t8, $t8, -0x3C6C
    ctx->r24 = ADD32(ctx->r24, -0X3C6C);
    // 0x80090078: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x8009007C: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x80090080: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80090084: lw          $v0, -0x54D4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54D4);
    // 0x80090088: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_8009008C:
    // 0x8009008C: beq         $v0, $zero, L_800900A4
    if (ctx->r2 == 0) {
        // 0x80090090: lui         $a0, 0x300
        ctx->r4 = S32(0X300 << 16);
            goto L_800900A4;
    }
    // 0x80090090: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x80090094: beq         $v0, $t3, L_8009010C
    if (ctx->r2 == ctx->r11) {
        // 0x80090098: lui         $a0, 0x300
        ctx->r4 = S32(0X300 << 16);
            goto L_8009010C;
    }
    // 0x80090098: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x8009009C: b           L_80090170
    // 0x800900A0: nop

        goto L_80090170;
    // 0x800900A0: nop

L_800900A4:
    // 0x800900A4: lui         $t6, 0x103
    ctx->r14 = S32(0X103 << 16);
    // 0x800900A8: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x800900AC: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800900B0: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x800900B4: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x800900B8: lw          $t7, 0x3930($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X3930);
    // 0x800900BC: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    // 0x800900C0: ori         $at, $zero, 0xE008
    ctx->r1 = 0 | 0XE008;
    // 0x800900C4: sll         $t9, $t7, 6
    ctx->r25 = S32(ctx->r15 << 6);
    // 0x800900C8: addu        $t8, $a0, $t9
    ctx->r24 = ADD32(ctx->r4, ctx->r25);
    // 0x800900CC: addu        $t6, $t8, $at
    ctx->r14 = ADD32(ctx->r24, ctx->r1);
    // 0x800900D0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800900D4: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x800900D8: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x800900DC: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x800900E0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800900E4: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x800900E8: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x800900EC: lw          $t9, 0x3930($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X3930);
    // 0x800900F0: ori         $at, $zero, 0xE088
    ctx->r1 = 0 | 0XE088;
    // 0x800900F4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800900F8: sll         $t8, $t9, 6
    ctx->r24 = S32(ctx->r25 << 6);
    // 0x800900FC: addu        $t6, $a0, $t8
    ctx->r14 = ADD32(ctx->r4, ctx->r24);
    // 0x80090100: addu        $t7, $t6, $at
    ctx->r15 = ADD32(ctx->r14, ctx->r1);
    // 0x80090104: b           L_80090170
    // 0x80090108: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
        goto L_80090170;
    // 0x80090108: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
L_8009010C:
    // 0x8009010C: lui         $t9, 0x103
    ctx->r25 = S32(0X103 << 16);
    // 0x80090110: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x80090114: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090118: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x8009011C: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80090120: lw          $t8, 0x3934($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X3934);
    // 0x80090124: addiu       $a0, $a0, 0x0
    ctx->r4 = ADD32(ctx->r4, 0X0);
    // 0x80090128: ori         $at, $zero, 0xE008
    ctx->r1 = 0 | 0XE008;
    // 0x8009012C: sll         $t6, $t8, 6
    ctx->r14 = S32(ctx->r24 << 6);
    // 0x80090130: addu        $t7, $a0, $t6
    ctx->r15 = ADD32(ctx->r4, ctx->r14);
    // 0x80090134: addu        $t9, $t7, $at
    ctx->r25 = ADD32(ctx->r15, ctx->r1);
    // 0x80090138: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009013C: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80090140: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80090144: ori         $t8, $t8, 0x40
    ctx->r24 = ctx->r24 | 0X40;
    // 0x80090148: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x8009014C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80090150: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x80090154: lw          $t6, 0x3934($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X3934);
    // 0x80090158: ori         $at, $zero, 0xE088
    ctx->r1 = 0 | 0XE088;
    // 0x8009015C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090160: sll         $t7, $t6, 6
    ctx->r15 = S32(ctx->r14 << 6);
    // 0x80090164: addu        $t9, $a0, $t7
    ctx->r25 = ADD32(ctx->r4, ctx->r15);
    // 0x80090168: addu        $t8, $t9, $at
    ctx->r24 = ADD32(ctx->r25, ctx->r1);
    // 0x8009016C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
L_80090170:
    // 0x80090170: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80090174: lw          $t6, -0x7E90($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X7E90);
    // 0x80090178: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8009017C: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090180: bne         $t0, $t6, L_800901CC
    if (ctx->r8 != ctx->r14) {
        // 0x80090184: lui         $t9, 0xB600
        ctx->r25 = S32(0XB600 << 16);
            goto L_800901CC;
    }
    // 0x80090184: lui         $t9, 0xB600
    ctx->r25 = S32(0XB600 << 16);
    // 0x80090188: lw          $t7, -0x54D8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D8);
    // 0x8009018C: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x80090190: lui         $t6, 0xB700
    ctx->r14 = S32(0XB700 << 16);
    { extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r15)); }
    // 0x80090194: bnel        $t3, $t7, L_800901D0
    if (ctx->r11 != ctx->r15) {
        // 0x80090198: addiu       $a2, $a2, 0x8
        ctx->r6 = ADD32(ctx->r6, 0X8);
            goto L_800901D0;
    }
    goto skip_0;
    // 0x80090198: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    skip_0:
    // 0x8009019C: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800901A0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800901A4: lui         $t9, 0xB600
    ctx->r25 = S32(0XB600 << 16);
    // 0x800901A8: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800901AC: lui         $t7, 0x1
    ctx->r15 = S32(0X1 << 16);
    // 0x800901B0: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x800901B4: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x800901B8: ori         $t7, $t7, 0x204
    ctx->r15 = ctx->r15 | 0X204;
    // 0x800901BC: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x800901C0: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800901C4: b           L_800901F4
    // 0x800901C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_800901F4;
    // 0x800901C8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_800901CC:
    // 0x800901CC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_800901D0:
    // 0x800901D0: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x800901D4: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800901D8: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x800901DC: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x800901E0: lui         $t6, 0xB700
    ctx->r14 = S32(0XB700 << 16);
    // 0x800901E4: addiu       $t7, $zero, 0x204
    ctx->r15 = ADD32(0, 0X204);
    // 0x800901E8: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x800901EC: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800901F0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_800901F4:
    // 0x800901F4: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800901F8: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x800901FC: addiu       $t9, $t9, 0x2D0
    ctx->r25 = ADD32(ctx->r25, 0X2D0);
    // 0x80090200: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80090204: sw          $ra, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r31;
    // 0x80090208: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8009020C: lw          $t8, -0x7E90($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E90);
    // 0x80090210: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090214: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090218: bne         $t0, $t8, L_800903B4
    if (ctx->r8 != ctx->r24) {
        // 0x8009021C: lui         $t6, 0xBA00
        ctx->r14 = S32(0XBA00 << 16);
            goto L_800903B4;
    }
    // 0x8009021C: lui         $t6, 0xBA00
    ctx->r14 = S32(0XBA00 << 16);
    // 0x80090220: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090224: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090228: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x8009022C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80090230: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090234: ori         $t6, $t6, 0x1402
    ctx->r14 = ctx->r14 | 0X1402;
    // 0x80090238: lui         $t7, 0x10
    ctx->r15 = S32(0X10 << 16);
    // 0x8009023C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090240: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80090244: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80090248: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x8009024C: lui         $t8, 0xCB02
    ctx->r24 = S32(0XCB02 << 16);
    // 0x80090250: ori         $t8, $t8, 0x4000
    ctx->r24 = ctx->r24 | 0X4000;
    // 0x80090254: ori         $t9, $t9, 0x31D
    ctx->r25 = ctx->r25 | 0X31D;
    // 0x80090258: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009025C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80090260: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80090264: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090268: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x8009026C: lui         $t7, 0xFFFC
    ctx->r15 = S32(0XFFFC << 16);
    // 0x80090270: ori         $t7, $t7, 0xF238
    ctx->r15 = ctx->r15 | 0XF238;
    // 0x80090274: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x80090278: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009027C: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x80090280: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x80090284: or          $t0, $a2, $zero
    ctx->r8 = ctx->r6 | 0;
    // 0x80090288: lui         $t9, 0xF800
    ctx->r25 = S32(0XF800 << 16);
    // 0x8009028C: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x80090290: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80090294: lw          $t8, -0x54D4($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54D4);
    // 0x80090298: addiu       $t5, $zero, 0x110
    ctx->r13 = ADD32(0, 0X110);
    // 0x8009029C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800902A0: multu       $t8, $t5
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800902A4: addiu       $t7, $t7, -0x4FA8
    ctx->r15 = ADD32(ctx->r15, -0X4FA8);
    // 0x800902A8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800902AC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800902B0: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x800902B4: ori         $at, $at, 0xF400
    ctx->r1 = ctx->r1 | 0XF400;
    // 0x800902B8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800902BC: mflo        $t6
    ctx->r14 = lo;
    // 0x800902C0: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800902C4: lw          $t9, 0x94($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X94);
    // 0x800902C8: lw          $t7, 0x88($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X88);
    // 0x800902CC: andi        $t8, $t9, 0xFF
    ctx->r24 = ctx->r25 & 0XFF;
    // 0x800902D0: sll         $t9, $t7, 24
    ctx->r25 = S32(ctx->r15 << 24);
    // 0x800902D4: lw          $t7, 0x8C($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X8C);
    // 0x800902D8: or          $t6, $t8, $t9
    ctx->r14 = ctx->r24 | ctx->r25;
    // 0x800902DC: andi        $t8, $t7, 0xFF
    ctx->r24 = ctx->r15 & 0XFF;
    // 0x800902E0: sll         $t9, $t8, 16
    ctx->r25 = S32(ctx->r24 << 16);
    // 0x800902E4: lw          $t8, 0x90($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X90);
    // 0x800902E8: or          $t7, $t6, $t9
    ctx->r15 = ctx->r14 | ctx->r25;
    // 0x800902EC: andi        $t6, $t8, 0xFF
    ctx->r14 = ctx->r24 & 0XFF;
    // 0x800902F0: sll         $t9, $t6, 8
    ctx->r25 = S32(ctx->r14 << 8);
    // 0x800902F4: or          $t8, $t7, $t9
    ctx->r24 = ctx->r15 | ctx->r25;
    // 0x800902F8: lui         $t6, 0xBC00
    ctx->r14 = S32(0XBC00 << 16);
    // 0x800902FC: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x80090300: ori         $t6, $t6, 0x8
    ctx->r14 = ctx->r14 | 0X8;
    // 0x80090304: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x80090308: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8009030C: lw          $t7, -0x54D4($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D4);
    // 0x80090310: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x80090314: addiu       $t8, $t8, -0x4FA8
    ctx->r24 = ADD32(ctx->r24, -0X4FA8);
    // 0x80090318: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009031C: mflo        $t9
    ctx->r25 = lo;
    // 0x80090320: addu        $v0, $t9, $t8
    ctx->r2 = ADD32(ctx->r25, ctx->r24);
    // 0x80090324: lw          $a0, 0x98($v0)
    ctx->r4 = MEM_W(ctx->r2, 0X98);
    // 0x80090328: lw          $t6, 0x9C($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X9C);
    // 0x8009032C: negu        $t7, $a0
    ctx->r15 = SUB32(0, ctx->r4);
    // 0x80090330: subu        $a1, $t6, $a0
    ctx->r5 = SUB32(ctx->r14, ctx->r4);
    // 0x80090334: sll         $t9, $t7, 8
    ctx->r25 = S32(ctx->r15 << 8);
    // 0x80090338: addu        $t8, $t9, $at
    ctx->r24 = ADD32(ctx->r25, ctx->r1);
    // 0x8009033C: div         $zero, $t8, $a1
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r5)));
    // 0x80090340: lui         $t9, 0x1
    ctx->r25 = S32(0X1 << 16);
    // 0x80090344: ori         $t9, $t9, 0xF400
    ctx->r25 = ctx->r25 | 0XF400;
    // 0x80090348: mflo        $t6
    ctx->r14 = lo;
    // 0x8009034C: andi        $t7, $t6, 0xFFFF
    ctx->r15 = ctx->r14 & 0XFFFF;
    // 0x80090350: bne         $a1, $zero, L_8009035C
    if (ctx->r5 != 0) {
        // 0x80090354: nop
    
            goto L_8009035C;
    }
    // 0x80090354: nop

    // 0x80090358: break       7
    do_break(2148074328);
L_8009035C:
    // 0x8009035C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090360: bne         $a1, $at, L_80090374
    if (ctx->r5 != ctx->r1) {
        // 0x80090364: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090374;
    }
    // 0x80090364: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090368: bne         $t8, $at, L_80090374
    if (ctx->r24 != ctx->r1) {
        // 0x8009036C: nop
    
            goto L_80090374;
    }
    // 0x8009036C: nop

    // 0x80090370: break       6
    do_break(2148074352);
L_80090374:
    // 0x80090374: div         $zero, $t9, $a1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r5))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r5)));
    // 0x80090378: mflo        $t8
    ctx->r24 = lo;
    // 0x8009037C: andi        $t6, $t8, 0xFFFF
    ctx->r14 = ctx->r24 & 0XFFFF;
    // 0x80090380: bne         $a1, $zero, L_8009038C
    if (ctx->r5 != 0) {
        // 0x80090384: nop
    
            goto L_8009038C;
    }
    // 0x80090384: nop

    // 0x80090388: break       7
    do_break(2148074376);
L_8009038C:
    // 0x8009038C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090390: bne         $a1, $at, L_800903A4
    if (ctx->r5 != ctx->r1) {
        // 0x80090394: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800903A4;
    }
    // 0x80090394: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090398: bne         $t9, $at, L_800903A4
    if (ctx->r25 != ctx->r1) {
        // 0x8009039C: nop
    
            goto L_800903A4;
    }
    // 0x8009039C: nop

    // 0x800903A0: break       6
    do_break(2148074400);
L_800903A4:
    // 0x800903A4: sll         $t9, $t6, 16
    ctx->r25 = S32(ctx->r14 << 16);
    // 0x800903A8: or          $t8, $t7, $t9
    ctx->r24 = ctx->r15 | ctx->r25;
    // 0x800903AC: b           L_80090420
    // 0x800903B0: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
        goto L_80090420;
    // 0x800903B0: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
L_800903B4:
    // 0x800903B4: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800903B8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800903BC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800903C0: lui         $t6, 0xBA00
    ctx->r14 = S32(0XBA00 << 16);
    // 0x800903C4: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x800903C8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x800903CC: ori         $t6, $t6, 0x1402
    ctx->r14 = ctx->r14 | 0X1402;
    // 0x800903D0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800903D4: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800903D8: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800903DC: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x800903E0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800903E4: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x800903E8: lui         $t9, 0xF0A
    ctx->r25 = S32(0XF0A << 16);
    // 0x800903EC: ori         $t9, $t9, 0x4000
    ctx->r25 = ctx->r25 | 0X4000;
    // 0x800903F0: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x800903F4: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x800903F8: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x800903FC: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x80090400: lui         $t6, 0xFFFC
    ctx->r14 = S32(0XFFFC << 16);
    // 0x80090404: lui         $t8, 0xFCFF
    ctx->r24 = S32(0XFCFF << 16);
    // 0x80090408: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x8009040C: ori         $t6, $t6, 0xF279
    ctx->r14 = ctx->r14 | 0XF279;
    // 0x80090410: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80090414: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x80090418: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009041C: addiu       $t5, $zero, 0x110
    ctx->r13 = ADD32(0, 0X110);
L_80090420:
    // 0x80090420: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80090424: lw          $t7, -0x54D8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D8);
    // 0x80090428: lui         $t4, 0x708
    ctx->r12 = S32(0X708 << 16);
    // 0x8009042C: ori         $t4, $t4, 0x200
    ctx->r12 = ctx->r12 | 0X200;
    { extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r15)); }
    // 0x80090430: bne         $t3, $t7, L_80090444
    if (ctx->r11 != ctx->r15) {
        // 0x80090434: lui         $t1, 0xFD10
        ctx->r9 = S32(0XFD10 << 16);
            goto L_80090444;
    }
    // 0x80090434: lui         $t1, 0xFD10
    ctx->r9 = S32(0XFD10 << 16);
    // 0x80090438: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009043C: lw          $t9, -0x19B4($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X19B4);
    // 0x80090440: bne         $t3, $t9, L_80090454
    if (ctx->r11 != ctx->r25) {
        // 0x80090444: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_80090454;
    }
L_80090444:
    // 0x80090444: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80090448: lw          $t8, -0x7E90($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E90);
    // 0x8009044C: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x80090450: bne         $t8, $at, L_80090558
    if (ctx->r24 != ctx->r1) {
        // 0x80090454: or          $v0, $a2, $zero
        ctx->r2 = ctx->r6 | 0;
            goto L_80090558;
    }
L_80090454:
    // 0x80090454: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090458: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009045C: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090460: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x80090464: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80090468: lui         $t6, 0xFD10
    ctx->r14 = S32(0XFD10 << 16);
    // 0x8009046C: lui         $t7, 0x800
    ctx->r15 = S32(0X800 << 16);
    // 0x80090470: addiu       $t7, $t7, 0x1400
    ctx->r15 = ADD32(ctx->r15, 0X1400);
    // 0x80090474: ori         $t6, $t6, 0xF
    ctx->r14 = ctx->r14 | 0XF;
    // 0x80090478: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009047C: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090480: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x80090484: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x80090488: lui         $t9, 0x701
    ctx->r25 = S32(0X701 << 16);
    // 0x8009048C: lui         $t0, 0xF510
    ctx->r8 = S32(0XF510 << 16);
    // 0x80090490: ori         $t9, $t9, 0xC140
    ctx->r25 = ctx->r25 | 0XC140;
    // 0x80090494: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090498: ori         $t0, $t0, 0x800
    ctx->r8 = ctx->r8 | 0X800;
    // 0x8009049C: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x800904A0: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x800904A4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800904A8: sw          $t0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r8;
    // 0x800904AC: lui         $t8, 0xE600
    ctx->r24 = S32(0XE600 << 16);
    // 0x800904B0: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x800904B4: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x800904B8: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x800904BC: lui         $t7, 0x703
    ctx->r15 = S32(0X703 << 16);
    // 0x800904C0: ori         $t7, $t7, 0xC1FC
    ctx->r15 = ctx->r15 | 0XC1FC;
    // 0x800904C4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800904C8: lui         $t6, 0xF400
    ctx->r14 = S32(0XF400 << 16);
    // 0x800904CC: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x800904D0: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800904D4: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x800904D8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800904DC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800904E0: lui         $t9, 0x1
    ctx->r25 = S32(0X1 << 16);
    // 0x800904E4: ori         $t9, $t9, 0xC140
    ctx->r25 = ctx->r25 | 0XC140;
    // 0x800904E8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800904EC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x800904F0: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x800904F4: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x800904F8: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800904FC: sw          $t0, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r8;
    // 0x80090500: lui         $t6, 0x3
    ctx->r14 = S32(0X3 << 16);
    // 0x80090504: ori         $t6, $t6, 0xC1FC
    ctx->r14 = ctx->r14 | 0XC1FC;
    // 0x80090508: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009050C: lui         $t8, 0xF200
    ctx->r24 = S32(0XF200 << 16);
    // 0x80090510: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x80090514: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x80090518: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x8009051C: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x80090520: addiu       $t7, $t7, 0x3F0
    ctx->r15 = ADD32(ctx->r15, 0X3F0);
    { extern uint32_t wr64_sunny_sky_bottom_draw(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_bottom_draw(rdram, (uint32_t)ctx->r15)); }
    // 0x80090524: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x80090528: sw          $ra, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r31;
    // 0x8009052C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80090530: lw          $t9, -0x7E90($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7E90);
    // 0x80090534: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090538: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x8009053C: bne         $t9, $at, L_80090558
    if (ctx->r25 != ctx->r1) {
        // 0x80090540: or          $v0, $a2, $zero
        ctx->r2 = ctx->r6 | 0;
            goto L_80090558;
    }
    // 0x80090540: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090544: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80090548: addiu       $t8, $t8, 0x430
    ctx->r24 = ADD32(ctx->r24, 0X430);
    // 0x8009054C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80090550: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090554: sw          $ra, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r31;
L_80090558:
    // 0x80090558: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009055C: lw          $t6, -0x54D4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D4);
    // 0x80090560: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090564: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80090568: multu       $t6, $t5
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009056C: addiu       $t8, $t8, 0x330
    ctx->r24 = ADD32(ctx->r24, 0X330);
    // 0x80090570: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090574: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80090578: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x8009057C: sw          $ra, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r31;
    // 0x80090580: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090584: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80090588: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x8009058C: lui         $t6, 0x800
    ctx->r14 = S32(0X800 << 16);
    // 0x80090590: addiu       $t9, $t9, -0x4FA8
    ctx->r25 = ADD32(ctx->r25, -0X4FA8);
    // 0x80090594: mflo        $t7
    ctx->r15 = lo;
    // 0x80090598: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x8009059C: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x800905A0: addiu       $t6, $t6, 0x0
    ctx->r14 = ADD32(ctx->r14, 0X0);
    // 0x800905A4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800905A8: addu        $v0, $t7, $t9
    ctx->r2 = ADD32(ctx->r15, ctx->r25);
    // 0x800905AC: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x800905B0: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x800905B4: lui         $t7, 0xF510
    ctx->r15 = S32(0XF510 << 16);
    // 0x800905B8: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x800905BC: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x800905C0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800905C4: or          $t0, $a2, $zero
    ctx->r8 = ctx->r6 | 0;
    // 0x800905C8: sw          $t4, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r12;
    // 0x800905CC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800905D0: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x800905D4: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x800905D8: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800905DC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800905E0: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x800905E4: lui         $t8, 0xF300
    ctx->r24 = S32(0XF300 << 16);
    // 0x800905E8: lui         $t5, 0x70F
    ctx->r13 = S32(0X70F << 16);
    // 0x800905EC: ori         $t5, $t5, 0xF800
    ctx->r13 = ctx->r13 | 0XF800;
    // 0x800905F0: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x800905F4: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800905F8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800905FC: sw          $t5, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r13;
    // 0x80090600: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090604: lui         $t6, 0xF510
    ctx->r14 = S32(0XF510 << 16);
    // 0x80090608: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x8009060C: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x80090610: sw          $t2, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r10;
    // 0x80090614: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x80090618: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x8009061C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x80090620: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090624: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090628: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x8009062C: ori         $t8, $zero, 0xC0FC
    ctx->r24 = 0 | 0XC0FC;
    // 0x80090630: lui         $t9, 0xF200
    ctx->r25 = S32(0XF200 << 16);
    // 0x80090634: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x80090638: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x8009063C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80090640: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x80090644: lui         $t9, 0xBA00
    ctx->r25 = S32(0XBA00 << 16);
    // 0x80090648: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    { extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r14 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r14)); }
    // 0x8009064C: bne         $t3, $t6, L_80090BD8
    if (ctx->r11 != ctx->r14) {
        // 0x80090650: ori         $t9, $t9, 0x1402
        ctx->r25 = ctx->r25 | 0X1402;
            goto L_80090BD8;
    }
    // 0x80090650: ori         $t9, $t9, 0x1402
    ctx->r25 = ctx->r25 | 0X1402;
    // 0x80090654: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090658: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009065C: lui         $t7, 0x800
    ctx->r15 = S32(0X800 << 16);
    // 0x80090660: addiu       $t7, $t7, 0x200
    ctx->r15 = ADD32(ctx->r15, 0X200);
    // 0x80090664: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090668: lui         $t9, 0xF510
    ctx->r25 = S32(0XF510 << 16);
    // 0x8009066C: ori         $t9, $t9, 0x100
    ctx->r25 = ctx->r25 | 0X100;
    // 0x80090670: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090674: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x80090678: sw          $t1, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r9;
    // 0x8009067C: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x80090680: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090684: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090688: sw          $t4, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r12;
    // 0x8009068C: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090690: lui         $t8, 0xE600
    ctx->r24 = S32(0XE600 << 16);
    // 0x80090694: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x80090698: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x8009069C: lui         $t6, 0xF300
    ctx->r14 = S32(0XF300 << 16);
    // 0x800906A0: sw          $t6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r14;
    // 0x800906A4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800906A8: or          $t0, $a2, $zero
    ctx->r8 = ctx->r6 | 0;
    // 0x800906AC: sw          $t5, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r13;
    // 0x800906B0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800906B4: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x800906B8: lui         $t7, 0xF510
    ctx->r15 = S32(0XF510 << 16);
    // 0x800906BC: ori         $t7, $t7, 0x300
    ctx->r15 = ctx->r15 | 0X300;
    // 0x800906C0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800906C4: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x800906C8: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x800906CC: lui         $t9, 0x108
    ctx->r25 = S32(0X108 << 16);
    // 0x800906D0: ori         $t9, $t9, 0x200
    ctx->r25 = ctx->r25 | 0X200;
    // 0x800906D4: sw          $t7, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r15;
    // 0x800906D8: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x800906DC: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x800906E0: lui         $t6, 0x100
    ctx->r14 = S32(0X100 << 16);
    // 0x800906E4: ori         $t6, $t6, 0xC0FC
    ctx->r14 = ctx->r14 | 0XC0FC;
    // 0x800906E8: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x800906EC: lui         $t8, 0xF200
    ctx->r24 = S32(0XF200 << 16);
    // 0x800906F0: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x800906F4: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x800906F8: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x800906FC: lui         $t7, 0xFB00
    ctx->r15 = S32(0XFB00 << 16);
    // 0x80090700: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x80090704: lwc1        $f4, 0x108($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X108);
    // 0x80090708: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x8009070C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80090710: mfc1        $v1, $f6
    ctx->r3 = (int32_t)ctx->f6.u32l;
    // 0x80090714: nop

    // 0x80090718: andi        $t8, $v1, 0xFF
    ctx->r24 = ctx->r3 & 0XFF;
    // 0x8009071C: sll         $t6, $t8, 24
    ctx->r14 = S32(ctx->r24 << 24);
    // 0x80090720: sll         $t7, $t8, 16
    ctx->r15 = S32(ctx->r24 << 16);
    // 0x80090724: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x80090728: sll         $t8, $t8, 8
    ctx->r24 = S32(ctx->r24 << 8);
    // 0x8009072C: or          $t6, $t9, $t8
    ctx->r14 = ctx->r25 | ctx->r24;
    // 0x80090730: ori         $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 | 0XFF;
    // 0x80090734: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x80090738: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x8009073C: lb          $t9, -0x6778($t9)
    ctx->r25 = MEM_B(ctx->r25, -0X6778);
    // 0x80090740: lui         $t8, 0x801C
    ctx->r24 = S32(0X801C << 16);
    { extern uint32_t wr64_sunny_sky_fog_update(uint8_t*, uint32_t); ctx->r25 = S32(wr64_sunny_sky_fog_update(rdram, (uint32_t)ctx->r25)); }
    // 0x80090744: beql        $t9, $zero, L_80090B8C
    if (ctx->r25 == 0) {
        // 0x80090748: or          $v0, $a2, $zero
        ctx->r2 = ctx->r6 | 0;
            goto L_80090B8C;
    }
    goto skip_1;
    // 0x80090748: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    skip_1:
    // 0x8009074C: lw          $t8, 0x1FD0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X1FD0);
    // 0x80090750: beql        $t8, $zero, L_800907A4
    if (ctx->r24 == 0) {
        // 0x80090754: lwc1        $f10, 0x108($v0)
        ctx->f10.u32l = MEM_W(ctx->r2, 0X108);
            goto L_800907A4;
    }
    goto skip_2;
    // 0x80090754: lwc1        $f10, 0x108($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X108);
    skip_2:
    // 0x80090758: lui         $at, 0x437F
    ctx->r1 = S32(0X437F << 16);
    // 0x8009075C: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x80090760: lwc1        $f0, 0x108($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X108);
    // 0x80090764: c.lt.s      $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f0.fl < ctx->f12.fl;
    // 0x80090768: nop

    // 0x8009076C: bc1fl       L_800907A4
    if (!c1cs) {
        // 0x80090770: lwc1        $f10, 0x108($v0)
        ctx->f10.u32l = MEM_W(ctx->r2, 0X108);
            goto L_800907A4;
    }
    goto skip_3;
    // 0x80090770: lwc1        $f10, 0x108($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X108);
    skip_3:
    // 0x80090774: lui         $at, 0x3FC0
    ctx->r1 = S32(0X3FC0 << 16);
    // 0x80090778: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009077C: nop

    // 0x80090780: add.s       $f2, $f0, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f0.fl + ctx->f8.fl;
    // 0x80090784: c.lt.s      $f12, $f2
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f12.fl < ctx->f2.fl;
    // 0x80090788: nop

    // 0x8009078C: bc1fl       L_800907A0
    if (!c1cs) {
        // 0x80090790: swc1        $f2, 0x108($v0)
        MEM_W(0X108, ctx->r2) = ctx->f2.u32l;
            goto L_800907A0;
    }
    goto skip_4;
    // 0x80090790: swc1        $f2, 0x108($v0)
    MEM_W(0X108, ctx->r2) = ctx->f2.u32l;
    skip_4:
    // 0x80090794: b           L_800907A0
    // 0x80090798: swc1        $f12, 0x108($v0)
    MEM_W(0X108, ctx->r2) = ctx->f12.u32l;
        goto L_800907A0;
    // 0x80090798: swc1        $f12, 0x108($v0)
    MEM_W(0X108, ctx->r2) = ctx->f12.u32l;
    // 0x8009079C: swc1        $f2, 0x108($v0)
    MEM_W(0X108, ctx->r2) = ctx->f2.u32l;
L_800907A0:
    // 0x800907A0: lwc1        $f10, 0x108($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X108);
L_800907A4:
    // 0x800907A4: lw          $a1, 0x18($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X18);
    // 0x800907A8: lw          $t7, 0x30($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X30);
    // 0x800907AC: trunc.w.s   $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x800907B0: addiu       $a0, $zero, 0xFF
    ctx->r4 = ADD32(0, 0XFF);
    // 0x800907B4: subu        $t9, $t7, $a1
    ctx->r25 = SUB32(ctx->r15, ctx->r5);
    // 0x800907B8: lw          $a3, 0x1C($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X1C);
    // 0x800907BC: mfc1        $v1, $f16
    ctx->r3 = (int32_t)ctx->f16.u32l;
    // 0x800907C0: lw          $t0, 0x20($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X20);
    // 0x800907C4: lw          $t1, 0x24($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X24);
    // 0x800907C8: multu       $t9, $v1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800907CC: lw          $t9, 0x34($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X34);
    // 0x800907D0: mflo        $t8
    ctx->r24 = lo;
    // 0x800907D4: nop

    // 0x800907D8: nop

    // 0x800907DC: div         $zero, $t8, $a0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r4)));
    // 0x800907E0: mflo        $t6
    ctx->r14 = lo;
    // 0x800907E4: addu        $t7, $t6, $a1
    ctx->r15 = ADD32(ctx->r14, ctx->r5);
    // 0x800907E8: bne         $a0, $zero, L_800907F4
    if (ctx->r4 != 0) {
        // 0x800907EC: nop
    
            goto L_800907F4;
    }
    // 0x800907EC: nop

    // 0x800907F0: break       7
    do_break(2148075504);
L_800907F4:
    // 0x800907F4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800907F8: bne         $a0, $at, L_8009080C
    if (ctx->r4 != ctx->r1) {
        // 0x800907FC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009080C;
    }
    // 0x800907FC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090800: bne         $t8, $at, L_8009080C
    if (ctx->r24 != ctx->r1) {
        // 0x80090804: nop
    
            goto L_8009080C;
    }
    // 0x80090804: nop

    // 0x80090808: break       6
    do_break(2148075528);
L_8009080C:
    // 0x8009080C: subu        $t8, $t9, $a3
    ctx->r24 = SUB32(ctx->r25, ctx->r7);
    // 0x80090810: multu       $t8, $v1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80090814: lw          $t8, 0x38($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X38);
    // 0x80090818: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x8009081C: lw          $a1, 0x28($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X28);
    // 0x80090820: mflo        $t6
    ctx->r14 = lo;
    // 0x80090824: nop

    // 0x80090828: nop

    // 0x8009082C: div         $zero, $t6, $a0
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r4)));
    // 0x80090830: mflo        $t7
    ctx->r15 = lo;
    // 0x80090834: addu        $t9, $t7, $a3
    ctx->r25 = ADD32(ctx->r15, ctx->r7);
    // 0x80090838: bne         $a0, $zero, L_80090844
    if (ctx->r4 != 0) {
        // 0x8009083C: nop
    
            goto L_80090844;
    }
    // 0x8009083C: nop

    // 0x80090840: break       7
    do_break(2148075584);
L_80090844:
    // 0x80090844: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090848: bne         $a0, $at, L_8009085C
    if (ctx->r4 != ctx->r1) {
        // 0x8009084C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009085C;
    }
    // 0x8009084C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090850: bne         $t6, $at, L_8009085C
    if (ctx->r14 != ctx->r1) {
        // 0x80090854: nop
    
            goto L_8009085C;
    }
    // 0x80090854: nop

    // 0x80090858: break       6
    do_break(2148075608);
L_8009085C:
    // 0x8009085C: subu        $t6, $t8, $t0
    ctx->r14 = SUB32(ctx->r24, ctx->r8);
    // 0x80090860: multu       $t6, $v1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80090864: lw          $t6, 0x3C($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X3C);
    // 0x80090868: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x8009086C: lw          $a3, 0x2C($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X2C);
    // 0x80090870: mflo        $t7
    ctx->r15 = lo;
    // 0x80090874: nop

    // 0x80090878: nop

    // 0x8009087C: div         $zero, $t7, $a0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r4)));
    // 0x80090880: mflo        $t9
    ctx->r25 = lo;
    // 0x80090884: addu        $t8, $t9, $t0
    ctx->r24 = ADD32(ctx->r25, ctx->r8);
    // 0x80090888: bne         $a0, $zero, L_80090894
    if (ctx->r4 != 0) {
        // 0x8009088C: nop
    
            goto L_80090894;
    }
    // 0x8009088C: nop

    // 0x80090890: break       7
    do_break(2148075664);
L_80090894:
    // 0x80090894: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090898: bne         $a0, $at, L_800908AC
    if (ctx->r4 != ctx->r1) {
        // 0x8009089C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800908AC;
    }
    // 0x8009089C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800908A0: bne         $t7, $at, L_800908AC
    if (ctx->r15 != ctx->r1) {
        // 0x800908A4: nop
    
            goto L_800908AC;
    }
    // 0x800908A4: nop

    // 0x800908A8: break       6
    do_break(2148075688);
L_800908AC:
    // 0x800908AC: subu        $t7, $t6, $t1
    ctx->r15 = SUB32(ctx->r14, ctx->r9);
    // 0x800908B0: multu       $t7, $v1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800908B4: lw          $t7, 0x40($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X40);
    // 0x800908B8: sw          $t8, 0x8($v0)
    MEM_W(0X8, ctx->r2) = ctx->r24;
    // 0x800908BC: lw          $t0, 0x58($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X58);
    // 0x800908C0: mflo        $t9
    ctx->r25 = lo;
    // 0x800908C4: nop

    // 0x800908C8: nop

    // 0x800908CC: div         $zero, $t9, $a0
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r4)));
    // 0x800908D0: mflo        $t8
    ctx->r24 = lo;
    // 0x800908D4: addu        $t6, $t8, $t1
    ctx->r14 = ADD32(ctx->r24, ctx->r9);
    // 0x800908D8: bne         $a0, $zero, L_800908E4
    if (ctx->r4 != 0) {
        // 0x800908DC: nop
    
            goto L_800908E4;
    }
    // 0x800908DC: nop

    // 0x800908E0: break       7
    do_break(2148075744);
L_800908E4:
    // 0x800908E4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800908E8: bne         $a0, $at, L_800908FC
    if (ctx->r4 != ctx->r1) {
        // 0x800908EC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800908FC;
    }
    // 0x800908EC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800908F0: bne         $t9, $at, L_800908FC
    if (ctx->r25 != ctx->r1) {
        // 0x800908F4: nop
    
            goto L_800908FC;
    }
    // 0x800908F4: nop

    // 0x800908F8: break       6
    do_break(2148075768);
L_800908FC:
    // 0x800908FC: subu        $t9, $t7, $a1
    ctx->r25 = SUB32(ctx->r15, ctx->r5);
    // 0x80090900: multu       $t9, $v1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80090904: lw          $t9, 0x44($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X44);
    // 0x80090908: sw          $t6, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r14;
    // 0x8009090C: lw          $t1, 0x5C($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X5C);
    // 0x80090910: mflo        $t8
    ctx->r24 = lo;
    // 0x80090914: nop

    // 0x80090918: nop

    // 0x8009091C: div         $zero, $t8, $a0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r4)));
    // 0x80090920: mflo        $t6
    ctx->r14 = lo;
    // 0x80090924: addu        $t7, $t6, $a1
    ctx->r15 = ADD32(ctx->r14, ctx->r5);
    // 0x80090928: bne         $a0, $zero, L_80090934
    if (ctx->r4 != 0) {
        // 0x8009092C: nop
    
            goto L_80090934;
    }
    // 0x8009092C: nop

    // 0x80090930: break       7
    do_break(2148075824);
L_80090934:
    // 0x80090934: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090938: bne         $a0, $at, L_8009094C
    if (ctx->r4 != ctx->r1) {
        // 0x8009093C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009094C;
    }
    // 0x8009093C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090940: bne         $t8, $at, L_8009094C
    if (ctx->r24 != ctx->r1) {
        // 0x80090944: nop
    
            goto L_8009094C;
    }
    // 0x80090944: nop

    // 0x80090948: break       6
    do_break(2148075848);
L_8009094C:
    // 0x8009094C: subu        $t8, $t9, $a3
    ctx->r24 = SUB32(ctx->r25, ctx->r7);
    // 0x80090950: multu       $t8, $v1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80090954: lw          $t8, 0x68($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X68);
    // 0x80090958: sw          $t7, 0x10($v0)
    MEM_W(0X10, ctx->r2) = ctx->r15;
    // 0x8009095C: lw          $a1, 0x60($v0)
    ctx->r5 = MEM_W(ctx->r2, 0X60);
    // 0x80090960: mflo        $t6
    ctx->r14 = lo;
    // 0x80090964: nop

    // 0x80090968: nop

    // 0x8009096C: div         $zero, $t6, $a0
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r4)));
    // 0x80090970: mflo        $t7
    ctx->r15 = lo;
    // 0x80090974: addu        $t9, $t7, $a3
    ctx->r25 = ADD32(ctx->r15, ctx->r7);
    // 0x80090978: bne         $a0, $zero, L_80090984
    if (ctx->r4 != 0) {
        // 0x8009097C: nop
    
            goto L_80090984;
    }
    // 0x8009097C: nop

    // 0x80090980: break       7
    do_break(2148075904);
L_80090984:
    // 0x80090984: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090988: bne         $a0, $at, L_8009099C
    if (ctx->r4 != ctx->r1) {
        // 0x8009098C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009099C;
    }
    // 0x8009098C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090990: bne         $t6, $at, L_8009099C
    if (ctx->r14 != ctx->r1) {
        // 0x80090994: nop
    
            goto L_8009099C;
    }
    // 0x80090994: nop

    // 0x80090998: break       6
    do_break(2148075928);
L_8009099C:
    // 0x8009099C: subu        $t6, $t8, $t0
    ctx->r14 = SUB32(ctx->r24, ctx->r8);
    // 0x800909A0: multu       $t6, $v1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800909A4: lw          $t6, 0x6C($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X6C);
    // 0x800909A8: sw          $t9, 0x14($v0)
    MEM_W(0X14, ctx->r2) = ctx->r25;
    // 0x800909AC: mflo        $t7
    ctx->r15 = lo;
    // 0x800909B0: nop

    // 0x800909B4: nop

    // 0x800909B8: div         $zero, $t7, $a0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r4)));
    // 0x800909BC: mflo        $t9
    ctx->r25 = lo;
    // 0x800909C0: addu        $t8, $t9, $t0
    ctx->r24 = ADD32(ctx->r25, ctx->r8);
    // 0x800909C4: bne         $a0, $zero, L_800909D0
    if (ctx->r4 != 0) {
        // 0x800909C8: nop
    
            goto L_800909D0;
    }
    // 0x800909C8: nop

    // 0x800909CC: break       7
    do_break(2148075980);
L_800909D0:
    // 0x800909D0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800909D4: bne         $a0, $at, L_800909E8
    if (ctx->r4 != ctx->r1) {
        // 0x800909D8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800909E8;
    }
    // 0x800909D8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800909DC: bne         $t7, $at, L_800909E8
    if (ctx->r15 != ctx->r1) {
        // 0x800909E0: nop
    
            goto L_800909E8;
    }
    // 0x800909E0: nop

    // 0x800909E4: break       6
    do_break(2148076004);
L_800909E8:
    // 0x800909E8: subu        $t7, $t6, $t1
    ctx->r15 = SUB32(ctx->r14, ctx->r9);
    // 0x800909EC: multu       $t7, $v1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800909F0: lw          $t7, 0x70($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X70);
    // 0x800909F4: sw          $t8, 0x48($v0)
    MEM_W(0X48, ctx->r2) = ctx->r24;
    // 0x800909F8: mflo        $t9
    ctx->r25 = lo;
    // 0x800909FC: nop

    // 0x80090A00: nop

    // 0x80090A04: div         $zero, $t9, $a0
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r4)));
    // 0x80090A08: mflo        $t8
    ctx->r24 = lo;
    // 0x80090A0C: addu        $t6, $t8, $t1
    ctx->r14 = ADD32(ctx->r24, ctx->r9);
    // 0x80090A10: bne         $a0, $zero, L_80090A1C
    if (ctx->r4 != 0) {
        // 0x80090A14: nop
    
            goto L_80090A1C;
    }
    // 0x80090A14: nop

    // 0x80090A18: break       7
    do_break(2148076056);
L_80090A1C:
    // 0x80090A1C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090A20: bne         $a0, $at, L_80090A34
    if (ctx->r4 != ctx->r1) {
        // 0x80090A24: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090A34;
    }
    // 0x80090A24: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090A28: bne         $t9, $at, L_80090A34
    if (ctx->r25 != ctx->r1) {
        // 0x80090A2C: nop
    
            goto L_80090A34;
    }
    // 0x80090A2C: nop

    // 0x80090A30: break       6
    do_break(2148076080);
L_80090A34:
    // 0x80090A34: subu        $t9, $t7, $a1
    ctx->r25 = SUB32(ctx->r15, ctx->r5);
    // 0x80090A38: multu       $t9, $v1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r3)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80090A3C: sw          $t6, 0x4C($v0)
    MEM_W(0X4C, ctx->r2) = ctx->r14;
    // 0x80090A40: sll         $t9, $v1, 4
    ctx->r25 = S32(ctx->r3 << 4);
    // 0x80090A44: mflo        $t8
    ctx->r24 = lo;
    // 0x80090A48: nop

    // 0x80090A4C: nop

    // 0x80090A50: div         $zero, $t8, $a0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r4)));
    // 0x80090A54: mflo        $t6
    ctx->r14 = lo;
    // 0x80090A58: addu        $t7, $t6, $a1
    ctx->r15 = ADD32(ctx->r14, ctx->r5);
    // 0x80090A5C: bne         $a0, $zero, L_80090A68
    if (ctx->r4 != 0) {
        // 0x80090A60: nop
    
            goto L_80090A68;
    }
    // 0x80090A60: nop

    // 0x80090A64: break       7
    do_break(2148076132);
L_80090A68:
    // 0x80090A68: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090A6C: bne         $a0, $at, L_80090A80
    if (ctx->r4 != ctx->r1) {
        // 0x80090A70: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090A80;
    }
    // 0x80090A70: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090A74: bne         $t8, $at, L_80090A80
    if (ctx->r24 != ctx->r1) {
        // 0x80090A78: nop
    
            goto L_80090A80;
    }
    // 0x80090A78: nop

    // 0x80090A7C: break       6
    do_break(2148076156);
L_80090A80:
    // 0x80090A80: div         $zero, $t9, $a0
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r4)));
    // 0x80090A84: sw          $t7, 0x50($v0)
    MEM_W(0X50, ctx->r2) = ctx->r15;
    // 0x80090A88: mflo        $t8
    ctx->r24 = lo;
    // 0x80090A8C: sll         $t7, $v1, 3
    ctx->r15 = S32(ctx->r3 << 3);
    // 0x80090A90: addu        $t7, $t7, $v1
    ctx->r15 = ADD32(ctx->r15, ctx->r3);
    // 0x80090A94: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80090A98: div         $zero, $t7, $a0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r4)));
    // 0x80090A9C: bne         $a0, $zero, L_80090AA8
    if (ctx->r4 != 0) {
        // 0x80090AA0: nop
    
            goto L_80090AA8;
    }
    // 0x80090AA0: nop

    // 0x80090AA4: break       7
    do_break(2148076196);
L_80090AA8:
    // 0x80090AA8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090AAC: bne         $a0, $at, L_80090AC0
    if (ctx->r4 != ctx->r1) {
        // 0x80090AB0: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090AC0;
    }
    // 0x80090AB0: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090AB4: bne         $t9, $at, L_80090AC0
    if (ctx->r25 != ctx->r1) {
        // 0x80090AB8: nop
    
            goto L_80090AC0;
    }
    // 0x80090AB8: nop

    // 0x80090ABC: break       6
    do_break(2148076220);
L_80090AC0:
    // 0x80090AC0: mflo        $t9
    ctx->r25 = lo;
    // 0x80090AC4: addiu       $t6, $t8, 0x3D4
    ctx->r14 = ADD32(ctx->r24, 0X3D4);
    // 0x80090AC8: sw          $t6, 0x78($v0)
    MEM_W(0X78, ctx->r2) = ctx->r14;
    // 0x80090ACC: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80090AD0: addu        $t6, $t6, $v1
    ctx->r14 = ADD32(ctx->r14, ctx->r3);
    // 0x80090AD4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x80090AD8: div         $zero, $t6, $a0
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r4)));
    // 0x80090ADC: addiu       $t8, $t9, 0x3AC
    ctx->r24 = ADD32(ctx->r25, 0X3AC);
    // 0x80090AE0: sw          $t8, 0x98($v0)
    MEM_W(0X98, ctx->r2) = ctx->r24;
    // 0x80090AE4: sll         $t8, $v1, 4
    ctx->r24 = S32(ctx->r3 << 4);
    // 0x80090AE8: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x80090AEC: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80090AF0: addu        $t8, $t8, $v1
    ctx->r24 = ADD32(ctx->r24, ctx->r3);
    // 0x80090AF4: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80090AF8: subu        $t8, $t8, $v1
    ctx->r24 = SUB32(ctx->r24, ctx->r3);
    // 0x80090AFC: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x80090B00: bne         $a0, $zero, L_80090B0C
    if (ctx->r4 != 0) {
        // 0x80090B04: nop
    
            goto L_80090B0C;
    }
    // 0x80090B04: nop

    // 0x80090B08: break       7
    do_break(2148076296);
L_80090B0C:
    // 0x80090B0C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090B10: bne         $a0, $at, L_80090B24
    if (ctx->r4 != ctx->r1) {
        // 0x80090B14: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090B24;
    }
    // 0x80090B14: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090B18: bne         $t7, $at, L_80090B24
    if (ctx->r15 != ctx->r1) {
        // 0x80090B1C: nop
    
            goto L_80090B24;
    }
    // 0x80090B1C: nop

    // 0x80090B20: break       6
    do_break(2148076320);
L_80090B24:
    // 0x80090B24: mflo        $t7
    ctx->r15 = lo;
    // 0x80090B28: addiu       $t9, $t7, 0x3D4
    ctx->r25 = ADD32(ctx->r15, 0X3D4);
    // 0x80090B2C: bne         $a0, $zero, L_80090B38
    if (ctx->r4 != 0) {
        // 0x80090B30: nop
    
            goto L_80090B38;
    }
    // 0x80090B30: nop

    // 0x80090B34: break       7
    do_break(2148076340);
L_80090B38:
    // 0x80090B38: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090B3C: bne         $a0, $at, L_80090B50
    if (ctx->r4 != ctx->r1) {
        // 0x80090B40: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090B50;
    }
    // 0x80090B40: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090B44: bne         $t6, $at, L_80090B50
    if (ctx->r14 != ctx->r1) {
        // 0x80090B48: nop
    
            goto L_80090B50;
    }
    // 0x80090B48: nop

    // 0x80090B4C: break       6
    do_break(2148076364);
L_80090B50:
    // 0x80090B50: div         $zero, $t8, $a0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r4)));
    // 0x80090B54: mflo        $t6
    ctx->r14 = lo;
    // 0x80090B58: addiu       $t7, $t6, 0x64
    ctx->r15 = ADD32(ctx->r14, 0X64);
    // 0x80090B5C: sw          $t9, 0x9C($v0)
    MEM_W(0X9C, ctx->r2) = ctx->r25;
    // 0x80090B60: bne         $a0, $zero, L_80090B6C
    if (ctx->r4 != 0) {
        // 0x80090B64: nop
    
            goto L_80090B6C;
    }
    // 0x80090B64: nop

    // 0x80090B68: break       7
    do_break(2148076392);
L_80090B6C:
    // 0x80090B6C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80090B70: bne         $a0, $at, L_80090B84
    if (ctx->r4 != ctx->r1) {
        // 0x80090B74: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80090B84;
    }
    // 0x80090B74: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80090B78: bne         $t8, $at, L_80090B84
    if (ctx->r24 != ctx->r1) {
        // 0x80090B7C: nop
    
            goto L_80090B84;
    }
    // 0x80090B7C: nop

    // 0x80090B80: break       6
    do_break(2148076416);
L_80090B84:
    // 0x80090B84: sw          $t7, 0xA0($v0)
    MEM_W(0XA0, ctx->r2) = ctx->r15;
    // 0x80090B88: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_80090B8C:
    // 0x80090B8C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090B90: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090B94: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x80090B98: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80090B9C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090BA0: lui         $t9, 0xBA00
    ctx->r25 = S32(0XBA00 << 16);
    // 0x80090BA4: ori         $t9, $t9, 0x1402
    ctx->r25 = ctx->r25 | 0X1402;
    // 0x80090BA8: lui         $t8, 0x10
    ctx->r24 = S32(0X10 << 16);
    // 0x80090BAC: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090BB0: lui         $t6, 0xFC22
    ctx->r14 = S32(0XFC22 << 16);
    // 0x80090BB4: lui         $t7, 0x1FFC
    ctx->r15 = S32(0X1FFC << 16);
    // 0x80090BB8: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80090BBC: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x80090BC0: ori         $t7, $t7, 0xFA38
    ctx->r15 = ctx->r15 | 0XFA38;
    // 0x80090BC4: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x80090BC8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80090BCC: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80090BD0: b           L_80090C18
    // 0x80090BD4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_80090C18;
    // 0x80090BD4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090BD8:
    // 0x80090BD8: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090BDC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090BE0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090BE4: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
    // 0x80090BE8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80090BEC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090BF0: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090BF4: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80090BF8: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x80090BFC: lui         $t8, 0xFCFF
    ctx->r24 = S32(0XFCFF << 16);
    // 0x80090C00: lui         $t6, 0xFFFC
    ctx->r14 = S32(0XFFFC << 16);
    // 0x80090C04: ori         $t6, $t6, 0xF279
    ctx->r14 = ctx->r14 | 0XF279;
    // 0x80090C08: ori         $t8, $t8, 0xFFFF
    ctx->r24 = ctx->r24 | 0XFFFF;
    // 0x80090C0C: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x80090C10: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x80090C14: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090C18:
    // 0x80090C18: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80090C1C: lw          $t7, -0x54D4($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D4);
    // 0x80090C20: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090C24: lui         $t6, 0x400
    ctx->r14 = S32(0X400 << 16);
    // 0x80090C28: bne         $t7, $zero, L_80090C54
    if (ctx->r15 != 0) {
        // 0x80090C2C: lui         $v1, 0x800E
        ctx->r3 = S32(0X800E << 16);
            goto L_80090C54;
    }
    // 0x80090C2C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80090C30: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090C34: lui         $t9, 0x400
    ctx->r25 = S32(0X400 << 16);
    // 0x80090C38: lui         $t8, 0x600
    ctx->r24 = S32(0X600 << 16);
    // 0x80090C3C: addiu       $t8, $t8, 0xE0
    ctx->r24 = ADD32(ctx->r24, 0XE0);
    // 0x80090C40: ori         $t9, $t9, 0xE6F
    ctx->r25 = ctx->r25 | 0XE6F;
    // 0x80090C44: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x80090C48: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80090C4C: b           L_80090C6C
    // 0x80090C50: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
        goto L_80090C6C;
    // 0x80090C50: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090C54:
    // 0x80090C54: lui         $t7, 0x600
    ctx->r15 = S32(0X600 << 16);
    // 0x80090C58: addiu       $t7, $t7, 0x150
    ctx->r15 = ADD32(ctx->r15, 0X150);
    // 0x80090C5C: ori         $t6, $t6, 0xE6F
    ctx->r14 = ctx->r14 | 0XE6F;
    // 0x80090C60: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80090C64: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x80090C68: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090C6C:
    // 0x80090C6C: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090C70: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x80090C74: addiu       $t9, $t9, 0x3B8
    ctx->r25 = ADD32(ctx->r25, 0X3B8);
    // 0x80090C78: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80090C7C: sw          $ra, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r31;
    // 0x80090C80: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
    // 0x80090C84: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090C88: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    { extern uint32_t wr64_two_player_celestial_draw(uint8_t*, recomp_context*, uint32_t); ctx->r6 = S32(wr64_two_player_celestial_draw(rdram, ctx, (uint32_t)ctx->r6)); }
    // 0x80090C8C: bne         $t3, $v1, L_80090D44
    if (ctx->r11 != ctx->r3) {
        // 0x80090C90: nop
    
            goto L_80090D44;
    }
    // 0x80090C90: nop

    // 0x80090C94: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
    // 0x80090C98: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80090C9C: beq         $v0, $zero, L_80090CC4
    if (ctx->r2 == 0) {
        // 0x80090CA0: nop
    
            goto L_80090CC4;
    }
    // 0x80090CA0: nop

    // 0x80090CA4: beq         $v0, $at, L_80090CC4
    if (ctx->r2 == ctx->r1) {
        // 0x80090CA8: addiu       $at, $zero, 0x6
        ctx->r1 = ADD32(0, 0X6);
            goto L_80090CC4;
    }
    // 0x80090CA8: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x80090CAC: beq         $v0, $at, L_80090CE8
    if (ctx->r2 == ctx->r1) {
        // 0x80090CB0: addiu       $at, $zero, 0x7
        ctx->r1 = ADD32(0, 0X7);
            goto L_80090CE8;
    }
    // 0x80090CB0: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x80090CB4: beq         $v0, $at, L_80090D14
    if (ctx->r2 == ctx->r1) {
        // 0x80090CB8: lui         $t8, 0x801D
        ctx->r24 = S32(0X801D << 16);
            goto L_80090D14;
    }
    // 0x80090CB8: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x80090CBC: b           L_80090D44
    // 0x80090CC0: nop

        goto L_80090D44;
    // 0x80090CC0: nop

L_80090CC4:
    // 0x80090CC4: jal         0x8008D94C
    // 0x80090CC8: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_8008D94C(rdram, ctx);
        goto after_3;
    // 0x80090CC8: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_3:
    // 0x80090CCC: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80090CD0: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x80090CD4: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x80090CD8: lui         $ra, 0x600
    ctx->r31 = S32(0X600 << 16);
    // 0x80090CDC: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x80090CE0: b           L_80090D44
    // 0x80090CE4: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
        goto L_80090D44;
    // 0x80090CE4: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
L_80090CE8:
    // 0x80090CE8: jal         0x8008CFEC
    // 0x80090CEC: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_8008CFEC(rdram, ctx);
        goto after_4;
    // 0x80090CEC: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_4:
    // 0x80090CF0: jal         0x8008D454
    // 0x80090CF4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8008D454(rdram, ctx);
        goto after_5;
    // 0x80090CF4: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x80090CF8: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80090CFC: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x80090D00: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x80090D04: lui         $ra, 0x600
    ctx->r31 = S32(0X600 << 16);
    // 0x80090D08: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
    // 0x80090D0C: b           L_80090D44
    // 0x80090D10: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
        goto L_80090D44;
    // 0x80090D10: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
L_80090D14:
    // 0x80090D14: lw          $t8, -0x19C8($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19C8);
    // 0x80090D18: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    // 0x80090D1C: bne         $t8, $at, L_80090D44
    if (ctx->r24 != ctx->r1) {
        // 0x80090D20: nop
    
            goto L_80090D44;
    }
    // 0x80090D20: nop

    // 0x80090D24: jal         0x8008DFD0
    // 0x80090D28: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_8008DFD0(rdram, ctx);
        goto after_6;
    // 0x80090D28: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_6:
    // 0x80090D2C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80090D30: lw          $v1, -0x54D8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X54D8);
    // 0x80090D34: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x80090D38: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x80090D3C: lui         $ra, 0x600
    ctx->r31 = S32(0X600 << 16);
    // 0x80090D40: or          $a2, $v0, $zero
    ctx->r6 = ctx->r2 | 0;
L_80090D44:
    { extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r3 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r3)); }
    // 0x80090D44: bne         $t3, $v1, L_80090F44
    if (ctx->r11 != ctx->r3) {
        // 0x80090D48: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_80090F44;
    }
    // 0x80090D48: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80090D4C: lw          $v0, -0x19B4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19B4);
    // 0x80090D50: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80090D54: beql        $t3, $v0, L_80090F48
    if (ctx->r11 == ctx->r2) {
        // 0x80090D58: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_80090F48;
    }
    goto skip_5;
    // 0x80090D58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_5:
    // 0x80090D5C: beq         $v0, $at, L_80090F44
    if (ctx->r2 == ctx->r1) {
        // 0x80090D60: lui         $t6, 0xB600
        ctx->r14 = S32(0XB600 << 16);
            goto L_80090F44;
    }
    // 0x80090D60: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x80090D64: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090D68: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090D6C: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80090D70: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x80090D74: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80090D78: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090D7C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090D80: lui         $t9, 0xB700
    ctx->r25 = S32(0XB700 << 16);
    // 0x80090D84: addiu       $t8, $zero, 0x204
    ctx->r24 = ADD32(0, 0X204);
    // 0x80090D88: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090D8C: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80090D90: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x80090D94: lui         $t6, 0xBB00
    ctx->r14 = S32(0XBB00 << 16);
    // 0x80090D98: lui         $t7, 0x8000
    ctx->r15 = S32(0X8000 << 16);
    // 0x80090D9C: ori         $t7, $t7, 0x8000
    ctx->r15 = ctx->r15 | 0X8000;
    // 0x80090DA0: ori         $t6, $t6, 0x1
    ctx->r14 = ctx->r14 | 0X1;
    // 0x80090DA4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090DA8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80090DAC: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80090DB0: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090DB4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090DB8: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090DBC: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x80090DC0: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80090DC4: lui         $t9, 0xBA00
    ctx->r25 = S32(0XBA00 << 16);
    // 0x80090DC8: ori         $t9, $t9, 0x1301
    ctx->r25 = ctx->r25 | 0X1301;
    // 0x80090DCC: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090DD0: lui         $t8, 0x8
    ctx->r24 = S32(0X8 << 16);
    // 0x80090DD4: sw          $t8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r24;
    // 0x80090DD8: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x80090DDC: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090DE0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090DE4: lui         $t6, 0xBA00
    ctx->r14 = S32(0XBA00 << 16);
    // 0x80090DE8: ori         $t6, $t6, 0x1402
    ctx->r14 = ctx->r14 | 0X1402;
    // 0x80090DEC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090DF0: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80090DF4: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80090DF8: lui         $t9, 0xFF87
    ctx->r25 = S32(0XFF87 << 16);
    // 0x80090DFC: lui         $t7, 0xFC11
    ctx->r15 = S32(0XFC11 << 16);
    // 0x80090E00: ori         $t7, $t7, 0xC223
    ctx->r15 = ctx->r15 | 0XC223;
    // 0x80090E04: ori         $t9, $t9, 0xFFFF
    ctx->r25 = ctx->r25 | 0XFFFF;
    // 0x80090E08: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090E0C: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x80090E10: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x80090E14: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80090E18: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090E1C: lui         $t8, 0xFA00
    ctx->r24 = S32(0XFA00 << 16);
    // 0x80090E20: addiu       $t0, $t0, -0x4FA8
    ctx->r8 = ADD32(ctx->r8, -0X4FA8);
    { extern void wr64_sunny_sky_cloud_color(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_color(rdram, ctx); }
    // 0x80090E24: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x80090E28: lw          $t6, 0xC0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0XC0);
    // 0x80090E2C: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090E30: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090E34: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x80090E38: lw          $t6, 0xB8($t0)
    ctx->r14 = MEM_W(ctx->r8, 0XB8);
    // 0x80090E3C: sll         $t9, $t7, 8
    ctx->r25 = S32(ctx->r15 << 8);
    // 0x80090E40: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090E44: sll         $t7, $t6, 24
    ctx->r15 = S32(ctx->r14 << 24);
    // 0x80090E48: lw          $t6, 0xBC($t0)
    ctx->r14 = MEM_W(ctx->r8, 0XBC);
    // 0x80090E4C: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x80090E50: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090E54: andi        $t9, $t6, 0xFF
    ctx->r25 = ctx->r14 & 0XFF;
    // 0x80090E58: sll         $t7, $t9, 16
    ctx->r15 = S32(ctx->r25 << 16);
    // 0x80090E5C: or          $t6, $t8, $t7
    ctx->r14 = ctx->r24 | ctx->r15;
    // 0x80090E60: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
    // 0x80090E64: lui         $t8, 0x50
    ctx->r24 = S32(0X50 << 16);
    // 0x80090E68: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x80090E6C: ori         $t9, $t9, 0x31D
    ctx->r25 = ctx->r25 | 0X31D;
    // 0x80090E70: ori         $t8, $t8, 0x4240
    ctx->r24 = ctx->r24 | 0X4240;
    // 0x80090E74: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80090E78: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80090E7C: lui         $t6, 0x800
    ctx->r14 = S32(0X800 << 16);
    // 0x80090E80: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090E84: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090E88: addiu       $t6, $t6, 0x7400
    ctx->r14 = ADD32(ctx->r14, 0X7400);
    // 0x80090E8C: lui         $t7, 0xFD70
    ctx->r15 = S32(0XFD70 << 16);
    // 0x80090E90: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x80090E94: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x80090E98: lui         $t8, 0x701
    ctx->r24 = S32(0X701 << 16);
    // 0x80090E9C: ori         $t8, $t8, 0x4060
    ctx->r24 = ctx->r24 | 0X4060;
    // 0x80090EA0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090EA4: lui         $t9, 0xF570
    ctx->r25 = S32(0XF570 << 16);
    // 0x80090EA8: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x80090EAC: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090EB0: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80090EB4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090EB8: lui         $t7, 0xE600
    ctx->r15 = S32(0XE600 << 16);
    // 0x80090EBC: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80090EC0: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    // 0x80090EC4: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80090EC8: lui         $t9, 0x77F
    ctx->r25 = S32(0X77F << 16);
    // 0x80090ECC: ori         $t9, $t9, 0xF080
    ctx->r25 = ctx->r25 | 0XF080;
    // 0x80090ED0: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090ED4: lui         $t6, 0xF300
    ctx->r14 = S32(0XF300 << 16);
    // 0x80090ED8: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80090EDC: or          $a1, $a2, $zero
    ctx->r5 = ctx->r6 | 0;
    // 0x80090EE0: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
    // 0x80090EE4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090EE8: or          $a3, $a2, $zero
    ctx->r7 = ctx->r6 | 0;
    // 0x80090EEC: lui         $t8, 0xF570
    ctx->r24 = S32(0XF570 << 16);
    // 0x80090EF0: ori         $t8, $t8, 0x2000
    ctx->r24 = ctx->r24 | 0X2000;
    // 0x80090EF4: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090EF8: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80090EFC: sw          $t2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r10;
    // 0x80090F00: lui         $t7, 0x1
    ctx->r15 = S32(0X1 << 16);
    // 0x80090F04: ori         $t7, $t7, 0x4060
    ctx->r15 = ctx->r15 | 0X4060;
    // 0x80090F08: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x80090F0C: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090F10: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
    // 0x80090F14: sw          $t7, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r15;
    // 0x80090F18: lui         $t9, 0xF
    ctx->r25 = S32(0XF << 16);
    // 0x80090F1C: ori         $t9, $t9, 0xC07C
    ctx->r25 = ctx->r25 | 0XC07C;
    // 0x80090F20: lui         $t6, 0xF200
    ctx->r14 = S32(0XF200 << 16);
    // 0x80090F24: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x80090F28: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80090F2C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80090F30: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80090F34: addiu       $t8, $t8, 0x470
    ctx->r24 = ADD32(ctx->r24, 0X470);
    { extern void wr64_sunny_sky_cloud_draw(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_draw(rdram, ctx); }
    // 0x80090F38: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80090F3C: sw          $ra, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r31;
    // 0x80090F40: addiu       $a2, $a2, 0x8
    ctx->r6 = ADD32(ctx->r6, 0X8);
L_80090F44:
    // 0x80090F44: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80090F48:
    // 0x80090F48: addiu       $sp, $sp, 0x1C0
    ctx->r29 = ADD32(ctx->r29, 0X1C0);
    // 0x80090F4C: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x80090F50: jr          $ra
    // 0x80090F54: nop

    return;
    // 0x80090F54: nop

;}
RECOMP_FUNC void Draw_WaterEffects(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80090F58: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x80090F5C: addiu       $t3, $t3, -0x7E90
    ctx->r11 = ADD32(ctx->r11, -0X7E90);
    // 0x80090F60: lw          $t6, 0x0($t3)
    ctx->r14 = MEM_W(ctx->r11, 0X0);
    // 0x80090F64: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80090F68: addiu       $sp, $sp, -0x78
    ctx->r29 = ADD32(ctx->r29, -0X78);
    // 0x80090F6C: bne         $t6, $at, L_80090FBC
    if (ctx->r14 != ctx->r1) {
        // 0x80090F70: lui         $t1, 0x600
        ctx->r9 = S32(0X600 << 16);
            goto L_80090FBC;
    }
    // 0x80090F70: lui         $t1, 0x600
    ctx->r9 = S32(0X600 << 16);
    // 0x80090F74: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80090F78: lw          $t7, -0x54D8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D8);
    // 0x80090F7C: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x80090F80: lui         $t4, 0xB600
    ctx->r12 = S32(0XB600 << 16);
    { extern uint32_t wr64_sunny_water_material_players(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_water_material_players(rdram, (uint32_t)ctx->r15)); }
    // 0x80090F84: bne         $t2, $t7, L_80090FBC
    if (ctx->r10 != ctx->r15) {
        // 0x80090F88: addiu       $t5, $zero, -0x1
        ctx->r13 = ADD32(0, -0X1);
            goto L_80090FBC;
    }
    // 0x80090F88: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
    // 0x80090F8C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80090F90: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80090F94: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80090F98: lui         $t9, 0x1
    ctx->r25 = S32(0X1 << 16);
    // 0x80090F9C: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x80090FA0: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x80090FA4: ori         $t9, $t9, 0x205
    ctx->r25 = ctx->r25 | 0X205;
    // 0x80090FA8: lui         $t8, 0xB700
    ctx->r24 = S32(0XB700 << 16);
    // 0x80090FAC: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80090FB0: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x80090FB4: b           L_80090FF0
    // 0x80090FB8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_80090FF0;
    // 0x80090FB8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80090FBC:
    // 0x80090FBC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80090FC0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80090FC4: lui         $t4, 0xB600
    ctx->r12 = S32(0XB600 << 16);
    // 0x80090FC8: addiu       $t5, $zero, -0x1
    ctx->r13 = ADD32(0, -0X1);
    // 0x80090FCC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80090FD0: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x80090FD4: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x80090FD8: lui         $t6, 0xB700
    ctx->r14 = S32(0XB700 << 16);
    // 0x80090FDC: addiu       $t7, $zero, 0x5
    ctx->r15 = ADD32(0, 0X5);
    // 0x80090FE0: addiu       $t2, $zero, 0x1
    ctx->r10 = ADD32(0, 0X1);
    // 0x80090FE4: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x80090FE8: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x80090FEC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80090FF0:
    // 0x80090FF0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80090FF4: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80090FF8: addiu       $t8, $t8, -0x7D70
    ctx->r24 = ADD32(ctx->r24, -0X7D70);
    // 0x80090FFC: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80091000: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091004: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80091008: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x8009100C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091010: lui         $t0, 0xE700
    ctx->r8 = S32(0XE700 << 16);
    { extern uint32_t wr64_sunny_water_material_players(uint8_t*, uint32_t); ctx->r25 = S32(wr64_sunny_water_material_players(rdram, (uint32_t)ctx->r25)); }
    // 0x80091014: beq         $t2, $t9, L_80091030
    if (ctx->r10 == ctx->r25) {
        // 0x80091018: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_80091030;
    }
    // 0x80091018: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x8009101C: lw          $t6, 0x0($t3)
    ctx->r14 = MEM_W(ctx->r11, 0X0);
    // 0x80091020: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x80091024: lui         $t7, 0xFD10
    ctx->r15 = S32(0XFD10 << 16);
    // 0x80091028: bne         $t6, $at, L_80091480
    if (ctx->r14 != ctx->r1) {
        // 0x8009102C: lui         $t9, 0x800
        ctx->r25 = S32(0X800 << 16);
            goto L_80091480;
    }
    // 0x8009102C: lui         $t9, 0x800
    ctx->r25 = S32(0X800 << 16);
L_80091030:
    // 0x80091030: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091034: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091038: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x8009103C: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80091040: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091044: lui         $t8, 0x800
    ctx->r24 = S32(0X800 << 16);
    // 0x80091048: addiu       $t8, $t8, 0x400
    ctx->r24 = ADD32(ctx->r24, 0X400);
    // 0x8009104C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091050: lui         $t7, 0xFD18
    ctx->r15 = S32(0XFD18 << 16);
    // 0x80091054: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80091058: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x8009105C: lui         $t6, 0x708
    ctx->r14 = S32(0X708 << 16);
    // 0x80091060: ori         $t6, $t6, 0x200
    ctx->r14 = ctx->r14 | 0X200;
    // 0x80091064: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091068: lui         $t9, 0xF518
    ctx->r25 = S32(0XF518 << 16);
    // 0x8009106C: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80091070: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80091074: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80091078: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009107C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80091080: lui         $t7, 0xE600
    ctx->r15 = S32(0XE600 << 16);
    // 0x80091084: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x80091088: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x8009108C: lui         $t9, 0x73F
    ctx->r25 = S32(0X73F << 16);
    // 0x80091090: ori         $t9, $t9, 0xF080
    ctx->r25 = ctx->r25 | 0XF080;
    // 0x80091094: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091098: lui         $t8, 0xF300
    ctx->r24 = S32(0XF300 << 16);
    // 0x8009109C: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x800910A0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800910A4: sw          $t9, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r25;
    // 0x800910A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800910AC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x800910B0: lui         $t6, 0xF518
    ctx->r14 = S32(0XF518 << 16);
    // 0x800910B4: ori         $t6, $t6, 0x1000
    ctx->r14 = ctx->r14 | 0X1000;
    // 0x800910B8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x800910BC: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x800910C0: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x800910C4: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x800910C8: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800910CC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800910D0: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800910D4: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x800910D8: lui         $t9, 0x7
    ctx->r25 = S32(0X7 << 16);
    // 0x800910DC: ori         $t9, $t9, 0xC07C
    ctx->r25 = ctx->r25 | 0XC07C;
    // 0x800910E0: lui         $t8, 0xF200
    ctx->r24 = S32(0XF200 << 16);
    // 0x800910E4: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x800910E8: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x800910EC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800910F0: lw          $t6, -0x19B4($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19B4);
    // 0x800910F4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800910F8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800910FC: bne         $t2, $t6, L_80091210
    if (ctx->r10 != ctx->r14) {
        // 0x80091100: lui         $t8, 0xFB00
        ctx->r24 = S32(0XFB00 << 16);
            goto L_80091210;
    }
    // 0x80091100: lui         $t8, 0xFB00
    ctx->r24 = S32(0XFB00 << 16);
    // 0x80091104: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091108: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009110C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091110: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x80091114: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
    // 0x80091118: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009111C: lui         $t7, 0xB700
    ctx->r15 = S32(0XB700 << 16);
    // 0x80091120: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x80091124: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091128: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x8009112C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80091130: lui         $t9, 0xBB00
    ctx->r25 = S32(0XBB00 << 16);
    // 0x80091134: lui         $t6, 0x8000
    ctx->r14 = S32(0X8000 << 16);
    // 0x80091138: ori         $t6, $t6, 0x8000
    ctx->r14 = ctx->r14 | 0X8000;
    // 0x8009113C: ori         $t9, $t9, 0x1
    ctx->r25 = ctx->r25 | 0X1;
    // 0x80091140: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80091144: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80091148: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009114C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80091150: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091154: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80091158: lui         $t7, 0xBA00
    ctx->r15 = S32(0XBA00 << 16);
    // 0x8009115C: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
    // 0x80091160: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x80091164: ori         $t7, $t7, 0x1402
    ctx->r15 = ctx->r15 | 0X1402;
    // 0x80091168: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009116C: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x80091170: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091174: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x80091178: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x8009117C: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x80091180: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091184: lui         $t9, 0x50
    ctx->r25 = S32(0X50 << 16);
    // 0x80091188: ori         $t9, $t9, 0x49D8
    ctx->r25 = ctx->r25 | 0X49D8;
    // 0x8009118C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x80091190: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091194: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80091198: lui         $t7, 0xFFFC
    ctx->r15 = S32(0XFFFC << 16);
    // 0x8009119C: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x800911A0: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x800911A4: ori         $t7, $t7, 0xF279
    ctx->r15 = ctx->r15 | 0XF279;
    // 0x800911A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800911AC: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x800911B0: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800911B4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800911B8: lui         $t8, 0xFB00
    ctx->r24 = S32(0XFB00 << 16);
    // 0x800911BC: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x800911C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    { extern uint32_t wr64_sunny_water_environment(uint8_t*, uint32_t); ctx->r1 = S32(wr64_sunny_water_environment(rdram, (uint32_t)ctx->r1)); }
    // 0x800911C4: lwc1        $f4, -0x4EA0($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X4EA0);
    // 0x800911C8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800911CC: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x800911D0: mfc1        $a2, $f6
    ctx->r6 = (int32_t)ctx->f6.u32l;
    // 0x800911D4: nop

    // 0x800911D8: andi        $t6, $a2, 0xFF
    ctx->r14 = ctx->r6 & 0XFF;
    // 0x800911DC: sll         $t7, $t6, 24
    ctx->r15 = S32(ctx->r14 << 24);
    // 0x800911E0: sll         $t8, $t6, 16
    ctx->r24 = S32(ctx->r14 << 16);
    // 0x800911E4: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x800911E8: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800911EC: lh          $t8, -0x6770($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X6770);
    // 0x800911F0: sll         $t6, $t6, 8
    ctx->r14 = S32(ctx->r14 << 8);
    // 0x800911F4: or          $t7, $t9, $t6
    ctx->r15 = ctx->r25 | ctx->r14;
    // 0x800911F8: andi        $t9, $t8, 0xFF
    ctx->r25 = ctx->r24 & 0XFF;
    // 0x800911FC: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x80091200: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x80091204: addiu       $a2, $a2, -0x54D4
    ctx->r6 = ADD32(ctx->r6, -0X54D4);
    // 0x80091208: b           L_800915A0
    // 0x8009120C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
        goto L_800915A0;
    // 0x8009120C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
L_80091210:
    // 0x80091210: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091214: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x80091218: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x8009121C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091220: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80091224: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    { extern uint32_t wr64_sunny_water_environment(uint8_t*, uint32_t); ctx->r1 = S32(wr64_sunny_water_environment(rdram, (uint32_t)ctx->r1)); }
    // 0x80091228: lwc1        $f8, -0x4EA0($at)
    ctx->f8.u32l = MEM_W(ctx->r1, -0X4EA0);
    // 0x8009122C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091230: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80091234: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80091238: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x8009123C: mfc1        $a2, $f10
    ctx->r6 = (int32_t)ctx->f10.u32l;
    // 0x80091240: nop

    // 0x80091244: andi        $t9, $a2, 0xFF
    ctx->r25 = ctx->r6 & 0XFF;
    // 0x80091248: sll         $t6, $t9, 24
    ctx->r14 = S32(ctx->r25 << 24);
    // 0x8009124C: sll         $t8, $t9, 16
    ctx->r24 = S32(ctx->r25 << 16);
    // 0x80091250: or          $t7, $t6, $t8
    ctx->r15 = ctx->r14 | ctx->r24;
    // 0x80091254: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80091258: lh          $t8, -0x6770($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X6770);
    // 0x8009125C: sll         $t9, $t9, 8
    ctx->r25 = S32(ctx->r25 << 8);
    // 0x80091260: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x80091264: andi        $t7, $t8, 0xFF
    ctx->r15 = ctx->r24 & 0XFF;
    // 0x80091268: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x8009126C: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x80091270: lw          $t8, 0x0($t3)
    ctx->r24 = MEM_W(ctx->r11, 0X0);
    // 0x80091274: lui         $t6, 0xBA00
    ctx->r14 = S32(0XBA00 << 16);
    // 0x80091278: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009127C: bne         $t8, $at, L_8009140C
    if (ctx->r24 != ctx->r1) {
        // 0x80091280: ori         $t6, $t6, 0x1402
        ctx->r14 = ctx->r14 | 0X1402;
            goto L_8009140C;
    }
    // 0x80091280: ori         $t6, $t6, 0x1402
    ctx->r14 = ctx->r14 | 0X1402;
    // 0x80091284: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091288: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x8009128C: sw          $t0, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r8;
    // 0x80091290: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x80091294: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091298: lui         $t7, 0x10
    ctx->r15 = S32(0X10 << 16);
    // 0x8009129C: sw          $t7, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r15;
    // 0x800912A0: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x800912A4: or          $t4, $a0, $zero
    ctx->r12 = ctx->r4 | 0;
    // 0x800912A8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800912AC: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x800912B0: lui         $t8, 0xC810
    ctx->r24 = S32(0XC810 << 16);
    // 0x800912B4: ori         $t8, $t8, 0x49D8
    ctx->r24 = ctx->r24 | 0X49D8;
    // 0x800912B8: ori         $t9, $t9, 0x31D
    ctx->r25 = ctx->r25 | 0X31D;
    // 0x800912BC: or          $t5, $a0, $zero
    ctx->r13 = ctx->r4 | 0;
    // 0x800912C0: sw          $t9, 0x0($t4)
    MEM_W(0X0, ctx->r12) = ctx->r25;
    // 0x800912C4: sw          $t8, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r24;
    // 0x800912C8: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x800912CC: lui         $t7, 0xFFFC
    ctx->r15 = S32(0XFFFC << 16);
    // 0x800912D0: ori         $t7, $t7, 0xF238
    ctx->r15 = ctx->r15 | 0XF238;
    // 0x800912D4: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x800912D8: sw          $t6, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r14;
    // 0x800912DC: sw          $t7, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r15;
    // 0x800912E0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800912E4: sw          $a0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r4;
    // 0x800912E8: lw          $t8, 0x4($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X4);
    // 0x800912EC: lui         $t9, 0xF800
    ctx->r25 = S32(0XF800 << 16);
    // 0x800912F0: addiu       $a2, $a2, -0x54D4
    ctx->r6 = ADD32(ctx->r6, -0X54D4);
    // 0x800912F4: sw          $t9, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r25;
    // 0x800912F8: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x800912FC: addiu       $a1, $zero, 0x110
    ctx->r5 = ADD32(0, 0X110);
    // 0x80091300: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80091304: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091308: addiu       $v1, $v1, -0x4FA8
    ctx->r3 = ADD32(ctx->r3, -0X4FA8);
    // 0x8009130C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091310: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80091314: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x80091318: ori         $at, $at, 0xF400
    ctx->r1 = ctx->r1 | 0XF400;
    // 0x8009131C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091320: mflo        $t7
    ctx->r15 = lo;
    // 0x80091324: addu        $v0, $v1, $t7
    ctx->r2 = ADD32(ctx->r3, ctx->r15);
    // 0x80091328: lw          $t9, 0x94($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X94);
    // 0x8009132C: andi        $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 & 0XFF;
    // 0x80091330: lw          $t9, 0x88($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X88);
    // 0x80091334: sll         $t7, $t9, 24
    ctx->r15 = S32(ctx->r25 << 24);
    // 0x80091338: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x8009133C: lw          $t6, 0x8C($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X8C);
    // 0x80091340: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x80091344: sll         $t6, $t7, 16
    ctx->r14 = S32(ctx->r15 << 16);
    // 0x80091348: or          $t7, $t9, $t6
    ctx->r15 = ctx->r25 | ctx->r14;
    // 0x8009134C: lw          $t9, 0x90($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X90);
    // 0x80091350: andi        $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 & 0XFF;
    // 0x80091354: sll         $t9, $t6, 8
    ctx->r25 = S32(ctx->r14 << 8);
    // 0x80091358: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x8009135C: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x80091360: ori         $t7, $t7, 0x8
    ctx->r15 = ctx->r15 | 0X8;
    // 0x80091364: sw          $t6, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r14;
    // 0x80091368: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x8009136C: lw          $t9, 0x0($a2)
    ctx->r25 = MEM_W(ctx->r6, 0X0);
    // 0x80091370: multu       $t9, $a1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091374: mflo        $t6
    ctx->r14 = lo;
    // 0x80091378: addu        $v0, $v1, $t6
    ctx->r2 = ADD32(ctx->r3, ctx->r14);
    // 0x8009137C: lw          $t0, 0x98($v0)
    ctx->r8 = MEM_W(ctx->r2, 0X98);
    // 0x80091380: lw          $t8, 0x9C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X9C);
    // 0x80091384: negu        $t7, $t0
    ctx->r15 = SUB32(0, ctx->r8);
    // 0x80091388: subu        $t3, $t8, $t0
    ctx->r11 = SUB32(ctx->r24, ctx->r8);
    // 0x8009138C: sll         $t9, $t7, 8
    ctx->r25 = S32(ctx->r15 << 8);
    // 0x80091390: addu        $t6, $t9, $at
    ctx->r14 = ADD32(ctx->r25, ctx->r1);
    // 0x80091394: div         $zero, $t6, $t3
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r11)));
    // 0x80091398: lui         $t9, 0x1
    ctx->r25 = S32(0X1 << 16);
    // 0x8009139C: ori         $t9, $t9, 0xF400
    ctx->r25 = ctx->r25 | 0XF400;
    // 0x800913A0: mflo        $t8
    ctx->r24 = lo;
    // 0x800913A4: andi        $t7, $t8, 0xFFFF
    ctx->r15 = ctx->r24 & 0XFFFF;
    // 0x800913A8: bne         $t3, $zero, L_800913B4
    if (ctx->r11 != 0) {
        // 0x800913AC: nop
    
            goto L_800913B4;
    }
    // 0x800913AC: nop

    // 0x800913B0: break       7
    do_break(2148078512);
L_800913B4:
    // 0x800913B4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800913B8: bne         $t3, $at, L_800913CC
    if (ctx->r11 != ctx->r1) {
        // 0x800913BC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800913CC;
    }
    // 0x800913BC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800913C0: bne         $t6, $at, L_800913CC
    if (ctx->r14 != ctx->r1) {
        // 0x800913C4: nop
    
            goto L_800913CC;
    }
    // 0x800913C4: nop

    // 0x800913C8: break       6
    do_break(2148078536);
L_800913CC:
    // 0x800913CC: div         $zero, $t9, $t3
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r11))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r11)));
    // 0x800913D0: mflo        $t6
    ctx->r14 = lo;
    // 0x800913D4: andi        $t8, $t6, 0xFFFF
    ctx->r24 = ctx->r14 & 0XFFFF;
    // 0x800913D8: bne         $t3, $zero, L_800913E4
    if (ctx->r11 != 0) {
        // 0x800913DC: nop
    
            goto L_800913E4;
    }
    // 0x800913DC: nop

    // 0x800913E0: break       7
    do_break(2148078560);
L_800913E4:
    // 0x800913E4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800913E8: bne         $t3, $at, L_800913FC
    if (ctx->r11 != ctx->r1) {
        // 0x800913EC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800913FC;
    }
    // 0x800913EC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800913F0: bne         $t9, $at, L_800913FC
    if (ctx->r25 != ctx->r1) {
        // 0x800913F4: nop
    
            goto L_800913FC;
    }
    // 0x800913F4: nop

    // 0x800913F8: break       6
    do_break(2148078584);
L_800913FC:
    // 0x800913FC: sll         $t9, $t8, 16
    ctx->r25 = S32(ctx->r24 << 16);
    // 0x80091400: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x80091404: b           L_800915A0
    // 0x80091408: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
        goto L_800915A0;
    // 0x80091408: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
L_8009140C:
    // 0x8009140C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091410: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091414: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091418: lui         $t8, 0xBA00
    ctx->r24 = S32(0XBA00 << 16);
    // 0x8009141C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x80091420: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80091424: ori         $t8, $t8, 0x1402
    ctx->r24 = ctx->r24 | 0X1402;
    // 0x80091428: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009142C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80091430: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091434: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80091438: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x8009143C: lui         $t9, 0x50
    ctx->r25 = S32(0X50 << 16);
    // 0x80091440: ori         $t9, $t9, 0x49D8
    ctx->r25 = ctx->r25 | 0X49D8;
    // 0x80091444: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x80091448: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009144C: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x80091450: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x80091454: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80091458: lui         $t8, 0xFFFC
    ctx->r24 = S32(0XFFFC << 16);
    // 0x8009145C: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x80091460: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x80091464: ori         $t8, $t8, 0xF279
    ctx->r24 = ctx->r24 | 0XF279;
    // 0x80091468: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x8009146C: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x80091470: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x80091474: addiu       $a2, $a2, -0x54D4
    ctx->r6 = ADD32(ctx->r6, -0X54D4);
    // 0x80091478: b           L_800915A0
    // 0x8009147C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_800915A0;
    // 0x8009147C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091480:
    // 0x80091480: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091484: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091488: lui         $t0, 0xE700
    ctx->r8 = S32(0XE700 << 16);
    // 0x8009148C: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091490: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x80091494: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80091498: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009149C: addiu       $t9, $t9, 0x400
    ctx->r25 = ADD32(ctx->r25, 0X400);
    // 0x800914A0: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x800914A4: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800914A8: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x800914AC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800914B0: lui         $t6, 0xF510
    ctx->r14 = S32(0XF510 << 16);
    // 0x800914B4: lui         $t8, 0x708
    ctx->r24 = S32(0X708 << 16);
    // 0x800914B8: ori         $t8, $t8, 0x200
    ctx->r24 = ctx->r24 | 0X200;
    // 0x800914BC: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x800914C0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800914C4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800914C8: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x800914CC: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800914D0: lui         $t7, 0xE600
    ctx->r15 = S32(0XE600 << 16);
    // 0x800914D4: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x800914D8: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x800914DC: lui         $t6, 0x73F
    ctx->r14 = S32(0X73F << 16);
    // 0x800914E0: ori         $t6, $t6, 0xF100
    ctx->r14 = ctx->r14 | 0XF100;
    // 0x800914E4: lui         $t9, 0xF300
    ctx->r25 = S32(0XF300 << 16);
    // 0x800914E8: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
    // 0x800914EC: sw          $t6, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r14;
    // 0x800914F0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800914F4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800914F8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800914FC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80091500: lui         $t8, 0xF510
    ctx->r24 = S32(0XF510 << 16);
    // 0x80091504: ori         $t8, $t8, 0x1000
    ctx->r24 = ctx->r24 | 0X1000;
    // 0x80091508: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x8009150C: sw          $t0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r8;
    // 0x80091510: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80091514: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x80091518: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x8009151C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80091520: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091524: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091528: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x8009152C: lui         $t6, 0x7
    ctx->r14 = S32(0X7 << 16);
    // 0x80091530: ori         $t6, $t6, 0xC07C
    ctx->r14 = ctx->r14 | 0XC07C;
    // 0x80091534: lui         $t9, 0xF200
    ctx->r25 = S32(0XF200 << 16);
    // 0x80091538: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8009153C: lui         $t8, 0xBA00
    ctx->r24 = S32(0XBA00 << 16);
    // 0x80091540: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80091544: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80091548: ori         $t8, $t8, 0x1402
    ctx->r24 = ctx->r24 | 0X1402;
    // 0x8009154C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x80091550: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091554: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x80091558: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x8009155C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091560: lui         $t9, 0x55
    ctx->r25 = S32(0X55 << 16);
    // 0x80091564: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x80091568: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x8009156C: ori         $t9, $t9, 0x2078
    ctx->r25 = ctx->r25 | 0X2078;
    // 0x80091570: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091574: sw          $t9, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r25;
    // 0x80091578: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
    // 0x8009157C: lui         $t8, 0xFFFC
    ctx->r24 = S32(0XFFFC << 16);
    // 0x80091580: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x80091584: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x80091588: ori         $t8, $t8, 0xF279
    ctx->r24 = ctx->r24 | 0XF279;
    // 0x8009158C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x80091590: addiu       $a2, $a2, -0x54D4
    ctx->r6 = ADD32(ctx->r6, -0X54D4);
    // 0x80091594: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80091598: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x8009159C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_800915A0:
    // 0x800915A0: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800915A4: lw          $t7, -0x676C($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X676C);
    // 0x800915A8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800915AC: addiu       $sp, $sp, 0x78
    ctx->r29 = ADD32(ctx->r29, 0X78);
    // 0x800915B0: beq         $t7, $zero, L_800916AC
    if (ctx->r15 == 0) {
        // 0x800915B4: nop
    
            goto L_800916AC;
    }
    // 0x800915B4: nop

    // 0x800915B8: lw          $v0, -0x19B4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19B4);
    // 0x800915BC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800915C0: beq         $v0, $zero, L_8009164C
    if (ctx->r2 == 0) {
        // 0x800915C4: nop
    
            goto L_8009164C;
    }
    // 0x800915C4: nop

    // 0x800915C8: beq         $v0, $t2, L_800915E4
    if (ctx->r2 == ctx->r10) {
        // 0x800915CC: lui         $t9, 0x101
        ctx->r25 = S32(0X101 << 16);
            goto L_800915E4;
    }
    // 0x800915CC: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x800915D0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800915D4: beql        $v0, $at, L_80091600
    if (ctx->r2 == ctx->r1) {
        // 0x800915D8: lw          $v0, 0x0($a2)
        ctx->r2 = MEM_W(ctx->r6, 0X0);
            goto L_80091600;
    }
    goto skip_0;
    // 0x800915D8: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
    skip_0:
    // 0x800915DC: b           L_800916AC
    // 0x800915E0: nop

        goto L_800916AC;
    // 0x800915E0: nop

L_800915E4:
    // 0x800915E4: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800915E8: addiu       $t9, $t9, -0x7D10
    ctx->r25 = ADD32(ctx->r25, -0X7D10);
    // 0x800915EC: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x800915F0: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x800915F4: b           L_800916AC
    // 0x800915F8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_800916AC;
    // 0x800915F8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800915FC: lw          $v0, 0x0($a2)
    ctx->r2 = MEM_W(ctx->r6, 0X0);
L_80091600:
    // 0x80091600: lui         $t6, 0x101
    ctx->r14 = S32(0X101 << 16);
    // 0x80091604: addiu       $t6, $t6, -0x2DA8
    ctx->r14 = ADD32(ctx->r14, -0X2DA8);
    // 0x80091608: beql        $v0, $zero, L_80091624
    if (ctx->r2 == 0) {
        // 0x8009160C: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_80091624;
    }
    goto skip_1;
    // 0x8009160C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    skip_1:
    // 0x80091610: beq         $v0, $t2, L_80091634
    if (ctx->r2 == ctx->r10) {
        // 0x80091614: lui         $t8, 0x101
        ctx->r24 = S32(0X101 << 16);
            goto L_80091634;
    }
    // 0x80091614: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80091618: b           L_800916AC
    // 0x8009161C: nop

        goto L_800916AC;
    // 0x8009161C: nop

    // 0x80091620: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_80091624:
    // 0x80091624: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091628: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x8009162C: b           L_800916AC
    // 0x80091630: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_800916AC;
    // 0x80091630: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091634:
    // 0x80091634: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091638: addiu       $t8, $t8, -0x1980
    ctx->r24 = ADD32(ctx->r24, -0X1980);
    // 0x8009163C: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80091640: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091644: b           L_800916AC
    // 0x80091648: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_800916AC;
    // 0x80091648: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_8009164C:
    // 0x8009164C: lw          $t7, -0x54D8($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54D8);
    // 0x80091650: lui         $t9, 0x101
    ctx->r25 = S32(0X101 << 16);
    // 0x80091654: addiu       $t9, $t9, -0x4A70
    ctx->r25 = ADD32(ctx->r25, -0X4A70);
    // 0x80091658: bne         $t2, $t7, L_80091670
    if (ctx->r10 != ctx->r15) {
        // 0x8009165C: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_80091670;
    }
    // 0x8009165C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091660: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091664: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091668: b           L_800916AC
    // 0x8009166C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
        goto L_800916AC;
    // 0x8009166C: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
L_80091670:
    // 0x80091670: lw          $t6, 0x0($a2)
    ctx->r14 = MEM_W(ctx->r6, 0X0);
    // 0x80091674: lui         $t7, 0x101
    ctx->r15 = S32(0X101 << 16);
    // 0x80091678: addiu       $t7, $t7, -0x1980
    ctx->r15 = ADD32(ctx->r15, -0X1980);
    // 0x8009167C: bne         $t6, $zero, L_800916A0
    if (ctx->r14 != 0) {
        // 0x80091680: or          $v0, $a0, $zero
        ctx->r2 = ctx->r4 | 0;
            goto L_800916A0;
    }
    // 0x80091680: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091684: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091688: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x8009168C: addiu       $t8, $t8, -0x2DA8
    ctx->r24 = ADD32(ctx->r24, -0X2DA8);
    // 0x80091690: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x80091694: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091698: b           L_800916AC
    // 0x8009169C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_800916AC;
    // 0x8009169C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_800916A0:
    // 0x800916A0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x800916A4: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x800916A8: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
L_800916AC:
    // 0x800916AC: jr          $ra
    // 0x800916B0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x800916B0: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_800916B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800916B4: lui         $t2, 0x8012
    ctx->r10 = S32(0X8012 << 16);
    // 0x800916B8: addiu       $t2, $t2, -0x720
    ctx->r10 = ADD32(ctx->r10, -0X720);
    // 0x800916BC: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x800916C0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800916C4: addiu       $t0, $t0, -0x54D4
    ctx->r8 = ADD32(ctx->r8, -0X54D4);
    // 0x800916C8: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x800916CC: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800916D0: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800916D4: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800916D8: addiu       $t3, $zero, 0x18
    ctx->r11 = ADD32(0, 0X18);
    // 0x800916DC: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800916E0: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800916E4: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x800916E8: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x800916EC: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800916F0: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x800916F4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800916F8: addiu       $t1, $t1, 0x43F8
    ctx->r9 = ADD32(ctx->r9, 0X43F8);
    // 0x800916FC: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80091700: addu        $t8, $t1, $t7
    ctx->r24 = ADD32(ctx->r9, ctx->r15);
    // 0x80091704: sll         $t6, $v0, 4
    ctx->r14 = S32(ctx->r2 << 4);
    // 0x80091708: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x8009170C: addu        $t6, $t6, $v0
    ctx->r14 = ADD32(ctx->r14, ctx->r2);
    // 0x80091710: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x80091714: addiu       $t7, $t7, -0x4FA8
    ctx->r15 = ADD32(ctx->r15, -0X4FA8);
    // 0x80091718: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x8009171C: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x80091720: lwc1        $f4, 0xAC($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0XAC);
    // 0x80091724: sw          $s0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r16;
    // 0x80091728: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8009172C: mflo        $t9
    ctx->r25 = lo;
    // 0x80091730: addu        $a0, $t8, $t9
    ctx->r4 = ADD32(ctx->r24, ctx->r25);
    // 0x80091734: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80091738: lw          $t8, 0x0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X0);
    // 0x8009173C: lwc1        $f8, 0xB0($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0XB0);
    // 0x80091740: lwc1        $f16, 0xB4($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0XB4);
    // 0x80091744: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x80091748: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x8009174C: mfc1        $t8, $f6
    ctx->r24 = (int32_t)ctx->f6.u32l;
    // 0x80091750: lw          $t6, 0x8($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X8);
    // 0x80091754: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x80091758: sw          $t8, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r24;
    // 0x8009175C: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x80091760: mfc1        $t6, $f10
    ctx->r14 = (int32_t)ctx->f10.u32l;
    // 0x80091764: mfc1        $t8, $f18
    ctx->r24 = (int32_t)ctx->f18.u32l;
    // 0x80091768: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x8009176C: sw          $ra, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r31;
    // 0x80091770: addiu       $a0, $a0, 0x35D0
    ctx->r4 = ADD32(ctx->r4, 0X35D0);
    // 0x80091774: lw          $a1, 0xC($v1)
    ctx->r5 = MEM_W(ctx->r3, 0XC);
    // 0x80091778: lw          $a2, 0x10($v1)
    ctx->r6 = MEM_W(ctx->r3, 0X10);
    // 0x8009177C: lw          $a3, 0x14($v1)
    ctx->r7 = MEM_W(ctx->r3, 0X14);
    // 0x80091780: sw          $t6, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r14;
    // 0x80091784: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x80091788: jal         0x80047F90
    // 0x8009178C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    SysUtils_LightsSetSource(rdram, ctx);
        goto after_0;
    // 0x8009178C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    after_0:
    // 0x80091790: lui         $t2, 0x8012
    ctx->r10 = S32(0X8012 << 16);
    // 0x80091794: addiu       $t2, $t2, -0x720
    ctx->r10 = ADD32(ctx->r10, -0X720);
    // 0x80091798: lw          $t9, 0x0($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X0);
    // 0x8009179C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800917A0: addiu       $t0, $t0, -0x54D4
    ctx->r8 = ADD32(ctx->r8, -0X54D4);
    // 0x800917A4: sll         $t6, $t9, 3
    ctx->r14 = S32(ctx->r25 << 3);
    // 0x800917A8: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800917AC: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x800917B0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800917B4: addiu       $t3, $zero, 0x18
    ctx->r11 = ADD32(0, 0X18);
    // 0x800917B8: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x800917BC: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800917C0: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800917C4: addu        $t6, $t6, $t9
    ctx->r14 = ADD32(ctx->r14, ctx->r25);
    // 0x800917C8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800917CC: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x800917D0: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x800917D4: addiu       $t1, $t1, 0x43F8
    ctx->r9 = ADD32(ctx->r9, 0X43F8);
    // 0x800917D8: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x800917DC: addu        $t7, $t1, $t6
    ctx->r15 = ADD32(ctx->r9, ctx->r14);
    // 0x800917E0: sll         $t9, $v0, 4
    ctx->r25 = S32(ctx->r2 << 4);
    // 0x800917E4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800917E8: addu        $t9, $t9, $v0
    ctx->r25 = ADD32(ctx->r25, ctx->r2);
    // 0x800917EC: sll         $t9, $t9, 4
    ctx->r25 = S32(ctx->r25 << 4);
    // 0x800917F0: addiu       $t6, $t6, -0x4FA8
    ctx->r14 = ADD32(ctx->r14, -0X4FA8);
    // 0x800917F4: addu        $v1, $t9, $t6
    ctx->r3 = ADD32(ctx->r25, ctx->r14);
    // 0x800917F8: lwc1        $f4, 0xFC($v1)
    ctx->f4.u32l = MEM_W(ctx->r3, 0XFC);
    // 0x800917FC: mflo        $t8
    ctx->r24 = lo;
    // 0x80091800: addu        $a0, $t7, $t8
    ctx->r4 = ADD32(ctx->r15, ctx->r24);
    // 0x80091804: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80091808: lw          $t7, 0xCC($v1)
    ctx->r15 = MEM_W(ctx->r3, 0XCC);
    // 0x8009180C: lwc1        $f8, 0x100($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X100);
    // 0x80091810: lwc1        $f16, 0x104($v1)
    ctx->f16.u32l = MEM_W(ctx->r3, 0X104);
    // 0x80091814: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    // 0x80091818: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x8009181C: mfc1        $t7, $f6
    ctx->r15 = (int32_t)ctx->f6.u32l;
    // 0x80091820: lw          $t9, 0xD4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0XD4);
    // 0x80091824: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x80091828: sw          $t7, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r15;
    // 0x8009182C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x80091830: mfc1        $t9, $f10
    ctx->r25 = (int32_t)ctx->f10.u32l;
    // 0x80091834: mfc1        $t7, $f18
    ctx->r15 = (int32_t)ctx->f18.u32l;
    // 0x80091838: lw          $t8, 0xD0($v1)
    ctx->r24 = MEM_W(ctx->r3, 0XD0);
    // 0x8009183C: addiu       $a0, $a0, 0x3600
    ctx->r4 = ADD32(ctx->r4, 0X3600);
    // 0x80091840: lw          $a1, 0xD8($v1)
    ctx->r5 = MEM_W(ctx->r3, 0XD8);
    // 0x80091844: lw          $a2, 0xDC($v1)
    ctx->r6 = MEM_W(ctx->r3, 0XDC);
    // 0x80091848: lw          $a3, 0xE0($v1)
    ctx->r7 = MEM_W(ctx->r3, 0XE0);
    // 0x8009184C: sw          $t9, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r25;
    // 0x80091850: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    // 0x80091854: jal         0x80047F90
    // 0x80091858: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    SysUtils_LightsSetSource(rdram, ctx);
        goto after_1;
    // 0x80091858: sw          $t7, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r15;
    after_1:
    // 0x8009185C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80091860: lw          $t8, -0x7E90($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X7E90);
    // 0x80091864: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80091868: lui         $t1, 0x801C
    ctx->r9 = S32(0X801C << 16);
    // 0x8009186C: lui         $t2, 0x8012
    ctx->r10 = S32(0X8012 << 16);
    // 0x80091870: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x80091874: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x80091878: addiu       $t4, $t4, -0x4FA8
    ctx->r12 = ADD32(ctx->r12, -0X4FA8);
    // 0x8009187C: addiu       $t2, $t2, -0x720
    ctx->r10 = ADD32(ctx->r10, -0X720);
    // 0x80091880: addiu       $t1, $t1, 0x43F8
    ctx->r9 = ADD32(ctx->r9, 0X43F8);
    // 0x80091884: addiu       $t0, $t0, -0x54D4
    ctx->r8 = ADD32(ctx->r8, -0X54D4);
    // 0x80091888: addiu       $t3, $zero, 0x18
    ctx->r11 = ADD32(0, 0X18);
    // 0x8009188C: bne         $t8, $at, L_80091ACC
    if (ctx->r24 != ctx->r1) {
        // 0x80091890: addiu       $t5, $zero, 0x110
        ctx->r13 = ADD32(0, 0X110);
            goto L_80091ACC;
    }
    // 0x80091890: addiu       $t5, $zero, 0x110
    ctx->r13 = ADD32(0, 0X110);
    // 0x80091894: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x80091898: lui         $t7, 0x801C
    ctx->r15 = S32(0X801C << 16);
    // 0x8009189C: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x800918A0: sll         $t6, $t9, 3
    ctx->r14 = S32(ctx->r25 << 3);
    // 0x800918A4: subu        $t6, $t6, $t9
    ctx->r14 = SUB32(ctx->r14, ctx->r25);
    // 0x800918A8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800918AC: addu        $t6, $t6, $t9
    ctx->r14 = ADD32(ctx->r14, ctx->r25);
    // 0x800918B0: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800918B4: addiu       $t7, $t7, 0x3C60
    ctx->r15 = ADD32(ctx->r15, 0X3C60);
    // 0x800918B8: addiu       $v0, $v0, 0x3C58
    ctx->r2 = ADD32(ctx->r2, 0X3C58);
    // 0x800918BC: addu        $t8, $t6, $t7
    ctx->r24 = ADD32(ctx->r14, ctx->r15);
    // 0x800918C0: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x800918C4: lw          $t6, 0x78($t8)
    ctx->r14 = MEM_W(ctx->r24, 0X78);
    // 0x800918C8: lui         $t8, 0xBC00
    ctx->r24 = S32(0XBC00 << 16);
    // 0x800918CC: ori         $t8, $t8, 0x2
    ctx->r24 = ctx->r24 | 0X2;
    // 0x800918D0: beq         $t6, $zero, L_80091A04
    if (ctx->r14 == 0) {
        // 0x800918D4: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_80091A04;
    }
    // 0x800918D4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x800918D8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x800918DC: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x800918E0: lui         $t8, 0x8000
    ctx->r24 = S32(0X8000 << 16);
    // 0x800918E4: ori         $t8, $t8, 0x60
    ctx->r24 = ctx->r24 | 0X60;
    // 0x800918E8: ori         $t7, $t7, 0x2
    ctx->r15 = ctx->r15 | 0X2;
    // 0x800918EC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x800918F0: lui         $t9, 0x386
    ctx->r25 = S32(0X386 << 16);
    // 0x800918F4: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x800918F8: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
    // 0x800918FC: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x80091900: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x80091904: sw          $t9, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r25;
    // 0x80091908: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x8009190C: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x80091910: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091914: multu       $t9, $t3
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091918: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x8009191C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091920: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091924: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091928: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009192C: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x80091930: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091934: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091938: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x8009193C: mflo        $t6
    ctx->r14 = lo;
    // 0x80091940: addu        $t8, $t1, $t7
    ctx->r24 = ADD32(ctx->r9, ctx->r15);
    // 0x80091944: addu        $t7, $t8, $t6
    ctx->r15 = ADD32(ctx->r24, ctx->r14);
    // 0x80091948: addiu       $t9, $t7, 0x35D8
    ctx->r25 = ADD32(ctx->r15, 0X35D8);
    // 0x8009194C: lui         $t8, 0x388
    ctx->r24 = S32(0X388 << 16);
    // 0x80091950: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x80091954: ori         $t8, $t8, 0x10
    ctx->r24 = ctx->r24 | 0X10;
    // 0x80091958: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009195C: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x80091960: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x80091964: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x80091968: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x8009196C: multu       $t8, $t3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091970: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x80091974: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091978: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009197C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091980: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x80091984: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x80091988: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009198C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091990: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80091994: mflo        $t6
    ctx->r14 = lo;
    // 0x80091998: addu        $t9, $t1, $t7
    ctx->r25 = ADD32(ctx->r9, ctx->r15);
    // 0x8009199C: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x800919A0: addiu       $t8, $t7, 0x3608
    ctx->r24 = ADD32(ctx->r15, 0X3608);
    // 0x800919A4: lui         $t9, 0x38A
    ctx->r25 = S32(0X38A << 16);
    // 0x800919A8: sw          $t8, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r24;
    // 0x800919AC: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x800919B0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800919B4: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x800919B8: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x800919BC: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x800919C0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x800919C4: multu       $t9, $t3
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800919C8: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x800919CC: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800919D0: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800919D4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800919D8: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x800919DC: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x800919E0: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800919E4: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x800919E8: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x800919EC: addu        $t8, $t1, $t7
    ctx->r24 = ADD32(ctx->r9, ctx->r15);
    // 0x800919F0: mflo        $t6
    ctx->r14 = lo;
    // 0x800919F4: addu        $t7, $t8, $t6
    ctx->r15 = ADD32(ctx->r24, ctx->r14);
    // 0x800919F8: addiu       $t9, $t7, 0x3600
    ctx->r25 = ADD32(ctx->r15, 0X3600);
    // 0x800919FC: b           L_80091B9C
    // 0x80091A00: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
        goto L_80091B9C;
    // 0x80091A00: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
L_80091A04:
    // 0x80091A04: lui         $t6, 0x8000
    ctx->r14 = S32(0X8000 << 16);
    // 0x80091A08: ori         $t6, $t6, 0x40
    ctx->r14 = ctx->r14 | 0X40;
    // 0x80091A0C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091A10: lui         $t7, 0x386
    ctx->r15 = S32(0X386 << 16);
    // 0x80091A14: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x80091A18: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x80091A1C: ori         $t7, $t7, 0x10
    ctx->r15 = ctx->r15 | 0X10;
    // 0x80091A20: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x80091A24: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80091A28: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x80091A2C: lw          $t9, 0x0($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X0);
    // 0x80091A30: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091A34: multu       $t7, $t3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091A38: sll         $t8, $t9, 3
    ctx->r24 = S32(ctx->r25 << 3);
    // 0x80091A3C: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091A40: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80091A44: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091A48: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x80091A4C: addu        $t8, $t8, $t9
    ctx->r24 = ADD32(ctx->r24, ctx->r25);
    // 0x80091A50: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80091A54: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091A58: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x80091A5C: mflo        $t9
    ctx->r25 = lo;
    // 0x80091A60: addu        $t6, $t1, $t8
    ctx->r14 = ADD32(ctx->r9, ctx->r24);
    // 0x80091A64: addu        $t8, $t6, $t9
    ctx->r24 = ADD32(ctx->r14, ctx->r25);
    // 0x80091A68: addiu       $t7, $t8, 0x35D8
    ctx->r15 = ADD32(ctx->r24, 0X35D8);
    // 0x80091A6C: lui         $t6, 0x388
    ctx->r14 = S32(0X388 << 16);
    // 0x80091A70: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x80091A74: ori         $t6, $t6, 0x10
    ctx->r14 = ctx->r14 | 0X10;
    // 0x80091A78: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80091A7C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80091A80: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x80091A84: lw          $t9, 0x0($t2)
    ctx->r25 = MEM_W(ctx->r10, 0X0);
    // 0x80091A88: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091A8C: multu       $t6, $t3
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091A90: sll         $t8, $t9, 3
    ctx->r24 = S32(ctx->r25 << 3);
    // 0x80091A94: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091A98: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80091A9C: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091AA0: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x80091AA4: addu        $t8, $t8, $t9
    ctx->r24 = ADD32(ctx->r24, ctx->r25);
    // 0x80091AA8: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x80091AAC: subu        $t8, $t8, $t9
    ctx->r24 = SUB32(ctx->r24, ctx->r25);
    // 0x80091AB0: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x80091AB4: addu        $t7, $t1, $t8
    ctx->r15 = ADD32(ctx->r9, ctx->r24);
    // 0x80091AB8: mflo        $t9
    ctx->r25 = lo;
    // 0x80091ABC: addu        $t8, $t7, $t9
    ctx->r24 = ADD32(ctx->r15, ctx->r25);
    // 0x80091AC0: addiu       $t6, $t8, 0x3600
    ctx->r14 = ADD32(ctx->r24, 0X3600);
    // 0x80091AC4: b           L_80091B9C
    // 0x80091AC8: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
        goto L_80091B9C;
    // 0x80091AC8: sw          $t6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r14;
L_80091ACC:
    // 0x80091ACC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x80091AD0: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x80091AD4: lui         $t9, 0x8000
    ctx->r25 = S32(0X8000 << 16);
    // 0x80091AD8: ori         $t9, $t9, 0x40
    ctx->r25 = ctx->r25 | 0X40;
    // 0x80091ADC: ori         $t7, $t7, 0x2
    ctx->r15 = ctx->r15 | 0X2;
    // 0x80091AE0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091AE4: lui         $t8, 0x386
    ctx->r24 = S32(0X386 << 16);
    // 0x80091AE8: sw          $t7, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r15;
    // 0x80091AEC: sw          $t9, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r25;
    // 0x80091AF0: ori         $t8, $t8, 0x10
    ctx->r24 = ctx->r24 | 0X10;
    // 0x80091AF4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x80091AF8: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80091AFC: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x80091B00: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x80091B04: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091B08: multu       $t8, $t3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091B0C: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x80091B10: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B14: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091B18: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B1C: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x80091B20: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x80091B24: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091B28: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B2C: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80091B30: mflo        $t6
    ctx->r14 = lo;
    // 0x80091B34: addu        $t9, $t1, $t7
    ctx->r25 = ADD32(ctx->r9, ctx->r15);
    // 0x80091B38: addu        $t7, $t9, $t6
    ctx->r15 = ADD32(ctx->r25, ctx->r14);
    // 0x80091B3C: addiu       $t8, $t7, 0x3608
    ctx->r24 = ADD32(ctx->r15, 0X3608);
    // 0x80091B40: lui         $t9, 0x388
    ctx->r25 = S32(0X388 << 16);
    // 0x80091B44: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80091B48: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x80091B4C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80091B50: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x80091B54: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x80091B58: lw          $t6, 0x0($t2)
    ctx->r14 = MEM_W(ctx->r10, 0X0);
    // 0x80091B5C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091B60: multu       $t9, $t3
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091B64: sll         $t7, $t6, 3
    ctx->r15 = S32(ctx->r14 << 3);
    // 0x80091B68: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B6C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091B70: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B74: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x80091B78: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x80091B7C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80091B80: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80091B84: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80091B88: addu        $t8, $t1, $t7
    ctx->r24 = ADD32(ctx->r9, ctx->r15);
    // 0x80091B8C: mflo        $t6
    ctx->r14 = lo;
    // 0x80091B90: addu        $t7, $t8, $t6
    ctx->r15 = ADD32(ctx->r24, ctx->r14);
    // 0x80091B94: addiu       $t9, $t7, 0x3600
    ctx->r25 = ADD32(ctx->r15, 0X3600);
    // 0x80091B98: sw          $t9, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r25;
L_80091B9C:
    // 0x80091B9C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80091BA0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091BA4: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x80091BA8: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x80091BAC: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x80091BB0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80091BB4: lui         $t6, 0xF800
    ctx->r14 = S32(0XF800 << 16);
    // 0x80091BB8: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x80091BBC: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x80091BC0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091BC4: or          $a2, $s0, $zero
    ctx->r6 = ctx->r16 | 0;
    // 0x80091BC8: multu       $t7, $t5
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091BCC: lui         $at, 0x1
    ctx->r1 = S32(0X1 << 16);
    // 0x80091BD0: ori         $at, $at, 0xF400
    ctx->r1 = ctx->r1 | 0XF400;
    // 0x80091BD4: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80091BD8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x80091BDC: mflo        $t9
    ctx->r25 = lo;
    // 0x80091BE0: addu        $v1, $t4, $t9
    ctx->r3 = ADD32(ctx->r12, ctx->r25);
    // 0x80091BE4: lw          $t8, 0x54($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X54);
    // 0x80091BE8: lw          $t9, 0x48($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X48);
    // 0x80091BEC: andi        $t6, $t8, 0xFF
    ctx->r14 = ctx->r24 & 0XFF;
    // 0x80091BF0: sll         $t8, $t9, 24
    ctx->r24 = S32(ctx->r25 << 24);
    // 0x80091BF4: lw          $t9, 0x4C($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4C);
    // 0x80091BF8: or          $t7, $t6, $t8
    ctx->r15 = ctx->r14 | ctx->r24;
    // 0x80091BFC: andi        $t6, $t9, 0xFF
    ctx->r14 = ctx->r25 & 0XFF;
    // 0x80091C00: sll         $t8, $t6, 16
    ctx->r24 = S32(ctx->r14 << 16);
    // 0x80091C04: lw          $t6, 0x50($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X50);
    // 0x80091C08: or          $t9, $t7, $t8
    ctx->r25 = ctx->r15 | ctx->r24;
    // 0x80091C0C: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x80091C10: sll         $t8, $t7, 8
    ctx->r24 = S32(ctx->r15 << 8);
    // 0x80091C14: or          $t6, $t9, $t8
    ctx->r14 = ctx->r25 | ctx->r24;
    // 0x80091C18: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x80091C1C: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80091C20: ori         $t7, $t7, 0x8
    ctx->r15 = ctx->r15 | 0X8;
    // 0x80091C24: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x80091C28: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x80091C2C: multu       $t9, $t5
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091C30: mflo        $t8
    ctx->r24 = lo;
    // 0x80091C34: addu        $v1, $t4, $t8
    ctx->r3 = ADD32(ctx->r12, ctx->r24);
    // 0x80091C38: lw          $a3, 0x78($v1)
    ctx->r7 = MEM_W(ctx->r3, 0X78);
    // 0x80091C3C: lw          $t6, 0x7C($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X7C);
    // 0x80091C40: negu        $t7, $a3
    ctx->r15 = SUB32(0, ctx->r7);
    // 0x80091C44: subu        $t1, $t6, $a3
    ctx->r9 = SUB32(ctx->r14, ctx->r7);
    // 0x80091C48: sll         $t9, $t7, 8
    ctx->r25 = S32(ctx->r15 << 8);
    // 0x80091C4C: addu        $t8, $t9, $at
    ctx->r24 = ADD32(ctx->r25, ctx->r1);
    // 0x80091C50: div         $zero, $t8, $t1
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r9)));
    // 0x80091C54: lui         $t9, 0x1
    ctx->r25 = S32(0X1 << 16);
    // 0x80091C58: ori         $t9, $t9, 0xF400
    ctx->r25 = ctx->r25 | 0XF400;
    // 0x80091C5C: mflo        $t6
    ctx->r14 = lo;
    // 0x80091C60: andi        $t7, $t6, 0xFFFF
    ctx->r15 = ctx->r14 & 0XFFFF;
    // 0x80091C64: bne         $t1, $zero, L_80091C70
    if (ctx->r9 != 0) {
        // 0x80091C68: nop
    
            goto L_80091C70;
    }
    // 0x80091C68: nop

    // 0x80091C6C: break       7
    do_break(2148080748);
L_80091C70:
    // 0x80091C70: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80091C74: bne         $t1, $at, L_80091C88
    if (ctx->r9 != ctx->r1) {
        // 0x80091C78: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80091C88;
    }
    // 0x80091C78: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80091C7C: bne         $t8, $at, L_80091C88
    if (ctx->r24 != ctx->r1) {
        // 0x80091C80: nop
    
            goto L_80091C88;
    }
    // 0x80091C80: nop

    // 0x80091C84: break       6
    do_break(2148080772);
L_80091C88:
    // 0x80091C88: div         $zero, $t9, $t1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r9)));
    // 0x80091C8C: mflo        $t8
    ctx->r24 = lo;
    // 0x80091C90: andi        $t6, $t8, 0xFFFF
    ctx->r14 = ctx->r24 & 0XFFFF;
    // 0x80091C94: bne         $t1, $zero, L_80091CA0
    if (ctx->r9 != 0) {
        // 0x80091C98: nop
    
            goto L_80091CA0;
    }
    // 0x80091C98: nop

    // 0x80091C9C: break       7
    do_break(2148080796);
L_80091CA0:
    // 0x80091CA0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80091CA4: bne         $t1, $at, L_80091CB8
    if (ctx->r9 != ctx->r1) {
        // 0x80091CA8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80091CB8;
    }
    // 0x80091CA8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80091CAC: bne         $t9, $at, L_80091CB8
    if (ctx->r25 != ctx->r1) {
        // 0x80091CB0: nop
    
            goto L_80091CB8;
    }
    // 0x80091CB0: nop

    // 0x80091CB4: break       6
    do_break(2148080820);
L_80091CB8:
    // 0x80091CB8: sll         $t9, $t6, 16
    ctx->r25 = S32(ctx->r14 << 16);
    // 0x80091CBC: or          $t8, $t7, $t9
    ctx->r24 = ctx->r15 | ctx->r25;
    // 0x80091CC0: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x80091CC4: lw          $ra, 0x34($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X34);
    // 0x80091CC8: lw          $s0, 0x30($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X30);
    // 0x80091CCC: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x80091CD0: jr          $ra
    // 0x80091CD4: nop

    return;
    // 0x80091CD4: nop

;}
RECOMP_FUNC void func_80091CD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80091CD8: lui         $t6, 0xBC00
    ctx->r14 = S32(0XBC00 << 16);
    // 0x80091CDC: lui         $t7, 0x8000
    ctx->r15 = S32(0X8000 << 16);
    // 0x80091CE0: ori         $t7, $t7, 0x40
    ctx->r15 = ctx->r15 | 0X40;
    // 0x80091CE4: ori         $t6, $t6, 0x2
    ctx->r14 = ctx->r14 | 0X2;
    // 0x80091CE8: lui         $t8, 0x386
    ctx->r24 = S32(0X386 << 16);
    // 0x80091CEC: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x80091CF0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80091CF4: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80091CF8: addiu       $a1, $a0, 0x8
    ctx->r5 = ADD32(ctx->r4, 0X8);
    // 0x80091CFC: ori         $t8, $t8, 0x10
    ctx->r24 = ctx->r24 | 0X10;
    // 0x80091D00: addiu       $t1, $t1, -0x54D4
    ctx->r9 = ADD32(ctx->r9, -0X54D4);
    // 0x80091D04: lui         $t0, 0x8012
    ctx->r8 = S32(0X8012 << 16);
    // 0x80091D08: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x80091D0C: lw          $t5, 0x0($t1)
    ctx->r13 = MEM_W(ctx->r9, 0X0);
    // 0x80091D10: addiu       $t0, $t0, -0x720
    ctx->r8 = ADD32(ctx->r8, -0X720);
    // 0x80091D14: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x80091D18: addiu       $t2, $zero, 0x18
    ctx->r10 = ADD32(0, 0X18);
    // 0x80091D1C: multu       $t5, $t2
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091D20: sll         $t3, $t9, 3
    ctx->r11 = S32(ctx->r25 << 3);
    // 0x80091D24: subu        $t3, $t3, $t9
    ctx->r11 = SUB32(ctx->r11, ctx->r25);
    // 0x80091D28: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x80091D2C: subu        $t3, $t3, $t9
    ctx->r11 = SUB32(ctx->r11, ctx->r25);
    // 0x80091D30: sll         $t3, $t3, 3
    ctx->r11 = S32(ctx->r11 << 3);
    // 0x80091D34: addu        $t3, $t3, $t9
    ctx->r11 = ADD32(ctx->r11, ctx->r25);
    // 0x80091D38: sll         $t3, $t3, 2
    ctx->r11 = S32(ctx->r11 << 2);
    // 0x80091D3C: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x80091D40: subu        $t3, $t3, $t9
    ctx->r11 = SUB32(ctx->r11, ctx->r25);
    // 0x80091D44: addiu       $a3, $a3, 0x43F8
    ctx->r7 = ADD32(ctx->r7, 0X43F8);
    // 0x80091D48: sll         $t3, $t3, 4
    ctx->r11 = S32(ctx->r11 << 4);
    // 0x80091D4C: mflo        $t6
    ctx->r14 = lo;
    // 0x80091D50: addu        $t4, $a3, $t3
    ctx->r12 = ADD32(ctx->r7, ctx->r11);
    // 0x80091D54: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x80091D58: addiu       $t8, $t7, 0x35D8
    ctx->r24 = ADD32(ctx->r15, 0X35D8);
    // 0x80091D5C: lui         $t9, 0x388
    ctx->r25 = S32(0X388 << 16);
    // 0x80091D60: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80091D64: addiu       $a2, $a1, 0x8
    ctx->r6 = ADD32(ctx->r5, 0X8);
    // 0x80091D68: ori         $t9, $t9, 0x10
    ctx->r25 = ctx->r25 | 0X10;
    // 0x80091D6C: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
    // 0x80091D70: lw          $t6, 0x0($t1)
    ctx->r14 = MEM_W(ctx->r9, 0X0);
    // 0x80091D74: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x80091D78: addiu       $v0, $a2, 0x8
    ctx->r2 = ADD32(ctx->r6, 0X8);
    // 0x80091D7C: multu       $t6, $t2
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r10)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80091D80: sll         $t5, $t3, 3
    ctx->r13 = S32(ctx->r11 << 3);
    // 0x80091D84: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x80091D88: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x80091D8C: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x80091D90: sll         $t5, $t5, 3
    ctx->r13 = S32(ctx->r13 << 3);
    // 0x80091D94: addu        $t5, $t5, $t3
    ctx->r13 = ADD32(ctx->r13, ctx->r11);
    // 0x80091D98: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x80091D9C: subu        $t5, $t5, $t3
    ctx->r13 = SUB32(ctx->r13, ctx->r11);
    // 0x80091DA0: sll         $t5, $t5, 4
    ctx->r13 = S32(ctx->r13 << 4);
    // 0x80091DA4: addu        $t4, $a3, $t5
    ctx->r12 = ADD32(ctx->r7, ctx->r13);
    // 0x80091DA8: mflo        $t7
    ctx->r15 = lo;
    // 0x80091DAC: addu        $t8, $t4, $t7
    ctx->r24 = ADD32(ctx->r12, ctx->r15);
    // 0x80091DB0: addiu       $t9, $t8, 0x35D0
    ctx->r25 = ADD32(ctx->r24, 0X35D0);
    // 0x80091DB4: jr          $ra
    // 0x80091DB8: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    return;
    // 0x80091DB8: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
;}
RECOMP_FUNC void func_80091DBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80091DBC: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80091DC0: lw          $v0, -0x56EC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X56EC);
    // 0x80091DC4: addiu       $v1, $zero, 0x1C
    ctx->r3 = ADD32(0, 0X1C);
    // 0x80091DC8: addiu       $at, $zero, 0x1F
    ctx->r1 = ADD32(0, 0X1F);
    // 0x80091DCC: bgez        $v0, L_80091DE0
    if (SIGNED(ctx->r2) >= 0) {
        // 0x80091DD0: andi        $t6, $v0, 0x1F
        ctx->r14 = ctx->r2 & 0X1F;
            goto L_80091DE0;
    }
    // 0x80091DD0: andi        $t6, $v0, 0x1F
    ctx->r14 = ctx->r2 & 0X1F;
    // 0x80091DD4: beq         $t6, $zero, L_80091DE0
    if (ctx->r14 == 0) {
        // 0x80091DD8: nop
    
            goto L_80091DE0;
    }
    // 0x80091DD8: nop

    // 0x80091DDC: addiu       $t6, $t6, -0x20
    ctx->r14 = ADD32(ctx->r14, -0X20);
L_80091DE0:
    // 0x80091DE0: addiu       $v0, $t6, 0x1
    ctx->r2 = ADD32(ctx->r14, 0X1);
    // 0x80091DE4: beq         $v0, $v1, L_80091DF4
    if (ctx->r2 == ctx->r3) {
        // 0x80091DE8: or          $a1, $a0, $zero
        ctx->r5 = ctx->r4 | 0;
            goto L_80091DF4;
    }
    // 0x80091DE8: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091DEC: bne         $v0, $at, L_80091E14
    if (ctx->r2 != ctx->r1) {
        // 0x80091DF0: lui         $t9, 0xBC00
        ctx->r25 = S32(0XBC00 << 16);
            goto L_80091E14;
    }
    // 0x80091DF0: lui         $t9, 0xBC00
    ctx->r25 = S32(0XBC00 << 16);
L_80091DF4:
    // 0x80091DF4: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
    // 0x80091DF8: lui         $t8, 0x8036
    ctx->r24 = S32(0X8036 << 16);
    // 0x80091DFC: addiu       $t8, $t8, -0x2E00
    ctx->r24 = ADD32(ctx->r24, -0X2E00);
    // 0x80091E00: ori         $t7, $t7, 0x2406
    ctx->r15 = ctx->r15 | 0X2406;
    // 0x80091E04: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x80091E08: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80091E0C: b           L_80091E30
    // 0x80091E10: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_80091E30;
    // 0x80091E10: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091E14:
    // 0x80091E14: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091E18: lui         $t0, 0x8036
    ctx->r8 = S32(0X8036 << 16);
    // 0x80091E1C: addiu       $t0, $t0, -0x3800
    ctx->r8 = ADD32(ctx->r8, -0X3800);
    // 0x80091E20: ori         $t9, $t9, 0x2406
    ctx->r25 = ctx->r25 | 0X2406;
    // 0x80091E24: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80091E28: sw          $t0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r8;
    // 0x80091E2C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091E30:
    // 0x80091E30: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x80091E34: beq         $v0, $at, L_80091E48
    if (ctx->r2 == ctx->r1) {
        // 0x80091E38: or          $a1, $a0, $zero
        ctx->r5 = ctx->r4 | 0;
            goto L_80091E48;
    }
    // 0x80091E38: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091E3C: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x80091E40: bne         $v0, $at, L_80091E68
    if (ctx->r2 != ctx->r1) {
        // 0x80091E44: lui         $t3, 0xBC00
        ctx->r11 = S32(0XBC00 << 16);
            goto L_80091E68;
    }
    // 0x80091E44: lui         $t3, 0xBC00
    ctx->r11 = S32(0XBC00 << 16);
L_80091E48:
    // 0x80091E48: lui         $t1, 0xBC00
    ctx->r9 = S32(0XBC00 << 16);
    // 0x80091E4C: lui         $t2, 0x8036
    ctx->r10 = S32(0X8036 << 16);
    // 0x80091E50: addiu       $t2, $t2, -0x1A00
    ctx->r10 = ADD32(ctx->r10, -0X1A00);
    // 0x80091E54: ori         $t1, $t1, 0x2C06
    ctx->r9 = ctx->r9 | 0X2C06;
    // 0x80091E58: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x80091E5C: sw          $t2, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r10;
    // 0x80091E60: b           L_80091E84
    // 0x80091E64: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_80091E84;
    // 0x80091E64: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091E68:
    // 0x80091E68: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091E6C: lui         $t4, 0x8036
    ctx->r12 = S32(0X8036 << 16);
    // 0x80091E70: addiu       $t4, $t4, -0x2400
    ctx->r12 = ADD32(ctx->r12, -0X2400);
    // 0x80091E74: ori         $t3, $t3, 0x2C06
    ctx->r11 = ctx->r11 | 0X2C06;
    // 0x80091E78: sw          $t3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r11;
    // 0x80091E7C: sw          $t4, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r12;
    // 0x80091E80: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091E84:
    // 0x80091E84: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x80091E88: beq         $v0, $at, L_80091E9C
    if (ctx->r2 == ctx->r1) {
        // 0x80091E8C: or          $a1, $a0, $zero
        ctx->r5 = ctx->r4 | 0;
            goto L_80091E9C;
    }
    // 0x80091E8C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091E90: addiu       $at, $zero, 0xE
    ctx->r1 = ADD32(0, 0XE);
    // 0x80091E94: bne         $v0, $at, L_80091EBC
    if (ctx->r2 != ctx->r1) {
        // 0x80091E98: lui         $t7, 0xBC00
        ctx->r15 = S32(0XBC00 << 16);
            goto L_80091EBC;
    }
    // 0x80091E98: lui         $t7, 0xBC00
    ctx->r15 = S32(0XBC00 << 16);
L_80091E9C:
    // 0x80091E9C: lui         $t5, 0xBC00
    ctx->r13 = S32(0XBC00 << 16);
    // 0x80091EA0: lui         $t6, 0x8036
    ctx->r14 = S32(0X8036 << 16);
    // 0x80091EA4: addiu       $t6, $t6, -0x600
    ctx->r14 = ADD32(ctx->r14, -0X600);
    // 0x80091EA8: ori         $t5, $t5, 0x3006
    ctx->r13 = ctx->r13 | 0X3006;
    // 0x80091EAC: sw          $t5, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r13;
    // 0x80091EB0: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80091EB4: b           L_80091ED8
    // 0x80091EB8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
        goto L_80091ED8;
    // 0x80091EB8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091EBC:
    // 0x80091EBC: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80091EC0: lui         $t8, 0x8036
    ctx->r24 = S32(0X8036 << 16);
    // 0x80091EC4: addiu       $t8, $t8, -0x1000
    ctx->r24 = ADD32(ctx->r24, -0X1000);
    // 0x80091EC8: ori         $t7, $t7, 0x3006
    ctx->r15 = ctx->r15 | 0X3006;
    // 0x80091ECC: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
    // 0x80091ED0: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80091ED4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
L_80091ED8:
    // 0x80091ED8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80091EDC: sw          $v0, -0x56EC($at)
    MEM_W(-0X56EC, ctx->r1) = ctx->r2;
    // 0x80091EE0: addiu       $at, $zero, 0x19
    ctx->r1 = ADD32(0, 0X19);
    // 0x80091EE4: beq         $v0, $at, L_80091EF8
    if (ctx->r2 == ctx->r1) {
        // 0x80091EE8: lui         $t9, 0xBC00
        ctx->r25 = S32(0XBC00 << 16);
            goto L_80091EF8;
    }
    // 0x80091EE8: lui         $t9, 0xBC00
    ctx->r25 = S32(0XBC00 << 16);
    // 0x80091EEC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80091EF0: bne         $v0, $v1, L_80091F1C
    if (ctx->r2 != ctx->r3) {
        // 0x80091EF4: sw          $v0, -0x56EC($at)
        MEM_W(-0X56EC, ctx->r1) = ctx->r2;
            goto L_80091F1C;
    }
    // 0x80091EF4: sw          $v0, -0x56EC($at)
    MEM_W(-0X56EC, ctx->r1) = ctx->r2;
L_80091EF8:
    // 0x80091EF8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091EFC: lui         $t0, 0x8036
    ctx->r8 = S32(0X8036 << 16);
    // 0x80091F00: addiu       $t0, $t0, 0xE00
    ctx->r8 = ADD32(ctx->r8, 0XE00);
    // 0x80091F04: ori         $t9, $t9, 0x2806
    ctx->r25 = ctx->r25 | 0X2806;
    // 0x80091F08: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x80091F0C: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x80091F10: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091F14: jr          $ra
    // 0x80091F18: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x80091F18: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_80091F1C:
    // 0x80091F1C: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091F20: lui         $t1, 0xBC00
    ctx->r9 = S32(0XBC00 << 16);
    // 0x80091F24: lui         $t2, 0x8036
    ctx->r10 = S32(0X8036 << 16);
    // 0x80091F28: addiu       $t2, $t2, 0x400
    ctx->r10 = ADD32(ctx->r10, 0X400);
    // 0x80091F2C: ori         $t1, $t1, 0x2806
    ctx->r9 = ctx->r9 | 0X2806;
    // 0x80091F30: sw          $t1, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r9;
    // 0x80091F34: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
    // 0x80091F38: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80091F3C: jr          $ra
    // 0x80091F40: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x80091F40: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80091F44: nop

    // 0x80091F48: nop

    // 0x80091F4C: nop

;}
RECOMP_FUNC void func_80091F50(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80091F50: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x80091F54: sw          $s1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r17;
    // 0x80091F58: sw          $s0, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r16;
    // 0x80091F5C: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x80091F60: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x80091F64: addiu       $s1, $s1, 0x1984
    ctx->r17 = ADD32(ctx->r17, 0X1984);
    // 0x80091F68: addiu       $s0, $s0, -0x1950
    ctx->r16 = ADD32(ctx->r16, -0X1950);
    // 0x80091F6C: lw          $t6, 0x0($s1)
    ctx->r14 = MEM_W(ctx->r17, 0X0);
    // 0x80091F70: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
    // 0x80091F74: sw          $zero, 0x8($s0)
    MEM_W(0X8, ctx->r16) = 0;
    // 0x80091F78: sw          $zero, 0xC($s0)
    MEM_W(0XC, ctx->r16) = 0;
    // 0x80091F7C: lui         $t7, 0x8015
    ctx->r15 = S32(0X8015 << 16);
    // 0x80091F80: sw          $t6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r14;
    // 0x80091F84: lw          $t7, 0x19AC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X19AC);
    // 0x80091F88: sw          $ra, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->r31;
    // 0x80091F8C: sw          $zero, 0x14($s0)
    MEM_W(0X14, ctx->r16) = 0;
    // 0x80091F90: sw          $zero, 0x18($s0)
    MEM_W(0X18, ctx->r16) = 0;
    // 0x80091F94: sw          $zero, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = 0;
    // 0x80091F98: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x80091F9C: sw          $t7, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r15;
    // 0x80091FA0: sdc1        $f30, 0x48($sp)
    CHECK_FR(ctx, 30);
    SD(ctx->f30.u64, 0X48, ctx->r29);
    // 0x80091FA4: sdc1        $f28, 0x40($sp)
    CHECK_FR(ctx, 28);
    SD(ctx->f28.u64, 0X40, ctx->r29);
    // 0x80091FA8: sdc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    SD(ctx->f26.u64, 0X38, ctx->r29);
    // 0x80091FAC: sdc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    SD(ctx->f24.u64, 0X30, ctx->r29);
    // 0x80091FB0: sdc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    SD(ctx->f22.u64, 0X28, ctx->r29);
    // 0x80091FB4: sdc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X20, ctx->r29);
    // 0x80091FB8: jal         0x800C5720
    // 0x80091FBC: lw          $a0, 0x45F0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45F0);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x80091FBC: lw          $a0, 0x45F0($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45F0);
    after_0:
    // 0x80091FC0: sw          $v0, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r2;
    // 0x80091FC4: sw          $zero, 0x24($s0)
    MEM_W(0X24, ctx->r16) = 0;
    // 0x80091FC8: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x80091FCC: jal         0x800C5720
    // 0x80091FD0: lw          $a0, 0x45E4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45E4);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_1;
    // 0x80091FD0: lw          $a0, 0x45E4($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45E4);
    after_1:
    // 0x80091FD4: sw          $v0, 0x34($s0)
    MEM_W(0X34, ctx->r16) = ctx->r2;
    // 0x80091FD8: lui         $a0, 0x800D
    ctx->r4 = S32(0X800D << 16);
    // 0x80091FDC: jal         0x800C5720
    // 0x80091FE0: lw          $a0, 0x45E8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45E8);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_2;
    // 0x80091FE0: lw          $a0, 0x45E8($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X45E8);
    after_2:
    // 0x80091FE4: sw          $v0, 0x38($s0)
    MEM_W(0X38, ctx->r16) = ctx->r2;
    // 0x80091FE8: jal         0x800C9E20
    // 0x80091FEC: lw          $a0, 0x0($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X0);
    osPhysicalToVirtual(rdram, ctx);
        goto after_3;
    // 0x80091FEC: lw          $a0, 0x0($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X0);
    after_3:
    // 0x80091FF0: lui         $t5, 0x8012
    ctx->r13 = S32(0X8012 << 16);
    // 0x80091FF4: lw          $t5, -0x720($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X720);
    // 0x80091FF8: lui         $t8, 0x101
    ctx->r24 = S32(0X101 << 16);
    // 0x80091FFC: lui         $t9, 0x100
    ctx->r25 = S32(0X100 << 16);
    // 0x80092000: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x80092004: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x80092008: addiu       $t9, $t9, 0x0
    ctx->r25 = ADD32(ctx->r25, 0X0);
    // 0x8009200C: addiu       $t8, $t8, -0x7D70
    ctx->r24 = ADD32(ctx->r24, -0X7D70);
    // 0x80092010: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x80092014: subu        $t1, $t8, $t9
    ctx->r9 = SUB32(ctx->r24, ctx->r25);
    // 0x80092018: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x8009201C: addiu       $t2, $t1, 0xF
    ctx->r10 = ADD32(ctx->r9, 0XF);
    // 0x80092020: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x80092024: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x80092028: and         $t3, $t2, $at
    ctx->r11 = ctx->r10 & ctx->r1;
    // 0x8009202C: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x80092030: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x80092034: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x80092038: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009203C: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x80092040: subu        $t6, $t6, $t5
    ctx->r14 = SUB32(ctx->r14, ctx->r13);
    // 0x80092044: addiu       $s0, $s0, -0x4938
    ctx->r16 = ADD32(ctx->r16, -0X4938);
    // 0x80092048: sw          $t4, -0x3170($at)
    MEM_W(-0X3170, ctx->r1) = ctx->r12;
    // 0x8009204C: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80092050: addu        $t7, $s0, $t6
    ctx->r15 = ADD32(ctx->r16, ctx->r14);
    // 0x80092054: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092058: sw          $t7, -0x1A08($at)
    MEM_W(-0X1A08, ctx->r1) = ctx->r15;
    // 0x8009205C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092060: sw          $zero, -0x1A04($at)
    MEM_W(-0X1A04, ctx->r1) = 0;
    // 0x80092064: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092068: addiu       $t8, $zero, -0x1
    ctx->r24 = ADD32(0, -0X1);
    // 0x8009206C: sh          $t8, -0x19DC($at)
    MEM_H(-0X19DC, ctx->r1) = ctx->r24;
    // 0x80092070: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092074: sh          $zero, -0x19D8($at)
    MEM_H(-0X19D8, ctx->r1) = 0;
    // 0x80092078: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009207C: sh          $zero, -0x19D4($at)
    MEM_H(-0X19D4, ctx->r1) = 0;
    // 0x80092080: lui         $at, 0x802C
    ctx->r1 = S32(0X802C << 16);
    // 0x80092084: sw          $zero, 0x6EE4($at)
    MEM_W(0X6EE4, ctx->r1) = 0;
    // 0x80092088: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x8009208C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092090: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x80092094: addiu       $s1, $s1, -0x4D80
    ctx->r17 = ADD32(ctx->r17, -0X4D80);
    // 0x80092098: sh          $t9, -0x18D2($at)
    MEM_H(-0X18D2, ctx->r1) = ctx->r25;
    // 0x8009209C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800920A0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800920A4: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800920A8: sb          $zero, 0x0($s1)
    MEM_B(0X0, ctx->r17) = 0;
    // 0x800920AC: addiu       $v1, $v1, -0x56C0
    ctx->r3 = ADD32(ctx->r3, -0X56C0);
    // 0x800920B0: addiu       $a0, $a0, -0x4D78
    ctx->r4 = ADD32(ctx->r4, -0X4D78);
    // 0x800920B4: addiu       $v0, $v0, -0x56B0
    ctx->r2 = ADD32(ctx->r2, -0X56B0);
L_800920B8:
    // 0x800920B8: lw          $t1, 0x0($v1)
    ctx->r9 = MEM_W(ctx->r3, 0X0);
    // 0x800920BC: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x800920C0: sltu        $at, $v1, $v0
    ctx->r1 = ctx->r3 < ctx->r2 ? 1 : 0;
    // 0x800920C4: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800920C8: bne         $at, $zero, L_800920B8
    if (ctx->r1 != 0) {
        // 0x800920CC: sw          $t1, -0x4($a0)
        MEM_W(-0X4, ctx->r4) = ctx->r9;
            goto L_800920B8;
    }
    // 0x800920CC: sw          $t1, -0x4($a0)
    MEM_W(-0X4, ctx->r4) = ctx->r9;
    // 0x800920D0: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x800920D4: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x800920D8: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800920DC: addiu       $t0, $t0, -0x5654
    ctx->r8 = ADD32(ctx->r8, -0X5654);
    // 0x800920E0: addiu       $a2, $a2, -0x5678
    ctx->r6 = ADD32(ctx->r6, -0X5678);
    // 0x800920E4: addiu       $a3, $a3, -0x4CF8
    ctx->r7 = ADD32(ctx->r7, -0X4CF8);
    // 0x800920E8: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
L_800920EC:
    // 0x800920EC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800920F0: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x800920F4: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
L_800920F8:
    // 0x800920F8: lw          $t2, 0x0($a0)
    ctx->r10 = MEM_W(ctx->r4, 0X0);
    // 0x800920FC: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x80092100: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x80092104: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x80092108: bne         $v0, $a1, L_800920F8
    if (ctx->r2 != ctx->r5) {
        // 0x8009210C: sw          $t2, -0x4($v1)
        MEM_W(-0X4, ctx->r3) = ctx->r10;
            goto L_800920F8;
    }
    // 0x8009210C: sw          $t2, -0x4($v1)
    MEM_W(-0X4, ctx->r3) = ctx->r10;
    // 0x80092110: addiu       $a2, $a2, 0xC
    ctx->r6 = ADD32(ctx->r6, 0XC);
    // 0x80092114: sltu        $at, $a2, $t0
    ctx->r1 = ctx->r6 < ctx->r8 ? 1 : 0;
    // 0x80092118: bne         $at, $zero, L_800920EC
    if (ctx->r1 != 0) {
        // 0x8009211C: addiu       $a3, $a3, 0xC
        ctx->r7 = ADD32(ctx->r7, 0XC);
            goto L_800920EC;
    }
    // 0x8009211C: addiu       $a3, $a3, 0xC
    ctx->r7 = ADD32(ctx->r7, 0XC);
    // 0x80092120: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80092124: lwc1        $f22, -0x5388($at)
    ctx->f22.u32l = MEM_W(ctx->r1, -0X5388);
    // 0x80092128: lui         $at, 0x4370
    ctx->r1 = S32(0X4370 << 16);
    // 0x8009212C: mtc1        $at, $f24
    ctx->f24.u32l = ctx->r1;
    // 0x80092130: lui         $at, 0x42C8
    ctx->r1 = S32(0X42C8 << 16);
    // 0x80092134: mtc1        $at, $f26
    ctx->f26.u32l = ctx->r1;
    // 0x80092138: lui         $at, 0xC2C8
    ctx->r1 = S32(0XC2C8 << 16);
    // 0x8009213C: mtc1        $at, $f28
    ctx->f28.u32l = ctx->r1;
    // 0x80092140: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x80092144: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80092148: mtc1        $at, $f30
    ctx->f30.u32l = ctx->r1;
    // 0x8009214C: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
    // 0x80092150: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x80092154: mfc1        $a1, $f20
    ctx->r5 = (int32_t)ctx->f20.u32l;
    // 0x80092158: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009215C: swc1        $f26, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f26.u32l;
    // 0x80092160: swc1        $f28, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f28.u32l;
    // 0x80092164: swc1        $f20, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f20.u32l;
    // 0x80092168: jal         0x800C74D4
    // 0x8009216C: swc1        $f30, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f30.u32l;
    func_800C74D4(rdram, ctx);
        goto after_4;
    // 0x8009216C: swc1        $f30, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f30.u32l;
    after_4:
    // 0x80092170: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80092174: mfc1        $a1, $f20
    ctx->r5 = (int32_t)ctx->f20.u32l;
    // 0x80092178: mfc1        $a2, $f22
    ctx->r6 = (int32_t)ctx->f22.u32l;
    // 0x8009217C: mfc1        $a3, $f24
    ctx->r7 = (int32_t)ctx->f24.u32l;
    // 0x80092180: addiu       $a0, $a0, -0x31A0
    ctx->r4 = ADD32(ctx->r4, -0X31A0);
    // 0x80092184: swc1        $f20, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f20.u32l;
    // 0x80092188: swc1        $f26, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f26.u32l;
    // 0x8009218C: swc1        $f28, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f28.u32l;
    // 0x80092190: jal         0x800C74D4
    // 0x80092194: swc1        $f30, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f30.u32l;
    func_800C74D4(rdram, ctx);
        goto after_5;
    // 0x80092194: swc1        $f30, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f30.u32l;
    after_5:
    // 0x80092198: jal         0x8004BA18
    // 0x8009219C: nop

    func_8004BA18(rdram, ctx);
        goto after_6;
    // 0x8009219C: nop

    after_6:
    // 0x800921A0: jal         0x80051530
    // 0x800921A4: nop

    func_80051530(rdram, ctx);
        goto after_7;
    // 0x800921A4: nop

    after_7:
    // 0x800921A8: jal         0x80088EA0
    // 0x800921AC: nop

    func_80088EA0(rdram, ctx);
        goto after_8;
    // 0x800921AC: nop

    after_8:
    // 0x800921B0: jal         0x801DD85C
    // 0x800921B4: nop

    func_801DD85C(rdram, ctx);
        goto after_9;
    // 0x800921B4: nop

    after_9:
    // 0x800921B8: jal         0x80094FE8
    // 0x800921BC: nop

    func_80094FE8(rdram, ctx);
        goto after_10;
    // 0x800921BC: nop

    after_10:
    // 0x800921C0: jal         0x8007BD70
    // 0x800921C4: nop

    func_8007BD70(rdram, ctx);
        goto after_11;
    // 0x800921C4: nop

    after_11:
    // 0x800921C8: jal         0x8007BE00
    // 0x800921CC: nop

    func_8007BE00(rdram, ctx);
        goto after_12;
    // 0x800921CC: nop

    after_12:
    // 0x800921D0: lb          $v1, 0x0($s1)
    ctx->r3 = MEM_B(ctx->r17, 0X0);
    // 0x800921D4: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x800921D8: addiu       $s0, $s0, -0x5614
    ctx->r16 = ADD32(ctx->r16, -0X5614);
    // 0x800921DC: andi        $t3, $v1, 0xC0
    ctx->r11 = ctx->r3 & 0XC0;
    // 0x800921E0: sll         $t4, $t3, 24
    ctx->r12 = S32(ctx->r11 << 24);
    // 0x800921E4: sra         $v1, $t4, 24
    ctx->r3 = S32(SIGNED(ctx->r12) >> 24);
    // 0x800921E8: andi        $t6, $v1, 0x40
    ctx->r14 = ctx->r3 & 0X40;
    // 0x800921EC: beq         $t6, $zero, L_80092208
    if (ctx->r14 == 0) {
        // 0x800921F0: addiu       $t7, $zero, 0x1
        ctx->r15 = ADD32(0, 0X1);
            goto L_80092208;
    }
    // 0x800921F0: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800921F4: sw          $t7, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r15;
    // 0x800921F8: jal         0x800C2FDC
    // 0x800921FC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C2FDC(rdram, ctx);
        goto after_13;
    // 0x800921FC: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_13:
    // 0x80092200: b           L_80092248
    // 0x80092204: lb          $t1, 0x0($s1)
    ctx->r9 = MEM_B(ctx->r17, 0X0);
        goto L_80092248;
    // 0x80092204: lb          $t1, 0x0($s1)
    ctx->r9 = MEM_B(ctx->r17, 0X0);
L_80092208:
    // 0x80092208: andi        $t8, $v1, 0x80
    ctx->r24 = ctx->r3 & 0X80;
    // 0x8009220C: beq         $t8, $zero, L_80092230
    if (ctx->r24 == 0) {
        // 0x80092210: lui         $s0, 0x800E
        ctx->r16 = S32(0X800E << 16);
            goto L_80092230;
    }
    // 0x80092210: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80092214: addiu       $s0, $s0, -0x5614
    ctx->r16 = ADD32(ctx->r16, -0X5614);
    // 0x80092218: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x8009221C: sw          $t9, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r25;
    // 0x80092220: jal         0x800C2FDC
    // 0x80092224: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C2FDC(rdram, ctx);
        goto after_14;
    // 0x80092224: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_14:
    // 0x80092228: b           L_80092248
    // 0x8009222C: lb          $t1, 0x0($s1)
    ctx->r9 = MEM_B(ctx->r17, 0X0);
        goto L_80092248;
    // 0x8009222C: lb          $t1, 0x0($s1)
    ctx->r9 = MEM_B(ctx->r17, 0X0);
L_80092230:
    // 0x80092230: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80092234: addiu       $s0, $s0, -0x5614
    ctx->r16 = ADD32(ctx->r16, -0X5614);
    // 0x80092238: sw          $zero, 0x0($s0)
    MEM_W(0X0, ctx->r16) = 0;
    // 0x8009223C: jal         0x800C2FDC
    // 0x80092240: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C2FDC(rdram, ctx);
        goto after_15;
    // 0x80092240: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_15:
    // 0x80092244: lb          $t1, 0x0($s1)
    ctx->r9 = MEM_B(ctx->r17, 0X0);
L_80092248:
    // 0x80092248: andi        $t2, $t1, 0x20
    ctx->r10 = ctx->r9 & 0X20;
    // 0x8009224C: beql        $t2, $zero, L_80092268
    if (ctx->r10 == 0) {
        // 0x80092250: addiu       $t3, $zero, 0x1
        ctx->r11 = ADD32(0, 0X1);
            goto L_80092268;
    }
    goto skip_0;
    // 0x80092250: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    skip_0:
    // 0x80092254: jal         0x800C3044
    // 0x80092258: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    myfree(rdram, ctx);
        goto after_16;
    // 0x80092258: sw          $zero, 0x4($s0)
    MEM_W(0X4, ctx->r16) = 0;
    after_16:
    // 0x8009225C: b           L_80092270
    // 0x80092260: nop

        goto L_80092270;
    // 0x80092260: nop

    // 0x80092264: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
L_80092268:
    // 0x80092268: jal         0x800C3034
    // 0x8009226C: sw          $t3, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r11;
    leoInitUnit_atten(rdram, ctx);
        goto after_17;
    // 0x8009226C: sw          $t3, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r11;
    after_17:
L_80092270:
    // 0x80092270: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80092274: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80092278: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x8009227C: addiu       $v1, $v1, -0x54F0
    ctx->r3 = ADD32(ctx->r3, -0X54F0);
    // 0x80092280: addiu       $a0, $a0, -0x1954
    ctx->r4 = ADD32(ctx->r4, -0X1954);
    // 0x80092284: addiu       $v0, $v0, -0x19A8
    ctx->r2 = ADD32(ctx->r2, -0X19A8);
L_80092288:
    // 0x80092288: lw          $at, 0x0($v1)
    ctx->r1 = MEM_W(ctx->r3, 0X0);
    // 0x8009228C: lw          $t5, 0x4($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X4);
    // 0x80092290: addiu       $v0, $v0, 0x1C
    ctx->r2 = ADD32(ctx->r2, 0X1C);
    // 0x80092294: swl         $at, -0x1C($v0)
    do_swl(rdram, -0X1C, ctx->r2, ctx->r1);
    // 0x80092298: swr         $at, -0x19($v0)
    do_swr(rdram, -0X19, ctx->r2, ctx->r1);
    // 0x8009229C: lhu         $at, 0x8($v1)
    ctx->r1 = MEM_HU(ctx->r3, 0X8);
    // 0x800922A0: swl         $t5, -0x18($v0)
    do_swl(rdram, -0X18, ctx->r2, ctx->r13);
    // 0x800922A4: sw          $zero, -0x4($v0)
    MEM_W(-0X4, ctx->r2) = 0;
    // 0x800922A8: sw          $zero, -0x8($v0)
    MEM_W(-0X8, ctx->r2) = 0;
    // 0x800922AC: swr         $t5, -0x15($v0)
    do_swr(rdram, -0X15, ctx->r2, ctx->r13);
    // 0x800922B0: bne         $v0, $a0, L_80092288
    if (ctx->r2 != ctx->r4) {
        // 0x800922B4: sh          $at, -0x14($v0)
        MEM_H(-0X14, ctx->r2) = ctx->r1;
            goto L_80092288;
    }
    // 0x800922B4: sh          $at, -0x14($v0)
    MEM_H(-0X14, ctx->r2) = ctx->r1;
    // 0x800922B8: lw          $ra, 0x5C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X5C);
    // 0x800922BC: ldc1        $f20, 0x20($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X20);
    // 0x800922C0: ldc1        $f22, 0x28($sp)
    CHECK_FR(ctx, 22);
    ctx->f22.u64 = LD(ctx->r29, 0X28);
    // 0x800922C4: ldc1        $f24, 0x30($sp)
    CHECK_FR(ctx, 24);
    ctx->f24.u64 = LD(ctx->r29, 0X30);
    // 0x800922C8: ldc1        $f26, 0x38($sp)
    CHECK_FR(ctx, 26);
    ctx->f26.u64 = LD(ctx->r29, 0X38);
    // 0x800922CC: ldc1        $f28, 0x40($sp)
    CHECK_FR(ctx, 28);
    ctx->f28.u64 = LD(ctx->r29, 0X40);
    // 0x800922D0: ldc1        $f30, 0x48($sp)
    CHECK_FR(ctx, 30);
    ctx->f30.u64 = LD(ctx->r29, 0X48);
    // 0x800922D4: lw          $s0, 0x54($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X54);
    // 0x800922D8: lw          $s1, 0x58($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X58);
    // 0x800922DC: jr          $ra
    // 0x800922E0: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x800922E0: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC void func_800922E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800922E4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800922E8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800922EC: jal         0x8004A2B4
    // 0x800922F0: nop

    SysUtils_UpdateControllers(rdram, ctx);
        goto after_0;
    // 0x800922F0: nop

    after_0:
    // 0x800922F4: jal         0x8006A264
    // 0x800922F8: nop

    func_8006A264(rdram, ctx);
        goto after_1;
    // 0x800922F8: nop

    after_1:
    // 0x800922FC: lui         $t6, 0x8012
    ctx->r14 = S32(0X8012 << 16);
    // 0x80092300: lw          $t6, -0x720($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X720);
    // 0x80092304: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x80092308: lw          $t0, -0x19C4($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X19C4);
    // 0x8009230C: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80092310: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80092314: sll         $t7, $t7, 4
    ctx->r15 = S32(ctx->r15 << 4);
    // 0x80092318: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x8009231C: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80092320: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x80092324: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80092328: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x8009232C: subu        $t7, $t7, $t6
    ctx->r15 = SUB32(ctx->r15, ctx->r14);
    // 0x80092330: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x80092334: addiu       $t8, $t8, -0x4938
    ctx->r24 = ADD32(ctx->r24, -0X4938);
    // 0x80092338: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x8009233C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092340: beq         $t0, $zero, L_8009239C
    if (ctx->r8 == 0) {
        // 0x80092344: sw          $t9, -0x1A08($at)
        MEM_W(-0X1A08, ctx->r1) = ctx->r25;
            goto L_8009239C;
    }
    // 0x80092344: sw          $t9, -0x1A08($at)
    MEM_W(-0X1A08, ctx->r1) = ctx->r25;
    // 0x80092348: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x8009234C: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80092350: addiu       $v1, $v1, -0x4C00
    ctx->r3 = ADD32(ctx->r3, -0X4C00);
    // 0x80092354: addiu       $a0, $zero, 0x23
    ctx->r4 = ADD32(0, 0X23);
    // 0x80092358: sw          $zero, 0x47E0($at)
    MEM_W(0X47E0, ctx->r1) = 0;
    // 0x8009235C: sb          $a0, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r4;
    // 0x80092360: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80092364: lw          $v0, -0x54DC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54DC);
    // 0x80092368: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009236C: sb          $a0, -0x4BFF($at)
    MEM_B(-0X4BFF, ctx->r1) = ctx->r4;
    // 0x80092370: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x80092374: bne         $v0, $at, L_80092384
    if (ctx->r2 != ctx->r1) {
        // 0x80092378: addiu       $t1, $zero, 0x32
        ctx->r9 = ADD32(0, 0X32);
            goto L_80092384;
    }
    // 0x80092378: addiu       $t1, $zero, 0x32
    ctx->r9 = ADD32(0, 0X32);
    // 0x8009237C: b           L_80092394
    // 0x80092380: sb          $t1, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r9;
        goto L_80092394;
    // 0x80092380: sb          $t1, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r9;
L_80092384:
    // 0x80092384: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x80092388: bne         $v0, $at, L_80092394
    if (ctx->r2 != ctx->r1) {
        // 0x8009238C: addiu       $t2, $zero, 0x3C
        ctx->r10 = ADD32(0, 0X3C);
            goto L_80092394;
    }
    // 0x8009238C: addiu       $t2, $zero, 0x3C
    ctx->r10 = ADD32(0, 0X3C);
    // 0x80092390: sb          $t2, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r10;
L_80092394:
    // 0x80092394: jal         0x800926F4
    // 0x80092398: nop

    func_800926F4(rdram, ctx);
        goto after_2;
    // 0x80092398: nop

    after_2:
L_8009239C:
    // 0x8009239C: jal         0x80092938
    // 0x800923A0: nop

    func_80092938(rdram, ctx);
        goto after_3;
    // 0x800923A0: nop

    after_3:
    // 0x800923A4: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800923A8: lw          $t3, -0x54DC($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X54DC);
    // 0x800923AC: addiu       $t4, $t3, -0x2
    ctx->r12 = ADD32(ctx->r11, -0X2);
    // 0x800923B0: sltiu       $at, $t4, 0x66
    ctx->r1 = ctx->r12 < 0X66 ? 1 : 0;
    // 0x800923B4: beq         $at, $zero, L_800926CC
    if (ctx->r1 == 0) {
        // 0x800923B8: sll         $t4, $t4, 2
        ctx->r12 = S32(ctx->r12 << 2);
            goto L_800926CC;
    }
    // 0x800923B8: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x800923BC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800923C0: addu        $at, $at, $t4
    gpr jr_addend_800923C8 = ctx->r12;
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x800923C4: lw          $t4, -0x5384($at)
    ctx->r12 = ADD32(ctx->r1, -0X5384);
    // 0x800923C8: jr          $t4
    // 0x800923CC: nop

    switch (jr_addend_800923C8 >> 2) {
        case 0: goto L_800923D0; break;
        case 1: goto L_800923D0; break;
        case 2: goto L_800923D0; break;
        case 3: goto L_80092654; break;
        case 4: goto L_80092654; break;
        case 5: goto L_800923D0; break;
        case 6: goto L_800923D0; break;
        case 7: goto L_800926CC; break;
        case 8: goto L_800924F4; break;
        case 9: goto L_800924F4; break;
        case 10: goto L_800926CC; break;
        case 11: goto L_800926CC; break;
        case 12: goto L_800926CC; break;
        case 13: goto L_800926CC; break;
        case 14: goto L_800926CC; break;
        case 15: goto L_800926CC; break;
        case 16: goto L_800926CC; break;
        case 17: goto L_800926CC; break;
        case 18: goto L_8009253C; break;
        case 19: goto L_8009253C; break;
        case 20: goto L_800926CC; break;
        case 21: goto L_800926CC; break;
        case 22: goto L_800926CC; break;
        case 23: goto L_800926CC; break;
        case 24: goto L_800926CC; break;
        case 25: goto L_800926CC; break;
        case 26: goto L_800926CC; break;
        case 27: goto L_800926CC; break;
        case 28: goto L_800923D0; break;
        case 29: goto L_800923D0; break;
        case 30: goto L_800926CC; break;
        case 31: goto L_800926CC; break;
        case 32: goto L_800926CC; break;
        case 33: goto L_800926CC; break;
        case 34: goto L_800926CC; break;
        case 35: goto L_800926CC; break;
        case 36: goto L_800926CC; break;
        case 37: goto L_800926CC; break;
        case 38: goto L_800923D0; break;
        case 39: goto L_800923D0; break;
        case 40: goto L_800923D0; break;
        case 41: goto L_800923D0; break;
        case 42: goto L_800923D0; break;
        case 43: goto L_800923D0; break;
        case 44: goto L_800926CC; break;
        case 45: goto L_800926CC; break;
        case 46: goto L_800926CC; break;
        case 47: goto L_800926CC; break;
        case 48: goto L_800924A4; break;
        case 49: goto L_800924A4; break;
        case 50: goto L_80092564; break;
        case 51: goto L_80092564; break;
        case 52: goto L_80092664; break;
        case 53: goto L_80092664; break;
        case 54: goto L_80092684; break;
        case 55: goto L_800926AC; break;
        case 56: goto L_800926CC; break;
        case 57: goto L_800926CC; break;
        case 58: goto L_800926CC; break;
        case 59: goto L_800926CC; break;
        case 60: goto L_8009258C; break;
        case 61: goto L_8009258C; break;
        case 62: goto L_800925F4; break;
        case 63: goto L_800925F4; break;
        case 64: goto L_800925D4; break;
        case 65: goto L_800925D4; break;
        case 66: goto L_800925E4; break;
        case 67: goto L_800925E4; break;
        case 68: goto L_800926CC; break;
        case 69: goto L_800926CC; break;
        case 70: goto L_800926CC; break;
        case 71: goto L_800926CC; break;
        case 72: goto L_800926CC; break;
        case 73: goto L_800926CC; break;
        case 74: goto L_800926CC; break;
        case 75: goto L_800926CC; break;
        case 76: goto L_800926CC; break;
        case 77: goto L_800926CC; break;
        case 78: goto L_800924CC; break;
        case 79: goto L_800924CC; break;
        case 80: goto L_800926CC; break;
        case 81: goto L_800926CC; break;
        case 82: goto L_800926CC; break;
        case 83: goto L_800926CC; break;
        case 84: goto L_800926CC; break;
        case 85: goto L_800926CC; break;
        case 86: goto L_800926CC; break;
        case 87: goto L_800926CC; break;
        case 88: goto L_80092604; break;
        case 89: goto L_80092604; break;
        case 90: goto L_800926CC; break;
        case 91: goto L_800926CC; break;
        case 92: goto L_800926CC; break;
        case 93: goto L_800926CC; break;
        case 94: goto L_800926CC; break;
        case 95: goto L_800926CC; break;
        case 96: goto L_800926CC; break;
        case 97: goto L_800926CC; break;
        case 98: goto L_8009262C; break;
        case 99: goto L_8009262C; break;
        case 100: goto L_800923D0; break;
        case 101: goto L_800923D0; break;
        default: switch_error(__func__, 0x800923C8, 0x800EAC7C);
    }
    // 0x800923CC: nop

L_800923D0:
    // 0x800923D0: jal         0x80086148
    // 0x800923D4: nop

    func_80086148(rdram, ctx);
        goto after_4;
    // 0x800923D4: nop

    after_4:
    // 0x800923D8: jal         0x800665B0
    // 0x800923DC: nop

    func_800665B0(rdram, ctx);
        goto after_5;
    // 0x800923DC: nop

    after_5:
    // 0x800923E0: jal         0x801DDE48
    // 0x800923E4: nop

    func_801DDE48(rdram, ctx);
        goto after_6;
    // 0x800923E4: nop

    after_6:
    // 0x800923E8: jal         0x80051238
    // 0x800923EC: nop

    func_80051238(rdram, ctx);
        goto after_7;
    // 0x800923EC: nop

    after_7:
    // 0x800923F0: jal         0x8008E794
    // 0x800923F4: nop

    func_8008E794(rdram, ctx);
        goto after_8;
    // 0x800923F4: nop

    after_8:
    // 0x800923F8: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x800923FC: lw          $t5, -0x19C8($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19C8);
    // 0x80092400: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    // 0x80092404: beq         $t5, $at, L_80092414
    if (ctx->r13 == ctx->r1) {
        // 0x80092408: nop
    
            goto L_80092414;
    }
    // 0x80092408: nop

    // 0x8009240C: jal         0x8006E3A8
    // 0x80092410: nop

    func_8006E3A8(rdram, ctx);
        goto after_9;
    // 0x80092410: nop

    after_9:
L_80092414:
    // 0x80092414: jal         0x800B2ABC
    // 0x80092418: nop

    func_800B2ABC(rdram, ctx);
        goto after_10;
    // 0x80092418: nop

    after_10:
    // 0x8009241C: jal         0x800AD418
    // 0x80092420: nop

    func_800AD418(rdram, ctx);
        goto after_11;
    // 0x80092420: nop

    after_11:
    // 0x80092424: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80092428: lw          $v0, -0x19C8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19C8);
    // 0x8009242C: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80092430: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80092434: bnel        $v0, $at, L_80092470
    if (ctx->r2 != ctx->r1) {
        // 0x80092438: addiu       $at, $zero, 0x8
        ctx->r1 = ADD32(0, 0X8);
            goto L_80092470;
    }
    goto skip_0;
    // 0x80092438: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    skip_0:
    // 0x8009243C: lw          $t6, -0x54DC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54DC);
    // 0x80092440: addiu       $at, $zero, 0x2D
    ctx->r1 = ADD32(0, 0X2D);
    // 0x80092444: bne         $t6, $at, L_8009245C
    if (ctx->r14 != ctx->r1) {
        // 0x80092448: nop
    
            goto L_8009245C;
    }
    // 0x80092448: nop

    // 0x8009244C: jal         0x802C7608
    // 0x80092450: nop

    func_i1_802C7608(rdram, ctx);
        goto after_12;
    // 0x80092450: nop

    after_12:
    // 0x80092454: b           L_800926CC
    // 0x80092458: nop

        goto L_800926CC;
    // 0x80092458: nop

L_8009245C:
    // 0x8009245C: jal         0x802C5800
    // 0x80092460: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_13;
    // 0x80092460: nop

    after_13:
    // 0x80092464: b           L_800926CC
    // 0x80092468: nop

        goto L_800926CC;
    // 0x80092468: nop

    // 0x8009246C: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
L_80092470:
    // 0x80092470: bnel        $v0, $at, L_8009248C
    if (ctx->r2 != ctx->r1) {
        // 0x80092474: addiu       $at, $zero, 0x15
        ctx->r1 = ADD32(0, 0X15);
            goto L_8009248C;
    }
    goto skip_1;
    // 0x80092474: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    skip_1:
    // 0x80092478: jal         0x802C5800
    // 0x8009247C: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_14;
    // 0x8009247C: nop

    after_14:
    // 0x80092480: b           L_800926CC
    // 0x80092484: nop

        goto L_800926CC;
    // 0x80092484: nop

    // 0x80092488: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
L_8009248C:
    // 0x8009248C: bne         $v0, $at, L_800926CC
    if (ctx->r2 != ctx->r1) {
        // 0x80092490: nop
    
            goto L_800926CC;
    }
    // 0x80092490: nop

    // 0x80092494: jal         0x802C5800
    // 0x80092498: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_15;
    // 0x80092498: nop

    after_15:
    // 0x8009249C: b           L_800926CC
    // 0x800924A0: nop

        goto L_800926CC;
    // 0x800924A0: nop

L_800924A4:
    // 0x800924A4: jal         0x801DDE48
    // 0x800924A8: nop

    func_801DDE48(rdram, ctx);
        goto after_16;
    // 0x800924A8: nop

    after_16:
    // 0x800924AC: jal         0x80051238
    // 0x800924B0: nop

    func_80051238(rdram, ctx);
        goto after_17;
    // 0x800924B0: nop

    after_17:
    // 0x800924B4: jal         0x8008E794
    // 0x800924B8: nop

    func_8008E794(rdram, ctx);
        goto after_18;
    // 0x800924B8: nop

    after_18:
    // 0x800924BC: jal         0x802C5800
    // 0x800924C0: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_19;
    // 0x800924C0: nop

    after_19:
    // 0x800924C4: b           L_800926CC
    // 0x800924C8: nop

        goto L_800926CC;
    // 0x800924C8: nop

L_800924CC:
    // 0x800924CC: jal         0x801DDE48
    // 0x800924D0: nop

    func_801DDE48(rdram, ctx);
        goto after_20;
    // 0x800924D0: nop

    after_20:
    // 0x800924D4: jal         0x80051238
    // 0x800924D8: nop

    func_80051238(rdram, ctx);
        goto after_21;
    // 0x800924D8: nop

    after_21:
    // 0x800924DC: jal         0x8008E794
    // 0x800924E0: nop

    func_8008E794(rdram, ctx);
        goto after_22;
    // 0x800924E0: nop

    after_22:
    // 0x800924E4: jal         0x802C5800
    // 0x800924E8: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_23;
    // 0x800924E8: nop

    after_23:
    // 0x800924EC: b           L_800926CC
    // 0x800924F0: nop

        goto L_800926CC;
    // 0x800924F0: nop

L_800924F4:
    // 0x800924F4: jal         0x80086148
    // 0x800924F8: nop

    func_80086148(rdram, ctx);
        goto after_24;
    // 0x800924F8: nop

    after_24:
    // 0x800924FC: jal         0x800665B0
    // 0x80092500: nop

    func_800665B0(rdram, ctx);
        goto after_25;
    // 0x80092500: nop

    after_25:
    // 0x80092504: jal         0x801DDE48
    // 0x80092508: nop

    func_801DDE48(rdram, ctx);
        goto after_26;
    // 0x80092508: nop

    after_26:
    // 0x8009250C: jal         0x80051238
    // 0x80092510: nop

    func_80051238(rdram, ctx);
        goto after_27;
    // 0x80092510: nop

    after_27:
    // 0x80092514: jal         0x8008E794
    // 0x80092518: nop

    func_8008E794(rdram, ctx);
        goto after_28;
    // 0x80092518: nop

    after_28:
    // 0x8009251C: jal         0x8006E3A8
    // 0x80092520: nop

    func_8006E3A8(rdram, ctx);
        goto after_29;
    // 0x80092520: nop

    after_29:
    // 0x80092524: jal         0x800B2ABC
    // 0x80092528: nop

    func_800B2ABC(rdram, ctx);
        goto after_30;
    // 0x80092528: nop

    after_30:
    // 0x8009252C: jal         0x802C5800
    // 0x80092530: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_31;
    // 0x80092530: nop

    after_31:
    // 0x80092534: b           L_800926CC
    // 0x80092538: nop

        goto L_800926CC;
    // 0x80092538: nop

L_8009253C:
    // 0x8009253C: jal         0x801DDE48
    // 0x80092540: nop

    func_801DDE48(rdram, ctx);
        goto after_32;
    // 0x80092540: nop

    after_32:
    // 0x80092544: jal         0x80051238
    // 0x80092548: nop

    func_80051238(rdram, ctx);
        goto after_33;
    // 0x80092548: nop

    after_33:
    // 0x8009254C: jal         0x8008E794
    // 0x80092550: nop

    func_8008E794(rdram, ctx);
        goto after_34;
    // 0x80092550: nop

    after_34:
    // 0x80092554: jal         0x802C5800
    // 0x80092558: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_35;
    // 0x80092558: nop

    after_35:
    // 0x8009255C: b           L_800926CC
    // 0x80092560: nop

        goto L_800926CC;
    // 0x80092560: nop

L_80092564:
    // 0x80092564: jal         0x801DDE48
    // 0x80092568: nop

    func_801DDE48(rdram, ctx);
        goto after_36;
    // 0x80092568: nop

    after_36:
    // 0x8009256C: jal         0x80051238
    // 0x80092570: nop

    func_80051238(rdram, ctx);
        goto after_37;
    // 0x80092570: nop

    after_37:
    // 0x80092574: jal         0x8008E794
    // 0x80092578: nop

    func_8008E794(rdram, ctx);
        goto after_38;
    // 0x80092578: nop

    after_38:
    // 0x8009257C: jal         0x802C5800
    // 0x80092580: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_39;
    // 0x80092580: nop

    after_39:
    // 0x80092584: b           L_800926CC
    // 0x80092588: nop

        goto L_800926CC;
    // 0x80092588: nop

L_8009258C:
    // 0x8009258C: jal         0x80086148
    // 0x80092590: nop

    func_80086148(rdram, ctx);
        goto after_40;
    // 0x80092590: nop

    after_40:
    // 0x80092594: jal         0x800665B0
    // 0x80092598: nop

    func_800665B0(rdram, ctx);
        goto after_41;
    // 0x80092598: nop

    after_41:
    // 0x8009259C: jal         0x801DDE48
    // 0x800925A0: nop

    func_801DDE48(rdram, ctx);
        goto after_42;
    // 0x800925A0: nop

    after_42:
    // 0x800925A4: jal         0x80051238
    // 0x800925A8: nop

    func_80051238(rdram, ctx);
        goto after_43;
    // 0x800925A8: nop

    after_43:
    // 0x800925AC: jal         0x8008E794
    // 0x800925B0: nop

    func_8008E794(rdram, ctx);
        goto after_44;
    // 0x800925B0: nop

    after_44:
    // 0x800925B4: jal         0x8006E3A8
    // 0x800925B8: nop

    func_8006E3A8(rdram, ctx);
        goto after_45;
    // 0x800925B8: nop

    after_45:
    // 0x800925BC: jal         0x800B2ABC
    // 0x800925C0: nop

    func_800B2ABC(rdram, ctx);
        goto after_46;
    // 0x800925C0: nop

    after_46:
    // 0x800925C4: jal         0x802C5800
    // 0x800925C8: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_47;
    // 0x800925C8: nop

    after_47:
    // 0x800925CC: b           L_800926CC
    // 0x800925D0: nop

        goto L_800926CC;
    // 0x800925D0: nop

L_800925D4:
    // 0x800925D4: jal         0x802C5800
    // 0x800925D8: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_48;
    // 0x800925D8: nop

    after_48:
    // 0x800925DC: b           L_800926CC
    // 0x800925E0: nop

        goto L_800926CC;
    // 0x800925E0: nop

L_800925E4:
    // 0x800925E4: jal         0x802C5800
    // 0x800925E8: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_49;
    // 0x800925E8: nop

    after_49:
    // 0x800925EC: b           L_800926CC
    // 0x800925F0: nop

        goto L_800926CC;
    // 0x800925F0: nop

L_800925F4:
    // 0x800925F4: jal         0x802C5800
    // 0x800925F8: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_50;
    // 0x800925F8: nop

    after_50:
    // 0x800925FC: b           L_800926CC
    // 0x80092600: nop

        goto L_800926CC;
    // 0x80092600: nop

L_80092604:
    // 0x80092604: jal         0x801DDE48
    // 0x80092608: nop

    func_801DDE48(rdram, ctx);
        goto after_51;
    // 0x80092608: nop

    after_51:
    // 0x8009260C: jal         0x80051238
    // 0x80092610: nop

    func_80051238(rdram, ctx);
        goto after_52;
    // 0x80092610: nop

    after_52:
    // 0x80092614: jal         0x8008E794
    // 0x80092618: nop

    func_8008E794(rdram, ctx);
        goto after_53;
    // 0x80092618: nop

    after_53:
    // 0x8009261C: jal         0x802C7090
    // 0x80092620: nop

    func_i5_802C7090(rdram, ctx);
        goto after_54;
    // 0x80092620: nop

    after_54:
    // 0x80092624: b           L_800926CC
    // 0x80092628: nop

        goto L_800926CC;
    // 0x80092628: nop

L_8009262C:
    // 0x8009262C: jal         0x801DDE48
    // 0x80092630: nop

    func_801DDE48(rdram, ctx);
        goto after_55;
    // 0x80092630: nop

    after_55:
    // 0x80092634: jal         0x80051238
    // 0x80092638: nop

    func_80051238(rdram, ctx);
        goto after_56;
    // 0x80092638: nop

    after_56:
    // 0x8009263C: jal         0x8008E794
    // 0x80092640: nop

    func_8008E794(rdram, ctx);
        goto after_57;
    // 0x80092640: nop

    after_57:
    // 0x80092644: jal         0x801E1290
    // 0x80092648: nop

    func_801E1290(rdram, ctx);
        goto after_58;
    // 0x80092648: nop

    after_58:
    // 0x8009264C: b           L_800926CC
    // 0x80092650: nop

        goto L_800926CC;
    // 0x80092650: nop

L_80092654:
    // 0x80092654: jal         0x802C5800
    // 0x80092658: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_59;
    // 0x80092658: nop

    after_59:
    // 0x8009265C: b           L_800926CC
    // 0x80092660: nop

        goto L_800926CC;
    // 0x80092660: nop

L_80092664:
    // 0x80092664: jal         0x801DDE48
    // 0x80092668: nop

    func_801DDE48(rdram, ctx);
        goto after_60;
    // 0x80092668: nop

    after_60:
    // 0x8009266C: jal         0x80051238
    // 0x80092670: nop

    func_80051238(rdram, ctx);
        goto after_61;
    // 0x80092670: nop

    after_61:
    // 0x80092674: jal         0x8008E794
    // 0x80092678: nop

    func_8008E794(rdram, ctx);
        goto after_62;
    // 0x80092678: nop

    after_62:
    // 0x8009267C: b           L_800926CC
    // 0x80092680: nop

        goto L_800926CC;
    // 0x80092680: nop

L_80092684:
    // 0x80092684: jal         0x801DDE48
    // 0x80092688: nop

    func_801DDE48(rdram, ctx);
        goto after_63;
    // 0x80092688: nop

    after_63:
    // 0x8009268C: jal         0x80051238
    // 0x80092690: nop

    func_80051238(rdram, ctx);
        goto after_64;
    // 0x80092690: nop

    after_64:
    // 0x80092694: jal         0x8008E794
    // 0x80092698: nop

    func_8008E794(rdram, ctx);
        goto after_65;
    // 0x80092698: nop

    after_65:
    // 0x8009269C: jal         0x802C5800
    // 0x800926A0: nop

    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_66;
    // 0x800926A0: nop

    after_66:
    // 0x800926A4: b           L_800926CC
    // 0x800926A8: nop

        goto L_800926CC;
    // 0x800926A8: nop

L_800926AC:
    // 0x800926AC: jal         0x801DDE48
    // 0x800926B0: nop

    func_801DDE48(rdram, ctx);
        goto after_67;
    // 0x800926B0: nop

    after_67:
    // 0x800926B4: jal         0x80051238
    // 0x800926B8: nop

    func_80051238(rdram, ctx);
        goto after_68;
    // 0x800926B8: nop

    after_68:
    // 0x800926BC: jal         0x8008E794
    // 0x800926C0: nop

    func_8008E794(rdram, ctx);
        goto after_69;
    // 0x800926C0: nop

    after_69:
    // 0x800926C4: jal         0x801E3250
    // 0x800926C8: nop

    func_801E3250(rdram, ctx);
        goto after_70;
    // 0x800926C8: nop

    after_70:
L_800926CC:
    // 0x800926CC: jal         0x801E5470
    // 0x800926D0: nop

    func_801E5470(rdram, ctx);
        goto after_71;
    // 0x800926D0: nop

    after_71:
    // 0x800926D4: jal         0x801EAFB4
    // 0x800926D8: nop

    func_801EAFB4(rdram, ctx);
        goto after_72;
    // 0x800926D8: nop

    after_72:
    // 0x800926DC: jal         0x801E71A8
    // 0x800926E0: nop

    func_801E71A8(rdram, ctx);
        goto after_73;
    // 0x800926E0: nop

    after_73:
    // 0x800926E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800926E8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800926EC: jr          $ra
    // 0x800926F0: nop

    return;
    // 0x800926F0: nop

;}
RECOMP_FUNC void func_800926F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800926F4: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800926F8: lw          $t6, -0x54DC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54DC);
    // 0x800926FC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80092700: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80092704: addiu       $t7, $t6, -0x2
    ctx->r15 = ADD32(ctx->r14, -0X2);
    // 0x80092708: sltiu       $at, $t7, 0x65
    ctx->r1 = ctx->r15 < 0X65 ? 1 : 0;
    // 0x8009270C: beq         $at, $zero, L_80092928
    if (ctx->r1 == 0) {
        // 0x80092710: sll         $t7, $t7, 2
        ctx->r15 = S32(ctx->r15 << 2);
            goto L_80092928;
    }
    // 0x80092710: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80092714: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80092718: addu        $at, $at, $t7
    gpr jr_addend_80092720 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x8009271C: lw          $t7, -0x51EC($at)
    ctx->r15 = ADD32(ctx->r1, -0X51EC);
    // 0x80092720: jr          $t7
    // 0x80092724: nop

    switch (jr_addend_80092720 >> 2) {
        case 0: goto L_80092728; break;
        case 1: goto L_80092928; break;
        case 2: goto L_80092928; break;
        case 3: goto L_80092928; break;
        case 4: goto L_80092928; break;
        case 5: goto L_80092728; break;
        case 6: goto L_80092928; break;
        case 7: goto L_80092928; break;
        case 8: goto L_80092728; break;
        case 9: goto L_80092928; break;
        case 10: goto L_80092928; break;
        case 11: goto L_80092928; break;
        case 12: goto L_80092928; break;
        case 13: goto L_80092928; break;
        case 14: goto L_80092928; break;
        case 15: goto L_80092928; break;
        case 16: goto L_80092928; break;
        case 17: goto L_80092928; break;
        case 18: goto L_800927DC; break;
        case 19: goto L_80092928; break;
        case 20: goto L_80092928; break;
        case 21: goto L_80092928; break;
        case 22: goto L_80092928; break;
        case 23: goto L_80092928; break;
        case 24: goto L_80092928; break;
        case 25: goto L_80092928; break;
        case 26: goto L_80092928; break;
        case 27: goto L_80092928; break;
        case 28: goto L_80092728; break;
        case 29: goto L_80092928; break;
        case 30: goto L_80092928; break;
        case 31: goto L_80092928; break;
        case 32: goto L_80092928; break;
        case 33: goto L_80092928; break;
        case 34: goto L_80092928; break;
        case 35: goto L_80092928; break;
        case 36: goto L_80092928; break;
        case 37: goto L_80092928; break;
        case 38: goto L_80092728; break;
        case 39: goto L_80092928; break;
        case 40: goto L_80092928; break;
        case 41: goto L_80092928; break;
        case 42: goto L_80092928; break;
        case 43: goto L_80092928; break;
        case 44: goto L_80092928; break;
        case 45: goto L_80092928; break;
        case 46: goto L_80092928; break;
        case 47: goto L_80092928; break;
        case 48: goto L_80092804; break;
        case 49: goto L_80092928; break;
        case 50: goto L_800927DC; break;
        case 51: goto L_80092928; break;
        case 52: goto L_800927DC; break;
        case 53: goto L_80092928; break;
        case 54: goto L_800927DC; break;
        case 55: goto L_80092928; break;
        case 56: goto L_80092928; break;
        case 57: goto L_80092928; break;
        case 58: goto L_80092928; break;
        case 59: goto L_80092928; break;
        case 60: goto L_80092728; break;
        case 61: goto L_80092928; break;
        case 62: goto L_80092928; break;
        case 63: goto L_80092928; break;
        case 64: goto L_80092928; break;
        case 65: goto L_80092928; break;
        case 66: goto L_80092928; break;
        case 67: goto L_80092928; break;
        case 68: goto L_80092928; break;
        case 69: goto L_80092928; break;
        case 70: goto L_80092928; break;
        case 71: goto L_80092928; break;
        case 72: goto L_80092928; break;
        case 73: goto L_80092928; break;
        case 74: goto L_80092928; break;
        case 75: goto L_80092928; break;
        case 76: goto L_80092928; break;
        case 77: goto L_80092928; break;
        case 78: goto L_800928AC; break;
        case 79: goto L_80092928; break;
        case 80: goto L_80092928; break;
        case 81: goto L_80092928; break;
        case 82: goto L_80092928; break;
        case 83: goto L_80092928; break;
        case 84: goto L_80092928; break;
        case 85: goto L_80092928; break;
        case 86: goto L_80092928; break;
        case 87: goto L_80092928; break;
        case 88: goto L_80092928; break;
        case 89: goto L_80092928; break;
        case 90: goto L_80092928; break;
        case 91: goto L_80092928; break;
        case 92: goto L_80092928; break;
        case 93: goto L_80092928; break;
        case 94: goto L_80092928; break;
        case 95: goto L_80092928; break;
        case 96: goto L_80092928; break;
        case 97: goto L_80092928; break;
        case 98: goto L_8009283C; break;
        case 99: goto L_80092928; break;
        case 100: goto L_80092728; break;
        default: switch_error(__func__, 0x80092720, 0x800EAE14);
    }
    // 0x80092724: nop

L_80092728:
    // 0x80092728: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009272C: jal         0x8006AACC
    // 0x80092730: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    func_8006AACC(rdram, ctx);
        goto after_0;
    // 0x80092730: lw          $a0, -0x7E90($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7E90);
    after_0:
    // 0x80092734: jal         0x80067E40
    // 0x80092738: nop

    func_80067E40(rdram, ctx);
        goto after_1;
    // 0x80092738: nop

    after_1:
    // 0x8009273C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80092740: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x80092744: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x80092748: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009274C: bne         $t8, $at, L_8009276C
    if (ctx->r24 != ctx->r1) {
        // 0x80092750: lui         $a1, 0x800D
        ctx->r5 = S32(0X800D << 16);
            goto L_8009276C;
    }
    // 0x80092750: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80092754: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80092758: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    // 0x8009275C: jal         0x8004F9E0
    // 0x80092760: addiu       $a0, $zero, -0x96
    ctx->r4 = ADD32(0, -0X96);
    func_8004F9E0(rdram, ctx);
        goto after_2;
    // 0x80092760: addiu       $a0, $zero, -0x96
    ctx->r4 = ADD32(0, -0X96);
    after_2:
    // 0x80092764: b           L_80092774
    // 0x80092768: nop

        goto L_80092774;
    // 0x80092768: nop

L_8009276C:
    // 0x8009276C: jal         0x8004F9E0
    // 0x80092770: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    func_8004F9E0(rdram, ctx);
        goto after_3;
    // 0x80092770: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    after_3:
L_80092774:
    // 0x80092774: jal         0x8008E4B0
    // 0x80092778: nop

    func_8008E4B0(rdram, ctx);
        goto after_4;
    // 0x80092778: nop

    after_4:
    // 0x8009277C: jal         0x801DDA24
    // 0x80092780: nop

    func_801DDA24(rdram, ctx);
        goto after_5;
    // 0x80092780: nop

    after_5:
    // 0x80092784: jal         0x800AC184
    // 0x80092788: nop

    func_800AC184(rdram, ctx);
        goto after_6;
    // 0x80092788: nop

    after_6:
    // 0x8009278C: jal         0x800AE7C4
    // 0x80092790: nop

    func_800AE7C4(rdram, ctx);
        goto after_7;
    // 0x80092790: nop

    after_7:
    // 0x80092794: jal         0x800893A8
    // 0x80092798: nop

    func_800893A8(rdram, ctx);
        goto after_8;
    // 0x80092798: nop

    after_8:
    // 0x8009279C: jal         0x8009C968
    // 0x800927A0: nop

    func_8009C968(rdram, ctx);
        goto after_9;
    // 0x800927A0: nop

    after_9:
    // 0x800927A4: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800927A8: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x800927AC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800927B0: bne         $t9, $at, L_800927C0
    if (ctx->r25 != ctx->r1) {
        // 0x800927B4: nop
    
            goto L_800927C0;
    }
    // 0x800927B4: nop

    // 0x800927B8: jal         0x8007FD80
    // 0x800927BC: nop

    func_8007FD80(rdram, ctx);
        goto after_10;
    // 0x800927BC: nop

    after_10:
L_800927C0:
    // 0x800927C0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800927C4: lw          $t0, -0x54DC($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X54DC);
    // 0x800927C8: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x800927CC: bne         $t0, $at, L_80092928
    if (ctx->r8 != ctx->r1) {
        // 0x800927D0: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_80092928;
    }
    // 0x800927D0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800927D4: b           L_80092928
    // 0x800927D8: sw          $zero, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = 0;
        goto L_80092928;
    // 0x800927D8: sw          $zero, -0x1908($at)
    MEM_W(-0X1908, ctx->r1) = 0;
L_800927DC:
    // 0x800927DC: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x800927E0: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    // 0x800927E4: jal         0x8004F9E0
    // 0x800927E8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_8004F9E0(rdram, ctx);
        goto after_11;
    // 0x800927E8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_11:
    // 0x800927EC: jal         0x8008E4B0
    // 0x800927F0: nop

    func_8008E4B0(rdram, ctx);
        goto after_12;
    // 0x800927F0: nop

    after_12:
    // 0x800927F4: jal         0x801DDA24
    // 0x800927F8: nop

    func_801DDA24(rdram, ctx);
        goto after_13;
    // 0x800927F8: nop

    after_13:
    // 0x800927FC: b           L_8009292C
    // 0x80092800: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8009292C;
    // 0x80092800: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80092804:
    // 0x80092804: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80092808: lw          $t1, -0x19CC($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X19CC);
    // 0x8009280C: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x80092810: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80092814: beq         $t1, $at, L_80092928
    if (ctx->r9 == ctx->r1) {
        // 0x80092818: lui         $a1, 0x800D
        ctx->r5 = S32(0X800D << 16);
            goto L_80092928;
    }
    // 0x80092818: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009281C: jal         0x8004F9E0
    // 0x80092820: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    func_8004F9E0(rdram, ctx);
        goto after_14;
    // 0x80092820: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    after_14:
    // 0x80092824: jal         0x8008E4B0
    // 0x80092828: nop

    func_8008E4B0(rdram, ctx);
        goto after_15;
    // 0x80092828: nop

    after_15:
    // 0x8009282C: jal         0x801DDA24
    // 0x80092830: nop

    func_801DDA24(rdram, ctx);
        goto after_16;
    // 0x80092830: nop

    after_16:
    // 0x80092834: b           L_8009292C
    // 0x80092838: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8009292C;
    // 0x80092838: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8009283C:
    // 0x8009283C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x80092840: lw          $t2, -0x19CC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X19CC);
    // 0x80092844: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x80092848: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009284C: bne         $t2, $at, L_80092878
    if (ctx->r10 != ctx->r1) {
        // 0x80092850: lui         $t3, 0x801D
        ctx->r11 = S32(0X801D << 16);
            goto L_80092878;
    }
    // 0x80092850: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80092854: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80092858: jal         0x8004F9E0
    // 0x8009285C: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    func_8004F9E0(rdram, ctx);
        goto after_17;
    // 0x8009285C: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    after_17:
    // 0x80092860: jal         0x8008E4B0
    // 0x80092864: nop

    func_8008E4B0(rdram, ctx);
        goto after_18;
    // 0x80092864: nop

    after_18:
    // 0x80092868: jal         0x801DDA24
    // 0x8009286C: nop

    func_801DDA24(rdram, ctx);
        goto after_19;
    // 0x8009286C: nop

    after_19:
    // 0x80092870: b           L_8009292C
    // 0x80092874: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8009292C;
    // 0x80092874: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80092878:
    // 0x80092878: lw          $t3, -0x19F8($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X19F8);
    // 0x8009287C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80092880: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80092884: bnel        $t3, $zero, L_8009292C
    if (ctx->r11 != 0) {
        // 0x80092888: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_8009292C;
    }
    goto skip_0;
    // 0x80092888: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x8009288C: jal         0x8004F9E0
    // 0x80092890: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    func_8004F9E0(rdram, ctx);
        goto after_20;
    // 0x80092890: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    after_20:
    // 0x80092894: jal         0x8008E4B0
    // 0x80092898: nop

    func_8008E4B0(rdram, ctx);
        goto after_21;
    // 0x80092898: nop

    after_21:
    // 0x8009289C: jal         0x801DDA24
    // 0x800928A0: nop

    func_801DDA24(rdram, ctx);
        goto after_22;
    // 0x800928A0: nop

    after_22:
    // 0x800928A4: b           L_8009292C
    // 0x800928A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_8009292C;
    // 0x800928A8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800928AC:
    // 0x800928AC: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x800928B0: lw          $t4, -0x19F8($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X19F8);
    // 0x800928B4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800928B8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800928BC: bne         $t4, $at, L_800928E0
    if (ctx->r12 != ctx->r1) {
        // 0x800928C0: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800928E0;
    }
    // 0x800928C0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800928C4: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x800928C8: lw          $t5, -0x19CC($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19CC);
    // 0x800928CC: addiu       $at, $zero, 0x43
    ctx->r1 = ADD32(0, 0X43);
    // 0x800928D0: beq         $t5, $at, L_80092904
    if (ctx->r13 == ctx->r1) {
        // 0x800928D4: nop
    
            goto L_80092904;
    }
    // 0x800928D4: nop

    // 0x800928D8: b           L_80092904
    // 0x800928DC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_80092904;
    // 0x800928DC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_800928E0:
    // 0x800928E0: lw          $v0, -0x19CC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19CC);
    // 0x800928E4: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x800928E8: beq         $v0, $at, L_80092900
    if (ctx->r2 == ctx->r1) {
        // 0x800928EC: addiu       $at, $zero, 0x32
        ctx->r1 = ADD32(0, 0X32);
            goto L_80092900;
    }
    // 0x800928EC: addiu       $at, $zero, 0x32
    ctx->r1 = ADD32(0, 0X32);
    // 0x800928F0: beq         $v0, $at, L_80092900
    if (ctx->r2 == ctx->r1) {
        // 0x800928F4: addiu       $at, $zero, 0x39
        ctx->r1 = ADD32(0, 0X39);
            goto L_80092900;
    }
    // 0x800928F4: addiu       $at, $zero, 0x39
    ctx->r1 = ADD32(0, 0X39);
    // 0x800928F8: bne         $v0, $at, L_80092904
    if (ctx->r2 != ctx->r1) {
        // 0x800928FC: nop
    
            goto L_80092904;
    }
    // 0x800928FC: nop

L_80092900:
    // 0x80092900: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_80092904:
    // 0x80092904: beq         $v1, $zero, L_80092928
    if (ctx->r3 == 0) {
        // 0x80092908: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80092928;
    }
    // 0x80092908: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009290C: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80092910: jal         0x8004F9E0
    // 0x80092914: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    func_8004F9E0(rdram, ctx);
        goto after_23;
    // 0x80092914: lw          $a1, 0x49B0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X49B0);
    after_23:
    // 0x80092918: jal         0x8008E4B0
    // 0x8009291C: nop

    func_8008E4B0(rdram, ctx);
        goto after_24;
    // 0x8009291C: nop

    after_24:
    // 0x80092920: jal         0x801DDA24
    // 0x80092924: nop

    func_801DDA24(rdram, ctx);
        goto after_25;
    // 0x80092924: nop

    after_25:
L_80092928:
    // 0x80092928: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8009292C:
    // 0x8009292C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80092930: jr          $ra
    // 0x80092934: nop

    return;
    // 0x80092934: nop

;}
RECOMP_FUNC void func_80092938(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80092938: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009293C: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x80092940: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x80092944: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x80092948: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x8009294C: addiu       $a3, $a3, -0x19A8
    ctx->r7 = ADD32(ctx->r7, -0X19A8);
    // 0x80092950: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x80092954: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80092958: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x8009295C: lui         $s2, 0x8015
    ctx->r18 = S32(0X8015 << 16);
    // 0x80092960: lui         $t5, 0x8015
    ctx->r13 = S32(0X8015 << 16);
    // 0x80092964: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80092968: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x8009296C: addiu       $t2, $t2, -0x4C00
    ctx->r10 = ADD32(ctx->r10, -0X4C00);
    // 0x80092970: addiu       $t3, $t3, -0x4BFF
    ctx->r11 = ADD32(ctx->r11, -0X4BFF);
    // 0x80092974: addiu       $t5, $t5, 0x4344
    ctx->r13 = ADD32(ctx->r13, 0X4344);
    // 0x80092978: addiu       $s2, $s2, 0x4330
    ctx->r18 = ADD32(ctx->r18, 0X4330);
    // 0x8009297C: addiu       $s1, $s1, 0x4308
    ctx->r17 = ADD32(ctx->r17, 0X4308);
    // 0x80092980: addiu       $s0, $s0, -0x54F0
    ctx->r16 = ADD32(ctx->r16, -0X54F0);
    // 0x80092984: addiu       $s3, $zero, 0xA
    ctx->r19 = ADD32(0, 0XA);
    // 0x80092988: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x8009298C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80092990: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x80092994: addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // 0x80092998: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
L_8009299C:
    // 0x8009299C: lwl         $at, 0x0($v1)
    ctx->r1 = do_lwl(rdram, ctx->r1, ctx->r3, 0X0);
    // 0x800929A0: lwr         $at, 0x3($v1)
    ctx->r1 = do_lwr(rdram, ctx->r1, ctx->r3, 0X3);
    // 0x800929A4: lwl         $t8, 0x4($v1)
    ctx->r24 = do_lwl(rdram, ctx->r24, ctx->r3, 0X4);
    // 0x800929A8: lwr         $t8, 0x7($v1)
    ctx->r24 = do_lwr(rdram, ctx->r24, ctx->r3, 0X7);
    // 0x800929AC: swl         $at, 0xA($v1)
    do_swl(rdram, 0XA, ctx->r3, ctx->r1);
    // 0x800929B0: swr         $at, 0xD($v1)
    do_swr(rdram, 0XD, ctx->r3, ctx->r1);
    // 0x800929B4: lhu         $at, 0x8($v1)
    ctx->r1 = MEM_HU(ctx->r3, 0X8);
    // 0x800929B8: swl         $t8, 0xE($v1)
    do_swl(rdram, 0XE, ctx->r3, ctx->r24);
    // 0x800929BC: swr         $t8, 0x11($v1)
    do_swr(rdram, 0X11, ctx->r3, ctx->r24);
    // 0x800929C0: beq         $v0, $zero, L_800929E0
    if (ctx->r2 == 0) {
        // 0x800929C4: sh          $at, 0x12($v1)
        MEM_H(0X12, ctx->r3) = ctx->r1;
            goto L_800929E0;
    }
    // 0x800929C4: sh          $at, 0x12($v1)
    MEM_H(0X12, ctx->r3) = ctx->r1;
    // 0x800929C8: beql        $v0, $t0, L_80092A50
    if (ctx->r2 == ctx->r8) {
        // 0x800929CC: lw          $a0, 0x0($t5)
        ctx->r4 = MEM_W(ctx->r13, 0X0);
            goto L_80092A50;
    }
    goto skip_0;
    // 0x800929CC: lw          $a0, 0x0($t5)
    ctx->r4 = MEM_W(ctx->r13, 0X0);
    skip_0:
    // 0x800929D0: beql        $v0, $t1, L_80092B00
    if (ctx->r2 == ctx->r9) {
        // 0x800929D4: lw          $t6, 0x0($t5)
        ctx->r14 = MEM_W(ctx->r13, 0X0);
            goto L_80092B00;
    }
    goto skip_1;
    // 0x800929D4: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    skip_1:
    // 0x800929D8: b           L_80092B98
    // 0x800929DC: lb          $a0, 0x8($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X8);
        goto L_80092B98;
    // 0x800929DC: lb          $a0, 0x8($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X8);
L_800929E0:
    // 0x800929E0: lw          $t9, 0x0($t5)
    ctx->r25 = MEM_W(ctx->r13, 0X0);
    // 0x800929E4: bgtzl       $t9, L_80092A14
    if (SIGNED(ctx->r25) > 0) {
        // 0x800929E8: lw          $t8, 0x0($s2)
        ctx->r24 = MEM_W(ctx->r18, 0X0);
            goto L_80092A14;
    }
    goto skip_2;
    // 0x800929E8: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    skip_2:
    // 0x800929EC: lw          $at, 0x0($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X0);
    // 0x800929F0: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x800929F4: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x800929F8: lw          $t6, 0x4($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X4);
    // 0x800929FC: swl         $t6, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r14);
    // 0x80092A00: swr         $t6, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r14);
    // 0x80092A04: lhu         $at, 0x8($s0)
    ctx->r1 = MEM_HU(ctx->r16, 0X8);
    // 0x80092A08: b           L_80092B94
    // 0x80092A0C: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B94;
    // 0x80092A0C: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
    // 0x80092A10: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
L_80092A14:
    // 0x80092A14: multu       $t8, $s3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80092A18: mflo        $t9
    ctx->r25 = lo;
    // 0x80092A1C: addu        $t7, $s1, $t9
    ctx->r15 = ADD32(ctx->r17, ctx->r25);
    // 0x80092A20: lwl         $at, 0x0($t7)
    ctx->r1 = do_lwl(rdram, ctx->r1, ctx->r15, 0X0);
    // 0x80092A24: lwr         $at, 0x3($t7)
    ctx->r1 = do_lwr(rdram, ctx->r1, ctx->r15, 0X3);
    // 0x80092A28: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092A2C: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092A30: lwl         $t8, 0x4($t7)
    ctx->r24 = do_lwl(rdram, ctx->r24, ctx->r15, 0X4);
    // 0x80092A34: lwr         $t8, 0x7($t7)
    ctx->r24 = do_lwr(rdram, ctx->r24, ctx->r15, 0X7);
    // 0x80092A38: swl         $t8, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r24);
    // 0x80092A3C: swr         $t8, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r24);
    // 0x80092A40: lhu         $at, 0x8($t7)
    ctx->r1 = MEM_HU(ctx->r15, 0X8);
    // 0x80092A44: b           L_80092B94
    // 0x80092A48: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B94;
    // 0x80092A48: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
    // 0x80092A4C: lw          $a0, 0x0($t5)
    ctx->r4 = MEM_W(ctx->r13, 0X0);
L_80092A50:
    // 0x80092A50: bne         $a0, $zero, L_80092A7C
    if (ctx->r4 != 0) {
        // 0x80092A54: nop
    
            goto L_80092A7C;
    }
    // 0x80092A54: nop

    // 0x80092A58: lw          $at, 0x0($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X0);
    // 0x80092A5C: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092A60: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092A64: lw          $t6, 0x4($s0)
    ctx->r14 = MEM_W(ctx->r16, 0X4);
    // 0x80092A68: swl         $t6, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r14);
    // 0x80092A6C: swr         $t6, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r14);
    // 0x80092A70: lhu         $at, 0x8($s0)
    ctx->r1 = MEM_HU(ctx->r16, 0X8);
    // 0x80092A74: b           L_80092B94
    // 0x80092A78: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B94;
    // 0x80092A78: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
L_80092A7C:
    // 0x80092A7C: bnel        $t0, $a0, L_80092AC4
    if (ctx->r8 != ctx->r4) {
        // 0x80092A80: lw          $t8, 0x4($s2)
        ctx->r24 = MEM_W(ctx->r18, 0X4);
            goto L_80092AC4;
    }
    goto skip_3;
    // 0x80092A80: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
    skip_3:
    // 0x80092A84: lw          $t7, 0x0($s2)
    ctx->r15 = MEM_W(ctx->r18, 0X0);
    // 0x80092A88: multu       $t7, $s3
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80092A8C: mflo        $t8
    ctx->r24 = lo;
    // 0x80092A90: addu        $t9, $s1, $t8
    ctx->r25 = ADD32(ctx->r17, ctx->r24);
    // 0x80092A94: lwl         $at, 0x0($t9)
    ctx->r1 = do_lwl(rdram, ctx->r1, ctx->r25, 0X0);
    // 0x80092A98: lwr         $at, 0x3($t9)
    ctx->r1 = do_lwr(rdram, ctx->r1, ctx->r25, 0X3);
    // 0x80092A9C: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092AA0: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092AA4: lwl         $t7, 0x4($t9)
    ctx->r15 = do_lwl(rdram, ctx->r15, ctx->r25, 0X4);
    // 0x80092AA8: lwr         $t7, 0x7($t9)
    ctx->r15 = do_lwr(rdram, ctx->r15, ctx->r25, 0X7);
    // 0x80092AAC: swl         $t7, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r15);
    // 0x80092AB0: swr         $t7, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r15);
    // 0x80092AB4: lhu         $at, 0x8($t9)
    ctx->r1 = MEM_HU(ctx->r25, 0X8);
    // 0x80092AB8: b           L_80092B94
    // 0x80092ABC: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B94;
    // 0x80092ABC: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
    // 0x80092AC0: lw          $t8, 0x4($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X4);
L_80092AC4:
    // 0x80092AC4: multu       $t8, $s3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80092AC8: mflo        $t6
    ctx->r14 = lo;
    // 0x80092ACC: addu        $t9, $s1, $t6
    ctx->r25 = ADD32(ctx->r17, ctx->r14);
    // 0x80092AD0: lwl         $at, 0x0($t9)
    ctx->r1 = do_lwl(rdram, ctx->r1, ctx->r25, 0X0);
    // 0x80092AD4: lwr         $at, 0x3($t9)
    ctx->r1 = do_lwr(rdram, ctx->r1, ctx->r25, 0X3);
    // 0x80092AD8: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092ADC: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092AE0: lwl         $t8, 0x4($t9)
    ctx->r24 = do_lwl(rdram, ctx->r24, ctx->r25, 0X4);
    // 0x80092AE4: lwr         $t8, 0x7($t9)
    ctx->r24 = do_lwr(rdram, ctx->r24, ctx->r25, 0X7);
    // 0x80092AE8: swl         $t8, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r24);
    // 0x80092AEC: swr         $t8, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r24);
    // 0x80092AF0: lhu         $at, 0x8($t9)
    ctx->r1 = MEM_HU(ctx->r25, 0X8);
    // 0x80092AF4: b           L_80092B94
    // 0x80092AF8: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B94;
    // 0x80092AF8: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
    // 0x80092AFC: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
L_80092B00:
    // 0x80092B00: bgtzl       $t6, L_80092B30
    if (SIGNED(ctx->r14) > 0) {
        // 0x80092B04: lw          $t8, 0x0($s2)
        ctx->r24 = MEM_W(ctx->r18, 0X0);
            goto L_80092B30;
    }
    goto skip_4;
    // 0x80092B04: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
    skip_4:
    // 0x80092B08: lw          $at, 0x0($s0)
    ctx->r1 = MEM_W(ctx->r16, 0X0);
    // 0x80092B0C: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092B10: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092B14: lw          $t9, 0x4($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X4);
    // 0x80092B18: swl         $t9, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r25);
    // 0x80092B1C: swr         $t9, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r25);
    // 0x80092B20: lhu         $at, 0x8($s0)
    ctx->r1 = MEM_HU(ctx->r16, 0X8);
    // 0x80092B24: b           L_80092B64
    // 0x80092B28: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
        goto L_80092B64;
    // 0x80092B28: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
    // 0x80092B2C: lw          $t8, 0x0($s2)
    ctx->r24 = MEM_W(ctx->r18, 0X0);
L_80092B30:
    // 0x80092B30: multu       $t8, $s3
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80092B34: mflo        $t6
    ctx->r14 = lo;
    // 0x80092B38: addu        $t7, $s1, $t6
    ctx->r15 = ADD32(ctx->r17, ctx->r14);
    // 0x80092B3C: lwl         $at, 0x0($t7)
    ctx->r1 = do_lwl(rdram, ctx->r1, ctx->r15, 0X0);
    // 0x80092B40: lwr         $at, 0x3($t7)
    ctx->r1 = do_lwr(rdram, ctx->r1, ctx->r15, 0X3);
    // 0x80092B44: swl         $at, 0x0($v1)
    do_swl(rdram, 0X0, ctx->r3, ctx->r1);
    // 0x80092B48: swr         $at, 0x3($v1)
    do_swr(rdram, 0X3, ctx->r3, ctx->r1);
    // 0x80092B4C: lwl         $t8, 0x4($t7)
    ctx->r24 = do_lwl(rdram, ctx->r24, ctx->r15, 0X4);
    // 0x80092B50: lwr         $t8, 0x7($t7)
    ctx->r24 = do_lwr(rdram, ctx->r24, ctx->r15, 0X7);
    // 0x80092B54: swl         $t8, 0x4($v1)
    do_swl(rdram, 0X4, ctx->r3, ctx->r24);
    // 0x80092B58: swr         $t8, 0x7($v1)
    do_swr(rdram, 0X7, ctx->r3, ctx->r24);
    // 0x80092B5C: lhu         $at, 0x8($t7)
    ctx->r1 = MEM_HU(ctx->r15, 0X8);
    // 0x80092B60: sh          $at, 0x8($v1)
    MEM_H(0X8, ctx->r3) = ctx->r1;
L_80092B64:
    // 0x80092B64: lw          $t6, 0x0($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X0);
    // 0x80092B68: slti        $at, $t6, 0x2
    ctx->r1 = SIGNED(ctx->r14) < 0X2 ? 1 : 0;
    // 0x80092B6C: bnel        $at, $zero, L_80092B98
    if (ctx->r1 != 0) {
        // 0x80092B70: lb          $a0, 0x8($v1)
        ctx->r4 = MEM_B(ctx->r3, 0X8);
            goto L_80092B98;
    }
    goto skip_5;
    // 0x80092B70: lb          $a0, 0x8($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X8);
    skip_5:
    // 0x80092B74: lhu         $t9, 0x0($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X0);
    // 0x80092B78: lhu         $t7, 0x1C($a3)
    ctx->r15 = MEM_HU(ctx->r7, 0X1C);
    // 0x80092B7C: lhu         $t6, 0x2($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X2);
    // 0x80092B80: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x80092B84: sh          $t8, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r24;
    // 0x80092B88: lhu         $t9, 0x1E($a3)
    ctx->r25 = MEM_HU(ctx->r7, 0X1E);
    // 0x80092B8C: or          $t7, $t6, $t9
    ctx->r15 = ctx->r14 | ctx->r25;
    // 0x80092B90: sh          $t7, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r15;
L_80092B94:
    // 0x80092B94: lb          $a0, 0x8($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X8);
L_80092B98:
    // 0x80092B98: lb          $a1, 0x0($t2)
    ctx->r5 = MEM_B(ctx->r10, 0X0);
    // 0x80092B9C: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x80092BA0: slt         $at, $a0, $a1
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x80092BA4: bne         $at, $zero, L_80092BEC
    if (ctx->r1 != 0) {
        // 0x80092BA8: negu        $a2, $a1
        ctx->r6 = SUB32(0, ctx->r5);
            goto L_80092BEC;
    }
    // 0x80092BA8: negu        $a2, $a1
    ctx->r6 = SUB32(0, ctx->r5);
    // 0x80092BAC: lb          $t8, 0x12($v1)
    ctx->r24 = MEM_B(ctx->r3, 0X12);
    // 0x80092BB0: slt         $at, $t8, $a1
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x80092BB4: beql        $at, $zero, L_80092BD4
    if (ctx->r1 == 0) {
        // 0x80092BB8: lhu         $t7, 0x0($v1)
        ctx->r15 = MEM_HU(ctx->r3, 0X0);
            goto L_80092BD4;
    }
    goto skip_6;
    // 0x80092BB8: lhu         $t7, 0x0($v1)
    ctx->r15 = MEM_HU(ctx->r3, 0X0);
    skip_6:
    // 0x80092BBC: lhu         $t6, 0x2($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X2);
    // 0x80092BC0: sw          $zero, 0x14($v1)
    MEM_W(0X14, ctx->r3) = 0;
    // 0x80092BC4: ori         $t9, $t6, 0x100
    ctx->r25 = ctx->r14 | 0X100;
    // 0x80092BC8: b           L_80092C34
    // 0x80092BCC: sh          $t9, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r25;
        goto L_80092C34;
    // 0x80092BCC: sh          $t9, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r25;
    // 0x80092BD0: lhu         $t7, 0x0($v1)
    ctx->r15 = MEM_HU(ctx->r3, 0X0);
L_80092BD4:
    // 0x80092BD4: lw          $t6, 0x14($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X14);
    // 0x80092BD8: ori         $t8, $t7, 0x100
    ctx->r24 = ctx->r15 | 0X100;
    // 0x80092BDC: addiu       $t9, $t6, 0x1
    ctx->r25 = ADD32(ctx->r14, 0X1);
    // 0x80092BE0: sh          $t8, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r24;
    // 0x80092BE4: b           L_80092C34
    // 0x80092BE8: sw          $t9, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r25;
        goto L_80092C34;
    // 0x80092BE8: sw          $t9, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r25;
L_80092BEC:
    // 0x80092BEC: slt         $at, $a2, $a0
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x80092BF0: bnel        $at, $zero, L_80092C38
    if (ctx->r1 != 0) {
        // 0x80092BF4: lb          $a0, 0x9($v1)
        ctx->r4 = MEM_B(ctx->r3, 0X9);
            goto L_80092C38;
    }
    goto skip_7;
    // 0x80092BF4: lb          $a0, 0x9($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X9);
    skip_7:
    // 0x80092BF8: lb          $t7, 0x12($v1)
    ctx->r15 = MEM_B(ctx->r3, 0X12);
    // 0x80092BFC: slt         $at, $a2, $t7
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x80092C00: beql        $at, $zero, L_80092C20
    if (ctx->r1 == 0) {
        // 0x80092C04: lhu         $t9, 0x0($v1)
        ctx->r25 = MEM_HU(ctx->r3, 0X0);
            goto L_80092C20;
    }
    goto skip_8;
    // 0x80092C04: lhu         $t9, 0x0($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X0);
    skip_8:
    // 0x80092C08: lhu         $t8, 0x2($v1)
    ctx->r24 = MEM_HU(ctx->r3, 0X2);
    // 0x80092C0C: sw          $zero, 0x14($v1)
    MEM_W(0X14, ctx->r3) = 0;
    // 0x80092C10: ori         $t6, $t8, 0x200
    ctx->r14 = ctx->r24 | 0X200;
    // 0x80092C14: b           L_80092C34
    // 0x80092C18: sh          $t6, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r14;
        goto L_80092C34;
    // 0x80092C18: sh          $t6, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r14;
    // 0x80092C1C: lhu         $t9, 0x0($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X0);
L_80092C20:
    // 0x80092C20: lw          $t8, 0x14($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X14);
    // 0x80092C24: ori         $t7, $t9, 0x200
    ctx->r15 = ctx->r25 | 0X200;
    // 0x80092C28: addiu       $t6, $t8, 0x1
    ctx->r14 = ADD32(ctx->r24, 0X1);
    // 0x80092C2C: sh          $t7, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r15;
    // 0x80092C30: sw          $t6, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r14;
L_80092C34:
    // 0x80092C34: lb          $a0, 0x9($v1)
    ctx->r4 = MEM_B(ctx->r3, 0X9);
L_80092C38:
    // 0x80092C38: lb          $a1, 0x0($t3)
    ctx->r5 = MEM_B(ctx->r11, 0X0);
    // 0x80092C3C: slt         $at, $a0, $a1
    ctx->r1 = SIGNED(ctx->r4) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x80092C40: bne         $at, $zero, L_80092C88
    if (ctx->r1 != 0) {
        // 0x80092C44: negu        $a2, $a1
        ctx->r6 = SUB32(0, ctx->r5);
            goto L_80092C88;
    }
    // 0x80092C44: negu        $a2, $a1
    ctx->r6 = SUB32(0, ctx->r5);
    // 0x80092C48: lb          $t9, 0x13($v1)
    ctx->r25 = MEM_B(ctx->r3, 0X13);
    // 0x80092C4C: slt         $at, $t9, $a1
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r5) ? 1 : 0;
    // 0x80092C50: beql        $at, $zero, L_80092C70
    if (ctx->r1 == 0) {
        // 0x80092C54: lhu         $t6, 0x0($v1)
        ctx->r14 = MEM_HU(ctx->r3, 0X0);
            goto L_80092C70;
    }
    goto skip_9;
    // 0x80092C54: lhu         $t6, 0x0($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X0);
    skip_9:
    // 0x80092C58: lhu         $t7, 0x2($v1)
    ctx->r15 = MEM_HU(ctx->r3, 0X2);
    // 0x80092C5C: sw          $zero, 0x18($v1)
    MEM_W(0X18, ctx->r3) = 0;
    // 0x80092C60: ori         $t8, $t7, 0x800
    ctx->r24 = ctx->r15 | 0X800;
    // 0x80092C64: b           L_80092CD0
    // 0x80092C68: sh          $t8, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r24;
        goto L_80092CD0;
    // 0x80092C68: sh          $t8, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r24;
    // 0x80092C6C: lhu         $t6, 0x0($v1)
    ctx->r14 = MEM_HU(ctx->r3, 0X0);
L_80092C70:
    // 0x80092C70: lw          $t7, 0x18($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X18);
    // 0x80092C74: ori         $t9, $t6, 0x800
    ctx->r25 = ctx->r14 | 0X800;
    // 0x80092C78: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x80092C7C: sh          $t9, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r25;
    // 0x80092C80: b           L_80092CD0
    // 0x80092C84: sw          $t8, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r24;
        goto L_80092CD0;
    // 0x80092C84: sw          $t8, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r24;
L_80092C88:
    // 0x80092C88: slt         $at, $a2, $a0
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x80092C8C: bne         $at, $zero, L_80092CD0
    if (ctx->r1 != 0) {
        // 0x80092C90: nop
    
            goto L_80092CD0;
    }
    // 0x80092C90: nop

    // 0x80092C94: lb          $t6, 0x13($v1)
    ctx->r14 = MEM_B(ctx->r3, 0X13);
    // 0x80092C98: slt         $at, $a2, $t6
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x80092C9C: beql        $at, $zero, L_80092CBC
    if (ctx->r1 == 0) {
        // 0x80092CA0: lhu         $t8, 0x0($v1)
        ctx->r24 = MEM_HU(ctx->r3, 0X0);
            goto L_80092CBC;
    }
    goto skip_10;
    // 0x80092CA0: lhu         $t8, 0x0($v1)
    ctx->r24 = MEM_HU(ctx->r3, 0X0);
    skip_10:
    // 0x80092CA4: lhu         $t9, 0x2($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X2);
    // 0x80092CA8: sw          $zero, 0x18($v1)
    MEM_W(0X18, ctx->r3) = 0;
    // 0x80092CAC: ori         $t7, $t9, 0x400
    ctx->r15 = ctx->r25 | 0X400;
    // 0x80092CB0: b           L_80092CD0
    // 0x80092CB4: sh          $t7, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r15;
        goto L_80092CD0;
    // 0x80092CB4: sh          $t7, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r15;
    // 0x80092CB8: lhu         $t8, 0x0($v1)
    ctx->r24 = MEM_HU(ctx->r3, 0X0);
L_80092CBC:
    // 0x80092CBC: lw          $t9, 0x18($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X18);
    // 0x80092CC0: ori         $t6, $t8, 0x400
    ctx->r14 = ctx->r24 | 0X400;
    // 0x80092CC4: addiu       $t7, $t9, 0x1
    ctx->r15 = ADD32(ctx->r25, 0X1);
    // 0x80092CC8: sh          $t6, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r14;
    // 0x80092CCC: sw          $t7, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r15;
L_80092CD0:
    // 0x80092CD0: bne         $v0, $t4, L_8009299C
    if (ctx->r2 != ctx->r12) {
        // 0x80092CD4: addiu       $v1, $v1, 0x1C
        ctx->r3 = ADD32(ctx->r3, 0X1C);
            goto L_8009299C;
    }
    // 0x80092CD4: addiu       $v1, $v1, 0x1C
    ctx->r3 = ADD32(ctx->r3, 0X1C);
    // 0x80092CD8: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x80092CDC: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x80092CE0: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x80092CE4: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x80092CE8: jr          $ra
    // 0x80092CEC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x80092CEC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_80092CF0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80092CF0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80092CF4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80092CF8: sh          $zero, -0x19D2($at)
    MEM_H(-0X19D2, ctx->r1) = 0;
    // 0x80092CFC: addiu       $v1, $v1, -0x19D6
    ctx->r3 = ADD32(ctx->r3, -0X19D6);
    // 0x80092D00: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80092D04: sh          $v0, 0x0($v1)
    MEM_H(0X0, ctx->r3) = ctx->r2;
    // 0x80092D08: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x80092D0C: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80092D10: sh          $zero, -0x75CA($at)
    MEM_H(-0X75CA, ctx->r1) = 0;
    // 0x80092D14: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80092D18: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x80092D1C: lui         $t6, 0xBC00
    ctx->r14 = S32(0XBC00 << 16);
    // 0x80092D20: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80092D24: sw          $zero, -0x75C0($at)
    MEM_W(-0X75C0, ctx->r1) = 0;
    // 0x80092D28: ori         $t6, $t6, 0x1406
    ctx->r14 = ctx->r14 | 0X1406;
    // 0x80092D2C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80092D30: addiu       $s0, $a0, 0x8
    ctx->r16 = ADD32(ctx->r4, 0X8);
    // 0x80092D34: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80092D38: lui         $a0, 0x801B
    ctx->r4 = S32(0X801B << 16);
    // 0x80092D3C: lw          $a0, -0x16B8($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X16B8);
    // 0x80092D40: jal         0x800C5720
    // 0x80092D44: sw          $a1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r5;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x80092D44: sw          $a1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r5;
    after_0:
    // 0x80092D48: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x80092D4C: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80092D50: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80092D54: sw          $v0, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r2;
    // 0x80092D58: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x80092D5C: addiu       $v1, $v1, -0x19D6
    ctx->r3 = ADD32(ctx->r3, -0X19D6);
    // 0x80092D60: sltiu       $at, $t7, 0x68
    ctx->r1 = ctx->r15 < 0X68 ? 1 : 0;
    // 0x80092D64: beq         $at, $zero, L_80093004
    if (ctx->r1 == 0) {
        // 0x80092D68: sll         $t7, $t7, 2
        ctx->r15 = S32(ctx->r15 << 2);
            goto L_80093004;
    }
    // 0x80092D68: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x80092D6C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80092D70: addu        $at, $at, $t7
    gpr jr_addend_80092D78 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x80092D74: lw          $t7, -0x5058($at)
    ctx->r15 = ADD32(ctx->r1, -0X5058);
    // 0x80092D78: jr          $t7
    // 0x80092D7C: nop

    switch (jr_addend_80092D78 >> 2) {
        case 0: goto L_80092D80; break;
        case 1: goto L_80093004; break;
        case 2: goto L_80092DD0; break;
        case 3: goto L_80092DE4; break;
        case 4: goto L_80092E0C; break;
        case 5: goto L_80092DBC; break;
        case 6: goto L_80092DBC; break;
        case 7: goto L_80092DF8; break;
        case 8: goto L_80092DF8; break;
        case 9: goto L_80093004; break;
        case 10: goto L_80092EC8; break;
        case 11: goto L_80092EC8; break;
        case 12: goto L_80093004; break;
        case 13: goto L_80093004; break;
        case 14: goto L_80093004; break;
        case 15: goto L_80093004; break;
        case 16: goto L_80093004; break;
        case 17: goto L_80093004; break;
        case 18: goto L_80093004; break;
        case 19: goto L_80093004; break;
        case 20: goto L_80092EDC; break;
        case 21: goto L_80092EDC; break;
        case 22: goto L_80093004; break;
        case 23: goto L_80093004; break;
        case 24: goto L_80093004; break;
        case 25: goto L_80093004; break;
        case 26: goto L_80093004; break;
        case 27: goto L_80093004; break;
        case 28: goto L_80093004; break;
        case 29: goto L_80093004; break;
        case 30: goto L_80092EF0; break;
        case 31: goto L_80092EF0; break;
        case 32: goto L_80093004; break;
        case 33: goto L_80093004; break;
        case 34: goto L_80093004; break;
        case 35: goto L_80093004; break;
        case 36: goto L_80093004; break;
        case 37: goto L_80093004; break;
        case 38: goto L_80093004; break;
        case 39: goto L_80093004; break;
        case 40: goto L_80092E20; break;
        case 41: goto L_80092E64; break;
        case 42: goto L_80092E64; break;
        case 43: goto L_80092E64; break;
        case 44: goto L_80092E64; break;
        case 45: goto L_80092E78; break;
        case 46: goto L_80093004; break;
        case 47: goto L_80093004; break;
        case 48: goto L_80093004; break;
        case 49: goto L_80093004; break;
        case 50: goto L_80092EA0; break;
        case 51: goto L_80092EA0; break;
        case 52: goto L_80092F04; break;
        case 53: goto L_80092F04; break;
        case 54: goto L_80092E8C; break;
        case 55: goto L_80092E8C; break;
        case 56: goto L_80092FE0; break;
        case 57: goto L_80092FF4; break;
        case 58: goto L_80093004; break;
        case 59: goto L_80093004; break;
        case 60: goto L_80092F18; break;
        case 61: goto L_80092F18; break;
        case 62: goto L_80092F2C; break;
        case 63: goto L_80092F2C; break;
        case 64: goto L_80092F90; break;
        case 65: goto L_80092F90; break;
        case 66: goto L_80092F40; break;
        case 67: goto L_80092F40; break;
        case 68: goto L_80092F54; break;
        case 69: goto L_80092F54; break;
        case 70: goto L_80092F7C; break;
        case 71: goto L_80092F7C; break;
        case 72: goto L_80092F68; break;
        case 73: goto L_80092F68; break;
        case 74: goto L_80093004; break;
        case 75: goto L_80093004; break;
        case 76: goto L_80093004; break;
        case 77: goto L_80093004; break;
        case 78: goto L_80093004; break;
        case 79: goto L_80093004; break;
        case 80: goto L_80092EB4; break;
        case 81: goto L_80092EB4; break;
        case 82: goto L_80093004; break;
        case 83: goto L_80093004; break;
        case 84: goto L_80093004; break;
        case 85: goto L_80093004; break;
        case 86: goto L_80093004; break;
        case 87: goto L_80093004; break;
        case 88: goto L_80093004; break;
        case 89: goto L_80093004; break;
        case 90: goto L_80092FA4; break;
        case 91: goto L_80092FA4; break;
        case 92: goto L_80093004; break;
        case 93: goto L_80093004; break;
        case 94: goto L_80093004; break;
        case 95: goto L_80093004; break;
        case 96: goto L_80093004; break;
        case 97: goto L_80093004; break;
        case 98: goto L_80093004; break;
        case 99: goto L_80093004; break;
        case 100: goto L_80092FB8; break;
        case 101: goto L_80092FB8; break;
        case 102: goto L_80092FCC; break;
        case 103: goto L_80092FCC; break;
        default: switch_error(__func__, 0x80092D78, 0x800EAFA8);
    }
    // 0x80092D7C: nop

L_80092D80:
    // 0x80092D80: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092D84: jal         0x80093F78
    // 0x80092D88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_80093F78(rdram, ctx);
        goto after_1;
    // 0x80092D88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x80092D8C: jal         0x80093104
    // 0x80092D90: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    func_80093104(rdram, ctx);
        goto after_2;
    // 0x80092D90: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    after_2:
    // 0x80092D94: beq         $v0, $zero, L_80092DAC
    if (ctx->r2 == 0) {
        // 0x80092D98: nop
    
            goto L_80092DAC;
    }
    // 0x80092D98: nop

    // 0x80092D9C: jal         0x801ECAF4
    // 0x80092DA0: nop

    func_801ECAF4(rdram, ctx);
        goto after_3;
    // 0x80092DA0: nop

    after_3:
    // 0x80092DA4: b           L_80093004
    // 0x80092DA8: nop

        goto L_80093004;
    // 0x80092DA8: nop

L_80092DAC:
    // 0x80092DAC: jal         0x801EB180
    // 0x80092DB0: nop

    func_801EB180(rdram, ctx);
        goto after_4;
    // 0x80092DB0: nop

    after_4:
    // 0x80092DB4: b           L_80093004
    // 0x80092DB8: nop

        goto L_80093004;
    // 0x80092DB8: nop

L_80092DBC:
    // 0x80092DBC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092DC0: jal         0x802C5BA4
    // 0x80092DC4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_1B1FB0_802C5BA4(rdram, ctx);
        goto after_5;
    // 0x80092DC4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_5:
    // 0x80092DC8: b           L_80093004
    // 0x80092DCC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092DCC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092DD0:
    // 0x80092DD0: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092DD4: jal         0x802C5800
    // 0x80092DD8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_6;
    // 0x80092DD8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_6:
    // 0x80092DDC: b           L_80093004
    // 0x80092DE0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092DE0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092DE4:
    // 0x80092DE4: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092DE8: jal         0x802C5A7C
    // 0x80092DEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i0_802C5A7C(rdram, ctx);
        goto after_7;
    // 0x80092DEC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_7:
    // 0x80092DF0: b           L_80093004
    // 0x80092DF4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092DF4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092DF8:
    // 0x80092DF8: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092DFC: jal         0x802C913C
    // 0x80092E00: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_802C913C(rdram, ctx);
        goto after_8;
    // 0x80092E00: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_8:
    // 0x80092E04: b           L_80093004
    // 0x80092E08: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E08: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092E0C:
    // 0x80092E0C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092E10: jal         0x802C6944
    // 0x80092E14: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i0_802C6944(rdram, ctx);
        goto after_9;
    // 0x80092E14: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_9:
    // 0x80092E18: b           L_80093004
    // 0x80092E1C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E1C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092E20:
    // 0x80092E20: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80092E24: lw          $v0, -0x19F8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X19F8);
    // 0x80092E28: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80092E2C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x80092E30: beq         $v0, $at, L_80092E40
    if (ctx->r2 == ctx->r1) {
        // 0x80092E34: addiu       $at, $zero, 0x1
        ctx->r1 = ADD32(0, 0X1);
            goto L_80092E40;
    }
    // 0x80092E34: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80092E38: bne         $v0, $at, L_80092E54
    if (ctx->r2 != ctx->r1) {
        // 0x80092E3C: nop
    
            goto L_80092E54;
    }
    // 0x80092E3C: nop

L_80092E40:
    // 0x80092E40: lw          $t8, -0x19B0($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X19B0);
    // 0x80092E44: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80092E48: beq         $t8, $at, L_80092E54
    if (ctx->r24 == ctx->r1) {
        // 0x80092E4C: nop
    
            goto L_80092E54;
    }
    // 0x80092E4C: nop

    // 0x80092E50: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
L_80092E54:
    // 0x80092E54: jal         0x802C5AE4
    // 0x80092E58: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5AE4)(rdram, ctx);
        goto after_10;
    // 0x80092E58: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_10:
    // 0x80092E5C: b           L_80093004
    // 0x80092E60: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E60: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092E64:
    // 0x80092E64: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092E68: jal         0x802C5AE4
    // 0x80092E6C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5AE4)(rdram, ctx);
        goto after_11;
    // 0x80092E6C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_11:
    // 0x80092E70: b           L_80093004
    // 0x80092E74: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E74: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092E78:
    // 0x80092E78: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092E7C: jal         0x802C7D00
    // 0x80092E80: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i1_802C7D00(rdram, ctx);
        goto after_12;
    // 0x80092E80: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_12:
    // 0x80092E84: b           L_80093004
    // 0x80092E88: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E88: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092E8C:
    // 0x80092E8C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092E90: jal         0x802C5800
    // 0x80092E94: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_13;
    // 0x80092E94: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_13:
    // 0x80092E98: b           L_80093004
    // 0x80092E9C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092E9C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092EA0:
    // 0x80092EA0: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092EA4: jal         0x802C5B74
    // 0x80092EA8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i6_802C5B74(rdram, ctx);
        goto after_14;
    // 0x80092EA8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_14:
    // 0x80092EAC: b           L_80093004
    // 0x80092EB0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092EB0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092EB4:
    // 0x80092EB4: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092EB8: jal         0x802C5924
    // 0x80092EBC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i14_802C5924(rdram, ctx);
        goto after_15;
    // 0x80092EBC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_15:
    // 0x80092EC0: b           L_80093004
    // 0x80092EC4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092EC4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092EC8:
    // 0x80092EC8: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092ECC: jal         0x802C5B4C
    // 0x80092ED0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i2_802C5B4C(rdram, ctx);
        goto after_16;
    // 0x80092ED0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_16:
    // 0x80092ED4: b           L_80093004
    // 0x80092ED8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092ED8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092EDC:
    // 0x80092EDC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092EE0: jal         0x802C5B78
    // 0x80092EE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i4_802C5B78(rdram, ctx);
        goto after_17;
    // 0x80092EE4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_17:
    // 0x80092EE8: b           L_80093004
    // 0x80092EEC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092EEC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092EF0:
    // 0x80092EF0: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092EF4: jal         0x802C5B40
    // 0x80092EF8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i3_802C5B40(rdram, ctx);
        goto after_18;
    // 0x80092EF8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_18:
    // 0x80092EFC: b           L_80093004
    // 0x80092F00: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F00: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F04:
    // 0x80092F04: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F08: jal         0x802C5C1C
    // 0x80092F0C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i5_802C5C1C(rdram, ctx);
        goto after_19;
    // 0x80092F0C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_19:
    // 0x80092F10: b           L_80093004
    // 0x80092F14: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F14: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F18:
    // 0x80092F18: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F1C: jal         0x802C5800
    // 0x80092F20: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_20;
    // 0x80092F20: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_20:
    // 0x80092F24: b           L_80093004
    // 0x80092F28: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F28: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F2C:
    // 0x80092F2C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F30: jal         0x802C5D3C
    // 0x80092F34: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i8_802C5D3C(rdram, ctx);
        goto after_21;
    // 0x80092F34: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_21:
    // 0x80092F38: b           L_80093004
    // 0x80092F3C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F3C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F40:
    // 0x80092F40: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F44: jal         0x802C5D24
    // 0x80092F48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i9_802C5D24(rdram, ctx);
        goto after_22;
    // 0x80092F48: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_22:
    // 0x80092F4C: b           L_80093004
    // 0x80092F50: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F50: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F54:
    // 0x80092F54: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F58: jal         0x802C5968
    // 0x80092F5C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i10_802C5968(rdram, ctx);
        goto after_23;
    // 0x80092F5C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_23:
    // 0x80092F60: b           L_80093004
    // 0x80092F64: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F64: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F68:
    // 0x80092F68: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F6C: jal         0x802C5800
    // 0x80092F70: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_24;
    // 0x80092F70: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_24:
    // 0x80092F74: b           L_80093004
    // 0x80092F78: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F78: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F7C:
    // 0x80092F7C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F80: jal         0x802C5800
    // 0x80092F84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5800)(rdram, ctx);
        goto after_25;
    // 0x80092F84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_25:
    // 0x80092F88: b           L_80093004
    // 0x80092F8C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092F8C: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092F90:
    // 0x80092F90: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092F94: jal         0x802C5F6C
    // 0x80092F98: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    LOOKUP_FUNC(0x802C5F6C)(rdram, ctx);
        goto after_26;
    // 0x80092F98: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_26:
    // 0x80092F9C: b           L_80093004
    // 0x80092FA0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092FA0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092FA4:
    // 0x80092FA4: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092FA8: jal         0x802C7484
    // 0x80092FAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i5_802C7484(rdram, ctx);
        goto after_27;
    // 0x80092FAC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_27:
    // 0x80092FB0: b           L_80093004
    // 0x80092FB4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092FB4: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092FB8:
    // 0x80092FB8: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092FBC: jal         0x801E1E8C
    // 0x80092FC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_801E1E8C(rdram, ctx);
        goto after_28;
    // 0x80092FC0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_28:
    // 0x80092FC4: b           L_80093004
    // 0x80092FC8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092FC8: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092FCC:
    // 0x80092FCC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092FD0: jal         0x802C5F50
    // 0x80092FD4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_i15_802C5F50(rdram, ctx);
        goto after_29;
    // 0x80092FD4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_29:
    // 0x80092FD8: b           L_80093004
    // 0x80092FDC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092FDC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092FE0:
    // 0x80092FE0: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092FE4: jal         0x802C583C
    // 0x80092FE8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_1C3780_802C583C(rdram, ctx);
        goto after_30;
    // 0x80092FE8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_30:
    // 0x80092FEC: b           L_80093004
    // 0x80092FF0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
        goto L_80093004;
    // 0x80092FF0: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80092FF4:
    // 0x80092FF4: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    // 0x80092FF8: jal         0x801E34F8
    // 0x80092FFC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_801E34F8(rdram, ctx);
        goto after_31;
    // 0x80092FFC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_31:
    // 0x80093000: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80093004:
    // 0x80093004: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80093008: lhu         $t9, -0x1970($t9)
    ctx->r25 = MEM_HU(ctx->r25, -0X1970);
    // 0x8009300C: ori         $at, $zero, 0xF000
    ctx->r1 = 0 | 0XF000;
    // 0x80093010: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80093014: andi        $t0, $t9, 0xF000
    ctx->r8 = ctx->r25 & 0XF000;
    // 0x80093018: bne         $t0, $at, L_80093030
    if (ctx->r8 != ctx->r1) {
        // 0x8009301C: lui         $t2, 0x800E
        ctx->r10 = S32(0X800E << 16);
            goto L_80093030;
    }
    // 0x8009301C: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80093020: lh          $t1, -0x19DC($t1)
    ctx->r9 = MEM_H(ctx->r9, -0X19DC);
    // 0x80093024: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80093028: beq         $t1, $at, L_80093048
    if (ctx->r9 == ctx->r1) {
        // 0x8009302C: nop
    
            goto L_80093048;
    }
    // 0x8009302C: nop

L_80093030:
    // 0x80093030: lh          $t2, -0x5488($t2)
    ctx->r10 = MEM_H(ctx->r10, -0X5488);
    // 0x80093034: bne         $t2, $zero, L_80093048
    if (ctx->r10 != 0) {
        // 0x80093038: nop
    
            goto L_80093048;
    }
    // 0x80093038: nop

    // 0x8009303C: jal         0x801E4440
    // 0x80093040: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_801E4440(rdram, ctx);
        goto after_32;
    // 0x80093040: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_32:
    // 0x80093044: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
L_80093048:
    // 0x80093048: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x8009304C: addiu       $v1, $v1, -0x548C
    ctx->r3 = ADD32(ctx->r3, -0X548C);
    // 0x80093050: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x80093054: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80093058: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009305C: beql        $v0, $a1, L_8009307C
    if (ctx->r2 == ctx->r5) {
        // 0x80093060: sh          $zero, 0x0($v1)
        MEM_H(0X0, ctx->r3) = 0;
            goto L_8009307C;
    }
    goto skip_0;
    // 0x80093060: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    skip_0:
    // 0x80093064: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80093068: beql        $v0, $at, L_80093090
    if (ctx->r2 == ctx->r1) {
        // 0x8009306C: sh          $zero, 0x0($v1)
        MEM_H(0X0, ctx->r3) = 0;
            goto L_80093090;
    }
    goto skip_1;
    // 0x8009306C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    skip_1:
    // 0x80093070: b           L_800930A0
    // 0x80093074: nop

        goto L_800930A0;
    // 0x80093074: nop

    // 0x80093078: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
L_8009307C:
    // 0x8009307C: jal         0x801E4C08
    // 0x80093080: sh          $a1, -0x5488($at)
    MEM_H(-0X5488, ctx->r1) = ctx->r5;
    func_801E4C08(rdram, ctx);
        goto after_33;
    // 0x80093080: sh          $a1, -0x5488($at)
    MEM_H(-0X5488, ctx->r1) = ctx->r5;
    after_33:
    // 0x80093084: b           L_800930A0
    // 0x80093088: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
        goto L_800930A0;
    // 0x80093088: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009308C: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
L_80093090:
    // 0x80093090: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093094: jal         0x801E4C38
    // 0x80093098: sh          $zero, -0x5488($at)
    MEM_H(-0X5488, ctx->r1) = 0;
    func_801E4C38(rdram, ctx);
        goto after_34;
    // 0x80093098: sh          $zero, -0x5488($at)
    MEM_H(-0X5488, ctx->r1) = 0;
    after_34:
    // 0x8009309C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_800930A0:
    // 0x800930A0: lui         $at, 0x8023
    ctx->r1 = S32(0X8023 << 16);
    // 0x800930A4: sh          $a1, -0x75CA($at)
    MEM_H(-0X75CA, ctx->r1) = ctx->r5;
    // 0x800930A8: jal         0x801E7908
    // 0x800930AC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_801E7908(rdram, ctx);
        goto after_35;
    // 0x800930AC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_35:
    // 0x800930B0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800930B4: addiu       $v1, $v1, -0x19D2
    ctx->r3 = ADD32(ctx->r3, -0X19D2);
    // 0x800930B8: lh          $t3, 0x0($v1)
    ctx->r11 = MEM_H(ctx->r3, 0X0);
    // 0x800930BC: or          $s0, $v0, $zero
    ctx->r16 = ctx->r2 | 0;
    // 0x800930C0: beq         $t3, $zero, L_800930D0
    if (ctx->r11 == 0) {
        // 0x800930C4: nop
    
            goto L_800930D0;
    }
    // 0x800930C4: nop

    // 0x800930C8: jal         0x801EB180
    // 0x800930CC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    func_801EB180(rdram, ctx);
        goto after_36;
    // 0x800930CC: sh          $zero, 0x0($v1)
    MEM_H(0X0, ctx->r3) = 0;
    after_36:
L_800930D0:
    // 0x800930D0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800930D4: addiu       $v0, $v0, -0x1A04
    ctx->r2 = ADD32(ctx->r2, -0X1A04);
    // 0x800930D8: lw          $t4, 0x0($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X0);
    // 0x800930DC: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x800930E0: slti        $at, $t5, 0x7530
    ctx->r1 = SIGNED(ctx->r13) < 0X7530 ? 1 : 0;
    // 0x800930E4: bne         $at, $zero, L_800930F0
    if (ctx->r1 != 0) {
        // 0x800930E8: sw          $t5, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r13;
            goto L_800930F0;
    }
    // 0x800930E8: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x800930EC: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
L_800930F0:
    // 0x800930F0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x800930F4: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x800930F8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800930FC: jr          $ra
    // 0x80093100: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x80093100: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_80093104(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80093104: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x80093108: lui         $t6, 0x8015
    ctx->r14 = S32(0X8015 << 16);
    // 0x8009310C: lbu         $t6, 0x4340($t6)
    ctx->r14 = MEM_BU(ctx->r14, 0X4340);
    // 0x80093110: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x80093114: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x80093118: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8009311C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80093120: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80093124: bne         $t6, $zero, L_80093134
    if (ctx->r14 != 0) {
        // 0x80093128: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_80093134;
    }
    // 0x80093128: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x8009312C: b           L_8009326C
    // 0x80093130: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x80093130: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80093134:
    // 0x80093134: lui         $t7, 0x8015
    ctx->r15 = S32(0X8015 << 16);
    // 0x80093138: lw          $v0, 0x4330($t7)
    ctx->r2 = MEM_W(ctx->r15, 0X4330);
    // 0x8009313C: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x80093140: addiu       $s0, $s0, -0x4BFC
    ctx->r16 = ADD32(ctx->r16, -0X4BFC);
    // 0x80093144: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x80093148: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x8009314C: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x80093150: sw          $v0, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r2;
    // 0x80093154: lbu         $t9, 0x42E2($t9)
    ctx->r25 = MEM_BU(ctx->r25, 0X42E2);
    // 0x80093158: sll         $t1, $v0, 2
    ctx->r9 = S32(ctx->r2 << 2);
    // 0x8009315C: addu        $t1, $t1, $v0
    ctx->r9 = ADD32(ctx->r9, ctx->r2);
    // 0x80093160: andi        $t0, $t9, 0x1
    ctx->r8 = ctx->r25 & 0X1;
    // 0x80093164: bne         $t0, $zero, L_80093174
    if (ctx->r8 != 0) {
        // 0x80093168: sll         $t1, $t1, 1
        ctx->r9 = S32(ctx->r9 << 1);
            goto L_80093174;
    }
    // 0x80093168: sll         $t1, $t1, 1
    ctx->r9 = S32(ctx->r9 << 1);
    // 0x8009316C: b           L_8009326C
    // 0x80093170: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x80093170: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80093174:
    // 0x80093174: lui         $t2, 0x8015
    ctx->r10 = S32(0X8015 << 16);
    // 0x80093178: addu        $t2, $t2, $t1
    ctx->r10 = ADD32(ctx->r10, ctx->r9);
    // 0x8009317C: lhu         $t2, 0x4308($t2)
    ctx->r10 = MEM_HU(ctx->r10, 0X4308);
    // 0x80093180: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x80093184: addiu       $s1, $s1, 0x40D0
    ctx->r17 = ADD32(ctx->r17, 0X40D0);
    // 0x80093188: andi        $t3, $t2, 0x1000
    ctx->r11 = ctx->r10 & 0X1000;
    // 0x8009318C: bne         $t3, $zero, L_8009319C
    if (ctx->r11 != 0) {
        // 0x80093190: or          $a0, $s1, $zero
        ctx->r4 = ctx->r17 | 0;
            goto L_8009319C;
    }
    // 0x80093190: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x80093194: b           L_8009326C
    // 0x80093198: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x80093198: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8009319C:
    // 0x8009319C: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800931A0: jal         0x800C85C0
    // 0x800931A4: addiu       $a1, $a1, -0x4940
    ctx->r5 = ADD32(ctx->r5, -0X4940);
    osPfsIsPlug_recomp(rdram, ctx);
        goto after_0;
    // 0x800931A4: addiu       $a1, $a1, -0x4940
    ctx->r5 = ADD32(ctx->r5, -0X4940);
    after_0:
    // 0x800931A8: beq         $v0, $zero, L_800931B8
    if (ctx->r2 == 0) {
        // 0x800931AC: lui         $s4, 0x801D
        ctx->r20 = S32(0X801D << 16);
            goto L_800931B8;
    }
    // 0x800931AC: lui         $s4, 0x801D
    ctx->r20 = S32(0X801D << 16);
    // 0x800931B0: b           L_8009326C
    // 0x800931B4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x800931B4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800931B8:
    // 0x800931B8: addiu       $s4, $s4, -0x49A8
    ctx->r20 = ADD32(ctx->r20, -0X49A8);
    // 0x800931BC: or          $a1, $s4, $zero
    ctx->r5 = ctx->r20 | 0;
    // 0x800931C0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x800931C4: jal         0x800C88F0
    // 0x800931C8: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    osPfsInit_recomp(rdram, ctx);
        goto after_1;
    // 0x800931C8: lw          $a2, 0x0($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X0);
    after_1:
    // 0x800931CC: beq         $v0, $zero, L_800931DC
    if (ctx->r2 == 0) {
        // 0x800931D0: or          $a0, $s4, $zero
        ctx->r4 = ctx->r20 | 0;
            goto L_800931DC;
    }
    // 0x800931D0: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x800931D4: b           L_8009326C
    // 0x800931D8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x800931D8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800931DC:
    // 0x800931DC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800931E0: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x800931E4: addiu       $a2, $a2, -0x4BF8
    ctx->r6 = ADD32(ctx->r6, -0X4BF8);
    // 0x800931E8: jal         0x800C9E30
    // 0x800931EC: addiu       $a1, $a1, -0x4BF4
    ctx->r5 = ADD32(ctx->r5, -0X4BF4);
    osPfsNumFiles_recomp(rdram, ctx);
        goto after_2;
    // 0x800931EC: addiu       $a1, $a1, -0x4BF4
    ctx->r5 = ADD32(ctx->r5, -0X4BF4);
    after_2:
    // 0x800931F0: beq         $v0, $zero, L_80093200
    if (ctx->r2 == 0) {
        // 0x800931F4: or          $s0, $zero, $zero
        ctx->r16 = 0 | 0;
            goto L_80093200;
    }
    // 0x800931F4: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x800931F8: b           L_8009326C
    // 0x800931FC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x800931FC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80093200:
    // 0x80093200: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80093204: lui         $s2, 0x801D
    ctx->r18 = S32(0X801D << 16);
    // 0x80093208: addiu       $s2, $s2, -0x4BE8
    ctx->r18 = ADD32(ctx->r18, -0X4BE8);
    // 0x8009320C: addiu       $s1, $s1, -0x49E8
    ctx->r17 = ADD32(ctx->r17, -0X49E8);
    // 0x80093210: addiu       $s3, $zero, 0x10
    ctx->r19 = ADD32(0, 0X10);
L_80093214:
    // 0x80093214: sll         $t4, $s0, 5
    ctx->r12 = S32(ctx->r16 << 5);
    // 0x80093218: addu        $a2, $s2, $t4
    ctx->r6 = ADD32(ctx->r18, ctx->r12);
    // 0x8009321C: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    // 0x80093220: jal         0x800C9F60
    // 0x80093224: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    osPfsFileState_recomp(rdram, ctx);
        goto after_3;
    // 0x80093224: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_3:
    // 0x80093228: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    // 0x8009322C: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x80093230: bne         $s0, $s3, L_80093214
    if (ctx->r16 != ctx->r19) {
        // 0x80093234: sw          $v0, -0x4($s1)
        MEM_W(-0X4, ctx->r17) = ctx->r2;
            goto L_80093214;
    }
    // 0x80093234: sw          $v0, -0x4($s1)
    MEM_W(-0X4, ctx->r17) = ctx->r2;
    // 0x80093238: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x8009323C: addiu       $s0, $s0, -0x4BF0
    ctx->r16 = ADD32(ctx->r16, -0X4BF0);
    // 0x80093240: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80093244: jal         0x800C8C10
    // 0x80093248: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    osPfsFreeBlocks_recomp(rdram, ctx);
        goto after_4;
    // 0x80093248: or          $a0, $s4, $zero
    ctx->r4 = ctx->r20 | 0;
    after_4:
    // 0x8009324C: beql        $v0, $zero, L_80093260
    if (ctx->r2 == 0) {
        // 0x80093250: lw          $t5, 0x0($s0)
        ctx->r13 = MEM_W(ctx->r16, 0X0);
            goto L_80093260;
    }
    goto skip_0;
    // 0x80093250: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
    skip_0:
    // 0x80093254: b           L_8009326C
    // 0x80093258: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_8009326C;
    // 0x80093258: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x8009325C: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
L_80093260:
    // 0x80093260: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80093264: sra         $t6, $t5, 8
    ctx->r14 = S32(SIGNED(ctx->r13) >> 8);
    // 0x80093268: sw          $t6, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->r14;
L_8009326C:
    // 0x8009326C: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x80093270: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80093274: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80093278: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x8009327C: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x80093280: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x80093284: jr          $ra
    // 0x80093288: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    return;
    // 0x80093288: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
;}
RECOMP_FUNC void func_8009328C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009328C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80093290: lw          $t6, -0x54D8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54D8);
    // 0x80093294: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80093298: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x8009329C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800932A0: bne         $t6, $at, L_80093344
    if (ctx->r14 != ctx->r1) {
        // 0x800932A4: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_80093344;
    }
    // 0x800932A4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800932A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    { extern uint32_t wr64_course_group_begin(uint8_t*, uint32_t, uint32_t); ctx->r4 = wr64_course_group_begin(rdram, ctx->r4, 0); }
    // 0x800932AC: jal         0x8008FB74
    // 0x800932B0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    func_8008FB74(rdram, ctx);
        goto after_0;
    // 0x800932B0: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    after_0:
    { extern uint32_t wr64_course_group_end(uint8_t*, uint32_t); ctx->r2 = wr64_course_group_end(rdram, ctx->r2); }
    // 0x800932B4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800932B8: jal         0x8006E674
    // 0x800932BC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_8006E674(rdram, ctx);
        goto after_1;
    // 0x800932BC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_1:
    // 0x800932C0: jal         0x800687A4
    // 0x800932C4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800687A4(rdram, ctx);
        goto after_2;
    // 0x800932C4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x800932C8: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800932CC: jal         0x8007FFA8
    // 0x800932D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_8007FFA8(rdram, ctx);
        goto after_3;
    // 0x800932D0: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x800932D4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800932D8: lw          $v1, -0x19C8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C8);
    // 0x800932DC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800932E0: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800932E4: beq         $v1, $at, L_80093300
    if (ctx->r3 == ctx->r1) {
        // 0x800932E8: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_80093300;
    }
    // 0x800932E8: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800932EC: beq         $v1, $at, L_80093300
    if (ctx->r3 == ctx->r1) {
        // 0x800932F0: nop
    
            goto L_80093300;
    }
    // 0x800932F0: nop

    // 0x800932F4: jal         0x800ADF90
    // 0x800932F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800ADF90(rdram, ctx);
        goto after_4;
    // 0x800932F8: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x800932FC: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_80093300:
    // 0x80093300: jal         0x80090F58
    // 0x80093304: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    Draw_WaterEffects(rdram, ctx);
        goto after_5;
    // 0x80093304: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_5:
    // 0x80093308: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x8009330C: jal         0x80069594
    // 0x80093310: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80069594(rdram, ctx);
        goto after_6;
    // 0x80093310: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_6:
    // 0x80093314: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093318: jal         0x80068538
    // 0x8009331C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80068538(rdram, ctx);
        goto after_7;
    // 0x8009331C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_7:
    // 0x80093320: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093324: jal         0x8006E024
    // 0x80093328: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    configSignalRectangle(rdram, ctx);
        goto after_8;
    // 0x80093328: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_8:
    // 0x8009332C: jal         0x800B305C
    // 0x80093330: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_800B305C(rdram, ctx);
        goto after_9;
    // 0x80093330: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_9:
    // 0x80093334: jal         0x8008BD2C
    // 0x80093338: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_8008BD2C(rdram, ctx);
        goto after_10;
    // 0x80093338: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_10:
    // 0x8009333C: b           L_80093378
    // 0x80093340: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
        goto L_80093378;
    // 0x80093340: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_80093344:
    // 0x80093344: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093348: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
    // 0x8009334C: jal         0x800933C4
    // 0x80093350: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800933C4(rdram, ctx);
        goto after_11;
    // 0x80093350: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_11:
    // 0x80093354: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x80093358: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x8009335C: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093360: sw          $t7, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = ctx->r15;
    // 0x80093364: jal         0x800933C4
    // 0x80093368: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800933C4(rdram, ctx);
        goto after_12;
    // 0x80093368: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_12:
    // 0x8009336C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093370: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093374: sw          $zero, -0x54D4($at)
    MEM_W(-0X54D4, ctx->r1) = 0;
L_80093378:
    // 0x80093378: jal         0x80051538
    // 0x8009337C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_80051538(rdram, ctx);
        goto after_13;
    // 0x8009337C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_13:
    // 0x80093380: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80093384: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x80093388: addiu       $at, $zero, 0x2D
    ctx->r1 = ADD32(0, 0X2D);
    // 0x8009338C: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093390: bne         $t8, $at, L_800933A8
    if (ctx->r24 != ctx->r1) {
        // 0x80093394: lui         $t9, 0x8023
        ctx->r25 = S32(0X8023 << 16);
            goto L_800933A8;
    }
    // 0x80093394: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x80093398: lw          $t9, -0x755C($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X755C);
    // 0x8009339C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800933A0: beql        $t9, $at, L_800933B4
    if (ctx->r25 == ctx->r1) {
        // 0x800933A4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800933B4;
    }
    goto skip_0;
    // 0x800933A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
L_800933A8:
    // 0x800933A8: jal         0x801FC4D4
    // 0x800933AC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_801FC4D4(rdram, ctx);
        goto after_14;
    // 0x800933AC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_14:
    // 0x800933B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800933B4:
    // 0x800933B4: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x800933B8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800933BC: jr          $ra
    // 0x800933C0: nop

    return;
    // 0x800933C0: nop

;}
RECOMP_FUNC void func_800933C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800933C4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800933C8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    { extern uint32_t wr64_course_group_begin(uint8_t*, uint32_t, uint32_t); ctx->r4 = wr64_course_group_begin(rdram, ctx->r4, MEM_W(0, S32(0x800DAB2C))); }
    // 0x800933CC: jal         0x8008FB74
    // 0x800933D0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_8008FB74(rdram, ctx);
        goto after_0;
    // 0x800933D0: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    { extern uint32_t wr64_course_group_end(uint8_t*, uint32_t); ctx->r2 = wr64_course_group_end(rdram, ctx->r2); }
    // 0x800933D4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800933D8: jal         0x8006E674
    // 0x800933DC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_8006E674(rdram, ctx);
        goto after_1;
    // 0x800933DC: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_1:
    // 0x800933E0: jal         0x800687A4
    // 0x800933E4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    func_800687A4(rdram, ctx);
        goto after_2;
    // 0x800933E4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_2:
    // 0x800933E8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800933EC: lw          $v1, -0x19C8($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X19C8);
    // 0x800933F0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800933F4: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x800933F8: beq         $v1, $at, L_80093414
    if (ctx->r3 == ctx->r1) {
        // 0x800933FC: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_80093414;
    }
    // 0x800933FC: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x80093400: beq         $v1, $at, L_80093414
    if (ctx->r3 == ctx->r1) {
        // 0x80093404: nop
    
            goto L_80093414;
    }
    // 0x80093404: nop

    // 0x80093408: jal         0x800ADF90
    // 0x8009340C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_800ADF90(rdram, ctx);
        goto after_3;
    // 0x8009340C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_3:
    // 0x80093410: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
L_80093414:
    // 0x80093414: jal         0x80090F58
    // 0x80093418: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    Draw_WaterEffects(rdram, ctx);
        goto after_4;
    // 0x80093418: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    after_4:
    // 0x8009341C: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093420: jal         0x80069594
    // 0x80093424: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80069594(rdram, ctx);
        goto after_5;
    // 0x80093424: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_5:
    // 0x80093428: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x8009342C: jal         0x80068538
    // 0x80093430: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    func_80068538(rdram, ctx);
        goto after_6;
    // 0x80093430: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_6:
    // 0x80093434: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    // 0x80093438: jal         0x8006E024
    // 0x8009343C: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    configSignalRectangle(rdram, ctx);
        goto after_7;
    // 0x8009343C: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_7:
    // 0x80093440: jal         0x800B305C
    // 0x80093444: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    func_800B305C(rdram, ctx);
        goto after_8;
    // 0x80093444: addiu       $a0, $sp, 0x18
    ctx->r4 = ADD32(ctx->r29, 0X18);
    after_8:
    // 0x80093448: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009344C: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    { extern uint32_t wr64_two_player_sun_overlay(uint8_t*, recomp_context*, uint32_t); ctx->r2 = S32(wr64_two_player_sun_overlay(rdram, ctx, (uint32_t)ctx->r2)); }
    // 0x80093450: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80093454: jr          $ra
    // 0x80093458: nop

    return;
    // 0x80093458: nop

;}
RECOMP_FUNC void func_8009345C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009345C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80093460: addiu       $v1, $v1, -0x54DC
    ctx->r3 = ADD32(ctx->r3, -0X54DC);
    // 0x80093464: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x80093468: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009346C: addiu       $t7, $zero, 0x28
    ctx->r15 = ADD32(0, 0X28);
    // 0x80093470: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x80093474: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093478: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x8009347C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80093480: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80093484: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093488: sw          $a2, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r6;
    // 0x8009348C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093490: sw          $a2, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r6;
    // 0x80093494: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093498: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x8009349C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800934A0: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x800934A4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800934A8: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x800934AC: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
    // 0x800934B0: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x800934B4: sw          $t4, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r12;
    // 0x800934B8: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x800934BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800934C0: addiu       $a3, $a3, -0x4CC8
    ctx->r7 = ADD32(ctx->r7, -0X4CC8);
    // 0x800934C4: sw          $zero, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = 0;
    // 0x800934C8: lw          $v0, 0x0($a3)
    ctx->r2 = MEM_W(ctx->r7, 0X0);
    // 0x800934CC: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x800934D0: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800934D4: bne         $v0, $zero, L_80093538
    if (ctx->r2 != 0) {
        // 0x800934D8: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80093538;
    }
    // 0x800934D8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800934DC: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x800934E0: jal         0x800948DC
    // 0x800934E4: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    func_800948DC(rdram, ctx);
        goto after_0;
    // 0x800934E4: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    after_0:
    // 0x800934E8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800934EC: addiu       $a0, $a0, -0x4CF8
    ctx->r4 = ADD32(ctx->r4, -0X4CF8);
    // 0x800934F0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800934F4: lw          $t8, 0x4($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X4);
    // 0x800934F8: lw          $t9, 0x8($a0)
    ctx->r25 = MEM_W(ctx->r4, 0X8);
    // 0x800934FC: lw          $t6, 0x0($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X0);
    // 0x80093500: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x80093504: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x80093508: addiu       $t0, $t0, -0x18D4
    ctx->r8 = ADD32(ctx->r8, -0X18D4);
    // 0x8009350C: sw          $v0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r2;
    // 0x80093510: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x80093514: lui         $ra, 0x800E
    ctx->r31 = S32(0X800E << 16);
    // 0x80093518: sw          $t8, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r24;
    // 0x8009351C: sw          $t9, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r25;
    // 0x80093520: sh          $t6, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r14;
    // 0x80093524: addiu       $a3, $a3, -0x4CC8
    ctx->r7 = ADD32(ctx->r7, -0X4CC8);
    // 0x80093528: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009352C: lw          $ra, -0x7E90($ra)
    ctx->r31 = MEM_W(ctx->r31, -0X7E90);
    // 0x80093530: b           L_80093644
    // 0x80093534: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
        goto L_80093644;
    // 0x80093534: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
L_80093538:
    // 0x80093538: bne         $a2, $v0, L_8009359C
    if (ctx->r6 != ctx->r2) {
        // 0x8009353C: lui         $a1, 0x800E
        ctx->r5 = S32(0X800E << 16);
            goto L_8009359C;
    }
    // 0x8009353C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80093540: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x80093544: jal         0x800948DC
    // 0x80093548: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    func_800948DC(rdram, ctx);
        goto after_1;
    // 0x80093548: or          $a0, $a2, $zero
    ctx->r4 = ctx->r6 | 0;
    after_1:
    // 0x8009354C: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80093550: addiu       $a0, $a0, -0x4CF8
    ctx->r4 = ADD32(ctx->r4, -0X4CF8);
    // 0x80093554: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80093558: lw          $t7, 0x10($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X10);
    // 0x8009355C: lw          $t8, 0x14($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X14);
    // 0x80093560: lw          $t9, 0xC($a0)
    ctx->r25 = MEM_W(ctx->r4, 0XC);
    // 0x80093564: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x80093568: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x8009356C: addiu       $t0, $t0, -0x18D4
    ctx->r8 = ADD32(ctx->r8, -0X18D4);
    // 0x80093570: sw          $v0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r2;
    // 0x80093574: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x80093578: lui         $ra, 0x800E
    ctx->r31 = S32(0X800E << 16);
    // 0x8009357C: sw          $t7, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r15;
    // 0x80093580: sw          $t8, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r24;
    // 0x80093584: sh          $t9, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r25;
    // 0x80093588: addiu       $a3, $a3, -0x4CC8
    ctx->r7 = ADD32(ctx->r7, -0X4CC8);
    // 0x8009358C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80093590: lw          $ra, -0x7E90($ra)
    ctx->r31 = MEM_W(ctx->r31, -0X7E90);
    // 0x80093594: b           L_80093644
    // 0x80093598: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
        goto L_80093644;
    // 0x80093598: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
L_8009359C:
    // 0x8009359C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800935A0: lh          $t6, -0x5498($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X5498);
    // 0x800935A4: beq         $t6, $zero, L_800935E8
    if (ctx->r14 == 0) {
        // 0x800935A8: lui         $ra, 0x800E
        ctx->r31 = S32(0X800E << 16);
            goto L_800935E8;
    }
    // 0x800935A8: lui         $ra, 0x800E
    ctx->r31 = S32(0X800E << 16);
    // 0x800935AC: lw          $ra, -0x7E90($ra)
    ctx->r31 = MEM_W(ctx->r31, -0X7E90);
    // 0x800935B0: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800935B4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800935B8: sll         $t7, $ra, 1
    ctx->r15 = S32(ctx->r31 << 1);
    // 0x800935BC: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x800935C0: lh          $t8, -0x5414($t8)
    ctx->r24 = MEM_H(ctx->r24, -0X5414);
    // 0x800935C4: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x800935C8: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800935CC: addiu       $t0, $t0, -0x18D4
    ctx->r8 = ADD32(ctx->r8, -0X18D4);
    // 0x800935D0: addiu       $t9, $zero, 0x5
    ctx->r25 = ADD32(0, 0X5);
    // 0x800935D4: sw          $t9, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r25;
    // 0x800935D8: sw          $t4, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r12;
    // 0x800935DC: sh          $zero, 0x0($t0)
    MEM_H(0X0, ctx->r8) = 0;
    // 0x800935E0: b           L_80093644
    // 0x800935E4: sw          $t8, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r24;
        goto L_80093644;
    // 0x800935E4: sw          $t8, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r24;
L_800935E8:
    // 0x800935E8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x800935EC: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    // 0x800935F0: jal         0x800948DC
    // 0x800935F4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800948DC(rdram, ctx);
        goto after_2;
    // 0x800935F4: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_2:
    // 0x800935F8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800935FC: addiu       $a0, $a0, -0x4CF8
    ctx->r4 = ADD32(ctx->r4, -0X4CF8);
    // 0x80093600: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80093604: lw          $t6, 0x1C($a0)
    ctx->r14 = MEM_W(ctx->r4, 0X1C);
    // 0x80093608: lw          $t7, 0x20($a0)
    ctx->r15 = MEM_W(ctx->r4, 0X20);
    // 0x8009360C: lw          $t8, 0x18($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X18);
    // 0x80093610: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x80093614: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x80093618: addiu       $t0, $t0, -0x18D4
    ctx->r8 = ADD32(ctx->r8, -0X18D4);
    // 0x8009361C: sw          $v0, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r2;
    // 0x80093620: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x80093624: lui         $ra, 0x800E
    ctx->r31 = S32(0X800E << 16);
    // 0x80093628: sw          $t6, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r14;
    // 0x8009362C: sw          $t7, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r15;
    // 0x80093630: sh          $t8, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r24;
    // 0x80093634: addiu       $a3, $a3, -0x4CC8
    ctx->r7 = ADD32(ctx->r7, -0X4CC8);
    // 0x80093638: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009363C: lw          $ra, -0x7E90($ra)
    ctx->r31 = MEM_W(ctx->r31, -0X7E90);
    // 0x80093640: addiu       $t4, $zero, 0x3
    ctx->r12 = ADD32(0, 0X3);
L_80093644:
    // 0x80093644: lw          $a0, 0x0($v1)
    ctx->r4 = MEM_W(ctx->r3, 0X0);
    // 0x80093648: lh          $t9, 0x4($v1)
    ctx->r25 = MEM_H(ctx->r3, 0X4);
    // 0x8009364C: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80093650: addiu       $t1, $t1, -0x19E0
    ctx->r9 = ADD32(ctx->r9, -0X19E0);
    // 0x80093654: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093658: sw          $a0, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r4;
    // 0x8009365C: sw          $t9, -0x54D8($at)
    MEM_W(-0X54D8, ctx->r1) = ctx->r25;
    // 0x80093660: lh          $t6, 0x6($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X6);
    // 0x80093664: lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // 0x80093668: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x8009366C: sw          $t6, -0x7D10($at)
    MEM_W(-0X7D10, ctx->r1) = ctx->r14;
    // 0x80093670: lw          $t7, 0xC($v1)
    ctx->r15 = MEM_W(ctx->r3, 0XC);
    // 0x80093674: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093678: addiu       $v0, $v0, 0x49B0
    ctx->r2 = ADD32(ctx->r2, 0X49B0);
    // 0x8009367C: sw          $t7, -0x7E8C($at)
    MEM_W(-0X7E8C, ctx->r1) = ctx->r15;
    // 0x80093680: lw          $t8, 0x14($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X14);
    // 0x80093684: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x80093688: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    // 0x8009368C: sh          $t8, 0x4970($at)
    MEM_H(0X4970, ctx->r1) = ctx->r24;
    // 0x80093690: lw          $t9, 0x8($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X8);
    // 0x80093694: bne         $t2, $a0, L_800936C4
    if (ctx->r10 != ctx->r4) {
        // 0x80093698: sw          $t9, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r25;
            goto L_800936C4;
    }
    // 0x80093698: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x8009369C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800936A0: lw          $t6, -0x1908($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X1908);
    // 0x800936A4: beq         $t6, $zero, L_800936BC
    if (ctx->r14 == 0) {
        // 0x800936A8: nop
    
            goto L_800936BC;
    }
    // 0x800936A8: nop

    // 0x800936AC: lw          $t7, 0x10($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X10);
    // 0x800936B0: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800936B4: addiu       $a1, $a1, -0x18D8
    ctx->r5 = ADD32(ctx->r5, -0X18D8);
    // 0x800936B8: sw          $t7, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r15;
L_800936BC:
    // 0x800936BC: b           L_80093714
    // 0x800936C0: addiu       $t3, $zero, 0xB
    ctx->r11 = ADD32(0, 0XB);
        goto L_80093714;
    // 0x800936C0: addiu       $t3, $zero, 0xB
    ctx->r11 = ADD32(0, 0XB);
L_800936C4:
    // 0x800936C4: addiu       $t3, $zero, 0xB
    ctx->r11 = ADD32(0, 0XB);
    // 0x800936C8: bne         $t3, $a0, L_80093704
    if (ctx->r11 != ctx->r4) {
        // 0x800936CC: lui         $a1, 0x801D
        ctx->r5 = S32(0X801D << 16);
            goto L_80093704;
    }
    // 0x800936CC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800936D0: sll         $t8, $ra, 1
    ctx->r24 = S32(ctx->r31 << 1);
    // 0x800936D4: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800936D8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800936DC: addu        $t9, $t9, $t8
    ctx->r25 = ADD32(ctx->r25, ctx->r24);
    // 0x800936E0: lh          $t9, -0x5414($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X5414);
    // 0x800936E4: sw          $zero, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = 0;
    // 0x800936E8: addiu       $a1, $a1, -0x18D8
    ctx->r5 = ADD32(ctx->r5, -0X18D8);
    // 0x800936EC: sw          $a2, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r6;
    // 0x800936F0: sw          $a2, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r6;
    // 0x800936F4: sh          $zero, 0x0($t0)
    MEM_H(0X0, ctx->r8) = 0;
    // 0x800936F8: sw          $t9, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r25;
    // 0x800936FC: b           L_80093714
    // 0x80093700: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
        goto L_80093714;
    // 0x80093700: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
L_80093704:
    // 0x80093704: lw          $t8, 0x10($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X10);
    // 0x80093708: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x8009370C: addiu       $a1, $a1, -0x18D8
    ctx->r5 = ADD32(ctx->r5, -0X18D8);
    // 0x80093710: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
L_80093714:
    // 0x80093714: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093718: sw          $zero, -0x7E88($at)
    MEM_W(-0X7E88, ctx->r1) = 0;
    // 0x8009371C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80093720: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093724: addiu       $v0, $v0, -0x1904
    ctx->r2 = ADD32(ctx->r2, -0X1904);
    // 0x80093728: sw          $zero, -0x19B4($at)
    MEM_W(-0X19B4, ctx->r1) = 0;
    // 0x8009372C: bne         $ra, $zero, L_80093744
    if (ctx->r31 != 0) {
        // 0x80093730: sh          $zero, 0x0($v0)
        MEM_H(0X0, ctx->r2) = 0;
            goto L_80093744;
    }
    // 0x80093730: sh          $zero, 0x0($v0)
    MEM_H(0X0, ctx->r2) = 0;
    // 0x80093734: lw          $t9, 0x0($t1)
    ctx->r25 = MEM_W(ctx->r9, 0X0);
    // 0x80093738: bne         $t3, $t9, L_80093744
    if (ctx->r11 != ctx->r25) {
        // 0x8009373C: nop
    
            goto L_80093744;
    }
    // 0x8009373C: nop

    // 0x80093740: sh          $a2, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r6;
L_80093744:
    // 0x80093744: bne         $ra, $zero, L_8009376C
    if (ctx->r31 != 0) {
        // 0x80093748: nop
    
            goto L_8009376C;
    }
    // 0x80093748: nop

    // 0x8009374C: lh          $t6, 0x0($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X0);
    // 0x80093750: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093754: bne         $t6, $zero, L_8009376C
    if (ctx->r14 != 0) {
        // 0x80093758: nop
    
            goto L_8009376C;
    }
    // 0x80093758: nop

    // 0x8009375C: sw          $t4, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = ctx->r12;
    // 0x80093760: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093764: b           L_8009377C
    // 0x80093768: sw          $t4, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r12;
        goto L_8009377C;
    // 0x80093768: sw          $t4, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r12;
L_8009376C:
    // 0x8009376C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093770: sw          $zero, -0x19B0($at)
    MEM_W(-0X19B0, ctx->r1) = 0;
    // 0x80093774: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093778: sw          $a2, -0x19B8($at)
    MEM_W(-0X19B8, ctx->r1) = ctx->r6;
L_8009377C:
    // 0x8009377C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80093780: beq         $a0, $zero, L_80093910
    if (ctx->r4 == 0) {
        // 0x80093784: sh          $zero, -0x1910($at)
        MEM_H(-0X1910, ctx->r1) = 0;
            goto L_80093910;
    }
    // 0x80093784: sh          $zero, -0x1910($at)
    MEM_H(-0X1910, ctx->r1) = 0;
    // 0x80093788: beq         $a0, $a2, L_800939D8
    if (ctx->r4 == ctx->r6) {
        // 0x8009378C: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_800939D8;
    }
    // 0x8009378C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80093790: beq         $a0, $t2, L_800937A8
    if (ctx->r4 == ctx->r10) {
        // 0x80093794: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_800937A8;
    }
    // 0x80093794: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80093798: beq         $a0, $t3, L_80093974
    if (ctx->r4 == ctx->r11) {
        // 0x8009379C: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_80093974;
    }
    // 0x8009379C: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800937A0: b           L_80093A3C
    // 0x800937A4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
        goto L_80093A3C;
    // 0x800937A4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_800937A8:
    // 0x800937A8: lh          $t7, -0x5498($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X5498);
    // 0x800937AC: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800937B0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800937B4: beq         $t7, $zero, L_800937C4
    if (ctx->r15 == 0) {
        // 0x800937B8: addiu       $a1, $a1, -0x4C08
        ctx->r5 = ADD32(ctx->r5, -0X4C08);
            goto L_800937C4;
    }
    // 0x800937B8: addiu       $a1, $a1, -0x4C08
    ctx->r5 = ADD32(ctx->r5, -0X4C08);
    // 0x800937BC: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x800937C0: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
L_800937C4:
    // 0x800937C4: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x800937C8: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x800937CC: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800937D0: addiu       $a0, $t9, -0x5650
    ctx->r4 = ADD32(ctx->r25, -0X5650);
    // 0x800937D4: lui         $v0, 0x8019
    ctx->r2 = S32(0X8019 << 16);
    // 0x800937D8: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x800937DC: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x800937E0: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x800937E4: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x800937E8: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800937EC: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x800937F0: sw          $zero, -0x7DC0($at)
    MEM_W(-0X7DC0, ctx->r1) = 0;
    // 0x800937F4: addu        $a3, $t7, $a0
    ctx->r7 = ADD32(ctx->r15, ctx->r4);
    // 0x800937F8: addiu       $t0, $t0, -0x4CD4
    ctx->r8 = ADD32(ctx->r8, -0X4CD4);
    // 0x800937FC: addiu       $t1, $t1, -0x56B0
    ctx->r9 = ADD32(ctx->r9, -0X56B0);
    // 0x80093800: addiu       $t2, $t2, -0x5640
    ctx->r10 = ADD32(ctx->r10, -0X5640);
    // 0x80093804: addiu       $t3, $t3, -0x4D68
    ctx->r11 = ADD32(ctx->r11, -0X4D68);
    // 0x80093808: addiu       $t4, $t4, -0x695C
    ctx->r12 = ADD32(ctx->r12, -0X695C);
    // 0x8009380C: addiu       $v0, $v0, 0x2690
    ctx->r2 = ADD32(ctx->r2, 0X2690);
    // 0x80093810: addiu       $t5, $zero, 0xC
    ctx->r13 = ADD32(0, 0XC);
    // 0x80093814: addiu       $a2, $zero, 0xE
    ctx->r6 = ADD32(0, 0XE);
    // 0x80093818: sw          $t6, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r14;
L_8009381C:
    // 0x8009381C: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x80093820: sh          $zero, 0x0($a1)
    MEM_H(0X0, ctx->r5) = 0;
    // 0x80093824: bne         $a0, $a3, L_8009387C
    if (ctx->r4 != ctx->r7) {
        // 0x80093828: sw          $t8, 0xB68($v0)
        MEM_W(0XB68, ctx->r2) = ctx->r24;
            goto L_8009387C;
    }
    // 0x80093828: sw          $t8, 0xB68($v0)
    MEM_W(0XB68, ctx->r2) = ctx->r24;
    // 0x8009382C: lw          $t6, 0x0($t0)
    ctx->r14 = MEM_W(ctx->r8, 0X0);
    // 0x80093830: bnel        $t6, $zero, L_80093850
    if (ctx->r14 != 0) {
        // 0x80093834: lw          $t8, 0xB68($v0)
        ctx->r24 = MEM_W(ctx->r2, 0XB68);
            goto L_80093850;
    }
    goto skip_0;
    // 0x80093834: lw          $t8, 0xB68($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XB68);
    skip_0:
    // 0x80093838: multu       $t8, $a2
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009383C: mflo        $t9
    ctx->r25 = lo;
    // 0x80093840: addu        $v1, $t1, $t9
    ctx->r3 = ADD32(ctx->r9, ctx->r25);
    // 0x80093844: b           L_80093864
    // 0x80093848: lb          $t7, 0xB($v1)
    ctx->r15 = MEM_B(ctx->r3, 0XB);
        goto L_80093864;
    // 0x80093848: lb          $t7, 0xB($v1)
    ctx->r15 = MEM_B(ctx->r3, 0XB);
    // 0x8009384C: lw          $t8, 0xB68($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XB68);
L_80093850:
    // 0x80093850: multu       $t8, $a2
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r6)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80093854: mflo        $t6
    ctx->r14 = lo;
    // 0x80093858: addu        $v1, $t3, $t6
    ctx->r3 = ADD32(ctx->r11, ctx->r14);
    // 0x8009385C: nop

    // 0x80093860: lb          $t7, 0xB($v1)
    ctx->r15 = MEM_B(ctx->r3, 0XB);
L_80093864:
    // 0x80093864: sw          $t7, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r15;
    // 0x80093868: lb          $t9, 0xC($v1)
    ctx->r25 = MEM_B(ctx->r3, 0XC);
    // 0x8009386C: sw          $t9, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r25;
    // 0x80093870: lb          $t8, 0xD($v1)
    ctx->r24 = MEM_B(ctx->r3, 0XD);
    // 0x80093874: b           L_800938B4
    // 0x80093878: sw          $t8, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r24;
        goto L_800938B4;
    // 0x80093878: sw          $t8, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r24;
L_8009387C:
    // 0x8009387C: lw          $t9, 0xB68($v0)
    ctx->r25 = MEM_W(ctx->r2, 0XB68);
    // 0x80093880: sll         $t6, $ra, 2
    ctx->r14 = S32(ctx->r31 << 2);
    // 0x80093884: subu        $t6, $t6, $ra
    ctx->r14 = SUB32(ctx->r14, ctx->r31);
    // 0x80093888: multu       $t9, $t5
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r13)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009388C: sll         $t6, $t6, 4
    ctx->r14 = S32(ctx->r14 << 4);
    // 0x80093890: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x80093894: mflo        $t8
    ctx->r24 = lo;
    // 0x80093898: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x8009389C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x800938A0: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x800938A4: lw          $t7, 0x8($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X8);
    // 0x800938A8: sw          $t6, 0xB6C($v0)
    MEM_W(0XB6C, ctx->r2) = ctx->r14;
    // 0x800938AC: sw          $t9, 0xB70($v0)
    MEM_W(0XB70, ctx->r2) = ctx->r25;
    // 0x800938B0: sw          $t7, 0xB74($v0)
    MEM_W(0XB74, ctx->r2) = ctx->r15;
L_800938B4:
    // 0x800938B4: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800938B8: addiu       $a1, $a1, 0x2
    ctx->r5 = ADD32(ctx->r5, 0X2);
    // 0x800938BC: bne         $a0, $t2, L_8009381C
    if (ctx->r4 != ctx->r10) {
        // 0x800938C0: addiu       $v0, $v0, 0x1718
        ctx->r2 = ADD32(ctx->r2, 0X1718);
            goto L_8009381C;
    }
    // 0x800938C0: addiu       $v0, $v0, 0x1718
    ctx->r2 = ADD32(ctx->r2, 0X1718);
    // 0x800938C4: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
    // 0x800938C8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800938CC: addiu       $v1, $v1, -0x190C
    ctx->r3 = ADD32(ctx->r3, -0X190C);
    // 0x800938D0: lh          $t7, 0x0($v1)
    ctx->r15 = MEM_H(ctx->r3, 0X0);
    // 0x800938D4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800938D8: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x800938DC: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x800938E0: addu        $t9, $v0, $t6
    ctx->r25 = ADD32(ctx->r2, ctx->r14);
    // 0x800938E4: beq         $t7, $zero, L_800938F0
    if (ctx->r15 == 0) {
        // 0x800938E8: lw          $a1, 0x0($t9)
        ctx->r5 = MEM_W(ctx->r25, 0X0);
            goto L_800938F0;
    }
    // 0x800938E8: lw          $a1, 0x0($t9)
    ctx->r5 = MEM_W(ctx->r25, 0X0);
    // 0x800938EC: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_800938F0:
    // 0x800938F0: lw          $t8, 0xC($v0)
    ctx->r24 = MEM_W(ctx->r2, 0XC);
    // 0x800938F4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800938F8: lw          $a2, 0x4($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X4);
    // 0x800938FC: lw          $a3, 0x8($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X8);
    // 0x80093900: jal         0x80096960
    // 0x80093904: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    func_80096960(rdram, ctx);
        goto after_3;
    // 0x80093904: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    after_3:
    // 0x80093908: b           L_80093A54
    // 0x8009390C: nop

        goto L_80093A54;
    // 0x8009390C: nop

L_80093910:
    // 0x80093910: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80093914: lh          $t6, -0x5498($t6)
    ctx->r14 = MEM_H(ctx->r14, -0X5498);
    // 0x80093918: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8009391C: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x80093920: beq         $t6, $zero, L_80093930
    if (ctx->r14 == 0) {
        // 0x80093924: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_80093930;
    }
    // 0x80093924: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80093928: addiu       $t9, $zero, 0x2
    ctx->r25 = ADD32(0, 0X2);
    // 0x8009392C: sw          $t9, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r25;
L_80093930:
    // 0x80093930: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x80093934: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x80093938: addiu       $v1, $v1, -0x190C
    ctx->r3 = ADD32(ctx->r3, -0X190C);
    // 0x8009393C: lh          $t9, 0x0($v1)
    ctx->r25 = MEM_H(ctx->r3, 0X0);
    // 0x80093940: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80093944: addu        $t6, $v0, $t8
    ctx->r14 = ADD32(ctx->r2, ctx->r24);
    // 0x80093948: beq         $t9, $zero, L_80093954
    if (ctx->r25 == 0) {
        // 0x8009394C: lw          $a1, 0x0($t6)
        ctx->r5 = MEM_W(ctx->r14, 0X0);
            goto L_80093954;
    }
    // 0x8009394C: lw          $a1, 0x0($t6)
    ctx->r5 = MEM_W(ctx->r14, 0X0);
    // 0x80093950: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_80093954:
    // 0x80093954: lw          $t7, 0xC($v0)
    ctx->r15 = MEM_W(ctx->r2, 0XC);
    // 0x80093958: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009395C: lw          $a2, 0x4($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X4);
    // 0x80093960: lw          $a3, 0x8($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X8);
    // 0x80093964: jal         0x80096960
    // 0x80093968: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    func_80096960(rdram, ctx);
        goto after_4;
    // 0x80093968: sw          $t7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r15;
    after_4:
    // 0x8009396C: b           L_80093A54
    // 0x80093970: nop

        goto L_80093A54;
    // 0x80093970: nop

L_80093974:
    // 0x80093974: bne         $ra, $at, L_80093984
    if (ctx->r31 != ctx->r1) {
        // 0x80093978: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_80093984;
    }
    // 0x80093978: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8009397C: b           L_8009398C
    // 0x80093980: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_8009398C;
    // 0x80093980: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_80093984:
    // 0x80093984: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x80093988: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
L_8009398C:
    // 0x8009398C: lui         $t6, 0x800D
    ctx->r14 = S32(0X800D << 16);
    // 0x80093990: lw          $t6, 0x48DC($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X48DC);
    // 0x80093994: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80093998: addiu       $v1, $v1, -0x190C
    ctx->r3 = ADD32(ctx->r3, -0X190C);
    // 0x8009399C: lh          $t8, 0x0($v1)
    ctx->r24 = MEM_H(ctx->r3, 0X0);
    // 0x800939A0: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x800939A4: sll         $t9, $t6, 2
    ctx->r25 = S32(ctx->r14 << 2);
    // 0x800939A8: addu        $t7, $v0, $t9
    ctx->r15 = ADD32(ctx->r2, ctx->r25);
    // 0x800939AC: beq         $t8, $zero, L_800939B8
    if (ctx->r24 == 0) {
        // 0x800939B0: lw          $a1, 0x0($t7)
        ctx->r5 = MEM_W(ctx->r15, 0X0);
            goto L_800939B8;
    }
    // 0x800939B0: lw          $a1, 0x0($t7)
    ctx->r5 = MEM_W(ctx->r15, 0X0);
    // 0x800939B4: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_800939B8:
    // 0x800939B8: lw          $t6, 0xC($v0)
    ctx->r14 = MEM_W(ctx->r2, 0XC);
    // 0x800939BC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800939C0: lw          $a2, 0x4($v0)
    ctx->r6 = MEM_W(ctx->r2, 0X4);
    // 0x800939C4: lw          $a3, 0x8($v0)
    ctx->r7 = MEM_W(ctx->r2, 0X8);
    // 0x800939C8: jal         0x80096960
    // 0x800939CC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_80096960(rdram, ctx);
        goto after_5;
    // 0x800939CC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_5:
    // 0x800939D0: b           L_80093A54
    // 0x800939D4: nop

        goto L_80093A54;
    // 0x800939D4: nop

L_800939D8:
    // 0x800939D8: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x800939DC: lw          $t9, 0x48DC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48DC);
    // 0x800939E0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800939E4: addiu       $v1, $v1, -0x190C
    ctx->r3 = ADD32(ctx->r3, -0X190C);
    // 0x800939E8: lh          $t6, 0x0($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X0);
    // 0x800939EC: addiu       $v0, $v0, -0x5650
    ctx->r2 = ADD32(ctx->r2, -0X5650);
    // 0x800939F0: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x800939F4: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x800939F8: beq         $t6, $zero, L_80093A04
    if (ctx->r14 == 0) {
        // 0x800939FC: lw          $a1, 0x0($t8)
        ctx->r5 = MEM_W(ctx->r24, 0X0);
            goto L_80093A04;
    }
    // 0x800939FC: lw          $a1, 0x0($t8)
    ctx->r5 = MEM_W(ctx->r24, 0X0);
    // 0x80093A00: addiu       $a1, $a1, 0x4
    ctx->r5 = ADD32(ctx->r5, 0X4);
L_80093A04:
    // 0x80093A04: lui         $t9, 0x800D
    ctx->r25 = S32(0X800D << 16);
    // 0x80093A08: lw          $t9, 0x48E0($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X48E0);
    // 0x80093A0C: lh          $t6, 0x2($v1)
    ctx->r14 = MEM_H(ctx->r3, 0X2);
    // 0x80093A10: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x80093A14: sll         $t7, $t9, 2
    ctx->r15 = S32(ctx->r25 << 2);
    // 0x80093A18: addu        $t8, $v0, $t7
    ctx->r24 = ADD32(ctx->r2, ctx->r15);
    // 0x80093A1C: beq         $t6, $zero, L_80093A28
    if (ctx->r14 == 0) {
        // 0x80093A20: lw          $a2, 0x0($t8)
        ctx->r6 = MEM_W(ctx->r24, 0X0);
            goto L_80093A28;
    }
    // 0x80093A20: lw          $a2, 0x0($t8)
    ctx->r6 = MEM_W(ctx->r24, 0X0);
    // 0x80093A24: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
L_80093A28:
    // 0x80093A28: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x80093A2C: jal         0x80096960
    // 0x80093A30: sw          $a2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r6;
    func_80096960(rdram, ctx);
        goto after_6;
    // 0x80093A30: sw          $a2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r6;
    after_6:
    // 0x80093A34: b           L_80093A54
    // 0x80093A38: nop

        goto L_80093A54;
    // 0x80093A38: nop

L_80093A3C:
    // 0x80093A3C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x80093A40: sw          $t9, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r25;
    // 0x80093A44: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x80093A48: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80093A4C: jal         0x80096960
    // 0x80093A50: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    func_80096960(rdram, ctx);
        goto after_7;
    // 0x80093A50: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    after_7:
L_80093A54:
    // 0x80093A54: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80093A58: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
    // 0x80093A5C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80093A60: addiu       $t8, $t8, -0x4A98
    ctx->r24 = ADD32(ctx->r24, -0X4A98);
    // 0x80093A64: bgez        $v0, L_80093A70
    if (SIGNED(ctx->r2) >= 0) {
        // 0x80093A68: lui         $a0, 0x806
        ctx->r4 = S32(0X806 << 16);
            goto L_80093A70;
    }
    // 0x80093A68: lui         $a0, 0x806
    ctx->r4 = S32(0X806 << 16);
    // 0x80093A6C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80093A70:
    // 0x80093A70: slti        $at, $v0, 0x9
    ctx->r1 = SIGNED(ctx->r2) < 0X9 ? 1 : 0;
    // 0x80093A74: bnel        $at, $zero, L_80093A84
    if (ctx->r1 != 0) {
        // 0x80093A78: sll         $t7, $v0, 2
        ctx->r15 = S32(ctx->r2 << 2);
            goto L_80093A84;
    }
    goto skip_1;
    // 0x80093A78: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    skip_1:
    // 0x80093A7C: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
    // 0x80093A80: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
L_80093A84:
    // 0x80093A84: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x80093A88: lh          $a1, 0x0($v1)
    ctx->r5 = MEM_H(ctx->r3, 0X0);
    // 0x80093A8C: jal         0x8009684C
    // 0x80093A90: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    func_8009684C(rdram, ctx);
        goto after_8;
    // 0x80093A90: lh          $a2, 0x2($v1)
    ctx->r6 = MEM_H(ctx->r3, 0X2);
    after_8:
    // 0x80093A94: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x80093A98: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    // 0x80093A9C: jal         0x801E6FB0
    // 0x80093AA0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    FadeTransition_SetProps(rdram, ctx);
        goto after_9;
    // 0x80093AA0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_9:
    // 0x80093AA4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80093AA8: jal         0x801E6A4C
    // 0x80093AAC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_801E6A4C(rdram, ctx);
        goto after_10;
    // 0x80093AAC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_10:
    // 0x80093AB0: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x80093AB4: addiu       $v0, $v0, 0x7C80
    ctx->r2 = ADD32(ctx->r2, 0X7C80);
    // 0x80093AB8: addiu       $t6, $zero, 0x3
    ctx->r14 = ADD32(0, 0X3);
    // 0x80093ABC: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80093AC0: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80093AC4: lw          $t9, -0x54D8($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X54D8);
    // 0x80093AC8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80093ACC: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    // 0x80093AD0: bne         $t9, $at, L_80093ADC
    if (ctx->r25 != ctx->r1) {
        // 0x80093AD4: lui         $a1, 0x800E
        ctx->r5 = S32(0X800E << 16);
            goto L_80093ADC;
    }
    // 0x80093AD4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80093AD8: sw          $t6, 0x10C($v0)
    MEM_W(0X10C, ctx->r2) = ctx->r14;
L_80093ADC:
    // 0x80093ADC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80093AE0: sh          $zero, -0x5654($at)
    MEM_H(-0X5654, ctx->r1) = 0;
    // 0x80093AE4: jal         0x800C21F4
    // 0x80093AE8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    func_800C21F4(rdram, ctx);
        goto after_11;
    // 0x80093AE8: lw          $a1, -0x7E90($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X7E90);
    after_11:
    // 0x80093AEC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x80093AF0: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    // 0x80093AF4: jr          $ra
    // 0x80093AF8: nop

    return;
    // 0x80093AF8: nop

;}
RECOMP_FUNC void func_80093AFC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80093AFC: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x80093B00: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80093B04: addiu       $v1, $a0, 0x8
    ctx->r3 = ADD32(ctx->r4, 0X8);
    // 0x80093B08: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x80093B0C: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80093B10: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80093B14: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80093B18: lui         $t8, 0xB700
    ctx->r24 = S32(0XB700 << 16);
    // 0x80093B1C: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80093B20: addiu       $a1, $v1, 0x8
    ctx->r5 = ADD32(ctx->r3, 0X8);
    // 0x80093B24: addiu       $t9, $zero, 0x5
    ctx->r25 = ADD32(0, 0X5);
    // 0x80093B28: sw          $t9, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r25;
    // 0x80093B2C: lui         $t1, 0xBB00
    ctx->r9 = S32(0XBB00 << 16);
    // 0x80093B30: sw          $t1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r9;
    // 0x80093B34: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80093B38: addiu       $a3, $a1, 0x8
    ctx->r7 = ADD32(ctx->r5, 0X8);
    // 0x80093B3C: addiu       $t0, $a3, 0x8
    ctx->r8 = ADD32(ctx->r7, 0X8);
    // 0x80093B40: lui         $t2, 0xE700
    ctx->r10 = S32(0XE700 << 16);
    // 0x80093B44: sw          $t2, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r10;
    // 0x80093B48: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x80093B4C: lui         $t3, 0xBA00
    ctx->r11 = S32(0XBA00 << 16);
    // 0x80093B50: ori         $t3, $t3, 0x1402
    ctx->r11 = ctx->r11 | 0X1402;
    // 0x80093B54: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
    // 0x80093B58: lui         $t4, 0x30
    ctx->r12 = S32(0X30 << 16);
    // 0x80093B5C: sw          $t4, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r12;
    // 0x80093B60: sw          $t3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r11;
    // 0x80093B64: lui         $t6, 0xFFFC
    ctx->r14 = S32(0XFFFC << 16);
    // 0x80093B68: lui         $t5, 0xFCFF
    ctx->r13 = S32(0XFCFF << 16);
    // 0x80093B6C: ori         $t5, $t5, 0xFFFF
    ctx->r13 = ctx->r13 | 0XFFFF;
    // 0x80093B70: ori         $t6, $t6, 0xF279
    ctx->r14 = ctx->r14 | 0XF279;
    // 0x80093B74: addiu       $v1, $v0, 0x8
    ctx->r3 = ADD32(ctx->r2, 0X8);
    // 0x80093B78: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x80093B7C: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
    // 0x80093B80: lui         $t8, 0xF0A
    ctx->r24 = S32(0XF0A << 16);
    // 0x80093B84: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x80093B88: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x80093B8C: ori         $t8, $t8, 0x4000
    ctx->r24 = ctx->r24 | 0X4000;
    // 0x80093B90: addiu       $a2, $v1, 0x8
    ctx->r6 = ADD32(ctx->r3, 0X8);
    // 0x80093B94: sw          $t8, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r24;
    // 0x80093B98: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80093B9C: lui         $t9, 0xFE00
    ctx->r25 = S32(0XFE00 << 16);
    // 0x80093BA0: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
    // 0x80093BA4: addiu       $a1, $a2, 0x8
    ctx->r5 = ADD32(ctx->r6, 0X8);
    // 0x80093BA8: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    // 0x80093BAC: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x80093BB0: jal         0x800C5720
    // 0x80093BB4: lui         $a0, 0x8070
    ctx->r4 = S32(0X8070 << 16);
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x80093BB4: lui         $a0, 0x8070
    ctx->r4 = S32(0X8070 << 16);
    after_0:
    // 0x80093BB8: lw          $a3, 0x40($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X40);
    // 0x80093BBC: lw          $a2, 0x20($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X20);
    // 0x80093BC0: lui         $t1, 0xFF10
    ctx->r9 = S32(0XFF10 << 16);
    // 0x80093BC4: ori         $t1, $t1, 0x1A7
    ctx->r9 = ctx->r9 | 0X1A7;
    // 0x80093BC8: sw          $v0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r2;
    // 0x80093BCC: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x80093BD0: addiu       $a1, $a3, 0x8
    ctx->r5 = ADD32(ctx->r7, 0X8);
    // 0x80093BD4: sw          $a1, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r5;
    // 0x80093BD8: lui         $a0, 0x8070
    ctx->r4 = S32(0X8070 << 16);
    // 0x80093BDC: jal         0x800C5720
    // 0x80093BE0: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_1;
    // 0x80093BE0: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    after_1:
    // 0x80093BE4: lw          $v1, 0x40($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X40);
    // 0x80093BE8: lw          $a3, 0x1C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X1C);
    // 0x80093BEC: lui         $t3, 0xFFFC
    ctx->r11 = S32(0XFFFC << 16);
    // 0x80093BF0: ori         $t3, $t3, 0xFFFC
    ctx->r11 = ctx->r11 | 0XFFFC;
    // 0x80093BF4: sw          $v0, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r2;
    // 0x80093BF8: lui         $t2, 0xF700
    ctx->r10 = S32(0XF700 << 16);
    // 0x80093BFC: addiu       $a0, $v1, 0x8
    ctx->r4 = ADD32(ctx->r3, 0X8);
    // 0x80093C00: lui         $t5, 0x6A
    ctx->r13 = S32(0X6A << 16);
    // 0x80093C04: addiu       $t5, $t5, -0x3C44
    ctx->r13 = ADD32(ctx->r13, -0X3C44);
    // 0x80093C08: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x80093C0C: sw          $t3, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r11;
    // 0x80093C10: lui         $t4, 0xED00
    ctx->r12 = S32(0XED00 << 16);
    // 0x80093C14: sw          $t4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r12;
    // 0x80093C18: sw          $t5, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r13;
    // 0x80093C1C: addiu       $a2, $a0, 0x8
    ctx->r6 = ADD32(ctx->r4, 0X8);
    // 0x80093C20: lui         $t6, 0xF66A
    ctx->r14 = S32(0XF66A << 16);
    // 0x80093C24: addiu       $t6, $t6, -0x3C44
    ctx->r14 = ADD32(ctx->r14, -0X3C44);
    // 0x80093C28: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x80093C2C: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x80093C30: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80093C34: addiu       $v0, $a2, 0x8
    ctx->r2 = ADD32(ctx->r6, 0X8);
    // 0x80093C38: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    // 0x80093C3C: jr          $ra
    // 0x80093C40: nop

    return;
    // 0x80093C40: nop

;}
RECOMP_FUNC void func_80093C44(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80093C44: addiu       $sp, $sp, -0x8
    ctx->r29 = ADD32(ctx->r29, -0X8);
    // 0x80093C48: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80093C4C: sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // 0x80093C50: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093C54: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x80093C58: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80093C5C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80093C60: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x80093C64: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80093C68: lui         $t8, 0xB700
    ctx->r24 = S32(0XB700 << 16);
    // 0x80093C6C: sw          $t8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r24;
    // 0x80093C70: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093C74: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x80093C78: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x80093C7C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80093C80: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093C84: lui         $t6, 0xBB00
    ctx->r14 = S32(0XBB00 << 16);
    // 0x80093C88: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x80093C8C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80093C90: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x80093C94: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093C98: lui         $v1, 0xE700
    ctx->r3 = S32(0XE700 << 16);
    // 0x80093C9C: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x80093CA0: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // 0x80093CA4: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x80093CA8: lui         $t7, 0xBA00
    ctx->r15 = S32(0XBA00 << 16);
    // 0x80093CAC: ori         $t7, $t7, 0x1402
    ctx->r15 = ctx->r15 | 0X1402;
    // 0x80093CB0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093CB4: lui         $t8, 0x30
    ctx->r24 = S32(0X30 << 16);
    // 0x80093CB8: sw          $t8, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r24;
    // 0x80093CBC: sw          $t7, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r15;
    // 0x80093CC0: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80093CC4: lui         $t6, 0xFFFC
    ctx->r14 = S32(0XFFFC << 16);
    // 0x80093CC8: lui         $t9, 0xFCFF
    ctx->r25 = S32(0XFCFF << 16);
    // 0x80093CCC: ori         $t9, $t9, 0xFFFF
    ctx->r25 = ctx->r25 | 0XFFFF;
    // 0x80093CD0: ori         $t6, $t6, 0xF279
    ctx->r14 = ctx->r14 | 0XF279;
    // 0x80093CD4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093CD8: sw          $t6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r14;
    // 0x80093CDC: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80093CE0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80093CE4: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093CE8: lui         $t7, 0xB900
    ctx->r15 = S32(0XB900 << 16);
    // 0x80093CEC: ori         $t7, $t7, 0x31D
    ctx->r15 = ctx->r15 | 0X31D;
    // 0x80093CF0: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80093CF4: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
    // 0x80093CF8: sw          $zero, 0x4($a2)
    MEM_W(0X4, ctx->r6) = 0;
    // 0x80093CFC: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093D00: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x80093D04: ori         $t8, $t8, 0x2
    ctx->r24 = ctx->r24 | 0X2;
    // 0x80093D08: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x80093D0C: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x80093D10: sw          $zero, 0x4($a3)
    MEM_W(0X4, ctx->r7) = 0;
    // 0x80093D14: lui         $t6, 0x6A
    ctx->r14 = S32(0X6A << 16);
    // 0x80093D18: addiu       $t6, $t6, -0x3C44
    ctx->r14 = ADD32(ctx->r14, -0X3C44);
    // 0x80093D1C: lui         $t9, 0xED00
    ctx->r25 = S32(0XED00 << 16);
    // 0x80093D20: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x80093D24: lui         $s0, 0x8015
    ctx->r16 = S32(0X8015 << 16);
    // 0x80093D28: lui         $t5, 0xF669
    ctx->r13 = S32(0XF669 << 16);
    // 0x80093D2C: lui         $t4, 0x1
    ctx->r12 = S32(0X1 << 16);
    // 0x80093D30: lui         $t1, 0xFF10
    ctx->r9 = S32(0XFF10 << 16);
    // 0x80093D34: sw          $t9, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r25;
    // 0x80093D38: sw          $t6, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r14;
    // 0x80093D3C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093D40: ori         $t1, $t1, 0x1A7
    ctx->r9 = ctx->r9 | 0X1A7;
    // 0x80093D44: ori         $t4, $t4, 0x1
    ctx->r12 = ctx->r12 | 0X1;
    // 0x80093D48: ori         $t5, $t5, 0xC3BC
    ctx->r13 = ctx->r13 | 0XC3BC;
    // 0x80093D4C: addiu       $s0, $s0, 0x42CC
    ctx->r16 = ADD32(ctx->r16, 0X42CC);
    // 0x80093D50: addiu       $v0, $v0, 0x42C0
    ctx->r2 = ADD32(ctx->r2, 0X42C0);
    // 0x80093D54: lui         $t3, 0xF700
    ctx->r11 = S32(0XF700 << 16);
    // 0x80093D58: lui         $t2, 0x8000
    ctx->r10 = S32(0X8000 << 16);
L_80093D5C:
    // 0x80093D5C: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80093D60: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093D64: sw          $v1, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r3;
    // 0x80093D68: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80093D6C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80093D70: sw          $t1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r9;
    // 0x80093D74: lw          $t7, 0x0($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X0);
    // 0x80093D78: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093D7C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80093D80: addu        $t8, $t7, $t2
    ctx->r24 = ADD32(ctx->r15, ctx->r10);
    // 0x80093D84: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
    // 0x80093D88: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093D8C: or          $t0, $a0, $zero
    ctx->r8 = ctx->r4 | 0;
    // 0x80093D90: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x80093D94: sw          $t4, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r12;
    // 0x80093D98: sw          $t3, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r11;
    // 0x80093D9C: sw          $zero, 0x4($t0)
    MEM_W(0X4, ctx->r8) = 0;
    // 0x80093DA0: sw          $t5, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r13;
    // 0x80093DA4: bne         $v0, $s0, L_80093D5C
    if (ctx->r2 != ctx->r16) {
        // 0x80093DA8: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_80093D5C;
    }
    // 0x80093DA8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093DAC: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
    // 0x80093DB0: addiu       $sp, $sp, 0x8
    ctx->r29 = ADD32(ctx->r29, 0X8);
    // 0x80093DB4: jr          $ra
    // 0x80093DB8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x80093DB8: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_80093DBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80093DBC: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x80093DC0: sw          $a1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r5;
    // 0x80093DC4: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    // 0x80093DC8: or          $t6, $a1, $zero
    ctx->r14 = ctx->r5 | 0;
    // 0x80093DCC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80093DD0: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    // 0x80093DD4: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x80093DD8: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x80093DDC: sw          $a3, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r7;
    // 0x80093DE0: or          $t7, $a2, $zero
    ctx->r15 = ctx->r6 | 0;
    // 0x80093DE4: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x80093DE8: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093DEC: lui         $t9, 0xB600
    ctx->r25 = S32(0XB600 << 16);
    // 0x80093DF0: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x80093DF4: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x80093DF8: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x80093DFC: or          $v1, $a0, $zero
    ctx->r3 = ctx->r4 | 0;
    // 0x80093E00: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E04: lui         $t7, 0xBB00
    ctx->r15 = S32(0XBB00 << 16);
    // 0x80093E08: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80093E0C: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x80093E10: or          $t8, $a3, $zero
    ctx->r24 = ctx->r7 | 0;
    // 0x80093E14: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80093E18: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E1C: or          $a3, $t8, $zero
    ctx->r7 = ctx->r24 | 0;
    // 0x80093E20: lui         $t0, 0xE700
    ctx->r8 = S32(0XE700 << 16);
    // 0x80093E24: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x80093E28: sw          $t0, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r8;
    // 0x80093E2C: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x80093E30: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E34: lui         $t8, 0xBA00
    ctx->r24 = S32(0XBA00 << 16);
    // 0x80093E38: ori         $t8, $t8, 0x1402
    ctx->r24 = ctx->r24 | 0X1402;
    // 0x80093E3C: lui         $t9, 0x30
    ctx->r25 = S32(0X30 << 16);
    // 0x80093E40: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x80093E44: sw          $t9, 0x4($t2)
    MEM_W(0X4, ctx->r10) = ctx->r25;
    // 0x80093E48: sw          $t8, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r24;
    // 0x80093E4C: lui         $t7, 0xFFFC
    ctx->r15 = S32(0XFFFC << 16);
    // 0x80093E50: lui         $t6, 0xFCFF
    ctx->r14 = S32(0XFCFF << 16);
    // 0x80093E54: ori         $t6, $t6, 0xFFFF
    ctx->r14 = ctx->r14 | 0XFFFF;
    // 0x80093E58: ori         $t7, $t7, 0xF279
    ctx->r15 = ctx->r15 | 0XF279;
    // 0x80093E5C: sw          $t7, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r15;
    // 0x80093E60: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x80093E64: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E68: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x80093E6C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E70: lui         $t8, 0xB900
    ctx->r24 = S32(0XB900 << 16);
    // 0x80093E74: ori         $t8, $t8, 0x31D
    ctx->r24 = ctx->r24 | 0X31D;
    // 0x80093E78: or          $t2, $a0, $zero
    ctx->r10 = ctx->r4 | 0;
    // 0x80093E7C: sw          $t8, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r24;
    // 0x80093E80: sw          $zero, 0x4($t1)
    MEM_W(0X4, ctx->r9) = 0;
    // 0x80093E84: lui         $t9, 0xB900
    ctx->r25 = S32(0XB900 << 16);
    // 0x80093E88: ori         $t9, $t9, 0x2
    ctx->r25 = ctx->r25 | 0X2;
    // 0x80093E8C: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093E90: or          $t3, $a0, $zero
    ctx->r11 = ctx->r4 | 0;
    // 0x80093E94: sw          $t9, 0x0($t2)
    MEM_W(0X0, ctx->r10) = ctx->r25;
    // 0x80093E98: sw          $zero, 0x4($t2)
    MEM_W(0X4, ctx->r10) = 0;
    // 0x80093E9C: lui         $t6, 0xED00
    ctx->r14 = S32(0XED00 << 16);
    // 0x80093EA0: addiu       $t6, $t6, 0x0
    ctx->r14 = ADD32(ctx->r14, 0X0);
    // 0x80093EA4: lui         $t7, 0x6A
    ctx->r15 = S32(0X6A << 16);
    // 0x80093EA8: addiu       $t7, $t7, -0x3C44
    ctx->r15 = ADD32(ctx->r15, -0X3C44);
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r14 = 0xED000000U; ctx->r15 = 0x006A03C0U; } }
    // 0x80093EAC: sw          $t6, 0x0($t3)
    MEM_W(0X0, ctx->r11) = ctx->r14;
    // 0x80093EB0: sw          $t7, 0x4($t3)
    MEM_W(0X4, ctx->r11) = ctx->r15;
    // 0x80093EB4: sll         $t6, $a2, 3
    ctx->r14 = S32(ctx->r6 << 3);
    // 0x80093EB8: andi        $t7, $t6, 0x7C0
    ctx->r15 = ctx->r14 & 0X7C0;
    // 0x80093EBC: sll         $t8, $a1, 8
    ctx->r24 = S32(ctx->r5 << 8);
    // 0x80093EC0: andi        $t9, $t8, 0xF800
    ctx->r25 = ctx->r24 & 0XF800;
    // 0x80093EC4: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x80093EC8: sra         $t6, $a3, 2
    ctx->r14 = S32(SIGNED(ctx->r7) >> 2);
    // 0x80093ECC: andi        $t9, $t6, 0x3E
    ctx->r25 = ctx->r14 & 0X3E;
    // 0x80093ED0: or          $t5, $t8, $t9
    ctx->r13 = ctx->r24 | ctx->r25;
    // 0x80093ED4: ori         $t7, $t5, 0x1
    ctx->r15 = ctx->r13 | 0X1;
    // 0x80093ED8: sll         $t6, $t7, 16
    ctx->r14 = S32(ctx->r15 << 16);
    // 0x80093EDC: lui         $t5, 0xF669
    ctx->r13 = S32(0XF669 << 16);
    // 0x80093EE0: lui         $t2, 0xFF10
    ctx->r10 = S32(0XFF10 << 16);
    // 0x80093EE4: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x80093EE8: lui         $s0, 0x2
    ctx->r16 = S32(0X2 << 16);
    // 0x80093EEC: lui         $s1, 0x8015
    ctx->r17 = S32(0X8015 << 16);
    // 0x80093EF0: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093EF4: addiu       $s1, $s1, 0x42CC
    ctx->r17 = ADD32(ctx->r17, 0X42CC);
    // 0x80093EF8: ori         $s0, $s0, 0x50
    ctx->r16 = ctx->r16 | 0X50;
    // 0x80093EFC: addiu       $v0, $v0, 0x42C0
    ctx->r2 = ADD32(ctx->r2, 0X42C0);
    // 0x80093F00: ori         $t2, $t2, 0x1A7
    ctx->r10 = ctx->r10 | 0X1A7;
    // 0x80093F04: ori         $t5, $t5, 0xC3BC
    ctx->r13 = ctx->r13 | 0XC3BC;
    // 0x80093F08: or          $v1, $t6, $t7
    ctx->r3 = ctx->r14 | ctx->r15;
    // 0x80093F0C: lui         $t3, 0x8000
    ctx->r11 = S32(0X8000 << 16);
    // 0x80093F10: lui         $t4, 0xF700
    ctx->r12 = S32(0XF700 << 16);
L_80093F14:
    // 0x80093F14: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x80093F18: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093F1C: sw          $t0, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r8;
    // 0x80093F20: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80093F24: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x80093F28: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
    // 0x80093F2C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x80093F30: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093F34: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80093F38: addu        $t9, $t8, $t3
    ctx->r25 = ADD32(ctx->r24, ctx->r11);
    // 0x80093F3C: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
    // 0x80093F40: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093F44: or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // 0x80093F48: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x80093F4C: sw          $v1, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r3;
    // 0x80093F50: sw          $t4, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r12;
    // 0x80093F54: sw          $s0, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r16;
    // 0x80093F58: sw          $t5, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r13;
    // 0x80093F5C: bne         $v0, $s1, L_80093F14
    if (ctx->r2 != ctx->r17) {
        // 0x80093F60: addiu       $a0, $a0, 0x8
        ctx->r4 = ADD32(ctx->r4, 0X8);
            goto L_80093F14;
    }
    // 0x80093F60: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80093F64: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x80093F68: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x80093F6C: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    // 0x80093F70: jr          $ra
    // 0x80093F74: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    return;
    // 0x80093F74: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
;}
RECOMP_FUNC void func_80093F78(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80093F78: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80093F7C: addiu       $v1, $a0, 0x8
    ctx->r3 = ADD32(ctx->r4, 0X8);
    // 0x80093F80: lui         $t6, 0xB600
    ctx->r14 = S32(0XB600 << 16);
    // 0x80093F84: addiu       $t7, $zero, -0x1
    ctx->r15 = ADD32(0, -0X1);
    // 0x80093F88: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
    // 0x80093F8C: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
    // 0x80093F90: addiu       $a1, $v1, 0x8
    ctx->r5 = ADD32(ctx->r3, 0X8);
    // 0x80093F94: lui         $t8, 0xBB00
    ctx->r24 = S32(0XBB00 << 16);
    // 0x80093F98: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80093F9C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80093FA0: addiu       $a2, $a1, 0x8
    ctx->r6 = ADD32(ctx->r5, 0X8);
    // 0x80093FA4: lui         $t9, 0xE700
    ctx->r25 = S32(0XE700 << 16);
    // 0x80093FA8: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80093FAC: sw          $zero, 0x4($a1)
    MEM_W(0X4, ctx->r5) = 0;
    // 0x80093FB0: lui         $t0, 0xBA00
    ctx->r8 = S32(0XBA00 << 16);
    // 0x80093FB4: ori         $t0, $t0, 0x1402
    ctx->r8 = ctx->r8 | 0X1402;
    // 0x80093FB8: lui         $t1, 0x30
    ctx->r9 = S32(0X30 << 16);
    // 0x80093FBC: sw          $t1, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r9;
    // 0x80093FC0: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
    // 0x80093FC4: addiu       $a3, $a2, 0x8
    ctx->r7 = ADD32(ctx->r6, 0X8);
    // 0x80093FC8: lui         $t2, 0xFCFF
    ctx->r10 = S32(0XFCFF << 16);
    // 0x80093FCC: lui         $t3, 0xFFFC
    ctx->r11 = S32(0XFFFC << 16);
    // 0x80093FD0: ori         $t3, $t3, 0xF279
    ctx->r11 = ctx->r11 | 0XF279;
    // 0x80093FD4: ori         $t2, $t2, 0xFFFF
    ctx->r10 = ctx->r10 | 0XFFFF;
    // 0x80093FD8: addiu       $v0, $a3, 0x8
    ctx->r2 = ADD32(ctx->r7, 0X8);
    // 0x80093FDC: sw          $t2, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r10;
    // 0x80093FE0: sw          $t3, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r11;
    // 0x80093FE4: lui         $t4, 0xB900
    ctx->r12 = S32(0XB900 << 16);
    // 0x80093FE8: ori         $t4, $t4, 0x31D
    ctx->r12 = ctx->r12 | 0X31D;
    // 0x80093FEC: addiu       $a0, $v0, 0x8
    ctx->r4 = ADD32(ctx->r2, 0X8);
    // 0x80093FF0: sw          $t4, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r12;
    // 0x80093FF4: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80093FF8: lui         $t5, 0xB900
    ctx->r13 = S32(0XB900 << 16);
    // 0x80093FFC: ori         $t5, $t5, 0x2
    ctx->r13 = ctx->r13 | 0X2;
    // 0x80094000: addiu       $a1, $a0, 0x8
    ctx->r5 = ADD32(ctx->r4, 0X8);
    // 0x80094004: sw          $t5, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r13;
    // 0x80094008: sw          $zero, 0x4($a0)
    MEM_W(0X4, ctx->r4) = 0;
    // 0x8009400C: lui         $t7, 0x6A
    ctx->r15 = S32(0X6A << 16);
    // 0x80094010: addiu       $t7, $t7, -0x3C44
    ctx->r15 = ADD32(ctx->r15, -0X3C44);
    // 0x80094014: lui         $t6, 0xED00
    ctx->r14 = S32(0XED00 << 16);
    // 0x80094018: lui         $t8, 0xFF10
    ctx->r24 = S32(0XFF10 << 16);
    // 0x8009401C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x80094020: sw          $t7, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r15;
    // 0x80094024: addiu       $a2, $a1, 0x8
    ctx->r6 = ADD32(ctx->r5, 0X8);
    // 0x80094028: ori         $t8, $t8, 0x1A7
    ctx->r24 = ctx->r24 | 0X1A7;
    // 0x8009402C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x80094030: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x80094034: lw          $t9, 0x1948($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X1948);
    // 0x80094038: lui         $t1, 0x8015
    ctx->r9 = S32(0X8015 << 16);
    // 0x8009403C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094040: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x80094044: addu        $t1, $t1, $t0
    ctx->r9 = ADD32(ctx->r9, ctx->r8);
    // 0x80094048: lw          $t1, 0x42C0($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X42C0);
    // 0x8009404C: addiu       $a3, $a2, 0x8
    ctx->r7 = ADD32(ctx->r6, 0X8);
    // 0x80094050: lui         $t4, 0x1
    ctx->r12 = S32(0X1 << 16);
    // 0x80094054: addu        $t2, $t1, $at
    ctx->r10 = ADD32(ctx->r9, ctx->r1);
    // 0x80094058: sw          $t2, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r10;
    // 0x8009405C: ori         $t4, $t4, 0x1
    ctx->r12 = ctx->r12 | 0X1;
    // 0x80094060: addiu       $v1, $a3, 0x8
    ctx->r3 = ADD32(ctx->r7, 0X8);
    // 0x80094064: lui         $t3, 0xF700
    ctx->r11 = S32(0XF700 << 16);
    // 0x80094068: lui         $t5, 0xF66A
    ctx->r13 = S32(0XF66A << 16);
    // 0x8009406C: addiu       $t5, $t5, -0x3C44
    ctx->r13 = ADD32(ctx->r13, -0X3C44);
    // 0x80094070: sw          $t3, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r11;
    // 0x80094074: sw          $t4, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r12;
    // 0x80094078: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x8009407C: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x80094080: jr          $ra
    // 0x80094084: addiu       $v0, $v1, 0x8
    ctx->r2 = ADD32(ctx->r3, 0X8);
    return;
    // 0x80094084: addiu       $v0, $v1, 0x8
    ctx->r2 = ADD32(ctx->r3, 0X8);
;}
RECOMP_FUNC void SegmentedToVirtual(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094088: srl         $v1, $a0, 24
    ctx->r3 = S32(U32(ctx->r4) >> 24);
    // 0x8009408C: slti        $at, $v1, 0x10
    ctx->r1 = SIGNED(ctx->r3) < 0X10 ? 1 : 0;
    // 0x80094090: bne         $at, $zero, L_8009409C
    if (ctx->r1 != 0) {
        // 0x80094094: lui         $t7, 0x801D
        ctx->r15 = S32(0X801D << 16);
            goto L_8009409C;
    }
    // 0x80094094: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094098: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_8009409C:
    // 0x8009409C: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x800940A0: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x800940A4: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x800940A8: lw          $t7, -0x1950($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X1950);
    // 0x800940AC: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x800940B0: and         $t8, $a0, $at
    ctx->r24 = ctx->r4 & ctx->r1;
    // 0x800940B4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800940B8: addu        $a1, $t7, $t8
    ctx->r5 = ADD32(ctx->r15, ctx->r24);
    // 0x800940BC: jr          $ra
    // 0x800940C0: addu        $v0, $a1, $at
    ctx->r2 = ADD32(ctx->r5, ctx->r1);
    return;
    // 0x800940C0: addu        $v0, $a1, $at
    ctx->r2 = ADD32(ctx->r5, ctx->r1);
;}
RECOMP_FUNC void func_800940C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800940C4: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800940C8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800940CC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800940D0: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800940D4: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800940D8: addiu       $v0, $v0, -0x54C8
    ctx->r2 = ADD32(ctx->r2, -0X54C8);
    // 0x800940DC: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_800940E0:
    // 0x800940E0: lh          $t6, 0x0($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X0);
    // 0x800940E4: beql        $t6, $zero, L_80094100
    if (ctx->r14 == 0) {
        // 0x800940E8: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_80094100;
    }
    goto skip_0;
    // 0x800940E8: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    skip_0:
    // 0x800940EC: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800940F0: slti        $at, $v1, 0x5
    ctx->r1 = SIGNED(ctx->r3) < 0X5 ? 1 : 0;
    // 0x800940F4: bne         $at, $zero, L_800940E0
    if (ctx->r1 != 0) {
        // 0x800940F8: addiu       $v0, $v0, 0x8
        ctx->r2 = ADD32(ctx->r2, 0X8);
            goto L_800940E0;
    }
    // 0x800940F8: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x800940FC: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
L_80094100:
    // 0x80094100: beq         $v1, $at, L_800941C0
    if (ctx->r3 == ctx->r1) {
        // 0x80094104: addiu       $a1, $zero, 0x1
        ctx->r5 = ADD32(0, 0X1);
            goto L_800941C0;
    }
    // 0x80094104: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80094108: bne         $a3, $a1, L_80094128
    if (ctx->r7 != ctx->r5) {
        // 0x8009410C: sh          $a1, 0x0($v0)
        MEM_H(0X0, ctx->r2) = ctx->r5;
            goto L_80094128;
    }
    // 0x8009410C: sh          $a1, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r5;
    // 0x80094110: sll         $a0, $a2, 2
    ctx->r4 = S32(ctx->r6 << 2);
    // 0x80094114: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80094118: addu        $t7, $t7, $a0
    ctx->r15 = ADD32(ctx->r15, ctx->r4);
    // 0x8009411C: lw          $t7, -0x3968($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X3968);
    // 0x80094120: b           L_8009413C
    // 0x80094124: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
        goto L_8009413C;
    // 0x80094124: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
L_80094128:
    // 0x80094128: sll         $a0, $a2, 2
    ctx->r4 = S32(ctx->r6 << 2);
    // 0x8009412C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80094130: addu        $t8, $t8, $a0
    ctx->r24 = ADD32(ctx->r24, ctx->r4);
    // 0x80094134: lw          $t8, -0x3944($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3944);
    // 0x80094138: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
L_8009413C:
    // 0x8009413C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x80094140: jal         0x80097E68
    // 0x80094144: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    func_80097E68(rdram, ctx);
        goto after_0;
    // 0x80094144: sw          $a3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r7;
    after_0:
    // 0x80094148: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8009414C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80094150: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x80094154: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80094158: lw          $a3, 0x2C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X2C);
    // 0x8009415C: addiu       $v1, $v1, -0x54A0
    ctx->r3 = ADD32(ctx->r3, -0X54A0);
    // 0x80094160: addiu       $v0, $v0, -0x54C8
    ctx->r2 = ADD32(ctx->r2, -0X54C8);
    // 0x80094164: lh          $t9, 0x0($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X0);
L_80094168:
    // 0x80094168: beq         $t9, $zero, L_8009417C
    if (ctx->r25 == 0) {
        // 0x8009416C: nop
    
            goto L_8009417C;
    }
    // 0x8009416C: nop

    // 0x80094170: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x80094174: bnel        $v0, $v1, L_80094168
    if (ctx->r2 != ctx->r3) {
        // 0x80094178: lh          $t9, 0x0($v0)
        ctx->r25 = MEM_H(ctx->r2, 0X0);
            goto L_80094168;
    }
    goto skip_1;
    // 0x80094178: lh          $t9, 0x0($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X0);
    skip_1:
L_8009417C:
    // 0x8009417C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80094180: addiu       $t0, $t0, -0x54A0
    ctx->r8 = ADD32(ctx->r8, -0X54A0);
    // 0x80094184: beql        $v0, $t0, L_800941C4
    if (ctx->r2 == ctx->r8) {
        // 0x80094188: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800941C4;
    }
    goto skip_2;
    // 0x80094188: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x8009418C: bne         $a3, $a1, L_800941A8
    if (ctx->r7 != ctx->r5) {
        // 0x80094190: sh          $a1, 0x0($v0)
        MEM_H(0X0, ctx->r2) = ctx->r5;
            goto L_800941A8;
    }
    // 0x80094190: sh          $a1, 0x0($v0)
    MEM_H(0X0, ctx->r2) = ctx->r5;
    // 0x80094194: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x80094198: addu        $t1, $t1, $a0
    ctx->r9 = ADD32(ctx->r9, ctx->r4);
    // 0x8009419C: lw          $t1, -0x3B10($t1)
    ctx->r9 = MEM_W(ctx->r9, -0X3B10);
    // 0x800941A0: b           L_800941B8
    // 0x800941A4: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
        goto L_800941B8;
    // 0x800941A4: sw          $t1, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r9;
L_800941A8:
    // 0x800941A8: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x800941AC: addu        $t2, $t2, $a0
    ctx->r10 = ADD32(ctx->r10, ctx->r4);
    // 0x800941B0: lw          $t2, -0x3AEC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X3AEC);
    // 0x800941B4: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
L_800941B8:
    // 0x800941B8: jal         0x80097E68
    // 0x800941BC: nop

    func_80097E68(rdram, ctx);
        goto after_1;
    // 0x800941BC: nop

    after_1:
L_800941C0:
    // 0x800941C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800941C4:
    // 0x800941C4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800941C8: jr          $ra
    // 0x800941CC: nop

    return;
    // 0x800941CC: nop

;}
RECOMP_FUNC void Strlen2(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800941D0: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    // 0x800941D4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800941D8: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800941DC: beq         $v0, $zero, L_800941F8
    if (ctx->r2 == 0) {
        // 0x800941E0: nop
    
            goto L_800941F8;
    }
    // 0x800941E0: nop

    // 0x800941E4: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
L_800941E8:
    // 0x800941E8: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800941EC: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    // 0x800941F0: bnel        $v0, $zero, L_800941E8
    if (ctx->r2 != 0) {
        // 0x800941F4: lb          $v0, 0x0($a0)
        ctx->r2 = MEM_B(ctx->r4, 0X0);
            goto L_800941E8;
    }
    goto skip_0;
    // 0x800941F4: lb          $v0, 0x0($a0)
    ctx->r2 = MEM_B(ctx->r4, 0X0);
    skip_0:
L_800941F8:
    // 0x800941F8: jr          $ra
    // 0x800941FC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
    return;
    // 0x800941FC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
;}
RECOMP_FUNC void func_80094200(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094200: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x80094204: sw          $s5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r21;
    // 0x80094208: or          $s5, $a0, $zero
    ctx->r21 = ctx->r4 | 0;
    // 0x8009420C: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x80094210: sw          $fp, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r30;
    // 0x80094214: sw          $s7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r23;
    // 0x80094218: sw          $s6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r22;
    // 0x8009421C: sw          $s4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r20;
    // 0x80094220: sw          $s3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r19;
    // 0x80094224: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x80094228: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x8009422C: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x80094230: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x80094234: addiu       $v0, $zero, 0xC
    ctx->r2 = ADD32(0, 0XC);
    // 0x80094238: bne         $a1, $zero, L_80094244
    if (ctx->r5 != 0) {
        // 0x8009423C: or          $t6, $a1, $zero
        ctx->r14 = ctx->r5 | 0;
            goto L_80094244;
    }
    // 0x8009423C: or          $t6, $a1, $zero
    ctx->r14 = ctx->r5 | 0;
    // 0x80094240: addiu       $v0, $zero, 0x12
    ctx->r2 = ADD32(0, 0X12);
L_80094244:
    // 0x80094244: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x80094248: lui         $fp, 0x800F
    ctx->r30 = S32(0X800F << 16);
    // 0x8009424C: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x80094250: addiu       $fp, $fp, -0x538C
    ctx->r30 = ADD32(ctx->r30, -0X538C);
    // 0x80094254: addu        $s2, $t7, $a3
    ctx->r18 = ADD32(ctx->r15, ctx->r7);
    // 0x80094258: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x8009425C: negu        $s6, $v0
    ctx->r22 = SUB32(0, ctx->r2);
    // 0x80094260: lw          $s7, 0x70($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X70);
    // 0x80094264: addiu       $s4, $zero, 0xA
    ctx->r20 = ADD32(0, 0XA);
    // 0x80094268: addiu       $s3, $sp, 0x50
    ctx->r19 = ADD32(ctx->r29, 0X50);
L_8009426C:
    // 0x8009426C: div         $zero, $s0, $s4
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r20))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r20)));
    // 0x80094270: mfhi        $a2
    ctx->r6 = hi;
    // 0x80094274: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    // 0x80094278: or          $a1, $fp, $zero
    ctx->r5 = ctx->r30 | 0;
    // 0x8009427C: bne         $s4, $zero, L_80094288
    if (ctx->r20 != 0) {
        // 0x80094280: nop
    
            goto L_80094288;
    }
    // 0x80094280: nop

    // 0x80094284: break       7
    do_break(2148090500);
L_80094288:
    // 0x80094288: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8009428C: bne         $s4, $at, L_800942A0
    if (ctx->r20 != ctx->r1) {
        // 0x80094290: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800942A0;
    }
    // 0x80094290: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094294: bne         $s0, $at, L_800942A0
    if (ctx->r16 != ctx->r1) {
        // 0x80094298: nop
    
            goto L_800942A0;
    }
    // 0x80094298: nop

    // 0x8009429C: break       6
    do_break(2148090524);
L_800942A0:
    // 0x800942A0: jal         0x800CA210
    // 0x800942A4: nop

    func_800CA210(rdram, ctx);
        goto after_0;
    // 0x800942A4: nop

    after_0:
    // 0x800942A8: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    // 0x800942AC: lw          $a1, 0x64($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X64);
    // 0x800942B0: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
    // 0x800942B4: or          $a3, $s2, $zero
    ctx->r7 = ctx->r18 | 0;
    // 0x800942B8: jal         0x801E9858
    // 0x800942BC: sw          $s7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r23;
    func_801E9858(rdram, ctx);
        goto after_1;
    // 0x800942BC: sw          $s7, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r23;
    after_1:
    // 0x800942C0: div         $zero, $s0, $s4
    lo = S32(S64(S32(ctx->r16)) / S64(S32(ctx->r20))); hi = S32(S64(S32(ctx->r16)) % S64(S32(ctx->r20)));
    // 0x800942C4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x800942C8: addu        $s2, $s2, $s6
    ctx->r18 = ADD32(ctx->r18, ctx->r22);
    // 0x800942CC: or          $s5, $v0, $zero
    ctx->r21 = ctx->r2 | 0;
    // 0x800942D0: bne         $s4, $zero, L_800942DC
    if (ctx->r20 != 0) {
        // 0x800942D4: nop
    
            goto L_800942DC;
    }
    // 0x800942D4: nop

    // 0x800942D8: break       7
    do_break(2148090584);
L_800942DC:
    // 0x800942DC: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800942E0: bne         $s4, $at, L_800942F4
    if (ctx->r20 != ctx->r1) {
        // 0x800942E4: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800942F4;
    }
    // 0x800942E4: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800942E8: bne         $s0, $at, L_800942F4
    if (ctx->r16 != ctx->r1) {
        // 0x800942EC: nop
    
            goto L_800942F4;
    }
    // 0x800942EC: nop

    // 0x800942F0: break       6
    do_break(2148090608);
L_800942F4:
    // 0x800942F4: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800942F8: mflo        $s0
    ctx->r16 = lo;
    // 0x800942FC: bne         $s1, $at, L_8009426C
    if (ctx->r17 != ctx->r1) {
        // 0x80094300: nop
    
            goto L_8009426C;
    }
    // 0x80094300: nop

    // 0x80094304: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x80094308: or          $v0, $s5, $zero
    ctx->r2 = ctx->r21 | 0;
    // 0x8009430C: lw          $s5, 0x34($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X34);
    // 0x80094310: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x80094314: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x80094318: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x8009431C: lw          $s3, 0x2C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X2C);
    // 0x80094320: lw          $s4, 0x30($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X30);
    // 0x80094324: lw          $s6, 0x38($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X38);
    // 0x80094328: lw          $s7, 0x3C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X3C);
    // 0x8009432C: lw          $fp, 0x40($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X40);
    // 0x80094330: jr          $ra
    // 0x80094334: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x80094334: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC /* WR64 Waku frame builder. The historical SUNEXIT-R5 attribution
   of this function to the sun was incorrect. Its 0x228 right comparisons
   remain at native16:9 for compatibility; config/us.rev1.toml provides the
   dynamic consumer hooks and signed ultrawide frame packets below. */
void func_80094338(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // WR64 MENU ULTRAWIDE: this is the shared Waku frame builder, not a sun
    // sprite. Keep the original display list byte-for-byte at native16:9.
    extern int32_t wr64_menu_half_extension(void);
    extern void wr64_menu_promote_waku_rect(uint8_t*, uint32_t, int32_t, int32_t);
    const int32_t wr64MenuHalf = wr64_menu_half_extension();
    const int32_t wr64MenuX = (int32_t)ctx->r6;
    const int32_t wr64MenuWidth = MEM_W(0x10, ctx->r29);
    // 0x80094338: addiu       $sp, $sp, -0xA8
    ctx->r29 = ADD32(ctx->r29, -0XA8);
    // 0x8009433C: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x80094340: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x80094344: sw          $s3, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r19;
    // 0x80094348: sw          $s2, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r18;
    // 0x8009434C: beq         $a1, $zero, L_80094380
    if (ctx->r5 == 0) {
        // 0x80094350: sw          $s1, 0xC($sp)
        MEM_W(0XC, ctx->r29) = ctx->r17;
            goto L_80094380;
    }
    // 0x80094350: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x80094354: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80094358: beq         $a1, $at, L_800944AC
    if (ctx->r5 == ctx->r1) {
        // 0x8009435C: lw          $t0, 0xB8($sp)
        ctx->r8 = MEM_W(ctx->r29, 0XB8);
            goto L_800944AC;
    }
    // 0x8009435C: lw          $t0, 0xB8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XB8);
    // 0x80094360: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80094364: beq         $a1, $at, L_8009441C
    if (ctx->r5 == ctx->r1) {
        // 0x80094368: lw          $t0, 0xB8($sp)
        ctx->r8 = MEM_W(ctx->r29, 0XB8);
            goto L_8009441C;
    }
    // 0x80094368: lw          $t0, 0xB8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XB8);
    // 0x8009436C: lw          $t1, 0xBC($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XBC);
    // 0x80094370: lw          $t0, 0xB8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XB8);
    // 0x80094374: lw          $a1, 0x90($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X90);
    // 0x80094378: b           L_8009453C
    // 0x8009437C: lw          $a0, 0x98($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X98);
        goto L_8009453C;
    // 0x8009437C: lw          $a0, 0x98($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X98);
L_80094380:
    // 0x80094380: lw          $t0, 0xB8($sp)
    ctx->r8 = MEM_W(ctx->r29, 0XB8);
    // 0x80094384: addiu       $t6, $zero, 0x4
    ctx->r14 = ADD32(0, 0X4);
    // 0x80094388: sw          $t6, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r14;
    // 0x8009438C: lui         $t6, 0x4
    ctx->r14 = S32(0X4 << 16);
    // 0x80094390: div         $zero, $t6, $t0
    lo = S32(S64(S32(ctx->r14)) / S64(S32(ctx->r8))); hi = S32(S64(S32(ctx->r14)) % S64(S32(ctx->r8)));
    // 0x80094394: lui         $t7, 0x105
    ctx->r15 = S32(0X105 << 16);
    // 0x80094398: addiu       $t7, $t7, 0x15A8
    ctx->r15 = ADD32(ctx->r15, 0X15A8);
    // 0x8009439C: sw          $t7, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r15;
    // 0x800943A0: lw          $t1, 0xBC($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XBC);
    // 0x800943A4: ori         $t7, $zero, 0x8000
    ctx->r15 = 0 | 0X8000;
    // 0x800943A8: mflo        $a1
    ctx->r5 = lo;
    // 0x800943AC: addiu       $t8, $zero, 0x100
    ctx->r24 = ADD32(0, 0X100);
    // 0x800943B0: sw          $t8, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r24;
    // 0x800943B4: div         $zero, $t7, $t1
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r9)));
    // 0x800943B8: addiu       $t9, $zero, 0x8
    ctx->r25 = ADD32(0, 0X8);
    // 0x800943BC: mflo        $t8
    ctx->r24 = lo;
    // 0x800943C0: sw          $t9, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r25;
    // 0x800943C4: bne         $t0, $zero, L_800943D0
    if (ctx->r8 != 0) {
        // 0x800943C8: nop
    
            goto L_800943D0;
    }
    // 0x800943C8: nop

    // 0x800943CC: break       7
    do_break(2148090828);
L_800943D0:
    // 0x800943D0: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800943D4: bne         $t0, $at, L_800943E8
    if (ctx->r8 != ctx->r1) {
        // 0x800943D8: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800943E8;
    }
    // 0x800943D8: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800943DC: bne         $t6, $at, L_800943E8
    if (ctx->r14 != ctx->r1) {
        // 0x800943E0: nop
    
            goto L_800943E8;
    }
    // 0x800943E0: nop

    // 0x800943E4: break       6
    do_break(2148090852);
L_800943E8:
    // 0x800943E8: sw          $t8, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->r24;
    // 0x800943EC: bne         $t1, $zero, L_800943F8
    if (ctx->r9 != 0) {
        // 0x800943F0: nop
    
            goto L_800943F8;
    }
    // 0x800943F0: nop

    // 0x800943F4: break       7
    do_break(2148090868);
L_800943F8:
    // 0x800943F8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800943FC: bne         $t1, $at, L_80094410
    if (ctx->r9 != ctx->r1) {
        // 0x80094400: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80094410;
    }
    // 0x80094400: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094404: bne         $t7, $at, L_80094410
    if (ctx->r15 != ctx->r1) {
        // 0x80094408: nop
    
            goto L_80094410;
    }
    // 0x80094408: nop

    // 0x8009440C: break       6
    do_break(2148090892);
L_80094410:
    // 0x80094410: addiu       $a0, $zero, 0x100
    ctx->r4 = ADD32(0, 0X100);
    // 0x80094414: b           L_80094540
    // 0x80094418: slti        $at, $a2, 0x1A8
    ctx->r1 = SIGNED(ctx->r6) < 0X228 ? 1 : 0; /* WR64 SUNEXIT-R5 */
        goto L_80094540;
    // 0x80094418: slti        $at, $a2, 0x1A8
    ctx->r1 = SIGNED(ctx->r6) < 0X228 ? 1 : 0; /* WR64 SUNEXIT-R5 */
L_8009441C:
    // 0x8009441C: lui         $t8, 0x4
    ctx->r24 = S32(0X4 << 16);
    // 0x80094420: div         $zero, $t8, $t0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r8))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r8)));
    // 0x80094424: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x80094428: sw          $t9, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r25;
    // 0x8009442C: lw          $t1, 0xBC($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XBC);
    // 0x80094430: ori         $t9, $zero, 0x8000
    ctx->r25 = 0 | 0X8000;
    // 0x80094434: mflo        $a1
    ctx->r5 = lo;
    // 0x80094438: lui         $t6, 0x105
    ctx->r14 = S32(0X105 << 16);
    // 0x8009443C: addiu       $t6, $t6, 0x65B8
    ctx->r14 = ADD32(ctx->r14, 0X65B8);
    // 0x80094440: div         $zero, $t9, $t1
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r9)));
    // 0x80094444: sw          $t6, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r14;
    // 0x80094448: addiu       $t7, $zero, 0x8
    ctx->r15 = ADD32(0, 0X8);
    // 0x8009444C: mflo        $t6
    ctx->r14 = lo;
    // 0x80094450: addiu       $a0, $zero, 0x100
    ctx->r4 = ADD32(0, 0X100);
    // 0x80094454: sw          $t7, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r15;
    // 0x80094458: bne         $t0, $zero, L_80094464
    if (ctx->r8 != 0) {
        // 0x8009445C: nop
    
            goto L_80094464;
    }
    // 0x8009445C: nop

    // 0x80094460: break       7
    do_break(2148090976);
L_80094464:
    // 0x80094464: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80094468: bne         $t0, $at, L_8009447C
    if (ctx->r8 != ctx->r1) {
        // 0x8009446C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009447C;
    }
    // 0x8009446C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094470: bne         $t8, $at, L_8009447C
    if (ctx->r24 != ctx->r1) {
        // 0x80094474: nop
    
            goto L_8009447C;
    }
    // 0x80094474: nop

    // 0x80094478: break       6
    do_break(2148091000);
L_8009447C:
    // 0x8009447C: sw          $t6, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->r14;
    // 0x80094480: bne         $t1, $zero, L_8009448C
    if (ctx->r9 != 0) {
        // 0x80094484: nop
    
            goto L_8009448C;
    }
    // 0x80094484: nop

    // 0x80094488: break       7
    do_break(2148091016);
L_8009448C:
    // 0x8009448C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80094490: bne         $t1, $at, L_800944A4
    if (ctx->r9 != ctx->r1) {
        // 0x80094494: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800944A4;
    }
    // 0x80094494: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094498: bne         $t9, $at, L_800944A4
    if (ctx->r25 != ctx->r1) {
        // 0x8009449C: nop
    
            goto L_800944A4;
    }
    // 0x8009449C: nop

    // 0x800944A0: break       6
    do_break(2148091040);
L_800944A4:
    // 0x800944A4: b           L_80094540
    // 0x800944A8: slti        $at, $a2, 0x140
    ctx->r1 = SIGNED(ctx->r6) < 0X228 ? 1 : 0; /* WR64 SUNEXIT-R5 (was 320) */
        goto L_80094540;
    // 0x800944A8: slti        $at, $a2, 0x140
    ctx->r1 = SIGNED(ctx->r6) < 0X228 ? 1 : 0; /* WR64 SUNEXIT-R5 (was 320) */
L_800944AC:
    // 0x800944AC: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800944B0: sw          $t7, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r15;
    // 0x800944B4: lui         $t7, 0x1
    ctx->r15 = S32(0X1 << 16);
    // 0x800944B8: div         $zero, $t7, $t0
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r8))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r8)));
    // 0x800944BC: lui         $t8, 0x105
    ctx->r24 = S32(0X105 << 16);
    // 0x800944C0: addiu       $t8, $t8, 0x55B0
    ctx->r24 = ADD32(ctx->r24, 0X55B0);
    // 0x800944C4: sw          $t8, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->r24;
    // 0x800944C8: lw          $t1, 0xBC($sp)
    ctx->r9 = MEM_W(ctx->r29, 0XBC);
    // 0x800944CC: ori         $t8, $zero, 0x8000
    ctx->r24 = 0 | 0X8000;
    // 0x800944D0: mflo        $a1
    ctx->r5 = lo;
    // 0x800944D4: addiu       $t9, $zero, 0x40
    ctx->r25 = ADD32(0, 0X40);
    // 0x800944D8: sw          $t9, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r25;
    // 0x800944DC: div         $zero, $t8, $t1
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r9))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r9)));
    // 0x800944E0: mflo        $t9
    ctx->r25 = lo;
    // 0x800944E4: addiu       $t6, $zero, 0x20
    ctx->r14 = ADD32(0, 0X20);
    // 0x800944E8: sw          $t6, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->r14;
    // 0x800944EC: bne         $t0, $zero, L_800944F8
    if (ctx->r8 != 0) {
        // 0x800944F0: nop
    
            goto L_800944F8;
    }
    // 0x800944F0: nop

    // 0x800944F4: break       7
    do_break(2148091124);
L_800944F8:
    // 0x800944F8: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800944FC: bne         $t0, $at, L_80094510
    if (ctx->r8 != ctx->r1) {
        // 0x80094500: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80094510;
    }
    // 0x80094500: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094504: bne         $t7, $at, L_80094510
    if (ctx->r15 != ctx->r1) {
        // 0x80094508: nop
    
            goto L_80094510;
    }
    // 0x80094508: nop

    // 0x8009450C: break       6
    do_break(2148091148);
L_80094510:
    // 0x80094510: sw          $t9, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->r25;
    // 0x80094514: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
    // 0x80094518: bne         $t1, $zero, L_80094524
    if (ctx->r9 != 0) {
        // 0x8009451C: nop
    
            goto L_80094524;
    }
    // 0x8009451C: nop

    // 0x80094520: break       7
    do_break(2148091168);
L_80094524:
    // 0x80094524: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x80094528: bne         $t1, $at, L_8009453C
    if (ctx->r9 != ctx->r1) {
        // 0x8009452C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_8009453C;
    }
    // 0x8009452C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094530: bne         $t8, $at, L_8009453C
    if (ctx->r24 != ctx->r1) {
        // 0x80094534: nop
    
            goto L_8009453C;
    }
    // 0x80094534: nop

    // 0x80094538: break       6
    do_break(2148091192);
L_8009453C:
    // 0x8009453C: slti        $at, $a2, 0x1A8
    ctx->r1 = SIGNED(ctx->r6) < 0X228 ? 1 : 0; /* WR64 SUNEXIT-R5 */
L_80094540:
    { extern int32_t wr64_sun_horizontal_cull_limit(void); ctx->r1 = SIGNED(ctx->r6) < wr64_sun_horizontal_cull_limit() ? 1 : 0; } /* WR64 ULTRAWIDE */
    if (wr64MenuHalf > 0) ctx->r1 = wr64MenuX < 424 + wr64MenuHalf;
    // 0x80094540: bne         $at, $zero, L_80094550
    if (ctx->r1 != 0) {
        // 0x80094544: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_80094550;
    }
    // 0x80094544: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80094548: b           L_80094580
    // 0x8009454C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_80094580;
    // 0x8009454C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80094550:
    // 0x80094550: addu        $t6, $a2, $t0
    ctx->r14 = ADD32(ctx->r6, ctx->r8);
    if (wr64MenuHalf > 0) ctx->r14 = ADD32(ctx->r14, wr64MenuHalf);
    // 0x80094554: bgez        $t6, L_80094564
    if (SIGNED(ctx->r14) >= 0) {
        // 0x80094558: slti        $at, $a3, 0xF0
        ctx->r1 = SIGNED(ctx->r7) < 0XF0 ? 1 : 0;
            goto L_80094564;
    }
    // 0x80094558: slti        $at, $a3, 0xF0
    ctx->r1 = SIGNED(ctx->r7) < 0XF0 ? 1 : 0;
    // 0x8009455C: b           L_80094580
    // 0x80094560: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_80094580;
    // 0x80094560: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80094564:
    // 0x80094564: bne         $at, $zero, L_80094574
    if (ctx->r1 != 0) {
        // 0x80094568: addu        $t7, $a3, $t1
        ctx->r15 = ADD32(ctx->r7, ctx->r9);
            goto L_80094574;
    }
    // 0x80094568: addu        $t7, $a3, $t1
    ctx->r15 = ADD32(ctx->r7, ctx->r9);
    // 0x8009456C: b           L_80094580
    // 0x80094570: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_80094580;
    // 0x80094570: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80094574:
    // 0x80094574: bgez        $t7, L_80094580
    if (SIGNED(ctx->r15) >= 0) {
        // 0x80094578: nop
    
            goto L_80094580;
    }
    // 0x80094578: nop

    // 0x8009457C: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80094580:
    // 0x80094580: bne         $v0, $zero, L_80094590
    if (ctx->r2 != 0) {
        // 0x80094584: lw          $t8, 0xA0($sp)
        ctx->r24 = MEM_W(ctx->r29, 0XA0);
            goto L_80094590;
    }
    // 0x80094584: lw          $t8, 0xA0($sp)
    ctx->r24 = MEM_W(ctx->r29, 0XA0);
    // 0x80094588: b           L_800948C4
    // 0x8009458C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
        goto L_800948C4;
    // 0x8009458C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_80094590:
    // 0x80094590: blez        $t8, L_800948C0
    if (SIGNED(ctx->r24) <= 0) {
        // 0x80094594: or          $t2, $zero, $zero
        ctx->r10 = 0 | 0;
            goto L_800948C0;
    }
    // 0x80094594: or          $t2, $zero, $zero
    ctx->r10 = 0 | 0;
    // 0x80094598: mtc1        $t8, $f10
    ctx->f10.u32l = ctx->r24;
    // 0x8009459C: lw          $t9, 0x94($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X94);
    // 0x800945A0: mtc1        $t1, $f6
    ctx->f6.u32l = ctx->r9;
    // 0x800945A4: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800945A8: multu       $a0, $t9
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800945AC: mtc1        $a3, $f4
    ctx->f4.u32l = ctx->r7;
    // 0x800945B0: sll         $v1, $a0, 1
    ctx->r3 = S32(ctx->r4 << 1);
    // 0x800945B4: addiu       $t6, $v1, 0x7
    ctx->r14 = ADD32(ctx->r3, 0X7);
    // 0x800945B8: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800945BC: sra         $t7, $t6, 3
    ctx->r15 = S32(SIGNED(ctx->r14) >> 3);
    // 0x800945C0: andi        $t8, $t7, 0x1FF
    ctx->r24 = ctx->r15 & 0X1FF;
    // 0x800945C4: sll         $t6, $t8, 9
    ctx->r14 = S32(ctx->r24 << 9);
    // 0x800945C8: addiu       $t8, $a0, -0x1
    ctx->r24 = ADD32(ctx->r4, -0X1);
    // 0x800945CC: cvt.s.w     $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    ctx->f0.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800945D0: mflo        $v0
    ctx->r2 = lo;
    // 0x800945D4: addu        $s1, $a2, $t0
    ctx->r17 = ADD32(ctx->r6, ctx->r8);
    // 0x800945D8: or          $t4, $zero, $zero
    ctx->r12 = 0 | 0;
    // 0x800945DC: addiu       $t5, $v0, -0x1
    ctx->r13 = ADD32(ctx->r2, -0X1);
    // 0x800945E0: div.s       $f2, $f8, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f8.fl, ctx->f16.fl);
    // 0x800945E4: bgez        $v1, L_800945F4
    if (SIGNED(ctx->r3) >= 0) {
        // 0x800945E8: sra         $t3, $v1, 3
        ctx->r11 = S32(SIGNED(ctx->r3) >> 3);
            goto L_800945F4;
    }
    // 0x800945E8: sra         $t3, $v1, 3
    ctx->r11 = S32(SIGNED(ctx->r3) >> 3);
    // 0x800945EC: addiu       $at, $v1, 0x7
    ctx->r1 = ADD32(ctx->r3, 0X7);
    // 0x800945F0: sra         $t3, $at, 3
    ctx->r11 = S32(SIGNED(ctx->r1) >> 3);
L_800945F4:
    // 0x800945F4: lui         $at, 0xF510
    ctx->r1 = S32(0XF510 << 16);
    // 0x800945F8: or          $t7, $t6, $at
    ctx->r15 = ctx->r14 | ctx->r1;
    // 0x800945FC: sw          $t7, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r15;
    // 0x80094600: sll         $t6, $t8, 2
    ctx->r14 = S32(ctx->r24 << 2);
    // 0x80094604: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x80094608: sll         $t8, $t7, 12
    ctx->r24 = S32(ctx->r15 << 12);
    // 0x8009460C: addiu       $t6, $t9, -0x1
    ctx->r14 = ADD32(ctx->r25, -0X1);
    // 0x80094610: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80094614: andi        $t9, $t7, 0xFFF
    ctx->r25 = ctx->r15 & 0XFFF;
    // 0x80094618: or          $t6, $t8, $t9
    ctx->r14 = ctx->r24 | ctx->r25;
    // 0x8009461C: sll         $t8, $a1, 1
    ctx->r24 = S32(ctx->r5 << 1);
    // 0x80094620: sllv        $s3, $a2, $t8
    ctx->r19 = S32(ctx->r6 << (ctx->r24 & 31));
    // 0x80094624: lw          $t8, 0x8C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X8C);
    // 0x80094628: sll         $t7, $s1, 2
    ctx->r15 = S32(ctx->r17 << 2);
    // 0x8009462C: sra         $t9, $s3, 7
    ctx->r25 = S32(SIGNED(ctx->r19) >> 7);
    // 0x80094630: or          $s1, $t7, $zero
    ctx->r17 = ctx->r15 | 0;
    // 0x80094634: or          $s3, $t9, $zero
    ctx->r19 = ctx->r25 | 0;
    // 0x80094638: sw          $t6, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r14;
    // 0x8009463C: sll         $t7, $a1, 16
    ctx->r15 = S32(ctx->r5 << 16);
    // 0x80094640: andi        $t9, $t8, 0xFFFF
    ctx->r25 = ctx->r24 & 0XFFFF;
    // 0x80094644: lui         $at, 0x4080
    ctx->r1 = S32(0X4080 << 16);
    // 0x80094648: mtc1        $at, $f14
    ctx->f14.u32l = ctx->r1;
    // 0x8009464C: or          $t6, $t7, $t9
    ctx->r14 = ctx->r15 | ctx->r25;
    // 0x80094650: sll         $s2, $a2, 2
    ctx->r18 = S32(ctx->r6 << 2);
    // 0x80094654: sw          $t6, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r14;
    // 0x80094658: sw          $a0, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->r4;
    // 0x8009465C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_80094660:
    // 0x80094660: lui         $t8, 0xFD10
    ctx->r24 = S32(0XFD10 << 16);
    // 0x80094664: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x80094668: lw          $t9, 0x80($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X80);
    // 0x8009466C: sll         $t7, $t4, 1
    ctx->r15 = S32(ctx->r12 << 1);
    // 0x80094670: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094674: addu        $t6, $t7, $t9
    ctx->r14 = ADD32(ctx->r15, ctx->r25);
    // 0x80094678: sw          $t6, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r14;
    // 0x8009467C: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x80094680: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094684: lui         $t7, 0x708
    ctx->r15 = S32(0X708 << 16);
    // 0x80094688: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x8009468C: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    // 0x80094690: lui         $t8, 0xF510
    ctx->r24 = S32(0XF510 << 16);
    // 0x80094694: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80094698: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x8009469C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x800946A0: lui         $t9, 0xE600
    ctx->r25 = S32(0XE600 << 16);
    // 0x800946A4: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x800946A8: or          $t0, $s0, $zero
    ctx->r8 = ctx->r16 | 0;
    // 0x800946AC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x800946B0: lui         $t6, 0xF300
    ctx->r14 = S32(0XF300 << 16);
    // 0x800946B4: slti        $at, $t5, 0x7FF
    ctx->r1 = SIGNED(ctx->r13) < 0X7FF ? 1 : 0;
    // 0x800946B8: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x800946BC: beq         $at, $zero, L_800946CC
    if (ctx->r1 == 0) {
        // 0x800946C0: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_800946CC;
    }
    // 0x800946C0: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x800946C4: b           L_800946D0
    // 0x800946C8: or          $a3, $t5, $zero
    ctx->r7 = ctx->r13 | 0;
        goto L_800946D0;
    // 0x800946C8: or          $a3, $t5, $zero
    ctx->r7 = ctx->r13 | 0;
L_800946CC:
    // 0x800946CC: addiu       $a3, $zero, 0x7FF
    ctx->r7 = ADD32(0, 0X7FF);
L_800946D0:
    // 0x800946D0: bgtz        $t3, L_800946E0
    if (SIGNED(ctx->r11) > 0) {
        // 0x800946D4: or          $v1, $s0, $zero
        ctx->r3 = ctx->r16 | 0;
            goto L_800946E0;
    }
    // 0x800946D4: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x800946D8: b           L_800946E4
    // 0x800946DC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_800946E4;
    // 0x800946DC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_800946E0:
    // 0x800946E0: or          $a2, $t3, $zero
    ctx->r6 = ctx->r11 | 0;
L_800946E4:
    // 0x800946E4: bgtz        $t3, L_800946F4
    if (SIGNED(ctx->r11) > 0) {
        // 0x800946E8: addiu       $t8, $a2, 0x7FF
        ctx->r24 = ADD32(ctx->r6, 0X7FF);
            goto L_800946F4;
    }
    // 0x800946E8: addiu       $t8, $a2, 0x7FF
    ctx->r24 = ADD32(ctx->r6, 0X7FF);
    // 0x800946EC: b           L_800946F8
    // 0x800946F0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_800946F8;
    // 0x800946F0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_800946F4:
    // 0x800946F4: or          $v0, $t3, $zero
    ctx->r2 = ctx->r11 | 0;
L_800946F8:
    // 0x800946F8: div         $zero, $t8, $v0
    lo = S32(S64(S32(ctx->r24)) / S64(S32(ctx->r2))); hi = S32(S64(S32(ctx->r24)) % S64(S32(ctx->r2)));
    // 0x800946FC: bne         $v0, $zero, L_80094708
    if (ctx->r2 != 0) {
        // 0x80094700: nop
    
            goto L_80094708;
    }
    // 0x80094700: nop

    // 0x80094704: break       7
    do_break(2148091652);
L_80094708:
    // 0x80094708: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8009470C: bne         $v0, $at, L_80094720
    if (ctx->r2 != ctx->r1) {
        // 0x80094710: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_80094720;
    }
    // 0x80094710: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x80094714: bne         $t8, $at, L_80094720
    if (ctx->r24 != ctx->r1) {
        // 0x80094718: nop
    
            goto L_80094720;
    }
    // 0x80094718: nop

    // 0x8009471C: break       6
    do_break(2148091676);
L_80094720:
    // 0x80094720: mflo        $t7
    ctx->r15 = lo;
    // 0x80094724: andi        $t9, $t7, 0xFFF
    ctx->r25 = ctx->r15 & 0XFFF;
    // 0x80094728: lui         $at, 0x700
    ctx->r1 = S32(0X700 << 16);
    // 0x8009472C: andi        $t8, $a3, 0xFFF
    ctx->r24 = ctx->r7 & 0XFFF;
    // 0x80094730: sll         $t7, $t8, 12
    ctx->r15 = S32(ctx->r24 << 12);
    // 0x80094734: or          $t6, $t9, $at
    ctx->r14 = ctx->r25 | ctx->r1;
    // 0x80094738: or          $t9, $t6, $t7
    ctx->r25 = ctx->r14 | ctx->r15;
    // 0x8009473C: sw          $t9, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r25;
    // 0x80094740: lui         $t8, 0xE700
    ctx->r24 = S32(0XE700 << 16);
    // 0x80094744: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80094748: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x8009474C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094750: lw          $t6, 0x2C($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X2C);
    // 0x80094754: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80094758: lui         $t7, 0x8
    ctx->r15 = S32(0X8 << 16);
    // 0x8009475C: ori         $t7, $t7, 0x200
    ctx->r15 = ctx->r15 | 0X200;
    // 0x80094760: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094764: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80094768: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x8009476C: lui         $t9, 0xF200
    ctx->r25 = S32(0XF200 << 16);
    // 0x80094770: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80094774: sw          $t9, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r25;
    // 0x80094778: lw          $t8, 0x28($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X28);
    // 0x8009477C: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094780: or          $t1, $s0, $zero
    ctx->r9 = ctx->r16 | 0;
    // 0x80094784: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80094788: blez        $s1, L_80094798
    if (SIGNED(ctx->r17) <= 0) {
        // 0x8009478C: sw          $t8, 0x4($a1)
        MEM_W(0X4, ctx->r5) = ctx->r24;
            goto L_80094798;
    }
    // 0x8009478C: sw          $t8, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r24;
    // 0x80094790: b           L_8009479C
    // 0x80094794: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
        goto L_8009479C;
    // 0x80094794: or          $a2, $s1, $zero
    ctx->r6 = ctx->r17 | 0;
L_80094798:
    // 0x80094798: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_8009479C:
    // 0x8009479C: mtc1        $t2, $f18
    ctx->f18.u32l = ctx->r10;
    // 0x800947A0: andi        $t8, $a2, 0xFFF
    ctx->r24 = ctx->r6 & 0XFFF;
    // 0x800947A4: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x800947A8: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800947AC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x800947B0: sll         $t6, $t8, 12
    ctx->r14 = S32(ctx->r24 << 12);
    // 0x800947B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800947B8: lui         $at, 0xE400
    ctx->r1 = S32(0XE400 << 16);
    // 0x800947BC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800947C0: mul.s       $f6, $f2, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // 0x800947C4: add.s       $f12, $f0, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f0.fl + ctx->f6.fl;
    // 0x800947C8: add.s       $f10, $f12, $f2
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f10.fl = ctx->f12.fl + ctx->f2.fl;
    // 0x800947CC: mul.s       $f8, $f10, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = MUL_S(ctx->f10.fl, ctx->f14.fl);
    // 0x800947D0: trunc.w.s   $f16, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    ctx->f16.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800947D4: mul.s       $f18, $f12, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f12.fl, ctx->f14.fl);
    // 0x800947D8: mfc1        $v1, $f16
    ctx->r3 = (int32_t)ctx->f16.u32l;
    // 0x800947DC: nop

    // 0x800947E0: blez        $v1, L_800947F0
    if (SIGNED(ctx->r3) <= 0) {
        // 0x800947E4: trunc.w.s   $f4, $f18
        CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
            goto L_800947F0;
    }
    // 0x800947E4: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x800947E8: b           L_800947F0
    // 0x800947EC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
        goto L_800947F0;
    // 0x800947EC: or          $v0, $v1, $zero
    ctx->r2 = ctx->r3 | 0;
L_800947F0:
    // 0x800947F0: andi        $t7, $v0, 0xFFF
    ctx->r15 = ctx->r2 & 0XFFF;
    // 0x800947F4: or          $t9, $t7, $at
    ctx->r25 = ctx->r15 | ctx->r1;
    // 0x800947F8: or          $t7, $t9, $t6
    ctx->r15 = ctx->r25 | ctx->r14;
    // 0x800947FC: blez        $s2, L_8009480C
    if (SIGNED(ctx->r18) <= 0) {
        // 0x80094800: sw          $t7, 0x0($t1)
        MEM_W(0X0, ctx->r9) = ctx->r15;
            goto L_8009480C;
    }
    // 0x80094800: sw          $t7, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r15;
    // 0x80094804: b           L_8009480C
    // 0x80094808: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
        goto L_8009480C;
    // 0x80094808: or          $a2, $s2, $zero
    ctx->r6 = ctx->r18 | 0;
L_8009480C:
    // 0x8009480C: mfc1        $a0, $f4
    ctx->r4 = (int32_t)ctx->f4.u32l;
    // 0x80094810: andi        $t6, $a2, 0xFFF
    ctx->r14 = ctx->r6 & 0XFFF;
    // 0x80094814: sll         $t7, $t6, 12
    ctx->r15 = S32(ctx->r14 << 12);
    // 0x80094818: blez        $a0, L_80094828
    if (SIGNED(ctx->r4) <= 0) {
        // 0x8009481C: lui         $t6, 0xB300
        ctx->r14 = S32(0XB300 << 16);
            goto L_80094828;
    }
    // 0x8009481C: lui         $t6, 0xB300
    ctx->r14 = S32(0XB300 << 16);
    // 0x80094820: b           L_8009482C
    // 0x80094824: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
        goto L_8009482C;
    // 0x80094824: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
L_80094828:
    // 0x80094828: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8009482C:
    // 0x8009482C: andi        $t9, $v0, 0xFFF
    ctx->r25 = ctx->r2 & 0XFFF;
    // 0x80094830: or          $t8, $t9, $t7
    ctx->r24 = ctx->r25 | ctx->r15;
    // 0x80094834: sw          $t8, 0x4($t1)
    MEM_W(0X4, ctx->r9) = ctx->r24;
    // 0x80094838: bgez        $s3, L_80094848
    if (SIGNED(ctx->r19) >= 0) {
        // 0x8009483C: sw          $t6, 0x0($a1)
        MEM_W(0X0, ctx->r5) = ctx->r14;
            goto L_80094848;
    }
    // 0x8009483C: sw          $t6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r14;
    // 0x80094840: b           L_8009484C
    // 0x80094844: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
        goto L_8009484C;
    // 0x80094844: or          $a2, $s3, $zero
    ctx->r6 = ctx->r19 | 0;
L_80094848:
    // 0x80094848: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
L_8009484C:
    // 0x8009484C: lw          $t9, 0x8C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X8C);
    // 0x80094850: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80094854: multu       $a0, $t9
    result = U64(U32(ctx->r4)) * U64(U32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094858: mflo        $v1
    ctx->r3 = lo;
    // 0x8009485C: sra         $t7, $v1, 7
    ctx->r15 = S32(SIGNED(ctx->r3) >> 7);
    // 0x80094860: bgez        $t7, L_80094870
    if (SIGNED(ctx->r15) >= 0) {
        // 0x80094864: or          $v1, $s0, $zero
        ctx->r3 = ctx->r16 | 0;
            goto L_80094870;
    }
    // 0x80094864: or          $v1, $s0, $zero
    ctx->r3 = ctx->r16 | 0;
    // 0x80094868: b           L_80094870
    // 0x8009486C: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
        goto L_80094870;
    // 0x8009486C: or          $v0, $t7, $zero
    ctx->r2 = ctx->r15 | 0;
L_80094870:
    // 0x80094870: negu        $t8, $v0
    ctx->r24 = SUB32(0, ctx->r2);
    // 0x80094874: andi        $t6, $t8, 0xFFFF
    ctx->r14 = ctx->r24 & 0XFFFF;
    // 0x80094878: negu        $t7, $a2
    ctx->r15 = SUB32(0, ctx->r6);
    // 0x8009487C: sll         $t8, $t7, 16
    ctx->r24 = S32(ctx->r15 << 16);
    // 0x80094880: or          $t9, $t6, $t8
    ctx->r25 = ctx->r14 | ctx->r24;
    // 0x80094884: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x80094888: lui         $t7, 0xB200
    ctx->r15 = S32(0XB200 << 16);
    // 0x8009488C: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x80094890: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x80094894: addiu       $t2, $t2, 0x1
    ctx->r10 = ADD32(ctx->r10, 0X1);
    // 0x80094898: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x8009489C: sw          $t6, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r14;
    if (wr64MenuHalf > 0) wr64_menu_promote_waku_rect(rdram, (uint32_t)ctx->r9, wr64MenuX, wr64MenuWidth);
    // 0x800948A0: lw          $t9, 0x94($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X94);
    // 0x800948A4: lw          $t8, 0x98($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X98);
    // 0x800948A8: lw          $t6, 0xA0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XA0);
    // 0x800948AC: multu       $t8, $t9
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800948B0: mflo        $t7
    ctx->r15 = lo;
    // 0x800948B4: addu        $t4, $t4, $t7
    ctx->r12 = ADD32(ctx->r12, ctx->r15);
    // 0x800948B8: bnel        $t2, $t6, L_80094660
    if (ctx->r10 != ctx->r14) {
        // 0x800948BC: or          $v0, $s0, $zero
        ctx->r2 = ctx->r16 | 0;
            goto L_80094660;
    }
    goto skip_0;
    // 0x800948BC: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
    skip_0:
L_800948C0:
    // 0x800948C0: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_800948C4:
    // 0x800948C4: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x800948C8: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x800948CC: lw          $s2, 0x10($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X10);
    // 0x800948D0: lw          $s3, 0x14($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X14);
    // 0x800948D4: jr          $ra
    // 0x800948D8: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
    return;
    // 0x800948D8: addiu       $sp, $sp, 0xA8
    ctx->r29 = ADD32(ctx->r29, 0XA8);
;}
RECOMP_FUNC void func_800948DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800948DC: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800948E0: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x800948E4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800948E8: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800948EC: addu        $v0, $v0, $t6
    ctx->r2 = ADD32(ctx->r2, ctx->r14);
    // 0x800948F0: lw          $v0, -0x4CF8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CF8);
    // 0x800948F4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800948F8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800948FC: beq         $v0, $zero, L_80094930
    if (ctx->r2 == 0) {
        // 0x80094900: lui         $t7, 0x801D
        ctx->r15 = S32(0X801D << 16);
            goto L_80094930;
    }
    // 0x80094900: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094904: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x80094908: beq         $v0, $v1, L_8009496C
    if (ctx->r2 == ctx->r3) {
        // 0x8009490C: lui         $at, 0x801D
        ctx->r1 = S32(0X801D << 16);
            goto L_8009496C;
    }
    // 0x8009490C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80094910: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80094914: beq         $v0, $at, L_80094978
    if (ctx->r2 == ctx->r1) {
        // 0x80094918: addiu       $a0, $zero, 0x28
        ctx->r4 = ADD32(0, 0X28);
            goto L_80094978;
    }
    // 0x80094918: addiu       $a0, $zero, 0x28
    ctx->r4 = ADD32(0, 0X28);
    // 0x8009491C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80094920: beq         $v0, $at, L_80094984
    if (ctx->r2 == ctx->r1) {
        // 0x80094924: nop
    
            goto L_80094984;
    }
    // 0x80094924: nop

    // 0x80094928: b           L_800949A4
    // 0x8009492C: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
        goto L_800949A4;
    // 0x8009492C: lw          $a0, 0x1C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X1C);
L_80094930:
    // 0x80094930: lh          $t7, -0x19F4($t7)
    ctx->r15 = MEM_H(ctx->r15, -0X19F4);
    // 0x80094934: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x80094938: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009493C: bne         $v1, $t7, L_80094958
    if (ctx->r3 != ctx->r15) {
        // 0x80094940: sw          $zero, -0x1A00($at)
        MEM_W(-0X1A00, ctx->r1) = 0;
            goto L_80094958;
    }
    // 0x80094940: sw          $zero, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = 0;
    // 0x80094944: sll         $t8, $a1, 1
    ctx->r24 = S32(ctx->r5 << 1);
    // 0x80094948: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x8009494C: addu        $a0, $a0, $t8
    ctx->r4 = ADD32(ctx->r4, ctx->r24);
    // 0x80094950: b           L_800949A4
    // 0x80094954: lh          $a0, -0x5414($a0)
    ctx->r4 = MEM_H(ctx->r4, -0X5414);
        goto L_800949A4;
    // 0x80094954: lh          $a0, -0x5414($a0)
    ctx->r4 = MEM_H(ctx->r4, -0X5414);
L_80094958:
    // 0x80094958: sll         $t9, $a1, 1
    ctx->r25 = S32(ctx->r5 << 1);
    // 0x8009495C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x80094960: addu        $a0, $a0, $t9
    ctx->r4 = ADD32(ctx->r4, ctx->r25);
    // 0x80094964: b           L_800949A4
    // 0x80094968: lh          $a0, -0x5400($a0)
    ctx->r4 = MEM_H(ctx->r4, -0X5400);
        goto L_800949A4;
    // 0x80094968: lh          $a0, -0x5400($a0)
    ctx->r4 = MEM_H(ctx->r4, -0X5400);
L_8009496C:
    // 0x8009496C: sw          $v1, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r3;
    // 0x80094970: b           L_800949A4
    // 0x80094974: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
        goto L_800949A4;
    // 0x80094974: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
L_80094978:
    // 0x80094978: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009497C: b           L_800949A4
    // 0x80094980: sw          $v1, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r3;
        goto L_800949A4;
    // 0x80094980: sw          $v1, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r3;
L_80094984:
    // 0x80094984: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80094988: jal         0x80047E50
    // 0x8009498C: sw          $v1, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r3;
    SysUtils_Rand(rdram, ctx);
        goto after_0;
    // 0x8009498C: sw          $v1, -0x1A00($at)
    MEM_W(-0X1A00, ctx->r1) = ctx->r3;
    after_0:
    // 0x80094990: addiu       $at, $zero, 0x1F
    ctx->r1 = ADD32(0, 0X1F);
    // 0x80094994: divu        $zero, $v0, $at
    lo = S32(U32(ctx->r2) / U32(ctx->r1)); hi = S32(U32(ctx->r2) % U32(ctx->r1));
    // 0x80094998: mfhi        $a0
    ctx->r4 = hi;
    // 0x8009499C: addiu       $a0, $a0, 0xA
    ctx->r4 = ADD32(ctx->r4, 0XA);
    // 0x800949A0: nop

L_800949A4:
    // 0x800949A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800949A8: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800949AC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800949B0: jr          $ra
    // 0x800949B4: nop

    return;
    // 0x800949B4: nop

;}
RECOMP_FUNC void func_800949B8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800949B8: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x800949BC: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x800949C0: addiu       $t7, $t7, -0x760
    ctx->r15 = ADD32(ctx->r15, -0X760);
    // 0x800949C4: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x800949C8: subu        $t9, $t9, $a1
    ctx->r25 = SUB32(ctx->r25, ctx->r5);
    // 0x800949CC: lui         $t1, 0x800E
    ctx->r9 = S32(0X800E << 16);
    // 0x800949D0: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x800949D4: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x800949D8: addiu       $a3, $a0, 0x8
    ctx->r7 = ADD32(ctx->r4, 0X8);
    // 0x800949DC: addiu       $t1, $t1, -0x55A8
    ctx->r9 = ADD32(ctx->r9, -0X55A8);
    // 0x800949E0: sll         $t9, $t9, 1
    ctx->r25 = S32(ctx->r25 << 1);
    // 0x800949E4: lui         $t8, 0xFA00
    ctx->r24 = S32(0XFA00 << 16);
    // 0x800949E8: sw          $t8, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r24;
    // 0x800949EC: addu        $v1, $t9, $t1
    ctx->r3 = ADD32(ctx->r25, ctx->r9);
    // 0x800949F0: lhu         $t5, 0x2($v1)
    ctx->r13 = MEM_HU(ctx->r3, 0X2);
    // 0x800949F4: lhu         $t3, 0x0($v1)
    ctx->r11 = MEM_HU(ctx->r3, 0X0);
    // 0x800949F8: lhu         $t9, 0x4($v1)
    ctx->r25 = MEM_HU(ctx->r3, 0X4);
    // 0x800949FC: andi        $t6, $t5, 0xFF
    ctx->r14 = ctx->r13 & 0XFF;
    // 0x80094A00: sll         $t7, $t6, 16
    ctx->r15 = S32(ctx->r14 << 16);
    // 0x80094A04: sll         $t4, $t3, 24
    ctx->r12 = S32(ctx->r11 << 24);
    // 0x80094A08: andi        $t1, $t9, 0xFF
    ctx->r9 = ctx->r25 & 0XFF;
    // 0x80094A0C: sll         $t2, $t1, 8
    ctx->r10 = S32(ctx->r9 << 8);
    // 0x80094A10: or          $t8, $t4, $t7
    ctx->r24 = ctx->r12 | ctx->r15;
    // 0x80094A14: or          $t3, $t8, $t2
    ctx->r11 = ctx->r24 | ctx->r10;
    // 0x80094A18: ori         $t5, $t3, 0xFF
    ctx->r13 = ctx->r11 | 0XFF;
    // 0x80094A1C: addiu       $t0, $a3, 0x8
    ctx->r8 = ADD32(ctx->r7, 0X8);
    // 0x80094A20: lui         $t6, 0xF668
    ctx->r14 = S32(0XF668 << 16);
    // 0x80094A24: addiu       $t6, $t6, -0x3C94
    ctx->r14 = ADD32(ctx->r14, -0X3C94);
    // 0x80094A28: lui         $t4, 0x2
    ctx->r12 = S32(0X2 << 16);
    // 0x80094A2C: addiu       $t4, $t4, 0x50
    ctx->r12 = ADD32(ctx->r12, 0X50);
    // 0x80094A30: sw          $t5, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r13;
    { extern uint32_t wr64_experimental_viewport_borders(void); if (wr64_experimental_viewport_borders()) { ctx->r14 = 0xF669C3BCU; ctx->r12 = 0x00000000U; } }
    // 0x80094A34: sw          $t4, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r12;
    // 0x80094A38: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x80094A3C: jr          $ra
    // 0x80094A40: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
    return;
    // 0x80094A40: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
;}
RECOMP_FUNC void func_80094A44(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094A44: bltz        $a1, L_80094A58
    if (SIGNED(ctx->r5) < 0) {
        // 0x80094A48: lui         $t1, 0xBF00
        ctx->r9 = S32(0XBF00 << 16);
            goto L_80094A58;
    }
    // 0x80094A48: lui         $t1, 0xBF00
    ctx->r9 = S32(0XBF00 << 16);
    // 0x80094A4C: slti        $at, $a1, 0x9
    ctx->r1 = SIGNED(ctx->r5) < 0X9 ? 1 : 0;
    // 0x80094A50: bne         $at, $zero, L_80094A5C
    if (ctx->r1 != 0) {
        // 0x80094A54: nop
    
            goto L_80094A5C;
    }
    // 0x80094A54: nop

L_80094A58:
    // 0x80094A58: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
L_80094A5C:
    // 0x80094A5C: lui         $t7, 0x107
    ctx->r15 = S32(0X107 << 16);
    // 0x80094A60: addiu       $t7, $t7, -0x718
    ctx->r15 = ADD32(ctx->r15, -0X718);
    // 0x80094A64: lui         $t6, 0x600
    ctx->r14 = S32(0X600 << 16);
    // 0x80094A68: lui         $t8, 0x400
    ctx->r24 = S32(0X400 << 16);
    // 0x80094A6C: sw          $t6, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r14;
    // 0x80094A70: sw          $t7, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->r15;
    // 0x80094A74: addiu       $a2, $a0, 0x8
    ctx->r6 = ADD32(ctx->r4, 0X8);
    // 0x80094A78: ori         $t8, $t8, 0x83F
    ctx->r24 = ctx->r24 | 0X83F;
    // 0x80094A7C: sll         $t9, $a1, 2
    ctx->r25 = S32(ctx->r5 << 2);
    // 0x80094A80: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80094A84: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x80094A88: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
    // 0x80094A8C: lw          $t2, -0x5570($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X5570);
    // 0x80094A90: addiu       $a3, $a2, 0x8
    ctx->r7 = ADD32(ctx->r6, 0X8);
    // 0x80094A94: addiu       $t0, $a3, 0x8
    ctx->r8 = ADD32(ctx->r7, 0X8);
    // 0x80094A98: sw          $t2, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r10;
    // 0x80094A9C: addiu       $t3, $zero, 0xF05
    ctx->r11 = ADD32(0, 0XF05);
    // 0x80094AA0: sw          $t3, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r11;
    // 0x80094AA4: sw          $t1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r9;
    // 0x80094AA8: addiu       $t4, $zero, 0xA0F
    ctx->r12 = ADD32(0, 0XA0F);
    // 0x80094AAC: sw          $t4, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r12;
    // 0x80094AB0: sw          $t1, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r9;
    // 0x80094AB4: jr          $ra
    // 0x80094AB8: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
    return;
    // 0x80094AB8: addiu       $v0, $t0, 0x8
    ctx->r2 = ADD32(ctx->r8, 0X8);
;}
RECOMP_FUNC void func_80094ABC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094ABC: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x80094AC0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80094AC4: jr          $ra
    // 0x80094AC8: sh          $t6, -0x54F4($at)
    MEM_H(-0X54F4, ctx->r1) = ctx->r14;
    return;
    // 0x80094AC8: sh          $t6, -0x54F4($at)
    MEM_H(-0X54F4, ctx->r1) = ctx->r14;
;}
RECOMP_FUNC void func_80094ACC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094ACC: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x80094AD0: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80094AD4: lui         $t2, 0x800F
    ctx->r10 = S32(0X800F << 16);
    // 0x80094AD8: sw          $s1, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r17;
    // 0x80094ADC: sw          $s0, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r16;
    // 0x80094AE0: addiu       $t2, $t2, -0x5450
    ctx->r10 = ADD32(ctx->r10, -0X5450);
    // 0x80094AE4: lh          $a0, -0x19F2($a0)
    ctx->r4 = MEM_H(ctx->r4, -0X19F2);
    // 0x80094AE8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094AEC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_80094AF0:
    // 0x80094AF0: blez        $a0, L_80094B78
    if (SIGNED(ctx->r4) <= 0) {
        // 0x80094AF4: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_80094B78;
    }
    // 0x80094AF4: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80094AF8: lui         $a1, 0x801C
    ctx->r5 = S32(0X801C << 16);
    // 0x80094AFC: addiu       $a1, $a1, 0x2938
    ctx->r5 = ADD32(ctx->r5, 0X2938);
L_80094B00:
    // 0x80094B00: lw          $t6, 0x4($a1)
    ctx->r14 = MEM_W(ctx->r5, 0X4);
    // 0x80094B04: sll         $a2, $v0, 2
    ctx->r6 = S32(ctx->r2 << 2);
    // 0x80094B08: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094B0C: bnel        $v1, $t6, L_80094B6C
    if (ctx->r3 != ctx->r14) {
        // 0x80094B10: addiu       $v0, $v0, 0x1
        ctx->r2 = ADD32(ctx->r2, 0X1);
            goto L_80094B6C;
    }
    goto skip_0;
    // 0x80094B10: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    skip_0:
    // 0x80094B14: lw          $t7, -0x4CCC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CCC);
    // 0x80094B18: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80094B1C: addiu       $t6, $t6, -0x4CB0
    ctx->r14 = ADD32(ctx->r14, -0X4CB0);
    // 0x80094B20: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x80094B24: addu        $t9, $t8, $a2
    ctx->r25 = ADD32(ctx->r24, ctx->r6);
    // 0x80094B28: lw          $t8, 0x2EC($a1)
    ctx->r24 = MEM_W(ctx->r5, 0X2EC);
    // 0x80094B2C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094B30: addiu       $t7, $t7, -0x4CC0
    ctx->r15 = ADD32(ctx->r15, -0X4CC0);
    // 0x80094B34: addu        $t0, $a2, $t7
    ctx->r8 = ADD32(ctx->r6, ctx->r15);
    // 0x80094B38: beq         $t8, $zero, L_80094B48
    if (ctx->r24 == 0) {
        // 0x80094B3C: addu        $a3, $t9, $t6
        ctx->r7 = ADD32(ctx->r25, ctx->r14);
            goto L_80094B48;
    }
    // 0x80094B3C: addu        $a3, $t9, $t6
    ctx->r7 = ADD32(ctx->r25, ctx->r14);
    // 0x80094B40: b           L_80094B58
    // 0x80094B44: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
        goto L_80094B58;
    // 0x80094B44: sw          $zero, 0x0($a3)
    MEM_W(0X0, ctx->r7) = 0;
L_80094B48:
    // 0x80094B48: sll         $t9, $v1, 1
    ctx->r25 = S32(ctx->r3 << 1);
    // 0x80094B4C: addu        $t6, $t2, $t9
    ctx->r14 = ADD32(ctx->r10, ctx->r25);
    // 0x80094B50: lh          $t7, 0x0($t6)
    ctx->r15 = MEM_H(ctx->r14, 0X0);
    // 0x80094B54: sw          $t7, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r15;
L_80094B58:
    // 0x80094B58: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x80094B5C: lw          $t9, 0x0($a3)
    ctx->r25 = MEM_W(ctx->r7, 0X0);
    // 0x80094B60: addu        $t6, $t8, $t9
    ctx->r14 = ADD32(ctx->r24, ctx->r25);
    // 0x80094B64: sw          $t6, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r14;
    // 0x80094B68: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
L_80094B6C:
    // 0x80094B6C: slt         $at, $v0, $a0
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x80094B70: bne         $at, $zero, L_80094B00
    if (ctx->r1 != 0) {
        // 0x80094B74: addiu       $a1, $a1, 0x378
        ctx->r5 = ADD32(ctx->r5, 0X378);
            goto L_80094B00;
    }
    // 0x80094B74: addiu       $a1, $a1, 0x378
    ctx->r5 = ADD32(ctx->r5, 0X378);
L_80094B78:
    // 0x80094B78: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x80094B7C: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x80094B80: bne         $at, $zero, L_80094AF0
    if (ctx->r1 != 0) {
        // 0x80094B84: addiu       $t1, $t1, 0x1
        ctx->r9 = ADD32(ctx->r9, 0X1);
            goto L_80094AF0;
    }
    // 0x80094B84: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094B88: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x80094B8C: addiu       $a2, $a2, -0x18E8
    ctx->r6 = ADD32(ctx->r6, -0X18E8);
    // 0x80094B90: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094B94: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_80094B98:
    // 0x80094B98: sw          $v1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r3;
    // 0x80094B9C: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x80094BA0: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x80094BA4: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094BA8: bne         $at, $zero, L_80094B98
    if (ctx->r1 != 0) {
        // 0x80094BAC: addiu       $a2, $a2, 0x4
        ctx->r6 = ADD32(ctx->r6, 0X4);
            goto L_80094B98;
    }
    // 0x80094BAC: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x80094BB0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x80094BB4: addiu       $t4, $t4, -0x18D8
    ctx->r12 = ADD32(ctx->r12, -0X18D8);
    // 0x80094BB8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094BBC: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x80094BC0: addiu       $t3, $zero, 0x4
    ctx->r11 = ADD32(0, 0X4);
L_80094BC4:
    // 0x80094BC4: slti        $at, $t1, 0x4
    ctx->r1 = SIGNED(ctx->r9) < 0X4 ? 1 : 0;
    // 0x80094BC8: beq         $at, $zero, L_80094D08
    if (ctx->r1 == 0) {
        // 0x80094BCC: or          $v0, $t1, $zero
        ctx->r2 = ctx->r9 | 0;
            goto L_80094D08;
    }
    // 0x80094BCC: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
    // 0x80094BD0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094BD4: lw          $t7, -0x4CCC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X4CCC);
    // 0x80094BD8: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80094BDC: addiu       $t9, $t9, -0x4CB0
    ctx->r25 = ADD32(ctx->r25, -0X4CB0);
    // 0x80094BE0: sll         $t8, $t7, 4
    ctx->r24 = S32(ctx->r15 << 4);
    // 0x80094BE4: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x80094BE8: addiu       $t8, $zero, 0x4
    ctx->r24 = ADD32(0, 0X4);
    // 0x80094BEC: subu        $a0, $t8, $t1
    ctx->r4 = SUB32(ctx->r24, ctx->r9);
    // 0x80094BF0: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80094BF4: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80094BF8: andi        $v1, $a0, 0x1
    ctx->r3 = ctx->r4 & 0X1;
    // 0x80094BFC: addiu       $t7, $t7, -0x18E8
    ctx->r15 = ADD32(ctx->r15, -0X18E8);
    // 0x80094C00: beq         $v1, $zero, L_80094C5C
    if (ctx->r3 == 0) {
        // 0x80094C04: addu        $a2, $t6, $t7
        ctx->r6 = ADD32(ctx->r14, ctx->r15);
            goto L_80094C5C;
    }
    // 0x80094C04: addu        $a2, $t6, $t7
    ctx->r6 = ADD32(ctx->r14, ctx->r15);
    // 0x80094C08: lw          $a3, 0x0($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X0);
    // 0x80094C0C: sll         $t9, $t1, 2
    ctx->r25 = S32(ctx->r9 << 2);
    // 0x80094C10: addu        $t0, $t9, $t7
    ctx->r8 = ADD32(ctx->r25, ctx->r15);
    // 0x80094C14: lw          $t2, 0x0($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X0);
    // 0x80094C18: sll         $t6, $a3, 2
    ctx->r14 = S32(ctx->r7 << 2);
    // 0x80094C1C: addu        $t8, $a1, $t6
    ctx->r24 = ADD32(ctx->r5, ctx->r14);
    // 0x80094C20: sll         $t7, $t2, 2
    ctx->r15 = S32(ctx->r10 << 2);
    // 0x80094C24: lw          $t9, 0x0($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X0);
    // 0x80094C28: addu        $t6, $a1, $t7
    ctx->r14 = ADD32(ctx->r5, ctx->r15);
    // 0x80094C2C: lw          $t8, 0x0($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X0);
    // 0x80094C30: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094C34: addiu       $v0, $t1, 0x1
    ctx->r2 = ADD32(ctx->r9, 0X1);
    // 0x80094C38: slt         $at, $t9, $t8
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x80094C3C: beq         $at, $zero, L_80094C48
    if (ctx->r1 == 0) {
        // 0x80094C40: nop
    
            goto L_80094C48;
    }
    // 0x80094C40: nop

    // 0x80094C44: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094C48:
    // 0x80094C48: beq         $a0, $zero, L_80094C58
    if (ctx->r4 == 0) {
        // 0x80094C4C: nop
    
            goto L_80094C58;
    }
    // 0x80094C4C: nop

    // 0x80094C50: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
    // 0x80094C54: sw          $a3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r7;
L_80094C58:
    // 0x80094C58: beq         $v0, $t3, L_80094D08
    if (ctx->r2 == ctx->r11) {
        // 0x80094C5C: lui         $t6, 0x801D
        ctx->r14 = S32(0X801D << 16);
            goto L_80094D08;
    }
L_80094C5C:
    // 0x80094C5C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80094C60: addiu       $t6, $t6, -0x18E8
    ctx->r14 = ADD32(ctx->r14, -0X18E8);
    // 0x80094C64: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x80094C68: addu        $t0, $t7, $t6
    ctx->r8 = ADD32(ctx->r15, ctx->r14);
    // 0x80094C6C: lw          $a3, 0x0($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X0);
L_80094C70:
    // 0x80094C70: lw          $t2, 0x0($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X0);
    // 0x80094C74: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094C78: sll         $t9, $a3, 2
    ctx->r25 = S32(ctx->r7 << 2);
    // 0x80094C7C: addu        $t8, $a1, $t9
    ctx->r24 = ADD32(ctx->r5, ctx->r25);
    // 0x80094C80: sll         $t6, $t2, 2
    ctx->r14 = S32(ctx->r10 << 2);
    // 0x80094C84: lw          $t7, 0x0($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X0);
    // 0x80094C88: addu        $t9, $a1, $t6
    ctx->r25 = ADD32(ctx->r5, ctx->r14);
    // 0x80094C8C: lw          $t8, 0x0($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X0);
    // 0x80094C90: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
    // 0x80094C94: slt         $at, $t7, $t8
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x80094C98: beql        $at, $zero, L_80094CA8
    if (ctx->r1 == 0) {
        // 0x80094C9C: sltu        $v0, $zero, $a0
        ctx->r2 = 0 < ctx->r4 ? 1 : 0;
            goto L_80094CA8;
    }
    goto skip_1;
    // 0x80094C9C: sltu        $v0, $zero, $a0
    ctx->r2 = 0 < ctx->r4 ? 1 : 0;
    skip_1:
    // 0x80094CA0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x80094CA4: sltu        $v0, $zero, $a0
    ctx->r2 = 0 < ctx->r4 ? 1 : 0;
L_80094CA8:
    // 0x80094CA8: beq         $v0, $zero, L_80094CC0
    if (ctx->r2 == 0) {
        // 0x80094CAC: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80094CC0;
    }
    // 0x80094CAC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094CB0: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
    // 0x80094CB4: sw          $a3, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r7;
    // 0x80094CB8: lw          $a3, 0x0($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X0);
    // 0x80094CBC: or          $v1, $a3, $zero
    ctx->r3 = ctx->r7 | 0;
L_80094CC0:
    // 0x80094CC0: lw          $t2, 0x4($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X4);
    // 0x80094CC4: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80094CC8: addu        $t9, $a1, $t6
    ctx->r25 = ADD32(ctx->r5, ctx->r14);
    // 0x80094CCC: sll         $t8, $t2, 2
    ctx->r24 = S32(ctx->r10 << 2);
    // 0x80094CD0: lw          $t7, 0x0($t9)
    ctx->r15 = MEM_W(ctx->r25, 0X0);
    // 0x80094CD4: addu        $t6, $a1, $t8
    ctx->r14 = ADD32(ctx->r5, ctx->r24);
    // 0x80094CD8: lw          $t9, 0x0($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X0);
    // 0x80094CDC: slt         $at, $t7, $t9
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x80094CE0: beq         $at, $zero, L_80094CEC
    if (ctx->r1 == 0) {
        // 0x80094CE4: nop
    
            goto L_80094CEC;
    }
    // 0x80094CE4: nop

    // 0x80094CE8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094CEC:
    // 0x80094CEC: beql        $a0, $zero, L_80094D00
    if (ctx->r4 == 0) {
        // 0x80094CF0: addiu       $t0, $t0, 0x8
        ctx->r8 = ADD32(ctx->r8, 0X8);
            goto L_80094D00;
    }
    goto skip_2;
    // 0x80094CF0: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
    skip_2:
    // 0x80094CF4: sw          $t2, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r10;
    // 0x80094CF8: sw          $a3, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r7;
    // 0x80094CFC: addiu       $t0, $t0, 0x8
    ctx->r8 = ADD32(ctx->r8, 0X8);
L_80094D00:
    // 0x80094D00: bnel        $t0, $t4, L_80094C70
    if (ctx->r8 != ctx->r12) {
        // 0x80094D04: lw          $a3, 0x0($a2)
        ctx->r7 = MEM_W(ctx->r6, 0X0);
            goto L_80094C70;
    }
    goto skip_3;
    // 0x80094D04: lw          $a3, 0x0($a2)
    ctx->r7 = MEM_W(ctx->r6, 0X0);
    skip_3:
L_80094D08:
    // 0x80094D08: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x80094D0C: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x80094D10: bne         $at, $zero, L_80094BC4
    if (ctx->r1 != 0) {
        // 0x80094D14: addiu       $t1, $t1, 0x1
        ctx->r9 = ADD32(ctx->r9, 0X1);
            goto L_80094BC4;
    }
    // 0x80094D14: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094D18: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x80094D1C: addiu       $a2, $a2, -0x5624
    ctx->r6 = ADD32(ctx->r6, -0X5624);
    // 0x80094D20: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094D24: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_80094D28:
    // 0x80094D28: sw          $v1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r3;
    // 0x80094D2C: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x80094D30: slti        $at, $v1, 0x4
    ctx->r1 = SIGNED(ctx->r3) < 0X4 ? 1 : 0;
    // 0x80094D34: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094D38: bne         $at, $zero, L_80094D28
    if (ctx->r1 != 0) {
        // 0x80094D3C: addiu       $a2, $a2, 0x4
        ctx->r6 = ADD32(ctx->r6, 0X4);
            goto L_80094D28;
    }
    // 0x80094D3C: addiu       $a2, $a2, 0x4
    ctx->r6 = ADD32(ctx->r6, 0X4);
    // 0x80094D40: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80094D44: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x80094D48: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x80094D4C: addiu       $a1, $a1, -0x4CC0
    ctx->r5 = ADD32(ctx->r5, -0X4CC0);
    // 0x80094D50: addiu       $a3, $a3, 0x2938
    ctx->r7 = ADD32(ctx->r7, 0X2938);
    // 0x80094D54: addiu       $t2, $t2, -0x5614
    ctx->r10 = ADD32(ctx->r10, -0X5614);
    // 0x80094D58: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094D5C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x80094D60: addiu       $t0, $zero, 0x378
    ctx->r8 = ADD32(0, 0X378);
L_80094D64:
    // 0x80094D64: slti        $at, $t1, 0x4
    ctx->r1 = SIGNED(ctx->r9) < 0X4 ? 1 : 0;
    // 0x80094D68: beq         $at, $zero, L_80094F80
    if (ctx->r1 == 0) {
        // 0x80094D6C: or          $v0, $t1, $zero
        ctx->r2 = ctx->r9 | 0;
            goto L_80094F80;
    }
    // 0x80094D6C: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
    // 0x80094D70: addiu       $t7, $zero, 0x4
    ctx->r15 = ADD32(0, 0X4);
    // 0x80094D74: subu        $a0, $t7, $t1
    ctx->r4 = SUB32(ctx->r15, ctx->r9);
    // 0x80094D78: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x80094D7C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80094D80: addiu       $t6, $t6, -0x5624
    ctx->r14 = ADD32(ctx->r14, -0X5624);
    // 0x80094D84: andi        $v1, $a0, 0x1
    ctx->r3 = ctx->r4 & 0X1;
    // 0x80094D88: beq         $v1, $zero, L_80094E34
    if (ctx->r3 == 0) {
        // 0x80094D8C: addu        $a2, $t8, $t6
        ctx->r6 = ADD32(ctx->r24, ctx->r14);
            goto L_80094E34;
    }
    // 0x80094D8C: addu        $a2, $t8, $t6
    ctx->r6 = ADD32(ctx->r24, ctx->r14);
    // 0x80094D90: lw          $t4, 0x0($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X0);
    // 0x80094D94: sll         $t9, $t1, 2
    ctx->r25 = S32(ctx->r9 << 2);
    // 0x80094D98: addu        $t5, $t9, $t6
    ctx->r13 = ADD32(ctx->r25, ctx->r14);
    // 0x80094D9C: lw          $s0, 0x0($t5)
    ctx->r16 = MEM_W(ctx->r13, 0X0);
    // 0x80094DA0: sll         $t8, $t4, 2
    ctx->r24 = S32(ctx->r12 << 2);
    // 0x80094DA4: addu        $t7, $a1, $t8
    ctx->r15 = ADD32(ctx->r5, ctx->r24);
    // 0x80094DA8: sll         $t6, $s0, 2
    ctx->r14 = S32(ctx->r16 << 2);
    // 0x80094DAC: lw          $t9, 0x0($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X0);
    // 0x80094DB0: addu        $t8, $a1, $t6
    ctx->r24 = ADD32(ctx->r5, ctx->r14);
    // 0x80094DB4: lw          $t7, 0x0($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X0);
    // 0x80094DB8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094DBC: addiu       $v0, $t1, 0x1
    ctx->r2 = ADD32(ctx->r9, 0X1);
    // 0x80094DC0: bne         $t9, $t7, L_80094DFC
    if (ctx->r25 != ctx->r15) {
        // 0x80094DC4: sll         $t8, $s0, 2
        ctx->r24 = S32(ctx->r16 << 2);
            goto L_80094DFC;
    }
    // 0x80094DC4: sll         $t8, $s0, 2
    ctx->r24 = S32(ctx->r16 << 2);
    // 0x80094DC8: multu       $s0, $t0
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094DCC: mflo        $t6
    ctx->r14 = lo;
    // 0x80094DD0: addu        $t8, $a3, $t6
    ctx->r24 = ADD32(ctx->r7, ctx->r14);
    // 0x80094DD4: lw          $t9, 0x4($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X4);
    // 0x80094DD8: multu       $t4, $t0
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094DDC: mflo        $t7
    ctx->r15 = lo;
    // 0x80094DE0: addu        $t6, $a3, $t7
    ctx->r14 = ADD32(ctx->r7, ctx->r15);
    // 0x80094DE4: lw          $t8, 0x4($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X4);
    // 0x80094DE8: slt         $at, $t9, $t8
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x80094DEC: beq         $at, $zero, L_80094E20
    if (ctx->r1 == 0) {
        // 0x80094DF0: nop
    
            goto L_80094E20;
    }
    // 0x80094DF0: nop

    // 0x80094DF4: b           L_80094E20
    // 0x80094DF8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_80094E20;
    // 0x80094DF8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094DFC:
    // 0x80094DFC: sll         $t7, $t4, 2
    ctx->r15 = S32(ctx->r12 << 2);
    // 0x80094E00: addu        $t6, $a1, $t7
    ctx->r14 = ADD32(ctx->r5, ctx->r15);
    // 0x80094E04: lw          $t9, 0x0($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X0);
    // 0x80094E08: addu        $t7, $a1, $t8
    ctx->r15 = ADD32(ctx->r5, ctx->r24);
    // 0x80094E0C: lw          $t6, 0x0($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X0);
    // 0x80094E10: slt         $at, $t9, $t6
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r14) ? 1 : 0;
    // 0x80094E14: beq         $at, $zero, L_80094E20
    if (ctx->r1 == 0) {
        // 0x80094E18: nop
    
            goto L_80094E20;
    }
    // 0x80094E18: nop

    // 0x80094E1C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094E20:
    // 0x80094E20: beq         $a0, $zero, L_80094E30
    if (ctx->r4 == 0) {
        // 0x80094E24: nop
    
            goto L_80094E30;
    }
    // 0x80094E24: nop

    // 0x80094E28: sw          $s0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r16;
    // 0x80094E2C: sw          $t4, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r12;
L_80094E30:
    // 0x80094E30: beq         $v0, $t3, L_80094F80
    if (ctx->r2 == ctx->r11) {
        // 0x80094E34: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_80094F80;
    }
L_80094E34:
    // 0x80094E34: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80094E38: addiu       $t7, $t7, -0x5624
    ctx->r15 = ADD32(ctx->r15, -0X5624);
    // 0x80094E3C: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x80094E40: addu        $t5, $t8, $t7
    ctx->r13 = ADD32(ctx->r24, ctx->r15);
    // 0x80094E44: lw          $t4, 0x0($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X0);
L_80094E48:
    // 0x80094E48: lw          $s0, 0x0($t5)
    ctx->r16 = MEM_W(ctx->r13, 0X0);
    // 0x80094E4C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094E50: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    // 0x80094E54: addu        $t6, $a1, $t9
    ctx->r14 = ADD32(ctx->r5, ctx->r25);
    // 0x80094E58: sll         $t7, $s0, 2
    ctx->r15 = S32(ctx->r16 << 2);
    // 0x80094E5C: lw          $t8, 0x0($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X0);
    // 0x80094E60: addu        $t9, $a1, $t7
    ctx->r25 = ADD32(ctx->r5, ctx->r15);
    // 0x80094E64: lw          $t6, 0x0($t9)
    ctx->r14 = MEM_W(ctx->r25, 0X0);
    // 0x80094E68: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
    // 0x80094E6C: sll         $t9, $s0, 2
    ctx->r25 = S32(ctx->r16 << 2);
    // 0x80094E70: bnel        $t8, $t6, L_80094EB0
    if (ctx->r24 != ctx->r14) {
        // 0x80094E74: sll         $t6, $t4, 2
        ctx->r14 = S32(ctx->r12 << 2);
            goto L_80094EB0;
    }
    goto skip_4;
    // 0x80094E74: sll         $t6, $t4, 2
    ctx->r14 = S32(ctx->r12 << 2);
    skip_4:
    // 0x80094E78: multu       $s0, $t0
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094E7C: mflo        $t7
    ctx->r15 = lo;
    // 0x80094E80: addu        $t9, $a3, $t7
    ctx->r25 = ADD32(ctx->r7, ctx->r15);
    // 0x80094E84: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x80094E88: multu       $t4, $t0
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094E8C: mflo        $t6
    ctx->r14 = lo;
    // 0x80094E90: addu        $t7, $a3, $t6
    ctx->r15 = ADD32(ctx->r7, ctx->r14);
    // 0x80094E94: lw          $t9, 0x4($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X4);
    // 0x80094E98: slt         $at, $t8, $t9
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r25) ? 1 : 0;
    // 0x80094E9C: beql        $at, $zero, L_80094ED4
    if (ctx->r1 == 0) {
        // 0x80094EA0: sltu        $v0, $zero, $a0
        ctx->r2 = 0 < ctx->r4 ? 1 : 0;
            goto L_80094ED4;
    }
    goto skip_5;
    // 0x80094EA0: sltu        $v0, $zero, $a0
    ctx->r2 = 0 < ctx->r4 ? 1 : 0;
    skip_5:
    // 0x80094EA4: b           L_80094ED0
    // 0x80094EA8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_80094ED0;
    // 0x80094EA8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x80094EAC: sll         $t6, $t4, 2
    ctx->r14 = S32(ctx->r12 << 2);
L_80094EB0:
    // 0x80094EB0: addu        $t7, $a1, $t6
    ctx->r15 = ADD32(ctx->r5, ctx->r14);
    // 0x80094EB4: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x80094EB8: addu        $t6, $a1, $t9
    ctx->r14 = ADD32(ctx->r5, ctx->r25);
    // 0x80094EBC: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x80094EC0: slt         $at, $t8, $t7
    ctx->r1 = SIGNED(ctx->r24) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x80094EC4: beql        $at, $zero, L_80094ED4
    if (ctx->r1 == 0) {
        // 0x80094EC8: sltu        $v0, $zero, $a0
        ctx->r2 = 0 < ctx->r4 ? 1 : 0;
            goto L_80094ED4;
    }
    goto skip_6;
    // 0x80094EC8: sltu        $v0, $zero, $a0
    ctx->r2 = 0 < ctx->r4 ? 1 : 0;
    skip_6:
    // 0x80094ECC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094ED0:
    // 0x80094ED0: sltu        $v0, $zero, $a0
    ctx->r2 = 0 < ctx->r4 ? 1 : 0;
L_80094ED4:
    // 0x80094ED4: beq         $v0, $zero, L_80094EEC
    if (ctx->r2 == 0) {
        // 0x80094ED8: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80094EEC;
    }
    // 0x80094ED8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80094EDC: sw          $s0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r16;
    // 0x80094EE0: sw          $t4, 0x0($t5)
    MEM_W(0X0, ctx->r13) = ctx->r12;
    // 0x80094EE4: lw          $t4, 0x0($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X0);
    // 0x80094EE8: or          $v1, $t4, $zero
    ctx->r3 = ctx->r12 | 0;
L_80094EEC:
    // 0x80094EEC: lw          $s1, 0x4($t5)
    ctx->r17 = MEM_W(ctx->r13, 0X4);
    // 0x80094EF0: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x80094EF4: addu        $t7, $a1, $t8
    ctx->r15 = ADD32(ctx->r5, ctx->r24);
    // 0x80094EF8: sll         $t9, $s1, 2
    ctx->r25 = S32(ctx->r17 << 2);
    // 0x80094EFC: addu        $t6, $a1, $t9
    ctx->r14 = ADD32(ctx->r5, ctx->r25);
    // 0x80094F00: lw          $s0, 0x0($t6)
    ctx->r16 = MEM_W(ctx->r14, 0X0);
    // 0x80094F04: lw          $t9, 0x0($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X0);
    // 0x80094F08: or          $v0, $s1, $zero
    ctx->r2 = ctx->r17 | 0;
    // 0x80094F0C: bnel        $t9, $s0, L_80094F4C
    if (ctx->r25 != ctx->r16) {
        // 0x80094F10: sll         $t9, $t4, 2
        ctx->r25 = S32(ctx->r12 << 2);
            goto L_80094F4C;
    }
    goto skip_7;
    // 0x80094F10: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
    skip_7:
    // 0x80094F14: multu       $v0, $t0
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094F18: mflo        $t6
    ctx->r14 = lo;
    // 0x80094F1C: addu        $t8, $a3, $t6
    ctx->r24 = ADD32(ctx->r7, ctx->r14);
    // 0x80094F20: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x80094F24: multu       $t4, $t0
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r8)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80094F28: mflo        $t9
    ctx->r25 = lo;
    // 0x80094F2C: addu        $t6, $a3, $t9
    ctx->r14 = ADD32(ctx->r7, ctx->r25);
    // 0x80094F30: lw          $t8, 0x4($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X4);
    // 0x80094F34: slt         $at, $t7, $t8
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r24) ? 1 : 0;
    // 0x80094F38: beq         $at, $zero, L_80094F64
    if (ctx->r1 == 0) {
        // 0x80094F3C: nop
    
            goto L_80094F64;
    }
    // 0x80094F3C: nop

    // 0x80094F40: b           L_80094F64
    // 0x80094F44: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_80094F64;
    // 0x80094F44: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x80094F48: sll         $t9, $t4, 2
    ctx->r25 = S32(ctx->r12 << 2);
L_80094F4C:
    // 0x80094F4C: addu        $t6, $a1, $t9
    ctx->r14 = ADD32(ctx->r5, ctx->r25);
    // 0x80094F50: lw          $t7, 0x0($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X0);
    // 0x80094F54: slt         $at, $t7, $s0
    ctx->r1 = SIGNED(ctx->r15) < SIGNED(ctx->r16) ? 1 : 0;
    // 0x80094F58: beq         $at, $zero, L_80094F64
    if (ctx->r1 == 0) {
        // 0x80094F5C: nop
    
            goto L_80094F64;
    }
    // 0x80094F5C: nop

    // 0x80094F60: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_80094F64:
    // 0x80094F64: beql        $a0, $zero, L_80094F78
    if (ctx->r4 == 0) {
        // 0x80094F68: addiu       $t5, $t5, 0x8
        ctx->r13 = ADD32(ctx->r13, 0X8);
            goto L_80094F78;
    }
    goto skip_8;
    // 0x80094F68: addiu       $t5, $t5, 0x8
    ctx->r13 = ADD32(ctx->r13, 0X8);
    skip_8:
    // 0x80094F6C: sw          $s1, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r17;
    // 0x80094F70: sw          $t4, 0x4($t5)
    MEM_W(0X4, ctx->r13) = ctx->r12;
    // 0x80094F74: addiu       $t5, $t5, 0x8
    ctx->r13 = ADD32(ctx->r13, 0X8);
L_80094F78:
    // 0x80094F78: bnel        $t5, $t2, L_80094E48
    if (ctx->r13 != ctx->r10) {
        // 0x80094F7C: lw          $t4, 0x0($a2)
        ctx->r12 = MEM_W(ctx->r6, 0X0);
            goto L_80094E48;
    }
    goto skip_9;
    // 0x80094F7C: lw          $t4, 0x0($a2)
    ctx->r12 = MEM_W(ctx->r6, 0X0);
    skip_9:
L_80094F80:
    // 0x80094F80: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x80094F84: slti        $at, $v1, 0x3
    ctx->r1 = SIGNED(ctx->r3) < 0X3 ? 1 : 0;
    // 0x80094F88: bne         $at, $zero, L_80094D64
    if (ctx->r1 != 0) {
        // 0x80094F8C: addiu       $t1, $t1, 0x1
        ctx->r9 = ADD32(ctx->r9, 0X1);
            goto L_80094D64;
    }
    // 0x80094F8C: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094F90: lui         $a0, 0x801C
    ctx->r4 = S32(0X801C << 16);
    // 0x80094F94: addiu       $a0, $a0, 0x2938
    ctx->r4 = ADD32(ctx->r4, 0X2938);
    // 0x80094F98: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80094F9C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_80094FA0:
    // 0x80094FA0: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x80094FA4: addiu       $t5, $t5, -0x5624
    ctx->r13 = ADD32(ctx->r13, -0X5624);
    // 0x80094FA8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80094FAC:
    // 0x80094FAC: lw          $t8, 0x0($t5)
    ctx->r24 = MEM_W(ctx->r13, 0X0);
    // 0x80094FB0: beql        $v1, $t8, L_80094FC8
    if (ctx->r3 == ctx->r24) {
        // 0x80094FB4: or          $v1, $t1, $zero
        ctx->r3 = ctx->r9 | 0;
            goto L_80094FC8;
    }
    goto skip_10;
    // 0x80094FB4: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    skip_10:
    // 0x80094FB8: addiu       $v0, $v0, 0x1
    ctx->r2 = ADD32(ctx->r2, 0X1);
    // 0x80094FBC: bne         $v0, $t3, L_80094FAC
    if (ctx->r2 != ctx->r11) {
        // 0x80094FC0: addiu       $t5, $t5, 0x4
        ctx->r13 = ADD32(ctx->r13, 0X4);
            goto L_80094FAC;
    }
    // 0x80094FC0: addiu       $t5, $t5, 0x4
    ctx->r13 = ADD32(ctx->r13, 0X4);
    // 0x80094FC4: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
L_80094FC8:
    // 0x80094FC8: addiu       $a0, $a0, 0x378
    ctx->r4 = ADD32(ctx->r4, 0X378);
    // 0x80094FCC: sw          $v0, -0x40($a0)
    MEM_W(-0X40, ctx->r4) = ctx->r2;
    // 0x80094FD0: bne         $t1, $t3, L_80094FA0
    if (ctx->r9 != ctx->r11) {
        // 0x80094FD4: addiu       $t1, $t1, 0x1
        ctx->r9 = ADD32(ctx->r9, 0X1);
            goto L_80094FA0;
    }
    // 0x80094FD4: addiu       $t1, $t1, 0x1
    ctx->r9 = ADD32(ctx->r9, 0X1);
    // 0x80094FD8: lw          $s0, 0x8($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X8);
    // 0x80094FDC: lw          $s1, 0xC($sp)
    ctx->r17 = MEM_W(ctx->r29, 0XC);
    // 0x80094FE0: jr          $ra
    // 0x80094FE4: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x80094FE4: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
;}
RECOMP_FUNC void func_80094FE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80094FE8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80094FEC: addiu       $v0, $v0, -0x54DC
    ctx->r2 = ADD32(ctx->r2, -0X54DC);
    // 0x80094FF0: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x80094FF4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80094FF8: addiu       $t7, $zero, 0x11
    ctx->r15 = ADD32(0, 0X11);
    // 0x80094FFC: sw          $t6, -0x19CC($at)
    MEM_W(-0X19CC, ctx->r1) = ctx->r14;
    // 0x80095000: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095004: sw          $zero, -0x19D0($at)
    MEM_W(-0X19D0, ctx->r1) = 0;
    // 0x80095008: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x8009500C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095010: sw          $t7, -0x19C8($at)
    MEM_W(-0X19C8, ctx->r1) = ctx->r15;
    // 0x80095014: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x80095018: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009501C: sw          $v1, -0x19C4($at)
    MEM_W(-0X19C4, ctx->r1) = ctx->r3;
    // 0x80095020: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095024: sw          $zero, -0x19C0($at)
    MEM_W(-0X19C0, ctx->r1) = 0;
    // 0x80095028: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009502C: sw          $zero, -0x19BC($at)
    MEM_W(-0X19BC, ctx->r1) = 0;
    // 0x80095030: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80095034: sw          $zero, -0x54E4($at)
    MEM_W(-0X54E4, ctx->r1) = 0;
    // 0x80095038: lui         $at, 0x800D
    ctx->r1 = S32(0X800D << 16);
    // 0x8009503C: jr          $ra
    // 0x80095040: sw          $v1, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r3;
    return;
    // 0x80095040: sw          $v1, 0x461C($at)
    MEM_W(0X461C, ctx->r1) = ctx->r3;
    // 0x80095044: nop

    // 0x80095048: nop

    // 0x8009504C: nop

;}
RECOMP_FUNC void unk_game_load(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80095050: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095054: lw          $v0, -0x54DC($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X54DC);
    // 0x80095058: addiu       $sp, $sp, -0x68
    ctx->r29 = ADD32(ctx->r29, -0X68);
    // 0x8009505C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80095060: slti        $at, $v0, 0x65
    ctx->r1 = SIGNED(ctx->r2) < 0X65 ? 1 : 0;
    // 0x80095064: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x80095068: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009506C: bne         $at, $zero, L_80095088
    if (ctx->r1 != 0) {
        // 0x80095070: or          $t1, $zero, $zero
        ctx->r9 = 0 | 0;
            goto L_80095088;
    }
    // 0x80095070: or          $t1, $zero, $zero
    ctx->r9 = 0 | 0;
    // 0x80095074: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x80095078: beq         $v0, $at, L_80095648
    if (ctx->r2 == ctx->r1) {
        // 0x8009507C: nop
    
            goto L_80095648;
    }
    // 0x8009507C: nop

    // 0x80095080: b           L_80095690
    // 0x80095084: nop

        goto L_80095690;
    // 0x80095084: nop

L_80095088:
    // 0x80095088: slti        $at, $v0, 0x49
    ctx->r1 = SIGNED(ctx->r2) < 0X49 ? 1 : 0;
    // 0x8009508C: bne         $at, $zero, L_800950A8
    if (ctx->r1 != 0) {
        // 0x80095090: addiu       $t6, $v0, -0x1
        ctx->r14 = ADD32(ctx->r2, -0X1);
            goto L_800950A8;
    }
    // 0x80095090: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x80095094: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x80095098: beq         $v0, $at, L_80095514
    if (ctx->r2 == ctx->r1) {
        // 0x8009509C: lui         $t0, 0x800E
        ctx->r8 = S32(0X800E << 16);
            goto L_80095514;
    }
    // 0x8009509C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800950A0: b           L_80095690
    // 0x800950A4: nop

        goto L_80095690;
    // 0x800950A4: nop

L_800950A8:
    // 0x800950A8: sltiu       $at, $t6, 0x48
    ctx->r1 = ctx->r14 < 0X48 ? 1 : 0;
    // 0x800950AC: beq         $at, $zero, L_80095690
    if (ctx->r1 == 0) {
        // 0x800950B0: sll         $t6, $t6, 2
        ctx->r14 = S32(ctx->r14 << 2);
            goto L_80095690;
    }
    // 0x800950B0: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800950B4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800950B8: addu        $at, $at, $t6
    gpr jr_addend_800950C0 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800950BC: lw          $t6, -0x4EB0($at)
    ctx->r14 = ADD32(ctx->r1, -0X4EB0);
    // 0x800950C0: jr          $t6
    // 0x800950C4: nop

    switch (jr_addend_800950C0 >> 2) {
        case 0: goto L_80095690; break;
        case 1: goto L_800950E0; break;
        case 2: goto L_80095690; break;
        case 3: goto L_80095690; break;
        case 4: goto L_800950C8; break;
        case 5: goto L_80095690; break;
        case 6: goto L_80095174; break;
        case 7: goto L_80095690; break;
        case 8: goto L_80095690; break;
        case 9: goto L_800952BC; break;
        case 10: goto L_80095690; break;
        case 11: goto L_80095690; break;
        case 12: goto L_80095690; break;
        case 13: goto L_80095690; break;
        case 14: goto L_80095690; break;
        case 15: goto L_80095690; break;
        case 16: goto L_80095690; break;
        case 17: goto L_80095690; break;
        case 18: goto L_80095690; break;
        case 19: goto L_800952E0; break;
        case 20: goto L_80095690; break;
        case 21: goto L_80095690; break;
        case 22: goto L_80095690; break;
        case 23: goto L_80095690; break;
        case 24: goto L_80095690; break;
        case 25: goto L_80095690; break;
        case 26: goto L_80095690; break;
        case 27: goto L_80095690; break;
        case 28: goto L_80095690; break;
        case 29: goto L_800953DC; break;
        case 30: goto L_80095690; break;
        case 31: goto L_80095690; break;
        case 32: goto L_80095690; break;
        case 33: goto L_80095690; break;
        case 34: goto L_80095690; break;
        case 35: goto L_80095690; break;
        case 36: goto L_80095690; break;
        case 37: goto L_80095690; break;
        case 38: goto L_80095690; break;
        case 39: goto L_80095174; break;
        case 40: goto L_800952AC; break;
        case 41: goto L_8009529C; break;
        case 42: goto L_80095690; break;
        case 43: goto L_80095690; break;
        case 44: goto L_80095690; break;
        case 45: goto L_80095690; break;
        case 46: goto L_80095690; break;
        case 47: goto L_80095690; break;
        case 48: goto L_80095690; break;
        case 49: goto L_8009537C; break;
        case 50: goto L_80095690; break;
        case 51: goto L_8009532C; break;
        case 52: goto L_80095690; break;
        case 53: goto L_80095600; break;
        case 54: goto L_80095690; break;
        case 55: goto L_800955B0; break;
        case 56: goto L_80095690; break;
        case 57: goto L_80095690; break;
        case 58: goto L_80095690; break;
        case 59: goto L_80095460; break;
        case 60: goto L_80095690; break;
        case 61: goto L_80095478; break;
        case 62: goto L_80095690; break;
        case 63: goto L_800954CC; break;
        case 64: goto L_80095690; break;
        case 65: goto L_800954E4; break;
        case 66: goto L_80095690; break;
        case 67: goto L_8009549C; break;
        case 68: goto L_80095690; break;
        case 69: goto L_800954FC; break;
        case 70: goto L_80095690; break;
        case 71: goto L_800954B4; break;
        default: switch_error(__func__, 0x800950C0, 0x800EB150);
    }
    // 0x800950C4: nop

L_800950C8:
    // 0x800950C8: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800950CC: addiu       $a3, $a3, -0x3900
    ctx->r7 = ADD32(ctx->r7, -0X3900);
    // 0x800950D0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800950D4: addiu       $a2, $zero, 0x3
    ctx->r6 = ADD32(0, 0X3);
    // 0x800950D8: b           L_80095690
    // 0x800950DC: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800950DC: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800950E0:
    // 0x800950E0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800950E4: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x800950E8: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x800950EC: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800950F0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800950F4: bgez        $a0, L_80095100
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800950F8: addiu       $v1, $v1, -0x38D8
        ctx->r3 = ADD32(ctx->r3, -0X38D8);
            goto L_80095100;
    }
    // 0x800950F8: addiu       $v1, $v1, -0x38D8
    ctx->r3 = ADD32(ctx->r3, -0X38D8);
    // 0x800950FC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095100:
    // 0x80095100: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095104: bne         $at, $zero, L_80095110
    if (ctx->r1 != 0) {
        // 0x80095108: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_80095110;
    }
    // 0x80095108: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x8009510C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095110:
    // 0x80095110: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
    // 0x80095114: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x80095118: lw          $t7, -0x3B10($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X3B10);
    // 0x8009511C: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80095120: addu        $t8, $t8, $v0
    ctx->r24 = ADD32(ctx->r24, ctx->r2);
    // 0x80095124: sw          $t7, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r15;
    // 0x80095128: lw          $t8, -0x3968($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3968);
    // 0x8009512C: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80095130: addu        $t9, $t9, $v0
    ctx->r25 = ADD32(ctx->r25, ctx->r2);
    // 0x80095134: sw          $t8, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r24;
    // 0x80095138: lw          $t9, -0x3F1C($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X3F1C);
    // 0x8009513C: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095140: addu        $t2, $t2, $v0
    ctx->r10 = ADD32(ctx->r10, ctx->r2);
    // 0x80095144: sw          $t9, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r25;
    // 0x80095148: lw          $t2, -0x3E74($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X3E74);
    // 0x8009514C: lui         $t3, 0x2
    ctx->r11 = S32(0X2 << 16);
    // 0x80095150: lui         $at, 0x8031
    ctx->r1 = S32(0X8031 << 16);
    // 0x80095154: ori         $at, $at, 0x6800
    ctx->r1 = ctx->r1 | 0X6800;
    // 0x80095158: addiu       $t3, $t3, 0x3930
    ctx->r11 = ADD32(ctx->r11, 0X3930);
    // 0x8009515C: addu        $t4, $t3, $at
    ctx->r12 = ADD32(ctx->r11, ctx->r1);
    // 0x80095160: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095164: sw          $t2, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r10;
    // 0x80095168: sw          $t4, -0x1668($at)
    MEM_W(-0X1668, ctx->r1) = ctx->r12;
    // 0x8009516C: b           L_80095690
    // 0x80095170: sw          $v1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r3;
        goto L_80095690;
    // 0x80095170: sw          $v1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r3;
L_80095174:
    { extern void wr64_sunny_detail_begin_load(uint8_t*); wr64_sunny_detail_begin_load(rdram); }
    // 0x80095174: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80095178: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x8009517C: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x80095180: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80095184: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80095188: bgez        $a0, L_80095194
    if (SIGNED(ctx->r4) >= 0) {
        // 0x8009518C: addiu       $v1, $v1, -0x19F8
        ctx->r3 = ADD32(ctx->r3, -0X19F8);
            goto L_80095194;
    }
    // 0x8009518C: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x80095190: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095194:
    // 0x80095194: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095198: bnel        $at, $zero, L_800951A8
    if (ctx->r1 != 0) {
        // 0x8009519C: lh          $t5, 0x4($v1)
        ctx->r13 = MEM_H(ctx->r3, 0X4);
            goto L_800951A8;
    }
    goto skip_0;
    // 0x8009519C: lh          $t5, 0x4($v1)
    ctx->r13 = MEM_H(ctx->r3, 0X4);
    skip_0:
    // 0x800951A0: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
    // 0x800951A4: lh          $t5, 0x4($v1)
    ctx->r13 = MEM_H(ctx->r3, 0X4);
L_800951A8:
    // 0x800951A8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800951AC: bnel        $t5, $at, L_8009524C
    if (ctx->r13 != ctx->r1) {
        // 0x800951B0: sll         $v0, $a0, 2
        ctx->r2 = S32(ctx->r4 << 2);
            goto L_8009524C;
    }
    goto skip_1;
    // 0x800951B0: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
    skip_1:
    // 0x800951B4: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800951B8: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800951BC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800951C0: beq         $v0, $zero, L_800951E0
    if (ctx->r2 == 0) {
        // 0x800951C4: lui         $t3, 0x800E
        ctx->r11 = S32(0X800E << 16);
            goto L_800951E0;
    }
    // 0x800951C4: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800951C8: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x800951CC: beq         $v0, $at, L_800951E8
    if (ctx->r2 == ctx->r1) {
        // 0x800951D0: lui         $a3, 0x800E
        ctx->r7 = S32(0X800E << 16);
            goto L_800951E8;
    }
    // 0x800951D0: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800951D4: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800951D8: b           L_800951EC
    // 0x800951DC: addiu       $a3, $a3, -0x3798
    ctx->r7 = ADD32(ctx->r7, -0X3798);
        goto L_800951EC;
    // 0x800951DC: addiu       $a3, $a3, -0x3798
    ctx->r7 = ADD32(ctx->r7, -0X3798);
L_800951E0:
    // 0x800951E0: b           L_800951EC
    // 0x800951E4: addiu       $a3, $a3, -0x3774
    ctx->r7 = ADD32(ctx->r7, -0X3774);
        goto L_800951EC;
    // 0x800951E4: addiu       $a3, $a3, -0x3774
    ctx->r7 = ADD32(ctx->r7, -0X3774);
L_800951E8:
    // 0x800951E8: addiu       $a3, $a3, -0x3750
    ctx->r7 = ADD32(ctx->r7, -0X3750);
L_800951EC:
    // 0x800951EC: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
    // 0x800951F0: addu        $t6, $t6, $v0
    ctx->r14 = ADD32(ctx->r14, ctx->r2);
    // 0x800951F4: lw          $t6, -0x3B10($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X3B10);
    // 0x800951F8: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800951FC: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x80095200: sw          $t6, 0x8($a3)
    MEM_W(0X8, ctx->r7) = ctx->r14;
    // 0x80095204: lw          $t7, -0x3968($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X3968);
    // 0x80095208: addu        $t3, $t3, $v0
    ctx->r11 = ADD32(ctx->r11, ctx->r2);
    // 0x8009520C: sw          $t7, 0xC($a3)
    MEM_W(0XC, ctx->r7) = ctx->r15;
    // 0x80095210: lw          $t8, 0x0($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X0);
    // 0x80095214: bnel        $t8, $zero, L_8009523C
    if (ctx->r24 != 0) {
        // 0x80095218: sw          $zero, 0x1C($a3)
        MEM_W(0X1C, ctx->r7) = 0;
            goto L_8009523C;
    }
    goto skip_2;
    // 0x80095218: sw          $zero, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = 0;
    skip_2:
    // 0x8009521C: lw          $t9, 0x0($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X0);
    // 0x80095220: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80095224: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095228: bne         $t9, $at, L_80095238
    if (ctx->r25 != ctx->r1) {
        // 0x8009522C: addiu       $t2, $t2, -0x38B8
        ctx->r10 = ADD32(ctx->r10, -0X38B8);
            goto L_80095238;
    }
    // 0x8009522C: addiu       $t2, $t2, -0x38B8
    ctx->r10 = ADD32(ctx->r10, -0X38B8);
    // 0x80095230: b           L_8009523C
    // 0x80095234: sw          $t2, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = ctx->r10;
        goto L_8009523C;
    // 0x80095234: sw          $t2, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = ctx->r10;
L_80095238:
    // 0x80095238: sw          $zero, 0x1C($a3)
    MEM_W(0X1C, ctx->r7) = 0;
L_8009523C:
    // 0x8009523C: lw          $t3, -0x3F1C($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X3F1C);
    // 0x80095240: b           L_80095284
    // 0x80095244: sw          $t3, 0x10($a3)
    MEM_W(0X10, ctx->r7) = ctx->r11;
        goto L_80095284;
    // 0x80095244: sw          $t3, 0x10($a3)
    MEM_W(0X10, ctx->r7) = ctx->r11;
    // 0x80095248: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
L_8009524C:
    // 0x8009524C: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x80095250: addu        $t4, $t4, $v0
    ctx->r12 = ADD32(ctx->r12, ctx->r2);
    // 0x80095254: lw          $t4, -0x3AEC($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X3AEC);
    // 0x80095258: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x8009525C: addiu       $a3, $v1, -0x372C
    ctx->r7 = ADD32(ctx->r3, -0X372C);
    // 0x80095260: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x80095264: addu        $t5, $t5, $v0
    ctx->r13 = ADD32(ctx->r13, ctx->r2);
    // 0x80095268: sw          $t4, 0x8($a3)
    MEM_W(0X8, ctx->r7) = ctx->r12;
    // 0x8009526C: lw          $t5, -0x3944($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X3944);
    // 0x80095270: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80095274: addu        $t6, $t6, $v0
    ctx->r14 = ADD32(ctx->r14, ctx->r2);
    // 0x80095278: sw          $t5, 0xC($a3)
    MEM_W(0XC, ctx->r7) = ctx->r13;
    // 0x8009527C: lw          $t6, -0x3EF8($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X3EF8);
    // 0x80095280: sw          $t6, 0x10($a3)
    MEM_W(0X10, ctx->r7) = ctx->r14;
L_80095284:
    // 0x80095284: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80095288: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x8009528C: lw          $t7, -0x3E74($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X3E74);
    // 0x80095290: sw          $t7, 0x14($a3)
    MEM_W(0X14, ctx->r7) = ctx->r15;
    // 0x80095294: b           L_80095690
    // 0x80095298: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x80095298: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_8009529C:
    // 0x8009529C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800952A0: addiu       $a3, $a3, -0x3798
    ctx->r7 = ADD32(ctx->r7, -0X3798);
    // 0x800952A4: b           L_80095690
    // 0x800952A8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800952A8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800952AC:
    // 0x800952AC: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800952B0: addiu       $a3, $a3, -0x3798
    ctx->r7 = ADD32(ctx->r7, -0X3798);
    // 0x800952B4: b           L_80095690
    // 0x800952B8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800952B8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800952BC:
    // 0x800952BC: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800952C0: lw          $t8, -0x3F1C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3F1C);
    // 0x800952C4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800952C8: addiu       $v0, $v0, -0x36C4
    ctx->r2 = ADD32(ctx->r2, -0X36C4);
    // 0x800952CC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800952D0: addiu       $a2, $zero, 0x2
    ctx->r6 = ADD32(0, 0X2);
    // 0x800952D4: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x800952D8: b           L_80095690
    // 0x800952DC: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
        goto L_80095690;
    // 0x800952DC: sw          $t8, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r24;
L_800952E0:
    // 0x800952E0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800952E4: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x800952E8: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x800952EC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800952F0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800952F4: bgez        $a0, L_80095300
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800952F8: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_80095300;
    }
    // 0x800952F8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800952FC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095300:
    // 0x80095300: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095304: bne         $at, $zero, L_80095310
    if (ctx->r1 != 0) {
        // 0x80095308: addiu       $v0, $v0, -0x3604
        ctx->r2 = ADD32(ctx->r2, -0X3604);
            goto L_80095310;
    }
    // 0x80095308: addiu       $v0, $v0, -0x3604
    ctx->r2 = ADD32(ctx->r2, -0X3604);
    // 0x8009530C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095310:
    // 0x80095310: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x80095314: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095318: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x8009531C: lw          $t2, -0x3F1C($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X3F1C);
    // 0x80095320: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x80095324: b           L_80095690
    // 0x80095328: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
        goto L_80095690;
    // 0x80095328: sw          $t2, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r10;
L_8009532C:
    // 0x8009532C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80095330: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x80095334: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x80095338: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x8009533C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80095340: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80095344: bgez        $a0, L_80095350
    if (SIGNED(ctx->r4) >= 0) {
        // 0x80095348: addiu       $a3, $a3, -0x35C8
        ctx->r7 = ADD32(ctx->r7, -0X35C8);
            goto L_80095350;
    }
    // 0x80095348: addiu       $a3, $a3, -0x35C8
    ctx->r7 = ADD32(ctx->r7, -0X35C8);
    // 0x8009534C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095350:
    // 0x80095350: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095354: bne         $at, $zero, L_80095360
    if (ctx->r1 != 0) {
        // 0x80095358: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_80095360;
    }
    // 0x80095358: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x8009535C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095360:
    // 0x80095360: sll         $t3, $a0, 2
    ctx->r11 = S32(ctx->r4 << 2);
    // 0x80095364: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x80095368: lw          $t4, -0x3F1C($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X3F1C);
    // 0x8009536C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x80095370: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
    // 0x80095374: b           L_80095690
    // 0x80095378: sw          $t4, -0x35C4($at)
    MEM_W(-0X35C4, ctx->r1) = ctx->r12;
        goto L_80095690;
    // 0x80095378: sw          $t4, -0x35C4($at)
    MEM_W(-0X35C4, ctx->r1) = ctx->r12;
L_8009537C:
    // 0x8009537C: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x80095380: lw          $t5, -0x19CC($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X19CC);
    // 0x80095384: addiu       $at, $zero, 0x64
    ctx->r1 = ADD32(0, 0X64);
    // 0x80095388: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009538C: beq         $t5, $at, L_800953D4
    if (ctx->r13 == ctx->r1) {
        // 0x80095390: addiu       $t0, $t0, -0x7E90
        ctx->r8 = ADD32(ctx->r8, -0X7E90);
            goto L_800953D4;
    }
    // 0x80095390: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x80095394: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x80095398: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009539C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800953A0: bgez        $a0, L_800953AC
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800953A4: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_800953AC;
    }
    // 0x800953A4: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800953A8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_800953AC:
    // 0x800953AC: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x800953B0: bne         $at, $zero, L_800953BC
    if (ctx->r1 != 0) {
        // 0x800953B4: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_800953BC;
    }
    // 0x800953B4: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800953B8: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_800953BC:
    // 0x800953BC: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800953C0: addu        $t7, $t7, $t6
    ctx->r15 = ADD32(ctx->r15, ctx->r14);
    // 0x800953C4: lw          $t7, -0x3F1C($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X3F1C);
    // 0x800953C8: addiu       $v0, $v0, -0x356C
    ctx->r2 = ADD32(ctx->r2, -0X356C);
    // 0x800953CC: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x800953D0: sw          $t7, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r15;
L_800953D4:
    // 0x800953D4: b           L_80095690
    // 0x800953D8: nop

        goto L_80095690;
    // 0x800953D8: nop

L_800953DC:
    // 0x800953DC: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800953E0: lw          $a0, -0x4CD0($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X4CD0);
    // 0x800953E4: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x800953E8: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800953EC: bgez        $a0, L_800953F8
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800953F0: addiu       $v1, $v1, -0x33F8
        ctx->r3 = ADD32(ctx->r3, -0X33F8);
            goto L_800953F8;
    }
    // 0x800953F0: addiu       $v1, $v1, -0x33F8
    ctx->r3 = ADD32(ctx->r3, -0X33F8);
    // 0x800953F4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_800953F8:
    // 0x800953F8: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x800953FC: bne         $at, $zero, L_80095408
    if (ctx->r1 != 0) {
        // 0x80095400: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_80095408;
    }
    // 0x80095400: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80095404: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095408:
    // 0x80095408: sll         $v0, $a0, 2
    ctx->r2 = S32(ctx->r4 << 2);
    // 0x8009540C: addu        $t8, $t8, $v0
    ctx->r24 = ADD32(ctx->r24, ctx->r2);
    // 0x80095410: lw          $t8, -0x3B10($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3B10);
    // 0x80095414: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80095418: addu        $t9, $t9, $v0
    ctx->r25 = ADD32(ctx->r25, ctx->r2);
    // 0x8009541C: sw          $t8, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r24;
    // 0x80095420: lw          $t9, -0x3968($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X3968);
    // 0x80095424: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095428: addu        $t2, $t2, $v0
    ctx->r10 = ADD32(ctx->r10, ctx->r2);
    // 0x8009542C: sw          $t9, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r25;
    // 0x80095430: lw          $t2, -0x3F1C($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X3F1C);
    // 0x80095434: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x80095438: addu        $t3, $t3, $v0
    ctx->r11 = ADD32(ctx->r11, ctx->r2);
    // 0x8009543C: sw          $t2, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r10;
    // 0x80095440: lw          $t3, -0x341C($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X341C);
    // 0x80095444: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x80095448: addu        $t4, $t4, $v0
    ctx->r12 = ADD32(ctx->r12, ctx->r2);
    // 0x8009544C: sw          $t3, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r11;
    // 0x80095450: lw          $t4, -0x3E74($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X3E74);
    // 0x80095454: sw          $v1, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r3;
    // 0x80095458: b           L_80095690
    // 0x8009545C: sw          $t4, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r12;
        goto L_80095690;
    // 0x8009545C: sw          $t4, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r12;
L_80095460:
    // 0x80095460: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x80095464: addiu       $a3, $a3, -0x33B4
    ctx->r7 = ADD32(ctx->r7, -0X33B4);
    // 0x80095468: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009546C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80095470: b           L_80095690
    // 0x80095474: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x80095474: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_80095478:
    // 0x80095478: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x8009547C: lw          $t5, -0x3F1C($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X3F1C);
    // 0x80095480: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095484: addiu       $v0, $v0, -0x338C
    ctx->r2 = ADD32(ctx->r2, -0X338C);
    // 0x80095488: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009548C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80095490: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x80095494: b           L_80095690
    // 0x80095498: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
        goto L_80095690;
    // 0x80095498: sw          $t5, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r13;
L_8009549C:
    // 0x8009549C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800954A0: addiu       $a3, $a3, -0x3330
    ctx->r7 = ADD32(ctx->r7, -0X3330);
    // 0x800954A4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800954A8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800954AC: b           L_80095690
    // 0x800954B0: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800954B0: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800954B4:
    // 0x800954B4: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800954B8: addiu       $a3, $a3, -0x3308
    ctx->r7 = ADD32(ctx->r7, -0X3308);
    // 0x800954BC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800954C0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800954C4: b           L_80095690
    // 0x800954C8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800954C8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800954CC:
    // 0x800954CC: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800954D0: addiu       $a3, $a3, -0x32B8
    ctx->r7 = ADD32(ctx->r7, -0X32B8);
    // 0x800954D4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800954D8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800954DC: b           L_80095690
    // 0x800954E0: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800954E0: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800954E4:
    // 0x800954E4: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800954E8: addiu       $a3, $a3, -0x335C
    ctx->r7 = ADD32(ctx->r7, -0X335C);
    // 0x800954EC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800954F0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800954F4: b           L_80095690
    // 0x800954F8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x800954F8: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_800954FC:
    // 0x800954FC: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x80095500: addiu       $a3, $a3, -0x32E0
    ctx->r7 = ADD32(ctx->r7, -0X32E0);
    // 0x80095504: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80095508: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009550C: b           L_80095690
    // 0x80095510: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
        goto L_80095690;
    // 0x80095510: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
L_80095514:
    // 0x80095514: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x80095518: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x8009551C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80095520: addiu       $v1, $v1, -0x19F8
    ctx->r3 = ADD32(ctx->r3, -0X19F8);
    // 0x80095524: bgez        $a0, L_80095530
    if (SIGNED(ctx->r4) >= 0) {
        // 0x80095528: lui         $t6, 0x801D
        ctx->r14 = S32(0X801D << 16);
            goto L_80095530;
    }
    // 0x80095528: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8009552C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095530:
    // 0x80095530: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095534: bne         $at, $zero, L_80095540
    if (ctx->r1 != 0) {
        // 0x80095538: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_80095540;
    }
    // 0x80095538: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x8009553C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095540:
    // 0x80095540: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x80095544: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80095548: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x8009554C: bne         $v0, $at, L_80095580
    if (ctx->r2 != ctx->r1) {
        // 0x80095550: addu        $t8, $t8, $t7
        ctx->r24 = ADD32(ctx->r24, ctx->r15);
            goto L_80095580;
    }
    // 0x80095550: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x80095554: lw          $t6, -0x19CC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19CC);
    // 0x80095558: addiu       $at, $zero, 0x67
    ctx->r1 = ADD32(0, 0X67);
    // 0x8009555C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095560: bne         $t6, $at, L_80095570
    if (ctx->r14 != ctx->r1) {
        // 0x80095564: addiu       $v0, $v0, -0x3598
        ctx->r2 = ADD32(ctx->r2, -0X3598);
            goto L_80095570;
    }
    // 0x80095564: addiu       $v0, $v0, -0x3598
    ctx->r2 = ADD32(ctx->r2, -0X3598);
    // 0x80095568: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009556C: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
L_80095570:
    // 0x80095570: lw          $t8, -0x3F1C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3F1C);
    // 0x80095574: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x80095578: b           L_800955A8
    // 0x8009557C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
        goto L_800955A8;
    // 0x8009557C: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
L_80095580:
    // 0x80095580: bne         $v0, $zero, L_800955A8
    if (ctx->r2 != 0) {
        // 0x80095584: sll         $t9, $a0, 2
        ctx->r25 = S32(ctx->r4 << 2);
            goto L_800955A8;
    }
    // 0x80095584: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x80095588: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x8009558C: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x80095590: lw          $t2, -0x3F1C($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X3F1C);
    // 0x80095594: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095598: addiu       $v0, $v0, -0x356C
    ctx->r2 = ADD32(ctx->r2, -0X356C);
    // 0x8009559C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800955A0: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x800955A4: sw          $t2, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r10;
L_800955A8:
    // 0x800955A8: b           L_80095690
    // 0x800955AC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
        goto L_80095690;
    // 0x800955AC: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_800955B0:
    // 0x800955B0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800955B4: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x800955B8: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x800955BC: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x800955C0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800955C4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800955C8: bgez        $a0, L_800955D4
    if (SIGNED(ctx->r4) >= 0) {
        // 0x800955CC: addiu       $a3, $a3, -0x327C
        ctx->r7 = ADD32(ctx->r7, -0X327C);
            goto L_800955D4;
    }
    // 0x800955CC: addiu       $a3, $a3, -0x327C
    ctx->r7 = ADD32(ctx->r7, -0X327C);
    // 0x800955D0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_800955D4:
    // 0x800955D4: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x800955D8: bne         $at, $zero, L_800955E4
    if (ctx->r1 != 0) {
        // 0x800955DC: lui         $t4, 0x800E
        ctx->r12 = S32(0X800E << 16);
            goto L_800955E4;
    }
    // 0x800955DC: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x800955E0: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_800955E4:
    // 0x800955E4: sll         $t3, $a0, 2
    ctx->r11 = S32(ctx->r4 << 2);
    // 0x800955E8: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x800955EC: lw          $t4, -0x3F1C($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X3F1C);
    // 0x800955F0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800955F4: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
    // 0x800955F8: b           L_80095690
    // 0x800955FC: sw          $t4, -0x3278($at)
    MEM_W(-0X3278, ctx->r1) = ctx->r12;
        goto L_80095690;
    // 0x800955FC: sw          $t4, -0x3278($at)
    MEM_W(-0X3278, ctx->r1) = ctx->r12;
L_80095600:
    // 0x80095600: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80095604: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x80095608: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x8009560C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095610: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80095614: bgez        $a0, L_80095620
    if (SIGNED(ctx->r4) >= 0) {
        // 0x80095618: addiu       $v0, $v0, -0x324C
        ctx->r2 = ADD32(ctx->r2, -0X324C);
            goto L_80095620;
    }
    // 0x80095618: addiu       $v0, $v0, -0x324C
    ctx->r2 = ADD32(ctx->r2, -0X324C);
    // 0x8009561C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095620:
    // 0x80095620: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x80095624: bne         $at, $zero, L_80095630
    if (ctx->r1 != 0) {
        // 0x80095628: lui         $t6, 0x800E
        ctx->r14 = S32(0X800E << 16);
            goto L_80095630;
    }
    // 0x80095628: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009562C: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095630:
    // 0x80095630: sll         $t5, $a0, 2
    ctx->r13 = S32(ctx->r4 << 2);
    // 0x80095634: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x80095638: lw          $t6, -0x3F1C($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X3F1C);
    // 0x8009563C: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x80095640: b           L_80095690
    // 0x80095644: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
        goto L_80095690;
    // 0x80095644: sw          $t6, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r14;
L_80095648:
    // 0x80095648: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009564C: addiu       $t0, $t0, -0x7E90
    ctx->r8 = ADD32(ctx->r8, -0X7E90);
    // 0x80095650: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x80095654: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x80095658: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    // 0x8009565C: bgez        $a0, L_80095668
    if (SIGNED(ctx->r4) >= 0) {
        // 0x80095660: lui         $v0, 0x800E
        ctx->r2 = S32(0X800E << 16);
            goto L_80095668;
    }
    // 0x80095660: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80095664: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80095668:
    // 0x80095668: slti        $at, $a0, 0x9
    ctx->r1 = SIGNED(ctx->r4) < 0X9 ? 1 : 0;
    // 0x8009566C: bne         $at, $zero, L_80095678
    if (ctx->r1 != 0) {
        // 0x80095670: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_80095678;
    }
    // 0x80095670: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80095674: addiu       $a0, $zero, 0x8
    ctx->r4 = ADD32(0, 0X8);
L_80095678:
    // 0x80095678: sll         $t7, $a0, 2
    ctx->r15 = S32(ctx->r4 << 2);
    // 0x8009567C: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x80095680: lw          $t8, -0x3F1C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X3F1C);
    // 0x80095684: addiu       $v0, $v0, -0x3200
    ctx->r2 = ADD32(ctx->r2, -0X3200);
    // 0x80095688: sw          $v0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r2;
    // 0x8009568C: sw          $t8, 0xC($v0)
    MEM_W(0XC, ctx->r2) = ctx->r24;
L_80095690:
    // 0x80095690: beq         $a1, $zero, L_80095A18
    if (ctx->r5 == 0) {
        // 0x80095694: lw          $a3, 0x48($sp)
        ctx->r7 = MEM_W(ctx->r29, 0X48);
            goto L_80095A18;
    }
    // 0x80095694: lw          $a3, 0x48($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X48);
    // 0x80095698: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x8009569C: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x800956A0: addu        $t2, $t2, $t9
    ctx->r10 = ADD32(ctx->r10, ctx->r25);
    // 0x800956A4: lw          $a0, -0x317C($t2)
    ctx->r4 = MEM_W(ctx->r10, -0X317C);
    // 0x800956A8: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x800956AC: addiu       $v0, $v0, 0x45F0
    ctx->r2 = ADD32(ctx->r2, 0X45F0);
    // 0x800956B0: sw          $a3, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r7;
    // 0x800956B4: sw          $t1, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r9;
    // 0x800956B8: jal         0x800C5720
    // 0x800956BC: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_0;
    // 0x800956BC: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    after_0:
    // 0x800956C0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800956C4: sw          $v0, -0x1930($at)
    MEM_W(-0X1930, ctx->r1) = ctx->r2;
    // 0x800956C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800956CC: sw          $zero, -0x18D0($at)
    MEM_W(-0X18D0, ctx->r1) = 0;
    // 0x800956D0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800956D4: lw          $a3, 0x48($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X48);
    // 0x800956D8: sw          $zero, -0x18CC($at)
    MEM_W(-0X18CC, ctx->r1) = 0;
    // 0x800956DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800956E0: sw          $zero, -0x18C8($at)
    MEM_W(-0X18C8, ctx->r1) = 0;
    // 0x800956E4: lw          $t3, 0x0($a3)
    ctx->r11 = MEM_W(ctx->r7, 0X0);
    // 0x800956E8: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
    // 0x800956EC: beq         $t3, $zero, L_80095718
    if (ctx->r11 == 0) {
        // 0x800956F0: nop
    
            goto L_80095718;
    }
    // 0x800956F0: nop

    // 0x800956F4: lw          $v1, 0x0($a3)
    ctx->r3 = MEM_W(ctx->r7, 0X0);
    // 0x800956F8: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
L_800956FC:
    // 0x800956FC: jal         0x80095A28
    // 0x80095700: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    func_80095A28(rdram, ctx);
        goto after_1;
    // 0x80095700: sw          $v0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r2;
    after_1:
    // 0x80095704: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x80095708: lw          $v1, 0x4($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X4);
    // 0x8009570C: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x80095710: bnel        $v1, $zero, L_800956FC
    if (ctx->r3 != 0) {
        // 0x80095714: or          $a0, $v1, $zero
        ctx->r4 = ctx->r3 | 0;
            goto L_800956FC;
    }
    goto skip_3;
    // 0x80095714: or          $a0, $v1, $zero
    ctx->r4 = ctx->r3 | 0;
    skip_3:
L_80095718:
    // 0x80095718: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x8009571C: lw          $t4, -0x18D0($t4)
    ctx->r12 = MEM_W(ctx->r12, -0X18D0);
    // 0x80095720: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x80095724: addiu       $a3, $a3, -0x18A0
    ctx->r7 = ADD32(ctx->r7, -0X18A0);
    // 0x80095728: blez        $t4, L_80095984
    if (SIGNED(ctx->r12) <= 0) {
        // 0x8009572C: lui         $t0, 0x8015
        ctx->r8 = S32(0X8015 << 16);
            goto L_80095984;
    }
    // 0x8009572C: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x80095730: lw          $a0, 0x0($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X0);
    // 0x80095734: addiu       $a2, $zero, -0x1
    ctx->r6 = ADD32(0, -0X1);
    // 0x80095738: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x8009573C: beq         $a2, $a0, L_800957A4
    if (ctx->r6 == ctx->r4) {
        // 0x80095740: addiu       $v0, $v0, 0x7A60
        ctx->r2 = ADD32(ctx->r2, 0X7A60);
            goto L_800957A4;
    }
    // 0x80095740: addiu       $v0, $v0, 0x7A60
    ctx->r2 = ADD32(ctx->r2, 0X7A60);
    // 0x80095744: lw          $t5, 0x30($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X30);
    // 0x80095748: lw          $t6, 0x34($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X34);
    // 0x8009574C: lw          $t7, 0x38($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X38);
    // 0x80095750: lw          $t8, 0x3C($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X3C);
    // 0x80095754: lw          $t9, 0x40($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X40);
    // 0x80095758: sll         $t2, $a0, 4
    ctx->r10 = S32(ctx->r4 << 4);
    // 0x8009575C: addu        $t2, $t2, $a0
    ctx->r10 = ADD32(ctx->r10, ctx->r4);
    // 0x80095760: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x80095764: addu        $v1, $v0, $t2
    ctx->r3 = ADD32(ctx->r2, ctx->r10);
    // 0x80095768: sw          $t5, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r13;
    // 0x8009576C: sw          $t6, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r14;
    // 0x80095770: sw          $t7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r15;
    // 0x80095774: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x80095778: sw          $t9, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r25;
    // 0x8009577C: lw          $t3, 0x30($v1)
    ctx->r11 = MEM_W(ctx->r3, 0X30);
    // 0x80095780: sw          $t3, 0x30($v0)
    MEM_W(0X30, ctx->r2) = ctx->r11;
    // 0x80095784: lw          $t4, 0x34($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X34);
    // 0x80095788: sw          $t4, 0x34($v0)
    MEM_W(0X34, ctx->r2) = ctx->r12;
    // 0x8009578C: lw          $t5, 0x38($v1)
    ctx->r13 = MEM_W(ctx->r3, 0X38);
    // 0x80095790: sw          $t5, 0x38($v0)
    MEM_W(0X38, ctx->r2) = ctx->r13;
    // 0x80095794: lw          $t6, 0x3C($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X3C);
    // 0x80095798: sw          $t6, 0x3C($v0)
    MEM_W(0X3C, ctx->r2) = ctx->r14;
    // 0x8009579C: lw          $t7, 0x40($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X40);
    // 0x800957A0: sw          $t7, 0x40($v0)
    MEM_W(0X40, ctx->r2) = ctx->r15;
L_800957A4:
    // 0x800957A4: lw          $a1, 0x4($a3)
    ctx->r5 = MEM_W(ctx->r7, 0X4);
    // 0x800957A8: lui         $v0, 0x8022
    ctx->r2 = S32(0X8022 << 16);
    // 0x800957AC: addiu       $v0, $v0, 0x7A60
    ctx->r2 = ADD32(ctx->r2, 0X7A60);
    // 0x800957B0: beq         $a2, $a1, L_8009584C
    if (ctx->r6 == ctx->r5) {
        // 0x800957B4: nop
    
            goto L_8009584C;
    }
    // 0x800957B4: nop

    // 0x800957B8: bne         $a1, $zero, L_80095804
    if (ctx->r5 != 0) {
        // 0x800957BC: sll         $t5, $a1, 4
        ctx->r13 = S32(ctx->r5 << 4);
            goto L_80095804;
    }
    // 0x800957BC: sll         $t5, $a1, 4
    ctx->r13 = S32(ctx->r5 << 4);
    // 0x800957C0: beq         $a2, $a0, L_80095804
    if (ctx->r6 == ctx->r4) {
        // 0x800957C4: lw          $t8, 0x44($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X44);
            goto L_80095804;
    }
    // 0x800957C4: lw          $t8, 0x44($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X44);
    // 0x800957C8: lw          $t9, 0x40($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X40);
    // 0x800957CC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800957D0: sw          $t8, 0x7AD4($at)
    MEM_W(0X7AD4, ctx->r1) = ctx->r24;
    // 0x800957D4: lw          $t2, 0x3C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X3C);
    // 0x800957D8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800957DC: sw          $t9, 0x7AD8($at)
    MEM_W(0X7AD8, ctx->r1) = ctx->r25;
    // 0x800957E0: lw          $t3, 0x38($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X38);
    // 0x800957E4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800957E8: sw          $t2, 0x7ADC($at)
    MEM_W(0X7ADC, ctx->r1) = ctx->r10;
    // 0x800957EC: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800957F0: lw          $t4, 0x34($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X34);
    // 0x800957F4: sw          $t3, 0x7AE0($at)
    MEM_W(0X7AE0, ctx->r1) = ctx->r11;
    // 0x800957F8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800957FC: b           L_8009584C
    // 0x80095800: sw          $t4, 0x7AE4($at)
    MEM_W(0X7AE4, ctx->r1) = ctx->r12;
        goto L_8009584C;
    // 0x80095800: sw          $t4, 0x7AE4($at)
    MEM_W(0X7AE4, ctx->r1) = ctx->r12;
L_80095804:
    // 0x80095804: addu        $t5, $t5, $a1
    ctx->r13 = ADD32(ctx->r13, ctx->r5);
    // 0x80095808: sll         $t5, $t5, 2
    ctx->r13 = S32(ctx->r13 << 2);
    // 0x8009580C: addu        $v1, $v0, $t5
    ctx->r3 = ADD32(ctx->r2, ctx->r13);
    // 0x80095810: lw          $t6, 0x30($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X30);
    // 0x80095814: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x80095818: sw          $t6, 0x7AD4($at)
    MEM_W(0X7AD4, ctx->r1) = ctx->r14;
    // 0x8009581C: lw          $t7, 0x34($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X34);
    // 0x80095820: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x80095824: sw          $t7, 0x7AD8($at)
    MEM_W(0X7AD8, ctx->r1) = ctx->r15;
    // 0x80095828: lw          $t8, 0x38($v1)
    ctx->r24 = MEM_W(ctx->r3, 0X38);
    // 0x8009582C: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x80095830: sw          $t8, 0x7ADC($at)
    MEM_W(0X7ADC, ctx->r1) = ctx->r24;
    // 0x80095834: lw          $t9, 0x3C($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X3C);
    // 0x80095838: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x8009583C: sw          $t9, 0x7AE0($at)
    MEM_W(0X7AE0, ctx->r1) = ctx->r25;
    // 0x80095840: lw          $t2, 0x40($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X40);
    // 0x80095844: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x80095848: sw          $t2, 0x7AE4($at)
    MEM_W(0X7AE4, ctx->r1) = ctx->r10;
L_8009584C:
    // 0x8009584C: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80095850: lw          $t3, -0x18C4($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X18C4);
    // 0x80095854: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80095858: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x8009585C: bne         $t3, $at, L_80095894
    if (ctx->r11 != ctx->r1) {
        // 0x80095860: lui         $a0, 0x800E
        ctx->r4 = S32(0X800E << 16);
            goto L_80095894;
    }
    // 0x80095860: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80095864: lw          $t4, 0x94($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X94);
    // 0x80095868: lw          $t5, 0xD8($v0)
    ctx->r13 = MEM_W(ctx->r2, 0XD8);
    // 0x8009586C: lw          $t6, 0x4($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X4);
    // 0x80095870: lw          $t7, 0xC($v0)
    ctx->r15 = MEM_W(ctx->r2, 0XC);
    // 0x80095874: lw          $t8, 0x48($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X48);
    // 0x80095878: lw          $t9, 0x50($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X50);
    // 0x8009587C: sw          $t4, 0x11C($v0)
    MEM_W(0X11C, ctx->r2) = ctx->r12;
    // 0x80095880: sw          $t5, 0x160($v0)
    MEM_W(0X160, ctx->r2) = ctx->r13;
    // 0x80095884: sw          $t6, 0x8C($v0)
    MEM_W(0X8C, ctx->r2) = ctx->r14;
    // 0x80095888: sw          $t7, 0x94($v0)
    MEM_W(0X94, ctx->r2) = ctx->r15;
    // 0x8009588C: sw          $t8, 0xD0($v0)
    MEM_W(0XD0, ctx->r2) = ctx->r24;
    // 0x80095890: sw          $t9, 0xD8($v0)
    MEM_W(0XD8, ctx->r2) = ctx->r25;
L_80095894:
    // 0x80095894: lw          $t2, -0x54DC($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X54DC);
    // 0x80095898: addiu       $at, $zero, 0x66
    ctx->r1 = ADD32(0, 0X66);
    // 0x8009589C: addiu       $a0, $a0, -0x3168
    ctx->r4 = ADD32(ctx->r4, -0X3168);
    // 0x800958A0: bne         $t2, $at, L_80095984
    if (ctx->r10 != ctx->r1) {
        // 0x800958A4: lui         $a1, 0x809
        ctx->r5 = S32(0X809 << 16);
            goto L_80095984;
    }
    // 0x800958A4: lui         $a1, 0x809
    ctx->r5 = S32(0X809 << 16);
    // 0x800958A8: lui         $t5, 0x8022
    ctx->r13 = S32(0X8022 << 16);
    // 0x800958AC: lw          $t5, 0x7A68($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7A68);
    // 0x800958B0: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800958B4: lw          $t3, -0x5650($t3)
    ctx->r11 = MEM_W(ctx->r11, -0X5650);
    // 0x800958B8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800958BC: sw          $t5, -0x1660($at)
    MEM_W(-0X1660, ctx->r1) = ctx->r13;
    // 0x800958C0: addiu       $a1, $a1, 0x510
    ctx->r5 = ADD32(ctx->r5, 0X510);
    // 0x800958C4: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800958C8: sll         $t4, $t3, 3
    ctx->r12 = S32(ctx->r11 << 3);
    // 0x800958CC: addu        $v0, $a0, $t4
    ctx->r2 = ADD32(ctx->r4, ctx->r12);
    // 0x800958D0: sw          $a1, 0x7A68($at)
    MEM_W(0X7A68, ctx->r1) = ctx->r5;
    // 0x800958D4: lw          $t6, 0x0($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X0);
    // 0x800958D8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800958DC: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x800958E0: sw          $t6, 0x7A6C($at)
    MEM_W(0X7A6C, ctx->r1) = ctx->r14;
    // 0x800958E4: lw          $t7, 0x4($v0)
    ctx->r15 = MEM_W(ctx->r2, 0X4);
    // 0x800958E8: lui         $at, 0x8022
    ctx->r1 = S32(0X8022 << 16);
    // 0x800958EC: addiu       $v1, $v1, 0x7AA4
    ctx->r3 = ADD32(ctx->r3, 0X7AA4);
    // 0x800958F0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800958F4: sw          $t7, 0x7A80($at)
    MEM_W(0X7A80, ctx->r1) = ctx->r15;
    // 0x800958F8: lw          $t2, 0x8($v1)
    ctx->r10 = MEM_W(ctx->r3, 0X8);
    // 0x800958FC: lw          $t8, -0x564C($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X564C);
    // 0x80095900: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095904: sw          $t2, -0x165C($at)
    MEM_W(-0X165C, ctx->r1) = ctx->r10;
    // 0x80095908: sll         $t9, $t8, 3
    ctx->r25 = S32(ctx->r24 << 3);
    // 0x8009590C: addu        $v0, $a0, $t9
    ctx->r2 = ADD32(ctx->r4, ctx->r25);
    // 0x80095910: sw          $a1, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r5;
    // 0x80095914: lw          $t3, 0x0($v0)
    ctx->r11 = MEM_W(ctx->r2, 0X0);
    // 0x80095918: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x8009591C: lw          $t7, 0x4C($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X4C);
    // 0x80095920: sw          $t3, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r11;
    // 0x80095924: lw          $t4, 0x4($v0)
    ctx->r12 = MEM_W(ctx->r2, 0X4);
    // 0x80095928: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009592C: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095930: sw          $t4, 0x20($v1)
    MEM_W(0X20, ctx->r3) = ctx->r12;
    // 0x80095934: lw          $t5, -0x5648($t5)
    ctx->r13 = MEM_W(ctx->r13, -0X5648);
    // 0x80095938: sw          $t7, -0x1658($at)
    MEM_W(-0X1658, ctx->r1) = ctx->r15;
    // 0x8009593C: sw          $a1, 0x4C($v1)
    MEM_W(0X4C, ctx->r3) = ctx->r5;
    // 0x80095940: sll         $t6, $t5, 3
    ctx->r14 = S32(ctx->r13 << 3);
    // 0x80095944: addu        $v0, $a0, $t6
    ctx->r2 = ADD32(ctx->r4, ctx->r14);
    // 0x80095948: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x8009594C: lw          $t4, 0x90($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X90);
    // 0x80095950: addiu       $v1, $v1, 0x88
    ctx->r3 = ADD32(ctx->r3, 0X88);
    // 0x80095954: sw          $t8, -0x38($v1)
    MEM_W(-0X38, ctx->r3) = ctx->r24;
    // 0x80095958: lw          $t9, 0x4($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X4);
    // 0x8009595C: sw          $t9, -0x24($v1)
    MEM_W(-0X24, ctx->r3) = ctx->r25;
    // 0x80095960: lw          $t2, -0x5644($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X5644);
    // 0x80095964: sw          $t4, -0x1654($at)
    MEM_W(-0X1654, ctx->r1) = ctx->r12;
    // 0x80095968: sw          $a1, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r5;
    // 0x8009596C: sll         $t3, $t2, 3
    ctx->r11 = S32(ctx->r10 << 3);
    // 0x80095970: addu        $v0, $a0, $t3
    ctx->r2 = ADD32(ctx->r4, ctx->r11);
    // 0x80095974: lw          $t5, 0x0($v0)
    ctx->r13 = MEM_W(ctx->r2, 0X0);
    // 0x80095978: sw          $t5, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r13;
    // 0x8009597C: lw          $t6, 0x4($v0)
    ctx->r14 = MEM_W(ctx->r2, 0X4);
    // 0x80095980: sw          $t6, 0x20($v1)
    MEM_W(0X20, ctx->r3) = ctx->r14;
L_80095984:
    // 0x80095984: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80095988: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x8009598C: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x80095990: lui         $t8, 0x8015
    ctx->r24 = S32(0X8015 << 16);
    // 0x80095994: beql        $t7, $at, L_80095A1C
    if (ctx->r15 == ctx->r1) {
        // 0x80095998: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_80095A1C;
    }
    goto skip_4;
    // 0x80095998: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x8009599C: lw          $t9, 0x50($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X50);
    // 0x800959A0: lw          $t8, 0x18B8($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X18B8);
    // 0x800959A4: addiu       $t0, $t0, 0x1944
    ctx->r8 = ADD32(ctx->r8, 0X1944);
    // 0x800959A8: bne         $t9, $zero, L_800959C8
    if (ctx->r25 != 0) {
        // 0x800959AC: sw          $t8, 0x0($t0)
        MEM_W(0X0, ctx->r8) = ctx->r24;
            goto L_800959C8;
    }
    // 0x800959AC: sw          $t8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r24;
    // 0x800959B0: jal         0x80093F78
    // 0x800959B4: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    func_80093F78(rdram, ctx);
        goto after_2;
    // 0x800959B4: or          $a0, $t8, $zero
    ctx->r4 = ctx->r24 | 0;
    after_2:
    // 0x800959B8: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x800959BC: addiu       $t0, $t0, 0x1944
    ctx->r8 = ADD32(ctx->r8, 0X1944);
    // 0x800959C0: b           L_800959E8
    // 0x800959C4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
        goto L_800959E8;
    // 0x800959C4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_800959C8:
    // 0x800959C8: lw          $a0, 0x0($t0)
    ctx->r4 = MEM_W(ctx->r8, 0X0);
    // 0x800959CC: addiu       $a1, $zero, 0xFF
    ctx->r5 = ADD32(0, 0XFF);
    // 0x800959D0: addiu       $a2, $zero, 0xFF
    ctx->r6 = ADD32(0, 0XFF);
    // 0x800959D4: jal         0x80093DBC
    // 0x800959D8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    func_80093DBC(rdram, ctx);
        goto after_3;
    // 0x800959D8: addiu       $a3, $zero, 0xFF
    ctx->r7 = ADD32(0, 0XFF);
    after_3:
    // 0x800959DC: lui         $t0, 0x8015
    ctx->r8 = S32(0X8015 << 16);
    // 0x800959E0: addiu       $t0, $t0, 0x1944
    ctx->r8 = ADD32(ctx->r8, 0X1944);
    // 0x800959E4: sw          $v0, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r2;
L_800959E8:
    // 0x800959E8: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x800959EC: lui         $t3, 0xE900
    ctx->r11 = S32(0XE900 << 16);
    // 0x800959F0: lui         $t5, 0xB800
    ctx->r13 = S32(0XB800 << 16);
    // 0x800959F4: addiu       $t2, $v0, 0x8
    ctx->r10 = ADD32(ctx->r2, 0X8);
    // 0x800959F8: sw          $t2, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r10;
    // 0x800959FC: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80095A00: sw          $t3, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r11;
    // 0x80095A04: lw          $v0, 0x0($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X0);
    // 0x80095A08: addiu       $t4, $v0, 0x8
    ctx->r12 = ADD32(ctx->r2, 0X8);
    // 0x80095A0C: sw          $t4, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r12;
    // 0x80095A10: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x80095A14: sw          $t5, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r13;
L_80095A18:
    // 0x80095A18: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_80095A1C:
    // 0x80095A1C: addiu       $sp, $sp, 0x68
    ctx->r29 = ADD32(ctx->r29, 0X68);
    // 0x80095A20: jr          $ra
    // 0x80095A24: nop

    return;
    // 0x80095A24: nop

;}
RECOMP_FUNC void func_80095A28(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    { extern uint32_t wr64_sunny_detail_assets(uint8_t*, uint32_t); ctx->r4 = S32(wr64_sunny_detail_assets(rdram, (uint32_t)ctx->r4)); }
    // 0x80095A28: addiu       $sp, $sp, -0x50
    ctx->r29 = ADD32(ctx->r29, -0X50);
    // 0x80095A2C: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x80095A30: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x80095A34: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x80095A38: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x80095A3C: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x80095A40: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x80095A44: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x80095A48: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80095A4C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80095A50: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80095A54: lw          $v0, 0x8($a0)
    ctx->r2 = MEM_W(ctx->r4, 0X8);
    // 0x80095A58: or          $s2, $a0, $zero
    ctx->r18 = ctx->r4 | 0;
    // 0x80095A5C: lui         $s7, 0x800D
    ctx->r23 = S32(0X800D << 16);
    // 0x80095A60: beq         $v0, $zero, L_80095CB8
    if (ctx->r2 == 0) {
        // 0x80095A64: lw          $fp, 0x44($sp)
        ctx->r30 = MEM_W(ctx->r29, 0X44);
            goto L_80095CB8;
    }
    // 0x80095A64: lw          $fp, 0x44($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X44);
    // 0x80095A68: lui         $s6, 0x801D
    ctx->r22 = S32(0X801D << 16);
    // 0x80095A6C: lui         $s5, 0x801D
    ctx->r21 = S32(0X801D << 16);
    // 0x80095A70: lui         $s4, 0x801D
    ctx->r20 = S32(0X801D << 16);
    // 0x80095A74: addiu       $s4, $s4, -0x18D0
    ctx->r20 = ADD32(ctx->r20, -0X18D0);
    // 0x80095A78: addiu       $s5, $s5, -0x18CC
    ctx->r21 = ADD32(ctx->r21, -0X18CC);
    // 0x80095A7C: addiu       $s6, $s6, -0x18C8
    ctx->r22 = ADD32(ctx->r22, -0X18C8);
    // 0x80095A80: addiu       $s7, $s7, 0x45E8
    ctx->r23 = ADD32(ctx->r23, 0X45E8);
    // 0x80095A84: addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
    // 0x80095A88: addiu       $s1, $zero, 0x1000
    ctx->r17 = ADD32(0, 0X1000);
    // 0x80095A8C: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
L_80095A90:
    // 0x80095A90: lw          $t6, 0x4($s2)
    ctx->r14 = MEM_W(ctx->r18, 0X4);
    // 0x80095A94: addiu       $at, $zero, -0x2
    ctx->r1 = ADD32(0, -0X2);
    // 0x80095A98: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80095A9C: subu        $a2, $t6, $a0
    ctx->r6 = SUB32(ctx->r14, ctx->r4);
    // 0x80095AA0: addiu       $a2, $a2, 0x1
    ctx->r6 = ADD32(ctx->r6, 0X1);
    // 0x80095AA4: and         $t7, $a2, $at
    ctx->r15 = ctx->r6 & ctx->r1;
    // 0x80095AA8: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x80095AAC: bne         $v0, $at, L_80095AC8
    if (ctx->r2 != ctx->r1) {
        // 0x80095AB0: or          $a2, $t7, $zero
        ctx->r6 = ctx->r15 | 0;
            goto L_80095AC8;
    }
    // 0x80095AB0: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x80095AB4: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80095AB8: jal         0x80097F74
    // 0x80095ABC: lw          $a1, 0x45EC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X45EC);
    func_80097F74(rdram, ctx);
        goto after_0;
    // 0x80095ABC: lw          $a1, 0x45EC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X45EC);
    after_0:
    // 0x80095AC0: b           L_80095CA8
    // 0x80095AC4: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
        goto L_80095CA8;
    // 0x80095AC4: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
L_80095AC8:
    // 0x80095AC8: lw          $t8, -0x54DC($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X54DC);
    // 0x80095ACC: bne         $s3, $t8, L_80095AE4
    if (ctx->r19 != ctx->r24) {
        // 0x80095AD0: nop
    
            goto L_80095AE4;
    }
    // 0x80095AD0: nop

    // 0x80095AD4: jal         0x80097F74
    // 0x80095AD8: lui         $a1, 0x8036
    ctx->r5 = S32(0X8036 << 16);
    func_80097F74(rdram, ctx);
        goto after_1;
    // 0x80095AD8: lui         $a1, 0x8036
    ctx->r5 = S32(0X8036 << 16);
    after_1:
    // 0x80095ADC: b           L_80095AF0
    // 0x80095AE0: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
        goto L_80095AF0;
    // 0x80095AE0: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
L_80095AE4:
    // 0x80095AE4: jal         0x80097F74
    // 0x80095AE8: lui         $a1, 0x802A
    ctx->r5 = S32(0X802A << 16);
    func_80097F74(rdram, ctx);
        goto after_2;
    // 0x80095AE8: lui         $a1, 0x802A
    ctx->r5 = S32(0X802A << 16);
    after_2:
    // 0x80095AEC: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
L_80095AF0:
    // 0x80095AF0: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x80095AF4: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80095AF8: bnel        $v0, $at, L_80095B4C
    if (ctx->r2 != ctx->r1) {
        // 0x80095AFC: addiu       $at, $zero, 0x8
        ctx->r1 = ADD32(0, 0X8);
            goto L_80095B4C;
    }
    goto skip_0;
    // 0x80095AFC: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    skip_0:
    // 0x80095B00: lh          $t9, -0x19F4($t9)
    ctx->r25 = MEM_H(ctx->r25, -0X19F4);
    // 0x80095B04: lui         $s0, 0x800D
    ctx->r16 = S32(0X800D << 16);
    // 0x80095B08: lw          $s0, 0x45E4($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X45E4);
    // 0x80095B0C: bne         $s3, $t9, L_80095B30
    if (ctx->r19 != ctx->r25) {
        // 0x80095B10: lui         $t2, 0x800E
        ctx->r10 = S32(0X800E << 16);
            goto L_80095B30;
    }
    // 0x80095B10: lui         $t2, 0x800E
    ctx->r10 = S32(0X800E << 16);
    // 0x80095B14: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80095B18: lw          $t0, -0x7E90($t0)
    ctx->r8 = MEM_W(ctx->r8, -0X7E90);
    // 0x80095B1C: lui         $fp, 0x800E
    ctx->r30 = S32(0X800E << 16);
    // 0x80095B20: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x80095B24: addu        $fp, $fp, $t1
    ctx->r30 = ADD32(ctx->r30, ctx->r9);
    // 0x80095B28: b           L_80095B90
    // 0x80095B2C: lw          $fp, -0x31C4($fp)
    ctx->r30 = MEM_W(ctx->r30, -0X31C4);
        goto L_80095B90;
    // 0x80095B2C: lw          $fp, -0x31C4($fp)
    ctx->r30 = MEM_W(ctx->r30, -0X31C4);
L_80095B30:
    // 0x80095B30: lw          $t2, -0x7E90($t2)
    ctx->r10 = MEM_W(ctx->r10, -0X7E90);
    // 0x80095B34: lui         $fp, 0x800E
    ctx->r30 = S32(0X800E << 16);
    // 0x80095B38: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x80095B3C: addu        $fp, $fp, $t3
    ctx->r30 = ADD32(ctx->r30, ctx->r11);
    // 0x80095B40: b           L_80095B90
    // 0x80095B44: lw          $fp, -0x31A0($fp)
    ctx->r30 = MEM_W(ctx->r30, -0X31A0);
        goto L_80095B90;
    // 0x80095B44: lw          $fp, -0x31A0($fp)
    ctx->r30 = MEM_W(ctx->r30, -0X31A0);
    // 0x80095B48: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
L_80095B4C:
    // 0x80095B4C: bne         $v0, $at, L_80095B74
    if (ctx->r2 != ctx->r1) {
        // 0x80095B50: lui         $t4, 0x800D
        ctx->r12 = S32(0X800D << 16);
            goto L_80095B74;
    }
    // 0x80095B50: lui         $t4, 0x800D
    ctx->r12 = S32(0X800D << 16);
    // 0x80095B54: lw          $t4, 0x45E4($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X45E4);
    // 0x80095B58: addu        $a0, $t4, $fp
    ctx->r4 = ADD32(ctx->r12, ctx->r30);
    // 0x80095B5C: jal         0x800C5720
    // 0x80095B60: sw          $a0, 0x0($s7)
    MEM_W(0X0, ctx->r23) = ctx->r4;
    osVirtualToPhysical_recomp(rdram, ctx);
        goto after_3;
    // 0x80095B60: sw          $a0, 0x0($s7)
    MEM_W(0X0, ctx->r23) = ctx->r4;
    after_3:
    // 0x80095B64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80095B68: sw          $v0, -0x1918($at)
    MEM_W(-0X1918, ctx->r1) = ctx->r2;
    // 0x80095B6C: b           L_80095B90
    // 0x80095B70: lw          $s0, 0x0($s7)
    ctx->r16 = MEM_W(ctx->r23, 0X0);
        goto L_80095B90;
    // 0x80095B70: lw          $s0, 0x0($s7)
    ctx->r16 = MEM_W(ctx->r23, 0X0);
L_80095B74:
    // 0x80095B74: addiu       $at, $zero, 0x9
    ctx->r1 = ADD32(0, 0X9);
    // 0x80095B78: bne         $v0, $at, L_80095B8C
    if (ctx->r2 != ctx->r1) {
        // 0x80095B7C: lui         $s0, 0x800D
        ctx->r16 = S32(0X800D << 16);
            goto L_80095B8C;
    }
    // 0x80095B7C: lui         $s0, 0x800D
    ctx->r16 = S32(0X800D << 16);
    // 0x80095B80: lui         $s0, 0x8029
    ctx->r16 = S32(0X8029 << 16);
    // 0x80095B84: b           L_80095B90
    // 0x80095B88: ori         $s0, $s0, 0xA200
    ctx->r16 = ctx->r16 | 0XA200;
        goto L_80095B90;
    // 0x80095B88: ori         $s0, $s0, 0xA200
    ctx->r16 = ctx->r16 | 0XA200;
L_80095B8C:
    // 0x80095B8C: lw          $s0, 0x45F0($s0)
    ctx->r16 = MEM_W(ctx->r16, 0X45F0);
L_80095B90:
    { extern uint32_t wr64_sunny_detail_shape_span(uint8_t*, uint32_t, uint32_t); ctx->r30 = S32(wr64_sunny_detail_shape_span(rdram, (uint32_t)ctx->r18, (uint32_t)ctx->r30)); }
    // 0x80095B90: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80095B94: lw          $t7, -0x54DC($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X54DC);
    // 0x80095B98: lw          $t6, 0xC($s2)
    ctx->r14 = MEM_W(ctx->r18, 0XC);
    // 0x80095B9C: lui         $a0, 0x802A
    ctx->r4 = S32(0X802A << 16);
    // 0x80095BA0: bne         $s3, $t7, L_80095BBC
    if (ctx->r19 != ctx->r15) {
        // 0x80095BA4: addu        $s0, $s0, $t6
        ctx->r16 = ADD32(ctx->r16, ctx->r14);
            goto L_80095BBC;
    }
    // 0x80095BA4: addu        $s0, $s0, $t6
    ctx->r16 = ADD32(ctx->r16, ctx->r14);
    // 0x80095BA8: lui         $a0, 0x8036
    ctx->r4 = S32(0X8036 << 16);
    // 0x80095BAC: jal         0x800B4D30
    // 0x80095BB0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Mio0_Decompress(rdram, ctx);
        goto after_4;
    // 0x80095BB0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_4:
    // 0x80095BB4: b           L_80095BC8
    // 0x80095BB8: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
        goto L_80095BC8;
    // 0x80095BB8: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
L_80095BBC:
    // 0x80095BBC: jal         0x800B4D30
    // 0x80095BC0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    Mio0_Decompress(rdram, ctx);
        goto after_5;
    // 0x80095BC0: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    after_5:
    // 0x80095BC4: lw          $v0, 0x8($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X8);
L_80095BC8:
    // 0x80095BC8: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80095BCC: addiu       $v1, $s0, 0x2000
    ctx->r3 = ADD32(ctx->r16, 0X2000);
    // 0x80095BD0: bne         $v0, $at, L_80095C14
    if (ctx->r2 != ctx->r1) {
        // 0x80095BD4: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_80095C14;
    }
    // 0x80095BD4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80095BD8: or          $v0, $s0, $zero
    ctx->r2 = ctx->r16 | 0;
L_80095BDC:
    // 0x80095BDC: lbu         $t8, 0x0($v0)
    ctx->r24 = MEM_BU(ctx->r2, 0X0);
    // 0x80095BE0: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x80095BE4: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x80095BE8: sb          $t8, -0x4($v1)
    MEM_B(-0X4, ctx->r3) = ctx->r24;
    // 0x80095BEC: lbu         $t9, 0x1($v0)
    ctx->r25 = MEM_BU(ctx->r2, 0X1);
    // 0x80095BF0: addiu       $v0, $v0, 0x4
    ctx->r2 = ADD32(ctx->r2, 0X4);
    // 0x80095BF4: sb          $t9, -0x3($v1)
    MEM_B(-0X3, ctx->r3) = ctx->r25;
    // 0x80095BF8: lbu         $t0, -0x2($v0)
    ctx->r8 = MEM_BU(ctx->r2, -0X2);
    // 0x80095BFC: sb          $t0, -0x2($v1)
    MEM_B(-0X2, ctx->r3) = ctx->r8;
    // 0x80095C00: lbu         $t1, -0x1($v0)
    ctx->r9 = MEM_BU(ctx->r2, -0X1);
    // 0x80095C04: bne         $a0, $s1, L_80095BDC
    if (ctx->r4 != ctx->r17) {
        // 0x80095C08: sb          $t1, -0x1($v1)
        MEM_B(-0X1, ctx->r3) = ctx->r9;
            goto L_80095BDC;
    }
    // 0x80095C08: sb          $t1, -0x1($v1)
    MEM_B(-0X1, ctx->r3) = ctx->r9;
    // 0x80095C0C: b           L_80095CA8
    // 0x80095C10: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
        goto L_80095CA8;
    // 0x80095C10: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
L_80095C14:
    // 0x80095C14: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80095C18: bnel        $v0, $at, L_80095C48
    if (ctx->r2 != ctx->r1) {
        // 0x80095C1C: addiu       $at, $zero, 0x7
        ctx->r1 = ADD32(0, 0X7);
            goto L_80095C48;
    }
    goto skip_1;
    // 0x80095C1C: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    skip_1:
    // 0x80095C20: jal         0x800C6740
    // 0x80095C24: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_6;
    // 0x80095C24: nop

    after_6:
    // 0x80095C28: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80095C2C: jal         0x80095CE8
    // 0x80095C30: lw          $a1, 0x0($s4)
    ctx->r5 = MEM_W(ctx->r20, 0X0);
    func_80095CE8(rdram, ctx);
        goto after_7;
    // 0x80095C30: lw          $a1, 0x0($s4)
    ctx->r5 = MEM_W(ctx->r20, 0X0);
    after_7:
    // 0x80095C34: lw          $t2, 0x0($s4)
    ctx->r10 = MEM_W(ctx->r20, 0X0);
    // 0x80095C38: addiu       $t3, $t2, 0x1
    ctx->r11 = ADD32(ctx->r10, 0X1);
    // 0x80095C3C: b           L_80095CA4
    // 0x80095C40: sw          $t3, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r11;
        goto L_80095CA4;
    // 0x80095C40: sw          $t3, 0x0($s4)
    MEM_W(0X0, ctx->r20) = ctx->r11;
    // 0x80095C44: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
L_80095C48:
    // 0x80095C48: bnel        $v0, $at, L_80095C78
    if (ctx->r2 != ctx->r1) {
        // 0x80095C4C: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_80095C78;
    }
    goto skip_2;
    // 0x80095C4C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    skip_2:
    // 0x80095C50: jal         0x800C6740
    // 0x80095C54: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_8;
    // 0x80095C54: nop

    after_8:
    // 0x80095C58: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80095C5C: jal         0x80096048
    // 0x80095C60: lw          $a1, 0x0($s5)
    ctx->r5 = MEM_W(ctx->r21, 0X0);
    func_80096048(rdram, ctx);
        goto after_9;
    // 0x80095C60: lw          $a1, 0x0($s5)
    ctx->r5 = MEM_W(ctx->r21, 0X0);
    after_9:
    // 0x80095C64: lw          $t4, 0x0($s5)
    ctx->r12 = MEM_W(ctx->r21, 0X0);
    // 0x80095C68: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x80095C6C: b           L_80095CA4
    // 0x80095C70: sw          $t5, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r13;
        goto L_80095CA4;
    // 0x80095C70: sw          $t5, 0x0($s5)
    MEM_W(0X0, ctx->r21) = ctx->r13;
    // 0x80095C74: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
L_80095C78:
    // 0x80095C78: bnel        $v0, $at, L_80095CA8
    if (ctx->r2 != ctx->r1) {
        // 0x80095C7C: lw          $v0, 0x18($s2)
        ctx->r2 = MEM_W(ctx->r18, 0X18);
            goto L_80095CA8;
    }
    goto skip_3;
    // 0x80095C7C: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
    skip_3:
    // 0x80095C80: jal         0x800C6740
    // 0x80095C84: nop

    osWritebackDCacheAll_recomp(rdram, ctx);
        goto after_10;
    // 0x80095C84: nop

    after_10:
    // 0x80095C88: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80095C8C: lw          $a1, 0xC($s2)
    ctx->r5 = MEM_W(ctx->r18, 0XC);
    // 0x80095C90: jal         0x80096694
    // 0x80095C94: lw          $a2, 0x0($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X0);
    func_80096694(rdram, ctx);
        goto after_11;
    // 0x80095C94: lw          $a2, 0x0($s6)
    ctx->r6 = MEM_W(ctx->r22, 0X0);
    after_11:
    // 0x80095C98: lw          $t6, 0x0($s6)
    ctx->r14 = MEM_W(ctx->r22, 0X0);
    // 0x80095C9C: addiu       $t7, $t6, 0x1
    ctx->r15 = ADD32(ctx->r14, 0X1);
    // 0x80095CA0: sw          $t7, 0x0($s6)
    MEM_W(0X0, ctx->r22) = ctx->r15;
L_80095CA4:
    // 0x80095CA4: lw          $v0, 0x18($s2)
    ctx->r2 = MEM_W(ctx->r18, 0X18);
L_80095CA8:
    // 0x80095CA8: addiu       $s2, $s2, 0x10
    ctx->r18 = ADD32(ctx->r18, 0X10);
    // 0x80095CAC: bnel        $v0, $zero, L_80095A90
    if (ctx->r2 != 0) {
        // 0x80095CB0: lw          $a0, 0x0($s2)
        ctx->r4 = MEM_W(ctx->r18, 0X0);
            goto L_80095A90;
    }
    goto skip_4;
    // 0x80095CB0: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    skip_4:
    // 0x80095CB4: sw          $fp, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r30;
L_80095CB8:
    // 0x80095CB8: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x80095CBC: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80095CC0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80095CC4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80095CC8: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x80095CCC: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x80095CD0: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x80095CD4: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x80095CD8: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x80095CDC: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x80095CE0: jr          $ra
    // 0x80095CE4: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
    return;
    // 0x80095CE4: addiu       $sp, $sp, 0x50
    ctx->r29 = ADD32(ctx->r29, 0X50);
;}
RECOMP_FUNC void func_80095CE8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80095CE8: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x80095CEC: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x80095CF0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80095CF4: addiu       $t6, $t6, -0x18C0
    ctx->r14 = ADD32(ctx->r14, -0X18C0);
    // 0x80095CF8: sll         $s7, $a1, 2
    ctx->r23 = S32(ctx->r5 << 2);
    // 0x80095CFC: addu        $a2, $s7, $t6
    ctx->r6 = ADD32(ctx->r23, ctx->r14);
    // 0x80095D00: lh          $t7, 0x2($a2)
    ctx->r15 = MEM_H(ctx->r6, 0X2);
    // 0x80095D04: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x80095D08: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x80095D0C: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x80095D10: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x80095D14: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x80095D18: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x80095D1C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80095D20: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80095D24: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80095D28: beq         $t7, $zero, L_80095D3C
    if (ctx->r15 == 0) {
        // 0x80095D2C: sw          $a0, 0x70($sp)
        MEM_W(0X70, ctx->r29) = ctx->r4;
            goto L_80095D3C;
    }
    // 0x80095D2C: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x80095D30: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x80095D34: b           L_80095D44
    // 0x80095D38: sw          $t8, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r24;
        goto L_80095D44;
    // 0x80095D38: sw          $t8, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r24;
L_80095D3C:
    // 0x80095D3C: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x80095D40: sw          $t9, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r25;
L_80095D44:
    // 0x80095D44: lw          $t0, 0x60($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X60);
    // 0x80095D48: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80095D4C: addiu       $fp, $zero, 0x1
    ctx->r30 = ADD32(0, 0X1);
    // 0x80095D50: blez        $t0, L_80096018
    if (SIGNED(ctx->r8) <= 0) {
        // 0x80095D54: addiu       $s6, $zero, 0x2
        ctx->r22 = ADD32(0, 0X2);
            goto L_80096018;
    }
    // 0x80095D54: addiu       $s6, $zero, 0x2
    ctx->r22 = ADD32(0, 0X2);
    // 0x80095D58: lui         $s4, 0xFF
    ctx->r20 = S32(0XFF << 16);
    // 0x80095D5C: lui         $s2, 0x800E
    ctx->r18 = S32(0X800E << 16);
    // 0x80095D60: addiu       $s2, $s2, -0x5330
    ctx->r18 = ADD32(ctx->r18, -0X5330);
    // 0x80095D64: ori         $s4, $s4, 0xFFFF
    ctx->r20 = ctx->r20 | 0XFFFF;
    // 0x80095D68: addiu       $s3, $zero, 0x44
    ctx->r19 = ADD32(0, 0X44);
    // 0x80095D6C: lw          $s1, 0x58($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X58);
    // 0x80095D70: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
    // 0x80095D74: lh          $t2, 0x0($a2)
    ctx->r10 = MEM_H(ctx->r6, 0X0);
L_80095D78:
    // 0x80095D78: lh          $t1, 0x2($a2)
    ctx->r9 = MEM_H(ctx->r6, 0X2);
    // 0x80095D7C: or          $s5, $zero, $zero
    ctx->r21 = 0 | 0;
    // 0x80095D80: multu       $t2, $a3
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r7)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095D84: mflo        $t3
    ctx->r11 = lo;
    // 0x80095D88: addu        $t4, $t1, $t3
    ctx->r12 = ADD32(ctx->r9, ctx->r11);
    // 0x80095D8C: addu        $s0, $t4, $v1
    ctx->r16 = ADD32(ctx->r12, ctx->r3);
    // 0x80095D90: sltiu       $at, $s5, 0x11
    ctx->r1 = ctx->r21 < 0X11 ? 1 : 0;
L_80095D94:
    // 0x80095D94: beq         $at, $zero, L_80095F5C
    if (ctx->r1 == 0) {
        // 0x80095D98: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_80095F5C;
    }
    // 0x80095D98: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80095D9C: sll         $t5, $s5, 2
    ctx->r13 = S32(ctx->r21 << 2);
    // 0x80095DA0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80095DA4: addu        $at, $at, $t5
    gpr jr_addend_80095DAC = ctx->r13;
    ctx->r1 = ADD32(ctx->r1, ctx->r13);
    // 0x80095DA8: lw          $t5, -0x4D90($at)
    ctx->r13 = ADD32(ctx->r1, -0X4D90);
    // 0x80095DAC: jr          $t5
    // 0x80095DB0: nop

    switch (jr_addend_80095DAC >> 2) {
        case 0: goto L_80095DB4; break;
        case 1: goto L_80095DCC; break;
        case 2: goto L_80095DE4; break;
        case 3: goto L_80095DFC; break;
        case 4: goto L_80095E14; break;
        case 5: goto L_80095E2C; break;
        case 6: goto L_80095E44; break;
        case 7: goto L_80095E5C; break;
        case 8: goto L_80095E74; break;
        case 9: goto L_80095E8C; break;
        case 10: goto L_80095EA4; break;
        case 11: goto L_80095EBC; break;
        case 12: goto L_80095ED4; break;
        case 13: goto L_80095EF0; break;
        case 14: goto L_80095F0C; break;
        case 15: goto L_80095F28; break;
        case 16: goto L_80095F44; break;
        default: switch_error(__func__, 0x80095DAC, 0x800EB270);
    }
    // 0x80095DB0: nop

L_80095DB4:
    // 0x80095DB4: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095DB8: mflo        $t6
    ctx->r14 = lo;
    // 0x80095DBC: addu        $t7, $s2, $t6
    ctx->r15 = ADD32(ctx->r18, ctx->r14);
    // 0x80095DC0: lw          $t8, 0x0($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X0);
    // 0x80095DC4: b           L_80095F5C
    // 0x80095DC8: and         $s1, $t8, $s4
    ctx->r17 = ctx->r24 & ctx->r20;
        goto L_80095F5C;
    // 0x80095DC8: and         $s1, $t8, $s4
    ctx->r17 = ctx->r24 & ctx->r20;
L_80095DCC:
    // 0x80095DCC: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095DD0: mflo        $t9
    ctx->r25 = lo;
    // 0x80095DD4: addu        $t0, $s2, $t9
    ctx->r8 = ADD32(ctx->r18, ctx->r25);
    // 0x80095DD8: lw          $t2, 0x4($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X4);
    // 0x80095DDC: b           L_80095F5C
    // 0x80095DE0: and         $s1, $t2, $s4
    ctx->r17 = ctx->r10 & ctx->r20;
        goto L_80095F5C;
    // 0x80095DE0: and         $s1, $t2, $s4
    ctx->r17 = ctx->r10 & ctx->r20;
L_80095DE4:
    // 0x80095DE4: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095DE8: mflo        $t1
    ctx->r9 = lo;
    // 0x80095DEC: addu        $t3, $s2, $t1
    ctx->r11 = ADD32(ctx->r18, ctx->r9);
    // 0x80095DF0: lw          $t4, 0x8($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X8);
    // 0x80095DF4: b           L_80095F5C
    // 0x80095DF8: and         $s1, $t4, $s4
    ctx->r17 = ctx->r12 & ctx->r20;
        goto L_80095F5C;
    // 0x80095DF8: and         $s1, $t4, $s4
    ctx->r17 = ctx->r12 & ctx->r20;
L_80095DFC:
    // 0x80095DFC: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E00: mflo        $t5
    ctx->r13 = lo;
    // 0x80095E04: addu        $t6, $s2, $t5
    ctx->r14 = ADD32(ctx->r18, ctx->r13);
    // 0x80095E08: lw          $t7, 0xC($t6)
    ctx->r15 = MEM_W(ctx->r14, 0XC);
    // 0x80095E0C: b           L_80095F5C
    // 0x80095E10: and         $s1, $t7, $s4
    ctx->r17 = ctx->r15 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E10: and         $s1, $t7, $s4
    ctx->r17 = ctx->r15 & ctx->r20;
L_80095E14:
    // 0x80095E14: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E18: mflo        $t8
    ctx->r24 = lo;
    // 0x80095E1C: addu        $t9, $s2, $t8
    ctx->r25 = ADD32(ctx->r18, ctx->r24);
    // 0x80095E20: lw          $t0, 0x10($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X10);
    // 0x80095E24: b           L_80095F5C
    // 0x80095E28: and         $s1, $t0, $s4
    ctx->r17 = ctx->r8 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E28: and         $s1, $t0, $s4
    ctx->r17 = ctx->r8 & ctx->r20;
L_80095E2C:
    // 0x80095E2C: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E30: mflo        $t2
    ctx->r10 = lo;
    // 0x80095E34: addu        $t1, $s2, $t2
    ctx->r9 = ADD32(ctx->r18, ctx->r10);
    // 0x80095E38: lw          $t3, 0x14($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X14);
    // 0x80095E3C: b           L_80095F5C
    // 0x80095E40: and         $s1, $t3, $s4
    ctx->r17 = ctx->r11 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E40: and         $s1, $t3, $s4
    ctx->r17 = ctx->r11 & ctx->r20;
L_80095E44:
    // 0x80095E44: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E48: mflo        $t4
    ctx->r12 = lo;
    // 0x80095E4C: addu        $t5, $s2, $t4
    ctx->r13 = ADD32(ctx->r18, ctx->r12);
    // 0x80095E50: lw          $t6, 0x18($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X18);
    // 0x80095E54: b           L_80095F5C
    // 0x80095E58: and         $s1, $t6, $s4
    ctx->r17 = ctx->r14 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E58: and         $s1, $t6, $s4
    ctx->r17 = ctx->r14 & ctx->r20;
L_80095E5C:
    // 0x80095E5C: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E60: mflo        $t7
    ctx->r15 = lo;
    // 0x80095E64: addu        $t8, $s2, $t7
    ctx->r24 = ADD32(ctx->r18, ctx->r15);
    // 0x80095E68: lw          $t9, 0x1C($t8)
    ctx->r25 = MEM_W(ctx->r24, 0X1C);
    // 0x80095E6C: b           L_80095F5C
    // 0x80095E70: and         $s1, $t9, $s4
    ctx->r17 = ctx->r25 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E70: and         $s1, $t9, $s4
    ctx->r17 = ctx->r25 & ctx->r20;
L_80095E74:
    // 0x80095E74: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E78: mflo        $t0
    ctx->r8 = lo;
    // 0x80095E7C: addu        $t2, $s2, $t0
    ctx->r10 = ADD32(ctx->r18, ctx->r8);
    // 0x80095E80: lw          $t1, 0x20($t2)
    ctx->r9 = MEM_W(ctx->r10, 0X20);
    // 0x80095E84: b           L_80095F5C
    // 0x80095E88: and         $s1, $t1, $s4
    ctx->r17 = ctx->r9 & ctx->r20;
        goto L_80095F5C;
    // 0x80095E88: and         $s1, $t1, $s4
    ctx->r17 = ctx->r9 & ctx->r20;
L_80095E8C:
    // 0x80095E8C: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095E90: mflo        $t3
    ctx->r11 = lo;
    // 0x80095E94: addu        $t4, $s2, $t3
    ctx->r12 = ADD32(ctx->r18, ctx->r11);
    // 0x80095E98: lw          $t5, 0x24($t4)
    ctx->r13 = MEM_W(ctx->r12, 0X24);
    // 0x80095E9C: b           L_80095F5C
    // 0x80095EA0: and         $s1, $t5, $s4
    ctx->r17 = ctx->r13 & ctx->r20;
        goto L_80095F5C;
    // 0x80095EA0: and         $s1, $t5, $s4
    ctx->r17 = ctx->r13 & ctx->r20;
L_80095EA4:
    // 0x80095EA4: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095EA8: mflo        $t6
    ctx->r14 = lo;
    // 0x80095EAC: addu        $t7, $s2, $t6
    ctx->r15 = ADD32(ctx->r18, ctx->r14);
    // 0x80095EB0: lw          $t8, 0x28($t7)
    ctx->r24 = MEM_W(ctx->r15, 0X28);
    // 0x80095EB4: b           L_80095F5C
    // 0x80095EB8: and         $s1, $t8, $s4
    ctx->r17 = ctx->r24 & ctx->r20;
        goto L_80095F5C;
    // 0x80095EB8: and         $s1, $t8, $s4
    ctx->r17 = ctx->r24 & ctx->r20;
L_80095EBC:
    // 0x80095EBC: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095EC0: mflo        $t9
    ctx->r25 = lo;
    // 0x80095EC4: addu        $t0, $s2, $t9
    ctx->r8 = ADD32(ctx->r18, ctx->r25);
    // 0x80095EC8: lw          $t2, 0x2C($t0)
    ctx->r10 = MEM_W(ctx->r8, 0X2C);
    // 0x80095ECC: b           L_80095F5C
    // 0x80095ED0: and         $s1, $t2, $s4
    ctx->r17 = ctx->r10 & ctx->r20;
        goto L_80095F5C;
    // 0x80095ED0: and         $s1, $t2, $s4
    ctx->r17 = ctx->r10 & ctx->r20;
L_80095ED4:
    // 0x80095ED4: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095ED8: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x80095EDC: mflo        $t1
    ctx->r9 = lo;
    // 0x80095EE0: addu        $t3, $s2, $t1
    ctx->r11 = ADD32(ctx->r18, ctx->r9);
    // 0x80095EE4: lw          $t4, 0x30($t3)
    ctx->r12 = MEM_W(ctx->r11, 0X30);
    // 0x80095EE8: b           L_80095F5C
    // 0x80095EEC: and         $s1, $t4, $s4
    ctx->r17 = ctx->r12 & ctx->r20;
        goto L_80095F5C;
    // 0x80095EEC: and         $s1, $t4, $s4
    ctx->r17 = ctx->r12 & ctx->r20;
L_80095EF0:
    // 0x80095EF0: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095EF4: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x80095EF8: mflo        $t5
    ctx->r13 = lo;
    // 0x80095EFC: addu        $t6, $s2, $t5
    ctx->r14 = ADD32(ctx->r18, ctx->r13);
    // 0x80095F00: lw          $t7, 0x34($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X34);
    // 0x80095F04: b           L_80095F5C
    // 0x80095F08: and         $s1, $t7, $s4
    ctx->r17 = ctx->r15 & ctx->r20;
        goto L_80095F5C;
    // 0x80095F08: and         $s1, $t7, $s4
    ctx->r17 = ctx->r15 & ctx->r20;
L_80095F0C:
    // 0x80095F0C: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095F10: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x80095F14: mflo        $t8
    ctx->r24 = lo;
    // 0x80095F18: addu        $t9, $s2, $t8
    ctx->r25 = ADD32(ctx->r18, ctx->r24);
    // 0x80095F1C: lw          $t0, 0x38($t9)
    ctx->r8 = MEM_W(ctx->r25, 0X38);
    // 0x80095F20: b           L_80095F5C
    // 0x80095F24: and         $s1, $t0, $s4
    ctx->r17 = ctx->r8 & ctx->r20;
        goto L_80095F5C;
    // 0x80095F24: and         $s1, $t0, $s4
    ctx->r17 = ctx->r8 & ctx->r20;
L_80095F28:
    // 0x80095F28: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095F2C: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x80095F30: mflo        $t2
    ctx->r10 = lo;
    // 0x80095F34: addu        $t1, $s2, $t2
    ctx->r9 = ADD32(ctx->r18, ctx->r10);
    // 0x80095F38: lw          $t3, 0x3C($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X3C);
    // 0x80095F3C: b           L_80095F5C
    // 0x80095F40: and         $s1, $t3, $s4
    ctx->r17 = ctx->r11 & ctx->r20;
        goto L_80095F5C;
    // 0x80095F40: and         $s1, $t3, $s4
    ctx->r17 = ctx->r11 & ctx->r20;
L_80095F44:
    // 0x80095F44: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80095F48: or          $v0, $s6, $zero
    ctx->r2 = ctx->r22 | 0;
    // 0x80095F4C: mflo        $t4
    ctx->r12 = lo;
    // 0x80095F50: addu        $t5, $s2, $t4
    ctx->r13 = ADD32(ctx->r18, ctx->r12);
    // 0x80095F54: lw          $t6, 0x40($t5)
    ctx->r14 = MEM_W(ctx->r13, 0X40);
    // 0x80095F58: and         $s1, $t6, $s4
    ctx->r17 = ctx->r14 & ctx->r20;
L_80095F5C:
    // 0x80095F5C: bne         $v0, $fp, L_80095F74
    if (ctx->r2 != ctx->r30) {
        // 0x80095F60: nop
    
            goto L_80095F74;
    }
    // 0x80095F60: nop

    // 0x80095F64: bne         $v1, $fp, L_80095F90
    if (ctx->r3 != ctx->r30) {
        // 0x80095F68: nop
    
            goto L_80095F90;
    }
    // 0x80095F68: nop

    // 0x80095F6C: b           L_80095FF8
    // 0x80095F70: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
        goto L_80095FF8;
    // 0x80095F70: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
L_80095F74:
    // 0x80095F74: bne         $v0, $s6, L_80095F90
    if (ctx->r2 != ctx->r22) {
        // 0x80095F78: nop
    
            goto L_80095F90;
    }
    // 0x80095F78: nop

    // 0x80095F7C: lh          $v0, 0x0($a2)
    ctx->r2 = MEM_H(ctx->r6, 0X0);
    // 0x80095F80: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x80095F84: beq         $s6, $v0, L_80095F90
    if (ctx->r22 == ctx->r2) {
        // 0x80095F88: nop
    
            goto L_80095F90;
    }
    // 0x80095F88: nop

    // 0x80095F8C: bne         $v0, $at, L_80095FF4
    if (ctx->r2 != ctx->r1) {
        // 0x80095F90: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_80095FF4;
    }
L_80095F90:
    // 0x80095F90: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80095F94: lw          $v0, -0x18C4($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X18C4);
    // 0x80095F98: lw          $t7, 0x70($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X70);
    // 0x80095F9C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80095FA0: beq         $a3, $v0, L_80095FB0
    if (ctx->r7 == ctx->r2) {
        // 0x80095FA4: addu        $a0, $t7, $s1
        ctx->r4 = ADD32(ctx->r15, ctx->r17);
            goto L_80095FB0;
    }
    // 0x80095FA4: addu        $a0, $t7, $s1
    ctx->r4 = ADD32(ctx->r15, ctx->r17);
    // 0x80095FA8: bne         $s6, $v0, L_80095FBC
    if (ctx->r22 != ctx->r2) {
        // 0x80095FAC: addiu       $at, $zero, 0x4
        ctx->r1 = ADD32(0, 0X4);
            goto L_80095FBC;
    }
    // 0x80095FAC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
L_80095FB0:
    // 0x80095FB0: addu        $a1, $a1, $s7
    ctx->r5 = ADD32(ctx->r5, ctx->r23);
    // 0x80095FB4: b           L_80095FDC
    // 0x80095FB8: lw          $a1, -0x5460($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5460);
        goto L_80095FDC;
    // 0x80095FB8: lw          $a1, -0x5460($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5460);
L_80095FBC:
    // 0x80095FBC: bne         $v0, $at, L_80095FD4
    if (ctx->r2 != ctx->r1) {
        // 0x80095FC0: lui         $a1, 0x800E
        ctx->r5 = S32(0X800E << 16);
            goto L_80095FD4;
    }
    // 0x80095FC0: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80095FC4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80095FC8: addu        $a1, $a1, $s7
    ctx->r5 = ADD32(ctx->r5, ctx->r23);
    // 0x80095FCC: b           L_80095FDC
    // 0x80095FD0: lw          $a1, -0x5440($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5440);
        goto L_80095FDC;
    // 0x80095FD0: lw          $a1, -0x5440($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5440);
L_80095FD4:
    // 0x80095FD4: addu        $a1, $a1, $s7
    ctx->r5 = ADD32(ctx->r5, ctx->r23);
    // 0x80095FD8: lw          $a1, -0x5470($a1)
    ctx->r5 = MEM_W(ctx->r5, -0X5470);
L_80095FDC:
    // 0x80095FDC: sw          $v1, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r3;
    // 0x80095FE0: jal         0x800967EC
    // 0x80095FE4: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    func_800967EC(rdram, ctx);
        goto after_0;
    // 0x80095FE4: sw          $a2, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r6;
    after_0:
    // 0x80095FE8: lw          $v1, 0x68($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X68);
    // 0x80095FEC: lw          $a2, 0x44($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X44);
    // 0x80095FF0: addiu       $a3, $zero, 0x3
    ctx->r7 = ADD32(0, 0X3);
L_80095FF4:
    // 0x80095FF4: addiu       $s5, $s5, 0x1
    ctx->r21 = ADD32(ctx->r21, 0X1);
L_80095FF8:
    // 0x80095FF8: addiu       $at, $zero, 0x11
    ctx->r1 = ADD32(0, 0X11);
    // 0x80095FFC: bnel        $s5, $at, L_80095D94
    if (ctx->r21 != ctx->r1) {
        // 0x80096000: sltiu       $at, $s5, 0x11
        ctx->r1 = ctx->r21 < 0X11 ? 1 : 0;
            goto L_80095D94;
    }
    goto skip_0;
    // 0x80096000: sltiu       $at, $s5, 0x11
    ctx->r1 = ctx->r21 < 0X11 ? 1 : 0;
    skip_0:
    // 0x80096004: lw          $t8, 0x60($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X60);
    // 0x80096008: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x8009600C: bnel        $v1, $t8, L_80095D78
    if (ctx->r3 != ctx->r24) {
        // 0x80096010: lh          $t2, 0x0($a2)
        ctx->r10 = MEM_H(ctx->r6, 0X0);
            goto L_80095D78;
    }
    goto skip_1;
    // 0x80096010: lh          $t2, 0x0($a2)
    ctx->r10 = MEM_H(ctx->r6, 0X0);
    skip_1:
    // 0x80096014: sw          $s1, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r17;
L_80096018:
    // 0x80096018: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8009601C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80096020: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80096024: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80096028: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8009602C: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x80096030: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x80096034: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x80096038: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x8009603C: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x80096040: jr          $ra
    // 0x80096044: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x80096044: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_80096048(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80096048: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x8009604C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80096050: addiu       $t7, $t7, -0x1828
    ctx->r15 = ADD32(ctx->r15, -0X1828);
    // 0x80096054: sll         $t6, $a1, 3
    ctx->r14 = S32(ctx->r5 << 3);
    // 0x80096058: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x8009605C: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x80096060: sll         $t2, $a1, 2
    ctx->r10 = S32(ctx->r5 << 2);
    // 0x80096064: subu        $t2, $t2, $a1
    ctx->r10 = SUB32(ctx->r10, ctx->r5);
    // 0x80096068: lw          $t1, 0x4($v0)
    ctx->r9 = MEM_W(ctx->r2, 0X4);
    // 0x8009606C: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x80096070: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x80096074: lui         $s7, 0xFF
    ctx->r23 = S32(0XFF << 16);
    // 0x80096078: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x8009607C: subu        $t2, $t2, $a1
    ctx->r10 = SUB32(ctx->r10, ctx->r5);
    // 0x80096080: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80096084: sll         $t0, $t8, 2
    ctx->r8 = S32(ctx->r24 << 2);
    // 0x80096088: ori         $s7, $s7, 0xFFFF
    ctx->r23 = ctx->r23 | 0XFFFF;
    // 0x8009608C: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x80096090: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x80096094: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x80096098: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x8009609C: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800960A0: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800960A4: addu        $v1, $v1, $t0
    ctx->r3 = ADD32(ctx->r3, ctx->r8);
    // 0x800960A8: addiu       $t3, $t3, -0x1880
    ctx->r11 = ADD32(ctx->r11, -0X1880);
    // 0x800960AC: sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10 << 2);
    // 0x800960B0: or          $s6, $a0, $zero
    ctx->r22 = ctx->r4 | 0;
    // 0x800960B4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800960B8: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800960BC: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800960C0: lw          $s3, -0x4B7C($v1)
    ctx->r19 = MEM_W(ctx->r3, -0X4B7C);
    // 0x800960C4: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x800960C8: addu        $fp, $t2, $t3
    ctx->r30 = ADD32(ctx->r10, ctx->r11);
    // 0x800960CC: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x800960D0: sw          $t8, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r24;
    // 0x800960D4: and         $s5, $t1, $s7
    ctx->r21 = ctx->r9 & ctx->r23;
L_800960D8:
    // 0x800960D8: lw          $s0, 0x0($s3)
    ctx->r16 = MEM_W(ctx->r19, 0X0);
    // 0x800960DC: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    // 0x800960E0: addu        $s1, $fp, $s2
    ctx->r17 = ADD32(ctx->r30, ctx->r18);
    // 0x800960E4: bne         $s0, $zero, L_80096114
    if (ctx->r16 != 0) {
        // 0x800960E8: and         $t5, $s0, $s7
        ctx->r13 = ctx->r16 & ctx->r23;
            goto L_80096114;
    }
    // 0x800960E8: and         $t5, $s0, $s7
    ctx->r13 = ctx->r16 & ctx->r23;
    // 0x800960EC: sw          $s4, 0x0($fp)
    MEM_W(0X0, ctx->r30) = ctx->r20;
    // 0x800960F0: lw          $t4, 0x40($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X40);
    // 0x800960F4: sltiu       $at, $t4, 0x9
    ctx->r1 = ctx->r12 < 0X9 ? 1 : 0;
    // 0x800960F8: beq         $at, $zero, L_80096188
    if (ctx->r1 == 0) {
        // 0x800960FC: sll         $t4, $t4, 2
        ctx->r12 = S32(ctx->r12 << 2);
            goto L_80096188;
    }
    // 0x800960FC: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x80096100: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80096104: addu        $at, $at, $t4
    gpr jr_addend_8009610C = ctx->r12;
    ctx->r1 = ADD32(ctx->r1, ctx->r12);
    // 0x80096108: lw          $t4, -0x4D4C($at)
    ctx->r12 = ADD32(ctx->r1, -0X4D4C);
    // 0x8009610C: jr          $t4
    // 0x80096110: nop

    switch (jr_addend_8009610C >> 2) {
        case 0: goto L_8009616C; break;
        case 1: goto L_80096148; break;
        case 2: goto L_80096158; break;
        case 3: goto L_80096134; break;
        case 4: goto L_80096158; break;
        case 5: goto L_80096188; break;
        case 6: goto L_80096134; break;
        case 7: goto L_80096188; break;
        case 8: goto L_8009617C; break;
        default: switch_error(__func__, 0x8009610C, 0x800EB2B4);
    }
    // 0x80096110: nop

L_80096114:
    // 0x80096114: jal         0x800967EC
    // 0x80096118: addu        $a0, $t5, $s6
    ctx->r4 = ADD32(ctx->r13, ctx->r22);
    func_800967EC(rdram, ctx);
        goto after_0;
    // 0x80096118: addu        $a0, $t5, $s6
    ctx->r4 = ADD32(ctx->r13, ctx->r22);
    after_0:
    // 0x8009611C: addu        $t6, $s0, $s5
    ctx->r14 = ADD32(ctx->r16, ctx->r21);
    // 0x80096120: sw          $t6, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->r14;
    // 0x80096124: addiu       $s4, $s4, 0x1
    ctx->r20 = ADD32(ctx->r20, 0X1);
    // 0x80096128: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x8009612C: b           L_800960D8
    // 0x80096130: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
        goto L_800960D8;
    // 0x80096130: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
L_80096134:
    // 0x80096134: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x80096138: jal         0x800961B8
    // 0x8009613C: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    func_800961B8(rdram, ctx);
        goto after_1;
    // 0x8009613C: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    after_1:
    // 0x80096140: b           L_80096188
    // 0x80096144: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
        goto L_80096188;
    // 0x80096144: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
L_80096148:
    // 0x80096148: jal         0x800962F0
    // 0x8009614C: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800962F0(rdram, ctx);
        goto after_2;
    // 0x8009614C: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_2:
    // 0x80096150: b           L_80096188
    // 0x80096154: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
        goto L_80096188;
    // 0x80096154: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
L_80096158:
    // 0x80096158: lw          $a0, 0x40($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X40);
    // 0x8009615C: jal         0x800963CC
    // 0x80096160: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    func_800963CC(rdram, ctx);
        goto after_3;
    // 0x80096160: or          $a1, $s5, $zero
    ctx->r5 = ctx->r21 | 0;
    after_3:
    // 0x80096164: b           L_80096188
    // 0x80096168: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
        goto L_80096188;
    // 0x80096168: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
L_8009616C:
    // 0x8009616C: jal         0x800965B8
    // 0x80096170: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800965B8(rdram, ctx);
        goto after_4;
    // 0x80096170: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_4:
    // 0x80096174: b           L_80096188
    // 0x80096178: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
        goto L_80096188;
    // 0x80096178: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
L_8009617C:
    // 0x8009617C: jal         0x800964CC
    // 0x80096180: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    func_800964CC(rdram, ctx);
        goto after_5;
    // 0x80096180: or          $a0, $s5, $zero
    ctx->r4 = ctx->r21 | 0;
    after_5:
    // 0x80096184: sw          $v0, 0x4($fp)
    MEM_W(0X4, ctx->r30) = ctx->r2;
L_80096188:
    // 0x80096188: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x8009618C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80096190: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80096194: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80096198: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x8009619C: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800961A0: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800961A4: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800961A8: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800961AC: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800961B0: jr          $ra
    // 0x800961B4: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800961B4: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_800961B8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800961B8: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x800961BC: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800961C0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800961C4: or          $s1, $a1, $zero
    ctx->r17 = ctx->r5 | 0;
    // 0x800961C8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800961CC: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800961D0: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800961D4: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800961D8: beq         $a0, $at, L_800961F4
    if (ctx->r4 == ctx->r1) {
        // 0x800961DC: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_800961F4;
    }
    // 0x800961DC: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800961E0: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800961E4: beq         $a0, $at, L_80096208
    if (ctx->r4 == ctx->r1) {
        // 0x800961E8: lui         $t7, 0x800
        ctx->r15 = S32(0X800 << 16);
            goto L_80096208;
    }
    // 0x800961E8: lui         $t7, 0x800
    ctx->r15 = S32(0X800 << 16);
    // 0x800961EC: b           L_80096214
    // 0x800961F0: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
        goto L_80096214;
    // 0x800961F0: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
L_800961F4:
    // 0x800961F4: lui         $t6, 0x800
    ctx->r14 = S32(0X800 << 16);
    // 0x800961F8: addiu       $t6, $t6, 0x2FA8
    ctx->r14 = ADD32(ctx->r14, 0X2FA8);
    // 0x800961FC: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x80096200: b           L_80096214
    // 0x80096204: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
        goto L_80096214;
    // 0x80096204: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_80096208:
    // 0x80096208: addiu       $t7, $t7, 0x2C00
    ctx->r15 = ADD32(ctx->r15, 0X2C00);
    // 0x8009620C: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x80096210: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_80096214:
    // 0x80096214: jal         0x80094088
    // 0x80096218: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x80096218: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    after_0:
    // 0x8009621C: addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // 0x80096220: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x80096224: blez        $s4, L_800962CC
    if (SIGNED(ctx->r20) <= 0) {
        // 0x80096228: or          $s3, $zero, $zero
        ctx->r19 = 0 | 0;
            goto L_800962CC;
    }
    // 0x80096228: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x8009622C: or          $s2, $t8, $zero
    ctx->r18 = ctx->r24 | 0;
L_80096230:
    // 0x80096230: jal         0x80094088
    // 0x80096234: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x80096234: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    after_1:
    // 0x80096238: addu        $s0, $v0, $s1
    ctx->r16 = ADD32(ctx->r2, ctx->r17);
    // 0x8009623C: sw          $s0, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r16;
    // 0x80096240: jal         0x80094088
    // 0x80096244: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x80096244: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x80096248: addu        $t9, $v0, $s1
    ctx->r25 = ADD32(ctx->r2, ctx->r17);
    // 0x8009624C: sw          $t9, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r25;
    // 0x80096250: jal         0x80094088
    // 0x80096254: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x80096254: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    after_3:
    // 0x80096258: addu        $t0, $v0, $s1
    ctx->r8 = ADD32(ctx->r2, ctx->r17);
    // 0x8009625C: sw          $t0, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r8;
    // 0x80096260: jal         0x80094088
    // 0x80096264: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    SegmentedToVirtual(rdram, ctx);
        goto after_4;
    // 0x80096264: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    after_4:
    // 0x80096268: addu        $t1, $v0, $s1
    ctx->r9 = ADD32(ctx->r2, ctx->r17);
    // 0x8009626C: sw          $t1, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r9;
    // 0x80096270: jal         0x80094088
    // 0x80096274: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    SegmentedToVirtual(rdram, ctx);
        goto after_5;
    // 0x80096274: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    after_5:
    // 0x80096278: addu        $t2, $v0, $s1
    ctx->r10 = ADD32(ctx->r2, ctx->r17);
    // 0x8009627C: sw          $t2, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r10;
    // 0x80096280: jal         0x80094088
    // 0x80096284: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    SegmentedToVirtual(rdram, ctx);
        goto after_6;
    // 0x80096284: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    after_6:
    // 0x80096288: addu        $t3, $v0, $s1
    ctx->r11 = ADD32(ctx->r2, ctx->r17);
    // 0x8009628C: sw          $t3, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r11;
    // 0x80096290: jal         0x80094088
    // 0x80096294: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    SegmentedToVirtual(rdram, ctx);
        goto after_7;
    // 0x80096294: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    after_7:
    // 0x80096298: addu        $t4, $v0, $s1
    ctx->r12 = ADD32(ctx->r2, ctx->r17);
    // 0x8009629C: sw          $t4, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r12;
    // 0x800962A0: jal         0x80094088
    // 0x800962A4: lw          $a0, 0x1C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X1C);
    SegmentedToVirtual(rdram, ctx);
        goto after_8;
    // 0x800962A4: lw          $a0, 0x1C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X1C);
    after_8:
    // 0x800962A8: addu        $t5, $v0, $s1
    ctx->r13 = ADD32(ctx->r2, ctx->r17);
    // 0x800962AC: sw          $t5, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->r13;
    // 0x800962B0: jal         0x80094088
    // 0x800962B4: lw          $a0, 0x20($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X20);
    SegmentedToVirtual(rdram, ctx);
        goto after_9;
    // 0x800962B4: lw          $a0, 0x20($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X20);
    after_9:
    // 0x800962B8: addiu       $s3, $s3, 0x1
    ctx->r19 = ADD32(ctx->r19, 0X1);
    // 0x800962BC: addu        $t6, $v0, $s1
    ctx->r14 = ADD32(ctx->r2, ctx->r17);
    // 0x800962C0: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x800962C4: bne         $s3, $s4, L_80096230
    if (ctx->r19 != ctx->r20) {
        // 0x800962C8: sw          $t6, 0x20($s0)
        MEM_W(0X20, ctx->r16) = ctx->r14;
            goto L_80096230;
    }
    // 0x800962C8: sw          $t6, 0x20($s0)
    MEM_W(0X20, ctx->r16) = ctx->r14;
L_800962CC:
    // 0x800962CC: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800962D0: lw          $v0, 0x38($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X38);
    // 0x800962D4: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800962D8: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800962DC: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800962E0: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800962E4: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800962E8: jr          $ra
    // 0x800962EC: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800962EC: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_800962F0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800962F0: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800962F4: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800962F8: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800962FC: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x80096300: lui         $a0, 0x800
    ctx->r4 = S32(0X800 << 16);
    // 0x80096304: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x80096308: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x8009630C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80096310: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80096314: jal         0x80094088
    // 0x80096318: addiu       $a0, $a0, 0x30EC
    ctx->r4 = ADD32(ctx->r4, 0X30EC);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x80096318: addiu       $a0, $a0, 0x30EC
    ctx->r4 = ADD32(ctx->r4, 0X30EC);
    after_0:
    // 0x8009631C: addu        $s2, $v0, $s1
    ctx->r18 = ADD32(ctx->r2, ctx->r17);
    // 0x80096320: sw          $s2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r18;
    // 0x80096324: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x80096328: addiu       $s4, $zero, 0xC
    ctx->r20 = ADD32(0, 0XC);
L_8009632C:
    // 0x8009632C: jal         0x80094088
    // 0x80096330: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x80096330: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    after_1:
    // 0x80096334: addu        $s0, $v0, $s1
    ctx->r16 = ADD32(ctx->r2, ctx->r17);
    // 0x80096338: sw          $s0, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r16;
    // 0x8009633C: jal         0x80094088
    // 0x80096340: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x80096340: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x80096344: addu        $t6, $v0, $s1
    ctx->r14 = ADD32(ctx->r2, ctx->r17);
    // 0x80096348: sw          $t6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r14;
    // 0x8009634C: jal         0x80094088
    // 0x80096350: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x80096350: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    after_3:
    // 0x80096354: addu        $t7, $v0, $s1
    ctx->r15 = ADD32(ctx->r2, ctx->r17);
    // 0x80096358: sw          $t7, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r15;
    // 0x8009635C: jal         0x80094088
    // 0x80096360: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    SegmentedToVirtual(rdram, ctx);
        goto after_4;
    // 0x80096360: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    after_4:
    // 0x80096364: addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // 0x80096368: sw          $t8, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r24;
    // 0x8009636C: jal         0x80094088
    // 0x80096370: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    SegmentedToVirtual(rdram, ctx);
        goto after_5;
    // 0x80096370: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    after_5:
    // 0x80096374: addu        $t9, $v0, $s1
    ctx->r25 = ADD32(ctx->r2, ctx->r17);
    // 0x80096378: sw          $t9, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r25;
    // 0x8009637C: jal         0x80094088
    // 0x80096380: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    SegmentedToVirtual(rdram, ctx);
        goto after_6;
    // 0x80096380: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    after_6:
    // 0x80096384: addu        $t0, $v0, $s1
    ctx->r8 = ADD32(ctx->r2, ctx->r17);
    // 0x80096388: sw          $t0, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r8;
    // 0x8009638C: jal         0x80094088
    // 0x80096390: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    SegmentedToVirtual(rdram, ctx);
        goto after_7;
    // 0x80096390: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    after_7:
    // 0x80096394: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x80096398: addu        $t1, $v0, $s1
    ctx->r9 = ADD32(ctx->r2, ctx->r17);
    // 0x8009639C: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x800963A0: bne         $s3, $s4, L_8009632C
    if (ctx->r19 != ctx->r20) {
        // 0x800963A4: sw          $t1, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r9;
            goto L_8009632C;
    }
    // 0x800963A4: sw          $t1, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r9;
    // 0x800963A8: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800963AC: lw          $v0, 0x34($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X34);
    // 0x800963B0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800963B4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800963B8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800963BC: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800963C0: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800963C4: jr          $ra
    // 0x800963C8: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800963C8: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void func_800963CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800963CC: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x800963D0: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800963D4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800963D8: or          $s3, $a1, $zero
    ctx->r19 = ctx->r5 | 0;
    // 0x800963DC: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800963E0: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800963E4: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800963E8: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800963EC: beq         $a0, $at, L_80096408
    if (ctx->r4 == ctx->r1) {
        // 0x800963F0: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_80096408;
    }
    // 0x800963F0: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800963F4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800963F8: beq         $a0, $at, L_8009641C
    if (ctx->r4 == ctx->r1) {
        // 0x800963FC: lui         $t7, 0x800
        ctx->r15 = S32(0X800 << 16);
            goto L_8009641C;
    }
    // 0x800963FC: lui         $t7, 0x800
    ctx->r15 = S32(0X800 << 16);
    // 0x80096400: b           L_80096428
    // 0x80096404: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
        goto L_80096428;
    // 0x80096404: lw          $s4, 0x40($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X40);
L_80096408:
    // 0x80096408: lui         $t6, 0x800
    ctx->r14 = S32(0X800 << 16);
    // 0x8009640C: addiu       $t6, $t6, 0x3578
    ctx->r14 = ADD32(ctx->r14, 0X3578);
    // 0x80096410: sw          $t6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r14;
    // 0x80096414: b           L_80096428
    // 0x80096418: addiu       $s4, $zero, 0x2
    ctx->r20 = ADD32(0, 0X2);
        goto L_80096428;
    // 0x80096418: addiu       $s4, $zero, 0x2
    ctx->r20 = ADD32(0, 0X2);
L_8009641C:
    // 0x8009641C: addiu       $t7, $t7, 0xD9C
    ctx->r15 = ADD32(ctx->r15, 0XD9C);
    // 0x80096420: sw          $t7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r15;
    // 0x80096424: addiu       $s4, $zero, 0x1
    ctx->r20 = ADD32(0, 0X1);
L_80096428:
    // 0x80096428: jal         0x80094088
    // 0x8009642C: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x8009642C: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    after_0:
    // 0x80096430: addu        $t8, $v0, $s3
    ctx->r24 = ADD32(ctx->r2, ctx->r19);
    // 0x80096434: sw          $t8, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r24;
    // 0x80096438: blez        $s4, L_800964A0
    if (SIGNED(ctx->r20) <= 0) {
        // 0x8009643C: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_800964A0;
    }
    // 0x8009643C: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x80096440: or          $s1, $t8, $zero
    ctx->r17 = ctx->r24 | 0;
L_80096444:
    // 0x80096444: jal         0x80094088
    // 0x80096448: lw          $a0, 0x0($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X0);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x80096448: lw          $a0, 0x0($s1)
    ctx->r4 = MEM_W(ctx->r17, 0X0);
    after_1:
    // 0x8009644C: addu        $s0, $v0, $s3
    ctx->r16 = ADD32(ctx->r2, ctx->r19);
    // 0x80096450: sw          $s0, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r16;
    // 0x80096454: jal         0x80094088
    // 0x80096458: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x80096458: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x8009645C: addu        $t9, $v0, $s3
    ctx->r25 = ADD32(ctx->r2, ctx->r19);
    // 0x80096460: sw          $t9, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r25;
    // 0x80096464: jal         0x80094088
    // 0x80096468: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x80096468: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    after_3:
    // 0x8009646C: addu        $t0, $v0, $s3
    ctx->r8 = ADD32(ctx->r2, ctx->r19);
    // 0x80096470: sw          $t0, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r8;
    // 0x80096474: jal         0x80094088
    // 0x80096478: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    SegmentedToVirtual(rdram, ctx);
        goto after_4;
    // 0x80096478: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    after_4:
    // 0x8009647C: addu        $t1, $v0, $s3
    ctx->r9 = ADD32(ctx->r2, ctx->r19);
    // 0x80096480: sw          $t1, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r9;
    // 0x80096484: jal         0x80094088
    // 0x80096488: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    SegmentedToVirtual(rdram, ctx);
        goto after_5;
    // 0x80096488: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    after_5:
    // 0x8009648C: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x80096490: addu        $t2, $v0, $s3
    ctx->r10 = ADD32(ctx->r2, ctx->r19);
    // 0x80096494: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x80096498: bne         $s2, $s4, L_80096444
    if (ctx->r18 != ctx->r20) {
        // 0x8009649C: sw          $t2, 0x10($s0)
        MEM_W(0X10, ctx->r16) = ctx->r10;
            goto L_80096444;
    }
    // 0x8009649C: sw          $t2, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r10;
L_800964A0:
    // 0x800964A0: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x800964A4: lw          $v0, 0x38($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X38);
    // 0x800964A8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800964AC: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800964B0: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800964B4: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800964B8: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800964BC: jr          $ra
    // 0x800964C0: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x800964C0: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_800964C4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800964C4: jr          $ra
    // 0x800964C8: nop

    return;
    // 0x800964C8: nop

;}
RECOMP_FUNC void func_800964CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800964CC: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800964D0: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800964D4: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800964D8: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800964DC: lui         $a0, 0x800
    ctx->r4 = S32(0X800 << 16);
    // 0x800964E0: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800964E4: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800964E8: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800964EC: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800964F0: jal         0x80094088
    // 0x800964F4: addiu       $a0, $a0, 0x1C58
    ctx->r4 = ADD32(ctx->r4, 0X1C58);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x800964F4: addiu       $a0, $a0, 0x1C58
    ctx->r4 = ADD32(ctx->r4, 0X1C58);
    after_0:
    // 0x800964F8: addu        $s2, $v0, $s1
    ctx->r18 = ADD32(ctx->r2, ctx->r17);
    // 0x800964FC: sw          $s2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r18;
    // 0x80096500: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x80096504: addiu       $s4, $zero, 0x8
    ctx->r20 = ADD32(0, 0X8);
L_80096508:
    // 0x80096508: jal         0x80094088
    // 0x8009650C: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x8009650C: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    after_1:
    // 0x80096510: addu        $s0, $v0, $s1
    ctx->r16 = ADD32(ctx->r2, ctx->r17);
    // 0x80096514: sw          $s0, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r16;
    // 0x80096518: jal         0x80094088
    // 0x8009651C: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x8009651C: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x80096520: addu        $t6, $v0, $s1
    ctx->r14 = ADD32(ctx->r2, ctx->r17);
    // 0x80096524: sw          $t6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r14;
    // 0x80096528: jal         0x80094088
    // 0x8009652C: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x8009652C: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    after_3:
    // 0x80096530: addu        $t7, $v0, $s1
    ctx->r15 = ADD32(ctx->r2, ctx->r17);
    // 0x80096534: sw          $t7, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r15;
    // 0x80096538: jal         0x80094088
    // 0x8009653C: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    SegmentedToVirtual(rdram, ctx);
        goto after_4;
    // 0x8009653C: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    after_4:
    // 0x80096540: addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // 0x80096544: sw          $t8, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r24;
    // 0x80096548: jal         0x80094088
    // 0x8009654C: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    SegmentedToVirtual(rdram, ctx);
        goto after_5;
    // 0x8009654C: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    after_5:
    // 0x80096550: addu        $t9, $v0, $s1
    ctx->r25 = ADD32(ctx->r2, ctx->r17);
    // 0x80096554: sw          $t9, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r25;
    // 0x80096558: jal         0x80094088
    // 0x8009655C: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    SegmentedToVirtual(rdram, ctx);
        goto after_6;
    // 0x8009655C: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    after_6:
    // 0x80096560: addu        $t0, $v0, $s1
    ctx->r8 = ADD32(ctx->r2, ctx->r17);
    // 0x80096564: sw          $t0, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r8;
    // 0x80096568: jal         0x80094088
    // 0x8009656C: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    SegmentedToVirtual(rdram, ctx);
        goto after_7;
    // 0x8009656C: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    after_7:
    // 0x80096570: addu        $t1, $v0, $s1
    ctx->r9 = ADD32(ctx->r2, ctx->r17);
    // 0x80096574: sw          $t1, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r9;
    // 0x80096578: jal         0x80094088
    // 0x8009657C: lw          $a0, 0x1C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X1C);
    SegmentedToVirtual(rdram, ctx);
        goto after_8;
    // 0x8009657C: lw          $a0, 0x1C($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X1C);
    after_8:
    // 0x80096580: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x80096584: addu        $t2, $v0, $s1
    ctx->r10 = ADD32(ctx->r2, ctx->r17);
    // 0x80096588: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x8009658C: bne         $s3, $s4, L_80096508
    if (ctx->r19 != ctx->r20) {
        // 0x80096590: sw          $t2, 0x1C($s0)
        MEM_W(0X1C, ctx->r16) = ctx->r10;
            goto L_80096508;
    }
    // 0x80096590: sw          $t2, 0x1C($s0)
    MEM_W(0X1C, ctx->r16) = ctx->r10;
    // 0x80096594: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x80096598: lw          $v0, 0x34($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X34);
    // 0x8009659C: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800965A0: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800965A4: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800965A8: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800965AC: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800965B0: jr          $ra
    // 0x800965B4: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800965B4: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void func_800965B8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800965B8: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800965BC: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800965C0: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x800965C4: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x800965C8: lui         $a0, 0x801
    ctx->r4 = S32(0X801 << 16);
    // 0x800965CC: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800965D0: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800965D4: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800965D8: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800965DC: jal         0x80094088
    // 0x800965E0: addiu       $a0, $a0, -0x3E04
    ctx->r4 = ADD32(ctx->r4, -0X3E04);
    SegmentedToVirtual(rdram, ctx);
        goto after_0;
    // 0x800965E0: addiu       $a0, $a0, -0x3E04
    ctx->r4 = ADD32(ctx->r4, -0X3E04);
    after_0:
    // 0x800965E4: addu        $s2, $v0, $s1
    ctx->r18 = ADD32(ctx->r2, ctx->r17);
    // 0x800965E8: sw          $s2, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r18;
    // 0x800965EC: or          $s3, $zero, $zero
    ctx->r19 = 0 | 0;
    // 0x800965F0: addiu       $s4, $zero, 0x20
    ctx->r20 = ADD32(0, 0X20);
L_800965F4:
    // 0x800965F4: jal         0x80094088
    // 0x800965F8: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    SegmentedToVirtual(rdram, ctx);
        goto after_1;
    // 0x800965F8: lw          $a0, 0x0($s2)
    ctx->r4 = MEM_W(ctx->r18, 0X0);
    after_1:
    // 0x800965FC: addu        $s0, $v0, $s1
    ctx->r16 = ADD32(ctx->r2, ctx->r17);
    // 0x80096600: sw          $s0, 0x0($s2)
    MEM_W(0X0, ctx->r18) = ctx->r16;
    // 0x80096604: jal         0x80094088
    // 0x80096608: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    SegmentedToVirtual(rdram, ctx);
        goto after_2;
    // 0x80096608: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_2:
    // 0x8009660C: addu        $t6, $v0, $s1
    ctx->r14 = ADD32(ctx->r2, ctx->r17);
    // 0x80096610: sw          $t6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->r14;
    // 0x80096614: jal         0x80094088
    // 0x80096618: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    SegmentedToVirtual(rdram, ctx);
        goto after_3;
    // 0x80096618: lw          $a0, 0x8($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X8);
    after_3:
    // 0x8009661C: addu        $t7, $v0, $s1
    ctx->r15 = ADD32(ctx->r2, ctx->r17);
    // 0x80096620: sw          $t7, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->r15;
    // 0x80096624: jal         0x80094088
    // 0x80096628: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    SegmentedToVirtual(rdram, ctx);
        goto after_4;
    // 0x80096628: lw          $a0, 0xC($s0)
    ctx->r4 = MEM_W(ctx->r16, 0XC);
    after_4:
    // 0x8009662C: addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // 0x80096630: sw          $t8, 0xC($s0)
    MEM_W(0XC, ctx->r16) = ctx->r24;
    // 0x80096634: jal         0x80094088
    // 0x80096638: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    SegmentedToVirtual(rdram, ctx);
        goto after_5;
    // 0x80096638: lw          $a0, 0x10($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X10);
    after_5:
    // 0x8009663C: addu        $t9, $v0, $s1
    ctx->r25 = ADD32(ctx->r2, ctx->r17);
    // 0x80096640: sw          $t9, 0x10($s0)
    MEM_W(0X10, ctx->r16) = ctx->r25;
    // 0x80096644: jal         0x80094088
    // 0x80096648: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    SegmentedToVirtual(rdram, ctx);
        goto after_6;
    // 0x80096648: lw          $a0, 0x14($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X14);
    after_6:
    // 0x8009664C: addu        $t0, $v0, $s1
    ctx->r8 = ADD32(ctx->r2, ctx->r17);
    // 0x80096650: sw          $t0, 0x14($s0)
    MEM_W(0X14, ctx->r16) = ctx->r8;
    // 0x80096654: jal         0x80094088
    // 0x80096658: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    SegmentedToVirtual(rdram, ctx);
        goto after_7;
    // 0x80096658: lw          $a0, 0x18($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X18);
    after_7:
    // 0x8009665C: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x80096660: addu        $t1, $v0, $s1
    ctx->r9 = ADD32(ctx->r2, ctx->r17);
    // 0x80096664: addiu       $s2, $s2, 0x4
    ctx->r18 = ADD32(ctx->r18, 0X4);
    // 0x80096668: bne         $s3, $s4, L_800965F4
    if (ctx->r19 != ctx->r20) {
        // 0x8009666C: sw          $t1, 0x18($s0)
        MEM_W(0X18, ctx->r16) = ctx->r9;
            goto L_800965F4;
    }
    // 0x8009666C: sw          $t1, 0x18($s0)
    MEM_W(0X18, ctx->r16) = ctx->r9;
    // 0x80096670: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x80096674: lw          $v0, 0x34($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X34);
    // 0x80096678: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x8009667C: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80096680: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80096684: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x80096688: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x8009668C: jr          $ra
    // 0x80096690: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x80096690: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void func_80096694(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80096694: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x80096698: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009669C: lw          $t6, -0x54DC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54DC);
    // 0x800966A0: sw          $fp, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r30;
    // 0x800966A4: sw          $s7, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r23;
    // 0x800966A8: addiu       $at, $zero, 0x1E
    ctx->r1 = ADD32(0, 0X1E);
    // 0x800966AC: or          $s7, $a0, $zero
    ctx->r23 = ctx->r4 | 0;
    // 0x800966B0: or          $fp, $a1, $zero
    ctx->r30 = ctx->r5 | 0;
    // 0x800966B4: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800966B8: sw          $s6, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r22;
    // 0x800966BC: sw          $s5, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r21;
    // 0x800966C0: sw          $s4, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r20;
    // 0x800966C4: sw          $s3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r19;
    // 0x800966C8: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x800966CC: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x800966D0: bne         $t6, $at, L_800966E4
    if (ctx->r14 != ctx->r1) {
        // 0x800966D4: sw          $s0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r16;
            goto L_800966E4;
    }
    // 0x800966D4: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800966D8: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800966DC: b           L_800966E8
    // 0x800966E0: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
        goto L_800966E8;
    // 0x800966E0: lw          $v0, -0x7E90($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X7E90);
L_800966E4:
    // 0x800966E4: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
L_800966E8:
    // 0x800966E8: sll         $t8, $v0, 2
    ctx->r24 = S32(ctx->r2 << 2);
    // 0x800966EC: sll         $t0, $v0, 2
    ctx->r8 = S32(ctx->r2 << 2);
    // 0x800966F0: subu        $t0, $t0, $v0
    ctx->r8 = SUB32(ctx->r8, ctx->r2);
    // 0x800966F4: subu        $t8, $t8, $v0
    ctx->r24 = SUB32(ctx->r24, ctx->r2);
    // 0x800966F8: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800966FC: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80096700: addiu       $t1, $t1, -0x1818
    ctx->r9 = ADD32(ctx->r9, -0X1818);
    // 0x80096704: addiu       $t9, $t9, -0x4888
    ctx->r25 = ADD32(ctx->r25, -0X4888);
    // 0x80096708: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8009670C: sll         $t0, $t0, 4
    ctx->r8 = S32(ctx->r8 << 4);
    // 0x80096710: lui         $s3, 0x800E
    ctx->r19 = S32(0X800E << 16);
    // 0x80096714: sll         $t7, $v0, 3
    ctx->r15 = S32(ctx->r2 << 3);
    // 0x80096718: lui         $s2, 0xFF
    ctx->r18 = S32(0XFF << 16);
    // 0x8009671C: ori         $s2, $s2, 0xFFFF
    ctx->r18 = ctx->r18 | 0XFFFF;
    // 0x80096720: sw          $t7, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r15;
    // 0x80096724: addiu       $s3, $s3, -0x48A0
    ctx->r19 = ADD32(ctx->r19, -0X48A0);
    // 0x80096728: addu        $s1, $t0, $t1
    ctx->r17 = ADD32(ctx->r8, ctx->r9);
    // 0x8009672C: addu        $s5, $t8, $t9
    ctx->r21 = ADD32(ctx->r24, ctx->r25);
    // 0x80096730: or          $s4, $zero, $zero
    ctx->r20 = 0 | 0;
    // 0x80096734: lui         $s6, 0x800
    ctx->r22 = S32(0X800 << 16);
L_80096738:
    // 0x80096738: lh          $t3, 0x0($s5)
    ctx->r11 = MEM_H(ctx->r21, 0X0);
    // 0x8009673C: lw          $s0, 0x0($s3)
    ctx->r16 = MEM_W(ctx->r19, 0X0);
    // 0x80096740: lw          $t2, 0x40($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X40);
    // 0x80096744: beq         $t3, $zero, L_8009679C
    if (ctx->r11 == 0) {
        // 0x80096748: addu        $s0, $s0, $t2
        ctx->r16 = ADD32(ctx->r16, ctx->r10);
            goto L_8009679C;
    }
    // 0x80096748: addu        $s0, $s0, $t2
    ctx->r16 = ADD32(ctx->r16, ctx->r10);
    // 0x8009674C: lw          $t4, 0x0($s0)
    ctx->r12 = MEM_W(ctx->r16, 0X0);
    // 0x80096750: or          $a1, $fp, $zero
    ctx->r5 = ctx->r30 | 0;
    // 0x80096754: and         $t5, $t4, $s2
    ctx->r13 = ctx->r12 & ctx->r18;
    // 0x80096758: addu        $t6, $t5, $s6
    ctx->r14 = ADD32(ctx->r13, ctx->r22);
    // 0x8009675C: sw          $t6, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->r14;
    // 0x80096760: lw          $t7, 0x4($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X4);
    // 0x80096764: and         $t8, $t7, $s2
    ctx->r24 = ctx->r15 & ctx->r18;
    // 0x80096768: addu        $t9, $t8, $s6
    ctx->r25 = ADD32(ctx->r24, ctx->r22);
    // 0x8009676C: sw          $t9, 0x18($s1)
    MEM_W(0X18, ctx->r17) = ctx->r25;
    // 0x80096770: lw          $t0, 0x0($s0)
    ctx->r8 = MEM_W(ctx->r16, 0X0);
    // 0x80096774: and         $t1, $t0, $s2
    ctx->r9 = ctx->r8 & ctx->r18;
    // 0x80096778: jal         0x800967EC
    // 0x8009677C: addu        $a0, $t1, $s7
    ctx->r4 = ADD32(ctx->r9, ctx->r23);
    func_800967EC(rdram, ctx);
        goto after_0;
    // 0x8009677C: addu        $a0, $t1, $s7
    ctx->r4 = ADD32(ctx->r9, ctx->r23);
    after_0:
    // 0x80096780: lw          $t2, 0x4($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X4);
    // 0x80096784: or          $a1, $fp, $zero
    ctx->r5 = ctx->r30 | 0;
    // 0x80096788: and         $t3, $t2, $s2
    ctx->r11 = ctx->r10 & ctx->r18;
    // 0x8009678C: jal         0x800967EC
    // 0x80096790: addu        $a0, $t3, $s7
    ctx->r4 = ADD32(ctx->r11, ctx->r23);
    func_800967EC(rdram, ctx);
        goto after_1;
    // 0x80096790: addu        $a0, $t3, $s7
    ctx->r4 = ADD32(ctx->r11, ctx->r23);
    after_1:
    // 0x80096794: b           L_800967A8
    // 0x80096798: addiu       $s4, $s4, 0x2
    ctx->r20 = ADD32(ctx->r20, 0X2);
        goto L_800967A8;
    // 0x80096798: addiu       $s4, $s4, 0x2
    ctx->r20 = ADD32(ctx->r20, 0X2);
L_8009679C:
    // 0x8009679C: sw          $zero, 0x0($s1)
    MEM_W(0X0, ctx->r17) = 0;
    // 0x800967A0: sw          $zero, 0x18($s1)
    MEM_W(0X18, ctx->r17) = 0;
    // 0x800967A4: addiu       $s4, $s4, 0x2
    ctx->r20 = ADD32(ctx->r20, 0X2);
L_800967A8:
    // 0x800967A8: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x800967AC: addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // 0x800967B0: addiu       $s5, $s5, 0x2
    ctx->r21 = ADD32(ctx->r21, 0X2);
    // 0x800967B4: bne         $s4, $at, L_80096738
    if (ctx->r20 != ctx->r1) {
        // 0x800967B8: addiu       $s1, $s1, 0x4
        ctx->r17 = ADD32(ctx->r17, 0X4);
            goto L_80096738;
    }
    // 0x800967B8: addiu       $s1, $s1, 0x4
    ctx->r17 = ADD32(ctx->r17, 0X4);
    // 0x800967BC: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800967C0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800967C4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x800967C8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x800967CC: lw          $s3, 0x24($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X24);
    // 0x800967D0: lw          $s4, 0x28($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X28);
    // 0x800967D4: lw          $s5, 0x2C($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X2C);
    // 0x800967D8: lw          $s6, 0x30($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X30);
    // 0x800967DC: lw          $s7, 0x34($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X34);
    // 0x800967E0: lw          $fp, 0x38($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X38);
    // 0x800967E4: jr          $ra
    // 0x800967E8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    return;
    // 0x800967E8: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
;}
RECOMP_FUNC void func_800967EC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800967EC: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x800967F0: addiu       $t0, $zero, 0xFD
    ctx->r8 = ADD32(0, 0XFD);
    // 0x800967F4: addiu       $a3, $zero, 0x4
    ctx->r7 = ADD32(0, 0X4);
    // 0x800967F8: addiu       $a2, $zero, 0xB8
    ctx->r6 = ADD32(0, 0XB8);
L_800967FC:
    // 0x800967FC: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x80096800: srl         $t6, $v1, 24
    ctx->r14 = S32(U32(ctx->r3) >> 24);
    // 0x80096804: beq         $t6, $a2, L_80096844
    if (ctx->r14 == ctx->r6) {
        // 0x80096808: or          $v1, $t6, $zero
        ctx->r3 = ctx->r14 | 0;
            goto L_80096844;
    }
    // 0x80096808: or          $v1, $t6, $zero
    ctx->r3 = ctx->r14 | 0;
    // 0x8009680C: bne         $t6, $a3, L_8009681C
    if (ctx->r14 != ctx->r7) {
        // 0x80096810: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_8009681C;
    }
    // 0x80096810: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x80096814: b           L_80096828
    // 0x80096818: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
        goto L_80096828;
    // 0x80096818: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
L_8009681C:
    // 0x8009681C: bne         $v1, $t0, L_80096828
    if (ctx->r3 != ctx->r8) {
        // 0x80096820: nop
    
            goto L_80096828;
    }
    // 0x80096820: nop

    // 0x80096824: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
L_80096828:
    // 0x80096828: beq         $a0, $zero, L_8009683C
    if (ctx->r4 == 0) {
        // 0x8009682C: addiu       $v1, $v0, 0x4
        ctx->r3 = ADD32(ctx->r2, 0X4);
            goto L_8009683C;
    }
    // 0x8009682C: addiu       $v1, $v0, 0x4
    ctx->r3 = ADD32(ctx->r2, 0X4);
    // 0x80096830: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x80096834: addu        $t8, $t7, $a1
    ctx->r24 = ADD32(ctx->r15, ctx->r5);
    // 0x80096838: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
L_8009683C:
    // 0x8009683C: b           L_800967FC
    // 0x80096840: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
        goto L_800967FC;
    // 0x80096840: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
L_80096844:
    // 0x80096844: jr          $ra
    // 0x80096848: nop

    return;
    // 0x80096848: nop

;}
RECOMP_FUNC void func_8009684C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009684C: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x80096850: sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // 0x80096854: or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // 0x80096858: sw          $s2, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r18;
    // 0x8009685C: sw          $s1, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r17;
    // 0x80096860: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80096864: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80096868: lui         $a3, 0x801D
    ctx->r7 = S32(0X801D << 16);
    // 0x8009686C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80096870: lui         $t5, 0xFF
    ctx->r13 = S32(0XFF << 16);
    // 0x80096874: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x80096878: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x8009687C: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x80096880: addiu       $t2, $t2, -0x1898
    ctx->r10 = ADD32(ctx->r10, -0X1898);
    // 0x80096884: addiu       $t3, $t3, -0x4AA8
    ctx->r11 = ADD32(ctx->r11, -0X4AA8);
    // 0x80096888: addiu       $t4, $t4, -0x4B58
    ctx->r12 = ADD32(ctx->r12, -0X4B58);
    // 0x8009688C: ori         $t5, $t5, 0xFFFF
    ctx->r13 = ctx->r13 | 0XFFFF;
    // 0x80096890: addiu       $t0, $t0, -0x4AC8
    ctx->r8 = ADD32(ctx->r8, -0X4AC8);
    // 0x80096894: addiu       $a3, $a3, -0x1828
    ctx->r7 = ADD32(ctx->r7, -0X1828);
    // 0x80096898: addiu       $s0, $s0, -0x31E8
    ctx->r16 = ADD32(ctx->r16, -0X31E8);
    // 0x8009689C: addiu       $a0, $a0, -0x4AC8
    ctx->r4 = ADD32(ctx->r4, -0X4AC8);
    // 0x800968A0: addiu       $s1, $zero, -0x40
    ctx->r17 = ADD32(0, -0X40);
    // 0x800968A4: addiu       $s2, $zero, 0x1
    ctx->r18 = ADD32(0, 0X1);
    // 0x800968A8: addiu       $t1, $zero, -0x1
    ctx->r9 = ADD32(0, -0X1);
L_800968AC:
    // 0x800968AC: bne         $t0, $a0, L_800968CC
    if (ctx->r8 != ctx->r4) {
        // 0x800968B0: nop
    
            goto L_800968CC;
    }
    // 0x800968B0: nop

    // 0x800968B4: beq         $a1, $t1, L_800968E0
    if (ctx->r5 == ctx->r9) {
        // 0x800968B8: or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
            goto L_800968E0;
    }
    // 0x800968B8: or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // 0x800968BC: sll         $t6, $a1, 1
    ctx->r14 = S32(ctx->r5 << 1);
    // 0x800968C0: addu        $t7, $t2, $t6
    ctx->r15 = ADD32(ctx->r10, ctx->r14);
    // 0x800968C4: b           L_800968E0
    // 0x800968C8: sh          $zero, 0x0($t7)
    MEM_H(0X0, ctx->r15) = 0;
        goto L_800968E0;
    // 0x800968C8: sh          $zero, 0x0($t7)
    MEM_H(0X0, ctx->r15) = 0;
L_800968CC:
    // 0x800968CC: beq         $a2, $t1, L_800968E0
    if (ctx->r6 == ctx->r9) {
        // 0x800968D0: or          $v1, $a2, $zero
        ctx->r3 = ctx->r6 | 0;
            goto L_800968E0;
    }
    // 0x800968D0: or          $v1, $a2, $zero
    ctx->r3 = ctx->r6 | 0;
    // 0x800968D4: sll         $t8, $a2, 1
    ctx->r24 = S32(ctx->r6 << 1);
    // 0x800968D8: addu        $t9, $t2, $t8
    ctx->r25 = ADD32(ctx->r10, ctx->r24);
    // 0x800968DC: sh          $s2, 0x0($t9)
    MEM_H(0X0, ctx->r25) = ctx->r18;
L_800968E0:
    // 0x800968E0: sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // 0x800968E4: bne         $v1, $t1, L_800968F8
    if (ctx->r3 != ctx->r9) {
        // 0x800968E8: sw          $v0, 0x4($a3)
        MEM_W(0X4, ctx->r7) = ctx->r2;
            goto L_800968F8;
    }
    // 0x800968E8: sw          $v0, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->r2;
    // 0x800968EC: sw          $zero, 0x8($t0)
    MEM_W(0X8, ctx->r8) = 0;
    // 0x800968F0: b           L_80096940
    // 0x800968F4: sw          $zero, 0xC($t0)
    MEM_W(0XC, ctx->r8) = 0;
        goto L_80096940;
    // 0x800968F4: sw          $zero, 0xC($t0)
    MEM_W(0XC, ctx->r8) = 0;
L_800968F8:
    // 0x800968F8: sll         $t6, $v1, 4
    ctx->r14 = S32(ctx->r3 << 4);
    // 0x800968FC: addu        $t7, $t4, $t6
    ctx->r15 = ADD32(ctx->r12, ctx->r14);
    // 0x80096900: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x80096904: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x80096908: and         $t6, $v0, $t5
    ctx->r14 = ctx->r2 & ctx->r13;
    // 0x8009690C: sw          $at, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->r1;
    // 0x80096910: lw          $t9, 0x4($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X4);
    // 0x80096914: sw          $t9, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->r25;
    // 0x80096918: lw          $at, 0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X8);
    // 0x8009691C: sw          $at, 0x8($t0)
    MEM_W(0X8, ctx->r8) = ctx->r1;
    // 0x80096920: lw          $t9, 0xC($t7)
    ctx->r25 = MEM_W(ctx->r15, 0XC);
    // 0x80096924: addu        $t7, $s0, $t8
    ctx->r15 = ADD32(ctx->r16, ctx->r24);
    // 0x80096928: sw          $t9, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r25;
    // 0x8009692C: lw          $t9, 0x0($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X0);
    // 0x80096930: sw          $t6, 0xC($t0)
    MEM_W(0XC, ctx->r8) = ctx->r14;
    // 0x80096934: addu        $v0, $v0, $t9
    ctx->r2 = ADD32(ctx->r2, ctx->r25);
    // 0x80096938: addiu       $t6, $v0, 0x3F
    ctx->r14 = ADD32(ctx->r2, 0X3F);
    // 0x8009693C: and         $v0, $t6, $s1
    ctx->r2 = ctx->r14 & ctx->r17;
L_80096940:
    // 0x80096940: addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // 0x80096944: bne         $t0, $t3, L_800968AC
    if (ctx->r8 != ctx->r11) {
        // 0x80096948: addiu       $a3, $a3, 0x8
        ctx->r7 = ADD32(ctx->r7, 0X8);
            goto L_800968AC;
    }
    // 0x80096948: addiu       $a3, $a3, 0x8
    ctx->r7 = ADD32(ctx->r7, 0X8);
    // 0x8009694C: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
    // 0x80096950: lw          $s1, 0x8($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X8);
    // 0x80096954: lw          $s2, 0xC($sp)
    ctx->r18 = MEM_W(ctx->r29, 0XC);
    // 0x80096958: jr          $ra
    // 0x8009695C: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    return;
    // 0x8009695C: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
;}
RECOMP_FUNC void func_80096960(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80096960: addiu       $sp, $sp, -0x70
    ctx->r29 = ADD32(ctx->r29, -0X70);
    // 0x80096964: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80096968: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009696C: sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // 0x80096970: sw          $a0, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->r4;
    // 0x80096974: sw          $a1, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->r5;
    // 0x80096978: sw          $a2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->r6;
    // 0x8009697C: sw          $a3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r7;
    // 0x80096980: addiu       $v0, $v0, -0x18A0
    ctx->r2 = ADD32(ctx->r2, -0X18A0);
    // 0x80096984: addiu       $t1, $t1, -0x18C0
    ctx->r9 = ADD32(ctx->r9, -0X18C0);
    // 0x80096988: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x8009698C: addiu       $t4, $zero, 0x1
    ctx->r12 = ADD32(0, 0X1);
L_80096990:
    // 0x80096990: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x80096994: sltu        $at, $t1, $v0
    ctx->r1 = ctx->r9 < ctx->r2 ? 1 : 0;
    // 0x80096998: bne         $at, $zero, L_80096990
    if (ctx->r1 != 0) {
        // 0x8009699C: sh          $t4, -0x2($t1)
        MEM_H(-0X2, ctx->r9) = ctx->r12;
            goto L_80096990;
    }
    // 0x8009699C: sh          $t4, -0x2($t1)
    MEM_H(-0X2, ctx->r9) = ctx->r12;
    // 0x800969A0: lw          $t8, 0x70($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X70);
    // 0x800969A4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800969A8: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x800969AC: addiu       $a2, $a2, -0x18A0
    ctx->r6 = ADD32(ctx->r6, -0X18A0);
    // 0x800969B0: addiu       $v0, $v0, -0x18C4
    ctx->r2 = ADD32(ctx->r2, -0X18C4);
    // 0x800969B4: addiu       $t6, $zero, -0x1
    ctx->r14 = ADD32(0, -0X1);
    // 0x800969B8: sltiu       $at, $t8, 0x5
    ctx->r1 = ctx->r24 < 0X5 ? 1 : 0;
    // 0x800969BC: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
    // 0x800969C0: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
    // 0x800969C4: beq         $at, $zero, L_80096AB4
    if (ctx->r1 == 0) {
        // 0x800969C8: sw          $t8, 0x0($v0)
        MEM_W(0X0, ctx->r2) = ctx->r24;
            goto L_80096AB4;
    }
    // 0x800969C8: sw          $t8, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r24;
    // 0x800969CC: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x800969D0: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800969D4: addu        $at, $at, $t9
    gpr jr_addend_800969DC = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x800969D8: lw          $t9, -0x4D28($at)
    ctx->r25 = ADD32(ctx->r1, -0X4D28);
    // 0x800969DC: jr          $t9
    // 0x800969E0: nop

    switch (jr_addend_800969DC >> 2) {
        case 0: goto L_800969E4; break;
        case 1: goto L_80096A00; break;
        case 2: goto L_80096A28; break;
        case 3: goto L_80096A54; break;
        case 4: goto L_80096A90; break;
        default: switch_error(__func__, 0x800969DC, 0x800EB2D8);
    }
    // 0x800969E0: nop

L_800969E4:
    // 0x800969E4: addiu       $s0, $zero, 0x4
    ctx->r16 = ADD32(0, 0X4);
    // 0x800969E8: addiu       $t6, $zero, 0x7
    ctx->r14 = ADD32(0, 0X7);
    // 0x800969EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800969F0: sw          $t6, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r14;
    // 0x800969F4: sh          $zero, -0x18BE($at)
    MEM_H(-0X18BE, ctx->r1) = 0;
    // 0x800969F8: b           L_80096AB4
    // 0x800969FC: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
        goto L_80096AB4;
    // 0x800969FC: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
L_80096A00:
    // 0x80096A00: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80096A04: addiu       $v1, $v1, -0x18C0
    ctx->r3 = ADD32(ctx->r3, -0X18C0);
    // 0x80096A08: sh          $zero, 0x6($v1)
    MEM_H(0X6, ctx->r3) = 0;
    // 0x80096A0C: lh          $t8, 0x6($v1)
    ctx->r24 = MEM_H(ctx->r3, 0X6);
    // 0x80096A10: addiu       $s0, $zero, 0x2
    ctx->r16 = ADD32(0, 0X2);
    // 0x80096A14: addiu       $t7, $zero, 0x2
    ctx->r15 = ADD32(0, 0X2);
    // 0x80096A18: sw          $t7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r15;
    // 0x80096A1C: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
    // 0x80096A20: b           L_80096AB4
    // 0x80096A24: sh          $t8, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r24;
        goto L_80096AB4;
    // 0x80096A24: sh          $t8, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r24;
L_80096A28:
    // 0x80096A28: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80096A2C: sh          $zero, -0x18BE($at)
    MEM_H(-0X18BE, ctx->r1) = 0;
    // 0x80096A30: sh          $zero, -0x18BA($at)
    MEM_H(-0X18BA, ctx->r1) = 0;
    // 0x80096A34: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80096A38: addiu       $s0, $zero, 0x4
    ctx->r16 = ADD32(0, 0X4);
    // 0x80096A3C: addiu       $t9, $zero, 0x4
    ctx->r25 = ADD32(0, 0X4);
    // 0x80096A40: sh          $zero, -0x18B6($at)
    MEM_H(-0X18B6, ctx->r1) = 0;
    // 0x80096A44: sh          $zero, -0x18B2($at)
    MEM_H(-0X18B2, ctx->r1) = 0;
    // 0x80096A48: sw          $t9, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r25;
    // 0x80096A4C: b           L_80096AB4
    // 0x80096A50: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
        goto L_80096AB4;
    // 0x80096A50: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
L_80096A54:
    // 0x80096A54: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80096A58: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80096A5C: addiu       $v1, $v1, -0x18A0
    ctx->r3 = ADD32(ctx->r3, -0X18A0);
    // 0x80096A60: addiu       $t1, $t1, -0x18C0
    ctx->r9 = ADD32(ctx->r9, -0X18C0);
L_80096A64:
    // 0x80096A64: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
    // 0x80096A68: sh          $zero, -0xE($t1)
    MEM_H(-0XE, ctx->r9) = 0;
    // 0x80096A6C: sh          $zero, -0xA($t1)
    MEM_H(-0XA, ctx->r9) = 0;
    // 0x80096A70: sh          $zero, -0x6($t1)
    MEM_H(-0X6, ctx->r9) = 0;
    // 0x80096A74: bne         $t1, $v1, L_80096A64
    if (ctx->r9 != ctx->r3) {
        // 0x80096A78: sh          $zero, -0x2($t1)
        MEM_H(-0X2, ctx->r9) = 0;
            goto L_80096A64;
    }
    // 0x80096A78: sh          $zero, -0x2($t1)
    MEM_H(-0X2, ctx->r9) = 0;
    // 0x80096A7C: addiu       $s0, $zero, 0x8
    ctx->r16 = ADD32(0, 0X8);
    // 0x80096A80: addiu       $t6, $zero, 0x8
    ctx->r14 = ADD32(0, 0X8);
    // 0x80096A84: sw          $t6, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r14;
    // 0x80096A88: b           L_80096AB4
    // 0x80096A8C: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
        goto L_80096AB4;
    // 0x80096A8C: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
L_80096A90:
    // 0x80096A90: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80096A94: addiu       $v1, $v1, -0x18C0
    ctx->r3 = ADD32(ctx->r3, -0X18C0);
    // 0x80096A98: sh          $zero, 0x6($v1)
    MEM_H(0X6, ctx->r3) = 0;
    // 0x80096A9C: lh          $t8, 0x6($v1)
    ctx->r24 = MEM_H(ctx->r3, 0X6);
    // 0x80096AA0: addiu       $s0, $zero, 0x4
    ctx->r16 = ADD32(0, 0X4);
    // 0x80096AA4: addiu       $t7, $zero, 0x6
    ctx->r15 = ADD32(0, 0X6);
    // 0x80096AA8: sw          $t7, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r15;
    // 0x80096AAC: sw          $s0, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->r16;
    // 0x80096AB0: sh          $t8, 0x2($v1)
    MEM_H(0X2, ctx->r3) = ctx->r24;
L_80096AB4:
    // 0x80096AB4: lw          $s0, 0x68($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X68);
    // 0x80096AB8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x80096ABC: addiu       $a1, $a1, -0x4CD0
    ctx->r5 = ADD32(ctx->r5, -0X4CD0);
    // 0x80096AC0: blez        $s0, L_80096C0C
    if (SIGNED(ctx->r16) <= 0) {
        // 0x80096AC4: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_80096C0C;
    }
    // 0x80096AC4: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80096AC8: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80096ACC: addiu       $t1, $t1, -0x18C0
    ctx->r9 = ADD32(ctx->r9, -0X18C0);
    // 0x80096AD0: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x80096AD4: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x80096AD8: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x80096ADC: lw          $a0, 0x60($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X60);
L_80096AE0:
    // 0x80096AE0: or          $t5, $a1, $zero
    ctx->r13 = ctx->r5 | 0;
    // 0x80096AE4: bgez        $t0, L_80096AF8
    if (SIGNED(ctx->r8) >= 0) {
        // 0x80096AE8: andi        $v0, $t0, 0x3
        ctx->r2 = ctx->r8 & 0X3;
            goto L_80096AF8;
    }
    // 0x80096AE8: andi        $v0, $t0, 0x3
    ctx->r2 = ctx->r8 & 0X3;
    // 0x80096AEC: beq         $v0, $zero, L_80096AF8
    if (ctx->r2 == 0) {
        // 0x80096AF0: nop
    
            goto L_80096AF8;
    }
    // 0x80096AF0: nop

    // 0x80096AF4: addiu       $v0, $v0, -0x4
    ctx->r2 = ADD32(ctx->r2, -0X4);
L_80096AF8:
    // 0x80096AF8: beq         $v0, $zero, L_80096B20
    if (ctx->r2 == 0) {
        // 0x80096AFC: lui         $t6, 0x800E
        ctx->r14 = S32(0X800E << 16);
            goto L_80096B20;
    }
    // 0x80096AFC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x80096B00: beq         $v0, $t4, L_80096B28
    if (ctx->r2 == ctx->r12) {
        // 0x80096B04: nop
    
            goto L_80096B28;
    }
    // 0x80096B04: nop

    // 0x80096B08: beq         $v0, $t2, L_80096B30
    if (ctx->r2 == ctx->r10) {
        // 0x80096B0C: nop
    
            goto L_80096B30;
    }
    // 0x80096B0C: nop

    // 0x80096B10: beql        $v0, $t3, L_80096B3C
    if (ctx->r2 == ctx->r11) {
        // 0x80096B14: lw          $a0, 0x80($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X80);
            goto L_80096B3C;
    }
    goto skip_0;
    // 0x80096B14: lw          $a0, 0x80($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X80);
    skip_0:
    // 0x80096B18: b           L_80096B3C
    // 0x80096B1C: nop

        goto L_80096B3C;
    // 0x80096B1C: nop

L_80096B20:
    // 0x80096B20: b           L_80096B3C
    // 0x80096B24: lw          $a0, 0x74($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X74);
        goto L_80096B3C;
    // 0x80096B24: lw          $a0, 0x74($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X74);
L_80096B28:
    // 0x80096B28: b           L_80096B3C
    // 0x80096B2C: lw          $a0, 0x78($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X78);
        goto L_80096B3C;
    // 0x80096B2C: lw          $a0, 0x78($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X78);
L_80096B30:
    // 0x80096B30: b           L_80096B3C
    // 0x80096B34: lw          $a0, 0x7C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X7C);
        goto L_80096B3C;
    // 0x80096B34: lw          $a0, 0x7C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X7C);
    // 0x80096B38: lw          $a0, 0x80($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X80);
L_80096B3C:
    // 0x80096B3C: bgez        $a0, L_80096B48
    if (SIGNED(ctx->r4) >= 0) {
        // 0x80096B40: addiu       $t6, $t6, -0x5430
        ctx->r14 = ADD32(ctx->r14, -0X5430);
            goto L_80096B48;
    }
    // 0x80096B40: addiu       $t6, $t6, -0x5430
    ctx->r14 = ADD32(ctx->r14, -0X5430);
    // 0x80096B44: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_80096B48:
    // 0x80096B48: sll         $t9, $a0, 4
    ctx->r25 = S32(ctx->r4 << 4);
    // 0x80096B4C: slti        $at, $t0, 0x4
    ctx->r1 = SIGNED(ctx->r8) < 0X4 ? 1 : 0;
    // 0x80096B50: bne         $at, $zero, L_80096B60
    if (ctx->r1 != 0) {
        // 0x80096B54: addu        $v0, $t9, $t6
        ctx->r2 = ADD32(ctx->r25, ctx->r14);
            goto L_80096B60;
    }
    // 0x80096B54: addu        $v0, $t9, $t6
    ctx->r2 = ADD32(ctx->r25, ctx->r14);
    // 0x80096B58: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x80096B5C: addiu       $v0, $v0, 0x40
    ctx->r2 = ADD32(ctx->r2, 0X40);
L_80096B60:
    // 0x80096B60: lh          $t7, 0x2($t1)
    ctx->r15 = MEM_H(ctx->r9, 0X2);
    // 0x80096B64: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    // 0x80096B68: sh          $a0, 0x0($t1)
    MEM_H(0X0, ctx->r9) = ctx->r4;
    // 0x80096B6C: beq         $t7, $zero, L_80096B7C
    if (ctx->r15 == 0) {
        // 0x80096B70: addiu       $t6, $zero, 0x4
        ctx->r14 = ADD32(0, 0X4);
            goto L_80096B7C;
    }
    // 0x80096B70: addiu       $t6, $zero, 0x4
    ctx->r14 = ADD32(0, 0X4);
    // 0x80096B74: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    // 0x80096B78: addiu       $v0, $v0, 0x80
    ctx->r2 = ADD32(ctx->r2, 0X80);
L_80096B7C:
    // 0x80096B7C: lw          $at, 0x0($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X0);
    // 0x80096B80: lw          $t9, 0x4($v0)
    ctx->r25 = MEM_W(ctx->r2, 0X4);
    // 0x80096B84: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80096B88: sw          $at, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r1;
    // 0x80096B8C: lw          $at, 0x8($v0)
    ctx->r1 = MEM_W(ctx->r2, 0X8);
    // 0x80096B90: sw          $t9, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->r25;
    // 0x80096B94: lw          $t9, 0xC($v0)
    ctx->r25 = MEM_W(ctx->r2, 0XC);
    // 0x80096B98: sw          $at, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r1;
    // 0x80096B9C: sw          $t6, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->r14;
    // 0x80096BA0: sw          $t9, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r25;
    // 0x80096BA4: lw          $v1, -0x18C4($v1)
    ctx->r3 = MEM_W(ctx->r3, -0X18C4);
    // 0x80096BA8: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x80096BAC: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x80096BB0: beq         $t3, $v1, L_80096BC0
    if (ctx->r11 == ctx->r3) {
        // 0x80096BB4: addu        $t7, $t7, $a3
        ctx->r15 = ADD32(ctx->r15, ctx->r7);
            goto L_80096BC0;
    }
    // 0x80096BB4: addu        $t7, $t7, $a3
    ctx->r15 = ADD32(ctx->r15, ctx->r7);
    // 0x80096BB8: bne         $t2, $v1, L_80096BCC
    if (ctx->r10 != ctx->r3) {
        // 0x80096BBC: addiu       $at, $zero, 0x4
        ctx->r1 = ADD32(0, 0X4);
            goto L_80096BCC;
    }
    // 0x80096BBC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
L_80096BC0:
    // 0x80096BC0: lw          $t7, -0x5460($t7)
    ctx->r15 = MEM_W(ctx->r15, -0X5460);
    // 0x80096BC4: b           L_80096BF4
    // 0x80096BC8: sw          $t7, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r15;
        goto L_80096BF4;
    // 0x80096BC8: sw          $t7, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r15;
L_80096BCC:
    // 0x80096BCC: bne         $v1, $at, L_80096BE8
    if (ctx->r3 != ctx->r1) {
        // 0x80096BD0: lui         $t9, 0x800E
        ctx->r25 = S32(0X800E << 16);
            goto L_80096BE8;
    }
    // 0x80096BD0: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x80096BD4: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x80096BD8: addu        $t8, $t8, $a3
    ctx->r24 = ADD32(ctx->r24, ctx->r7);
    // 0x80096BDC: lw          $t8, -0x5440($t8)
    ctx->r24 = MEM_W(ctx->r24, -0X5440);
    // 0x80096BE0: b           L_80096BF4
    // 0x80096BE4: sw          $t8, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r24;
        goto L_80096BF4;
    // 0x80096BE4: sw          $t8, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r24;
L_80096BE8:
    // 0x80096BE8: addu        $t9, $t9, $a3
    ctx->r25 = ADD32(ctx->r25, ctx->r7);
    // 0x80096BEC: lw          $t9, -0x5470($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X5470);
    // 0x80096BF0: sw          $t9, 0xC($a1)
    MEM_W(0XC, ctx->r5) = ctx->r25;
L_80096BF4:
    // 0x80096BF4: addiu       $a3, $a3, 0x4
    ctx->r7 = ADD32(ctx->r7, 0X4);
    // 0x80096BF8: bne         $t0, $s0, L_80096AE0
    if (ctx->r8 != ctx->r16) {
        // 0x80096BFC: addiu       $a1, $a1, 0x10
        ctx->r5 = ADD32(ctx->r5, 0X10);
            goto L_80096AE0;
    }
    // 0x80096BFC: addiu       $a1, $a1, 0x10
    ctx->r5 = ADD32(ctx->r5, 0X10);
    // 0x80096C00: sw          $a0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r4;
    // 0x80096C04: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80096C08: sw          $t5, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r13;
L_80096C0C:
    // 0x80096C0C: lw          $t5, 0x54($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X54);
    // 0x80096C10: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x80096C14: addiu       $t3, $zero, 0x3
    ctx->r11 = ADD32(0, 0X3);
    // 0x80096C18: addiu       $v0, $sp, 0x40
    ctx->r2 = ADD32(ctx->r29, 0X40);
    // 0x80096C1C: addiu       $v1, $sp, 0x50
    ctx->r3 = ADD32(ctx->r29, 0X50);
    // 0x80096C20: addiu       $t5, $t5, 0x10
    ctx->r13 = ADD32(ctx->r13, 0X10);
    // 0x80096C24: sw          $zero, 0x0($t5)
    MEM_W(0X0, ctx->r13) = 0;
    // 0x80096C28: sw          $zero, 0x4($t5)
    MEM_W(0X4, ctx->r13) = 0;
    // 0x80096C2C: sw          $zero, 0x8($t5)
    MEM_W(0X8, ctx->r13) = 0;
    // 0x80096C30: sw          $zero, 0xC($t5)
    MEM_W(0XC, ctx->r13) = 0;
L_80096C34:
    // 0x80096C34: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x80096C38: sltu        $at, $v0, $v1
    ctx->r1 = ctx->r2 < ctx->r3 ? 1 : 0;
    // 0x80096C3C: bne         $at, $zero, L_80096C34
    if (ctx->r1 != 0) {
        // 0x80096C40: sh          $zero, -0x2($v0)
        MEM_H(-0X2, ctx->r2) = 0;
            goto L_80096C34;
    }
    // 0x80096C40: sh          $zero, -0x2($v0)
    MEM_H(-0X2, ctx->r2) = 0;
    // 0x80096C44: lw          $t6, 0x70($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X70);
    // 0x80096C48: sltiu       $at, $t6, 0x5
    ctx->r1 = ctx->r14 < 0X5 ? 1 : 0;
    // 0x80096C4C: beq         $at, $zero, L_80097C68
    if (ctx->r1 == 0) {
        // 0x80096C50: sw          $t6, 0x1C($sp)
        MEM_W(0X1C, ctx->r29) = ctx->r14;
            goto L_80097C68;
    }
    // 0x80096C50: sw          $t6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r14;
    // 0x80096C54: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80096C58: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80096C5C: addu        $at, $at, $t7
    gpr jr_addend_80096C64 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x80096C60: lw          $t7, -0x4D14($at)
    ctx->r15 = ADD32(ctx->r1, -0X4D14);
    // 0x80096C64: jr          $t7
    // 0x80096C68: nop

    switch (jr_addend_80096C64 >> 2) {
        case 0: goto L_80096C6C; break;
        case 1: goto L_80097154; break;
        case 2: goto L_8009736C; break;
        case 3: goto L_80097968; break;
        case 4: goto L_8009767C; break;
        default: switch_error(__func__, 0x80096C64, 0x800EB2EC);
    }
    // 0x80096C68: nop

L_80096C6C:
    // 0x80096C6C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80096C70: lh          $v0, -0x18C0($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X18C0);
    // 0x80096C74: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x80096C78: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80096C7C: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096C80: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80096C84: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80096C88: addiu       $t8, $t8, 0x7A60
    ctx->r24 = ADD32(ctx->r24, 0X7A60);
    // 0x80096C8C: mflo        $t9
    ctx->r25 = lo;
    // 0x80096C90: nop

    // 0x80096C94: nop

    // 0x80096C98: multu       $t9, $a1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096C9C: mflo        $t6
    ctx->r14 = lo;
    // 0x80096CA0: addu        $t7, $a0, $t6
    ctx->r15 = ADD32(ctx->r4, ctx->r14);
    // 0x80096CA4: addiu       $t6, $t7, 0x3C
    ctx->r14 = ADD32(ctx->r15, 0X3C);
L_80096CA8:
    // 0x80096CA8: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x80096CAC: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x80096CB0: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80096CB4: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80096CB8: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x80096CBC: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80096CC0: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x80096CC4: bne         $t7, $t6, L_80096CA8
    if (ctx->r15 != ctx->r14) {
        // 0x80096CC8: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80096CA8;
    }
    // 0x80096CC8: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80096CCC: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x80096CD0: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x80096CD4: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80096CD8: lw          $t6, 0x4($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X4);
    // 0x80096CDC: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x80096CE0: addiu       $t7, $t7, 0x7AA4
    ctx->r15 = ADD32(ctx->r15, 0X7AA4);
    // 0x80096CE4: sw          $t6, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r14;
    // 0x80096CE8: lh          $t1, -0x18BC($t1)
    ctx->r9 = MEM_H(ctx->r9, -0X18BC);
    // 0x80096CEC: multu       $t1, $t3
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096CF0: mflo        $t9
    ctx->r25 = lo;
    // 0x80096CF4: nop

    // 0x80096CF8: nop

    // 0x80096CFC: multu       $t9, $a1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096D00: mflo        $t6
    ctx->r14 = lo;
    // 0x80096D04: addu        $v1, $a0, $t6
    ctx->r3 = ADD32(ctx->r4, ctx->r14);
    // 0x80096D08: or          $t9, $v1, $zero
    ctx->r25 = ctx->r3 | 0;
    // 0x80096D0C: addiu       $t6, $v1, 0x3C
    ctx->r14 = ADD32(ctx->r3, 0X3C);
L_80096D10:
    // 0x80096D10: lw          $at, 0x44($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X44);
    // 0x80096D14: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80096D18: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x80096D1C: sw          $at, -0xC($t7)
    MEM_W(-0XC, ctx->r15) = ctx->r1;
    // 0x80096D20: lw          $at, 0x3C($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X3C);
    // 0x80096D24: sw          $at, -0x8($t7)
    MEM_W(-0X8, ctx->r15) = ctx->r1;
    // 0x80096D28: lw          $at, 0x40($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X40);
    // 0x80096D2C: bne         $t9, $t6, L_80096D10
    if (ctx->r25 != ctx->r14) {
        // 0x80096D30: sw          $at, -0x4($t7)
        MEM_W(-0X4, ctx->r15) = ctx->r1;
            goto L_80096D10;
    }
    // 0x80096D30: sw          $at, -0x4($t7)
    MEM_W(-0X4, ctx->r15) = ctx->r1;
    // 0x80096D34: lw          $at, 0x44($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X44);
    // 0x80096D38: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80096D3C: addiu       $t8, $t8, 0x7AE8
    ctx->r24 = ADD32(ctx->r24, 0X7AE8);
    // 0x80096D40: sw          $at, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r1;
    // 0x80096D44: lw          $t6, 0x48($t9)
    ctx->r14 = MEM_W(ctx->r25, 0X48);
    // 0x80096D48: or          $t9, $v1, $zero
    ctx->r25 = ctx->r3 | 0;
    // 0x80096D4C: sw          $t6, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->r14;
    // 0x80096D50: addiu       $t7, $v1, 0x3C
    ctx->r15 = ADD32(ctx->r3, 0X3C);
L_80096D54:
    // 0x80096D54: lw          $at, 0x88($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X88);
    // 0x80096D58: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80096D5C: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80096D60: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80096D64: lw          $at, 0x80($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X80);
    // 0x80096D68: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80096D6C: lw          $at, 0x84($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X84);
    // 0x80096D70: bne         $t9, $t7, L_80096D54
    if (ctx->r25 != ctx->r15) {
        // 0x80096D74: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80096D54;
    }
    // 0x80096D74: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80096D78: lw          $at, 0x88($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X88);
    // 0x80096D7C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x80096D80: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80096D84: lw          $t7, 0x8C($t9)
    ctx->r15 = MEM_W(ctx->r25, 0X8C);
    // 0x80096D88: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x80096D8C: addiu       $t9, $t9, 0x7B2C
    ctx->r25 = ADD32(ctx->r25, 0X7B2C);
    // 0x80096D90: sw          $t7, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r15;
    // 0x80096D94: lh          $t4, -0x18B8($t4)
    ctx->r12 = MEM_H(ctx->r12, -0X18B8);
    // 0x80096D98: multu       $t4, $t3
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096D9C: mflo        $t6
    ctx->r14 = lo;
    // 0x80096DA0: nop

    // 0x80096DA4: nop

    // 0x80096DA8: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096DAC: mflo        $t7
    ctx->r15 = lo;
    // 0x80096DB0: addu        $a3, $a0, $t7
    ctx->r7 = ADD32(ctx->r4, ctx->r15);
    // 0x80096DB4: or          $t6, $a3, $zero
    ctx->r14 = ctx->r7 | 0;
    // 0x80096DB8: addiu       $t7, $a3, 0x3C
    ctx->r15 = ADD32(ctx->r7, 0X3C);
L_80096DBC:
    // 0x80096DBC: lw          $at, 0x44($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X44);
    // 0x80096DC0: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80096DC4: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80096DC8: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x80096DCC: lw          $at, 0x3C($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X3C);
    // 0x80096DD0: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x80096DD4: lw          $at, 0x40($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X40);
    // 0x80096DD8: bne         $t6, $t7, L_80096DBC
    if (ctx->r14 != ctx->r15) {
        // 0x80096DDC: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80096DBC;
    }
    // 0x80096DDC: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x80096DE0: lw          $at, 0x44($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X44);
    // 0x80096DE4: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80096DE8: addiu       $t8, $t8, 0x7B70
    ctx->r24 = ADD32(ctx->r24, 0X7B70);
    // 0x80096DEC: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x80096DF0: lw          $t7, 0x48($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X48);
    // 0x80096DF4: or          $t6, $a3, $zero
    ctx->r14 = ctx->r7 | 0;
    // 0x80096DF8: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x80096DFC: addiu       $t9, $a3, 0x3C
    ctx->r25 = ADD32(ctx->r7, 0X3C);
L_80096E00:
    // 0x80096E00: lw          $at, 0x88($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X88);
    // 0x80096E04: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80096E08: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80096E0C: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80096E10: lw          $at, 0x80($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X80);
    // 0x80096E14: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80096E18: lw          $at, 0x84($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X84);
    // 0x80096E1C: bne         $t6, $t9, L_80096E00
    if (ctx->r14 != ctx->r25) {
        // 0x80096E20: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80096E00;
    }
    // 0x80096E20: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80096E24: lw          $at, 0x88($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X88);
    // 0x80096E28: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x80096E2C: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x80096E30: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80096E34: lw          $t9, 0x8C($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X8C);
    // 0x80096E38: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x80096E3C: addiu       $t6, $t6, 0x7BB4
    ctx->r14 = ADD32(ctx->r14, 0X7BB4);
    // 0x80096E40: sw          $t9, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r25;
    // 0x80096E44: lh          $t5, -0x18B4($t5)
    ctx->r13 = MEM_H(ctx->r13, -0X18B4);
    // 0x80096E48: multu       $t5, $t3
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096E4C: mflo        $t7
    ctx->r15 = lo;
    // 0x80096E50: nop

    // 0x80096E54: nop

    // 0x80096E58: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80096E5C: mflo        $t9
    ctx->r25 = lo;
    // 0x80096E60: addu        $t0, $a0, $t9
    ctx->r8 = ADD32(ctx->r4, ctx->r25);
    // 0x80096E64: or          $t7, $t0, $zero
    ctx->r15 = ctx->r8 | 0;
    // 0x80096E68: addiu       $t9, $t0, 0x3C
    ctx->r25 = ADD32(ctx->r8, 0X3C);
L_80096E6C:
    // 0x80096E6C: lw          $at, 0x44($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X44);
    // 0x80096E70: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x80096E74: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80096E78: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x80096E7C: lw          $at, 0x3C($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X3C);
    // 0x80096E80: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x80096E84: lw          $at, 0x40($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X40);
    // 0x80096E88: bne         $t7, $t9, L_80096E6C
    if (ctx->r15 != ctx->r25) {
        // 0x80096E8C: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_80096E6C;
    }
    // 0x80096E8C: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x80096E90: lw          $at, 0x44($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X44);
    // 0x80096E94: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x80096E98: addiu       $t8, $t8, 0x7BF8
    ctx->r24 = ADD32(ctx->r24, 0X7BF8);
    // 0x80096E9C: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x80096EA0: lw          $t9, 0x48($t7)
    ctx->r25 = MEM_W(ctx->r15, 0X48);
    // 0x80096EA4: or          $t7, $t0, $zero
    ctx->r15 = ctx->r8 | 0;
    // 0x80096EA8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x80096EAC: sw          $t9, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r25;
    // 0x80096EB0: addiu       $t6, $t0, 0x3C
    ctx->r14 = ADD32(ctx->r8, 0X3C);
L_80096EB4:
    // 0x80096EB4: lw          $at, 0x88($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X88);
    // 0x80096EB8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x80096EBC: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80096EC0: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80096EC4: lw          $at, 0x80($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X80);
    // 0x80096EC8: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80096ECC: lw          $at, 0x84($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X84);
    // 0x80096ED0: bne         $t7, $t6, L_80096EB4
    if (ctx->r15 != ctx->r14) {
        // 0x80096ED4: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80096EB4;
    }
    // 0x80096ED4: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80096ED8: lw          $at, 0x88($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X88);
    // 0x80096EDC: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x80096EE0: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80096EE4: lw          $t6, 0x8C($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X8C);
    // 0x80096EE8: bne         $t2, $v0, L_80096EFC
    if (ctx->r10 != ctx->r2) {
        // 0x80096EEC: sw          $t6, 0x4($t8)
        MEM_W(0X4, ctx->r24) = ctx->r14;
            goto L_80096EFC;
    }
    // 0x80096EEC: sw          $t6, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r14;
    // 0x80096EF0: sh          $t9, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r25;
    // 0x80096EF4: b           L_80096F08
    // 0x80096EF8: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
        goto L_80096F08;
    // 0x80096EF8: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
L_80096EFC:
    // 0x80096EFC: bne         $a3, $v0, L_80096F08
    if (ctx->r7 != ctx->r2) {
        // 0x80096F00: nop
    
            goto L_80096F08;
    }
    // 0x80096F00: nop

    // 0x80096F04: sh          $t2, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r10;
L_80096F08:
    // 0x80096F08: bne         $t2, $t1, L_80096F1C
    if (ctx->r10 != ctx->r9) {
        // 0x80096F0C: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_80096F1C;
    }
    // 0x80096F0C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80096F10: sh          $v0, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r2;
    // 0x80096F14: b           L_80096F2C
    // 0x80096F18: sh          $v0, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r2;
        goto L_80096F2C;
    // 0x80096F18: sh          $v0, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r2;
L_80096F1C:
    // 0x80096F1C: bne         $a3, $t1, L_80096F2C
    if (ctx->r7 != ctx->r9) {
        // 0x80096F20: nop
    
            goto L_80096F2C;
    }
    // 0x80096F20: nop

    // 0x80096F24: sh          $t2, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r10;
    // 0x80096F28: sh          $t2, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r10;
L_80096F2C:
    // 0x80096F2C: bne         $t2, $t4, L_80096F40
    if (ctx->r10 != ctx->r12) {
        // 0x80096F30: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_80096F40;
    }
    // 0x80096F30: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x80096F34: sh          $v1, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r3;
    // 0x80096F38: b           L_80096F50
    // 0x80096F3C: sh          $v1, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r3;
        goto L_80096F50;
    // 0x80096F3C: sh          $v1, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r3;
L_80096F40:
    // 0x80096F40: bne         $a3, $t4, L_80096F50
    if (ctx->r7 != ctx->r12) {
        // 0x80096F44: nop
    
            goto L_80096F50;
    }
    // 0x80096F44: nop

    // 0x80096F48: sh          $t2, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r10;
    // 0x80096F4C: sh          $t2, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r10;
L_80096F50:
    // 0x80096F50: bne         $t2, $t5, L_80096F64
    if (ctx->r10 != ctx->r13) {
        // 0x80096F54: andi        $v0, $s0, 0x3
        ctx->r2 = ctx->r16 & 0X3;
            goto L_80096F64;
    }
    // 0x80096F54: andi        $v0, $s0, 0x3
    ctx->r2 = ctx->r16 & 0X3;
    // 0x80096F58: sh          $t8, 0x4C($sp)
    MEM_H(0X4C, ctx->r29) = ctx->r24;
    // 0x80096F5C: b           L_80096F74
    // 0x80096F60: sh          $t8, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r24;
        goto L_80096F74;
    // 0x80096F60: sh          $t8, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r24;
L_80096F64:
    // 0x80096F64: bne         $a3, $t5, L_80096F74
    if (ctx->r7 != ctx->r13) {
        // 0x80096F68: nop
    
            goto L_80096F74;
    }
    // 0x80096F68: nop

    // 0x80096F6C: sh          $t2, 0x4C($sp)
    MEM_H(0X4C, ctx->r29) = ctx->r10;
    // 0x80096F70: sh          $t2, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r10;
L_80096F74:
    // 0x80096F74: blez        $s0, L_80097C68
    if (SIGNED(ctx->r16) <= 0) {
        // 0x80096F78: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_80097C68;
    }
    // 0x80096F78: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80096F7C: beq         $v0, $zero, L_80096FEC
    if (ctx->r2 == 0) {
        // 0x80096F80: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_80096FEC;
    }
    // 0x80096F80: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x80096F84: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x80096F88: addiu       $t8, $t8, -0x18C0
    ctx->r24 = ADD32(ctx->r24, -0X18C0);
    // 0x80096F8C: sll         $t7, $zero, 2
    ctx->r15 = S32(0 << 2);
    // 0x80096F90: addu        $t1, $t7, $t8
    ctx->r9 = ADD32(ctx->r15, ctx->r24);
L_80096F94:
    // 0x80096F94: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80096F98: bne         $t2, $v0, L_80096FBC
    if (ctx->r10 != ctx->r2) {
        // 0x80096F9C: nop
    
            goto L_80096FBC;
    }
    // 0x80096F9C: nop

    // 0x80096FA0: bne         $t0, $zero, L_80096FB0
    if (ctx->r8 != 0) {
        // 0x80096FA4: addu        $t9, $t0, $t0
        ctx->r25 = ADD32(ctx->r8, ctx->r8);
            goto L_80096FB0;
    }
    // 0x80096FA4: addu        $t9, $t0, $t0
    ctx->r25 = ADD32(ctx->r8, ctx->r8);
    // 0x80096FA8: b           L_80096FDC
    // 0x80096FAC: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80096FDC;
    // 0x80096FAC: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_80096FB0:
    // 0x80096FB0: addiu       $t6, $t9, -0x1
    ctx->r14 = ADD32(ctx->r25, -0X1);
    // 0x80096FB4: b           L_80096FDC
    // 0x80096FB8: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
        goto L_80096FDC;
    // 0x80096FB8: sw          $t6, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r14;
L_80096FBC:
    // 0x80096FBC: bnel        $a3, $v0, L_80096FE0
    if (ctx->r7 != ctx->r2) {
        // 0x80096FC0: addiu       $t0, $t0, 0x1
        ctx->r8 = ADD32(ctx->r8, 0X1);
            goto L_80096FE0;
    }
    goto skip_1;
    // 0x80096FC0: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    skip_1:
    // 0x80096FC4: bne         $t0, $zero, L_80096FD4
    if (ctx->r8 != 0) {
        // 0x80096FC8: addu        $t7, $t0, $t0
        ctx->r15 = ADD32(ctx->r8, ctx->r8);
            goto L_80096FD4;
    }
    // 0x80096FC8: addu        $t7, $t0, $t0
    ctx->r15 = ADD32(ctx->r8, ctx->r8);
    // 0x80096FCC: b           L_80096FDC
    // 0x80096FD0: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
        goto L_80096FDC;
    // 0x80096FD0: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80096FD4:
    // 0x80096FD4: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x80096FD8: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_80096FDC:
    // 0x80096FDC: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
L_80096FE0:
    // 0x80096FE0: bne         $v1, $t0, L_80096F94
    if (ctx->r3 != ctx->r8) {
        // 0x80096FE4: addiu       $t1, $t1, 0x4
        ctx->r9 = ADD32(ctx->r9, 0X4);
            goto L_80096F94;
    }
    // 0x80096FE4: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x80096FE8: beq         $t0, $s0, L_80097C68
    if (ctx->r8 == ctx->r16) {
        // 0x80096FEC: lui         $t6, 0x801D
        ctx->r14 = S32(0X801D << 16);
            goto L_80097C68;
    }
L_80096FEC:
    // 0x80096FEC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80096FF0: addiu       $t6, $t6, -0x18C0
    ctx->r14 = ADD32(ctx->r14, -0X18C0);
    // 0x80096FF4: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x80096FF8: addu        $t1, $t9, $t6
    ctx->r9 = ADD32(ctx->r25, ctx->r14);
    // 0x80096FFC: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x80097000: addiu       $a0, $zero, -0x3
    ctx->r4 = ADD32(0, -0X3);
    // 0x80097004: addiu       $v1, $zero, -0x2
    ctx->r3 = ADD32(0, -0X2);
L_80097008:
    // 0x80097008: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x8009700C: bne         $t2, $v0, L_80097030
    if (ctx->r10 != ctx->r2) {
        // 0x80097010: nop
    
            goto L_80097030;
    }
    // 0x80097010: nop

    // 0x80097014: bne         $t0, $zero, L_80097024
    if (ctx->r8 != 0) {
        // 0x80097018: addu        $t7, $t0, $t0
        ctx->r15 = ADD32(ctx->r8, ctx->r8);
            goto L_80097024;
    }
    // 0x80097018: addu        $t7, $t0, $t0
    ctx->r15 = ADD32(ctx->r8, ctx->r8);
    // 0x8009701C: b           L_80097050
    // 0x80097020: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80097050;
    // 0x80097020: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_80097024:
    // 0x80097024: addiu       $t8, $t7, -0x1
    ctx->r24 = ADD32(ctx->r15, -0X1);
    // 0x80097028: b           L_80097050
    // 0x8009702C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
        goto L_80097050;
    // 0x8009702C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
L_80097030:
    // 0x80097030: bnel        $a3, $v0, L_80097054
    if (ctx->r7 != ctx->r2) {
        // 0x80097034: lh          $v0, 0x4($t1)
        ctx->r2 = MEM_H(ctx->r9, 0X4);
            goto L_80097054;
    }
    goto skip_2;
    // 0x80097034: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
    skip_2:
    // 0x80097038: bne         $t0, $zero, L_80097048
    if (ctx->r8 != 0) {
        // 0x8009703C: addu        $t9, $t0, $t0
        ctx->r25 = ADD32(ctx->r8, ctx->r8);
            goto L_80097048;
    }
    // 0x8009703C: addu        $t9, $t0, $t0
    ctx->r25 = ADD32(ctx->r8, ctx->r8);
    // 0x80097040: b           L_80097050
    // 0x80097044: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
        goto L_80097050;
    // 0x80097044: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80097048:
    // 0x80097048: addiu       $t6, $t9, -0x1
    ctx->r14 = ADD32(ctx->r25, -0X1);
    // 0x8009704C: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097050:
    // 0x80097050: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
L_80097054:
    // 0x80097054: bne         $t2, $v0, L_8009707C
    if (ctx->r10 != ctx->r2) {
        // 0x80097058: nop
    
            goto L_8009707C;
    }
    // 0x80097058: nop

    // 0x8009705C: bne         $t0, $a1, L_80097070
    if (ctx->r8 != ctx->r5) {
        // 0x80097060: addu        $t8, $t0, $t0
        ctx->r24 = ADD32(ctx->r8, ctx->r8);
            goto L_80097070;
    }
    // 0x80097060: addu        $t8, $t0, $t0
    ctx->r24 = ADD32(ctx->r8, ctx->r8);
    // 0x80097064: addiu       $t7, $t0, 0x1
    ctx->r15 = ADD32(ctx->r8, 0X1);
    // 0x80097068: b           L_800970A0
    // 0x8009706C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_800970A0;
    // 0x8009706C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_80097070:
    // 0x80097070: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x80097074: b           L_800970A0
    // 0x80097078: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_800970A0;
    // 0x80097078: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_8009707C:
    // 0x8009707C: bnel        $a3, $v0, L_800970A4
    if (ctx->r7 != ctx->r2) {
        // 0x80097080: lh          $v0, 0x8($t1)
        ctx->r2 = MEM_H(ctx->r9, 0X8);
            goto L_800970A4;
    }
    goto skip_3;
    // 0x80097080: lh          $v0, 0x8($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X8);
    skip_3:
    // 0x80097084: bne         $t0, $a1, L_80097098
    if (ctx->r8 != ctx->r5) {
        // 0x80097088: addu        $t7, $t0, $t0
        ctx->r15 = ADD32(ctx->r8, ctx->r8);
            goto L_80097098;
    }
    // 0x80097088: addu        $t7, $t0, $t0
    ctx->r15 = ADD32(ctx->r8, ctx->r8);
    // 0x8009708C: addiu       $t6, $t0, 0x1
    ctx->r14 = ADD32(ctx->r8, 0X1);
    // 0x80097090: b           L_800970A0
    // 0x80097094: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
        goto L_800970A0;
    // 0x80097094: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097098:
    // 0x80097098: addiu       $t8, $t7, 0x1
    ctx->r24 = ADD32(ctx->r15, 0X1);
    // 0x8009709C: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_800970A0:
    // 0x800970A0: lh          $v0, 0x8($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X8);
L_800970A4:
    // 0x800970A4: bne         $t2, $v0, L_800970CC
    if (ctx->r10 != ctx->r2) {
        // 0x800970A8: nop
    
            goto L_800970CC;
    }
    // 0x800970A8: nop

    // 0x800970AC: bne         $t0, $v1, L_800970C0
    if (ctx->r8 != ctx->r3) {
        // 0x800970B0: addu        $t6, $t0, $t0
        ctx->r14 = ADD32(ctx->r8, ctx->r8);
            goto L_800970C0;
    }
    // 0x800970B0: addu        $t6, $t0, $t0
    ctx->r14 = ADD32(ctx->r8, ctx->r8);
    // 0x800970B4: addiu       $t9, $t0, 0x2
    ctx->r25 = ADD32(ctx->r8, 0X2);
    // 0x800970B8: b           L_800970F0
    // 0x800970BC: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_800970F0;
    // 0x800970BC: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_800970C0:
    // 0x800970C0: addiu       $t7, $t6, 0x3
    ctx->r15 = ADD32(ctx->r14, 0X3);
    // 0x800970C4: b           L_800970F0
    // 0x800970C8: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_800970F0;
    // 0x800970C8: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_800970CC:
    // 0x800970CC: bnel        $a3, $v0, L_800970F4
    if (ctx->r7 != ctx->r2) {
        // 0x800970D0: lh          $v0, 0xC($t1)
        ctx->r2 = MEM_H(ctx->r9, 0XC);
            goto L_800970F4;
    }
    goto skip_4;
    // 0x800970D0: lh          $v0, 0xC($t1)
    ctx->r2 = MEM_H(ctx->r9, 0XC);
    skip_4:
    // 0x800970D4: bne         $t0, $v1, L_800970E8
    if (ctx->r8 != ctx->r3) {
        // 0x800970D8: addu        $t9, $t0, $t0
        ctx->r25 = ADD32(ctx->r8, ctx->r8);
            goto L_800970E8;
    }
    // 0x800970D8: addu        $t9, $t0, $t0
    ctx->r25 = ADD32(ctx->r8, ctx->r8);
    // 0x800970DC: addiu       $t8, $t0, 0x2
    ctx->r24 = ADD32(ctx->r8, 0X2);
    // 0x800970E0: b           L_800970F0
    // 0x800970E4: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
        goto L_800970F0;
    // 0x800970E4: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_800970E8:
    // 0x800970E8: addiu       $t6, $t9, 0x3
    ctx->r14 = ADD32(ctx->r25, 0X3);
    // 0x800970EC: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_800970F0:
    // 0x800970F0: lh          $v0, 0xC($t1)
    ctx->r2 = MEM_H(ctx->r9, 0XC);
L_800970F4:
    // 0x800970F4: bne         $t2, $v0, L_8009711C
    if (ctx->r10 != ctx->r2) {
        // 0x800970F8: nop
    
            goto L_8009711C;
    }
    // 0x800970F8: nop

    // 0x800970FC: bne         $t0, $a0, L_80097110
    if (ctx->r8 != ctx->r4) {
        // 0x80097100: addu        $t8, $t0, $t0
        ctx->r24 = ADD32(ctx->r8, ctx->r8);
            goto L_80097110;
    }
    // 0x80097100: addu        $t8, $t0, $t0
    ctx->r24 = ADD32(ctx->r8, ctx->r8);
    // 0x80097104: addiu       $t7, $t0, 0x3
    ctx->r15 = ADD32(ctx->r8, 0X3);
    // 0x80097108: b           L_80097140
    // 0x8009710C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097140;
    // 0x8009710C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_80097110:
    // 0x80097110: addiu       $t9, $t8, 0x5
    ctx->r25 = ADD32(ctx->r24, 0X5);
    // 0x80097114: b           L_80097140
    // 0x80097118: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_80097140;
    // 0x80097118: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_8009711C:
    // 0x8009711C: bnel        $a3, $v0, L_80097144
    if (ctx->r7 != ctx->r2) {
        // 0x80097120: addiu       $t0, $t0, 0x4
        ctx->r8 = ADD32(ctx->r8, 0X4);
            goto L_80097144;
    }
    goto skip_5;
    // 0x80097120: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    skip_5:
    // 0x80097124: bne         $t0, $a0, L_80097138
    if (ctx->r8 != ctx->r4) {
        // 0x80097128: addu        $t7, $t0, $t0
        ctx->r15 = ADD32(ctx->r8, ctx->r8);
            goto L_80097138;
    }
    // 0x80097128: addu        $t7, $t0, $t0
    ctx->r15 = ADD32(ctx->r8, ctx->r8);
    // 0x8009712C: addiu       $t6, $t0, 0x3
    ctx->r14 = ADD32(ctx->r8, 0X3);
    // 0x80097130: b           L_80097140
    // 0x80097134: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
        goto L_80097140;
    // 0x80097134: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097138:
    // 0x80097138: addiu       $t8, $t7, 0x5
    ctx->r24 = ADD32(ctx->r15, 0X5);
    // 0x8009713C: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_80097140:
    // 0x80097140: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
L_80097144:
    // 0x80097144: bne         $t0, $s0, L_80097008
    if (ctx->r8 != ctx->r16) {
        // 0x80097148: addiu       $t1, $t1, 0x10
        ctx->r9 = ADD32(ctx->r9, 0X10);
            goto L_80097008;
    }
    // 0x80097148: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
    // 0x8009714C: b           L_80097C6C
    // 0x80097150: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
        goto L_80097C6C;
    // 0x80097150: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
L_80097154:
    // 0x80097154: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80097158: addiu       $v1, $v1, -0x18C0
    ctx->r3 = ADD32(ctx->r3, -0X18C0);
    // 0x8009715C: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x80097160: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x80097164: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80097168: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009716C: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80097170: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x80097174: addiu       $t9, $t9, 0x7A60
    ctx->r25 = ADD32(ctx->r25, 0X7A60);
    // 0x80097178: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x8009717C: mflo        $t6
    ctx->r14 = lo;
    // 0x80097180: nop

    // 0x80097184: nop

    // 0x80097188: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009718C: mflo        $t7
    ctx->r15 = lo;
    // 0x80097190: addu        $t8, $a0, $t7
    ctx->r24 = ADD32(ctx->r4, ctx->r15);
    // 0x80097194: addiu       $t7, $t8, 0x3C
    ctx->r15 = ADD32(ctx->r24, 0X3C);
L_80097198:
    // 0x80097198: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x8009719C: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x800971A0: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x800971A4: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x800971A8: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x800971AC: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x800971B0: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x800971B4: bne         $t8, $t7, L_80097198
    if (ctx->r24 != ctx->r15) {
        // 0x800971B8: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80097198;
    }
    // 0x800971B8: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x800971BC: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x800971C0: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x800971C4: addiu       $t6, $t6, 0x7AA4
    ctx->r14 = ADD32(ctx->r14, 0X7AA4);
    // 0x800971C8: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x800971CC: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x800971D0: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x800971D4: lh          $t1, 0x4($v1)
    ctx->r9 = MEM_H(ctx->r3, 0X4);
    // 0x800971D8: multu       $t1, $t3
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800971DC: mflo        $t7
    ctx->r15 = lo;
    // 0x800971E0: nop

    // 0x800971E4: nop

    // 0x800971E8: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800971EC: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800971F0: mflo        $t8
    ctx->r24 = lo;
    // 0x800971F4: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x800971F8: addiu       $t8, $t9, 0x3C
    ctx->r24 = ADD32(ctx->r25, 0X3C);
L_800971FC:
    // 0x800971FC: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x80097200: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80097204: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80097208: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x8009720C: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x80097210: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x80097214: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x80097218: bne         $t9, $t8, L_800971FC
    if (ctx->r25 != ctx->r24) {
        // 0x8009721C: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_800971FC;
    }
    // 0x8009721C: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x80097220: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x80097224: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x80097228: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x8009722C: bne         $t2, $v0, L_80097240
    if (ctx->r10 != ctx->r2) {
        // 0x80097230: sw          $t8, 0x4($t6)
        MEM_W(0X4, ctx->r14) = ctx->r24;
            goto L_80097240;
    }
    // 0x80097230: sw          $t8, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r24;
    // 0x80097234: sh          $t7, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r15;
    // 0x80097238: b           L_8009724C
    // 0x8009723C: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
        goto L_8009724C;
    // 0x8009723C: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
L_80097240:
    // 0x80097240: bne         $a3, $v0, L_8009724C
    if (ctx->r7 != ctx->r2) {
        // 0x80097244: nop
    
            goto L_8009724C;
    }
    // 0x80097244: nop

    // 0x80097248: sh          $t2, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r10;
L_8009724C:
    // 0x8009724C: bne         $t2, $t1, L_8009725C
    if (ctx->r10 != ctx->r9) {
        // 0x80097250: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_8009725C;
    }
    // 0x80097250: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x80097254: b           L_80097268
    // 0x80097258: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
        goto L_80097268;
    // 0x80097258: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
L_8009725C:
    // 0x8009725C: bne         $a3, $t1, L_80097268
    if (ctx->r7 != ctx->r9) {
        // 0x80097260: nop
    
            goto L_80097268;
    }
    // 0x80097260: nop

    // 0x80097264: sh          $t2, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r10;
L_80097268:
    // 0x80097268: blez        $s0, L_80097C68
    if (SIGNED(ctx->r16) <= 0) {
        // 0x8009726C: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_80097C68;
    }
    // 0x8009726C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80097270: andi        $v0, $s0, 0x3
    ctx->r2 = ctx->r16 & 0X3;
    // 0x80097274: beq         $v0, $zero, L_800972BC
    if (ctx->r2 == 0) {
        // 0x80097278: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800972BC;
    }
    // 0x80097278: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x8009727C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80097280: addiu       $t6, $t6, -0x18C0
    ctx->r14 = ADD32(ctx->r14, -0X18C0);
    // 0x80097284: sll         $t9, $zero, 2
    ctx->r25 = S32(0 << 2);
    // 0x80097288: addu        $t1, $t9, $t6
    ctx->r9 = ADD32(ctx->r25, ctx->r14);
L_8009728C:
    // 0x8009728C: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80097290: bne         $t2, $v0, L_800972A0
    if (ctx->r10 != ctx->r2) {
        // 0x80097294: nop
    
            goto L_800972A0;
    }
    // 0x80097294: nop

    // 0x80097298: b           L_800972AC
    // 0x8009729C: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_800972AC;
    // 0x8009729C: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_800972A0:
    // 0x800972A0: bnel        $a3, $v0, L_800972B0
    if (ctx->r7 != ctx->r2) {
        // 0x800972A4: addiu       $t0, $t0, 0x1
        ctx->r8 = ADD32(ctx->r8, 0X1);
            goto L_800972B0;
    }
    goto skip_6;
    // 0x800972A4: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    skip_6:
    // 0x800972A8: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_800972AC:
    // 0x800972AC: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
L_800972B0:
    // 0x800972B0: bne         $v1, $t0, L_8009728C
    if (ctx->r3 != ctx->r8) {
        // 0x800972B4: addiu       $t1, $t1, 0x4
        ctx->r9 = ADD32(ctx->r9, 0X4);
            goto L_8009728C;
    }
    // 0x800972B4: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x800972B8: beq         $t0, $s0, L_80097C68
    if (ctx->r8 == ctx->r16) {
        // 0x800972BC: lui         $t8, 0x801D
        ctx->r24 = S32(0X801D << 16);
            goto L_80097C68;
    }
L_800972BC:
    // 0x800972BC: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800972C0: addiu       $t8, $t8, -0x18C0
    ctx->r24 = ADD32(ctx->r24, -0X18C0);
    // 0x800972C4: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x800972C8: addu        $t1, $t7, $t8
    ctx->r9 = ADD32(ctx->r15, ctx->r24);
L_800972CC:
    // 0x800972CC: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x800972D0: addiu       $t9, $t0, 0x1
    ctx->r25 = ADD32(ctx->r8, 0X1);
    // 0x800972D4: addiu       $t7, $t0, 0x2
    ctx->r15 = ADD32(ctx->r8, 0X2);
    // 0x800972D8: bne         $t2, $v0, L_800972E8
    if (ctx->r10 != ctx->r2) {
        // 0x800972DC: nop
    
            goto L_800972E8;
    }
    // 0x800972DC: nop

    // 0x800972E0: b           L_800972F4
    // 0x800972E4: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_800972F4;
    // 0x800972E4: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_800972E8:
    // 0x800972E8: bnel        $a3, $v0, L_800972F8
    if (ctx->r7 != ctx->r2) {
        // 0x800972EC: lh          $v0, 0x4($t1)
        ctx->r2 = MEM_H(ctx->r9, 0X4);
            goto L_800972F8;
    }
    goto skip_7;
    // 0x800972EC: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
    skip_7:
    // 0x800972F0: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_800972F4:
    // 0x800972F4: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
L_800972F8:
    // 0x800972F8: bne         $t2, $v0, L_80097308
    if (ctx->r10 != ctx->r2) {
        // 0x800972FC: nop
    
            goto L_80097308;
    }
    // 0x800972FC: nop

    // 0x80097300: b           L_80097314
    // 0x80097304: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_80097314;
    // 0x80097304: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_80097308:
    // 0x80097308: bne         $a3, $v0, L_80097314
    if (ctx->r7 != ctx->r2) {
        // 0x8009730C: addiu       $t6, $t0, 0x1
        ctx->r14 = ADD32(ctx->r8, 0X1);
            goto L_80097314;
    }
    // 0x8009730C: addiu       $t6, $t0, 0x1
    ctx->r14 = ADD32(ctx->r8, 0X1);
    // 0x80097310: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097314:
    // 0x80097314: lh          $v0, 0x8($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X8);
    // 0x80097318: addiu       $t9, $t0, 0x3
    ctx->r25 = ADD32(ctx->r8, 0X3);
    // 0x8009731C: bne         $t2, $v0, L_8009732C
    if (ctx->r10 != ctx->r2) {
        // 0x80097320: nop
    
            goto L_8009732C;
    }
    // 0x80097320: nop

    // 0x80097324: b           L_80097338
    // 0x80097328: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097338;
    // 0x80097328: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_8009732C:
    // 0x8009732C: bne         $a3, $v0, L_80097338
    if (ctx->r7 != ctx->r2) {
        // 0x80097330: addiu       $t8, $t0, 0x2
        ctx->r24 = ADD32(ctx->r8, 0X2);
            goto L_80097338;
    }
    // 0x80097330: addiu       $t8, $t0, 0x2
    ctx->r24 = ADD32(ctx->r8, 0X2);
    // 0x80097334: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_80097338:
    // 0x80097338: lh          $v0, 0xC($t1)
    ctx->r2 = MEM_H(ctx->r9, 0XC);
    // 0x8009733C: bne         $t2, $v0, L_8009734C
    if (ctx->r10 != ctx->r2) {
        // 0x80097340: nop
    
            goto L_8009734C;
    }
    // 0x80097340: nop

    // 0x80097344: b           L_80097358
    // 0x80097348: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_80097358;
    // 0x80097348: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_8009734C:
    // 0x8009734C: bne         $a3, $v0, L_80097358
    if (ctx->r7 != ctx->r2) {
        // 0x80097350: addiu       $t6, $t0, 0x3
        ctx->r14 = ADD32(ctx->r8, 0X3);
            goto L_80097358;
    }
    // 0x80097350: addiu       $t6, $t0, 0x3
    ctx->r14 = ADD32(ctx->r8, 0X3);
    // 0x80097354: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097358:
    // 0x80097358: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x8009735C: bne         $t0, $s0, L_800972CC
    if (ctx->r8 != ctx->r16) {
        // 0x80097360: addiu       $t1, $t1, 0x10
        ctx->r9 = ADD32(ctx->r9, 0X10);
            goto L_800972CC;
    }
    // 0x80097360: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
    // 0x80097364: b           L_80097C6C
    // 0x80097368: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
        goto L_80097C6C;
    // 0x80097368: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
L_8009736C:
    // 0x8009736C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80097370: addiu       $v1, $v1, -0x18C0
    ctx->r3 = ADD32(ctx->r3, -0X18C0);
    // 0x80097374: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x80097378: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x8009737C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80097380: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097384: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80097388: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x8009738C: addiu       $t7, $t7, 0x7A60
    ctx->r15 = ADD32(ctx->r15, 0X7A60);
    // 0x80097390: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x80097394: mflo        $t8
    ctx->r24 = lo;
    // 0x80097398: nop

    // 0x8009739C: nop

    // 0x800973A0: multu       $t8, $a1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800973A4: mflo        $t9
    ctx->r25 = lo;
    // 0x800973A8: addu        $t6, $a0, $t9
    ctx->r14 = ADD32(ctx->r4, ctx->r25);
    // 0x800973AC: addiu       $t9, $t6, 0x3C
    ctx->r25 = ADD32(ctx->r14, 0X3C);
L_800973B0:
    // 0x800973B0: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x800973B4: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x800973B8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x800973BC: sw          $at, -0xC($t7)
    MEM_W(-0XC, ctx->r15) = ctx->r1;
    // 0x800973C0: lw          $at, -0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X8);
    // 0x800973C4: sw          $at, -0x8($t7)
    MEM_W(-0X8, ctx->r15) = ctx->r1;
    // 0x800973C8: lw          $at, -0x4($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X4);
    // 0x800973CC: bne         $t6, $t9, L_800973B0
    if (ctx->r14 != ctx->r25) {
        // 0x800973D0: sw          $at, -0x4($t7)
        MEM_W(-0X4, ctx->r15) = ctx->r1;
            goto L_800973B0;
    }
    // 0x800973D0: sw          $at, -0x4($t7)
    MEM_W(-0X4, ctx->r15) = ctx->r1;
    // 0x800973D4: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x800973D8: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x800973DC: addiu       $t8, $t8, 0x7AA4
    ctx->r24 = ADD32(ctx->r24, 0X7AA4);
    // 0x800973E0: sw          $at, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->r1;
    // 0x800973E4: lw          $t9, 0x4($t6)
    ctx->r25 = MEM_W(ctx->r14, 0X4);
    // 0x800973E8: sw          $t9, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->r25;
    // 0x800973EC: lh          $t1, 0x4($v1)
    ctx->r9 = MEM_H(ctx->r3, 0X4);
    // 0x800973F0: multu       $t1, $t3
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800973F4: mflo        $t9
    ctx->r25 = lo;
    // 0x800973F8: nop

    // 0x800973FC: nop

    // 0x80097400: multu       $t9, $a1
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097404: mflo        $t6
    ctx->r14 = lo;
    // 0x80097408: addu        $t7, $a0, $t6
    ctx->r15 = ADD32(ctx->r4, ctx->r14);
    // 0x8009740C: addiu       $t6, $t7, 0x3C
    ctx->r14 = ADD32(ctx->r15, 0X3C);
L_80097410:
    // 0x80097410: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x80097414: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x80097418: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x8009741C: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80097420: lw          $at, -0x8($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X8);
    // 0x80097424: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80097428: lw          $at, -0x4($t7)
    ctx->r1 = MEM_W(ctx->r15, -0X4);
    // 0x8009742C: bne         $t7, $t6, L_80097410
    if (ctx->r15 != ctx->r14) {
        // 0x80097430: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80097410;
    }
    // 0x80097430: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80097434: lw          $at, 0x0($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X0);
    // 0x80097438: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x8009743C: addiu       $t9, $t9, 0x7AE8
    ctx->r25 = ADD32(ctx->r25, 0X7AE8);
    // 0x80097440: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80097444: lw          $t6, 0x4($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X4);
    // 0x80097448: sw          $t6, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r14;
    // 0x8009744C: lh          $t4, 0x8($v1)
    ctx->r12 = MEM_H(ctx->r3, 0X8);
    // 0x80097450: multu       $t4, $t3
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097454: mflo        $t6
    ctx->r14 = lo;
    // 0x80097458: nop

    // 0x8009745C: nop

    // 0x80097460: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097464: mflo        $t7
    ctx->r15 = lo;
    // 0x80097468: addu        $t8, $a0, $t7
    ctx->r24 = ADD32(ctx->r4, ctx->r15);
    // 0x8009746C: addiu       $t7, $t8, 0x3C
    ctx->r15 = ADD32(ctx->r24, 0X3C);
L_80097470:
    // 0x80097470: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x80097474: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80097478: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x8009747C: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x80097480: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x80097484: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x80097488: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x8009748C: bne         $t8, $t7, L_80097470
    if (ctx->r24 != ctx->r15) {
        // 0x80097490: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80097470;
    }
    // 0x80097490: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x80097494: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x80097498: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x8009749C: addiu       $t6, $t6, 0x7B2C
    ctx->r14 = ADD32(ctx->r14, 0X7B2C);
    // 0x800974A0: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x800974A4: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x800974A8: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x800974AC: lh          $t5, 0xC($v1)
    ctx->r13 = MEM_H(ctx->r3, 0XC);
    // 0x800974B0: multu       $t5, $t3
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800974B4: mflo        $t7
    ctx->r15 = lo;
    // 0x800974B8: nop

    // 0x800974BC: nop

    // 0x800974C0: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800974C4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800974C8: mflo        $t8
    ctx->r24 = lo;
    // 0x800974CC: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x800974D0: addiu       $t8, $t9, 0x3C
    ctx->r24 = ADD32(ctx->r25, 0X3C);
L_800974D4:
    // 0x800974D4: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x800974D8: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x800974DC: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x800974E0: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x800974E4: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x800974E8: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x800974EC: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x800974F0: bne         $t9, $t8, L_800974D4
    if (ctx->r25 != ctx->r24) {
        // 0x800974F4: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_800974D4;
    }
    // 0x800974F4: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x800974F8: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x800974FC: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x80097500: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x80097504: bne         $t2, $v0, L_80097518
    if (ctx->r10 != ctx->r2) {
        // 0x80097508: sw          $t8, 0x4($t6)
        MEM_W(0X4, ctx->r14) = ctx->r24;
            goto L_80097518;
    }
    // 0x80097508: sw          $t8, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r24;
    // 0x8009750C: sh          $t7, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r15;
    // 0x80097510: b           L_80097524
    // 0x80097514: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
        goto L_80097524;
    // 0x80097514: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
L_80097518:
    // 0x80097518: bne         $a3, $v0, L_80097524
    if (ctx->r7 != ctx->r2) {
        // 0x8009751C: nop
    
            goto L_80097524;
    }
    // 0x8009751C: nop

    // 0x80097520: sh          $t2, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r10;
L_80097524:
    // 0x80097524: bne         $t2, $t1, L_80097534
    if (ctx->r10 != ctx->r9) {
        // 0x80097528: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_80097534;
    }
    // 0x80097528: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x8009752C: b           L_80097540
    // 0x80097530: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
        goto L_80097540;
    // 0x80097530: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
L_80097534:
    // 0x80097534: bne         $a3, $t1, L_80097540
    if (ctx->r7 != ctx->r9) {
        // 0x80097538: nop
    
            goto L_80097540;
    }
    // 0x80097538: nop

    // 0x8009753C: sh          $t2, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r10;
L_80097540:
    // 0x80097540: bne         $t2, $t4, L_80097550
    if (ctx->r10 != ctx->r12) {
        // 0x80097544: addiu       $v0, $zero, 0x1
        ctx->r2 = ADD32(0, 0X1);
            goto L_80097550;
    }
    // 0x80097544: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80097548: b           L_8009755C
    // 0x8009754C: sh          $v0, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r2;
        goto L_8009755C;
    // 0x8009754C: sh          $v0, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r2;
L_80097550:
    // 0x80097550: bne         $a3, $t4, L_8009755C
    if (ctx->r7 != ctx->r12) {
        // 0x80097554: nop
    
            goto L_8009755C;
    }
    // 0x80097554: nop

    // 0x80097558: sh          $t2, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r10;
L_8009755C:
    // 0x8009755C: bne         $t2, $t5, L_8009756C
    if (ctx->r10 != ctx->r13) {
        // 0x80097560: addiu       $t6, $zero, 0x1
        ctx->r14 = ADD32(0, 0X1);
            goto L_8009756C;
    }
    // 0x80097560: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x80097564: b           L_80097578
    // 0x80097568: sh          $t6, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r14;
        goto L_80097578;
    // 0x80097568: sh          $t6, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r14;
L_8009756C:
    // 0x8009756C: bne         $a3, $t5, L_80097578
    if (ctx->r7 != ctx->r13) {
        // 0x80097570: nop
    
            goto L_80097578;
    }
    // 0x80097570: nop

    // 0x80097574: sh          $t2, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r10;
L_80097578:
    // 0x80097578: blez        $s0, L_80097C68
    if (SIGNED(ctx->r16) <= 0) {
        // 0x8009757C: or          $t0, $zero, $zero
        ctx->r8 = 0 | 0;
            goto L_80097C68;
    }
    // 0x8009757C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80097580: andi        $v0, $s0, 0x3
    ctx->r2 = ctx->r16 & 0X3;
    // 0x80097584: beq         $v0, $zero, L_800975CC
    if (ctx->r2 == 0) {
        // 0x80097588: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800975CC;
    }
    // 0x80097588: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x8009758C: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x80097590: addiu       $t8, $t8, -0x18C0
    ctx->r24 = ADD32(ctx->r24, -0X18C0);
    // 0x80097594: sll         $t7, $zero, 2
    ctx->r15 = S32(0 << 2);
    // 0x80097598: addu        $t1, $t7, $t8
    ctx->r9 = ADD32(ctx->r15, ctx->r24);
L_8009759C:
    // 0x8009759C: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x800975A0: bne         $t2, $v0, L_800975B0
    if (ctx->r10 != ctx->r2) {
        // 0x800975A4: nop
    
            goto L_800975B0;
    }
    // 0x800975A4: nop

    // 0x800975A8: b           L_800975BC
    // 0x800975AC: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_800975BC;
    // 0x800975AC: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_800975B0:
    // 0x800975B0: bnel        $a3, $v0, L_800975C0
    if (ctx->r7 != ctx->r2) {
        // 0x800975B4: addiu       $t0, $t0, 0x1
        ctx->r8 = ADD32(ctx->r8, 0X1);
            goto L_800975C0;
    }
    goto skip_8;
    // 0x800975B4: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    skip_8:
    // 0x800975B8: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_800975BC:
    // 0x800975BC: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
L_800975C0:
    // 0x800975C0: bne         $v1, $t0, L_8009759C
    if (ctx->r3 != ctx->r8) {
        // 0x800975C4: addiu       $t1, $t1, 0x4
        ctx->r9 = ADD32(ctx->r9, 0X4);
            goto L_8009759C;
    }
    // 0x800975C4: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x800975C8: beq         $t0, $s0, L_80097C68
    if (ctx->r8 == ctx->r16) {
        // 0x800975CC: lui         $t6, 0x801D
        ctx->r14 = S32(0X801D << 16);
            goto L_80097C68;
    }
L_800975CC:
    // 0x800975CC: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800975D0: addiu       $t6, $t6, -0x18C0
    ctx->r14 = ADD32(ctx->r14, -0X18C0);
    // 0x800975D4: sll         $t9, $t0, 2
    ctx->r25 = S32(ctx->r8 << 2);
    // 0x800975D8: addu        $t1, $t9, $t6
    ctx->r9 = ADD32(ctx->r25, ctx->r14);
L_800975DC:
    // 0x800975DC: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x800975E0: addiu       $t7, $t0, 0x1
    ctx->r15 = ADD32(ctx->r8, 0X1);
    // 0x800975E4: addiu       $t9, $t0, 0x2
    ctx->r25 = ADD32(ctx->r8, 0X2);
    // 0x800975E8: bne         $t2, $v0, L_800975F8
    if (ctx->r10 != ctx->r2) {
        // 0x800975EC: nop
    
            goto L_800975F8;
    }
    // 0x800975EC: nop

    // 0x800975F0: b           L_80097604
    // 0x800975F4: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80097604;
    // 0x800975F4: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_800975F8:
    // 0x800975F8: bnel        $a3, $v0, L_80097608
    if (ctx->r7 != ctx->r2) {
        // 0x800975FC: lh          $v0, 0x4($t1)
        ctx->r2 = MEM_H(ctx->r9, 0X4);
            goto L_80097608;
    }
    goto skip_9;
    // 0x800975FC: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
    skip_9:
    // 0x80097600: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80097604:
    // 0x80097604: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
L_80097608:
    // 0x80097608: bne         $t2, $v0, L_80097618
    if (ctx->r10 != ctx->r2) {
        // 0x8009760C: nop
    
            goto L_80097618;
    }
    // 0x8009760C: nop

    // 0x80097610: b           L_80097624
    // 0x80097614: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097624;
    // 0x80097614: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_80097618:
    // 0x80097618: bne         $a3, $v0, L_80097624
    if (ctx->r7 != ctx->r2) {
        // 0x8009761C: addiu       $t8, $t0, 0x1
        ctx->r24 = ADD32(ctx->r8, 0X1);
            goto L_80097624;
    }
    // 0x8009761C: addiu       $t8, $t0, 0x1
    ctx->r24 = ADD32(ctx->r8, 0X1);
    // 0x80097620: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_80097624:
    // 0x80097624: lh          $v0, 0x8($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X8);
    // 0x80097628: addiu       $t7, $t0, 0x3
    ctx->r15 = ADD32(ctx->r8, 0X3);
    // 0x8009762C: bne         $t2, $v0, L_8009763C
    if (ctx->r10 != ctx->r2) {
        // 0x80097630: nop
    
            goto L_8009763C;
    }
    // 0x80097630: nop

    // 0x80097634: b           L_80097648
    // 0x80097638: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
        goto L_80097648;
    // 0x80097638: sw          $t9, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r25;
L_8009763C:
    // 0x8009763C: bne         $a3, $v0, L_80097648
    if (ctx->r7 != ctx->r2) {
        // 0x80097640: addiu       $t6, $t0, 0x2
        ctx->r14 = ADD32(ctx->r8, 0X2);
            goto L_80097648;
    }
    // 0x80097640: addiu       $t6, $t0, 0x2
    ctx->r14 = ADD32(ctx->r8, 0X2);
    // 0x80097644: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097648:
    // 0x80097648: lh          $v0, 0xC($t1)
    ctx->r2 = MEM_H(ctx->r9, 0XC);
    // 0x8009764C: bne         $t2, $v0, L_8009765C
    if (ctx->r10 != ctx->r2) {
        // 0x80097650: nop
    
            goto L_8009765C;
    }
    // 0x80097650: nop

    // 0x80097654: b           L_80097668
    // 0x80097658: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097668;
    // 0x80097658: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_8009765C:
    // 0x8009765C: bne         $a3, $v0, L_80097668
    if (ctx->r7 != ctx->r2) {
        // 0x80097660: addiu       $t8, $t0, 0x3
        ctx->r24 = ADD32(ctx->r8, 0X3);
            goto L_80097668;
    }
    // 0x80097660: addiu       $t8, $t0, 0x3
    ctx->r24 = ADD32(ctx->r8, 0X3);
    // 0x80097664: sw          $t8, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r24;
L_80097668:
    // 0x80097668: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x8009766C: bne         $t0, $s0, L_800975DC
    if (ctx->r8 != ctx->r16) {
        // 0x80097670: addiu       $t1, $t1, 0x10
        ctx->r9 = ADD32(ctx->r9, 0X10);
            goto L_800975DC;
    }
    // 0x80097670: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
    // 0x80097674: b           L_80097C6C
    // 0x80097678: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
        goto L_80097C6C;
    // 0x80097678: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
L_8009767C:
    // 0x8009767C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x80097680: addiu       $v1, $v1, -0x18C0
    ctx->r3 = ADD32(ctx->r3, -0X18C0);
    // 0x80097684: lh          $v0, 0x0($v1)
    ctx->r2 = MEM_H(ctx->r3, 0X0);
    // 0x80097688: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x8009768C: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80097690: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097694: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80097698: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x8009769C: addiu       $t9, $t9, 0x7A60
    ctx->r25 = ADD32(ctx->r25, 0X7A60);
    // 0x800976A0: mflo        $t6
    ctx->r14 = lo;
    // 0x800976A4: nop

    // 0x800976A8: nop

    // 0x800976AC: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800976B0: mflo        $t7
    ctx->r15 = lo;
    // 0x800976B4: addu        $t8, $a0, $t7
    ctx->r24 = ADD32(ctx->r4, ctx->r15);
    // 0x800976B8: addiu       $t7, $t8, 0x3C
    ctx->r15 = ADD32(ctx->r24, 0X3C);
L_800976BC:
    // 0x800976BC: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x800976C0: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x800976C4: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x800976C8: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x800976CC: lw          $at, -0x8($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X8);
    // 0x800976D0: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x800976D4: lw          $at, -0x4($t8)
    ctx->r1 = MEM_W(ctx->r24, -0X4);
    // 0x800976D8: bne         $t8, $t7, L_800976BC
    if (ctx->r24 != ctx->r15) {
        // 0x800976DC: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_800976BC;
    }
    // 0x800976DC: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x800976E0: lw          $at, 0x0($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X0);
    // 0x800976E4: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x800976E8: addiu       $t6, $t6, 0x7AA4
    ctx->r14 = ADD32(ctx->r14, 0X7AA4);
    // 0x800976EC: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x800976F0: lw          $t7, 0x4($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X4);
    // 0x800976F4: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x800976F8: lh          $t1, 0x4($v1)
    ctx->r9 = MEM_H(ctx->r3, 0X4);
    // 0x800976FC: multu       $t1, $t3
    result = U64(U32(ctx->r9)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097700: mflo        $t7
    ctx->r15 = lo;
    // 0x80097704: nop

    // 0x80097708: nop

    // 0x8009770C: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097710: mflo        $t8
    ctx->r24 = lo;
    // 0x80097714: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x80097718: addiu       $t8, $t9, 0x3C
    ctx->r24 = ADD32(ctx->r25, 0X3C);
L_8009771C:
    // 0x8009771C: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x80097720: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80097724: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80097728: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x8009772C: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x80097730: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x80097734: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x80097738: bne         $t9, $t8, L_8009771C
    if (ctx->r25 != ctx->r24) {
        // 0x8009773C: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_8009771C;
    }
    // 0x8009773C: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x80097740: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x80097744: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x80097748: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x8009774C: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x80097750: addiu       $t9, $t9, 0x7AE8
    ctx->r25 = ADD32(ctx->r25, 0X7AE8);
    // 0x80097754: sw          $t8, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r24;
    // 0x80097758: lh          $t4, 0x8($v1)
    ctx->r12 = MEM_H(ctx->r3, 0X8);
    // 0x8009775C: multu       $t4, $t3
    result = U64(U32(ctx->r12)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097760: mflo        $t7
    ctx->r15 = lo;
    // 0x80097764: nop

    // 0x80097768: nop

    // 0x8009776C: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097770: mflo        $t8
    ctx->r24 = lo;
    // 0x80097774: addu        $a3, $a0, $t8
    ctx->r7 = ADD32(ctx->r4, ctx->r24);
    // 0x80097778: or          $t8, $a3, $zero
    ctx->r24 = ctx->r7 | 0;
    // 0x8009777C: addiu       $t7, $a3, 0x3C
    ctx->r15 = ADD32(ctx->r7, 0X3C);
L_80097780:
    // 0x80097780: lw          $at, 0x44($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X44);
    // 0x80097784: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80097788: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x8009778C: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x80097790: lw          $at, 0x3C($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X3C);
    // 0x80097794: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x80097798: lw          $at, 0x40($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X40);
    // 0x8009779C: bne         $t8, $t7, L_80097780
    if (ctx->r24 != ctx->r15) {
        // 0x800977A0: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80097780;
    }
    // 0x800977A0: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x800977A4: lw          $at, 0x44($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X44);
    // 0x800977A8: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x800977AC: lw          $t7, 0x48($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X48);
    // 0x800977B0: lui         $t8, 0x8022
    ctx->r24 = S32(0X8022 << 16);
    // 0x800977B4: addiu       $t8, $t8, 0x7B2C
    ctx->r24 = ADD32(ctx->r24, 0X7B2C);
    // 0x800977B8: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x800977BC: lh          $t5, 0xC($v1)
    ctx->r13 = MEM_H(ctx->r3, 0XC);
    // 0x800977C0: multu       $t5, $t3
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800977C4: mflo        $t6
    ctx->r14 = lo;
    // 0x800977C8: nop

    // 0x800977CC: nop

    // 0x800977D0: multu       $t6, $a1
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800977D4: mflo        $t7
    ctx->r15 = lo;
    // 0x800977D8: addu        $t0, $a0, $t7
    ctx->r8 = ADD32(ctx->r4, ctx->r15);
    // 0x800977DC: or          $t7, $t0, $zero
    ctx->r15 = ctx->r8 | 0;
    // 0x800977E0: addiu       $t6, $t0, 0x3C
    ctx->r14 = ADD32(ctx->r8, 0X3C);
L_800977E4:
    // 0x800977E4: lw          $at, 0x44($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X44);
    // 0x800977E8: addiu       $t7, $t7, 0xC
    ctx->r15 = ADD32(ctx->r15, 0XC);
    // 0x800977EC: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x800977F0: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x800977F4: lw          $at, 0x3C($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X3C);
    // 0x800977F8: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x800977FC: lw          $at, 0x40($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X40);
    // 0x80097800: bne         $t7, $t6, L_800977E4
    if (ctx->r15 != ctx->r14) {
        // 0x80097804: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_800977E4;
    }
    // 0x80097804: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80097808: lw          $at, 0x44($t7)
    ctx->r1 = MEM_W(ctx->r15, 0X44);
    // 0x8009780C: lui         $t9, 0x8022
    ctx->r25 = S32(0X8022 << 16);
    // 0x80097810: addiu       $t9, $t9, 0x7B70
    ctx->r25 = ADD32(ctx->r25, 0X7B70);
    // 0x80097814: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80097818: lw          $t6, 0x48($t7)
    ctx->r14 = MEM_W(ctx->r15, 0X48);
    // 0x8009781C: addiu       $t7, $a3, 0x3C
    ctx->r15 = ADD32(ctx->r7, 0X3C);
    // 0x80097820: sw          $t6, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r14;
    // 0x80097824: or          $t8, $a3, $zero
    ctx->r24 = ctx->r7 | 0;
L_80097828:
    // 0x80097828: lw          $at, 0x88($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X88);
    // 0x8009782C: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80097830: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80097834: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x80097838: lw          $at, 0x80($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X80);
    // 0x8009783C: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x80097840: lw          $at, 0x84($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X84);
    // 0x80097844: bne         $t8, $t7, L_80097828
    if (ctx->r24 != ctx->r15) {
        // 0x80097848: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80097828;
    }
    // 0x80097848: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x8009784C: lw          $at, 0x88($t8)
    ctx->r1 = MEM_W(ctx->r24, 0X88);
    // 0x80097850: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x80097854: addiu       $t6, $t6, 0x7BB4
    ctx->r14 = ADD32(ctx->r14, 0X7BB4);
    // 0x80097858: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x8009785C: lw          $t7, 0x8C($t8)
    ctx->r15 = MEM_W(ctx->r24, 0X8C);
    // 0x80097860: addiu       $t8, $t0, 0x3C
    ctx->r24 = ADD32(ctx->r8, 0X3C);
    // 0x80097864: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x80097868: sw          $t7, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r15;
    // 0x8009786C: or          $t9, $t0, $zero
    ctx->r25 = ctx->r8 | 0;
L_80097870:
    // 0x80097870: lw          $at, 0x88($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X88);
    // 0x80097874: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80097878: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x8009787C: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x80097880: lw          $at, 0x80($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X80);
    // 0x80097884: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x80097888: lw          $at, 0x84($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X84);
    // 0x8009788C: bne         $t9, $t8, L_80097870
    if (ctx->r25 != ctx->r24) {
        // 0x80097890: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_80097870;
    }
    // 0x80097890: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x80097894: lw          $at, 0x88($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X88);
    // 0x80097898: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x8009789C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x800978A0: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x800978A4: lw          $t8, 0x8C($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X8C);
    // 0x800978A8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800978AC: bne         $t2, $v0, L_800978C0
    if (ctx->r10 != ctx->r2) {
        // 0x800978B0: sw          $t8, 0x4($t6)
        MEM_W(0X4, ctx->r14) = ctx->r24;
            goto L_800978C0;
    }
    // 0x800978B0: sw          $t8, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r24;
    // 0x800978B4: sh          $t7, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r15;
    // 0x800978B8: b           L_800978CC
    // 0x800978BC: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
        goto L_800978CC;
    // 0x800978BC: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
L_800978C0:
    // 0x800978C0: bne         $a3, $v0, L_800978CC
    if (ctx->r7 != ctx->r2) {
        // 0x800978C4: nop
    
            goto L_800978CC;
    }
    // 0x800978C4: nop

    // 0x800978C8: sh          $t2, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r10;
L_800978CC:
    // 0x800978CC: bne         $t2, $t1, L_800978DC
    if (ctx->r10 != ctx->r9) {
        // 0x800978D0: addiu       $t8, $zero, 0x1
        ctx->r24 = ADD32(0, 0X1);
            goto L_800978DC;
    }
    // 0x800978D0: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800978D4: b           L_800978E8
    // 0x800978D8: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
        goto L_800978E8;
    // 0x800978D8: sh          $t8, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r24;
L_800978DC:
    // 0x800978DC: bne         $a3, $t1, L_800978E8
    if (ctx->r7 != ctx->r9) {
        // 0x800978E0: nop
    
            goto L_800978E8;
    }
    // 0x800978E0: nop

    // 0x800978E4: sh          $t2, 0x42($sp)
    MEM_H(0X42, ctx->r29) = ctx->r10;
L_800978E8:
    // 0x800978E8: bne         $t2, $t4, L_800978FC
    if (ctx->r10 != ctx->r12) {
        // 0x800978EC: lui         $t1, 0x801D
        ctx->r9 = S32(0X801D << 16);
            goto L_800978FC;
    }
    // 0x800978EC: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800978F0: sh          $t9, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r25;
    // 0x800978F4: b           L_8009790C
    // 0x800978F8: sh          $t9, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r25;
        goto L_8009790C;
    // 0x800978F8: sh          $t9, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r25;
L_800978FC:
    // 0x800978FC: bne         $a3, $t4, L_8009790C
    if (ctx->r7 != ctx->r12) {
        // 0x80097900: nop
    
            goto L_8009790C;
    }
    // 0x80097900: nop

    // 0x80097904: sh          $t2, 0x44($sp)
    MEM_H(0X44, ctx->r29) = ctx->r10;
    // 0x80097908: sh          $t2, 0x48($sp)
    MEM_H(0X48, ctx->r29) = ctx->r10;
L_8009790C:
    // 0x8009790C: bne         $t2, $t5, L_80097924
    if (ctx->r10 != ctx->r13) {
        // 0x80097910: addiu       $t1, $t1, -0x18C0
        ctx->r9 = ADD32(ctx->r9, -0X18C0);
            goto L_80097924;
    }
    // 0x80097910: addiu       $t1, $t1, -0x18C0
    ctx->r9 = ADD32(ctx->r9, -0X18C0);
    // 0x80097914: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x80097918: sh          $v1, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r3;
    // 0x8009791C: b           L_80097934
    // 0x80097920: sh          $v1, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r3;
        goto L_80097934;
    // 0x80097920: sh          $v1, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r3;
L_80097924:
    // 0x80097924: bne         $a3, $t5, L_80097934
    if (ctx->r7 != ctx->r13) {
        // 0x80097928: nop
    
            goto L_80097934;
    }
    // 0x80097928: nop

    // 0x8009792C: sh          $t2, 0x46($sp)
    MEM_H(0X46, ctx->r29) = ctx->r10;
    // 0x80097930: sh          $t2, 0x4A($sp)
    MEM_H(0X4A, ctx->r29) = ctx->r10;
L_80097934:
    // 0x80097934: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80097938: bne         $t2, $v0, L_80097948
    if (ctx->r10 != ctx->r2) {
        // 0x8009793C: nop
    
            goto L_80097948;
    }
    // 0x8009793C: nop

    // 0x80097940: b           L_80097954
    // 0x80097944: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80097954;
    // 0x80097944: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_80097948:
    // 0x80097948: bnel        $a3, $v0, L_80097958
    if (ctx->r7 != ctx->r2) {
        // 0x8009794C: addiu       $t0, $t0, 0x1
        ctx->r8 = ADD32(ctx->r8, 0X1);
            goto L_80097958;
    }
    goto skip_10;
    // 0x8009794C: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    skip_10:
    // 0x80097950: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80097954:
    // 0x80097954: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
L_80097958:
    // 0x80097958: bne         $t0, $t2, L_80097934
    if (ctx->r8 != ctx->r10) {
        // 0x8009795C: addiu       $t1, $t1, 0x4
        ctx->r9 = ADD32(ctx->r9, 0X4);
            goto L_80097934;
    }
    // 0x8009795C: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x80097960: b           L_80097C6C
    // 0x80097964: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
        goto L_80097C6C;
    // 0x80097964: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
L_80097968:
    // 0x80097968: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    // 0x8009796C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80097970: blez        $t9, L_80097B6C
    if (SIGNED(ctx->r25) <= 0) {
        // 0x80097974: andi        $v0, $t9, 0x1
        ctx->r2 = ctx->r25 & 0X1;
            goto L_80097B6C;
    }
    // 0x80097974: andi        $v0, $t9, 0x1
    ctx->r2 = ctx->r25 & 0X1;
    // 0x80097978: beq         $v0, $zero, L_80097A14
    if (ctx->r2 == 0) {
        // 0x8009797C: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_80097A14;
    }
    // 0x8009797C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x80097980: lh          $v0, -0x18C0($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X18C0);
    // 0x80097984: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x80097988: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009798C: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097990: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80097994: lui         $t6, 0x8022
    ctx->r14 = S32(0X8022 << 16);
    // 0x80097998: addiu       $t6, $t6, 0x7A60
    ctx->r14 = ADD32(ctx->r14, 0X7A60);
    // 0x8009799C: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x800979A0: mflo        $t7
    ctx->r15 = lo;
    // 0x800979A4: nop

    // 0x800979A8: nop

    // 0x800979AC: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800979B0: mflo        $t8
    ctx->r24 = lo;
    // 0x800979B4: addu        $t9, $a0, $t8
    ctx->r25 = ADD32(ctx->r4, ctx->r24);
    // 0x800979B8: addiu       $t8, $t9, 0x3C
    ctx->r24 = ADD32(ctx->r25, 0X3C);
L_800979BC:
    // 0x800979BC: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x800979C0: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x800979C4: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x800979C8: sw          $at, -0xC($t6)
    MEM_W(-0XC, ctx->r14) = ctx->r1;
    // 0x800979CC: lw          $at, -0x8($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X8);
    // 0x800979D0: sw          $at, -0x8($t6)
    MEM_W(-0X8, ctx->r14) = ctx->r1;
    // 0x800979D4: lw          $at, -0x4($t9)
    ctx->r1 = MEM_W(ctx->r25, -0X4);
    // 0x800979D8: bne         $t9, $t8, L_800979BC
    if (ctx->r25 != ctx->r24) {
        // 0x800979DC: sw          $at, -0x4($t6)
        MEM_W(-0X4, ctx->r14) = ctx->r1;
            goto L_800979BC;
    }
    // 0x800979DC: sw          $at, -0x4($t6)
    MEM_W(-0X4, ctx->r14) = ctx->r1;
    // 0x800979E0: lw          $at, 0x0($t9)
    ctx->r1 = MEM_W(ctx->r25, 0X0);
    // 0x800979E4: sw          $at, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->r1;
    // 0x800979E8: lw          $t8, 0x4($t9)
    ctx->r24 = MEM_W(ctx->r25, 0X4);
    // 0x800979EC: bne         $t2, $v0, L_800979FC
    if (ctx->r10 != ctx->r2) {
        // 0x800979F0: sw          $t8, 0x4($t6)
        MEM_W(0X4, ctx->r14) = ctx->r24;
            goto L_800979FC;
    }
    // 0x800979F0: sw          $t8, 0x4($t6)
    MEM_W(0X4, ctx->r14) = ctx->r24;
    // 0x800979F4: b           L_80097A08
    // 0x800979F8: sh          $t4, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r12;
        goto L_80097A08;
    // 0x800979F8: sh          $t4, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r12;
L_800979FC:
    // 0x800979FC: bnel        $a3, $v0, L_80097A0C
    if (ctx->r7 != ctx->r2) {
        // 0x80097A00: lw          $t7, 0x64($sp)
        ctx->r15 = MEM_W(ctx->r29, 0X64);
            goto L_80097A0C;
    }
    goto skip_11;
    // 0x80097A00: lw          $t7, 0x64($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X64);
    skip_11:
    // 0x80097A04: sh          $t2, 0x40($sp)
    MEM_H(0X40, ctx->r29) = ctx->r10;
L_80097A08:
    // 0x80097A08: lw          $t7, 0x64($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X64);
L_80097A0C:
    // 0x80097A0C: or          $t0, $t4, $zero
    ctx->r8 = ctx->r12 | 0;
    // 0x80097A10: beq         $t4, $t7, L_80097B68
    if (ctx->r12 == ctx->r15) {
        // 0x80097A14: sll         $t6, $t0, 4
        ctx->r14 = S32(ctx->r8 << 4);
            goto L_80097B68;
    }
L_80097A14:
    // 0x80097A14: sll         $t6, $t0, 4
    ctx->r14 = S32(ctx->r8 << 4);
    // 0x80097A18: addu        $t6, $t6, $t0
    ctx->r14 = ADD32(ctx->r14, ctx->r8);
    // 0x80097A1C: lui         $t7, 0x8022
    ctx->r15 = S32(0X8022 << 16);
    // 0x80097A20: addiu       $t7, $t7, 0x7A60
    ctx->r15 = ADD32(ctx->r15, 0X7A60);
    // 0x80097A24: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x80097A28: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80097A2C: addiu       $t9, $t9, -0x18C0
    ctx->r25 = ADD32(ctx->r25, -0X18C0);
    // 0x80097A30: addu        $v1, $t6, $t7
    ctx->r3 = ADD32(ctx->r14, ctx->r15);
    // 0x80097A34: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80097A38: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x80097A3C: addu        $t1, $t8, $t9
    ctx->r9 = ADD32(ctx->r24, ctx->r25);
    // 0x80097A40: addiu       $a0, $a0, -0x5330
    ctx->r4 = ADD32(ctx->r4, -0X5330);
    // 0x80097A44: addiu       $t5, $v1, 0x44
    ctx->r13 = ADD32(ctx->r3, 0X44);
    // 0x80097A48: addiu       $a1, $zero, 0x44
    ctx->r5 = ADD32(0, 0X44);
    // 0x80097A4C: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
L_80097A50:
    // 0x80097A50: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80097A54: sll         $t7, $t0, 1
    ctx->r15 = S32(ctx->r8 << 1);
    // 0x80097A58: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097A5C: mflo        $t8
    ctx->r24 = lo;
    // 0x80097A60: nop

    // 0x80097A64: nop

    // 0x80097A68: multu       $t8, $a1
    result = U64(U32(ctx->r24)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097A6C: mflo        $t9
    ctx->r25 = lo;
    // 0x80097A70: addu        $t6, $a0, $t9
    ctx->r14 = ADD32(ctx->r4, ctx->r25);
    // 0x80097A74: addiu       $t8, $t6, 0x3C
    ctx->r24 = ADD32(ctx->r14, 0X3C);
    // 0x80097A78: or          $t9, $v1, $zero
    ctx->r25 = ctx->r3 | 0;
L_80097A7C:
    // 0x80097A7C: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x80097A80: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80097A84: addiu       $t9, $t9, 0xC
    ctx->r25 = ADD32(ctx->r25, 0XC);
    // 0x80097A88: sw          $at, -0xC($t9)
    MEM_W(-0XC, ctx->r25) = ctx->r1;
    // 0x80097A8C: lw          $at, -0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X8);
    // 0x80097A90: sw          $at, -0x8($t9)
    MEM_W(-0X8, ctx->r25) = ctx->r1;
    // 0x80097A94: lw          $at, -0x4($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X4);
    // 0x80097A98: bne         $t6, $t8, L_80097A7C
    if (ctx->r14 != ctx->r24) {
        // 0x80097A9C: sw          $at, -0x4($t9)
        MEM_W(-0X4, ctx->r25) = ctx->r1;
            goto L_80097A7C;
    }
    // 0x80097A9C: sw          $at, -0x4($t9)
    MEM_W(-0X4, ctx->r25) = ctx->r1;
    // 0x80097AA0: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x80097AA4: addiu       $v1, $v1, 0x88
    ctx->r3 = ADD32(ctx->r3, 0X88);
    // 0x80097AA8: sw          $at, 0x0($t9)
    MEM_W(0X0, ctx->r25) = ctx->r1;
    // 0x80097AAC: lw          $t8, 0x4($t6)
    ctx->r24 = MEM_W(ctx->r14, 0X4);
    // 0x80097AB0: bne         $t2, $v0, L_80097AC4
    if (ctx->r10 != ctx->r2) {
        // 0x80097AB4: sw          $t8, 0x4($t9)
        MEM_W(0X4, ctx->r25) = ctx->r24;
            goto L_80097AC4;
    }
    // 0x80097AB4: sw          $t8, 0x4($t9)
    MEM_W(0X4, ctx->r25) = ctx->r24;
    // 0x80097AB8: addu        $t8, $sp, $t7
    ctx->r24 = ADD32(ctx->r29, ctx->r15);
    // 0x80097ABC: b           L_80097AD4
    // 0x80097AC0: sh          $t4, 0x40($t8)
    MEM_H(0X40, ctx->r24) = ctx->r12;
        goto L_80097AD4;
    // 0x80097AC0: sh          $t4, 0x40($t8)
    MEM_H(0X40, ctx->r24) = ctx->r12;
L_80097AC4:
    // 0x80097AC4: bne         $a3, $v0, L_80097AD4
    if (ctx->r7 != ctx->r2) {
        // 0x80097AC8: sll         $t6, $t0, 1
        ctx->r14 = S32(ctx->r8 << 1);
            goto L_80097AD4;
    }
    // 0x80097AC8: sll         $t6, $t0, 1
    ctx->r14 = S32(ctx->r8 << 1);
    // 0x80097ACC: addu        $t9, $sp, $t6
    ctx->r25 = ADD32(ctx->r29, ctx->r14);
    // 0x80097AD0: sh          $t2, 0x40($t9)
    MEM_H(0X40, ctx->r25) = ctx->r10;
L_80097AD4:
    // 0x80097AD4: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
    // 0x80097AD8: sll         $t9, $t0, 1
    ctx->r25 = S32(ctx->r8 << 1);
    // 0x80097ADC: multu       $v0, $t3
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r11)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097AE0: mflo        $t7
    ctx->r15 = lo;
    // 0x80097AE4: nop

    // 0x80097AE8: nop

    // 0x80097AEC: multu       $t7, $a1
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r5)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80097AF0: mflo        $t8
    ctx->r24 = lo;
    // 0x80097AF4: addu        $t6, $a0, $t8
    ctx->r14 = ADD32(ctx->r4, ctx->r24);
    // 0x80097AF8: addiu       $t7, $t6, 0x3C
    ctx->r15 = ADD32(ctx->r14, 0X3C);
    // 0x80097AFC: or          $t8, $t5, $zero
    ctx->r24 = ctx->r13 | 0;
L_80097B00:
    // 0x80097B00: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x80097B04: addiu       $t6, $t6, 0xC
    ctx->r14 = ADD32(ctx->r14, 0XC);
    // 0x80097B08: addiu       $t8, $t8, 0xC
    ctx->r24 = ADD32(ctx->r24, 0XC);
    // 0x80097B0C: sw          $at, -0xC($t8)
    MEM_W(-0XC, ctx->r24) = ctx->r1;
    // 0x80097B10: lw          $at, -0x8($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X8);
    // 0x80097B14: sw          $at, -0x8($t8)
    MEM_W(-0X8, ctx->r24) = ctx->r1;
    // 0x80097B18: lw          $at, -0x4($t6)
    ctx->r1 = MEM_W(ctx->r14, -0X4);
    // 0x80097B1C: bne         $t6, $t7, L_80097B00
    if (ctx->r14 != ctx->r15) {
        // 0x80097B20: sw          $at, -0x4($t8)
        MEM_W(-0X4, ctx->r24) = ctx->r1;
            goto L_80097B00;
    }
    // 0x80097B20: sw          $at, -0x4($t8)
    MEM_W(-0X4, ctx->r24) = ctx->r1;
    // 0x80097B24: lw          $at, 0x0($t6)
    ctx->r1 = MEM_W(ctx->r14, 0X0);
    // 0x80097B28: sw          $at, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->r1;
    // 0x80097B2C: lw          $t7, 0x4($t6)
    ctx->r15 = MEM_W(ctx->r14, 0X4);
    // 0x80097B30: bne         $t2, $v0, L_80097B44
    if (ctx->r10 != ctx->r2) {
        // 0x80097B34: sw          $t7, 0x4($t8)
        MEM_W(0X4, ctx->r24) = ctx->r15;
            goto L_80097B44;
    }
    // 0x80097B34: sw          $t7, 0x4($t8)
    MEM_W(0X4, ctx->r24) = ctx->r15;
    // 0x80097B38: addu        $t7, $sp, $t9
    ctx->r15 = ADD32(ctx->r29, ctx->r25);
    // 0x80097B3C: b           L_80097B54
    // 0x80097B40: sh          $t4, 0x42($t7)
    MEM_H(0X42, ctx->r15) = ctx->r12;
        goto L_80097B54;
    // 0x80097B40: sh          $t4, 0x42($t7)
    MEM_H(0X42, ctx->r15) = ctx->r12;
L_80097B44:
    // 0x80097B44: bne         $a3, $v0, L_80097B54
    if (ctx->r7 != ctx->r2) {
        // 0x80097B48: sll         $t6, $t0, 1
        ctx->r14 = S32(ctx->r8 << 1);
            goto L_80097B54;
    }
    // 0x80097B48: sll         $t6, $t0, 1
    ctx->r14 = S32(ctx->r8 << 1);
    // 0x80097B4C: addu        $t8, $sp, $t6
    ctx->r24 = ADD32(ctx->r29, ctx->r14);
    // 0x80097B50: sh          $t2, 0x42($t8)
    MEM_H(0X42, ctx->r24) = ctx->r10;
L_80097B54:
    // 0x80097B54: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    // 0x80097B58: addiu       $t0, $t0, 0x2
    ctx->r8 = ADD32(ctx->r8, 0X2);
    // 0x80097B5C: addiu       $t1, $t1, 0x8
    ctx->r9 = ADD32(ctx->r9, 0X8);
    // 0x80097B60: bne         $t0, $t9, L_80097A50
    if (ctx->r8 != ctx->r25) {
        // 0x80097B64: addiu       $t5, $t5, 0x88
        ctx->r13 = ADD32(ctx->r13, 0X88);
            goto L_80097A50;
    }
    // 0x80097B64: addiu       $t5, $t5, 0x88
    ctx->r13 = ADD32(ctx->r13, 0X88);
L_80097B68:
    // 0x80097B68: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
L_80097B6C:
    // 0x80097B6C: blez        $s0, L_80097C68
    if (SIGNED(ctx->r16) <= 0) {
        // 0x80097B70: addiu       $a3, $zero, 0x6
        ctx->r7 = ADD32(0, 0X6);
            goto L_80097C68;
    }
    // 0x80097B70: addiu       $a3, $zero, 0x6
    ctx->r7 = ADD32(0, 0X6);
    // 0x80097B74: andi        $v0, $s0, 0x3
    ctx->r2 = ctx->r16 & 0X3;
    // 0x80097B78: beq         $v0, $zero, L_80097BC0
    if (ctx->r2 == 0) {
        // 0x80097B7C: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_80097BC0;
    }
    // 0x80097B7C: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x80097B80: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80097B84: addiu       $t6, $t6, -0x18C0
    ctx->r14 = ADD32(ctx->r14, -0X18C0);
    // 0x80097B88: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x80097B8C: addu        $t1, $t7, $t6
    ctx->r9 = ADD32(ctx->r15, ctx->r14);
L_80097B90:
    // 0x80097B90: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80097B94: bne         $t2, $v0, L_80097BA4
    if (ctx->r10 != ctx->r2) {
        // 0x80097B98: nop
    
            goto L_80097BA4;
    }
    // 0x80097B98: nop

    // 0x80097B9C: b           L_80097BB0
    // 0x80097BA0: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80097BB0;
    // 0x80097BA0: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_80097BA4:
    // 0x80097BA4: bnel        $a3, $v0, L_80097BB4
    if (ctx->r7 != ctx->r2) {
        // 0x80097BA8: addiu       $t0, $t0, 0x1
        ctx->r8 = ADD32(ctx->r8, 0X1);
            goto L_80097BB4;
    }
    goto skip_12;
    // 0x80097BA8: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    skip_12:
    // 0x80097BAC: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80097BB0:
    // 0x80097BB0: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
L_80097BB4:
    // 0x80097BB4: bne         $v1, $t0, L_80097B90
    if (ctx->r3 != ctx->r8) {
        // 0x80097BB8: addiu       $t1, $t1, 0x4
        ctx->r9 = ADD32(ctx->r9, 0X4);
            goto L_80097B90;
    }
    // 0x80097BB8: addiu       $t1, $t1, 0x4
    ctx->r9 = ADD32(ctx->r9, 0X4);
    // 0x80097BBC: beq         $t0, $s0, L_80097C68
    if (ctx->r8 == ctx->r16) {
        // 0x80097BC0: lui         $t9, 0x801D
        ctx->r25 = S32(0X801D << 16);
            goto L_80097C68;
    }
L_80097BC0:
    // 0x80097BC0: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80097BC4: addiu       $t9, $t9, -0x18C0
    ctx->r25 = ADD32(ctx->r25, -0X18C0);
    // 0x80097BC8: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x80097BCC: addu        $t1, $t8, $t9
    ctx->r9 = ADD32(ctx->r24, ctx->r25);
L_80097BD0:
    // 0x80097BD0: lh          $v0, 0x0($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X0);
    // 0x80097BD4: addiu       $t7, $t0, 0x1
    ctx->r15 = ADD32(ctx->r8, 0X1);
    // 0x80097BD8: addiu       $t8, $t0, 0x2
    ctx->r24 = ADD32(ctx->r8, 0X2);
    // 0x80097BDC: bne         $t2, $v0, L_80097BEC
    if (ctx->r10 != ctx->r2) {
        // 0x80097BE0: nop
    
            goto L_80097BEC;
    }
    // 0x80097BE0: nop

    // 0x80097BE4: b           L_80097BF8
    // 0x80097BE8: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
        goto L_80097BF8;
    // 0x80097BE8: sw          $t0, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r8;
L_80097BEC:
    // 0x80097BEC: bnel        $a3, $v0, L_80097BFC
    if (ctx->r7 != ctx->r2) {
        // 0x80097BF0: lh          $v0, 0x4($t1)
        ctx->r2 = MEM_H(ctx->r9, 0X4);
            goto L_80097BFC;
    }
    goto skip_13;
    // 0x80097BF0: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
    skip_13:
    // 0x80097BF4: sw          $t0, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r8;
L_80097BF8:
    // 0x80097BF8: lh          $v0, 0x4($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X4);
L_80097BFC:
    // 0x80097BFC: bne         $t2, $v0, L_80097C0C
    if (ctx->r10 != ctx->r2) {
        // 0x80097C00: nop
    
            goto L_80097C0C;
    }
    // 0x80097C00: nop

    // 0x80097C04: b           L_80097C18
    // 0x80097C08: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097C18;
    // 0x80097C08: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_80097C0C:
    // 0x80097C0C: bne         $a3, $v0, L_80097C18
    if (ctx->r7 != ctx->r2) {
        // 0x80097C10: addiu       $t6, $t0, 0x1
        ctx->r14 = ADD32(ctx->r8, 0X1);
            goto L_80097C18;
    }
    // 0x80097C10: addiu       $t6, $t0, 0x1
    ctx->r14 = ADD32(ctx->r8, 0X1);
    // 0x80097C14: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097C18:
    // 0x80097C18: lh          $v0, 0x8($t1)
    ctx->r2 = MEM_H(ctx->r9, 0X8);
    // 0x80097C1C: addiu       $t7, $t0, 0x3
    ctx->r15 = ADD32(ctx->r8, 0X3);
    // 0x80097C20: bne         $t2, $v0, L_80097C30
    if (ctx->r10 != ctx->r2) {
        // 0x80097C24: nop
    
            goto L_80097C30;
    }
    // 0x80097C24: nop

    // 0x80097C28: b           L_80097C3C
    // 0x80097C2C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
        goto L_80097C3C;
    // 0x80097C2C: sw          $t8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r24;
L_80097C30:
    // 0x80097C30: bne         $a3, $v0, L_80097C3C
    if (ctx->r7 != ctx->r2) {
        // 0x80097C34: addiu       $t9, $t0, 0x2
        ctx->r25 = ADD32(ctx->r8, 0X2);
            goto L_80097C3C;
    }
    // 0x80097C34: addiu       $t9, $t0, 0x2
    ctx->r25 = ADD32(ctx->r8, 0X2);
    // 0x80097C38: sw          $t9, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r25;
L_80097C3C:
    // 0x80097C3C: lh          $v0, 0xC($t1)
    ctx->r2 = MEM_H(ctx->r9, 0XC);
    // 0x80097C40: bne         $t2, $v0, L_80097C50
    if (ctx->r10 != ctx->r2) {
        // 0x80097C44: nop
    
            goto L_80097C50;
    }
    // 0x80097C44: nop

    // 0x80097C48: b           L_80097C5C
    // 0x80097C4C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
        goto L_80097C5C;
    // 0x80097C4C: sw          $t7, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->r15;
L_80097C50:
    // 0x80097C50: bne         $a3, $v0, L_80097C5C
    if (ctx->r7 != ctx->r2) {
        // 0x80097C54: addiu       $t6, $t0, 0x3
        ctx->r14 = ADD32(ctx->r8, 0X3);
            goto L_80097C5C;
    }
    // 0x80097C54: addiu       $t6, $t0, 0x3
    ctx->r14 = ADD32(ctx->r8, 0X3);
    // 0x80097C58: sw          $t6, 0x4($a2)
    MEM_W(0X4, ctx->r6) = ctx->r14;
L_80097C5C:
    // 0x80097C5C: addiu       $t0, $t0, 0x4
    ctx->r8 = ADD32(ctx->r8, 0X4);
    // 0x80097C60: bne         $t0, $s0, L_80097BD0
    if (ctx->r8 != ctx->r16) {
        // 0x80097C64: addiu       $t1, $t1, 0x10
        ctx->r9 = ADD32(ctx->r9, 0X10);
            goto L_80097BD0;
    }
    // 0x80097C64: addiu       $t1, $t1, 0x10
    ctx->r9 = ADD32(ctx->r9, 0X10);
L_80097C68:
    // 0x80097C68: lw          $t8, 0x64($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X64);
L_80097C6C:
    // 0x80097C6C: or          $t0, $zero, $zero
    ctx->r8 = 0 | 0;
    // 0x80097C70: addiu       $v0, $sp, 0x40
    ctx->r2 = ADD32(ctx->r29, 0X40);
    // 0x80097C74: blez        $t8, L_80097E5C
    if (SIGNED(ctx->r24) <= 0) {
        // 0x80097C78: lui         $v1, 0x8022
        ctx->r3 = S32(0X8022 << 16);
            goto L_80097E5C;
    }
    // 0x80097C78: lui         $v1, 0x8022
    ctx->r3 = S32(0X8022 << 16);
    // 0x80097C7C: lui         $a3, 0x800E
    ctx->r7 = S32(0X800E << 16);
    // 0x80097C80: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x80097C84: addiu       $a2, $a2, -0x5470
    ctx->r6 = ADD32(ctx->r6, -0X5470);
    // 0x80097C88: addiu       $a3, $a3, -0x5440
    ctx->r7 = ADD32(ctx->r7, -0X5440);
    // 0x80097C8C: addiu       $v1, $v1, 0x7A60
    ctx->r3 = ADD32(ctx->r3, 0X7A60);
    // 0x80097C90: lw          $t2, 0x1C($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X1C);
    // 0x80097C94: addiu       $t1, $zero, 0x4
    ctx->r9 = ADD32(0, 0X4);
    // 0x80097C98: lw          $a0, 0x58($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X58);
L_80097C9C:
    // 0x80097C9C: sltiu       $at, $t2, 0x5
    ctx->r1 = ctx->r10 < 0X5 ? 1 : 0;
    // 0x80097CA0: beq         $at, $zero, L_80097D3C
    if (ctx->r1 == 0) {
        // 0x80097CA4: sll         $t9, $t2, 2
        ctx->r25 = S32(ctx->r10 << 2);
            goto L_80097D3C;
    }
    // 0x80097CA4: sll         $t9, $t2, 2
    ctx->r25 = S32(ctx->r10 << 2);
    // 0x80097CA8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80097CAC: addu        $at, $at, $t9
    gpr jr_addend_80097CB4 = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x80097CB0: lw          $t9, -0x4D00($at)
    ctx->r25 = ADD32(ctx->r1, -0X4D00);
    // 0x80097CB4: jr          $t9
    // 0x80097CB8: nop

    switch (jr_addend_80097CB4 >> 2) {
        case 0: goto L_80097CBC; break;
        case 1: goto L_80097CEC; break;
        case 2: goto L_80097D2C; break;
        case 3: goto L_80097D2C; break;
        case 4: goto L_80097CFC; break;
        default: switch_error(__func__, 0x80097CB4, 0x800EB300);
    }
    // 0x80097CB8: nop

L_80097CBC:
    // 0x80097CBC: bne         $t0, $zero, L_80097CCC
    if (ctx->r8 != 0) {
        // 0x80097CC0: addiu       $t7, $t0, -0x1
        ctx->r15 = ADD32(ctx->r8, -0X1);
            goto L_80097CCC;
    }
    // 0x80097CC0: addiu       $t7, $t0, -0x1
    ctx->r15 = ADD32(ctx->r8, -0X1);
    // 0x80097CC4: b           L_80097D3C
    // 0x80097CC8: lw          $a0, 0x0($a2)
    ctx->r4 = MEM_W(ctx->r6, 0X0);
        goto L_80097D3C;
    // 0x80097CC8: lw          $a0, 0x0($a2)
    ctx->r4 = MEM_W(ctx->r6, 0X0);
L_80097CCC:
    // 0x80097CCC: bgez        $t7, L_80097CDC
    if (SIGNED(ctx->r15) >= 0) {
        // 0x80097CD0: sra         $t6, $t7, 1
        ctx->r14 = S32(SIGNED(ctx->r15) >> 1);
            goto L_80097CDC;
    }
    // 0x80097CD0: sra         $t6, $t7, 1
    ctx->r14 = S32(SIGNED(ctx->r15) >> 1);
    // 0x80097CD4: addiu       $at, $t7, 0x1
    ctx->r1 = ADD32(ctx->r15, 0X1);
    // 0x80097CD8: sra         $t6, $at, 1
    ctx->r14 = S32(SIGNED(ctx->r1) >> 1);
L_80097CDC:
    // 0x80097CDC: sll         $t8, $t6, 2
    ctx->r24 = S32(ctx->r14 << 2);
    // 0x80097CE0: addu        $t9, $a2, $t8
    ctx->r25 = ADD32(ctx->r6, ctx->r24);
    // 0x80097CE4: b           L_80097D3C
    // 0x80097CE8: lw          $a0, 0x4($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X4);
        goto L_80097D3C;
    // 0x80097CE8: lw          $a0, 0x4($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X4);
L_80097CEC:
    // 0x80097CEC: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x80097CF0: addu        $t6, $a2, $t7
    ctx->r14 = ADD32(ctx->r6, ctx->r15);
    // 0x80097CF4: b           L_80097D3C
    // 0x80097CF8: lw          $a0, 0x0($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X0);
        goto L_80097D3C;
    // 0x80097CF8: lw          $a0, 0x0($t6)
    ctx->r4 = MEM_W(ctx->r14, 0X0);
L_80097CFC:
    // 0x80097CFC: slti        $at, $t0, 0x4
    ctx->r1 = SIGNED(ctx->r8) < 0X4 ? 1 : 0;
    // 0x80097D00: beq         $at, $zero, L_80097D14
    if (ctx->r1 == 0) {
        // 0x80097D04: sll         $t8, $t0, 2
        ctx->r24 = S32(ctx->r8 << 2);
            goto L_80097D14;
    }
    // 0x80097D04: sll         $t8, $t0, 2
    ctx->r24 = S32(ctx->r8 << 2);
    // 0x80097D08: addu        $t9, $a3, $t8
    ctx->r25 = ADD32(ctx->r7, ctx->r24);
    // 0x80097D0C: b           L_80097D3C
    // 0x80097D10: lw          $a0, 0x0($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X0);
        goto L_80097D3C;
    // 0x80097D10: lw          $a0, 0x0($t9)
    ctx->r4 = MEM_W(ctx->r25, 0X0);
L_80097D14:
    // 0x80097D14: bne         $t0, $t1, L_80097D24
    if (ctx->r8 != ctx->r9) {
        // 0x80097D18: nop
    
            goto L_80097D24;
    }
    // 0x80097D18: nop

    // 0x80097D1C: b           L_80097D3C
    // 0x80097D20: lw          $a0, 0x8($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X8);
        goto L_80097D3C;
    // 0x80097D20: lw          $a0, 0x8($a3)
    ctx->r4 = MEM_W(ctx->r7, 0X8);
L_80097D24:
    // 0x80097D24: b           L_80097D3C
    // 0x80097D28: lw          $a0, 0xC($a3)
    ctx->r4 = MEM_W(ctx->r7, 0XC);
        goto L_80097D3C;
    // 0x80097D28: lw          $a0, 0xC($a3)
    ctx->r4 = MEM_W(ctx->r7, 0XC);
L_80097D2C:
    // 0x80097D2C: sll         $t7, $t0, 2
    ctx->r15 = S32(ctx->r8 << 2);
    // 0x80097D30: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x80097D34: addu        $a0, $a0, $t7
    ctx->r4 = ADD32(ctx->r4, ctx->r15);
    // 0x80097D38: lw          $a0, -0x5460($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X5460);
L_80097D3C:
    // 0x80097D3C: lw          $t6, 0x0($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X0);
    // 0x80097D40: lw          $t9, 0x4($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X4);
    // 0x80097D44: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097D48: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097D4C: lw          $t6, 0x8($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X8);
    // 0x80097D50: lw          $t9, 0xC($v1)
    ctx->r25 = MEM_W(ctx->r3, 0XC);
    // 0x80097D54: sw          $t8, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r24;
    // 0x80097D58: sw          $t7, 0x4($v1)
    MEM_W(0X4, ctx->r3) = ctx->r15;
    // 0x80097D5C: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097D60: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097D64: lw          $t6, 0x10($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X10);
    // 0x80097D68: lw          $t9, 0x14($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X14);
    // 0x80097D6C: sw          $t8, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r24;
    // 0x80097D70: sw          $t7, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r15;
    // 0x80097D74: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097D78: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097D7C: lw          $t6, 0x18($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X18);
    // 0x80097D80: lw          $t9, 0x1C($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X1C);
    // 0x80097D84: sw          $t8, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r24;
    // 0x80097D88: sw          $t7, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r15;
    // 0x80097D8C: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097D90: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097D94: lw          $t6, 0x20($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X20);
    // 0x80097D98: lw          $t9, 0x24($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X24);
    // 0x80097D9C: sw          $t8, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r24;
    // 0x80097DA0: sw          $t7, 0x1C($v1)
    MEM_W(0X1C, ctx->r3) = ctx->r15;
    // 0x80097DA4: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097DA8: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097DAC: lw          $t6, 0x28($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X28);
    // 0x80097DB0: lw          $t9, 0x2C($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X2C);
    // 0x80097DB4: sw          $t8, 0x20($v1)
    MEM_W(0X20, ctx->r3) = ctx->r24;
    // 0x80097DB8: sw          $t7, 0x24($v1)
    MEM_W(0X24, ctx->r3) = ctx->r15;
    // 0x80097DBC: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097DC0: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097DC4: sw          $t8, 0x28($v1)
    MEM_W(0X28, ctx->r3) = ctx->r24;
    // 0x80097DC8: sw          $t7, 0x2C($v1)
    MEM_W(0X2C, ctx->r3) = ctx->r15;
    // 0x80097DCC: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
    // 0x80097DD0: beq         $a1, $zero, L_80097DE8
    if (ctx->r5 == 0) {
        // 0x80097DD4: nop
    
            goto L_80097DE8;
    }
    // 0x80097DD4: nop

    // 0x80097DD8: lw          $t6, 0x30($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X30);
    // 0x80097DDC: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097DE0: sw          $t8, 0x30($v1)
    MEM_W(0X30, ctx->r3) = ctx->r24;
    // 0x80097DE4: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
L_80097DE8:
    // 0x80097DE8: beq         $a1, $zero, L_80097E00
    if (ctx->r5 == 0) {
        // 0x80097DEC: nop
    
            goto L_80097E00;
    }
    // 0x80097DEC: nop

    // 0x80097DF0: lw          $t9, 0x34($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X34);
    // 0x80097DF4: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097DF8: sw          $t7, 0x34($v1)
    MEM_W(0X34, ctx->r3) = ctx->r15;
    // 0x80097DFC: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
L_80097E00:
    // 0x80097E00: beq         $a1, $zero, L_80097E18
    if (ctx->r5 == 0) {
        // 0x80097E04: nop
    
            goto L_80097E18;
    }
    // 0x80097E04: nop

    // 0x80097E08: lw          $t6, 0x38($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X38);
    // 0x80097E0C: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097E10: sw          $t8, 0x38($v1)
    MEM_W(0X38, ctx->r3) = ctx->r24;
    // 0x80097E14: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
L_80097E18:
    // 0x80097E18: beq         $a1, $zero, L_80097E30
    if (ctx->r5 == 0) {
        // 0x80097E1C: nop
    
            goto L_80097E30;
    }
    // 0x80097E1C: nop

    // 0x80097E20: lw          $t9, 0x3C($v1)
    ctx->r25 = MEM_W(ctx->r3, 0X3C);
    // 0x80097E24: addu        $t7, $t9, $a0
    ctx->r15 = ADD32(ctx->r25, ctx->r4);
    // 0x80097E28: sw          $t7, 0x3C($v1)
    MEM_W(0X3C, ctx->r3) = ctx->r15;
    // 0x80097E2C: lh          $a1, 0x0($v0)
    ctx->r5 = MEM_H(ctx->r2, 0X0);
L_80097E30:
    // 0x80097E30: beql        $a1, $zero, L_80097E48
    if (ctx->r5 == 0) {
        // 0x80097E34: lw          $t9, 0x64($sp)
        ctx->r25 = MEM_W(ctx->r29, 0X64);
            goto L_80097E48;
    }
    goto skip_14;
    // 0x80097E34: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    skip_14:
    // 0x80097E38: lw          $t6, 0x40($v1)
    ctx->r14 = MEM_W(ctx->r3, 0X40);
    // 0x80097E3C: addu        $t8, $t6, $a0
    ctx->r24 = ADD32(ctx->r14, ctx->r4);
    // 0x80097E40: sw          $t8, 0x40($v1)
    MEM_W(0X40, ctx->r3) = ctx->r24;
    // 0x80097E44: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
L_80097E48:
    // 0x80097E48: addiu       $t0, $t0, 0x1
    ctx->r8 = ADD32(ctx->r8, 0X1);
    // 0x80097E4C: addiu       $v0, $v0, 0x2
    ctx->r2 = ADD32(ctx->r2, 0X2);
    // 0x80097E50: bne         $t0, $t9, L_80097C9C
    if (ctx->r8 != ctx->r25) {
        // 0x80097E54: addiu       $v1, $v1, 0x44
        ctx->r3 = ADD32(ctx->r3, 0X44);
            goto L_80097C9C;
    }
    // 0x80097E54: addiu       $v1, $v1, 0x44
    ctx->r3 = ADD32(ctx->r3, 0X44);
    // 0x80097E58: sw          $a0, 0x58($sp)
    MEM_W(0X58, ctx->r29) = ctx->r4;
L_80097E5C:
    // 0x80097E5C: lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X4);
    // 0x80097E60: jr          $ra
    // 0x80097E64: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
    return;
    // 0x80097E64: addiu       $sp, $sp, 0x70
    ctx->r29 = ADD32(ctx->r29, 0X70);
;}
RECOMP_FUNC void func_80097E68(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80097E68: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80097E6C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80097E70: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80097E74: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80097E78: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80097E7C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80097E80: addiu       $s0, $s0, -0x54C8
    ctx->r16 = ADD32(ctx->r16, -0X54C8);
    // 0x80097E84: or          $s1, $zero, $zero
    ctx->r17 = 0 | 0;
    // 0x80097E88: addiu       $s2, $zero, 0x5
    ctx->r18 = ADD32(0, 0X5);
L_80097E8C:
    // 0x80097E8C: lh          $t6, 0x0($s0)
    ctx->r14 = MEM_H(ctx->r16, 0X0);
    // 0x80097E90: beql        $t6, $zero, L_80097EA8
    if (ctx->r14 == 0) {
        // 0x80097E94: addiu       $s1, $s1, 0x1
        ctx->r17 = ADD32(ctx->r17, 0X1);
            goto L_80097EA8;
    }
    goto skip_0;
    // 0x80097E94: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    skip_0:
    // 0x80097E98: sh          $zero, 0x0($s0)
    MEM_H(0X0, ctx->r16) = 0;
    // 0x80097E9C: jal         0x80095A28
    // 0x80097EA0: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    func_80095A28(rdram, ctx);
        goto after_0;
    // 0x80097EA0: lw          $a0, 0x4($s0)
    ctx->r4 = MEM_W(ctx->r16, 0X4);
    after_0:
    // 0x80097EA4: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
L_80097EA8:
    // 0x80097EA8: bne         $s1, $s2, L_80097E8C
    if (ctx->r17 != ctx->r18) {
        // 0x80097EAC: addiu       $s0, $s0, 0x8
        ctx->r16 = ADD32(ctx->r16, 0X8);
            goto L_80097E8C;
    }
    // 0x80097EAC: addiu       $s0, $s0, 0x8
    ctx->r16 = ADD32(ctx->r16, 0X8);
    // 0x80097EB0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80097EB4: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80097EB8: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80097EBC: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80097EC0: jr          $ra
    // 0x80097EC4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x80097EC4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_80097EC8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80097EC8: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x80097ECC: addiu       $a3, $a3, 0x40B8
    ctx->r7 = ADD32(ctx->r7, 0X40B8);
    // 0x80097ED0: lw          $t6, 0x8($a3)
    ctx->r14 = MEM_W(ctx->r7, 0X8);
    // 0x80097ED4: lw          $t7, 0x10($a3)
    ctx->r15 = MEM_W(ctx->r7, 0X10);
    // 0x80097ED8: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80097EDC: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80097EE0: slt         $at, $t6, $t7
    ctx->r1 = SIGNED(ctx->r14) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x80097EE4: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x80097EE8: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x80097EEC: bne         $at, $zero, L_80097F08
    if (ctx->r1 != 0) {
        // 0x80097EF0: sw          $a2, 0x30($sp)
        MEM_W(0X30, ctx->r29) = ctx->r6;
            goto L_80097F08;
    }
    // 0x80097EF0: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x80097EF4: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80097EF8: addiu       $a1, $a1, 0x1954
    ctx->r5 = ADD32(ctx->r5, 0X1954);
    // 0x80097EFC: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x80097F00: jal         0x800C5C60
    // 0x80097F04: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x80097F04: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_0:
L_80097F08:
    // 0x80097F08: lw          $a0, 0x2C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X2C);
    // 0x80097F0C: jal         0x800CA2C0
    // 0x80097F10: lw          $a1, 0x30($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X30);
    osInvalDCache_recomp(rdram, ctx);
        goto after_1;
    // 0x80097F10: lw          $a1, 0x30($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X30);
    after_1:
    // 0x80097F14: jal         0x800C9E20
    // 0x80097F18: lw          $a0, 0x2C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X2C);
    osPhysicalToVirtual(rdram, ctx);
        goto after_2;
    // 0x80097F18: lw          $a0, 0x2C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X2C);
    after_2:
    // 0x80097F1C: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x80097F20: lui         $t9, 0x8015
    ctx->r25 = S32(0X8015 << 16);
    // 0x80097F24: addiu       $t9, $t9, 0x40B8
    ctx->r25 = ADD32(ctx->r25, 0X40B8);
    // 0x80097F28: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80097F2C: addiu       $a0, $a0, 0x42A0
    ctx->r4 = ADD32(ctx->r4, 0X42A0);
    // 0x80097F30: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
    // 0x80097F34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x80097F38: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x80097F3C: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x80097F40: sw          $v0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r2;
    // 0x80097F44: jal         0x800CA370
    // 0x80097F48: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    osPiStartDma_recomp(rdram, ctx);
        goto after_3;
    // 0x80097F48: sw          $t8, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r24;
    after_3:
    // 0x80097F4C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80097F50: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80097F54: addiu       $a1, $a1, 0x1954
    ctx->r5 = ADD32(ctx->r5, 0X1954);
    // 0x80097F58: addiu       $a0, $a0, 0x40B8
    ctx->r4 = ADD32(ctx->r4, 0X40B8);
    // 0x80097F5C: jal         0x800C5C60
    // 0x80097F60: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_4;
    // 0x80097F60: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_4:
    // 0x80097F64: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80097F68: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x80097F6C: jr          $ra
    // 0x80097F70: nop

    return;
    // 0x80097F70: nop

;}
RECOMP_FUNC void func_80097F74(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80097F74: addiu       $a3, $zero, 0x2800
    ctx->r7 = ADD32(0, 0X2800);
    // 0x80097F78: divu        $zero, $a2, $a3
    lo = S32(U32(ctx->r6) / U32(ctx->r7)); hi = S32(U32(ctx->r6) % U32(ctx->r7));
    // 0x80097F7C: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x80097F80: sw          $s3, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r19;
    // 0x80097F84: mflo        $v0
    ctx->r2 = lo;
    // 0x80097F88: mfhi        $v1
    ctx->r3 = hi;
    // 0x80097F8C: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80097F90: sw          $s2, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r18;
    // 0x80097F94: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x80097F98: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x80097F9C: sw          $a0, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r4;
    // 0x80097FA0: sw          $a1, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r5;
    // 0x80097FA4: bne         $a3, $zero, L_80097FB0
    if (ctx->r7 != 0) {
        // 0x80097FA8: nop
    
            goto L_80097FB0;
    }
    // 0x80097FA8: nop

    // 0x80097FAC: break       7
    do_break(2148106156);
L_80097FB0:
    // 0x80097FB0: or          $s3, $v0, $zero
    ctx->r19 = ctx->r2 | 0;
    // 0x80097FB4: beq         $v1, $zero, L_80097FCC
    if (ctx->r3 == 0) {
        // 0x80097FB8: sw          $v1, 0x2C($sp)
        MEM_W(0X2C, ctx->r29) = ctx->r3;
            goto L_80097FCC;
    }
    // 0x80097FB8: sw          $v1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r3;
    // 0x80097FBC: sltiu       $at, $v1, 0x10
    ctx->r1 = ctx->r3 < 0X10 ? 1 : 0;
    // 0x80097FC0: beq         $at, $zero, L_80097FCC
    if (ctx->r1 == 0) {
        // 0x80097FC4: addiu       $t6, $zero, 0x10
        ctx->r14 = ADD32(0, 0X10);
            goto L_80097FCC;
    }
    // 0x80097FC4: addiu       $t6, $zero, 0x10
    ctx->r14 = ADD32(0, 0X10);
    // 0x80097FC8: sw          $t6, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r14;
L_80097FCC:
    // 0x80097FCC: blez        $v0, L_80098000
    if (SIGNED(ctx->r2) <= 0) {
        // 0x80097FD0: or          $s2, $zero, $zero
        ctx->r18 = 0 | 0;
            goto L_80098000;
    }
    // 0x80097FD0: or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // 0x80097FD4: blez        $v0, L_80098000
    if (SIGNED(ctx->r2) <= 0) {
        // 0x80097FD8: lw          $s0, 0x38($sp)
        ctx->r16 = MEM_W(ctx->r29, 0X38);
            goto L_80098000;
    }
    // 0x80097FD8: lw          $s0, 0x38($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X38);
    // 0x80097FDC: lw          $s1, 0x3C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X3C);
L_80097FE0:
    // 0x80097FE0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80097FE4: or          $a1, $s1, $zero
    ctx->r5 = ctx->r17 | 0;
    // 0x80097FE8: jal         0x80097EC8
    // 0x80097FEC: addiu       $a2, $zero, 0x2800
    ctx->r6 = ADD32(0, 0X2800);
    func_80097EC8(rdram, ctx);
        goto after_0;
    // 0x80097FEC: addiu       $a2, $zero, 0x2800
    ctx->r6 = ADD32(0, 0X2800);
    after_0:
    // 0x80097FF0: addiu       $s2, $s2, 0x1
    ctx->r18 = ADD32(ctx->r18, 0X1);
    // 0x80097FF4: addiu       $s0, $s0, 0x2800
    ctx->r16 = ADD32(ctx->r16, 0X2800);
    // 0x80097FF8: bne         $s2, $s3, L_80097FE0
    if (ctx->r18 != ctx->r19) {
        // 0x80097FFC: addiu       $s1, $s1, 0x2800
        ctx->r17 = ADD32(ctx->r17, 0X2800);
            goto L_80097FE0;
    }
    // 0x80097FFC: addiu       $s1, $s1, 0x2800
    ctx->r17 = ADD32(ctx->r17, 0X2800);
L_80098000:
    // 0x80098000: lw          $t7, 0x2C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X2C);
    // 0x80098004: sll         $v0, $s2, 2
    ctx->r2 = S32(ctx->r18 << 2);
    // 0x80098008: addu        $v0, $v0, $s2
    ctx->r2 = ADD32(ctx->r2, ctx->r18);
    // 0x8009800C: beq         $t7, $zero, L_8009802C
    if (ctx->r15 == 0) {
        // 0x80098010: sll         $v0, $v0, 11
        ctx->r2 = S32(ctx->r2 << 11);
            goto L_8009802C;
    }
    // 0x80098010: sll         $v0, $v0, 11
    ctx->r2 = S32(ctx->r2 << 11);
    // 0x80098014: lw          $t8, 0x38($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X38);
    // 0x80098018: lw          $t9, 0x3C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X3C);
    // 0x8009801C: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    // 0x80098020: addu        $a0, $t8, $v0
    ctx->r4 = ADD32(ctx->r24, ctx->r2);
    // 0x80098024: jal         0x80097EC8
    // 0x80098028: addu        $a1, $t9, $v0
    ctx->r5 = ADD32(ctx->r25, ctx->r2);
    func_80097EC8(rdram, ctx);
        goto after_1;
    // 0x80098028: addu        $a1, $t9, $v0
    ctx->r5 = ADD32(ctx->r25, ctx->r2);
    after_1:
L_8009802C:
    // 0x8009802C: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80098030: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x80098034: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x80098038: lw          $s2, 0x1C($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X1C);
    // 0x8009803C: lw          $s3, 0x20($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X20);
    // 0x80098040: jr          $ra
    // 0x80098044: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    return;
    // 0x80098044: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
;}
RECOMP_FUNC void func_80098048(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098048: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009804C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80098050: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x80098054: bne         $a0, $zero, L_80098064
    if (ctx->r4 != 0) {
        // 0x80098058: or          $a3, $a0, $zero
        ctx->r7 = ctx->r4 | 0;
            goto L_80098064;
    }
    // 0x80098058: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x8009805C: b           L_80098068
    // 0x80098060: addiu       $v1, $zero, 0x10
    ctx->r3 = ADD32(0, 0X10);
        goto L_80098068;
    // 0x80098060: addiu       $v1, $zero, 0x10
    ctx->r3 = ADD32(0, 0X10);
L_80098064:
    // 0x80098064: addiu       $v1, $zero, 0xF
    ctx->r3 = ADD32(0, 0XF);
L_80098068:
    // 0x80098068: lw          $t8, 0x1C($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X1C);
    // 0x8009806C: sll         $a2, $v1, 2
    ctx->r6 = S32(ctx->r3 << 2);
    // 0x80098070: subu        $a2, $a2, $v1
    ctx->r6 = SUB32(ctx->r6, ctx->r3);
    // 0x80098074: sll         $a2, $a2, 2
    ctx->r6 = S32(ctx->r6 << 2);
    // 0x80098078: multu       $a2, $t8
    result = U64(U32(ctx->r6)) * U64(U32(ctx->r24)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009807C: sll         $t6, $a3, 2
    ctx->r14 = S32(ctx->r7 << 2);
    // 0x80098080: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x80098084: addu        $v0, $v0, $t6
    ctx->r2 = ADD32(ctx->r2, ctx->r14);
    // 0x80098088: lw          $v0, -0x56E0($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X56E0);
    // 0x8009808C: lui         $at, 0xFF
    ctx->r1 = S32(0XFF << 16);
    // 0x80098090: ori         $at, $at, 0xFFFF
    ctx->r1 = ctx->r1 | 0XFFFF;
    // 0x80098094: lui         $t1, 0x16
    ctx->r9 = S32(0X16 << 16);
    // 0x80098098: and         $t7, $v0, $at
    ctx->r15 = ctx->r2 & ctx->r1;
    // 0x8009809C: addiu       $t1, $t1, 0x5C00
    ctx->r9 = ADD32(ctx->r9, 0X5C00);
    // 0x800980A0: mflo        $t9
    ctx->r25 = lo;
    // 0x800980A4: addu        $t0, $t7, $t9
    ctx->r8 = ADD32(ctx->r15, ctx->r25);
    // 0x800980A8: lui         $a1, 0x801D
    ctx->r5 = S32(0X801D << 16);
    // 0x800980AC: addiu       $a1, $a1, -0x1648
    ctx->r5 = ADD32(ctx->r5, -0X1648);
    // 0x800980B0: jal         0x80097EC8
    // 0x800980B4: addu        $a0, $t0, $t1
    ctx->r4 = ADD32(ctx->r8, ctx->r9);
    func_80097EC8(rdram, ctx);
        goto after_0;
    // 0x800980B4: addu        $a0, $t0, $t1
    ctx->r4 = ADD32(ctx->r8, ctx->r9);
    after_0:
    // 0x800980B8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800980BC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800980C0: jr          $ra
    // 0x800980C4: nop

    return;
    // 0x800980C4: nop

;}
RECOMP_FUNC void func_800980C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800980C8: jr          $ra
    // 0x800980CC: nop

    return;
    // 0x800980CC: nop

;}
RECOMP_FUNC void func_800980D0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800980D0: lui         $v1, 0x8015
    ctx->r3 = S32(0X8015 << 16);
    // 0x800980D4: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x800980D8: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800980DC: addiu       $a3, $a3, 0x42CC
    ctx->r7 = ADD32(ctx->r7, 0X42CC);
    // 0x800980E0: addiu       $v1, $v1, 0x42C0
    ctx->r3 = ADD32(ctx->r3, 0X42C0);
    // 0x800980E4: ori         $a1, $zero, 0x9600
    ctx->r5 = 0 | 0X9600;
    // 0x800980E8: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
L_800980EC:
    // 0x800980EC: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
L_800980F0:
    // 0x800980F0: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    // 0x800980F4: sw          $zero, 0x0($v0)
    MEM_W(0X0, ctx->r2) = 0;
    // 0x800980F8: sw          $zero, 0x4($v0)
    MEM_W(0X4, ctx->r2) = 0;
    // 0x800980FC: sw          $zero, 0x8($v0)
    MEM_W(0X8, ctx->r2) = 0;
    // 0x80098100: sw          $zero, 0xC($v0)
    MEM_W(0XC, ctx->r2) = 0;
    // 0x80098104: bne         $a0, $a1, L_800980F0
    if (ctx->r4 != ctx->r5) {
        // 0x80098108: addiu       $v0, $v0, 0x10
        ctx->r2 = ADD32(ctx->r2, 0X10);
            goto L_800980F0;
    }
    // 0x80098108: addiu       $v0, $v0, 0x10
    ctx->r2 = ADD32(ctx->r2, 0X10);
    // 0x8009810C: addiu       $v1, $v1, 0x4
    ctx->r3 = ADD32(ctx->r3, 0X4);
    // 0x80098110: sltu        $at, $v1, $a3
    ctx->r1 = ctx->r3 < ctx->r7 ? 1 : 0;
    // 0x80098114: bnel        $at, $zero, L_800980EC
    if (ctx->r1 != 0) {
        // 0x80098118: lw          $v0, 0x0($v1)
        ctx->r2 = MEM_W(ctx->r3, 0X0);
            goto L_800980EC;
    }
    goto skip_0;
    // 0x80098118: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    skip_0:
    // 0x8009811C: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80098120: addiu       $v1, $v1, -0x3138
    ctx->r3 = ADD32(ctx->r3, -0X3138);
    // 0x80098124: ori         $a1, $zero, 0xB980
    ctx->r5 = 0 | 0XB980;
    // 0x80098128: addiu       $t0, $zero, 0x80
    ctx->r8 = ADD32(0, 0X80);
L_8009812C:
    // 0x8009812C: addiu       $a3, $zero, 0x20
    ctx->r7 = ADD32(0, 0X20);
    // 0x80098130: addu        $v0, $a2, $a1
    ctx->r2 = ADD32(ctx->r6, ctx->r5);
L_80098134:
    // 0x80098134: addiu       $v0, $v0, 0x128
    ctx->r2 = ADD32(ctx->r2, 0X128);
L_80098138:
    // 0x80098138: ld          $t7, 0x0($v1)
    ctx->r15 = LD(ctx->r3, 0X0);
    // 0x8009813C: sd          $t7, 0x0($v0)
    SD(ctx->r15, 0X0, ctx->r2);
L_80098140:
    // 0x80098140: addiu       $v1, $v1, 0x8
    ctx->r3 = ADD32(ctx->r3, 0X8);
    // 0x80098144: addiu       $v0, $v0, 0x8
    ctx->r2 = ADD32(ctx->r2, 0X8);
    // 0x80098148: addiu       $a3, $a3, -0x1
    ctx->r7 = ADD32(ctx->r7, -0X1);
    // 0x8009814C: bne         $a3, $zero, L_80098138
    if (ctx->r7 != 0) {
        // 0x80098150: nop
    
            goto L_80098138;
    }
    // 0x80098150: nop

    // 0x80098154: addiu       $t0, $t0, -0x1
    ctx->r8 = ADD32(ctx->r8, -0X1);
    // 0x80098158: bne         $t0, $zero, L_8009812C
    if (ctx->r8 != 0) {
        // 0x8009815C: addiu       $a1, $a1, 0x350
        ctx->r5 = ADD32(ctx->r5, 0X350);
            goto L_8009812C;
    }
    // 0x8009815C: addiu       $a1, $a1, 0x350
    ctx->r5 = ADD32(ctx->r5, 0X350);
    // 0x80098160: j           L_8009817C
    // 0x80098164: nop

        goto L_8009817C;
    // 0x80098164: nop

    // 0x80098168: bne         $a0, $a3, L_80098140
    if (ctx->r4 != ctx->r7) {
        // 0x8009816C: sh          $t1, -0x2($v0)
        MEM_H(-0X2, ctx->r2) = ctx->r9;
            goto L_80098140;
    }
    // 0x8009816C: sh          $t1, -0x2($v0)
    MEM_H(-0X2, ctx->r2) = ctx->r9;
    // 0x80098170: addiu       $a1, $a1, 0x140
    ctx->r5 = ADD32(ctx->r5, 0X140);
    // 0x80098174: bnel        $a1, $t0, L_80098134
    if (ctx->r5 != ctx->r8) {
        // 0x80098178: sll         $t6, $a1, 1
        ctx->r14 = S32(ctx->r5 << 1);
            goto L_80098134;
    }
    goto skip_1;
    // 0x80098178: sll         $t6, $a1, 1
    ctx->r14 = S32(ctx->r5 << 1);
    skip_1:
L_8009817C:
    // 0x8009817C: jr          $ra
    // 0x80098180: nop

    // Identify this completed CPU-written image before the native VI swap.
    // Presentation keeps its established 16:9 proportions on wider windows.
    { extern void wr64_note_cpu_boot_logo(uint8_t*, uint32_t); wr64_note_cpu_boot_logo(rdram, (uint32_t)ctx->r6); }
    return;
    // 0x80098180: nop

    // 0x80098184: nop

    // 0x80098188: nop

    // 0x8009818C: nop

;}
RECOMP_FUNC void GameLoad_LoadCodeseg(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098190: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80098194: lui         $a0, 0x801E
    ctx->r4 = S32(0X801E << 16);
    // 0x80098198: lui         $t6, 0x8020
    ctx->r14 = S32(0X8020 << 16);
    // 0x8009819C: addiu       $a0, $a0, -0x5060
    ctx->r4 = ADD32(ctx->r4, -0X5060);
    // 0x800981A0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800981A4: addiu       $t6, $t6, -0x37C0
    ctx->r14 = ADD32(ctx->r14, -0X37C0);
    // 0x800981A8: jal         0x800CA480
    // 0x800981AC: subu        $a1, $t6, $a0
    ctx->r5 = SUB32(ctx->r14, ctx->r4);
    osInvalICache_recomp(rdram, ctx);
        goto after_0;
    // 0x800981AC: subu        $a1, $t6, $a0
    ctx->r5 = SUB32(ctx->r14, ctx->r4);
    after_0:
    // 0x800981B0: lui         $a0, 0xB
    ctx->r4 = S32(0XB << 16);
    // 0x800981B4: lui         $t7, 0xF
    ctx->r15 = S32(0XF << 16);
    // 0x800981B8: addiu       $a0, $a0, -0x6A30
    ctx->r4 = ADD32(ctx->r4, -0X6A30);
    // 0x800981BC: addiu       $t7, $t7, 0x6090
    ctx->r15 = ADD32(ctx->r15, 0X6090);
    // 0x800981C0: subu        $a2, $t7, $a0
    ctx->r6 = SUB32(ctx->r15, ctx->r4);
    // 0x800981C4: addiu       $a2, $a2, 0xF
    ctx->r6 = ADD32(ctx->r6, 0XF);
    // 0x800981C8: addiu       $at, $zero, -0x10
    ctx->r1 = ADD32(0, -0X10);
    // 0x800981CC: and         $t8, $a2, $at
    ctx->r24 = ctx->r6 & ctx->r1;
    // 0x800981D0: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800981D4: lw          $a1, 0x196C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X196C);
    // 0x800981D8: jal         0x80097EC8
    // 0x800981DC: or          $a2, $t8, $zero
    ctx->r6 = ctx->r24 | 0;
    func_80097EC8(rdram, ctx);
        goto after_1;
    // 0x800981DC: or          $a2, $t8, $zero
    ctx->r6 = ctx->r24 | 0;
    after_1:
    // 0x800981E0: lui         $a0, 0x8022
    ctx->r4 = S32(0X8022 << 16);
    // 0x800981E4: lui         $t9, 0x8023
    ctx->r25 = S32(0X8023 << 16);
    // 0x800981E8: addiu       $a0, $a0, 0x7A60
    ctx->r4 = ADD32(ctx->r4, 0X7A60);
    // 0x800981EC: addiu       $t9, $t9, -0x71F0
    ctx->r25 = ADD32(ctx->r25, -0X71F0);
    // 0x800981F0: jal         0x800CA500
    // 0x800981F4: subu        $a1, $t9, $a0
    ctx->r5 = SUB32(ctx->r25, ctx->r4);
    bzero_recomp(rdram, ctx);
        goto after_2;
    // 0x800981F4: subu        $a1, $t9, $a0
    ctx->r5 = SUB32(ctx->r25, ctx->r4);
    after_2:
    // 0x800981F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800981FC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80098200: jr          $ra
    // 0x80098204: nop

    return;
    // 0x80098204: nop

;}
