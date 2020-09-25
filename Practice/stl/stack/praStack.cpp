#include <iostream>
#include <stack>

using namespace std;

int main(){

    // 1.定义一个stack 
    stack<int> stk;

    // 2.在栈顶增加元素
    cout<<"1.in stack:"<<endl;
    for(int i=0;i<5;i++){
        stk.push(i);
        cout<<"    push()="<<stk.top()<<endl;
    }

    // 3.栈判空，空为真
    if(stk.empty()==true){
        cout<<"2.empty()=true"<<endl;
    }else{
        cout<<"2.empty()=false"<<endl;
    }
    
    // 4.返回栈顶元素：top()
    cout<<"3.top()="<<stk.top()<<endl;

    // 5.移除栈顶元素
    stk.pop();
    cout<<"4.popped an element"<<endl;
    cout<<"    new top()="<<stk.top()<<endl;

    // 6.栈中元素个数
    cout<<"5.size()="<<stk.size()<<endl;

    // 7.弹出所有元素
    cout<<"6.out stack:"<<endl;
    while(!stk.empty()){
        cout<<"    top()="<<stk.top()<<endl;
        stk.pop();
    }

    system("pause");
    return 0;
}