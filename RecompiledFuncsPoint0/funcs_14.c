#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void func_800C1F30(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1F30: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1F34: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1F38: jal         0x800C1B98
    // 0x800C1F3C: nop

    func_800C1B98(rdram, ctx);
        goto after_0;
    // 0x800C1F3C: nop

    after_0:
    // 0x800C1F40: jal         0x800BFD34
    // 0x800C1F44: nop

    func_800BFD34(rdram, ctx);
        goto after_1;
    // 0x800C1F44: nop

    after_1:
    // 0x800C1F48: jal         0x800BFD68
    // 0x800C1F4C: nop

    func_800BFD68(rdram, ctx);
        goto after_2;
    // 0x800C1F4C: nop

    after_2:
    // 0x800C1F50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C1F54: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C1F58: jr          $ra
    // 0x800C1F5C: nop

    return;
    // 0x800C1F5C: nop

;}
RECOMP_FUNC void func_800C1F60(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C1F60: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1F64: sw          $zero, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = 0;
    // 0x800C1F68: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1F6C: sw          $zero, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = 0;
    // 0x800C1F70: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C1F74: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C1F78: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C1F7C: sw          $zero, 0x7CEC($at)
    MEM_W(0X7CEC, ctx->r1) = 0;
    // 0x800C1F80: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C1F84: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C1F88: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C1F8C: bne         $t6, $at, L_800C2014
    if (ctx->r14 != ctx->r1) {
        // 0x800C1F90: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_800C2014;
    }
    // 0x800C1F90: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C1F94: jal         0x800C1F30
    // 0x800C1F98: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800C1F30(rdram, ctx);
        goto after_0;
    // 0x800C1F98: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800C1F9C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1FA0: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C1FA4: jal         0x800C538C
    // 0x800C1FA8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_1;
    // 0x800C1FA8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_1:
    // 0x800C1FAC: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1FB0: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C1FB4: jal         0x800C538C
    // 0x800C1FB8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_2;
    // 0x800C1FB8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_2:
    // 0x800C1FBC: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1FC0: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C1FC4: jal         0x800C538C
    // 0x800C1FC8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_3;
    // 0x800C1FC8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_3:
    // 0x800C1FCC: lw          $t7, 0x18($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X18);
    // 0x800C1FD0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C1FD4: beq         $t7, $at, L_800C1FF0
    if (ctx->r15 == ctx->r1) {
        // 0x800C1FD8: addiu       $at, $zero, 0x6
        ctx->r1 = ADD32(0, 0X6);
            goto L_800C1FF0;
    }
    // 0x800C1FD8: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800C1FDC: beq         $t7, $at, L_800C1FF0
    if (ctx->r15 == ctx->r1) {
        // 0x800C1FE0: lui         $a0, 0x100
        ctx->r4 = S32(0X100 << 16);
            goto L_800C1FF0;
    }
    // 0x800C1FE0: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C1FE4: ori         $a0, $a0, 0xC00
    ctx->r4 = ctx->r4 | 0XC00;
    // 0x800C1FE8: jal         0x800C538C
    // 0x800C1FEC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_4;
    // 0x800C1FEC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_4:
L_800C1FF0:
    // 0x800C1FF0: jal         0x800C1A20
    // 0x800C1FF4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1A20(rdram, ctx);
        goto after_5;
    // 0x800C1FF4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_5:
    // 0x800C1FF8: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C1FFC: lw          $t8, 0x7DC0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7DC0);
    // 0x800C2000: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C2004: bne         $a1, $t8, L_800C2014
    if (ctx->r5 != ctx->r24) {
        // 0x800C2008: nop
    
            goto L_800C2014;
    }
    // 0x800C2008: nop

    // 0x800C200C: jal         0x800C1A20
    // 0x800C2010: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    func_800C1A20(rdram, ctx);
        goto after_6;
    // 0x800C2010: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    after_6:
L_800C2014:
    // 0x800C2014: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C2018: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C201C: lb          $v0, 0x7C94($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7C94);
    // 0x800C2020: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C2024: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C2028: bne         $a0, $v0, L_800C203C
    if (ctx->r4 != ctx->r2) {
        // 0x800C202C: addiu       $v1, $v1, 0x7DF4
        ctx->r3 = ADD32(ctx->r3, 0X7DF4);
            goto L_800C203C;
    }
    // 0x800C202C: addiu       $v1, $v1, 0x7DF4
    ctx->r3 = ADD32(ctx->r3, 0X7DF4);
    // 0x800C2030: beq         $a0, $a1, L_800C21E4
    if (ctx->r4 == ctx->r5) {
        // 0x800C2034: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_800C21E4;
    }
    // 0x800C2034: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800C2038: beq         $a0, $at, L_800C21E4
    if (ctx->r4 == ctx->r1) {
        // 0x800C203C: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_800C21E4;
    }
L_800C203C:
    // 0x800C203C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2040: sw          $zero, 0x7CE4($at)
    MEM_W(0X7CE4, ctx->r1) = 0;
    // 0x800C2044: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2048: sb          $zero, 0x7DF2($at)
    MEM_B(0X7DF2, ctx->r1) = 0;
    // 0x800C204C: sltiu       $at, $a0, 0xD
    ctx->r1 = ctx->r4 < 0XD ? 1 : 0;
    // 0x800C2050: sb          $zero, 0x2($v1)
    MEM_B(0X2, ctx->r3) = 0;
    // 0x800C2054: beq         $at, $zero, L_800C21E4
    if (ctx->r1 == 0) {
        // 0x800C2058: sb          $zero, 0x3($v1)
        MEM_B(0X3, ctx->r3) = 0;
            goto L_800C21E4;
    }
    // 0x800C2058: sb          $zero, 0x3($v1)
    MEM_B(0X3, ctx->r3) = 0;
    // 0x800C205C: sll         $t9, $a0, 2
    ctx->r25 = S32(ctx->r4 << 2);
    // 0x800C2060: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C2064: addu        $at, $at, $t9
    gpr jr_addend_800C206C = ctx->r25;
    ctx->r1 = ADD32(ctx->r1, ctx->r25);
    // 0x800C2068: lw          $t9, -0x3C54($at)
    ctx->r25 = ADD32(ctx->r1, -0X3C54);
    // 0x800C206C: jr          $t9
    // 0x800C2070: nop

    switch (jr_addend_800C206C >> 2) {
        case 0: goto L_800C2074; break;
        case 1: goto L_800C20D0; break;
        case 2: goto L_800C20FC; break;
        case 3: goto L_800C2114; break;
        case 4: goto L_800C21E4; break;
        case 5: goto L_800C2138; break;
        case 6: goto L_800C21E4; break;
        case 7: goto L_800C2150; break;
        case 8: goto L_800C21E4; break;
        case 9: goto L_800C209C; break;
        case 10: goto L_800C2168; break;
        case 11: goto L_800C2190; break;
        case 12: goto L_800C21B8; break;
        default: switch_error(__func__, 0x800C206C, 0x800EC3AC);
    }
    // 0x800C2070: nop

L_800C2074:
    // 0x800C2074: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2078: sw          $zero, 0x7CB8($at)
    MEM_W(0X7CB8, ctx->r1) = 0;
    // 0x800C207C: jal         0x800C1650
    // 0x800C2080: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1650(rdram, ctx);
        goto after_7;
    // 0x800C2080: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_7:
    // 0x800C2084: jal         0x800C1674
    // 0x800C2088: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_8;
    // 0x800C2088: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_8:
    // 0x800C208C: jal         0x800C1608
    // 0x800C2090: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1608(rdram, ctx);
        goto after_9;
    // 0x800C2090: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_9:
    // 0x800C2094: b           L_800C21E8
    // 0x800C2098: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C2098: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C209C:
    // 0x800C209C: bne         $v0, $zero, L_800C20AC
    if (ctx->r2 != 0) {
        // 0x800C20A0: nop
    
            goto L_800C20AC;
    }
    // 0x800C20A0: nop

    // 0x800C20A4: jal         0x800C1650
    // 0x800C20A8: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1650(rdram, ctx);
        goto after_10;
    // 0x800C20A8: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_10:
L_800C20AC:
    // 0x800C20AC: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800C20B0: lw          $t0, 0x7DCC($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7DCC);
    // 0x800C20B4: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    // 0x800C20B8: beql        $t0, $at, L_800C21E8
    if (ctx->r8 == ctx->r1) {
        // 0x800C20BC: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C21E8;
    }
    goto skip_0;
    // 0x800C20BC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C20C0: jal         0x800C1674
    // 0x800C20C4: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_11;
    // 0x800C20C4: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_11:
    // 0x800C20C8: b           L_800C21E8
    // 0x800C20CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C20CC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C20D0:
    // 0x800C20D0: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800C20D4: beql        $v0, $at, L_800C21E8
    if (ctx->r2 == ctx->r1) {
        // 0x800C20D8: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C21E8;
    }
    goto skip_1;
    // 0x800C20D8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x800C20DC: jal         0x800C1650
    // 0x800C20E0: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1650(rdram, ctx);
        goto after_12;
    // 0x800C20E0: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_12:
    // 0x800C20E4: jal         0x800C1674
    // 0x800C20E8: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_13;
    // 0x800C20E8: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_13:
    // 0x800C20EC: jal         0x800C1608
    // 0x800C20F0: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1608(rdram, ctx);
        goto after_14;
    // 0x800C20F0: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_14:
    // 0x800C20F4: b           L_800C21E8
    // 0x800C20F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C20F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C20FC:
    // 0x800C20FC: jal         0x800C1674
    // 0x800C2100: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_15;
    // 0x800C2100: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_15:
    // 0x800C2104: jal         0x800C1608
    // 0x800C2108: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1608(rdram, ctx);
        goto after_16;
    // 0x800C2108: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_16:
    // 0x800C210C: b           L_800C21E8
    // 0x800C2110: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C2110: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2114:
    // 0x800C2114: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C2118: lw          $t1, 0x7DC8($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X7DC8);
    // 0x800C211C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C2120: bnel        $t1, $at, L_800C21E8
    if (ctx->r9 != ctx->r1) {
        // 0x800C2124: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C21E8;
    }
    goto skip_2;
    // 0x800C2124: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x800C2128: jal         0x800C1674
    // 0x800C212C: addiu       $a0, $zero, 0x140
    ctx->r4 = ADD32(0, 0X140);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_17;
    // 0x800C212C: addiu       $a0, $zero, 0x140
    ctx->r4 = ADD32(0, 0X140);
    after_17:
    // 0x800C2130: b           L_800C21E8
    // 0x800C2134: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C2134: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2138:
    // 0x800C2138: jal         0x800C1608
    // 0x800C213C: addiu       $a0, $zero, 0x46
    ctx->r4 = ADD32(0, 0X46);
    func_800C1608(rdram, ctx);
        goto after_18;
    // 0x800C213C: addiu       $a0, $zero, 0x46
    ctx->r4 = ADD32(0, 0X46);
    after_18:
    // 0x800C2140: jal         0x800C1674
    // 0x800C2144: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_19;
    // 0x800C2144: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_19:
    // 0x800C2148: b           L_800C21E8
    // 0x800C214C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C214C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2150:
    // 0x800C2150: jal         0x800C162C
    // 0x800C2154: addiu       $a0, $zero, 0x8C
    ctx->r4 = ADD32(0, 0X8C);
    func_800C162C(rdram, ctx);
        goto after_20;
    // 0x800C2154: addiu       $a0, $zero, 0x8C
    ctx->r4 = ADD32(0, 0X8C);
    after_20:
    // 0x800C2158: jal         0x800C1650
    // 0x800C215C: addiu       $a0, $zero, 0x8C
    ctx->r4 = ADD32(0, 0X8C);
    func_800C1650(rdram, ctx);
        goto after_21;
    // 0x800C215C: addiu       $a0, $zero, 0x8C
    ctx->r4 = ADD32(0, 0X8C);
    after_21:
    // 0x800C2160: b           L_800C21E8
    // 0x800C2164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C2164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2168:
    // 0x800C2168: beql        $a1, $v0, L_800C21E8
    if (ctx->r5 == ctx->r2) {
        // 0x800C216C: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C21E8;
    }
    goto skip_3;
    // 0x800C216C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_3:
    // 0x800C2170: jal         0x800C1650
    // 0x800C2174: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1650(rdram, ctx);
        goto after_22;
    // 0x800C2174: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_22:
    // 0x800C2178: jal         0x800C1674
    // 0x800C217C: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_23;
    // 0x800C217C: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_23:
    // 0x800C2180: jal         0x800C1608
    // 0x800C2184: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1608(rdram, ctx);
        goto after_24;
    // 0x800C2184: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_24:
    // 0x800C2188: b           L_800C21E8
    // 0x800C218C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C218C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2190:
    // 0x800C2190: jal         0x800C162C
    // 0x800C2194: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    func_800C162C(rdram, ctx);
        goto after_25;
    // 0x800C2194: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    after_25:
    // 0x800C2198: jal         0x800C1650
    // 0x800C219C: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    func_800C1650(rdram, ctx);
        goto after_26;
    // 0x800C219C: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    after_26:
    // 0x800C21A0: jal         0x800C1674
    // 0x800C21A4: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_27;
    // 0x800C21A4: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    after_27:
    // 0x800C21A8: jal         0x800C1608
    // 0x800C21AC: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    func_800C1608(rdram, ctx);
        goto after_28;
    // 0x800C21AC: addiu       $a0, $zero, 0x258
    ctx->r4 = ADD32(0, 0X258);
    after_28:
    // 0x800C21B0: b           L_800C21E8
    // 0x800C21B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C21E8;
    // 0x800C21B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C21B8:
    // 0x800C21B8: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C21BC: bnel        $v0, $at, L_800C21E8
    if (ctx->r2 != ctx->r1) {
        // 0x800C21C0: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C21E8;
    }
    goto skip_4;
    // 0x800C21C0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x800C21C4: jal         0x800C162C
    // 0x800C21C8: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    func_800C162C(rdram, ctx);
        goto after_29;
    // 0x800C21C8: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    after_29:
    // 0x800C21CC: jal         0x800C1650
    // 0x800C21D0: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    func_800C1650(rdram, ctx);
        goto after_30;
    // 0x800C21D0: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    after_30:
    // 0x800C21D4: jal         0x800C1674
    // 0x800C21D8: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_31;
    // 0x800C21D8: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    after_31:
    // 0x800C21DC: jal         0x800C1608
    // 0x800C21E0: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    func_800C1608(rdram, ctx);
        goto after_32;
    // 0x800C21E0: addiu       $a0, $zero, 0x12C
    ctx->r4 = ADD32(0, 0X12C);
    after_32:
L_800C21E4:
    // 0x800C21E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C21E8:
    // 0x800C21E8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C21EC: jr          $ra
    // 0x800C21F0: nop

    return;
    // 0x800C21F0: nop

;}
RECOMP_FUNC void func_800C21F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C21F4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C21F8: sw          $zero, 0x7CE0($at)
    MEM_W(0X7CE0, ctx->r1) = 0;
    // 0x800C21FC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2200: sw          $zero, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = 0;
    // 0x800C2204: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2208: sw          $zero, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = 0;
    // 0x800C220C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2210: sw          $zero, 0x7CD4($at)
    MEM_W(0X7CD4, ctx->r1) = 0;
    // 0x800C2214: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2218: sw          $zero, 0x7CA0($at)
    MEM_W(0X7CA0, ctx->r1) = 0;
    // 0x800C221C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2220: sw          $zero, 0x7CEC($at)
    MEM_W(0X7CEC, ctx->r1) = 0;
    // 0x800C2224: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2228: sw          $zero, 0x7CA8($at)
    MEM_W(0X7CA8, ctx->r1) = 0;
    // 0x800C222C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2230: sw          $zero, 0x7DD0($at)
    MEM_W(0X7DD0, ctx->r1) = 0;
    // 0x800C2234: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2238: sw          $zero, 0x7CF0($at)
    MEM_W(0X7CF0, ctx->r1) = 0;
    // 0x800C223C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2240: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2244: sw          $zero, 0x7CF4($at)
    MEM_W(0X7CF4, ctx->r1) = 0;
    // 0x800C2248: addiu       $v0, $v0, 0x7DF4
    ctx->r2 = ADD32(ctx->r2, 0X7DF4);
    // 0x800C224C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C2250: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C2254: sb          $zero, 0x2($v0)
    MEM_B(0X2, ctx->r2) = 0;
    // 0x800C2258: sb          $zero, 0x3($v0)
    MEM_B(0X3, ctx->r2) = 0;
    // 0x800C225C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2260: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800C2264: sw          $zero, 0x7CB0($at)
    MEM_W(0X7CB0, ctx->r1) = 0;
    // 0x800C2268: jal         0x800C16F0
    // 0x800C226C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    func_800C16F0(rdram, ctx);
        goto after_0;
    // 0x800C226C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    after_0:
    // 0x800C2270: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C2274: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x800C2278: lb          $v0, 0x7C94($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7C94);
    // 0x800C227C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800C2280: bne         $a0, $v0, L_800C2294
    if (ctx->r4 != ctx->r2) {
        // 0x800C2284: nop
    
            goto L_800C2294;
    }
    // 0x800C2284: nop

    // 0x800C2288: beq         $a0, $a2, L_800C2EDC
    if (ctx->r4 == ctx->r6) {
        // 0x800C228C: addiu       $at, $zero, 0xA
        ctx->r1 = ADD32(0, 0XA);
            goto L_800C2EDC;
    }
    // 0x800C228C: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800C2290: beq         $a0, $at, L_800C2EDC
    if (ctx->r4 == ctx->r1) {
        // 0x800C2294: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_800C2EDC;
    }
L_800C2294:
    // 0x800C2294: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2298: sb          $a0, 0x7C94($at)
    MEM_B(0X7C94, ctx->r1) = ctx->r4;
    // 0x800C229C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x800C22A0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C22A4: sw          $a2, 0x7CBC($at)
    MEM_W(0X7CBC, ctx->r1) = ctx->r6;
    // 0x800C22A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C22AC: sw          $a2, 0x7CC0($at)
    MEM_W(0X7CC0, ctx->r1) = ctx->r6;
    // 0x800C22B0: slti        $at, $a0, 0xD
    ctx->r1 = SIGNED(ctx->r4) < 0XD ? 1 : 0;
    // 0x800C22B4: bne         $at, $zero, L_800C22D0
    if (ctx->r1 != 0) {
        // 0x800C22B8: or          $v1, $v0, $zero
        ctx->r3 = ctx->r2 | 0;
            goto L_800C22D0;
    }
    // 0x800C22B8: or          $v1, $v0, $zero
    ctx->r3 = ctx->r2 | 0;
    // 0x800C22BC: addiu       $at, $zero, 0xFF
    ctx->r1 = ADD32(0, 0XFF);
    // 0x800C22C0: beq         $a0, $at, L_800C2E84
    if (ctx->r4 == ctx->r1) {
        // 0x800C22C4: nop
    
            goto L_800C2E84;
    }
    // 0x800C22C4: nop

    // 0x800C22C8: b           L_800C2E8C
    // 0x800C22CC: nop

        goto L_800C2E8C;
    // 0x800C22CC: nop

L_800C22D0:
    // 0x800C22D0: sltiu       $at, $a0, 0xD
    ctx->r1 = ctx->r4 < 0XD ? 1 : 0;
    // 0x800C22D4: beq         $at, $zero, L_800C2E8C
    if (ctx->r1 == 0) {
        // 0x800C22D8: sll         $t6, $a0, 2
        ctx->r14 = S32(ctx->r4 << 2);
            goto L_800C2E8C;
    }
    // 0x800C22D8: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800C22DC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C22E0: addu        $at, $at, $t6
    gpr jr_addend_800C22E8 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800C22E4: lw          $t6, -0x3C20($at)
    ctx->r14 = ADD32(ctx->r1, -0X3C20);
    // 0x800C22E8: jr          $t6
    // 0x800C22EC: nop

    switch (jr_addend_800C22E8 >> 2) {
        case 0: goto L_800C22F0; break;
        case 1: goto L_800C2414; break;
        case 2: goto L_800C24E4; break;
        case 3: goto L_800C2620; break;
        case 4: goto L_800C26A0; break;
        case 5: goto L_800C26F4; break;
        case 6: goto L_800C2AD0; break;
        case 7: goto L_800C2714; break;
        case 8: goto L_800C2D90; break;
        case 9: goto L_800C23E4; break;
        case 10: goto L_800C24A0; break;
        case 11: goto L_800C2DAC; break;
        case 12: goto L_800C2E54; break;
        default: switch_error(__func__, 0x800C22E8, 0x800EC3E0);
    }
    // 0x800C22EC: nop

L_800C22F0:
    // 0x800C22F0: jal         0x800C1698
    // 0x800C22F4: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    func_800C1698(rdram, ctx);
        goto after_1;
    // 0x800C22F4: sw          $v1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r3;
    after_1:
    // 0x800C22F8: lw          $v1, 0x1C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X1C);
    // 0x800C22FC: beql        $v1, $zero, L_800C2310
    if (ctx->r3 == 0) {
        // 0x800C2300: lui         $a0, 0x4601
        ctx->r4 = S32(0X4601 << 16);
            goto L_800C2310;
    }
    goto skip_0;
    // 0x800C2300: lui         $a0, 0x4601
    ctx->r4 = S32(0X4601 << 16);
    skip_0:
    // 0x800C2304: jal         0x800C1714
    // 0x800C2308: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1714(rdram, ctx);
        goto after_2;
    // 0x800C2308: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_2:
    // 0x800C230C: lui         $a0, 0x4601
    ctx->r4 = S32(0X4601 << 16);
L_800C2310:
    // 0x800C2310: jal         0x800C53D4
    // 0x800C2314: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800C2314: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    after_3:
    // 0x800C2318: jal         0x800C13AC
    // 0x800C231C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_4;
    // 0x800C231C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_4:
    // 0x800C2320: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2324: jal         0x800C53D4
    // 0x800C2328: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_5;
    // 0x800C2328: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_5:
    // 0x800C232C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2330: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C2334: jal         0x800C53D4
    // 0x800C2338: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_6;
    // 0x800C2338: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_6:
    // 0x800C233C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2340: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C2344: jal         0x800C53D4
    // 0x800C2348: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_7;
    // 0x800C2348: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_7:
    // 0x800C234C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2350: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2354: jal         0x800C53D4
    // 0x800C2358: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_8;
    // 0x800C2358: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_8:
    // 0x800C235C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2360: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C2364: jal         0x800C53D4
    // 0x800C2368: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_9;
    // 0x800C2368: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_9:
    // 0x800C236C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2370: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2374: jal         0x800C53D4
    // 0x800C2378: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_10;
    // 0x800C2378: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_10:
    // 0x800C237C: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x800C2380: jal         0x800C1500
    // 0x800C2384: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C1500(rdram, ctx);
        goto after_11;
    // 0x800C2384: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_11:
    // 0x800C2388: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C238C: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C2390: jal         0x800C538C
    // 0x800C2394: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_12;
    // 0x800C2394: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_12:
    // 0x800C2398: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C239C: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C23A0: jal         0x800C538C
    // 0x800C23A4: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_13;
    // 0x800C23A4: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_13:
    // 0x800C23A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C23AC: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C23B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C23B4: addiu       $t7, $zero, 0xFF
    ctx->r15 = ADD32(0, 0XFF);
    // 0x800C23B8: sb          $t7, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r15;
    // 0x800C23BC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C23C0: sw          $zero, 0x7DC0($at)
    MEM_W(0X7DC0, ctx->r1) = 0;
    // 0x800C23C4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C23C8: sw          $zero, 0x7DC4($at)
    MEM_W(0X7DC4, ctx->r1) = 0;
    // 0x800C23CC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C23D0: addiu       $t8, $zero, 0x3
    ctx->r24 = ADD32(0, 0X3);
    // 0x800C23D4: jal         0x800BFB50
    // 0x800C23D8: sw          $t8, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r24;
    func_800BFB50(rdram, ctx);
        goto after_14;
    // 0x800C23D8: sw          $t8, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r24;
    after_14:
    // 0x800C23DC: b           L_800C2E8C
    // 0x800C23E0: nop

        goto L_800C2E8C;
    // 0x800C23E0: nop

L_800C23E4:
    // 0x800C23E4: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x800C23E8: lw          $t9, 0x7DCC($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7DCC);
    // 0x800C23EC: addiu       $at, $zero, 0x18
    ctx->r1 = ADD32(0, 0X18);
    // 0x800C23F0: addiu       $a0, $zero, 0x18
    ctx->r4 = ADD32(0, 0X18);
    // 0x800C23F4: beq         $t9, $at, L_800C2E8C
    if (ctx->r25 == ctx->r1) {
        // 0x800C23F8: nop
    
            goto L_800C2E8C;
    }
    // 0x800C23F8: nop

    // 0x800C23FC: jal         0x800C1588
    // 0x800C2400: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C1588(rdram, ctx);
        goto after_15;
    // 0x800C2400: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_15:
    // 0x800C2404: addiu       $t0, $zero, 0x18
    ctx->r8 = ADD32(0, 0X18);
    // 0x800C2408: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C240C: b           L_800C2E8C
    // 0x800C2410: sw          $t0, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r8;
        goto L_800C2E8C;
    // 0x800C2410: sw          $t0, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r8;
L_800C2414:
    // 0x800C2414: addiu       $at, $zero, 0xA
    ctx->r1 = ADD32(0, 0XA);
    // 0x800C2418: beql        $v1, $at, L_800C2490
    if (ctx->r3 == ctx->r1) {
        // 0x800C241C: addiu       $a0, $zero, 0xD
        ctx->r4 = ADD32(0, 0XD);
            goto L_800C2490;
    }
    goto skip_1;
    // 0x800C241C: addiu       $a0, $zero, 0xD
    ctx->r4 = ADD32(0, 0XD);
    skip_1:
    // 0x800C2420: jal         0x800C1488
    // 0x800C2424: nop

    func_800C1488(rdram, ctx);
        goto after_16;
    // 0x800C2424: nop

    after_16:
    // 0x800C2428: jal         0x800C13AC
    // 0x800C242C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_17;
    // 0x800C242C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_17:
    // 0x800C2430: jal         0x800C1608
    // 0x800C2434: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    func_800C1608(rdram, ctx);
        goto after_18;
    // 0x800C2434: addiu       $a0, $zero, 0xA0
    ctx->r4 = ADD32(0, 0XA0);
    after_18:
    // 0x800C2438: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x800C243C: jal         0x800C1588
    // 0x800C2440: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    func_800C1588(rdram, ctx);
        goto after_19;
    // 0x800C2440: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    after_19:
    // 0x800C2444: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2448: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C244C: jal         0x800C538C
    // 0x800C2450: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_20;
    // 0x800C2450: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_20:
    // 0x800C2454: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2458: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C245C: jal         0x800C538C
    // 0x800C2460: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_21;
    // 0x800C2460: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_21:
    // 0x800C2464: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2468: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C246C: jal         0x800C538C
    // 0x800C2470: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_22;
    // 0x800C2470: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_22:
    // 0x800C2474: lw          $t2, 0x24($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X24);
    // 0x800C2478: addiu       $t1, $zero, 0xFF
    ctx->r9 = ADD32(0, 0XFF);
    // 0x800C247C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2480: sb          $t1, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r9;
    // 0x800C2484: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2488: sw          $t2, 0x7DC0($at)
    MEM_W(0X7DC0, ctx->r1) = ctx->r10;
    // 0x800C248C: addiu       $a0, $zero, 0xD
    ctx->r4 = ADD32(0, 0XD);
L_800C2490:
    // 0x800C2490: jal         0x800C37C0
    // 0x800C2494: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_800C37C0(rdram, ctx);
        goto after_23;
    // 0x800C2494: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_23:
    // 0x800C2498: b           L_800C2E8C
    // 0x800C249C: nop

        goto L_800C2E8C;
    // 0x800C249C: nop

L_800C24A0:
    // 0x800C24A0: beql        $v1, $a2, L_800C24D4
    if (ctx->r3 == ctx->r6) {
        // 0x800C24A4: addiu       $a0, $zero, 0xC
        ctx->r4 = ADD32(0, 0XC);
            goto L_800C24D4;
    }
    goto skip_2;
    // 0x800C24A4: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
    skip_2:
    // 0x800C24A8: jal         0x800C1488
    // 0x800C24AC: nop

    func_800C1488(rdram, ctx);
        goto after_24;
    // 0x800C24AC: nop

    after_24:
    // 0x800C24B0: jal         0x800C13AC
    // 0x800C24B4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_25;
    // 0x800C24B4: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_25:
    // 0x800C24B8: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    // 0x800C24BC: jal         0x800C1588
    // 0x800C24C0: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    func_800C1588(rdram, ctx);
        goto after_26;
    // 0x800C24C0: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    after_26:
    // 0x800C24C4: addiu       $t3, $zero, 0xFF
    ctx->r11 = ADD32(0, 0XFF);
    // 0x800C24C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C24CC: sb          $t3, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r11;
    // 0x800C24D0: addiu       $a0, $zero, 0xC
    ctx->r4 = ADD32(0, 0XC);
L_800C24D4:
    // 0x800C24D4: jal         0x800C37C0
    // 0x800C24D8: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    func_800C37C0(rdram, ctx);
        goto after_27;
    // 0x800C24D8: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    after_27:
    // 0x800C24DC: b           L_800C2E8C
    // 0x800C24E0: nop

        goto L_800C2E8C;
    // 0x800C24E0: nop

L_800C24E4:
    // 0x800C24E4: jal         0x800C1488
    // 0x800C24E8: nop

    func_800C1488(rdram, ctx);
        goto after_28;
    // 0x800C24E8: nop

    after_28:
    // 0x800C24EC: jal         0x800C13AC
    // 0x800C24F0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_29;
    // 0x800C24F0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_29:
    // 0x800C24F4: jal         0x800C1674
    // 0x800C24F8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_30;
    // 0x800C24F8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_30:
    // 0x800C24FC: jal         0x800C1608
    // 0x800C2500: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1608(rdram, ctx);
        goto after_31;
    // 0x800C2500: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_31:
    // 0x800C2504: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2508: jal         0x800C53D4
    // 0x800C250C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_32;
    // 0x800C250C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_32:
    // 0x800C2510: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2514: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C2518: jal         0x800C53D4
    // 0x800C251C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_33;
    // 0x800C251C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_33:
    // 0x800C2520: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2524: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C2528: jal         0x800C53D4
    // 0x800C252C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_34;
    // 0x800C252C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_34:
    // 0x800C2530: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2534: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2538: jal         0x800C53D4
    // 0x800C253C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_35;
    // 0x800C253C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_35:
    // 0x800C2540: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2544: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C2548: jal         0x800C53D4
    // 0x800C254C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_36;
    // 0x800C254C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_36:
    // 0x800C2550: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2554: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2558: jal         0x800C53D4
    // 0x800C255C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_37;
    // 0x800C255C: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_37:
    // 0x800C2560: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2564: jal         0x800C538C
    // 0x800C2568: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_38;
    // 0x800C2568: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_38:
    // 0x800C256C: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2570: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2574: jal         0x800C538C
    // 0x800C2578: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_39;
    // 0x800C2578: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_39:
    // 0x800C257C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2580: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C2584: jal         0x800C538C
    // 0x800C2588: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_40;
    // 0x800C2588: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_40:
    // 0x800C258C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2590: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2594: jal         0x800C538C
    // 0x800C2598: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_41;
    // 0x800C2598: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_41:
    // 0x800C259C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C25A0: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C25A4: jal         0x800C538C
    // 0x800C25A8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_42;
    // 0x800C25A8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_42:
    // 0x800C25AC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C25B0: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C25B4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C25B8: addiu       $t4, $zero, 0xFF
    ctx->r12 = ADD32(0, 0XFF);
    // 0x800C25BC: jal         0x800BFB50
    // 0x800C25C0: sb          $t4, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r12;
    func_800BFB50(rdram, ctx);
        goto after_43;
    // 0x800C25C0: sb          $t4, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r12;
    after_43:
    // 0x800C25C4: lw          $t5, 0x24($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X24);
    // 0x800C25C8: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x800C25CC: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C25D0: bne         $t5, $at, L_800C2604
    if (ctx->r13 != ctx->r1) {
        // 0x800C25D4: addiu       $a0, $a0, 0x10
        ctx->r4 = ADD32(ctx->r4, 0X10);
            goto L_800C2604;
    }
    // 0x800C25D4: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x800C25D8: addiu       $a0, $zero, 0x34
    ctx->r4 = ADD32(0, 0X34);
    // 0x800C25DC: jal         0x800C37F4
    // 0x800C25E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_44;
    // 0x800C25E0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_44:
    // 0x800C25E4: addiu       $a0, $zero, 0x11
    ctx->r4 = ADD32(0, 0X11);
    // 0x800C25E8: jal         0x800C37C0
    // 0x800C25EC: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    func_800C37C0(rdram, ctx);
        goto after_45;
    // 0x800C25EC: addiu       $a1, $zero, 0x50
    ctx->r5 = ADD32(0, 0X50);
    after_45:
    // 0x800C25F0: addiu       $a0, $zero, 0x19
    ctx->r4 = ADD32(0, 0X19);
    // 0x800C25F4: jal         0x800C1500
    // 0x800C25F8: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_800C1500(rdram, ctx);
        goto after_46;
    // 0x800C25F8: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_46:
    // 0x800C25FC: b           L_800C2E8C
    // 0x800C2600: nop

        goto L_800C2E8C;
    // 0x800C2600: nop

L_800C2604:
    // 0x800C2604: jal         0x800C37C0
    // 0x800C2608: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    func_800C37C0(rdram, ctx);
        goto after_47;
    // 0x800C2608: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    after_47:
    // 0x800C260C: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    // 0x800C2610: jal         0x800C1500
    // 0x800C2614: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_800C1500(rdram, ctx);
        goto after_48;
    // 0x800C2614: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_48:
    // 0x800C2618: b           L_800C2E8C
    // 0x800C261C: nop

        goto L_800C2E8C;
    // 0x800C261C: nop

L_800C2620:
    // 0x800C2620: jal         0x800C1488
    // 0x800C2624: nop

    func_800C1488(rdram, ctx);
        goto after_49;
    // 0x800C2624: nop

    after_49:
    // 0x800C2628: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C262C: lw          $t6, 0x7DC8($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC8);
    // 0x800C2630: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C2634: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x800C2638: bne         $t6, $at, L_800C2648
    if (ctx->r14 != ctx->r1) {
        // 0x800C263C: nop
    
            goto L_800C2648;
    }
    // 0x800C263C: nop

    // 0x800C2640: jal         0x800C1500
    // 0x800C2644: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C1500(rdram, ctx);
        goto after_50;
    // 0x800C2644: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_50:
L_800C2648:
    // 0x800C2648: jal         0x800C13AC
    // 0x800C264C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_51;
    // 0x800C264C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_51:
    // 0x800C2650: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C2654: lw          $t7, 0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC0);
    // 0x800C2658: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
    // 0x800C265C: bne         $t7, $zero, L_800C2E8C
    if (ctx->r15 != 0) {
        // 0x800C2660: nop
    
            goto L_800C2E8C;
    }
    // 0x800C2660: nop

    // 0x800C2664: bne         $t8, $zero, L_800C268C
    if (ctx->r24 != 0) {
        // 0x800C2668: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C268C;
    }
    // 0x800C2668: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C266C: lw          $v0, 0x7DC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC8);
    // 0x800C2670: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C2674: beq         $v0, $at, L_800C268C
    if (ctx->r2 == ctx->r1) {
        // 0x800C2678: addiu       $a0, $v0, 0x56
        ctx->r4 = ADD32(ctx->r2, 0X56);
            goto L_800C268C;
    }
    // 0x800C2678: addiu       $a0, $v0, 0x56
    ctx->r4 = ADD32(ctx->r2, 0X56);
    // 0x800C267C: jal         0x800C3524
    // 0x800C2680: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C3524(rdram, ctx);
        goto after_52;
    // 0x800C2680: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_52:
    // 0x800C2684: b           L_800C2E8C
    // 0x800C2688: nop

        goto L_800C2E8C;
    // 0x800C2688: nop

L_800C268C:
    // 0x800C268C: addiu       $a0, $zero, 0x5B
    ctx->r4 = ADD32(0, 0X5B);
    // 0x800C2690: jal         0x800C3524
    // 0x800C2694: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C3524(rdram, ctx);
        goto after_53;
    // 0x800C2694: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_53:
    // 0x800C2698: b           L_800C2E8C
    // 0x800C269C: nop

        goto L_800C2E8C;
    // 0x800C269C: nop

L_800C26A0:
    // 0x800C26A0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x800C26A4: jal         0x800C5244
    // 0x800C26A8: addiu       $a1, $zero, 0xF0
    ctx->r5 = ADD32(0, 0XF0);
    AudioThread_SetFadeOutTimer(rdram, ctx);
        goto after_54;
    // 0x800C26A8: addiu       $a1, $zero, 0xF0
    ctx->r5 = ADD32(0, 0XF0);
    after_54:
    // 0x800C26AC: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800C26B0: lw          $t0, 0x7DC4($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7DC4);
    // 0x800C26B4: addiu       $t9, $zero, 0x50
    ctx->r25 = ADD32(0, 0X50);
    // 0x800C26B8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C26BC: bne         $t0, $zero, L_800C26E4
    if (ctx->r8 != 0) {
        // 0x800C26C0: sw          $t9, 0x7CE0($at)
        MEM_W(0X7CE0, ctx->r1) = ctx->r25;
            goto L_800C26E4;
    }
    // 0x800C26C0: sw          $t9, 0x7CE0($at)
    MEM_W(0X7CE0, ctx->r1) = ctx->r25;
    // 0x800C26C4: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C26C8: lw          $t1, 0x7DC0($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X7DC0);
    // 0x800C26CC: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C26D0: ori         $a0, $a0, 0xC00
    ctx->r4 = ctx->r4 | 0XC00;
    // 0x800C26D4: bnel        $t1, $zero, L_800C26E8
    if (ctx->r9 != 0) {
        // 0x800C26D8: addiu       $t2, $zero, 0x4
        ctx->r10 = ADD32(0, 0X4);
            goto L_800C26E8;
    }
    goto skip_3;
    // 0x800C26D8: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
    skip_3:
    // 0x800C26DC: jal         0x800C538C
    // 0x800C26E0: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_55;
    // 0x800C26E0: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_55:
L_800C26E4:
    // 0x800C26E4: addiu       $t2, $zero, 0x4
    ctx->r10 = ADD32(0, 0X4);
L_800C26E8:
    // 0x800C26E8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C26EC: b           L_800C2E8C
    // 0x800C26F0: sw          $t2, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r10;
        goto L_800C2E8C;
    // 0x800C26F0: sw          $t2, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r10;
L_800C26F4:
    // 0x800C26F4: addiu       $a0, $zero, 0x17
    ctx->r4 = ADD32(0, 0X17);
    // 0x800C26F8: jal         0x800C1500
    // 0x800C26FC: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    func_800C1500(rdram, ctx);
        goto after_56;
    // 0x800C26FC: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    after_56:
    // 0x800C2700: addiu       $a0, $zero, 0x1F
    ctx->r4 = ADD32(0, 0X1F);
    // 0x800C2704: jal         0x800C3524
    // 0x800C2708: addiu       $a1, $zero, 0x46
    ctx->r5 = ADD32(0, 0X46);
    func_800C3524(rdram, ctx);
        goto after_57;
    // 0x800C2708: addiu       $a1, $zero, 0x46
    ctx->r5 = ADD32(0, 0X46);
    after_57:
    // 0x800C270C: b           L_800C2E8C
    // 0x800C2710: nop

        goto L_800C2E8C;
    // 0x800C2710: nop

L_800C2714:
    // 0x800C2714: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x800C2718: jal         0x800C1714
    // 0x800C271C: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    func_800C1714(rdram, ctx);
        goto after_58;
    // 0x800C271C: addiu       $a0, $a0, 0x1
    ctx->r4 = ADD32(ctx->r4, 0X1);
    after_58:
    // 0x800C2720: lw          $v1, 0x24($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X24);
    // 0x800C2724: lui         $t3, 0x800E
    ctx->r11 = S32(0X800E << 16);
    // 0x800C2728: lui         $t4, 0x800E
    ctx->r12 = S32(0X800E << 16);
    // 0x800C272C: addu        $t3, $t3, $v1
    ctx->r11 = ADD32(ctx->r11, ctx->r3);
    // 0x800C2730: lb          $t3, 0x7CF8($t3)
    ctx->r11 = MEM_B(ctx->r11, 0X7CF8);
    // 0x800C2734: addu        $t4, $t4, $v1
    ctx->r12 = ADD32(ctx->r12, ctx->r3);
    // 0x800C2738: lb          $t4, 0x7D04($t4)
    ctx->r12 = MEM_B(ctx->r12, 0X7D04);
    // 0x800C273C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2740: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800C2744: addu        $t5, $t5, $v1
    ctx->r13 = ADD32(ctx->r13, ctx->r3);
    // 0x800C2748: sw          $t3, 0x7E08($at)
    MEM_W(0X7E08, ctx->r1) = ctx->r11;
    // 0x800C274C: lb          $t5, 0x7D10($t5)
    ctx->r13 = MEM_B(ctx->r13, 0X7D10);
    // 0x800C2750: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2754: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2758: sw          $t4, 0x7E0C($at)
    MEM_W(0X7E0C, ctx->r1) = ctx->r12;
    // 0x800C275C: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
    // 0x800C2760: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2764: sw          $t5, 0x7E10($at)
    MEM_W(0X7E10, ctx->r1) = ctx->r13;
    // 0x800C2768: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C276C: beq         $v0, $zero, L_800C2798
    if (ctx->r2 == 0) {
        // 0x800C2770: sw          $v1, 0x7DC4($at)
        MEM_W(0X7DC4, ctx->r1) = ctx->r3;
            goto L_800C2798;
    }
    // 0x800C2770: sw          $v1, 0x7DC4($at)
    MEM_W(0X7DC4, ctx->r1) = ctx->r3;
    // 0x800C2774: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C2778: beq         $v0, $at, L_800C28C0
    if (ctx->r2 == ctx->r1) {
        // 0x800C277C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C28C0;
    }
    // 0x800C277C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C2780: beq         $v0, $at, L_800C298C
    if (ctx->r2 == ctx->r1) {
        // 0x800C2784: addiu       $at, $zero, 0x3
        ctx->r1 = ADD32(0, 0X3);
            goto L_800C298C;
    }
    // 0x800C2784: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C2788: beq         $v0, $at, L_800C2A2C
    if (ctx->r2 == ctx->r1) {
        // 0x800C278C: nop
    
            goto L_800C2A2C;
    }
    // 0x800C278C: nop

    // 0x800C2790: b           L_800C2AC0
    // 0x800C2794: nop

        goto L_800C2AC0;
    // 0x800C2794: nop

L_800C2798:
    // 0x800C2798: jal         0x800C1488
    // 0x800C279C: nop

    func_800C1488(rdram, ctx);
        goto after_59;
    // 0x800C279C: nop

    after_59:
    // 0x800C27A0: jal         0x800C13AC
    // 0x800C27A4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_60;
    // 0x800C27A4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_60:
    // 0x800C27A8: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C27AC: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C27B0: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C27B4: addiu       $t6, $zero, 0x8
    ctx->r14 = ADD32(0, 0X8);
    // 0x800C27B8: sb          $t6, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r14;
    // 0x800C27BC: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C27C0: jal         0x800C53D4
    // 0x800C27C4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_61;
    // 0x800C27C4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_61:
    // 0x800C27C8: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C27CC: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C27D0: jal         0x800C53D4
    // 0x800C27D4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_62;
    // 0x800C27D4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_62:
    // 0x800C27D8: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C27DC: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C27E0: jal         0x800C53D4
    // 0x800C27E4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_63;
    // 0x800C27E4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_63:
    // 0x800C27E8: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C27EC: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C27F0: jal         0x800C53D4
    // 0x800C27F4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_64;
    // 0x800C27F4: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_64:
    // 0x800C27F8: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C27FC: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C2800: jal         0x800C53D4
    // 0x800C2804: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_65;
    // 0x800C2804: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_65:
    // 0x800C2808: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C280C: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2810: jal         0x800C53D4
    // 0x800C2814: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_66;
    // 0x800C2814: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_66:
    // 0x800C2818: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C281C: lw          $t7, 0x7C98($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7C98);
    // 0x800C2820: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
    // 0x800C2824: beq         $t7, $zero, L_800C283C
    if (ctx->r15 == 0) {
        // 0x800C2828: addiu       $a0, $t8, 0x6
        ctx->r4 = ADD32(ctx->r24, 0X6);
            goto L_800C283C;
    }
    // 0x800C2828: addiu       $a0, $t8, 0x6
    ctx->r4 = ADD32(ctx->r24, 0X6);
    // 0x800C282C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2830: addiu       $v0, $v0, 0x7DCC
    ctx->r2 = ADD32(ctx->r2, 0X7DCC);
    // 0x800C2834: jal         0x800C14D0
    // 0x800C2838: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    func_800C14D0(rdram, ctx);
        goto after_67;
    // 0x800C2838: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    after_67:
L_800C283C:
    // 0x800C283C: lw          $t0, 0x24($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X24);
    // 0x800C2840: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2844: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2848: bne         $t0, $zero, L_800C2884
    if (ctx->r8 != 0) {
        // 0x800C284C: nop
    
            goto L_800C2884;
    }
    // 0x800C284C: nop

    // 0x800C2850: jal         0x800C538C
    // 0x800C2854: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_68;
    // 0x800C2854: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_68:
    // 0x800C2858: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C285C: lui         $a1, 0x3F49
    ctx->r5 = S32(0X3F49 << 16);
    // 0x800C2860: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    // 0x800C2864: jal         0x800C538C
    // 0x800C2868: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_69;
    // 0x800C2868: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    after_69:
    // 0x800C286C: addiu       $t1, $zero, 0x8
    ctx->r9 = ADD32(0, 0X8);
    // 0x800C2870: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2874: sw          $t1, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = ctx->r9;
    // 0x800C2878: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C287C: b           L_800C2AC0
    // 0x800C2880: sb          $zero, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = 0;
        goto L_800C2AC0;
    // 0x800C2880: sb          $zero, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = 0;
L_800C2884:
    // 0x800C2884: jal         0x800C1EB8
    // 0x800C2888: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    func_800C1EB8(rdram, ctx);
        goto after_70;
    // 0x800C2888: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    after_70:
    // 0x800C288C: jal         0x800BFB50
    // 0x800C2890: nop

    func_800BFB50(rdram, ctx);
        goto after_71;
    // 0x800C2890: nop

    after_71:
    // 0x800C2894: lw          $t2, 0x24($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X24);
    // 0x800C2898: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C289C: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x800C28A0: bne         $t2, $at, L_800C28B0
    if (ctx->r10 != ctx->r1) {
        // 0x800C28A4: nop
    
            goto L_800C28B0;
    }
    // 0x800C28A4: nop

    // 0x800C28A8: b           L_800C28B0
    // 0x800C28AC: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
        goto L_800C28B0;
    // 0x800C28AC: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
L_800C28B0:
    // 0x800C28B0: jal         0x800C3524
    // 0x800C28B4: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    func_800C3524(rdram, ctx);
        goto after_72;
    // 0x800C28B4: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    after_72:
    // 0x800C28B8: b           L_800C2AC0
    // 0x800C28BC: nop

        goto L_800C2AC0;
    // 0x800C28BC: nop

L_800C28C0:
    // 0x800C28C0: jal         0x800C1488
    // 0x800C28C4: nop

    func_800C1488(rdram, ctx);
        goto after_73;
    // 0x800C28C4: nop

    after_73:
    // 0x800C28C8: jal         0x800C13AC
    // 0x800C28CC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_74;
    // 0x800C28CC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_74:
    // 0x800C28D0: addiu       $t3, $zero, 0x1
    ctx->r11 = ADD32(0, 0X1);
    // 0x800C28D4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C28D8: sb          $t3, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = ctx->r11;
    // 0x800C28DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C28E0: addiu       $t4, $zero, 0x4
    ctx->r12 = ADD32(0, 0X4);
    // 0x800C28E4: sb          $t4, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r12;
    // 0x800C28E8: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C28EC: jal         0x800C53D4
    // 0x800C28F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_75;
    // 0x800C28F0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_75:
    // 0x800C28F4: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C28F8: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C28FC: jal         0x800C53D4
    // 0x800C2900: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_76;
    // 0x800C2900: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_76:
    // 0x800C2904: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2908: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C290C: jal         0x800C53D4
    // 0x800C2910: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_77;
    // 0x800C2910: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_77:
    // 0x800C2914: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2918: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C291C: jal         0x800C53D4
    // 0x800C2920: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_78;
    // 0x800C2920: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_78:
    // 0x800C2924: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2928: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C292C: jal         0x800C53D4
    // 0x800C2930: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_79;
    // 0x800C2930: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_79:
    // 0x800C2934: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C2938: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C293C: jal         0x800C53D4
    // 0x800C2940: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_80;
    // 0x800C2940: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_80:
    // 0x800C2944: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2948: lui         $a1, 0x3EF1
    ctx->r5 = S32(0X3EF1 << 16);
    // 0x800C294C: ori         $a1, $a1, 0xE3C8
    ctx->r5 = ctx->r5 | 0XE3C8;
    // 0x800C2950: jal         0x800C538C
    // 0x800C2954: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_81;
    // 0x800C2954: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_81:
    // 0x800C2958: jal         0x800C1EB8
    // 0x800C295C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_82;
    // 0x800C295C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_82:
    // 0x800C2960: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800C2964: lw          $t5, 0x7C98($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7C98);
    // 0x800C2968: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
    // 0x800C296C: beq         $t5, $zero, L_800C2AC0
    if (ctx->r13 == 0) {
        // 0x800C2970: addiu       $a0, $t6, 0x6
        ctx->r4 = ADD32(ctx->r14, 0X6);
            goto L_800C2AC0;
    }
    // 0x800C2970: addiu       $a0, $t6, 0x6
    ctx->r4 = ADD32(ctx->r14, 0X6);
    // 0x800C2974: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2978: addiu       $v0, $v0, 0x7DCC
    ctx->r2 = ADD32(ctx->r2, 0X7DCC);
    // 0x800C297C: jal         0x800C14D0
    // 0x800C2980: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    func_800C14D0(rdram, ctx);
        goto after_83;
    // 0x800C2980: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    after_83:
    // 0x800C2984: b           L_800C2AC0
    // 0x800C2988: nop

        goto L_800C2AC0;
    // 0x800C2988: nop

L_800C298C:
    // 0x800C298C: jal         0x800C1488
    // 0x800C2990: nop

    func_800C1488(rdram, ctx);
        goto after_84;
    // 0x800C2990: nop

    after_84:
    // 0x800C2994: jal         0x800C13AC
    // 0x800C2998: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_85;
    // 0x800C2998: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_85:
    // 0x800C299C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C29A0: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C29A4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C29A8: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C29AC: sb          $zero, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = 0;
    // 0x800C29B0: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C29B4: jal         0x800C538C
    // 0x800C29B8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_86;
    // 0x800C29B8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_86:
    // 0x800C29BC: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
    // 0x800C29C0: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C29C4: lui         $a1, 0x3F49
    ctx->r5 = S32(0X3F49 << 16);
    // 0x800C29C8: bne         $t8, $zero, L_800C29F0
    if (ctx->r24 != 0) {
        // 0x800C29CC: ori         $a0, $a0, 0x500
        ctx->r4 = ctx->r4 | 0X500;
            goto L_800C29F0;
    }
    // 0x800C29CC: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C29D0: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C29D4: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C29D8: jal         0x800C538C
    // 0x800C29DC: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_87;
    // 0x800C29DC: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    after_87:
    // 0x800C29E0: addiu       $t9, $zero, 0x8
    ctx->r25 = ADD32(0, 0X8);
    // 0x800C29E4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C29E8: b           L_800C29F8
    // 0x800C29EC: sw          $t9, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = ctx->r25;
        goto L_800C29F8;
    // 0x800C29EC: sw          $t9, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = ctx->r25;
L_800C29F0:
    // 0x800C29F0: jal         0x800C538C
    // 0x800C29F4: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_88;
    // 0x800C29F4: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_88:
L_800C29F8:
    // 0x800C29F8: jal         0x800C1EB8
    // 0x800C29FC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_89;
    // 0x800C29FC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_89:
    // 0x800C2A00: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800C2A04: lw          $t0, 0x7C98($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7C98);
    // 0x800C2A08: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x800C2A0C: beq         $t0, $zero, L_800C2AC0
    if (ctx->r8 == 0) {
        // 0x800C2A10: addiu       $a0, $t1, 0x6
        ctx->r4 = ADD32(ctx->r9, 0X6);
            goto L_800C2AC0;
    }
    // 0x800C2A10: addiu       $a0, $t1, 0x6
    ctx->r4 = ADD32(ctx->r9, 0X6);
    // 0x800C2A14: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2A18: addiu       $v0, $v0, 0x7DCC
    ctx->r2 = ADD32(ctx->r2, 0X7DCC);
    // 0x800C2A1C: jal         0x800C14D0
    // 0x800C2A20: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    func_800C14D0(rdram, ctx);
        goto after_90;
    // 0x800C2A20: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    after_90:
    // 0x800C2A24: b           L_800C2AC0
    // 0x800C2A28: nop

        goto L_800C2AC0;
    // 0x800C2A28: nop

L_800C2A2C:
    // 0x800C2A2C: jal         0x800C1488
    // 0x800C2A30: nop

    func_800C1488(rdram, ctx);
        goto after_91;
    // 0x800C2A30: nop

    after_91:
    // 0x800C2A34: jal         0x800C13AC
    // 0x800C2A38: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C13AC(rdram, ctx);
        goto after_92;
    // 0x800C2A38: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_92:
    // 0x800C2A3C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2A40: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C2A44: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2A48: addiu       $t3, $zero, 0x4
    ctx->r11 = ADD32(0, 0X4);
    // 0x800C2A4C: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2A50: sb          $t3, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r11;
    // 0x800C2A54: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2A58: jal         0x800C538C
    // 0x800C2A5C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_93;
    // 0x800C2A5C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_93:
    // 0x800C2A60: lw          $t4, 0x24($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X24);
    // 0x800C2A64: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2A68: lui         $a1, 0x3F49
    ctx->r5 = S32(0X3F49 << 16);
    // 0x800C2A6C: bne         $t4, $zero, L_800C2A8C
    if (ctx->r12 != 0) {
        // 0x800C2A70: ori         $a0, $a0, 0x500
        ctx->r4 = ctx->r4 | 0X500;
            goto L_800C2A8C;
    }
    // 0x800C2A70: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2A74: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2A78: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2A7C: jal         0x800C538C
    // 0x800C2A80: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_94;
    // 0x800C2A80: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    after_94:
    // 0x800C2A84: b           L_800C2A94
    // 0x800C2A88: nop

        goto L_800C2A94;
    // 0x800C2A88: nop

L_800C2A8C:
    // 0x800C2A8C: jal         0x800C538C
    // 0x800C2A90: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_95;
    // 0x800C2A90: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_95:
L_800C2A94:
    // 0x800C2A94: jal         0x800C1EB8
    // 0x800C2A98: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_96;
    // 0x800C2A98: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_96:
    // 0x800C2A9C: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800C2AA0: lw          $t5, 0x7C98($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7C98);
    // 0x800C2AA4: lw          $t6, 0x24($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X24);
    // 0x800C2AA8: beq         $t5, $zero, L_800C2AC0
    if (ctx->r13 == 0) {
        // 0x800C2AAC: addiu       $a0, $t6, 0x6
        ctx->r4 = ADD32(ctx->r14, 0X6);
            goto L_800C2AC0;
    }
    // 0x800C2AAC: addiu       $a0, $t6, 0x6
    ctx->r4 = ADD32(ctx->r14, 0X6);
    // 0x800C2AB0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2AB4: addiu       $v0, $v0, 0x7DCC
    ctx->r2 = ADD32(ctx->r2, 0X7DCC);
    // 0x800C2AB8: jal         0x800C14D0
    // 0x800C2ABC: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    func_800C14D0(rdram, ctx);
        goto after_97;
    // 0x800C2ABC: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    after_97:
L_800C2AC0:
    { extern void wr64_free_ride_schedule_music(uint8_t*); wr64_free_ride_schedule_music(rdram); }
    // 0x800C2AC0: jal         0x800C14D0
    // 0x800C2AC4: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    func_800C14D0(rdram, ctx);
        goto after_98;
    // 0x800C2AC4: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    after_98:
    // 0x800C2AC8: b           L_800C2E8C
    // 0x800C2ACC: nop

        goto L_800C2E8C;
    // 0x800C2ACC: nop

L_800C2AD0:
    // 0x800C2AD0: addiu       $t8, $zero, 0xFF
    ctx->r24 = ADD32(0, 0XFF);
    // 0x800C2AD4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2AD8: sb          $t8, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r24;
    // 0x800C2ADC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2AE0: sw          $a2, 0x7DD0($at)
    MEM_W(0X7DD0, ctx->r1) = ctx->r6;
    // 0x800C2AE4: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2AE8: jal         0x800C538C
    // 0x800C2AEC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_99;
    // 0x800C2AEC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_99:
    // 0x800C2AF0: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C2AF4: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C2AF8: jal         0x800C538C
    // 0x800C2AFC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_100;
    // 0x800C2AFC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_100:
    // 0x800C2B00: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2B04: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C2B08: jal         0x800C538C
    // 0x800C2B0C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_101;
    // 0x800C2B0C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_101:
    // 0x800C2B10: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2B14: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C2B18: jal         0x800C538C
    // 0x800C2B1C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_102;
    // 0x800C2B1C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_102:
    // 0x800C2B20: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C2B24: ori         $a0, $a0, 0x700
    ctx->r4 = ctx->r4 | 0X700;
    // 0x800C2B28: jal         0x800C538C
    // 0x800C2B2C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_103;
    // 0x800C2B2C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_103:
    // 0x800C2B30: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x800C2B34: jal         0x800C5244
    // 0x800C2B38: addiu       $a1, $zero, 0x3C
    ctx->r5 = ADD32(0, 0X3C);
    AudioThread_SetFadeOutTimer(rdram, ctx);
        goto after_104;
    // 0x800C2B38: addiu       $a1, $zero, 0x3C
    ctx->r5 = ADD32(0, 0X3C);
    after_104:
    // 0x800C2B3C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2B40: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
    // 0x800C2B44: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    // 0x800C2B48: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2B4C: beq         $v0, $zero, L_800C2B80
    if (ctx->r2 == 0) {
        // 0x800C2B50: addiu       $t0, $t9, -0x1
        ctx->r8 = ADD32(ctx->r25, -0X1);
            goto L_800C2B80;
    }
    // 0x800C2B50: addiu       $t0, $t9, -0x1
    ctx->r8 = ADD32(ctx->r25, -0X1);
    // 0x800C2B54: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C2B58: beq         $v0, $at, L_800C2D08
    if (ctx->r2 == ctx->r1) {
        // 0x800C2B5C: addiu       $t2, $zero, 0x15
        ctx->r10 = ADD32(0, 0X15);
            goto L_800C2D08;
    }
    // 0x800C2B5C: addiu       $t2, $zero, 0x15
    ctx->r10 = ADD32(0, 0X15);
    // 0x800C2B60: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C2B64: beq         $v0, $at, L_800C2C7C
    if (ctx->r2 == ctx->r1) {
        // 0x800C2B68: lw          $t1, 0x24($sp)
        ctx->r9 = MEM_W(ctx->r29, 0X24);
            goto L_800C2C7C;
    }
    // 0x800C2B68: lw          $t1, 0x24($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X24);
    // 0x800C2B6C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C2B70: beql        $v0, $at, L_800C2C80
    if (ctx->r2 == ctx->r1) {
        // 0x800C2B74: andi        $t2, $t1, 0x1
        ctx->r10 = ctx->r9 & 0X1;
            goto L_800C2C80;
    }
    goto skip_4;
    // 0x800C2B74: andi        $t2, $t1, 0x1
    ctx->r10 = ctx->r9 & 0X1;
    skip_4:
    // 0x800C2B78: b           L_800C2D74
    // 0x800C2B7C: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
        goto L_800C2D74;
    // 0x800C2B7C: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
L_800C2B80:
    // 0x800C2B80: addiu       $t1, $t0, 0xF
    ctx->r9 = ADD32(ctx->r8, 0XF);
    // 0x800C2B84: sw          $t0, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r8;
    // 0x800C2B88: sw          $t1, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r9;
    // 0x800C2B8C: addiu       $a0, $zero, 0xE
    ctx->r4 = ADD32(0, 0XE);
    // 0x800C2B90: addiu       $a1, $zero, 0x7E
    ctx->r5 = ADD32(0, 0X7E);
    // 0x800C2B94: jal         0x800C32A0
    // 0x800C2B98: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    func_800C32A0(rdram, ctx);
        goto after_105;
    // 0x800C2B98: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_105:
    // 0x800C2B9C: addiu       $a0, $zero, 0xE
    ctx->r4 = ADD32(0, 0XE);
    // 0x800C2BA0: addiu       $a1, $zero, 0x7E
    ctx->r5 = ADD32(0, 0X7E);
    // 0x800C2BA4: jal         0x800C32A0
    // 0x800C2BA8: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    func_800C32A0(rdram, ctx);
        goto after_106;
    // 0x800C2BA8: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_106:
    // 0x800C2BAC: lw          $t2, 0x24($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X24);
    // 0x800C2BB0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2BB4: addiu       $v0, $v0, 0x7DF8
    ctx->r2 = ADD32(ctx->r2, 0X7DF8);
    // 0x800C2BB8: beq         $t2, $zero, L_800C2BD0
    if (ctx->r10 == 0) {
        // 0x800C2BBC: addiu       $at, $zero, 0x4
        ctx->r1 = ADD32(0, 0X4);
            goto L_800C2BD0;
    }
    // 0x800C2BBC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C2BC0: beq         $t2, $at, L_800C2C0C
    if (ctx->r10 == ctx->r1) {
        // 0x800C2BC4: lui         $a0, 0x8004
        ctx->r4 = S32(0X8004 << 16);
            goto L_800C2C0C;
    }
    // 0x800C2BC4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C2BC8: b           L_800C2C48
    // 0x800C2BCC: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
        goto L_800C2C48;
    // 0x800C2BCC: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
L_800C2BD0:
    // 0x800C2BD0: lb          $t3, 0x1($v0)
    ctx->r11 = MEM_B(ctx->r2, 0X1);
    // 0x800C2BD4: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    // 0x800C2BD8: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x800C2BDC: bne         $t3, $zero, L_800C2BF4
    if (ctx->r11 != 0) {
        // 0x800C2BE0: addiu       $a0, $zero, 0xF
        ctx->r4 = ADD32(0, 0XF);
            goto L_800C2BF4;
    }
    // 0x800C2BE0: addiu       $a0, $zero, 0xF
    ctx->r4 = ADD32(0, 0XF);
    // 0x800C2BE4: jal         0x800C32A0
    // 0x800C2BE8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    func_800C32A0(rdram, ctx);
        goto after_107;
    // 0x800C2BE8: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    after_107:
    // 0x800C2BEC: b           L_800C2C00
    // 0x800C2BF0: addiu       $t4, $zero, 0x1E
    ctx->r12 = ADD32(0, 0X1E);
        goto L_800C2C00;
    // 0x800C2BF0: addiu       $t4, $zero, 0x1E
    ctx->r12 = ADD32(0, 0X1E);
L_800C2BF4:
    // 0x800C2BF4: jal         0x800C3524
    // 0x800C2BF8: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C3524(rdram, ctx);
        goto after_108;
    // 0x800C2BF8: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_108:
    // 0x800C2BFC: addiu       $t4, $zero, 0x1E
    ctx->r12 = ADD32(0, 0X1E);
L_800C2C00:
    // 0x800C2C00: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2C04: b           L_800C2C60
    // 0x800C2C08: sw          $t4, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r12;
        goto L_800C2C60;
    // 0x800C2C08: sw          $t4, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r12;
L_800C2C0C:
    // 0x800C2C0C: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800C2C10: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    // 0x800C2C14: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x800C2C18: andi        $t5, $a0, 0x1
    ctx->r13 = ctx->r4 & 0X1;
    // 0x800C2C1C: jal         0x800C32A0
    // 0x800C2C20: addiu       $a0, $t5, 0x14
    ctx->r4 = ADD32(ctx->r13, 0X14);
    func_800C32A0(rdram, ctx);
        goto after_109;
    // 0x800C2C20: addiu       $a0, $t5, 0x14
    ctx->r4 = ADD32(ctx->r13, 0X14);
    after_109:
    // 0x800C2C24: addiu       $t6, $zero, 0x1B
    ctx->r14 = ADD32(0, 0X1B);
    // 0x800C2C28: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2C2C: sw          $t6, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r14;
    // 0x800C2C30: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2C34: addiu       $t7, $zero, 0x1E
    ctx->r15 = ADD32(0, 0X1E);
    // 0x800C2C38: addiu       $t8, $zero, 0x5
    ctx->r24 = ADD32(0, 0X5);
    // 0x800C2C3C: sw          $t7, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r15;
    // 0x800C2C40: b           L_800C2C60
    // 0x800C2C44: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
        goto L_800C2C60;
    // 0x800C2C44: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
L_800C2C48:
    // 0x800C2C48: addiu       $a0, $a0, 0x10
    ctx->r4 = ADD32(ctx->r4, 0X10);
    // 0x800C2C4C: jal         0x800C3524
    // 0x800C2C50: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C3524(rdram, ctx);
        goto after_110;
    // 0x800C2C50: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_110:
    // 0x800C2C54: addiu       $t9, $zero, 0x14
    ctx->r25 = ADD32(0, 0X14);
    // 0x800C2C58: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2C5C: sw          $t9, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r25;
L_800C2C60:
    // 0x800C2C60: addiu       $t0, $zero, 0x8
    ctx->r8 = ADD32(0, 0X8);
    // 0x800C2C64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2C68: sb          $t0, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r8;
    // 0x800C2C6C: jal         0x800C1EB8
    // 0x800C2C70: addiu       $a0, $zero, 0xF
    ctx->r4 = ADD32(0, 0XF);
    func_800C1EB8(rdram, ctx);
        goto after_111;
    // 0x800C2C70: addiu       $a0, $zero, 0xF
    ctx->r4 = ADD32(0, 0XF);
    after_111:
    // 0x800C2C74: b           L_800C2D74
    // 0x800C2C78: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
        goto L_800C2D74;
    // 0x800C2C78: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
L_800C2C7C:
    // 0x800C2C7C: andi        $t2, $t1, 0x1
    ctx->r10 = ctx->r9 & 0X1;
L_800C2C80:
    // 0x800C2C80: bne         $t2, $zero, L_800C2CCC
    if (ctx->r10 != 0) {
        // 0x800C2C84: addiu       $t7, $zero, 0x11
        ctx->r15 = ADD32(0, 0X11);
            goto L_800C2CCC;
    }
    // 0x800C2C84: addiu       $t7, $zero, 0x11
    ctx->r15 = ADD32(0, 0X11);
    // 0x800C2C88: addiu       $t3, $zero, 0x14
    ctx->r11 = ADD32(0, 0X14);
    // 0x800C2C8C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2C90: sw          $t3, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r11;
    // 0x800C2C94: jal         0x800C3500
    // 0x800C2C98: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    func_800C3500(rdram, ctx);
        goto after_112;
    // 0x800C2C98: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    after_112:
    // 0x800C2C9C: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x800C2CA0: lw          $t4, 0x7DC0($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7DC0);
    // 0x800C2CA4: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C2CA8: addiu       $t5, $zero, 0xF
    ctx->r13 = ADD32(0, 0XF);
    // 0x800C2CAC: bne         $t4, $at, L_800C2CC0
    if (ctx->r12 != ctx->r1) {
        // 0x800C2CB0: addiu       $t6, $zero, 0x2
        ctx->r14 = ADD32(0, 0X2);
            goto L_800C2CC0;
    }
    // 0x800C2CB0: addiu       $t6, $zero, 0x2
    ctx->r14 = ADD32(0, 0X2);
    // 0x800C2CB4: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2CB8: b           L_800C2CE8
    // 0x800C2CBC: sw          $t5, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r13;
        goto L_800C2CE8;
    // 0x800C2CBC: sw          $t5, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r13;
L_800C2CC0:
    // 0x800C2CC0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2CC4: b           L_800C2CE8
    // 0x800C2CC8: sw          $t6, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r14;
        goto L_800C2CE8;
    // 0x800C2CC8: sw          $t6, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r14;
L_800C2CCC:
    // 0x800C2CCC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2CD0: sw          $t7, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r15;
    // 0x800C2CD4: jal         0x800C3500
    // 0x800C2CD8: addiu       $a0, $zero, 0x14
    ctx->r4 = ADD32(0, 0X14);
    func_800C3500(rdram, ctx);
        goto after_113;
    // 0x800C2CD8: addiu       $a0, $zero, 0x14
    ctx->r4 = ADD32(0, 0X14);
    after_113:
    // 0x800C2CDC: addiu       $t8, $zero, 0x1E
    ctx->r24 = ADD32(0, 0X1E);
    // 0x800C2CE0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2CE4: sw          $t8, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r24;
L_800C2CE8:
    // 0x800C2CE8: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    // 0x800C2CEC: addiu       $at, $zero, 0x80
    ctx->r1 = ADD32(0, 0X80);
    // 0x800C2CF0: addiu       $t1, $zero, 0xA0
    ctx->r9 = ADD32(0, 0XA0);
    // 0x800C2CF4: andi        $t0, $t9, 0x80
    ctx->r8 = ctx->r25 & 0X80;
    // 0x800C2CF8: bne         $t0, $at, L_800C2D70
    if (ctx->r8 != ctx->r1) {
        // 0x800C2CFC: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_800C2D70;
    }
    // 0x800C2CFC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2D00: b           L_800C2D70
    // 0x800C2D04: sw          $t1, 0x7CB0($at)
    MEM_W(0X7CB0, ctx->r1) = ctx->r9;
        goto L_800C2D70;
    // 0x800C2D04: sw          $t1, 0x7CB0($at)
    MEM_W(0X7CB0, ctx->r1) = ctx->r9;
L_800C2D08:
    // 0x800C2D08: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2D0C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2D10: addiu       $v0, $v0, 0x7DF8
    ctx->r2 = ADD32(ctx->r2, 0X7DF8);
    // 0x800C2D14: sw          $t2, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r10;
    // 0x800C2D18: lb          $t3, 0x2($v0)
    ctx->r11 = MEM_B(ctx->r2, 0X2);
    // 0x800C2D1C: bne         $t3, $zero, L_800C2D2C
    if (ctx->r11 != 0) {
        // 0x800C2D20: nop
    
            goto L_800C2D2C;
    }
    // 0x800C2D20: nop

    // 0x800C2D24: lb          $t4, 0x1($v0)
    ctx->r12 = MEM_B(ctx->r2, 0X1);
    // 0x800C2D28: beq         $t4, $zero, L_800C2D4C
    if (ctx->r12 == 0) {
        // 0x800C2D2C: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C2D4C;
    }
L_800C2D2C:
    // 0x800C2D2C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2D30: addiu       $v0, $v0, 0x7E00
    ctx->r2 = ADD32(ctx->r2, 0X7E00);
    // 0x800C2D34: lb          $t5, 0x2($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X2);
    // 0x800C2D38: bne         $t5, $zero, L_800C2D5C
    if (ctx->r13 != 0) {
        // 0x800C2D3C: nop
    
            goto L_800C2D5C;
    }
    // 0x800C2D3C: nop

    // 0x800C2D40: lb          $t6, 0x1($v0)
    ctx->r14 = MEM_B(ctx->r2, 0X1);
    // 0x800C2D44: bne         $t6, $zero, L_800C2D5C
    if (ctx->r14 != 0) {
        // 0x800C2D48: nop
    
            goto L_800C2D5C;
    }
    // 0x800C2D48: nop

L_800C2D4C:
    // 0x800C2D4C: jal         0x800C3500
    // 0x800C2D50: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    func_800C3500(rdram, ctx);
        goto after_114;
    // 0x800C2D50: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    after_114:
    // 0x800C2D54: b           L_800C2D68
    // 0x800C2D58: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
        goto L_800C2D68;
    // 0x800C2D58: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
L_800C2D5C:
    // 0x800C2D5C: jal         0x800C3500
    // 0x800C2D60: addiu       $a0, $zero, 0xE
    ctx->r4 = ADD32(0, 0XE);
    func_800C3500(rdram, ctx);
        goto after_115;
    // 0x800C2D60: addiu       $a0, $zero, 0xE
    ctx->r4 = ADD32(0, 0XE);
    after_115:
    // 0x800C2D64: addiu       $t7, $zero, 0xA
    ctx->r15 = ADD32(0, 0XA);
L_800C2D68:
    // 0x800C2D68: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C2D6C: sw          $t7, 0x7CDC($at)
    MEM_W(0X7CDC, ctx->r1) = ctx->r15;
L_800C2D70:
    // 0x800C2D70: lw          $t8, 0x24($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X24);
L_800C2D74:
    // 0x800C2D74: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2D78: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800C2D7C: lw          $a0, 0x7DCC($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X7DCC);
    // 0x800C2D80: jal         0x800C14D0
    // 0x800C2D84: sw          $t8, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r24;
    func_800C14D0(rdram, ctx);
        goto after_116;
    // 0x800C2D84: sw          $t8, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r24;
    after_116:
    // 0x800C2D88: b           L_800C2E8C
    // 0x800C2D8C: nop

        goto L_800C2E8C;
    // 0x800C2D8C: nop

L_800C2D90:
    // 0x800C2D90: lui         $a0, 0x4601
    ctx->r4 = S32(0X4601 << 16);
    // 0x800C2D94: jal         0x800C53D4
    // 0x800C2D98: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_117;
    // 0x800C2D98: addiu       $a1, $zero, 0x12
    ctx->r5 = ADD32(0, 0X12);
    after_117:
    // 0x800C2D9C: jal         0x800C13AC
    // 0x800C2DA0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_118;
    // 0x800C2DA0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_118:
    // 0x800C2DA4: b           L_800C2E8C
    // 0x800C2DA8: nop

        goto L_800C2E8C;
    // 0x800C2DA8: nop

L_800C2DAC:
    // 0x800C2DAC: jal         0x800C1698
    // 0x800C2DB0: nop

    func_800C1698(rdram, ctx);
        goto after_119;
    // 0x800C2DB0: nop

    after_119:
    // 0x800C2DB4: jal         0x800C1714
    // 0x800C2DB8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    func_800C1714(rdram, ctx);
        goto after_120;
    // 0x800C2DB8: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_120:
    // 0x800C2DBC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C2DC0: lw          $v0, -0x4CC8($v0)
    ctx->r2 = MEM_W(ctx->r2, -0X4CC8);
    // 0x800C2DC4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C2DC8: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    // 0x800C2DCC: beql        $v0, $zero, L_800C2DF0
    if (ctx->r2 == 0) {
        // 0x800C2DD0: addiu       $at, $zero, 0x4
        ctx->r1 = ADD32(0, 0X4);
            goto L_800C2DF0;
    }
    goto skip_5;
    // 0x800C2DD0: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    skip_5:
    // 0x800C2DD4: beq         $v0, $at, L_800C2DEC
    if (ctx->r2 == ctx->r1) {
        // 0x800C2DD8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C2DEC;
    }
    // 0x800C2DD8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C2DDC: beq         $v0, $at, L_800C2E14
    if (ctx->r2 == ctx->r1) {
        // 0x800C2DE0: nop
    
            goto L_800C2E14;
    }
    // 0x800C2DE0: nop

    // 0x800C2DE4: b           L_800C2E1C
    // 0x800C2DE8: nop

        goto L_800C2E1C;
    // 0x800C2DE8: nop

L_800C2DEC:
    // 0x800C2DEC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
L_800C2DF0:
    // 0x800C2DF0: bne         $t9, $at, L_800C2E08
    if (ctx->r25 != ctx->r1) {
        // 0x800C2DF4: addiu       $t1, $zero, 0x1
        ctx->r9 = ADD32(0, 0X1);
            goto L_800C2E08;
    }
    // 0x800C2DF4: addiu       $t1, $zero, 0x1
    ctx->r9 = ADD32(0, 0X1);
    // 0x800C2DF8: addiu       $t0, $zero, 0x2
    ctx->r8 = ADD32(0, 0X2);
    // 0x800C2DFC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E00: b           L_800C2E1C
    // 0x800C2E04: sw          $t0, 0x7DD4($at)
    MEM_W(0X7DD4, ctx->r1) = ctx->r8;
        goto L_800C2E1C;
    // 0x800C2E04: sw          $t0, 0x7DD4($at)
    MEM_W(0X7DD4, ctx->r1) = ctx->r8;
L_800C2E08:
    // 0x800C2E08: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E0C: b           L_800C2E1C
    // 0x800C2E10: sw          $t1, 0x7DD4($at)
    MEM_W(0X7DD4, ctx->r1) = ctx->r9;
        goto L_800C2E1C;
    // 0x800C2E10: sw          $t1, 0x7DD4($at)
    MEM_W(0X7DD4, ctx->r1) = ctx->r9;
L_800C2E14:
    // 0x800C2E14: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E18: sw          $zero, 0x7DD4($at)
    MEM_W(0X7DD4, ctx->r1) = 0;
L_800C2E1C:
    // 0x800C2E1C: jal         0x800C141C
    // 0x800C2E20: nop

    func_800C141C(rdram, ctx);
        goto after_121;
    // 0x800C2E20: nop

    after_121:
    // 0x800C2E24: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E28: lw          $t2, 0x24($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X24);
    // 0x800C2E2C: sw          $zero, 0x7E18($at)
    MEM_W(0X7E18, ctx->r1) = 0;
    // 0x800C2E30: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E34: sw          $zero, 0x7E14($at)
    MEM_W(0X7E14, ctx->r1) = 0;
    // 0x800C2E38: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C2E3C: addiu       $t3, $t2, -0x1
    ctx->r11 = ADD32(ctx->r10, -0X1);
    // 0x800C2E40: sw          $t3, 0x7DC8($at)
    MEM_W(0X7DC8, ctx->r1) = ctx->r11;
    // 0x800C2E44: jal         0x800C14D0
    // 0x800C2E48: addiu       $a0, $zero, 0x1C
    ctx->r4 = ADD32(0, 0X1C);
    func_800C14D0(rdram, ctx);
        goto after_122;
    // 0x800C2E48: addiu       $a0, $zero, 0x1C
    ctx->r4 = ADD32(0, 0X1C);
    after_122:
    // 0x800C2E4C: b           L_800C2E8C
    // 0x800C2E50: nop

        goto L_800C2E8C;
    // 0x800C2E50: nop

L_800C2E54:
    // 0x800C2E54: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C2E58: bne         $v1, $at, L_800C2E8C
    if (ctx->r3 != ctx->r1) {
        // 0x800C2E5C: nop
    
            goto L_800C2E8C;
    }
    // 0x800C2E5C: nop

    // 0x800C2E60: jal         0x800C1698
    // 0x800C2E64: nop

    func_800C1698(rdram, ctx);
        goto after_123;
    // 0x800C2E64: nop

    after_123:
    // 0x800C2E68: jal         0x800C13AC
    // 0x800C2E6C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_124;
    // 0x800C2E6C: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_124:
    // 0x800C2E70: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x800C2E74: jal         0x800C1500
    // 0x800C2E78: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C1500(rdram, ctx);
        goto after_125;
    // 0x800C2E78: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_125:
    // 0x800C2E7C: b           L_800C2E8C
    // 0x800C2E80: nop

        goto L_800C2E8C;
    // 0x800C2E80: nop

L_800C2E84:
    // 0x800C2E84: jal         0x800C1698
    // 0x800C2E88: nop

    func_800C1698(rdram, ctx);
        goto after_126;
    // 0x800C2E88: nop

    after_126:
L_800C2E8C:
    // 0x800C2E8C: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C2E90: lb          $v0, 0x7C94($v0)
    ctx->r2 = MEM_B(ctx->r2, 0X7C94);
    // 0x800C2E94: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C2E98: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2E9C: beq         $v0, $at, L_800C2EC0
    if (ctx->r2 == ctx->r1) {
        // 0x800C2EA0: ori         $a0, $a0, 0xC05
        ctx->r4 = ctx->r4 | 0XC05;
            goto L_800C2EC0;
    }
    // 0x800C2EA0: ori         $a0, $a0, 0xC05
    ctx->r4 = ctx->r4 | 0XC05;
    // 0x800C2EA4: addiu       $at, $zero, 0x6
    ctx->r1 = ADD32(0, 0X6);
    // 0x800C2EA8: beq         $v0, $at, L_800C2EC0
    if (ctx->r2 == ctx->r1) {
        // 0x800C2EAC: addiu       $at, $zero, 0xB
        ctx->r1 = ADD32(0, 0XB);
            goto L_800C2EC0;
    }
    // 0x800C2EAC: addiu       $at, $zero, 0xB
    ctx->r1 = ADD32(0, 0XB);
    // 0x800C2EB0: beq         $v0, $at, L_800C2EC0
    if (ctx->r2 == ctx->r1) {
        // 0x800C2EB4: nop
    
            goto L_800C2EC0;
    }
    // 0x800C2EB4: nop

    // 0x800C2EB8: bne         $v0, $zero, L_800C2ED0
    if (ctx->r2 != 0) {
        // 0x800C2EBC: addiu       $a1, $zero, 0x1
        ctx->r5 = ADD32(0, 0X1);
            goto L_800C2ED0;
    }
    // 0x800C2EBC: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_800C2EC0:
    // 0x800C2EC0: jal         0x800C53D4
    // 0x800C2EC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_127;
    // 0x800C2EC4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_127:
    // 0x800C2EC8: b           L_800C2EE0
    // 0x800C2ECC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C2EE0;
    // 0x800C2ECC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2ED0:
    // 0x800C2ED0: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2ED4: jal         0x800C53D4
    // 0x800C2ED8: ori         $a0, $a0, 0xC05
    ctx->r4 = ctx->r4 | 0XC05;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_128;
    // 0x800C2ED8: ori         $a0, $a0, 0xC05
    ctx->r4 = ctx->r4 | 0XC05;
    after_128:
L_800C2EDC:
    // 0x800C2EDC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C2EE0:
    // 0x800C2EE0: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C2EE4: jr          $ra
    // 0x800C2EE8: nop

    return;
    // 0x800C2EE8: nop

;}
RECOMP_FUNC void func_800C2EEC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C2EEC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C2EF0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C2EF4: jal         0x800C1488
    // 0x800C2EF8: nop

    func_800C1488(rdram, ctx);
        goto after_0;
    // 0x800C2EF8: nop

    after_0:
    // 0x800C2EFC: lui         $a0, 0x8200
    ctx->r4 = S32(0X8200 << 16);
    // 0x800C2F00: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C2F04: jal         0x800C53B0
    // 0x800C2F08: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_1;
    // 0x800C2F08: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x800C2F0C: jal         0x800C5404
    // 0x800C2F10: nop

    AudioThread_ScheduleProcessCmds(rdram, ctx);
        goto after_2;
    // 0x800C2F10: nop

    after_2:
    // 0x800C2F14: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C2F18: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C2F1C: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C2F20: jal         0x800C5C60
    // 0x800C2F24: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_3;
    // 0x800C2F24: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800C2F28: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C2F2C: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C2F30: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C2F34: jal         0x800C5C60
    // 0x800C2F38: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_4;
    // 0x800C2F38: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_4:
    // 0x800C2F3C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C2F40: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C2F44: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    // 0x800C2F48: jal         0x800C5C60
    // 0x800C2F4C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_5;
    // 0x800C2F4C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_5:
    // 0x800C2F50: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C2F54: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C2F58: jr          $ra
    // 0x800C2F5C: nop

    return;
    // 0x800C2F5C: nop

;}
RECOMP_FUNC void func_800C2F60(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C2F60: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C2F64: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C2F68: sll         $a1, $a1, 24
    ctx->r5 = S32(ctx->r5 << 24);
    // 0x800C2F6C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C2F70: sra         $t6, $a1, 24
    ctx->r14 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C2F74: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2F78: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C2F7C: ori         $a0, $a0, 0x2
    ctx->r4 = ctx->r4 | 0X2;
    // 0x800C2F80: jal         0x800C53D4
    // 0x800C2F84: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C2F84: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    after_0:
    // 0x800C2F88: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2F8C: ori         $a0, $a0, 0x1
    ctx->r4 = ctx->r4 | 0X1;
    // 0x800C2F90: jal         0x800C53D4
    // 0x800C2F94: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C2F94: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    after_1:
    // 0x800C2F98: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2F9C: jal         0x800C53D4
    // 0x800C2FA0: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C2FA0: lb          $a1, 0x23($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X23);
    after_2:
    // 0x800C2FA4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C2FA8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C2FAC: jr          $ra
    // 0x800C2FB0: nop

    return;
    // 0x800C2FB0: nop

;}
RECOMP_FUNC void func_800C2FB4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C2FB4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C2FB8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C2FBC: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C2FC0: ori         $a0, $a0, 0x4
    ctx->r4 = ctx->r4 | 0X4;
    // 0x800C2FC4: jal         0x800C53D4
    // 0x800C2FC8: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C2FC8: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    after_0:
    // 0x800C2FCC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C2FD0: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C2FD4: jr          $ra
    // 0x800C2FD8: nop

    return;
    // 0x800C2FD8: nop

;}
RECOMP_FUNC void func_800C2FDC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C2FDC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C2FE0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C2FE4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C2FE8: lw          $a1, 0x18($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X18);
    // 0x800C2FEC: jal         0x800C53B0
    // 0x800C2FF0: lui         $a0, 0xF000
    ctx->r4 = S32(0XF000 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C2FF0: lui         $a0, 0xF000
    ctx->r4 = S32(0XF000 << 16);
    after_0:
    // 0x800C2FF4: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C2FF8: jal         0x800C377C
    // 0x800C2FFC: addiu       $a0, $a0, 0x1A
    ctx->r4 = ADD32(ctx->r4, 0X1A);
    func_800C377C(rdram, ctx);
        goto after_1;
    // 0x800C2FFC: addiu       $a0, $a0, 0x1A
    ctx->r4 = ADD32(ctx->r4, 0X1A);
    after_1:
    // 0x800C3000: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3004: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3008: jr          $ra
    // 0x800C300C: nop

    return;
    // 0x800C300C: nop

;}
RECOMP_FUNC void func_800C3010(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3010: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3014: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3018: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x800C301C: jal         0x800C53B0
    // 0x800C3020: lui         $a0, 0xF000
    ctx->r4 = S32(0XF000 << 16);
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_0;
    // 0x800C3020: lui         $a0, 0xF000
    ctx->r4 = S32(0XF000 << 16);
    after_0:
    // 0x800C3024: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3028: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C302C: jr          $ra
    // 0x800C3030: nop

    return;
    // 0x800C3030: nop

;}
RECOMP_FUNC void leoInitUnit_atten(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3034: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800C3038: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C303C: jr          $ra
    // 0x800C3040: sw          $t6, 0x7C98($at)
    MEM_W(0X7C98, ctx->r1) = ctx->r14;
    return;
    // 0x800C3040: sw          $t6, 0x7C98($at)
    MEM_W(0X7C98, ctx->r1) = ctx->r14;
;}
RECOMP_FUNC void myfree(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3044: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3048: jr          $ra
    // 0x800C304C: sw          $zero, 0x7C98($at)
    MEM_W(0X7C98, ctx->r1) = 0;
    return;
    // 0x800C304C: sw          $zero, 0x7C98($at)
    MEM_W(0X7C98, ctx->r1) = 0;
;}
RECOMP_FUNC void func_800C3050(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3050: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3054: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3058: blez        $a0, L_800C308C
    if (SIGNED(ctx->r4) <= 0) {
        // 0x800C305C: sw          $a0, 0x18($sp)
        MEM_W(0X18, ctx->r29) = ctx->r4;
            goto L_800C308C;
    }
    // 0x800C305C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C3060: jal         0x800C1650
    // 0x800C3064: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
    func_800C1650(rdram, ctx);
        goto after_0;
    // 0x800C3064: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
    after_0:
    // 0x800C3068: jal         0x800C1674
    // 0x800C306C: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_1;
    // 0x800C306C: addiu       $a0, $zero, 0x40
    ctx->r4 = ADD32(0, 0X40);
    after_1:
    // 0x800C3070: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C3074: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    // 0x800C3078: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800C307C: jal         0x800C1540
    // 0x800C3080: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    func_800C1540(rdram, ctx);
        goto after_2;
    // 0x800C3080: addiu       $a0, $a0, 0x2
    ctx->r4 = ADD32(ctx->r4, 0X2);
    after_2:
    // 0x800C3084: b           L_800C30A4
    // 0x800C3088: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
        goto L_800C30A4;
    // 0x800C3088: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
L_800C308C:
    // 0x800C308C: lw          $t7, 0x18($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X18);
    // 0x800C3090: bnel        $t7, $zero, L_800C30A4
    if (ctx->r15 != 0) {
        // 0x800C3094: lw          $t8, 0x18($sp)
        ctx->r24 = MEM_W(ctx->r29, 0X18);
            goto L_800C30A4;
    }
    goto skip_0;
    // 0x800C3094: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    skip_0:
    // 0x800C3098: jal         0x800C1674
    // 0x800C309C: addiu       $a0, $zero, 0x100
    ctx->r4 = ADD32(0, 0X100);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_3;
    // 0x800C309C: addiu       $a0, $zero, 0x100
    ctx->r4 = ADD32(0, 0X100);
    after_3:
    // 0x800C30A0: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
L_800C30A4:
    // 0x800C30A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C30A8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C30AC: addiu       $t9, $t8, 0x2
    ctx->r25 = ADD32(ctx->r24, 0X2);
    // 0x800C30B0: sw          $t9, 0x7DCC($at)
    MEM_W(0X7DCC, ctx->r1) = ctx->r25;
    // 0x800C30B4: jr          $ra
    // 0x800C30B8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800C30B8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800C30BC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C30BC: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C30C0: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C30C4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C30C8: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C30CC: bne         $t6, $at, L_800C30E8
    if (ctx->r14 != ctx->r1) {
        // 0x800C30D0: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C30E8;
    }
    // 0x800C30D0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C30D4: jal         0x800C1650
    // 0x800C30D8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1650(rdram, ctx);
        goto after_0;
    // 0x800C30D8: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_0:
    // 0x800C30DC: addiu       $a0, $zero, 0x13
    ctx->r4 = ADD32(0, 0X13);
    // 0x800C30E0: jal         0x800C15C8
    // 0x800C30E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_1;
    // 0x800C30E4: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
L_800C30E8:
    // 0x800C30E8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C30EC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C30F0: jr          $ra
    // 0x800C30F4: nop

    return;
    // 0x800C30F4: nop

;}
RECOMP_FUNC void func_800C30F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C30F8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C30FC: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C3100: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3104: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C3108: bne         $t6, $at, L_800C311C
    if (ctx->r14 != ctx->r1) {
        // 0x800C310C: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C311C;
    }
    // 0x800C310C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3110: addiu       $a0, $zero, 0x16
    ctx->r4 = ADD32(0, 0X16);
    // 0x800C3114: jal         0x800C1500
    // 0x800C3118: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    func_800C1500(rdram, ctx);
        goto after_0;
    // 0x800C3118: addiu       $a1, $zero, 0x28
    ctx->r5 = ADD32(0, 0X28);
    after_0:
L_800C311C:
    // 0x800C311C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3120: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3124: jr          $ra
    // 0x800C3128: nop

    return;
    // 0x800C3128: nop

;}
RECOMP_FUNC void func_800C312C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C312C: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C3130: lhu         $t6, 0x7DEC($t6)
    ctx->r14 = MEM_HU(ctx->r14, 0X7DEC);
    // 0x800C3134: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3138: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C313C: bne         $t6, $at, L_800C315C
    if (ctx->r14 != ctx->r1) {
        // 0x800C3140: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C315C;
    }
    // 0x800C3140: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3144: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C3148: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C314C: jal         0x800C53D4
    // 0x800C3150: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C3150: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    after_0:
    // 0x800C3154: b           L_800C3170
    // 0x800C3158: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3170;
    // 0x800C3158: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C315C:
    // 0x800C315C: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C3160: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C3164: jal         0x800C53D4
    // 0x800C3168: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C3168: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_1:
    // 0x800C316C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3170:
    // 0x800C3170: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3174: jr          $ra
    // 0x800C3178: nop

    return;
    // 0x800C3178: nop

;}
RECOMP_FUNC void func_800C317C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C317C: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C3180: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3184: beq         $a0, $zero, L_800C31A0
    if (ctx->r4 == 0) {
        // 0x800C3188: sw          $a1, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r5;
            goto L_800C31A0;
    }
    // 0x800C3188: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x800C318C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800C3190: beq         $a0, $v0, L_800C31F0
    if (ctx->r4 == ctx->r2) {
        // 0x800C3194: lui         $t8, 0x801D
        ctx->r24 = S32(0X801D << 16);
            goto L_800C31F0;
    }
    // 0x800C3194: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C3198: b           L_800C3234
    // 0x800C319C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3234;
    // 0x800C319C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C31A0:
    // 0x800C31A0: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C31A4: lw          $t6, 0x7DC0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC0);
    // 0x800C31A8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800C31AC: bnel        $v0, $t6, L_800C31C0
    if (ctx->r2 != ctx->r14) {
        // 0x800C31B0: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800C31C0;
    }
    goto skip_0;
    // 0x800C31B0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    skip_0:
    // 0x800C31B4: b           L_800C31C0
    // 0x800C31B8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_800C31C0;
    // 0x800C31B8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800C31BC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800C31C0:
    // 0x800C31C0: jal         0x800C312C
    // 0x800C31C4: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    func_800C312C(rdram, ctx);
        goto after_0;
    // 0x800C31C4: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    after_0:
    // 0x800C31C8: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x800C31CC: lui         $at, 0x600
    ctx->r1 = S32(0X600 << 16);
    // 0x800C31D0: ori         $at, $at, 0xA00
    ctx->r1 = ctx->r1 | 0XA00;
    // 0x800C31D4: andi        $a0, $v0, 0xFF
    ctx->r4 = ctx->r2 & 0XFF;
    // 0x800C31D8: or          $t7, $a0, $at
    ctx->r15 = ctx->r4 | ctx->r1;
    // 0x800C31DC: or          $a0, $t7, $zero
    ctx->r4 = ctx->r15 | 0;
    // 0x800C31E0: jal         0x800C53D4
    // 0x800C31E4: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C31E4: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_1:
    // 0x800C31E8: b           L_800C3234
    // 0x800C31EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3234;
    // 0x800C31EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C31F0:
    // 0x800C31F0: lhu         $t8, 0x7DEE($t8)
    ctx->r24 = MEM_HU(ctx->r24, 0X7DEE);
    // 0x800C31F4: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C31F8: addiu       $a1, $zero, 0x66
    ctx->r5 = ADD32(0, 0X66);
    // 0x800C31FC: bne         $v0, $t8, L_800C3218
    if (ctx->r2 != ctx->r24) {
        // 0x800C3200: ori         $a0, $a0, 0xA00
        ctx->r4 = ctx->r4 | 0XA00;
            goto L_800C3218;
    }
    // 0x800C3200: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C3204: lui         $a0, 0x500
    ctx->r4 = S32(0X500 << 16);
    // 0x800C3208: jal         0x800C53D4
    // 0x800C320C: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C320C: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    after_2:
    // 0x800C3210: b           L_800C3224
    // 0x800C3214: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
        goto L_800C3224;
    // 0x800C3214: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
L_800C3218:
    // 0x800C3218: jal         0x800C53D4
    // 0x800C321C: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800C321C: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    after_3:
    // 0x800C3220: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
L_800C3224:
    // 0x800C3224: ori         $a0, $a0, 0xA02
    ctx->r4 = ctx->r4 | 0XA02;
    // 0x800C3228: jal         0x800C53D4
    // 0x800C322C: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800C322C: lb          $a1, 0x27($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X27);
    after_4:
    // 0x800C3230: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3234:
    // 0x800C3234: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C3238: jr          $ra
    // 0x800C323C: nop

    return;
    // 0x800C323C: nop

;}
RECOMP_FUNC void func_800C3240(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3240: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3244: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3248: jal         0x800C312C
    // 0x800C324C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800C312C(rdram, ctx);
        goto after_0;
    // 0x800C324C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800C3250: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3254: ori         $a0, $a0, 0xA01
    ctx->r4 = ctx->r4 | 0XA01;
    // 0x800C3258: jal         0x800C53D4
    // 0x800C325C: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C325C: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    after_1:
    // 0x800C3260: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3264: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3268: jr          $ra
    // 0x800C326C: nop

    return;
    // 0x800C326C: nop

;}
RECOMP_FUNC void func_800C3270(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3270: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3274: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3278: jal         0x800C312C
    // 0x800C327C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    func_800C312C(rdram, ctx);
        goto after_0;
    // 0x800C327C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    after_0:
    // 0x800C3280: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3284: ori         $a0, $a0, 0xA02
    ctx->r4 = ctx->r4 | 0XA02;
    // 0x800C3288: jal         0x800C53D4
    // 0x800C328C: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C328C: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    after_1:
    // 0x800C3290: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3294: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3298: jr          $ra
    // 0x800C329C: nop

    return;
    // 0x800C329C: nop

;}
RECOMP_FUNC void func_800C32A0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C32A0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C32A4: addiu       $v1, $v1, 0x7DF0
    ctx->r3 = ADD32(ctx->r3, 0X7DF0);
    // 0x800C32A8: lbu         $a3, 0x2($v1)
    ctx->r7 = MEM_BU(ctx->r3, 0X2);
    // 0x800C32AC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C32B0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C32B4: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C32B8: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C32BC: beq         $a3, $zero, L_800C32DC
    if (ctx->r7 == 0) {
        // 0x800C32C0: sw          $a2, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r6;
            goto L_800C32DC;
    }
    // 0x800C32C0: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C32C4: lbu         $t7, 0x1($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X1);
    // 0x800C32C8: slt         $at, $a1, $t7
    ctx->r1 = SIGNED(ctx->r5) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800C32CC: beql        $at, $zero, L_800C32E0
    if (ctx->r1 == 0) {
        // 0x800C32D0: lui         $a0, 0x600
        ctx->r4 = S32(0X600 << 16);
            goto L_800C32E0;
    }
    goto skip_0;
    // 0x800C32D0: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    skip_0:
    // 0x800C32D4: b           L_800C3310
    // 0x800C32D8: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
        goto L_800C3310;
    // 0x800C32D8: or          $v0, $a3, $zero
    ctx->r2 = ctx->r7 | 0;
L_800C32DC:
    // 0x800C32DC: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
L_800C32E0:
    // 0x800C32E0: ori         $a0, $a0, 0xC00
    ctx->r4 = ctx->r4 | 0XC00;
    // 0x800C32E4: jal         0x800C53D4
    // 0x800C32E8: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C32E8: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    after_0:
    // 0x800C32EC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C32F0: lw          $t8, 0x18($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X18);
    // 0x800C32F4: lw          $t9, 0x1C($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X1C);
    // 0x800C32F8: lw          $t0, 0x20($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X20);
    // 0x800C32FC: addiu       $v1, $v1, 0x7DF0
    ctx->r3 = ADD32(ctx->r3, 0X7DF0);
    // 0x800C3300: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x800C3304: sb          $t8, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r24;
    // 0x800C3308: sb          $t9, 0x1($v1)
    MEM_B(0X1, ctx->r3) = ctx->r25;
    // 0x800C330C: sb          $t0, 0x2($v1)
    MEM_B(0X2, ctx->r3) = ctx->r8;
L_800C3310:
    // 0x800C3310: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3314: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3318: jr          $ra
    // 0x800C331C: nop

    return;
    // 0x800C331C: nop

;}
RECOMP_FUNC void func_800C3320(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3320: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C3324: lw          $t6, 0x7DC4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC4);
    // 0x800C3328: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C332C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3330: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C3334: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C3338: beq         $t6, $zero, L_800C337C
    if (ctx->r14 == 0) {
        // 0x800C333C: sw          $a2, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r6;
            goto L_800C337C;
    }
    // 0x800C333C: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C3340: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C3344: lb          $t7, 0x7C94($t7)
    ctx->r15 = MEM_B(ctx->r15, 0X7C94);
    // 0x800C3348: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C334C: bnel        $t7, $at, L_800C3380
    if (ctx->r15 != ctx->r1) {
        // 0x800C3350: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C3380;
    }
    goto skip_0;
    // 0x800C3350: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C3354: jal         0x800C32A0
    // 0x800C3358: nop

    func_800C32A0(rdram, ctx);
        goto after_0;
    // 0x800C3358: nop

    after_0:
    // 0x800C335C: beq         $v0, $zero, L_800C337C
    if (ctx->r2 == 0) {
        // 0x800C3360: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800C337C;
    }
    // 0x800C3360: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800C3364: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x800C3368: beq         $at, $zero, L_800C337C
    if (ctx->r1 == 0) {
        // 0x800C336C: lw          $a0, 0x18($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X18);
            goto L_800C337C;
    }
    // 0x800C336C: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C3370: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x800C3374: jal         0x800C33C8
    // 0x800C3378: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    func_800C33C8(rdram, ctx);
        goto after_1;
    // 0x800C3378: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    after_1:
L_800C337C:
    // 0x800C337C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3380:
    // 0x800C3380: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3384: jr          $ra
    // 0x800C3388: nop

    return;
    // 0x800C3388: nop

;}
RECOMP_FUNC void func_800C338C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C338C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3390: addiu       $v0, $v0, 0x7DF4
    ctx->r2 = ADD32(ctx->r2, 0X7DF4);
    // 0x800C3394: lbu         $t6, 0x2($v0)
    ctx->r14 = MEM_BU(ctx->r2, 0X2);
    // 0x800C3398: beql        $t6, $zero, L_800C33B4
    if (ctx->r14 == 0) {
        // 0x800C339C: sb          $a0, 0x0($v0)
        MEM_B(0X0, ctx->r2) = ctx->r4;
            goto L_800C33B4;
    }
    goto skip_0;
    // 0x800C339C: sb          $a0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r4;
    skip_0:
    // 0x800C33A0: lbu         $t7, 0x1($v0)
    ctx->r15 = MEM_BU(ctx->r2, 0X1);
    // 0x800C33A4: slt         $at, $a2, $t7
    ctx->r1 = SIGNED(ctx->r6) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x800C33A8: bne         $at, $zero, L_800C33C0
    if (ctx->r1 != 0) {
        // 0x800C33AC: nop
    
            goto L_800C33C0;
    }
    // 0x800C33AC: nop

    // 0x800C33B0: sb          $a0, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r4;
L_800C33B4:
    // 0x800C33B4: sb          $a2, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r6;
    // 0x800C33B8: sb          $a1, 0x3($v0)
    MEM_B(0X3, ctx->r2) = ctx->r5;
    // 0x800C33BC: sb          $a3, 0x2($v0)
    MEM_B(0X2, ctx->r2) = ctx->r7;
L_800C33C0:
    // 0x800C33C0: jr          $ra
    // 0x800C33C4: nop

    return;
    // 0x800C33C4: nop

;}
RECOMP_FUNC void func_800C33C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C33C8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C33CC: lw          $t6, 0x7DC4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC4);
    // 0x800C33D0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C33D4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C33D8: beq         $t6, $zero, L_800C33F8
    if (ctx->r14 == 0) {
        // 0x800C33DC: lui         $t7, 0x800E
        ctx->r15 = S32(0X800E << 16);
            goto L_800C33F8;
    }
    // 0x800C33DC: lui         $t7, 0x800E
    ctx->r15 = S32(0X800E << 16);
    // 0x800C33E0: lb          $t7, 0x7C94($t7)
    ctx->r15 = MEM_B(ctx->r15, 0X7C94);
    // 0x800C33E4: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C33E8: bnel        $t7, $at, L_800C33FC
    if (ctx->r15 != ctx->r1) {
        // 0x800C33EC: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C33FC;
    }
    goto skip_0;
    // 0x800C33EC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C33F0: jal         0x800C338C
    // 0x800C33F4: nop

    func_800C338C(rdram, ctx);
        goto after_0;
    // 0x800C33F4: nop

    after_0:
L_800C33F8:
    // 0x800C33F8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C33FC:
    // 0x800C33FC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3400: jr          $ra
    // 0x800C3404: nop

    return;
    // 0x800C3404: nop

;}
RECOMP_FUNC void func_800C3408(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3408: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C340C: lw          $t6, 0x7DC0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC0);
    // 0x800C3410: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3414: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3418: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C341C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x800C3420: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C3424: bne         $t6, $at, L_800C3454
    if (ctx->r14 != ctx->r1) {
        // 0x800C3428: sw          $a2, 0x20($sp)
        MEM_W(0X20, ctx->r29) = ctx->r6;
            goto L_800C3454;
    }
    // 0x800C3428: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x800C342C: jal         0x800C32A0
    // 0x800C3430: nop

    func_800C32A0(rdram, ctx);
        goto after_0;
    // 0x800C3430: nop

    after_0:
    // 0x800C3434: beq         $v0, $zero, L_800C3454
    if (ctx->r2 == 0) {
        // 0x800C3438: or          $a1, $v0, $zero
        ctx->r5 = ctx->r2 | 0;
            goto L_800C3454;
    }
    // 0x800C3438: or          $a1, $v0, $zero
    ctx->r5 = ctx->r2 | 0;
    // 0x800C343C: slti        $at, $v0, 0x5
    ctx->r1 = SIGNED(ctx->r2) < 0X5 ? 1 : 0;
    // 0x800C3440: beq         $at, $zero, L_800C3454
    if (ctx->r1 == 0) {
        // 0x800C3444: lw          $a0, 0x18($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X18);
            goto L_800C3454;
    }
    // 0x800C3444: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x800C3448: lw          $a2, 0x1C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X1C);
    // 0x800C344C: jal         0x800C33C8
    // 0x800C3450: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    func_800C33C8(rdram, ctx);
        goto after_1;
    // 0x800C3450: lw          $a3, 0x20($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X20);
    after_1:
L_800C3454:
    // 0x800C3454: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3458: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C345C: jr          $ra
    // 0x800C3460: nop

    return;
    // 0x800C3460: nop

;}
RECOMP_FUNC void func_800C3464(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3464: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C3468: lw          $t6, 0x7DC0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC0);
    // 0x800C346C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3470: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3474: bne         $t6, $at, L_800C3484
    if (ctx->r14 != ctx->r1) {
        // 0x800C3478: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C3484;
    }
    // 0x800C3478: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C347C: jal         0x800C338C
    // 0x800C3480: nop

    func_800C338C(rdram, ctx);
        goto after_0;
    // 0x800C3480: nop

    after_0:
L_800C3484:
    // 0x800C3484: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3488: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C348C: jr          $ra
    // 0x800C3490: nop

    return;
    // 0x800C3490: nop

;}
RECOMP_FUNC void func_800C3494(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3494: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C3498: addiu       $v1, $v1, 0x7DF4
    ctx->r3 = ADD32(ctx->r3, 0X7DF4);
    // 0x800C349C: lbu         $v0, 0x3($v1)
    ctx->r2 = MEM_BU(ctx->r3, 0X3);
    // 0x800C34A0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C34A4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C34A8: beq         $v0, $zero, L_800C34D8
    if (ctx->r2 == 0) {
        // 0x800C34AC: addiu       $t6, $v0, -0x1
        ctx->r14 = ADD32(ctx->r2, -0X1);
            goto L_800C34D8;
    }
    // 0x800C34AC: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    // 0x800C34B0: andi        $t7, $t6, 0xFF
    ctx->r15 = ctx->r14 & 0XFF;
    // 0x800C34B4: bne         $t7, $zero, L_800C34D8
    if (ctx->r15 != 0) {
        // 0x800C34B8: sb          $t6, 0x3($v1)
        MEM_B(0X3, ctx->r3) = ctx->r14;
            goto L_800C34D8;
    }
    // 0x800C34B8: sb          $t6, 0x3($v1)
    MEM_B(0X3, ctx->r3) = ctx->r14;
    // 0x800C34BC: lbu         $a0, 0x0($v1)
    ctx->r4 = MEM_BU(ctx->r3, 0X0);
    // 0x800C34C0: lbu         $a1, 0x1($v1)
    ctx->r5 = MEM_BU(ctx->r3, 0X1);
    // 0x800C34C4: jal         0x800C32A0
    // 0x800C34C8: lbu         $a2, 0x2($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0X2);
    func_800C32A0(rdram, ctx);
        goto after_0;
    // 0x800C34C8: lbu         $a2, 0x2($v1)
    ctx->r6 = MEM_BU(ctx->r3, 0X2);
    after_0:
    // 0x800C34CC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C34D0: addiu       $v1, $v1, 0x7DF4
    ctx->r3 = ADD32(ctx->r3, 0X7DF4);
    // 0x800C34D4: sb          $v0, 0x2($v1)
    MEM_B(0X2, ctx->r3) = ctx->r2;
L_800C34D8:
    // 0x800C34D8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C34DC: addiu       $v1, $v1, 0x7DF0
    ctx->r3 = ADD32(ctx->r3, 0X7DF0);
    // 0x800C34E0: lbu         $v0, 0x2($v1)
    ctx->r2 = MEM_BU(ctx->r3, 0X2);
    // 0x800C34E4: beq         $v0, $zero, L_800C34F0
    if (ctx->r2 == 0) {
        // 0x800C34E8: addiu       $t8, $v0, -0x1
        ctx->r24 = ADD32(ctx->r2, -0X1);
            goto L_800C34F0;
    }
    // 0x800C34E8: addiu       $t8, $v0, -0x1
    ctx->r24 = ADD32(ctx->r2, -0X1);
    // 0x800C34EC: sb          $t8, 0x2($v1)
    MEM_B(0X2, ctx->r3) = ctx->r24;
L_800C34F0:
    // 0x800C34F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C34F4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C34F8: jr          $ra
    // 0x800C34FC: nop

    return;
    // 0x800C34FC: nop

;}
RECOMP_FUNC void func_800C3500(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3500: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3504: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3508: addiu       $a1, $zero, 0x7D
    ctx->r5 = ADD32(0, 0X7D);
    // 0x800C350C: jal         0x800C32A0
    // 0x800C3510: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    func_800C32A0(rdram, ctx);
        goto after_0;
    // 0x800C3510: addiu       $a2, $zero, 0xA
    ctx->r6 = ADD32(0, 0XA);
    after_0:
    // 0x800C3514: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3518: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C351C: jr          $ra
    // 0x800C3520: nop

    return;
    // 0x800C3520: nop

;}
RECOMP_FUNC void func_800C3524(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3524: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3528: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C352C: addiu       $a2, $zero, 0x7D
    ctx->r6 = ADD32(0, 0X7D);
    // 0x800C3530: jal         0x800C338C
    // 0x800C3534: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    func_800C338C(rdram, ctx);
        goto after_0;
    // 0x800C3534: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    after_0:
    // 0x800C3538: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C353C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3540: jr          $ra
    // 0x800C3544: nop

    return;
    // 0x800C3544: nop

;}
RECOMP_FUNC void func_800C3548(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3548: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C354C: lw          $t6, 0x7DD0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DD0);
    // 0x800C3550: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3554: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3558: bne         $t6, $zero, L_800C35A4
    if (ctx->r14 != 0) {
        // 0x800C355C: lui         $v0, 0x8004
        ctx->r2 = S32(0X8004 << 16);
            goto L_800C35A4;
    }
    // 0x800C355C: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C3560: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C3564: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    // 0x800C3568: addiu       $a2, $zero, 0x1E
    ctx->r6 = ADD32(0, 0X1E);
    // 0x800C356C: andi        $t7, $v0, 0x3
    ctx->r15 = ctx->r2 & 0X3;
    // 0x800C3570: jal         0x800C3408
    // 0x800C3574: addiu       $a0, $t7, 0x6C
    ctx->r4 = ADD32(ctx->r15, 0X6C);
    func_800C3408(rdram, ctx);
        goto after_0;
    // 0x800C3574: addiu       $a0, $t7, 0x6C
    ctx->r4 = ADD32(ctx->r15, 0X6C);
    after_0:
    // 0x800C3578: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C357C: lw          $t8, 0x562C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X562C);
    // 0x800C3580: andi        $t9, $t8, 0x1
    ctx->r25 = ctx->r24 & 0X1;
    // 0x800C3584: beq         $t9, $zero, L_800C359C
    if (ctx->r25 == 0) {
        // 0x800C3588: nop
    
            goto L_800C359C;
    }
    // 0x800C3588: nop

    // 0x800C358C: jal         0x800C1EB8
    // 0x800C3590: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C1EB8(rdram, ctx);
        goto after_1;
    // 0x800C3590: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_1:
    // 0x800C3594: b           L_800C35A8
    // 0x800C3598: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C35A8;
    // 0x800C3598: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C359C:
    // 0x800C359C: jal         0x800C1EB8
    // 0x800C35A0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C1EB8(rdram, ctx);
        goto after_2;
    // 0x800C35A0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_2:
L_800C35A4:
    // 0x800C35A4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C35A8:
    // 0x800C35A8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C35AC: jr          $ra
    // 0x800C35B0: nop

    return;
    // 0x800C35B0: nop

;}
RECOMP_FUNC void func_800C35B4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C35B4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C35B8: lw          $t6, 0x7DD0($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DD0);
    // 0x800C35BC: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C35C0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C35C4: bne         $t6, $zero, L_800C3618
    if (ctx->r14 != 0) {
        // 0x800C35C8: lui         $v0, 0x8004
        ctx->r2 = S32(0X8004 << 16);
            goto L_800C3618;
    }
    // 0x800C35C8: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C35CC: lw          $v0, 0x562C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X562C);
    // 0x800C35D0: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C35D4: addiu       $a1, $zero, 0x20
    ctx->r5 = ADD32(0, 0X20);
    // 0x800C35D8: divu        $zero, $v0, $at
    lo = S32(U32(ctx->r2) / U32(ctx->r1)); hi = S32(U32(ctx->r2) % U32(ctx->r1));
    // 0x800C35DC: mfhi        $t7
    ctx->r15 = hi;
    // 0x800C35E0: addiu       $a0, $t7, 0x66
    ctx->r4 = ADD32(ctx->r15, 0X66);
    // 0x800C35E4: jal         0x800C3408
    // 0x800C35E8: addiu       $a2, $zero, 0x1E
    ctx->r6 = ADD32(0, 0X1E);
    func_800C3408(rdram, ctx);
        goto after_0;
    // 0x800C35E8: addiu       $a2, $zero, 0x1E
    ctx->r6 = ADD32(0, 0X1E);
    after_0:
    // 0x800C35EC: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C35F0: lw          $t8, 0x562C($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X562C);
    // 0x800C35F4: andi        $t9, $t8, 0x1
    ctx->r25 = ctx->r24 & 0X1;
    // 0x800C35F8: beq         $t9, $zero, L_800C3610
    if (ctx->r25 == 0) {
        // 0x800C35FC: nop
    
            goto L_800C3610;
    }
    // 0x800C35FC: nop

    // 0x800C3600: jal         0x800C1EB8
    // 0x800C3604: addiu       $a0, $zero, 0x13
    ctx->r4 = ADD32(0, 0X13);
    func_800C1EB8(rdram, ctx);
        goto after_1;
    // 0x800C3604: addiu       $a0, $zero, 0x13
    ctx->r4 = ADD32(0, 0X13);
    after_1:
    // 0x800C3608: b           L_800C361C
    // 0x800C360C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C361C;
    // 0x800C360C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3610:
    // 0x800C3610: jal         0x800C1EB8
    // 0x800C3614: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_2;
    // 0x800C3614: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_2:
L_800C3618:
    // 0x800C3618: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C361C:
    // 0x800C361C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3620: jr          $ra
    // 0x800C3624: nop

    return;
    // 0x800C3624: nop

;}
RECOMP_FUNC void func_800C3628(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3628: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C362C: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x800C3630: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x800C3634: sll         $a1, $s0, 24
    ctx->r5 = S32(ctx->r16 << 24);
    // 0x800C3638: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x800C363C: sra         $t6, $a1, 24
    ctx->r14 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C3640: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3644: ori         $a0, $a0, 0xF01
    ctx->r4 = ctx->r4 | 0XF01;
    // 0x800C3648: jal         0x800C53D4
    // 0x800C364C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C364C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    after_0:
    // 0x800C3650: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3654: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C3658: jal         0x800C53D4
    // 0x800C365C: addiu       $a1, $zero, 0x25
    ctx->r5 = ADD32(0, 0X25);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C365C: addiu       $a1, $zero, 0x25
    ctx->r5 = ADD32(0, 0X25);
    after_1:
    // 0x800C3660: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C3664: bne         $s0, $at, L_800C367C
    if (ctx->r16 != ctx->r1) {
        // 0x800C3668: addiu       $a0, $zero, 0x64
        ctx->r4 = ADD32(0, 0X64);
            goto L_800C367C;
    }
    // 0x800C3668: addiu       $a0, $zero, 0x64
    ctx->r4 = ADD32(0, 0X64);
    // 0x800C366C: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C3670: addiu       $a2, $zero, 0x10
    ctx->r6 = ADD32(0, 0X10);
    // 0x800C3674: jal         0x800C3464
    // 0x800C3678: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    func_800C3464(rdram, ctx);
        goto after_2;
    // 0x800C3678: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    after_2:
L_800C367C:
    // 0x800C367C: addiu       $at, $zero, 0x8
    ctx->r1 = ADD32(0, 0X8);
    // 0x800C3680: bne         $s0, $at, L_800C3698
    if (ctx->r16 != ctx->r1) {
        // 0x800C3684: addiu       $a0, $zero, 0x69
        ctx->r4 = ADD32(0, 0X69);
            goto L_800C3698;
    }
    // 0x800C3684: addiu       $a0, $zero, 0x69
    ctx->r4 = ADD32(0, 0X69);
    // 0x800C3688: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C368C: addiu       $a2, $zero, 0x12
    ctx->r6 = ADD32(0, 0X12);
    // 0x800C3690: jal         0x800C3464
    // 0x800C3694: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    func_800C3464(rdram, ctx);
        goto after_3;
    // 0x800C3694: addiu       $a3, $zero, 0xA
    ctx->r7 = ADD32(0, 0XA);
    after_3:
L_800C3698:
    // 0x800C3698: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x800C369C: bne         $s0, $at, L_800C36B4
    if (ctx->r16 != ctx->r1) {
        // 0x800C36A0: addiu       $a0, $zero, 0x6A
        ctx->r4 = ADD32(0, 0X6A);
            goto L_800C36B4;
    }
    // 0x800C36A0: addiu       $a0, $zero, 0x6A
    ctx->r4 = ADD32(0, 0X6A);
    // 0x800C36A4: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C36A8: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x800C36AC: jal         0x800C3464
    // 0x800C36B0: addiu       $a3, $zero, 0x14
    ctx->r7 = ADD32(0, 0X14);
    func_800C3464(rdram, ctx);
        goto after_4;
    // 0x800C36B0: addiu       $a3, $zero, 0x14
    ctx->r7 = ADD32(0, 0X14);
    after_4:
L_800C36B4:
    // 0x800C36B4: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C36B8: lw          $t7, 0x7DC4($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC4);
    // 0x800C36BC: lui         $t8, 0x800F
    ctx->r24 = S32(0X800F << 16);
    // 0x800C36C0: addiu       $a0, $zero, 0x6B
    ctx->r4 = ADD32(0, 0X6B);
    // 0x800C36C4: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x800C36C8: lb          $t8, -0x7BD0($t8)
    ctx->r24 = MEM_B(ctx->r24, -0X7BD0);
    // 0x800C36CC: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C36D0: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x800C36D4: bnel        $s0, $t8, L_800C36E8
    if (ctx->r16 != ctx->r24) {
        // 0x800C36D8: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_800C36E8;
    }
    goto skip_0;
    // 0x800C36D8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_0:
    // 0x800C36DC: jal         0x800C3464
    // 0x800C36E0: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    func_800C3464(rdram, ctx);
        goto after_5;
    // 0x800C36E0: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    after_5:
    // 0x800C36E4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_800C36E8:
    // 0x800C36E8: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x800C36EC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C36F0: jr          $ra
    // 0x800C36F4: nop

    return;
    // 0x800C36F4: nop

;}
RECOMP_FUNC void func_800C36F8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C36F8: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C36FC: lw          $t6, 0x7DC4($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7DC4);
    // 0x800C3700: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3704: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3708: beq         $t6, $zero, L_800C376C
    if (ctx->r14 == 0) {
        // 0x800C370C: or          $a2, $a0, $zero
        ctx->r6 = ctx->r4 | 0;
            goto L_800C376C;
    }
    // 0x800C370C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800C3710: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C3714: lw          $t7, 0x7DC0($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7DC0);
    // 0x800C3718: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C371C: beq         $t7, $at, L_800C376C
    if (ctx->r15 == ctx->r1) {
        // 0x800C3720: addiu       $at, $zero, 0x5
        ctx->r1 = ADD32(0, 0X5);
            goto L_800C376C;
    }
    // 0x800C3720: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C3724: bne         $a0, $at, L_800C3740
    if (ctx->r4 != ctx->r1) {
        // 0x800C3728: addiu       $a1, $zero, 0x36
        ctx->r5 = ADD32(0, 0X36);
            goto L_800C3740;
    }
    // 0x800C3728: addiu       $a1, $zero, 0x36
    ctx->r5 = ADD32(0, 0X36);
    // 0x800C372C: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3730: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C3734: jal         0x800C53D4
    // 0x800C3738: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C3738: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    after_0:
    // 0x800C373C: lw          $a2, 0x18($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X18);
L_800C3740:
    // 0x800C3740: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C3744: lw          $t8, 0x7CD8($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7CD8);
    // 0x800C3748: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x800C374C: bnel        $t8, $zero, L_800C3770
    if (ctx->r24 != 0) {
        // 0x800C3750: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C3770;
    }
    goto skip_0;
    // 0x800C3750: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C3754: bne         $a2, $at, L_800C376C
    if (ctx->r6 != ctx->r1) {
        // 0x800C3758: addiu       $a0, $zero, 0x5E
        ctx->r4 = ADD32(0, 0X5E);
            goto L_800C376C;
    }
    // 0x800C3758: addiu       $a0, $zero, 0x5E
    ctx->r4 = ADD32(0, 0X5E);
    // 0x800C375C: addiu       $a1, $zero, 0x1E
    ctx->r5 = ADD32(0, 0X1E);
    // 0x800C3760: addiu       $a2, $zero, 0x20
    ctx->r6 = ADD32(0, 0X20);
    // 0x800C3764: jal         0x800C33C8
    // 0x800C3768: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    func_800C33C8(rdram, ctx);
        goto after_1;
    // 0x800C3768: addiu       $a3, $zero, 0x1E
    ctx->r7 = ADD32(0, 0X1E);
    after_1:
L_800C376C:
    // 0x800C376C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3770:
    // 0x800C3770: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3774: jr          $ra
    // 0x800C3778: nop

    return;
    // 0x800C3778: nop

;}
RECOMP_FUNC void func_800C377C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C377C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800C3780: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3784: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    // 0x800C3788: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C378C: sra         $t6, $a1, 24
    ctx->r14 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C3790: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3794: ori         $a0, $a0, 0xC01
    ctx->r4 = ctx->r4 | 0XC01;
    // 0x800C3798: jal         0x800C53D4
    // 0x800C379C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C379C: or          $a1, $t6, $zero
    ctx->r5 = ctx->r14 | 0;
    after_0:
    // 0x800C37A0: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C37A4: ori         $a0, $a0, 0xC00
    ctx->r4 = ctx->r4 | 0XC00;
    // 0x800C37A8: jal         0x800C53D4
    // 0x800C37AC: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C37AC: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_1:
    // 0x800C37B0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C37B4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C37B8: jr          $ra
    // 0x800C37BC: nop

    return;
    // 0x800C37BC: nop

;}
RECOMP_FUNC void func_800C37C0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C37C0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C37C4: sw          $a1, 0x7CE4($at)
    MEM_W(0X7CE4, ctx->r1) = ctx->r5;
    // 0x800C37C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C37CC: jr          $ra
    // 0x800C37D0: sw          $a0, 0x7E1C($at)
    MEM_W(0X7E1C, ctx->r1) = ctx->r4;
    return;
    // 0x800C37D0: sw          $a0, 0x7E1C($at)
    MEM_W(0X7E1C, ctx->r1) = ctx->r4;
;}
RECOMP_FUNC void func_800C37D4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C37D4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C37D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C37DC: jal         0x800C377C
    // 0x800C37E0: nop

    func_800C377C(rdram, ctx);
        goto after_0;
    // 0x800C37E0: nop

    after_0:
    // 0x800C37E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C37E8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C37EC: jr          $ra
    // 0x800C37F0: nop

    return;
    // 0x800C37F0: nop

;}
RECOMP_FUNC void func_800C37F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C37F4: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C37F8: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C37FC: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x800C3800: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C3804: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3808: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x800C380C: beq         $t6, $at, L_800C3838
    if (ctx->r14 == ctx->r1) {
        // 0x800C3810: or          $a3, $a1, $zero
        ctx->r7 = ctx->r5 | 0;
            goto L_800C3838;
    }
    // 0x800C3810: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x800C3814: addiu       $t7, $a0, -0xA
    ctx->r15 = ADD32(ctx->r4, -0XA);
    // 0x800C3818: sltiu       $at, $t7, 0x2C
    ctx->r1 = ctx->r15 < 0X2C ? 1 : 0;
    // 0x800C381C: beq         $at, $zero, L_800C3838
    if (ctx->r1 == 0) {
        // 0x800C3820: sll         $t7, $t7, 2
        ctx->r15 = S32(ctx->r15 << 2);
            goto L_800C3838;
    }
    // 0x800C3820: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x800C3824: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C3828: addu        $at, $at, $t7
    gpr jr_addend_800C3830 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x800C382C: lw          $t7, -0x3BEC($at)
    ctx->r15 = ADD32(ctx->r1, -0X3BEC);
    // 0x800C3830: jr          $t7
    // 0x800C3834: nop

    switch (jr_addend_800C3830 >> 2) {
        case 0: goto L_800C3DD0; break;
        case 1: goto L_800C3838; break;
        case 2: goto L_800C3838; break;
        case 3: goto L_800C3838; break;
        case 4: goto L_800C3838; break;
        case 5: goto L_800C3838; break;
        case 6: goto L_800C3838; break;
        case 7: goto L_800C3838; break;
        case 8: goto L_800C3838; break;
        case 9: goto L_800C3838; break;
        case 10: goto L_800C3838; break;
        case 11: goto L_800C3838; break;
        case 12: goto L_800C3838; break;
        case 13: goto L_800C3838; break;
        case 14: goto L_800C3838; break;
        case 15: goto L_800C3838; break;
        case 16: goto L_800C3838; break;
        case 17: goto L_800C3838; break;
        case 18: goto L_800C3838; break;
        case 19: goto L_800C3838; break;
        case 20: goto L_800C3838; break;
        case 21: goto L_800C3838; break;
        case 22: goto L_800C3838; break;
        case 23: goto L_800C3DD0; break;
        case 24: goto L_800C3838; break;
        case 25: goto L_800C3838; break;
        case 26: goto L_800C3838; break;
        case 27: goto L_800C3838; break;
        case 28: goto L_800C3DD0; break;
        case 29: goto L_800C3DD0; break;
        case 30: goto L_800C3DD0; break;
        case 31: goto L_800C3DD0; break;
        case 32: goto L_800C3838; break;
        case 33: goto L_800C3838; break;
        case 34: goto L_800C3838; break;
        case 35: goto L_800C3838; break;
        case 36: goto L_800C3838; break;
        case 37: goto L_800C3838; break;
        case 38: goto L_800C3838; break;
        case 39: goto L_800C3838; break;
        case 40: goto L_800C3838; break;
        case 41: goto L_800C3838; break;
        case 42: goto L_800C3838; break;
        case 43: goto L_800C3DD0; break;
        default: switch_error(__func__, 0x800C3830, 0x800EC414);
    }
    // 0x800C3834: nop

L_800C3838:
    // 0x800C3838: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C383C: lw          $t8, 0x7DC0($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7DC0);
    // 0x800C3840: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3844: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3848: beq         $t8, $at, L_800C38B4
    if (ctx->r24 == ctx->r1) {
        // 0x800C384C: ori         $a0, $a0, 0xF00
        ctx->r4 = ctx->r4 | 0XF00;
            goto L_800C38B4;
    }
    // 0x800C384C: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C3850: addiu       $at, $zero, 0x28
    ctx->r1 = ADD32(0, 0X28);
    // 0x800C3854: beq         $a2, $at, L_800C3868
    if (ctx->r6 == ctx->r1) {
        // 0x800C3858: lui         $t9, 0x801D
        ctx->r25 = S32(0X801D << 16);
            goto L_800C3868;
    }
    // 0x800C3858: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x800C385C: addiu       $at, $zero, 0x29
    ctx->r1 = ADD32(0, 0X29);
    // 0x800C3860: bnel        $a2, $at, L_800C38B8
    if (ctx->r6 != ctx->r1) {
        // 0x800C3864: sll         $a1, $a2, 24
        ctx->r5 = S32(ctx->r6 << 24);
            goto L_800C38B8;
    }
    goto skip_0;
    // 0x800C3864: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    skip_0:
L_800C3868:
    // 0x800C3868: lb          $t9, 0x7DFC($t9)
    ctx->r25 = MEM_B(ctx->r25, 0X7DFC);
    // 0x800C386C: andi        $t2, $a3, 0x80
    ctx->r10 = ctx->r7 & 0X80;
    // 0x800C3870: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x800C3874: beq         $t9, $zero, L_800C3890
    if (ctx->r25 == 0) {
        // 0x800C3878: andi        $t5, $a3, 0x80
        ctx->r13 = ctx->r7 & 0X80;
            goto L_800C3890;
    }
    // 0x800C3878: andi        $t5, $a3, 0x80
    ctx->r13 = ctx->r7 & 0X80;
    // 0x800C387C: bne         $t2, $zero, L_800C3890
    if (ctx->r10 != 0) {
        // 0x800C3880: andi        $t3, $a3, 0xF
        ctx->r11 = ctx->r7 & 0XF;
            goto L_800C3890;
    }
    // 0x800C3880: andi        $t3, $a3, 0xF
    ctx->r11 = ctx->r7 & 0XF;
    // 0x800C3884: beq         $t3, $zero, L_800C3890
    if (ctx->r11 == 0) {
        // 0x800C3888: nop
    
            goto L_800C3890;
    }
    // 0x800C3888: nop

    // 0x800C388C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_800C3890:
    // 0x800C3890: lb          $t4, 0x7E04($t4)
    ctx->r12 = MEM_B(ctx->r12, 0X7E04);
    // 0x800C3894: addiu       $at, $zero, 0x80
    ctx->r1 = ADD32(0, 0X80);
    // 0x800C3898: beql        $t4, $zero, L_800C38B8
    if (ctx->r12 == 0) {
        // 0x800C389C: sll         $a1, $a2, 24
        ctx->r5 = S32(ctx->r6 << 24);
            goto L_800C38B8;
    }
    goto skip_1;
    // 0x800C389C: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    skip_1:
    // 0x800C38A0: bne         $t5, $at, L_800C38B4
    if (ctx->r13 != ctx->r1) {
        // 0x800C38A4: andi        $t6, $a3, 0xF
        ctx->r14 = ctx->r7 & 0XF;
            goto L_800C38B4;
    }
    // 0x800C38A4: andi        $t6, $a3, 0xF
    ctx->r14 = ctx->r7 & 0XF;
    // 0x800C38A8: beql        $t6, $zero, L_800C38B8
    if (ctx->r14 == 0) {
        // 0x800C38AC: sll         $a1, $a2, 24
        ctx->r5 = S32(ctx->r6 << 24);
            goto L_800C38B8;
    }
    goto skip_2;
    // 0x800C38AC: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
    skip_2:
    // 0x800C38B0: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
L_800C38B4:
    // 0x800C38B4: sll         $a1, $a2, 24
    ctx->r5 = S32(ctx->r6 << 24);
L_800C38B8:
    // 0x800C38B8: sra         $t7, $a1, 24
    ctx->r15 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C38BC: or          $a1, $t7, $zero
    ctx->r5 = ctx->r15 | 0;
    // 0x800C38C0: or          $v0, $a2, $zero
    ctx->r2 = ctx->r6 | 0;
    // 0x800C38C4: sw          $a2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r6;
    // 0x800C38C8: jal         0x800C53D4
    // 0x800C38CC: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C38CC: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    after_0:
    // 0x800C38D0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C38D4: lb          $t8, 0x7C94($t8)
    ctx->r24 = MEM_B(ctx->r24, 0X7C94);
    // 0x800C38D8: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x800C38DC: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C38E0: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C38E4: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C38E8: addiu       $a0, $a0, 0x7E00
    ctx->r4 = ADD32(ctx->r4, 0X7E00);
    // 0x800C38EC: lw          $v0, 0x18($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X18);
    // 0x800C38F0: addiu       $a1, $zero, 0x80
    ctx->r5 = ADD32(0, 0X80);
    // 0x800C38F4: bne         $t8, $at, L_800C3958
    if (ctx->r24 != ctx->r1) {
        // 0x800C38F8: lw          $a3, 0x3C($sp)
        ctx->r7 = MEM_W(ctx->r29, 0X3C);
            goto L_800C3958;
    }
    // 0x800C38F8: lw          $a3, 0x3C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X3C);
    // 0x800C38FC: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800C3900: lw          $t9, 0x7CB8($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7CB8);
    // 0x800C3904: addiu       $at, $zero, 0x23
    ctx->r1 = ADD32(0, 0X23);
    // 0x800C3908: bnel        $t9, $zero, L_800C395C
    if (ctx->r25 != 0) {
        // 0x800C390C: addiu       $t6, $v0, -0x1
        ctx->r14 = ADD32(ctx->r2, -0X1);
            goto L_800C395C;
    }
    goto skip_3;
    // 0x800C390C: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
    skip_3:
    // 0x800C3910: bne         $v0, $at, L_800C3944
    if (ctx->r2 != ctx->r1) {
        // 0x800C3914: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_800C3944;
    }
    // 0x800C3914: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800C3918: addiu       $t2, $zero, 0xA
    ctx->r10 = ADD32(0, 0XA);
    // 0x800C391C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3920: sw          $t2, 0x7CD8($at)
    MEM_W(0X7CD8, ctx->r1) = ctx->r10;
    // 0x800C3924: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3928: addiu       $t3, $zero, 0xB4
    ctx->r11 = ADD32(0, 0XB4);
    // 0x800C392C: sw          $t3, 0x7CD4($at)
    MEM_W(0X7CD4, ctx->r1) = ctx->r11;
    // 0x800C3930: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3934: sw          $t0, 0x7CA0($at)
    MEM_W(0X7CA0, ctx->r1) = ctx->r8;
    // 0x800C3938: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C393C: addiu       $t4, $zero, 0x140
    ctx->r12 = ADD32(0, 0X140);
    // 0x800C3940: sw          $t4, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r12;
L_800C3944:
    // 0x800C3944: addiu       $at, $zero, 0x21
    ctx->r1 = ADD32(0, 0X21);
    // 0x800C3948: bne         $v0, $at, L_800C3958
    if (ctx->r2 != ctx->r1) {
        // 0x800C394C: addiu       $t5, $zero, 0xA0
        ctx->r13 = ADD32(0, 0XA0);
            goto L_800C3958;
    }
    // 0x800C394C: addiu       $t5, $zero, 0xA0
    ctx->r13 = ADD32(0, 0XA0);
    // 0x800C3950: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3954: sw          $t5, 0x7CE8($at)
    MEM_W(0X7CE8, ctx->r1) = ctx->r13;
L_800C3958:
    // 0x800C3958: addiu       $t6, $v0, -0x1
    ctx->r14 = ADD32(ctx->r2, -0X1);
L_800C395C:
    // 0x800C395C: sltiu       $at, $t6, 0x35
    ctx->r1 = ctx->r14 < 0X35 ? 1 : 0;
    // 0x800C3960: beq         $at, $zero, L_800C3DD0
    if (ctx->r1 == 0) {
        // 0x800C3964: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_800C3DD0;
    }
    // 0x800C3964: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800C3968: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800C396C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C3970: addu        $at, $at, $t6
    gpr jr_addend_800C3978 = ctx->r14;
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800C3974: lw          $t6, -0x3B3C($at)
    ctx->r14 = ADD32(ctx->r1, -0X3B3C);
    // 0x800C3978: jr          $t6
    // 0x800C397C: nop

    switch (jr_addend_800C3978 >> 2) {
        case 0: goto L_800C3C40; break;
        case 1: goto L_800C3DD0; break;
        case 2: goto L_800C3DD0; break;
        case 3: goto L_800C3DD0; break;
        case 4: goto L_800C3DD0; break;
        case 5: goto L_800C3DD0; break;
        case 6: goto L_800C3DD0; break;
        case 7: goto L_800C3DD0; break;
        case 8: goto L_800C3DD0; break;
        case 9: goto L_800C3CC0; break;
        case 10: goto L_800C3DD0; break;
        case 11: goto L_800C3DD0; break;
        case 12: goto L_800C3DD0; break;
        case 13: goto L_800C3DD0; break;
        case 14: goto L_800C3DD0; break;
        case 15: goto L_800C3DD0; break;
        case 16: goto L_800C3DD0; break;
        case 17: goto L_800C3DD0; break;
        case 18: goto L_800C3DD0; break;
        case 19: goto L_800C3DD0; break;
        case 20: goto L_800C3DD0; break;
        case 21: goto L_800C3DD0; break;
        case 22: goto L_800C3DD0; break;
        case 23: goto L_800C3DD0; break;
        case 24: goto L_800C3DD0; break;
        case 25: goto L_800C3DD0; break;
        case 26: goto L_800C3DD0; break;
        case 27: goto L_800C3DD0; break;
        case 28: goto L_800C3DD0; break;
        case 29: goto L_800C3DD0; break;
        case 30: goto L_800C3DD0; break;
        case 31: goto L_800C3DD0; break;
        case 32: goto L_800C3980; break;
        case 33: goto L_800C3D14; break;
        case 34: goto L_800C3D2C; break;
        case 35: goto L_800C3DD0; break;
        case 36: goto L_800C3DD0; break;
        case 37: goto L_800C3BEC; break;
        case 38: goto L_800C3BEC; break;
        case 39: goto L_800C3C40; break;
        case 40: goto L_800C3C40; break;
        case 41: goto L_800C3DD0; break;
        case 42: goto L_800C3DD0; break;
        case 43: goto L_800C3DD0; break;
        case 44: goto L_800C3D44; break;
        case 45: goto L_800C3DD0; break;
        case 46: goto L_800C3DD0; break;
        case 47: goto L_800C3DD0; break;
        case 48: goto L_800C3DD0; break;
        case 49: goto L_800C3DD0; break;
        case 50: goto L_800C3D5C; break;
        case 51: goto L_800C3DD0; break;
        case 52: goto L_800C3D80; break;
        default: switch_error(__func__, 0x800C3978, 0x800EC4C4);
    }
    // 0x800C397C: nop

L_800C3980:
    // 0x800C3980: addiu       $a0, $zero, 0x12
    ctx->r4 = ADD32(0, 0X12);
    // 0x800C3984: jal         0x800C1EB8
    // 0x800C3988: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    func_800C1EB8(rdram, ctx);
        goto after_1;
    // 0x800C3988: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    after_1:
    // 0x800C398C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C3990: lw          $v1, 0x7DC0($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7DC0);
    // 0x800C3994: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
    // 0x800C3998: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C399C: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C39A0: lw          $a3, 0x3C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X3C);
    // 0x800C39A4: bne         $v0, $v1, L_800C3A18
    if (ctx->r2 != ctx->r3) {
        // 0x800C39A8: addiu       $t0, $zero, 0x1
        ctx->r8 = ADD32(0, 0X1);
            goto L_800C3A18;
    }
    // 0x800C39A8: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800C39AC: andi        $t7, $a3, 0x1
    ctx->r15 = ctx->r7 & 0X1;
    // 0x800C39B0: bne         $t0, $t7, L_800C39D8
    if (ctx->r8 != ctx->r15) {
        // 0x800C39B4: andi        $t9, $a3, 0x2
        ctx->r25 = ctx->r7 & 0X2;
            goto L_800C39D8;
    }
    // 0x800C39B4: andi        $t9, $a3, 0x2
    ctx->r25 = ctx->r7 & 0X2;
    // 0x800C39B8: addiu       $t8, $zero, 0x3D
    ctx->r24 = ADD32(0, 0X3D);
    // 0x800C39BC: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C39C0: sw          $t8, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r24;
    // 0x800C39C4: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C39C8: jal         0x800C53D4
    // 0x800C39CC: addiu       $a1, $zero, 0x39
    ctx->r5 = ADD32(0, 0X39);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C39CC: addiu       $a1, $zero, 0x39
    ctx->r5 = ADD32(0, 0X39);
    after_2:
    // 0x800C39D0: b           L_800C3A00
    // 0x800C39D4: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
        goto L_800C3A00;
    // 0x800C39D4: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
L_800C39D8:
    // 0x800C39D8: bne         $v0, $t9, L_800C39EC
    if (ctx->r2 != ctx->r25) {
        // 0x800C39DC: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C39EC;
    }
    // 0x800C39DC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C39E0: addiu       $t2, $zero, 0x2E
    ctx->r10 = ADD32(0, 0X2E);
    // 0x800C39E4: b           L_800C39FC
    // 0x800C39E8: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
        goto L_800C39FC;
    // 0x800C39E8: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
L_800C39EC:
    // 0x800C39EC: lw          $v1, 0x562C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X562C);
    // 0x800C39F0: andi        $t3, $v1, 0x1
    ctx->r11 = ctx->r3 & 0X1;
    // 0x800C39F4: addiu       $t4, $t3, 0x3E
    ctx->r12 = ADD32(ctx->r11, 0X3E);
    // 0x800C39F8: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
L_800C39FC:
    // 0x800C39FC: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
L_800C3A00:
    // 0x800C3A00: addiu       $a1, $zero, 0x1E
    ctx->r5 = ADD32(0, 0X1E);
    // 0x800C3A04: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    // 0x800C3A08: jal         0x800C33C8
    // 0x800C3A0C: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    func_800C33C8(rdram, ctx);
        goto after_3;
    // 0x800C3A0C: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    after_3:
    // 0x800C3A10: b           L_800C3DD4
    // 0x800C3A14: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3A14: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3A18:
    // 0x800C3A18: bne         $t0, $v1, L_800C3A8C
    if (ctx->r8 != ctx->r3) {
        // 0x800C3A1C: andi        $v0, $a3, 0x80
        ctx->r2 = ctx->r7 & 0X80;
            goto L_800C3A8C;
    }
    // 0x800C3A1C: andi        $v0, $a3, 0x80
    ctx->r2 = ctx->r7 & 0X80;
    // 0x800C3A20: beq         $v0, $zero, L_800C3DD0
    if (ctx->r2 == 0) {
        // 0x800C3A24: lui         $t5, 0x800E
        ctx->r13 = S32(0X800E << 16);
            goto L_800C3DD0;
    }
    // 0x800C3A24: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800C3A28: lw          $t5, 0x7CA8($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X7CA8);
    // 0x800C3A2C: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C3A30: bnel        $t5, $zero, L_800C3DD4
    if (ctx->r13 != 0) {
        // 0x800C3A34: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C3DD4;
    }
    goto skip_4;
    // 0x800C3A34: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_4:
    // 0x800C3A38: lw          $t6, 0x7C98($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7C98);
    // 0x800C3A3C: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    // 0x800C3A40: beq         $t6, $zero, L_800C3A68
    if (ctx->r14 == 0) {
        // 0x800C3A44: nop
    
            goto L_800C3A68;
    }
    // 0x800C3A44: nop

    // 0x800C3A48: jal         0x800C15C8
    // 0x800C3A4C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_4;
    // 0x800C3A4C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_4:
    // 0x800C3A50: jal         0x800C1674
    // 0x800C3A54: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_5;
    // 0x800C3A54: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_5:
    // 0x800C3A58: addiu       $t7, $zero, 0x12
    ctx->r15 = ADD32(0, 0X12);
    // 0x800C3A5C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3A60: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800C3A64: sw          $t7, 0x7CEC($at)
    MEM_W(0X7CEC, ctx->r1) = ctx->r15;
L_800C3A68:
    // 0x800C3A68: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3A6C: sw          $t0, 0x7CA8($at)
    MEM_W(0X7CA8, ctx->r1) = ctx->r8;
    // 0x800C3A70: addiu       $a0, $zero, 0x3B
    ctx->r4 = ADD32(0, 0X3B);
    // 0x800C3A74: addiu       $a1, $zero, 0x10
    ctx->r5 = ADD32(0, 0X10);
    // 0x800C3A78: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    // 0x800C3A7C: jal         0x800C33C8
    // 0x800C3A80: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    func_800C33C8(rdram, ctx);
        goto after_6;
    // 0x800C3A80: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    after_6:
    // 0x800C3A84: b           L_800C3DD4
    // 0x800C3A88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3A88: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3A8C:
    // 0x800C3A8C: beq         $v0, $zero, L_800C3B34
    if (ctx->r2 == 0) {
        // 0x800C3A90: lui         $t8, 0x800E
        ctx->r24 = S32(0X800E << 16);
            goto L_800C3B34;
    }
    // 0x800C3A90: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C3A94: lw          $t8, 0x7C98($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7C98);
    // 0x800C3A98: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    // 0x800C3A9C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x800C3AA0: beql        $t8, $zero, L_800C3AD8
    if (ctx->r24 == 0) {
        // 0x800C3AA4: lb          $v0, 0x2($t1)
        ctx->r2 = MEM_B(ctx->r9, 0X2);
            goto L_800C3AD8;
    }
    goto skip_5;
    // 0x800C3AA4: lb          $v0, 0x2($t1)
    ctx->r2 = MEM_B(ctx->r9, 0X2);
    skip_5:
    // 0x800C3AA8: jal         0x800C15C8
    // 0x800C3AAC: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    func_800C15C8(rdram, ctx);
        goto after_7;
    // 0x800C3AAC: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    after_7:
    // 0x800C3AB0: jal         0x800C1674
    // 0x800C3AB4: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    AudioGeneral_DisableSeqPlayer2(rdram, ctx);
        goto after_8;
    // 0x800C3AB4: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    after_8:
    // 0x800C3AB8: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C3ABC: addiu       $t9, $zero, 0x12
    ctx->r25 = ADD32(0, 0X12);
    // 0x800C3AC0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3AC4: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C3AC8: lw          $a3, 0x3C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X3C);
    // 0x800C3ACC: addiu       $t0, $zero, 0x1
    ctx->r8 = ADD32(0, 0X1);
    // 0x800C3AD0: sw          $t9, 0x7CEC($at)
    MEM_W(0X7CEC, ctx->r1) = ctx->r25;
    // 0x800C3AD4: lb          $v0, 0x2($t1)
    ctx->r2 = MEM_B(ctx->r9, 0X2);
L_800C3AD8:
    // 0x800C3AD8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x800C3ADC: addiu       $t5, $zero, 0x10
    ctx->r13 = ADD32(0, 0X10);
    // 0x800C3AE0: bne         $v0, $zero, L_800C3AF4
    if (ctx->r2 != 0) {
        // 0x800C3AE4: andi        $t6, $a3, 0x1
        ctx->r14 = ctx->r7 & 0X1;
            goto L_800C3AF4;
    }
    // 0x800C3AE4: andi        $t6, $a3, 0x1
    ctx->r14 = ctx->r7 & 0X1;
    // 0x800C3AE8: addiu       $t2, $zero, 0x39
    ctx->r10 = ADD32(0, 0X39);
    // 0x800C3AEC: b           L_800C3B10
    // 0x800C3AF0: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
        goto L_800C3B10;
    // 0x800C3AF0: sw          $t2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r10;
L_800C3AF4:
    // 0x800C3AF4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C3AF8: bne         $v0, $at, L_800C3B0C
    if (ctx->r2 != ctx->r1) {
        // 0x800C3AFC: addiu       $t4, $zero, 0x3B
        ctx->r12 = ADD32(0, 0X3B);
            goto L_800C3B0C;
    }
    // 0x800C3AFC: addiu       $t4, $zero, 0x3B
    ctx->r12 = ADD32(0, 0X3B);
    // 0x800C3B00: addiu       $t3, $zero, 0x3A
    ctx->r11 = ADD32(0, 0X3A);
    // 0x800C3B04: b           L_800C3B10
    // 0x800C3B08: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
        goto L_800C3B10;
    // 0x800C3B08: sw          $t3, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r11;
L_800C3B0C:
    // 0x800C3B0C: sw          $t4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r12;
L_800C3B10:
    // 0x800C3B10: bne         $t0, $t6, L_800C3BBC
    if (ctx->r8 != ctx->r14) {
        // 0x800C3B14: sw          $t5, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r13;
            goto L_800C3BBC;
    }
    // 0x800C3B14: sw          $t5, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r13;
    // 0x800C3B18: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3B1C: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C3B20: addiu       $a1, $zero, 0x39
    ctx->r5 = ADD32(0, 0X39);
    // 0x800C3B24: jal         0x800C53D4
    // 0x800C3B28: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_9;
    // 0x800C3B28: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    after_9:
    // 0x800C3B2C: b           L_800C3BBC
    // 0x800C3B30: lw          $v1, 0x34($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X34);
        goto L_800C3BBC;
    // 0x800C3B30: lw          $v1, 0x34($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X34);
L_800C3B34:
    // 0x800C3B34: bne         $a3, $t0, L_800C3B68
    if (ctx->r7 != ctx->r8) {
        // 0x800C3B38: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C3B68;
    }
    // 0x800C3B38: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C3B3C: addiu       $t7, $zero, 0x3D
    ctx->r15 = ADD32(0, 0X3D);
    // 0x800C3B40: addiu       $t8, $zero, 0x1E
    ctx->r24 = ADD32(0, 0X1E);
    // 0x800C3B44: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C3B48: sw          $t7, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r15;
    // 0x800C3B4C: sw          $t8, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r24;
    // 0x800C3B50: ori         $a0, $a0, 0xF00
    ctx->r4 = ctx->r4 | 0XF00;
    // 0x800C3B54: addiu       $a1, $zero, 0x39
    ctx->r5 = ADD32(0, 0X39);
    // 0x800C3B58: jal         0x800C53D4
    // 0x800C3B5C: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_10;
    // 0x800C3B5C: sw          $zero, 0x34($sp)
    MEM_W(0X34, ctx->r29) = 0;
    after_10:
    // 0x800C3B60: b           L_800C3BBC
    // 0x800C3B64: lw          $v1, 0x34($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X34);
        goto L_800C3BBC;
    // 0x800C3B64: lw          $v1, 0x34($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X34);
L_800C3B68:
    // 0x800C3B68: lw          $v1, 0x562C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X562C);
    // 0x800C3B6C: lb          $v0, 0x2($t1)
    ctx->r2 = MEM_B(ctx->r9, 0X2);
    // 0x800C3B70: addiu       $t3, $zero, 0x1E
    ctx->r11 = ADD32(0, 0X1E);
    // 0x800C3B74: andi        $t9, $v1, 0x1
    ctx->r25 = ctx->r3 & 0X1;
    // 0x800C3B78: bne         $v0, $zero, L_800C3B88
    if (ctx->r2 != 0) {
        // 0x800C3B7C: or          $v1, $t9, $zero
        ctx->r3 = ctx->r25 | 0;
            goto L_800C3B88;
    }
    // 0x800C3B7C: or          $v1, $t9, $zero
    ctx->r3 = ctx->r25 | 0;
    // 0x800C3B80: b           L_800C3BB4
    // 0x800C3B84: addiu       $a0, $zero, 0x2D
    ctx->r4 = ADD32(0, 0X2D);
        goto L_800C3BB4;
    // 0x800C3B84: addiu       $a0, $zero, 0x2D
    ctx->r4 = ADD32(0, 0X2D);
L_800C3B88:
    // 0x800C3B88: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3B8C: bnel        $v0, $at, L_800C3BA0
    if (ctx->r2 != ctx->r1) {
        // 0x800C3B90: lb          $t2, 0x0($t1)
        ctx->r10 = MEM_B(ctx->r9, 0X0);
            goto L_800C3BA0;
    }
    goto skip_6;
    // 0x800C3B90: lb          $t2, 0x0($t1)
    ctx->r10 = MEM_B(ctx->r9, 0X0);
    skip_6:
    // 0x800C3B94: b           L_800C3BB4
    // 0x800C3B98: addiu       $a0, $zero, 0x30
    ctx->r4 = ADD32(0, 0X30);
        goto L_800C3BB4;
    // 0x800C3B98: addiu       $a0, $zero, 0x30
    ctx->r4 = ADD32(0, 0X30);
    // 0x800C3B9C: lb          $t2, 0x0($t1)
    ctx->r10 = MEM_B(ctx->r9, 0X0);
L_800C3BA0:
    // 0x800C3BA0: addiu       $a0, $zero, 0x36
    ctx->r4 = ADD32(0, 0X36);
    // 0x800C3BA4: beq         $t2, $zero, L_800C3BB4
    if (ctx->r10 == 0) {
        // 0x800C3BA8: nop
    
            goto L_800C3BB4;
    }
    // 0x800C3BA8: nop

    // 0x800C3BAC: b           L_800C3BB4
    // 0x800C3BB0: addiu       $a0, $zero, 0x33
    ctx->r4 = ADD32(0, 0X33);
        goto L_800C3BB4;
    // 0x800C3BB0: addiu       $a0, $zero, 0x33
    ctx->r4 = ADD32(0, 0X33);
L_800C3BB4:
    // 0x800C3BB4: sw          $t3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r11;
    // 0x800C3BB8: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
L_800C3BBC:
    // 0x800C3BBC: lw          $t4, 0x30($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X30);
    // 0x800C3BC0: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x800C3BC4: addiu       $a2, $zero, 0x64
    ctx->r6 = ADD32(0, 0X64);
    // 0x800C3BC8: addiu       $a3, $zero, 0x32
    ctx->r7 = ADD32(0, 0X32);
    // 0x800C3BCC: jal         0x800C33C8
    // 0x800C3BD0: addu        $a0, $t4, $v1
    ctx->r4 = ADD32(ctx->r12, ctx->r3);
    func_800C33C8(rdram, ctx);
        goto after_11;
    // 0x800C3BD0: addu        $a0, $t4, $v1
    ctx->r4 = ADD32(ctx->r12, ctx->r3);
    after_11:
    // 0x800C3BD4: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C3BD8: addiu       $t1, $t1, 0x7DF8
    ctx->r9 = ADD32(ctx->r9, 0X7DF8);
    // 0x800C3BDC: lb          $t5, 0x2($t1)
    ctx->r13 = MEM_B(ctx->r9, 0X2);
    // 0x800C3BE0: sb          $zero, 0x0($t1)
    MEM_B(0X0, ctx->r9) = 0;
    // 0x800C3BE4: b           L_800C3DD0
    // 0x800C3BE8: sb          $t5, 0x3($t1)
    MEM_B(0X3, ctx->r9) = ctx->r13;
        goto L_800C3DD0;
    // 0x800C3BE8: sb          $t5, 0x3($t1)
    MEM_B(0X3, ctx->r9) = ctx->r13;
L_800C3BEC:
    // 0x800C3BEC: lb          $t6, 0x4($t1)
    ctx->r14 = MEM_B(ctx->r9, 0X4);
    // 0x800C3BF0: addiu       $v0, $zero, 0x5
    ctx->r2 = ADD32(0, 0X5);
    // 0x800C3BF4: andi        $t7, $a3, 0x80
    ctx->r15 = ctx->r7 & 0X80;
    // 0x800C3BF8: beql        $v0, $t6, L_800C3C0C
    if (ctx->r2 == ctx->r14) {
        // 0x800C3BFC: lb          $t8, 0x4($a0)
        ctx->r24 = MEM_B(ctx->r4, 0X4);
            goto L_800C3C0C;
    }
    goto skip_7;
    // 0x800C3BFC: lb          $t8, 0x4($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X4);
    skip_7:
    // 0x800C3C00: beq         $t7, $zero, L_800C3C1C
    if (ctx->r15 == 0) {
        // 0x800C3C04: nop
    
            goto L_800C3C1C;
    }
    // 0x800C3C04: nop

    // 0x800C3C08: lb          $t8, 0x4($a0)
    ctx->r24 = MEM_B(ctx->r4, 0X4);
L_800C3C0C:
    // 0x800C3C0C: andi        $t9, $a3, 0x80
    ctx->r25 = ctx->r7 & 0X80;
    // 0x800C3C10: beql        $v0, $t8, L_800C3DD4
    if (ctx->r2 == ctx->r24) {
        // 0x800C3C14: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C3DD4;
    }
    goto skip_8;
    // 0x800C3C14: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_8:
    // 0x800C3C18: bne         $a1, $t9, L_800C3DD0
    if (ctx->r5 != ctx->r25) {
        // 0x800C3C1C: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C3DD0;
    }
L_800C3C1C:
    // 0x800C3C1C: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C3C20: lw          $v1, 0x562C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X562C);
    // 0x800C3C24: addiu       $a1, $zero, 0xA
    ctx->r5 = ADD32(0, 0XA);
    // 0x800C3C28: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x800C3C2C: andi        $t2, $v1, 0x3
    ctx->r10 = ctx->r3 & 0X3;
    // 0x800C3C30: jal         0x800C3320
    // 0x800C3C34: addiu       $a0, $t2, 0x61
    ctx->r4 = ADD32(ctx->r10, 0X61);
    func_800C3320(rdram, ctx);
        goto after_12;
    // 0x800C3C34: addiu       $a0, $t2, 0x61
    ctx->r4 = ADD32(ctx->r10, 0X61);
    after_12:
    // 0x800C3C38: b           L_800C3DD4
    // 0x800C3C3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3C3C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3C40:
    // 0x800C3C40: andi        $v0, $a3, 0x80
    ctx->r2 = ctx->r7 & 0X80;
    // 0x800C3C44: beq         $v0, $zero, L_800C3C5C
    if (ctx->r2 == 0) {
        // 0x800C3C48: andi        $v1, $a3, 0xF
        ctx->r3 = ctx->r7 & 0XF;
            goto L_800C3C5C;
    }
    // 0x800C3C48: andi        $v1, $a3, 0xF
    ctx->r3 = ctx->r7 & 0XF;
    // 0x800C3C4C: beql        $v0, $a1, L_800C3C6C
    if (ctx->r2 == ctx->r5) {
        // 0x800C3C50: sb          $t0, 0x0($a0)
        MEM_B(0X0, ctx->r4) = ctx->r8;
            goto L_800C3C6C;
    }
    goto skip_9;
    // 0x800C3C50: sb          $t0, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r8;
    skip_9:
    // 0x800C3C54: b           L_800C3C70
    // 0x800C3C58: nop

        goto L_800C3C70;
    // 0x800C3C58: nop

L_800C3C5C:
    // 0x800C3C5C: sb          $t0, 0x0($t1)
    MEM_B(0X0, ctx->r9) = ctx->r8;
    // 0x800C3C60: b           L_800C3C70
    // 0x800C3C64: sb          $t0, 0x1($t1)
    MEM_B(0X1, ctx->r9) = ctx->r8;
        goto L_800C3C70;
    // 0x800C3C64: sb          $t0, 0x1($t1)
    MEM_B(0X1, ctx->r9) = ctx->r8;
    // 0x800C3C68: sb          $t0, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r8;
L_800C3C6C:
    // 0x800C3C6C: sb          $t0, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r8;
L_800C3C70:
    // 0x800C3C70: beq         $v1, $zero, L_800C3C9C
    if (ctx->r3 == 0) {
        // 0x800C3C74: addiu       $a1, $zero, 0x19
        ctx->r5 = ADD32(0, 0X19);
            goto L_800C3C9C;
    }
    // 0x800C3C74: addiu       $a1, $zero, 0x19
    ctx->r5 = ADD32(0, 0X19);
    // 0x800C3C78: beq         $v1, $t0, L_800C3CA4
    if (ctx->r3 == ctx->r8) {
        // 0x800C3C7C: addiu       $v0, $zero, 0x2
        ctx->r2 = ADD32(0, 0X2);
            goto L_800C3CA4;
    }
    // 0x800C3C7C: addiu       $v0, $zero, 0x2
    ctx->r2 = ADD32(0, 0X2);
    // 0x800C3C80: beq         $v1, $v0, L_800C3CAC
    if (ctx->r3 == ctx->r2) {
        // 0x800C3C84: addiu       $a0, $zero, 0x1A
        ctx->r4 = ADD32(0, 0X1A);
            goto L_800C3CAC;
    }
    // 0x800C3C84: addiu       $a0, $zero, 0x1A
    ctx->r4 = ADD32(0, 0X1A);
    // 0x800C3C88: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C3C8C: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800C3C90: andi        $t3, $a0, 0x1
    ctx->r11 = ctx->r4 & 0X1;
    // 0x800C3C94: b           L_800C3CAC
    // 0x800C3C98: addiu       $a0, $t3, 0x1B
    ctx->r4 = ADD32(ctx->r11, 0X1B);
        goto L_800C3CAC;
    // 0x800C3C98: addiu       $a0, $t3, 0x1B
    ctx->r4 = ADD32(ctx->r11, 0X1B);
L_800C3C9C:
    // 0x800C3C9C: b           L_800C3CAC
    // 0x800C3CA0: addiu       $a0, $zero, 0x22
    ctx->r4 = ADD32(0, 0X22);
        goto L_800C3CAC;
    // 0x800C3CA0: addiu       $a0, $zero, 0x22
    ctx->r4 = ADD32(0, 0X22);
L_800C3CA4:
    // 0x800C3CA4: b           L_800C3CAC
    // 0x800C3CA8: addiu       $a0, $zero, 0x19
    ctx->r4 = ADD32(0, 0X19);
        goto L_800C3CAC;
    // 0x800C3CA8: addiu       $a0, $zero, 0x19
    ctx->r4 = ADD32(0, 0X19);
L_800C3CAC:
    // 0x800C3CAC: addiu       $a2, $zero, 0x28
    ctx->r6 = ADD32(0, 0X28);
    // 0x800C3CB0: jal         0x800C33C8
    // 0x800C3CB4: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    func_800C33C8(rdram, ctx);
        goto after_13;
    // 0x800C3CB4: addiu       $a3, $zero, 0x28
    ctx->r7 = ADD32(0, 0X28);
    after_13:
    // 0x800C3CB8: b           L_800C3DD4
    // 0x800C3CBC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3CBC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3CC0:
    // 0x800C3CC0: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x800C3CC4: lw          $t4, 0x7DC4($t4)
    ctx->r12 = MEM_W(ctx->r12, 0X7DC4);
    // 0x800C3CC8: andi        $v1, $a3, 0xF
    ctx->r3 = ctx->r7 & 0XF;
    // 0x800C3CCC: addiu       $v0, $zero, 0x4
    ctx->r2 = ADD32(0, 0X4);
    // 0x800C3CD0: bne         $t4, $zero, L_800C3CE0
    if (ctx->r12 != 0) {
        // 0x800C3CD4: andi        $t5, $a3, 0x80
        ctx->r13 = ctx->r7 & 0X80;
            goto L_800C3CE0;
    }
    // 0x800C3CD4: andi        $t5, $a3, 0x80
    ctx->r13 = ctx->r7 & 0X80;
    // 0x800C3CD8: b           L_800C3CE0
    // 0x800C3CDC: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
        goto L_800C3CE0;
    // 0x800C3CDC: addiu       $v0, $zero, 0x8
    ctx->r2 = ADD32(0, 0X8);
L_800C3CE0:
    // 0x800C3CE0: bne         $v0, $v1, L_800C3DD0
    if (ctx->r2 != ctx->r3) {
        // 0x800C3CE4: addiu       $a1, $zero, 0x14
        ctx->r5 = ADD32(0, 0X14);
            goto L_800C3DD0;
    }
    // 0x800C3CE4: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    // 0x800C3CE8: bne         $t5, $zero, L_800C3D04
    if (ctx->r13 != 0) {
        // 0x800C3CEC: addiu       $a0, $zero, 0x20
        ctx->r4 = ADD32(0, 0X20);
            goto L_800C3D04;
    }
    // 0x800C3CEC: addiu       $a0, $zero, 0x20
    ctx->r4 = ADD32(0, 0X20);
    // 0x800C3CF0: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C3CF4: lw          $a0, 0x562C($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X562C);
    // 0x800C3CF8: andi        $t6, $a0, 0x1
    ctx->r14 = ctx->r4 & 0X1;
    // 0x800C3CFC: b           L_800C3D04
    // 0x800C3D00: addiu       $a0, $t6, 0x1D
    ctx->r4 = ADD32(ctx->r14, 0X1D);
        goto L_800C3D04;
    // 0x800C3D00: addiu       $a0, $t6, 0x1D
    ctx->r4 = ADD32(ctx->r14, 0X1D);
L_800C3D04:
    // 0x800C3D04: jal         0x800C3320
    // 0x800C3D08: addiu       $a2, $zero, 0x28
    ctx->r6 = ADD32(0, 0X28);
    func_800C3320(rdram, ctx);
        goto after_14;
    // 0x800C3D08: addiu       $a2, $zero, 0x28
    ctx->r6 = ADD32(0, 0X28);
    after_14:
    // 0x800C3D0C: b           L_800C3DD4
    // 0x800C3D10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3D10: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3D14:
    // 0x800C3D14: addiu       $a0, $a3, 0xA
    ctx->r4 = ADD32(ctx->r7, 0XA);
    // 0x800C3D18: addiu       $a1, $zero, 0x5A
    ctx->r5 = ADD32(0, 0X5A);
    // 0x800C3D1C: jal         0x800C3320
    // 0x800C3D20: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    func_800C3320(rdram, ctx);
        goto after_15;
    // 0x800C3D20: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_15:
    // 0x800C3D24: b           L_800C3DD4
    // 0x800C3D28: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3D28: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3D2C:
    // 0x800C3D2C: addiu       $a0, $zero, 0xA
    ctx->r4 = ADD32(0, 0XA);
    // 0x800C3D30: addiu       $a1, $zero, 0x64
    ctx->r5 = ADD32(0, 0X64);
    // 0x800C3D34: jal         0x800C3320
    // 0x800C3D38: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    func_800C3320(rdram, ctx);
        goto after_16;
    // 0x800C3D38: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    after_16:
    // 0x800C3D3C: b           L_800C3DD4
    // 0x800C3D40: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3D40: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3D44:
    // 0x800C3D44: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800C3D48: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    // 0x800C3D4C: jal         0x800C32A0
    // 0x800C3D50: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    func_800C32A0(rdram, ctx);
        goto after_17;
    // 0x800C3D50: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    after_17:
    // 0x800C3D54: b           L_800C3DD4
    // 0x800C3D58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3D58: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3D5C:
    // 0x800C3D5C: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C3D60: lw          $v1, 0x562C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X562C);
    // 0x800C3D64: addiu       $a1, $zero, 0x18
    ctx->r5 = ADD32(0, 0X18);
    // 0x800C3D68: addiu       $a2, $zero, 0x14
    ctx->r6 = ADD32(0, 0X14);
    // 0x800C3D6C: andi        $t7, $v1, 0x1
    ctx->r15 = ctx->r3 & 0X1;
    // 0x800C3D70: jal         0x800C3408
    // 0x800C3D74: addiu       $a0, $t7, 0x40
    ctx->r4 = ADD32(ctx->r15, 0X40);
    func_800C3408(rdram, ctx);
        goto after_18;
    // 0x800C3D74: addiu       $a0, $t7, 0x40
    ctx->r4 = ADD32(ctx->r15, 0X40);
    after_18:
    // 0x800C3D78: b           L_800C3DD4
    // 0x800C3D7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3DD4;
    // 0x800C3D7C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3D80:
    // 0x800C3D80: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x800C3D84: addiu       $v0, $v0, 0x7CF4
    ctx->r2 = ADD32(ctx->r2, 0X7CF4);
    // 0x800C3D88: lw          $t8, 0x0($v0)
    ctx->r24 = MEM_W(ctx->r2, 0X0);
    // 0x800C3D8C: addiu       $t2, $zero, 0x64
    ctx->r10 = ADD32(0, 0X64);
    // 0x800C3D90: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3D94: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x800C3D98: sw          $t9, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r25;
    // 0x800C3D9C: sw          $t2, 0x7CF0($at)
    MEM_W(0X7CF0, ctx->r1) = ctx->r10;
    // 0x800C3DA0: lw          $v1, 0x0($v0)
    ctx->r3 = MEM_W(ctx->r2, 0X0);
    // 0x800C3DA4: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x800C3DA8: beq         $v1, $at, L_800C3DB4
    if (ctx->r3 == ctx->r1) {
        // 0x800C3DAC: addiu       $at, $zero, 0xC
        ctx->r1 = ADD32(0, 0XC);
            goto L_800C3DB4;
    }
    // 0x800C3DAC: addiu       $at, $zero, 0xC
    ctx->r1 = ADD32(0, 0XC);
    // 0x800C3DB0: bne         $v1, $at, L_800C3DD0
    if (ctx->r3 != ctx->r1) {
        // 0x800C3DB4: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C3DD0;
    }
L_800C3DB4:
    // 0x800C3DB4: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C3DB8: lw          $v1, 0x562C($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X562C);
    // 0x800C3DBC: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    // 0x800C3DC0: addiu       $a2, $zero, 0x3C
    ctx->r6 = ADD32(0, 0X3C);
    // 0x800C3DC4: andi        $t3, $v1, 0x1
    ctx->r11 = ctx->r3 & 0X1;
    // 0x800C3DC8: jal         0x800C32A0
    // 0x800C3DCC: addiu       $a0, $t3, 0x17
    ctx->r4 = ADD32(ctx->r11, 0X17);
    func_800C32A0(rdram, ctx);
        goto after_19;
    // 0x800C3DCC: addiu       $a0, $t3, 0x17
    ctx->r4 = ADD32(ctx->r11, 0X17);
    after_19:
L_800C3DD0:
    // 0x800C3DD0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3DD4:
    // 0x800C3DD4: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800C3DD8: jr          $ra
    // 0x800C3DDC: nop

    return;
    // 0x800C3DDC: nop

;}
RECOMP_FUNC void func_800C3DE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3DE0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3DE4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3DE8: addiu       $a0, $zero, 0x20
    ctx->r4 = ADD32(0, 0X20);
    // 0x800C3DEC: jal         0x800C37F4
    // 0x800C3DF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x800C3DF0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C3DF4: lui         $a0, 0xF100
    ctx->r4 = S32(0XF100 << 16);
    // 0x800C3DF8: jal         0x800C53B0
    // 0x800C3DFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_1;
    // 0x800C3DFC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x800C3E00: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3E04: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x800C3E08: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3E0C: sw          $t6, 0x7CC4($at)
    MEM_W(0X7CC4, ctx->r1) = ctx->r14;
    // 0x800C3E10: jr          $ra
    // 0x800C3E14: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800C3E14: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800C3E18(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3E18: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3E1C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3E20: addiu       $a0, $zero, 0x20
    ctx->r4 = ADD32(0, 0X20);
    // 0x800C3E24: jal         0x800C37F4
    // 0x800C3E28: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C37F4(rdram, ctx);
        goto after_0;
    // 0x800C3E28: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C3E2C: lui         $a0, 0xF200
    ctx->r4 = S32(0XF200 << 16);
    // 0x800C3E30: jal         0x800C53B0
    // 0x800C3E34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS32(rdram, ctx);
        goto after_1;
    // 0x800C3E34: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x800C3E38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3E3C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C3E40: sw          $zero, 0x7CC4($at)
    MEM_W(0X7CC4, ctx->r1) = 0;
    // 0x800C3E44: jr          $ra
    // 0x800C3E48: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800C3E48: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800C3E4C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3E4C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3E50: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3E54: jal         0x800C3500
    // 0x800C3E58: addiu       $a0, $zero, 0x5C
    ctx->r4 = ADD32(0, 0X5C);
    func_800C3500(rdram, ctx);
        goto after_0;
    // 0x800C3E58: addiu       $a0, $zero, 0x5C
    ctx->r4 = ADD32(0, 0X5C);
    after_0:
    // 0x800C3E5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C3E60: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3E64: jr          $ra
    // 0x800C3E68: nop

    return;
    // 0x800C3E68: nop

;}
RECOMP_FUNC void func_800C3E6C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3E6C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C3E70: beq         $a0, $zero, L_800C3EA0
    if (ctx->r4 == 0) {
        // 0x800C3E74: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C3EA0;
    }
    // 0x800C3E74: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3E78: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800C3E7C: beq         $a0, $at, L_800C3EB0
    if (ctx->r4 == ctx->r1) {
        // 0x800C3E80: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C3EB0;
    }
    // 0x800C3E80: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C3E84: beq         $a0, $at, L_800C3EC0
    if (ctx->r4 == ctx->r1) {
        // 0x800C3E88: lui         $a1, 0x8004
        ctx->r5 = S32(0X8004 << 16);
            goto L_800C3EC0;
    }
    // 0x800C3E88: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C3E8C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3E90: beq         $a0, $at, L_800C3EDC
    if (ctx->r4 == ctx->r1) {
        // 0x800C3E94: nop
    
            goto L_800C3EDC;
    }
    // 0x800C3E94: nop

    // 0x800C3E98: b           L_800C3EE8
    // 0x800C3E9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3EE8;
    // 0x800C3E9C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3EA0:
    // 0x800C3EA0: jal         0x800C3500
    // 0x800C3EA4: addiu       $a0, $zero, 0x18
    ctx->r4 = ADD32(0, 0X18);
    func_800C3500(rdram, ctx);
        goto after_0;
    // 0x800C3EA4: addiu       $a0, $zero, 0x18
    ctx->r4 = ADD32(0, 0X18);
    after_0:
    // 0x800C3EA8: b           L_800C3EE8
    // 0x800C3EAC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3EE8;
    // 0x800C3EAC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3EB0:
    // 0x800C3EB0: jal         0x800C3500
    // 0x800C3EB4: addiu       $a0, $zero, 0x65
    ctx->r4 = ADD32(0, 0X65);
    func_800C3500(rdram, ctx);
        goto after_1;
    // 0x800C3EB4: addiu       $a0, $zero, 0x65
    ctx->r4 = ADD32(0, 0X65);
    after_1:
    // 0x800C3EB8: b           L_800C3EE8
    // 0x800C3EBC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3EE8;
    // 0x800C3EBC: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3EC0:
    // 0x800C3EC0: lw          $a1, 0x562C($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X562C);
    // 0x800C3EC4: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x800C3EC8: andi        $t6, $a1, 0x3
    ctx->r14 = ctx->r5 & 0X3;
    // 0x800C3ECC: jal         0x800C317C
    // 0x800C3ED0: addiu       $a1, $t6, 0x8
    ctx->r5 = ADD32(ctx->r14, 0X8);
    func_800C317C(rdram, ctx);
        goto after_2;
    // 0x800C3ED0: addiu       $a1, $t6, 0x8
    ctx->r5 = ADD32(ctx->r14, 0X8);
    after_2:
    // 0x800C3ED4: b           L_800C3EE8
    // 0x800C3ED8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C3EE8;
    // 0x800C3ED8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3EDC:
    // 0x800C3EDC: jal         0x800C377C
    // 0x800C3EE0: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    func_800C377C(rdram, ctx);
        goto after_3;
    // 0x800C3EE0: addiu       $a0, $zero, 0xB
    ctx->r4 = ADD32(0, 0XB);
    after_3:
    // 0x800C3EE4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C3EE8:
    // 0x800C3EE8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C3EEC: jr          $ra
    // 0x800C3EF0: nop

    return;
    // 0x800C3EF0: nop

;}
RECOMP_FUNC void func_800C3EF4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C3EF4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x800C3EF8: slti        $at, $a0, 0x2
    ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
    // 0x800C3EFC: beq         $at, $zero, L_800C3F18
    if (ctx->r1 == 0) {
        // 0x800C3F00: sw          $ra, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r31;
            goto L_800C3F18;
    }
    // 0x800C3F00: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C3F04: slti        $at, $a0, -0x1
    ctx->r1 = SIGNED(ctx->r4) < -0X1 ? 1 : 0;
    // 0x800C3F08: bnel        $at, $zero, L_800C3F1C
    if (ctx->r1 != 0) {
        // 0x800C3F0C: slti        $at, $a0, 0x2
        ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
            goto L_800C3F1C;
    }
    goto skip_0;
    // 0x800C3F0C: slti        $at, $a0, 0x2
    ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
    skip_0:
    // 0x800C3F10: b           L_800C3F30
    // 0x800C3F14: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_800C3F30;
    // 0x800C3F14: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_800C3F18:
    // 0x800C3F18: slti        $at, $a0, 0x2
    ctx->r1 = SIGNED(ctx->r4) < 0X2 ? 1 : 0;
L_800C3F1C:
    // 0x800C3F1C: bne         $at, $zero, L_800C3F2C
    if (ctx->r1 != 0) {
        // 0x800C3F20: addiu       $v1, $zero, 0x1
        ctx->r3 = ADD32(0, 0X1);
            goto L_800C3F2C;
    }
    // 0x800C3F20: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C3F24: b           L_800C3F30
    // 0x800C3F28: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
        goto L_800C3F30;
    // 0x800C3F28: addiu       $v1, $zero, 0x2
    ctx->r3 = ADD32(0, 0X2);
L_800C3F2C:
    // 0x800C3F2C: negu        $a0, $a0
    ctx->r4 = SUB32(0, ctx->r4);
L_800C3F30:
    // 0x800C3F30: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x800C3F34: lb          $t6, 0x7C94($t6)
    ctx->r14 = MEM_B(ctx->r14, 0X7C94);
    // 0x800C3F38: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C3F3C: bnel        $t6, $at, L_800C406C
    if (ctx->r14 != ctx->r1) {
        // 0x800C3F40: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C406C;
    }
    goto skip_1;
    // 0x800C3F40: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_1:
    // 0x800C3F44: beq         $v1, $zero, L_800C3F70
    if (ctx->r3 == 0) {
        // 0x800C3F48: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C3F70;
    }
    // 0x800C3F48: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3F4C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C3F50: beq         $v1, $a1, L_800C3FA0
    if (ctx->r3 == ctx->r5) {
        // 0x800C3F54: slti        $at, $a0, 0x14
        ctx->r1 = SIGNED(ctx->r4) < 0X14 ? 1 : 0;
            goto L_800C3FA0;
    }
    // 0x800C3F54: slti        $at, $a0, 0x14
    ctx->r1 = SIGNED(ctx->r4) < 0X14 ? 1 : 0;
    // 0x800C3F58: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C3F5C: beq         $v1, $at, L_800C3FC4
    if (ctx->r3 == ctx->r1) {
        // 0x800C3F60: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C3FC4;
    }
    // 0x800C3F60: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3F64: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3F68: b           L_800C3FE4
    // 0x800C3F6C: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
        goto L_800C3FE4;
    // 0x800C3F6C: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
L_800C3F70:
    // 0x800C3F70: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
    // 0x800C3F74: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x800C3F78: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C3F7C: bnel        $a1, $v0, L_800C406C
    if (ctx->r5 != ctx->r2) {
        // 0x800C3F80: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C406C;
    }
    goto skip_2;
    // 0x800C3F80: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_2:
    // 0x800C3F84: lw          $t7, 0x562C($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X562C);
    // 0x800C3F88: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C3F8C: divu        $zero, $t7, $at
    lo = S32(U32(ctx->r15) / U32(ctx->r1)); hi = S32(U32(ctx->r15) % U32(ctx->r1));
    // 0x800C3F90: mfhi        $t8
    ctx->r24 = hi;
    // 0x800C3F94: addiu       $t9, $t8, 0x16
    ctx->r25 = ADD32(ctx->r24, 0X16);
    // 0x800C3F98: b           L_800C3FE4
    // 0x800C3F9C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
        goto L_800C3FE4;
    // 0x800C3F9C: sw          $t9, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r25;
L_800C3FA0:
    // 0x800C3FA0: bne         $at, $zero, L_800C3FB8
    if (ctx->r1 != 0) {
        // 0x800C3FA4: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C3FB8;
    }
    // 0x800C3FA4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3FA8: addiu       $t0, $zero, 0x15
    ctx->r8 = ADD32(0, 0X15);
    // 0x800C3FAC: sw          $t0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r8;
    // 0x800C3FB0: b           L_800C3FBC
    // 0x800C3FB4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_800C3FBC;
    // 0x800C3FB4: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_800C3FB8:
    // 0x800C3FB8: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
L_800C3FBC:
    // 0x800C3FBC: b           L_800C3FE4
    // 0x800C3FC0: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
        goto L_800C3FE4;
    // 0x800C3FC0: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
L_800C3FC4:
    // 0x800C3FC4: slti        $at, $a0, 0x14
    ctx->r1 = SIGNED(ctx->r4) < 0X14 ? 1 : 0;
    // 0x800C3FC8: bne         $at, $zero, L_800C3FDC
    if (ctx->r1 != 0) {
        // 0x800C3FCC: addiu       $t1, $zero, 0x19
        ctx->r9 = ADD32(0, 0X19);
            goto L_800C3FDC;
    }
    // 0x800C3FCC: addiu       $t1, $zero, 0x19
    ctx->r9 = ADD32(0, 0X19);
    // 0x800C3FD0: sw          $t1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r9;
    // 0x800C3FD4: b           L_800C3FE0
    // 0x800C3FD8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
        goto L_800C3FE0;
    // 0x800C3FD8: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
L_800C3FDC:
    // 0x800C3FDC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
L_800C3FE0:
    // 0x800C3FE0: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
L_800C3FE4:
    // 0x800C3FE4: beq         $a1, $v0, L_800C3FF4
    if (ctx->r5 == ctx->r2) {
        // 0x800C3FE8: lw          $t2, 0x18($sp)
        ctx->r10 = MEM_W(ctx->r29, 0X18);
            goto L_800C3FF4;
    }
    // 0x800C3FE8: lw          $t2, 0x18($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X18);
    // 0x800C3FEC: addiu       $at, $zero, 0x15
    ctx->r1 = ADD32(0, 0X15);
    // 0x800C3FF0: beq         $t2, $at, L_800C4068
    if (ctx->r10 == ctx->r1) {
        // 0x800C3FF4: lui         $v0, 0x801D
        ctx->r2 = S32(0X801D << 16);
            goto L_800C4068;
    }
L_800C3FF4:
    // 0x800C3FF4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C3FF8: addiu       $v0, $v0, 0x7DF0
    ctx->r2 = ADD32(ctx->r2, 0X7DF0);
    // 0x800C3FFC: lbu         $t3, 0x2($v0)
    ctx->r11 = MEM_BU(ctx->r2, 0X2);
    // 0x800C4000: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C4004: ori         $a0, $a0, 0xC02
    ctx->r4 = ctx->r4 | 0XC02;
    // 0x800C4008: beq         $t3, $zero, L_800C401C
    if (ctx->r11 == 0) {
        // 0x800C400C: sll         $a1, $v1, 24
        ctx->r5 = S32(ctx->r3 << 24);
            goto L_800C401C;
    }
    // 0x800C400C: sll         $a1, $v1, 24
    ctx->r5 = S32(ctx->r3 << 24);
    // 0x800C4010: lbu         $t4, 0x1($v0)
    ctx->r12 = MEM_BU(ctx->r2, 0X1);
    // 0x800C4014: slti        $at, $t4, 0x51
    ctx->r1 = SIGNED(ctx->r12) < 0X51 ? 1 : 0;
    // 0x800C4018: beq         $at, $zero, L_800C4068
    if (ctx->r1 == 0) {
        // 0x800C401C: sra         $t5, $a1, 24
        ctx->r13 = S32(SIGNED(ctx->r5) >> 24);
            goto L_800C4068;
    }
L_800C401C:
    // 0x800C401C: sra         $t5, $a1, 24
    ctx->r13 = S32(SIGNED(ctx->r5) >> 24);
    // 0x800C4020: jal         0x800C53D4
    // 0x800C4024: or          $a1, $t5, $zero
    ctx->r5 = ctx->r13 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C4024: or          $a1, $t5, $zero
    ctx->r5 = ctx->r13 | 0;
    after_0:
    // 0x800C4028: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C402C: ori         $a0, $a0, 0xC01
    ctx->r4 = ctx->r4 | 0XC01;
    // 0x800C4030: jal         0x800C53D4
    // 0x800C4034: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C4034: lb          $a1, 0x1B($sp)
    ctx->r5 = MEM_B(ctx->r29, 0X1B);
    after_1:
    // 0x800C4038: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C403C: ori         $a0, $a0, 0xC00
    ctx->r4 = ctx->r4 | 0XC00;
    // 0x800C4040: jal         0x800C53D4
    // 0x800C4044: addiu       $a1, $zero, 0x7E
    ctx->r5 = ADD32(0, 0X7E);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_2;
    // 0x800C4044: addiu       $a1, $zero, 0x7E
    ctx->r5 = ADD32(0, 0X7E);
    after_2:
    // 0x800C4048: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C404C: lw          $t6, 0x18($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X18);
    // 0x800C4050: addiu       $v0, $v0, 0x7DF0
    ctx->r2 = ADD32(ctx->r2, 0X7DF0);
    // 0x800C4054: addiu       $t7, $zero, 0x55
    ctx->r15 = ADD32(0, 0X55);
    // 0x800C4058: addiu       $t8, $zero, 0x32
    ctx->r24 = ADD32(0, 0X32);
    // 0x800C405C: sb          $t7, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r15;
    // 0x800C4060: sb          $t8, 0x2($v0)
    MEM_B(0X2, ctx->r2) = ctx->r24;
    // 0x800C4064: sb          $t6, 0x0($v0)
    MEM_B(0X0, ctx->r2) = ctx->r14;
L_800C4068:
    // 0x800C4068: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C406C:
    // 0x800C406C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x800C4070: jr          $ra
    // 0x800C4074: nop

    return;
    // 0x800C4074: nop

;}
RECOMP_FUNC void func_800C4078(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C4078: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C407C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C4080: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C4084: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C4088: jal         0x800C53D4
    // 0x800C408C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_0;
    // 0x800C408C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_0:
    // 0x800C4090: lui         $a0, 0x600
    ctx->r4 = S32(0X600 << 16);
    // 0x800C4094: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C4098: jal         0x800C53D4
    // 0x800C409C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_1;
    // 0x800C409C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_1:
    // 0x800C40A0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C40A4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C40A8: jr          $ra
    // 0x800C40AC: nop

    return;
    // 0x800C40AC: nop

;}
RECOMP_FUNC void func_800C40B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C40B0: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C40B4: lw          $v0, 0x7DD4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DD4);
    // 0x800C40B8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C40BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C40C0: beq         $v0, $zero, L_800C40E4
    if (ctx->r2 == 0) {
        // 0x800C40C4: addiu       $v1, $zero, 0x1
        ctx->r3 = ADD32(0, 0X1);
            goto L_800C40E4;
    }
    // 0x800C40C4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C40C8: beq         $v0, $v1, L_800C4428
    if (ctx->r2 == ctx->r3) {
        // 0x800C40CC: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C4428;
    }
    // 0x800C40CC: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C40D0: beq         $v0, $at, L_800C4768
    if (ctx->r2 == ctx->r1) {
        // 0x800C40D4: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_800C4768;
    }
    // 0x800C40D4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C40D8: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C40DC: b           L_800C4868
    // 0x800C40E0: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C40E0: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C40E4:
    // 0x800C40E4: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C40E8: lw          $v0, 0x7DC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC8);
    // 0x800C40EC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C40F0: beq         $v0, $zero, L_800C4118
    if (ctx->r2 == 0) {
        // 0x800C40F4: nop
    
            goto L_800C4118;
    }
    // 0x800C40F4: nop

    // 0x800C40F8: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C40FC: beq         $v0, $v1, L_800C421C
    if (ctx->r2 == ctx->r3) {
        // 0x800C4100: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C421C;
    }
    // 0x800C4100: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C4104: beq         $v0, $at, L_800C4324
    if (ctx->r2 == ctx->r1) {
        // 0x800C4108: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_800C4324;
    }
    // 0x800C4108: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C410C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4110: b           L_800C4868
    // 0x800C4114: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4114: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4118:
    // 0x800C4118: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C411C: addiu       $at, $zero, 0x2EE
    ctx->r1 = ADD32(0, 0X2EE);
    // 0x800C4120: beq         $v1, $at, L_800C4148
    if (ctx->r3 == ctx->r1) {
        // 0x800C4124: addiu       $at, $zero, 0x348
        ctx->r1 = ADD32(0, 0X348);
            goto L_800C4148;
    }
    // 0x800C4124: addiu       $at, $zero, 0x348
    ctx->r1 = ADD32(0, 0X348);
    // 0x800C4128: beq         $v1, $at, L_800C415C
    if (ctx->r3 == ctx->r1) {
        // 0x800C412C: addiu       $at, $zero, 0x398
        ctx->r1 = ADD32(0, 0X398);
            goto L_800C415C;
    }
    // 0x800C412C: addiu       $at, $zero, 0x398
    ctx->r1 = ADD32(0, 0X398);
    // 0x800C4130: beq         $v1, $at, L_800C4170
    if (ctx->r3 == ctx->r1) {
        // 0x800C4134: addiu       $at, $zero, 0x3CA
        ctx->r1 = ADD32(0, 0X3CA);
            goto L_800C4170;
    }
    // 0x800C4134: addiu       $at, $zero, 0x3CA
    ctx->r1 = ADD32(0, 0X3CA);
    // 0x800C4138: beql        $v1, $at, L_800C4190
    if (ctx->r3 == ctx->r1) {
        // 0x800C413C: slti        $at, $v1, 0x349
        ctx->r1 = SIGNED(ctx->r3) < 0X349 ? 1 : 0;
            goto L_800C4190;
    }
    goto skip_0;
    // 0x800C413C: slti        $at, $v1, 0x349
    ctx->r1 = SIGNED(ctx->r3) < 0X349 ? 1 : 0;
    skip_0:
    // 0x800C4140: b           L_800C4190
    // 0x800C4144: slti        $at, $v1, 0x349
    ctx->r1 = SIGNED(ctx->r3) < 0X349 ? 1 : 0;
        goto L_800C4190;
    // 0x800C4144: slti        $at, $v1, 0x349
    ctx->r1 = SIGNED(ctx->r3) < 0X349 ? 1 : 0;
L_800C4148:
    // 0x800C4148: jal         0x800C1650
    // 0x800C414C: addiu       $a0, $zero, 0x4B0
    ctx->r4 = ADD32(0, 0X4B0);
    func_800C1650(rdram, ctx);
        goto after_0;
    // 0x800C414C: addiu       $a0, $zero, 0x4B0
    ctx->r4 = ADD32(0, 0X4B0);
    after_0:
    // 0x800C4150: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4154: b           L_800C418C
    // 0x800C4158: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C418C;
    // 0x800C4158: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C415C:
    // 0x800C415C: jal         0x800C3500
    // 0x800C4160: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C3500(rdram, ctx);
        goto after_1;
    // 0x800C4160: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_1:
    // 0x800C4164: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4168: b           L_800C418C
    // 0x800C416C: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C418C;
    // 0x800C416C: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4170:
    // 0x800C4170: jal         0x800C4078
    // 0x800C4174: nop

    func_800C4078(rdram, ctx);
        goto after_2;
    // 0x800C4174: nop

    after_2:
    // 0x800C4178: addiu       $a0, $zero, 0x1D
    ctx->r4 = ADD32(0, 0X1D);
    // 0x800C417C: jal         0x800C15C8
    // 0x800C4180: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_3;
    // 0x800C4180: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_3:
    // 0x800C4184: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4188: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C418C:
    // 0x800C418C: slti        $at, $v1, 0x349
    ctx->r1 = SIGNED(ctx->r3) < 0X349 ? 1 : 0;
L_800C4190:
    // 0x800C4190: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C4194: slti        $at, $v1, 0x398
        ctx->r1 = SIGNED(ctx->r3) < 0X398 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C4194: slti        $at, $v1, 0x398
    ctx->r1 = SIGNED(ctx->r3) < 0X398 ? 1 : 0;
    // 0x800C4198: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C419C: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_1;
    // 0x800C419C: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_1:
    // 0x800C41A0: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C41A4: lui         $at, 0x4466
    ctx->r1 = S32(0X4466 << 16);
    // 0x800C41A8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C41AC: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C41B0: lui         $at, 0x42A0
    ctx->r1 = S32(0X42A0 << 16);
    // 0x800C41B4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C41B8: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C41BC: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C41C0: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C41C4: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C41C8: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C41CC: jal         0x800C538C
    // 0x800C41D0: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_4;
    // 0x800C41D0: nop

    after_4:
    // 0x800C41D4: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x800C41D8: lw          $t6, 0x7E14($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X7E14);
    // 0x800C41DC: lui         $at, 0x4466
    ctx->r1 = S32(0X4466 << 16);
    // 0x800C41E0: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C41E4: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x800C41E8: lui         $at, 0x42A0
    ctx->r1 = S32(0X42A0 << 16);
    // 0x800C41EC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C41F0: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C41F4: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C41F8: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C41FC: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C4200: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4204: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4208: jal         0x800C538C
    // 0x800C420C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_5;
    // 0x800C420C: nop

    after_5:
    // 0x800C4210: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4214: b           L_800C4868
    // 0x800C4218: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4218: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C421C:
    // 0x800C421C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4220: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C4224: addiu       $at, $zero, 0x28A
    ctx->r1 = ADD32(0, 0X28A);
    // 0x800C4228: beq         $v1, $at, L_800C4250
    if (ctx->r3 == ctx->r1) {
        // 0x800C422C: addiu       $at, $zero, 0x2BC
        ctx->r1 = ADD32(0, 0X2BC);
            goto L_800C4250;
    }
    // 0x800C422C: addiu       $at, $zero, 0x2BC
    ctx->r1 = ADD32(0, 0X2BC);
    // 0x800C4230: beq         $v1, $at, L_800C4264
    if (ctx->r3 == ctx->r1) {
        // 0x800C4234: addiu       $at, $zero, 0x2E4
        ctx->r1 = ADD32(0, 0X2E4);
            goto L_800C4264;
    }
    // 0x800C4234: addiu       $at, $zero, 0x2E4
    ctx->r1 = ADD32(0, 0X2E4);
    // 0x800C4238: beq         $v1, $at, L_800C4278
    if (ctx->r3 == ctx->r1) {
        // 0x800C423C: addiu       $at, $zero, 0x311
        ctx->r1 = ADD32(0, 0X311);
            goto L_800C4278;
    }
    // 0x800C423C: addiu       $at, $zero, 0x311
    ctx->r1 = ADD32(0, 0X311);
    // 0x800C4240: beql        $v1, $at, L_800C4298
    if (ctx->r3 == ctx->r1) {
        // 0x800C4244: slti        $at, $v1, 0x26D
        ctx->r1 = SIGNED(ctx->r3) < 0X26D ? 1 : 0;
            goto L_800C4298;
    }
    goto skip_2;
    // 0x800C4244: slti        $at, $v1, 0x26D
    ctx->r1 = SIGNED(ctx->r3) < 0X26D ? 1 : 0;
    skip_2:
    // 0x800C4248: b           L_800C4298
    // 0x800C424C: slti        $at, $v1, 0x26D
    ctx->r1 = SIGNED(ctx->r3) < 0X26D ? 1 : 0;
        goto L_800C4298;
    // 0x800C424C: slti        $at, $v1, 0x26D
    ctx->r1 = SIGNED(ctx->r3) < 0X26D ? 1 : 0;
L_800C4250:
    // 0x800C4250: jal         0x800C1650
    // 0x800C4254: addiu       $a0, $zero, 0x3E8
    ctx->r4 = ADD32(0, 0X3E8);
    func_800C1650(rdram, ctx);
        goto after_6;
    // 0x800C4254: addiu       $a0, $zero, 0x3E8
    ctx->r4 = ADD32(0, 0X3E8);
    after_6:
    // 0x800C4258: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C425C: b           L_800C4294
    // 0x800C4260: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4294;
    // 0x800C4260: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4264:
    // 0x800C4264: jal         0x800C3500
    // 0x800C4268: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C3500(rdram, ctx);
        goto after_7;
    // 0x800C4268: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_7:
    // 0x800C426C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4270: b           L_800C4294
    // 0x800C4274: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4294;
    // 0x800C4274: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4278:
    // 0x800C4278: jal         0x800C4078
    // 0x800C427C: nop

    func_800C4078(rdram, ctx);
        goto after_8;
    // 0x800C427C: nop

    after_8:
    // 0x800C4280: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    // 0x800C4284: jal         0x800C15C8
    // 0x800C4288: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_9;
    // 0x800C4288: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_9:
    // 0x800C428C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4290: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4294:
    // 0x800C4294: slti        $at, $v1, 0x26D
    ctx->r1 = SIGNED(ctx->r3) < 0X26D ? 1 : 0;
L_800C4298:
    // 0x800C4298: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C429C: slti        $at, $v1, 0x2E4
        ctx->r1 = SIGNED(ctx->r3) < 0X2E4 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C429C: slti        $at, $v1, 0x2E4
    ctx->r1 = SIGNED(ctx->r3) < 0X2E4 ? 1 : 0;
    // 0x800C42A0: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C42A4: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_3;
    // 0x800C42A4: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_3:
    // 0x800C42A8: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C42AC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C42B0: lwc1        $f4, -0x3A68($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X3A68);
    // 0x800C42B4: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C42B8: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C42BC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C42C0: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C42C4: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C42C8: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C42CC: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C42D0: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C42D4: jal         0x800C538C
    // 0x800C42D8: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_10;
    // 0x800C42D8: nop

    after_10:
    // 0x800C42DC: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x800C42E0: lw          $t7, 0x7E14($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X7E14);
    // 0x800C42E4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C42E8: lwc1        $f6, -0x3A64($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3A64);
    // 0x800C42EC: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x800C42F0: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C42F4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C42F8: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C42FC: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4300: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C4304: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C4308: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C430C: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4310: jal         0x800C538C
    // 0x800C4314: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_11;
    // 0x800C4314: nop

    after_11:
    // 0x800C4318: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C431C: b           L_800C4868
    // 0x800C4320: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4320: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4324:
    // 0x800C4324: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C4328: addiu       $at, $zero, 0x258
    ctx->r1 = ADD32(0, 0X258);
    // 0x800C432C: beq         $v1, $at, L_800C4354
    if (ctx->r3 == ctx->r1) {
        // 0x800C4330: addiu       $at, $zero, 0x2A8
        ctx->r1 = ADD32(0, 0X2A8);
            goto L_800C4354;
    }
    // 0x800C4330: addiu       $at, $zero, 0x2A8
    ctx->r1 = ADD32(0, 0X2A8);
    // 0x800C4334: beq         $v1, $at, L_800C4368
    if (ctx->r3 == ctx->r1) {
        // 0x800C4338: addiu       $at, $zero, 0x2D0
        ctx->r1 = ADD32(0, 0X2D0);
            goto L_800C4368;
    }
    // 0x800C4338: addiu       $at, $zero, 0x2D0
    ctx->r1 = ADD32(0, 0X2D0);
    // 0x800C433C: beq         $v1, $at, L_800C437C
    if (ctx->r3 == ctx->r1) {
        // 0x800C4340: addiu       $at, $zero, 0x2E4
        ctx->r1 = ADD32(0, 0X2E4);
            goto L_800C437C;
    }
    // 0x800C4340: addiu       $at, $zero, 0x2E4
    ctx->r1 = ADD32(0, 0X2E4);
    // 0x800C4344: beql        $v1, $at, L_800C439C
    if (ctx->r3 == ctx->r1) {
        // 0x800C4348: slti        $at, $v1, 0x259
        ctx->r1 = SIGNED(ctx->r3) < 0X259 ? 1 : 0;
            goto L_800C439C;
    }
    goto skip_4;
    // 0x800C4348: slti        $at, $v1, 0x259
    ctx->r1 = SIGNED(ctx->r3) < 0X259 ? 1 : 0;
    skip_4:
    // 0x800C434C: b           L_800C439C
    // 0x800C4350: slti        $at, $v1, 0x259
    ctx->r1 = SIGNED(ctx->r3) < 0X259 ? 1 : 0;
        goto L_800C439C;
    // 0x800C4350: slti        $at, $v1, 0x259
    ctx->r1 = SIGNED(ctx->r3) < 0X259 ? 1 : 0;
L_800C4354:
    // 0x800C4354: jal         0x800C1650
    // 0x800C4358: addiu       $a0, $zero, 0x4B0
    ctx->r4 = ADD32(0, 0X4B0);
    func_800C1650(rdram, ctx);
        goto after_12;
    // 0x800C4358: addiu       $a0, $zero, 0x4B0
    ctx->r4 = ADD32(0, 0X4B0);
    after_12:
    // 0x800C435C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4360: b           L_800C4398
    // 0x800C4364: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4398;
    // 0x800C4364: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4368:
    // 0x800C4368: jal         0x800C3500
    // 0x800C436C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C3500(rdram, ctx);
        goto after_13;
    // 0x800C436C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_13:
    // 0x800C4370: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4374: b           L_800C4398
    // 0x800C4378: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4398;
    // 0x800C4378: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C437C:
    // 0x800C437C: jal         0x800C4078
    // 0x800C4380: nop

    func_800C4078(rdram, ctx);
        goto after_14;
    // 0x800C4380: nop

    after_14:
    // 0x800C4384: addiu       $a0, $zero, 0x1F
    ctx->r4 = ADD32(0, 0X1F);
    // 0x800C4388: jal         0x800C15C8
    // 0x800C438C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_15;
    // 0x800C438C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
    // 0x800C4390: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4394: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4398:
    // 0x800C4398: slti        $at, $v1, 0x259
    ctx->r1 = SIGNED(ctx->r3) < 0X259 ? 1 : 0;
L_800C439C:
    // 0x800C439C: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C43A0: slti        $at, $v1, 0x2D0
        ctx->r1 = SIGNED(ctx->r3) < 0X2D0 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C43A0: slti        $at, $v1, 0x2D0
    ctx->r1 = SIGNED(ctx->r3) < 0X2D0 ? 1 : 0;
    // 0x800C43A4: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C43A8: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_5;
    // 0x800C43A8: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_5:
    // 0x800C43AC: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C43B0: lui         $at, 0x4434
    ctx->r1 = S32(0X4434 << 16);
    // 0x800C43B4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C43B8: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C43BC: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C43C0: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C43C4: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C43C8: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C43CC: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C43D0: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C43D4: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C43D8: jal         0x800C538C
    // 0x800C43DC: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_16;
    // 0x800C43DC: nop

    after_16:
    // 0x800C43E0: lui         $t8, 0x801D
    ctx->r24 = S32(0X801D << 16);
    // 0x800C43E4: lw          $t8, 0x7E14($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X7E14);
    // 0x800C43E8: lui         $at, 0x4434
    ctx->r1 = S32(0X4434 << 16);
    // 0x800C43EC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C43F0: mtc1        $t8, $f4
    ctx->f4.u32l = ctx->r24;
    // 0x800C43F4: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C43F8: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C43FC: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C4400: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4404: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C4408: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C440C: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4410: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4414: jal         0x800C538C
    // 0x800C4418: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_17;
    // 0x800C4418: nop

    after_17:
    // 0x800C441C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4420: b           L_800C4868
    // 0x800C4424: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4424: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4428:
    // 0x800C4428: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C442C: lw          $v0, 0x7DC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC8);
    // 0x800C4430: beq         $v0, $zero, L_800C4454
    if (ctx->r2 == 0) {
        // 0x800C4434: nop
    
            goto L_800C4454;
    }
    // 0x800C4434: nop

    // 0x800C4438: beq         $v0, $v1, L_800C455C
    if (ctx->r2 == ctx->r3) {
        // 0x800C443C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C455C;
    }
    // 0x800C443C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C4440: beq         $v0, $at, L_800C4664
    if (ctx->r2 == ctx->r1) {
        // 0x800C4444: lui         $v1, 0x801D
        ctx->r3 = S32(0X801D << 16);
            goto L_800C4664;
    }
    // 0x800C4444: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4448: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C444C: b           L_800C4868
    // 0x800C4450: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4450: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4454:
    // 0x800C4454: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4458: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C445C: addiu       $at, $zero, 0x1B8
    ctx->r1 = ADD32(0, 0X1B8);
    // 0x800C4460: beq         $v1, $at, L_800C4488
    if (ctx->r3 == ctx->r1) {
        // 0x800C4464: addiu       $at, $zero, 0x1EA
        ctx->r1 = ADD32(0, 0X1EA);
            goto L_800C4488;
    }
    // 0x800C4464: addiu       $at, $zero, 0x1EA
    ctx->r1 = ADD32(0, 0X1EA);
    // 0x800C4468: beq         $v1, $at, L_800C449C
    if (ctx->r3 == ctx->r1) {
        // 0x800C446C: addiu       $at, $zero, 0x24E
        ctx->r1 = ADD32(0, 0X24E);
            goto L_800C449C;
    }
    // 0x800C446C: addiu       $at, $zero, 0x24E
    ctx->r1 = ADD32(0, 0X24E);
    // 0x800C4470: beq         $v1, $at, L_800C44B0
    if (ctx->r3 == ctx->r1) {
        // 0x800C4474: addiu       $at, $zero, 0x262
        ctx->r1 = ADD32(0, 0X262);
            goto L_800C44B0;
    }
    // 0x800C4474: addiu       $at, $zero, 0x262
    ctx->r1 = ADD32(0, 0X262);
    // 0x800C4478: beql        $v1, $at, L_800C44D0
    if (ctx->r3 == ctx->r1) {
        // 0x800C447C: slti        $at, $v1, 0x191
        ctx->r1 = SIGNED(ctx->r3) < 0X191 ? 1 : 0;
            goto L_800C44D0;
    }
    goto skip_6;
    // 0x800C447C: slti        $at, $v1, 0x191
    ctx->r1 = SIGNED(ctx->r3) < 0X191 ? 1 : 0;
    skip_6:
    // 0x800C4480: b           L_800C44D0
    // 0x800C4484: slti        $at, $v1, 0x191
    ctx->r1 = SIGNED(ctx->r3) < 0X191 ? 1 : 0;
        goto L_800C44D0;
    // 0x800C4484: slti        $at, $v1, 0x191
    ctx->r1 = SIGNED(ctx->r3) < 0X191 ? 1 : 0;
L_800C4488:
    // 0x800C4488: jal         0x800C1650
    // 0x800C448C: addiu       $a0, $zero, 0x708
    ctx->r4 = ADD32(0, 0X708);
    func_800C1650(rdram, ctx);
        goto after_18;
    // 0x800C448C: addiu       $a0, $zero, 0x708
    ctx->r4 = ADD32(0, 0X708);
    after_18:
    // 0x800C4490: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4494: b           L_800C44CC
    // 0x800C4498: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C44CC;
    // 0x800C4498: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C449C:
    // 0x800C449C: jal         0x800C3500
    // 0x800C44A0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C3500(rdram, ctx);
        goto after_19;
    // 0x800C44A0: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_19:
    // 0x800C44A4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C44A8: b           L_800C44CC
    // 0x800C44AC: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C44CC;
    // 0x800C44AC: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C44B0:
    // 0x800C44B0: jal         0x800C4078
    // 0x800C44B4: nop

    func_800C4078(rdram, ctx);
        goto after_20;
    // 0x800C44B4: nop

    after_20:
    // 0x800C44B8: addiu       $a0, $zero, 0x1D
    ctx->r4 = ADD32(0, 0X1D);
    // 0x800C44BC: jal         0x800C15C8
    // 0x800C44C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_21;
    // 0x800C44C0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_21:
    // 0x800C44C4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C44C8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C44CC:
    // 0x800C44CC: slti        $at, $v1, 0x191
    ctx->r1 = SIGNED(ctx->r3) < 0X191 ? 1 : 0;
L_800C44D0:
    // 0x800C44D0: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C44D4: slti        $at, $v1, 0x24E
        ctx->r1 = SIGNED(ctx->r3) < 0X24E ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C44D4: slti        $at, $v1, 0x24E
    ctx->r1 = SIGNED(ctx->r3) < 0X24E ? 1 : 0;
    // 0x800C44D8: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C44DC: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_7;
    // 0x800C44DC: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_7:
    // 0x800C44E0: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C44E4: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C44E8: lwc1        $f4, -0x3A60($at)
    ctx->f4.u32l = MEM_W(ctx->r1, -0X3A60);
    // 0x800C44EC: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C44F0: lui         $at, 0x433E
    ctx->r1 = S32(0X433E << 16);
    // 0x800C44F4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C44F8: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C44FC: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C4500: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C4504: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4508: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C450C: jal         0x800C538C
    // 0x800C4510: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_22;
    // 0x800C4510: nop

    after_22:
    // 0x800C4514: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x800C4518: lw          $t9, 0x7E14($t9)
    ctx->r25 = MEM_W(ctx->r25, 0X7E14);
    // 0x800C451C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C4520: lwc1        $f6, -0x3A5C($at)
    ctx->f6.u32l = MEM_W(ctx->r1, -0X3A5C);
    // 0x800C4524: mtc1        $t9, $f4
    ctx->f4.u32l = ctx->r25;
    // 0x800C4528: lui         $at, 0x433E
    ctx->r1 = S32(0X433E << 16);
    // 0x800C452C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4530: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C4534: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4538: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C453C: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C4540: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4544: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4548: jal         0x800C538C
    // 0x800C454C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_23;
    // 0x800C454C: nop

    after_23:
    // 0x800C4550: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4554: b           L_800C4868
    // 0x800C4558: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4558: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C455C:
    // 0x800C455C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4560: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C4564: addiu       $at, $zero, 0x1E0
    ctx->r1 = ADD32(0, 0X1E0);
    // 0x800C4568: beq         $v1, $at, L_800C4590
    if (ctx->r3 == ctx->r1) {
        // 0x800C456C: addiu       $at, $zero, 0x208
        ctx->r1 = ADD32(0, 0X208);
            goto L_800C4590;
    }
    // 0x800C456C: addiu       $at, $zero, 0x208
    ctx->r1 = ADD32(0, 0X208);
    // 0x800C4570: beq         $v1, $at, L_800C45A4
    if (ctx->r3 == ctx->r1) {
        // 0x800C4574: addiu       $at, $zero, 0x244
        ctx->r1 = ADD32(0, 0X244);
            goto L_800C45A4;
    }
    // 0x800C4574: addiu       $at, $zero, 0x244
    ctx->r1 = ADD32(0, 0X244);
    // 0x800C4578: beq         $v1, $at, L_800C45B8
    if (ctx->r3 == ctx->r1) {
        // 0x800C457C: addiu       $at, $zero, 0x280
        ctx->r1 = ADD32(0, 0X280);
            goto L_800C45B8;
    }
    // 0x800C457C: addiu       $at, $zero, 0x280
    ctx->r1 = ADD32(0, 0X280);
    // 0x800C4580: beql        $v1, $at, L_800C45D8
    if (ctx->r3 == ctx->r1) {
        // 0x800C4584: slti        $at, $v1, 0x1B9
        ctx->r1 = SIGNED(ctx->r3) < 0X1B9 ? 1 : 0;
            goto L_800C45D8;
    }
    goto skip_8;
    // 0x800C4584: slti        $at, $v1, 0x1B9
    ctx->r1 = SIGNED(ctx->r3) < 0X1B9 ? 1 : 0;
    skip_8:
    // 0x800C4588: b           L_800C45D8
    // 0x800C458C: slti        $at, $v1, 0x1B9
    ctx->r1 = SIGNED(ctx->r3) < 0X1B9 ? 1 : 0;
        goto L_800C45D8;
    // 0x800C458C: slti        $at, $v1, 0x1B9
    ctx->r1 = SIGNED(ctx->r3) < 0X1B9 ? 1 : 0;
L_800C4590:
    // 0x800C4590: jal         0x800C1650
    // 0x800C4594: addiu       $a0, $zero, 0x3E8
    ctx->r4 = ADD32(0, 0X3E8);
    func_800C1650(rdram, ctx);
        goto after_24;
    // 0x800C4594: addiu       $a0, $zero, 0x3E8
    ctx->r4 = ADD32(0, 0X3E8);
    after_24:
    // 0x800C4598: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C459C: b           L_800C45D4
    // 0x800C45A0: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C45D4;
    // 0x800C45A0: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C45A4:
    // 0x800C45A4: jal         0x800C3500
    // 0x800C45A8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    func_800C3500(rdram, ctx);
        goto after_25;
    // 0x800C45A8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    after_25:
    // 0x800C45AC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C45B0: b           L_800C45D4
    // 0x800C45B4: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C45D4;
    // 0x800C45B4: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C45B8:
    // 0x800C45B8: jal         0x800C4078
    // 0x800C45BC: nop

    func_800C4078(rdram, ctx);
        goto after_26;
    // 0x800C45BC: nop

    after_26:
    // 0x800C45C0: addiu       $a0, $zero, 0x1E
    ctx->r4 = ADD32(0, 0X1E);
    // 0x800C45C4: jal         0x800C15C8
    // 0x800C45C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_27;
    // 0x800C45C8: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_27:
    // 0x800C45CC: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C45D0: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C45D4:
    // 0x800C45D4: slti        $at, $v1, 0x1B9
    ctx->r1 = SIGNED(ctx->r3) < 0X1B9 ? 1 : 0;
L_800C45D8:
    // 0x800C45D8: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C45DC: slti        $at, $v1, 0x244
        ctx->r1 = SIGNED(ctx->r3) < 0X244 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C45DC: slti        $at, $v1, 0x244
    ctx->r1 = SIGNED(ctx->r3) < 0X244 ? 1 : 0;
    // 0x800C45E0: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C45E4: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_9;
    // 0x800C45E4: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_9:
    // 0x800C45E8: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C45EC: lui         $at, 0x4411
    ctx->r1 = S32(0X4411 << 16);
    // 0x800C45F0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C45F4: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C45F8: lui         $at, 0x430C
    ctx->r1 = S32(0X430C << 16);
    // 0x800C45FC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4600: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4604: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C4608: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C460C: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4610: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4614: jal         0x800C538C
    // 0x800C4618: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_28;
    // 0x800C4618: nop

    after_28:
    // 0x800C461C: lui         $t0, 0x801D
    ctx->r8 = S32(0X801D << 16);
    // 0x800C4620: lw          $t0, 0x7E14($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X7E14);
    // 0x800C4624: lui         $at, 0x4411
    ctx->r1 = S32(0X4411 << 16);
    // 0x800C4628: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C462C: mtc1        $t0, $f4
    ctx->f4.u32l = ctx->r8;
    // 0x800C4630: lui         $at, 0x430C
    ctx->r1 = S32(0X430C << 16);
    // 0x800C4634: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4638: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C463C: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4640: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C4644: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C4648: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C464C: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4650: jal         0x800C538C
    // 0x800C4654: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_29;
    // 0x800C4654: nop

    after_29:
    // 0x800C4658: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C465C: b           L_800C4868
    // 0x800C4660: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4660: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4664:
    // 0x800C4664: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C4668: addiu       $at, $zero, 0x208
    ctx->r1 = ADD32(0, 0X208);
    // 0x800C466C: beq         $v1, $at, L_800C4694
    if (ctx->r3 == ctx->r1) {
        // 0x800C4670: addiu       $at, $zero, 0x226
        ctx->r1 = ADD32(0, 0X226);
            goto L_800C4694;
    }
    // 0x800C4670: addiu       $at, $zero, 0x226
    ctx->r1 = ADD32(0, 0X226);
    // 0x800C4674: beq         $v1, $at, L_800C46A8
    if (ctx->r3 == ctx->r1) {
        // 0x800C4678: addiu       $at, $zero, 0x258
        ctx->r1 = ADD32(0, 0X258);
            goto L_800C46A8;
    }
    // 0x800C4678: addiu       $at, $zero, 0x258
    ctx->r1 = ADD32(0, 0X258);
    // 0x800C467C: beq         $v1, $at, L_800C46BC
    if (ctx->r3 == ctx->r1) {
        // 0x800C4680: addiu       $at, $zero, 0x26C
        ctx->r1 = ADD32(0, 0X26C);
            goto L_800C46BC;
    }
    // 0x800C4680: addiu       $at, $zero, 0x26C
    ctx->r1 = ADD32(0, 0X26C);
    // 0x800C4684: beql        $v1, $at, L_800C46DC
    if (ctx->r3 == ctx->r1) {
        // 0x800C4688: slti        $at, $v1, 0x1E1
        ctx->r1 = SIGNED(ctx->r3) < 0X1E1 ? 1 : 0;
            goto L_800C46DC;
    }
    goto skip_10;
    // 0x800C4688: slti        $at, $v1, 0x1E1
    ctx->r1 = SIGNED(ctx->r3) < 0X1E1 ? 1 : 0;
    skip_10:
    // 0x800C468C: b           L_800C46DC
    // 0x800C4690: slti        $at, $v1, 0x1E1
    ctx->r1 = SIGNED(ctx->r3) < 0X1E1 ? 1 : 0;
        goto L_800C46DC;
    // 0x800C4690: slti        $at, $v1, 0x1E1
    ctx->r1 = SIGNED(ctx->r3) < 0X1E1 ? 1 : 0;
L_800C4694:
    // 0x800C4694: jal         0x800C1650
    // 0x800C4698: addiu       $a0, $zero, 0x320
    ctx->r4 = ADD32(0, 0X320);
    func_800C1650(rdram, ctx);
        goto after_30;
    // 0x800C4698: addiu       $a0, $zero, 0x320
    ctx->r4 = ADD32(0, 0X320);
    after_30:
    // 0x800C469C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C46A0: b           L_800C46D8
    // 0x800C46A4: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C46D8;
    // 0x800C46A4: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C46A8:
    // 0x800C46A8: jal         0x800C3500
    // 0x800C46AC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C3500(rdram, ctx);
        goto after_31;
    // 0x800C46AC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_31:
    // 0x800C46B0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C46B4: b           L_800C46D8
    // 0x800C46B8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C46D8;
    // 0x800C46B8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C46BC:
    // 0x800C46BC: jal         0x800C4078
    // 0x800C46C0: nop

    func_800C4078(rdram, ctx);
        goto after_32;
    // 0x800C46C0: nop

    after_32:
    // 0x800C46C4: addiu       $a0, $zero, 0x1F
    ctx->r4 = ADD32(0, 0X1F);
    // 0x800C46C8: jal         0x800C15C8
    // 0x800C46CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_33;
    // 0x800C46CC: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_33:
    // 0x800C46D0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C46D4: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C46D8:
    // 0x800C46D8: slti        $at, $v1, 0x1E1
    ctx->r1 = SIGNED(ctx->r3) < 0X1E1 ? 1 : 0;
L_800C46DC:
    // 0x800C46DC: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C46E0: slti        $at, $v1, 0x258
        ctx->r1 = SIGNED(ctx->r3) < 0X258 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C46E0: slti        $at, $v1, 0x258
    ctx->r1 = SIGNED(ctx->r3) < 0X258 ? 1 : 0;
    // 0x800C46E4: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C46E8: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_11;
    // 0x800C46E8: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_11:
    // 0x800C46EC: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C46F0: lui         $at, 0x4416
    ctx->r1 = S32(0X4416 << 16);
    // 0x800C46F4: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C46F8: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C46FC: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C4700: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4704: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4708: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C470C: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C4710: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4714: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4718: jal         0x800C538C
    // 0x800C471C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_34;
    // 0x800C471C: nop

    after_34:
    // 0x800C4720: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x800C4724: lw          $t1, 0x7E14($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X7E14);
    // 0x800C4728: lui         $at, 0x4416
    ctx->r1 = S32(0X4416 << 16);
    // 0x800C472C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C4730: mtc1        $t1, $f4
    ctx->f4.u32l = ctx->r9;
    // 0x800C4734: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C4738: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C473C: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C4740: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4744: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C4748: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C474C: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4750: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4754: jal         0x800C538C
    // 0x800C4758: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_35;
    // 0x800C4758: nop

    after_35:
    // 0x800C475C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4760: b           L_800C4868
    // 0x800C4764: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C4868;
    // 0x800C4764: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4768:
    // 0x800C4768: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
    // 0x800C476C: addiu       $at, $zero, 0x190
    ctx->r1 = ADD32(0, 0X190);
    // 0x800C4770: beq         $v1, $at, L_800C4798
    if (ctx->r3 == ctx->r1) {
        // 0x800C4774: addiu       $at, $zero, 0x1E0
        ctx->r1 = ADD32(0, 0X1E0);
            goto L_800C4798;
    }
    // 0x800C4774: addiu       $at, $zero, 0x1E0
    ctx->r1 = ADD32(0, 0X1E0);
    // 0x800C4778: beq         $v1, $at, L_800C47AC
    if (ctx->r3 == ctx->r1) {
        // 0x800C477C: addiu       $at, $zero, 0x208
        ctx->r1 = ADD32(0, 0X208);
            goto L_800C47AC;
    }
    // 0x800C477C: addiu       $at, $zero, 0x208
    ctx->r1 = ADD32(0, 0X208);
    // 0x800C4780: beq         $v1, $at, L_800C47C0
    if (ctx->r3 == ctx->r1) {
        // 0x800C4784: addiu       $at, $zero, 0x26C
        ctx->r1 = ADD32(0, 0X26C);
            goto L_800C47C0;
    }
    // 0x800C4784: addiu       $at, $zero, 0x26C
    ctx->r1 = ADD32(0, 0X26C);
    // 0x800C4788: beql        $v1, $at, L_800C47E0
    if (ctx->r3 == ctx->r1) {
        // 0x800C478C: slti        $at, $v1, 0x169
        ctx->r1 = SIGNED(ctx->r3) < 0X169 ? 1 : 0;
            goto L_800C47E0;
    }
    goto skip_12;
    // 0x800C478C: slti        $at, $v1, 0x169
    ctx->r1 = SIGNED(ctx->r3) < 0X169 ? 1 : 0;
    skip_12:
    // 0x800C4790: b           L_800C47E0
    // 0x800C4794: slti        $at, $v1, 0x169
    ctx->r1 = SIGNED(ctx->r3) < 0X169 ? 1 : 0;
        goto L_800C47E0;
    // 0x800C4794: slti        $at, $v1, 0x169
    ctx->r1 = SIGNED(ctx->r3) < 0X169 ? 1 : 0;
L_800C4798:
    // 0x800C4798: jal         0x800C1650
    // 0x800C479C: addiu       $a0, $zero, 0x320
    ctx->r4 = ADD32(0, 0X320);
    func_800C1650(rdram, ctx);
        goto after_36;
    // 0x800C479C: addiu       $a0, $zero, 0x320
    ctx->r4 = ADD32(0, 0X320);
    after_36:
    // 0x800C47A0: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C47A4: b           L_800C47DC
    // 0x800C47A8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C47DC;
    // 0x800C47A8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C47AC:
    // 0x800C47AC: jal         0x800C3500
    // 0x800C47B0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    func_800C3500(rdram, ctx);
        goto after_37;
    // 0x800C47B0: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    after_37:
    // 0x800C47B4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C47B8: b           L_800C47DC
    // 0x800C47BC: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
        goto L_800C47DC;
    // 0x800C47BC: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C47C0:
    // 0x800C47C0: jal         0x800C4078
    // 0x800C47C4: nop

    func_800C4078(rdram, ctx);
        goto after_38;
    // 0x800C47C4: nop

    after_38:
    // 0x800C47C8: addiu       $a0, $zero, 0x20
    ctx->r4 = ADD32(0, 0X20);
    // 0x800C47CC: jal         0x800C15C8
    // 0x800C47D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    func_800C15C8(rdram, ctx);
        goto after_39;
    // 0x800C47D0: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_39:
    // 0x800C47D4: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C47D8: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C47DC:
    // 0x800C47DC: slti        $at, $v1, 0x169
    ctx->r1 = SIGNED(ctx->r3) < 0X169 ? 1 : 0;
L_800C47E0:
    // 0x800C47E0: bne         $at, $zero, L_800C4868
    if (ctx->r1 != 0) {
        // 0x800C47E4: slti        $at, $v1, 0x1E0
        ctx->r1 = SIGNED(ctx->r3) < 0X1E0 ? 1 : 0;
            goto L_800C4868;
    }
    // 0x800C47E4: slti        $at, $v1, 0x1E0
    ctx->r1 = SIGNED(ctx->r3) < 0X1E0 ? 1 : 0;
    // 0x800C47E8: beql        $at, $zero, L_800C486C
    if (ctx->r1 == 0) {
        // 0x800C47EC: addiu       $at, $zero, 0x14
        ctx->r1 = ADD32(0, 0X14);
            goto L_800C486C;
    }
    goto skip_13;
    // 0x800C47EC: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
    skip_13:
    // 0x800C47F0: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x800C47F4: lui         $at, 0x43F0
    ctx->r1 = S32(0X43F0 << 16);
    // 0x800C47F8: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x800C47FC: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C4800: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C4804: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4808: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C480C: ori         $a0, $a0, 0xB00
    ctx->r4 = ctx->r4 | 0XB00;
    // 0x800C4810: sub.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl - ctx->f8.fl;
    // 0x800C4814: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4818: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C481C: jal         0x800C538C
    // 0x800C4820: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_40;
    // 0x800C4820: nop

    after_40:
    // 0x800C4824: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x800C4828: lw          $t2, 0x7E14($t2)
    ctx->r10 = MEM_W(ctx->r10, 0X7E14);
    // 0x800C482C: lui         $at, 0x43F0
    ctx->r1 = S32(0X43F0 << 16);
    // 0x800C4830: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x800C4834: mtc1        $t2, $f4
    ctx->f4.u32l = ctx->r10;
    // 0x800C4838: lui         $at, 0x42F0
    ctx->r1 = S32(0X42F0 << 16);
    // 0x800C483C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800C4840: cvt.s.w     $f8, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    ctx->f8.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800C4844: lui         $a0, 0x100
    ctx->r4 = S32(0X100 << 16);
    // 0x800C4848: ori         $a0, $a0, 0xA00
    ctx->r4 = ctx->r4 | 0XA00;
    // 0x800C484C: sub.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x800C4850: div.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = DIV_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800C4854: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x800C4858: jal         0x800C538C
    // 0x800C485C: nop

    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_41;
    // 0x800C485C: nop

    after_41:
    // 0x800C4860: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4864: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4868:
    // 0x800C4868: addiu       $at, $zero, 0x14
    ctx->r1 = ADD32(0, 0X14);
L_800C486C:
    // 0x800C486C: bne         $v1, $at, L_800C4884
    if (ctx->r3 != ctx->r1) {
        // 0x800C4870: addiu       $a0, $zero, 0x1C
        ctx->r4 = ADD32(0, 0X1C);
            goto L_800C4884;
    }
    // 0x800C4870: addiu       $a0, $zero, 0x1C
    ctx->r4 = ADD32(0, 0X1C);
    // 0x800C4874: jal         0x800C1500
    // 0x800C4878: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    func_800C1500(rdram, ctx);
        goto after_42;
    // 0x800C4878: addiu       $a1, $zero, 0x14
    ctx->r5 = ADD32(0, 0X14);
    after_42:
    // 0x800C487C: lui         $v1, 0x801D
    ctx->r3 = S32(0X801D << 16);
    // 0x800C4880: lw          $v1, 0x7E14($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X7E14);
L_800C4884:
    // 0x800C4884: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C4888: addiu       $t3, $v1, 0x1
    ctx->r11 = ADD32(ctx->r3, 0X1);
    // 0x800C488C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4890: sw          $t3, 0x7E14($at)
    MEM_W(0X7E14, ctx->r1) = ctx->r11;
    // 0x800C4894: jr          $ra
    // 0x800C4898: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    return;
    // 0x800C4898: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
;}
RECOMP_FUNC void func_800C489C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C489C: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C48A0: lw          $v0, 0x7DD4($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DD4);
    // 0x800C48A4: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C48A8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C48AC: beq         $v0, $zero, L_800C48CC
    if (ctx->r2 == 0) {
        // 0x800C48B0: addiu       $v1, $zero, 0x1
        ctx->r3 = ADD32(0, 0X1);
            goto L_800C48CC;
    }
    // 0x800C48B0: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C48B4: beq         $v0, $v1, L_800C4928
    if (ctx->r2 == ctx->r3) {
        // 0x800C48B8: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C4928;
    }
    // 0x800C48B8: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C48BC: beq         $v0, $at, L_800C4980
    if (ctx->r2 == ctx->r1) {
        // 0x800C48C0: nop
    
            goto L_800C4980;
    }
    // 0x800C48C0: nop

    // 0x800C48C4: b           L_800C4980
    // 0x800C48C8: nop

        goto L_800C4980;
    // 0x800C48C8: nop

L_800C48CC:
    // 0x800C48CC: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C48D0: lw          $v0, 0x7DC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC8);
    // 0x800C48D4: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C48D8: beq         $v0, $zero, L_800C48F8
    if (ctx->r2 == 0) {
        // 0x800C48DC: nop
    
            goto L_800C48F8;
    }
    // 0x800C48DC: nop

    // 0x800C48E0: beq         $v0, $v1, L_800C4908
    if (ctx->r2 == ctx->r3) {
        // 0x800C48E4: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C4908;
    }
    // 0x800C48E4: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C48E8: beq         $v0, $at, L_800C4918
    if (ctx->r2 == ctx->r1) {
        // 0x800C48EC: nop
    
            goto L_800C4918;
    }
    // 0x800C48EC: nop

    // 0x800C48F0: b           L_800C498C
    // 0x800C48F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C48F4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C48F8:
    // 0x800C48F8: jal         0x800C3500
    // 0x800C48FC: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    func_800C3500(rdram, ctx);
        goto after_0;
    // 0x800C48FC: addiu       $a0, $zero, 0x5
    ctx->r4 = ADD32(0, 0X5);
    after_0:
    // 0x800C4900: b           L_800C498C
    // 0x800C4904: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C4904: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4908:
    // 0x800C4908: jal         0x800C3500
    // 0x800C490C: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C3500(rdram, ctx);
        goto after_1;
    // 0x800C490C: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_1:
    // 0x800C4910: b           L_800C498C
    // 0x800C4914: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C4914: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4918:
    // 0x800C4918: jal         0x800C3500
    // 0x800C491C: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C3500(rdram, ctx);
        goto after_2;
    // 0x800C491C: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_2:
    // 0x800C4920: b           L_800C498C
    // 0x800C4924: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C4924: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4928:
    // 0x800C4928: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C492C: lw          $v0, 0x7DC8($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC8);
    // 0x800C4930: beq         $v0, $zero, L_800C4950
    if (ctx->r2 == 0) {
        // 0x800C4934: nop
    
            goto L_800C4950;
    }
    // 0x800C4934: nop

    // 0x800C4938: beq         $v0, $v1, L_800C4960
    if (ctx->r2 == ctx->r3) {
        // 0x800C493C: addiu       $at, $zero, 0x2
        ctx->r1 = ADD32(0, 0X2);
            goto L_800C4960;
    }
    // 0x800C493C: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x800C4940: beq         $v0, $at, L_800C4970
    if (ctx->r2 == ctx->r1) {
        // 0x800C4944: nop
    
            goto L_800C4970;
    }
    // 0x800C4944: nop

    // 0x800C4948: b           L_800C498C
    // 0x800C494C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C494C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4950:
    // 0x800C4950: jal         0x800C3500
    // 0x800C4954: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    func_800C3500(rdram, ctx);
        goto after_3;
    // 0x800C4954: addiu       $a0, $zero, 0x4
    ctx->r4 = ADD32(0, 0X4);
    after_3:
    // 0x800C4958: b           L_800C498C
    // 0x800C495C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C495C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4960:
    // 0x800C4960: jal         0x800C3500
    // 0x800C4964: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    func_800C3500(rdram, ctx);
        goto after_4;
    // 0x800C4964: addiu       $a0, $zero, 0x6
    ctx->r4 = ADD32(0, 0X6);
    after_4:
    // 0x800C4968: b           L_800C498C
    // 0x800C496C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C496C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4970:
    // 0x800C4970: jal         0x800C3500
    // 0x800C4974: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C3500(rdram, ctx);
        goto after_5;
    // 0x800C4974: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_5:
    // 0x800C4978: b           L_800C498C
    // 0x800C497C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C498C;
    // 0x800C497C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4980:
    // 0x800C4980: jal         0x800C3500
    // 0x800C4984: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    func_800C3500(rdram, ctx);
        goto after_6;
    // 0x800C4984: addiu       $a0, $zero, 0x7
    ctx->r4 = ADD32(0, 0X7);
    after_6:
    // 0x800C4988: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C498C:
    // 0x800C498C: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C4990: jr          $ra
    // 0x800C4994: nop

    return;
    // 0x800C4994: nop

;}
RECOMP_FUNC void func_800C4998(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C4998: addiu       $t6, $zero, 0x7
    ctx->r14 = ADD32(0, 0X7);
    // 0x800C499C: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C49A0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C49A4: sb          $t6, 0x7C94($at)
    MEM_B(0X7C94, ctx->r1) = ctx->r14;
    // 0x800C49A8: addu        $t8, $t8, $a1
    ctx->r24 = ADD32(ctx->r24, ctx->r5);
    // 0x800C49AC: lb          $t8, 0x7CF8($t8)
    ctx->r24 = MEM_B(ctx->r24, 0X7CF8);
    // 0x800C49B0: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C49B4: addiu       $t7, $zero, 0x1
    ctx->r15 = ADD32(0, 0X1);
    // 0x800C49B8: lui         $t9, 0x800E
    ctx->r25 = S32(0X800E << 16);
    // 0x800C49BC: sw          $t7, 0x7CB8($at)
    MEM_W(0X7CB8, ctx->r1) = ctx->r15;
    // 0x800C49C0: addu        $t9, $t9, $a1
    ctx->r25 = ADD32(ctx->r25, ctx->r5);
    // 0x800C49C4: lb          $t9, 0x7D04($t9)
    ctx->r25 = MEM_B(ctx->r25, 0X7D04);
    // 0x800C49C8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C49CC: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800C49D0: sw          $t8, 0x7E08($at)
    MEM_W(0X7E08, ctx->r1) = ctx->r24;
    // 0x800C49D4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C49D8: addiu       $t0, $t0, 0x7D10
    ctx->r8 = ADD32(ctx->r8, 0X7D10);
    // 0x800C49DC: addu        $v0, $a1, $t0
    ctx->r2 = ADD32(ctx->r5, ctx->r8);
    // 0x800C49E0: sw          $t9, 0x7E0C($at)
    MEM_W(0X7E0C, ctx->r1) = ctx->r25;
    // 0x800C49E4: lb          $t1, 0x0($v0)
    ctx->r9 = MEM_B(ctx->r2, 0X0);
    // 0x800C49E8: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C49EC: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x800C49F0: sw          $t1, 0x7E10($at)
    MEM_W(0X7E10, ctx->r1) = ctx->r9;
    // 0x800C49F4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C49F8: sw          $a0, 0x7DC0($at)
    MEM_W(0X7DC0, ctx->r1) = ctx->r4;
    // 0x800C49FC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C4A00: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4A04: sw          $a1, 0x7DC4($at)
    MEM_W(0X7DC4, ctx->r1) = ctx->r5;
    // 0x800C4A08: addiu       $a0, $zero, 0xF0
    ctx->r4 = ADD32(0, 0XF0);
    // 0x800C4A0C: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x800C4A10: jal         0x800C1650
    // 0x800C4A14: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    func_800C1650(rdram, ctx);
        goto after_0;
    // 0x800C4A14: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    after_0:
    // 0x800C4A18: jal         0x800C1488
    // 0x800C4A1C: nop

    func_800C1488(rdram, ctx);
        goto after_1;
    // 0x800C4A1C: nop

    after_1:
    // 0x800C4A20: jal         0x800C13AC
    // 0x800C4A24: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    func_800C13AC(rdram, ctx);
        goto after_2;
    // 0x800C4A24: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    after_2:
    // 0x800C4A28: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x800C4A2C: lw          $v0, 0x7DC0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X7DC0);
    // 0x800C4A30: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C4A34: addiu       $t2, $zero, 0x8
    ctx->r10 = ADD32(0, 0X8);
    // 0x800C4A38: beq         $v0, $zero, L_800C4A60
    if (ctx->r2 == 0) {
        // 0x800C4A3C: lui         $a0, 0x300
        ctx->r4 = S32(0X300 << 16);
            goto L_800C4A60;
    }
    // 0x800C4A3C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4A40: addiu       $v1, $zero, 0x1
    ctx->r3 = ADD32(0, 0X1);
    // 0x800C4A44: beq         $v0, $v1, L_800C4B3C
    if (ctx->r2 == ctx->r3) {
        // 0x800C4A48: lui         $at, 0x800E
        ctx->r1 = S32(0X800E << 16);
            goto L_800C4B3C;
    }
    // 0x800C4A48: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C4A4C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x800C4A50: beq         $v0, $at, L_800C4BCC
    if (ctx->r2 == ctx->r1) {
        // 0x800C4A54: addiu       $t6, $zero, 0x4
        ctx->r14 = ADD32(0, 0X4);
            goto L_800C4BCC;
    }
    // 0x800C4A54: addiu       $t6, $zero, 0x4
    ctx->r14 = ADD32(0, 0X4);
    // 0x800C4A58: b           L_800C4C34
    // 0x800C4A5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C4C34;
    // 0x800C4A5C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4A60:
    // 0x800C4A60: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C4A64: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4A68: sb          $t2, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r10;
    // 0x800C4A6C: jal         0x800C53D4
    // 0x800C4A70: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_3;
    // 0x800C4A70: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_3:
    // 0x800C4A74: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4A78: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C4A7C: jal         0x800C53D4
    // 0x800C4A80: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_4;
    // 0x800C4A80: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_4:
    // 0x800C4A84: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4A88: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C4A8C: jal         0x800C53D4
    // 0x800C4A90: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_5;
    // 0x800C4A90: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_5:
    // 0x800C4A94: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4A98: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C4A9C: jal         0x800C53D4
    // 0x800C4AA0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_6;
    // 0x800C4AA0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_6:
    // 0x800C4AA4: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4AA8: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C4AAC: jal         0x800C53D4
    // 0x800C4AB0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_7;
    // 0x800C4AB0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_7:
    // 0x800C4AB4: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4AB8: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C4ABC: jal         0x800C53D4
    // 0x800C4AC0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_8;
    // 0x800C4AC0: addiu       $a1, $zero, 0x40
    ctx->r5 = ADD32(0, 0X40);
    after_8:
    // 0x800C4AC4: lw          $t3, 0x2C($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X2C);
    // 0x800C4AC8: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4ACC: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C4AD0: bne         $t3, $zero, L_800C4B00
    if (ctx->r11 != 0) {
        // 0x800C4AD4: nop
    
            goto L_800C4B00;
    }
    // 0x800C4AD4: nop

    // 0x800C4AD8: jal         0x800C538C
    // 0x800C4ADC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_9;
    // 0x800C4ADC: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_9:
    // 0x800C4AE0: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4AE4: lui         $a1, 0x3F49
    ctx->r5 = S32(0X3F49 << 16);
    // 0x800C4AE8: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    // 0x800C4AEC: jal         0x800C538C
    // 0x800C4AF0: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_10;
    // 0x800C4AF0: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    after_10:
    // 0x800C4AF4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4AF8: b           L_800C4C30
    // 0x800C4AFC: sb          $zero, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = 0;
        goto L_800C4C30;
    // 0x800C4AFC: sb          $zero, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = 0;
L_800C4B00:
    // 0x800C4B00: jal         0x800C1EB8
    // 0x800C4B04: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    func_800C1EB8(rdram, ctx);
        goto after_11;
    // 0x800C4B04: addiu       $a0, $zero, 0x10
    ctx->r4 = ADD32(0, 0X10);
    after_11:
    // 0x800C4B08: jal         0x800BFB50
    // 0x800C4B0C: nop

    func_800BFB50(rdram, ctx);
        goto after_12;
    // 0x800C4B0C: nop

    after_12:
    // 0x800C4B10: lw          $t4, 0x2C($sp)
    ctx->r12 = MEM_W(ctx->r29, 0X2C);
    // 0x800C4B14: addiu       $at, $zero, 0x7
    ctx->r1 = ADD32(0, 0X7);
    // 0x800C4B18: lw          $a0, 0x2C($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X2C);
    // 0x800C4B1C: bne         $t4, $at, L_800C4B2C
    if (ctx->r12 != ctx->r1) {
        // 0x800C4B20: nop
    
            goto L_800C4B2C;
    }
    // 0x800C4B20: nop

    // 0x800C4B24: b           L_800C4B2C
    // 0x800C4B28: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
        goto L_800C4B2C;
    // 0x800C4B28: addiu       $a0, $zero, 0x9
    ctx->r4 = ADD32(0, 0X9);
L_800C4B2C:
    // 0x800C4B2C: jal         0x800C3524
    // 0x800C4B30: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    func_800C3524(rdram, ctx);
        goto after_13;
    // 0x800C4B30: addiu       $a1, $zero, 0xF
    ctx->r5 = ADD32(0, 0XF);
    after_13:
    // 0x800C4B34: b           L_800C4C34
    // 0x800C4B38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C4C34;
    // 0x800C4B38: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4B3C:
    // 0x800C4B3C: sb          $v1, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = ctx->r3;
    // 0x800C4B40: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4B44: addiu       $t5, $zero, 0x4
    ctx->r13 = ADD32(0, 0X4);
    // 0x800C4B48: sb          $t5, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r13;
    // 0x800C4B4C: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B50: jal         0x800C53D4
    // 0x800C4B54: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_14;
    // 0x800C4B54: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_14:
    // 0x800C4B58: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B5C: ori         $a0, $a0, 0x100
    ctx->r4 = ctx->r4 | 0X100;
    // 0x800C4B60: jal         0x800C53D4
    // 0x800C4B64: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_15;
    // 0x800C4B64: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_15:
    // 0x800C4B68: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B6C: ori         $a0, $a0, 0x200
    ctx->r4 = ctx->r4 | 0X200;
    // 0x800C4B70: jal         0x800C53D4
    // 0x800C4B74: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_16;
    // 0x800C4B74: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    after_16:
    // 0x800C4B78: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B7C: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C4B80: jal         0x800C53D4
    // 0x800C4B84: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_17;
    // 0x800C4B84: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_17:
    // 0x800C4B88: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B8C: ori         $a0, $a0, 0x400
    ctx->r4 = ctx->r4 | 0X400;
    // 0x800C4B90: jal         0x800C53D4
    // 0x800C4B94: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_18;
    // 0x800C4B94: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_18:
    // 0x800C4B98: lui         $a0, 0x300
    ctx->r4 = S32(0X300 << 16);
    // 0x800C4B9C: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C4BA0: jal         0x800C53D4
    // 0x800C4BA4: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    AudioThread_QueueCmdS8(rdram, ctx);
        goto after_19;
    // 0x800C4BA4: addiu       $a1, $zero, 0x7F
    ctx->r5 = ADD32(0, 0X7F);
    after_19:
    // 0x800C4BA8: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4BAC: lui         $a1, 0x3EF1
    ctx->r5 = S32(0X3EF1 << 16);
    // 0x800C4BB0: ori         $a1, $a1, 0xE3C8
    ctx->r5 = ctx->r5 | 0XE3C8;
    // 0x800C4BB4: jal         0x800C538C
    // 0x800C4BB8: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_20;
    // 0x800C4BB8: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    after_20:
    // 0x800C4BBC: jal         0x800C1EB8
    // 0x800C4BC0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_21;
    // 0x800C4BC0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_21:
    // 0x800C4BC4: b           L_800C4C34
    // 0x800C4BC8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C4C34;
    // 0x800C4BC8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4BCC:
    // 0x800C4BCC: lui         $at, 0x800E
    ctx->r1 = S32(0X800E << 16);
    // 0x800C4BD0: sb          $zero, 0x7C90($at)
    MEM_B(0X7C90, ctx->r1) = 0;
    // 0x800C4BD4: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800C4BD8: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4BDC: sb          $t6, 0x7E05($at)
    MEM_B(0X7E05, ctx->r1) = ctx->r14;
    // 0x800C4BE0: ori         $a0, $a0, 0x300
    ctx->r4 = ctx->r4 | 0X300;
    // 0x800C4BE4: jal         0x800C538C
    // 0x800C4BE8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_22;
    // 0x800C4BE8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_22:
    // 0x800C4BEC: lw          $t7, 0x1C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X1C);
    // 0x800C4BF0: lui         $t8, 0x800E
    ctx->r24 = S32(0X800E << 16);
    // 0x800C4BF4: addiu       $t8, $t8, 0x7D10
    ctx->r24 = ADD32(ctx->r24, 0X7D10);
    // 0x800C4BF8: bne         $t7, $t8, L_800C4C1C
    if (ctx->r15 != ctx->r24) {
        // 0x800C4BFC: lui         $a0, 0x200
        ctx->r4 = S32(0X200 << 16);
            goto L_800C4C1C;
    }
    // 0x800C4BFC: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4C00: lui         $a0, 0x200
    ctx->r4 = S32(0X200 << 16);
    // 0x800C4C04: lui         $a1, 0x3F49
    ctx->r5 = S32(0X3F49 << 16);
    // 0x800C4C08: ori         $a1, $a1, 0x9326
    ctx->r5 = ctx->r5 | 0X9326;
    // 0x800C4C0C: jal         0x800C538C
    // 0x800C4C10: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_23;
    // 0x800C4C10: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    after_23:
    // 0x800C4C14: b           L_800C4C28
    // 0x800C4C18: nop

        goto L_800C4C28;
    // 0x800C4C18: nop

L_800C4C1C:
    // 0x800C4C1C: ori         $a0, $a0, 0x500
    ctx->r4 = ctx->r4 | 0X500;
    // 0x800C4C20: jal         0x800C538C
    // 0x800C4C24: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    AudioThread_QueueCmdF32(rdram, ctx);
        goto after_24;
    // 0x800C4C24: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_24:
L_800C4C28:
    // 0x800C4C28: jal         0x800C1EB8
    // 0x800C4C2C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    func_800C1EB8(rdram, ctx);
        goto after_25;
    // 0x800C4C2C: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    after_25:
L_800C4C30:
    // 0x800C4C30: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C4C34:
    // 0x800C4C34: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x800C4C38: jr          $ra
    // 0x800C4C3C: nop

    return;
    // 0x800C4C3C: nop

;}
RECOMP_FUNC void AudioThread_CreateTask(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C4C40: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C4C44: addiu       $v1, $v1, 0x5550
    ctx->r3 = ADD32(ctx->r3, 0X5550);
    // 0x800C4C48: lw          $v0, 0x0($v1)
    ctx->r2 = MEM_W(ctx->r3, 0X0);
    // 0x800C4C4C: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C4C50: addiu       $sp, $sp, -0x58
    ctx->r29 = ADD32(ctx->r29, -0X58);
    // 0x800C4C54: addiu       $t6, $v0, 0x1
    ctx->r14 = ADD32(ctx->r2, 0X1);
    // 0x800C4C58: sw          $t6, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r14;
    // 0x800C4C5C: lw          $t7, 0x0($v1)
    ctx->r15 = MEM_W(ctx->r3, 0X0);
    // 0x800C4C60: lh          $t8, 0x5520($t8)
    ctx->r24 = MEM_H(ctx->r24, 0X5520);
    // 0x800C4C64: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C4C68: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C4C6C: div         $zero, $t7, $t8
    lo = S32(S64(S32(ctx->r15)) / S64(S32(ctx->r24))); hi = S32(S64(S32(ctx->r15)) % S64(S32(ctx->r24)));
    // 0x800C4C70: mfhi        $t9
    ctx->r25 = hi;
    // 0x800C4C74: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800C4C78: bne         $t8, $zero, L_800C4C84
    if (ctx->r24 != 0) {
        // 0x800C4C7C: nop
    
            goto L_800C4C84;
    }
    // 0x800C4C7C: nop

    // 0x800C4C80: break       7
    do_break(2148289664);
L_800C4C84:
    // 0x800C4C84: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C4C88: bne         $t8, $at, L_800C4C9C
    if (ctx->r24 != ctx->r1) {
        // 0x800C4C8C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800C4C9C;
    }
    // 0x800C4C8C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800C4C90: bne         $t7, $at, L_800C4C9C
    if (ctx->r15 != ctx->r1) {
        // 0x800C4C94: nop
    
            goto L_800C4C9C;
    }
    // 0x800C4C94: nop

    // 0x800C4C98: break       6
    do_break(2148289688);
L_800C4C9C:
    // 0x800C4C9C: beq         $t9, $zero, L_800C4CAC
    if (ctx->r25 == 0) {
        // 0x800C4CA0: nop
    
            goto L_800C4CAC;
    }
    // 0x800C4CA0: nop

    // 0x800C4CA4: b           L_800C5078
    // 0x800C4CA8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800C5078;
    // 0x800C4CA8: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800C4CAC:
    // 0x800C4CAC: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C4CB0: jal         0x800C57A0
    // 0x800C4CB4: lw          $a1, 0x0($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X0);
    osSendMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x800C4CB4: lw          $a1, 0x0($v1)
    ctx->r5 = MEM_W(ctx->r3, 0X0);
    after_0:
    // 0x800C4CB8: addiu       $a0, $zero, 0x3
    ctx->r4 = ADD32(0, 0X3);
    // 0x800C4CBC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C4CC0: addiu       $v1, $v1, 0x555C
    ctx->r3 = ADD32(ctx->r3, 0X555C);
    // 0x800C4CC4: lw          $t4, 0x0($v1)
    ctx->r12 = MEM_W(ctx->r3, 0X0);
    // 0x800C4CC8: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C4CCC: addiu       $a1, $a1, 0x5558
    ctx->r5 = ADD32(ctx->r5, 0X5558);
    // 0x800C4CD0: addiu       $t5, $t4, 0x1
    ctx->r13 = ADD32(ctx->r12, 0X1);
    // 0x800C4CD4: div         $zero, $t5, $a0
    lo = S32(S64(S32(ctx->r13)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r13)) % S64(S32(ctx->r4)));
    // 0x800C4CD8: mfhi        $t7
    ctx->r15 = hi;
    // 0x800C4CDC: addiu       $t9, $t7, 0x1
    ctx->r25 = ADD32(ctx->r15, 0X1);
    // 0x800C4CE0: or          $t6, $t5, $zero
    ctx->r14 = ctx->r13 | 0;
    // 0x800C4CE4: div         $zero, $t9, $a0
    lo = S32(S64(S32(ctx->r25)) / S64(S32(ctx->r4))); hi = S32(S64(S32(ctx->r25)) % S64(S32(ctx->r4)));
    // 0x800C4CE8: lw          $t2, 0x0($a1)
    ctx->r10 = MEM_W(ctx->r5, 0X0);
    // 0x800C4CEC: sw          $t5, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r13;
    // 0x800C4CF0: mfhi        $a2
    ctx->r6 = hi;
    // 0x800C4CF4: xori        $t3, $t2, 0x1
    ctx->r11 = ctx->r10 ^ 0X1;
    // 0x800C4CF8: sw          $t3, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->r11;
    // 0x800C4CFC: bne         $a0, $zero, L_800C4D08
    if (ctx->r4 != 0) {
        // 0x800C4D00: nop
    
            goto L_800C4D08;
    }
    // 0x800C4D00: nop

    // 0x800C4D04: break       7
    do_break(2148289796);
L_800C4D08:
    // 0x800C4D08: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C4D0C: bne         $a0, $at, L_800C4D20
    if (ctx->r4 != ctx->r1) {
        // 0x800C4D10: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800C4D20;
    }
    // 0x800C4D10: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800C4D14: bne         $t6, $at, L_800C4D20
    if (ctx->r14 != ctx->r1) {
        // 0x800C4D18: nop
    
            goto L_800C4D20;
    }
    // 0x800C4D18: nop

    // 0x800C4D1C: break       6
    do_break(2148289820);
L_800C4D20:
    // 0x800C4D20: sw          $t7, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r15;
    // 0x800C4D24: or          $t8, $t7, $zero
    ctx->r24 = ctx->r15 | 0;
    // 0x800C4D28: bne         $a0, $zero, L_800C4D34
    if (ctx->r4 != 0) {
        // 0x800C4D2C: nop
    
            goto L_800C4D34;
    }
    // 0x800C4D2C: nop

    // 0x800C4D30: break       7
    do_break(2148289840);
L_800C4D34:
    // 0x800C4D34: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C4D38: bne         $a0, $at, L_800C4D4C
    if (ctx->r4 != ctx->r1) {
        // 0x800C4D3C: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800C4D4C;
    }
    // 0x800C4D3C: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800C4D40: bne         $t9, $at, L_800C4D4C
    if (ctx->r25 != ctx->r1) {
        // 0x800C4D44: nop
    
            goto L_800C4D4C;
    }
    // 0x800C4D44: nop

    // 0x800C4D48: break       6
    do_break(2148289864);
L_800C4D4C:
    // 0x800C4D4C: sw          $a2, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r6;
    // 0x800C4D50: jal         0x800CA950
    // 0x800C4D54: nop

    osAiGetLength_recomp(rdram, ctx);
        goto after_1;
    // 0x800C4D54: nop

    after_1:
    // 0x800C4D58: lw          $a2, 0x4C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X4C);
    // 0x800C4D5C: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C4D60: srl         $t2, $v0, 2
    ctx->r10 = S32(U32(ctx->r2) >> 2);
    // 0x800C4D64: sll         $t3, $a2, 1
    ctx->r11 = S32(ctx->r6 << 1);
    // 0x800C4D68: addu        $v1, $v1, $t3
    ctx->r3 = ADD32(ctx->r3, ctx->r11);
    // 0x800C4D6C: lh          $v1, 0x5624($v1)
    ctx->r3 = MEM_H(ctx->r3, 0X5624);
    // 0x800C4D70: sw          $t2, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r10;
    // 0x800C4D74: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C4D78: beq         $v1, $zero, L_800C4D90
    if (ctx->r3 == 0) {
        // 0x800C4D7C: sll         $t4, $a2, 2
        ctx->r12 = S32(ctx->r6 << 2);
            goto L_800C4D90;
    }
    // 0x800C4D7C: sll         $t4, $a2, 2
    ctx->r12 = S32(ctx->r6 << 2);
    // 0x800C4D80: addu        $a0, $a0, $t4
    ctx->r4 = ADD32(ctx->r4, ctx->r12);
    // 0x800C4D84: lw          $a0, 0x5618($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5618);
    // 0x800C4D88: jal         0x800CA960
    // 0x800C4D8C: sll         $a1, $v1, 2
    ctx->r5 = S32(ctx->r3 << 2);
    osAiSetNextBuffer_recomp(rdram, ctx);
        goto after_2;
    // 0x800C4D8C: sll         $a1, $v1, 2
    ctx->r5 = S32(ctx->r3 << 2);
    after_2:
L_800C4D90:
    // 0x800C4D90: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C4D94: addiu       $v1, $v1, 0x5554
    ctx->r3 = ADD32(ctx->r3, 0X5554);
    // 0x800C4D98: jal         0x800B8E34
    // 0x800C4D9C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    AudioLoad_DecreaseSampleDmaTtls(rdram, ctx);
        goto after_3;
    // 0x800C4D9C: sw          $zero, 0x0($v1)
    MEM_W(0X0, ctx->r3) = 0;
    after_3:
    // 0x800C4DA0: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C4DA4: lw          $a0, -0x7A00($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A00);
    // 0x800C4DA8: addiu       $a1, $sp, 0x38
    ctx->r5 = ADD32(ctx->r29, 0X38);
    // 0x800C4DAC: jal         0x800C5C60
    // 0x800C4DB0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    osRecvMesg_recomp(rdram, ctx);
        goto after_4;
    // 0x800C4DB0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_4:
    // 0x800C4DB4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C4DB8: beq         $v0, $at, L_800C4DDC
    if (ctx->r2 == ctx->r1) {
        // 0x800C4DBC: lui         $t8, 0x8004
        ctx->r24 = S32(0X8004 << 16);
            goto L_800C4DDC;
    }
    // 0x800C4DBC: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C4DC0: lw          $t5, 0x38($sp)
    ctx->r13 = MEM_W(ctx->r29, 0X38);
    // 0x800C4DC4: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C4DC8: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C4DCC: addiu       $t7, $t7, -0x1348
    ctx->r15 = ADD32(ctx->r15, -0X1348);
    // 0x800C4DD0: addiu       $t6, $zero, 0x5
    ctx->r14 = ADD32(0, 0X5);
    // 0x800C4DD4: sb          $t5, -0x1347($at)
    MEM_B(-0X1347, ctx->r1) = ctx->r13;
    // 0x800C4DD8: sb          $t6, 0x0($t7)
    MEM_B(0X0, ctx->r15) = ctx->r14;
L_800C4DDC:
    // 0x800C4DDC: addiu       $t8, $t8, -0x1348
    ctx->r24 = ADD32(ctx->r24, -0X1348);
    // 0x800C4DE0: lbu         $t9, 0x0($t8)
    ctx->r25 = MEM_BU(ctx->r24, 0X0);
    // 0x800C4DE4: beq         $t9, $zero, L_800C4E28
    if (ctx->r25 == 0) {
        // 0x800C4DE8: nop
    
            goto L_800C4E28;
    }
    // 0x800C4DE8: nop

    // 0x800C4DEC: jal         0x800B8480
    // 0x800C4DF0: nop

    AudioHeap_ResetStep(rdram, ctx);
        goto after_5;
    // 0x800C4DF0: nop

    after_5:
    // 0x800C4DF4: bne         $v0, $zero, L_800C4E28
    if (ctx->r2 != 0) {
        // 0x800C4DF8: lui         $t2, 0x8004
        ctx->r10 = S32(0X8004 << 16);
            goto L_800C4E28;
    }
    // 0x800C4DF8: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800C4DFC: addiu       $t2, $t2, -0x1348
    ctx->r10 = ADD32(ctx->r10, -0X1348);
    // 0x800C4E00: lbu         $t3, 0x0($t2)
    ctx->r11 = MEM_BU(ctx->r10, 0X0);
    // 0x800C4E04: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C4E08: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C4E0C: bne         $t3, $zero, L_800C4E20
    if (ctx->r11 != 0) {
        // 0x800C4E10: or          $a2, $zero, $zero
        ctx->r6 = 0 | 0;
            goto L_800C4E20;
    }
    // 0x800C4E10: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800C4E14: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    // 0x800C4E18: jal         0x800C57A0
    // 0x800C4E1C: lbu         $a1, -0x1347($a1)
    ctx->r5 = MEM_BU(ctx->r5, -0X1347);
    osSendMesg_recomp(rdram, ctx);
        goto after_6;
    // 0x800C4E1C: lbu         $a1, -0x1347($a1)
    ctx->r5 = MEM_BU(ctx->r5, -0X1347);
    after_6:
L_800C4E20:
    // 0x800C4E20: b           L_800C5078
    // 0x800C4E24: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
        goto L_800C5078;
    // 0x800C4E24: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800C4E28:
    // 0x800C4E28: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C4E2C: lw          $v0, 0x5558($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X5558);
    // 0x800C4E30: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800C4E34: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800C4E38: sll         $t4, $v0, 2
    ctx->r12 = S32(ctx->r2 << 2);
    // 0x800C4E3C: addu        $t4, $t4, $v0
    ctx->r12 = ADD32(ctx->r12, ctx->r2);
    // 0x800C4E40: sll         $t4, $t4, 4
    ctx->r12 = S32(ctx->r12 << 4);
    // 0x800C4E44: addiu       $t5, $t5, 0x5570
    ctx->r13 = ADD32(ctx->r13, 0X5570);
    // 0x800C4E48: addiu       $t1, $t1, 0x556C
    ctx->r9 = ADD32(ctx->r9, 0X556C);
    // 0x800C4E4C: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x800C4E50: lui         $t8, 0x8004
    ctx->r24 = S32(0X8004 << 16);
    // 0x800C4E54: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x800C4E58: sw          $t6, 0x0($t1)
    MEM_W(0X0, ctx->r9) = ctx->r14;
    // 0x800C4E5C: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x800C4E60: lw          $t8, 0x5560($t8)
    ctx->r24 = MEM_W(ctx->r24, 0X5560);
    // 0x800C4E64: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800C4E68: lw          $a2, 0x555C($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X555C);
    // 0x800C4E6C: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C4E70: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C4E74: addiu       $a1, $a1, 0x5520
    ctx->r5 = ADD32(ctx->r5, 0X5520);
    // 0x800C4E78: lui         $t2, 0x8004
    ctx->r10 = S32(0X8004 << 16);
    // 0x800C4E7C: sw          $t8, 0x5568($at)
    MEM_W(0X5568, ctx->r1) = ctx->r24;
    // 0x800C4E80: lh          $t6, 0x6($a1)
    ctx->r14 = MEM_H(ctx->r5, 0X6);
    // 0x800C4E84: lw          $t7, 0x54($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X54);
    // 0x800C4E88: addiu       $t2, $t2, 0x5618
    ctx->r10 = ADD32(ctx->r10, 0X5618);
    // 0x800C4E8C: sll         $t9, $a2, 2
    ctx->r25 = S32(ctx->r6 << 2);
    // 0x800C4E90: addu        $a3, $t9, $t2
    ctx->r7 = ADD32(ctx->r25, ctx->r10);
    // 0x800C4E94: lw          $t3, 0x0($a3)
    ctx->r11 = MEM_W(ctx->r7, 0X0);
    // 0x800C4E98: subu        $t8, $t6, $t7
    ctx->r24 = SUB32(ctx->r14, ctx->r15);
    // 0x800C4E9C: addiu       $t9, $t8, 0x40
    ctx->r25 = ADD32(ctx->r24, 0X40);
    // 0x800C4EA0: lui         $t5, 0x8004
    ctx->r13 = S32(0X8004 << 16);
    // 0x800C4EA4: addiu       $t5, $t5, 0x5624
    ctx->r13 = ADD32(ctx->r13, 0X5624);
    // 0x800C4EA8: andi        $t2, $t9, 0xFFF0
    ctx->r10 = ctx->r25 & 0XFFF0;
    // 0x800C4EAC: sll         $t4, $a2, 1
    ctx->r12 = S32(ctx->r6 << 1);
    // 0x800C4EB0: sw          $t3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r11;
    // 0x800C4EB4: addiu       $t3, $t2, 0x10
    ctx->r11 = ADD32(ctx->r10, 0X10);
    // 0x800C4EB8: addu        $t0, $t4, $t5
    ctx->r8 = ADD32(ctx->r12, ctx->r13);
    // 0x800C4EBC: sh          $t3, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r11;
    // 0x800C4EC0: lh          $v1, 0x0($t0)
    ctx->r3 = MEM_H(ctx->r8, 0X0);
    // 0x800C4EC4: lh          $a0, 0xA($a1)
    ctx->r4 = MEM_H(ctx->r5, 0XA);
    // 0x800C4EC8: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x800C4ECC: slt         $at, $v1, $a0
    ctx->r1 = SIGNED(ctx->r3) < SIGNED(ctx->r4) ? 1 : 0;
    // 0x800C4ED0: beql        $at, $zero, L_800C4EE4
    if (ctx->r1 == 0) {
        // 0x800C4ED4: lh          $v0, 0x8($a1)
        ctx->r2 = MEM_H(ctx->r5, 0X8);
            goto L_800C4EE4;
    }
    goto skip_0;
    // 0x800C4ED4: lh          $v0, 0x8($a1)
    ctx->r2 = MEM_H(ctx->r5, 0X8);
    skip_0:
    // 0x800C4ED8: sh          $a0, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r4;
    // 0x800C4EDC: lh          $v1, 0x0($t0)
    ctx->r3 = MEM_H(ctx->r8, 0X0);
    // 0x800C4EE0: lh          $v0, 0x8($a1)
    ctx->r2 = MEM_H(ctx->r5, 0X8);
L_800C4EE4:
    // 0x800C4EE4: addiu       $a1, $sp, 0x34
    ctx->r5 = ADD32(ctx->r29, 0X34);
    // 0x800C4EE8: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C4EEC: slt         $at, $v0, $v1
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r3) ? 1 : 0;
    // 0x800C4EF0: beq         $at, $zero, L_800C4EFC
    if (ctx->r1 == 0) {
        // 0x800C4EF4: nop
    
            goto L_800C4EFC;
    }
    // 0x800C4EF4: nop

    // 0x800C4EF8: sh          $v0, 0x0($t0)
    MEM_H(0X0, ctx->r8) = ctx->r2;
L_800C4EFC:
    // 0x800C4EFC: lw          $a0, -0x7A04($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A04);
    // 0x800C4F00: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x800C4F04: jal         0x800C5C60
    // 0x800C4F08: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    osRecvMesg_recomp(rdram, ctx);
        goto after_7;
    // 0x800C4F08: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    after_7:
    // 0x800C4F0C: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800C4F10: beq         $v0, $at, L_800C4F28
    if (ctx->r2 == ctx->r1) {
        // 0x800C4F14: lw          $t0, 0x2C($sp)
        ctx->r8 = MEM_W(ctx->r29, 0X2C);
            goto L_800C4F28;
    }
    // 0x800C4F14: lw          $t0, 0x2C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X2C);
    // 0x800C4F18: lw          $a0, 0x34($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X34);
    // 0x800C4F1C: jal         0x800C547C
    // 0x800C4F20: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    AudioThread_ProcessCmds(rdram, ctx);
        goto after_8;
    // 0x800C4F20: sw          $t0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r8;
    after_8:
    // 0x800C4F24: lw          $t0, 0x2C($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X2C);
L_800C4F28:
    // 0x800C4F28: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C4F2C: lw          $a0, 0x5568($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5568);
    // 0x800C4F30: addiu       $a1, $sp, 0x50
    ctx->r5 = ADD32(ctx->r29, 0X50);
    // 0x800C4F34: lw          $a2, 0x40($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X40);
    // 0x800C4F38: jal         0x800B527C
    // 0x800C4F3C: lh          $a3, 0x0($t0)
    ctx->r7 = MEM_H(ctx->r8, 0X0);
    AudioSynth_Update(rdram, ctx);
        goto after_9;
    // 0x800C4F3C: lh          $a3, 0x0($t0)
    ctx->r7 = MEM_H(ctx->r8, 0X0);
    after_9:
    // 0x800C4F40: lui         $t0, 0x8004
    ctx->r8 = S32(0X8004 << 16);
    // 0x800C4F44: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C4F48: sw          $v0, 0x5568($at)
    MEM_W(0X5568, ctx->r1) = ctx->r2;
    // 0x800C4F4C: addiu       $t0, $t0, 0x5550
    ctx->r8 = ADD32(ctx->r8, 0X5550);
    // 0x800C4F50: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C4F54: lw          $t4, 0x0($t0)
    ctx->r12 = MEM_W(ctx->r8, 0X0);
    // 0x800C4F58: addiu       $a0, $a0, 0x562C
    ctx->r4 = ADD32(ctx->r4, 0X562C);
    // 0x800C4F5C: lw          $t5, 0x0($a0)
    ctx->r13 = MEM_W(ctx->r4, 0X0);
    // 0x800C4F60: lw          $t7, 0x0($t0)
    ctx->r15 = MEM_W(ctx->r8, 0X0);
    // 0x800C4F64: lw          $t9, 0x24($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X24);
    // 0x800C4F68: addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // 0x800C4F6C: multu       $t6, $t7
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r15)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800C4F70: lw          $t3, 0x0($t0)
    ctx->r11 = MEM_W(ctx->r8, 0X0);
    // 0x800C4F74: lui         $t1, 0x8004
    ctx->r9 = S32(0X8004 << 16);
    // 0x800C4F78: addiu       $t1, $t1, 0x556C
    ctx->r9 = ADD32(ctx->r9, 0X556C);
    // 0x800C4F7C: andi        $t4, $t3, 0xFF
    ctx->r12 = ctx->r11 & 0XFF;
    // 0x800C4F80: sll         $t5, $t4, 1
    ctx->r13 = S32(ctx->r12 << 1);
    // 0x800C4F84: lw          $t3, 0x0($t1)
    ctx->r11 = MEM_W(ctx->r9, 0X0);
    // 0x800C4F88: lui         $a2, 0x8004
    ctx->r6 = S32(0X8004 << 16);
    // 0x800C4F8C: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x800C4F90: addiu       $a1, $a1, 0x22B0
    ctx->r5 = ADD32(ctx->r5, 0X22B0);
    // 0x800C4F94: mflo        $t8
    ctx->r24 = lo;
    // 0x800C4F98: sw          $t8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r24;
    // 0x800C4F9C: lw          $t2, 0x0($t9)
    ctx->r10 = MEM_W(ctx->r25, 0X0);
    // 0x800C4FA0: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x800C4FA4: lui         $a3, 0x800F
    ctx->r7 = S32(0X800F << 16);
    // 0x800C4FA8: addu        $t6, $t2, $t5
    ctx->r14 = ADD32(ctx->r10, ctx->r13);
    // 0x800C4FAC: lh          $t7, 0x0($t6)
    ctx->r15 = MEM_H(ctx->r14, 0X0);
    // 0x800C4FB0: lui         $t5, 0x800D
    ctx->r13 = S32(0X800D << 16);
    // 0x800C4FB4: addiu       $t5, $t5, 0x2380
    ctx->r13 = ADD32(ctx->r13, 0X2380);
    // 0x800C4FB8: addu        $t9, $t7, $t8
    ctx->r25 = ADD32(ctx->r15, ctx->r24);
    // 0x800C4FBC: sw          $t9, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->r25;
    // 0x800C4FC0: lw          $a2, 0x5558($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X5558);
    // 0x800C4FC4: sw          $zero, 0x40($t3)
    MEM_W(0X40, ctx->r11) = 0;
    // 0x800C4FC8: lw          $t4, 0x0($t1)
    ctx->r12 = MEM_W(ctx->r9, 0X0);
    // 0x800C4FCC: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800C4FD0: addiu       $a3, $a3, -0x14F0
    ctx->r7 = ADD32(ctx->r7, -0X14F0);
    // 0x800C4FD4: sw          $zero, 0x44($t4)
    MEM_W(0X44, ctx->r12) = 0;
    // 0x800C4FD8: lw          $v1, 0x0($t1)
    ctx->r3 = MEM_W(ctx->r9, 0X0);
    // 0x800C4FDC: subu        $t6, $t5, $a1
    ctx->r14 = SUB32(ctx->r13, ctx->r5);
    // 0x800C4FE0: addiu       $t9, $t9, -0x1230
    ctx->r25 = ADD32(ctx->r25, -0X1230);
    // 0x800C4FE4: addiu       $t2, $zero, 0x2
    ctx->r10 = ADD32(0, 0X2);
    // 0x800C4FE8: subu        $t3, $t9, $a3
    ctx->r11 = SUB32(ctx->r25, ctx->r7);
    // 0x800C4FEC: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x800C4FF0: sra         $t4, $t3, 3
    ctx->r12 = S32(SIGNED(ctx->r11) >> 3);
    // 0x800C4FF4: sw          $t2, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->r10;
    // 0x800C4FF8: sw          $t6, 0xC($v1)
    MEM_W(0XC, ctx->r3) = ctx->r14;
    // 0x800C4FFC: addiu       $t7, $t7, 0x37B0
    ctx->r15 = ADD32(ctx->r15, 0X37B0);
    // 0x800C5000: addiu       $t8, $zero, 0x800
    ctx->r24 = ADD32(0, 0X800);
    // 0x800C5004: sll         $t2, $t4, 3
    ctx->r10 = S32(ctx->r12 << 3);
    // 0x800C5008: lui         $t6, 0x8004
    ctx->r14 = S32(0X8004 << 16);
    // 0x800C500C: sll         $t5, $a2, 2
    ctx->r13 = S32(ctx->r6 << 2);
    // 0x800C5010: addu        $t6, $t6, $t5
    ctx->r14 = ADD32(ctx->r14, ctx->r13);
    // 0x800C5014: sw          $zero, 0x4($v1)
    MEM_W(0X4, ctx->r3) = 0;
    // 0x800C5018: sw          $a1, 0x8($v1)
    MEM_W(0X8, ctx->r3) = ctx->r5;
    // 0x800C501C: sw          $t7, 0x10($v1)
    MEM_W(0X10, ctx->r3) = ctx->r15;
    // 0x800C5020: sw          $a3, 0x18($v1)
    MEM_W(0X18, ctx->r3) = ctx->r7;
    // 0x800C5024: sw          $t8, 0x14($v1)
    MEM_W(0X14, ctx->r3) = ctx->r24;
    // 0x800C5028: sw          $t2, 0x1C($v1)
    MEM_W(0X1C, ctx->r3) = ctx->r10;
    // 0x800C502C: sw          $zero, 0x20($v1)
    MEM_W(0X20, ctx->r3) = 0;
    // 0x800C5030: sw          $zero, 0x24($v1)
    MEM_W(0X24, ctx->r3) = 0;
    // 0x800C5034: sw          $zero, 0x28($v1)
    MEM_W(0X28, ctx->r3) = 0;
    // 0x800C5038: sw          $zero, 0x2C($v1)
    MEM_W(0X2C, ctx->r3) = 0;
    // 0x800C503C: lw          $t6, 0x5560($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5560);
    // 0x800C5040: lui         $t9, 0x800F
    ctx->r25 = S32(0X800F << 16);
    // 0x800C5044: sw          $t6, 0x30($v1)
    MEM_W(0X30, ctx->r3) = ctx->r14;
    // 0x800C5048: lw          $t7, 0x50($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X50);
    // 0x800C504C: sw          $zero, 0x38($v1)
    MEM_W(0X38, ctx->r3) = 0;
    // 0x800C5050: sw          $zero, 0x3C($v1)
    MEM_W(0X3C, ctx->r3) = 0;
    // 0x800C5054: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x800C5058: sw          $t8, 0x34($v1)
    MEM_W(0X34, ctx->r3) = ctx->r24;
    // 0x800C505C: lw          $t3, 0x50($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X50);
    // 0x800C5060: lw          $t9, -0x7970($t9)
    ctx->r25 = MEM_W(ctx->r25, -0X7970);
    // 0x800C5064: slt         $at, $t9, $t3
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x800C5068: beq         $at, $zero, L_800C5074
    if (ctx->r1 == 0) {
        // 0x800C506C: lui         $at, 0x800F
        ctx->r1 = S32(0X800F << 16);
            goto L_800C5074;
    }
    // 0x800C506C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C5070: sw          $t3, -0x7970($at)
    MEM_W(-0X7970, ctx->r1) = ctx->r11;
L_800C5074:
    // 0x800C5074: lw          $v0, 0x0($t1)
    ctx->r2 = MEM_W(ctx->r9, 0X0);
L_800C5078:
    // 0x800C5078: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C507C: addiu       $sp, $sp, 0x58
    ctx->r29 = ADD32(ctx->r29, 0X58);
    // 0x800C5080: jr          $ra
    // 0x800C5084: nop

    return;
    // 0x800C5084: nop

;}
RECOMP_FUNC void AudioThread_ProcessGlobalCmd(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C5088: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C508C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C5090: lbu         $v0, 0x0($a0)
    ctx->r2 = MEM_BU(ctx->r4, 0X0);
    // 0x800C5094: addiu       $at, $zero, 0x81
    ctx->r1 = ADD32(0, 0X81);
    // 0x800C5098: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x800C509C: beq         $v0, $at, L_800C50E4
    if (ctx->r2 == ctx->r1) {
        // 0x800C50A0: addiu       $a1, $zero, 0x3
        ctx->r5 = ADD32(0, 0X3);
            goto L_800C50E4;
    }
    // 0x800C50A0: addiu       $a1, $zero, 0x3
    ctx->r5 = ADD32(0, 0X3);
    // 0x800C50A4: addiu       $at, $zero, 0x82
    ctx->r1 = ADD32(0, 0X82);
    // 0x800C50A8: beq         $v0, $at, L_800C50F4
    if (ctx->r2 == ctx->r1) {
        // 0x800C50AC: addiu       $at, $zero, 0x83
        ctx->r1 = ADD32(0, 0X83);
            goto L_800C50F4;
    }
    // 0x800C50AC: addiu       $at, $zero, 0x83
    ctx->r1 = ADD32(0, 0X83);
    // 0x800C50B0: beq         $v0, $at, L_800C5120
    if (ctx->r2 == ctx->r1) {
        // 0x800C50B4: addiu       $at, $zero, 0x88
        ctx->r1 = ADD32(0, 0X88);
            goto L_800C5120;
    }
    // 0x800C50B4: addiu       $at, $zero, 0x88
    ctx->r1 = ADD32(0, 0X88);
    // 0x800C50B8: beq         $v0, $at, L_800C50F4
    if (ctx->r2 == ctx->r1) {
        // 0x800C50BC: addiu       $at, $zero, 0xF0
        ctx->r1 = ADD32(0, 0XF0);
            goto L_800C50F4;
    }
    // 0x800C50BC: addiu       $at, $zero, 0xF0
    ctx->r1 = ADD32(0, 0XF0);
    // 0x800C50C0: beq         $v0, $at, L_800C5178
    if (ctx->r2 == ctx->r1) {
        // 0x800C50C4: addiu       $at, $zero, 0xF1
        ctx->r1 = ADD32(0, 0XF1);
            goto L_800C5178;
    }
    // 0x800C50C4: addiu       $at, $zero, 0xF1
    ctx->r1 = ADD32(0, 0XF1);
    // 0x800C50C8: beq         $v0, $at, L_800C5188
    if (ctx->r2 == ctx->r1) {
        // 0x800C50CC: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C5188;
    }
    // 0x800C50CC: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C50D0: addiu       $at, $zero, 0xF2
    ctx->r1 = ADD32(0, 0XF2);
    // 0x800C50D4: beq         $v0, $at, L_800C51D8
    if (ctx->r2 == ctx->r1) {
        // 0x800C50D8: lui         $v1, 0x8004
        ctx->r3 = S32(0X8004 << 16);
            goto L_800C51D8;
    }
    // 0x800C50D8: lui         $v1, 0x8004
    ctx->r3 = S32(0X8004 << 16);
    // 0x800C50DC: b           L_800C5238
    // 0x800C50E0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C5238;
    // 0x800C50E0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C50E4:
    // 0x800C50E4: jal         0x800B9E40
    // 0x800C50E8: lbu         $a0, 0x2($a3)
    ctx->r4 = MEM_BU(ctx->r7, 0X2);
    Audio_PreLoadSequence(rdram, ctx);
        goto after_0;
    // 0x800C50E8: lbu         $a0, 0x2($a3)
    ctx->r4 = MEM_BU(ctx->r7, 0X2);
    after_0:
    // 0x800C50EC: b           L_800C5238
    // 0x800C50F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C5238;
    // 0x800C50F0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C50F4:
    // 0x800C50F4: lbu         $a0, 0x1($a3)
    ctx->r4 = MEM_BU(ctx->r7, 0X1);
    // 0x800C50F8: lbu         $a1, 0x2($a3)
    ctx->r5 = MEM_BU(ctx->r7, 0X2);
    // 0x800C50FC: lbu         $a2, 0x3($a3)
    ctx->r6 = MEM_BU(ctx->r7, 0X3);
    // 0x800C5100: jal         0x800B9F3C
    // 0x800C5104: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    Audio_LoadSequence(rdram, ctx);
        goto after_1;
    // 0x800C5104: sw          $a3, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r7;
    after_1:
    // 0x800C5108: lw          $a3, 0x18($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X18);
    // 0x800C510C: lbu         $a0, 0x1($a3)
    ctx->r4 = MEM_BU(ctx->r7, 0X1);
    // 0x800C5110: jal         0x800C528C
    // 0x800C5114: lw          $a1, 0x4($a3)
    ctx->r5 = MEM_W(ctx->r7, 0X4);
    AudioThread_SetFadeInTimer(rdram, ctx);
        goto after_2;
    // 0x800C5114: lw          $a1, 0x4($a3)
    ctx->r5 = MEM_W(ctx->r7, 0X4);
    after_2:
    // 0x800C5118: b           L_800C5238
    // 0x800C511C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C5238;
    // 0x800C511C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C5120:
    // 0x800C5120: lbu         $v0, 0x1($a3)
    ctx->r2 = MEM_BU(ctx->r7, 0X1);
    // 0x800C5124: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C5128: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x800C512C: sll         $t6, $v0, 2
    ctx->r14 = S32(ctx->r2 << 2);
    // 0x800C5130: addu        $t6, $t6, $v0
    ctx->r14 = ADD32(ctx->r14, ctx->r2);
    // 0x800C5134: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x800C5138: addu        $a0, $t6, $t7
    ctx->r4 = ADD32(ctx->r14, ctx->r15);
    // 0x800C513C: lw          $t8, 0x0($a0)
    ctx->r24 = MEM_W(ctx->r4, 0X0);
    // 0x800C5140: srl         $t9, $t8, 31
    ctx->r25 = S32(U32(ctx->r24) >> 31);
    // 0x800C5144: beql        $t9, $zero, L_800C5238
    if (ctx->r25 == 0) {
        // 0x800C5148: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_800C5238;
    }
    goto skip_0;
    // 0x800C5148: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
    // 0x800C514C: lw          $a1, 0x4($a3)
    ctx->r5 = MEM_W(ctx->r7, 0X4);
    // 0x800C5150: bne         $a1, $zero, L_800C5168
    if (ctx->r5 != 0) {
        // 0x800C5154: nop
    
            goto L_800C5168;
    }
    // 0x800C5154: nop

    // 0x800C5158: jal         0x800BCEE0
    // 0x800C515C: nop

    AudioSeq_SequencePlayerDisable(rdram, ctx);
        goto after_3;
    // 0x800C515C: nop

    after_3:
    // 0x800C5160: b           L_800C5238
    // 0x800C5164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C5238;
    // 0x800C5164: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C5168:
    // 0x800C5168: jal         0x800C5244
    // 0x800C516C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    AudioThread_SetFadeOutTimer(rdram, ctx);
        goto after_4;
    // 0x800C516C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    after_4:
    // 0x800C5170: b           L_800C5238
    // 0x800C5174: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
        goto L_800C5238;
    // 0x800C5174: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C5178:
    // 0x800C5178: lw          $t0, 0x4($a3)
    ctx->r8 = MEM_W(ctx->r7, 0X4);
    // 0x800C517C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C5180: b           L_800C5234
    // 0x800C5184: sb          $t0, 0x554E($at)
    MEM_B(0X554E, ctx->r1) = ctx->r8;
        goto L_800C5234;
    // 0x800C5184: sb          $t0, 0x554E($at)
    MEM_B(0X554E, ctx->r1) = ctx->r8;
L_800C5188:
    // 0x800C5188: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C518C: lbu         $t3, -0x338($v0)
    ctx->r11 = MEM_BU(ctx->r2, -0X338);
    // 0x800C5190: lbu         $t0, -0x1F8($v1)
    ctx->r8 = MEM_BU(ctx->r3, -0X1F8);
    // 0x800C5194: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C5198: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C519C: lbu         $t2, 0x88($a1)
    ctx->r10 = MEM_BU(ctx->r5, 0X88);
    // 0x800C51A0: lbu         $t6, -0xB8($a0)
    ctx->r14 = MEM_BU(ctx->r4, -0XB8);
    // 0x800C51A4: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C51A8: ori         $v0, $t3, 0x24
    ctx->r2 = ctx->r11 | 0X24;
    // 0x800C51AC: sb          $v0, -0x338($at)
    MEM_B(-0X338, ctx->r1) = ctx->r2;
    // 0x800C51B0: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C51B4: ori         $v1, $t0, 0x24
    ctx->r3 = ctx->r8 | 0X24;
    // 0x800C51B8: sb          $v1, -0x1F8($at)
    MEM_B(-0X1F8, ctx->r1) = ctx->r3;
    // 0x800C51BC: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C51C0: ori         $t8, $t6, 0x24
    ctx->r24 = ctx->r14 | 0X24;
    // 0x800C51C4: sb          $t8, -0xB8($at)
    MEM_B(-0XB8, ctx->r1) = ctx->r24;
    // 0x800C51C8: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C51CC: ori         $t4, $t2, 0x24
    ctx->r12 = ctx->r10 | 0X24;
    // 0x800C51D0: b           L_800C5234
    // 0x800C51D4: sb          $t4, 0x88($at)
    MEM_B(0X88, ctx->r1) = ctx->r12;
        goto L_800C5234;
    // 0x800C51D4: sb          $t4, 0x88($at)
    MEM_B(0X88, ctx->r1) = ctx->r12;
L_800C51D8:
    // 0x800C51D8: lui         $v0, 0x8004
    ctx->r2 = S32(0X8004 << 16);
    // 0x800C51DC: lbu         $v0, -0x338($v0)
    ctx->r2 = MEM_BU(ctx->r2, -0X338);
    // 0x800C51E0: lbu         $v1, -0x1F8($v1)
    ctx->r3 = MEM_BU(ctx->r3, -0X1F8);
    // 0x800C51E4: lui         $a0, 0x8004
    ctx->r4 = S32(0X8004 << 16);
    // 0x800C51E8: lbu         $a0, -0xB8($a0)
    ctx->r4 = MEM_BU(ctx->r4, -0XB8);
    // 0x800C51EC: lui         $a1, 0x8004
    ctx->r5 = S32(0X8004 << 16);
    // 0x800C51F0: andi        $t7, $v0, 0xFFDF
    ctx->r15 = ctx->r2 & 0XFFDF;
    // 0x800C51F4: lbu         $a1, 0x88($a1)
    ctx->r5 = MEM_BU(ctx->r5, 0X88);
    // 0x800C51F8: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C51FC: ori         $v0, $t7, 0x4
    ctx->r2 = ctx->r15 | 0X4;
    // 0x800C5200: sb          $v0, -0x338($at)
    MEM_B(-0X338, ctx->r1) = ctx->r2;
    // 0x800C5204: andi        $t2, $v1, 0xFFDF
    ctx->r10 = ctx->r3 & 0XFFDF;
    // 0x800C5208: ori         $v1, $t2, 0x4
    ctx->r3 = ctx->r10 | 0X4;
    // 0x800C520C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C5210: sb          $v1, -0x1F8($at)
    MEM_B(-0X1F8, ctx->r1) = ctx->r3;
    // 0x800C5214: andi        $t7, $a0, 0xFFDF
    ctx->r15 = ctx->r4 & 0XFFDF;
    // 0x800C5218: ori         $t9, $t7, 0x4
    ctx->r25 = ctx->r15 | 0X4;
    // 0x800C521C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C5220: sb          $t9, -0xB8($at)
    MEM_B(-0XB8, ctx->r1) = ctx->r25;
    // 0x800C5224: andi        $t2, $a1, 0xFFDF
    ctx->r10 = ctx->r5 & 0XFFDF;
    // 0x800C5228: ori         $t4, $t2, 0x4
    ctx->r12 = ctx->r10 | 0X4;
    // 0x800C522C: lui         $at, 0x8004
    ctx->r1 = S32(0X8004 << 16);
    // 0x800C5230: sb          $t4, 0x88($at)
    MEM_B(0X88, ctx->r1) = ctx->r12;
L_800C5234:
    // 0x800C5234: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_800C5238:
    // 0x800C5238: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C523C: jr          $ra
    // 0x800C5240: nop

    return;
    // 0x800C5240: nop

;}
RECOMP_FUNC void AudioThread_SetFadeOutTimer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C5244: bne         $a1, $zero, L_800C5250
    if (ctx->r5 != 0) {
        // 0x800C5248: sll         $t6, $a0, 2
        ctx->r14 = S32(ctx->r4 << 2);
            goto L_800C5250;
    }
    // 0x800C5248: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800C524C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
L_800C5250:
    // 0x800C5250: mtc1        $a1, $f6
    ctx->f6.u32l = ctx->r5;
    // 0x800C5254: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800C5258: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C525C: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800C5260: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x800C5264: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x800C5268: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800C526C: lwc1        $f4, 0x18($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X18);
    // 0x800C5270: addiu       $t8, $zero, 0x2
    ctx->r24 = ADD32(0, 0X2);
    // 0x800C5274: sb          $t8, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r24;
    // 0x800C5278: div.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f4.fl, ctx->f8.fl);
    // 0x800C527C: sh          $a1, 0x10($v0)
    MEM_H(0X10, ctx->r2) = ctx->r5;
    // 0x800C5280: neg.s       $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = -ctx->f10.fl;
    // 0x800C5284: jr          $ra
    // 0x800C5288: swc1        $f16, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f16.u32l;
    return;
    // 0x800C5288: swc1        $f16, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f16.u32l;
;}
RECOMP_FUNC void AudioThread_SetFadeInTimer(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C528C: beq         $a1, $zero, L_800C52C4
    if (ctx->r5 == 0) {
        // 0x800C5290: sll         $t6, $a0, 2
        ctx->r14 = S32(ctx->r4 << 2);
            goto L_800C52C4;
    }
    // 0x800C5290: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800C5294: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800C5298: lui         $t7, 0x8004
    ctx->r15 = S32(0X8004 << 16);
    // 0x800C529C: addiu       $t7, $t7, -0x338
    ctx->r15 = ADD32(ctx->r15, -0X338);
    // 0x800C52A0: sll         $t6, $t6, 6
    ctx->r14 = S32(ctx->r14 << 6);
    // 0x800C52A4: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800C52A8: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x800C52AC: addiu       $t8, $zero, 0x1
    ctx->r24 = ADD32(0, 0X1);
    // 0x800C52B0: sb          $t8, 0x1($v0)
    MEM_B(0X1, ctx->r2) = ctx->r24;
    // 0x800C52B4: sh          $a1, 0x12($v0)
    MEM_H(0X12, ctx->r2) = ctx->r5;
    // 0x800C52B8: sh          $a1, 0x10($v0)
    MEM_H(0X10, ctx->r2) = ctx->r5;
    // 0x800C52BC: swc1        $f0, 0x18($v0)
    MEM_W(0X18, ctx->r2) = ctx->f0.u32l;
    // 0x800C52C0: swc1        $f0, 0x1C($v0)
    MEM_W(0X1C, ctx->r2) = ctx->f0.u32l;
L_800C52C4:
    // 0x800C52C4: jr          $ra
    // 0x800C52C8: nop

    return;
    // 0x800C52C8: nop

;}
RECOMP_FUNC void AudioThread_InitQueues(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C52CC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C52D0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C52D4: sb          $zero, -0x7A10($at)
    MEM_B(-0X7A10, ctx->r1) = 0;
    // 0x800C52D8: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C52DC: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800C52E0: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C52E4: lui         $a1, 0x801E
    ctx->r5 = S32(0X801E << 16);
    // 0x800C52E8: sb          $zero, -0x7A0C($at)
    MEM_B(-0X7A0C, ctx->r1) = 0;
    // 0x800C52EC: addiu       $a1, $a1, -0x7970
    ctx->r5 = ADD32(ctx->r5, -0X7970);
    // 0x800C52F0: lw          $a0, -0x7A08($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A08);
    // 0x800C52F4: jal         0x800C6310
    // 0x800C52F8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_0;
    // 0x800C52F8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_0:
    // 0x800C52FC: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C5300: lui         $a1, 0x801E
    ctx->r5 = S32(0X801E << 16);
    // 0x800C5304: addiu       $a1, $a1, -0x7968
    ctx->r5 = ADD32(ctx->r5, -0X7968);
    // 0x800C5308: lw          $a0, -0x7A04($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A04);
    // 0x800C530C: jal         0x800C6310
    // 0x800C5310: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_1;
    // 0x800C5310: addiu       $a2, $zero, 0x4
    ctx->r6 = ADD32(0, 0X4);
    after_1:
    // 0x800C5314: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C5318: lui         $a1, 0x801E
    ctx->r5 = S32(0X801E << 16);
    // 0x800C531C: addiu       $a1, $a1, -0x7958
    ctx->r5 = ADD32(ctx->r5, -0X7958);
    // 0x800C5320: lw          $a0, -0x7A00($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X7A00);
    // 0x800C5324: jal         0x800C6310
    // 0x800C5328: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_2;
    // 0x800C5328: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_2:
    // 0x800C532C: lui         $a0, 0x800F
    ctx->r4 = S32(0X800F << 16);
    // 0x800C5330: lui         $a1, 0x801E
    ctx->r5 = S32(0X801E << 16);
    // 0x800C5334: addiu       $a1, $a1, -0x7954
    ctx->r5 = ADD32(ctx->r5, -0X7954);
    // 0x800C5338: lw          $a0, -0x79FC($a0)
    ctx->r4 = MEM_W(ctx->r4, -0X79FC);
    // 0x800C533C: jal         0x800C6310
    // 0x800C5340: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osCreateMesgQueue_recomp(rdram, ctx);
        goto after_3;
    // 0x800C5340: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_3:
    // 0x800C5344: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C5348: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C534C: jr          $ra
    // 0x800C5350: nop

    return;
    // 0x800C5350: nop

;}
RECOMP_FUNC void AudioThread_QueueCmd(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C5354: lui         $v1, 0x800F
    ctx->r3 = S32(0X800F << 16);
    // 0x800C5358: addiu       $v1, $v1, -0x7A10
    ctx->r3 = ADD32(ctx->r3, -0X7A10);
    // 0x800C535C: lbu         $t7, 0x0($v1)
    ctx->r15 = MEM_BU(ctx->r3, 0X0);
    // 0x800C5360: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x800C5364: addiu       $t9, $t9, 0x7E90
    ctx->r25 = ADD32(ctx->r25, 0X7E90);
    // 0x800C5368: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x800C536C: addu        $v0, $t8, $t9
    ctx->r2 = ADD32(ctx->r24, ctx->r25);
    // 0x800C5370: sw          $a0, 0x0($v0)
    MEM_W(0X0, ctx->r2) = ctx->r4;
    // 0x800C5374: lw          $t0, 0x0($a1)
    ctx->r8 = MEM_W(ctx->r5, 0X0);
    // 0x800C5378: sw          $t0, 0x4($v0)
    MEM_W(0X4, ctx->r2) = ctx->r8;
    // 0x800C537C: lbu         $t1, 0x0($v1)
    ctx->r9 = MEM_BU(ctx->r3, 0X0);
    // 0x800C5380: addiu       $t2, $t1, 0x1
    ctx->r10 = ADD32(ctx->r9, 0X1);
    // 0x800C5384: jr          $ra
    // 0x800C5388: sb          $t2, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r10;
    return;
    // 0x800C5388: sb          $t2, 0x0($v1)
    MEM_B(0X0, ctx->r3) = ctx->r10;
;}
RECOMP_FUNC void AudioThread_QueueCmdF32(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800C538C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800C5390: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800C5394: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x800C5398: jal         0x800C5354
    // 0x800C539C: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    AudioThread_QueueCmd(rdram, ctx);
        goto after_0;
    // 0x800C539C: addiu       $a1, $sp, 0x1C
    ctx->r5 = ADD32(ctx->r29, 0X1C);
    after_0:
    // 0x800C53A0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800C53A4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800C53A8: jr          $ra
    // 0x800C53AC: nop

    return;
    // 0x800C53AC: nop

;}
