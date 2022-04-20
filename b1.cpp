#include <bits/stdc++.h>
using namespace std;
int main()
{
    int m,n,k;
    cin>>m>>n;
    cin>>k;
    int *array=(int*)malloc(sizeof(m*n));//dynamically alloting memory
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>array[i+j];
        }
    }
    //since it is given that the entered array is sorted
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(array[i+j]==k)
            {
                cout<<"True"<<endl;
                cout<<i<<" "<<j<<endl;
            }
        }
    }
    
}