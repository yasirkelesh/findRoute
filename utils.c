#include "route_find.h"

int heuristic(Node *n, Node *end)
{
    // Manhattan distance kullanılır
    double dx = fabs(end->x - n->x);
    double dy = fabs(end->y - n->y);
    return dx + dy;
}

void initNodes(MapData *map)
{
    for (int i = 0; i < map->numNodes; i++)
    {
        map->nodes[i].g = INT_MAX;
        map->nodes[i].prev = NULL;
    }
}

bool isInList(Node *node, Node *list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (node == list[i])
        {
            return true;
        }
    }
    return false;
}

int getNodeIndex(Node *node, Node *list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (node == list[i])
        {
            return i;
        }
    }
    return -1;
}
double yaw(double uav_x, double uav_y, double hedef_x, double hedef_y)
{
    double xDiff = hedef_x - uav_x;
    double yDiff = hedef_y - uav_y;
    return atan2(yDiff, xDiff);
}

UAV uav_path(UAV uav, Route rota, int i)
{

    double yon_degisimi;

    // UAV'nin hedef noktaya bakması için gerekli olan yön değiştirme miktarını hesapla
    yon_degisimi = yaw(uav.x, uav.y, rota.path[i]->x, rota.path[i]->y) - uav.yaw;
    // UAV'nin yaw değerini güncelle
    uav.yaw += yon_degisimi;

    return uav;
}