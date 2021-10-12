#ifndef _WORK_H_
#define _WORK_H_

#include "link.h"

#define T_ERR 0        // ����
#define T_ID 1         // ��ʶ��
#define T_EQ 2         // ��ֵ
#define T_IF 3         // IF
#define T_THEN 4       // THEN
#define T_ELSE 5       // ELSE
#define T_BEGIN 6      // BEGIN
#define T_END 7        // END
#define T_WHILE 8      // WHILE
#define T_DO 9         // DO
#define T_INT 10       // ����
#define T_LT 11        // С��
#define T_LE 12        // С�ڵ���
#define T_NE 13        // ������
#define T_GT 14        // ����
#define T_GE 15        // ���ڵ���
#define T_N_LINE 16    // ��ע�ͷ�
#define T_N_BEGIN 17   // ��ע�ͷ���ʼ
#define T_N_END 18     // ��ע�ͷ�����
#define T_CMP0 19      // ����
#define T_ADD 20       // ��
#define T_SUB 21       // ��
#define T_MUL 22       // ��
#define T_DIV 23       // ��
#define T_CUT 24       // �ָ���
#define T_POINT 25     // ����
#define T_CUT_LEFT 26  // ������
#define T_CUT_RIGHT 27 // ������

typedef struct // ���ʶ�Ԫʽ ���ڴ洢ÿһ���ʵ����ͼ�����������ݽṹ
{
    int dual_type;
    union // ��Ԫʽ���ʴ洢����
    {
        char lexme_text[100];
        int lexme_num;
    } lexme;
    int line;
} Dual;

// �ʷ�����
int word_control(Link *link, char *text);
// s Ϊ���� Pascal �����ַ������� s ������е��ʻ��֣�������� word��δ���м��
// ���ض�ȡ s �ַ����ӿ�ʼ�������ʽ����ĳ��ȣ�word �洢��ȡ s �ַ������ص��ʣ���ĩβ�� 0
int get_word(char *word, char *s);
// �ж�һ����Ԫʽ�������Ƿ����ĳ�����͵Ķ�Ԫʽ
int have_type(Link *sentence, int type);
// ��ȡ�����ַ����Ļ��кţ��Ի�ȡ�����������
int get_line_change(char *s, int len);
// ��������ע�ͷ���ע�ͳ���
int to_n_end(char *s, int type);
// �������ַ���������Ϊ��ֵ
int char_to_num(char *s);

// �Ǵʷ�����ʹ��

// ��ȡһ���ַ���������
int get_type(char *word);
// ��ȡ��Ԫʽ�����еĵ� i ��Ԫ�ص�����
int get_type_in_link(Link *link, int i);

#endif
