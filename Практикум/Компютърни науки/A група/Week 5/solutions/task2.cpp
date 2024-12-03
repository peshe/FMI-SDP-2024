#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generateString(int index, const vector<vector<char>> &data, string &s)
{
    if (index >= data.size())
    {
        cout << s << endl;
        return;
    }
    for (int i = 0; i < data[index].size(); i++)
    {
        s[index] = data[index][i];
        generateString(index + 1, data, s);
    }
}

int main()
{
    string line;
    bool inGroup = false;
    vector<vector<char>> data;
    getline(cin, line);
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '{')
        {
            data.push_back(vector<char>());
            inGroup = true;
        }
        else if (line[i] >= 'a' && line[i] <= 'z')
        {
            if (!inGroup)
                data.push_back({line[i]});
            else
                data[data.size() - 1].push_back(line[i]);
        }
        else if (line[i] == '}')
        {
            inGroup = false;
        }
    }
    string s(data.size(), ' ');
    generateString(0, data, s);
}

//{a,b}c{d,e}f