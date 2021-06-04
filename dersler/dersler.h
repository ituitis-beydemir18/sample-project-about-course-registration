#define DERSAD_UZUNLUK 20			//Ders adinin max uzunlugu 15 karakter olabilecegi varsayilmistir. Istenirse degistirilebilir
#define TAD_UZUNLUK 20				//Tip adinin max uzunlugu 20 karakter olabilecegi varsayilmistir. Istenirse degistirilebilir
#define MAX_DERS 10					//Bir ogrencinin max ders sayisi 10 olarak varsayilmistir. Istenirse degistirilebilir
#define SAAT 1						//Sistem saatinin Ist.a gore yanilma payi programda saate eklenecektir

/*Herbir aktivite icin ayri ayri aktivite structi kullanilacaktir...*/
struct aktivite{
	char tip[TAD_UZUNLUK];			//aktivitenin tipini tutar
	int ay;							//aktivitenin bitis ayini tutar
	int gun;						//aktivitenin bitis gununu tutar
	int saat;						//aktivitenin bitis saatini tutar
	int toplam;
};

/*Herbir ders icin ayri ayri Ders structi kullanilacaktir...*/
struct Ders{	
	char ad[DERSAD_UZUNLUK];		//dersin adini tutar
	aktivite *yapilcak;				//aktiviteye point eder
	Ders *sonraki;					//sonraki derse point eder
};
