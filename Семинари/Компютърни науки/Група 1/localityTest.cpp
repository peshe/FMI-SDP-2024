#include <iostream>
#include <ctime>

using namespace std;

int main(){
    const size_t MAXN = 30000;
    int *arr = new int[MAXN*MAXN];
    
    time_t start , end;
    size_t sum = 0;
    for(int i=0; i < MAXN; i++){
        for(int j=0; j < MAXN; j++){
            arr[i*MAXN + j] = i*MAXN + j;
        }
    }
    cout<<"Array ready"<<endl;
    
    
    start = std::time(NULL);
    for(int i=0; i < MAXN; i++){
        for(int j=0; j < MAXN; j++){
            sum+=arr[i*MAXN+ j];
        }
    }
    end = std::time(NULL);
    std::cout<<"sum: "<<sum<<" | time: "<< end-start<<std::endl;
    
    
    
    sum=0;
    start = std::time(NULL);
    for(int i=0; i < MAXN; i++){
        for(int j=0; j < MAXN; j++){
            sum+=arr[j * MAXN+ i];
        }
    }
    end = std::time(NULL);
    std::cout<<"sum: "<<sum<<" | time: "<< end-start<<std::endl;

}