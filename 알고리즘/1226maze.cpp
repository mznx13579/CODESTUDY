#include<iostream>
using namespace std;

char maze[16][16];
int visit[16][16];

int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int entry_x, entry_y, exit_x, exit_y;
int sol;

bool check(int y, int x){
    if(y>=0&&y<16&&x>=0&&x<16&&maze[y][x]!='1'&&!visit[y][x])
        return true;
    return false;
}

void dfs(int y, int x){
    if(y==exit_y&&x==exit_x){
        sol=1;
        return;
    }
    int ny, nx;
    for(int i=0; i<4; i++){
        ny=y+dy[i];
        nx=x+dx[i];
        if(check(ny, nx)){
            visit[ny][nx] = 1;
            dfs(ny, nx);
        }
    }
}

void init(){
    sol=0;
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            visit[i][j]=0;
        }
    }
}

int main(){
    int T=0;
    for(int t=1; t<=10; t++){
        cin>>T;
        for(int i=0; i<16; i++) {
            for(int j=0; j<16; j++){
                cin>>maze[i][j];
                if(maze[i][j] == '2'){
                    entry_y = i;
                    entry_x = j;
                }
                else if(maze[i][j] == '3'){
                    exit_y = i;
                    exit_x = j;
                }
            }
        }
        visit[entry_y][entry_x]  = 1;
        dfs(entry_y, entry_x);
        cout<<"#"<<t<<" "<<sol<<endl;
        init();
    }
    return 0;
}

