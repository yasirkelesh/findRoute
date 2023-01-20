#ifndef ROUTE_FIND_H
#define ROUTE_FIND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define MAX_NODES 100

typedef struct {
    double x;
    double y;
    int index;
    int g; // g değeri, başlangıç düğümünden bu düğüme olan gerçek mesafeyi temsil eder
    int h; // h değeri, bu düğümden hedef düğüme olan tahmini mesafeyi temsil eder
    int f; // f değeri, g + h değerlerinin toplamını temsil eder
    double yaw;
    struct Node *prev;
} Node;

typedef struct {
    int length;
    int cost;
    Node *path[MAX_NODES];
} Route;

typedef struct {
    int numNodes;
    Node nodes[MAX_NODES];
    int numEdges;
    int edges[MAX_NODES][MAX_NODES];
} MapData;

// Uçak veri yapısı
typedef struct
{
    double x;   // Uçak konumu x koordinatı
    double y;   // Uçak konumu y koordinatı
    double yaw; // Uçak yönü (radyan cinsinden)
} UAV;

int heuristic(Node *n, Node *end);
Route aStar(MapData *map, Node *start, Node *end);
void initNodes(MapData *map);
bool isInList(Node *node, Node *list[], int size);
int getNodeIndex(Node *node, Node *list[], int size);
double yaw(double uav_x, double uav_y, double hedef_x,double hedef_y);
UAV uav_path(UAV uav, Route rota, int i);
#endif