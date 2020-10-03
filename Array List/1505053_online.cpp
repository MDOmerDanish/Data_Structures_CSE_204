#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	}
	if(length==0){
        initializeList();
	}

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\n  Current size: %d, current length: %d\n", listMaxSize, length);
}
int getLength(){
    return length;
}
int insertItemAt(int pos,int item){
    int temp =list[pos-1];
    list[pos-1]=item;
    insertItem(temp);
}
void shrink(){

    if(listMaxSize==length*2){
        listMaxSize=listMaxSize/2;
        int * tempList ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ;
   }

}
void deleteLast(){
    length--;
    shrink();
}
int getLast(){
    return list[length-1];

}

void deleteAll(){
    int i,ck=length;
    for ( i=0;i<ck;i++){
        deleteLast();
    }
    printf(" all items deleted\n");
}

void Clear(){
    deleteAll();
    printf("and cleared ");
    free(list);
    length=0;
}



int removeDuplicate(int item){
  int i,j,count=0;

/*for(i=1;i<length;i++){
     for(j=0;j<=i;j++){
     if(list[i]==list[j]){
         printf("item to be removed %d",list[i]);
     deleteItem(list[i]);

     }
*/
   for (i=0;i<length;i++){
    if(list[i]==item){
    count++;
    }
    if(count>0){
    for(j=i+1;j<length;j++){
        if(list[j]==item){
         deleteItemAt(j);

        }
    }

    }


   }


     }








int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4.getLength  5. Print. 6. exit. 7.insertItemAt 9.deleteLast 11.deleteAll 10.clear 8.shrink  12.removeDuplicate\n");

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
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==5)
        {
            printList();
        }
       else if(ch==4)
        {
            int len;
            len=getLength();
            printf("%d \n",len);
        }
        else if(ch==7)
        {
            int pos,item;
            printf("enter position");
            scanf("%d",&pos);
            printf("enter item");
            scanf("%d",&item);

            insertItemAt(pos,item);
        }
        else if(ch==8)
        {
            shrink();
        }
        else if(ch==9)
        {
            deleteLast();
        }
        else if(ch==10)
        {
            Clear();
        }
        else if(ch==11)
        {
            deleteAll();
        }

        else if(ch==6)
        {
            break;
        }
           else if(ch==12)
        {
            int item;
            printf("enter the duplicate");
            scanf("%d",&item);

            removeDuplicate(item);
        }




    }

}



//postfix main
/*

int main()
{
    char a[30];
    printf("enter the string :");
    gets(a);
    char t;
    int c[30];
    int i,j=0,n=strlen(a);
    initializeList();
    for(i=0; i<n; i++)
    {
        t=a[i];
        if((t=='+')||(t=='-')||(t=='*')||(t=='/'))
        {
            if(t=='+'){
            //printf("Inside +\n");
            int tm1,tm2;
            tm1=getLast();
            deleteLast();
                tm2=getLast();
                deleteLast();
                insertItem(tm2+tm1);

            }
            else if(t=='-'){
                int tm1,tm2;
                tm1=getLast();
                deleteLast();
                tm2=getLast();
                deleteLast();
                insertItem(tm2-tm1);
            }
            else if(t=='*'){
                int tm1,tm2;
                tm1=getLast();deleteLast();
                tm2=getLast();deleteLast();
                insertItem(tm2*tm1);

            }
            else if(t=='/'){
                int tm1,tm2;
                tm1=getLast();deleteLast();
                tm2=getLast();deleteLast();
                insertItem(tm2/tm1);

            }
        }

        else {
            insertItem(t-'0');
        }

    }

    printf("Final Result : %d",getLast());

}

*/

