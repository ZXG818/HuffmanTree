#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstdio>
#include <assert.h>
using namespace std;

template <typename elemtype>
class Treeleaf			//Huffman���Ĵ�����ƽʱ�Ĳ�һ��������ֻҪ����Ҷ�Ӿͺ�
{
public:
	elemtype value;
	int freq;
	Treeleaf *left;
	Treeleaf *right;
	int ltag;			//�������ֵ
	int rtag;			//�ұ�����ֵ

	typedef Treeleaf* NodePointer;

	Treeleaf();
};

//���ع��캯��
template <typename elemtype>
Treeleaf<elemtype>::Treeleaf()
{
	left = NULL;
	right = NULL;
	value = '*';
	freq = 0;
	ltag = -1;			//�������Ĭ��Ϊ-1
	rtag = -1;			//�ұ�����Ĭ��Ϊ-1
}

