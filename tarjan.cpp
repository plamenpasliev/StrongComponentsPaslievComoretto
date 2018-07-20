#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <stack>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <time.h>

struct node_properties {
  int component;
};
struct edge_properties {
};
struct graph_properties {
  int number_of_components;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    node_properties, edge_properties, graph_properties>          graph_t;
typedef typename boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef typename boost::graph_traits<graph_t>::edge_descriptor   edge_t;

std::stack<int> S;
int inde=0;
int c=0;
graph_t graph;

//Algorithm 1 from "On finding the strongly connected components in a Directed Graph" - E. Nuutila  
void visit(int v, bool visited[], int root[], bool inComponent[]) {
    root[v]=v;
	visited[v] = true;
	inComponent[v] = false;
	S.push(v);
    auto edges = boost::edges(graph);
    
    int w;
	for (auto it = edges.first; it != edges.second; ++it) {

        if(v==boost::source(*it,graph)){	
             w=boost::target(*it,graph);

        	if (!visited[w]) {
        		visit(w, visited, root, inComponent);
        	}
        	if (!inComponent[w]) {
        		root[v] = std::min(root[v],root[w]);
        	}

        }
	}

	if (root[v]==v) {
		while (v!=w) {
		    w = S.top();
			S.pop();
			inComponent[w] = true;
		}
	}
}


//This method generates a graph with v number of vertices and no edges.
graph_t notConnected(int v){
    graph_t connectedGraph;
    std::vector<vertex_t> verticesConnected;
    // We add v vertices and no edges
    for(int i=0; i<v; i++){
        verticesConnected.push_back(boost::add_vertex(connectedGraph));
    }
    
    return connectedGraph;
} 


//This method generates a graph with v number of vertices and edges from every vertex to every other vertex.
graph_t fullyConnected(int v){
    graph_t connectedGraph;
    std::vector<vertex_t> verticesConnected;
    
    //First we add v vertices
    for(int i=0; i<v; i++){
        verticesConnected.push_back(boost::add_vertex(connectedGraph));
    }
    //Then we add edges from every vertex to every other vertex
    for(int m=0; m<v; m++){
        for(int n=0; n<v; n++){
            if(n!=m){
                boost::add_edge(verticesConnected.at(m), verticesConnected.at(n), connectedGraph);
            }
        }
    }
    return connectedGraph;
} 

//This method generates a graph in which every vertex has an edge to the vertex after him, thus forming a circle. 
graph_t circularGraph(int v){
    graph_t connectedGraph;
    std::vector<vertex_t> verticesConnected;

    //First we add v vertices
    for(int i=0; i<v; i++){
        verticesConnected.push_back(boost::add_vertex(connectedGraph));
    }
    //Then we connect every v vertex with its successor v+1
    for(int m=0; m<v-1; m++){
        boost::add_edge(verticesConnected.at(m), verticesConnected.at(m+1), connectedGraph);
    }
    
    //We also connect the last vertex with the initial root vertex 0. 
    boost::add_edge(verticesConnected.at(v-1), verticesConnected.at(0), connectedGraph);

    return connectedGraph;
} 

//This method generates a graph with v vertices and e number of edges randomly distributed among vertices. 
graph_t randomGraph(int v, int e){
    graph_t connectedGraph;
    std::vector<vertex_t> verticesConnected;
    
    //First we add v vertices
    for(int i=0; i<v; i++){
        verticesConnected.push_back(boost::add_vertex(connectedGraph));
    }
    //Then we add e edges going from a random vertex to another random vertex
    srand(time(NULL));
    for(int m=0; m<e; m++){
        boost::add_edge(verticesConnected.at(rand() % v), verticesConnected.at(rand() % v), connectedGraph);
    }
    
    return connectedGraph;
} 

int main() {

  graph = randomGraph(10, 20);
  
  int size_vert=boost::num_vertices(graph);
  bool visited [size_vert];
  int root [size_vert];
  bool inComponent [size_vert];
  
  for (int v=0; v<size_vert; ++v) {
        visited[v]=false;
  }
        
  for (int v=0; v<size_vert; ++v) {
    if(visited[v]==false) {
        visit(v, visited, root, inComponent);
    }
  }
  for (int v=0; v<size_vert;v++) {
      std::cout << "vertex " << v << " in component " << root[v]<<"\n";
  }
  return 0; 
}







