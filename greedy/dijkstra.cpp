#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>>adjfun(vector<vector<int>>&edges, int v){
    vector<vector<vector<int>>>adj(v);
    for(auto i:edges){
        int u = i[0];
        int v = i[1];
        int wt = i[2];
        adj[u].push_back({v,wt});
        adj[v].push_back({u,wt});
    }
    return adj;
}

vector<int>dijkstra(int v,vector<vector<int>>&edges, int src){
    vector<vector<vector<int>>>adj = adjfun(edges,v);
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
    vector<int>dist(v,INT_MAX);
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty()){
        int u=pq.top()[1];
        pq.pop();
        for(auto &i:adj[u]){
            int v = i[0];
            int wt = i[1];
            if(dist[v]>dist[u]+wt){
                dist[v] = dist[u]+wt;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

int main(){
    int v,e,src;
    cout<<"enter number of vertices: ";
    cin>>v;
    cout<<"enter number of edges: ";
    cin>>e; 
    vector<vector<int>>edges(e);
    cout<<"enter {u,v,w}: ";
    for(int i=0;i<e;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges[i]={u,v,w};
    }
    cout<<"enter source: ";
    cin>>src;
    vector<int>ans = dijkstra(v,edges,src);
    cout<<"shortest distance from vertex: "<<src<<" are"<<endl;
    for(int i:ans) cout<<i<<" ";
}