#include<bits/stdc++.h>
using namespace std;

bool isSafe(int row,int col, int n,vector<string>&board,vector<vector<string>>&ans){
    int actualRow = row;
    int actualCol = col;
    while(col>=0){
        if(board[row][col]=='Q') return false;
        col--;
    }
    col = actualCol;
    while(col>=0 && row>=0){
        if(board[row][col]=='Q') return false;
        col--;
        row--;
    }
    row = actualRow;
    col = actualCol;
    while(col>=0 && row<n){
        if(board[row][col]=='Q') return false;
        col--;
        row++;
    }
    return true;
}

void helper(int col,int n, vector<string>&board,vector<vector<string>>&ans){
    if(col==n){
        ans.push_back(board);
        return;
    }
    for(int row=0;row<n;row++){
        if(isSafe(row,col,n,board,ans)){
            board[row][col]='Q';
            helper(col+1,n,board,ans);
            board[row][col]='*';
        }
    }
}

void branchandBound(int col, int n, vector<string>&board,vector<vector<string>>&ans,vector<int>&leftRow,vector<int>&upperDiagonal,vector<int>&lowerDiagonal){
    if(col==n){
        ans.push_back(board);
        return;
    }
    for(int row=0;row<n;row++){
        if(leftRow[row]==0 && lowerDiagonal[row+col]==0 && upperDiagonal[n+col-row-1]==0){
            board[row][col]='Q';
            leftRow[row]=1;
            lowerDiagonal[row+col]=1;
            upperDiagonal[n-1+col-row]=1;
            branchandBound(col+1,n,board,ans,leftRow,upperDiagonal,lowerDiagonal);
            board[row][col]='*';
            leftRow[row]=0;
            lowerDiagonal[row+col]=0;
            upperDiagonal[n-1+col-row]=0;
        }
    }
}

int main(){
    int n;
    cin>>n;
    vector<string>board(n,string(n,'*'));
    vector<vector<string>>ans;
    // helper(0,n,board,ans);
    vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
    branchandBound(0, n, board, ans, leftRow, upperDiagonal, lowerDiagonal);
    cout<<"number of solutions: "<<ans.size()<<endl;
    for(auto i:ans){
        for(auto j:i){
            cout<<j<<endl;
        }
        cout<<endl;
    }
}