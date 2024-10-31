class MyQueue {
public:
    MyQueue() { }
    
    void push(int x) {
        // Винаги добавяме в правия стек.
        reverseStack(reversedStack, mainStack);
        mainStack.push(x);
    }
    
    int pop() {
        int result = peek();
        reversedStack.pop();
        return result;
    }
    
    int peek() {
        // Винаги връщаме от обърнатия стек.
        reverseStack(mainStack, reversedStack);
        return reversedStack.top();
    }
    
    bool empty() {
        return mainStack.empty() && reversedStack.empty();
    }

private:
    stack<int> mainStack;
    stack<int> reversedStack;

    static void reverseStack(stack<int>& from, stack<int>& to) {
        while (!from.empty()) {
            to.push(from.top());
            from.pop();
        }
    }
}
