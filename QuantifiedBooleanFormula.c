#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node
{
    struct node *l,*r,*pa;
    int data;
};


struct list
{
    struct list *ne;
    struct list *pr;
    struct node *d;
    int dep;
};

int nov;
char s[100000];

struct list* dequeue(struct list * q)
{
    struct list * last = q->pr;
   
    (last->pr)->ne=q;
   
    q->pr=last->pr;
   
    return last;

}

struct list * enqueue(struct list* q , struct list * ne)
{
    struct list *first = q->ne;

    ne->pr=q;
    ne->ne=first;
    q->ne=ne;
    first->pr=ne;

}



void evaluate(struct node * curr, int d)
{
    struct list * q=(struct list *)malloc(sizeof(struct list));
    struct list * start=(struct list *)malloc(sizeof(struct list));
   

    start->dep=0;
    start->d=curr;
   
    q->dep =-1;
    q->d=NULL;
   
   
    q->ne=start;
    q->pr=start;
    start->pr=q;
    start->ne=q;
   
   
    while(1)
    {
   
        if((q->pr)->dep == nov)
        break;
       
           
        struct list * temp = dequeue(q);   
       
       
        struct list * random=(struct list *)malloc(sizeof(struct list));
       
        random->d=temp->d->l;
        random->dep=(temp->dep)+1;
       
        enqueue(q,random);
       
        struct list * ran=(struct list *)malloc(sizeof(struct list));
       
        ran->d=temp->d->r;
        ran->dep= (temp->dep)+1;
       
        enqueue(q,ran);
       
       
    }
   
    int eval[26]={0};
   
    while(1)
    {
   
        if(q->ne==q)    // queue empty
            break;
           
           
        struct list * temp = dequeue(q);
       
       
        if(nov== temp->dep)
        {
            int ans=1,i;


            for(i=0;s[i]!='\0';i++)
            {
                i++;
                int clause=0;

                while(s[i]!=')')
                {
                    int neg=0;

                    if(s[i]=='-')
                    {
                        i++;
                        neg=1;
                    }

                    int literal;
                    literal= eval[((int)s[i])-65];

                    if(neg)
                        clause=clause|(!literal);
                    else 
                        clause=clause|literal;
                  
                    if(s[i+1]==')')i++;
                    else
                        i+=2;
                }

                ans=ans&clause;
                if(!ans)break;

                i+=1;
            }

            temp->d->data=ans;
           
          
           
               
            ///         addd parent in quueue
           
            //printf("%d ",ans);
        
               
                int last=nov-1;
               
                while(eval[last]==1 && last>=0)
                    eval[last--]=0;
                   
                eval[last]=1; 
        }
        else
        {
            if((temp->dep)&1)
            {
                temp->d->data = (temp->d->l->data)&(temp->d->r->data);
            }
            else
                temp->d->data = (temp->d->l->data)|(temp->d->r->data);       
        }
       
       
       
        if(temp->d->pa)
        {
       
            if(temp->d->pa->r == temp->d )
           
            {struct list * te = (struct list * )malloc(sizeof(struct list));
           
            te->dep=(temp->dep)-1;
            te->d = temp->d->pa;
           
            enqueue(q,te);
            }
       
        }
           
    }
       

}





void treeconstruct(struct node* curr , int d)
{
    d++;
   
    if(d==nov)
    {return;}

    struct node * le = (struct node * )malloc(sizeof(struct node));
    le->l=NULL;
    le->r=NULL;
    le->pa=curr;
    le->data=0;

    struct node * ri = (struct node * )malloc(sizeof(struct node));
    ri->l=NULL;
    ri->r=NULL;
    ri->pa=curr;
    ri->data=0;

    curr->l = le;
    curr->r = ri;
   

  
    treeconstruct(curr->l,d);
 
    treeconstruct(curr->r,d);

    //printf("%d ",curr->data);

    return ;

}

void preorder(struct node* curr)
{
    if(curr)
    {
        printf("%d",curr->data);
        preorder(curr->l);
        preorder(curr->r);  
    }
    return ;
}

int main()
{
  
    int i,a[26]={0},eval[26]={0};
    nov=0;

    scanf("%s",s);

    //printf("%s\n",s);

    for(i=0;s[i]!='\0';i++)
    {
        if(isalpha(s[i]))
            a[(int)s[i]-65]=1;
    }

    for(i=0;i<26;i++)
    {
        if(a[i]==1)
            nov++;
    }
    //printf("%d\n",nov);

    struct node * tree = (struct node*)malloc(sizeof(struct node));
    tree->data=0;
    tree->l=NULL;
    tree->r=NULL;
    tree->pa=NULL;
   
    treeconstruct(tree,-1);
    evaluate(tree,-1);

    preorder(tree);

    return 0;

}
