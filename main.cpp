#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef struct
{
    double coef;//系数
    int expn;//指数
}term;
typedef struct LNode
{
    term data;
    LNode *next;
}*Link, *Linklist;
Linklist La, Lb, Lc, Ld, Le, Lf;
int cmp(term a, term b)
{
    if(a.expn == b.expn) return 0;
    else return (a.expn - b.expn) / abs(a.expn - b.expn);
}
int ElemLocate(Linklist L, term e, Link &S, Link &Q, int (*compara)(term, term))
{
    Link p;
    S = L; p = S->next;
    while(p && compara(p->data, e) != 0)
    {
        S = p;
        p = p->next;
    }
    if(!p)
    {
        S = Q = NULL;
        return 0;
    }
    else
    {
        Q = p;
        return 1;
    }
}
void Orderinsert(Linklist &L, term e, int (*compara)(term, term))
{
    Link o, p, q;
    q = L; p = q->next;
    while(p && compara(p->data, e) < 0)
    {
        q = p;
        p = p->next;
    }
    o = (Link)malloc(sizeof(LNode));
    o->data = e;
    q->next = o;
    o->next = p;
}
void DeleteElem(Linklist &L, Link S)
{
    Link Q = S->next;
    S->next = Q->next;
    free(Q);
}
void InsertElem(Linklist &L, term e, int (*compara)(term, term), char op)
{
    Link Q, S;
    if(ElemLocate(L, e, S, Q, compara))//存在当前指数
    {
        switch(op)
        {
            case '+': Q->data.coef += e.coef; break;
            case '-': Q->data.coef -= e.coef;
        }
        if(!Q->data.coef)
            DeleteElem(L, S);
    }
    else
        Orderinsert(L, e, compara);//不存在当前指数 找到合适顺序插入
}
void inputpolynomial(Linklist &L)//输入多项式
{
    printf("*******************************************************************************\n");
    L = (Link)malloc(sizeof(LNode));
    L->next = NULL;
    int m;
    printf("\t\t\t\t请输入多项式项数:");
    scanf("%d", &m);
    printf("\t\t\t\t请输入每一项的系数与指数\n");
    for(int i = 1; i <= m; i++)
    {
        term e;
        printf("\t\t\t\t第%d项系数与指数:", i);
        scanf("%lf%d", &e.coef, &e.expn);
        InsertElem(L, e, cmp, '+');//插入元素
    }
    printf("*******************************************************************************\n");
}
void outputpolynomial(Linklist &L)//输出多项式
{
    printf("*******************************************************************************\n");
    Link Q = L->next;
    printf("输出多项式:\n");
    while(Q)
    {
        if(Q->data.expn == 0)
            printf("%.2lf", Q->data.coef);
        else if(Q->data.coef == 1 && Q->data.expn == 1)
            printf("x");
        else if(Q->data.coef == -1 && Q->data.expn == 1)
            printf("-x");
        else if(Q->data.coef == 1)
            printf("x^%d", Q->data.expn);
        else if(Q->data.coef == -1)
            printf("-x^%d", Q->data.expn);
        else if(Q->data.expn == 1)
            printf("%.2lf*x", Q->data.coef);
        else
            printf("%.2lf*x^%d", Q->data.coef, Q->data.expn);
        if(Q->next)
        {
            if(Q->next->data.coef > 0)
                printf("+");
        }
        Q = Q->next;
    }
    printf("\n");
    printf("*******************************************************************************\n");
}
void polynomialadd_sub(Linklist &L1, Linklist &L2, Linklist &L3, char op)
{
    printf("*******************************************************************************\n");
    L3 = (Link)malloc(sizeof(LNode));
    L3->next = NULL;
    Link S = L1->next;
    term e;
    while(S)
    {
        e.coef = S->data.coef;
        e.expn = S->data.expn;
        InsertElem(L3, e, cmp, op);
        S = S->next;
    }
    S = L2->next;
    while(S)
    {
        e.coef = S->data.coef;
        e.expn = S->data.expn;
        InsertElem(L3, e, cmp, op);
        S = S->next;
    }
    switch(op)
    {
        case '+': printf("\t\t\t\t已经成功将两个多项式相加\n"); break;
        case '-': printf("\t\t\t\t已经成功将两个多项式相减\n");
    }
    printf("*******************************************************************************\n");
}
void polynomialmui_div(Linklist &L1, Linklist &L2, Linklist &L3)
{
    printf("*******************************************************************************\n");
    L3 = (Link)malloc(sizeof(LNode));
    L3->next = NULL;
    Link S = L1->next;
    term s, e;
    while(S)//先插入L1
    {
        s.coef = S->data.coef;
        s.expn = S->data.expn;
        Link Q = L2->next;
        while(Q)
        {
            e.coef = s.coef * Q->data.coef;
            e.expn = s.expn + Q->data.expn;
            InsertElem(L3, e, cmp, '+');
            Q = Q->next;
        }
        S = S->next;
    }
    printf("\t\t\t\t已经成功将两个多项式相乘\n");
    printf("*******************************************************************************\n");
}
void Chooseoperator(int op)
{
    int C;
    switch(op)
    {
        case 1:
                printf("\n\n\n\n\n");
                printf("\t\t\t\t请您选择操作\n");
                printf("\t\t\t\t1:开始使用\n");
                printf("\t\t\t\t2:退出系统\n");
                printf("\t\t\t\t您的选择:"); scanf("%d", &C);
                while(C < 1 || C > 2)
                {
                    printf("\t\t\t\t输入不合法，请您重新输入\n");
                    printf("\t\t\t\t您的选择:"); scanf("%d", &C);
                }
                switch(C)
                {
                    case 1: system("cls"); Chooseoperator(2); break;
                    case 2: system("cls");
                            printf("\n\n");
                            printf("\t\t\t\t亲\n\t\t\t\t，\n");
                            printf("\t\t\t\t谢\n\t\t\t\t谢\n\t\t\t\t您\n\t\t\t\t的\n\t\t\t\t使\n\t\t\t\t用\n\t\t\t\t！\n");
                }
                break;
        case 2:
                printf("\n\n");
                printf("\t\t\t\t请您选择操作\n");
                printf("\t\t\t\t1:输入多项式a\n");
                printf("\t\t\t\t2:输出多项式a\n");
                printf("\t\t\t\t3:输入多项式b\n");
                printf("\t\t\t\t4:输出多项式b\n");
                printf("\t\t\t\t5:多项式a、b相加得到多项式c\n");
                printf("\t\t\t\t6:输出多项式c\n");
                printf("\t\t\t\t7:多项式a、b相减得到多项式d\n");
                printf("\t\t\t\t8:输出多项式d\n");
                printf("\t\t\t\t9:多项式a、b相乘得到多项式e\n");
                printf("\t\t\t\t10:输出多项式e\n");
                printf("\t\t\t\t11:回退上一步\n");
                printf("\t\t\t\t您的选择:"); scanf("%d", &C);
                while(C < 1 || C > 11)
                {
                    printf("\t\t\t\t输入不合法，请您重新输入:");
                    printf("\t\t\t\t您的选择:"); scanf("%d", &C);
                }
                switch(C)
                {
                    case 1: system("cls"); inputpolynomial(La); Chooseoperator(2); break;
                    case 2: system("cls"); outputpolynomial(La); Chooseoperator(2); break;
                    case 3: system("cls"); inputpolynomial(Lb); Chooseoperator(2); break;
                    case 4: system("cls"); outputpolynomial(Lb); Chooseoperator(2); break;
                    case 5: system("cls"); polynomialadd_sub(La, Lb, Lc, '+'); Chooseoperator(2); break;
                    case 6: system("cls"); outputpolynomial(Lc); Chooseoperator(2); break;
                    case 7: system("cls"); polynomialadd_sub(La, Lb, Ld, '-'); Chooseoperator(2); break;
                    case 8: system("cls"); outputpolynomial(Ld); Chooseoperator(2); break;
                    case 9: system("cls"); polynomialmui_div(La, Lb, Le); Chooseoperator(2); break;
                    case 10: system("cls"); outputpolynomial(Le); Chooseoperator(2); break;
                    case 11: system("cls"); Chooseoperator(1);
                }
    }
}
int main()
{
    printf("********************************欢迎使用该系统**********************************");
    Chooseoperator(1);
    return 0;
}
