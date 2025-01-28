// Class to handle graphs and operations that are done on them
// By  Gia Berekashvili
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>
#include <climits>
#include <set>
#include "DisjointSet.h"
using namespace std;

class Graph
{
    private:
        int numNodes;
        vector<list<pair<int, int>>> adjList;
        map<string, int> nodeNameToIndex;
        vector<string> indexToNodeName;

        int getNodeIndex(const string& name) const;
        void resetGraph();

    public:
        Graph();

        bool readGraph(const string& txtFile);

        void printGraph() const;

        void computeTopologicalSort() const;

        void computeShortestPaths(const string& startNode) const;

        void computeMinimumSpanningTree() const;

    private:

};

#endif