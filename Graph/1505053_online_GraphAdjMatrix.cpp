#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define BLACK 3
#define GREY 2

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int *color,*parent,*dist;
    int *dfs_color,*dfs_parent,*dfs_start,*dfs_finish;
    int time;

    //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs();
    void dfs_visit(int u);
    void printBridges();

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    color=0;
    parent=0;
    dist=0;
    matrix = 0 ;
    directed = dir ;
    time=0;
    //set direction of the graph
    //define other variables to be initialized
    dfs_color=0;
    dfs_parent=0;
    dfs_start=0;
    dfs_finish=0;


}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }



}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{

    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    printf("in to remove func");

    if(!directed) matrix[v][u] = 0;

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(directed)
    {
        if (matrix[u][v]==1) return true;
        else return false;
    }
    else if(!directed)
    {
        if(matrix[u][v]==1||matrix[v][u]==1)return true;
        else return false;
    }
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    int count=0;
    if(!directed)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[u][j]==1)count++;
        }
        return count;

    }
    else if(directed)
    {
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[u][j]==1)count++;
        }
        int j=0;
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[j][u]==1)count++;
        }
    }
    return count;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false ;

    for(int j=0; j<nVertices; j++)
    {
        if(matrix[u][j]==1&&matrix[v][j]==1)return true;
    }

    return false;


}

void Graph::bfs(int source)
{
    //fine till here
    //complete this function
    //initialize BFS variables
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    int u;
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    //fine till here
    while( !q.empty() )
    {
        //complete this part
        u=q.dequeue();
        for(int j=0; j<nVertices; j++)
        {
            if(isEdge(u,j))
            {
                if(color[j]==WHITE)
                {
                    dist[j]=dist[u]+1;
                    parent[j]=u;
                    color[j]=GREY;
                    q.enqueue(j);
                }
            }
        }
        //printf("Inside BFS\n");
        color[u]=BLACK;
    }

}

void Graph::dfs_visit(int u)
{

    time=time+1;
    dfs_start[u]=time;
    dfs_color[u]=GREY;

    for(int j=0; j<nVertices; j++)
    {
        if(isEdge(u,j))
        {
            if(dfs_color[j]==WHITE)
            {
                dfs_parent[j]=u;
                dfs_visit(j);
            }
        }
    }
    time=time+1;
    dfs_finish[u]=time;
    dfs_color[u]=BLACK;




}
void Graph::dfs()
{
    //write this function
    dfs_color=new int[nVertices];
    dfs_parent=new int[nVertices];
    dfs_finish=new int[nVertices];
    dfs_start=new int[nVertices];

    int i,u;
    for(i=0; i<nVertices; i++)
    {
        dfs_color[i]=WHITE;
        dfs_start[i]=dfs_finish[i]=INFINITY;
        dfs_parent[i]=NULL_VALUE;
    }
    i=0;
    for(i=0; i<nVertices; i++)
    {
        if(dfs_color[i]==WHITE) dfs_visit( i);

    }
    for(int p=0; p<nVertices; p++)
    {
        printf("%d:\t%d\t%d\n",p,dfs_start[p],dfs_finish[p]);
    }

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return  INFINITY;

    bfs(u);
    return dist[v];

}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
    printf("\n\n\n");
}



void Graph::printBridges(){
    for (int i=0;i<nVertices;i++){
     for(int j=0;j<nVertices;j++){
         if(isEdge(i,j)){
             removeEdge(i,j);
             bfs(0);
             for(int k=0;k<nVertices;k++){
                 if(color[k]==WHITE) return;
                 else{
                   printf("%d     %d\n",i,j);

                 }

             }

         }
                   addEdge(i,j);

     }

    }
    }
Graph::~Graph()
{
    //write your destructor here
    int j;
    for( j=0; j<nVertices; j++)
    {

        if(matrix[j]) delete[]matrix[j];
        matrix[j]=0;
    }
      if(matrix) delete[]matrix;
     matrix=0;
    if(color) delete[] color;
    if(parent)delete [] parent;
    if(dist)delete [] dist;
    if(dfs_color) delete[] dfs_color;
    if(dfs_parent)delete [] dfs_parent;
    if(dfs_start)delete [] dfs_start;
    if(dfs_finish)delete[]dfs_finish;
    dfs_color=0;
    dfs_parent=0;
    dfs_start=0;
    dfs_finish=0;
    color=0;
    parent=0;
    dist=0;



}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g = new Graph(false);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \t");
        printf("2.is edge \t3.get degree \t4.remove edge \t7.has common adjacent \n5. Print Graph\t6. dfs \t\t8.getdist \t9. Exit.\t 10.printBridges  \n\n\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            printf("enter first vertice");
            scanf("%d",&u);
            printf("enter second vertice") ;
            scanf("%d",&v);
            bool p= g.isEdge(u,v);
            if(p)printf("true");
            else printf("false");
        }
        else if(ch==3)
        {
            int u;
            printf("enter vertice");
            scanf("%d",&u);
            printf("%d\n",g.getDegree(u));

        }
        else if(ch==4)
        {
            int u,v;
            printf("enter first vertice");
            scanf("%d",&u);
            printf("enter second vertice") ;
            scanf("%d",&v);
            g.removeEdge(u,v);
        }
        else if(ch==7)
        {

            int u,v;
            printf("enter first vertice");
            scanf("%d",&u);
            printf("enter second vertice") ;
            scanf("%d",&v);
            bool p= g.hasCommonAdjacent(u,v);
            if(p)printf("true");
            else printf("false");



        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==9)
        {
            break;
        }
        else if(ch==8)
        {
            int u,v;
            printf("enter first vertice");
            scanf("%d",&u);
            printf("enter second vertice") ;
            scanf("%d",&v);
            printf("%d\n",g.getDist(u,v));
        }
        else if(ch==6)
        {
            g.dfs();
        }
         else if(ch==6)
        {
            g.printBridges();
        }
    }

}
