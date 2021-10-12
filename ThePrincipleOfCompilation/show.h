#ifndef _SHOW_H_
#define _SHOW_H_

#include <stdio.h>

#include "link.h"
#include "id_table.h"
#include "word.h"
#include "semantics.h"

// 词法分析结果显示
void show_LexicalAnalysis(Link *link);



// 语义分析结果显示
void show_asm(Link* asm_link);

#endif