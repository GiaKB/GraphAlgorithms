This README helps the user understand how to run and interpret this code.
To compile, the files TextMenu.cpp, DisjointSet.cpp, Graph.cpp, and graphRunner.cpp must be compiled together.

From here, you are asked to input the name of a graph from a .txt file. Example files are included, but if you are looking to create your own graph, the general format is as such:

Number of nodes
Node1
Node2
Until NodeN, where N is the total number of nodes
Number of connections between nodes
Connection 1, formatted as FROM NODE space TO NODE space WEIGHT "\n"
Connection 2
Until ConnectionX, where X is the total number of connections on the graph

Once a graph has been successfully read, you are able to do a few operations.
1. Reading another graph - You are able to switch which graph you're working with by using this function.
2. Printing the graph - This function allows the graph to be printed in the same format as it was read in.
3. Topological Sort - Assuming the graph can be topologically sorted, this function will return a topological sort of the graph in the format NodeA  --> NodeB --> NodeC and so on. If the graph cannot be topologically sorted, a message will be printed to the console saying so.
4. Shortest Paths - This function allows for you to compute the shortest possible path to all nodes from an inputted starting node. The path is formatted in the same way that the topological sort is, but if the graph is weighted, this path is followed by "|| Weight: " and the weight of the path.
5. Minimum Spanning Tree - This function utilizes Kruskal's algorithm along with disjoint sets to compute the minimum spanning tree for the inputted graph.
6. Exit - This function ends the program with a goodbye message.
