#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// プログラムカウンター(PC)の挙動を示す簡易VM
// ・順次進行: PC が +1 される
// ・条件分岐/繰り返し: 命令により PC が任意のアドレス(≠ 現PC+1)に設定される
// 命令セット:
//   NOP      : 何もしない (PC = PC + 1)
//   LOAD n   : 汎用レジスタRに即値nを読み込む (PC = PC + 1)
//   DEC      : Rを1減らす (PC = PC + 1)
//   JNZ a    : R != 0 なら PC = a (≠+1)、そうでなければ PC = PC + 1
//   JMP a    : 無条件に PC = a (≠+1)
//   HALT     : 実行停止

// 命令種別
typedef enum {
    OP_NOP,
    OP_LOAD,
    OP_DEC,
    OP_JNZ,
    OP_JMP,
    OP_HALT
} OpCode;

// 命令表現
typedef struct {
    OpCode op;
    int operand; // LOADの即値、JNZ/JMPのジャンプ先アドレスに使用
} Instr;

// 1ステップ実行し、PCの変化を表示
bool step(Instr *prog, int prog_len, int *pc, int *R) {
    if (*pc < 0 || *pc >= prog_len) {
        printf("PC が範囲外です: %d\n", *pc);
        return false;
    }

    int oldPC = *pc;
    Instr ins = prog[*pc];

    // 命令名の表示用
    const char *name = "";
    switch (ins.op) {
        case OP_NOP:  name = "NOP";  break;
        case OP_LOAD: name = "LOAD"; break;
        case OP_DEC:  name = "DEC";  break;
        case OP_JNZ:  name = "JNZ";  break;
        case OP_JMP:  name = "JMP";  break;
        case OP_HALT: name = "HALT"; break;
        default:      name = "?";    break;
    }

    // 実行前に命令とオペランドを表示
    if (ins.op == OP_LOAD || ins.op == OP_JNZ || ins.op == OP_JMP) {
        printf("PC=%d: 実行命令 %s %d\n", oldPC, name, ins.operand);
    } else {
        printf("PC=%d: 実行命令 %s\n", oldPC, name);
    }

    // デフォルトは順次進行(+1)
    int nextPC = *pc + 1;

    // 命令の実行
    switch (ins.op) {
        case OP_NOP:
            // 何もしない
            break;
        case OP_LOAD:
            *R = ins.operand;
            printf("  R <- %d\n", *R);
            break;
        case OP_DEC:
            (*R) -= 1;
            printf("  R <- %d\n", *R);
            break;
        case OP_JNZ:
            if (*R != 0) {
                nextPC = ins.operand; // 分岐: PCが任意のアドレスに設定される
                printf("  条件成立(R!=0)。PC <- %d (≠ 旧PC+1)\n", nextPC);
            } else {
                printf("  条件不成立(R==0)。PC は順次進行(+1)\n");
            }
            break;
        case OP_JMP:
            nextPC = ins.operand; // 無条件ジャンプ
            printf("  無条件ジャンプ。PC <- %d (≠ 旧PC+1)\n", nextPC);
            break;
        case OP_HALT:
            printf("  停止\n");
            return false; // 実行停止
        default:
            printf("未知の命令\n");
            return false;
    }

    // PC 更新と、順次(+1)かどうかの表示
    *pc = nextPC;
    if (*pc == oldPC + 1) {
        printf("  PCの更新: %d -> %d (順次進行: +1)\n\n", oldPC, *pc);
    } else {
        printf("  PCの更新: %d -> %d (分岐/ジャンプ: ≠ +1)\n\n", oldPC, *pc);
    }

    return true;
}

int main(void) {
    printf("## プログラムカウンターの例\n");
    printf("順次進行では PC は +1。分岐や繰り返しでは PC が任意アドレス(≠+1)に設定されます。\n\n");

    // デモ用プログラム:
    // 0: LOAD 3     ; R=3
    // 1: NOP        ; 順次(+1)
    // 2: DEC        ; R=2
    // 3: JNZ 2      ; R!=0 なら PC=2 に戻って繰り返し(≠+1)
    // 4: JMP 6      ; 無条件ジャンプで分岐(≠+1)
    // 5: NOP        ; (ここは飛ばされる)
    // 6: HALT
    Instr program[] = {
        {OP_LOAD, 3},
        {OP_NOP,  0},
        {OP_DEC,  0},
        {OP_JNZ,  2},
        {OP_JMP,  6},
        {OP_NOP,  0},
        {OP_HALT, 0}
    };
    int prog_len = (int)(sizeof(program)/sizeof(program[0]));

    int pc = 0;  // プログラムカウンター
    int R  = 0;  // 汎用レジスタ

    // 実行ループ
    while (step(program, prog_len, &pc, &R)) {
        // 1ステップずつ実行
    }

    printf("\n実行終了: PC=%d, R=%d\n", pc, R);
    return EXIT_SUCCESS;
}
