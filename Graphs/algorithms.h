#ifndef ALG
#define ALG

struct Dijkstra_edge {
    uint weight;
    uint vertex;
};

Graph* Prim(Graph* graph);
Graph* Kruscal(Graph* graph);
Dijkstra_edge* Dijkstra(Graph* graph, uint vertex);

int edge_comp(const void* a, const void* b);
void recolor(Graph* tree, uint* vertecies, uint vertex, uint color);

void show_dijkstra(Dijkstra_edge* array, uint src, uint dest);
void get_way(Graph* graph, uint src, uint dest);

uint* Sort(OrientedGraph* graph);
uint Find_no_in(OrientedGraph* graph);
int Is_cycled(OrientedGraph* graph);

#endif //ALG
