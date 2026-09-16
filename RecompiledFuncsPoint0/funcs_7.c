#include "recomp.h"
#include "funcs.h"

RECOMP_FUNC void GameLoad_LoadOverlay(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098208: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009820C: lw          $t6, -0x54DC($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X54DC);
    // 0x80098210: addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // 0x80098214: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80098218: addiu       $t7, $t6, -0x1
    ctx->r15 = ADD32(ctx->r14, -0X1);
    // 0x8009821C: sltiu       $at, $t7, 0x66
    ctx->r1 = ctx->r15 < 0X66 ? 1 : 0;
    // 0x80098220: beq         $at, $zero, L_800983B8
    if (ctx->r1 == 0) {
        // 0x80098224: or          $v0, $zero, $zero
        ctx->r2 = 0 | 0;
            goto L_800983B8;
    }
    // 0x80098224: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x80098228: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009822C: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80098230: addu        $at, $at, $t7
    gpr jr_addend_80098238 = ctx->r15;
    ctx->r1 = ADD32(ctx->r1, ctx->r15);
    // 0x80098234: lw          $t7, -0x4CE0($at)
    ctx->r15 = ADD32(ctx->r1, -0X4CE0);
    // 0x80098238: jr          $t7
    // 0x8009823C: nop

    switch (jr_addend_80098238 >> 2) {
        case 0: goto L_800983B8; break;
        case 1: goto L_80098254; break;
        case 2: goto L_800983B8; break;
        case 3: goto L_800983B8; break;
        case 4: goto L_80098240; break;
        case 5: goto L_800983B8; break;
        case 6: goto L_800983A8; break;
        case 7: goto L_800983B8; break;
        case 8: goto L_800983B8; break;
        case 9: goto L_80098268; break;
        case 10: goto L_800983B8; break;
        case 11: goto L_800983B8; break;
        case 12: goto L_800983B8; break;
        case 13: goto L_800983B8; break;
        case 14: goto L_800983B8; break;
        case 15: goto L_800983B8; break;
        case 16: goto L_800983B8; break;
        case 17: goto L_800983B8; break;
        case 18: goto L_800983B8; break;
        case 19: goto L_80098290; break;
        case 20: goto L_800983B8; break;
        case 21: goto L_800983B8; break;
        case 22: goto L_800983B8; break;
        case 23: goto L_800983B8; break;
        case 24: goto L_800983B8; break;
        case 25: goto L_800983B8; break;
        case 26: goto L_800983B8; break;
        case 27: goto L_800983B8; break;
        case 28: goto L_800983B8; break;
        case 29: goto L_8009827C; break;
        case 30: goto L_800983B8; break;
        case 31: goto L_800983B8; break;
        case 32: goto L_800983B8; break;
        case 33: goto L_800983B8; break;
        case 34: goto L_800983B8; break;
        case 35: goto L_800983B8; break;
        case 36: goto L_800983B8; break;
        case 37: goto L_800983B8; break;
        case 38: goto L_800983B8; break;
        case 39: goto L_800983A8; break;
        case 40: goto L_800983B8; break;
        case 41: goto L_800983B8; break;
        case 42: goto L_800983B8; break;
        case 43: goto L_800983B8; break;
        case 44: goto L_800983B8; break;
        case 45: goto L_800983B8; break;
        case 46: goto L_800983B8; break;
        case 47: goto L_800983B8; break;
        case 48: goto L_800983B8; break;
        case 49: goto L_800982CC; break;
        case 50: goto L_800983B8; break;
        case 51: goto L_800982A4; break;
        case 52: goto L_800983B8; break;
        case 53: goto L_800982B8; break;
        case 54: goto L_800983B8; break;
        case 55: goto L_800982E0; break;
        case 56: goto L_800983B8; break;
        case 57: goto L_800983B8; break;
        case 58: goto L_800983B8; break;
        case 59: goto L_800982F4; break;
        case 60: goto L_800983B8; break;
        case 61: goto L_80098308; break;
        case 62: goto L_800983B8; break;
        case 63: goto L_8009836C; break;
        case 64: goto L_800983B8; break;
        case 65: goto L_8009831C; break;
        case 66: goto L_800983B8; break;
        case 67: goto L_80098330; break;
        case 68: goto L_800983B8; break;
        case 69: goto L_80098358; break;
        case 70: goto L_800983B8; break;
        case 71: goto L_80098344; break;
        case 72: goto L_800983B8; break;
        case 73: goto L_800983B8; break;
        case 74: goto L_800983B8; break;
        case 75: goto L_800983B8; break;
        case 76: goto L_800983B8; break;
        case 77: goto L_800983B8; break;
        case 78: goto L_800983B8; break;
        case 79: goto L_80098380; break;
        case 80: goto L_800983B8; break;
        case 81: goto L_800983B8; break;
        case 82: goto L_800983B8; break;
        case 83: goto L_800983B8; break;
        case 84: goto L_800983B8; break;
        case 85: goto L_800983B8; break;
        case 86: goto L_800983B8; break;
        case 87: goto L_800983B8; break;
        case 88: goto L_800983B8; break;
        case 89: goto L_800983B8; break;
        case 90: goto L_800983B8; break;
        case 91: goto L_800983B8; break;
        case 92: goto L_800983B8; break;
        case 93: goto L_800983B8; break;
        case 94: goto L_800983B8; break;
        case 95: goto L_800983B8; break;
        case 96: goto L_800983B8; break;
        case 97: goto L_800983B8; break;
        case 98: goto L_800983B8; break;
        case 99: goto L_800983B8; break;
        case 100: goto L_800983B8; break;
        case 101: goto L_80098394; break;
        default: switch_error(__func__, 0x80098238, 0x800EB320);
    }
    // 0x8009823C: nop

L_80098240:
    // 0x80098240: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098244: addiu       $t0, $t0, 0x4ED0
    ctx->r8 = ADD32(ctx->r8, 0X4ED0);
    // 0x80098248: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8009824C: b           L_800983B8
    // 0x80098250: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098250: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098254:
    // 0x80098254: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098258: addiu       $t0, $t0, 0x4EF0
    ctx->r8 = ADD32(ctx->r8, 0X4EF0);
    // 0x8009825C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098260: b           L_800983B8
    // 0x80098264: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098264: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098268:
    // 0x80098268: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009826C: addiu       $t0, $t0, 0x4F10
    ctx->r8 = ADD32(ctx->r8, 0X4F10);
    // 0x80098270: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098274: b           L_800983B8
    // 0x80098278: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098278: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_8009827C:
    // 0x8009827C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098280: addiu       $t0, $t0, 0x4F30
    ctx->r8 = ADD32(ctx->r8, 0X4F30);
    // 0x80098284: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098288: b           L_800983B8
    // 0x8009828C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x8009828C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098290:
    // 0x80098290: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098294: addiu       $t0, $t0, 0x4F50
    ctx->r8 = ADD32(ctx->r8, 0X4F50);
    // 0x80098298: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8009829C: b           L_800983B8
    // 0x800982A0: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800982A0: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800982A4:
    // 0x800982A4: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800982A8: addiu       $t0, $t0, 0x4F70
    ctx->r8 = ADD32(ctx->r8, 0X4F70);
    // 0x800982AC: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800982B0: b           L_800983B8
    // 0x800982B4: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800982B4: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800982B8:
    // 0x800982B8: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800982BC: addiu       $t0, $t0, 0x4F90
    ctx->r8 = ADD32(ctx->r8, 0X4F90);
    // 0x800982C0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800982C4: b           L_800983B8
    // 0x800982C8: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800982C8: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800982CC:
    // 0x800982CC: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800982D0: addiu       $t0, $t0, 0x4FB0
    ctx->r8 = ADD32(ctx->r8, 0X4FB0);
    // 0x800982D4: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800982D8: b           L_800983B8
    // 0x800982DC: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800982DC: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800982E0:
    // 0x800982E0: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800982E4: addiu       $t0, $t0, 0x4FD0
    ctx->r8 = ADD32(ctx->r8, 0X4FD0);
    // 0x800982E8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800982EC: b           L_800983B8
    // 0x800982F0: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800982F0: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800982F4:
    // 0x800982F4: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800982F8: addiu       $t0, $t0, 0x4FF0
    ctx->r8 = ADD32(ctx->r8, 0X4FF0);
    // 0x800982FC: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098300: b           L_800983B8
    // 0x80098304: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098304: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098308:
    // 0x80098308: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009830C: addiu       $t0, $t0, 0x5010
    ctx->r8 = ADD32(ctx->r8, 0X5010);
    // 0x80098310: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098314: b           L_800983B8
    // 0x80098318: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098318: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_8009831C:
    // 0x8009831C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098320: addiu       $t0, $t0, 0x5030
    ctx->r8 = ADD32(ctx->r8, 0X5030);
    // 0x80098324: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098328: b           L_800983B8
    // 0x8009832C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x8009832C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098330:
    // 0x80098330: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098334: addiu       $t0, $t0, 0x5050
    ctx->r8 = ADD32(ctx->r8, 0X5050);
    // 0x80098338: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8009833C: b           L_800983B8
    // 0x80098340: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098340: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098344:
    // 0x80098344: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098348: addiu       $t0, $t0, 0x5070
    ctx->r8 = ADD32(ctx->r8, 0X5070);
    // 0x8009834C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098350: b           L_800983B8
    // 0x80098354: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098354: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098358:
    // 0x80098358: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009835C: addiu       $t0, $t0, 0x5090
    ctx->r8 = ADD32(ctx->r8, 0X5090);
    // 0x80098360: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098364: b           L_800983B8
    // 0x80098368: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098368: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_8009836C:
    // 0x8009836C: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098370: addiu       $t0, $t0, 0x50B0
    ctx->r8 = ADD32(ctx->r8, 0X50B0);
    // 0x80098374: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098378: b           L_800983B8
    // 0x8009837C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x8009837C: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098380:
    // 0x80098380: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098384: addiu       $t0, $t0, 0x50D0
    ctx->r8 = ADD32(ctx->r8, 0X50D0);
    // 0x80098388: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8009838C: b           L_800983B8
    // 0x80098390: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x80098390: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_80098394:
    // 0x80098394: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x80098398: addiu       $t0, $t0, 0x50F0
    ctx->r8 = ADD32(ctx->r8, 0X50F0);
    // 0x8009839C: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800983A0: b           L_800983B8
    // 0x800983A4: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
        goto L_800983B8;
    // 0x800983A4: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800983A8:
    // 0x800983A8: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x800983AC: addiu       $t0, $t0, 0x5110
    ctx->r8 = ADD32(ctx->r8, 0X5110);
    // 0x800983B0: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x800983B4: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
L_800983B8:
    // 0x800983B8: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x800983BC: bne         $v0, $at, L_800984BC
    if (ctx->r2 != ctx->r1) {
        // 0x800983C0: lw          $t0, 0x28($sp)
        ctx->r8 = MEM_W(ctx->r29, 0X28);
            goto L_800984BC;
    }
    // 0x800983C0: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x800983C4: lw          $t8, 0x4($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X4);
    // 0x800983C8: lw          $t9, 0x0($t0)
    ctx->r25 = MEM_W(ctx->r8, 0X0);
    // 0x800983CC: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x800983D0: addiu       $a3, $a3, 0x40B8
    ctx->r7 = ADD32(ctx->r7, 0X40B8);
    // 0x800983D4: lw          $t2, 0x8($a3)
    ctx->r10 = MEM_W(ctx->r7, 0X8);
    // 0x800983D8: lw          $t3, 0x10($a3)
    ctx->r11 = MEM_W(ctx->r7, 0X10);
    // 0x800983DC: subu        $v1, $t8, $t9
    ctx->r3 = SUB32(ctx->r24, ctx->r25);
    // 0x800983E0: addiu       $v1, $v1, 0x1
    ctx->r3 = ADD32(ctx->r3, 0X1);
    // 0x800983E4: addiu       $at, $zero, -0x2
    ctx->r1 = ADD32(0, -0X2);
    // 0x800983E8: and         $t1, $v1, $at
    ctx->r9 = ctx->r3 & ctx->r1;
    // 0x800983EC: slt         $at, $t2, $t3
    ctx->r1 = SIGNED(ctx->r10) < SIGNED(ctx->r11) ? 1 : 0;
    // 0x800983F0: bne         $at, $zero, L_8009841C
    if (ctx->r1 != 0) {
        // 0x800983F4: or          $v1, $t1, $zero
        ctx->r3 = ctx->r9 | 0;
            goto L_8009841C;
    }
    // 0x800983F4: or          $v1, $t1, $zero
    ctx->r3 = ctx->r9 | 0;
    // 0x800983F8: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800983FC: addiu       $a1, $a1, 0x1954
    ctx->r5 = ADD32(ctx->r5, 0X1954);
    // 0x80098400: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x80098404: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x80098408: sw          $t1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r9;
    // 0x8009840C: jal         0x800C5C60
    // 0x80098410: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    osRecvMesg_recomp(rdram, ctx);
        goto after_0;
    // 0x80098410: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    after_0:
    // 0x80098414: lw          $v1, 0x2C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X2C);
    // 0x80098418: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
L_8009841C:
    // 0x8009841C: lw          $v0, 0x8($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X8);
    // 0x80098420: lw          $t4, 0xC($t0)
    ctx->r12 = MEM_W(ctx->r8, 0XC);
    // 0x80098424: sw          $t0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r8;
    // 0x80098428: sw          $v1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r3;
    // 0x8009842C: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x80098430: jal         0x800CA480
    // 0x80098434: subu        $a1, $t4, $v0
    ctx->r5 = SUB32(ctx->r12, ctx->r2);
    osInvalICache_recomp(rdram, ctx);
        goto after_1;
    // 0x80098434: subu        $a1, $t4, $v0
    ctx->r5 = SUB32(ctx->r12, ctx->r2);
    after_1:
    // 0x80098438: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x8009843C: lw          $v0, 0x10($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X10);
    // 0x80098440: lw          $t5, 0x14($t0)
    ctx->r13 = MEM_W(ctx->r8, 0X14);
    // 0x80098444: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x80098448: jal         0x800CA2C0
    // 0x8009844C: subu        $a1, $t5, $v0
    ctx->r5 = SUB32(ctx->r13, ctx->r2);
    osInvalDCache_recomp(rdram, ctx);
        goto after_2;
    // 0x8009844C: subu        $a1, $t5, $v0
    ctx->r5 = SUB32(ctx->r13, ctx->r2);
    after_2:
    // 0x80098450: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x80098454: lw          $v1, 0x2C($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X2C);
    // 0x80098458: lui         $t6, 0x802C
    ctx->r14 = S32(0X802C << 16);
    // 0x8009845C: lui         $t7, 0x8015
    ctx->r15 = S32(0X8015 << 16);
    // 0x80098460: lw          $a3, 0x0($t0)
    ctx->r7 = MEM_W(ctx->r8, 0X0);
    // 0x80098464: addiu       $t7, $t7, 0x40B8
    ctx->r15 = ADD32(ctx->r15, 0X40B8);
    // 0x80098468: ori         $t6, $t6, 0x5800
    ctx->r14 = ctx->r14 | 0X5800;
    // 0x8009846C: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x80098470: addiu       $a0, $a0, 0x42A0
    ctx->r4 = ADD32(ctx->r4, 0X42A0);
    // 0x80098474: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x80098478: sw          $t7, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r15;
    // 0x8009847C: or          $a1, $zero, $zero
    ctx->r5 = 0 | 0;
    // 0x80098480: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x80098484: jal         0x800CA370
    // 0x80098488: sw          $v1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r3;
    osPiStartDma_recomp(rdram, ctx);
        goto after_3;
    // 0x80098488: sw          $v1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r3;
    after_3:
    // 0x8009848C: lw          $t0, 0x28($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X28);
    // 0x80098490: lw          $v0, 0x18($t0)
    ctx->r2 = MEM_W(ctx->r8, 0X18);
    // 0x80098494: lw          $t8, 0x1C($t0)
    ctx->r24 = MEM_W(ctx->r8, 0X1C);
    // 0x80098498: or          $a0, $v0, $zero
    ctx->r4 = ctx->r2 | 0;
    // 0x8009849C: jal         0x800CA500
    // 0x800984A0: subu        $a1, $t8, $v0
    ctx->r5 = SUB32(ctx->r24, ctx->r2);
    bzero_recomp(rdram, ctx);
        goto after_4;
    // 0x800984A0: subu        $a1, $t8, $v0
    ctx->r5 = SUB32(ctx->r24, ctx->r2);
    after_4:
    // 0x800984A4: lui         $a0, 0x8015
    ctx->r4 = S32(0X8015 << 16);
    // 0x800984A8: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800984AC: addiu       $a1, $a1, 0x1954
    ctx->r5 = ADD32(ctx->r5, 0X1954);
    // 0x800984B0: addiu       $a0, $a0, 0x40B8
    ctx->r4 = ADD32(ctx->r4, 0X40B8);
    // 0x800984B4: jal         0x800C5C60
    // 0x800984B8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    osRecvMesg_recomp(rdram, ctx);
        goto after_5;
    // 0x800984B8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    after_5:
L_800984BC:
    // 0x800984BC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x800984C0: addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // 0x800984C4: jr          $ra
    // 0x800984C8: nop

    return;
    // 0x800984C8: nop

    // 0x800984CC: nop

;}
RECOMP_FUNC void Math_Fabs(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800984D0: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800984D4: nop

    // 0x800984D8: c.lt.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl < ctx->f4.fl;
    // 0x800984DC: nop

    // 0x800984E0: bc1f        L_800984EC
    if (!c1cs) {
        // 0x800984E4: nop
    
            goto L_800984EC;
    }
    // 0x800984E4: nop

    // 0x800984E8: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
L_800984EC:
    // 0x800984EC: jr          $ra
    // 0x800984F0: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    return;
    // 0x800984F0: mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
;}
RECOMP_FUNC void Math_Vec3f_Set(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800984F4: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x800984F8: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x800984FC: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x80098500: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    // 0x80098504: swc1        $f14, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f14.u32l;
    // 0x80098508: lwc1        $f4, 0xC($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0XC);
    // 0x8009850C: jr          $ra
    // 0x80098510: swc1        $f4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x80098510: swc1        $f4, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void Math_Vec3f_Initialize(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098514: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x80098518: nop

    // 0x8009851C: swc1        $f0, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f0.u32l;
    // 0x80098520: swc1        $f0, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f0.u32l;
    // 0x80098524: jr          $ra
    // 0x80098528: swc1        $f0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f0.u32l;
    return;
    // 0x80098528: swc1        $f0, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f0.u32l;
;}
RECOMP_FUNC void Math_Vec3f_Copy(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009852C: lwc1        $f4, 0x0($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80098530: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    // 0x80098534: lwc1        $f6, 0x4($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80098538: swc1        $f6, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f6.u32l;
    // 0x8009853C: lwc1        $f8, 0x8($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80098540: jr          $ra
    // 0x80098544: swc1        $f8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f8.u32l;
    return;
    // 0x80098544: swc1        $f8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f8.u32l;
    // 0x80098548: lh          $t6, 0x0($a1)
    ctx->r14 = MEM_H(ctx->r5, 0X0);
    // 0x8009854C: sh          $t6, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r14;
    // 0x80098550: lh          $t7, 0x2($a1)
    ctx->r15 = MEM_H(ctx->r5, 0X2);
    // 0x80098554: sh          $t7, 0x2($a0)
    MEM_H(0X2, ctx->r4) = ctx->r15;
    // 0x80098558: lh          $t8, 0x4($a1)
    ctx->r24 = MEM_H(ctx->r5, 0X4);
    // 0x8009855C: jr          $ra
    // 0x80098560: sh          $t8, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r24;
    return;
    // 0x80098560: sh          $t8, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r24;
;}
RECOMP_FUNC void func_80098564(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098564: jr          $ra
    // 0x80098568: nop

    return;
    // 0x80098568: nop

    // 0x8009856C: jr          $ra
    // 0x80098570: nop

    return;
    // 0x80098570: nop

;}
RECOMP_FUNC void func_80098574(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098574: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80098578: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009857C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80098580: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x80098584: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x80098588: jal         0x8009852C
    // 0x8009858C: addiu       $a0, $sp, 0x1C
    ctx->r4 = ADD32(ctx->r29, 0X1C);
    Math_Vec3f_Copy(rdram, ctx);
        goto after_0;
    // 0x8009858C: addiu       $a0, $sp, 0x1C
    ctx->r4 = ADD32(ctx->r29, 0X1C);
    after_0:
    // 0x80098590: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x80098594: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80098598: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009859C: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x800985A0: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x800985A4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x800985A8: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800985AC: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x800985B0: addiu       $a1, $a1, 0x4350
    ctx->r5 = ADD32(ctx->r5, 0X4350);
    // 0x800985B4: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x800985B8: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800985BC: lwc1        $f8, 0x1C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800985C0: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x800985C4: lwc1        $f16, 0x24($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800985C8: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x800985CC: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x800985D0: nop

    // 0x800985D4: addiu       $t8, $v0, 0x400
    ctx->r24 = ADD32(ctx->r2, 0X400);
    // 0x800985D8: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x800985DC: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x800985E0: addu        $v1, $a1, $t0
    ctx->r3 = ADD32(ctx->r5, ctx->r8);
    // 0x800985E4: lwc1        $f6, 0x0($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0X0);
    // 0x800985E8: andi        $t1, $v0, 0xFFF
    ctx->r9 = ctx->r2 & 0XFFF;
    // 0x800985EC: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x800985F0: addu        $a0, $a1, $t2
    ctx->r4 = ADD32(ctx->r5, ctx->r10);
    // 0x800985F4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800985F8: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800985FC: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x80098600: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x80098604: swc1        $f6, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->f6.u32l;
    // 0x80098608: lwc1        $f8, 0x20($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X20);
    // 0x8009860C: swc1        $f8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->f8.u32l;
    // 0x80098610: lwc1        $f18, 0x0($v1)
    ctx->f18.u32l = MEM_W(ctx->r3, 0X0);
    // 0x80098614: lwc1        $f16, 0x24($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80098618: lwc1        $f6, 0x1C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x8009861C: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80098620: mul.s       $f10, $f16, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x80098624: nop

    // 0x80098628: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x8009862C: sub.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f10.fl - ctx->f8.fl;
    // 0x80098630: swc1        $f16, 0x8($a3)
    MEM_W(0X8, ctx->r7) = ctx->f16.u32l;
    // 0x80098634: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80098638: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009863C: jr          $ra
    // 0x80098640: nop

    return;
    // 0x80098640: nop

;}
RECOMP_FUNC void func_80098644(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098644: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80098648: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009864C: or          $a3, $a0, $zero
    ctx->r7 = ctx->r4 | 0;
    // 0x80098650: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x80098654: sw          $a3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r7;
    // 0x80098658: jal         0x8009852C
    // 0x8009865C: addiu       $a0, $sp, 0x1C
    ctx->r4 = ADD32(ctx->r29, 0X1C);
    Math_Vec3f_Copy(rdram, ctx);
        goto after_0;
    // 0x8009865C: addiu       $a0, $sp, 0x1C
    ctx->r4 = ADD32(ctx->r29, 0X1C);
    after_0:
    // 0x80098660: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x80098664: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80098668: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009866C: mtc1        $t6, $f4
    ctx->f4.u32l = ctx->r14;
    // 0x80098670: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80098674: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80098678: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x8009867C: lui         $a1, 0x8015
    ctx->r5 = S32(0X8015 << 16);
    // 0x80098680: addiu       $a1, $a1, 0x4350
    ctx->r5 = ADD32(ctx->r5, 0X4350);
    // 0x80098684: lw          $a3, 0x28($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X28);
    // 0x80098688: div.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f6.fl, ctx->f8.fl);
    // 0x8009868C: lwc1        $f6, 0x24($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80098690: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80098694: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x80098698: lwc1        $f18, 0x20($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X20);
    // 0x8009869C: mfc1        $v0, $f4
    ctx->r2 = (int32_t)ctx->f4.u32l;
    // 0x800986A0: nop

    // 0x800986A4: addiu       $t8, $v0, 0x400
    ctx->r24 = ADD32(ctx->r2, 0X400);
    // 0x800986A8: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x800986AC: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x800986B0: addu        $v1, $a1, $t0
    ctx->r3 = ADD32(ctx->r5, ctx->r8);
    // 0x800986B4: lwc1        $f8, 0x0($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X0);
    // 0x800986B8: andi        $t1, $v0, 0xFFF
    ctx->r9 = ctx->r2 & 0XFFF;
    // 0x800986BC: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x800986C0: addu        $a0, $a1, $t2
    ctx->r4 = ADD32(ctx->r5, ctx->r10);
    // 0x800986C4: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800986C8: lwc1        $f16, 0x0($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800986CC: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x800986D0: sub.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl - ctx->f4.fl;
    // 0x800986D4: swc1        $f6, 0x8($a3)
    MEM_W(0X8, ctx->r7) = ctx->f6.u32l;
    // 0x800986D8: lwc1        $f16, 0x20($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800986DC: lwc1        $f8, 0x0($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X0);
    // 0x800986E0: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800986E4: lwc1        $f10, 0x24($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X24);
    // 0x800986E8: mul.s       $f18, $f8, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f16.fl);
    // 0x800986EC: nop

    // 0x800986F0: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x800986F4: add.s       $f8, $f18, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f18.fl + ctx->f6.fl;
    // 0x800986F8: swc1        $f8, 0x4($a3)
    MEM_W(0X4, ctx->r7) = ctx->f8.u32l;
    // 0x800986FC: lwc1        $f16, 0x1C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x80098700: swc1        $f16, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->f16.u32l;
    // 0x80098704: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80098708: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009870C: jr          $ra
    // 0x80098710: nop

    return;
    // 0x80098710: nop

;}
RECOMP_FUNC void func_80098714(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098714: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80098718: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x8009871C: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x80098720: mtc1        $a1, $f14
    ctx->f14.u32l = ctx->r5;
    // 0x80098724: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098728: c.lt.s      $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f0.fl < ctx->f12.fl;
    // 0x8009872C: nop

    // 0x80098730: bc1fl       L_80098740
    if (!c1cs) {
        // 0x80098734: lwc1        $f0, 0x0($a0)
        ctx->f0.u32l = MEM_W(ctx->r4, 0X0);
            goto L_80098740;
    }
    goto skip_0;
    // 0x80098734: lwc1        $f0, 0x0($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X0);
    skip_0:
    // 0x80098738: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x8009873C: lwc1        $f0, 0x0($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X0);
L_80098740:
    // 0x80098740: sub.s       $f4, $f14, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f14.fl - ctx->f0.fl;
    // 0x80098744: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80098748: add.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f0.fl;
    // 0x8009874C: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
    // 0x80098750: lwc1        $f10, 0x0($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80098754: c.eq.s      $f14, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f14.fl == ctx->f10.fl;
    // 0x80098758: nop

    // 0x8009875C: bc1f        L_8009876C
    if (!c1cs) {
        // 0x80098760: nop
    
            goto L_8009876C;
    }
    // 0x80098760: nop

    // 0x80098764: jr          $ra
    // 0x80098768: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x80098768: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_8009876C:
    // 0x8009876C: jr          $ra
    // 0x80098770: nop

    return;
    // 0x80098770: nop

;}
RECOMP_FUNC void func_80098774(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098774: sll         $t6, $a1, 16
    ctx->r14 = S32(ctx->r5 << 16);
    // 0x80098778: sll         $t8, $a2, 16
    ctx->r24 = S32(ctx->r6 << 16);
    // 0x8009877C: sra         $t9, $t8, 16
    ctx->r25 = S32(SIGNED(ctx->r24) >> 16);
    // 0x80098780: sra         $t7, $t6, 16
    ctx->r15 = S32(SIGNED(ctx->r14) >> 16);
    // 0x80098784: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    // 0x80098788: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x8009878C: or          $a2, $t9, $zero
    ctx->r6 = ctx->r25 | 0;
    // 0x80098790: or          $a1, $t7, $zero
    ctx->r5 = ctx->r15 | 0;
    // 0x80098794: bne         $t9, $zero, L_800987A4
    if (ctx->r25 != 0) {
        // 0x80098798: lh          $v0, 0x0($a0)
        ctx->r2 = MEM_H(ctx->r4, 0X0);
            goto L_800987A4;
    }
    // 0x80098798: lh          $v0, 0x0($a0)
    ctx->r2 = MEM_H(ctx->r4, 0X0);
    // 0x8009879C: b           L_80098800
    // 0x800987A0: sh          $a1, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r5;
        goto L_80098800;
    // 0x800987A0: sh          $a1, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r5;
L_800987A4:
    // 0x800987A4: subu        $v0, $v0, $a1
    ctx->r2 = SUB32(ctx->r2, ctx->r5);
    // 0x800987A8: sll         $t0, $v0, 16
    ctx->r8 = S32(ctx->r2 << 16);
    // 0x800987AC: sra         $t1, $t0, 16
    ctx->r9 = S32(SIGNED(ctx->r8) >> 16);
    // 0x800987B0: div         $zero, $t1, $a2
    lo = S32(S64(S32(ctx->r9)) / S64(S32(ctx->r6))); hi = S32(S64(S32(ctx->r9)) % S64(S32(ctx->r6)));
    // 0x800987B4: or          $v0, $t1, $zero
    ctx->r2 = ctx->r9 | 0;
    // 0x800987B8: bne         $a2, $zero, L_800987C4
    if (ctx->r6 != 0) {
        // 0x800987BC: nop
    
            goto L_800987C4;
    }
    // 0x800987BC: nop

    // 0x800987C0: break       7
    do_break(2148108224);
L_800987C4:
    // 0x800987C4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x800987C8: bne         $a2, $at, L_800987DC
    if (ctx->r6 != ctx->r1) {
        // 0x800987CC: lui         $at, 0x8000
        ctx->r1 = S32(0X8000 << 16);
            goto L_800987DC;
    }
    // 0x800987CC: lui         $at, 0x8000
    ctx->r1 = S32(0X8000 << 16);
    // 0x800987D0: bne         $v0, $at, L_800987DC
    if (ctx->r2 != ctx->r1) {
        // 0x800987D4: nop
    
            goto L_800987DC;
    }
    // 0x800987D4: nop

    // 0x800987D8: break       6
    do_break(2148108248);
L_800987DC:
    // 0x800987DC: mflo        $t2
    ctx->r10 = lo;
    // 0x800987E0: subu        $v0, $v0, $t2
    ctx->r2 = SUB32(ctx->r2, ctx->r10);
    // 0x800987E4: sll         $t3, $v0, 16
    ctx->r11 = S32(ctx->r2 << 16);
    // 0x800987E8: sra         $t4, $t3, 16
    ctx->r12 = S32(SIGNED(ctx->r11) >> 16);
    // 0x800987EC: addu        $v0, $t4, $a1
    ctx->r2 = ADD32(ctx->r12, ctx->r5);
    // 0x800987F0: sll         $t5, $v0, 16
    ctx->r13 = S32(ctx->r2 << 16);
    // 0x800987F4: sra         $t6, $t5, 16
    ctx->r14 = S32(SIGNED(ctx->r13) >> 16);
    // 0x800987F8: or          $v0, $t6, $zero
    ctx->r2 = ctx->r14 | 0;
    // 0x800987FC: sh          $t6, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r14;
L_80098800:
    // 0x80098800: lh          $t7, 0x0($a0)
    ctx->r15 = MEM_H(ctx->r4, 0X0);
    // 0x80098804: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x80098808: bne         $a1, $t7, L_80098818
    if (ctx->r5 != ctx->r15) {
        // 0x8009880C: nop
    
            goto L_80098818;
    }
    // 0x8009880C: nop

    // 0x80098810: jr          $ra
    // 0x80098814: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x80098814: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_80098818:
    // 0x80098818: jr          $ra
    // 0x8009881C: nop

    return;
    // 0x8009881C: nop

;}
RECOMP_FUNC void func_80098820(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098820: mtc1        $a2, $f14
    ctx->f14.u32l = ctx->r6;
    // 0x80098824: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x80098828: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x8009882C: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80098830: c.lt.s      $f14, $f2
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f14.fl < ctx->f2.fl;
    // 0x80098834: lui         $at, 0xBF80
    ctx->r1 = S32(0XBF80 << 16);
    // 0x80098838: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
    // 0x8009883C: sub.s       $f0, $f12, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f0.fl = ctx->f12.fl - ctx->f4.fl;
    // 0x80098840: bc1fl       L_8009885C
    if (!c1cs) {
        // 0x80098844: c.lt.s      $f2, $f0
        CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
            goto L_8009885C;
    }
    goto skip_0;
    // 0x80098844: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    skip_0:
    // 0x80098848: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009884C: nop

    // 0x80098850: mul.s       $f14, $f6, $f14
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f14.fl = MUL_S(ctx->f6.fl, ctx->f14.fl);
    // 0x80098854: nop

    // 0x80098858: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
L_8009885C:
    // 0x8009885C: nop

    // 0x80098860: bc1fl       L_80098894
    if (!c1cs) {
        // 0x80098864: add.s       $f0, $f0, $f14
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f0.fl + ctx->f14.fl;
            goto L_80098894;
    }
    goto skip_1;
    // 0x80098864: add.s       $f0, $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f0.fl + ctx->f14.fl;
    skip_1:
    // 0x80098868: sub.s       $f0, $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f0.fl - ctx->f14.fl;
    // 0x8009886C: c.lt.s      $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f2.fl < ctx->f0.fl;
    // 0x80098870: nop

    // 0x80098874: bc1f        L_80098888
    if (!c1cs) {
        // 0x80098878: nop
    
            goto L_80098888;
    }
    // 0x80098878: nop

    // 0x8009887C: sub.s       $f8, $f12, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = ctx->f12.fl - ctx->f0.fl;
    // 0x80098880: b           L_800988B4
    // 0x80098884: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
        goto L_800988B4;
    // 0x80098884: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
L_80098888:
    // 0x80098888: b           L_800988B4
    // 0x8009888C: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
        goto L_800988B4;
    // 0x8009888C: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    // 0x80098890: add.s       $f0, $f0, $f14
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f0.fl = ctx->f0.fl + ctx->f14.fl;
L_80098894:
    // 0x80098894: c.lt.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
    // 0x80098898: nop

    // 0x8009889C: bc1fl       L_800988B4
    if (!c1cs) {
        // 0x800988A0: swc1        $f12, 0x0($a0)
        MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
            goto L_800988B4;
    }
    goto skip_2;
    // 0x800988A0: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    skip_2:
    // 0x800988A4: sub.s       $f10, $f12, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f12.fl - ctx->f0.fl;
    // 0x800988A8: b           L_800988B4
    // 0x800988AC: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
        goto L_800988B4;
    // 0x800988AC: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
    // 0x800988B0: swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
L_800988B4:
    // 0x800988B4: lwc1        $f16, 0x0($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X0);
    // 0x800988B8: c.eq.s      $f12, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    c1cs = ctx->f12.fl == ctx->f16.fl;
    // 0x800988BC: nop

    // 0x800988C0: bc1f        L_800988D0
    if (!c1cs) {
        // 0x800988C4: nop
    
            goto L_800988D0;
    }
    // 0x800988C4: nop

    // 0x800988C8: jr          $ra
    // 0x800988CC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    return;
    // 0x800988CC: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
L_800988D0:
    // 0x800988D0: jr          $ra
    // 0x800988D4: nop

    return;
    // 0x800988D4: nop

;}
RECOMP_FUNC void func_800988D8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800988D8: sll         $v0, $a0, 1
    ctx->r2 = S32(ctx->r4 << 1);
    // 0x800988DC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800988E0: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x800988E4: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x800988E8: sh          $zero, -0x1018($at)
    MEM_H(-0X1018, ctx->r1) = 0;
    // 0x800988EC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x800988F0: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x800988F4: addu        $at, $at, $t6
    ctx->r1 = ADD32(ctx->r1, ctx->r14);
    // 0x800988F8: swc1        $f4, -0x1020($at)
    MEM_W(-0X1020, ctx->r1) = ctx->f4.u32l;
    // 0x800988FC: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80098900: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x80098904: sh          $zero, -0x1014($at)
    MEM_H(-0X1014, ctx->r1) = 0;
    // 0x80098908: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009890C: addu        $at, $at, $a0
    ctx->r1 = ADD32(ctx->r1, ctx->r4);
    // 0x80098910: jr          $ra
    // 0x80098914: sb          $zero, -0x1010($at)
    MEM_B(-0X1010, ctx->r1) = 0;
    return;
    // 0x80098914: sb          $zero, -0x1010($at)
    MEM_B(-0X1010, ctx->r1) = 0;
;}
RECOMP_FUNC void func_80098918(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098918: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x8009891C: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x80098920: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80098924: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x80098928: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x8009892C: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x80098930: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x80098934: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x80098938: lui         $t7, 0x8019
    ctx->r15 = S32(0X8019 << 16);
    // 0x8009893C: addiu       $t7, $t7, 0x2690
    ctx->r15 = ADD32(ctx->r15, 0X2690);
    // 0x80098940: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80098944: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x80098948: lwc1        $f0, 0x6C($v0)
    ctx->f0.u32l = MEM_W(ctx->r2, 0X6C);
    // 0x8009894C: lwc1        $f2, 0x74($v0)
    ctx->f2.u32l = MEM_W(ctx->r2, 0X74);
    // 0x80098950: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80098954: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80098958: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009895C: sw          $v0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r2;
    // 0x80098960: mul.s       $f6, $f2, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x80098964: jal         0x800C7010
    // 0x80098968: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80098968: add.s       $f12, $f4, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f12.fl = ctx->f4.fl + ctx->f6.fl;
    after_0:
    // 0x8009896C: lw          $v0, 0x1C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X1C);
    // 0x80098970: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x80098974: jal         0x801ED154
    // 0x80098978: lwc1        $f12, 0x70($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X70);
    func_801ED154(rdram, ctx);
        goto after_1;
    // 0x80098978: lwc1        $f12, 0x70($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X70);
    after_1:
    // 0x8009897C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80098980: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x80098984: jr          $ra
    // 0x80098988: nop

    return;
    // 0x80098988: nop

;}
RECOMP_FUNC void func_8009898C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009898C: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x80098990: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x80098994: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80098998: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x8009899C: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800989A0: addu        $t6, $t6, $a0
    ctx->r14 = ADD32(ctx->r14, ctx->r4);
    // 0x800989A4: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800989A8: subu        $t6, $t6, $a0
    ctx->r14 = SUB32(ctx->r14, ctx->r4);
    // 0x800989AC: lui         $t7, 0x8019
    ctx->r15 = S32(0X8019 << 16);
    // 0x800989B0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x800989B4: addiu       $t7, $t7, 0x2690
    ctx->r15 = ADD32(ctx->r15, 0X2690);
    // 0x800989B8: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800989BC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x800989C0: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x800989C4: lwc1        $f12, 0x6C($v0)
    ctx->f12.u32l = MEM_W(ctx->r2, 0X6C);
    // 0x800989C8: jal         0x801ED154
    // 0x800989CC: lwc1        $f14, 0x74($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X74);
    func_801ED154(rdram, ctx);
        goto after_0;
    // 0x800989CC: lwc1        $f14, 0x74($v0)
    ctx->f14.u32l = MEM_W(ctx->r2, 0X74);
    after_0:
    // 0x800989D0: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x800989D4: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x800989D8: jr          $ra
    // 0x800989DC: nop

    return;
    // 0x800989DC: nop

;}
RECOMP_FUNC void func_800989E0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800989E0: sll         $t6, $a1, 2
    ctx->r14 = S32(ctx->r5 << 2);
    // 0x800989E4: subu        $t6, $t6, $a1
    ctx->r14 = SUB32(ctx->r14, ctx->r5);
    // 0x800989E8: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800989EC: subu        $t6, $t6, $a1
    ctx->r14 = SUB32(ctx->r14, ctx->r5);
    // 0x800989F0: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x800989F4: addu        $t6, $t6, $a1
    ctx->r14 = ADD32(ctx->r14, ctx->r5);
    // 0x800989F8: sll         $t6, $t6, 2
    ctx->r14 = S32(ctx->r14 << 2);
    // 0x800989FC: subu        $t6, $t6, $a1
    ctx->r14 = SUB32(ctx->r14, ctx->r5);
    // 0x80098A00: lui         $t7, 0x8019
    ctx->r15 = S32(0X8019 << 16);
    // 0x80098A04: addiu       $t7, $t7, 0x2690
    ctx->r15 = ADD32(ctx->r15, 0X2690);
    // 0x80098A08: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80098A0C: addu        $v0, $t6, $t7
    ctx->r2 = ADD32(ctx->r14, ctx->r15);
    // 0x80098A10: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x80098A14: lwc1        $f6, 0xB78($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0XB78);
    // 0x80098A18: lwc1        $f4, 0x0($a0)
    ctx->f4.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80098A1C: mtc1        $a3, $f14
    ctx->f14.u32l = ctx->r7;
    // 0x80098A20: mul.s       $f8, $f6, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x80098A24: lwc1        $f16, 0x4($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X4);
    // 0x80098A28: add.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x80098A2C: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
    // 0x80098A30: lwc1        $f18, 0xB7C($v0)
    ctx->f18.u32l = MEM_W(ctx->r2, 0XB7C);
    // 0x80098A34: mul.s       $f6, $f18, $f14
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f14.fl);
    // 0x80098A38: add.s       $f4, $f16, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f6.fl;
    // 0x80098A3C: lwc1        $f16, 0x8($a0)
    ctx->f16.u32l = MEM_W(ctx->r4, 0X8);
    // 0x80098A40: swc1        $f4, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f4.u32l;
    // 0x80098A44: lwc1        $f10, 0x10($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X10);
    // 0x80098A48: lwc1        $f8, 0xB80($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XB80);
    // 0x80098A4C: mul.s       $f18, $f8, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80098A50: add.s       $f6, $f16, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f6.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x80098A54: jr          $ra
    // 0x80098A58: swc1        $f6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f6.u32l;
    return;
    // 0x80098A58: swc1        $f6, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f6.u32l;
;}
RECOMP_FUNC void func_80098A5C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098A5C: jr          $ra
    // 0x80098A60: nop

    return;
    // 0x80098A60: nop

;}
RECOMP_FUNC void func_80098A64(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098A64: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80098A68: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80098A6C: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80098A70: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80098A74: lui         $s0, 0x801D
    ctx->r16 = S32(0X801D << 16);
    // 0x80098A78: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80098A7C: lui         $s2, 0x801D
    ctx->r18 = S32(0X801D << 16);
    // 0x80098A80: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80098A84: addiu       $s2, $s2, -0xF9C
    ctx->r18 = ADD32(ctx->r18, -0XF9C);
    // 0x80098A88: addiu       $s1, $s1, -0x1008
    ctx->r17 = ADD32(ctx->r17, -0X1008);
    // 0x80098A8C: addiu       $s0, $s0, -0xFFC
    ctx->r16 = ADD32(ctx->r16, -0XFFC);
L_80098A90:
    // 0x80098A90: jal         0x80098514
    // 0x80098A94: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    Math_Vec3f_Initialize(rdram, ctx);
        goto after_0;
    // 0x80098A94: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    after_0:
    // 0x80098A98: jal         0x80098514
    // 0x80098A9C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    Math_Vec3f_Initialize(rdram, ctx);
        goto after_1;
    // 0x80098A9C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x80098AA0: addiu       $s0, $s0, 0x18
    ctx->r16 = ADD32(ctx->r16, 0X18);
    // 0x80098AA4: bne         $s0, $s2, L_80098A90
    if (ctx->r16 != ctx->r18) {
        // 0x80098AA8: addiu       $s1, $s1, 0x18
        ctx->r17 = ADD32(ctx->r17, 0X18);
            goto L_80098A90;
    }
    // 0x80098AA8: addiu       $s1, $s1, 0x18
    ctx->r17 = ADD32(ctx->r17, 0X18);
    // 0x80098AAC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80098AB0: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80098AB4: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80098AB8: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80098ABC: jr          $ra
    // 0x80098AC0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x80098AC0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_80098AC4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098AC4: addiu       $sp, $sp, -0x48
    ctx->r29 = ADD32(ctx->r29, -0X48);
    // 0x80098AC8: sw          $s2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r18;
    // 0x80098ACC: sw          $s1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r17;
    // 0x80098AD0: sdc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    SD(ctx->f20.u64, 0X18, ctx->r29);
    // 0x80098AD4: sw          $fp, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r30;
    // 0x80098AD8: sw          $s7, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r23;
    // 0x80098ADC: sw          $s6, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r22;
    // 0x80098AE0: sw          $s5, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r21;
    // 0x80098AE4: sw          $s4, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r20;
    // 0x80098AE8: sw          $s3, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r19;
    // 0x80098AEC: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x80098AF0: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80098AF4: lui         $s2, 0x8019
    ctx->r18 = S32(0X8019 << 16);
    // 0x80098AF8: mtc1        $zero, $f20
    ctx->f20.u32l = 0;
    // 0x80098AFC: andi        $s4, $a0, 0xFF
    ctx->r20 = ctx->r4 & 0XFF;
    // 0x80098B00: andi        $s5, $a1, 0xFF
    ctx->r21 = ctx->r5 & 0XFF;
    // 0x80098B04: andi        $s6, $a2, 0xFF
    ctx->r22 = ctx->r6 & 0XFF;
    // 0x80098B08: andi        $s7, $a3, 0xFF
    ctx->r23 = ctx->r7 & 0XFF;
    // 0x80098B0C: sw          $ra, 0x44($sp)
    MEM_W(0X44, ctx->r29) = ctx->r31;
    // 0x80098B10: sw          $a0, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->r4;
    // 0x80098B14: sw          $a1, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->r5;
    // 0x80098B18: sw          $a2, 0x50($sp)
    MEM_W(0X50, ctx->r29) = ctx->r6;
    // 0x80098B1C: sw          $a3, 0x54($sp)
    MEM_W(0X54, ctx->r29) = ctx->r7;
    // 0x80098B20: addiu       $s2, $s2, 0x2690
    ctx->r18 = ADD32(ctx->r18, 0X2690);
    // 0x80098B24: addiu       $s1, $s1, -0x1008
    ctx->r17 = ADD32(ctx->r17, -0X1008);
    // 0x80098B28: or          $s0, $zero, $zero
    ctx->r16 = 0 | 0;
    // 0x80098B2C: addiu       $s3, $zero, 0x1718
    ctx->r19 = ADD32(0, 0X1718);
    // 0x80098B30: lbu         $fp, 0x5B($sp)
    ctx->r30 = MEM_BU(ctx->r29, 0X5B);
L_80098B34:
    // 0x80098B34: beq         $s4, $zero, L_80098B50
    if (ctx->r20 == 0) {
        // 0x80098B38: nop
    
            goto L_80098B50;
    }
    // 0x80098B38: nop

    // 0x80098B3C: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098B40: mflo        $t6
    ctx->r14 = lo;
    // 0x80098B44: addu        $t7, $s2, $t6
    ctx->r15 = ADD32(ctx->r18, ctx->r14);
    // 0x80098B48: lwc1        $f4, 0x44($t7)
    ctx->f4.u32l = MEM_W(ctx->r15, 0X44);
    // 0x80098B4C: swc1        $f4, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->f4.u32l;
L_80098B50:
    // 0x80098B50: beq         $s5, $zero, L_80098B6C
    if (ctx->r21 == 0) {
        // 0x80098B54: nop
    
            goto L_80098B6C;
    }
    // 0x80098B54: nop

    // 0x80098B58: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098B5C: mflo        $t8
    ctx->r24 = lo;
    // 0x80098B60: addu        $t9, $s2, $t8
    ctx->r25 = ADD32(ctx->r18, ctx->r24);
    // 0x80098B64: lwc1        $f6, 0x48($t9)
    ctx->f6.u32l = MEM_W(ctx->r25, 0X48);
    // 0x80098B68: swc1        $f6, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->f6.u32l;
L_80098B6C:
    // 0x80098B6C: beq         $s6, $zero, L_80098B88
    if (ctx->r22 == 0) {
        // 0x80098B70: nop
    
            goto L_80098B88;
    }
    // 0x80098B70: nop

    // 0x80098B74: multu       $s0, $s3
    result = U64(U32(ctx->r16)) * U64(U32(ctx->r19)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098B78: mflo        $t0
    ctx->r8 = lo;
    // 0x80098B7C: addu        $t1, $s2, $t0
    ctx->r9 = ADD32(ctx->r18, ctx->r8);
    // 0x80098B80: lwc1        $f8, 0x4C($t1)
    ctx->f8.u32l = MEM_W(ctx->r9, 0X4C);
    // 0x80098B84: swc1        $f8, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->f8.u32l;
L_80098B88:
    // 0x80098B88: beql        $s7, $zero, L_80098BA4
    if (ctx->r23 == 0) {
        // 0x80098B8C: swc1        $f20, 0xC($s1)
        MEM_W(0XC, ctx->r17) = ctx->f20.u32l;
            goto L_80098BA4;
    }
    goto skip_0;
    // 0x80098B8C: swc1        $f20, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f20.u32l;
    skip_0:
    // 0x80098B90: jal         0x80098918
    // 0x80098B94: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_80098918(rdram, ctx);
        goto after_0;
    // 0x80098B94: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_0:
    // 0x80098B98: b           L_80098BA4
    // 0x80098B9C: swc1        $f0, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f0.u32l;
        goto L_80098BA4;
    // 0x80098B9C: swc1        $f0, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f0.u32l;
    // 0x80098BA0: swc1        $f20, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f20.u32l;
L_80098BA4:
    // 0x80098BA4: beql        $fp, $zero, L_80098BBC
    if (ctx->r30 == 0) {
        // 0x80098BA8: addiu       $s0, $s0, 0x1
        ctx->r16 = ADD32(ctx->r16, 0X1);
            goto L_80098BBC;
    }
    goto skip_1;
    // 0x80098BA8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
    skip_1:
    // 0x80098BAC: jal         0x8009898C
    // 0x80098BB0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    func_8009898C(rdram, ctx);
        goto after_1;
    // 0x80098BB0: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    after_1:
    // 0x80098BB4: swc1        $f0, 0x10($s1)
    MEM_W(0X10, ctx->r17) = ctx->f0.u32l;
    // 0x80098BB8: addiu       $s0, $s0, 0x1
    ctx->r16 = ADD32(ctx->r16, 0X1);
L_80098BBC:
    // 0x80098BBC: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x80098BC0: bne         $s0, $at, L_80098B34
    if (ctx->r16 != ctx->r1) {
        // 0x80098BC4: addiu       $s1, $s1, 0x18
        ctx->r17 = ADD32(ctx->r17, 0X18);
            goto L_80098B34;
    }
    // 0x80098BC4: addiu       $s1, $s1, 0x18
    ctx->r17 = ADD32(ctx->r17, 0X18);
    // 0x80098BC8: lw          $ra, 0x44($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X44);
    // 0x80098BCC: ldc1        $f20, 0x18($sp)
    CHECK_FR(ctx, 20);
    ctx->f20.u64 = LD(ctx->r29, 0X18);
    // 0x80098BD0: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x80098BD4: lw          $s1, 0x24($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X24);
    // 0x80098BD8: lw          $s2, 0x28($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X28);
    // 0x80098BDC: lw          $s3, 0x2C($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X2C);
    // 0x80098BE0: lw          $s4, 0x30($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X30);
    // 0x80098BE4: lw          $s5, 0x34($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X34);
    // 0x80098BE8: lw          $s6, 0x38($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X38);
    // 0x80098BEC: lw          $s7, 0x3C($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X3C);
    // 0x80098BF0: lw          $fp, 0x40($sp)
    ctx->r30 = MEM_W(ctx->r29, 0X40);
    // 0x80098BF4: jr          $ra
    // 0x80098BF8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
    return;
    // 0x80098BF8: addiu       $sp, $sp, 0x48
    ctx->r29 = ADD32(ctx->r29, 0X48);
;}
RECOMP_FUNC void func_80098BFC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098BFC: jr          $ra
    // 0x80098C00: nop

    return;
    // 0x80098C00: nop

;}
RECOMP_FUNC void func_80098C04(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098C04: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x80098C08: sll         $t6, $a2, 24
    ctx->r14 = S32(ctx->r6 << 24);
    // 0x80098C0C: sra         $t7, $t6, 24
    ctx->r15 = S32(SIGNED(ctx->r14) >> 24);
    // 0x80098C10: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x80098C14: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80098C18: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x80098C1C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80098C20: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x80098C24: sw          $a2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r6;
    // 0x80098C28: beq         $t7, $at, L_80098C50
    if (ctx->r15 == ctx->r1) {
        // 0x80098C2C: or          $a3, $a1, $zero
        ctx->r7 = ctx->r5 | 0;
            goto L_80098C50;
    }
    // 0x80098C2C: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x80098C30: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x80098C34: beq         $t7, $at, L_80098D50
    if (ctx->r15 == ctx->r1) {
        // 0x80098C38: sll         $t6, $a3, 2
        ctx->r14 = S32(ctx->r7 << 2);
            goto L_80098D50;
    }
    // 0x80098C38: sll         $t6, $a3, 2
    ctx->r14 = S32(ctx->r7 << 2);
    // 0x80098C3C: addiu       $at, $zero, 0x3
    ctx->r1 = ADD32(0, 0X3);
    // 0x80098C40: beq         $t7, $at, L_80098CDC
    if (ctx->r15 == ctx->r1) {
        // 0x80098C44: sll         $t2, $a3, 2
        ctx->r10 = S32(ctx->r7 << 2);
            goto L_80098CDC;
    }
    // 0x80098C44: sll         $t2, $a3, 2
    ctx->r10 = S32(ctx->r7 << 2);
    // 0x80098C48: b           L_80098DD0
    // 0x80098C4C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_80098DD0;
    // 0x80098C4C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_80098C50:
    // 0x80098C50: sll         $t8, $a3, 2
    ctx->r24 = S32(ctx->r7 << 2);
    // 0x80098C54: subu        $t8, $t8, $a3
    ctx->r24 = SUB32(ctx->r24, ctx->r7);
    // 0x80098C58: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80098C5C: addiu       $t9, $t9, -0x1008
    ctx->r25 = ADD32(ctx->r25, -0X1008);
    // 0x80098C60: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x80098C64: addu        $s1, $t8, $t9
    ctx->r17 = ADD32(ctx->r24, ctx->r25);
    // 0x80098C68: lwc1        $f4, 0x10($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X10);
    // 0x80098C6C: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80098C70: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80098C74: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80098C78: mfc1        $a2, $f6
    ctx->r6 = (int32_t)ctx->f6.u32l;
    // 0x80098C7C: jal         0x80098574
    // 0x80098C80: nop

    func_80098574(rdram, ctx);
        goto after_0;
    // 0x80098C80: nop

    after_0:
    // 0x80098C84: lwc1        $f8, 0x0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X0);
    // 0x80098C88: lwc1        $f10, 0x0($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0X0);
    // 0x80098C8C: lui         $t1, 0x8019
    ctx->r9 = S32(0X8019 << 16);
    // 0x80098C90: lwc1        $f4, 0x4($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X4);
    // 0x80098C94: add.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x80098C98: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80098C9C: swc1        $f16, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f16.u32l;
    // 0x80098CA0: lw          $t1, 0x2458($t1)
    ctx->r9 = MEM_W(ctx->r9, 0X2458);
    // 0x80098CA4: lwc1        $f6, 0x4($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X4);
    // 0x80098CA8: lwc1        $f16, -0x4B40($at)
    ctx->f16.u32l = MEM_W(ctx->r1, -0X4B40);
    // 0x80098CAC: mtc1        $t1, $f18
    ctx->f18.u32l = ctx->r9;
    // 0x80098CB0: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80098CB4: lwc1        $f6, 0x8($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X8);
    // 0x80098CB8: cvt.s.w     $f0, $f18
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    ctx->f0.fl = CVT_S_W(ctx->f18.u32l);
    // 0x80098CBC: sub.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = ctx->f8.fl - ctx->f0.fl;
    // 0x80098CC0: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x80098CC4: add.s       $f4, $f18, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f0.fl;
    // 0x80098CC8: swc1        $f4, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f4.u32l;
    // 0x80098CCC: lwc1        $f8, 0x8($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X8);
    // 0x80098CD0: add.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80098CD4: b           L_80098DCC
    // 0x80098CD8: swc1        $f10, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f10.u32l;
        goto L_80098DCC;
    // 0x80098CD8: swc1        $f10, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f10.u32l;
L_80098CDC:
    // 0x80098CDC: subu        $t2, $t2, $a3
    ctx->r10 = SUB32(ctx->r10, ctx->r7);
    // 0x80098CE0: lui         $t3, 0x801D
    ctx->r11 = S32(0X801D << 16);
    // 0x80098CE4: addiu       $t3, $t3, -0x1008
    ctx->r11 = ADD32(ctx->r11, -0X1008);
    // 0x80098CE8: sll         $t2, $t2, 3
    ctx->r10 = S32(ctx->r10 << 3);
    // 0x80098CEC: addu        $s1, $t2, $t3
    ctx->r17 = ADD32(ctx->r10, ctx->r11);
    // 0x80098CF0: lwc1        $f16, 0x10($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X10);
    // 0x80098CF4: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80098CF8: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80098CFC: trunc.w.s   $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x80098D00: mfc1        $a2, $f18
    ctx->r6 = (int32_t)ctx->f18.u32l;
    // 0x80098D04: jal         0x80098574
    // 0x80098D08: nop

    func_80098574(rdram, ctx);
        goto after_1;
    // 0x80098D08: nop

    after_1:
    // 0x80098D0C: lwc1        $f4, 0x0($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0X0);
    // 0x80098D10: lwc1        $f6, 0x0($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X0);
    // 0x80098D14: lui         $t5, 0x8019
    ctx->r13 = S32(0X8019 << 16);
    // 0x80098D18: lwc1        $f10, 0x4($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X4);
    // 0x80098D1C: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80098D20: lwc1        $f6, 0x8($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X8);
    // 0x80098D24: swc1        $f8, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f8.u32l;
    // 0x80098D28: lw          $t5, 0x2458($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X2458);
    // 0x80098D2C: mtc1        $t5, $f16
    ctx->f16.u32l = ctx->r13;
    // 0x80098D30: nop

    // 0x80098D34: cvt.s.w     $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    ctx->f18.fl = CVT_S_W(ctx->f16.u32l);
    // 0x80098D38: add.s       $f4, $f10, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f10.fl + ctx->f18.fl;
    // 0x80098D3C: swc1        $f4, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f4.u32l;
    // 0x80098D40: lwc1        $f8, 0x8($s1)
    ctx->f8.u32l = MEM_W(ctx->r17, 0X8);
    // 0x80098D44: add.s       $f16, $f6, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f8.fl;
    // 0x80098D48: b           L_80098DCC
    // 0x80098D4C: swc1        $f16, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f16.u32l;
        goto L_80098DCC;
    // 0x80098D4C: swc1        $f16, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f16.u32l;
L_80098D50:
    // 0x80098D50: subu        $t6, $t6, $a3
    ctx->r14 = SUB32(ctx->r14, ctx->r7);
    // 0x80098D54: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80098D58: addiu       $t7, $t7, -0x1008
    ctx->r15 = ADD32(ctx->r15, -0X1008);
    // 0x80098D5C: sll         $t6, $t6, 3
    ctx->r14 = S32(ctx->r14 << 3);
    // 0x80098D60: addu        $s1, $t6, $t7
    ctx->r17 = ADD32(ctx->r14, ctx->r15);
    // 0x80098D64: lwc1        $f10, 0xC($s1)
    ctx->f10.u32l = MEM_W(ctx->r17, 0XC);
    // 0x80098D68: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80098D6C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80098D70: trunc.w.s   $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.u32l = TRUNC_W_S(ctx->f10.fl);
    // 0x80098D74: mfc1        $a2, $f18
    ctx->r6 = (int32_t)ctx->f18.u32l;
    // 0x80098D78: jal         0x80098644
    // 0x80098D7C: nop

    func_80098644(rdram, ctx);
        goto after_2;
    // 0x80098D7C: nop

    after_2:
    // 0x80098D80: lwc1        $f4, 0x10($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X10);
    // 0x80098D84: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x80098D88: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x80098D8C: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80098D90: mfc1        $a2, $f6
    ctx->r6 = (int32_t)ctx->f6.u32l;
    // 0x80098D94: jal         0x80098574
    // 0x80098D98: nop

    func_80098574(rdram, ctx);
        goto after_3;
    // 0x80098D98: nop

    after_3:
    // 0x80098D9C: lwc1        $f8, 0x0($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X0);
    // 0x80098DA0: lwc1        $f16, 0x0($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X0);
    // 0x80098DA4: lwc1        $f18, 0x4($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X4);
    // 0x80098DA8: add.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x80098DAC: lwc1        $f8, 0x8($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X8);
    // 0x80098DB0: swc1        $f10, 0x0($s0)
    MEM_W(0X0, ctx->r16) = ctx->f10.u32l;
    // 0x80098DB4: lwc1        $f4, 0x4($s1)
    ctx->f4.u32l = MEM_W(ctx->r17, 0X4);
    // 0x80098DB8: add.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl + ctx->f4.fl;
    // 0x80098DBC: swc1        $f6, 0x4($s0)
    MEM_W(0X4, ctx->r16) = ctx->f6.u32l;
    // 0x80098DC0: lwc1        $f16, 0x8($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X8);
    // 0x80098DC4: add.s       $f10, $f8, $f16
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x80098DC8: swc1        $f10, 0x8($s0)
    MEM_W(0X8, ctx->r16) = ctx->f10.u32l;
L_80098DCC:
    // 0x80098DCC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_80098DD0:
    // 0x80098DD0: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x80098DD4: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x80098DD8: jr          $ra
    // 0x80098DDC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x80098DDC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_80098DE0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098DE0: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x80098DE4: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80098DE8: lui         $a2, 0x3D4C
    ctx->r6 = S32(0X3D4C << 16);
    // 0x80098DEC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x80098DF0: ori         $a2, $a2, 0xCCCD
    ctx->r6 = ctx->r6 | 0XCCCD;
    // 0x80098DF4: jal         0x80098714
    // 0x80098DF8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    func_80098714(rdram, ctx);
        goto after_0;
    // 0x80098DF8: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    after_0:
    // 0x80098DFC: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x80098E00: lui         $a2, 0x3D4C
    ctx->r6 = S32(0X3D4C << 16);
    // 0x80098E04: ori         $a2, $a2, 0xCCCD
    ctx->r6 = ctx->r6 | 0XCCCD;
    // 0x80098E08: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x80098E0C: jal         0x80098714
    // 0x80098E10: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    func_80098714(rdram, ctx);
        goto after_1;
    // 0x80098E10: addiu       $a0, $a0, 0x4
    ctx->r4 = ADD32(ctx->r4, 0X4);
    after_1:
    // 0x80098E14: lw          $a0, 0x18($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X18);
    // 0x80098E18: lui         $a2, 0x3D4C
    ctx->r6 = S32(0X3D4C << 16);
    // 0x80098E1C: ori         $a2, $a2, 0xCCCD
    ctx->r6 = ctx->r6 | 0XCCCD;
    // 0x80098E20: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x80098E24: jal         0x80098714
    // 0x80098E28: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    func_80098714(rdram, ctx);
        goto after_2;
    // 0x80098E28: addiu       $a0, $a0, 0x8
    ctx->r4 = ADD32(ctx->r4, 0X8);
    after_2:
    // 0x80098E2C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80098E30: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x80098E34: jr          $ra
    // 0x80098E38: nop

    return;
    // 0x80098E38: nop

;}
RECOMP_FUNC void Math_Vec3f_Substract(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098E3C: lwc1        $f4, 0x0($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80098E40: lwc1        $f6, 0x0($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X0);
    // 0x80098E44: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x80098E48: swc1        $f8, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f8.u32l;
    // 0x80098E4C: lwc1        $f16, 0x4($a2)
    ctx->f16.u32l = MEM_W(ctx->r6, 0X4);
    // 0x80098E50: lwc1        $f10, 0x4($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80098E54: sub.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = ctx->f10.fl - ctx->f16.fl;
    // 0x80098E58: swc1        $f18, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f18.u32l;
    // 0x80098E5C: lwc1        $f6, 0x8($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X8);
    // 0x80098E60: lwc1        $f4, 0x8($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80098E64: sub.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x80098E68: jr          $ra
    // 0x80098E6C: swc1        $f8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f8.u32l;
    return;
    // 0x80098E6C: swc1        $f8, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f8.u32l;
;}
RECOMP_FUNC void func_80098E70(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098E70: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x80098E74: sw          $s0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r16;
    // 0x80098E78: lui         $s0, 0x800E
    ctx->r16 = S32(0X800E << 16);
    // 0x80098E7C: addiu       $s0, $s0, 0x5138
    ctx->r16 = ADD32(ctx->r16, 0X5138);
    // 0x80098E80: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
    // 0x80098E84: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x80098E88: sw          $a3, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r7;
    // 0x80098E8C: addu        $t6, $t6, $v0
    ctx->r14 = ADD32(ctx->r14, ctx->r2);
    // 0x80098E90: lbu         $t6, -0x155A($t6)
    ctx->r14 = MEM_BU(ctx->r14, -0X155A);
    // 0x80098E94: or          $a3, $a1, $zero
    ctx->r7 = ctx->r5 | 0;
    // 0x80098E98: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80098E9C: sw          $s2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r18;
    // 0x80098EA0: sw          $s1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r17;
    // 0x80098EA4: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x80098EA8: sw          $a1, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r5;
    // 0x80098EAC: beq         $t6, $zero, L_80098F78
    if (ctx->r14 == 0) {
        // 0x80098EB0: sw          $a2, 0x30($sp)
        MEM_W(0X30, ctx->r29) = ctx->r6;
            goto L_80098F78;
    }
    // 0x80098EB0: sw          $a2, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r6;
    // 0x80098EB4: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80098EB8: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x80098EBC: lbu         $t7, -0x155C($t7)
    ctx->r15 = MEM_BU(ctx->r15, -0X155C);
    // 0x80098EC0: addiu       $s2, $zero, 0x48
    ctx->r18 = ADD32(0, 0X48);
    // 0x80098EC4: bne         $t7, $zero, L_80098F20
    if (ctx->r15 != 0) {
        // 0x80098EC8: nop
    
            goto L_80098F20;
    }
    // 0x80098EC8: nop

    // 0x80098ECC: addiu       $s2, $zero, 0x48
    ctx->r18 = ADD32(0, 0X48);
    // 0x80098ED0: multu       $v0, $s2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098ED4: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80098ED8: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x80098EDC: addiu       $s1, $s1, -0x1420
    ctx->r17 = ADD32(ctx->r17, -0X1420);
    // 0x80098EE0: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x80098EE4: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x80098EE8: mflo        $t8
    ctx->r24 = lo;
    // 0x80098EEC: addu        $a0, $s1, $t8
    ctx->r4 = ADD32(ctx->r17, ctx->r24);
    // 0x80098EF0: jal         0x80098E3C
    // 0x80098EF4: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    Math_Vec3f_Substract(rdram, ctx);
        goto after_0;
    // 0x80098EF4: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    after_0:
    // 0x80098EF8: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x80098EFC: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x80098F00: lw          $a2, 0x30($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X30);
    // 0x80098F04: multu       $t9, $s2
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098F08: mflo        $t0
    ctx->r8 = lo;
    // 0x80098F0C: addu        $a0, $s1, $t0
    ctx->r4 = ADD32(ctx->r17, ctx->r8);
    // 0x80098F10: jal         0x80098E3C
    // 0x80098F14: nop

    Math_Vec3f_Substract(rdram, ctx);
        goto after_1;
    // 0x80098F14: nop

    after_1:
    // 0x80098F18: b           L_80098F6C
    // 0x80098F1C: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
        goto L_80098F6C;
    // 0x80098F1C: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_80098F20:
    // 0x80098F20: multu       $v0, $s2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098F24: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80098F28: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x80098F2C: addiu       $s1, $s1, -0x1420
    ctx->r17 = ADD32(ctx->r17, -0X1420);
    // 0x80098F30: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    // 0x80098F34: addiu       $a1, $a1, 0xC
    ctx->r5 = ADD32(ctx->r5, 0XC);
    // 0x80098F38: mflo        $t1
    ctx->r9 = lo;
    // 0x80098F3C: addu        $a0, $s1, $t1
    ctx->r4 = ADD32(ctx->r17, ctx->r9);
    // 0x80098F40: jal         0x80098E3C
    // 0x80098F44: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    Math_Vec3f_Substract(rdram, ctx);
        goto after_2;
    // 0x80098F44: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    after_2:
    // 0x80098F48: lw          $t2, 0x0($s0)
    ctx->r10 = MEM_W(ctx->r16, 0X0);
    // 0x80098F4C: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x80098F50: lw          $a2, 0x30($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X30);
    // 0x80098F54: multu       $t2, $s2
    result = U64(U32(ctx->r10)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098F58: mflo        $t3
    ctx->r11 = lo;
    // 0x80098F5C: addu        $a0, $s1, $t3
    ctx->r4 = ADD32(ctx->r17, ctx->r11);
    // 0x80098F60: jal         0x80098E3C
    // 0x80098F64: addiu       $a0, $a0, 0x24
    ctx->r4 = ADD32(ctx->r4, 0X24);
    Math_Vec3f_Substract(rdram, ctx);
        goto after_3;
    // 0x80098F64: addiu       $a0, $a0, 0x24
    ctx->r4 = ADD32(ctx->r4, 0X24);
    after_3:
    // 0x80098F68: lw          $v0, 0x0($s0)
    ctx->r2 = MEM_W(ctx->r16, 0X0);
L_80098F6C:
    // 0x80098F6C: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x80098F70: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x80098F74: sb          $zero, -0x155A($at)
    MEM_B(-0X155A, ctx->r1) = 0;
L_80098F78:
    // 0x80098F78: addiu       $s2, $zero, 0x48
    ctx->r18 = ADD32(0, 0X48);
    // 0x80098F7C: multu       $v0, $s2
    result = U64(U32(ctx->r2)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098F80: lui         $s1, 0x801D
    ctx->r17 = S32(0X801D << 16);
    // 0x80098F84: addiu       $s1, $s1, -0x1420
    ctx->r17 = ADD32(ctx->r17, -0X1420);
    // 0x80098F88: mflo        $t4
    ctx->r12 = lo;
    // 0x80098F8C: addu        $a0, $s1, $t4
    ctx->r4 = ADD32(ctx->r17, ctx->r12);
    // 0x80098F90: jal         0x80098DE0
    // 0x80098F94: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    func_80098DE0(rdram, ctx);
        goto after_4;
    // 0x80098F94: addiu       $a0, $a0, 0xC
    ctx->r4 = ADD32(ctx->r4, 0XC);
    after_4:
    // 0x80098F98: lw          $t5, 0x0($s0)
    ctx->r13 = MEM_W(ctx->r16, 0X0);
    // 0x80098F9C: multu       $t5, $s2
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098FA0: mflo        $t6
    ctx->r14 = lo;
    // 0x80098FA4: addu        $a0, $s1, $t6
    ctx->r4 = ADD32(ctx->r17, ctx->r14);
    // 0x80098FA8: jal         0x80098DE0
    // 0x80098FAC: nop

    func_80098DE0(rdram, ctx);
        goto after_5;
    // 0x80098FAC: nop

    after_5:
    // 0x80098FB0: lw          $t7, 0x0($s0)
    ctx->r15 = MEM_W(ctx->r16, 0X0);
    // 0x80098FB4: multu       $t7, $s2
    result = U64(U32(ctx->r15)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098FB8: mflo        $t8
    ctx->r24 = lo;
    // 0x80098FBC: addu        $a0, $s1, $t8
    ctx->r4 = ADD32(ctx->r17, ctx->r24);
    // 0x80098FC0: jal         0x80098DE0
    // 0x80098FC4: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    func_80098DE0(rdram, ctx);
        goto after_6;
    // 0x80098FC4: addiu       $a0, $a0, 0x30
    ctx->r4 = ADD32(ctx->r4, 0X30);
    after_6:
    // 0x80098FC8: lw          $t9, 0x0($s0)
    ctx->r25 = MEM_W(ctx->r16, 0X0);
    // 0x80098FCC: multu       $t9, $s2
    result = U64(U32(ctx->r25)) * U64(U32(ctx->r18)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80098FD0: mflo        $t0
    ctx->r8 = lo;
    // 0x80098FD4: addu        $a0, $s1, $t0
    ctx->r4 = ADD32(ctx->r17, ctx->r8);
    // 0x80098FD8: jal         0x80098DE0
    // 0x80098FDC: addiu       $a0, $a0, 0x24
    ctx->r4 = ADD32(ctx->r4, 0X24);
    func_80098DE0(rdram, ctx);
        goto after_7;
    // 0x80098FDC: addiu       $a0, $a0, 0x24
    ctx->r4 = ADD32(ctx->r4, 0X24);
    after_7:
    // 0x80098FE0: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    // 0x80098FE4: lw          $s0, 0x18($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X18);
    // 0x80098FE8: lw          $s1, 0x1C($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X1C);
    // 0x80098FEC: lw          $s2, 0x20($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X20);
    // 0x80098FF0: jr          $ra
    // 0x80098FF4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // 0x80098FF4: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
;}
RECOMP_FUNC void func_80098FF8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80098FF8: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x80098FFC: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80099000: sw          $a2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r6;
    // 0x80099004: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    // 0x80099008: lwc1        $f6, 0x0($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X0);
    // 0x8009900C: lwc1        $f4, 0x0($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80099010: lwc1        $f10, 0x4($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X4);
    // 0x80099014: lwc1        $f8, 0x4($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X4);
    // 0x80099018: sub.s       $f0, $f4, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f0.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x8009901C: lwc1        $f6, 0x8($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X8);
    // 0x80099020: lwc1        $f4, 0x8($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X8);
    // 0x80099024: sub.s       $f2, $f8, $f10
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f2.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x80099028: mul.s       $f16, $f0, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x8009902C: swc1        $f0, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f0.u32l;
    // 0x80099030: sub.s       $f14, $f4, $f6
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f14.fl = ctx->f4.fl - ctx->f6.fl;
    // 0x80099034: swc1        $f2, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f2.u32l;
    // 0x80099038: mul.s       $f18, $f14, $f14
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f18.fl = MUL_S(ctx->f14.fl, ctx->f14.fl);
    // 0x8009903C: swc1        $f14, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f14.u32l;
    // 0x80099040: swc1        $f16, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f16.u32l;
    // 0x80099044: mul.s       $f8, $f2, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x80099048: swc1        $f18, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f18.u32l;
    // 0x8009904C: add.s       $f10, $f16, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f16.fl + ctx->f8.fl;
    // 0x80099050: jal         0x800C7010
    // 0x80099054: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    _nsqrtf(rdram, ctx);
        goto after_0;
    // 0x80099054: add.s       $f12, $f10, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f18.fl;
    after_0:
    // 0x80099058: lwc1        $f16, 0x1C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x8009905C: lwc1        $f18, 0x18($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X18);
    // 0x80099060: lw          $t6, 0x38($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X38);
    // 0x80099064: add.s       $f12, $f16, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x80099068: jal         0x800C7010
    // 0x8009906C: swc1        $f0, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f0.u32l;
    _nsqrtf(rdram, ctx);
        goto after_1;
    // 0x8009906C: swc1        $f0, 0x0($t6)
    MEM_W(0X0, ctx->r14) = ctx->f0.u32l;
    after_1:
    // 0x80099070: lwc1        $f12, 0x28($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X28);
    // 0x80099074: jal         0x801ED154
    // 0x80099078: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    func_801ED154(rdram, ctx);
        goto after_2;
    // 0x80099078: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    after_2:
    // 0x8009907C: lw          $t7, 0x3C($sp)
    ctx->r15 = MEM_W(ctx->r29, 0X3C);
    // 0x80099080: swc1        $f0, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f0.u32l;
    // 0x80099084: lwc1        $f14, 0x24($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X24);
    // 0x80099088: jal         0x801ED154
    // 0x8009908C: lwc1        $f12, 0x2C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X2C);
    func_801ED154(rdram, ctx);
        goto after_3;
    // 0x8009908C: lwc1        $f12, 0x2C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X2C);
    after_3:
    // 0x80099090: lw          $t8, 0x40($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X40);
    // 0x80099094: swc1        $f0, 0x0($t8)
    MEM_W(0X0, ctx->r24) = ctx->f0.u32l;
    // 0x80099098: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009909C: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x800990A0: jr          $ra
    // 0x800990A4: nop

    return;
    // 0x800990A4: nop

;}
RECOMP_FUNC void func_800990A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800990A8: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x800990AC: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800990B0: lwc1        $f4, 0x10($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X10);
    // 0x800990B4: mtc1        $a3, $f14
    ctx->f14.u32l = ctx->r7;
    // 0x800990B8: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x800990BC: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800990C0: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800990C4: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x800990C8: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x800990CC: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x800990D0: div.s       $f16, $f14, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f14.fl, ctx->f0.fl);
    // 0x800990D4: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800990D8: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800990DC: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x800990E0: mfc1        $v0, $f10
    ctx->r2 = (int32_t)ctx->f10.u32l;
    // 0x800990E4: nop

    // 0x800990E8: andi        $t1, $v0, 0xFFF
    ctx->r9 = ctx->r2 & 0XFFF;
    // 0x800990EC: trunc.w.s   $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x800990F0: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x800990F4: addu        $t3, $a3, $t2
    ctx->r11 = ADD32(ctx->r7, ctx->r10);
    // 0x800990F8: lwc1        $f6, 0x0($t3)
    ctx->f6.u32l = MEM_W(ctx->r11, 0X0);
    // 0x800990FC: mfc1        $v1, $f4
    ctx->r3 = (int32_t)ctx->f4.u32l;
    // 0x80099100: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80099104: addiu       $t7, $v0, 0x400
    ctx->r15 = ADD32(ctx->r2, 0X400);
    // 0x80099108: addiu       $t8, $v1, 0x400
    ctx->r24 = ADD32(ctx->r3, 0X400);
    // 0x8009910C: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x80099110: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x80099114: addu        $a2, $a3, $t0
    ctx->r6 = ADD32(ctx->r7, ctx->r8);
    // 0x80099118: lwc1        $f8, 0x0($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X0);
    // 0x8009911C: andi        $t4, $v1, 0xFFF
    ctx->r12 = ctx->r3 & 0XFFF;
    // 0x80099120: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x80099124: mul.s       $f10, $f12, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f8.fl);
    // 0x80099128: addu        $t6, $a3, $t5
    ctx->r14 = ADD32(ctx->r7, ctx->r13);
    // 0x8009912C: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x80099130: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x80099134: addu        $t0, $a3, $t9
    ctx->r8 = ADD32(ctx->r7, ctx->r25);
    // 0x80099138: mul.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x8009913C: add.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x80099140: swc1        $f4, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f4.u32l;
    // 0x80099144: lwc1        $f8, 0x0($t6)
    ctx->f8.u32l = MEM_W(ctx->r14, 0X0);
    // 0x80099148: lwc1        $f10, 0x4($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X4);
    // 0x8009914C: mul.s       $f6, $f8, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f8.fl, ctx->f12.fl);
    // 0x80099150: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80099154: swc1        $f16, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f16.u32l;
    // 0x80099158: lwc1        $f4, 0x0($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X0);
    // 0x8009915C: lwc1        $f18, 0x0($t0)
    ctx->f18.u32l = MEM_W(ctx->r8, 0X0);
    // 0x80099160: lwc1        $f10, 0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X8);
    // 0x80099164: mul.s       $f8, $f12, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f12.fl, ctx->f4.fl);
    // 0x80099168: nop

    // 0x8009916C: mul.s       $f6, $f18, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f6.fl = MUL_S(ctx->f18.fl, ctx->f8.fl);
    // 0x80099170: add.s       $f16, $f6, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80099174: jr          $ra
    // 0x80099178: swc1        $f16, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f16.u32l;
    return;
    // 0x80099178: swc1        $f16, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f16.u32l;
;}
RECOMP_FUNC void func_8009917C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009917C: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x80099180: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x80099184: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x80099188: addiu       $a0, $sp, 0x24
    ctx->r4 = ADD32(ctx->r29, 0X24);
    // 0x8009918C: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x80099190: sw          $a2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r6;
    // 0x80099194: jal         0x8009852C
    // 0x80099198: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    Math_Vec3f_Copy(rdram, ctx);
        goto after_0;
    // 0x80099198: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    after_0:
    // 0x8009919C: lw          $a3, 0x3C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X3C);
    // 0x800991A0: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x800991A4: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x800991A8: lwc1        $f4, 0x0($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X0);
    // 0x800991AC: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x800991B0: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x800991B4: div.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800991B8: lw          $a2, 0x38($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X38);
    // 0x800991BC: lui         $v0, 0x8015
    ctx->r2 = S32(0X8015 << 16);
    // 0x800991C0: addiu       $v0, $v0, 0x4350
    ctx->r2 = ADD32(ctx->r2, 0X4350);
    // 0x800991C4: lwc1        $f16, 0x8($a2)
    ctx->f16.u32l = MEM_W(ctx->r6, 0X8);
    // 0x800991C8: lw          $a1, 0x34($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X34);
    // 0x800991CC: lw          $t0, 0x30($sp)
    ctx->r8 = MEM_W(ctx->r29, 0X30);
    // 0x800991D0: mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // 0x800991D4: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800991D8: lwc1        $f8, 0x4($a2)
    ctx->f8.u32l = MEM_W(ctx->r6, 0X4);
    // 0x800991DC: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x800991E0: nop

    // 0x800991E4: addiu       $t7, $v1, 0x400
    ctx->r15 = ADD32(ctx->r3, 0X400);
    // 0x800991E8: andi        $t8, $t7, 0xFFF
    ctx->r24 = ctx->r15 & 0XFFF;
    // 0x800991EC: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x800991F0: addu        $t1, $v0, $t9
    ctx->r9 = ADD32(ctx->r2, ctx->r25);
    // 0x800991F4: lwc1        $f18, 0x0($t1)
    ctx->f18.u32l = MEM_W(ctx->r9, 0X0);
    // 0x800991F8: andi        $t2, $v1, 0xFFF
    ctx->r10 = ctx->r3 & 0XFFF;
    // 0x800991FC: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x80099200: addu        $t4, $v0, $t3
    ctx->r12 = ADD32(ctx->r2, ctx->r11);
    // 0x80099204: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x80099208: lwc1        $f6, 0x0($t4)
    ctx->f6.u32l = MEM_W(ctx->r12, 0X0);
    // 0x8009920C: mul.s       $f10, $f6, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80099210: sub.s       $f16, $f4, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f4.fl - ctx->f10.fl;
    // 0x80099214: neg.s       $f18, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = -ctx->f16.fl;
    // 0x80099218: swc1        $f18, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f18.u32l;
    // 0x8009921C: lwc1        $f6, 0x0($a3)
    ctx->f6.u32l = MEM_W(ctx->r7, 0X0);
    // 0x80099220: div.s       $f8, $f6, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f0.fl);
    // 0x80099224: lwc1        $f6, 0x4($a2)
    ctx->f6.u32l = MEM_W(ctx->r6, 0X4);
    // 0x80099228: mul.s       $f4, $f8, $f2
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x8009922C: trunc.w.s   $f10, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    ctx->f10.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80099230: lwc1        $f4, 0x8($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X8);
    // 0x80099234: mfc1        $v1, $f10
    ctx->r3 = (int32_t)ctx->f10.u32l;
    // 0x80099238: nop

    // 0x8009923C: addiu       $t6, $v1, 0x400
    ctx->r14 = ADD32(ctx->r3, 0X400);
    // 0x80099240: andi        $t7, $t6, 0xFFF
    ctx->r15 = ctx->r14 & 0XFFF;
    // 0x80099244: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x80099248: addu        $t9, $v0, $t8
    ctx->r25 = ADD32(ctx->r2, ctx->r24);
    // 0x8009924C: lwc1        $f16, 0x0($t9)
    ctx->f16.u32l = MEM_W(ctx->r25, 0X0);
    // 0x80099250: andi        $t1, $v1, 0xFFF
    ctx->r9 = ctx->r3 & 0XFFF;
    // 0x80099254: sll         $t2, $t1, 2
    ctx->r10 = S32(ctx->r9 << 2);
    // 0x80099258: addu        $t3, $v0, $t2
    ctx->r11 = ADD32(ctx->r2, ctx->r10);
    // 0x8009925C: mul.s       $f8, $f16, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f6.fl);
    // 0x80099260: lwc1        $f10, 0x0($t3)
    ctx->f10.u32l = MEM_W(ctx->r11, 0X0);
    // 0x80099264: mul.s       $f16, $f4, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x80099268: add.s       $f6, $f8, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f6.fl = ctx->f8.fl + ctx->f16.fl;
    // 0x8009926C: swc1        $f6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f6.u32l;
    // 0x80099270: lwc1        $f4, 0x0($a2)
    ctx->f4.u32l = MEM_W(ctx->r6, 0X0);
    // 0x80099274: swc1        $f4, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f4.u32l;
    // 0x80099278: lwc1        $f10, 0x4($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0X4);
    // 0x8009927C: div.s       $f8, $f10, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f8.fl = DIV_S(ctx->f10.fl, ctx->f0.fl);
    // 0x80099280: mul.s       $f16, $f8, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f8.fl, ctx->f2.fl);
    // 0x80099284: lwc1        $f8, 0x0($a1)
    ctx->f8.u32l = MEM_W(ctx->r5, 0X0);
    // 0x80099288: trunc.w.s   $f6, $f16
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 16);
    ctx->f6.u32l = TRUNC_W_S(ctx->f16.fl);
    // 0x8009928C: mfc1        $a0, $f6
    ctx->r4 = (int32_t)ctx->f6.u32l;
    // 0x80099290: nop

    // 0x80099294: andi        $t5, $a0, 0xFFF
    ctx->r13 = ctx->r4 & 0XFFF;
    // 0x80099298: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x8009929C: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x800992A0: lwc1        $f4, 0x0($t7)
    ctx->f4.u32l = MEM_W(ctx->r15, 0X0);
    // 0x800992A4: addiu       $t8, $a0, 0x400
    ctx->r24 = ADD32(ctx->r4, 0X400);
    // 0x800992A8: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x800992AC: mul.s       $f10, $f18, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f18.fl, ctx->f4.fl);
    // 0x800992B0: sll         $t1, $t9, 2
    ctx->r9 = S32(ctx->r25 << 2);
    // 0x800992B4: addu        $t2, $v0, $t1
    ctx->r10 = ADD32(ctx->r2, ctx->r9);
    // 0x800992B8: lwc1        $f6, 0x0($t2)
    ctx->f6.u32l = MEM_W(ctx->r10, 0X0);
    // 0x800992BC: lwc1        $f18, 0x18($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X18);
    // 0x800992C0: mul.s       $f4, $f6, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x800992C4: add.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x800992C8: add.s       $f8, $f4, $f16
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f16.fl;
    // 0x800992CC: swc1        $f8, 0x0($t0)
    MEM_W(0X0, ctx->r8) = ctx->f8.u32l;
    // 0x800992D0: lwc1        $f10, 0x1C($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X1C);
    // 0x800992D4: lwc1        $f6, 0x4($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X4);
    // 0x800992D8: add.s       $f18, $f10, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = ctx->f10.fl + ctx->f6.fl;
    // 0x800992DC: swc1        $f18, 0x4($t0)
    MEM_W(0X4, ctx->r8) = ctx->f18.u32l;
    // 0x800992E0: lwc1        $f4, 0x4($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X4);
    // 0x800992E4: lwc1        $f6, 0x20($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X20);
    // 0x800992E8: div.s       $f16, $f4, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f16.fl = DIV_S(ctx->f4.fl, ctx->f0.fl);
    // 0x800992EC: mul.s       $f8, $f16, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f8.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x800992F0: lwc1        $f16, 0x8($a1)
    ctx->f16.u32l = MEM_W(ctx->r5, 0X8);
    // 0x800992F4: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x800992F8: mfc1        $a0, $f10
    ctx->r4 = (int32_t)ctx->f10.u32l;
    // 0x800992FC: nop

    // 0x80099300: addiu       $t4, $a0, 0x400
    ctx->r12 = ADD32(ctx->r4, 0X400);
    // 0x80099304: andi        $t5, $t4, 0xFFF
    ctx->r13 = ctx->r12 & 0XFFF;
    // 0x80099308: sll         $t6, $t5, 2
    ctx->r14 = S32(ctx->r13 << 2);
    // 0x8009930C: addu        $t7, $v0, $t6
    ctx->r15 = ADD32(ctx->r2, ctx->r14);
    // 0x80099310: lwc1        $f18, 0x0($t7)
    ctx->f18.u32l = MEM_W(ctx->r15, 0X0);
    // 0x80099314: andi        $t8, $a0, 0xFFF
    ctx->r24 = ctx->r4 & 0XFFF;
    // 0x80099318: sll         $t9, $t8, 2
    ctx->r25 = S32(ctx->r24 << 2);
    // 0x8009931C: mul.s       $f4, $f6, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // 0x80099320: addu        $t1, $v0, $t9
    ctx->r9 = ADD32(ctx->r2, ctx->r25);
    // 0x80099324: lwc1        $f10, 0x0($t1)
    ctx->f10.u32l = MEM_W(ctx->r9, 0X0);
    // 0x80099328: lwc1        $f6, 0x18($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X18);
    // 0x8009932C: mul.s       $f18, $f10, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x80099330: add.s       $f8, $f16, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f16.fl + ctx->f4.fl;
    // 0x80099334: sub.s       $f16, $f8, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = ctx->f8.fl - ctx->f18.fl;
    // 0x80099338: swc1        $f16, 0x8($t0)
    MEM_W(0X8, ctx->r8) = ctx->f16.u32l;
    // 0x8009933C: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x80099340: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x80099344: jr          $ra
    // 0x80099348: nop

    return;
    // 0x80099348: nop

;}
RECOMP_FUNC void func_8009934C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009934C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80099350: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80099354: addiu       $sp, $sp, -0x10
    ctx->r29 = ADD32(ctx->r29, -0X10);
    // 0x80099358: c.lt.s      $f16, $f12
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f16.fl < ctx->f12.fl;
    // 0x8009935C: nop

    // 0x80099360: bc1fl       L_80099370
    if (!c1cs) {
        // 0x80099364: sub.s       $f0, $f16, $f12
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f16.fl - ctx->f12.fl;
            goto L_80099370;
    }
    goto skip_0;
    // 0x80099364: sub.s       $f0, $f16, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f16.fl - ctx->f12.fl;
    skip_0:
    // 0x80099368: mov.s       $f12, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    ctx->f12.fl = ctx->f16.fl;
    // 0x8009936C: sub.s       $f0, $f16, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f0.fl = ctx->f16.fl - ctx->f12.fl;
L_80099370:
    // 0x80099370: lui         $at, 0x40C0
    ctx->r1 = S32(0X40C0 << 16);
    // 0x80099374: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x80099378: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8009937C: mul.s       $f4, $f0, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80099380: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80099384: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x80099388: lw          $v1, 0x20($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X20);
    // 0x8009938C: lw          $a0, 0x24($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X24);
    // 0x80099390: lw          $v0, 0x28($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X28);
    // 0x80099394: mul.s       $f6, $f4, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // 0x80099398: nop

    // 0x8009939C: mul.s       $f2, $f12, $f12
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f2.fl = MUL_S(ctx->f12.fl, ctx->f12.fl);
    // 0x800993A0: div.s       $f8, $f6, $f18
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f8.fl = DIV_S(ctx->f6.fl, ctx->f18.fl);
    // 0x800993A4: mul.s       $f14, $f2, $f12
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f14.fl = MUL_S(ctx->f2.fl, ctx->f12.fl);
    // 0x800993A8: nop

    // 0x800993AC: mul.s       $f4, $f14, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // 0x800993B0: lwc1        $f10, -0x4B3C($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X4B3C);
    // 0x800993B4: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x800993B8: swc1        $f8, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->f8.u32l;
    // 0x800993BC: sub.s       $f6, $f4, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f4.fl - ctx->f2.fl;
    // 0x800993C0: add.s       $f4, $f6, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x800993C4: neg.s       $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = -ctx->f12.fl;
    // 0x800993C8: swc1        $f4, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f4.u32l;
    // 0x800993CC: mul.s       $f10, $f6, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f12.fl);
    // 0x800993D0: nop

    // 0x800993D4: mul.s       $f6, $f10, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x800993D8: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800993DC: nop

    // 0x800993E0: mul.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x800993E4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800993E8: nop

    // 0x800993EC: mul.s       $f10, $f2, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = MUL_S(ctx->f2.fl, ctx->f10.fl);
    // 0x800993F0: add.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x800993F4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x800993F8: lui         $at, 0x800F
    ctx->r1 = S32(0X800F << 16);
    // 0x800993FC: mul.s       $f10, $f12, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f10.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // 0x80099400: add.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x80099404: lwc1        $f10, -0x4B38($at)
    ctx->f10.u32l = MEM_W(ctx->r1, -0X4B38);
    // 0x80099408: add.s       $f6, $f6, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f6.fl + ctx->f10.fl;
    // 0x8009940C: div.s       $f10, $f14, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f10.fl = DIV_S(ctx->f14.fl, ctx->f18.fl);
    // 0x80099410: swc1        $f6, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f6.u32l;
    // 0x80099414: swc1        $f10, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f10.u32l;
    // 0x80099418: lwc1        $f10, 0x0($a3)
    ctx->f10.u32l = MEM_W(ctx->r7, 0X0);
    // 0x8009941C: mul.s       $f8, $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f8.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80099420: lwc1        $f10, 0x0($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X0);
    // 0x80099424: mul.s       $f4, $f4, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f4.fl, ctx->f10.fl);
    // 0x80099428: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8009942C: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80099430: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80099434: lwc1        $f8, 0x0($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0X0);
    // 0x80099438: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x8009943C: lwc1        $f10, 0xC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC);
    // 0x80099440: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80099444: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x80099448: swc1        $f8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f8.u32l;
    // 0x8009944C: lwc1        $f10, 0x0($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X0);
    // 0x80099450: lwc1        $f4, 0x4($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X4);
    // 0x80099454: lwc1        $f8, 0x4($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X4);
    // 0x80099458: mul.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = MUL_S(ctx->f10.fl, ctx->f4.fl);
    // 0x8009945C: lwc1        $f10, 0x4($v1)
    ctx->f10.u32l = MEM_W(ctx->r3, 0X4);
    // 0x80099460: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80099464: lwc1        $f10, 0x8($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X8);
    // 0x80099468: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x8009946C: lwc1        $f6, 0x4($a0)
    ctx->f6.u32l = MEM_W(ctx->r4, 0X4);
    // 0x80099470: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x80099474: lwc1        $f6, 0x4($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X4);
    // 0x80099478: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x8009947C: lwc1        $f8, 0xC($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0XC);
    // 0x80099480: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x80099484: add.s       $f6, $f4, $f10
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f6.fl = ctx->f4.fl + ctx->f10.fl;
    // 0x80099488: swc1        $f6, 0x4($a1)
    MEM_W(0X4, ctx->r5) = ctx->f6.u32l;
    // 0x8009948C: lwc1        $f8, 0x0($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X0);
    // 0x80099490: lwc1        $f4, 0x8($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0X8);
    // 0x80099494: lwc1        $f6, 0x4($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X4);
    // 0x80099498: mul.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = MUL_S(ctx->f8.fl, ctx->f4.fl);
    // 0x8009949C: lwc1        $f8, 0x8($v1)
    ctx->f8.u32l = MEM_W(ctx->r3, 0X8);
    // 0x800994A0: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800994A4: lwc1        $f8, 0x8($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X8);
    // 0x800994A8: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800994AC: lwc1        $f10, 0x8($a0)
    ctx->f10.u32l = MEM_W(ctx->r4, 0X8);
    // 0x800994B0: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x800994B4: lwc1        $f10, 0x8($v0)
    ctx->f10.u32l = MEM_W(ctx->r2, 0X8);
    // 0x800994B8: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x800994BC: lwc1        $f6, 0xC($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0XC);
    // 0x800994C0: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x800994C4: add.s       $f10, $f4, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = ctx->f4.fl + ctx->f8.fl;
    // 0x800994C8: swc1        $f10, 0x8($a1)
    MEM_W(0X8, ctx->r5) = ctx->f10.u32l;
    // 0x800994CC: lwc1        $f4, 0xC($a3)
    ctx->f4.u32l = MEM_W(ctx->r7, 0XC);
    // 0x800994D0: lwc1        $f6, 0x0($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X0);
    // 0x800994D4: lwc1        $f10, 0x4($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0X4);
    // 0x800994D8: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x800994DC: lwc1        $f6, 0xC($v1)
    ctx->f6.u32l = MEM_W(ctx->r3, 0XC);
    // 0x800994E0: mul.s       $f4, $f10, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f6.fl);
    // 0x800994E4: lwc1        $f6, 0x8($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X8);
    // 0x800994E8: add.s       $f10, $f8, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f10.fl = ctx->f8.fl + ctx->f4.fl;
    // 0x800994EC: lwc1        $f8, 0xC($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0XC);
    // 0x800994F0: mul.s       $f4, $f6, $f8
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f4.fl = MUL_S(ctx->f6.fl, ctx->f8.fl);
    // 0x800994F4: lwc1        $f8, 0xC($v0)
    ctx->f8.u32l = MEM_W(ctx->r2, 0XC);
    // 0x800994F8: add.s       $f6, $f10, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f10.fl + ctx->f4.fl;
    // 0x800994FC: lwc1        $f10, 0xC($sp)
    ctx->f10.u32l = MEM_W(ctx->r29, 0XC);
    // 0x80099500: addiu       $sp, $sp, 0x10
    ctx->r29 = ADD32(ctx->r29, 0X10);
    // 0x80099504: mul.s       $f4, $f8, $f10
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f4.fl = MUL_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80099508: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8009950C: jr          $ra
    // 0x80099510: swc1        $f8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->f8.u32l;
    return;
    // 0x80099510: swc1        $f8, 0x0($a2)
    MEM_W(0X0, ctx->r6) = ctx->f8.u32l;
;}
RECOMP_FUNC void func_80099514(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099514: addiu       $sp, $sp, -0xA0
    ctx->r29 = ADD32(ctx->r29, -0XA0);
    // 0x80099518: sw          $ra, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r31;
    // 0x8009951C: sw          $s0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r16;
    // 0x80099520: sw          $a0, 0xA0($sp)
    MEM_W(0XA0, ctx->r29) = ctx->r4;
    // 0x80099524: sw          $a1, 0xA4($sp)
    MEM_W(0XA4, ctx->r29) = ctx->r5;
    // 0x80099528: sw          $a3, 0xAC($sp)
    MEM_W(0XAC, ctx->r29) = ctx->r7;
    // 0x8009952C: sw          $zero, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = 0;
    // 0x80099530: lh          $v1, 0x0($a3)
    ctx->r3 = MEM_H(ctx->r7, 0X0);
    // 0x80099534: addiu       $t4, $zero, 0xA
    ctx->r12 = ADD32(0, 0XA);
    // 0x80099538: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8009953C: multu       $v1, $t4
    result = U64(U32(ctx->r3)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x80099540: lw          $t6, 0xB0($sp)
    ctx->r14 = MEM_W(ctx->r29, 0XB0);
    // 0x80099544: or          $s0, $a2, $zero
    ctx->r16 = ctx->r6 | 0;
    // 0x80099548: addiu       $t2, $zero, -0x1
    ctx->r10 = ADD32(0, -0X1);
    // 0x8009954C: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x80099550: mov.s       $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    ctx->f16.fl = ctx->f0.fl;
    // 0x80099554: lwc1        $f12, 0x0($t6)
    ctx->f12.u32l = MEM_W(ctx->r14, 0X0);
    // 0x80099558: mflo        $t8
    ctx->r24 = lo;
    // 0x8009955C: addu        $t0, $a2, $t8
    ctx->r8 = ADD32(ctx->r6, ctx->r24);
    // 0x80099560: lb          $t1, 0x0($t0)
    ctx->r9 = MEM_B(ctx->r8, 0X0);
    // 0x80099564: bgez        $v1, L_8009957C
    if (SIGNED(ctx->r3) >= 0) {
        // 0x80099568: or          $t3, $t1, $zero
        ctx->r11 = ctx->r9 | 0;
            goto L_8009957C;
    }
    // 0x80099568: or          $t3, $t1, $zero
    ctx->r11 = ctx->r9 | 0;
    // 0x8009956C: or          $v1, $zero, $zero
    ctx->r3 = 0 | 0;
    // 0x80099570: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x80099574: or          $t0, $a2, $zero
    ctx->r8 = ctx->r6 | 0;
    // 0x80099578: lb          $t1, 0x0($a2)
    ctx->r9 = MEM_B(ctx->r6, 0X0);
L_8009957C:
    // 0x8009957C: beq         $t2, $t1, L_800995A4
    if (ctx->r10 == ctx->r9) {
        // 0x80099580: nop
    
            goto L_800995A4;
    }
    // 0x80099580: nop

    // 0x80099584: lb          $t9, 0xA($t0)
    ctx->r25 = MEM_B(ctx->r8, 0XA);
    // 0x80099588: beq         $t2, $t9, L_800995A4
    if (ctx->r10 == ctx->r25) {
        // 0x8009958C: nop
    
            goto L_800995A4;
    }
    // 0x8009958C: nop

    // 0x80099590: lb          $t5, 0x14($t0)
    ctx->r13 = MEM_B(ctx->r8, 0X14);
    // 0x80099594: sll         $t6, $v1, 2
    ctx->r14 = S32(ctx->r3 << 2);
    // 0x80099598: addu        $t6, $t6, $v1
    ctx->r14 = ADD32(ctx->r14, ctx->r3);
    // 0x8009959C: bne         $t2, $t5, L_800995AC
    if (ctx->r10 != ctx->r13) {
        // 0x800995A0: sll         $t6, $t6, 1
        ctx->r14 = S32(ctx->r14 << 1);
            goto L_800995AC;
    }
    // 0x800995A0: sll         $t6, $t6, 1
    ctx->r14 = S32(ctx->r14 << 1);
L_800995A4:
    // 0x800995A4: b           L_80099844
    // 0x800995A8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
        goto L_80099844;
    // 0x800995A8: addiu       $v0, $zero, 0x1
    ctx->r2 = ADD32(0, 0X1);
L_800995AC:
    // 0x800995AC: addu        $v0, $s0, $t6
    ctx->r2 = ADD32(ctx->r16, ctx->r14);
    // 0x800995B0: lh          $t7, 0x4($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X4);
    // 0x800995B4: lw          $a1, 0xA0($sp)
    ctx->r5 = MEM_W(ctx->r29, 0XA0);
    // 0x800995B8: lw          $a2, 0xA4($sp)
    ctx->r6 = MEM_W(ctx->r29, 0XA4);
    // 0x800995BC: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x800995C0: addiu       $a3, $sp, 0x5C
    ctx->r7 = ADD32(ctx->r29, 0X5C);
    // 0x800995C4: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x800995C8: swc1        $f6, 0x5C($sp)
    MEM_W(0X5C, ctx->r29) = ctx->f6.u32l;
    // 0x800995CC: lh          $t8, 0x6($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X6);
    // 0x800995D0: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x800995D4: nop

    // 0x800995D8: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800995DC: swc1        $f10, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->f10.u32l;
    // 0x800995E0: lh          $t9, 0x8($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X8);
    // 0x800995E4: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x800995E8: nop

    // 0x800995EC: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800995F0: swc1        $f4, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->f4.u32l;
    // 0x800995F4: lb          $t5, 0x2($v0)
    ctx->r13 = MEM_B(ctx->r2, 0X2);
    // 0x800995F8: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x800995FC: nop

    // 0x80099600: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x80099604: swc1        $f8, 0x68($sp)
    MEM_W(0X68, ctx->r29) = ctx->f8.u32l;
    // 0x80099608: lh          $t6, 0xE($v0)
    ctx->r14 = MEM_H(ctx->r2, 0XE);
    // 0x8009960C: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x80099610: nop

    // 0x80099614: cvt.s.w     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.fl = CVT_S_W(ctx->f10.u32l);
    // 0x80099618: swc1        $f18, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f18.u32l;
    // 0x8009961C: lh          $t7, 0x10($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X10);
    // 0x80099620: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x80099624: nop

    // 0x80099628: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x8009962C: swc1        $f6, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f6.u32l;
    // 0x80099630: lh          $t8, 0x12($v0)
    ctx->r24 = MEM_H(ctx->r2, 0X12);
    // 0x80099634: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x80099638: nop

    // 0x8009963C: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x80099640: swc1        $f10, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f10.u32l;
    // 0x80099644: lb          $t9, 0xC($v0)
    ctx->r25 = MEM_B(ctx->r2, 0XC);
    // 0x80099648: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x8009964C: nop

    // 0x80099650: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x80099654: swc1        $f4, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f4.u32l;
    // 0x80099658: lh          $t5, 0x18($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X18);
    // 0x8009965C: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x80099660: nop

    // 0x80099664: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x80099668: swc1        $f8, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f8.u32l;
    // 0x8009966C: lh          $t6, 0x1A($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X1A);
    // 0x80099670: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x80099674: nop

    // 0x80099678: cvt.s.w     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.fl = CVT_S_W(ctx->f10.u32l);
    // 0x8009967C: swc1        $f18, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f18.u32l;
    // 0x80099680: lh          $t7, 0x1C($v0)
    ctx->r15 = MEM_H(ctx->r2, 0X1C);
    // 0x80099684: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x80099688: nop

    // 0x8009968C: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80099690: swc1        $f6, 0x84($sp)
    MEM_W(0X84, ctx->r29) = ctx->f6.u32l;
    // 0x80099694: lb          $t8, 0x16($v0)
    ctx->r24 = MEM_B(ctx->r2, 0X16);
    // 0x80099698: mtc1        $t8, $f8
    ctx->f8.u32l = ctx->r24;
    // 0x8009969C: addiu       $t8, $sp, 0x6C
    ctx->r24 = ADD32(ctx->r29, 0X6C);
    // 0x800996A0: cvt.s.w     $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.fl = CVT_S_W(ctx->f8.u32l);
    // 0x800996A4: swc1        $f10, 0x88($sp)
    MEM_W(0X88, ctx->r29) = ctx->f10.u32l;
    // 0x800996A8: lh          $t9, 0x22($v0)
    ctx->r25 = MEM_H(ctx->r2, 0X22);
    // 0x800996AC: mtc1        $t9, $f18
    ctx->f18.u32l = ctx->r25;
    // 0x800996B0: addiu       $t9, $sp, 0x7C
    ctx->r25 = ADD32(ctx->r29, 0X7C);
    // 0x800996B4: cvt.s.w     $f4, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    ctx->f4.fl = CVT_S_W(ctx->f18.u32l);
    // 0x800996B8: swc1        $f4, 0x8C($sp)
    MEM_W(0X8C, ctx->r29) = ctx->f4.u32l;
    // 0x800996BC: lh          $t5, 0x24($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X24);
    // 0x800996C0: mtc1        $t5, $f6
    ctx->f6.u32l = ctx->r13;
    // 0x800996C4: addiu       $t5, $sp, 0x8C
    ctx->r13 = ADD32(ctx->r29, 0X8C);
    // 0x800996C8: cvt.s.w     $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.fl = CVT_S_W(ctx->f6.u32l);
    // 0x800996CC: swc1        $f8, 0x90($sp)
    MEM_W(0X90, ctx->r29) = ctx->f8.u32l;
    // 0x800996D0: lh          $t6, 0x26($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X26);
    // 0x800996D4: mtc1        $t6, $f10
    ctx->f10.u32l = ctx->r14;
    // 0x800996D8: nop

    // 0x800996DC: cvt.s.w     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.fl = CVT_S_W(ctx->f10.u32l);
    // 0x800996E0: swc1        $f18, 0x94($sp)
    MEM_W(0X94, ctx->r29) = ctx->f18.u32l;
    // 0x800996E4: lb          $t7, 0x20($v0)
    ctx->r15 = MEM_B(ctx->r2, 0X20);
    // 0x800996E8: swc1        $f16, 0x48($sp)
    MEM_W(0X48, ctx->r29) = ctx->f16.u32l;
    // 0x800996EC: swc1        $f14, 0x4C($sp)
    MEM_W(0X4C, ctx->r29) = ctx->f14.u32l;
    // 0x800996F0: mtc1        $t7, $f4
    ctx->f4.u32l = ctx->r15;
    // 0x800996F4: sw          $t3, 0x40($sp)
    MEM_W(0X40, ctx->r29) = ctx->r11;
    // 0x800996F8: sw          $t5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r13;
    // 0x800996FC: cvt.s.w     $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.fl = CVT_S_W(ctx->f4.u32l);
    // 0x80099700: sw          $t9, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r25;
    // 0x80099704: sw          $t8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r24;
    // 0x80099708: jal         0x8009934C
    // 0x8009970C: swc1        $f6, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f6.u32l;
    func_8009934C(rdram, ctx);
        goto after_0;
    // 0x8009970C: swc1        $f6, 0x98($sp)
    MEM_W(0X98, ctx->r29) = ctx->f6.u32l;
    after_0:
    // 0x80099710: lw          $a0, 0xAC($sp)
    ctx->r4 = MEM_W(ctx->r29, 0XAC);
    // 0x80099714: addiu       $t4, $zero, 0xA
    ctx->r12 = ADD32(0, 0XA);
    // 0x80099718: lw          $t3, 0x40($sp)
    ctx->r11 = MEM_W(ctx->r29, 0X40);
    // 0x8009971C: lh          $t6, 0x0($a0)
    ctx->r14 = MEM_H(ctx->r4, 0X0);
    // 0x80099720: lw          $a1, 0xB0($sp)
    ctx->r5 = MEM_W(ctx->r29, 0XB0);
    // 0x80099724: lw          $a3, 0xA0($sp)
    ctx->r7 = MEM_W(ctx->r29, 0XA0);
    // 0x80099728: multu       $t6, $t4
    result = U64(U32(ctx->r14)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x8009972C: addiu       $t2, $zero, -0x1
    ctx->r10 = ADD32(0, -0X1);
    // 0x80099730: lwc1        $f14, 0x4C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80099734: lwc1        $f16, 0x48($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X48);
    // 0x80099738: sll         $a2, $t3, 24
    ctx->r6 = S32(ctx->r11 << 24);
    // 0x8009973C: mflo        $t7
    ctx->r15 = lo;
    // 0x80099740: addu        $v0, $s0, $t7
    ctx->r2 = ADD32(ctx->r16, ctx->r15);
    // 0x80099744: lb          $v1, 0xB($v0)
    ctx->r3 = MEM_B(ctx->r2, 0XB);
    // 0x80099748: beql        $v1, $zero, L_80099768
    if (ctx->r3 == 0) {
        // 0x8009974C: lb          $v1, 0x15($v0)
        ctx->r3 = MEM_B(ctx->r2, 0X15);
            goto L_80099768;
    }
    goto skip_0;
    // 0x8009974C: lb          $v1, 0x15($v0)
    ctx->r3 = MEM_B(ctx->r2, 0X15);
    skip_0:
    // 0x80099750: mtc1        $v1, $f10
    ctx->f10.u32l = ctx->r3;
    // 0x80099754: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80099758: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009975C: cvt.s.w     $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    ctx->f18.fl = CVT_S_W(ctx->f10.u32l);
    // 0x80099760: div.s       $f14, $f8, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f14.fl = DIV_S(ctx->f8.fl, ctx->f18.fl);
    // 0x80099764: lb          $v1, 0x15($v0)
    ctx->r3 = MEM_B(ctx->r2, 0X15);
L_80099768:
    // 0x80099768: beql        $v1, $zero, L_80099788
    if (ctx->r3 == 0) {
        // 0x8009976C: sub.s       $f8, $f16, $f14
        CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f16.fl - ctx->f14.fl;
            goto L_80099788;
    }
    goto skip_1;
    // 0x8009976C: sub.s       $f8, $f16, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f16.fl - ctx->f14.fl;
    skip_1:
    // 0x80099770: mtc1        $v1, $f6
    ctx->f6.u32l = ctx->r3;
    // 0x80099774: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80099778: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009977C: cvt.s.w     $f10, $f6
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    ctx->f10.fl = CVT_S_W(ctx->f6.u32l);
    // 0x80099780: div.s       $f16, $f4, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = DIV_S(ctx->f4.fl, ctx->f10.fl);
    // 0x80099784: sub.s       $f8, $f16, $f14
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f8.fl = ctx->f16.fl - ctx->f14.fl;
L_80099788:
    // 0x80099788: lwc1        $f0, 0x0($a1)
    ctx->f0.u32l = MEM_W(ctx->r5, 0X0);
    // 0x8009978C: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x80099790: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x80099794: mul.s       $f18, $f0, $f8
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f18.fl = MUL_S(ctx->f0.fl, ctx->f8.fl);
    // 0x80099798: add.s       $f2, $f18, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 14);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f14.fl); 
    ctx->f2.fl = ctx->f18.fl + ctx->f14.fl;
    // 0x8009979C: add.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = ctx->f0.fl + ctx->f2.fl;
    // 0x800997A0: swc1        $f6, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f6.u32l;
    // 0x800997A4: lwc1        $f4, 0x0($a1)
    ctx->f4.u32l = MEM_W(ctx->r5, 0X0);
    // 0x800997A8: c.le.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl <= ctx->f4.fl;
    // 0x800997AC: nop

    // 0x800997B0: bc1f        L_800997F8
    if (!c1cs) {
        // 0x800997B4: nop
    
            goto L_800997F8;
    }
    // 0x800997B4: nop

    // 0x800997B8: lh          $t8, 0x0($a0)
    ctx->r24 = MEM_H(ctx->r4, 0X0);
    // 0x800997BC: addiu       $t9, $t8, 0x1
    ctx->r25 = ADD32(ctx->r24, 0X1);
    // 0x800997C0: sh          $t9, 0x0($a0)
    MEM_H(0X0, ctx->r4) = ctx->r25;
    // 0x800997C4: lh          $t5, 0x0($a0)
    ctx->r13 = MEM_H(ctx->r4, 0X0);
    // 0x800997C8: addiu       $t9, $zero, 0x1
    ctx->r25 = ADD32(0, 0X1);
    // 0x800997CC: multu       $t5, $t4
    result = U64(U32(ctx->r13)) * U64(U32(ctx->r12)); lo = S32(result >> 0); hi = S32(result >> 32);
    // 0x800997D0: mflo        $t6
    ctx->r14 = lo;
    // 0x800997D4: addu        $t7, $s0, $t6
    ctx->r15 = ADD32(ctx->r16, ctx->r14);
    // 0x800997D8: lb          $t8, 0x1E($t7)
    ctx->r24 = MEM_B(ctx->r15, 0X1E);
    // 0x800997DC: bnel        $t2, $t8, L_800997F0
    if (ctx->r10 != ctx->r24) {
        // 0x800997E0: lwc1        $f10, 0x0($a1)
        ctx->f10.u32l = MEM_W(ctx->r5, 0X0);
            goto L_800997F0;
    }
    goto skip_2;
    // 0x800997E0: lwc1        $f10, 0x0($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X0);
    skip_2:
    // 0x800997E4: sh          $zero, 0x0($a0)
    MEM_H(0X0, ctx->r4) = 0;
    // 0x800997E8: sw          $t9, 0x9C($sp)
    MEM_W(0X9C, ctx->r29) = ctx->r25;
    // 0x800997EC: lwc1        $f10, 0x0($a1)
    ctx->f10.u32l = MEM_W(ctx->r5, 0X0);
L_800997F0:
    // 0x800997F0: sub.s       $f8, $f10, $f12
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f8.fl = ctx->f10.fl - ctx->f12.fl;
    // 0x800997F4: swc1        $f8, 0x0($a1)
    MEM_W(0X0, ctx->r5) = ctx->f8.u32l;
L_800997F8:
    // 0x800997F8: lui         $t5, 0x800E
    ctx->r13 = S32(0X800E << 16);
    // 0x800997FC: lw          $t5, 0x5138($t5)
    ctx->r13 = MEM_W(ctx->r13, 0X5138);
    // 0x80099800: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    // 0x80099804: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x80099808: bne         $t5, $zero, L_80099834
    if (ctx->r13 != 0) {
        // 0x8009980C: sra         $t7, $a2, 24
        ctx->r15 = S32(SIGNED(ctx->r6) >> 24);
            goto L_80099834;
    }
    // 0x8009980C: sra         $t7, $a2, 24
    ctx->r15 = S32(SIGNED(ctx->r6) >> 24);
    // 0x80099810: sll         $a2, $t3, 24
    ctx->r6 = S32(ctx->r11 << 24);
    // 0x80099814: sra         $t6, $a2, 24
    ctx->r14 = S32(SIGNED(ctx->r6) >> 24);
    // 0x80099818: lui         $a1, 0x800D
    ctx->r5 = S32(0X800D << 16);
    // 0x8009981C: lw          $a1, 0x48DC($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48DC);
    // 0x80099820: or          $a2, $t6, $zero
    ctx->r6 = ctx->r14 | 0;
    // 0x80099824: jal         0x80098C04
    // 0x80099828: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    func_80098C04(rdram, ctx);
        goto after_1;
    // 0x80099828: or          $a0, $a3, $zero
    ctx->r4 = ctx->r7 | 0;
    after_1:
    // 0x8009982C: b           L_80099844
    // 0x80099830: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
        goto L_80099844;
    // 0x80099830: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
L_80099834:
    // 0x80099834: lw          $a1, 0x48E0($a1)
    ctx->r5 = MEM_W(ctx->r5, 0X48E0);
    // 0x80099838: jal         0x80098C04
    // 0x8009983C: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    func_80098C04(rdram, ctx);
        goto after_2;
    // 0x8009983C: or          $a2, $t7, $zero
    ctx->r6 = ctx->r15 | 0;
    after_2:
    // 0x80099840: lw          $v0, 0x9C($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X9C);
L_80099844:
    // 0x80099844: lw          $ra, 0x2C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X2C);
    // 0x80099848: lw          $s0, 0x28($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X28);
    // 0x8009984C: addiu       $sp, $sp, 0xA0
    ctx->r29 = ADD32(ctx->r29, 0XA0);
    // 0x80099850: jr          $ra
    // 0x80099854: nop

    return;
    // 0x80099854: nop

;}
RECOMP_FUNC void func_80099858(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099858: sw          $a1, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r5;
    // 0x8009985C: sw          $a2, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r6;
    // 0x80099860: sw          $a3, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r7;
    // 0x80099864: sb          $a1, 0x0($a0)
    MEM_B(0X0, ctx->r4) = ctx->r5;
    // 0x80099868: sb          $a2, 0x1($a0)
    MEM_B(0X1, ctx->r4) = ctx->r6;
    // 0x8009986C: sb          $a3, 0x2($a0)
    MEM_B(0X2, ctx->r4) = ctx->r7;
    // 0x80099870: lw          $t1, 0x14($sp)
    ctx->r9 = MEM_W(ctx->r29, 0X14);
    // 0x80099874: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80099878: beql        $t1, $zero, L_80099898
    if (ctx->r9 == 0) {
        // 0x8009987C: lh          $t4, 0x0($v0)
        ctx->r12 = MEM_H(ctx->r2, 0X0);
            goto L_80099898;
    }
    goto skip_0;
    // 0x8009987C: lh          $t4, 0x0($v0)
    ctx->r12 = MEM_H(ctx->r2, 0X0);
    skip_0:
    // 0x80099880: lw          $v0, 0x10($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X10);
    // 0x80099884: lh          $t2, 0x0($v0)
    ctx->r10 = MEM_H(ctx->r2, 0X0);
    // 0x80099888: negu        $t3, $t2
    ctx->r11 = SUB32(0, ctx->r10);
    // 0x8009988C: b           L_8009989C
    // 0x80099890: sh          $t3, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r11;
        goto L_8009989C;
    // 0x80099890: sh          $t3, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r11;
    // 0x80099894: lh          $t4, 0x0($v0)
    ctx->r12 = MEM_H(ctx->r2, 0X0);
L_80099898:
    // 0x80099898: sh          $t4, 0x4($a0)
    MEM_H(0X4, ctx->r4) = ctx->r12;
L_8009989C:
    // 0x8009989C: lh          $t5, 0x2($v0)
    ctx->r13 = MEM_H(ctx->r2, 0X2);
    // 0x800998A0: sh          $t5, 0x6($a0)
    MEM_H(0X6, ctx->r4) = ctx->r13;
    // 0x800998A4: lh          $t6, 0x4($v0)
    ctx->r14 = MEM_H(ctx->r2, 0X4);
    // 0x800998A8: jr          $ra
    // 0x800998AC: sh          $t6, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r14;
    return;
    // 0x800998AC: sh          $t6, 0x8($a0)
    MEM_H(0X8, ctx->r4) = ctx->r14;
;}
RECOMP_FUNC void func_800998B0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x800998B0: addiu       $sp, $sp, -0x40
    ctx->r29 = ADD32(ctx->r29, -0X40);
    // 0x800998B4: sw          $s7, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r23;
    // 0x800998B8: or          $s7, $a1, $zero
    ctx->r23 = ctx->r5 | 0;
    // 0x800998BC: sw          $s5, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r21;
    // 0x800998C0: sw          $ra, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r31;
    // 0x800998C4: sw          $s6, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r22;
    // 0x800998C8: sw          $s4, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->r20;
    // 0x800998CC: sw          $s3, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r19;
    // 0x800998D0: sw          $s2, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r18;
    // 0x800998D4: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x800998D8: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x800998DC: or          $s5, $a2, $zero
    ctx->r21 = ctx->r6 | 0;
    // 0x800998E0: lbu         $a2, 0x1($s7)
    ctx->r6 = MEM_BU(ctx->r23, 0X1);
    // 0x800998E4: lb          $a3, 0x2($s7)
    ctx->r7 = MEM_B(ctx->r23, 0X2);
    // 0x800998E8: lb          $a1, 0x0($a1)
    ctx->r5 = MEM_B(ctx->r5, 0X0);
    // 0x800998EC: addiu       $t6, $s7, 0x4
    ctx->r14 = ADD32(ctx->r23, 0X4);
    // 0x800998F0: or          $s6, $a0, $zero
    ctx->r22 = ctx->r4 | 0;
    // 0x800998F4: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x800998F8: jal         0x80099858
    // 0x800998FC: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    func_80099858(rdram, ctx);
        goto after_0;
    // 0x800998FC: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    after_0:
    // 0x80099900: addiu       $s3, $s6, 0xA
    ctx->r19 = ADD32(ctx->r22, 0XA);
    // 0x80099904: addiu       $s1, $zero, 0x1
    ctx->r17 = ADD32(0, 0X1);
    // 0x80099908: addiu       $s6, $zero, -0x1
    ctx->r22 = ADD32(0, -0X1);
    // 0x8009990C: or          $s0, $s7, $zero
    ctx->r16 = ctx->r23 | 0;
    // 0x80099910: lb          $s2, 0x0($s7)
    ctx->r18 = MEM_B(ctx->r23, 0X0);
    // 0x80099914: addiu       $s4, $s7, 0x4
    ctx->r20 = ADD32(ctx->r23, 0X4);
L_80099918:
    // 0x80099918: sll         $a1, $s2, 24
    ctx->r5 = S32(ctx->r18 << 24);
L_8009991C:
    // 0x8009991C: sra         $t7, $a1, 24
    ctx->r15 = S32(SIGNED(ctx->r5) >> 24);
    // 0x80099920: lbu         $a2, 0x1($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X1);
    // 0x80099924: lb          $a3, 0x2($s0)
    ctx->r7 = MEM_B(ctx->r16, 0X2);
    // 0x80099928: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x8009992C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x80099930: or          $a1, $t7, $zero
    ctx->r5 = ctx->r15 | 0;
    // 0x80099934: jal         0x80099858
    // 0x80099938: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    func_80099858(rdram, ctx);
        goto after_1;
    // 0x80099938: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_1:
    // 0x8009993C: lb          $s2, 0xA($s0)
    ctx->r18 = MEM_B(ctx->r16, 0XA);
    // 0x80099940: addiu       $s1, $s1, 0x1
    ctx->r17 = ADD32(ctx->r17, 0X1);
    // 0x80099944: addiu       $s3, $s3, 0xA
    ctx->r19 = ADD32(ctx->r19, 0XA);
    // 0x80099948: addiu       $s0, $s0, 0xA
    ctx->r16 = ADD32(ctx->r16, 0XA);
    // 0x8009994C: bne         $s6, $s2, L_80099918
    if (ctx->r22 != ctx->r18) {
        // 0x80099950: addiu       $s4, $s4, 0xA
        ctx->r20 = ADD32(ctx->r20, 0XA);
            goto L_80099918;
    }
    // 0x80099950: addiu       $s4, $s4, 0xA
    ctx->r20 = ADD32(ctx->r20, 0XA);
    // 0x80099954: addiu       $t8, $s1, 0x3
    ctx->r24 = ADD32(ctx->r17, 0X3);
    // 0x80099958: slti        $at, $t8, 0x1F
    ctx->r1 = SIGNED(ctx->r24) < 0X1F ? 1 : 0;
    // 0x8009995C: beql        $at, $zero, L_8009991C
    if (ctx->r1 == 0) {
        // 0x80099960: sll         $a1, $s2, 24
        ctx->r5 = S32(ctx->r18 << 24);
            goto L_8009991C;
    }
    goto skip_0;
    // 0x80099960: sll         $a1, $s2, 24
    ctx->r5 = S32(ctx->r18 << 24);
    skip_0:
    // 0x80099964: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
    // 0x80099968: lbu         $a2, 0x1($s0)
    ctx->r6 = MEM_BU(ctx->r16, 0X1);
    // 0x8009996C: lb          $a3, 0x2($s0)
    ctx->r7 = MEM_B(ctx->r16, 0X2);
    // 0x80099970: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x80099974: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x80099978: jal         0x80099858
    // 0x8009997C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    func_80099858(rdram, ctx);
        goto after_2;
    // 0x8009997C: or          $a0, $s3, $zero
    ctx->r4 = ctx->r19 | 0;
    after_2:
    // 0x80099980: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
    // 0x80099984: lb          $a3, 0x2($s0)
    ctx->r7 = MEM_B(ctx->r16, 0X2);
    // 0x80099988: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x8009998C: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x80099990: addiu       $a0, $s3, 0xA
    ctx->r4 = ADD32(ctx->r19, 0XA);
    // 0x80099994: jal         0x80099858
    // 0x80099998: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_80099858(rdram, ctx);
        goto after_3;
    // 0x80099998: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_3:
    // 0x8009999C: lb          $a1, 0x0($s7)
    ctx->r5 = MEM_B(ctx->r23, 0X0);
    // 0x800999A0: lb          $a3, 0x2($s0)
    ctx->r7 = MEM_B(ctx->r16, 0X2);
    // 0x800999A4: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x800999A8: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x800999AC: addiu       $a0, $s3, 0x14
    ctx->r4 = ADD32(ctx->r19, 0X14);
    // 0x800999B0: jal         0x80099858
    // 0x800999B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_80099858(rdram, ctx);
        goto after_4;
    // 0x800999B4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_4:
    // 0x800999B8: lb          $a3, 0x2($s0)
    ctx->r7 = MEM_B(ctx->r16, 0X2);
    // 0x800999BC: sw          $s5, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r21;
    // 0x800999C0: sw          $s4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r20;
    // 0x800999C4: addiu       $a0, $s3, 0x1E
    ctx->r4 = ADD32(ctx->r19, 0X1E);
    // 0x800999C8: addiu       $a1, $zero, -0x1
    ctx->r5 = ADD32(0, -0X1);
    // 0x800999CC: jal         0x80099858
    // 0x800999D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    func_80099858(rdram, ctx);
        goto after_5;
    // 0x800999D0: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    after_5:
    // 0x800999D4: lw          $ra, 0x3C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X3C);
    // 0x800999D8: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x800999DC: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x800999E0: lw          $s2, 0x24($sp)
    ctx->r18 = MEM_W(ctx->r29, 0X24);
    // 0x800999E4: lw          $s3, 0x28($sp)
    ctx->r19 = MEM_W(ctx->r29, 0X28);
    // 0x800999E8: lw          $s4, 0x2C($sp)
    ctx->r20 = MEM_W(ctx->r29, 0X2C);
    // 0x800999EC: lw          $s5, 0x30($sp)
    ctx->r21 = MEM_W(ctx->r29, 0X30);
    // 0x800999F0: lw          $s6, 0x34($sp)
    ctx->r22 = MEM_W(ctx->r29, 0X34);
    // 0x800999F4: lw          $s7, 0x38($sp)
    ctx->r23 = MEM_W(ctx->r29, 0X38);
    // 0x800999F8: jr          $ra
    // 0x800999FC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
    return;
    // 0x800999FC: addiu       $sp, $sp, 0x40
    ctx->r29 = ADD32(ctx->r29, 0X40);
;}
RECOMP_FUNC void func_80099A00(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099A00: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x80099A04: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x80099A08: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x80099A0C: sw          $a2, 0x38($sp)
    MEM_W(0X38, ctx->r29) = ctx->r6;
    // 0x80099A10: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80099A14: sw          $a3, 0x3C($sp)
    MEM_W(0X3C, ctx->r29) = ctx->r7;
    // 0x80099A18: addiu       $a0, $a0, -0x12A0
    ctx->r4 = ADD32(ctx->r4, -0X12A0);
    // 0x80099A1C: jal         0x800998B0
    // 0x80099A20: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    func_800998B0(rdram, ctx);
        goto after_0;
    // 0x80099A20: or          $a2, $a3, $zero
    ctx->r6 = ctx->r7 | 0;
    after_0:
    // 0x80099A24: lui         $a0, 0x801D
    ctx->r4 = S32(0X801D << 16);
    // 0x80099A28: addiu       $a0, $a0, -0x1160
    ctx->r4 = ADD32(ctx->r4, -0X1160);
    // 0x80099A2C: lw          $a1, 0x38($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X38);
    // 0x80099A30: jal         0x800998B0
    // 0x80099A34: lw          $a2, 0x3C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X3C);
    func_800998B0(rdram, ctx);
        goto after_1;
    // 0x80099A34: lw          $a2, 0x3C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X3C);
    after_1:
    // 0x80099A38: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80099A3C: lw          $v1, 0x5138($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5138);
    // 0x80099A40: lw          $v0, 0x30($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X30);
    // 0x80099A44: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x80099A48: addiu       $t9, $t9, -0x1020
    ctx->r25 = ADD32(ctx->r25, -0X1020);
    // 0x80099A4C: lui         $t7, 0x801D
    ctx->r15 = S32(0X801D << 16);
    // 0x80099A50: sll         $t8, $v1, 2
    ctx->r24 = S32(ctx->r3 << 2);
    // 0x80099A54: addu        $t0, $t8, $t9
    ctx->r8 = ADD32(ctx->r24, ctx->r25);
    // 0x80099A58: addiu       $t7, $t7, -0x1018
    ctx->r15 = ADD32(ctx->r15, -0X1018);
    // 0x80099A5C: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x80099A60: sll         $t6, $v1, 1
    ctx->r14 = S32(ctx->r3 << 1);
    // 0x80099A64: addiu       $a1, $v0, 0x18
    ctx->r5 = ADD32(ctx->r2, 0X18);
    // 0x80099A68: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x80099A6C: addu        $a3, $t6, $t7
    ctx->r7 = ADD32(ctx->r14, ctx->r15);
    // 0x80099A70: addiu       $a2, $a2, -0x12A0
    ctx->r6 = ADD32(ctx->r6, -0X12A0);
    // 0x80099A74: sw          $t0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r8;
    // 0x80099A78: jal         0x80099514
    // 0x80099A7C: addiu       $a0, $v0, 0xC
    ctx->r4 = ADD32(ctx->r2, 0XC);
    func_80099514(rdram, ctx);
        goto after_2;
    // 0x80099A7C: addiu       $a0, $v0, 0xC
    ctx->r4 = ADD32(ctx->r2, 0XC);
    after_2:
    // 0x80099A80: lui         $v1, 0x800E
    ctx->r3 = S32(0X800E << 16);
    // 0x80099A84: lw          $v1, 0x5138($v1)
    ctx->r3 = MEM_W(ctx->r3, 0X5138);
    // 0x80099A88: lui         $t4, 0x801D
    ctx->r12 = S32(0X801D << 16);
    // 0x80099A8C: addiu       $t4, $t4, -0x1020
    ctx->r12 = ADD32(ctx->r12, -0X1020);
    // 0x80099A90: lui         $t2, 0x801D
    ctx->r10 = S32(0X801D << 16);
    // 0x80099A94: sll         $t3, $v1, 2
    ctx->r11 = S32(ctx->r3 << 2);
    // 0x80099A98: addu        $t5, $t3, $t4
    ctx->r13 = ADD32(ctx->r11, ctx->r12);
    // 0x80099A9C: addiu       $t2, $t2, -0x1018
    ctx->r10 = ADD32(ctx->r10, -0X1018);
    // 0x80099AA0: lui         $a2, 0x801D
    ctx->r6 = S32(0X801D << 16);
    // 0x80099AA4: sll         $t1, $v1, 1
    ctx->r9 = S32(ctx->r3 << 1);
    // 0x80099AA8: addu        $a3, $t1, $t2
    ctx->r7 = ADD32(ctx->r9, ctx->r10);
    // 0x80099AAC: addiu       $a2, $a2, -0x1160
    ctx->r6 = ADD32(ctx->r6, -0X1160);
    // 0x80099AB0: sw          $t5, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r13;
    // 0x80099AB4: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x80099AB8: sw          $v0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r2;
    // 0x80099ABC: jal         0x80099514
    // 0x80099AC0: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    func_80099514(rdram, ctx);
        goto after_3;
    // 0x80099AC0: lw          $a0, 0x30($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X30);
    after_3:
    // 0x80099AC4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x80099AC8: lw          $t6, 0x28($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X28);
    // 0x80099ACC: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x80099AD0: jr          $ra
    // 0x80099AD4: or          $v0, $v0, $t6
    ctx->r2 = ctx->r2 | ctx->r14;
    return;
    // 0x80099AD4: or          $v0, $v0, $t6
    ctx->r2 = ctx->r2 | ctx->r14;
;}
RECOMP_FUNC void func_80099AD8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099AD8: mtc1        $a2, $f12
    ctx->f12.u32l = ctx->r6;
    // 0x80099ADC: mtc1        $a3, $f14
    ctx->f14.u32l = ctx->r7;
    // 0x80099AE0: bltz        $a0, L_80099B18
    if (SIGNED(ctx->r4) < 0) {
        // 0x80099AE4: slti        $at, $a0, 0x3
        ctx->r1 = SIGNED(ctx->r4) < 0X3 ? 1 : 0;
            goto L_80099B18;
    }
    // 0x80099AE4: slti        $at, $a0, 0x3
    ctx->r1 = SIGNED(ctx->r4) < 0X3 ? 1 : 0;
    // 0x80099AE8: beq         $at, $zero, L_80099B18
    if (ctx->r1 == 0) {
        // 0x80099AEC: sll         $t6, $a0, 2
        ctx->r14 = S32(ctx->r4 << 2);
            goto L_80099B18;
    }
    // 0x80099AEC: sll         $t6, $a0, 2
    ctx->r14 = S32(ctx->r4 << 2);
    // 0x80099AF0: addu        $v0, $a1, $t6
    ctx->r2 = ADD32(ctx->r5, ctx->r14);
    // 0x80099AF4: lwc1        $f4, 0x44($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X44);
    // 0x80099AF8: c.lt.s      $f4, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f4.fl < ctx->f12.fl;
    // 0x80099AFC: nop

    // 0x80099B00: bc1f        L_80099B18
    if (!c1cs) {
        // 0x80099B04: nop
    
            goto L_80099B18;
    }
    // 0x80099B04: nop

    // 0x80099B08: swc1        $f12, 0x44($v0)
    MEM_W(0X44, ctx->r2) = ctx->f12.u32l;
    // 0x80099B0C: swc1        $f14, 0x68($v0)
    MEM_W(0X68, ctx->r2) = ctx->f14.u32l;
    // 0x80099B10: lwc1        $f6, 0x10($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X10);
    // 0x80099B14: swc1        $f6, 0x5C($v0)
    MEM_W(0X5C, ctx->r2) = ctx->f6.u32l;
L_80099B18:
    // 0x80099B18: jr          $ra
    // 0x80099B1C: nop

    return;
    // 0x80099B1C: nop

;}
RECOMP_FUNC void func_80099B20(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099B20: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x80099B24: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x80099B28: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80099B2C: nop

    // 0x80099B30: c.eq.s      $f12, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f12.fl == ctx->f4.fl;
    // 0x80099B34: nop

    // 0x80099B38: bc1fl       L_80099B7C
    if (!c1cs) {
        // 0x80099B3C: lwc1        $f18, 0x0($a0)
        ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
            goto L_80099B7C;
    }
    goto skip_0;
    // 0x80099B3C: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
    skip_0:
    // 0x80099B40: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x80099B44: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80099B48: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x80099B4C: c.lt.s      $f6, $f8
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f6.fl < ctx->f8.fl;
    // 0x80099B50: nop

    // 0x80099B54: bc1fl       L_80099B70
    if (!c1cs) {
        // 0x80099B58: mtc1        $at, $f16
        ctx->f16.u32l = ctx->r1;
            goto L_80099B70;
    }
    goto skip_1;
    // 0x80099B58: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    skip_1:
    // 0x80099B5C: lui         $at, 0xC2B4
    ctx->r1 = S32(0XC2B4 << 16);
    // 0x80099B60: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80099B64: b           L_80099B84
    // 0x80099B68: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
        goto L_80099B84;
    // 0x80099B68: swc1        $f10, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f10.u32l;
    // 0x80099B6C: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
L_80099B70:
    // 0x80099B70: b           L_80099B84
    // 0x80099B74: swc1        $f16, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f16.u32l;
        goto L_80099B84;
    // 0x80099B74: swc1        $f16, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f16.u32l;
    // 0x80099B78: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
L_80099B7C:
    // 0x80099B7C: add.s       $f4, $f18, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f12.fl;
    // 0x80099B80: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
L_80099B84:
    // 0x80099B84: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80099B88: mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // 0x80099B8C: lwc1        $f0, 0x0($a0)
    ctx->f0.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80099B90: div.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f6.fl = DIV_S(ctx->f0.fl, ctx->f2.fl);
    // 0x80099B94: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80099B98: mfc1        $t7, $f8
    ctx->r15 = (int32_t)ctx->f8.u32l;
    // 0x80099B9C: nop

    // 0x80099BA0: mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // 0x80099BA4: nop

    // 0x80099BA8: cvt.s.w     $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    ctx->f16.fl = CVT_S_W(ctx->f10.u32l);
    // 0x80099BAC: mul.s       $f18, $f16, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f18.fl = MUL_S(ctx->f16.fl, ctx->f2.fl);
    // 0x80099BB0: sub.s       $f4, $f0, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f0.fl - ctx->f18.fl;
    // 0x80099BB4: jr          $ra
    // 0x80099BB8: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
    return;
    // 0x80099BB8: swc1        $f4, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f4.u32l;
;}
RECOMP_FUNC void func_80099BBC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099BBC: addiu       $sp, $sp, -0x60
    ctx->r29 = ADD32(ctx->r29, -0X60);
    // 0x80099BC0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80099BC4: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x80099BC8: sw          $a0, 0x60($sp)
    MEM_W(0X60, ctx->r29) = ctx->r4;
    // 0x80099BCC: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x80099BD0: sw          $a1, 0x64($sp)
    MEM_W(0X64, ctx->r29) = ctx->r5;
    // 0x80099BD4: or          $s1, $a2, $zero
    ctx->r17 = ctx->r6 | 0;
    // 0x80099BD8: lw          $a1, 0x4C($a2)
    ctx->r5 = MEM_W(ctx->r6, 0X4C);
    // 0x80099BDC: lw          $a2, 0x50($a2)
    ctx->r6 = MEM_W(ctx->r6, 0X50);
    // 0x80099BE0: lw          $a3, 0x54($s1)
    ctx->r7 = MEM_W(ctx->r17, 0X54);
    // 0x80099BE4: jal         0x800984F4
    // 0x80099BE8: addiu       $a0, $sp, 0x40
    ctx->r4 = ADD32(ctx->r29, 0X40);
    Math_Vec3f_Set(rdram, ctx);
        goto after_0;
    // 0x80099BE8: addiu       $a0, $sp, 0x40
    ctx->r4 = ADD32(ctx->r29, 0X40);
    after_0:
    // 0x80099BEC: addiu       $a0, $sp, 0x34
    ctx->r4 = ADD32(ctx->r29, 0X34);
    // 0x80099BF0: lw          $a1, 0x7C($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X7C);
    // 0x80099BF4: lw          $a2, 0x80($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X80);
    // 0x80099BF8: jal         0x800984F4
    // 0x80099BFC: lw          $a3, 0x84($s1)
    ctx->r7 = MEM_W(ctx->r17, 0X84);
    Math_Vec3f_Set(rdram, ctx);
        goto after_1;
    // 0x80099BFC: lw          $a3, 0x84($s1)
    ctx->r7 = MEM_W(ctx->r17, 0X84);
    after_1:
    // 0x80099C00: lw          $v1, 0x60($sp)
    ctx->r3 = MEM_W(ctx->r29, 0X60);
    // 0x80099C04: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x80099C08: lw          $v0, 0x64($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X64);
    // 0x80099C0C: beql        $v1, $zero, L_80099C20
    if (ctx->r3 == 0) {
        // 0x80099C10: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_80099C20;
    }
    goto skip_0;
    // 0x80099C10: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_0:
    // 0x80099C14: bnel        $v1, $at, L_80099D84
    if (ctx->r3 != ctx->r1) {
        // 0x80099C18: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_80099D84;
    }
    goto skip_1;
    // 0x80099C18: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_1:
    // 0x80099C1C: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_80099C20:
    // 0x80099C20: lwc1        $f4, 0x44($v0)
    ctx->f4.u32l = MEM_W(ctx->r2, 0X44);
    // 0x80099C24: addiu       $a0, $sp, 0x40
    ctx->r4 = ADD32(ctx->r29, 0X40);
    // 0x80099C28: addiu       $a1, $sp, 0x34
    ctx->r5 = ADD32(ctx->r29, 0X34);
    // 0x80099C2C: c.eq.s      $f0, $f4
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    c1cs = ctx->f0.fl == ctx->f4.fl;
    // 0x80099C30: addiu       $a2, $sp, 0x5C
    ctx->r6 = ADD32(ctx->r29, 0X5C);
    // 0x80099C34: addiu       $a3, $sp, 0x4C
    ctx->r7 = ADD32(ctx->r29, 0X4C);
    // 0x80099C38: addiu       $t6, $sp, 0x50
    ctx->r14 = ADD32(ctx->r29, 0X50);
    // 0x80099C3C: bc1f        L_80099C58
    if (!c1cs) {
        // 0x80099C40: nop
    
            goto L_80099C58;
    }
    // 0x80099C40: nop

    // 0x80099C44: lwc1        $f6, 0x48($v0)
    ctx->f6.u32l = MEM_W(ctx->r2, 0X48);
    // 0x80099C48: c.eq.s      $f0, $f6
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f0.fl == ctx->f6.fl;
    // 0x80099C4C: nop

    // 0x80099C50: bc1tl       L_80099D6C
    if (c1cs) {
        // 0x80099C54: lwc1        $f8, 0x34($sp)
        ctx->f8.u32l = MEM_W(ctx->r29, 0X34);
            goto L_80099D6C;
    }
    goto skip_2;
    // 0x80099C54: lwc1        $f8, 0x34($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X34);
    skip_2:
L_80099C58:
    // 0x80099C58: jal         0x80098FF8
    // 0x80099C5C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_80098FF8(rdram, ctx);
        goto after_2;
    // 0x80099C5C: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_2:
    // 0x80099C60: lw          $v0, 0x60($sp)
    ctx->r2 = MEM_W(ctx->r29, 0X60);
    // 0x80099C64: lw          $t9, 0x64($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X64);
    // 0x80099C68: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80099C6C: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x80099C70: addu        $s0, $t9, $t7
    ctx->r16 = ADD32(ctx->r25, ctx->r15);
    // 0x80099C74: lwc1        $f8, 0x50($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X50);
    // 0x80099C78: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80099C7C: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80099C80: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x80099C84: div.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = DIV_S(ctx->f8.fl, ctx->f10.fl);
    // 0x80099C88: lui         $at, 0x8015
    ctx->r1 = S32(0X8015 << 16);
    // 0x80099C8C: lwc1        $f10, 0x44($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X44);
    // 0x80099C90: addiu       $t8, $sp, 0x4C
    ctx->r24 = ADD32(ctx->r29, 0X4C);
    // 0x80099C94: addu        $v1, $t7, $t8
    ctx->r3 = ADD32(ctx->r15, ctx->r24);
    // 0x80099C98: mul.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = MUL_S(ctx->f16.fl, ctx->f18.fl);
    // 0x80099C9C: lwc1        $f18, 0x0($v1)
    ctx->f18.u32l = MEM_W(ctx->r3, 0X0);
    // 0x80099CA0: trunc.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = TRUNC_W_S(ctx->f4.fl);
    // 0x80099CA4: mfc1        $t1, $f6
    ctx->r9 = (int32_t)ctx->f6.u32l;
    // 0x80099CA8: nop

    // 0x80099CAC: andi        $t2, $t1, 0xFFF
    ctx->r10 = ctx->r9 & 0XFFF;
    // 0x80099CB0: sll         $t3, $t2, 2
    ctx->r11 = S32(ctx->r10 << 2);
    // 0x80099CB4: addu        $at, $at, $t3
    ctx->r1 = ADD32(ctx->r1, ctx->r11);
    // 0x80099CB8: lwc1        $f8, 0x4350($at)
    ctx->f8.u32l = MEM_W(ctx->r1, 0X4350);
    // 0x80099CBC: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x80099CC0: mul.s       $f16, $f10, $f8
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f8.fl);
    // 0x80099CC4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80099CC8: add.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = ctx->f18.fl + ctx->f16.fl;
    // 0x80099CCC: swc1        $f4, 0x0($v1)
    MEM_W(0X0, ctx->r3) = ctx->f4.u32l;
    // 0x80099CD0: lwc1        $f6, 0x4C($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80099CD4: jal         0x800984D0
    // 0x80099CD8: sub.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl - ctx->f10.fl;
    Math_Fabs(rdram, ctx);
        goto after_3;
    // 0x80099CD8: sub.s       $f12, $f6, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f6.fl - ctx->f10.fl;
    after_3:
    // 0x80099CDC: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x80099CE0: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80099CE4: lui         $at, 0x4387
    ctx->r1 = S32(0X4387 << 16);
    // 0x80099CE8: lwc1        $f18, 0x4C($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X4C);
    // 0x80099CEC: c.lt.s      $f8, $f0
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f8.fl < ctx->f0.fl;
    // 0x80099CF0: nop

    // 0x80099CF4: bc1fl       L_80099D3C
    if (!c1cs) {
        // 0x80099CF8: addiu       $a0, $s0, 0x50
        ctx->r4 = ADD32(ctx->r16, 0X50);
            goto L_80099D3C;
    }
    goto skip_3;
    // 0x80099CF8: addiu       $a0, $s0, 0x50
    ctx->r4 = ADD32(ctx->r16, 0X50);
    skip_3:
    // 0x80099CFC: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80099D00: jal         0x800984D0
    // 0x80099D04: sub.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f16.fl;
    Math_Fabs(rdram, ctx);
        goto after_4;
    // 0x80099D04: sub.s       $f12, $f18, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f16.fl;
    after_4:
    // 0x80099D08: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x80099D0C: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80099D10: addiu       $a0, $sp, 0x40
    ctx->r4 = ADD32(ctx->r29, 0X40);
    // 0x80099D14: addiu       $a1, $sp, 0x34
    ctx->r5 = ADD32(ctx->r29, 0X34);
    // 0x80099D18: c.lt.s      $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f4.fl < ctx->f0.fl;
    // 0x80099D1C: lw          $a2, 0x5C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X5C);
    // 0x80099D20: lwc1        $f6, 0x50($sp)
    ctx->f6.u32l = MEM_W(ctx->r29, 0X50);
    // 0x80099D24: bc1fl       L_80099D3C
    if (!c1cs) {
        // 0x80099D28: addiu       $a0, $s0, 0x50
        ctx->r4 = ADD32(ctx->r16, 0X50);
            goto L_80099D3C;
    }
    goto skip_4;
    // 0x80099D28: addiu       $a0, $s0, 0x50
    ctx->r4 = ADD32(ctx->r16, 0X50);
    skip_4:
    // 0x80099D2C: lw          $a3, 0x4C($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X4C);
    // 0x80099D30: jal         0x800990A8
    // 0x80099D34: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    func_800990A8(rdram, ctx);
        goto after_5;
    // 0x80099D34: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    after_5:
    // 0x80099D38: addiu       $a0, $s0, 0x50
    ctx->r4 = ADD32(ctx->r16, 0X50);
L_80099D3C:
    // 0x80099D3C: jal         0x80099B20
    // 0x80099D40: lw          $a1, 0x5C($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X5C);
    func_80099B20(rdram, ctx);
        goto after_6;
    // 0x80099D40: lw          $a1, 0x5C($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X5C);
    after_6:
    // 0x80099D44: addiu       $a0, $s0, 0x44
    ctx->r4 = ADD32(ctx->r16, 0X44);
    // 0x80099D48: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x80099D4C: jal         0x80098820
    // 0x80099D50: lw          $a2, 0x68($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X68);
    func_80098820(rdram, ctx);
        goto after_7;
    // 0x80099D50: lw          $a2, 0x68($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X68);
    after_7:
    // 0x80099D54: bnel        $v0, $zero, L_80099D6C
    if (ctx->r2 != 0) {
        // 0x80099D58: lwc1        $f8, 0x34($sp)
        ctx->f8.u32l = MEM_W(ctx->r29, 0X34);
            goto L_80099D6C;
    }
    goto skip_5;
    // 0x80099D58: lwc1        $f8, 0x34($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X34);
    skip_5:
    // 0x80099D5C: mtc1        $zero, $f10
    ctx->f10.u32l = 0;
    // 0x80099D60: nop

    // 0x80099D64: swc1        $f10, 0x50($s0)
    MEM_W(0X50, ctx->r16) = ctx->f10.u32l;
    // 0x80099D68: lwc1        $f8, 0x34($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X34);
L_80099D6C:
    // 0x80099D6C: swc1        $f8, 0x7C($s1)
    MEM_W(0X7C, ctx->r17) = ctx->f8.u32l;
    // 0x80099D70: lwc1        $f18, 0x38($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X38);
    // 0x80099D74: swc1        $f18, 0x80($s1)
    MEM_W(0X80, ctx->r17) = ctx->f18.u32l;
    // 0x80099D78: lwc1        $f16, 0x3C($sp)
    ctx->f16.u32l = MEM_W(ctx->r29, 0X3C);
    // 0x80099D7C: swc1        $f16, 0x84($s1)
    MEM_W(0X84, ctx->r17) = ctx->f16.u32l;
    // 0x80099D80: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_80099D84:
    // 0x80099D84: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x80099D88: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x80099D8C: jr          $ra
    // 0x80099D90: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
    return;
    // 0x80099D90: addiu       $sp, $sp, 0x60
    ctx->r29 = ADD32(ctx->r29, 0X60);
;}
RECOMP_FUNC void func_80099D94(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x80099D94: addiu       $sp, $sp, -0x88
    ctx->r29 = ADD32(ctx->r29, -0X88);
    // 0x80099D98: sw          $s1, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r17;
    // 0x80099D9C: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x80099DA0: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x80099DA4: sw          $s0, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r16;
    // 0x80099DA8: or          $s0, $a1, $zero
    ctx->r16 = ctx->r5 | 0;
    // 0x80099DAC: jal         0x80098514
    // 0x80099DB0: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    Math_Vec3f_Initialize(rdram, ctx);
        goto after_0;
    // 0x80099DB0: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    after_0:
    // 0x80099DB4: addiu       $a0, $sp, 0x2C
    ctx->r4 = ADD32(ctx->r29, 0X2C);
    // 0x80099DB8: lw          $a1, 0x70($s0)
    ctx->r5 = MEM_W(ctx->r16, 0X70);
    // 0x80099DBC: lw          $a2, 0x74($s0)
    ctx->r6 = MEM_W(ctx->r16, 0X74);
    // 0x80099DC0: jal         0x800984F4
    // 0x80099DC4: lw          $a3, 0x78($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X78);
    Math_Vec3f_Set(rdram, ctx);
        goto after_1;
    // 0x80099DC4: lw          $a3, 0x78($s0)
    ctx->r7 = MEM_W(ctx->r16, 0X78);
    after_1:
    // 0x80099DC8: mtc1        $zero, $f4
    ctx->f4.u32l = 0;
    // 0x80099DCC: lwc1        $f6, 0x4C($s1)
    ctx->f6.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x80099DD0: c.eq.s      $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    c1cs = ctx->f4.fl == ctx->f6.fl;
    // 0x80099DD4: nop

    // 0x80099DD8: bc1tl       L_8009A03C
    if (c1cs) {
        // 0x80099DDC: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_8009A03C;
    }
    goto skip_0;
    // 0x80099DDC: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x80099DE0: lwc1        $f16, 0x80($s0)
    ctx->f16.u32l = MEM_W(ctx->r16, 0X80);
    // 0x80099DE4: lwc1        $f18, 0x50($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0X50);
    // 0x80099DE8: lwc1        $f8, 0x7C($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X7C);
    // 0x80099DEC: lwc1        $f10, 0x4C($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X4C);
    // 0x80099DF0: sub.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl - ctx->f18.fl;
    // 0x80099DF4: sub.s       $f0, $f8, $f10
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f0.fl = ctx->f8.fl - ctx->f10.fl;
    // 0x80099DF8: swc1        $f4, 0x70($sp)
    MEM_W(0X70, ctx->r29) = ctx->f4.u32l;
    // 0x80099DFC: lwc1        $f8, 0x54($s0)
    ctx->f8.u32l = MEM_W(ctx->r16, 0X54);
    // 0x80099E00: lwc1        $f6, 0x84($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0X84);
    // 0x80099E04: mul.s       $f10, $f0, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = MUL_S(ctx->f0.fl, ctx->f0.fl);
    // 0x80099E08: swc1        $f0, 0x74($sp)
    MEM_W(0X74, ctx->r29) = ctx->f0.u32l;
    // 0x80099E0C: sub.s       $f2, $f6, $f8
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f2.fl = ctx->f6.fl - ctx->f8.fl;
    // 0x80099E10: mul.s       $f16, $f2, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f2.fl); 
    ctx->f16.fl = MUL_S(ctx->f2.fl, ctx->f2.fl);
    // 0x80099E14: swc1        $f2, 0x6C($sp)
    MEM_W(0X6C, ctx->r29) = ctx->f2.u32l;
    // 0x80099E18: jal         0x800C7010
    // 0x80099E1C: add.s       $f12, $f10, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f16.fl;
    _nsqrtf(rdram, ctx);
        goto after_2;
    // 0x80099E1C: add.s       $f12, $f10, $f16
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f12.fl = ctx->f10.fl + ctx->f16.fl;
    after_2:
    // 0x80099E20: lwc1        $f12, 0x70($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X70);
    // 0x80099E24: jal         0x801ED154
    // 0x80099E28: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    func_801ED154(rdram, ctx);
        goto after_3;
    // 0x80099E28: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    after_3:
    // 0x80099E2C: swc1        $f0, 0x80($sp)
    MEM_W(0X80, ctx->r29) = ctx->f0.u32l;
    // 0x80099E30: lwc1        $f12, 0x74($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X74);
    // 0x80099E34: jal         0x801ED154
    // 0x80099E38: lwc1        $f14, 0x6C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X6C);
    func_801ED154(rdram, ctx);
        goto after_4;
    // 0x80099E38: lwc1        $f14, 0x6C($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X6C);
    after_4:
    // 0x80099E3C: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x80099E40: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x80099E44: lwc1        $f18, 0x80($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X80);
    // 0x80099E48: swc1        $f0, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->f0.u32l;
    // 0x80099E4C: jal         0x800984D0
    // 0x80099E50: sub.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f4.fl;
    Math_Fabs(rdram, ctx);
        goto after_5;
    // 0x80099E50: sub.s       $f12, $f18, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f12.fl = ctx->f18.fl - ctx->f4.fl;
    after_5:
    // 0x80099E54: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x80099E58: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80099E5C: lui         $at, 0x4387
    ctx->r1 = S32(0X4387 << 16);
    // 0x80099E60: lwc1        $f8, 0x80($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X80);
    // 0x80099E64: c.lt.s      $f6, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f6.fl < ctx->f0.fl;
    // 0x80099E68: nop

    // 0x80099E6C: bc1fl       L_8009A03C
    if (!c1cs) {
        // 0x80099E70: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_8009A03C;
    }
    goto skip_1;
    // 0x80099E70: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_1:
    // 0x80099E74: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x80099E78: jal         0x800984D0
    // 0x80099E7C: sub.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f10.fl;
    Math_Fabs(rdram, ctx);
        goto after_6;
    // 0x80099E7C: sub.s       $f12, $f8, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f12.fl = ctx->f8.fl - ctx->f10.fl;
    after_6:
    // 0x80099E80: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x80099E84: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x80099E88: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    // 0x80099E8C: addiu       $a1, $sp, 0x2C
    ctx->r5 = ADD32(ctx->r29, 0X2C);
    // 0x80099E90: c.lt.s      $f16, $f0
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f16.fl < ctx->f0.fl;
    // 0x80099E94: addiu       $a2, $sp, 0x5C
    ctx->r6 = ADD32(ctx->r29, 0X5C);
    // 0x80099E98: addiu       $a3, $sp, 0x68
    ctx->r7 = ADD32(ctx->r29, 0X68);
    // 0x80099E9C: addiu       $t6, $sp, 0x64
    ctx->r14 = ADD32(ctx->r29, 0X64);
    // 0x80099EA0: bc1fl       L_8009A03C
    if (!c1cs) {
        // 0x80099EA4: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_8009A03C;
    }
    goto skip_2;
    // 0x80099EA4: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_2:
    // 0x80099EA8: jal         0x80098FF8
    // 0x80099EAC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    func_80098FF8(rdram, ctx);
        goto after_7;
    // 0x80099EAC: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    after_7:
    // 0x80099EB0: lwc1        $f18, 0x64($sp)
    ctx->f18.u32l = MEM_W(ctx->r29, 0X64);
    // 0x80099EB4: lwc1        $f4, 0x7C($sp)
    ctx->f4.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x80099EB8: addiu       $a0, $sp, 0x38
    ctx->r4 = ADD32(ctx->r29, 0X38);
    // 0x80099EBC: addiu       $a1, $sp, 0x2C
    ctx->r5 = ADD32(ctx->r29, 0X2C);
    // 0x80099EC0: sub.s       $f6, $f18, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f6.fl = ctx->f18.fl - ctx->f4.fl;
    // 0x80099EC4: lw          $a2, 0x5C($sp)
    ctx->r6 = MEM_W(ctx->r29, 0X5C);
    // 0x80099EC8: lw          $a3, 0x68($sp)
    ctx->r7 = MEM_W(ctx->r29, 0X68);
    // 0x80099ECC: jal         0x800990A8
    // 0x80099ED0: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    func_800990A8(rdram, ctx);
        goto after_8;
    // 0x80099ED0: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    after_8:
    // 0x80099ED4: lwc1        $f12, 0x2C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x80099ED8: lwc1        $f14, 0x30($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X30);
    // 0x80099EDC: jal         0x801ED154
    // 0x80099EE0: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    func_801ED154(rdram, ctx);
        goto after_9;
    // 0x80099EE0: neg.s       $f12, $f12
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); 
    ctx->f12.fl = -ctx->f12.fl;
    after_9:
    // 0x80099EE4: lui         $at, 0x40E0
    ctx->r1 = S32(0X40E0 << 16);
    // 0x80099EE8: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x80099EEC: lwc1        $f10, 0x74($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0X74);
    // 0x80099EF0: mov.s       $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    ctx->f2.fl = ctx->f0.fl;
    // 0x80099EF4: addiu       $a0, $s1, 0x58
    ctx->r4 = ADD32(ctx->r17, 0X58);
    // 0x80099EF8: c.eq.s      $f8, $f10
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    c1cs = ctx->f8.fl == ctx->f10.fl;
    // 0x80099EFC: nop

    // 0x80099F00: bc1fl       L_80099F14
    if (!c1cs) {
        // 0x80099F04: lw          $a1, 0x64($s1)
        ctx->r5 = MEM_W(ctx->r17, 0X64);
            goto L_80099F14;
    }
    goto skip_3;
    // 0x80099F04: lw          $a1, 0x64($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X64);
    skip_3:
    // 0x80099F08: mtc1        $zero, $f2
    ctx->f2.u32l = 0;
    // 0x80099F0C: nop

    // 0x80099F10: lw          $a1, 0x64($s1)
    ctx->r5 = MEM_W(ctx->r17, 0X64);
L_80099F14:
    // 0x80099F14: jal         0x80099B20
    // 0x80099F18: swc1        $f2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f2.u32l;
    func_80099B20(rdram, ctx);
        goto after_10;
    // 0x80099F18: swc1        $f2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f2.u32l;
    after_10:
    // 0x80099F1C: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80099F20: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x80099F24: lwc1        $f16, 0x58($s1)
    ctx->f16.u32l = MEM_W(ctx->r17, 0X58);
    // 0x80099F28: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80099F2C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x80099F30: div.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = DIV_S(ctx->f16.fl, ctx->f18.fl);
    // 0x80099F34: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x80099F38: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x80099F3C: lwc1        $f18, 0x4C($s1)
    ctx->f18.u32l = MEM_W(ctx->r17, 0X4C);
    // 0x80099F40: lwc1        $f2, 0x78($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X78);
    // 0x80099F44: lw          $a2, 0x70($s1)
    ctx->r6 = MEM_W(ctx->r17, 0X70);
    // 0x80099F48: addiu       $a0, $s1, 0x4C
    ctx->r4 = ADD32(ctx->r17, 0X4C);
    // 0x80099F4C: addiu       $a1, $zero, 0x0
    ctx->r5 = ADD32(0, 0X0);
    // 0x80099F50: mul.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = MUL_S(ctx->f4.fl, ctx->f6.fl);
    // 0x80099F54: trunc.w.s   $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    ctx->f10.u32l = TRUNC_W_S(ctx->f8.fl);
    // 0x80099F58: mfc1        $t8, $f10
    ctx->r24 = (int32_t)ctx->f10.u32l;
    // 0x80099F5C: nop

    // 0x80099F60: andi        $t9, $t8, 0xFFF
    ctx->r25 = ctx->r24 & 0XFFF;
    // 0x80099F64: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x80099F68: addu        $t1, $a3, $t0
    ctx->r9 = ADD32(ctx->r7, ctx->r8);
    // 0x80099F6C: lwc1        $f16, 0x0($t1)
    ctx->f16.u32l = MEM_W(ctx->r9, 0X0);
    // 0x80099F70: mul.s       $f4, $f18, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f4.fl = MUL_S(ctx->f18.fl, ctx->f16.fl);
    // 0x80099F74: add.s       $f2, $f2, $f4
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f2.fl = ctx->f2.fl + ctx->f4.fl;
    // 0x80099F78: jal         0x80098820
    // 0x80099F7C: swc1        $f2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f2.u32l;
    func_80098820(rdram, ctx);
        goto after_11;
    // 0x80099F7C: swc1        $f2, 0x78($sp)
    MEM_W(0X78, ctx->r29) = ctx->f2.u32l;
    after_11:
    // 0x80099F80: lui         $at, 0x43B4
    ctx->r1 = S32(0X43B4 << 16);
    // 0x80099F84: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x80099F88: lui         $at, 0x4580
    ctx->r1 = S32(0X4580 << 16);
    // 0x80099F8C: mtc1        $at, $f12
    ctx->f12.u32l = ctx->r1;
    // 0x80099F90: lui         $a3, 0x8015
    ctx->r7 = S32(0X8015 << 16);
    // 0x80099F94: addiu       $a3, $a3, 0x4350
    ctx->r7 = ADD32(ctx->r7, 0X4350);
    // 0x80099F98: bne         $v0, $zero, L_80099FAC
    if (ctx->r2 != 0) {
        // 0x80099F9C: lwc1        $f2, 0x78($sp)
        ctx->f2.u32l = MEM_W(ctx->r29, 0X78);
            goto L_80099FAC;
    }
    // 0x80099F9C: lwc1        $f2, 0x78($sp)
    ctx->f2.u32l = MEM_W(ctx->r29, 0X78);
    // 0x80099FA0: mtc1        $zero, $f6
    ctx->f6.u32l = 0;
    // 0x80099FA4: nop

    // 0x80099FA8: swc1        $f6, 0x58($s1)
    MEM_W(0X58, ctx->r17) = ctx->f6.u32l;
L_80099FAC:
    // 0x80099FAC: lwc1        $f8, 0x7C($sp)
    ctx->f8.u32l = MEM_W(ctx->r29, 0X7C);
    // 0x80099FB0: div.s       $f4, $f2, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f4.fl = DIV_S(ctx->f2.fl, ctx->f0.fl);
    // 0x80099FB4: div.s       $f10, $f8, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f0.fl); 
    ctx->f10.fl = DIV_S(ctx->f8.fl, ctx->f0.fl);
    // 0x80099FB8: mul.s       $f18, $f10, $f12
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f12.fl);
    // 0x80099FBC: nop

    // 0x80099FC0: mul.s       $f6, $f4, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f12.fl);
    // 0x80099FC4: trunc.w.s   $f16, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    ctx->f16.u32l = TRUNC_W_S(ctx->f18.fl);
    // 0x80099FC8: trunc.w.s   $f8, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    ctx->f8.u32l = TRUNC_W_S(ctx->f6.fl);
    // 0x80099FCC: mfc1        $v0, $f16
    ctx->r2 = (int32_t)ctx->f16.u32l;
    // 0x80099FD0: mfc1        $v1, $f8
    ctx->r3 = (int32_t)ctx->f8.u32l;
    // 0x80099FD4: andi        $t6, $v0, 0xFFF
    ctx->r14 = ctx->r2 & 0XFFF;
    // 0x80099FD8: sll         $t7, $t6, 2
    ctx->r15 = S32(ctx->r14 << 2);
    // 0x80099FDC: andi        $t4, $v1, 0xFFF
    ctx->r12 = ctx->r3 & 0XFFF;
    // 0x80099FE0: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x80099FE4: addu        $a0, $a3, $t5
    ctx->r4 = ADD32(ctx->r7, ctx->r13);
    // 0x80099FE8: addu        $t8, $a3, $t7
    ctx->r24 = ADD32(ctx->r7, ctx->r15);
    // 0x80099FEC: lwc1        $f10, 0x0($t8)
    ctx->f10.u32l = MEM_W(ctx->r24, 0X0);
    // 0x80099FF0: lwc1        $f18, 0x0($a0)
    ctx->f18.u32l = MEM_W(ctx->r4, 0X0);
    // 0x80099FF4: addiu       $t9, $v1, 0x400
    ctx->r25 = ADD32(ctx->r3, 0X400);
    // 0x80099FF8: andi        $t0, $t9, 0xFFF
    ctx->r8 = ctx->r25 & 0XFFF;
    // 0x80099FFC: mul.s       $f16, $f10, $f18
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f16.fl = MUL_S(ctx->f10.fl, ctx->f18.fl);
    // 0x8009A000: sll         $t1, $t0, 2
    ctx->r9 = S32(ctx->r8 << 2);
    // 0x8009A004: addu        $t2, $a3, $t1
    ctx->r10 = ADD32(ctx->r7, ctx->r9);
    // 0x8009A008: addiu       $t3, $v0, 0x400
    ctx->r11 = ADD32(ctx->r2, 0X400);
    // 0x8009A00C: andi        $t4, $t3, 0xFFF
    ctx->r12 = ctx->r11 & 0XFFF;
    // 0x8009A010: sll         $t5, $t4, 2
    ctx->r13 = S32(ctx->r12 << 2);
    // 0x8009A014: addu        $t6, $a3, $t5
    ctx->r14 = ADD32(ctx->r7, ctx->r13);
    // 0x8009A018: swc1        $f16, 0x78($s0)
    MEM_W(0X78, ctx->r16) = ctx->f16.u32l;
    // 0x8009A01C: lwc1        $f4, 0x0($t2)
    ctx->f4.u32l = MEM_W(ctx->r10, 0X0);
    // 0x8009A020: swc1        $f4, 0x74($s0)
    MEM_W(0X74, ctx->r16) = ctx->f4.u32l;
    // 0x8009A024: lwc1        $f8, 0x0($a0)
    ctx->f8.u32l = MEM_W(ctx->r4, 0X0);
    // 0x8009A028: lwc1        $f6, 0x0($t6)
    ctx->f6.u32l = MEM_W(ctx->r14, 0X0);
    // 0x8009A02C: neg.s       $f10, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = -ctx->f8.fl;
    // 0x8009A030: mul.s       $f18, $f6, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f18.fl = MUL_S(ctx->f6.fl, ctx->f10.fl);
    // 0x8009A034: swc1        $f18, 0x70($s0)
    MEM_W(0X70, ctx->r16) = ctx->f18.u32l;
    // 0x8009A038: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_8009A03C:
    // 0x8009A03C: lw          $s0, 0x1C($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A040: lw          $s1, 0x20($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X20);
    // 0x8009A044: jr          $ra
    // 0x8009A048: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
    return;
    // 0x8009A048: addiu       $sp, $sp, 0x88
    ctx->r29 = ADD32(ctx->r29, 0X88);
;}
RECOMP_FUNC void func_8009A04C(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A04C: addiu       $sp, $sp, -0x30
    ctx->r29 = ADD32(ctx->r29, -0X30);
    // 0x8009A050: sll         $t6, $a1, 16
    ctx->r14 = S32(ctx->r5 << 16);
    // 0x8009A054: sra         $t7, $t6, 16
    ctx->r15 = S32(SIGNED(ctx->r14) >> 16);
    // 0x8009A058: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x8009A05C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A060: sw          $a0, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->r4;
    // 0x8009A064: beq         $t7, $at, L_8009A08C
    if (ctx->r15 == ctx->r1) {
        // 0x8009A068: sw          $a1, 0x34($sp)
        MEM_W(0X34, ctx->r29) = ctx->r5;
            goto L_8009A08C;
    }
    // 0x8009A068: sw          $a1, 0x34($sp)
    MEM_W(0X34, ctx->r29) = ctx->r5;
    // 0x8009A06C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x8009A070: beq         $t7, $at, L_8009A104
    if (ctx->r15 == ctx->r1) {
        // 0x8009A074: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_8009A104;
    }
    // 0x8009A074: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009A078: addiu       $at, $zero, 0x5
    ctx->r1 = ADD32(0, 0X5);
    // 0x8009A07C: beq         $t7, $at, L_8009A178
    if (ctx->r15 == ctx->r1) {
        // 0x8009A080: or          $a0, $zero, $zero
        ctx->r4 = 0 | 0;
            goto L_8009A178;
    }
    // 0x8009A080: or          $a0, $zero, $zero
    ctx->r4 = 0 | 0;
    // 0x8009A084: b           L_8009A1C0
    // 0x8009A088: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8009A1C0;
    // 0x8009A088: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A08C:
    // 0x8009A08C: lw          $t8, 0x30($sp)
    ctx->r24 = MEM_W(ctx->r29, 0X30);
    // 0x8009A090: lui         $t1, 0x801D
    ctx->r9 = S32(0X801D << 16);
    // 0x8009A094: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x8009A098: andi        $t9, $t8, 0x1
    ctx->r25 = ctx->r24 & 0X1;
    // 0x8009A09C: sll         $t0, $t9, 2
    ctx->r8 = S32(ctx->r25 << 2);
    // 0x8009A0A0: addu        $t0, $t0, $t9
    ctx->r8 = ADD32(ctx->r8, ctx->r25);
    // 0x8009A0A4: sll         $t0, $t0, 2
    ctx->r8 = S32(ctx->r8 << 2);
    // 0x8009A0A8: subu        $t0, $t0, $t9
    ctx->r8 = SUB32(ctx->r8, ctx->r25);
    // 0x8009A0AC: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009A0B0: sll         $t0, $t0, 3
    ctx->r8 = S32(ctx->r8 << 3);
    // 0x8009A0B4: addiu       $t1, $t1, -0x1550
    ctx->r9 = ADD32(ctx->r9, -0X1550);
    // 0x8009A0B8: addu        $a1, $t0, $t1
    ctx->r5 = ADD32(ctx->r8, ctx->r9);
    // 0x8009A0BC: lui         $a3, 0x3ECC
    ctx->r7 = S32(0X3ECC << 16);
    // 0x8009A0C0: ori         $a3, $a3, 0xCCCD
    ctx->r7 = ctx->r7 | 0XCCCD;
    // 0x8009A0C4: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x8009A0C8: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A0CC: lui         $a2, 0x4040
    ctx->r6 = S32(0X4040 << 16);
    // 0x8009A0D0: jal         0x80099AD8
    // 0x8009A0D4: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    func_80099AD8(rdram, ctx);
        goto after_0;
    // 0x8009A0D4: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    after_0:
    // 0x8009A0D8: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x8009A0DC: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009A0E0: lui         $a3, 0x3E99
    ctx->r7 = S32(0X3E99 << 16);
    // 0x8009A0E4: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x8009A0E8: ori         $a3, $a3, 0x999A
    ctx->r7 = ctx->r7 | 0X999A;
    // 0x8009A0EC: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x8009A0F0: lui         $a2, 0x4000
    ctx->r6 = S32(0X4000 << 16);
    // 0x8009A0F4: jal         0x80099AD8
    // 0x8009A0F8: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    func_80099AD8(rdram, ctx);
        goto after_1;
    // 0x8009A0F8: swc1        $f6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f6.u32l;
    after_1:
    // 0x8009A0FC: b           L_8009A1C0
    // 0x8009A100: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8009A1C0;
    // 0x8009A100: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A104:
    // 0x8009A104: lw          $t2, 0x30($sp)
    ctx->r10 = MEM_W(ctx->r29, 0X30);
    // 0x8009A108: lui         $t5, 0x801D
    ctx->r13 = S32(0X801D << 16);
    // 0x8009A10C: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x8009A110: andi        $t3, $t2, 0x1
    ctx->r11 = ctx->r10 & 0X1;
    // 0x8009A114: sll         $t4, $t3, 2
    ctx->r12 = S32(ctx->r11 << 2);
    // 0x8009A118: addu        $t4, $t4, $t3
    ctx->r12 = ADD32(ctx->r12, ctx->r11);
    // 0x8009A11C: sll         $t4, $t4, 2
    ctx->r12 = S32(ctx->r12 << 2);
    // 0x8009A120: subu        $t4, $t4, $t3
    ctx->r12 = SUB32(ctx->r12, ctx->r11);
    // 0x8009A124: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009A128: sll         $t4, $t4, 3
    ctx->r12 = S32(ctx->r12 << 3);
    // 0x8009A12C: addiu       $t5, $t5, -0x1550
    ctx->r13 = ADD32(ctx->r13, -0X1550);
    // 0x8009A130: addu        $a1, $t4, $t5
    ctx->r5 = ADD32(ctx->r12, ctx->r13);
    // 0x8009A134: lui         $a3, 0x3E4C
    ctx->r7 = S32(0X3E4C << 16);
    // 0x8009A138: ori         $a3, $a3, 0xCCCD
    ctx->r7 = ctx->r7 | 0XCCCD;
    // 0x8009A13C: sw          $a1, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r5;
    // 0x8009A140: lui         $a2, 0x40A0
    ctx->r6 = S32(0X40A0 << 16);
    // 0x8009A144: jal         0x80099AD8
    // 0x8009A148: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
    func_80099AD8(rdram, ctx);
        goto after_2;
    // 0x8009A148: swc1        $f8, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f8.u32l;
    after_2:
    // 0x8009A14C: lui         $at, 0x41A0
    ctx->r1 = S32(0X41A0 << 16);
    // 0x8009A150: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8009A154: lui         $a3, 0x3E99
    ctx->r7 = S32(0X3E99 << 16);
    // 0x8009A158: lw          $a1, 0x24($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X24);
    // 0x8009A15C: ori         $a3, $a3, 0x999A
    ctx->r7 = ctx->r7 | 0X999A;
    // 0x8009A160: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x8009A164: lui         $a2, 0x4080
    ctx->r6 = S32(0X4080 << 16);
    // 0x8009A168: jal         0x80099AD8
    // 0x8009A16C: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    func_80099AD8(rdram, ctx);
        goto after_3;
    // 0x8009A16C: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    after_3:
    // 0x8009A170: b           L_8009A1C0
    // 0x8009A174: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8009A1C0;
    // 0x8009A174: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A178:
    // 0x8009A178: lw          $t6, 0x30($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X30);
    // 0x8009A17C: lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // 0x8009A180: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x8009A184: andi        $t7, $t6, 0x1
    ctx->r15 = ctx->r14 & 0X1;
    // 0x8009A188: sll         $t8, $t7, 2
    ctx->r24 = S32(ctx->r15 << 2);
    // 0x8009A18C: addu        $t8, $t8, $t7
    ctx->r24 = ADD32(ctx->r24, ctx->r15);
    // 0x8009A190: sll         $t8, $t8, 2
    ctx->r24 = S32(ctx->r24 << 2);
    // 0x8009A194: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A198: lui         $t9, 0x801D
    ctx->r25 = S32(0X801D << 16);
    // 0x8009A19C: addiu       $t9, $t9, -0x1550
    ctx->r25 = ADD32(ctx->r25, -0X1550);
    // 0x8009A1A0: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009A1A4: lui         $a3, 0x3E4C
    ctx->r7 = S32(0X3E4C << 16);
    // 0x8009A1A8: ori         $a3, $a3, 0xCCCD
    ctx->r7 = ctx->r7 | 0XCCCD;
    // 0x8009A1AC: addu        $a1, $t8, $t9
    ctx->r5 = ADD32(ctx->r24, ctx->r25);
    // 0x8009A1B0: lui         $a2, 0x4040
    ctx->r6 = S32(0X4040 << 16);
    // 0x8009A1B4: jal         0x80099AD8
    // 0x8009A1B8: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    func_80099AD8(rdram, ctx);
        goto after_4;
    // 0x8009A1B8: swc1        $f16, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f16.u32l;
    after_4:
    // 0x8009A1BC: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A1C0:
    // 0x8009A1C0: addiu       $sp, $sp, 0x30
    ctx->r29 = ADD32(ctx->r29, 0X30);
    // 0x8009A1C4: jr          $ra
    // 0x8009A1C8: nop

    return;
    // 0x8009A1C8: nop

;}
RECOMP_FUNC void func_8009A1CC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A1CC: mtc1        $a1, $f12
    ctx->f12.u32l = ctx->r5;
    // 0x8009A1D0: lui         $at, 0x40E0
    ctx->r1 = S32(0X40E0 << 16);
    // 0x8009A1D4: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x8009A1D8: add.s       $f4, $f12, $f12
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f12.fl); 
    ctx->f4.fl = ctx->f12.fl + ctx->f12.fl;
    // 0x8009A1DC: lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // 0x8009A1E0: mtc1        $at, $f18
    ctx->f18.u32l = ctx->r1;
    // 0x8009A1E4: lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // 0x8009A1E8: div.s       $f2, $f4, $f16
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f2.fl = DIV_S(ctx->f4.fl, ctx->f16.fl);
    // 0x8009A1EC: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8009A1F0: mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // 0x8009A1F4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A1F8: sw          $a0, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r4;
    // 0x8009A1FC: or          $a1, $a0, $zero
    ctx->r5 = ctx->r4 | 0;
    // 0x8009A200: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x8009A204: div.s       $f14, $f12, $f16
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f14.fl = DIV_S(ctx->f12.fl, ctx->f16.fl);
    // 0x8009A208: c.lt.s      $f18, $f2
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f18.fl < ctx->f2.fl;
    // 0x8009A20C: sub.s       $f12, $f12, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f12.fl = ctx->f12.fl - ctx->f18.fl;
    // 0x8009A210: bc1fl       L_8009A220
    if (!c1cs) {
        // 0x8009A214: c.lt.s      $f0, $f2
        CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
            goto L_8009A220;
    }
    goto skip_0;
    // 0x8009A214: c.lt.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
    skip_0:
    // 0x8009A218: mov.s       $f2, $f18
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 18);
    ctx->f2.fl = ctx->f18.fl;
    // 0x8009A21C: c.lt.s      $f0, $f2
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    c1cs = ctx->f0.fl < ctx->f2.fl;
L_8009A220:
    // 0x8009A220: nop

    // 0x8009A224: bc1fl       L_8009A234
    if (!c1cs) {
        // 0x8009A228: mtc1        $zero, $f0
        ctx->f0.u32l = 0;
            goto L_8009A234;
    }
    goto skip_1;
    // 0x8009A228: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    skip_1:
    // 0x8009A22C: mov.s       $f14, $f0
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 0);
    ctx->f14.fl = ctx->f0.fl;
    // 0x8009A230: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
L_8009A234:
    // 0x8009A234: nop

    // 0x8009A238: c.lt.s      $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    c1cs = ctx->f12.fl < ctx->f0.fl;
    // 0x8009A23C: nop

    // 0x8009A240: bc1fl       L_8009A250
    if (!c1cs) {
        // 0x8009A244: lwc1        $f6, 0x90($a1)
        ctx->f6.u32l = MEM_W(ctx->r5, 0X90);
            goto L_8009A250;
    }
    goto skip_2;
    // 0x8009A244: lwc1        $f6, 0x90($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X90);
    skip_2:
    // 0x8009A248: mov.s       $f12, $f0
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 0);
    ctx->f12.fl = ctx->f0.fl;
    // 0x8009A24C: lwc1        $f6, 0x90($a1)
    ctx->f6.u32l = MEM_W(ctx->r5, 0X90);
L_8009A250:
    // 0x8009A250: c.lt.s      $f6, $f12
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 12);
    c1cs = ctx->f6.fl < ctx->f12.fl;
    // 0x8009A254: nop

    // 0x8009A258: bc1fl       L_8009A2D8
    if (!c1cs) {
        // 0x8009A25C: lw          $ra, 0x1C($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X1C);
            goto L_8009A2D8;
    }
    goto skip_3;
    // 0x8009A25C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    skip_3:
    // 0x8009A260: mtc1        $at, $f8
    ctx->f8.u32l = ctx->r1;
    // 0x8009A264: lui         $at, 0x42B4
    ctx->r1 = S32(0X42B4 << 16);
    // 0x8009A268: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009A26C: div.s       $f10, $f2, $f8
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f8.fl); 
    ctx->f10.fl = DIV_S(ctx->f2.fl, ctx->f8.fl);
    // 0x8009A270: mfc1        $a2, $f2
    ctx->r6 = (int32_t)ctx->f2.u32l;
    // 0x8009A274: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A278: sw          $a1, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->r5;
    // 0x8009A27C: swc1        $f12, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f12.u32l;
    // 0x8009A280: swc1        $f14, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f14.u32l;
    // 0x8009A284: swc1        $f4, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f4.u32l;
    // 0x8009A288: mfc1        $a3, $f10
    ctx->r7 = (int32_t)ctx->f10.u32l;
    // 0x8009A28C: jal         0x80099AD8
    // 0x8009A290: nop

    func_80099AD8(rdram, ctx);
        goto after_0;
    // 0x8009A290: nop

    after_0:
    // 0x8009A294: lui         $at, 0x4120
    ctx->r1 = S32(0X4120 << 16);
    // 0x8009A298: lwc1        $f14, 0x20($sp)
    ctx->f14.u32l = MEM_W(ctx->r29, 0X20);
    // 0x8009A29C: mtc1        $at, $f6
    ctx->f6.u32l = ctx->r1;
    // 0x8009A2A0: lui         $at, 0x4334
    ctx->r1 = S32(0X4334 << 16);
    // 0x8009A2A4: mtc1        $at, $f10
    ctx->f10.u32l = ctx->r1;
    // 0x8009A2A8: div.s       $f8, $f14, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = DIV_S(ctx->f14.fl, ctx->f6.fl);
    // 0x8009A2AC: mfc1        $a2, $f14
    ctx->r6 = (int32_t)ctx->f14.u32l;
    // 0x8009A2B0: addiu       $a0, $zero, 0x2
    ctx->r4 = ADD32(0, 0X2);
    // 0x8009A2B4: lw          $a1, 0x28($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X28);
    // 0x8009A2B8: swc1        $f10, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f10.u32l;
    // 0x8009A2BC: mfc1        $a3, $f8
    ctx->r7 = (int32_t)ctx->f8.u32l;
    // 0x8009A2C0: jal         0x80099AD8
    // 0x8009A2C4: nop

    func_80099AD8(rdram, ctx);
        goto after_1;
    // 0x8009A2C4: nop

    after_1:
    // 0x8009A2C8: lwc1        $f12, 0x2C($sp)
    ctx->f12.u32l = MEM_W(ctx->r29, 0X2C);
    // 0x8009A2CC: lw          $t6, 0x28($sp)
    ctx->r14 = MEM_W(ctx->r29, 0X28);
    // 0x8009A2D0: swc1        $f12, 0x90($t6)
    MEM_W(0X90, ctx->r14) = ctx->f12.u32l;
    // 0x8009A2D4: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A2D8:
    // 0x8009A2D8: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009A2DC: jr          $ra
    // 0x8009A2E0: nop

    return;
    // 0x8009A2E0: nop

;}
RECOMP_FUNC void func_8009A2E4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A2E4: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009A2E8: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009A2EC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A2F0: sw          $s1, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r17;
    // 0x8009A2F4: or          $s1, $a0, $zero
    ctx->r17 = ctx->r4 | 0;
    // 0x8009A2F8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A2FC: bne         $t6, $zero, L_8009A310
    if (ctx->r14 != 0) {
        // 0x8009A300: sw          $s0, 0x14($sp)
        MEM_W(0X14, ctx->r29) = ctx->r16;
            goto L_8009A310;
    }
    // 0x8009A300: sw          $s0, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r16;
    // 0x8009A304: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x8009A308: b           L_8009A318
    // 0x8009A30C: lw          $v0, 0x48DC($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X48DC);
        goto L_8009A318;
    // 0x8009A30C: lw          $v0, 0x48DC($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X48DC);
L_8009A310:
    // 0x8009A310: lui         $v0, 0x800D
    ctx->r2 = S32(0X800D << 16);
    // 0x8009A314: lw          $v0, 0x48E0($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X48E0);
L_8009A318:
    // 0x8009A318: sll         $t7, $v0, 2
    ctx->r15 = S32(ctx->r2 << 2);
    // 0x8009A31C: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x8009A320: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009A324: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x8009A328: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009A32C: addu        $t7, $t7, $v0
    ctx->r15 = ADD32(ctx->r15, ctx->r2);
    // 0x8009A330: sll         $t7, $t7, 2
    ctx->r15 = S32(ctx->r15 << 2);
    // 0x8009A334: subu        $t7, $t7, $v0
    ctx->r15 = SUB32(ctx->r15, ctx->r2);
    // 0x8009A338: lui         $t8, 0x8019
    ctx->r24 = S32(0X8019 << 16);
    // 0x8009A33C: addiu       $t8, $t8, 0x2690
    ctx->r24 = ADD32(ctx->r24, 0X2690);
    // 0x8009A340: sll         $t7, $t7, 3
    ctx->r15 = S32(ctx->r15 << 3);
    // 0x8009A344: addu        $s0, $t7, $t8
    ctx->r16 = ADD32(ctx->r15, ctx->r24);
    // 0x8009A348: lwc1        $f4, 0xC3C($s0)
    ctx->f4.u32l = MEM_W(ctx->r16, 0XC3C);
    // 0x8009A34C: lwc1        $f6, 0xC44($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC44);
    // 0x8009A350: lwc1        $f10, 0xC48($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0XC48);
    // 0x8009A354: lwc1        $f18, 0xC4C($s0)
    ctx->f18.u32l = MEM_W(ctx->r16, 0XC4C);
    // 0x8009A358: add.s       $f8, $f4, $f6
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl); 
    ctx->f8.fl = ctx->f4.fl + ctx->f6.fl;
    // 0x8009A35C: lwc1        $f6, 0xC50($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC50);
    // 0x8009A360: mtc1        $zero, $f0
    ctx->f0.u32l = 0;
    // 0x8009A364: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8009A368: add.s       $f16, $f8, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f10.fl); 
    ctx->f16.fl = ctx->f8.fl + ctx->f10.fl;
    // 0x8009A36C: add.s       $f4, $f16, $f18
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f18.fl); 
    ctx->f4.fl = ctx->f16.fl + ctx->f18.fl;
    // 0x8009A370: add.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = ctx->f6.fl + ctx->f4.fl;
    // 0x8009A374: c.eq.s      $f0, $f8
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 8);
    c1cs = ctx->f0.fl == ctx->f8.fl;
    // 0x8009A378: nop

    // 0x8009A37C: bc1tl       L_8009A3F0
    if (c1cs) {
        // 0x8009A380: swc1        $f0, 0x90($s1)
        MEM_W(0X90, ctx->r17) = ctx->f0.u32l;
            goto L_8009A3F0;
    }
    goto skip_0;
    // 0x8009A380: swc1        $f0, 0x90($s1)
    MEM_W(0X90, ctx->r17) = ctx->f0.u32l;
    skip_0:
    // 0x8009A384: lwc1        $f10, 0xC38($s0)
    ctx->f10.u32l = MEM_W(ctx->r16, 0XC38);
    // 0x8009A388: mtc1        $at, $f16
    ctx->f16.u32l = ctx->r1;
    // 0x8009A38C: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8009A390: mul.s       $f18, $f10, $f16
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 16);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f16.fl); 
    ctx->f18.fl = MUL_S(ctx->f10.fl, ctx->f16.fl);
    // 0x8009A394: mfc1        $a1, $f18
    ctx->r5 = (int32_t)ctx->f18.u32l;
    // 0x8009A398: jal         0x8009A1CC
    // 0x8009A39C: nop

    func_8009A1CC(rdram, ctx);
        goto after_0;
    // 0x8009A39C: nop

    after_0:
    // 0x8009A3A0: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8009A3A4: jal         0x8009A1CC
    // 0x8009A3A8: lw          $a1, 0xC3C($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC3C);
    func_8009A1CC(rdram, ctx);
        goto after_1;
    // 0x8009A3A8: lw          $a1, 0xC3C($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC3C);
    after_1:
    // 0x8009A3AC: lui         $at, 0x3F00
    ctx->r1 = S32(0X3F00 << 16);
    // 0x8009A3B0: mtc1        $at, $f4
    ctx->f4.u32l = ctx->r1;
    // 0x8009A3B4: lwc1        $f6, 0xC40($s0)
    ctx->f6.u32l = MEM_W(ctx->r16, 0XC40);
    // 0x8009A3B8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8009A3BC: mul.s       $f8, $f6, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f4.fl); 
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f4.fl);
    // 0x8009A3C0: mfc1        $a1, $f8
    ctx->r5 = (int32_t)ctx->f8.u32l;
    // 0x8009A3C4: jal         0x8009A1CC
    // 0x8009A3C8: nop

    func_8009A1CC(rdram, ctx);
        goto after_2;
    // 0x8009A3C8: nop

    after_2:
    // 0x8009A3CC: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8009A3D0: jal         0x8009A1CC
    // 0x8009A3D4: lw          $a1, 0xC44($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC44);
    func_8009A1CC(rdram, ctx);
        goto after_3;
    // 0x8009A3D4: lw          $a1, 0xC44($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC44);
    after_3:
    // 0x8009A3D8: or          $a0, $s1, $zero
    ctx->r4 = ctx->r17 | 0;
    // 0x8009A3DC: jal         0x8009A1CC
    // 0x8009A3E0: lw          $a1, 0xC50($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC50);
    func_8009A1CC(rdram, ctx);
        goto after_4;
    // 0x8009A3E0: lw          $a1, 0xC50($s0)
    ctx->r5 = MEM_W(ctx->r16, 0XC50);
    after_4:
    // 0x8009A3E4: b           L_8009A3F4
    // 0x8009A3E8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
        goto L_8009A3F4;
    // 0x8009A3E8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A3EC: swc1        $f0, 0x90($s1)
    MEM_W(0X90, ctx->r17) = ctx->f0.u32l;
L_8009A3F0:
    // 0x8009A3F0: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
L_8009A3F4:
    // 0x8009A3F4: lw          $s0, 0x14($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X14);
    // 0x8009A3F8: lw          $s1, 0x18($sp)
    ctx->r17 = MEM_W(ctx->r29, 0X18);
    // 0x8009A3FC: jr          $ra
    // 0x8009A400: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    return;
    // 0x8009A400: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
;}
RECOMP_FUNC void func_8009A404(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A404: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009A408: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009A40C: or          $a2, $a0, $zero
    ctx->r6 = ctx->r4 | 0;
    // 0x8009A410: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009A414: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    // 0x8009A418: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009A41C: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009A420: addu        $at, $at, $a0
    ctx->r1 = ADD32(ctx->r1, ctx->r4);
    // 0x8009A424: sb          $a2, -0x155C($at)
    MEM_B(-0X155C, ctx->r1) = ctx->r6;
    // 0x8009A428: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009A42C: sll         $v0, $a0, 1
    ctx->r2 = S32(ctx->r4 << 1);
    // 0x8009A430: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x8009A434: sh          $a1, -0x156C($at)
    MEM_H(-0X156C, ctx->r1) = ctx->r5;
    // 0x8009A438: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009A43C: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x8009A440: addiu       $t8, $zero, 0x4000
    ctx->r24 = ADD32(0, 0X4000);
    // 0x8009A444: sw          $a1, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r5;
    // 0x8009A448: jal         0x800988D8
    // 0x8009A44C: sh          $t8, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r24;
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009A44C: sh          $t8, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r24;
    after_0:
    // 0x8009A450: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009A454: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009A458: jr          $ra
    // 0x8009A45C: nop

    return;
    // 0x8009A45C: nop

;}
RECOMP_FUNC void func_8009A460(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A460: lui         $t0, 0x800E
    ctx->r8 = S32(0X800E << 16);
    // 0x8009A464: lw          $t0, 0x5138($t0)
    ctx->r8 = MEM_W(ctx->r8, 0X5138);
    // 0x8009A468: lui         $v0, 0x801D
    ctx->r2 = S32(0X801D << 16);
    // 0x8009A46C: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009A470: sll         $t1, $t0, 1
    ctx->r9 = S32(ctx->r8 << 1);
    // 0x8009A474: addu        $v0, $v0, $t1
    ctx->r2 = ADD32(ctx->r2, ctx->r9);
    // 0x8009A478: lh          $v0, -0x1568($v0)
    ctx->r2 = MEM_H(ctx->r2, -0X1568);
    // 0x8009A47C: sll         $t6, $a2, 16
    ctx->r14 = S32(ctx->r6 << 16);
    // 0x8009A480: sra         $t7, $t6, 16
    ctx->r15 = S32(SIGNED(ctx->r14) >> 16);
    // 0x8009A484: sll         $t8, $a3, 16
    ctx->r24 = S32(ctx->r7 << 16);
    // 0x8009A488: slt         $at, $v0, $t7
    ctx->r1 = SIGNED(ctx->r2) < SIGNED(ctx->r15) ? 1 : 0;
    // 0x8009A48C: sra         $t9, $t8, 16
    ctx->r25 = S32(SIGNED(ctx->r24) >> 16);
    // 0x8009A490: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009A494: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009A498: sw          $a2, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r6;
    // 0x8009A49C: bne         $at, $zero, L_8009A4C8
    if (ctx->r1 != 0) {
        // 0x8009A4A0: sw          $a3, 0x24($sp)
        MEM_W(0X24, ctx->r29) = ctx->r7;
            goto L_8009A4C8;
    }
    // 0x8009A4A0: sw          $a3, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r7;
    // 0x8009A4A4: addiu       $at, $zero, -0x1
    ctx->r1 = ADD32(0, -0X1);
    // 0x8009A4A8: beq         $t9, $at, L_8009A4B8
    if (ctx->r25 == ctx->r1) {
        // 0x8009A4AC: slt         $at, $t9, $v0
        ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r2) ? 1 : 0;
            goto L_8009A4B8;
    }
    // 0x8009A4AC: slt         $at, $t9, $v0
    ctx->r1 = SIGNED(ctx->r25) < SIGNED(ctx->r2) ? 1 : 0;
    // 0x8009A4B0: bnel        $at, $zero, L_8009A4CC
    if (ctx->r1 != 0) {
        // 0x8009A4B4: lw          $ra, 0x14($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X14);
            goto L_8009A4CC;
    }
    goto skip_0;
    // 0x8009A4B4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    skip_0:
L_8009A4B8:
    // 0x8009A4B8: lw          $t9, 0x18($sp)
    ctx->r25 = MEM_W(ctx->r29, 0X18);
    // 0x8009A4BC: or          $a0, $a1, $zero
    ctx->r4 = ctx->r5 | 0;
    // 0x8009A4C0: jalr        $t9
    // 0x8009A4C4: nop

    LOOKUP_FUNC(ctx->r25)(rdram, ctx);
        goto after_0;
    // 0x8009A4C4: nop

    after_0:
L_8009A4C8:
    // 0x8009A4C8: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
L_8009A4CC:
    // 0x8009A4CC: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009A4D0: or          $v0, $zero, $zero
    ctx->r2 = 0 | 0;
    // 0x8009A4D4: jr          $ra
    // 0x8009A4D8: nop

    return;
    // 0x8009A4D8: nop

;}
RECOMP_FUNC void func_8009A4DC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A4DC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A4E0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A4E4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A4E8: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009A4EC: jal         0x800988D8
    // 0x8009A4F0: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009A4F0: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_0:
    // 0x8009A4F4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009A4F8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009A4FC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A500: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A504: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A508: jal         0x80098AC4
    // 0x8009A50C: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009A50C: addiu       $a3, $zero, 0x1
    ctx->r7 = ADD32(0, 0X1);
    after_1:
    // 0x8009A510: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A514: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A518: jr          $ra
    // 0x8009A51C: nop

    return;
    // 0x8009A51C: nop

;}
RECOMP_FUNC void func_8009A520(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A520: lui         $v0, 0x800E
    ctx->r2 = S32(0X800E << 16);
    // 0x8009A524: lw          $v0, 0x5138($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X5138);
    // 0x8009A528: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009A52C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009A530: addu        $at, $at, $v0
    ctx->r1 = ADD32(ctx->r1, ctx->r2);
    // 0x8009A534: sb          $t6, -0x155A($at)
    MEM_B(-0X155A, ctx->r1) = ctx->r14;
    // 0x8009A538: lui         $at, 0x801D
    ctx->r1 = S32(0X801D << 16);
    // 0x8009A53C: sll         $t8, $v0, 1
    ctx->r24 = S32(ctx->r2 << 1);
    // 0x8009A540: addu        $at, $at, $t8
    ctx->r1 = ADD32(ctx->r1, ctx->r24);
    // 0x8009A544: addiu       $t7, $zero, -0x8000
    ctx->r15 = ADD32(0, -0X8000);
    // 0x8009A548: sw          $a0, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r4;
    // 0x8009A54C: jr          $ra
    // 0x8009A550: sh          $t7, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r15;
    return;
    // 0x8009A550: sh          $t7, -0x1568($at)
    MEM_H(-0X1568, ctx->r1) = ctx->r15;
;}
RECOMP_FUNC void func_8009A554(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A554: addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // 0x8009A558: sw          $s0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r16;
    // 0x8009A55C: or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // 0x8009A560: sw          $ra, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->r31;
    // 0x8009A564: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A568: addiu       $a0, $a0, -0x5B24
    ctx->r4 = ADD32(ctx->r4, -0X5B24);
    // 0x8009A56C: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009A570: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009A574: jal         0x8009A460
    // 0x8009A578: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009A578: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009A57C: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A580: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A584: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A588: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8009A58C: jal         0x80098AC4
    // 0x8009A590: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009A590: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_1:
    // 0x8009A594: lui         $t6, 0x801D
    ctx->r14 = S32(0X801D << 16);
    // 0x8009A598: lw          $t6, -0x19E0($t6)
    ctx->r14 = MEM_W(ctx->r14, -0X19E0);
    // 0x8009A59C: addiu       $at, $zero, 0x4
    ctx->r1 = ADD32(0, 0X4);
    // 0x8009A5A0: lui         $t7, 0x800D
    ctx->r15 = S32(0X800D << 16);
    // 0x8009A5A4: bnel        $t6, $at, L_8009A69C
    if (ctx->r14 != ctx->r1) {
        // 0x8009A5A8: lw          $ra, 0x24($sp)
        ctx->r31 = MEM_W(ctx->r29, 0X24);
            goto L_8009A69C;
    }
    goto skip_0;
    // 0x8009A5A8: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
    skip_0:
    // 0x8009A5AC: lw          $t7, 0x48DC($t7)
    ctx->r15 = MEM_W(ctx->r15, 0X48DC);
    // 0x8009A5B0: lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // 0x8009A5B4: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A5B8: sll         $t8, $t7, 3
    ctx->r24 = S32(ctx->r15 << 3);
    // 0x8009A5BC: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A5C0: sll         $t8, $t8, 4
    ctx->r24 = S32(ctx->r24 << 4);
    // 0x8009A5C4: subu        $t8, $t8, $t7
    ctx->r24 = SUB32(ctx->r24, ctx->r15);
    // 0x8009A5C8: sll         $t8, $t8, 3
    ctx->r24 = S32(ctx->r24 << 3);
    // 0x8009A5CC: addu        $v0, $v0, $t8
    ctx->r2 = ADD32(ctx->r2, ctx->r24);
    // 0x8009A5D0: lw          $v0, 0x293C($v0)
    ctx->r2 = MEM_W(ctx->r2, 0X293C);
    // 0x8009A5D4: addiu       $a1, $a1, 0x52B4
    ctx->r5 = ADD32(ctx->r5, 0X52B4);
    // 0x8009A5D8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009A5DC: beq         $v0, $zero, L_8009A604
    if (ctx->r2 == 0) {
        // 0x8009A5E0: lui         $a2, 0x800E
        ctx->r6 = S32(0X800E << 16);
            goto L_8009A604;
    }
    // 0x8009A5E0: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A5E4: addiu       $at, $zero, 0x1
    ctx->r1 = ADD32(0, 0X1);
    // 0x8009A5E8: beq         $v0, $at, L_8009A61C
    if (ctx->r2 == ctx->r1) {
        // 0x8009A5EC: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_8009A61C;
    }
    // 0x8009A5EC: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009A5F0: addiu       $at, $zero, 0x2
    ctx->r1 = ADD32(0, 0X2);
    // 0x8009A5F4: beq         $v0, $at, L_8009A640
    if (ctx->r2 == ctx->r1) {
        // 0x8009A5F8: or          $a0, $s0, $zero
        ctx->r4 = ctx->r16 | 0;
            goto L_8009A640;
    }
    // 0x8009A5F8: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
    // 0x8009A5FC: b           L_8009A664
    // 0x8009A600: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
        goto L_8009A664;
    // 0x8009A600: or          $a0, $s0, $zero
    ctx->r4 = ctx->r16 | 0;
L_8009A604:
    // 0x8009A604: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A608: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A60C: jal         0x80099A00
    // 0x8009A610: addiu       $a2, $a2, 0x52E8
    ctx->r6 = ADD32(ctx->r6, 0X52E8);
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009A610: addiu       $a2, $a2, 0x52E8
    ctx->r6 = ADD32(ctx->r6, 0X52E8);
    after_2:
    // 0x8009A614: b           L_8009A680
    // 0x8009A618: nop

        goto L_8009A680;
    // 0x8009A618: nop

L_8009A61C:
    // 0x8009A61C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A620: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A624: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A628: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A62C: addiu       $a2, $a2, 0x528C
    ctx->r6 = ADD32(ctx->r6, 0X528C);
    // 0x8009A630: jal         0x80099A00
    // 0x8009A634: addiu       $a1, $a1, 0x5264
    ctx->r5 = ADD32(ctx->r5, 0X5264);
    func_80099A00(rdram, ctx);
        goto after_3;
    // 0x8009A634: addiu       $a1, $a1, 0x5264
    ctx->r5 = ADD32(ctx->r5, 0X5264);
    after_3:
    // 0x8009A638: b           L_8009A680
    // 0x8009A63C: nop

        goto L_8009A680;
    // 0x8009A63C: nop

L_8009A640:
    // 0x8009A640: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A644: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A648: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A64C: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A650: addiu       $a2, $a2, 0x5228
    ctx->r6 = ADD32(ctx->r6, 0X5228);
    // 0x8009A654: jal         0x80099A00
    // 0x8009A658: addiu       $a1, $a1, 0x51EC
    ctx->r5 = ADD32(ctx->r5, 0X51EC);
    func_80099A00(rdram, ctx);
        goto after_4;
    // 0x8009A658: addiu       $a1, $a1, 0x51EC
    ctx->r5 = ADD32(ctx->r5, 0X51EC);
    after_4:
    // 0x8009A65C: b           L_8009A680
    // 0x8009A660: nop

        goto L_8009A680;
    // 0x8009A660: nop

L_8009A664:
    // 0x8009A664: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A668: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A66C: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A670: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A674: addiu       $a2, $a2, 0x51A4
    ctx->r6 = ADD32(ctx->r6, 0X51A4);
    // 0x8009A678: jal         0x80099A00
    // 0x8009A67C: addiu       $a1, $a1, 0x515C
    ctx->r5 = ADD32(ctx->r5, 0X515C);
    func_80099A00(rdram, ctx);
        goto after_5;
    // 0x8009A67C: addiu       $a1, $a1, 0x515C
    ctx->r5 = ADD32(ctx->r5, 0X515C);
    after_5:
L_8009A680:
    // 0x8009A680: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A684: addiu       $a0, $a0, -0x5AE0
    ctx->r4 = ADD32(ctx->r4, -0X5AE0);
    // 0x8009A688: or          $a1, $s0, $zero
    ctx->r5 = ctx->r16 | 0;
    // 0x8009A68C: addiu       $a2, $zero, 0x59
    ctx->r6 = ADD32(0, 0X59);
    // 0x8009A690: jal         0x8009A460
    // 0x8009A694: addiu       $a3, $zero, 0x59
    ctx->r7 = ADD32(0, 0X59);
    func_8009A460(rdram, ctx);
        goto after_6;
    // 0x8009A694: addiu       $a3, $zero, 0x59
    ctx->r7 = ADD32(0, 0X59);
    after_6:
    // 0x8009A698: lw          $ra, 0x24($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X24);
L_8009A69C:
    // 0x8009A69C: lw          $s0, 0x20($sp)
    ctx->r16 = MEM_W(ctx->r29, 0X20);
    // 0x8009A6A0: addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    // 0x8009A6A4: jr          $ra
    // 0x8009A6A8: nop

    return;
    // 0x8009A6A8: nop

;}
RECOMP_FUNC void func_8009A6AC(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A6AC: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A6B0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A6B4: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A6B8: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A6BC: addiu       $a0, $a0, -0x5B24
    ctx->r4 = ADD32(ctx->r4, -0X5B24);
    // 0x8009A6C0: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A6C4: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009A6C8: jal         0x8009A460
    // 0x8009A6CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_0;
    // 0x8009A6CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009A6D0: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A6D4: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A6D8: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A6DC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    // 0x8009A6E0: jal         0x80098AC4
    // 0x8009A6E4: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009A6E4: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    after_1:
    // 0x8009A6E8: lui         $t6, 0x800E
    ctx->r14 = S32(0X800E << 16);
    // 0x8009A6EC: lw          $t6, 0x5138($t6)
    ctx->r14 = MEM_W(ctx->r14, 0X5138);
    // 0x8009A6F0: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A6F4: addiu       $a1, $a1, 0x536C
    ctx->r5 = ADD32(ctx->r5, 0X536C);
    // 0x8009A6F8: bne         $t6, $zero, L_8009A728
    if (ctx->r14 != 0) {
        // 0x8009A6FC: lw          $a0, 0x20($sp)
        ctx->r4 = MEM_W(ctx->r29, 0X20);
            goto L_8009A728;
    }
    // 0x8009A6FC: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    // 0x8009A700: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A704: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A708: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A70C: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A710: addiu       $a2, $a2, 0x5344
    ctx->r6 = ADD32(ctx->r6, 0X5344);
    // 0x8009A714: addiu       $a1, $a1, 0x531C
    ctx->r5 = ADD32(ctx->r5, 0X531C);
    // 0x8009A718: jal         0x80099A00
    // 0x8009A71C: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009A71C: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    after_2:
    // 0x8009A720: b           L_8009A73C
    // 0x8009A724: nop

        goto L_8009A73C;
    // 0x8009A724: nop

L_8009A728:
    // 0x8009A728: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A72C: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A730: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A734: jal         0x80099A00
    // 0x8009A738: addiu       $a2, $a2, 0x5394
    ctx->r6 = ADD32(ctx->r6, 0X5394);
    func_80099A00(rdram, ctx);
        goto after_3;
    // 0x8009A738: addiu       $a2, $a2, 0x5394
    ctx->r6 = ADD32(ctx->r6, 0X5394);
    after_3:
L_8009A73C:
    // 0x8009A73C: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A740: addiu       $a0, $a0, -0x5AE0
    ctx->r4 = ADD32(ctx->r4, -0X5AE0);
    // 0x8009A744: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A748: addiu       $a2, $zero, 0x43
    ctx->r6 = ADD32(0, 0X43);
    // 0x8009A74C: jal         0x8009A460
    // 0x8009A750: addiu       $a3, $zero, 0x43
    ctx->r7 = ADD32(0, 0X43);
    func_8009A460(rdram, ctx);
        goto after_4;
    // 0x8009A750: addiu       $a3, $zero, 0x43
    ctx->r7 = ADD32(0, 0X43);
    after_4:
    // 0x8009A754: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A758: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A75C: jr          $ra
    // 0x8009A760: nop

    return;
    // 0x8009A760: nop

;}
RECOMP_FUNC void func_8009A764(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A764: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A768: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A76C: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A770: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009A774: jal         0x800988D8
    // 0x8009A778: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    func_800988D8(rdram, ctx);
        goto after_0;
    // 0x8009A778: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    after_0:
    // 0x8009A77C: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009A780: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009A784: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A788: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A78C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A790: jal         0x80098AC4
    // 0x8009A794: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_1;
    // 0x8009A794: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009A798: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A79C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A7A0: jr          $ra
    // 0x8009A7A4: nop

    return;
    // 0x8009A7A4: nop

;}
RECOMP_FUNC void func_8009A7A8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A7A8: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A7AC: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A7B0: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A7B4: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009A7B8: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009A7BC: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A7C0: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A7C4: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A7C8: jal         0x80098AC4
    // 0x8009A7CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009A7CC: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009A7D0: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A7D4: addiu       $a0, $a0, -0x589C
    ctx->r4 = ADD32(ctx->r4, -0X589C);
    // 0x8009A7D8: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A7DC: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009A7E0: jal         0x8009A460
    // 0x8009A7E4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009A7E4: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009A7E8: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A7EC: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A7F0: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A7F4: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A7F8: addiu       $a2, $a2, 0x53DC
    ctx->r6 = ADD32(ctx->r6, 0X53DC);
    // 0x8009A7FC: addiu       $a1, $a1, 0x53BC
    ctx->r5 = ADD32(ctx->r5, 0X53BC);
    // 0x8009A800: jal         0x80099A00
    // 0x8009A804: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    func_80099A00(rdram, ctx);
        goto after_2;
    // 0x8009A804: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    after_2:
    // 0x8009A808: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A80C: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A810: jr          $ra
    // 0x8009A814: nop

    return;
    // 0x8009A814: nop

;}
RECOMP_FUNC void func_8009A818(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A818: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009A81C: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009A820: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009A824: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009A828: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    // 0x8009A82C: jal         0x8009A04C
    // 0x8009A830: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    func_8009A04C(rdram, ctx);
        goto after_0;
    // 0x8009A830: addiu       $a1, $zero, 0x5
    ctx->r5 = ADD32(0, 0X5);
    after_0:
    // 0x8009A834: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009A838: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009A83C: jr          $ra
    // 0x8009A840: nop

    return;
    // 0x8009A840: nop

;}
RECOMP_FUNC void func_8009A844(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A844: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A848: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A84C: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A850: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A854: sw          $zero, 0x10($sp)
    MEM_W(0X10, ctx->r29) = 0;
    // 0x8009A858: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A85C: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A860: jal         0x80098AC4
    // 0x8009A864: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009A864: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009A868: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A86C: addiu       $a0, $a0, -0x589C
    ctx->r4 = ADD32(ctx->r4, -0X589C);
    // 0x8009A870: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A874: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009A878: jal         0x8009A460
    // 0x8009A87C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009A87C: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009A880: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A884: addiu       $a0, $a0, -0x57E8
    ctx->r4 = ADD32(ctx->r4, -0X57E8);
    // 0x8009A888: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A88C: addiu       $a2, $zero, 0xD
    ctx->r6 = ADD32(0, 0XD);
    // 0x8009A890: jal         0x8009A460
    // 0x8009A894: addiu       $a3, $zero, 0xD
    ctx->r7 = ADD32(0, 0XD);
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009A894: addiu       $a3, $zero, 0xD
    ctx->r7 = ADD32(0, 0XD);
    after_2:
    // 0x8009A898: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A89C: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A8A0: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A8A4: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A8A8: addiu       $a2, $a2, 0x5424
    ctx->r6 = ADD32(ctx->r6, 0X5424);
    // 0x8009A8AC: addiu       $a1, $a1, 0x53FC
    ctx->r5 = ADD32(ctx->r5, 0X53FC);
    // 0x8009A8B0: jal         0x80099A00
    // 0x8009A8B4: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    func_80099A00(rdram, ctx);
        goto after_3;
    // 0x8009A8B4: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    after_3:
    // 0x8009A8B8: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A8BC: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A8C0: jr          $ra
    // 0x8009A8C4: nop

    return;
    // 0x8009A8C4: nop

;}
RECOMP_FUNC void func_8009A8C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A8C8: addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // 0x8009A8CC: sw          $a0, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r4;
    // 0x8009A8D0: sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // 0x8009A8D4: lui         $a0, 0x800E
    ctx->r4 = S32(0X800E << 16);
    // 0x8009A8D8: lw          $a0, 0x5138($a0)
    ctx->r4 = MEM_W(ctx->r4, 0X5138);
    // 0x8009A8DC: jal         0x8009A04C
    // 0x8009A8E0: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    func_8009A04C(rdram, ctx);
        goto after_0;
    // 0x8009A8E0: addiu       $a1, $zero, 0x4
    ctx->r5 = ADD32(0, 0X4);
    after_0:
    // 0x8009A8E4: lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X14);
    // 0x8009A8E8: addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // 0x8009A8EC: jr          $ra
    // 0x8009A8F0: nop

    return;
    // 0x8009A8F0: nop

;}
RECOMP_FUNC void func_8009A8F4(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    // 0x8009A8F4: addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // 0x8009A8F8: sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // 0x8009A8FC: sw          $a0, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r4;
    // 0x8009A900: addiu       $t6, $zero, 0x1
    ctx->r14 = ADD32(0, 0X1);
    // 0x8009A904: sw          $t6, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r14;
    // 0x8009A908: addiu       $a0, $zero, 0x1
    ctx->r4 = ADD32(0, 0X1);
    // 0x8009A90C: addiu       $a1, $zero, 0x1
    ctx->r5 = ADD32(0, 0X1);
    // 0x8009A910: addiu       $a2, $zero, 0x1
    ctx->r6 = ADD32(0, 0X1);
    // 0x8009A914: jal         0x80098AC4
    // 0x8009A918: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_80098AC4(rdram, ctx);
        goto after_0;
    // 0x8009A918: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_0:
    // 0x8009A91C: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A920: addiu       $a0, $a0, -0x589C
    ctx->r4 = ADD32(ctx->r4, -0X589C);
    // 0x8009A924: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A928: or          $a2, $zero, $zero
    ctx->r6 = 0 | 0;
    // 0x8009A92C: jal         0x8009A460
    // 0x8009A930: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    func_8009A460(rdram, ctx);
        goto after_1;
    // 0x8009A930: or          $a3, $zero, $zero
    ctx->r7 = 0 | 0;
    after_1:
    // 0x8009A934: lui         $a0, 0x800A
    ctx->r4 = S32(0X800A << 16);
    // 0x8009A938: addiu       $a0, $a0, -0x5738
    ctx->r4 = ADD32(ctx->r4, -0X5738);
    // 0x8009A93C: lw          $a1, 0x20($sp)
    ctx->r5 = MEM_W(ctx->r29, 0X20);
    // 0x8009A940: addiu       $a2, $zero, 0x1D
    ctx->r6 = ADD32(0, 0X1D);
    // 0x8009A944: jal         0x8009A460
    // 0x8009A948: addiu       $a3, $zero, 0x1D
    ctx->r7 = ADD32(0, 0X1D);
    func_8009A460(rdram, ctx);
        goto after_2;
    // 0x8009A948: addiu       $a3, $zero, 0x1D
    ctx->r7 = ADD32(0, 0X1D);
    after_2:
    // 0x8009A94C: lui         $a1, 0x800E
    ctx->r5 = S32(0X800E << 16);
    // 0x8009A950: lui         $a2, 0x800E
    ctx->r6 = S32(0X800E << 16);
    // 0x8009A954: lui         $a3, 0x801C
    ctx->r7 = S32(0X801C << 16);
    // 0x8009A958: lw          $a3, 0x1F90($a3)
    ctx->r7 = MEM_W(ctx->r7, 0X1F90);
    // 0x8009A95C: addiu       $a2, $a2, 0x5474
    ctx->r6 = ADD32(ctx->r6, 0X5474);
    // 0x8009A960: addiu       $a1, $a1, 0x544C
    ctx->r5 = ADD32(ctx->r5, 0X544C);
    // 0x8009A964: jal         0x80099A00
    // 0x8009A968: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    func_80099A00(rdram, ctx);
        goto after_3;
    // 0x8009A968: lw          $a0, 0x20($sp)
    ctx->r4 = MEM_W(ctx->r29, 0X20);
    after_3:
    // 0x8009A96C: lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(ctx->r29, 0X1C);
    // 0x8009A970: addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // 0x8009A974: jr          $ra
    // 0x8009A978: nop

    return;
    // 0x8009A978: nop

;}
