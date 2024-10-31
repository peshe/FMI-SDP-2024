class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> nextFriends;
        for (int i = 1; i <= n; ++i) {
            nextFriends.push(i);
        }
        
        while (nextFriends.size() > 1) {
            for (int i = 1; i < k; ++i) {
                nextFriends.push(nextFriends.front());
                nextFriends.pop();
            }
            nextFriends.pop();
        }

        return nextFriends.front();
    }
}
