/*
Programmer: Wenxiu Ye
Data: 5/20/2015
Name of the file: test_word_count.c
Bytecount: 1,187 bytes
*/

#include <stdio.h>
#include "word_count.h"
#include <stdlib.h>
#define MAX 100

int main(int argc, char *argv[])
{
	while(1)
	{
		if(argc != 3)
		{
			printf("Wrong command, try again \n");
			break;
		}
		else if (argc == 3 && fopen(argv[1], "r") != NULL  && fopen(argv[2], "w") != NULL)
		{
			FILE *in;
			FILE *out;
			in = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			struct Node *wordCount = NULL;
			char line[MAX];
			char word[MAX];
			int lineNum = 1 ;				
			int pos;
			int len;
			while (fgets(line, MAX-1, in) != NULL)
			{
				pos = 1;
				len = 0;
				printf("line %d : %s", lineNum, line);
				while(sscanf(line, "%s ", word) == 1)
				{
					int count;
					len += getLen(word);
					len+=1; 
					wordCount = add(wordCount, word, lineNum, pos);
					for(count = 0; count < len; count++)
						line[count] = ' ';
					pos++;
				}
				lineNum++;
			}
			printf("\n");
			print(wordCount);
			putFile(wordCount, out);
			fclose(in);
			fclose(out);
			freeM(wordCount);
			break;
		}
		else
		{
			printf("Wrong File Name, try again \n");
			break;
		}
	}
}