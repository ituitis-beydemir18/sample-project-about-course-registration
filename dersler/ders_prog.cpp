#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
//#include "stdafx.h"

#include "islemler.h"
using namespace std;


typedef Islemler ajanda;
ajanda program;

void menu_yazdir();
bool islem_yap(char);
void ders_ara();
void ders_ekle();
void ders_sil();
void yapilcak_sil();
void ders_guncelle();
void ders_listele();
void temizle();
void ders_guncelle();


int main(int argc,char *argv[]){

	 if(argc>3) return EXIT_FAILURE;
	 if(argc==3){
		    program.olustur();
			program.verileriyaz(argv[2]);
	 }
	 else if(argc==2){
		   program.olustur();
		   program.ara(argv[1]);   
	 }
    else if(argc==1){	
	program.olustur();	
	bool bitir = false; 
	char secim; 	
	while (!bitir) { 
		menu_yazdir(); 
		cin >> secim;
		bitir = islem_yap(secim); 
		} 	
	program.kapat();
	}
	getchar();
	return EXIT_SUCCESS;
}

void menu_yazdir(){
	system("cls");	//linux'ta ekran temizleme icin system("clear"); kullaniniz
	cout << endl << endl;
	cout << "Sinif Disi Ders Calisma Planlayici Uygulamasi" << endl;
	cout << "Bir islem seciniz" << endl;
	cout << "A: Kayit Arama" << endl;
	cout << "E: Kayit Ekleme" << endl;
	cout << "S: Herhangi Bir Dersle Ilgili Kayiti Silmek" << endl;	
	cout << "T: Tum Dersleri Sil" << endl;
	cout << "G: Ders guncelle" <<endl;
 	cout << "C: Cikis" << endl<<endl;
	cout << "Bir secenek giriniz {A, E, S, T, G, C} : ";
}

bool islem_yap(char secim){
	bool sonlandir=false;
	switch (secim) { 
		case 'A': case 'a': 
			ders_ara();
			break; 
		case 'E': case 'e': 
			ders_ekle();
			break; 
		case 'S': case 's': 
			ders_sil();
			break;
		case 'G': case 'g':
			ders_guncelle();
			break;
		case 'T': case 't':
			temizle();
			break;
		case 'C': case 'c': 
			cout << "Programi sonlandirmak istediðinize emin misiniz? (E/H):";
			cin >> secim;
			if(secim=='E' || secim=='e')
				sonlandir=true; 
				break; 
		default: 
			cout << "Hata: Yanlis giris yaptiniz" << endl; 
			cout << "Tekrar deneyiniz {A, E, G, S, T, C} :" ;
			cin >> secim;
			sonlandir = islem_yap(secim);
			break; 
	}
	return sonlandir;
}

void ders_ara(){
	char ad[DERSAD_UZUNLUK];
	cout << "Lutfen aramak istediginiz dersin adini giriniz (tum dersler icin 'h'ye basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,DERSAD_UZUNLUK);
	int *bulunan=program.ara(ad);
	getchar();
	return;
};

void ders_ekle(){
	char ad[DERSAD_UZUNLUK];
	char tip[TAD_UZUNLUK];
	cout << "Lutfen kaydetmek istediginiz dersin bilgilerini giriniz" << endl;
	cout << "Ad : " ;
		cin.ignore(1000, '\n');
		cin.getline(ad,DERSAD_UZUNLUK);
	cout << "Yapilacak isi tanimlayan anahtar sozcuk giriniz : ";
		cin.getline(tip,TAD_UZUNLUK);
	int gun,ay,saat;			//gecici degiskenler
	cout<< "Bitis tarihinin kacinci ayda oldugunu giriniz: "<<endl;
		cin>>ay;
	cout<<ay<<". ayin kacinci gununde suresi bitmektedir: "<<endl;
		cin>>gun;
	cout<<gun<<".un hangi saatinde bitmektedir:(Saati tam olarak giriniz orn:15) "<<endl;			//Dakikanýn pek bi ehemmiyeti olmadigi dusunulmustur
		cin>>saat;
    int toplamsaat=saat+gun*24+ay*30*24;
	program.ekle(ad,tip,ay,gun,saat,toplamsaat);

	cout << "Kaydiniz eklenmistir" << endl;
	getchar();
};

void ders_sil(){
	char ad[DERSAD_UZUNLUK];
	bool varmi = false;	
	cout << "Lutfen kaydini silmek istediginiz dersin adini giriniz (tum liste için 'h' ye basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,DERSAD_UZUNLUK);
	int *derssayisi=program.ara(ad); 

	if ((derssayisi[0]!=-1)&&(derssayisi[1]==-1)){
		cout << "Kayit bulundu." << endl;
		char secimm;
			cout << "Ders defterindeki bu kaydi silmek istediginize emin misiniz?(E/H)"<< endl;
			cin >> secimm;
			if(secimm=='E' || secimm=='e'){ 
			secimm=derssayisi[0];
			program.sil(secimm);
			cout<< "Kayit silindi."<<endl;
		}
			if(secimm=='H' || secimm=='h')return;
		}
		
	else
		if (derssayisi[1]!=-1) {
		cout << "Silmek istediginiz dersin numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
		int secim;
		cin >> secim;
			if(secim==-1) return;
		int i=0;
		while(derssayisi[i]!=-1) {
			if(secim == derssayisi[i])
				varmi = true;
			i++;		
		}
		if(varmi){
			program.sil(secim);	
			cout << "Kayit silindi" <<endl;		
		}
		if(!varmi)
			cout<<"Hatali siranumarasi girdiniz"<<endl;
		}
	getchar();
	getchar();
};

void temizle(){
	 char secim;
    cout << "Dersler defterindeki butun kayitlari silmek istediginize emin misiniz?(E/H)"<< endl;
    cin >> secim;
    if(secim=='E' || secim=='e'){
        program.listebosalt();
        cout << "Temizle islemi tamamlandi."<< endl;
    }
    if(secim=='H' || secim=='h')return;
};

void ders_guncelle(){
	char ad[DERSAD_UZUNLUK];
	char tip[TAD_UZUNLUK];
	int gun,ay,saat;			//gecici degiskenler
	bool varmi=false;
	int secim;
	cout << "Lutfen kaydini silmek istediginiz dersin adini giriniz (tum liste için 'h' ye basiniz):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,DERSAD_UZUNLUK);
	int *derssayisi=program.ara(ad); 
	
	if ((derssayisi[0]!=-1)&&(derssayisi[1]==-1)){		
		cout << "Kayit bulundu." << endl;
		char secimm;
		cout << "Ders defterindeki bu kaydi guncellemek istediginize emin misiniz?(E/H)"<< endl;
		cin >> secimm;
		if(secimm=='E' || secimm=='e'){ 
			secimm=derssayisi[0];
			program.sil(secimm);
		cout << "Lutfen yeni dersin bilgilerini giriniz" << endl;
		cout << "Ad : " ;
			cin.ignore(1000, '\n');
			cin.getline(ad,DERSAD_UZUNLUK);
		cout << "Yapilacak isi tanimlayan anahtar sozcuk giriniz : ";
			cin.getline(tip,TAD_UZUNLUK);
		cout<< "Bitis tarihinin kacinci ayda oldugunu giriniz: "<<endl;
			cin>>ay;
		cout<<ay<<". ayin kacinci gununde suresi bitmektedir: "<<endl;
			cin>>gun;
		cout<<gun<<".un hangi saatinde bitmektedir:(Saati tam olarak giriniz orn:15) "<<endl;			//Dakikanýn pek bi ehemmiyeti olmadigi dusunulmustur
			cin>>saat;
		int toplamsaat=saat+gun*24+ay*30*24;
		program.ekle(ad,tip,ay,gun,saat,toplamsaat);
			cout<< "Kayit guncellendi."<<endl;
		}
		if(secimm=='H' || secimm=='h')return;
	}
		
	else
		if (derssayisi[1]!=-1) {
			cout << "Guncellemek istediginiz dersin sira numarasini giriniz (Islem yapmadan cikmak icin -1 giriniz): " ;
			cin >> secim;
			if(secim==-1) return;
			int i=0;
			while(derssayisi[i]!=NULL) {
				if(secim == derssayisi[i])
					varmi = true;
				i++;		
			}
			if(varmi){
				program.sil(secim);	
				cout << "Lutfen guncellemek istediginiz dersin bilgilerini giriniz" << endl;
				cout << "Ad : " ;
				cin.ignore(1000, '\n');
				cin.getline(ad,DERSAD_UZUNLUK);
				cout << "Yapilacak isi tanimlayan anahtar sozcuk giriniz : ";
				//cin.ignore(1000, '\n');
				cin.getline(tip,TAD_UZUNLUK);
				cout<< "Bitis tarihinin kacinci ayda oldugunu giriniz: "<<endl;
					cin>>ay;
				cout<<ay<<". ayin kacinci gununde suresi bitmektedir: "<<endl;
					cin>>gun;
				cout<<gun<<".un hangi saatinde bitmektedir:(Saati tam olarak giriniz orn:15) "<<endl;			//Dakikanýn pek bi ehemmiyeti olmadigi dusunulmustur
					cin>>saat;
				int toplamsaat=saat+gun*24+ay*30*24;
				program.ekle(ad,tip,ay,gun,saat,toplamsaat);
					cout << "Kayit guncellendi" <<endl;
			}
			if(!varmi)
				cout<<"Hatali siranumarasi girdiniz"<<endl;
		}
	getchar();
	getchar();
}