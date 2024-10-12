#include <iostream>

class Board{
    bool* rows;
    bool* columns;
    bool* diagonals1;
    bool* diagonals2;
    int* queens;
    size_t n,Qcount=0;
    private:

    void alloc(size_t size){
        rows = new bool[n+1];
        columns = new bool[n+1];
        diagonals1 = new bool[2*n+2];
        diagonals2 = new bool[2*n+2];
        queens = new int[n+1];
        Qcount = 0;
        n = size;
        for(int i = 0; i<n;i++ ){
            rows[i] = false;
            columns[i] = false;
            queens[i] = 0;
        }
        for(int i = 0; i<2*n+2;i++ ){
            diagonals1[i] = false;
            diagonals2[i] = false;
        }
    }

    void copy(const Board& other){
        alloc(other.n);
        for(int i = 0; i<n;i++ ){
            rows[i]=other.rows[i];
            columns[i]=other.columns[i];
            queens[i]=other.queens[i];
        }
        for(int i = 0; i<2*n+2;i++ ){
            diagonals1[i]=other.diagonals1[i];
            diagonals2[i]=other.diagonals2[i];
        }
    }
    void free(){
        delete[] rows;
        delete[] columns;
        delete[] diagonals1;
        delete[] diagonals2;
        delete[] queens;
    }

    public:
    Board(size_t size){
        alloc(size);
        std::cout<<"construct"<<std::endl;
    }
    Board(const Board& other){
        std::cout<<"copy"<<std::endl;
        copy(other);
    }
    Board& operator=(const Board& other){
        std::cout<<"operator="<<std::endl;
        if(this != &other){
            free();
            copy(other);
        }
        return *this;
    }
    ~Board(){
        std::cout<<"destructor"<<std::endl;
        free();
    }

    void mark(int loc,bool val){
        rows[loc/n] = columns[loc%n] = diagonals1[(loc/n-loc%n)+n]  = diagonals2[loc/n+loc%n] = val;
    }

    bool isSafe(int loc)const {
        int x = loc/n;
        int y = loc%n;
        int d = x - y + n;
        int d2 = x + y;
        if(rows[x] || columns[y] || diagonals1[d] || diagonals2[d2])return false;
        return true;
    }
    void addQueen(int loc){
        queens[Qcount] = loc;
        Qcount++ ;
        mark(loc,true);
    }
    void removeQueen(int loc){
        Qcount--;
        mark(loc,false);
    }
    int const * const getQueens()const{
        return queens;
    }
    size_t getQcount()const {return Qcount;}

    void PrintBoard()const {
        int index = 0;
        for(size_t i = 0; i< n*n;i++){
            if(!(i % n)){
                std::cout<<std::endl;
            }
            if(i == queens[index]){
                std::cout<<" Q";
                index++;
            }
            else std::cout<<" .";
        }
        std::cout<<"\n\n\n";

    }
};

void GenerateQueensBoard(size_t n,size_t loc,Board& board){
    if(board.getQcount() == n)return board.PrintBoard();
    if(loc>=n*n)return;
    if(board.isSafe(loc)){

        board.addQueen(loc);

        GenerateQueensBoard(n, loc+1,board);
        
        board.removeQueen(loc);
    }
    GenerateQueensBoard(n, loc+1,board);
}

void Queens(int n){
    Board b(n);
    GenerateQueensBoard(n,0,b);
}

int main(){
    Queens(8);
}