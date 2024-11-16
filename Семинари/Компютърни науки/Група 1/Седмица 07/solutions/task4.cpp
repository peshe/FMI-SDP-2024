#include <iostream>

using namespace std;

struct MatrixCell{
    int val;
    MatrixCell* next, *down;
};

MatrixCell* createMatrix(int arr[][3],size_t n,size_t m){
    MatrixCell** startPoints = new MatrixCell*[m];
    MatrixCell** currPoints = new MatrixCell*[m];
    for(int j=0;j<m;j++)
        startPoints[j] = nullptr;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0){
                startPoints[j] = new MatrixCell{arr[i][j],nullptr,nullptr};
                currPoints[j] = startPoints[j];
            }
            else{
                currPoints[j]->down = new MatrixCell{arr[i][j],nullptr,nullptr};
                currPoints[j] = currPoints[j]->down; 
            }
        }
    }
    for(int j=0;j<m;j++)
    currPoints[j] = startPoints[j];
   for(int i=0;i<n;i++){
        for(int j=0;j<m-1;j++){
            currPoints[j]->next = currPoints[j+1];
        }
        for(int j=0;j<m;j++){
            currPoints[j] = currPoints[j]->down;
        }
    }
 
    MatrixCell* temp = startPoints[0];
    delete[] startPoints;
    delete[] currPoints;
    return temp;
}   

void print(MatrixCell* start){
    MatrixCell* lineStart=start, *curr = start;

    for(int i=0;lineStart;i++){
        curr = lineStart;
        for(int j=0;curr;j++){
            cout<<curr->val<<" ";
            curr=curr->next;
        }
        cout<<endl;
        lineStart = lineStart->down;
    }
}

int main(){
    int arr[4][3]={
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10, 0 ,5}
    };
    print(createMatrix(arr,4,3));
}
