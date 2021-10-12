#include <stdio.h>
#include <malloc.h>
#include <string.h>

// #include "run.h"
#include "link.h"
#include "word.h"
#include "semantics.h"
// #include "show.h"
#include "id_table.h"

Link* turn_to_asm(Link* link, Link* asm_link, Link* id_table)
{
    // link:�����������, asm_link:�������
    Dual* get, *get1, *get2;
    Link* sentence;
    int i, j, k;
    int last_type = T_ERR;
    int have_begin= 0; // �����ж�����ڲ������� ��¼ BEGIN �� END ����
    int iner= 0; // �����־λ
    int err_sum = 0, show_line_sum = 0, i_temp;
    Link* sentence_link, *temp, *temp1;
    Asm* asm_get;
    Link* all_sentence = link_create();
    // ���� ����������
    if (asm_link == NULL)
    {
        asm_link = link_create();
    }
    // ���� ���� id_table ����
    if (id_table == NULL)
    {
        id_table = link_create();
    }
    get1 = (Dual *)link_get_i(link, 0);
    get2 = (Dual *)link_get_i(link, link->len-1);

    // �жϳ�����������Ƿ�Ϊ��������
    if (get1->dual_type == T_BEGIN && get2->dual_type == T_END)
    {
        iner = 1;
        i = 1; // �������ʽڵ� BEGIN
    }
    else
    {
        i = 0;
    }
    have_begin = 0;
    // ��������д���
    while (i < link->len)
    {
        sentence = link_create();
        have_begin = 0;
        do
        {
            get = (Dual *)link_get_i(link, i);
            // ��¼ BEGIN END ���ִ���
            if (get->dual_type == T_BEGIN)
            {
                have_begin++;
            }
            else if (get->dual_type == T_END)
            {
                have_begin--;
            }
            // ���ʽڵ���ӵ������
            link_add(sentence, get);
            // ȷ�������Ϊ��������
            if (iner == 1 && i == link->len-2)
            {
                i +=2;
                break;
            }
            i++;
            
        } while (((get->dual_type != T_ELSE && get->dual_type != T_DO \
        && get->dual_type != T_THEN && get->dual_type != T_CUT \
        && get->dual_type != T_END) || (have_begin)) && i < link->len);
        // �������ӵ��������������
        link_add(all_sentence, sentence);
    }
    // �����������?
    for (i = 0; i < all_sentence->len; i++)
    {
        sentence = (Link *)link_get_i(all_sentence, i);
        get = (Dual *)link_get_i(sentence, 0);
        if (get->dual_type == T_BEGIN)
        {
            turn_to_asm(sentence, asm_link, id_table); // ���� �ݹ����
        }
        // if ��䴦��
        else if (get->dual_type == T_IF)
        {
            // ����仯���ָ��
            temp = sentence_to_asm(sentence, id_table);
            // ����������
            link_add_link(asm_link, temp);
            // ��ȡ�жϱ��ʽ
            temp1 = (Link *)link_get_i(all_sentence, i+1);
            turn_to_asm(temp1, asm_link, id_table); // if �Ƚϱ��ʽ �ݹ����
            asm_get = (Asm *)link_get_i(temp, temp->len-1); // ���� if ����ܳ���
            asm_get->num = asm_link->len;
            i++;
        }
        // while ��䴦��
        else if (get->dual_type == T_WHILE)
        {
            // ��ǰ�����䳤��(λ��),��Ϊѭ�����
            i_temp = asm_link->len;
            // ���ת��ಢ��������
            temp = sentence_to_asm(sentence, id_table);
            link_add_link(asm_link, temp);
            // ����Ƚϱ��ʽ
            temp1 = (Link *)link_get_i(all_sentence, i+1);
            turn_to_asm(temp1, asm_link, id_table);
            asm_get = (Asm *)link_get_i(temp, temp->len-1);
            link_add(asm_link, asm_word(T_ASM_JMP, 0, 0, i_temp)); // jmp 
            asm_get->num = asm_link->len;
            link_destroy(&temp);
            i++;
        }
        // ��ֵ��� �ж�������䴦��
        else
        {
            sentence_link = sentence_to_asm(sentence, id_table);
            link_add_link(asm_link, sentence_link);
            link_destroy(&sentence_link);
        }
        
    }
    return asm_link;
}

void expression_to_asm(Link* list, Link* asm_link, Link* id_table)
{
    Link* list_min;
    LinkNode* p;
    int kuo_sum, addr;
    Dual* get = NULL,*last_get = NULL;

    p = list->head; // ���ʽͷ�ڵ�
    get = (Dual *)(p->data); // ���ʽͷ��������

    if (get->dual_type == T_ID)
    {
        addr = get_id_addr(id_table, get->lexme.lexme_text); // *** ��ʶ����ӵ�id_table��, ��Ҫ�Ҹ�ʶ���ʶ���ĵط���������ӽ�ȥ,��������#+��������
        if (addr < 0)
        {
            printf("ʹ����δ����ı�ʶ������%d�У�\n", get->line);
            // show_word(get);
            return ;
        }
        // ��ֵ���: ������ʽΪ,��ʶ����ַ��ֵ�� r2,r1 �Ĵ洢ֵ���� r2
        link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R2, 0, addr)); // MOV R2,addr
        link_add(asm_link, asm_word(T_ASM_MOV_REG_MEM, REG_R1, REG_R2, 0)); // MOV R1,(R2)
        p = p->next;
    }
    else if (get->dual_type == T_INT)
    {
        // ������ʽ: ��������ֵ���Ĵ��� r1
        link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R1, 0, get->lexme.lexme_num)); // MOV R1,num
        p = p->next;
    }
    // �Ǹ�ֵ��� || ��ֵ��� �Ұ벿�ִ���
    while (p)
    {
        get = (Dual *)(p->data);
        if (get->dual_type == T_CUT_LEFT) // �����Ŵ���
        {
            kuo_sum = 1;
            list_min = link_create();
            // ����С��䴦��
            while (1)
            {
                p = p->next;
                get = (Dual *)(p->data);
                if (get->dual_type == T_CUT_LEFT)
                {
                    kuo_sum++;
                }
                else if (get->dual_type == T_CUT_RIGHT)
                {
                    kuo_sum--;
                }
                if (kuo_sum == 0)
                {
                    break;
                }
                link_add(list_min, get);
            }
            // ˫����Ŀ�ļĴ���
            link_add(asm_link, asm_word(T_ASM_MOV_REG_REG, REG_R5, REG_R1, addr)); // MOV R5,R1
            // �����ݹ鴦��
            expression_to_asm(list_min, asm_link, id_table);
            // ***Ŀǰδ֪����
            if (last_get)
            {
                switch (last_get->dual_type)
                {
                case T_ADD:
                    link_add(asm_link, asm_word(T_ASM_ADD, REG_R1, REG_R5, 0)); // ADD R1,R5
                    break;
                case T_SUB:
                    link_add(asm_link, asm_word(T_ASM_SUB, REG_R5, REG_R1, 0)); // SUB R5,R1
                    link_add(asm_link, asm_word(T_ASM_MOV_REG_REG, REG_R1, REG_R5, addr)); // MOV R1,R5
                    break;
                default:
                    printf("δ֪����?");
                    break;
                }
            }
            link_destroy(&list_min);
        }
        else
        {
            // ȡ�������������� R2
            if (get->dual_type == T_ID)
            {
                addr = get_id_addr(id_table, get->lexme.lexme_text);
                if (addr <0)
                {
                    printf("ʹ����δ����ı�ʶ������%d�У�\n", get->line);
                    // show_word(get);
                    return ;
                }
                link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R3, 0, addr)); // MOV R3,addr
                link_add(asm_link, asm_word(T_ASM_MOV_REG_MEM, REG_R2, REG_R3, 0)); // MOV R2,(R3)
            }
            else if (get->dual_type == T_INT)
            {
                link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R2, 0, get->lexme.lexme_num)); // MOV R2,num
            }
            // ��� asm
            if (last_get && last_get->dual_type == T_ADD)
            {
                link_add(asm_link, asm_word(T_ASM_ADD, REG_R1, REG_R2, 0)); // ADD R1,R2
            }
            else if (last_get && last_get->dual_type == T_SUB)
            {
                link_add(asm_link, asm_word(T_ASM_SUB, REG_R1, REG_R2, 0)); // SUB R1,R2
            }
            else if (last_get && (last_get->dual_type == T_LT || last_get->dual_type == T_GT \
                || last_get->dual_type == T_NE || last_get->dual_type == T_LE || last_get->dual_type == T_GE \
                || last_get->dual_type == T_GE || last_get->dual_type == T_CMP0))
            {
                link_add(asm_link, asm_word(T_ASM_CMP, REG_R1, REG_R2, 0)); // CMP R1,R5
            }
        }
        last_get =get;
        p = p->next;
    }
}

Link* sentence_to_asm(Link* sentence, Link* id_table)
{
    Link* sentence_asm; // �����ʽ����
    Dual* get;
    Link* link; // ԭ���ʽ
    int i = 0, t, addr;
    sentence_asm = link_create();
    get = (Dual *)link_get_i(sentence, 0);
    if (have_type(sentence, T_EQ)) // ��ֵ���
    {
        link = link_create();
        i = 2;
        // ����ֵ���ź�ֵ��ӵ����ʽ link ��
        while (get_type_in_link(sentence, i) != T_CUT && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // link ������ʽ -> �����ʽ, get��ظ�ֵ����
        get = (Dual *)link_get_i(sentence, 0);
        expression_to_asm(link, sentence_asm, id_table);
        // �������: ����������Ĵ���, �Ĵ�����ֵַ����Ĵ���
        link_add(sentence_asm, asm_word(T_ASM_MOV_REG_NUM, REG_R2, 0, get_id_addr(id_table, get->lexme.lexme_text))); // MOV R2,addr
        link_add(sentence_asm, asm_word(T_ASM_MOV_MEM_REG, REG_R2, REG_R1, 0)); // MOV (R2),R1
        link_destroy(&link);
    }
    else if (have_type(sentence, T_WHILE) || have_type(sentence, T_IF)) // IF/WHILE ���
    {
        // ��ȡ���ʽ?
        link = link_create();
        i =1;
        // ���� if �� while, ���жϱ��ʽ���д���
        while (get_type_in_link(sentence, i) != T_DO && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // get����ָ�� if �� while ����
        get = (Dual *)link_get_i(sentence, 0);
        expression_to_asm(link, sentence_asm, id_table);
        if (have_type(sentence, T_LT)) // ���ڵ���ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_NB, 0, 0, 0)); // JB * // С��->��С��
        }
        else if (have_type(sentence, T_GT)) // С�ڵ���ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_BE, 0, 0, 0)); // NB * // ����->�����ڣ�С�ڵ���)
        }
        else if (have_type(sentence, T_NE)) // ����ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_E, 0, 0, 0)); // NB * // ������->����
        }
        else if (have_type(sentence, T_LE)) // ����ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_JG, 0, 0, 0)); // NB * // С�ڵ���->����
        }
        else if (have_type(sentence, T_GE)) // С��ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_JB, 0, 0, 0)); // NB * // ���ڵ���->С��
        }
        else if (have_type(sentence, T_CMP0)) // ������ת��
        {
            link_add(sentence_asm, asm_word(T_ASM_NE,0 , 0, 0)); // NB * // ����->������?
        }
        link_destroy(&link);
    }
    // show_asm(sentence_asm);
    return sentence_asm;
}

Asm* asm_word(int type, int op, int op_ed, int num)
{
    Asm* asm_word;
    asm_word = (Asm *)malloc((int)sizeof(Asm));
    asm_word->type = type;
    asm_word->op = op;
    asm_word->op_ed = op_ed;
    asm_word->num = num;
    return asm_word;
}


