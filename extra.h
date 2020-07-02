#ifndef _EXTRA_H_
#define _EXTRA_H_

#define MAXCAPACITY 0x7fffffff


typedef struct path_node
{
    int v;//结点编号
    int path_end;//路径字符数组的末尾指针
}Pnode;

//栈
typedef struct search_stack {
    int top;
    Pnode data[MAXCAPACITY];
} S_Stack;
void initStack(S_Stack** S);
void push(Pnode d, S_Stack* S);
Pnode pop(S_Stack* S);
void deleteStack(S_Stack* S);

//队列
typedef struct search_queue {
    int front, rear;
    Pnode data[MAXCAPACITY];
} S_Queue;
void initQueue(S_Queue** Q);
void enQueue(Pnode d, S_Queue* S);
Pnode deQueue(S_Queue* S);
void deleteQueue(S_Queue* Q);

//十进制数转字符串
void itoa(char* dest, int src);


#endif