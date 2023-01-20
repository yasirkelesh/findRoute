#include "route_find.h"

Route aStar(MapData *map, Node *start, Node *end)
{
    initNodes(map);

    Node *openList[MAX_NODES] = {NULL}; // başlagıç düğümünü içericek
    // diğerlerini sonra eklicem
    Node *closedList[MAX_NODES] = {NULL};
    // ziyaret edilen düğümler
    int openListSize = 0;
    int closedListSize = 0;

    // ilk düğümü init
    start->g = 0;
    start->h = heuristic(start, end);
    start->f = start->g + start->h;
    openList[openListSize++] = start;

    while (openListSize > 0)
    {
        Node *current = NULL;
        int lowestF = INT_MAX; // en düşük maliyet
        int lowestFIndex = -1;

        // en düşük maliyetliyi seçmeye çalış
        for (int i = 0; i < openListSize; i++)
        {
            if (openList[i]->f < lowestF)
            {
                current = openList[i];

                lowestF = openList[i]->f;
                lowestFIndex = i;
            }
        }

        if (current == NULL)
        {
            break;
        }
        // eğer ulşatıysak Route yı olustur
        if (current->index == end->index)
        {
            // build path
            Route route = {0};
            int i = 0;
            Node *n = current;
            // geriye değru bir okuma yapıyoruz
            // end hangi yoldan geldiğimizi görmek için
            while (n->prev != NULL)
            {
                route.path[i++] = n;
                n = n->prev;
            }
            route.path[i] = start;
            route.length = i;

            return route;
        }

        // geçtiğiiz düğümü açık listeden kaldırıp kapalı listeye alıyoruz
        openList[lowestFIndex] = openList[--openListSize];
        closedList[closedListSize++] = current;

        for (int i = 0; i < map->numNodes; i++)
        {
            if (map->edges[current->index][i] > 0)
            {
                Node *neighbor = &map->nodes[i];

                // kapalı listede varmı diye kontrol ediyorum
                if (isInList(neighbor, closedList, closedListSize))
                {
                    continue;
                }

                int cost = map->edges[current->index][i];
                // printf("cost : %d\n",cost);
                int tentativeG = current->g + cost;
                // printf("tentativeG : %d\n",tentativeG);


                //açık listede varmı diye kontrol ett
                //değilse ekle ve h değerini de hesapla çünkü burda yeniden ekleme yaptın
                if (!isInList(neighbor, openList, openListSize))
                {
                    openList[openListSize++] = neighbor;
                    neighbor->h = heuristic(neighbor, end);
                }
                //eğer listede var ise
                //ve benim hesapladığım g değeri büyükse
                //demek ki verimli bir yol değil
                else if (tentativeG >= neighbor->g)
                {
                    continue;
                }

                //demek ki doğru yoldayım
                neighbor->prev = current;//geri gidebilmek için adresi atıyorum
                neighbor->g = tentativeG;
                neighbor->f = neighbor->g + neighbor->h;
            }
        }
    }

    return (Route){0};
}