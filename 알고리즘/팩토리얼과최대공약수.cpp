#include<iostream>
using namespace std;

int main(){
	int T;
    cin>>T;
    for(int t=1; t<=T; t++){
    	cout<<"#"<<t<<" ";
        int N, K;
        cin>>N>>K;
        int result=1;
        if(N>=K){
        	result=K;
        }
        else{
        	for(int i=N; i>0; i--){
            	if(K%i==0){
                	result*=i;
                    K/=i;
                }
            }
        }
        cout<<result<<endl;
    }
    return 0;
}
