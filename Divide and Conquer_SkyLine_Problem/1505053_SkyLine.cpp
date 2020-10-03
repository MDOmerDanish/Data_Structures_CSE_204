#include<iostream>
#define NULL_VALUE -99999
#define INFINITY 99999

using namespace std;
//pt class represents structure of points

class Pt{
public:
    int x ;
    int y ;
    bool dom;

    Pt(int a=0,int b=0, bool c=false);
    bool is_Dominating(Pt p);
    bool equals(Pt p);
};

//constructing

Pt :: Pt(int a,int b,bool c)
{
    x=a;
    y=b;
    dom = c ;
}
//fuction to check whether it is dominating or not


bool Pt::is_Dominating(Pt p)
{
    if(x>=p.x && y>=p.y) return true ;
    else return false ;
}
// return true if two points are equal


bool Pt::equals(Pt p)
{
    if(x==p.x && y==p.y)return true;
    else return false ;

}
//Queue class from previous offline


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    Pt * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(Pt item); //insert item in the queue
    Pt dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
    int getLength();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new Pt[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}

int Queue::getLength()
{
    return length ;
}

void Queue::enqueue(Pt item)
{
	if (length == queueMaxSize)
	{
		Pt * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new Pt[queueMaxSize] ;
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
		data = tempData ; //make list to Pt to new memory
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


Pt Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	Pt item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//

void Merge_func(Pt Array[],int a,int b,int c)
{
    int n1,n2;
    Pt Inf_point;
    Inf_point.x = INFINITY;
    Inf_point.y = INFINITY;
    n1 = b-a+1;
    n2 = c-b ;
    Pt L[n1+1],R[n2+1];
    for(int i=0;i<n1;i++)L[i]=Array[a+i];
    for(int j=0;j<n2;j++)R[j]=Array[b+j+1] ;

    L[n1] = Inf_point ;
    R[n2] = Inf_point ;
    int i=0,j=0;

    for(int k=a;k<=c;k++){
        if(L[i].x<=R[j].x){
            Array[k] = L[i] ;
            i++ ;
        }
        else {
            Array[k] = R[j] ;
            j++ ;
        }
    }
}
      //this function will sort the points in increasing
      //order of x

void Merge_sort(Pt Array[],int a,int c)
{
    if(c<=a)return ;
    int b;
    b=(a+c)/2;
    Merge_sort(Array,a,b) ;
    Merge_sort(Array,b+1,c);
    Merge_func(Array,a,b,c);
}

Queue Que ;

void skyline(Pt point_array[],int lo,int hi)
{
    if(hi<=lo){                         //if there is more element in the array to be
        Que.enqueue(point_array[lo]);    // handeled
        return ;
    }
    int piv = (hi+lo)/2 ;
    Pt p2 ;
    int i,j,flag = 0 ,tmp = 0;

    skyline(point_array,lo,piv);

    for(i=piv+1;i<=hi;i++){
            flag = 0;
            tmp = Que.getLength();
        for(j=0;j<tmp;j++){
            p2 = Que.dequeue();
            if(point_array[i].is_Dominating(p2)) {
                flag = 1;
                Que.enqueue(p2);
                break ;
            }
            Que.enqueue(p2);
        }
        if(!flag) {
            Que.enqueue(point_array[i]);
        }
    }

    return ;
}


int main()
{
    int n,a,b;
    cin>>n;                 //Taking the number of points
    Pt point_array[n];
    for(int i=0;i<n;i++){   //Taking points as input
        cin>>a>>b;
        point_array[i].x=a;   //setting coordinate for i th point
        point_array[i].y=b;
        point_array[i].dom = false ;
    }

    Merge_sort(point_array,0,n-1);   //this will sort the points according the value of x
    skyline(point_array,0,n-1);


    Pt p2;
    int tmp = Que.getLength() ;
    cout<<"skyline points are"<<endl;
    for(int j=0;j<tmp;j++){     //Showing skyline output
        p2 = Que.dequeue();
        cout<<"             ("<<p2.x<<" , "<<p2.y<<")"<<endl;
    }

    return 0;
}




