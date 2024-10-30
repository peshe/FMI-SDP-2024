#include <bits/stdc++.h>
#include <sstream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'getMax' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY operations as parameter.
 */

vector<int> getMax(vector<string> operations) {
    std::stack<int> values;
    std::stack<int> maxValues;
    std::vector<int> result;
    
    for(const std::string& input : operations) {
        std::stringstream ss(input);
        int operation;
        int value;
        ss >> operation;
        switch (operation) {
            case 1: {
                ss >> value;
                values.push(value);

                if(maxValues.empty() || maxValues.top() <= value) {
                    maxValues.push(value);
                }
                break;
            }
            case 2: {
                if(!values.empty() && !maxValues.empty() && values.top() == maxValues.top()) {
                    maxValues.pop();
                }

                values.pop();
                break;
            }
            case 3: {
                if(!maxValues.empty()) {
                    result.push_back(maxValues.top());
                }
                
                break;
            }
        }
    }
    
    return result;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> ops(n);

    for (int i = 0; i < n; i++) {
        string ops_item;
        getline(cin, ops_item);

        ops[i] = ops_item;
    }

    vector<int> res = getMax(ops);

    for (size_t i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
