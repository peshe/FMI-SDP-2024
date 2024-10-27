class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> unexploded;
        for (int asteroid : asteroids) {
            addAsteroid(unexploded, asteroid);
        }

        vector<int> result(unexploded.size(), 0);
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = unexploded.top();
            unexploded.pop();
        }
        return result;
    }

private:
    static void addAsteroid(stack<int>& unexploded, int asteroid) {
        if (unexploded.empty()) {
            unexploded.push(asteroid);
            return;
        }

        int top = unexploded.top();
        if (signbit(top) == signbit(asteroid) || asteroid > 0) {
            // Или се движат в същата посока, или новият астероид надясно, а
            // предният наляво => няма сблъсък.
            unexploded.push(asteroid);
            return;
        }

        while (top > 0) {
            if (top > abs(asteroid)) return; // само новият е унищожен
            unexploded.pop(); // иначе предният е унищожен
            if (top == abs(asteroid)) return; // все пак и новият е унищожен

            if (unexploded.empty()) break;
            top = unexploded.top(); // иначе продължаваме до следващия сблъсък
        }

        // Щом до този момент новият не е бил унищожен, значи остава.
        unexploded.push(asteroid);
    }
}
