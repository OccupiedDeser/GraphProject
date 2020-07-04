#include "extra.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>

void initStack(S_Stack** S_pointer)
{
    *S_pointer = (S_Stack*)malloc(sizeof(S_Stack));
    (*S_pointer)->top = -1;
}

void push(int d, S_Stack* S)
{
    if (!isStackFull(S)) {
        S->top++;
        S->data[S->top] = d;
    } else {
        printf("栈溢出");
    }
}

int pop(S_Stack* S)
{
    if (!isStackEmpty(S)) {
        S->top--;
        return S->data[S->top + 1];
    } else {
        printf("空栈");
        int error = { -1 };
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

void enQueue(int d, S_Queue* Q)
{
    if (!isQueueFull(Q)) {
        Q->data[Q->rear] = d;
        Q->rear++;
    } else {
        printf("满队队列");
    }
}

int deQueue(S_Queue* Q)
{
    if (!isQueueEmpty(Q)) {
        Q->front++;
        return Q->data[Q->front - 1];
    } else {
        printf("空队列");
        int error = -1;
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

int extra_strcmp(char* a, char* b)
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

int extra_itoa(int x, char* str)
{
    if (x == 0) {
        str[0] = '0';
        str[1] = '\0';
        return 1;
    }

    int i = 0, top = -1;
    char _stack[10];
    while (x != 0) {
        top++;
        _stack[top] = x % 10 + '0';
        x /= 10;
    }
    while (top > -1) {
        str[i] = _stack[top];
        i++;
        top--;
    }
    str[i] = '\0';
    return i;
}

int extra_strcpy(char* dest, char* source)
{
    int i;
    for (i = 0; source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return i;
}

int extra_atoi(char* str)
{
    int ret = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > '9' || str[i] < '0') {
            return -1;
        }
        ret = 10 * ret + str[i] - '0';
    }
    return ret;
}

int cmp(const void* a, const void* b)
{
    int* x = (int*)a;
    int* y = (int*)b;
    if (x[0] != y[0]) {
        return x[0] - y[0];
    } else {
        return x[1] - y[1];
    }
}

void draw_garlic()
{
    printf("\n");
    printf("                                          ..\'\'.                           \n");
    printf("                                      .:xKNNKKXXOd;                       \n");
    printf("                                    ;ONOooXd\'   .l0X.                     \n");
    printf("                                 .o0x,     ,dNNK0OXX.                     \n");
    printf("                               .k0l          .OKo,.                       \n");
    printf("                              ,0c          .kx\'                           \n");
    printf("                             cX:         .xO.                             \n");
    printf("                            cNc         ;O,                               \n");
    printf("                         . \'NN;        kXlc\'                              \n");
    printf("               .,cdkKNNXWNKKKWK.  .\',:xOdd0NNK0O0NNNKdoo:\'.               \n");
    printf("           ,okOdlc;,..       .O.            .:o0d.   . ..\';cddo,          \n");
    printf("        ;k0o.                ;c.;      ..       .:cl           :0d\'       \n");
    printf("      ;K0;.                  Odo.      ;d          \'d\'           cNd      \n");
    printf("     xX:                   .o:          X            ,:           \'Xx     \n");
    printf("   .K0.                   ::            X;             :.          \'Nd    \n");
    printf("  .KO                   ,c              Ox              ;.          xW;   \n");
    printf("  ON.                 ,k:               xk               ;,         ;Wd   \n");
    printf(" ,WO                ,k;                 xd                k.        .NX   \n");
    printf(" xWl              \'OW:                  d:                k\'         XW.  \n");
    printf(" 0M;            ,kdNX                   k\'                x.         kW.  \n");
    printf(" KW:           :c kW;                   0.                k          kW.  \n");
    printf(" kM,             .Xk       \'ldxkxk0xddx0koddxdd:.         k          0W.  \n");
    printf(" ,N0.            :N.    :OW0o:,....           .c0x.      c;         .NX   \n");
    printf("  lX:            k0   lXx;                       lK      k          OW.   \n");
    printf("  .oXX,          Kk  .Nc    ..   ;x   x\'    .;   .N.    0:         oWd    \n");
    printf("    \'XWd.        0O  ;K   \'OO0Oc.oK   xk.\':x00x. .N.   d:        .kN;     \n");
    printf("     .0WN,       .0  ,N.  o.   ;okc   .doc,.  .  lk   :;        cNk.      \n");
    printf("       dWWk.      :l  0l                         K;  .;       .O0\'        \n");
    printf("        .dWWl      0. .K:          .   .   .K\'  .X.  \'      .dO,          \n");
    printf("          .OWXc.   ;0  .Oo    ko .x00.KXo :Kc   ok   ,.   .xO\'            \n");
    printf("            .oXWk:. co . d0.   KOk\' ON: xXl    lK. cd  .lOo.              \n");
    printf("               .:xKN0XdX0okX;  ..    .       \'0o,o0dcdOo.                 \n");
    printf("                    .,:; .lONxc,.         ..xWXNX0kkl.                    \n");
    printf("                             ..;oxdxkxddxx0oxxo:.                         \n");
    printf("\n\n");
    return;
}
