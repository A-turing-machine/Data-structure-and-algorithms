#include<bits/stdc++.h>
using namespace std;
struct node
{
    int a;
    struct node *l,*r,*p;
}*root,*t1,*t2;
void transplant(struct node *a,struct node *s)
{
    if(!(a->p))
        { root=s;
            s->p=NULL;}
    else if(a==(a->p)->r)
        (a->p)->r=s;
    else (a->p)->l=s;

    if(s)
    s->p=a->p;
}
void splay(struct node* a)
{
    if(!a)return;

    while(a->p&&(a->p)->p)
    {
      struct node *b=a->p,*c=(a->p)->p;

        if(b->l==a&&c->l==b)
        {
            transplant(b,b->r);
            transplant(a,a->r);
            b->p=a;
            a->r=b;
            transplant(c,a);
            c->p=b;
            b->r=c;
        }
        else if(b->l==a&&c->r==b)
        {
            transplant(a,a->r);
            transplant(b,a->l);
            transplant(c,a);
            a->r=b;
            b->p=a;
            a->l=c;
            c->p=a;
        }
        else if(b->r==a&&(c->r==b))
        {
            transplant(b,b->l);
            transplant(a,a->l);
            b->p=a;
            a->l=b;
            transplant(c,a);
            c->p=b;
            b->l=c;
        }
        else
        {
            transplant(a,a->l);
            transplant(b,a->r);
            transplant(c,a);
            a->l=b;
            b->p=a;
            a->r=c;
            c->p=a;
        }
    }
    if(a->p)
    {
        struct node* b=a->p;
        if(a==b->l)
        {
            transplant(a,a->r);
            transplant(b,a);
            a->r=b;
            b->p=a;
        }
        else
        {
            transplant(a,a->l);
            transplant(b,a);
            a->l=b;
            b->p=a;
        }

    }
}
struct node* treesearch(int k)
{
    struct node* temp=root;
    while(temp&&temp->a!=k)
    {//cout<<temp->d<<" ";
        if(temp->a>k)
            temp=temp->l;
        else
            temp=temp->r;
    }
    splay(temp);
    return temp;
}

void treewalk(struct node* x,int lev)
{
    lev++;
    if(x)
    {
        treewalk(x->l,lev);
        cout<<"("<<x->a<<","<<lev<<")"<<" ";
        treewalk(x->r,lev);
    }

}

struct node* treemin(struct node* p)
{
    struct node* temp=p;

    while(temp->l)temp=temp->l;
    return temp;

}
struct node* succ(int k)
{
    struct node* temp=treesearch(k);
    if(!temp)
        return NULL;

    if(temp->r)
    {
        return treemin(temp->r);

    }
    struct node* y=temp->p;

    while(y&&temp==y->r)
    {
        temp=y;
        y=y->p;
    }
    return y;


}
void treedelete(int k)
{
    struct node* temp=treesearch(k);

    if(!(temp->l))
        transplant(temp,temp->r);
    else if(!(temp->r))
        transplant(temp,temp->l);
    else
    {
        struct node *y=succ(k);
        if(y->p!=temp)
        {
            transplant(y,y->r);
        y->r=temp->r;
        (y->r)->p=y;
        }
         transplant(temp,y);
            (temp->l)->p=y;
            y->l=temp->l;

    }
}
void split(struct node *a)
{
    splay(a);
    t1=a;
    t2=a->r;
    t2->p=NULL;
    t1->r=NULL;

}




void treeinsert(int k)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->a=k;
    temp->l=NULL;
    temp->r=NULL;
    temp->p=NULL;

    if(root==NULL)
        root=temp;
    else
    {
        struct node* x=root;

        while(1)
        {
            if((x->a)>k)
            {
                if(!(x->l))
                     {x->l=temp;break;}
                else
                    x=x->l;
            }
            else
            {
                 if(!(x->r))
                    {x->r=temp;break;}
                else
                    x=x->r;

            }
        }
        temp->p=x;
    }
}
int main()
{
    root=NULL;
    treeinsert(4);
    treeinsert(6);
    treeinsert(10);
    treeinsert(2);
    treeinsert(3);
    treewalk(root,0); cout<<endl;
    treedelete(2);
    cout<<treesearch(3)->a<<endl;  treewalk(root,0); cout<<endl;
    cout<<treesearch(6)->a<<endl;  treewalk(root,0); cout<<endl;
    cout<<treesearch(10)->a<<endl;  treewalk(root,0); cout<<endl;
    cout<<treesearch(4)->a<<endl;   treewalk(root,0);cout<<endl;
    treewalk(root,0); cout<<endl;

}
