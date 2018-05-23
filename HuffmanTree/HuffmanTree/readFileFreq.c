#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "一些宏定义.h"


typedef struct
{
	char value;		//字符
	int freq;		//字符出现的频率
}CharFreq;			//字符出现的频率的结构体

int countFrequency(char *filename, CharFreq *freq)
{
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("文件打开错误\n");
		return 0;
	}

	
	CharFreq temp[2*NUMLETTER];
	for (int i = 0; i < 2*NUMLETTER; i++)
	{
		temp[i].freq = 0;
	}
	while (!feof(fptr))
	{
		int onechar = fgetc(fptr);
		if (onechar != EOF)
		{
			temp[onechar].value = (char)onechar;
			temp[onechar].freq++;
		}
	}
	fclose(fptr);			//关闭文件

	int count = 0;
	for (int i = 0; i < 2*NUMLETTER; i++)
	{
		if (temp[i].freq && temp[i].freq > 0)
		{
			freq[count].value = temp[i].value;
			freq[count++].freq = temp[i].freq;
		}
	}

	return count;
}

void printFrequency(CharFreq *freq,int count)
{
	int ind;
	for (ind = 0; ind < count; ind++)
	{
		if (freq[ind].value == ' ')
		{
			printf("空格\t%d\n", freq[ind].freq);
		}
		else if (freq[ind].value == '\n')
		{
			printf("换行\t%d\n", freq[ind].freq);
		}
		else
		{
			printf("%c\t%d\n", freq[ind].value, freq[ind].freq);
		}
	}
	printf("-----------------------------\n");
}

//冒泡排序
void sortFrequency(CharFreq *freq,int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (freq[j].freq > freq[j+1].freq)
			{
				CharFreq temp = freq[j];
				freq[j] = freq[j+1];
				freq[j+1] = temp;
			}
		}
	}
}


/*
测试程序
int main(int argc, char *argv[])
{
	CharFreq freq[2*NUMLETTER];
	for (int i = 0; i < 2*NUMLETTER; i++)
	{
		freq[i].freq = 0;
	}


	char *filename = "C://Users//pc//Desktop//测试英文.txt";
	int count = countFrequency(filename, freq);
	printFrequency(freq,count);
	sortFrequency(freq,count);
	printFrequency(freq,count);
	printf("%d\n", count);
}
*/