#include "show.h"

char R[5][3] = {{""},{"R1"},{"R2"},{"R3"},{"R5"}};

void show_LexicalAnalysis(Link *link)
{
	int i = 0;
	Dual *word;
    printf("[seq]\t[type]\t\t[line]\n");
	while (i < link->len)
	{	
		word = (Dual *)link_get_i(link, i);
		if (word != NULL)
		{
			
			printf("[%d] \t", i+1);
			switch (word->dual_type)
            {
            case T_ID:
                printf("标识符{%s}\t", word->lexme.lexme_text);
                break;
            case T_EQ:
                printf(":=\t\t");
                break;
            case T_IF:
                printf("if\t\t");
                break;
            case T_THEN:
                printf("then\t\t");
                break;
            case T_ELSE:
                printf("else\t\t");
                break;
            case T_BEGIN:
                printf("begin\t\t");
                break;
            case T_END:
                printf("end\t\t");
                break;
            case T_WHILE:
                printf("while\t\t");
                break;
            case T_DO:
                printf("do\t\t");
                break;
            case T_INT:
                printf("常量{%d}\t\t", word->lexme.lexme_num);
                break;
            case T_LT:
                printf("<\t\t");
                break;
            case T_LE:
                printf("<=\t\t");
                break;
            case T_NE:
                printf("<>\t\t");
                break;
            case T_GT:
                printf(">\t\t");
                break;
            case T_GE:
                printf(">=\t\t");
                break;
            case T_N_LINE:
                printf("//\t\t");
                break;
            case T_N_BEGIN:
                printf("/*\t\t");
                break;
            case T_N_END:
                printf("*/\t\t");
                break;
            case T_CMP0:
                printf("==\t\t");
                break;
            case T_ADD:
                printf("+\t\t");
                break;
            case T_SUB:
                printf("-\t\t");
                break;
            case T_MUL:
                printf("*\t\t");
                break;
            case T_DIV:
                printf("/\t\t");
                break;
            case T_CUT:
                printf(";\t\t");
                break;
            case T_POINT:
                printf(",\t\t");
                break;
            case T_CUT_LEFT:
                printf("(\t\t");
                break;
            case T_CUT_RIGHT:
                printf(")\t\t");
                break;
            default:
                printf("error!\n");
                break;
            }
            
			printf("%d\n", word->line);
		}
		i++;
	}
}

void show_word(Dual* word)
{
    printf("[line %d]\t", word->line);
    switch (word->dual_type)
    {
    case T_ID:
        printf("标识符{%s}\n", word->lexme.lexme_text);
        break;
    case T_EQ:
        printf(":=\n");
        break;
    case T_IF:
        printf("if\n");
        break;
    case T_THEN:
        printf("then\n");
        break;
    case T_ELSE:
        printf("else\n");
        break;
    case T_BEGIN:
        printf("begin\n");
        break;
    case T_END:
        printf("end\n");
        break;
    case T_WHILE:
        printf("while\n");
        break;
    case T_DO:
        printf("do\n");
        break;
    case T_INT:
        printf("常量{%d}\n", word->lexme.lexme_num);
        break;
    case T_LT:
        printf("<\n");
        break;
    case T_LE:
        printf("<=\n");
        break;
    case T_NE:
        printf("<>\n");
        break;
    case T_GT:
        printf(">\n");
        break;
    case T_GE:
        printf(">=\n");
        break;
    case T_N_LINE:
        printf("//\n");
        break;
    case T_N_BEGIN:
        printf("/*\n");
        break;
    case T_N_END:
        printf("*/\n");
        break;
    case T_CMP0:
        printf("==\n");
        break;
    case T_ADD:
        printf("+\n");
        break;
    case T_SUB:
        printf("-\n");
        break;
    case T_MUL:
        printf("*\n");
        break;
    case T_DIV:
        printf("/\n");
        break;
    case T_CUT:
        printf(";\n");
        break;
    case T_POINT:
        printf(",\n");
        break;
    case T_CUT_LEFT:
        printf("(\n");
        break;
    case T_CUT_RIGHT:
        printf(")\n");
        break;
    default:
        printf("error!\n");
        break;
    }
}

void show_asm(Link* asm_link)
{
    LinkNode* p = asm_link->head;
    Asm* asm_data;
    for (int i = 0; i < asm_link->len; i++)
    {
        printf("%2d\t", i+1);
        asm_data = (Asm *)p->data;
        if (asm_data->type == T_ASM_JMP)
        {
            printf("jMP\t %d\n", asm_data->num);
        }
        else if (asm_data->type == T_ASM_MOV_REG_NUM) // MOV R2,addr
        {
            printf("MOV\t %s    %d\n", R[asm_data->op%30], asm_data->num);
        }
        else if (asm_data->type == T_ASM_MOV_REG_MEM) // MOV R1,(R2)
        {
            printf("MOV\t %s  (%s)\n", R[asm_data->op%30], R[asm_data->op_ed%30]);
        }
        else if (asm_data->type == T_ASM_MOV_REG_REG) // MOV R5,R1
        {
            printf("MOV\t %s  %s  %d\n", R[asm_data->op%30], R[asm_data->op_ed%30], asm_data->num);
        }
        else if (asm_data->type == T_ASM_MOV_MEM_REG) // MOV (R2),R1
        {
            printf("MOV\t(%s)  %s\n", R[asm_data->op%30], R[asm_data->op_ed%30]);
        }
        else if (asm_data->type == T_ASM_ADD)
        {
            printf("ADD\t %s   %s\n", R[asm_data->op%30], R[asm_data->op_ed%30]);
        }
        else if (asm_data->type == T_ASM_SUB)
        {
            printf("SUB\t %s   %s\n", R[asm_data->op%30], R[asm_data->op_ed%30]);
        }
        else if (asm_data->type == T_ASM_CMP)
        {
            printf("CMP\t %s   %s\n", R[asm_data->op%30], R[asm_data->op_ed%30]);
        }
        else if (asm_data->type == T_ASM_NB) // 大于等于转移
        {
            printf("NE\t %d\n", asm_data->num);
        }
        else if (asm_data->type == T_ASM_BE) // 小于等于转移
        {
            printf("BE\t %d\n", asm_data->num); 
        }
        else if (asm_data->type == T_ASM_E) // 等于转移
        {
            printf("E\t %d\n", asm_data->num); 
        }
        else if (asm_data->type == T_ASM_JG) // 大于转移
        {
            printf("JG\t %d\n", asm_data->num);
        }
        else if (asm_data->type == T_ASM_JB) // 小于转移
        {
            printf("JB\t %d\n", asm_data->num);
        }
        else if (asm_data->type == T_ASM_NE) // 不等于转移
        {
            printf("NE\t %d\n", asm_data->num);
        }
        p = p->next;
    }
    
}