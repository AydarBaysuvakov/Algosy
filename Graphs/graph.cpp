#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

void graph_ctor(Graph* graph, uint vertex_count, uint edge_count, Edge edge_array[]) {
    assert(graph);

    graph->vertex_count = vertex_count;
    graph->edge_count   = 0;
    graph->matrix       = (uint*) calloc(vertex_count * vertex_count, sizeof(uint));

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = i + 1; j < vertex_count; ++j) {
            change_edge(graph, i, j, NO_EDGE);
        }
    }

    if (edge_count) {
        for (int i = 0; i < edge_count; ++i) {
            Edge edge = edge_array[i];
            change_edge(graph, edge.vertex_1, edge.vertex_2, edge.weight);
        }
    }
    graph->edge_count = edge_count;
}

uint get_edge(Graph* graph, int i, int j) {
    assert(graph);

    if (i >= graph->vertex_count || j >= graph->vertex_count) {
        printf("ERROR: vertices in graph - %d; edge has vertices: %d, %d.\n", graph->vertex_count, i, j);
        printf("Вершина ребра имеет номер превышающий количество вершин графа.\n");
        return 0;
    }

    if (i == j) return NO_EDGE;
    return graph->matrix[graph->vertex_count * j + i];
}

void change_edge(Graph* graph, int i, int j, int weight) {
    assert(graph);

    if (i >= graph->vertex_count || j >= graph->vertex_count) {
        printf("ERROR: vertices in graph - %d; edge has vertices: %d, %d.\n", graph->vertex_count, i, j);
        printf("Вершина ребра имеет номер превышающий количество вершин графа.\n");
        return;
    }

    if (i == j) {
        printf("ERROR: edge vertices are equal.\n");
        return;
    }

    if (weight == NO_EDGE) graph->edge_count--;
    if (graph->matrix[graph->vertex_count * j + i] == NO_EDGE) graph->edge_count++;

    graph->matrix[graph->vertex_count * j + i] = weight;
    graph->matrix[graph->vertex_count * i + j] = weight;
}

void graph_dtor(Graph* graph) {
    assert(graph);

    free(graph->matrix);
    free(graph);
}

void show_graph(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; ++i) {
        for (int j = 0; j < graph->vertex_count; ++j) {
            uint edge = get_edge(graph, i, j);
            if (edge == NO_EDGE) printf("M\t");
            else printf("%d\t", edge);
        }
        printf("\n");
    }
    printf("\n");
}


void orgraph_ctor(OrientedGraph* graph, uint vertex_count, uint edge_count, Edge edge_array[]) {
    assert(graph);

    graph->vertex_count = vertex_count;
    graph->edge_count   = 0;
    graph->matrix       = (uint*) calloc(vertex_count * vertex_count, sizeof(uint));

    for (int i = 0; i < vertex_count; ++i) {
        for (int j = 0; j < vertex_count; ++j) {
            if (i == j) continue;
            change_oredge(graph, i, j, NO_EDGE);
        }
    }

    if (edge_count) {
        for (int i = 0; i < edge_count; ++i) {
            Edge edge = edge_array[i];
            change_oredge(graph, edge.vertex_1, edge.vertex_2, edge.weight);
        }
    }
    graph->edge_count = edge_count;
}

uint get_oredge(OrientedGraph* graph, int i, int j) {
    assert(graph);

    if (i >= graph->vertex_count || j >= graph->vertex_count) {
        printf("ERROR: vertices in graph - %d; edge has vertices: %d, %d.\n", graph->vertex_count, i, j);
        printf("Вершина ребра имеет номер превышающий количество вершин графа.\n");
        return 0;
    }

    if (i == j) return NO_EDGE;
    return graph->matrix[graph->vertex_count * i + j];
}

void change_oredge(OrientedGraph* graph, int i, int j, int weight) {
    assert(graph);

    if (i >= graph->vertex_count || j >= graph->vertex_count) {
        printf("ERROR: vertices in graph - %d; edge has vertices: %d, %d.\n", graph->vertex_count, i, j);
        printf("Вершина ребра имеет номер превышающий количество вершин графа.\n");
        return;
    }

    if (i == j) {
        printf("ERROR: edge vertices are equal.\n");
        return;
    }

    if (weight == NO_EDGE) graph->edge_count--;
    if (graph->matrix[graph->vertex_count * i + j] == NO_EDGE) graph->edge_count++;

    graph->matrix[graph->vertex_count * i + j] = weight;
}

void orgraph_dtor(OrientedGraph* graph) {
    assert(graph);

    free(graph->matrix);
    free(graph);
}

void show_orgraph(OrientedGraph* graph) {
    for (int i = 0; i < graph->vertex_count; ++i) {
        for (int j = 0; j < graph->vertex_count; ++j) {
            uint edge = get_oredge(graph, i, j);
            if (edge == NO_EDGE) printf("M\t");
            else printf("%d\t", edge);
        }
        printf("\n");
    }
    printf("\n");
}
