/*
Programmer: Wenxiu Ye
Data: 5/13/2015
Name of the file: word_count.h
Bytecount: 454 bytes
*/
struct LocationInfo;
struct Node;
int getLen(char str[]);
struct Node *add(struct Node *list, char *word, int lineNum, int posNum);
struct LocationInfo *Loc(struct LocationInfo *list, int lineNum, int posNum);
int duplicate(struct Node list, char *word);
void putFile(struct Node *list, FILE *f);
void freeM(struct Node *list);
void print(struct Node *list);