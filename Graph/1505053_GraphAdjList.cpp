#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
    int *color,*parent,*dist;
    int *dfs_color,*dfs_parent,*dfs_start,*dfs_finish;
    int time=0;

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
	//void dfs(int source); //will run dfs in the graph
    void dfs_visit(int u);
    void dfs();

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color=0;
    parent=0;
    dist=0;
    dfs_color=0;
    dfs_parent=0;
    dfs_start=0;
    dfs_finish=0;


}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
	adjList[u].removeItem(v) ;
	if(!directed) adjList[v].removeItem(u) ;


}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
   if(directed){
   if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
   else return false;
   }
   else{
            if(adjList[u].searchItem(v)!=NULL_VALUE||adjList[v].searchItem(u)!=NULL_VALUE)return true;
            else return false;
   }

}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0||u>nVertices)return NULL_VALUE;
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
 int i,j;
    for(i=0;i<adjList[u].getLength();i++){
    for(j=0;j<adjList[v].getLength();j++)
        if(adjList[u].getItem(i)==adjList[v].getItem(j)) return true;
 }

    return false;
}

void Graph::bfs(int source)
{
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
    Queue q ;
    int u;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
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


//void Graph::dfs(int source)
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
    for(int p=0;p<nVertices;p++){
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

    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
     printf("\n\n\n");


}

Graph::~Graph()
{
    //write your destructor here
    int j;
    if(adjList!=0) delete[] adjList;
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
    dfs_finish =0;
    color=0;
    parent=0;
    dist=0;
}

//**********************Graph class ends here******************************

//******main function to test your code*************************
int main(void)
{
    int n;
    //Graph g;
    Graph g = new Graph(true);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        /*
        printf("1. Add edge. \n");
        printf("4.remove edge 2.is edge 3.get degree 7.has common adjacent 8.getdist . 5. Print Graph  9. Exit.\n");
          */
        printf("1. Add edge. \t");
        printf("2.is edge \t3.get degree \t4.remove edge \t7.has common adjacent \n5. Print Graph\t6. dfs \t\t8.getdist \t9. Exit.\n\n\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        { int u,v;
            printf("enter first vertice   ");
            scanf("%d",&u);
            printf("enter second vertice  ") ;
            scanf("%d",&v);
            bool p= g.isEdge(u,v);
            if(p)printf("true");
            else printf("false");


        }
        else if(ch==3)
        { int u;
            printf("enter vertice");
            scanf("%d",&u);
            printf("%d\n",g.getDegree(u));


        }
        else if(ch==4)
        {
            int u,v;
            printf("enter first vertice   ");
            scanf("%d",&u);
            printf("enter second vertice  ") ;
            scanf("%d",&v);
            g.removeEdge(u,v);
        }

        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==7)
        {

                int u,v;
                printf("enter first vertice   ");
                scanf("%d",&u);
                printf("enter second vertice  ") ;
                scanf("%d",&v);
                bool p= g.hasCommonAdjacent(u,v);
                if(p)printf("true");
                else printf("false");



        }
        else if(ch==8)
        {
            int u,v;
            printf("enter first vertice  ");
            scanf("%d",&u);
            printf("enter second vertice  ") ;
            scanf("%d",&v);
            printf("%d\n",g.getDist(u,v));
        }
        else if(ch==6){
                int source;
            printf("enter source  \n");
    //      scanf("%d",&source);
//g.dfs(source);
            g.dfs();
        }


        else if(ch==9)
        {
            break;
        }
    }

}
