#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;


//链表的第一个元素下表是1
template <typename elemtype>
class linklist{
public:
    class linknode{
    public:
        elemtype data;//节点的数据域
		int freq;
        linknode *next;//指向下一个指针类型的指针域
    };
    typedef linknode* nodepointer;

    //非循环单链表的清空
    void clear();

    //删除非循环单链表中数据域为e的第一个节点
    bool delete_elem(elemtype e);


    //取非循环单链表中第i个节点的值
    void get_elem(int i,elemtype &value,int &frequency);

    //取第一个节点的指针
    //nodepointer get_head();


    //在第i个结点之前插入一个数据域为e的结点
    bool insert(int i,elemtype e,int frequency);

    //判断非循环单链表是否为空
    bool is_empty();

    //默认构造函数
    linklist();
    //非循环单链表的析构函数
    ~linklist();
    //拷贝初始化构造函数
    linklist(linklist &other);

	//获取链表长度
	int get_length();
	

	//重载输出函数
    template <typename out_put>
    friend ostream& operator<<(ostream& out,linklist<out_put> other){
        nodepointer p = other.head;
        while(p){
			out << p->data << "-->>" << p->freq << endl;
            p = p->next;
        }
        return out;
    }



protected:
    nodepointer head;//头指针

};

//获取链表长度
template <typename elemtype>
int linklist<elemtype>::get_length()
{
	nodepointer p = head;
	int cnt = 0;
	while (p)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}



template <typename elemtype>
linklist<elemtype>::linklist(){
    head = NULL;//默认初始化构造函数就要设置头指针为空
}

template <typename elemtype>
linklist<elemtype>::~linklist(){
    clear();
}

//非循环单链表的拷贝初始化构造函数
template <typename elemtype>
linklist<elemtype>::linklist(linklist<elemtype> &other){
    nodepointer p;//预指向当前非循环单链表当前结点的指针
    nodepointer op = other.head;
    nodepointer s;//预指向新节点的指针
    head = p = NULL;//指针都接受初始化为空，准备接受初始化

    //赋值other里的每个节点
    while(op){
        s = new linknode;
        assert(s!=0);

        s->data = op->data;
		s->freq = op->freq;

        if(!head){
            head = s;
        }else{
            p->next = s;
        }

        p = s;//形成链表
        op = op->next;//other链表指向下一个结点
    }
    if (head){
        p->next = NULL;//链表的末尾置空
    }
}



//单链表置空
template <typename elemtype>
void linklist<elemtype>::clear(){
    nodepointer p,q;
    p = NULL;
    q = head;
    while(q){
        p = q;
        q = q->next;
        delete p;
    }
    head = NULL;
}

//删除非循环链表中数据域为e的第一个结点
template <typename elemtype>
bool linklist<elemtype>::delete_elem(elemtype e){
    nodepointer r,p;
    r = NULL;
    p = head;
    while(p && !(p->data == e)){//找p->data等于e的前驱结点
        r = p;
        p = p->next;
    }
    if (p==NULL){//找到链表尾也没有找到符合的元素
        return false;
    }
    if(r == NULL){
        head = head->next;
    }else{
        r->next = p->next;//删除结点
    }
    free(p);
    return true;
}



//取非循环链表的第i个结点
template <typename elemtype>
void linklist<elemtype>::get_elem(int i,elemtype &value,int &frequency){//链表中不能含有零
    int j = 1;
    nodepointer p;
    p = head;
    while(p && j!=i){
        p = p->next;
        j++;
    }
    if(p == NULL){
		value = p->data;
		frequency = p->freq;
    }else{
        value = p->data;
		frequency = p->freq;
    }
}

//取非循环单链表头指针head
/*
template <typename elemtype>//注意这个函数定义的格式
typename linklist<elemtype>::nodepointer linklist<elemtype>::get_head(){
    return head;
}*/



//插入结点
template <typename elemtype>
bool linklist<elemtype>::insert(int i ,elemtype e,int frequency){
    int j = 1;
    nodepointer p = head;
    nodepointer s;//带插入结点的指针
    if(i==1){
        s = new linknode;
        s->next = head;
        head = s;
        s->data = e;
		s->freq = frequency;
        return true;
    }

    while(p && j<i-1){
        ++j;
        p = p->next;
    }

    if(!p || j>i){
        return false;
    }
    s = new linknode;
    assert(s!=0);
    s->data = e;
	s->freq = frequency;
    if(i==1){
        s->next = head;
        head = s;
    }else{
        s->next = p->next;
        p->next = s;
    }
    return true;
}

//判断链表是否为空
template <typename elemtype>
bool linklist<elemtype>::is_empty(){
    return head?false:true;
}



/*测试程序
int main(void){
	linklist<int> t1;
	cout << "....." << endl;
    if(t1.is_empty()){
        cout<<"空"<<endl;
    }
    else{
        cout<<"非空"<<endl;
    }

    for(int i = 1;i<=10;i++){
        if(t1.insert(i,i)){
            cout<<"成功"<<endl;
        }
        else{
            cout<<"失败"<<endl;
        }
    }

    t1.insert(11,1);

    cout<<"现在显示链表:"<<endl;

    cout<<t1<<endl;

    cout<<"现在的链表为:"<<endl;
    cout<<t1<<endl;

    return 0;
}

*/
