class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        vector<vector<int>> graph (quiet.size());
        vector<int> inDegree(501, 0);
        for(int i = 0; i < richer.size(); ++i)
        {
            int a = richer[i][0];
            int b = richer[i][1];
            graph[b].push_back(a);
            inDegree[a]++;
        }
        
        vector<int> topoSort;
        for(int i = 0; i < graph.size(); ++i)
        {
            if(inDegree[i] == 0)
            {
                topoSort.push_back(i);
            }
        }

        for(int i = 0; i < topoSort.size(); ++i)
        {
            int currentNode = topoSort[i];
            for(int j = 0; j < graph[currentNode].size(); ++j)
            {
                inDegree[graph[currentNode][j]]--;
                if(inDegree[graph[currentNode][j]] == 0)
                {
                    topoSort.push_back(graph[currentNode][j]);
                }
            }
        }

        vector<int> result (graph.size());
        for(int i = 0; i < result.size(); ++i) {
            result[i] = i;
        }

        for(int i = topoSort.size() - 1; i >= 0; --i)
        {
            int min = quiet[topoSort[i]];
            int minIndex = topoSort[i];
            for(int j = 0; j < graph[topoSort[i]].size(); ++j)
            {
                int childIndex = graph[topoSort[i]][j];
                if(quiet[result[childIndex]] < min)
                {
                    min = quiet[result[childIndex]];
                    minIndex = result[childIndex];
                }
            }
            result[topoSort[i]] = minIndex;
        }

        return result;
    }
};