 /*
Programmer: Wenxiu Ye
Data: 5/13/2015
Name of the file: word_count.c
Bytecount: 2,833 bytes
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct LocationInfo
{
	int line;
	int pos;
	struct LocationInfo *next;
}Loc;
typedef struct Node
{
	char *word;
	int count;
	struct LocationInfo *info;
	struct Node *next;
} Node;

int getLen(char str[])
{
    int count = 0;
        while(str[count] != '\0')
                count++;
        return count;
}
int duplicate(Node *list, char *word)
{
	if (list == NULL)
		return -1;
	Node *temp = list;
	while(temp != NULL)
	{
		if (strcmp(word, temp->word) == 0)
			return 0;
		temp = temp->next;
	}
	return -1;
}
Loc *addLoc(Loc *list, int lineNum, int posNum)
{
	Loc *newPos = (Loc *) malloc(sizeof(Loc));
	newPos->line = lineNum;
	newPos->pos = posNum;
	newPos->next = NULL;
	if(list == NULL)
		return newPos;
	Loc *temp = list;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newPos;
	return list;
}
Node *add(Node *list, char *word, int lineNum, int posNum)
{
	Node *node = (Node *) malloc(sizeof(Node));
	node->word  = (char *) malloc(strlen(word) + 1);
	strcpy(node->word, word);

	node->count = 1;
	node->info = NULL;
	node->info = addLoc(node->info, lineNum, posNum);
	node->next = NULL;

	Node *last = list;
	if(list == NULL)
		return node;
	else
	{
		int dup = duplicate(list, word);
		if(dup != 0){
			while(last->next != NULL)
				last = last->next;
			last->next = node;
		}
		else
		{
			Node *temp = list;
			while(temp != NULL)
			{
				if (strcmp(word, temp->word) == 0)
				{
					temp->count++;
					temp->info = addLoc(temp->info, lineNum, posNum);
				}
				temp = temp->next;
			}
		}
	}
	return list;
}
void putFile(Node *list, FILE *f)
{
	if (list == NULL)
		return;
	Node *temp = list;
	Loc *loc;
	while(temp != NULL)
	{
		fputs(temp->word, f);
  		fputs(",", f);
  		fprintf(f, "%d, ", temp->count);

		loc = temp->info;
		int count = 0;
		while(loc != NULL)
		{
			if(count != 0)
				fputs(",", f);
			fprintf(f, "(%d,", loc->line);
			fprintf(f, " %d)", loc->pos);
			loc = loc->next;
			count = 1;
		}
		fputs(" \n", f);
		temp = temp->next;
	}
}
void freeM(Node *list)
{
	Node *temp = list;
	while(temp != NULL)
	{
		free(temp->word);
		Loc *temp1 = temp->info;
		while(temp1 != NULL)
		{
			Loc *temp2 = temp1->next;
			free(temp1);
			temp1 = temp2;
		}
		temp = temp->next;
	}
}
void print(Node *list)
{
	if (list == NULL)
		return;
	Node *temp = list;
	Loc *loc;
	int num = 1;
	while(temp != NULL)
	{
		printf("Word %d : %s, count:%d, ", num, temp->word, temp->count);
		loc = temp->info;
		int count = 0;
		while(loc != NULL)
		{
			if(count != 0)
				printf(",");
			printf("(%d, %d)",loc->line, loc->pos );
			loc = loc->next;
			count = 1;
		}
		printf("\n");
		temp = temp->next;
		num++;
	}
	printf("\n");
}