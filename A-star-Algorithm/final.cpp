#include<bits/stdc++.h>
using namespace std;

set<vector<vector<int>>>visited;

int calculate(vector<vector<int>>&curr,vector<vector<int>>&goal){
    int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(curr[i][j]!=0 && curr[i][j]!=goal[i][j]) count++;
        }
    }
    return count;
}

pair<int,int>findBlank(vector<vector<int>>&board){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==0) return make_pair(i,j);
        }
    }
    return make_pair(-1,-1);
}

vector<pair<vector<vector<int>>,int>>generate(vector<vector<int>>&curr,vector<vector<int>>&goal){
    vector<pair<vector<vector<int>>,int>>nextState;
    pair<int,int>blank=findBlank(curr);
    int x = blank.first;
    int y = blank.second;
    vector<pair<int,int>>directions = {{0,1},{1,0},{0,-1},{-1,0}};
    for(int i=0;i<4;i++){
        int newX = x+directions[i].first;
        int newY = y+directions[i].second;
        if(newX>=0 && newY>=0 && newX<3 && newY<3){
            vector<vector<int>>newBoard = curr;
            swap(newBoard[x][y],newBoard[newX][newY]);
            if(visited.find(newBoard) == visited.end()){
                int h = calculate(newBoard,goal);
                nextState.push_back(make_pair(newBoard,h));
            }
        }
    }
    return nextState;
}

int helper(vector<vector<int>>&start,vector<vector<int>>&goal){
    // f=g+h,h,g,state
    typedef tuple<int,int,int,vector<vector<int>>>tp;
    priority_queue<tp,vector<tp>,greater<tp>>pq;
    int h=calculate(start,goal);
    pq.push(make_tuple(h,h,0,start));
    while(!pq.empty()){
        int f,currH,g;
        vector<vector<int>>state;
        tie(f,currH,g,state) = pq.top();
        pq.pop();
        if(visited.find(state)!=visited.end()) continue;
        visited.insert(state);
        if(goal==state) return g;
        vector<pair<vector<vector<int>>,int>> nextState = generate(state,goal);
        for(int i=0;i<nextState.size();i++){
            vector<vector<int>>next = nextState[i].first;
            int newH = nextState[i].second;
            int newG = g+1;
            pq.push(make_tuple(newG+newH,newH,newG,next));
        }
    }
    return -1;
}

int main(){
    int n=3;
    vector<vector<int>>start(n,vector<int>(3));
    vector<vector<int>>goal(n,vector<int>(3));
    cout<<"Enter input: ";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>start[i][j];
        }
    }
    cout<<"Enter goal: ";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>goal[i][j];
        }
    }
    int ans=helper(start,goal);
    if(ans!=-1){
        cout<<"Answer found in steps:- "<<ans<<endl;
    }
    else cout<<"Solution does not exist"<<endl;
}