#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include "link.h"

#define T_ASM_JMP 10            // JMP
#define T_ASM_MOV_REG_NUM 11    // MOV R2,addr
#define T_ASM_MOV_REG_MEM 12    // MOV R1,(R2)
#define T_ASM_MOV_REG_REG 13    // MOV R5,R1
#define T_ASM_MOV_MEM_REG 14    // MOV (R2),R1
#define T_ASM_ADD 15        // ADD
#define T_ASM_SUB 16        // SUB
#define T_ASM_CMP 17        // CMP
#define T_ASM_NB 21         // NB 大于等于转移
#define T_ASM_BE 22         // BE 小于等于转移
#define T_ASM_E 23          // E 等于转移
#define T_ASM_JG 24         // JG 大于转移
#define T_ASM_JB 25         // JB 小于转移
#define T_ASM_NE 26         // NE 不等于转移
#define REG_R1 31 // R1
#define REG_R2 32 // R2
#define REG_R3 33 // R3
#define REG_R5 35 // R5


// 汇编指令结构
typedef struct
{
    int type;   // 操作码
    int op;     // 原寄存器
    int op_ed;  // 目标寄存器
    int num;    // 立即数
}Asm;

// 语义分析
Link* turn_to_asm(Link* link, Link* asm_link, Link* id_table);
// 表达式 -> 汇编表达式
void expression_to_asm(Link* list, Link* asm_link, Link* id_table);
// 语句 -> 汇编表达式
Link* sentence_to_asm(Link* sentence, Link* id_table);
// 汇编表达式语句格式转换
Asm* asm_word(int type, int op, int op_ed, int num);
#endif
