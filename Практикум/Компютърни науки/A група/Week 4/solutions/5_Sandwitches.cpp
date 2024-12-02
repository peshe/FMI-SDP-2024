#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int hungry_students(int n, int k, vector<int> &sandwiches, vector<int> &preferences)
{
    queue<int> studentQueue;

    for (int i = 0; i < n; ++i)
    {
        studentQueue.push(preferences[i]);
    }

    int attempts = 0;
    int total_students = n;

    while (!studentQueue.empty() && !sandwiches.empty())
    {
        int currentPreference = studentQueue.front();
        studentQueue.pop();

        if (currentPreference == sandwiches[0])
        {
            sandwiches.erase(sandwiches.begin());
            attempts = 0;
        }
        else
        {
            studentQueue.push(currentPreference);
            attempts++;

            if (attempts >= total_students)
            {
                break;
            }
        }
    }

    return studentQueue.size();
}

int main()
{
    int n, k;
    cout << "Enter number of sandwiches/students (N) and number of types (K): ";
    cin >> n >> k;

    vector<int> sandwiches(n);
    vector<int> preferences(n);

    cout << "Enter sandwich types: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> sandwiches[i];
    }

    cout << "Enter students' preferences: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> preferences[i];
    }

    int result = hungry_students(n, k, sandwiches, preferences);
    cout << "Number of hungry students: " << result << endl;

    return 0;
}
