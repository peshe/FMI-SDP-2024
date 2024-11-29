#include <iostream>
#include <vector>
#include <stack>
#include <string>

class TextEditor
{
private:
    std::vector<char> text;
    std::stack<std::vector<char>> undoStack;
    std::stack<std::vector<char>> redoStack;

public:
    TextEditor() {}

    void write(char c)
    {
        undoStack.push(text);
        while (!redoStack.empty())
        {
            redoStack.pop();
        }
        text.push_back(c);
    }

    void read() const
    {
        for (char c : text)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    void undo()
    {
        if (!undoStack.empty())
        {
            redoStack.push(text);
            text = undoStack.top();
            undoStack.pop();
        }
    }

    void redo()
    {
        if (!redoStack.empty())
        {
            undoStack.push(text);
            text = redoStack.top();
            redoStack.pop();
        }
    }
};

int main()
{
    TextEditor editor;

    editor.write('a'); // a
    editor.write('b'); // ab
    editor.write('c'); // abc
    editor.write('d'); // abcd
    editor.read();     // prints abcd

    editor.undo(); // abc
    editor.undo(); // ab
    editor.read(); // prints ab

    editor.redo(); // abc
    editor.read(); // prints abc

    editor.redo(); // abcd
    editor.read(); // prints abcd

    return 0;
}
