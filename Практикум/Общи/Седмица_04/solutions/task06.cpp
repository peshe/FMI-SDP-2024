unsigned int islands(const vector<vector<int>> &g)
{
    unsigned count = 0;
    bool visited[g.size()][g.size()];

    for (size_t i = 0; i < g.size(); i++)
    {
        for (size_t j = 0; j < g.size(); j++)
        {
            visited[i][j] = false;
        }
    }

    for (std::size_t i = 0; i < g.size(); ++i)
    {
        for (std::size_t j = 0; j < g[i].size(); ++j)
        {
            // Check if not visited and if it's land
            if (!visited[i][j] && g[i][j])
            {
                visited[i][j] = true;
                std::queue<std::pair<std::size_t, std::size_t>> landQueue;
                landQueue.push(std::make_pair(i, j));
                while (!landQueue.empty())
                {
                    std::size_t x = landQueue.front().first;
                    std::size_t y = landQueue.front().second;
                    landQueue.pop();

                    // Check neighbours:
                    // 0, -1
                    if (y >= 1 && !visited[x][y - 1] && g[x][y - 1])
                    {
                        visited[x][y - 1] = true;
                        landQueue.push(std::make_pair(x, y - 1));
                    }
                    // -1, 0
                    if (x >= 1 && !visited[x - 1][y] && g[x - 1][y])
                    {
                        visited[x - 1][y] = true;
                        landQueue.push(std::make_pair(x - 1, y));
                    }
                    // 0, +1
                    if (y + 1 < g[x].size() && !visited[x][y + 1] && g[x][y + 1])
                    {
                        visited[x][y + 1] = true;
                        landQueue.push(std::make_pair(x, y + 1));
                    }
                    // +1, 0
                    if (x + 1 < g.size() && !visited[x + 1][y] && g[x + 1][y])
                    {
                        visited[x + 1][y] = true;
                        landQueue.push(std::make_pair(x + 1, y));
                    }
                }
                count++;
            }
        }
    }

    return count;
}