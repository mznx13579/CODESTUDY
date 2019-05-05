#include<iostream>
#include<stack>
#include<string>
using namespace std;

int main(){
    for(int t=1; t<=10; t++){
        cout<<"#"<<t<<" ";
        int nx;
        cin>>nx;
        stack<char> Ss;
        while(!Ss.empty()){
            Ss.pop();
        }
        string s;
        cin>>s;
        for(int i=0; i<s.size(); i++){
            if(s[i]==41){
                if(Ss.top()=='('){
                    Ss.pop();
                }
                else{
                    break;
                }
            }
            else if(s[i]==125){
                if(Ss.top()=='{'){
                    Ss.pop();
                }
                else {
                    break;
                }
            }
            else if(s[i]==93){
                if(Ss.top()=='['){
                    Ss.pop();
                }
                else{
                    break;
                }
            }
            else if(s[i]==62){
                if(Ss.top()=='<'){
                    Ss.pop();
                }
                else{
                    break;
                }
            }
            else Ss.push(s[i]);
        }
        
        if(Ss.empty()){
            cout<<'1'<<endl;
        }
        else if(!Ss.empty()){
            cout<<'0'<<endl;
        }
    }
    return 0;
}
