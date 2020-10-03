#include<iostream>
#include<cstdio>
#define NULL_VALUE -99999
#define INFINITY 99999

using namespace std;

class point{
public:
    int x ;
    int y ;

    point(int a=0,int b=0);

};

point :: point(int a,int b)
{
    x=a;
    y=b;
}

void Merge(point arr[],int p,int q,int r)
{
    int n1,n2;
    point Pin;
    Pin.x = INFINITY;
    Pin.y = INFINITY;
    n1 = q-p+1;
    n2 = r-q ;
    point a1[n1+1],a2[n2+1];
    for(int i=0;i<n1;i++)a1[i]=arr[p+i];
    for(int j=0;j<n2;j++)a2[j]=arr[q+j+1] ;

    a1[n1] = Pin ;
    a2[n2] = Pin ;
    int i=0,j=0;

    for(int k=p;k<=r;k++){
        if(a1[i].x<=a2[j].x){
            arr[k] = a1[i] ;
            i++ ;
        }
        else {
            arr[k] = a2[j] ;
            j++ ;
        }
    }
}

void MergeSort(point arr[],int p,int r)
{
    //base case
    if(r<=p)return ;
    int q;
    q=(p+r)/2;
    MergeSort(arr,p,q) ;
    MergeSort(arr,q+1,r);
    Merge(arr,p,q,r);
}

int main()
{
    int n,a,b;
    cin>>n;
    point parray[n];
    for(int i=0;i<n;i++){
        cin>>a;
        parray[i].x=a;
        parray[i].y=i+1;
    }

    MergeSort(parray,0,n-1);
//    skyline(parray,0,n-1);
for(int j=0;j<n;j++){

   cout<< parray[j].y<<endl;

}
    return 0;
}




