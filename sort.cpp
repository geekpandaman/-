#include<iostream>
#include<stdlib.h>
#include<math.h>

#define Heap_MAX 10000

using namespace std;



class sort_fun{
    public:
        void Insert_sort(int *a,int num,int gap=1);/*默认参数只能写在类函数声明处*/
        void Bubble_sort(int *a,int num);
        void Shell_sort(int *a,int num);
        void Quick_sort(int *a,int num);
        void Merge_sort(int *a,int num);
        void Heap_sort(int *a,int num);
};

int main()
{   
    sort_fun function;
    int n=1000;
    int a[n];
    for(int i=0;i!=n;i++)
    {
        a[i]=rand()%100;
    }
    function.Heap_sort(a,n);
    for(int i=0;i!=n;i++)
    {
        cout<<a[i]<<' ';
    }
    return 0;
}



void sort_fun::Insert_sort(int *a,int num,int gap)
{
    for(int i=0;i<num;i+=gap)
    {
        int tmp=a[i];
        int j=i;
        while(j>0&&a[j-1]>tmp)
        {
            a[j]=a[j-1];
            j-=gap;
        }
        a[j]=tmp;
    }
}

void sort_fun::Bubble_sort(int *a,int num)
{
    for(int i=num;i!=0;i--)
    {   
        bool flag=1;
        for(int j=0;j!=num;j++)
            if(a[j]>a[j+1])
            {int tmp=a[j];a[j]=a[j+1];a[j+1]=tmp;flag=0;}
        if(flag)
            break;
    }
}

void sort_fun::Shell_sort(int *a,int num)
{
    /*采用sedgewick增量序列*/
    for(int i=5;i>=0;i--)
    {
        int n1=pow(4,i+2)-3*pow(2,i+2)+1;
        int n2=9*pow(4,i)-9*pow(2,i)+1;
        this->Insert_sort(a,num,n1);
        this->Insert_sort(a,num,n2);
    }
}

void sort_fun::Quick_sort(int *a,int num)
{   
    //需要调也是
    void q_sort(int *a,int left,int right);
    q_sort(a,0,num-1);
}
void q_sort(int *a,int left,int right)
{   
    int partition(int *a,int left,int right);
    if(left<right){
        /*将中间元素移动到左边*/
        int medium=(left+right)/2;
        int tmp;
        if(a[left]>a[medium])
            {tmp=a[left];a[left]=a[medium];a[medium]=tmp;}
        if(a[medium]>a[right])
            {tmp=a[medium];a[medium]=a[right];a[right]=tmp;}
        if(a[left]>a[medium])
            {tmp=a[left];a[left]=a[medium];a[medium]=tmp;}
        tmp=a[left];a[left]=a[medium];a[medium]=tmp;
        int pivotloc=partition(a,left,right);
        q_sort(a,left,pivotloc-1);
        q_sort(a,pivotloc+1,right);
    }
}

int partition(int *a,int left,int right)
{
    int pivot=a[left];
    while(left<right)
    {
        while(left<right&&a[right]>=pivot)/*必须写>=，否则在两边等于成为移动元素条件，陷入死循环*/
            right--;
        a[left]=a[right];
        while(left<right&&a[left]<=pivot)
            left++;
        a[right]=a[left];
    }
    a[left]=pivot;
    return left;
}

void sort_fun::Merge_sort(int *a,int num)
{
    if(num>1)
    {   
        int *L=a;
        int *R=a+num/2;
        Merge_sort(L,num/2);
        Merge_sort(R,num-num/2);
        int tmp[num];
        int i=0;
        while(L!=a+num/2&&R!=a+num)
        {
            if(*L<*R)
                {tmp[i]=*L;L++;}
            else
                {tmp[i]=*R;R++;}
            i++;
        }
        if(L==a+num/2)
            while(R!=a+num)
                {tmp[i]=*R;R++;i++;}
        if(R==a+num)
            while(L!=a+num/2)
                {tmp[i]=*L;L++;i++;}
        for(int j=0;j!=num;j++)
            a[j]=tmp[j];
            
    }
}



void sort_fun::Heap_sort(int *a,int num)
{
    /*建立最小堆*/
    int tmp[num];
    void Adjustheap(int *a,int loc,const int maxsize);
    int Deleteheap(int *a,int loc,int num);
    for(int i=num-1;i>=0;i--)
    {
        Adjustheap(a,i,num);
    }//将a调整为堆
    /*
    for(int i=0;i!=num;i++)
    {
        tmp[i]=Deleteheap(a,num-1-i,num);
    }

    for(int j=0;j!=num;j++)
        a[j]=tmp[j];*/

}

void Adjustheap(int *a,int loc,const int maxsize)
{
    /*对于某一节点，在左右子树都是最小堆的情况下，构建一最小堆*/
    int *L,*R=nullptr;
    if((loc+1)*2-1<maxsize)
        L=a+(loc+1)*2-1;
    if((loc+1)*2<maxsize)
        R=a+(loc+1)*2;
    if(L!=nullptr&&R!=nullptr)
    {
        if(*L<*R)
        {
            if(*L<a[loc])
            {int tmp=*L;*L=a[loc];a[loc]=tmp;Adjustheap(a,(loc+1)*2-1,maxsize);}
        }
        else if (*R<*L)
        {
            if(*R<a[loc])
            {int tmp=*R;*R=a[loc];a[loc]=tmp;Adjustheap(a,(loc+1)*2,maxsize);}
        }
    }
    else if(L!=nullptr)
    {
        if(*L<a[loc])
            {int tmp=*L;*L=a[loc];a[loc]=tmp;Adjustheap(a,(loc+1)*2-1,maxsize);}
    }
    
}

int Deleteheap(int *a,int loc,int num)
{   
    void Adjustheap(int *a,int loc,const int maxsize);
    int tmp=a[0];
    a[0]=a[loc];
    a[loc]=Heap_MAX;
    Adjustheap(a,0,num);
    return tmp;
}