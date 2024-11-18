class BrowserHistory {
public:
    BrowserHistory(string homepage) {
      this->history = new Node(homepage);
    }
    
    void visit(string url) {
        delete this->history->next;
       Node* newPage = new Node(url, nullptr, this->history);
       this->history->next = newPage;
       this->history = newPage; 
    }
    
    string back(int steps) {
        if(!this->history){
            return "";
        }
        while(steps && this->history->prev)
        {
            this->history = this->history->prev;
            steps--;
        }
        return this->history->data;
    }
    
    string forward(int steps) {
        if(!this->history){
            return "";
        }
        while(steps && this->history->next)
        {
            this->history = this->history->next;
            steps--;
        }
        return this->history->data;
    }

    ~BrowserHistory() {
        Node* toDelete = this->history;
        while(toDelete->prev) {
            toDelete = toDelete->prev;
        }
        delete toDelete;
    }
private:
    class Node {
    public:
        string data;
        Node* next;
        Node* prev;
        Node(string data, Node* next = nullptr, Node* prev = nullptr)
            : data(data), next(next), prev(prev) {}

        ~Node() {
            delete next;
        }           
    };

    Node* history;
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */