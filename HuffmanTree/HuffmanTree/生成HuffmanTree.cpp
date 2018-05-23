#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string.h>
#include "һЩ�궨��.h"
#include "��ѭ��������.cpp"
#include "readFileFreq.c"
#include "������.cpp"

using namespace std;


//����Huffman���ĺ�������
void CreateHuffmanTree(linklist<char> &templist, Treeleaf<char>::NodePointer &tl);

//���ڽ����뺯������
void InsertNewToList(linklist<char> &templist, Treeleaf<char>::NodePointer tl);

//�������ɵ���
void TestTree(Treeleaf<char>::NodePointer tl);

//ɾ��HuffmanTree���ĺ���
void ReleaseHuffmanTree(Treeleaf<char>::NodePointer root);

//��ȡ�ļ�
bool ReadFile(char *filename, char *file);

//ת��ΪHuffman��
void Encoder(char *encode, Treeleaf<char>::NodePointer root, char *filename, char *file);

//����
void Decoder(char *code, Treeleaf<char>::NodePointer root, char *result);


int main(void)
{
	//ʹ��readFileFreq.c��׼��
	char fileName[128] = "C://Users//pc//Desktop//����Ӣ��.txt";		//Ҫ�򿪵��ļ�

	CharFreq freq[2 * NUMLETTER];
	for (int i = 0; i < 2 * NUMLETTER; i++)
	{
		freq[i].freq = 0;
	}
	//׼�����

	int count = countFrequency(fileName, freq);

	printFrequency(freq, count);
	sortFrequency(freq, count);
	cout << "�����:" << endl;
	cout << "-----------------------------" << endl;
	printFrequency(freq, count);

	linklist<char> templist;
	for (int i = 1; i <= count; i++)
	{
		templist.insert(i, freq[i - 1].value, freq[i - 1].freq);
	}
	cout << "�����е�������:" << endl << templist << endl;

	cout << "������Ϊ:" << templist.get_length() << endl;

	cout << "=======================================" << endl;

	//�����ļ�ת������������


	Treeleaf<char>::NodePointer tl = new Treeleaf<char>;

	CreateHuffmanTree(templist, tl);
	cout << "��������Huffman������:" << endl;

	TestTree(tl);

	char readFileTest[1280];
	
	ReadFile(fileName, readFileTest);
	cout << "�ļ�������:" << readFileTest << endl;			//readFileTest�к����ļ�������

	char encode[1280];
	
	Encoder(encode, tl, fileName,readFileTest);
	cout << "Huffman����Ϊ:" << encode << endl;


	char result[1280];
	Decoder(encode, tl, result);
	cout << "�ļ�ԭ������Ϊ:" << result << endl;

	ReleaseHuffmanTree(tl);									//���������ͷ�֮ǰ����Ŀռ�



	char HuffmanTargetFile[128] = "C://Users//pc//Desktop//���������ļ�.txt";
	FILE *fp = fopen(HuffmanTargetFile, "w");
	fputs(encode, fp);
	fclose(fp);
	cout << "Huffman������д��ɹ�" << endl;
	return 0;
}


//��ʼ����Huffman��
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
	Treeleaf<char>::NodePointer pptr = new Treeleaf<char>;				//Ԥָ��p_temp_sum��ָ��
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

			templist.delete_elem(value);				//ɾ�������е�һ��ֵΪvalue�Ľ��

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
	t = pptr;			//Huffman���ĸ��ڵ㣬�����ô���ȥ
}



//�������������������������һ�����Եĺ���
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


//ɾ��HuffmanTree���ĺ���
void ReleaseHuffmanTree(Treeleaf<char>::NodePointer root)
{
	Treeleaf<char>::NodePointer p = root;
	if (p)
	{
		ReleaseHuffmanTree(p->left);
		ReleaseHuffmanTree(p->right);
		cout << "ɾ�����..." << endl;
		delete p;
	}
}




//��ȡ�ļ�
/*����˵��:
��һ���������������ļ�����
�ڶ������������洢�ļ��е����ݣ������������ı���
*/
bool ReadFile(char *filename, char *file)
{
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		cout << "�ļ���ȡ����ʧ��." << endl;
		return false;
	}

	char *filePtr = file;
	while (!feof(fptr))
	{
		*filePtr++ = fgetc(fptr);
	}
	*filePtr = '\0';			//��β
	fclose(fptr);				//�ر��ļ�
	return true;
}



//����˵����char *encode �����洢Huffman����
//�ڶ����������Ѿ������õ�Huffman��
//�����ĸ�������Ҫ�ǵ���ReadFileʹ��
void Encoder(char *encode, Treeleaf<char>::NodePointer root, char *filename, char *file)
{
	char *encodePtr = encode;
	Treeleaf<char>::NodePointer p = root;
	ReadFile(filename, file);
	char *filePtr = file;
	for (; *filePtr; filePtr++)
	{
		p = root;								//ÿ�β�����ϣ������ĸ��ڵ㿪ʼ
		char temp[1280];						//������ʱ�洢ÿһ���ַ���·�����룬����Ƶ�
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
			*tempPtr = '\0';		//��β
		}
		else
		{
			*tempPtr++ = '1';
			*tempPtr = '\0';		//��β
		}


		cout << *filePtr << ":" << temp << endl;
		for (tempPtr = temp; *tempPtr; tempPtr++)
		{
			*encodePtr++ = *tempPtr;
		}
		cout << "���һ��" << endl;
	}
	*encodePtr = '\0';				//��β
}



//����
/*
*����˵��:
*��һ��������Huffman��
*�ڶ��������ǹ�����Huffman���ĸ�ָ��
*���������������ڴ洢�����
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
			p = p->left;							//���»�
			if (p->ltag == -1)
			{
				*resultPtr++ = p->value;			//���������һ������ֵҪ��result�ַ�����
				p = root;							//�ص����ڵ㣬��ʼ�´β���
			}
		}
		if (*codePtr == '1')
		{
			p = p->right;
			*resultPtr++ = p->value;
			p = root;								//�ص����ڵ㣬��ʼ�´β���
		}
	}
	*resultPtr = '\0';
}


