#include "word.h"

int word_control(Link *link, char *text)
{
    char *s = text, word[100];
    int i = 0, len, type, jump_len = 0; // ����ע������
    int line_num = 1; // ��¼����������
    int err_sum = 0; // ͳ�ƴʷ���������

    if (link == NULL)
    {
        printf("Link����Ϊ��\n\n");
        return -1;
    }
    while (*s)
    {
        len = get_word(word, s);
        // δ�������ʣ��ҵ���λ��Ϊ0������������ַ�������
        if (word[0] == 0 && *(s + len) == 0)
        {
            break;
        }
        // ��ȡ���ʴ��� word����ʼ�������ͼ��
        type = get_type(word);
        if (type == T_ERR)
        {
            // ��ȡ��������
            line_num += get_line_change(s, jump_len + len);
            printf("(ERR)In line %d :UNKNOW WORD: (%s)\n", line_num, word);
            s += len; // ������λ��
            err_sum++;
        }
        else
        {
            jump_len = 0;
            if (type == T_N_LINE || type == T_N_BEGIN) // ����ע�ͳ���
            {
                jump_len = to_n_end(s + len, type);
            }
            // ����������
            line_num += get_line_change(s, jump_len + len);
            // ָ��ǰ��
            s += jump_len + len;
            if (type == T_N_BEGIN ||type == T_N_END || type == T_N_LINE)
            // ����ע������
            {
                continue;
            }

            Dual *p = (Dual *)malloc((int)sizeof(Dual));
            if (p == NULL)
            {
                printf("��Ԫʽ�洢�ṹ����ʧ��\n\n");
                return -1;
            }
            // ���������ݴ洢��p�ڵ�
            p->dual_type = type;
            p->line = line_num;
            if (type == T_INT)
            {
                p->lexme.lexme_num = char_to_num(word);
                // printf("num::%d\n", char_to_num(word));
            }
            else
            {
                strcpy(p->lexme.lexme_text, word);
            }
            // �����ʽڵ���� link ����
            link_add(link, p);
        }
    }
    return err_sum;
}

int get_word(char *word, char *s)
{
    int len = 0, i = 0;
    // �����ɺ����ַ�
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
    {
        i++;
    }
    // ����/��ʶ��
    if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
    {
        while ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            word[len++] = s[i++];
        }
    }
    // =
    else if (s[i] == '=')
    {
        word[len++] = s[i++];
        // ==
        if (s[i] == '=')
        {
            word[len++] = s[i++];
        }
    }
    // :
    else if (s[i] == ':')
    {
        word[len++] = s[i++];
        // :=
        if (s[i] == '=')
        {
            word[len++] = s[i++];
        }
    }
    // <
    else if (s[i] == '<')
    {
        word[len++] = s[i++];
        // <= <>
        if (s[i] == '=' || s[i] == '>')
        {
            word[len++] = s[i++];
        }
    }
    // >
    else if (s[i] == '>')
    {
        word[len++] = s[i++];
        // >=
        if (s[i] == '=')
        {
            word[len++] = s[i++];
        }
    }
    // +
    else if (s[i] == '+')
    {
        word[len++] = s[i++];
    }
    // -
    else if (s[i] == '-')
    {
        word[len++] = s[i++];
    }
    // *
    else if (s[i] == '*')
    {
        word[len++] = s[i++];
        // */
        if (s[i] == '/')
        {
            word[len++] = s[i++];
        }
    }
    // /
    else if (s[i] == '/')
    {
        word[len++] = s[i++];
        // // /*
        if (s[i] == '/' || s[i] == '*')
        {
            word[len++] = s[i++];
        }
    }
    // ;,()
    else if (s[i] == ';' || s[i] == ',' || s[i] == '(' || s[i] == ')')
    {
        word[len++] = s[i++];
    }
    // ���������δ֪�ַ������ڵ��������κα�ʶ�����������
    else
    {
        while (s[i] && s[i] != ' ' && s[i] != ';' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n' && s[i] != ':' && s[i] != '=' && s[i] != '<' && s[i] != '>' && s[i] != '/' && s[i] != ',')
        {
            word[len++] = s[i++];
        }
    }
    word[len] = 0; // word �洢��ȡ s �ַ������ص��ʣ���ĩβ�� 0
    return i;      // ���ض�ȡ s �ַ����ӿ�ʼ�����ʽ����ĳ���
}

int get_type(char *word)
{
    int i = 0;
    if (word[i] == '<')
    { 
        if (word[i+1] == 0)
        {
            return T_LT;
        }
        else if (word[i+1] == '=' && word[i+2] == 0)
        {
            return T_LE;
        }
        else if (word[i+1] == '>' && word[i+2] == 0)
        {
            return T_NE;
        }
    }
    else if (word[i] == '>')
    {
        if (word[i+1] == 0)
        {
            return T_GT;
        }
        else if (word[i+1] == '=' && word[i+2] == 0)
        {
            return T_GE;
        }
    }
    else if (strcmp(word, "==") == 0)
    {
        return T_CMP0;
    }
    else if (strcmp(word, ":=") == 0)
    {
        return T_EQ;
    }
    else if (strcmp(word, "+") == 0)
    {
        return T_ADD;
    }
    else if (strcmp(word, "-") == 0)
    {
        return T_SUB;
    }
    else if (word[i] == '*')
    {
        if (word[i+1] == 0)
        {
            return T_MUL;
        }
        else if (word[i+1] == '/' && word[i+2] == 0)
        {
            return T_N_END;
        }
    }
    else if (word[i] == '/')
    {
        if (word[i+1] == 0)
        {
            return T_DIV;
        }
        else if (word[i+1] == '/' && word[i+2] == 0)
        {
            return T_N_LINE;
        }
        else if (word[i+1] == '*' && word[i+2] == 0)
        {
            return T_N_BEGIN;
        }
    }
    else if (strcmp(word, ";") == 0)
    {
        return T_CUT;
    }
    else if (strcmp(word, ",") == 0)
    {
        return T_POINT;
    }
    else if (strcmp(word, "(") == 0)
    {
        return T_CUT_LEFT;
    }
    else if (strcmp(word, ")") == 0)
    {
        return T_CUT_RIGHT;
    }
    // ����
    else if (word[i] >= '0' && word[i] <= '9')
    {
        while (word[i] >= '0' && word[i] <= '9')
        {
            i++;
        }
        if (word[i] == 0)
        {
            return T_INT;
        }
    }
    // ��ʶ��
    else if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
    {
        while ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9'))
        {
            i++;
            if (i == 2)
            {
                if (strcmp(word, "IF") == 0)
                {
                    return T_IF;
                }
                else if (strcmp(word, "DO") == 0)
                {
                    return T_DO;
                }
            }
            else if (i == 3)
            {
                if (strcmp(word, "END") == 0)
                {
                    return T_END;
                }
            }
            else if (i == 4)
            {
                if (strcmp(word, "THEN") == 0)
                {
                    return T_THEN;
                }
                else if (strcmp(word, "ELSE") == 0)
                {
                    return T_ELSE;
                }
            }
            else if (i == 5)
            {
                if (strcmp(word, "BEGIN") == 0)                                                                                                         
                {
                    return T_BEGIN;
                }
                
                else if (strcmp(word, "WHILE") == 0)
                {
                    return T_WHILE;
                }
            }  
        }
        if (word[i] == 0)
        {
            return T_ID;
        }
    }
    return T_ERR;
}

int get_line_change(char *s, int len)
{
    int i = 0, j = 0;
    while (s[j] && j < len)
    {
        if (s[j] == '\n')
        {
            i++;
        }
        j++;
    }
    return i;
}

int to_n_end(char *s, int type)
{
    int i = 0;
    if (type == T_N_LINE) //��ע�ͷ�
    {
        while (s[i] != 0 && s[i] != '\n')
        {
            i++;
        }
        return i;
    }
    else if (type == T_N_BEGIN)
    {
        while (s[i] != 0 && (s[i] != '*' && s[i + 1] != '/'))
        {   
            i++;
        }
        if (s[i])
        {
            return i;
        }
    }
    return 0;
}

int char_to_num(char *s)
{
    int result = 0;
    while (*s >= '0' && *s <= '9')
    {
        result *= 10;
        result += *s - '0';
        s++;
    }
    return result;
}

// �Ǵʷ�����ʹ��

int have_type(Link *sentence, int type)
{
    Dual *get;
    int i;
    for (int i = 0; i < sentence->len; i++)
    {
        get = (Dual *)link_get_i(sentence, i);
        if (get->dual_type == type)
        {
            return 1;
        }
    }
    return 0;
}

int get_type_in_link(Link *link, int i)
{
    Dual *get;
    if (link == NULL || i >= link->len)
    {
        return -10;
    }
    get = (Dual *)link_get_i(link, i);
    return get->dual_type;
}
