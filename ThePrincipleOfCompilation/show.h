#ifndef _SHOW_H_
#define _SHOW_H_

#include <stdio.h>

#include "link.h"
#include "id_table.h"
#include "word.h"
#include "semantics.h"

// �ʷ����������ʾ
void show_LexicalAnalysis(Link *link);



// ������������ʾ
void show_asm(Link* asm_link);

#endif