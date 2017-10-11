#ifndef _graph_h
#define _graph_h

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Graph {
  public:
    
    // Constructor of graph.
    // Receives the number of vertices the graph will have.
    Graph(int nVertices);
    
    // This function add a new undirected edge.
    // An edge between u anv v with cost c.
    void addEdge(int u, int v, int c);
  
    // This function computes the sigma matrix.
    // Remembering that is the same sigma defined by Brandes.
    void computeSigma();

  private:
    
    int nVertices_;

    // Sigma matrix.
    // It holds the number of paths there exists between every
    // pair of vertices of graph.
    vector<vector<long long int> > vsigma;
    
    // Representation of a weighted graph.
    vector<pair<int, int> > graph;
    
    // This function will compute the value of dependency of u,
    // given s.
    void computeDependency(int s, int u);
};


#endif
