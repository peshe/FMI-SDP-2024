#pragma once

#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Graph{
    public:
    typedef map<pair<string,string>,int > DistancesType;
    typedef vector<string> NodesList;
    
    private:
    struct EdgeString{
        string from;
        string dest;
        int weight;
    };
    struct EdgeInt{
        int dest;
        int weight;
    };

    
    void DFS_Helper(const string &start, unordered_set<string>& used, Graph::NodesList& res) const;
    bool Cycle_Helper(const string &curr,unordered_set<string>& used) const;

    
    // vector< vector<EdgeInt> > graph; // претеглен граф с върхове числа
    // vector< vector<int> > graph; // непретеглен граф с върхове числа
    
    // unordered_map<string, vector<string> > graph;// непретеглен грап с върхове низове
    unordered_map<string, vector<EdgeString> > graph;// претеглен граф с върхове низове
    
    public:
    Graph();
    void addEdge(const string& from, const string& to, int weight,bool oriented);
    void addEdge(EdgeString edge,bool oriented);

    void deserialise(istream& in) ;
    void serialise(ostream& out)const ;

    NodesList DFS(const string& start)const ;
    NodesList BFS(const string& start)const ;
    DistancesType Dijkstra(const string& start)const ;
    DistancesType BellmanFord(const string& start)const ;
    DistancesType FloydWarshall()const ;
    
    Graph Prim()const ;
    Graph Kruskal()const;
    
    NodesList TopologicalSort()const ;
    bool hasCycle()const ;

    friend bool cmpEdges(const EdgeString& A, const EdgeString& B);
};

#endif