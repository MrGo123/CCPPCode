#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include "word.h"

// �﷨����
int grammar_control(Link* link, int level);
// �ж�����Ƿ�Ϸ�
int legitimate_statement(Link* sentence);
// �жϱ��ʽ�Ƿ�Ϸ�
int legitimate_expression(Link* link);

#endif