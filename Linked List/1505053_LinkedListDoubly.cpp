#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem( int newItem)
{
    //write your codes here
     struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
   if(tail==0){
    tail=newNode;
   }
    return SUCCESS_VALUE ;

}

//add required codes to delete item, remember to properly set the tail pointer!
int deleteAfter(int item)
{ struct listNode * newNode,*OLD_ITEM,*temp ;

    OLD_ITEM=searchItem(item);

    if(OLD_ITEM == 0) return NULL_VALUE;
    temp=list;
    if(temp==0||OLD_ITEM->next==0)
    {
        return SUCCESS_VALUE;
    }
   else if(OLD_ITEM!=0)
    {
        temp=OLD_ITEM->next;
        OLD_ITEM->next=temp->next;
        tail=temp->next;
        free(temp);
        return SUCCESS_VALUE;
       }
}

int insertLast(int item)
{
    //write your codes here
    struct listNode * newNode,*temp ;
    temp=list;
    if(temp==0)
        {
            insertItem(item);
            return SUCCESS_VALUE;
        }
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item=item;
    tail->next=newNode;
    newNode->next=0;
    tail=newNode;

}
int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item after... 3. Search item. \n");
        printf("4. insert last . 5. Print. 6. exit.  \n");//7. delete after

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==4)
        {int item;
        scanf("%d",&item);
            insertLast( item);

        }

    }

}
