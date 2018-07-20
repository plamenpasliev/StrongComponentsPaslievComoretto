#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <stack>
#include <iostream>
#include <vector>

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

bool visited [6];
int root [6];
bool inComponent [6];
std::stack<int> S;
int inde=0;
int c=0;
graph_t graph;
	
void print_graph(const graph_t &graph) {
  std::cout << "Graph:" << std::endl;
  auto edges = boost::edges(graph);
  for (auto it = edges.first; it != edges.second; ++it) {
    std::cout << boost::source(*it, graph) << " -> "
              << boost::target(*it, graph) << std::endl;
  }
}

void visit(int v) {
    root[v]=v;
	visited[v] = true;
	inComponent[v] = false;
	
    auto edges = boost::edges(graph);
    int w;
	for (auto it = edges.first; it != edges.second; ++it) {
     
        if(v==boost::source(*it,graph)){	
             w=boost::target(*it,graph);
             std::cout << v << root[v]<< w << root[w] << "\n";

        	if (!visited[w]) {
        		visit(w);
        	}
        	if (!inComponent[w]) {
        		root[v] = std::min(root[v],root[w]);
        	}
        	std::cout << v << root[v]<< w << root[w] << "\n";

        }
	}

	if (root[v]==v) {
	    inComponent[v] = true;

		while (S.top() > v) {
		    w = S.top();
			S.pop();
			inComponent[w] = true;
			std::cout << w << "\n";
		}
	} else {
	    S.push(v);
	}
}



int main() {

  std::vector<vertex_t> vertices;
  
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));

  boost::add_edge(vertices.at(4), vertices.at(2), graph);
  boost::add_edge(vertices.at(0), vertices.at(1), graph);
  boost::add_edge(vertices.at(1), vertices.at(2), graph);
  boost::add_edge(vertices.at(2), vertices.at(0), graph);
  boost::add_edge(vertices.at(3), vertices.at(4), graph);
  boost::add_edge(vertices.at(4), vertices.at(3), graph);

  int size_vert=boost::num_vertices(graph);
  S.push(-1);

  for (int v=0; v<size_vert; ++v) {
        visited[v]=false;
  }
        
  for (int v=0; v<size_vert; ++v) {
    if(visited[v]==false) {
        visit(v);
    }
  }
  for (int v=0; v<size_vert;v++) {
      std::cout << v << " in comp " << root[v]<<"\n";
  }
  return 0; 
}







