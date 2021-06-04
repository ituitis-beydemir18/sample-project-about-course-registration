// proje.cpp : Defines the entry point for the console application.
//
#include "islemler.h"
//#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Windows.h>				//System saati structeri bu headerda tanimlandigi icin include etmemiz gerekli


using namespace std;

void Islemler::olustur(){	
/********************************************************************************************************
*  Fonksiyonun adi:		olustur																			*
*  Amacý:				Program her baslatildiginda bir txt dosyasi acip onceki verileri oraya yazmak	*
*  Giris parametreleri: ---																				*
*  Cikis parametreleri: ---																				*
*  Veri yapilari      : ---																				*
********************************************************************************************************/
	dosyaadi="defter.txt";
	defter = fopen( dosyaadi, "r+" );
	if(!defter){		
		if(!(defter = fopen( dosyaadi, "w+" ))){
			cerr << "Dosya acilamadi" << endl;
			exit(1);
		}
	}
	dosyadan_oku();
}

int* Islemler::ara(char *ara_ders){
/****************************************************************************************************************
*  Fonksiyonun adi:		ara																						*
*  Amacý:				Giris parametresinin ders adlari icerinde var olup olmadigina bakip varsa ekrana basacak*
*  Giris parametreleri: Aranacak string dizisi																	*
*  Cikis parametreleri: Siranumaralarini tutan bir dizi															*
*  Veri yapilari      : Baglantili liste																		*
****************************************************************************************************************/
	Ders *tara;
	aktivite *act;
	tara=bas;
	int zaman;
	int *bulunan= new int[MAX_DERS];
	SYSTEMTIME st;
    GetSystemTime(&st);
	for(int j=0;j<MAX_DERS;j++)
		bulunan[j]=-1;
	int sayac=0,i=0; 
	bool tumu = false;
	if(ara_ders[0]=='h')
		tumu = true;
	
	while(tara){
		sayac++;
		if(tumu){
			cout << sayac << "." << tara->ad <<endl;
			bulunan[i] = sayac ;
			i++;
			act=tara->yapilcak;	
				zaman=(act->ay-st.wMonth)*30*24 + (act->gun-st.wDay)*24+(act->saat-st.wHour-SAAT) ;
				cout<<"     "<<act->tip<<endl;
				if(zaman <=0 )
					cout <<"\tSon tarihi maalesef gecmistir."<<endl;
				else{
					if(zaman<=48)
						cout<<"\a\a\a\tDikkat bitim tarihine cok az sure kalmistir..."<<endl;
					cout<<"\tkalan ay : "<<(zaman)/(24*30)<<endl;
					cout<<"\tkalan gun : "<<(zaman)/24 - (zaman/(24*30))*30<<endl;
					cout<<"\tkalan saat : "<<zaman%24<<endl;
			}
		}							
		else 
			if(strncmp(ara_ders,tara->ad,strlen(ara_ders))==0) {
				cout << sayac << "." << tara->ad <<endl;
				act=tara->yapilcak;
				temp=tara;
				bulunan[i] = sayac ;
				i++;
					zaman=(act->ay-st.wMonth)*30*24 + (act->gun-st.wDay)*24+(act->saat-st.wHour-SAAT) ;
					cout<<"     "<<act->tip<<endl;
				if(zaman <=0 )
					cout <<"\tSon tarihi maalesef gecmistir. "<<endl;
				else{
					if(zaman<=48)
						cout<<"\a\a\aDikkat bitim tarihine cok az sure kalmistir..."<<endl;
					cout<<"\tkalan ay : "<<(zaman)/(24*30)<<endl;
					cout<<"\tkalan gun : "<<(zaman)/24 - (zaman/(24*30))*30<<endl;
					cout<<"\tkalan saat : "<<zaman%24<<endl;
				}	
			}
			tara=tara->sonraki;	
	}	
	if(!bas)	
		cout<<"Guncel ders kaydi bulunmamaktadir."<<endl;
	else 
		if(i==0)
		cout << "Aradiginiz kriterlere uygun kayit bulunamadi" << endl;

	return bulunan;
}

void Islemler::ekle(char *yeniad,char *yenitip,int month,int day,int hour,int total){
/************************************************************************************************************
*  Fonksiyonun adi:		ekle																				*
*  Amacý:				Baglantili listeye ders ekleme														*
*  Giris parametreleri: Yeni ders adini ve tipini tutan karakter dizileri ve ay,gun,saat,total degiskenleri *
*  Cikis parametreleri: ---																					*
*  Veri yapilari      : Baglantili liste																	*
************************************************************************************************************/
	Ders *tara,*arka,*yeniders;
	aktivite *act,*eski;
	tara=bas;
	if(bas==NULL){
			bas=ders_olustur(yeniad,yenitip,month,day,hour,total);
		return;
	}
	if(total < bas->yapilcak->toplam){	//liste basina ekleme
			yeniders=ders_olustur(yeniad,yenitip,month,day,hour,total);
			yeniders->sonraki=bas;
			bas= yeniders ;
		return;
	}
	while(tara&& (total> tara->yapilcak->toplam)){
		arka=tara;
		tara=tara->sonraki;
	}
		yeniders=ders_olustur(yeniad,yenitip,month,day,hour,total);
		if(tara){
			yeniders->sonraki= tara;
			arka->sonraki = yeniders;
		}
		else
			arka->sonraki=yeniders;
	
}

Ders* Islemler::ders_olustur(char *ad,char *tip,int month,int day,int hour,int total){
/********************************************************************************************************
*  Fonksiyonun adi:		ders_olustur																	*
*  Amacý:				Ders structi tipinde bir struct olusturmak										*
*  Giris parametreleri: Yeni ders adini ve tipini tutan karakter dizileri ve ay,gun,saat degiskenleri	*
*  Cikis parametreleri: Ders structina pointeri															*
*  Veri yapilari      : Baglantili liste																*
********************************************************************************************************/
	Ders *yeniders;
	aktivite *yenitip;
	yeniders = new Ders;
	strcpy(yeniders->ad,ad);
	yenitip = new aktivite;
	yeniders->yapilcak = yenitip;
	strcpy(yenitip->tip,tip);
	yenitip->ay=month;
	yenitip->gun=day;
	yenitip->saat=hour;
	yenitip->toplam=total;
	yeniders->sonraki=NULL;
	return yeniders;
};

void Islemler::sil(int sirano){
/********************************************************************************************************
*  Fonksiyonun adi:		sil																				*
*  Amacý:				Ders structi tipinde bir struct silmek											*
*  Giris parametreleri: Silinmek istenen structin siranumarasi											*
*  Cikis parametreleri: ---																				*
*  Veri yapilari      : Baglantili liste																*
********************************************************************************************************/
	Ders *tara,*arka;
	aktivite *act;
	tara=bas;
	if(sirano==1){
		bas=bas->sonraki;
		act = tara->yapilcak;
			delete act;
			delete tara;
		return;
	}
		int sayac=1;
	while((tara!=NULL)&&(sayac<sirano)){
		arka=tara;
		tara= tara->sonraki;
		sayac++;
	}
	if(sayac<sirano) {
		cout << "Silinece kayit bulunamadi " <<endl;
	}
	else{
		arka->sonraki = tara->sonraki;
		act = tara->yapilcak;
			delete act;
			delete tara;
	}
};

void Islemler::kapat(){
/********************************************************************************************************************
*  Fonksiyonun adi:		kapat																						*
*  Amacý:				Program kapatilcagi zaman kayitlari dosyaya yaz ve listeyibosalt fonksiyonlarini cagirir	*
*  Giris parametreleri: ---																							*
*  Cikis parametreleri: ---																							*
*  Veri yapilari      : ---																							*
********************************************************************************************************************/
	dosyaya_yaz();
	listebosalt();
};

void Islemler::listebosalt(){
/********************************************************************************************************
*  Fonksiyonun adi:		listebosalt																		*
*  Amacý:				Remde olusturulan listeyi program kapatilcagi zaman silmek						*
*  Giris parametreleri: ---																				*
*  Cikis parametreleri: ---																				*
*  Veri yapilari      : ---																				*
********************************************************************************************************/
	Ders *d;
	aktivite *a;
	while(bas) {
		d=bas;
		bas=bas->sonraki;
		a=d->yapilcak;
			delete a;
			delete d;
	}
};
			
void Islemler::dosyadan_oku(){
/********************************************************************************************************************
*  Fonksiyonun adi:		dosyadan_oku																				*
*  Amacý:				Onceden olusturulmus dosyadan program baslatildigi zaman verileri okumak ve listeye eklemek	*
*  Giris parametreleri: ---																							*
*  Cikis parametreleri: ---																							*
*  Veri yapilari      : ---																							*
********************************************************************************************************************/
	struct Ders_kayit{
		char ad[DERSAD_UZUNLUK];
		char tip[TAD_UZUNLUK];
		int ayi;
		int gunu;
		int saati;
		int total;
	};
	Ders_kayit kayit;
	dosyaadi="defter.txt" ;
		if(!(defter=fopen(dosyaadi,"r+")))
			if(!(defter=fopen(dosyaadi,"w+"))){
				cerr<<" Dosya acilamadi " <<endl;
				cerr<<" Sadece bellekte calisacak "<<endl;
				return;
			}
	fseek(defter,0,SEEK_SET);
	while(!feof(defter)) {
		fread(&kayit,sizeof(Ders_kayit),1,defter);
		if(feof(defter))  break;
		ekle(kayit.ad,kayit.tip,kayit.ayi,kayit.gunu,kayit.saati,kayit.total);
		}
	fclose(defter);
};

void Islemler::dosyaya_yaz(){
/********************************************************************************************************
*  Fonksiyonun adi:		dosyaya_yaz																		*
*  Amacý:				Ders listesindeki kayitlari program kapatilacagi zaman bir dosyaya yazmak		*
*  Giris parametreleri: ---																				*
*  Cikis parametreleri: ---																				*
*  Veri yapilari      : ---																				*
********************************************************************************************************/
	struct Ders_Kayit{
		char ad[DERSAD_UZUNLUK];
		char tip[TAD_UZUNLUK];
		int ayi;
		int gunu;
		int saati;
		int total;
	};
	Ders_Kayit kayit ;
	Ders *dersler;
	aktivite *akt;
		if(!(defter=fopen(dosyaadi,"w+"))){
			cerr<<"Dosya acilamadi "<<endl;
			return;
		}
	fseek(defter,0,SEEK_SET);
	dersler=bas;
	while(dersler){
		akt=dersler->yapilcak;
			strcpy(kayit.ad,dersler->ad);
			strcpy(kayit.tip,akt->tip);
			kayit.ayi=akt->ay;
			kayit.gunu=akt->gun;
			kayit.saati=akt->saat;
			kayit.total=akt->toplam;
			fwrite(&kayit,sizeof(Ders_Kayit),1,defter);
		dersler=dersler->sonraki;
		}
	fclose(defter);
};


void Islemler::verileriyaz(char *dosya){
/************************************************************************************
*  Fonksiyon adý:		verileriyaz													*
*  Amacý:			    Kayitlari herhangi bir dosyaya readable sekilde yazmak		*
*  Giris parametreleri: Dosya isimli yazilacak dosya adini tutan karakter dizisi	*
*  Cikis parametreleri: ---															*
*  Veri yapilari      : Baglantili liste											*
************************************************************************************/
	SYSTEMTIME st;
    GetSystemTime(&st);
	int zaman;
     Ders *tara;
	 aktivite *act;
     tara=bas;
	 FILE *deftereptr;
	 if(!(deftereptr=fopen(dosya,"r+")))
		if(!(deftereptr=fopen(dosya,"w+")))
			cout<<"File could not be opened "<<endl;
		else{
			while(tara){
				act=tara->yapilcak;
				zaman=(act->ay-st.wMonth)*30*24 + (act->gun-st.wDay)*24+(act->saat-st.wHour-SAAT) ;
				fprintf(deftereptr,"Ders adi : %s \n",tara->ad);
				fprintf(deftereptr,"\t\t%s \n",act->tip);
				fprintf(deftereptr,"\t\t\t Kalan ay: %d\n\t\t\t Kalan gun : %d\n\t\t\t Kalan saat : %d\n\n",zaman/(24*30),zaman/24-(zaman/(24*30))*30,zaman%24);
				tara=tara->sonraki;
			}
		}
};
