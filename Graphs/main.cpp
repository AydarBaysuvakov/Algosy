#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algorithms.h"

int main() {

    uint vertex_count = 6;
    uint edge_count   = 10;
    Edge edge_array[10] = {{0, 1, 3},
                           {0, 4, 6},
                           {0, 5, 5},
                           {1, 2, 1},
                           {1, 5, 4},
                           {2, 3, 6},
                           {2, 5, 4},
                           {3, 4, 8},
                           {3, 5, 5},
                           {4, 5, 2}};


    printf("Prim\n");
    Graph* prima_graph = (Graph*) calloc(1, sizeof(Graph));
    graph_ctor(prima_graph, vertex_count, edge_count, edge_array);
    show_graph(prima_graph);
    Graph* tree = Prim(prima_graph);
    show_graph(tree);
    graph_dtor(prima_graph);
    graph_dtor(tree);
    printf("\n-----------------------------------------------------------------------------------------\n");

    printf("Kruscal\n");
    Graph* krusk_graph = (Graph*) calloc(1, sizeof(Graph));
    graph_ctor(krusk_graph, vertex_count, edge_count, edge_array);
    tree = Kruscal(krusk_graph);
    show_graph(tree);
    graph_dtor(krusk_graph);
    graph_dtor(tree);
    printf("\n-----------------------------------------------------------------------------------------\n");

    printf("Dijkstra\n");
    Graph* dijkstr_graph = (Graph*) calloc(1, sizeof(Graph));
    graph_ctor(dijkstr_graph, vertex_count, edge_count, edge_array);
    for (int i = 0; i < vertex_count; ++i) get_way(dijkstr_graph, 1, i);
    graph_dtor(dijkstr_graph);
    printf("\n-----------------------------------------------------------------------------------------\n");

    printf("Sorting oriented graph\n");
    OrientedGraph* graph2 = (OrientedGraph*) calloc(1, sizeof(OrientedGraph));
    uint edge_count2   = 7;
    uint vertex_count2 = 5;
    Edge edge_array2[7] = {{0, 1, 1},
                           {0, 3, 1},
                           {0, 4, 1},
                           {1, 4, 1},
                           {2, 0, 1},
                           {2, 1, 1},
                           {3, 4, 1}};

    orgraph_ctor(graph2, vertex_count2, edge_count2, edge_array2);
    show_orgraph(graph2);
    uint* sorted = Sort(graph2);
    if (sorted) {
        for (int i = 0; i < graph2->vertex_count; ++i)
            printf("%d ", sorted[i]);
    }
    printf("\n-----------------------------------------------------------------------------------------\n");
    free(sorted);
    orgraph_dtor(graph2);
}
