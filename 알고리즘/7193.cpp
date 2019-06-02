#include<iostream>
using namespace std;
int iy[9];
int ky[9];
bool checkArr[9];
int win;

void permutation(int idx, int ky_score, int iy_score){
    if(idx==9){
        if(ky_score>iy_score) {
            win++;
            return;
        }
        return;
    }
    for(int i=0; i<9; i++){
        if(checkArr[i]==false){
            checkArr[i]=true;
            if(ky[idx]>iy[i]) permutation(idx+1, ky_score+(ky[idx]+iy[i]), iy_score);
            else permutation(idx+1, ky_score, iy_score+(ky[idx]+iy[i]));
            checkArr[i]=false;
        }
    }
}

int main(){
    int T;
    cin>>T;
    for(int t=1; t<=T; t++){
        cout<<'#'<<t<<' ';
        win=0;
        int card[19]={0};
        for(int i=0; i<9; i++){
            cin>>ky[i];
            card[ky[i]]=1;
        }
        int k=0;
        for(int i=1; i<=18; i++){
            if(card[i]==0) {iy[k++]=i;}
        }
        permutation(0,0,0);
        cout<<win<<' '<<362880-win<<'\n';
    }
    return 0;
}
