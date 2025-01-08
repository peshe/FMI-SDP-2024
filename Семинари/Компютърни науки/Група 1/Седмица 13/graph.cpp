#include "graph.h"
#include <limits.h>
using namespace std;
Graph::Graph(){}
void Graph::addEdge(const string& from, const string& to, int weight,bool oriented = false){
    graph[from].push_back({from,to,weight});
    if(!oriented)
        graph[to].push_back({to,from,weight});
    if(!graph.count(to))graph.insert({to,{}});//ако връх до който има ребро не е записан в графа го добавяме
}
void Graph::addEdge(EdgeString edge,bool oriented = false){
    graph[edge.from].push_back(edge);
    if(!oriented)
        graph[edge.dest].push_back({edge.dest,edge.from,edge.weight});
}

void Graph::deserialise(istream& in){
    int N,M,weight;
    string from,to;
    in>>N>>M;
    for(int i = 0; i<M; i++){
        in>>from>>to>>weight;
        addEdge(from,to,weight);
        // addEdge(to,from,weight);// if the graph is not oriented
    }
}
void Graph::serialise(ostream& out)const{
    int N = graph.size(),M=0; 
    for(pair<string, vector<EdgeString>> it:graph)
        M+=it.second.size();
    out<<N<<" "<<M<<endl;
    for(pair<string, vector<EdgeString>> it:graph){
        for(EdgeString edge:it.second){
            out<<it.first<<" "<<edge.dest<<" "<<edge.weight<<endl;
        }
    }   
}

Graph::NodesList Graph::DFS(const string &start) const
{
    unordered_set<string> used;
    NodesList res;
    DFS_Helper(start,used,res);
    return res;
}
void Graph::DFS_Helper(const string &curr,
                       unordered_set<string>& used,
                       NodesList& res) const{
    used.insert(curr);
    res.push_back(curr);
    if(!graph.count(curr))
        throw invalid_argument(curr+" is not found in the graph");
    for(EdgeString edge:graph.at(curr)){
        if(!used.count(edge.dest))
            DFS_Helper(edge.dest,used,res);
    }
}


Graph::NodesList Graph::BFS(const string &start) const
{
    queue<string> que;
    unordered_set<string> used;
    NodesList res;

    string curr;
    que.push(start);

    while(!que.empty()){
        curr=que.front();
        que.pop();
        if(used.count(curr))
            continue;

        if(!graph.count(curr))
            throw invalid_argument(curr+" is not found in the graph");
        
        used.insert(curr);
        res.push_back(curr);
        for(EdgeString edge:graph.at(curr))
            que.push(edge.dest);
    }
    return res;
}

/*

priority_queue<type,container,comp> - max-heap по подразбиране

comp може да бъде:
-структура със дефиниран оператор() приемащ два обекта от типа на опашката
-ламба функция приемаща два обека от типа на опашката 

priority_queue<type>
може и да се дефинира само оператор < във класа(можем да го имплементираме като > за да постигне min-heap)  

*/

template <typename T>
struct EdgeCompare{
    bool operator()(const T& A,const T& B){
        return A.weight>B.weight;
    }
};

Graph::DistancesType Graph::Dijkstra(const string& start)const{
    typedef Graph::EdgeString Checkpoint;
    
    Graph::DistancesType res;
    unordered_set<string> used;
    unordered_map<string,int>dist;
    priority_queue<Checkpoint,
                        vector<Checkpoint>,
                        EdgeCompare<Checkpoint> > que;
    
    for(pair<string, vector<EdgeString>> node:graph){
        dist[node.first]=INT_MAX;
    }
    dist[start]=0;

    que.push({start,start,0});
    Checkpoint curr;
    while(!que.empty()){
        curr = que.top();
        que.pop();
        if(used.count(curr.dest))continue;

        used.insert(curr.dest);
        res.insert({{start,curr.dest},curr.weight});

        for(EdgeString edge:graph.at(curr.dest)){
            if(!used.count(edge.dest) && dist[edge.dest] > dist[curr.dest] + edge.weight){
                dist[edge.dest] = dist[curr.dest] + edge.weight;
                que.push({curr.dest, edge.dest, dist[edge.dest]});
            }
        }
    }
    return res; 
}

Graph::DistancesType Graph::BellmanFord(const std::string &start) const{
    Graph::DistancesType res;
    unordered_map<string,int>dist;
    for(pair<string, vector<EdgeString>> node:graph){
        dist[node.first]=INT_MAX;
    }
    dist[start]=0;
    res[{start,start}] = 0;
    for(int i =0;i<graph.size()-1;i++){
        for(pair<string, vector<EdgeString>> node:graph){
            for(EdgeString edge:node.second){
                if(dist[edge.from]+edge.weight < dist[edge.dest])
                    dist[edge.dest] = dist[edge.from]+edge.weight;
            }
        }   
    }
    for(pair<string, vector<EdgeString>> node:graph)
        res[{start,node.first}] = dist[node.first];
    // for(pair<string, vector<EdgeString>> node:graph){    Намиране на отрицателни цикли
    //     for(EdgeString edge:node.second){
    //         if(dist[edge.from]+edge.weight < dist[edge.dest])
    //             //negative cycle detected
    //     }
    // }   
    return res;
}

Graph::DistancesType Graph::FloydWarshall() const
{
    Graph::DistancesType res;
    for(pair<string, vector<EdgeString>> start:graph){
        for(pair<string, vector<EdgeString>> end:graph)
            res[{start.first,end.first}] = INT_MAX;
    }
    for(pair<string, vector<EdgeString>> start:graph)
            res[{start.first,start.first}] = 0;

    for(pair<string, vector<EdgeString>> node:graph)
            for(EdgeString edge:node.second)
                res[{node.first, edge.dest}] = edge.weight;

    for(pair<string, vector<EdgeString>> k:graph)
        for(pair<string, vector<EdgeString>> i:graph)
            for(pair<string, vector<EdgeString>> j:graph)
                res[{i.first,j.first}] = min(res[{i.first,j.first}],res[{i.first,k.first}] + res[{k.first,j.first}]);


    // for (const auto& node : graph) {     Намиране на отрицателни цикли
    //     if (res[{node.first, node.first}] < 0) {
    //         // Negative cycle detected
    //     }
    // }
    return res;
}

Graph Graph::Prim() const
{   
    Graph res;
    unordered_set<string> used;
    unordered_map<string,int>dist;
    priority_queue<EdgeString,
                        vector<EdgeString>,
                        EdgeCompare<EdgeString> > que;

    if(graph.empty())return res;
    string start =(*graph.begin()).first; 

    EdgeString curr;
    que.push({start,start,0});
    while(!que.empty()){
        curr = que.top();
        que.pop();

        if(used.count(curr.dest))continue;

        used.insert(curr.dest);
        if(start != curr.dest){
            res.addEdge(curr,false);
        }

        for(EdgeString edge:graph.at(curr.dest)){
            if(!used.count(edge.dest)){
                
                que.push({curr.dest, edge.dest, edge.weight});
            }
        }
    }
    return res;
}

bool cmpEdges(const Graph::EdgeString& A, const Graph::EdgeString& B){
    return A.weight<B.weight;
}

string Find(const string& curr,unordered_map<string,string>& parents){
    if(parents[curr] == curr)
        return curr;
    return parents[curr] = Find(parents[curr],parents);
}

void Union(const string& A,const string& B,unordered_map<string,string>& parents,unordered_map<string,int>& ranks){
    string p1 = Find(A,parents);
    string p2 = Find(B,parents);

    if(p1 == p2)return;
    if(ranks[p1]<ranks[p2])
        parents[p1] = p2;
    else if(ranks[p1]>ranks[p2])
        parents[p2] = p1;
    else {
        parents[p1] = p2;
        ranks[p2]++;
    }
}

Graph Graph::Kruskal() const
{
    unordered_map<string,string> parent;
    unordered_map<string, int>rank;
    vector<EdgeString> edges;
    Graph res;

    for(pair<string,vector<EdgeString>> node:graph){
        edges.insert(edges.end(), node.second.begin(), node.second.end());
        rank[node.first] = 0;
        parent[node.first] = node.first;
    }
    sort(edges.begin(),edges.end(),cmpEdges);
    int N = graph.size();
    int count = 0;
    for(EdgeString edge :edges){
        
        if(Find(edge.from,parent) != Find(edge.dest,parent)){
            Union(edge.from,edge.dest,parent,rank);
            res.addEdge(edge,false);
            count++;
        }

        if(count == N-1)
            break;
    }
    return res;
}

Graph::NodesList Graph::TopologicalSort() const //Алгоритъм на Кан
{
    // if(hasCycle())
    //     throw logic_error("Cannot topologicaly sort a graph which contains cycles");
    NodesList res;
    unordered_map<string,int>incoming;
    for(pair<string, vector<EdgeString>> node:graph){
        incoming[node.first]=0;
    }
    for(pair<string, vector<EdgeString>> node:graph)
            for(EdgeString edge:node.second)
                incoming[edge.dest]++;
    
    queue<string> que;
    for(pair<string,int> i : incoming)
        if(!i.second)
            que.push(i.first);
    string curr;
    while(!que.empty()){
        curr = que.front();
        que.pop();
        res.push_back(curr);
        
        for(EdgeString edge:graph.at(curr)){
            incoming[edge.dest]--;
            if(!incoming[edge.dest])
                que.push(edge.dest);
        }
    }
    if (res.size() != graph.size()) {
        throw logic_error("Cannot topologicaly sort a graph which contains cycles");
    }

    return res;
}

bool Graph::hasCycle() const
{
    unordered_set<string> used;
    for(pair<string, vector<EdgeString>> start:graph)
        if(!used.count(start.first)&&Cycle_Helper(start.first,used))
            return true;
}

bool Graph::Cycle_Helper(const string &curr,unordered_set<string>& used) const{
    if(used.count(curr))return true;
    
    used.insert(curr);
    if(!graph.count(curr))
        throw invalid_argument(curr+" is not found in the graph");
    for(EdgeString edge:graph.at(curr)){
        if(Cycle_Helper(edge.dest,used))return true;
    }
    return false;
}

