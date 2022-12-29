#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 100 // Maksimum düğüm sayısı
#define PI 3.14159265  // Pi sayısının sabiti

// Harita verilerini tutan veri yapısı
typedef struct
{
    int numNodes;                    // Düğüm sayısı
    Node nodes[MAX_NODES];           // Düğümler
    int numEdges;                    // Kenar sayısı
    int edges[MAX_NODES][MAX_NODES]; // Kenarlar
} MapData;

// Rota bilgisini tutan veri yapısı
typedef struct
{
    int length;           // Rota uzunluğu (adım sayısı)
    int cost;             // Rota maliyeti (toplam yön değişim miktarı)
    Node path[MAX_NODES]; // Rota düğümleri
} Route;

// Düğümleri tutan veri yapısı
typedef struct
{
    int x; // Düğümün x koordinatı
    int y; // Düğümün y koordinatı
} Node;

// Uçak (UAV) türünde bir nesnenin verilerini tutan veri yapısı
typedef struct
{
    int x;          // Uçak nesnesinin x koordinatı
    int y;          // Uçak nesnesinin y koordinatı
    double heading; // Uçak nesnesinin yönü (radyan cinsinden)
} UAV;

// Düğümler arasındaki mesafeyi hesaplama fonksiyonu
double mesafe(Node n1, Node n2)
{
    int dx = n2.x - n1.x;
    int dy = n2.y - n1.y;
    return sqrt(dx * dx + dy * dy);
}


// Uçak nesnesinin yönünü hedef düğüme doğru değiştirme fonksiyonu
double yon_degisimi(UAV uav, Node hedef)
{
    double yon1 = atan2(hedef.y - uav.y, hedef.x - uav.x);
    double yon2 = uav.heading;
    double degisim = yon1 - yon2;
    if (degisim < -PI)
    {
        degisim += 2 * PI;
    }
    else if (degisim > PI)
    {
        degisim -= 2 * PI;
    }
    return degisim;
}

// Rota listesi oluşturma fonksiyonu
double *rota_hesapla(MapData map, UAV uav, int startNode, int endNode, double manevra_kabiliyeti)
{

    // Rota listesi için yer ayırıyoruz
    int rota_uzunlugu = (int)(mesafe(map.nodes[startNode], map.nodes[endNode]) / manevra_kabiliyeti);
    double *rota = (double *)malloc(sizeof(double) * rota_uzunlugu);

    // A* algoritmasını kullanarak en kısa rotayı bulalım
    //Route route = findRoute(map, startNode, endNode, ROUTE_TYPE_SHORTEST);

    // Rota listesini oluşturuyoruz
    for (int i = 0; i < rota_uzunlugu; i++)
    {
        Node mevcut_hedef = Route.path[i];
        double yon_degisim = yon_degisimi(uav, mevcut_hedef);
        rota[i] = yon_degisim / PI; // Yön değişim miktarını yüzdelik olarak kaydediyoruz
    }

    return rota;
}
int main()
{
    UAV uav;
    MapData map;

    map.numNodes = 5;
    map.nodes[0].x = 0;
    map.nodes[0].y = 0;
    map.nodes[1].x = 10;
    map.nodes[1].y = 0;
    map.nodes[2].x = 10;
    map.nodes[2].y = 10;
    map.nodes[3].x = 0;
    map.nodes[3].y = 10;
    map.nodes[4].x = 5;
    map.nodes[4].y = 5;

    map.numEdges = 5;
    map.edges[0][1] = 1;
    map.edges[0][3] = 1;
    map.edges[1][0] = 1;
    map.edges[1][2] = 1;
    map.edges[1][4] = 1;
    map.edges[2][1] = 1;
    map.edges[2][3] = 1;
    map.edges[3][0] = 1;
    map.edges[3][2] = 1;
    map.edges[4][1] = 1;
    map.edges[4][4] = 1;


    uav.x = 10;
    uav.y = 15;
    uav.heading = PI;

    int rota_uzunlugu = (int)(mesafe(map.nodes[0], map.nodes[3]) / 5);
    double *rota = rota_hesapla(map, uav,0, 3, 5);
    
    for (int i = 0; i < rota_uzunlugu; i++) {
        printf("%f\n",rota[i]);
    }
    
}