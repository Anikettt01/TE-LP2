#include<bits/stdc++.h>
using namespace std;

void dfs(int start,vector<bool>&visited,vector<vector<int>>&adj){
    visited[start]=true;
    cout<<start<<" ";
    for(int i:adj[start]){
        if(!visited[i]) dfs(i,visited,adj);
    }
}

void bfs(int start,vector<bool>&visited,vector<vector<int>>&adj){
    queue<int>q;
    visited[start] = true;
    q.push(start);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout<<node<<" ";
        for(int i:adj[node]){
            if(!visited[i]){
                visited[i]=true;
                q.push(i);
            }
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<bool>visited(n,false);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0,visited,adj);
    cout<<endl;
    visited = vector<bool>(n,false);
    bfs(0,visited,adj);
}