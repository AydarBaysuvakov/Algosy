#ifndef GRAPH
#define GRAPH

const uint NO_EDGE = (uint) -1;

struct Graph {
    uint  vertex_count;
    uint  edge_count;
    uint* matrix;
};

struct OrientedGraph {
    uint  vertex_count;
    uint  edge_count;
    uint* matrix;
};

struct Edge {
    uint vertex_1;
    uint vertex_2;
    uint weight;
};

void graph_ctor(struct Graph* graph, uint vertex_count, uint edge_count = 0, struct Edge edge_array[] = NULL);
void graph_dtor(struct Graph* graph);

void change_edge(struct Graph* graph, int i, int j, int weight);
uint get_edge(struct Graph* graph, int i, int j);
void show_graph(Graph* graph);

void orgraph_ctor(struct OrientedGraph* graph, uint vertex_count, uint edge_count = 0, struct Edge edge_array[] = NULL);
void orgraph_dtor(struct OrientedGraph* graph);

void change_oredge(struct OrientedGraph* graph, int i, int j, int weight);
uint get_oredge(struct OrientedGraph* graph, int i, int j);
void show_orgraph(OrientedGraph* graph);

#endif //GRAPH
