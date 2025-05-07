#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void helper(vector<int>&arr,int n){
    for(int i=0;i<n-1;i++){
        int minIndex=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[minIndex]){
                minIndex=j;
            }
        }
        swap(arr[i],arr[minIndex]);
    }
}

int main() {
    int n;
    cin>>n;
    vi arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    helper(arr,n);
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";
    
    return 0;
}