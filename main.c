#include  "route_find.h"

int main()
{
    MapData map = {0};

    // Harita veri yapısını oluşturun ve doldurun. Örnek olarak, 3 düğüm ve 2 kenar kullanacağım
    map.numNodes = 11;
    map.nodes[0].x = 0;
    map.nodes[0].y = 0;
    map.nodes[0].index = 0;
    map.nodes[1].x = 6;
    map.nodes[1].y = 1;
    map.nodes[1].index = 1;
    map.nodes[2].x = 10;
    map.nodes[2].y = 3;
    map.nodes[2].index = 2;
    map.nodes[3].x = 14;
    map.nodes[3].y = 2;
    map.nodes[3].index = 3;
    map.nodes[4].x = 13;
    map.nodes[4].y = 5;
    map.nodes[4].index = 4;
    map.nodes[5].x = 6;
    map.nodes[5].y = 14;
    map.nodes[5].index = 5;
    map.nodes[6].x = 5;
    map.nodes[6].y = 5;
    map.nodes[6].index = 6;
    map.nodes[7].x = 10;
    map.nodes[7].y = 5;
    map.nodes[7].index = 7;
    map.nodes[8].x = 11;
    map.nodes[8].y = 8;
    map.nodes[8].index = 8;
    map.nodes[9].x = 11;
    map.nodes[9].y = 11;
    map.nodes[9].index = 9;
    map.nodes[10].x = 10;
    map.nodes[10].y = 7;
    map.nodes[10].index = 10;



    map.numEdges = 14;
    map.edges[0][1] = 1;
    map.edges[0][7] = 1;

    map.edges[1][2] = 1;

    map.edges[2][3] = 1;
    map.edges[2][6] = 1;
    map.edges[2][4] = 1;

    map.edges[3][4] = 1;

    map.edges[4][5] = 1;

    map.edges[5][10] = 1;

    map.edges[6][7] = 1;
    map.edges[6][8] = 1;

    map.edges[7][9] = 1;

    map.edges[8][10] = 1;
    map.edges[9][8] = 1;


    UAV uav;
    uav.x = 0;
    uav.y = 0;
    uav.yaw = 0;

    Node *start = &map.nodes[0];
    Node *end = &map.nodes[10];

    // Route route = findRoute(map,uav,*start,*end,0.5);
    Route route = aStar(&map, start, end);
    for (int i = route.length ; i >= 0 ; i--)
    {
        uav.x = route.path[i]->x;
        uav.y = route.path[i]->y;
        uav.yaw = route.path[i]->yaw;//burda başlangıç yönü girilmeli
        while (uav.x != route.path[i-1]->x &&
        uav.y != route.path[i-1]->y){
            //uçağın yönünü bir sonraki düğüme ulaşana kadar güncelle
            uav=uav_path(uav,route,i);   
        }
        
        
    }
    

    // rota bilgileri
    printf("Rota uzunluğu: %d\n", route.length);
    printf("Rota maliyeti: %d\n", route.cost);

    // rota düğümleri
    printf("Rota düğümleri: \n");
    for (int i = route.length; i >= 0; i--)
    {
        printf("(%f, %f) \n", route.path[i]->x, route.path[i]->y);
    }
    printf("\n");
    return 0;
}