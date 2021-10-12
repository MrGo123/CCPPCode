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
    // link:导入语句链表, asm_link:汇编链表
    Dual* get, *get1, *get2;
    Link* sentence;
    int i, j, k;
    int last_type = T_ERR;
    int have_begin= 0; // 用于判断语句内部语句表框架 记录 BEGIN 和 END 次数
    int iner= 0; // 语句表标志位
    int err_sum = 0, show_line_sum = 0, i_temp;
    Link* sentence_link, *temp, *temp1;
    Asm* asm_get;
    Link* all_sentence = link_create();
    // 初步 汇编语句链表
    if (asm_link == NULL)
    {
        asm_link = link_create();
    }
    // 初步 创建 id_table 链表
    if (id_table == NULL)
    {
        id_table = link_create();
    }
    get1 = (Dual *)link_get_i(link, 0);
    get2 = (Dual *)link_get_i(link, link->len-1);

    // 判断初步读入语句是否为完整语句表
    if (get1->dual_type == T_BEGIN && get2->dual_type == T_END)
    {
        iner = 1;
        i = 1; // 跳过单词节点 BEGIN
    }
    else
    {
        i = 0;
    }
    have_begin = 0;
    // 对语句表进行处理
    while (i < link->len)
    {
        sentence = link_create();
        have_begin = 0;
        do
        {
            get = (Dual *)link_get_i(link, i);
            // 记录 BEGIN END 出现次数
            if (get->dual_type == T_BEGIN)
            {
                have_begin++;
            }
            else if (get->dual_type == T_END)
            {
                have_begin--;
            }
            // 单词节点添加到语句中
            link_add(sentence, get);
            // 确定其遍历为完整语句表
            if (iner == 1 && i == link->len-2)
            {
                i +=2;
                break;
            }
            i++;
            
        } while (((get->dual_type != T_ELSE && get->dual_type != T_DO \
        && get->dual_type != T_THEN && get->dual_type != T_CUT \
        && get->dual_type != T_END) || (have_begin)) && i < link->len);
        // 将语句添加到整体语句链表中
        link_add(all_sentence, sentence);
    }
    // 遍历所有语句?
    for (i = 0; i < all_sentence->len; i++)
    {
        sentence = (Link *)link_get_i(all_sentence, i);
        get = (Dual *)link_get_i(sentence, 0);
        if (get->dual_type == T_BEGIN)
        {
            turn_to_asm(sentence, asm_link, id_table); // 语句表 递归调用
        }
        // if 语句处理
        else if (get->dual_type == T_IF)
        {
            // 该语句化汇编指令
            temp = sentence_to_asm(sentence, id_table);
            // 汇编链表添加
            link_add_link(asm_link, temp);
            // 获取判断表达式
            temp1 = (Link *)link_get_i(all_sentence, i+1);
            turn_to_asm(temp1, asm_link, id_table); // if 比较表达式 递归调用
            asm_get = (Asm *)link_get_i(temp, temp->len-1); // 返回 if 语句总长度
            asm_get->num = asm_link->len;
            i++;
        }
        // while 语句处理
        else if (get->dual_type == T_WHILE)
        {
            // 当前汇编语句长度(位置),变为循环入口
            i_temp = asm_link->len;
            // 语句转汇编并加入链表
            temp = sentence_to_asm(sentence, id_table);
            link_add_link(asm_link, temp);
            // 处理比较表达式
            temp1 = (Link *)link_get_i(all_sentence, i+1);
            turn_to_asm(temp1, asm_link, id_table);
            asm_get = (Asm *)link_get_i(temp, temp->len-1);
            link_add(asm_link, asm_word(T_ASM_JMP, 0, 0, i_temp)); // jmp 
            asm_get->num = asm_link->len;
            link_destroy(&temp);
            i++;
        }
        // 赋值语句 判断语句等语句处理
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

    p = list->head; // 表达式头节点
    get = (Dual *)(p->data); // 表达式头单词数据

    if (get->dual_type == T_ID)
    {
        addr = get_id_addr(id_table, get->lexme.lexme_text); // *** 标识符添加到id_table表, 我要找个识别标识符的地方把添加语句加进去,立即数用#+数字命名
        if (addr < 0)
        {
            printf("使用了未定义的标识符！在%d行！\n", get->line);
            // show_word(get);
            return ;
        }
        // 赋值语句: 表现形式为,标识符地址赋值给 r2,r1 的存储值符给 r2
        link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R2, 0, addr)); // MOV R2,addr
        link_add(asm_link, asm_word(T_ASM_MOV_REG_MEM, REG_R1, REG_R2, 0)); // MOV R1,(R2)
        p = p->next;
    }
    else if (get->dual_type == T_INT)
    {
        // 表现形式: 立即数赋值给寄存器 r1
        link_add(asm_link, asm_word(T_ASM_MOV_REG_NUM, REG_R1, 0, get->lexme.lexme_num)); // MOV R1,num
        p = p->next;
    }
    // 非赋值语句 || 赋值语句 右半部分处理
    while (p)
    {
        get = (Dual *)(p->data);
        if (get->dual_type == T_CUT_LEFT) // 左括号处理
        {
            kuo_sum = 1;
            list_min = link_create();
            // 括号小语句处理
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
            // 双处理目的寄存器
            link_add(asm_link, asm_word(T_ASM_MOV_REG_REG, REG_R5, REG_R1, addr)); // MOV R5,R1
            // 子语句递归处理
            expression_to_asm(list_min, asm_link, id_table);
            // ***目前未知处理
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
                    printf("未知运行?");
                    break;
                }
            }
            link_destroy(&list_min);
        }
        else
        {
            // 取出带操作数放于 R2
            if (get->dual_type == T_ID)
            {
                addr = get_id_addr(id_table, get->lexme.lexme_text);
                if (addr <0)
                {
                    printf("使用了未定义的标识符！在%d行！\n", get->line);
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
            // 添加 asm
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
    Link* sentence_asm; // 汇编表达式链表
    Dual* get;
    Link* link; // 原表达式
    int i = 0, t, addr;
    sentence_asm = link_create();
    get = (Dual *)link_get_i(sentence, 0);
    if (have_type(sentence, T_EQ)) // 赋值语句
    {
        link = link_create();
        i = 2;
        // 将赋值符号后赋值添加到表达式 link 中
        while (get_type_in_link(sentence, i) != T_CUT && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // link 导入表达式 -> 汇编表达式, get变回赋值变量
        get = (Dual *)link_get_i(sentence, 0);
        expression_to_asm(link, sentence_asm, id_table);
        // 理论理解: 立即数存入寄存器, 寄存器地址值存入寄存器
        link_add(sentence_asm, asm_word(T_ASM_MOV_REG_NUM, REG_R2, 0, get_id_addr(id_table, get->lexme.lexme_text))); // MOV R2,addr
        link_add(sentence_asm, asm_word(T_ASM_MOV_MEM_REG, REG_R2, REG_R1, 0)); // MOV (R2),R1
        link_destroy(&link);
    }
    else if (have_type(sentence, T_WHILE) || have_type(sentence, T_IF)) // IF/WHILE 语句
    {
        // 获取表达式?
        link = link_create();
        i =1;
        // 跳过 if 或 while, 对判断表达式进行处理
        while (get_type_in_link(sentence, i) != T_DO && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // get重新指向 if 或 while 单词
        get = (Dual *)link_get_i(sentence, 0);
        expression_to_asm(link, sentence_asm, id_table);
        if (have_type(sentence, T_LT)) // 大于等于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_NB, 0, 0, 0)); // JB * // 小于->不小于
        }
        else if (have_type(sentence, T_GT)) // 小于等于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_BE, 0, 0, 0)); // NB * // 大于->不大于（小于等于)
        }
        else if (have_type(sentence, T_NE)) // 等于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_E, 0, 0, 0)); // NB * // 不等于->等于
        }
        else if (have_type(sentence, T_LE)) // 大于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_JG, 0, 0, 0)); // NB * // 小于等于->大于
        }
        else if (have_type(sentence, T_GE)) // 小于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_JB, 0, 0, 0)); // NB * // 大于等于->小于
        }
        else if (have_type(sentence, T_CMP0)) // 不等于转移
        {
            link_add(sentence_asm, asm_word(T_ASM_NE,0 , 0, 0)); // NB * // 等于->不等于?
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


