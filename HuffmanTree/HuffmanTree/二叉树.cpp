#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstdio>
#include <assert.h>
using namespace std;

template <typename elemtype>
class Treeleaf			//Huffman树的创建和平时的不一样，这里只要定义叶子就好
{
public:
	elemtype value;
	int freq;
	Treeleaf *left;
	Treeleaf *right;
	int ltag;			//左边索引值
	int rtag;			//右边索引值

	typedef Treeleaf* NodePointer;

	Treeleaf();
};

//重载构造函数
template <typename elemtype>
Treeleaf<elemtype>::Treeleaf()
{
	left = NULL;
	right = NULL;
	value = '*';
	freq = 0;
	ltag = -1;			//左边索引默认为-1
	rtag = -1;			//右边索引默认为-1
}

