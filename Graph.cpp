// Implementation file for Graph class
// By Gia Berekashvili

#include "Graph.h"

using namespace std;

Graph::Graph() : numNodes(0) {}

// This private method is executed when we read in another graph. Resets everything, including number of nodes, adjadency list, and our two node to index relationship vectors.
void Graph::resetGraph()
{
    numNodes = 0;
    adjList.clear();
    nodeNameToIndex.clear();
    indexToNodeName.clear();
}

// This method gets our node index by using our disjoint set class.
int Graph::getNodeIndex(const string &name) const
{
    auto i = nodeNameToIndex.find(name);
    if (i!=nodeNameToIndex.end())
    {
        return i->second;
    }
    else
    {
        return -1;
    }
}

// This method reads the graph from the textfile. Returns false if the file can't be read, and true otherwise.
bool Graph::readGraph(const string &txtFile)
{
    ifstream file(txtFile);
    if (!file.is_open())
    {
        return false;
    }

    resetGraph();

    file >> numNodes;
    indexToNodeName.resize(numNodes);
    adjList.resize(numNodes);

    for (int i = 0; i<numNodes; ++i)
    {
        file >> indexToNodeName[i];
        nodeNameToIndex[indexToNodeName[i]] = i;
    }

    int numEdges;
    file >> numEdges;
    string from, to;
    int weight;
    for (int i = 0; i < numEdges; ++i)
    {
        file >> from >> to >> weight;
        int fromIndex = getNodeIndex(from);
        int toIndex = getNodeIndex(to);
        if (fromIndex != -1 && toIndex != -1)
        {
            adjList[fromIndex].emplace_back(toIndex, weight);
        }
    }

    return true;
}

// This method prints the graph in the same format as the read-in graph.
void Graph::printGraph() const
{
    cout<<numNodes<<"\n";

    for (const string& node : indexToNodeName)
    {
        cout<<node<<"\n";
    }

    vector<tuple<string, string, int>> edges;

    for (int from = 0; from<numNodes; from++)
    {
        for (const auto &edge : adjList[from])
        {
            int to = edge.first;
            int weight = edge.second;

            string nodeFrom = indexToNodeName[from];
            string nodeTo = indexToNodeName[to];

            edges.emplace_back(nodeFrom, nodeTo, weight);
        }
    }

    cout<<edges.size()<<"\n";

    for (const auto&[from, to, weight] : edges)
    {
        cout<<from<<" "<<to<<" "<<weight<<"\n";
    }
}

// This method performs a topological sort of the graph using the techniques we learned in class.
void Graph::computeTopologicalSort() const
{
    vector<int> inDegree(numNodes, 0);
    for (const auto& edges : adjList)
    {
        for (const auto& edge : edges)
        {
            inDegree[edge.first]++;
        }
    }

    queue<int> q;
    for (int i = 0; i<numNodes; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topOrder;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topOrder.push_back(node);

        for (const auto& edge : adjList[node])
        {
            if (--inDegree[edge.first] == 0)
            {
                q.push(edge.first);
            }
        }
    }

    if (topOrder.size() == numNodes)
    {
        for (int index : topOrder)
        {
            cout<<indexToNodeName[index];
            if (index!=topOrder.size()-1)
            {
                cout<<" --> ";
            }
        }
        cout<<"\n";
    }
    else
    {
        cout<<"This graph cannot be topologically sorted.\n";
    }
}

// This method computes the shortest path to all vertices from a starting vertex. If a path can't be found, we print out a statement saying so.
void Graph::computeShortestPaths(const string &startNode) const
{
    int startIndex = getNodeIndex(startNode);
    if (startIndex==-1)
    {
        cout<<"Start node "<<startNode<<" not found in the graph.\n";
        return;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    vector<int> distances(numNodes, INT_MAX);
    vector<int> previous(numNodes, -1);

    distances[startIndex] = 0;
    pq.emplace(0, startIndex);

    while (!pq.empty())
    {
        auto [currentDistance, currentIndex] = pq.top();
        pq.pop();

        if (currentDistance > distances[currentIndex])
        {
            continue;
        }

        for (const auto &edge : adjList[currentIndex])
        {
            int neighborIndex = edge.first;
            int weight = edge.second;

            int newDistance = currentDistance + weight;
            if (newDistance<distances[neighborIndex])
            {
                distances[neighborIndex] = newDistance;
                previous[neighborIndex] = currentIndex;
                pq.emplace(newDistance, neighborIndex);
            }
        }
    }

    cout<<"Shortest paths from "<<startNode<<":\n";
    for (int i = 0; i<numNodes; i++)
    {
        if (i==startIndex)
        {
            continue;
        }
        if (distances[i]==INT_MAX)
        {
            cout<<"No path from "<<startNode<<" to "<<indexToNodeName[i]<<" found.\n";
        }
        else
        {
            vector<string> path;
            for (int at = i; at!=-1; at=previous[at])
            {
                path.push_back((indexToNodeName[at]));
            }
            reverse(path.begin(), path.end());

            for (int j = 0; j<path.size(); j++)
            {
                cout<<path[j];
                if (j<path.size()-1)
                {
                    cout<<" --> ";
                }
            }
            cout<<" || Weight: "<<distances[i]<<"\n";
        }
    }
}

// This method computes the minimum spanning tree of the graph using Kruskal's algorithm.
void Graph::computeMinimumSpanningTree() const
{
    vector <tuple<int, int, int>> edges;
    for (int from = 0; from<numNodes; from++)
    {
        for (const auto &edge : adjList[from])
        {
            int to = edge.first;
            int weight = edge.second;

            if (from<to)
            {
                edges.emplace_back(weight, from, to);
            }
        }
    }

    sort(edges.begin(), edges.end());

    DisjointSet ds(numNodes);

    vector <tuple<int, int, int>> mstEdges;
    int totalWeight = 0;

    for (const auto &[weight, from, to] : edges)
    {
        if (ds.find(from) != ds.find(to))
        {
            ds.doUnion(from, to);
            mstEdges.emplace_back(from, to, weight);
            totalWeight+=weight;
        }
    }

    for (const auto &[from, to, weight] : mstEdges)
    {
        cout<<indexToNodeName[from]<<" -- "<<indexToNodeName[to]<<" || Weight: "<<weight<<"\n";
    }
    cout<<"Total Cost: "<<totalWeight<<"\n";
}