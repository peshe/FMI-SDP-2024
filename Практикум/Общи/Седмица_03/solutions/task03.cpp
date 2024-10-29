class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
      stack<int> st;
      int poppedCount = 0;
      for(int pu:pushed) {
        st.push(pu);
        while(!st.empty() && st.top() == popped[poppedCount]) {
            poppedCount++;
            st.pop();
        }
      }
      return st.empty() && poppedCount == popped.size();
    }
};