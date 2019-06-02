#include<iostream>
using namespace std;
int number;
typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

void inorder(treePointer ptr){
    if(ptr){
        inorder(ptr->leftChild);
        cout<<ptr->data;
        inorder(ptr->rightChild);
    }
}

int main(void){
    for(int t=1; t<=10; t++){
        cout<<"#"<<t<<' ';
        cin>>number;
        node nodes[number+1];
        int N;
        char C;
        for(int i=1; i<=number; i++){
            if(number%2==0){
                if(i<number/2){
                    cin>>N>>C>>N>>N;
                    nodes[i].data = C;
                    nodes[i].leftChild = NULL;
                    nodes[i].rightChild = NULL;
                }
                else if (i==number/2){
                    cin>>N>>C>>N;
                    nodes[i].data = C;
                    nodes[i].leftChild = NULL;
                    nodes[i].rightChild = NULL;
                }
                else {
                    cin>>N>>C;
                    nodes[i].data = C;
                    nodes[i].leftChild = NULL;
                    nodes[i].rightChild = NULL;
                }
            }
            else{
                if(i<=number/2){
                    cin>>N>>C>>N>>N;
                    nodes[i].data = C;
                    nodes[i].leftChild = NULL;
                    nodes[i].rightChild = NULL;
                }
                
                else {
                    cin>>N>>C;
                    nodes[i].data = C;
                    nodes[i].leftChild = NULL;
                    nodes[i].rightChild = NULL;
                }
            }
        }
        for(int i=1; i<=number; i++){
            if(i%2==0)
                nodes[i/2].leftChild = &nodes[i];
            else
                nodes[i/2].rightChild = &nodes[i];
        }
        inorder(&nodes[1]);
        cout<<'\n';
    }
    return 0;
}
