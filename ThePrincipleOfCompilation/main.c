#include <stdio.h>
#include <stdlib.h>

#include "link.h"
#include "word.h"
#include "sentence.h"
#include "semantics.h"
#include "id_table.h"
#include "show.h"


// 文件获取
char *readfile(char *path) {
	FILE *pfile;
	char *data;
	int len;
	pfile = fopen(path, "rb");
	if (pfile == NULL) {
		printf("file link is empty!");
		return NULL;
	}
	// 指针跳至文件末尾，计算文件大小
	fseek(pfile, 0, SEEK_END);
	len = ftell(pfile);
	// 设置存储空间，指针返回文件开头
	data = (char *)malloc((len + 1) * sizeof(char));
	rewind(pfile);
	// 读取文件
	len = fread(data, 1, len, pfile);
	data[len] = '\0';

	fclose(pfile);
	return data;
}

// 词法分析函数
Link *LexicalAnalysis(char *text, Link *id_list) {
	Dual *id_node;
	LinkNode *p;
	int error_word = 0;
	Link *link;
	link = link_create();
	if (link == NULL) {
		printf("Set up link failed!\n");
		return NULL;
	}
	error_word = word_control(link, text);
	if (error_word == 0) {
		printf("\n\nProgram(Lexical Analysis) Successful!\n");
		p = link->head;
		for (int i = 0; i < link->len; i++) {
			id_node = (Dual *)p->data;
			if (id_node->dual_type == T_ID) {
				add_id_addr(id_list, id_node->lexme.lexme_text);
			}
			p = p->next;
		}
		return link;
	} else {
		printf("\n\nProgram(Lexical Analysis)\nerror word: %d\n", error_word);
		return NULL;
	}
}

// 语法分析函数
Link *GrammarAnalysis(Link *link) {
	int err_count = 0;

	err_count = grammar_control(link, 0);
	if (err_count == 0) {
		printf("\n\nProgram(Grammar Analysis) Successful!\n");
		return link;
	} else {
		printf("\n\nProgram(Grammar Analysis)\nerror count: %d\n", err_count);
		return NULL;
	}
}

// 语义分析函数
Link *SemanticAnalysis(Link *link, Link *asm_link, Link *id_table) {
	asm_link = turn_to_asm(link, asm_link, id_table);
	// printf("asmlink:%d\n", asm_link->len);
	return asm_link;
}

int main(int argc, char *argv[]) {

	// fplink 后期可能换为输入路径
	char fplink[150] = "testfile\\code.txt";
	char *text;

	Link *link;
	Link *id_list = link_create();
	Link *asm_list = link_create();

	text = readfile(fplink);

	link = LexicalAnalysis(text, id_list);
	// printf("id:%d\n", id_list->len);

	show_LexicalAnalysis(link);

	link = GrammarAnalysis(link);

	asm_list = SemanticAnalysis(link, asm_list, id_list);
	show_asm(asm_list);
	return 0;
}
