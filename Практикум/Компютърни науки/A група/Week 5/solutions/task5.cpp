#include <iostream>
#include <queue>
#include <stack>

using namespace std;

void tokenise(string path, queue<string> &directories)
{
    string s = "";
    for (int i = 1; i < path.size(); i++)
    {
        if (path[i] == '/')
        {
            if (s != "")
                directories.push(s);
            s = "";
        }
        else
            s.push_back(path[i]);
    }
    if (s != "")
        directories.push(s);
}

string simplifyPath(string path)
{
    queue<string> directories;
    tokenise(path, directories);

    string curr;
    deque<string> result; // може да се направи със стек и reverse на стека след това
    while (!directories.empty())
    {
        curr = directories.front();
        directories.pop();
        if (curr == ".")
            continue;
        if (curr == "..")
        {
            if (!result.empty())
                result.pop_back();
        }
        else
            result.push_back(curr);
    }

    // Превръщане на двустранната опашка в стринг
    string resultS = "/";
    if (result.empty())
        resultS.push_back('/');

    while (!result.empty())
    {
        resultS.append(result.front());
        resultS.push_back('/');
        result.pop_front();
    }

    resultS.pop_back();
    return resultS;
}

int main()
{
    string s;
    cin >> s;
    cout << simplifyPath(s);
}