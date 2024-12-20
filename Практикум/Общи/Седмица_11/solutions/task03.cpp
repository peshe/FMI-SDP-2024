class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        size_t nRemaining = rooms.size();
        vector<bool> visited(nRemaining, false);
    
        queue<int> next;
        next.push(0);

        while (!next.empty()) {
            int current = next.front();
            next.pop();

            if (!visited[current]) {
                visited[current] = true;
                --nRemaining;

                for (int i : rooms[current]) {
                    next.push(i);
                }
            }
        }

        return nRemaining == 0;
    }
};
