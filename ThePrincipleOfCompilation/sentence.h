#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include "word.h"

// 语法分析
int grammar_control(Link* link, int level);
// 判断语句是否合法
int legitimate_statement(Link* sentence);
// 判断表达式是否合法
int legitimate_expression(Link* link);

#endif