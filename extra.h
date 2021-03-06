#ifndef _EXTRA_H_
#define _EXTRA_H_

#define MAXCAPACITY 200000000

//栈
typedef struct search_stack {
    int top;
    int data[MAXCAPACITY];
} S_Stack;
void initStack(S_Stack** S);
void push(int d, S_Stack* S);
int pop(S_Stack* S);
void deleteStack(S_Stack* S);
int isStackEmpty(S_Stack* S);
int isStackFull(S_Stack* S);

//队列
typedef struct search_queue {
    int front, rear;
    int data[MAXCAPACITY];
} S_Queue;
void initQueue(S_Queue** Q);
void enQueue(int d, S_Queue* S);
int deQueue(S_Queue* S);
void deleteQueue(S_Queue* Q);
int isQueueEmpty(S_Queue* Q);
int isQueueFull(S_Queue* Q);

int extra_strcmp(char* a, char* b);               //字符串比较
int extra_itoa(int x, char* str);                 //把一个整数写入字符串中，返回写入的长度
int extra_strcpy(char* dest, char* source);       //字符串复制，返回复制的长度
int extra_atoi(char* str);                        //把字符串转换为正整数，返回-1表示数字不合法
int cmp(const void* a, const void* b);            //以arr[0]、arr[1]分别为第一、第二关键词比较
void draw_garlic();                               //Rua!=

#endif
