#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include "一些宏定义.h"
#include "非循环单链表.cpp"
#include "readFileFreq.c"
#include "二叉树.cpp"

using namespace std;


//创建Huffman树的函数声明
void CreateHuffmanTree(linklist<char> &templist, Treeleaf<char>::NodePointer &tl);

//树内结点插入函数声明
void InsertNewToList(linklist<char> &templist, Treeleaf<char>::NodePointer tl);

//测试生成的树
void TestTree(Treeleaf<char>::NodePointer tl);

//删除HuffmanTree结点的函数
void ReleaseHuffmanTree(Treeleaf<char>::NodePointer root);

//读取文件
bool ReadFile(char *filename, char *file);

//转化为Huffman码
void Encoder(char *encode, Treeleaf<char>::NodePointer root, char *filename, char *file);

//解码
void Decoder(char *code, Treeleaf<char>::NodePointer root, char *result);


int main(void)
{
	//使用readFileFreq.c的准备
	char fileName[128] = "C://Users//pc//Desktop//测试英文.txt";		//要打开的文件

	CharFreq freq[2 * NUMLETTER];
	for (int i = 0; i < 2 * NUMLETTER; i++)
	{
		freq[i].freq = 0;
	}
	//准备完毕

	int count = countFrequency(fileName, freq);

	printFrequency(freq, count);
	sortFrequency(freq, count);
	cout << "排序后:" << endl;
	cout << "-----------------------------" << endl;
	printFrequency(freq, count);

	linklist<char> templist;
	for (int i = 1; i <= count; i++)
	{
		templist.insert(i, freq[i - 1].value, freq[i - 1].freq);
	}
	cout << "链表中的内容是:" << endl << templist << endl;

	cout << "链表长度为:" << templist.get_length() << endl;

	cout << "=======================================" << endl;

	//以上文件转化链表测试完毕


	Treeleaf<char>::NodePointer tl = new Treeleaf<char>;

	CreateHuffmanTree(templist, tl);
	cout << "测试生成Huffman树部分:" << endl;

	TestTree(tl);

	char readFileTest[1280];
	
	ReadFile(fileName, readFileTest);
	cout << "文件内容是:" << readFileTest << endl;			//readFileTest中含有文件的内容

	char encode[1280];
	
	Encoder(encode, tl, fileName,readFileTest);
	cout << "Huffman编码为:" << encode << endl;


	char result[1280];
	Decoder(encode, tl, result);
	cout << "文件原先内容为:" << result << endl;

	ReleaseHuffmanTree(tl);									//销毁树，释放之前申请的空间



	char HuffmanTargetFile[128] = "C://Users//pc//Desktop//哈夫曼码文件.txt";
	FILE *fp = fopen(HuffmanTargetFile, "w");
	fputs(encode, fp);
	fclose(fp);
	cout << "Huffman树编码写入成功" << endl;
	return 0;
}


//开始创建Huffman树
void CreateHuffmanTree(linklist<char> &templist, Treeleaf<char>::NodePointer &t)
{
	char value;
	int freq;


	Treeleaf<char>::NodePointer p1 = new Treeleaf<char>;
	Treeleaf<char>::NodePointer p2 = new Treeleaf<char>;
	templist.get_elem(1, value, freq);
	p1->value = value;
	p1->freq = freq;

	templist.delete_elem(value);

	templist.get_elem(1, value, freq);

	p2->value = value;
	p2->freq = freq;

	templist.delete_elem(value);

	Treeleaf<char>::NodePointer p_sum = new Treeleaf<char>;
	p_sum->freq = p1->freq + p2->freq;

	p_sum->left = p1;
	p_sum->ltag = 0;
	p_sum->right = p2;
	p_sum->rtag = 1;



	int cnt = 0;
	Treeleaf<char>::NodePointer pptr = new Treeleaf<char>;				//预指向p_temp_sum的指针
	while (!templist.is_empty())
	{
		cnt++;

		Treeleaf<char>::NodePointer p_temp = new Treeleaf<char>;
		Treeleaf<char>::NodePointer p_temp_sum = new Treeleaf<char>;
		if (cnt == 1)
		{
			templist.get_elem(1, value, freq);
			p_temp->value = value;
			p_temp->freq = freq;

			templist.delete_elem(value);				//删除链表中第一个值为value的结点

			p_temp_sum->freq = p_sum->freq + p_temp->freq;
			p_temp_sum->left = p_sum;
			p_temp_sum->ltag = 0;
			p_temp_sum->right = p_temp;
			p_temp_sum->rtag = 1;

			pptr = p_temp_sum;
		}
		else
		{
			templist.get_elem(1, value, freq);
			p_temp->value = value;
			p_temp->freq = freq;
			templist.delete_elem(value);

			p_temp_sum->freq = pptr->freq + p_temp->freq;
			p_temp_sum->left = pptr;
			p_temp_sum->ltag = 0;
			p_temp_sum->right = p_temp;
			p_temp_sum->rtag = 1;


			pptr = p_temp_sum;
		}

	}
	t = pptr;			//Huffman树的根节点，传引用传过去
}



//测试生成树的中序遍历，这是一个测试的函数
void TestTree(Treeleaf<char>::NodePointer root)
{
	if (root)
	{
		TestTree(root->left);
		cout << root->value << "\t" << root->freq << endl;
		cout << root->ltag << "\t" << root->rtag << endl << endl << endl;
		TestTree(root->right);
	}
}


//删除HuffmanTree结点的函数
void ReleaseHuffmanTree(Treeleaf<char>::NodePointer root)
{
	Treeleaf<char>::NodePointer p = root;
	if (p)
	{
		ReleaseHuffmanTree(p->left);
		ReleaseHuffmanTree(p->right);
		cout << "删除结点..." << endl;
		delete p;
	}
}




//读取文件
/*参数说明:
第一个参数用来传进文件名称
第二个参数用来存储文件中的内容，用来接下来的编码
*/
bool ReadFile(char *filename, char *file)
{
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		cout << "文件读取内容失败." << endl;
		return false;
	}

	char *filePtr = file;
	while (!feof(fptr))
	{
		*filePtr++ = fgetc(fptr);
	}
	*filePtr = '\0';			//结尾
	fclose(fptr);				//关闭文件
	return true;
}



//参数说明：char *encode 用来存储Huffman编码
//第二个参数是已经创建好的Huffman树
//第三四个参数主要是调用ReadFile使用
void Encoder(char *encode, Treeleaf<char>::NodePointer root, char *filename, char *file)
{
	char *encodePtr = encode;
	Treeleaf<char>::NodePointer p = root;
	ReadFile(filename, file);
	char *filePtr = file;
	for (; *filePtr; filePtr++)
	{
		p = root;								//每次查找完毕，从树的根节点开始
		char temp[1280];						//用于临时存储每一个字符的路径代码，最后复制到
		char *tempPtr = temp;
		while (p->right->value != *filePtr && p->left->ltag != -1)
		{
			//cout << p->right->value << endl;
			p = p->left;
			*tempPtr++ = '0';
			
		}
		if (p->left->ltag == -1 && p->left->value == *filePtr)
		{
			*tempPtr++ = '0';
			*tempPtr = '\0';		//结尾
		}
		else
		{
			*tempPtr++ = '1';
			*tempPtr = '\0';		//结尾
		}


		cout << *filePtr << ":" << temp << endl;
		for (tempPtr = temp; *tempPtr; tempPtr++)
		{
			*encodePtr++ = *tempPtr;
		}
		cout << "完成一轮" << endl;
	}
	*encodePtr = '\0';				//结尾
}



//解码
/*
*参数说明:
*第一个参数是Huffman码
*第二个参数是构建的Huffman树的根指针
*第三个参数是用于存储结果的
*/
void Decoder(char *code, Treeleaf<char>::NodePointer root, char *result)
{
	Treeleaf<char>::NodePointer p = root;

	char *resultPtr = result;

	char *codePtr = code;
	for (; *codePtr; codePtr++)
	{
		if (*codePtr == '0')
		{
			p = p->left;							//往下滑
			if (p->ltag == -1)
			{
				*resultPtr++ = p->value;			//中序遍历第一个结点的值要给result字符数组
				p = root;							//回到根节点，开始下次查找
			}
		}
		if (*codePtr == '1')
		{
			p = p->right;
			*resultPtr++ = p->value;
			p = root;								//回到根节点，开始下次查找
		}
	}
	*resultPtr = '\0';
}


