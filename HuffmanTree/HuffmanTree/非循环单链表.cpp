#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;


//����ĵ�һ��Ԫ���±���1
template <typename elemtype>
class linklist{
public:
    class linknode{
    public:
        elemtype data;//�ڵ��������
		int freq;
        linknode *next;//ָ����һ��ָ�����͵�ָ����
    };
    typedef linknode* nodepointer;

    //��ѭ������������
    void clear();

    //ɾ����ѭ����������������Ϊe�ĵ�һ���ڵ�
    bool delete_elem(elemtype e);


    //ȡ��ѭ���������е�i���ڵ��ֵ
    void get_elem(int i,elemtype &value,int &frequency);

    //ȡ��һ���ڵ��ָ��
    //nodepointer get_head();


    //�ڵ�i�����֮ǰ����һ��������Ϊe�Ľ��
    bool insert(int i,elemtype e,int frequency);

    //�жϷ�ѭ���������Ƿ�Ϊ��
    bool is_empty();

    //Ĭ�Ϲ��캯��
    linklist();
    //��ѭ�����������������
    ~linklist();
    //������ʼ�����캯��
    linklist(linklist &other);

	//��ȡ������
	int get_length();
	

	//�����������
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
    nodepointer head;//ͷָ��

};

//��ȡ������
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
    head = NULL;//Ĭ�ϳ�ʼ�����캯����Ҫ����ͷָ��Ϊ��
}

template <typename elemtype>
linklist<elemtype>::~linklist(){
    clear();
}

//��ѭ��������Ŀ�����ʼ�����캯��
template <typename elemtype>
linklist<elemtype>::linklist(linklist<elemtype> &other){
    nodepointer p;//Ԥָ��ǰ��ѭ��������ǰ����ָ��
    nodepointer op = other.head;
    nodepointer s;//Ԥָ���½ڵ��ָ��
    head = p = NULL;//ָ�붼���ܳ�ʼ��Ϊ�գ�׼�����ܳ�ʼ��

    //��ֵother���ÿ���ڵ�
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

        p = s;//�γ�����
        op = op->next;//other����ָ����һ�����
    }
    if (head){
        p->next = NULL;//�����ĩβ�ÿ�
    }
}



//�������ÿ�
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

//ɾ����ѭ��������������Ϊe�ĵ�һ�����
template <typename elemtype>
bool linklist<elemtype>::delete_elem(elemtype e){
    nodepointer r,p;
    r = NULL;
    p = head;
    while(p && !(p->data == e)){//��p->data����e��ǰ�����
        r = p;
        p = p->next;
    }
    if (p==NULL){//�ҵ�����βҲû���ҵ����ϵ�Ԫ��
        return false;
    }
    if(r == NULL){
        head = head->next;
    }else{
        r->next = p->next;//ɾ�����
    }
    free(p);
    return true;
}



//ȡ��ѭ������ĵ�i�����
template <typename elemtype>
void linklist<elemtype>::get_elem(int i,elemtype &value,int &frequency){//�����в��ܺ�����
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

//ȡ��ѭ��������ͷָ��head
/*
template <typename elemtype>//ע�������������ĸ�ʽ
typename linklist<elemtype>::nodepointer linklist<elemtype>::get_head(){
    return head;
}*/



//������
template <typename elemtype>
bool linklist<elemtype>::insert(int i ,elemtype e,int frequency){
    int j = 1;
    nodepointer p = head;
    nodepointer s;//���������ָ��
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

//�ж������Ƿ�Ϊ��
template <typename elemtype>
bool linklist<elemtype>::is_empty(){
    return head?false:true;
}



/*���Գ���
int main(void){
	linklist<int> t1;
	cout << "....." << endl;
    if(t1.is_empty()){
        cout<<"��"<<endl;
    }
    else{
        cout<<"�ǿ�"<<endl;
    }

    for(int i = 1;i<=10;i++){
        if(t1.insert(i,i)){
            cout<<"�ɹ�"<<endl;
        }
        else{
            cout<<"ʧ��"<<endl;
        }
    }

    t1.insert(11,1);

    cout<<"������ʾ����:"<<endl;

    cout<<t1<<endl;

    cout<<"���ڵ�����Ϊ:"<<endl;
    cout<<t1<<endl;

    return 0;
}

*/
