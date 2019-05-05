#include<iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int arr[102][102]={{0,},};
    int d[2]={1,-1};
    for(int t=0; t<10; t++){
        int T;
        cin>>T;
        cout<<"#"<<T<<" ";
        int x, y;
        for(int i=1; i<=100; i++){
            for(int j=1; j<=100; j++){
                cin>>arr[i][j];
                if(arr[i][j]==2){
                    x=i;
                    y=j;
                }
            }
        }
        int tmp=1;
        while(x!=1){
            if(tmp==1){
                if(arr[x][y+d[0]]==0&&arr[x][y+d[1]]==0){
                    tmp=1;
                    x-=1;
                }
                else if(arr[x][y+d[1]]==1){
                    tmp=2;
                    y-=1;
                }
                else if(arr[x][y+d[0]]==1){
                    tmp=3;
                    y+=1;
                }
            }
            if(tmp==2){
                if(arr[x][y+d[1]]==0||y+d[1]==0){
                    tmp=1;
                    x-=1;
                }
                else
                    y-=1;
            }
            if(tmp==3){
                if(arr[x][y+d[0]]==0||y+d[0]==101){
                    tmp=1;
                    x-=1;
                }
                else
                    y+=1;
            }
        }
        cout<<y-1<<endl;
    }
    return 0;
}
