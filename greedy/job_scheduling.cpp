#include<bits/stdc++.h>
using namespace std;

vector<int> helper(int n,vector<char>&jobId,vector<int>&deadlines,vector<int>&profit){
    vector<tuple<int,int,char>>jobs;
    for(int i=0;i<n;i++){
        jobs.push_back({profit[i],deadlines[i],jobId[i]});
    }
    sort(jobs.begin(),jobs.end(),greater<tuple<int,int,char>>());
    int maxi=0;
    for(int i:deadlines){
        maxi = max(i,maxi);
    }
    vector<char>schedule(maxi+1,'-');
    int total=0;
    for(auto i:jobs){
        int p = get<0>(i);
        int d = get<1>(i);
        char id = get<2>(i);
        for(int j=d;j>0;j--){
            if(schedule[j]=='-'){
                schedule[j]=id;
                total+=p;
                break;
            }
        }
    }
    cout<<"Schedule jobs: "<<endl;
    for(int i=1;i<=maxi;i++){
        if(schedule[i]!='-') cout<<schedule[i]<<" ";
    }
    cout<<"total profit: "<<total<<endl;
    return {0,total};
}

int main(){
    int n;
    cout<<"Enter number of jobs: ";
    cin>>n;
    vector<char>jobId(n);
    vector<int>deadlines(n);
    vector<int>profit(n);
    cout<<"Enter jobId, deadline and profit: ";
    for(int i=0;i<n;i++){
        cin>>jobId[i]>>deadlines[i]>>profit[i];
    }
    helper(n,jobId,deadlines,profit);
    return 0;
}