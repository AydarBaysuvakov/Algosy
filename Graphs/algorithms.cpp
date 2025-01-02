#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "algorithms.h"

Graph* Prim(Graph* graph) {
    assert(graph);

    Graph* tree = (Graph*) calloc(1, sizeof(Graph));
    graph_ctor(tree, graph->vertex_count);

    char* vertices = (char*) calloc(graph->vertex_count, sizeof(char));
    memset(vertices, 0, graph->vertex_count);

    vertices[0] = 1;
    uint used_v = 1;

    while (used_v < graph->vertex_count) {
        Edge min_edge = {0, 0, (uint) -1};
        for (int i = 0; i < graph->vertex_count; ++i) {
            if (vertices[i]) {
                for (int j = 0; j < graph->vertex_count; ++j) {
                    if (!vertices[j]) {
                        uint weight = get_edge(graph, i, j);
                        if (weight < min_edge.weight) {
                            min_edge.vertex_1 = i;
                            min_edge.vertex_2 = j;
                            min_edge.weight = weight;
                        }
                    }
                }
            }
        }
        change_edge(tree, min_edge.vertex_1, min_edge.vertex_2, min_edge.weight);
        vertices[min_edge.vertex_2] = 1;
        used_v++;
    }

    free(vertices);
    return tree;
}


Graph* Kruscal(Graph* graph) {
    assert(graph);

    Graph* tree = (Graph*) calloc(1, sizeof(Graph));
    graph_ctor(tree, graph->vertex_count);

    uint* vertices = (uint*) calloc(graph->vertex_count, sizeof(uint));
    memset(vertices, 0, graph->vertex_count);

    Edge* edges = (Edge*) calloc(graph->edge_count, sizeof(Edge));
    uint index = 0;
    for (int i = 0; i < graph->vertex_count; ++i) {
        for (int j = i + 1; j < graph->vertex_count; ++j) {
            uint weight = get_edge(graph, i, j);
            if (weight != NO_EDGE) {
                edges[index].vertex_1 = i;
                edges[index].vertex_2 = j;
                edges[index].weight = weight;
                index++;
            }
        }
    }
    qsort(edges, graph->edge_count, sizeof(Edge), edge_comp);

    uint groups = 0;

    for (uint i = 0; i < graph->edge_count; ++i) {
        Edge curent_edge = edges[i];
        if (vertices[curent_edge.vertex_1] == 0) {
            groups++;
            vertices[curent_edge.vertex_1] = groups;
        }
        if (vertices[curent_edge.vertex_2] != vertices[curent_edge.vertex_1]) {
            change_edge(tree, curent_edge.vertex_1, curent_edge.vertex_2, curent_edge.weight);
            recolor(tree, vertices, curent_edge.vertex_1, vertices[curent_edge.vertex_1]);
        }
    }

    free(vertices);
    free(edges);
    return tree;
}

int edge_comp(const void* a, const void* b) {
    Edge edge_1 = *(const Edge*) a;
    Edge edge_2 = *(const Edge*) b;

    return edge_1.weight - edge_2.weight;
}

void recolor(Graph* tree, uint* vertecies, uint vertex, uint color) {
    assert(tree);

    vertecies[vertex] = color;
    for (int i = 0; i < tree->vertex_count; ++i) {
        if (get_edge(tree, vertex, i) != NO_EDGE && vertecies[i] != color)
            recolor(tree, vertecies, i, color);
    }
}

Dijkstra_edge* Dijkstra(Graph* graph, uint vertex) {
    assert(graph);
    assert(vertex < graph->vertex_count);

    Dijkstra_edge* vertices = (Dijkstra_edge*) calloc(graph->vertex_count, sizeof(Dijkstra_edge));
    for (int i = 0; i < graph->vertex_count; ++i) {
        vertices[i].weight = NO_EDGE;
        vertices[i].vertex = NO_EDGE;
    }

    vertices[vertex].weight = 0;
    vertices[vertex].vertex = vertex;
    uint used_v = 1;

    while (used_v < graph->vertex_count) {
        Edge min_edge = {0, 0, (uint) -1};
        for (int i = 0; i < graph->vertex_count; ++i) {
            if (vertices[i].vertex != NO_EDGE) {
                for (int j = 0; j < graph->vertex_count; ++j) {
                    if (vertices[j].vertex == NO_EDGE) {
                        uint weight = get_edge(graph, i, j);
                        if (weight != NO_EDGE) weight += vertices[i].weight;
                        if (weight < min_edge.weight) {
                            min_edge.vertex_1 = i;
                            min_edge.vertex_2 = j;
                            min_edge.weight = weight;
                        }
                    }
                }
            }
        }
        vertices[min_edge.vertex_2].weight = min_edge.weight;
        vertices[min_edge.vertex_2].vertex = min_edge.vertex_1;
        used_v++;
    }

    return vertices;
}

void show_dijkstra(Dijkstra_edge* array, uint src, uint dest) {
    printf("weight: %d; road: %d ", array[dest].weight, dest);
    uint vertex = array[dest].vertex;
    while (vertex != src) {
        printf("%d ", vertex);
        vertex = array[vertex].vertex;
    }
    printf("%d\n", src);
}

void get_way(Graph* graph, uint src, uint dest) {
    assert(graph);

    Dijkstra_edge* array = Dijkstra(graph, src);
    show_dijkstra(array, src, dest);
    free(array);
}

int Is_cycled(OrientedGraph* graph) {
    assert(graph);

    uint* stack = (uint*) calloc(graph->vertex_count, sizeof(uint));
    int sp = 0;

    char* vertices = (char*) calloc(graph->vertex_count, sizeof(char));
    memset(vertices, 0, graph->vertex_count);

    uint cur_v  = 0;
    do {
        vertices[cur_v] = 1;
        int i;

        for (i = 0; i < graph->vertex_count; ++i) {
            if (get_oredge(graph, cur_v, i) != NO_EDGE) {
                if (vertices[i] == 1 && sp && i != stack[sp - 1]) {
                    printf("Найден цикл\n");
                    free(stack);
                    free(vertices);
                    return 1;
                }
            }
        }
        for (i = 0; i < graph->vertex_count; ++i) {
            if (get_oredge(graph, cur_v, i) != NO_EDGE) {
                if (!vertices[i]) {
                    stack[sp++] = cur_v;
                    cur_v = i;
                    break;
                }
            }
        }
        if (i == graph->vertex_count) {
            vertices[cur_v] = 2;

            cur_v = stack[--sp];
            stack[sp] = 0;
        }
    } while (sp != -1);
    free(stack);
    free(vertices);
    return 0;
}

uint* Sort(OrientedGraph* graph) {
    assert(graph);

    if (Is_cycled(graph)) {
        printf("В графе найден цикл, сортировка невозможна.\n");
        return NULL;
    }

    char* vertices = (char*) calloc(graph->vertex_count, sizeof(char));
    memset(vertices, 0, graph->vertex_count);

    uint* stack_in = (uint*) calloc(graph->vertex_count, sizeof(uint));
    uint spi = 0;

    uint* stack_out = (uint*) calloc(graph->vertex_count, sizeof(uint));
    uint spo = graph->vertex_count - 1;

    uint cur_v  = Find_no_in(graph);
    if (cur_v == -1) return NULL;
    stack_out[0] = cur_v;
    do {
        vertices[cur_v] = 1;
        int i;
        for (i = 0; i < graph->vertex_count; ++i) {
            if (get_oredge(graph, cur_v, i) != NO_EDGE) {
                if (!vertices[i]) {
                    stack_in[spi++] = cur_v;
                    cur_v = i;
                    break;
                }
            }
        }
        if (i == graph->vertex_count) {
            vertices[cur_v] = 2;
            stack_out[spo--] = cur_v;
            cur_v = stack_in[--spi];
        }
    } while (spo != 1);
    free(vertices);
    free(stack_in);
    return stack_out;

}

uint Find_no_in(OrientedGraph* graph) {
    assert(graph);

    for (int i = 0; i < graph->vertex_count; ++i) {
        int count = 0;
        for (int j = 0; j < graph->vertex_count; ++j) {
            if (get_oredge(graph, j, i) != NO_EDGE)
                count++;
        }
        if (count == 0)
            return i;
    }
    printf("Не найдено вершин, в которые не входят ребер, возможно, есть цикл.\n");
    return -1;
}
