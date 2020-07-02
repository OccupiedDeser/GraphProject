#include "extra.h"
#include <stdio.h>
#include <stdlib.h>

void initStack(S_Stack** S_pointer)
{
    *S_pointer = (S_Stack*)malloc(sizeof(S_Stack));
    (*S_pointer)->top = -1;
}

void push(Pnode d, S_Stack* S)
{
    if (!isStackFull(S)) {
        S->top++;
        S->data[S->top] = d;
    } else {
        printf("栈溢出");
    }
}

Pnode pop(S_Stack* S)
{
    if (!isStackEmpty(S)) {
        S->top--;
        return S->data[S->top + 1];
    } else {
        printf("空栈");
        Pnode error = { -1, -1 };
        return error;
    }
}

int isStackEmpty(S_Stack* S)
{
    return S->top == -1;
}

int isStackFull(S_Stack* S)
{
    return S->top == MAXCAPACITY - 1;
}

void deleteStack(S_Stack* S)
{
    free(S);
}

void initQueue(S_Queue** Q_pointer)
{
    *Q_pointer = (S_Queue*)malloc(sizeof(S_Queue));
    (*Q_pointer)->front = (*Q_pointer)->rear = 0;
}

void enQueue(Pnode d, S_Queue* Q)
{
    if (!isQueueFull(Q)) {
        Q->data[Q->rear] = d;
        Q->rear++;
    } else {
        printf("满队队列");
    }
}

Pnode deQueue(S_Queue* Q)
{
    if (!isQueueEmpty(Q)) {
        Q->front++;
        return Q->data[Q->front - 1];
    } else {
        printf("空队列");
        Pnode error = { -1, -1 };
        return error;
    }
}

int isQueueEmpty(S_Queue* Q)
{
    return Q->front == Q->rear;
}

int isQueueFull(S_Queue* Q)
{
    return Q->front == (Q->rear + 1);
}

void deleteQueue(S_Queue* Q)
{
    free(Q);
}

int strcmp(char* a, char* b)
{
    int i, flag = 0;
    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i]) {
            flag = a[i] - b[i];
            break;
        }
    }
    if (a[i] == '\0' || b[i] == '\0') {
        flag = a[i] - b[i];
    }
    return flag;
}

int itoa(int x, char* str)
{
    if (x == 0) {
        str[0] = '0';
        return 1;
    }

    int i = 0, top = -1;
    char _stack[10];
    while (x != 0) {
        top++;
        _stack[top] = x % 10 + '0';
    }
    while (top > -1) {
        str[i] = _stack[top];
        i++;
        top--;
    }
    str[i] = '\0';
    return i;
}

int strcpy(char* dest, char* source)
{
    int i;
    for (i = 0; source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return i;
}
