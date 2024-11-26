#include <iostream>

using namespace std;

struct MatrixCell{
    int val;
    MatrixCell* next, *down;
};

MatrixCell* createMatrix(int** arr,size_t n,size_t m){ //O(n) memory
    MatrixCell** startPoints = new MatrixCell*[n];
    MatrixCell* curr,*res;

    for(int i=0;i<n;i++){
        curr = startPoints[i] = new MatrixCell{arr[i][0],nullptr,nullptr};
        for(int j=1;j<m;j++){
            curr->next = new MatrixCell{arr[i][j],nullptr,nullptr};
            curr = curr->next; 
        }
    }
    res = startPoints[0];
    for(int i=0;i<m-1;i++){
        for(int j=0;j<n-1;j++){
            startPoints[j]->down = startPoints[j+1];
            startPoints[j] = startPoints[j]->next;
        }
    }
    delete[] startPoints;
    return res;
}   

MatrixCell* createMatrix1(int **arr,size_t N,size_t M){ // O(1) memory
    MatrixCell *begin,*prevRow = nullptr, *currRow,*prev, *curr = new MatrixCell({arr[0][0],nullptr,nullptr});
    begin = currRow = curr;
    for(int j = 1; j<M; j++ ){
        curr->next = new MatrixCell({arr[0][j],nullptr,nullptr});
        curr = curr->next;
    }
    prevRow = currRow;
    for(int i = 1; i < N; i++ ){

        currRow->down = new MatrixCell({arr[i][0],nullptr,nullptr});
        currRow = currRow->down;
        prev = prevRow;
        curr= currRow;
        for(int j = 1; j<M; j++ ){
            curr->next = new MatrixCell({arr[i][j],nullptr,nullptr});
            prev->down = curr;
            prev = prev->next;
            curr = curr->next;
        }
        prevRow = currRow;
    }
    return begin;
}

void print(MatrixCell* start){
    MatrixCell* lineStart=start, *curr = start;
    cout<<"------------\n";
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
    int N,M;
    cin>>N>>M;

    int **arr = new int*[N];
    for(int i = 0; i<N;i++){
        arr[i] = new int[M];
        for(int j = 0 ; j< M ; j++)
            cin>>arr[i][j];
    }
    print(createMatrix1(arr,4,3));
    for(int i = 0; i<N;i++)
        delete[] arr[i];
    delete[] arr;
}
