#include "dersler.h"
#include <stdio.h>

struct Islemler{
	void ekle(char *,char *,int,int,int,int);				//giris parametreleri olarak: eklenecek ders adi,dersle ilgili aktivite adi,son bitis tarihi ay-gun-saat olarak verilmelidir...
	Ders* ders_olustur(char *,char *,int,int,int,int);		//ekle fonksiyonun aldigi parametreleri alarak bir kayit olusturur...
	int* ara(char *);									//arama fonksiyonunu yapip cagirilan fonksiyona dizi dondurur							//
	void kapat();										//program kapatilacagi zaman cagrilir ve eldeki verileri dosyaya yazan fonksiyonla verileri remden silen fonksiyonu cagirir
	void sil(int );										//herhangi bir dersle ilgili tum isleri siler (dersin adini da)
	void aktivite_sil(char *);							//herhangi bir derse ait yalnizca bir kayidi siler
	void dosyaya_yaz();									//remdeki verileri dosyaya yazar
	void dosyadan_oku();								//dosyadaki verileri okuyup reme yazar					
	void olustur();										//bir dosya olusturup verileri dosyadan oku fonksiyonuyla alip oraya yazar
	void listebosalt();									//tum kayitlari siler
	void verileriyaz(char *);
	FILE *defter;										//dosyaya pointer
	char *dosyaadi;										//dosyaadini tutan string dizisi
	Ders *bas;											//derslerin basini tutan pointer
	Ders *temp;											//aramada tek bir kaydi tutan pointer (aktivite_sil fonksiyonunda gerekli...)
};
