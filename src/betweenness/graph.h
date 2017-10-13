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
  
    // Returns the betweenness value for each vertex.
    std::vector<long double> betweenness();
    
    int nVertices() { return this->nVertices_; }

  private:
    
    // Just an Epsilon value...
    // I use this to make double comparisons.
    const long double EPS = 1e-6;

    int nVertices_;

    // Sigma matrix.
    // It holds the number of paths there exists between every
    // pair of vertices of graph.
    vector<vector<long long int> > vsigma;
    
    // Representation of a weighted graph.
    vector<vector<pair<int, int> > > graph;
    
    // Dependency Matrix.
    vector<vector<long double> > vdependency;

    
    // This function will compute the value of dependency of u,
    // given s.
    long double computeDependency(const vector<vector<int> >& dag,
                                  int s, int u);
    
    // Dijkstra's Algorithm
    // It's ran from vertex s
    // At this function, vsigma is updated.
    vector<vector<int> > dijkstra(int s);
};


#endif
