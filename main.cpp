#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef struct
{
    double coef;//ϵ��
    int expn;//ָ��
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
    if(ElemLocate(L, e, S, Q, compara))//���ڵ�ǰָ��
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
        Orderinsert(L, e, compara);//�����ڵ�ǰָ�� �ҵ�����˳�����
}
void inputpolynomial(Linklist &L)//�������ʽ
{
    printf("*******************************************************************************\n");
    L = (Link)malloc(sizeof(LNode));
    L->next = NULL;
    int m;
    printf("\t\t\t\t���������ʽ����:");
    scanf("%d", &m);
    printf("\t\t\t\t������ÿһ���ϵ����ָ��\n");
    for(int i = 1; i <= m; i++)
    {
        term e;
        printf("\t\t\t\t��%d��ϵ����ָ��:", i);
        scanf("%lf%d", &e.coef, &e.expn);
        InsertElem(L, e, cmp, '+');//����Ԫ��
    }
    printf("*******************************************************************************\n");
}
void outputpolynomial(Linklist &L)//�������ʽ
{
    printf("*******************************************************************************\n");
    Link Q = L->next;
    printf("�������ʽ:\n");
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
        case '+': printf("\t\t\t\t�Ѿ��ɹ�����������ʽ���\n"); break;
        case '-': printf("\t\t\t\t�Ѿ��ɹ�����������ʽ���\n");
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
    while(S)//�Ȳ���L1
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
    printf("\t\t\t\t�Ѿ��ɹ�����������ʽ���\n");
    printf("*******************************************************************************\n");
}
void Chooseoperator(int op)
{
    int C;
    switch(op)
    {
        case 1:
                printf("\n\n\n\n\n");
                printf("\t\t\t\t����ѡ�����\n");
                printf("\t\t\t\t1:��ʼʹ��\n");
                printf("\t\t\t\t2:�˳�ϵͳ\n");
                printf("\t\t\t\t����ѡ��:"); scanf("%d", &C);
                while(C < 1 || C > 2)
                {
                    printf("\t\t\t\t���벻�Ϸ���������������\n");
                    printf("\t\t\t\t����ѡ��:"); scanf("%d", &C);
                }
                switch(C)
                {
                    case 1: system("cls"); Chooseoperator(2); break;
                    case 2: system("cls");
                            printf("\n\n");
                            printf("\t\t\t\t��\n\t\t\t\t��\n");
                            printf("\t\t\t\tл\n\t\t\t\tл\n\t\t\t\t��\n\t\t\t\t��\n\t\t\t\tʹ\n\t\t\t\t��\n\t\t\t\t��\n");
                }
                break;
        case 2:
                printf("\n\n");
                printf("\t\t\t\t����ѡ�����\n");
                printf("\t\t\t\t1:�������ʽa\n");
                printf("\t\t\t\t2:�������ʽa\n");
                printf("\t\t\t\t3:�������ʽb\n");
                printf("\t\t\t\t4:�������ʽb\n");
                printf("\t\t\t\t5:����ʽa��b��ӵõ�����ʽc\n");
                printf("\t\t\t\t6:�������ʽc\n");
                printf("\t\t\t\t7:����ʽa��b����õ�����ʽd\n");
                printf("\t\t\t\t8:�������ʽd\n");
                printf("\t\t\t\t9:����ʽa��b��˵õ�����ʽe\n");
                printf("\t\t\t\t10:�������ʽe\n");
                printf("\t\t\t\t11:������һ��\n");
                printf("\t\t\t\t����ѡ��:"); scanf("%d", &C);
                while(C < 1 || C > 11)
                {
                    printf("\t\t\t\t���벻�Ϸ���������������:");
                    printf("\t\t\t\t����ѡ��:"); scanf("%d", &C);
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
    printf("********************************��ӭʹ�ø�ϵͳ**********************************");
    Chooseoperator(1);
    return 0;
}
