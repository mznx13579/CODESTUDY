#include<iostream>
#include<string>
using namespace std;

int main(){
    string s;
    cin>>s;
    char c[s.length()];
    bool check[s.length()];
    
    cout<<"입력된 글자는 "<<"'"<<s<<"'"<<"입니다"<<endl;
    cout<<endl;
    cout<<"글자수는 "<<s.length()<<"개 입니다."<<endl;
    for(int x=0; x<s.length(); x++){
        c[x]='_';
        check[x]=false;
        cout<<c[x];
    }
    cout<<endl;
    cout<<endl;
    
    char alphabet;
    int count=0;
    
    if(s.length()<1||s.length()>8){
        cout<<"글자수 오류!"<<endl;
        exit(0);
    }
    else {
        for(int t=1; t<=8; t++){
            cout<<t<<"번째 시도입니다"<<endl;
            cout<<endl;
            cin>>alphabet;
            cout<<endl;
            
            cout<<"d_matrix에 보이는 내용 :"<<endl;
            cout<<alphabet<<endl;
            
            cout<<endl;
            for(int i=0; i<s.length(); i++){
                if(s[i]==alphabet){
                    check[i] = true;
                    count++;
                    c[i]='O';
                }
            }
            
            cout<<"clcd에 보이는 내용 :"<<endl;
            
            for(int i=0; i<s.length(); i++){
                if(check[i]==true){
                    cout<<s[i];
                }
                else{
                    cout<<'_';
                }
            }
            cout<<endl;
            cout<<endl;
            cout<<"fnd에 보이는 내용 :"<<endl;
            
            for(int i=0; i<s.length(); i++){
                cout<<c[i];
            }
            cout<<endl;
            cout<<endl;
            
            if(count==s.length())
                break;
        }
        if(count==s.length())
            cout<<"성공!"<<endl;
        else
            cout<<"실패!"<<endl;
    }
    return 0;
}
