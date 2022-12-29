#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 100 // Maksimum düğüm sayısı

typedef struct
{
    int numNodes;                    // Düğüm sayısı
    int numEdges;                    // Kenar sayısı
    Node nodes[MAX_NODES];           // Düğümler
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
double *rota_hesapla(UAV uav, Node hedef, double manevra_kabiliyeti)
{
    // Harita verilerini tutan veri yapısı

    // Rota listesi için yer ayırıyoruz
    int rota_uzunlugu = (int)(mesafe(uav, hedef) / manevra_kabiliyeti);
    double rota = (double)malloc(sizeof(double) * rota_uzunlugu);

    // Rota listesini oluşturuyoruz
    for (int i = 0; i < rota_uzunlugu; i++)
    {
        Node mevcut_hedef;
        mevcut_hedef.x = uav.x + (hedef.x - uav.x) * (i + 1) / rota_uzunlugu;
        mevcut_hedef.y = uav.y + (hedef.y - uav.y) * (i + 1) / rota_uzunlugu;

        double yon_degisim = yon_degisimi(uav, mevcut_hedef);
        rota[i] = yon_degisim / PI; // Yön değişim miktarını yüzdelik olarak kaydediyoruz
    }

    return rota;
}
