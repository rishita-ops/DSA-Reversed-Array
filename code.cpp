#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the size of the array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the elements of the array: ";
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }

    cout<<"The reversed array is: ";
    for(int i=n-1; i>=0; i--)
    {
        cout<<arr[i]<<" ";
    }
}