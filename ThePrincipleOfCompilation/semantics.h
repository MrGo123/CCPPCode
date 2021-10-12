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
#define T_ASM_NB 21         // NB ���ڵ���ת��
#define T_ASM_BE 22         // BE С�ڵ���ת��
#define T_ASM_E 23          // E ����ת��
#define T_ASM_JG 24         // JG ����ת��
#define T_ASM_JB 25         // JB С��ת��
#define T_ASM_NE 26         // NE ������ת��
#define REG_R1 31 // R1
#define REG_R2 32 // R2
#define REG_R3 33 // R3
#define REG_R5 35 // R5


// ���ָ��ṹ
typedef struct
{
    int type;   // ������
    int op;     // ԭ�Ĵ���
    int op_ed;  // Ŀ��Ĵ���
    int num;    // ������
}Asm;

// �������
Link* turn_to_asm(Link* link, Link* asm_link, Link* id_table);
// ���ʽ -> �����ʽ
void expression_to_asm(Link* list, Link* asm_link, Link* id_table);
// ��� -> �����ʽ
Link* sentence_to_asm(Link* sentence, Link* id_table);
// �����ʽ����ʽת��
Asm* asm_word(int type, int op, int op_ed, int num);
#endif
