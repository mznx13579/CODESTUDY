#include<iostream>
#include<cstring>
using namespace std;

int main(){
    for(int t=1; t<=10; t++){
        cout<<"#"<<t<<" ";
        string s;
        int n;
        cin>>n>>s;
        int result=0;
        for(int i=0; i<n; i++){
            if(s[i]!=43){
                result+=s[i]-48;
            }
        }
        cout<<result<<endl;
    }
    return 0;
}
