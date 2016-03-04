#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *l,*r;
    char ch;
    int f,tb;
};

int hs=0,noc;
int tbc=0;

int left(int i)
{return i<<1;}

int right(int i)
{return i<<1|1;}

int parent(int i)
{return i>>1;}


void minhpy(struct node **heap , int i)
{
    int s;

    if(left(i)<=hs && ((heap[left(i)]->f < heap[i]->f)||(heap[left(i)]->f == heap[i]->f && heap[left(i)]->tb < heap[i]->tb)))
    {
        s =left(i);
    }
    else
        s =i;


    if(right(i)<=hs && ((heap[right(i)]->f < heap[s]->f)||(heap[right(i)]->f == heap[s]->f && heap[right(i)]->tb < heap[s]->tb)))
    {
        s =right(i);
    }


    if(s!=i)
    {
        struct node * temp = heap[i]; heap[i]=heap[s]; heap[s]=temp;
    
        minhpy(heap,s);
    }

    return;

}

void buildh(struct node** h)
{
    int i=hs>>1;

    for(;i>0;i--)
        minhpy(h,i);

}

struct node * extmin(struct node ** h)
{
    struct node* temp = h[1]; h[1]=h[hs] ; h[hs]=temp;
    hs--;

    minhpy(h,1);

    return h[hs+1];
}

void deckey(struct node **h,int i,int nk)
{
    
}

void insert(struct node **h , struct node * z)
{
    hs++;
    h[hs]=z;
    
    int i=hs;

    while(i>1 && ((h[parent(i)]->f > h[i]->f)||((h[parent(i)]->f==h[i]->f)&&(h[parent(i)]->tb > h[i]->tb))))
    {
        struct node * temp = h[i]; h[i]=h[parent(i)] ; h[parent(i)]=temp;
        i=parent(i);
    }

    return ;
}


struct node * hoffman(struct node ** h)
{
    int i,j;
    char cc;
    for(i=1;i<noc;i++)
    {
        struct node * x=extmin(h);
        struct node * y=extmin(h);

        struct node * z = (struct node * )malloc(sizeof(struct node));

        z->l=x;
        z->r=y;
        z->ch='0';
        z->f=(x->f)+(y->f);
        z->tb=(tbc++);

        insert(h,z);
        
    }

    return extmin(h);

}

void postorder(struct node * t)
{
    if(t)
    { 
        postorder(t->l);
        postorder(t->r);
        printf("%c",t->ch);
    }
}

void inorder(struct node *t)
{
    if(t)
    {
        inorder(t->l);
        printf("%c",t->ch);
        inorder(t->r);
    }
}

void code(char c,struct node * a,int *eval,int d)
{
    d++;

    if(a->ch==c)
    {
        int i;
        for(i=0;i<d;i++)
        {
            printf("%d",eval[i]);
        }
        return;
    }

    eval[d]=0;

    if(a->l)
        code(c,a->l,eval,d);

    eval[d]=1;

    if(a->r)
        code(c,a->r,eval,d);

    return;
}

int main()
{
    int a[26]={0},i=0;
    char st[1000];

    

    scanf("%s",st);

    for(i=0;st[i]!='\0';i++)
        a[(int)st[i]-65]++;

    for(i=0;i<26;i++)
        if(a[i])
            noc++;


    struct node *heap[10000];
 
    for(i=0;st[i]!='\0';i++)
    {
        if(a[(int)st[i]-65]>0)
        {
            heap[hs+1]= (struct node *)malloc(sizeof(struct node));

            (heap[hs+1])->ch=st[i];
            (heap[hs+1])->f=a[(int)st[i]-65];
            (heap[hs+1])->tb=(tbc++);
            (heap[hs+1])->l=heap[hs+1]->r=NULL;

            a[(int)st[i]-65]=0;

            hs++;
        }
    }
     
    buildh(heap);


    for(i=1;i<=hs;i++)
    {
        printf("%c %d %d\n",heap[i]->ch,heap[i]->f,heap[i]->tb);
    }

    struct node * tree =hoffman(heap);

    printf("%d\n",noc+noc-1);
    postorder(tree);
    printf("\n");
    inorder(tree);
    printf("\n");
    int eval[100]={0};

    for(i=0;st[i]!='\0';i++)
    {
        code(st[i],tree,eval,-1);
    }
    
}
