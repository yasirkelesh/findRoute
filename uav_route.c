#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* Rota belirleme algoritmasının hangi verilere göre çalışacağını belirleyin. 
Örneğin, rota belirleme algoritması harita verileri, kullanıcının bulunduğu konum, 
hedef konum ve seyahat sırasında kullanılacak yol türleri gibi verilere göre çalışabilir. 
Bu verileri nasıl elde edeceğinizi ve nasıl depolayacağınızı düşünün.
Rota belirleme algoritmasının çalışma prensibini belirleyin. 
Örneğin, rota belirleme algoritması en kısa yolu bulmak için Dijkstra algoritmasını kullanabilir 
veya en az maliyetli yolu bulmak için A* algoritmasını kullanabilir. Hangi algoritmayı kullanacağınıza karar verdikten sonra, 
algoritmanın nasıl çalıştığını anlamaya çalışın ve bu algoritmayı nasıl uygulayacağınızı planlayın.
Verileri elde edin ve depolayın. Örneğin, harita verilerini bir veri yapısına yükleyin ve 
kullanıcının bulunduğu konumu ve hedef konumu STM32 microcontroller'daki sensörler veya GPS modülü aracılığıyla elde edin.
Rota belirleme algoritmasını yazın ve test edin. Algoritmanızı yazdıktan sonra, v
erileri kullanarak test edin ve algoritmanın doğru bir şekilde çalışıp çalışmadığını kontrol edin.
Algoritmayı uygulayın. Algoritmanızın doğru bir şekilde çalıştığını doğruladıktan sonra, 
STM32 microcontroller üzerinde rota belirleme algoritmasını uygulayarak kullanıcının hedef konumuna doğru rota belirleyin. */


#define PI 3.14159265  // Pi sayısının sabiti

#define MAX_NODES 100  // Maksimum düğüm sayısı

// Düğümleri tutan veri yapısı
typedef struct {
  int x;  // Düğümün x koordinatı
  int y;  // Düğümün y koordinatı
} Node;

/* // Uçak (UAV) türünde bir nesnenin verilerini tutan veri yapısı
typedef struct {
  int x;  // Uçak nesnesinin x koordinatı
  int y;  // Uçak nesnesinin y koordinatı
  double heading;  // Uçak nesnesinin yönü (radyan cinsinden)
} UAV;
 */
// UAV'nin mevcut konumunu ve yönünü temsil eden bir yapı
typedef struct {
    double x;  // x koordinatı
    double y;  // y koordinatı
    double yaw;  // Radyan cinsinden yaw açısı
} UAV;

// Haritadaki bir noktayı temsil eden bir yapı
typedef struct {
    double x;  // x koordinatı
    double y;  // y koordinatı
} Point;

// İki nokta arasındaki mesafeyi hesaplayan bir fonksiyon
double mesafe(UAV p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// İki nokta arasındaki yaw açısını hesaplayan bir fonksiyon
double yaw(UAV p1, Point p2) {
    return atan2(p2.y - p1.y, p2.x - p1.x);
}

// UAV'nin belirli bir noktaya bakması için gerekli olan yön değiştirme miktarını hesaplayan bir fonksiyon
double yon_degisimi(UAV uav, Point p) {
    double istenen_yaw = yaw(uav, p);
    return istenen_yaw - uav.yaw;
}

// UAV'nin takip etmesi gereken rotayı hesaplayan bir fonksiyon
// Bu fonksiyon, UAV'nin mevcut konumunu ve yönünü, hedef noktayı ve UAV'nin manevra kabiliyetini alır
// Bir rota listesi döndürür
// Rota listesi, yön değiştirme miktarının yüzdelik oranını içeren bir dizidir
// Örneğin, rota[0] = 50% demek, UAV'nin yönünü yarısına kadar değiştirmesi gerektiği anlamına gelir
double *rota_hesapla(UAV uav, Point hedef, double manevra_kabiliyeti) {
    // Rota listesi için yer ayırıyoruz
    int rota_uzunlugu = (int) (mesafe(uav, hedef) / manevra_kabiliyeti);
    double *rota = (double*) malloc(sizeof(double) * rota_uzunlugu);

    // Rota listesini oluşturuyoruz
    for (int i = 0; i < rota_uzunlugu; i++) {
        Point mevcut_hedef;
        mevcut_hedef.x = uav.x + (hedef.x - uav.x) * (i + 1) / rota_uzunlugu;
        mevcut_hedef.y = uav.y + (hedef.y - uav.y) * (i + 1) / rota_uzunlugu;

        double yon_degisim = yon_degisimi(uav, mevcut_hedef);
        rota[i] = yon_degisim / PI;  // Yön değişim miktarını yüzdelik olarak kaydediyoruz
    }

    return rota;
}

// test 
int main()
{
    UAV uav;
    Point hedef;

    uav.x = 10;
    uav.y = 15;
    uav.yaw = PI;

    hedef.x = 25;
    hedef.y = 65;
    int rota_uzunlugu = (int) (mesafe(uav, hedef) / 4);
    double *rota = rota_hesapla(uav,hedef, 5);
    
    for (int i = 0; i < rota_uzunlugu; i++) {
        printf("%f\n",rota[i]);
    }
    
}
