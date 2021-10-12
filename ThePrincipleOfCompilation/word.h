#ifndef _WORK_H_
#define _WORK_H_

#include "link.h"

#define T_ERR 0        // 错误
#define T_ID 1         // 标识符
#define T_EQ 2         // 赋值
#define T_IF 3         // IF
#define T_THEN 4       // THEN
#define T_ELSE 5       // ELSE
#define T_BEGIN 6      // BEGIN
#define T_END 7        // END
#define T_WHILE 8      // WHILE
#define T_DO 9         // DO
#define T_INT 10       // 常数
#define T_LT 11        // 小于
#define T_LE 12        // 小于等于
#define T_NE 13        // 不等于
#define T_GT 14        // 大于
#define T_GE 15        // 大于等于
#define T_N_LINE 16    // 行注释符
#define T_N_BEGIN 17   // 段注释符开始
#define T_N_END 18     // 端注释符结束
#define T_CMP0 19      // 等于
#define T_ADD 20       // 加
#define T_SUB 21       // 减
#define T_MUL 22       // 乘
#define T_DIV 23       // 除
#define T_CUT 24       // 分隔符
#define T_POINT 25     // 逗号
#define T_CUT_LEFT 26  // 左括号
#define T_CUT_RIGHT 27 // 右括号

typedef struct // 单词二元式 用于存储每一个词的类型及其参数的数据结构
{
    int dual_type;
    union // 二元式单词存储内容
    {
        char lexme_text[100];
        int lexme_num;
    } lexme;
    int line;
} Dual;

// 词法分析
int word_control(Link *link, char *text);
// s 为读入 Pascal 程序字符，根据 s 输入进行单词划分，结果存入 word，未进行检错
// 返回读取 s 字符串从开始读到单词结束的长度，word 存储读取 s 字符串返回单词，并末尾填 0
int get_word(char *word, char *s);
// 判断一个二元式链表中是否包含某种类型的二元式
int have_type(Link *sentence, int type);
// 获取输入字符串的换行号，以获取输入程序行数
int get_line_change(char *s, int len);
// 返回两类注释符后注释长度
int to_n_end(char *s, int type);
// 将读入字符串常数化为数值
int char_to_num(char *s);

// 非词法分析使用

// 获取一个字符串的类型
int get_type(char *word);
// 获取二元式链表中的第 i 个元素的类型
int get_type_in_link(Link *link, int i);

#endif
