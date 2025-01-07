class Solution {
public:
    bool visited[101];
    bool colour[101];

    void dfs(vector<vector<int>>& graph, int node, bool c, bool& answer)
    {
        visited[node] = true;
        colour[node] = c;
        for(int i = 0; i < graph[node].size(); ++i)
        {
            if(!visited[graph[node][i]])
            {
                dfs(graph, graph[node][i], !c, answer);
            }
            else
            {
                if(colour[node] == colour[graph[node][i]])
                {
                    answer = false;
                }
            }
        }
    }

    bool isBipartite(vector<vector<int>>& graph) {
        bool answer = true;
        for(int i = 0; i < graph.size(); ++i)
        {
            if(!visited[i])
            {
                dfs(graph, i, 0, answer);
            }
        }
        return answer;   
    }
};