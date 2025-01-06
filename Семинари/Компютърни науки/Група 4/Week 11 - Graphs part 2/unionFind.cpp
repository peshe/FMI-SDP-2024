#include <iostream>

int N, M;
int parrent[255];
int depth[255];

int root(int node)
{
    while(parrent[node] != node)
    {
        node = parrent[node];
    }
    return node;
}
bool find(int a, int b)
{
    return root(a) == root(b);
}
void unionF(int a, int b)
{
    if(find(a, b))
    {
        return;
    }
    int rootA = root(a);
    int rootB = root(b);
    if(depth[rootA] > depth[rootB])
    {
        parrent[rootB] = rootA;
    }
    else if(depth[rootA] == depth[rootB])
    {
        parrent[rootB] = rootA;
        depth[rootA]++;
    }
    else
    {
        parrent[rootA] = rootB;
    }
}
int main()
{
    int N, M;
    std::cin >> N >> M;
    int a, b;
    for(int i = 0; i < N; i++)
    {
        parrent[i] = i;
    }
    for(int i = 0; i < M; i++)
    {
        std::cin >> a >> b;
        unionF(a, b);
    }
    int k;
    std::cin >> k;
    for(int i = 0; i < k; i++)
    {
        std::cin >> a >> b;
        std::cout << std::boolalpha << find(a, b) << std::endl;
    }

}