#include <stdio.h>

#include "sentence.h"

int show_line_sum = 0;

// show_word(get);

// �﷨����
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
        printf("\n(Grammar Analysis) ȱ�ٹؼ�Ԫ�أ�\n");
        return 1;
    }
    //  �ж�����ͷ��������Ԫʽ����� begin �� end  
    if (get1->dual_type == T_BEGIN && get2->dual_type == T_END)
    {
        iner = 1;
        i = 1;
    }
    else
    {
        i = 0;
    }
    // �����ʶ�Ԫʽ�������ָ�
    while (i<link->len)
    {
        sentence = link_create();
        have_begin = 0;
        do
        {
            get = (Dual *)link_get_i(link, i);
            if (get == NULL)
            {
                printf("(Grammar Analysis) ȱ�ٹؼ�Ԫ�أ�\n");
                return 1;
            }
            // have_begin ���� BEGIN �� END ���ɵ�����BEGIN �� END ��ƥ�䱨����
            if (get->dual_type == T_BEGIN)
            {
                have_begin++;
            }
            else if (get->dual_type == T_END)
            {
                if (have_begin == 0)
                {
                    printf("\n(Grammar Analysis) ȱ�ٿ�ʼ���ţ����ڵ� %d �У�\n", get->line);
                    return -1;
                }
                else
                {
                    have_begin--;
                }
            }
            // ����Ԫʽ����������
            link_add(sentence, get);
            // ���� link Ϊ������ BEGIN �� END �������������
            if (iner == 1 && i == link->len-2)
            {
                i += 2;
                break;
            }
            i++;    
        } while (((get->dual_type != T_ELSE && get->dual_type != T_DO \
        && get->dual_type != T_THEN && get->dual_type != T_CUT \
        && get->dual_type != T_END) || (have_begin)) && i < link->len);
        // ѭ����������������䣬ѭ�����ؼ��֣����ָ���������������ţ�����δ����ʱǰ��Լ��ʧЧ��ѭ����䲻�������� link ����
        // ���������������
        link_add(all_sentence, sentence);
    }
    // �� get ��Ԫʽ������������Ƴ�ѭ��ʱ������δ������ɣ�������������ɣ����������ʷ����ָ����� END
    if (have_begin != 0 || (have_begin == 0 && (get->dual_type != T_CUT \
    && get->dual_type != T_END)))
    {
        printf("\n(Grammar Analysis) ȱ�ٽ����������� %d �У�%d\n", get->line, have_begin);
        return -1;
    }
    // �����������
    for (int i = 0; i < all_sentence->len; i++)
    {
        sentence = (Link *)link_get_i(all_sentence, i);
        get = (Dual *)link_get_i(sentence, 0);
        // ����������Ϊ��������ѭ����䣬��Ϊȫ�������һ��������
        // �����﷨�ṹ��THEN �� DO ���ִ����䣬��Ϊ��������Ҫִ����䣩
        if ((get->dual_type == T_IF || get->dual_type == T_WHILE) \
        && i == all_sentence->len-1)
        {
            get = (Dual *)link_get_i(sentence, 0);
            // show_line(get->line);
            printf("\n(Grammar Analysis) error line: %d\n", get->line);
            printf("������������壡\n\n");
            err_sum++;
        }
        // ��ȡ��������� Begin
        // ���������ʽ����
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
            
            // �ݹ������伯
            // �ݹ�����ʱ�������ڲ����ִ��󣬽���ͳ��
            if ((temp = grammar_control(sentence, level+1)) != 0)
            {
                get = (Dual *)link_get_i(sentence, 0);
                err_sum += temp;
            }
            get = (Dual *)link_get_i(sentence, sentence->len-1);
            // ����Ϊ����ĩβ END Ϊ�����������
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
                // ���������ʽ����
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
            // �ж�����Ƿ�Ϸ�
            if (legitimate_statement(sentence) != 0)
            {
                get = (Dual *)link_get_i(sentence, 0);
                printf("\n(Grammar Analysis) error line: %d\n", get->line);
                // show_line(get->line);
                printf("�﷨����\n\n");
                // return -1;
                err_sum++;
            }   
        }
    }
    return err_sum;
}

// �ж�����Ƿ�Ϸ�
int legitimate_statement(Link* sentence)
{
    Dual* get;
    Link* link;
    int i = 0, t;

    get = (Dual *)link_get_i(sentence, 0);
    //��ֵ���
    
    if (have_type(sentence, T_EQ)) 
    {
        if (get_type_in_link(sentence, 0) != T_ID \
        || get_type_in_link(sentence, 1) != T_EQ)
        {
            printf("\n(Grammar Analysis) �����޸ĵ���ֵ���ڵ� %d ��\n", get->line);
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
            // ����䳤�ȵ��ڶ�ȡ���ʳ�����δ��ȡ�ָ���
            if (i == sentence->len)
            {
                printf("\n(Grammar Analysis) δ�����ı��ʽ���ڵ� %d ��\n", get->line);
                link_destroy(&link);
                return -2;
            }
            // ��ֵ���ʽ�и�ֵ���ʣ��б�ʶ���������н����ָ�����������α��ʽ�жϣ�linkֻ���� "a := b;" �� "b" ����
            else
            {
                if ((t = legitimate_expression(link)) != 0)
                {
                    // show_link(sentence);
                    printf("\n(Grammar Analysis) ���Ϸ��ı��ʽ���ڵ� %d ��\n", get->line);
                    link_destroy(&link);
                    return -3;
                }
            }
            link_destroy(&link);
        }
    }
    // IF �ж����
    else if (have_type(sentence, T_IF))
    {
        // �������в����� THEN
        if (have_type(sentence, T_THEN) == 0)
        {
            printf("\n(Grammar Analysis) ȱ��: THEN���ڵ� %d ��\n", get->line);
            return -2;
        }
        // ��ȡ���ʽ����
        link = link_create();
        i = 1;
        while (get_type_in_link(sentence, i) != T_THEN && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // �жϱ��ʽ�Ƿ�Ϸ�
        if (i == sentence->len)
        {
            printf("\n(Grammar Analysis) δ�����ı��ʽ���ڵ� %d ��\n", get->line);
            link_destroy(&link);
            return -2;
        }
        else
        {
            if ((t = legitimate_expression(link)) != 0)
            {
                // show_link(sentence);
                printf("\n(Grammar Analysis) ���Ϸ��ı��ʽ���ڵ� %d ��\n", get->line);
                link_destroy(&link);
                return -3;
            }
            
        }
        link_destroy(&link);
    }
    // WHILE ���
    else if (have_type(sentence, T_WHILE))
    {
        // ��䲻���� DO
        if (have_type(sentence, T_DO) == 0) 
        {
            printf("\n(Grammar Analysis) ȱ��: DO���ڵ� %d ��\n", get->line);
            return -3;
        }
        // ��ȡ���ʽ����
        link = link_create();
        i = 1;
        while (get_type_in_link(sentence, i) != T_DO && i < sentence->len)
        {
            get = (Dual *)link_get_i(sentence, i);
            link_add(link, get);
            i++;
        }
        // �жϱ��ʽ�Ƿ�Ϸ�
        if (i == sentence->len)
        {
            printf("\n(Grammar Analysis) δ�����ı��ʽ���ڵ� %d ��\n", get->line);
            link_destroy(&link);
            return -2;
        }
        else
        {
            if ((t = legitimate_expression(link)) != 0)
            {
                // show_link(sentence);
                printf("\n(Grammar Analysis) ���Ϸ��ı��ʽ���ڵ� %d ��\n", get->line);
                link_destroy(&link);
                return -3;
            }
            
        }
        link_destroy(&link);
    }
    // DO ���
    else if (have_type(sentence, T_DO))
    {
        // ��䲻���� WHILE
        if (have_type(sentence, T_WHILE) == 0) 
        {
            printf("ȱ��: WHILE���ڵ� %d ��\n", get->line);
            return -4;
        }
    }
    // THEN ���  
    else if (have_type(sentence, T_THEN))
    {
        // ��䲻���� IF
        if (have_type(sentence, T_IF) == 0) 
        {
            printf("\n(Grammar Analysis) ȱ��: IF���ڵ� %d ��\n", get->line);
            return -5;
        }
    }
    // ELSE ���
    else if (have_type(sentence, T_THEN))
    {
        printf("\n(Grammar Analysis) ȱ��: DO���ڵ� %d ��\n", get->line);
        return -5;
    }
    // δ֪����ж�
    else
    {
        printf("\n(Grammar Analysis) �������䣡�ڵ� %d ��\n", get->line);
        return -7;
    }
    
    return 0;
}

// �жϱ��ʽ�Ƿ�Ϸ�
int legitimate_expression(Link* link)
{
    int i = 0;
    int t,last_t;
    int kuo_sum = 0; // ����ͳ�ƻ���
    Dual* p ;
    last_t = get_type_in_link(link, 0);
    t = last_t;
    // ����λ��Ϊ��ʶ��������������������
    if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
    {
        printf("\n(Grammar Analysis) ����ı��ʽ��ʼ��");
        return -1;
    }
    for (i = 1; i < link->len; i++)
    {
        // ������λ���ʶ����൥�ʽ��з���
        // ��� last_t �� t ������ last_t �����ж� t ����ȷ����
        p = (Dual *)link_get_i(link, i);
        t = p->dual_type;
        switch (last_t)
        {
            // ��ʶ������������
        case T_ID:
        case T_INT:
            // ����ֵ��������������ţ��ǹ�ϵ�����
            if (t != T_ADD && t != T_SUB && t != T_MUL \
            && t != T_DIV && t != T_CUT_RIGHT && t != T_LT \
            && t != T_LE && t != T_NE && t != T_GT && t != T_GE \
            && t != T_CMP0)
            {
                printf("\n(Grammar Analysis) �������������ڵ� %d �ʣ�����λ�ã���\n", i);
                return -2;
            }
            break;
            // ������
        case T_CUT_LEFT:
            kuo_sum++;
            // ����ֵ��ʶ����������������
            if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
            {
                printf("\n(Grammar Analysis) ����Ĳ��������ڵ� %d �ʣ�\n", i);
                return -3;
            }
            break;
            // ������
        case T_CUT_RIGHT:
            // �ȶ� last_t ���з��� 
            if (kuo_sum == 0)
            {
                printf("\n(Grammar Analysis) ����������ţ��ڵ� %d �ʣ�\n", i);
                return -12;
            }
            else
            {
                kuo_sum--;
            }
            // t ������ֵ��ʶ�����������ţ��Ǳ��ʽ
            if (t != T_ADD && t != T_ADD && t != T_MUL \
            && t != T_DIV && t != T_CUT_RIGHT && t != T_LT \
            && t != T_LE && t != T_NE && t != T_GT && t != T_GE \
            && t != T_CMP0)
            {
                printf("\n(Grammar Analysis) �������������ڵ� %d �ʣ���������λ�ã�\n", i);
                return -4;
            }
            break;
            // �����
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
            // ����ֵ��ʶ����������������
            if (t != T_ID && t != T_INT && t != T_CUT_LEFT)
            {
                printf("\n(Grammar Analysis) ����Ĳ��������ڵ� %d �ʣ�\n", i);
                return -5;
            }
            break;
        default:
            printf("\n(Grammar Analysis) �﷨���������ʽ�Ϸ��Լ�飬δ֪����\n");
            return -100;
            break;
        }
        // ��ǰ��ⵥ�ʴ��ݸ�ǰλ��
        last_t = t;
    }
    // ����ı��ʽ��β
    if (t != T_ID && t != T_INT && t != T_CUT_RIGHT)
    {
        printf("\n(Grammar Analysis) �����ڱ��ʽ��β���ڵ� %d �ʣ�\n", i);
        return -3;
    }
    // ��������Żָ�
    if (t == T_CUT_RIGHT)
    {
        kuo_sum--;
    }
    // �ж������Ƿ�ƥ��
    if (kuo_sum != 0)
    {
        printf("\n(Grammar Analysis) ���������ƥ�䣡�ڵ� %d �ʣ�\n", i);
        return -7;
    }
    // ���ʽ�Ϸ�
    return 0;  
}


