#include<stdio.h>
#include<stdlib.h>

struct node
{
    int a,b;
    struct node *p,*m,*l,*h;
};

struct qu
{
    struct node* nd;
    struct qu *pr,*ne;
};

int dig(int n)                                         // O(1)
{
    int temp=0;
    while(n)
    {
        temp++;
        n/=10;
    }
    return temp;
}

void enq(struct qu * n,struct qu * q)                  // O(1)
{
    n->pr=q;
    n->ne=q->ne;
    q->ne->pr=n;
    q->ne=n;
}

struct qu* deq(struct qu* q)                            //O(1)
{
    struct qu* la=q->pr;

    la->pr->ne=q;
    q->pr=la->pr;

    return la;
}

struct qu*  pop(struct qu* q)                           //O(1)
{
    struct qu* st=q->ne;

    st->ne->pr=q;
    q->ne=st->ne;

    return st;
}

void renq(struct qu* n,struct qu* q)                   //O(1)
{
    struct qu* la=q->pr;

    n->ne=q;
    n->pr=la;
    la->ne=n;
    q->pr=n;
}

int inline max(int a,int b)                             //O(1)
{
    if(a>b)return a;
    
    return b;
}

void karas(int m1,int m2)                               //O(lg(max(m1,m2))^1.59)
{
    struct qu *q;                                      
    q=(struct qu*)malloc(sizeof(struct qu));

    q->nd=NULL;
    q->pr=q;
    q->ne=q;                                       // queue

    struct qu * st=(struct qu*)malloc(sizeof(struct qu));
    st->nd=NULL;
    st->pr=st->ne=st;                              //stack

    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->a=m1;
    temp->b=m2;
    temp->p=temp->l=temp->m=temp->h=NULL;

    struct qu *te=(struct qu*)malloc(sizeof(struct qu));
    
    te->nd=temp;
    te->ne=te->pr=q;
    q->ne=q->pr=te;


    while(q->ne != q)
    {
        struct qu* cur= deq(q);

        int fi=cur->nd->a;
        int se=cur->nd->b;

        if(dig(fi)<=1 && dig(se)<=1)
        {
            enq(cur,st);
        }
        else
        {
            int bign=max(dig(fi),dig(se));
            bign/=2;

            int mod=1;
            for(;bign;bign--)
                mod*=10;

            int l1= fi%mod;
            int l2= se%mod;
            int h1= fi/mod;
            int h2= se/mod;

            struct node *n1=(struct node*)malloc(sizeof(struct node));// middle  
            struct node *n2=(struct node*)malloc(sizeof(struct node));// high
            struct node *n3=(struct node*)malloc(sizeof(struct node));// low

            n1->p=n2->p=n3->p=cur->nd;
            n1->l=n2->l=n3->l=NULL;
            n1->m=n2->m=n3->m=NULL;
            n1->h=n2->h=n3->h=NULL;
            cur->nd->m=n1;
            cur->nd->h=n2;
            cur->nd->l=n3;

            n1->a =l1+h1;
            n1->b=l2+h2;
            n2->a =h1;
            n2->b=h2;
            n3->a =l1;
            n3->b=l2;

            struct qu* q1=(struct qu*)malloc(sizeof(struct qu));
            struct qu* q2=(struct qu*)malloc(sizeof(struct qu));
            struct qu* q3=(struct qu*)malloc(sizeof(struct qu));

            q1->nd=n1;
            enq(q1,q);

            q2->nd=n2;
            enq(q2,q);

            q3->nd=n3;
            enq(q3,q);

        }

    }

     while(st->ne!=st)
     {
        struct qu* tem=pop(st);
    
        if(tem->nd->l==NULL)
        {
            int mul = tem->nd->a;
            mul*=tem->nd->b;
            printf("%dX%d=%d\n",tem->nd->a,tem->nd->b,mul);
            tem->nd->a=mul;   
        }
        else
        {
            int bign=max(dig(tem->nd->a),dig(tem->nd->b));
            bign/=2;

            int mod=1;
            for(;bign;bign--)
                mod*=10;

            int mid=tem->nd->m->a;
            int low=tem->nd->l->a;
            int high=tem->nd->h->a;


            int ans=low+mod*(mid-low-high);
            ans+=mod*mod*high;

            printf("%dX%d=",tem->nd->a,tem->nd->b);
            printf("%dX%dX%d+",high,mod,mod);
            printf("(%d-%d-%d)X%d+",mid,high,low,mod);
            printf("%d=%d\n",low,ans);

            tem->nd->a=ans;
        }
            if(tem->nd->p && tem->nd->p->m==tem->nd)
            {
                 struct qu* ne = (struct qu*)malloc(sizeof(struct qu));
                 ne->nd=tem->nd->p;

                 renq(ne,st);
            }
    }

}

int main()
{
    int m1,m2;
    char ch;
    
    scanf("%d %c%d",&m1,&ch,&m2);

    karas(m1,m2);
}
