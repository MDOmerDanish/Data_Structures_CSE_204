#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};



struct treeNode * root;
void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}


int getSize(struct treeNode * node)
{
    if(node==0) return 0;
    /*
    else
    {
        getSize(node->left);
        getSize(node->right);
    }*/
    else
    {
        return ( getSize(node->left)+getSize(node->right)+1);
    }
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    struct treeNode * Node = root;
    //Node=searchItem(root,node->item);
    int depth=0;
    while(Node!=0)
    {
        if(node->item==Node->item)break;
        if(node->item<Node->item)
        {
            Node=Node->left;
            depth ++;
            // if(Node==0) break;
        }
        else
        {
            Node=Node->right;
            depth ++;
            // if(Node==0) break;
        }
    }

    return depth;

}

int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode * node = 0;
    node=searchItem(root,item);
    calcNodeDepth(node);
}
int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode * node = 0;
    node=root;
    while(node->left!=0)
    {
        node=node->left;
    }
    return node->item;
}
int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode * tmp, * parent = 0;
    tmp=node;
    if(node->item==item){

        if(node->right==0&&node->left==0){
            free(node);
            initializeTree();
            return TRUE_VALUE;
        }
        else{
           parent=tmp->right;
        struct treeNode * last_node = parent;
           while(last_node->left!=0){
            parent=last_node;
           last_node=last_node->left;
           }

         tmp->item=last_node->item;
         parent->left=0;
         free(last_node);
        return TRUE_VALUE;
        }

    }

    if(node->left==0||node->right==0){

        if(node->left==0){
                node=node->right;
             free(node);
        }
        if(node->right==0){
                node=node->left;
             free(node);
        }
        return TRUE_VALUE;
    }
    while(item!=tmp->item)
    {
        if(item<tmp->item)
        {
            parent=tmp;
            tmp=tmp->left;
        }
        if(item>tmp->item)
        {
            parent=tmp;
            tmp=tmp->right;
        }
    }
    if(tmp->left==0&&tmp->right==0)
    {
        if(parent->item>item)
        {
            parent->left=0;
            free(tmp);
        }
        else if(parent->item<item)
        {
            parent->right=0;
            free(tmp);
        }
        return TRUE_VALUE;
    }
    else if (tmp->left==0&&tmp->right!=0)
    {
        if(item<parent->item)
        {
            parent->left=tmp->right;
            free(tmp);
        }
        else
        {
            parent->right=tmp->right;
            free(tmp);
        }
        return TRUE_VALUE;
    }
    else if (tmp->left!=0&&tmp->right==0)
    {

        if(item<parent->item)
        {
            parent->left=tmp->left;
            free(tmp);
        }
        else
        {
            parent->right=tmp->left;
            free(tmp);
        }
        return TRUE_VALUE;
    }
    else if (tmp->left!=0&&tmp->right!=0)
    {
          printf("enter in double child situation \n\n");
        struct treeNode * tm = 0;
        struct treeNode * tm_2 = 0;
       // tm=tmp->right;
        tm_2=tmp->right;
        if(tm_2->left==0&&tm_2->right==0 ) {
                tmp->item=tm_2->item;
                tmp->right=0;

               // deleteItem(root,tm_2->item);
                free(tm_2);
            return TRUE_VALUE;
        }
       if((tmp->left->left==0&&tmp->left->right==0 )&&tmp->right==0) {
                tmp->item=tmp->left->item;
                tmp->left=0;

               // deleteItem(root,tm_2->item);
                free(tmp->left);
            return TRUE_VALUE;
        }
        if(tmp->right->left!=0){

           parent=tmp->right;
        struct treeNode * last_node = parent;
           while(last_node->left!=0){
            last_node=parent;
           last_node=last_node->left;

           }

         tmp->item=last_node->item;
         parent->left=0;
         free(last_node);
        return TRUE_VALUE;

        }

    }
}
int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode * node = 0;
    node=root;
    while(node->right!=0)
    {
        node=node->right;

    }
    return node->item;

}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    //write your codes here
    if(node==0||(node->item<leftBound)||(node->item>rightBound)) return 0;
    /*
    else
    {
        getSize(node->left);
        getSize(node->right);
    }*/
    else
    {
        return ( rangeSearch(node->left,leftBound,rightBound)+rangeSearch(node->right,leftBound,rightBound)+1);
    }
}

void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}
int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit. 8.max item 9.min item 10.getsize \n");
        printf("11. calc node depth 12.calcDepth with item  13.rangesearch 14. delete item\n\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==8)
        {
            printf("%d \n\n",getMaxItem());
        }

        else if(ch==9)
        {
            printf("%d \n\n",getMinItem());
        }


        else if(ch==10)
        {
            struct treeNode * Node = root;
            printf("%d \n\n",getSize(root));
        }

        else if(ch==11)
        {
            struct treeNode * Node = root;
            printf("%d \n\n",getSize(root));
        }
        else if(ch==12)

        {
            int item;
            printf("enter item\n");
            scanf("%d",&item);
            printf("%d\n\n",calcDepth(item));

        }
        else if(ch==13)

        {
            int leftitem,rightitem;
            printf("enter leftbound\n");
            scanf("%d",&leftitem);
            printf("enter rightbound\n");
            scanf("%d",&rightitem);
            printf("%d\n\n",rangeSearch(root,leftitem,rightitem));



        }
        else if(ch==14)
        {
            int item;
            struct treeNode * Node = root;
            printf("enter element");
            scanf("%d",&item);
            deleteItem(root,item);

        }



    }
}



