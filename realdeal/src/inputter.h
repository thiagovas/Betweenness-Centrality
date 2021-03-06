// The Inputter class just serves to read the input.
//
// It is useful, since the vertices of the input graph, not
// necessarily is a permutation of n, n being the number
// of vertices of the graph.

#ifndef _inputter_h
#define _inputter_h

#include <map>

#include "graph.h"

class Inputter {
  public:
    
    // Inputter Constructor
    Inputter();
    
    // This function just serves to read the input and returns the graph.
    Graph readInput();
   
    int getVertexId(int permutationIndex);

  private:
    
    // It maps the integer received from the input to the
    // permutation defined by me.
    std::map<int, int> inputtoperm;
    
    // It maps the vertices id from the permutation defined by me
    // to the integer received from the input.
    std::map<int, int> permtoinput;
    
    // This variable keeps the number of vertices of the graph.
    int nVertices;
    
    // This function create a new entry on the inputtoperm and
    // permtoinput maps.
    void mapvertex(int u);
};

#endif
