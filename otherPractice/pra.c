#include <stdio.h>
#include <stdlib.h>

// 字符串反转函数
void reverse(char* p1, char* p2) {
    if(p1 == NULL || p2 == NULL)
        return;
    while (p1 < p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
        p1++;p2--;
    }
}

int main(){
    char s[50];
    scanf("%[^\n]",s);// \n作为字符串输入的结束符
    printf("%s\n",s);

    char* p = s;

    
    while(*p!='\0'){
          printf("%c",*p);
    }

    system("pause");
    return 0;
}

