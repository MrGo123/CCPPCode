#include <stdio.h>

#include "sentence.h"

int show_line_sum = 0;

// show_word(get);

// 语法分析
int grammar_control(Link* link, int level)
{
    int i, j, k;
    int last_type = T_ERR;
    int have_begin = 0;
    int iner = 0;
    int err_sum = 0, temp, show_linesum = 0;
    Dual *get, *get1, *get2;
    Link *sentence;
    Link* all_sentence = link_create();

    get1 = (Dual *)link_get_i(link, 0);
    get2 = (Dual *)link_get_i(link, link->len-1);
    if (get1 == NULL || get2 == NULL)
    {
        printf("\n(Grammar Analysis) 缺少关键元素！\n");
        return 1;
    }
    //  判断语句表开头，跳过二元式最外层 begin 和 end  
    if (get1->dual_type == T_BEGIN && get2->dual_type == T_END)
    {
        iner = 1;
        i = 1;
    }
    else
    {
        i = 0;
    }
    // 将单词二元式进行语句分割
    while (i<link->len)
    {
        sentence = link_create();
        have_begin = 0;
        do
        {
            get = (Dual *)link_get_i(link, i);
            if (get == NULL)
            {
                printf("(Grammar Analysis) 缺少关键元素！\n");
                return 1;
            }
            // have_begin 处理 BEGIN 和 END 构成的语句表，BEGIN 和 END 不匹配报错弹出
            if (get->dual_type == T_BEGIN)
            {
                have_begin++;
            }
            else if (get->dual_type == T_END)
            {
                if (have_begin == 0)
                {
                    printf("\n(Grammar Analysis) 缺少开始符号！（在第 %d 行）\n", get->line);
                    return -1;
                }
                else
                {
                    have_begin--;
                }
            }
            // 将二元式添加入语句中
            link_add(sentence, get);
            // 输入 link 为完整的 BEGIN 到 END 的语句表，完成跳出
            if (iner == 1 && i == link->len-2)
            {
                i += 2;
                break;
            }
            i++;    
        } while (((get->dual_type != T_ELSE && get->dual_type != T_DO \
        && get->dual_type != T_THEN && get->dual_type != T_CUT \
        && get->dual_type != T_END) || (have_begin)) && i < link->len);
        // 循环条件：非条件语句，循环语句关键字，语句分隔符，语句表结束符号，语句表未结束时前向约束失效；循环语句不超过导入 link 长度
        // 语句添加入语句链表
        link_add(all_sentence, sentence);
    }
    // 在 get 二元式在语句读入完成推出循环时，语句表未清算完成，或语句表清算完成，但结束单词非语句分隔符或 END
    if (have_begin != 0 || (have_begin == 0 && (get->dual_type != T_CUT \
    && get->dual_type != T_END)))
    {
        printf("\n(Grammar Analysis) 缺少结束符！（在 %d 行）%d\n", get->line, have_begin);
        return -1;
    }
    // 遍历所有语句
    for (int i = 0; i < all_sentence->len; i++)
    {
        sentence = (Link *)link_get_i(all_sentence, i);
        get = (Dual *)link_get_i(sentence, 0);
        // 如果语句类型为条件语句或循环语句，且为全语句的最后一条，报错
        // （按语法结构，THEN 或 DO 后接执行语句，但为最后语句无要执行语句）
        if ((get->dual_type == T_IF || get->dual_type == T_WHILE) \
        && i == all_sentence->len-1)
        {
            get = (Dual *)link_get_i(sentence, 0);
            // show_line(get->line);
            printf("\n(Grammar Analysis) error line: %d\n", get->line);
            printf("不完整的语句体！\n\n");
            err_sum++;
        }
        // 读取到语句表入口 Begin
        // 界面输出格式控制
        if (get->dual_type == T_BEGIN)
        {
            for (k = 0; k < level-(!!(show_line_sum == 0)); k++)
            {
                printf("\t");
            }
            if (level && show_line_sum++==0)
            {
                printf("+-------");
            }
            if (level)
            {
                printf("|");
            }
            show_word(get);
            
            // 递归遍历语句集
            // 递归语句表时，语句表内部发现错误，进行统计
            if ((temp = grammar_control(sentence, level+1)) != 0)
            {
                get = (Dual *)link_get_i(sentence, 0);
                err_sum += temp;
            }
            get = (Dual *)link_get_i(sentence, sentence->len-1);
            // 理论为处理末尾 END 为理解其他功能
            for (k = 0; k < level-(!!(show_line_sum == 0)); k++)
            {
                printf("\t");
            }
            if (level && show_line_sum++==0)
            {
                printf("+-------");
            }
            if (level)
            {
                printf("|");
            }
            show_word(get);
        }
        else
        {
            for (j = 0; j < sentence->len; j++)
            {
                get = (Dual *)link_get_i(sentence, j);
                // 界面输出格式控制
                for (k = 0; k < level-(!!(show_line_sum == 0)); k++)
                {
                    printf("\t");
                }
                if (level && show_line_sum++==0)
                {
                    printf("+-------");
                }
                if (level)
                {
                    printf("|");
                }
                show_word(get);
            }
            // 判断语句是否合法
            if (legitimate_statement(sentence) != 0)
            {
                get = (Dual *)link_get_i(sentence, 0);
                printf("\n(Grammar Analysis) error line: %d\n", get->line);
                // show_line(get->line);
                printf("语法错误！\n\n");
                // return -1;
                err_sum++;
            }   
        }
    }
    return err_sum;
}

// 判断语句是否合法
int legitimate_statement(Link* sentence)
{
    Dual* get;
    Link* link;
    int i = 0, t;

    get = (Dual *)link_get_i(sentence, 0);
    //赋值语句
    
    if (have_type(sentence, T_EQ)) 
    {
        if (get_type_in_link(sentence, 0) != T_ID \
        || get_type_in_link(sentence, 1) != T_EQ)
        {
            printf("\n(Grammar Analysis) 不可修改的左值！在第 %d 行\n", get->line);
            return -1;
        }
        else
        {
            link = link_create();
            i = 2;
            while (get_type_in_link(sentence, i) != T_CUT && i < sentence->len)
            {
                get = (Dual *)link_get_i(sentence, i);
                link_add(link, get);
                i++;
            }
            // 若语句长度等于读取单词长度且未读取分隔符
            if (i == sentence->len)
            {
                printf("\n(Grammar Analysis) 未结束的表达式！在第 %d 行\n", get->line);
                link_destroy(&link);
                return -2;
            }
            // 赋值表达式有赋值单词，有标识符变量，有结束分隔符，进入后半段表达式判断，link只包含 "a := b;" 的 "b" 部分
            else
            {
                if ((t = legitimate_expression(link)) != 0)
                {
                    // show_link(sentence);
                    printf("\n(Grammar Analysis) 不合法的表达式！在第 %d 行\n", get->line);
                    link_destroy(&link);
                    return -3;
                }
            }
            link_destroy(&link);
        }
    }
    // IF 判断语句
    else if (have_type(sentence, T_IF))
    {
        // 如果语句中不存在 THEN
        if (have_type(sentence, T_THEN) == 0)
        {
            printf("\n(Grammar Analysis) 缺少: THEN！在第 %d 行\n", get->line);
            return -2;
        }
        // 获取表达式链表
        link = link_create();
        i = 1;
        while (get_type_in_link(sentence, i) != T_THEN && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // 判断表达式是否合法
        if (i == sentence->len)
        {
            printf("\n(Grammar Analysis) 未结束的表达式！在第 %d 行\n", get->line);
            link_destroy(&link);
            return -2;
        }
        else
        {
            if ((t = legitimate_expression(link)) != 0)
            {
                // show_link(sentence);
                printf("\n(Grammar Analysis) 不合法的表达式！在第 %d 行\n", get->line);
                link_destroy(&link);
                return -3;
            }
            
        }
        link_destroy(&link);
    }
    // WHILE 语句
    else if (have_type(sentence, T_WHILE))
    {
        // 语句不存在 DO
        if (have_type(sentence, T_DO) == 0) 
        {
            printf("\n(Grammar Analysis) 缺少: DO！在第 %d 行\n", get->line);
            return -3;
        }
        // 获取表达式链表
        link = link_create();
        i = 1;
        while (get_type_in_link(sentence, i) != T_DO && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // 判断表达式是否合法
        if (i == sentence->len)
        {
            printf("\n(Grammar Analysis) 未结束的表达式！在第 %d 行\n", get->line);
            link_destroy(&link);
            return -2;
        }
        else
        {
            if ((t = legitimate_expression(link)) != 0)
            {
                // show_link(sentence);
                printf("\n(Grammar Analysis) 不合法的表达式！在第 %d 行\n", get->line);
                link_destroy(&link);
                return -3;
            }
            
        }
        link_destroy(&link);
    }
    // DO 语句
    else if (have_type(sentence, T_DO))
    {
        // 语句不存在 WHILE
        if (have_type(sentence, T_WHILE) == 0) 
        {
            printf("缺少: WHILE！在第 %d 行\n", get->line);
            return -4;
        }
    }
    // THEN 语句  
    else if (have_type(sentence, T_THEN))
    {
        // 语句不存在 IF
        if (have_type(sentence, T_IF) == 0) 
        {
            printf("\n(Grammar Analysis) 缺少: IF！在第 %d 行\n", get->line);
            return -5;
        }
    }
    // ELSE 语句
    else if (have_type(sentence, T_THEN))
    {
        printf("\n(Grammar Analysis) 缺少: DO！在第 %d 行\n", get->line);
        return -5;
    }
    // 未知语句判断
    else
    {
        printf("\n(Grammar Analysis) 错误的语句！在第 %d 行\n", get->line);
        return -7;
    }
    
    return 0;
}

// 判断表达式是否合法
int legitimate_expression(Link* link)
{
    int i = 0;
    int t,last_t;
    int kuo_sum = 0; // 括号统计机制
    Dual* p ;
    last_t = get_type_in_link(link, 0);
    t = last_t;
    // 若首位不为标识符变量，常数，左括号
    if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
    {
        printf("\n(Grammar Analysis) 错误的表达式开始！");
        return -1;
    }
    for (i = 1; i < link->len; i++)
    {
        // 根据首位单词对其余单词进行分析
        // 检测 last_t 和 t ，根据 last_t 类型判断 t 的正确跟随
        p = (Dual *)link_get_i(link, i);
        t = p->dual_type;
        switch (last_t)
        {
            // 标识符变量，常量
        case T_ID:
        case T_INT:
            // 非数值运算符，非右括号，非关系运算符
            if (t != T_ADD && t != T_SUB && t != T_MUL \
            && t != T_DIV && t != T_CUT_RIGHT && t != T_LT \
            && t != T_LE && t != T_NE && t != T_GT && t != T_GE \
            && t != T_CMP0)
            {
                printf("\n(Grammar Analysis) 错误的运算符！在第 %d 词（变量位置）！\n", i);
                return -2;
            }
            break;
            // 左括号
        case T_CUT_LEFT:
            kuo_sum++;
            // 非数值标识符，常量，左括号
            if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
            {
                printf("\n(Grammar Analysis) 错误的操作数！在第 %d 词！\n", i);
                return -3;
            }
            break;
            // 右括号
        case T_CUT_RIGHT:
            // 先对 last_t 进行分析 
            if (kuo_sum == 0)
            {
                printf("\n(Grammar Analysis) 错误的右括号！在第 %d 词！\n", i);
                return -12;
            }
            else
            {
                kuo_sum--;
            }
            // t 若非数值标识符，非右括号，非表达式
            if (t != T_ADD && t != T_ADD && t != T_MUL \
            && t != T_DIV && t != T_CUT_RIGHT && t != T_LT \
            && t != T_LE && t != T_NE && t != T_GT && t != T_GE \
            && t != T_CMP0)
            {
                printf("\n(Grammar Analysis) 错误的运算符！在第 %d 词！（右括号位置）\n", i);
                return -4;
            }
            break;
            // 运算符
        case T_ADD:
        case T_SUB:
        case T_MUL:
        case T_DIV:
        case T_LT:
        case T_LE:
        case T_NE:
        case T_GT:
        case T_GE:
        case T_CMP0:
            // 非数值标识符，常量，左括号
            if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
            {
                printf("\n(Grammar Analysis) 错误的操作数！在第 %d 词！\n", i);
                return -5;
            }
            break;
        default:
            printf("\n(Grammar Analysis) 语法分析，表达式合法性检查，未知错误！\n");
            return -100;
            break;
        }
        // 当前检测单词传递给前位置
        last_t = t;
    }
    // 错误的表达式结尾
    if (t != T_ID && t != T_INT && t != T_CUT_RIGHT)
    {
        printf("\n(Grammar Analysis) 错误在表达式结尾！在第 %d 词！\n", i);
        return -3;
    }
    // 最后右括号恢复
    if (t == T_CUT_RIGHT)
    {
        kuo_sum--;
    }
    // 判断括号是否匹配
    if (kuo_sum != 0)
    {
        printf("\n(Grammar Analysis) 错误的括号匹配！在第 %d 词！\n", i);
        return -7;
    }
    // 表达式合法
    return 0;  
}


