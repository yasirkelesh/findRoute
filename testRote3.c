#define MAX_NODES 100 // Maksimum düğüm sayısı

// Düğümleri tutan veri yapısı
typedef struct
{
    int x; // Düğümün x koordinatı
    int y; // Düğümün y koordinatı
} Node;

// Rota bilgisini tutan veri yapısı
typedef struct
{
    int length;           // Rota uzunluğu (adım sayısı)
    int cost;             // Rota maliyeti (toplam yön değişim miktarı)
    Node path[MAX_NODES]; // Rota düğümleri
} Route;

// Uçak veri yapısı
typedef struct
{
    double x;   // Uçak konumu x koordinatı
    double y;   // Uçak konumu y koordinatı
    double yon; // Uçak yönü (radyan cinsinden)
} UAV;

// Harita verilerini tutan veri yapısı
typedef struct
{
    int numNodes;                    // Düğüm sayısı
    Node nodes[MAX_NODES];           // Düğümler
    int numEdges;                    // Kenar sayısı
    int edges[MAX_NODES][MAX_NODES]; // Kenarlar
} MapData;

// Rota bulma algoritması
Route findRoute(MapData map, UAV uav, int startNode, int endNode, double manevra_kabiliyeti)
{
    // A* algoritmasını kullanarak en kısa rotayı bulalım
    Route route = aStar(map, startNode, endNode);

    // Rota uzunluğunu manevra kabiliyetine göre ayarlayalım
    double rota_uzunlugu = mesafe(uav, map.nodes[endNode]) / manevra_kabiliyeti;
    int mevcut_rota_uzunlugu = route.length;
    if (rota_uzunlugu > mevcut_rota_uzunlugu)
    {
        // Rota listesini uzatıyoruz
        int ek_adim_sayisi = rota_uzunlugu - mevcut_rota_uzunlugu;
        for (int i = 0; i < ek_adim_sayisi; i++)
        {
            route.path[mevcut_rota_uzunlugu + i] = route.path[mevcut_rota_uzunlugu - 1];
        }
        route.length += ek_adim_sayisi;
    }
    else if (rota_uzunlugu < mevcut_rota_uzunlugu)
    {
        // Rota listesini kısaltıyoruz
        int azaltilacak_adim_sayisi = mevcut_rota_uzunlugu - rota_uzunlugu;
        for (int i = 0; i < azaltilacak_adim_sayisi; i++)
        {
            route.path[mevcut_rota_uzunlugu - i - 1] = route.path[mevcut_rota_uzunlugu - azaltilacak_adim_sayisi - 1];
        }
        route.length -= azaltilacak_adim_sayisi;
    }

    return route;
}
