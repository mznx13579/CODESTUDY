#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main(){
    for(int t=1; t<=10; t++){
        cout<<"#"<<t<<" ";
        string s;
        int n;
        cin>>n>>s;
        stack<int> stack1;
        stack<int> stack2;
        for(int i=0; i<n; i++){
            if(s[i]>=48&&s[i]<=57){
                stack1.push(s[i]-48);
            }
            if(s[i]==42||s[i]==43){
                if(s[i]==stack2.top()||s[i]>stack2.top()){
                    int temp=stack1.top()-48;
                    stack1.pop();
                    while(!stack2.empty()){
                        if(stack2.top()==42){
                            temp*=stack1.top()-48;
                            stack1.pop();
                            stack2.pop();
                        }
                        else if(stack2.top()==43){
                            temp+=stack1.top()-48;
                            stack1.pop();
                            stack2.pop();
                        }
                    }
                    stack1.push(temp+48);
                }
                else{
                    stack2.push(s[i]);
                }
            }
        }
        cout<<stack1.top()-48<<endl;
    }
    return 0;
}
