#include <iostream>
#include <queue>

using namespace std;

int main(){
    // 1.定义一个队列
    queue<int> que;
    
    // 2.在队列末尾中加入元素
    cout<<"1.push into queue"<<endl;
    for(int i=0;i<5;i++){
        que.push(i);
    }
    
    // 3.返回第一个元素
    cout<<"2.first element-front()="<<que.front()<<endl;

    // 4.返回最后一个元素
    cout<<"3.last element-back()="<<que.back()<<endl;
    
    // 5.返回队列元素个数
    cout<<"4.size()="<<que.size()<<endl;

    // 6.判空，空为true
    if(que.empty()){
        cout<<"5.queue empty()=true"<<endl;
    }else{
        cout<<"5.queue empty()=false"<<endl;
    }

    // 7.遍历队列，弹出元素pop()
    cout<<"6.out queue"<<endl;
    while(!que.empty()){
        cout<<"    front()="<<que.front()<<endl;
        que.pop();
    }

    system("pause");
    return 0;
}