#include <iostream>
#include <algorithm>
#include <vector>

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
struct Edge
{
    int a, b;
    int weight;
};
int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<Edge> listOfEdges;
    int a, b, c;
    for(int i = 0; i < N; i++)
    {
        parrent[i] = i;
    }
    for(int i = 0; i < M; i++)
    {
        std::cin >> a >> b >> c;
        Edge tmp;
        tmp.a = a;
        tmp.b = b;
        tmp.weight = c;

        listOfEdges.push_back(tmp);
        
    }

    for(int i = 0; i < listOfEdges.size(); i++)
    {
        for(int j = i + 1; j < listOfEdges.size(); j++)
        {
            if(listOfEdges[i].weight > listOfEdges[j].weight)
            {
                std::swap(listOfEdges[i], listOfEdges[j]);
            }
        }
    }

    std::vector<Edge> minimalSpaningTree;
    for(Edge i : listOfEdges)
    {
        if(!find(i.a, i.b))
        {
            unionF(i.a, i.b);
            minimalSpaningTree.push_back(i);
        }
    }

    for(Edge i : minimalSpaningTree)
    {
        std::cout << i.a << " " << i.b << " " << i.weight << std::endl;
    }

}