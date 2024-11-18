#include <cmath>
#include <cstdio>
#include <stack>
#include <iostream>

void textEditor() {
    std::stack<std::string> editor;

    editor.push("");

    int Q;
    std::cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int command;
        std::cin >> command;

        std::string& currentState = editor.top();

        if (command == 1) {
            std::cin.ignore();
            std::string appended;

            std::getline(std::cin, appended);

            editor.push(currentState + appended);
        }
        if (command == 2) {
            int k;
            std::cin >> k;

            editor.push(currentState.substr(0, currentState.length() - k));
        }
        if (command == 4) {
            editor.pop();
        }
        if (command == 3) {
            int k;
            std::cin >> k;
            std::cout << currentState.at(k - 1) << std::endl;
        }
    }
}

int main() {
    textEditor(); 
    return 0;
}
