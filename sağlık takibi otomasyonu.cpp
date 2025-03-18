#include <iostream>
#include <locale.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;
void AnaMenu(char,double,double,int);
void SuHedefi();
void SuGuncelleme();
int ProgramdanCikis();
void KaloriHedef();
void KaloriGuncelleme();
void KaloriHesaplama(char,double,double,int);
void HarcananKaloriHesaplama(double);
void AdimHedefi();
void AdimGuncelleme();
void TansiyonBilgileri();
void KanSekeriBilgileri();
void NabizBilgileri();
void IlacTakibi();
void RandevuTakibi();
void VucutKitleİndeksi(double, double, int);
void IdealVucutAgirligi(char, double);
void VucutYagOraniHesaplama(char, double);
void BazalMetabolikHiz(char, double, double, int);

double toplamSu = 0, hedef = 0;
double kaloriHedef = 0;
int adim = 0, toplamAdim = 0;
vector <double> kalori;

struct kiloBilgileri {
	double kiloHedefi = 0;
	double toplamVerilenKilo = 0;
};

 void KiloHedefi(kiloBilgileri& kisiselBilgiler)
{
	 system("cls");
	cout << " Kilo hedefi koymak için 'y' ya da eski hedefinizi görmek için 'e' tuşlayınız. " << endl;
	char cevap = 0;
	cin >> cevap;
	do {
		if (cevap != 'y' && cevap != 'Y' && cevap != 'e' && cevap != 'E')
			cout << " Lütfen geçerli bir yanıt giriniz. " << endl;
	} while (cevap != 'y' && cevap != 'Y' && cevap != 'e' && cevap != 'E');
	if (cevap == 'y' || cevap == 'Y')
	{
		cout << " Kilo hedefinizi giriniz (kg): " << endl;
		cin >> kisiselBilgiler.kiloHedefi;
		cout << " Kilo hedefiniz: " << kisiselBilgiler.kiloHedefi << " kg" << endl;
		ofstream kiloHedef;
		kiloHedef.open("KiloHedefi.txt", ios::out);
		if (!kiloHedef.is_open())
			cout << " Kilo hedefi dosyası açılamadı. " << endl;
		kiloHedef << kisiselBilgiler.kiloHedefi << endl;
		kiloHedef.close();
	}
	else
	{
		ifstream kiloHedef;
		kiloHedef.open("KiloHedefi.txt", ios::in);
		if (!kiloHedef.is_open())
			cout << " Kilo hedefi dosyası açılamadı. " << endl;
		string satir;
		while (getline(kiloHedef, satir))
			cout << " Kilo hedefiniz: " << satir << " kg" << endl;
		kiloHedef.close();

	}
}

void VerilenKiloGuncelleme(kiloBilgileri& kisiselBilgiler, double &kilo)
{
	system("cls");
	double verilenKilo = 0;
	string tarih;
	cout << " Kaybedilen kiloyu giriniz (kg): ";
	cin >> verilenKilo;
	cout << " Tarihi giriniz: ";
	cin >> tarih;
	kisiselBilgiler.toplamVerilenKilo += verilenKilo;
	cout << " Toplam verilen kilo: " << kisiselBilgiler.toplamVerilenKilo << endl;
	double guncelKilo = (kilo - kisiselBilgiler.toplamVerilenKilo);
	cout << " Güncel kilonuz: " << guncelKilo << " kg" << endl;
	double hedef;
	ifstream kiloHedef;
	kiloHedef.open("KiloHedefi.txt", ios::in);
	if (!kiloHedef.is_open())
		cout << " Kilo hedefi dosyası açılamadı. " << endl;
	kiloHedef >> hedef;
	kiloHedef.close();
	
	if (guncelKilo <= hedef)
		cout << " Tebrikler hedef kilonuza ulaştınız! " << endl;
	kilo = guncelKilo;
	ofstream kiloGuncelleme;
	kiloGuncelleme.open("KiloVerme.txt",ios::app);
	if (!kiloGuncelleme.is_open())
		cout << " Verilen kilo güncelleme dosyası açılamadı. " << endl;
	kiloGuncelleme << tarih << "\t" << verilenKilo << endl;
	kiloGuncelleme.close();
	char cevap = 0;
	do
	{
		cout << " Verdiğiniz bütün kiloların bilgilerine ulaşmak istiyorsanız 'e' istemiyorsanız 'h' tuşlayınız. " << endl;
		cin >> cevap;
		if (cevap != 'e' && cevap != 'E' && cevap != 'h' && cevap != 'H')
			cout << " Lütfen geçerli bir yanıt giriniz. " << endl;
	} while (cevap != 'e' && cevap != 'E' && cevap != 'h' && cevap != 'H');
	if (cevap == 'e' || cevap == 'E')
	{
		ifstream kiloGuncelleme;
		kiloGuncelleme.open("KiloVerme.txt", ios::in);
		if (!kiloGuncelleme.is_open())
			cout << " Verilen kilo güncelleme dosyası açılamadı. " << endl;
		string satir;
		while (getline(kiloGuncelleme, satir))
			cout << satir << endl;
		kiloGuncelleme.close();
	}
}


int main()
{
	setlocale(LC_ALL, "Turkish");
	string adSoyad;
	char cinsiyet;
	int yas;
	double boy, kilo;
	cout << " İstenilen bilgileri giriniz. " << endl << " Adınız ve soyadınız: ";
	getline(cin, adSoyad);
	do {
		cout << " Cinsiyetiniz (kadın için 'k' erkek için 'e' tuşlayınız): ";
		cin >> cinsiyet;
		if (cinsiyet != 'k' && cinsiyet != 'e' && cinsiyet != 'K' && cinsiyet != 'E')
			cout << " Lütfen geçerli bir yanıt giriniz. " << endl;
	} while (cinsiyet != 'k' && cinsiyet != 'e' && cinsiyet != 'K' && cinsiyet != 'E');
	cout << " Yaşınız: ";
	cin >> yas;
	cout << " Kilonuz(kg): ";
	cin >> kilo;
	cout << " Boyunuz(cm): ";
	cin >> boy;
	kiloBilgileri kisiselBilgiler;

	AnaMenu(cinsiyet,kilo,boy,yas);

	return 0;
}
void AnaMenu(char cinsiyet, double kilo, double boy, int yas)
{

	system("cls");
	int secenek = 0;
	bool kontrol = true;

		kiloBilgileri kisiselBilgiler;
		cout << " ****************** HOŞGELDİNİZ! ****************** " << endl;
		cout << " Yapmak istediğiniz işlem için başında yazan sayıyı tuşlayınız. " << endl;
		cout << " (1) Günlük su hedefi \n (2) İçilen suyu güncelleme\n (3) Günlük adım sayısı hedefi\n (4) Atılan adım sayısı güncelleme\n";
		cout << " (5) Günlük alınması gereken kalori miktarını hesaplama\n (6) Günlük kalori hedefi\n (7) Alınan kalori miktarını güncelleme\n";
		cout << " (8) Tansiyon bilgilerini girme ve önceki bilgilere erişme\n (9) Kan şekeri bilgilerini girme ve önceki bilgilere erişme\n";
		cout << " (10) Nabız bilgilerini girme ve önceki bilgilere erişme\n (11) İlaç takibi\n (12) Hastane - doktor randevu takibi\n";
		cout << " (13) Vücut kitle indeksi \n (14) İdeal vücut ağırlığı\n (15) Kilo hedefi\n";
		cout << " (16) Kaybedilen kiloyu güncelleme\n (17) Vücut yağ oranı\n (18) Yapılan aktivite ve süresine göre harcanan kaloriyi hesaplama\n";
		cout << " (19) Bazal metabolik hız\n (20) Programdan çıkış\n"; 
		cin >> secenek;    
		switch (secenek)
		{
		case 1:
			SuHedefi();
			break;
		case 2:
			SuGuncelleme();
			break;
		case 3:
			AdimHedefi();
			break;
		case 4:
			AdimGuncelleme();
			break;
		case 5:
			KaloriHesaplama(cinsiyet, kilo, boy, yas);
			break;
		case 6:
			KaloriHedef();
			break;
		case 7:
			KaloriGuncelleme();
			break;
		case 8:
			TansiyonBilgileri();
			break;
		case 9:
			KanSekeriBilgileri();
			break;
		case 10:
			NabizBilgileri();
			break;
		case 11:
			IlacTakibi();
			break;
		case 12:
			RandevuTakibi();
			break;
		case 13:
			VucutKitleİndeksi(boy, kilo, yas);
			break;
		case 14:
			IdealVucutAgirligi(cinsiyet, boy);
			break;
		case 15:
			KiloHedefi(kisiselBilgiler);
			break;
		case 16:
			VerilenKiloGuncelleme(kisiselBilgiler, kilo);
			break;
		case 17:
			VucutYagOraniHesaplama(cinsiyet, boy);
			break;
		case 18:
			HarcananKaloriHesaplama(kilo);
			break;
		case 19:
			BazalMetabolikHiz(cinsiyet, kilo, boy, yas);
			break;
		case 20:
			ProgramdanCikis();
			break;
		}

		char cevap = 0;
		cout << " \n Başka bir işlem yapmak ister misiniz? Cevabınız evet ise 'e' hayır ise 'h' tuşlayınız." << endl;
		do
		{
			cin >> cevap;
			if (cevap != 'e' && cevap != 'E' && cevap != 'h' && cevap != 'H')
			{
				cout << " Girdiğiniz yanıt geçersiz lütfen cevabınızın yukarıda yazıldığı gibi olduğundan emin olunuz.\n";
			}
		} while (cevap != 'e' && cevap != 'E' && cevap != 'h' && cevap != 'H');
		if (cevap == 'h' || cevap == 'H')
			ProgramdanCikis();
		else
		{
			system("cls");
			AnaMenu(cinsiyet, kilo, boy, yas);
		}
}

void SuHedefi()
{
	system("cls");
	cout << " Günlük su hedefinizi ml cinsinden giriniz. " << endl;
	cin >> hedef;
	cout << " Günlük su hedefiniz: " << hedef << " ml." << endl;
	fstream suHedef;
	suHedef.open("SuHedefi.txt", ios::out);
	if (!suHedef.is_open())
		cout << " Hedef dosyası bulunamadı. " << endl;
	suHedef << hedef;
	suHedef.close();
}

void SuGuncelleme()
{
	system("cls");
	double hedef = 0;
	double icilenSu = 0;
	cout << " İçtiğiniz su miktarını ml cinsinden giriniz. " << endl;
	cin >> icilenSu;
	toplamSu += icilenSu;
	cout << " İçtiğiniz toplam su miktarı: " << toplamSu << " ml." << endl;
	ifstream suHedef;
	suHedef.open("SuHedefi.txt", ios::in);
	if (!suHedef.is_open())
		cout << " Hedef dosyası bulunamadı. " << endl;
	suHedef >> hedef;
	if (toplamSu >= hedef)
	{
		cout << " Tebrikler su hedefinize ulaştınız! " << endl;
	}
	else
		cout << " Su hedefinize ulaşamadınız. " << endl;
	suHedef.close();
}

void KaloriHedef()
{
	system("cls");
	cout << " Günlük alınması gereken kalori hedefinizi giriniz. " << endl;
	cin >> kaloriHedef;
	cout << " Kalori hedefiniz: " << kaloriHedef << " kalori." << endl;
}

void KaloriGuncelleme()
{
	system("cls");
	double alinanKalori = 0;
	cout << " Alınan kalori miktarını giriniz. " << endl;
	cin >> alinanKalori;
	kalori.push_back(alinanKalori);
	double toplamKalori = 0;
	for (int i = 0; i < kalori.size(); ++i) {
		toplamKalori += kalori[i];
	}
	cout << " Aldığınız toplam kalori miktarı: " << toplamKalori << " kalori." << endl;
	if (toplamKalori >= kaloriHedef)
		cout << " Tebrikler kalori hedefinize ulaştınız! " << endl;
	else
		cout << " Kalori hedefinize ulaşamadınız. " << endl;
}

void KaloriHesaplama(char cinsiyet,double kilo,double boy, int yas)
{
	system("cls");
	cout << " Alınması gereken kalori miktarını hesaplamak için günlük yapılan aktivite seviyenizin bilinmesi gerekiyor. " << endl;
	cout << " Aşağıdaki seçeneklerden size uygun olanı seçiniz. Seçmek için yanında yazan sayıları tuşlayınız." << endl;
	cout << " Oturarak çalışıyor ve egzersiz yapmıyorsanız. (1)\n Hafif egzersiz yapıyorsanız (haftada 1-3 gün) (2)\n";
	cout << " Orta derecede egzersiz yapıyorsanız (haftada 3-5 gün) (3)\n Aktif egzersiz yapıyorsanız (haftada 6-7 gün) (4)\n";
	cout << " Çok aktif egzersiz yapıyorsanız (sporcu veya fiziksel olarak yoğun işte çalışma) (5)\n";
	int sayi = 0;
	cin >> sayi;
	double bmhK = 0, bmhE = 0, kKalori = 0, eKalori = 0;
	if (cinsiyet == 'k' || cinsiyet == 'K')
	   bmhK = 447.593 + (9.247 * kilo) + (3.098 * boy) - (4.330 * yas);
	else if (cinsiyet == 'e' || cinsiyet == 'E')
       bmhE = 88.362 + (13.397 * kilo) + (4.799 * boy) - (5.677 * yas);
	switch (sayi)
	{
	case 1:
		if (cinsiyet == 'k' || cinsiyet == 'K')
		{
			kKalori = bmhK * 1.2;
			cout << " Almanız gereken günlük kalori miktarı " << kKalori << " kaloridir. " << endl;

		}
		else if (cinsiyet == 'e' || cinsiyet == 'E')
		{
			eKalori = bmhE * 1.2;
			cout << " Almanız gereken günlük kalori miktarı " << eKalori << " kaloridir. " << endl;

		}
		break;
	case 2:
		if (cinsiyet == 'k' || cinsiyet == 'K')
		{
			kKalori = bmhK * 1.375;
			cout << " Almanız gereken günlük kalori miktarı " << kKalori << " kaloridir. " << endl;
		}
		else if (cinsiyet == 'e' || cinsiyet == 'E')
		{
			eKalori = bmhE * 1.375;
			cout << " Almanız gereken günlük kalori miktarı " << eKalori << " kaloridir. " << endl;
		}
		break;
	case 3:
		if (cinsiyet == 'k' || cinsiyet == 'K')
		{
			kKalori = bmhK * 1.55;
			cout << " Almanız gereken günlük kalori miktarı " << kKalori << " kaloridir. " << endl;
		}
		else if (cinsiyet == 'e' || cinsiyet == 'E')
		{
			eKalori = bmhE * 1.55;
			cout << " Almanız gereken günlük kalori miktarı " << eKalori << " kaloridir. " << endl;
		}
		break;
	case 4:
		if (cinsiyet == 'k' || cinsiyet == 'K')
		{
			kKalori = bmhK * 1.725;
			cout << " Almanız gereken günlük kalori miktarı " << kKalori << " kaloridir. " << endl;
		}
		else if (cinsiyet == 'e' || cinsiyet == 'E')
		{
			eKalori = bmhE * 1.725;
			cout << " Almanız gereken günlük kalori miktarı " << eKalori << " kaloridir. " << endl;
		}
		break;
	case 5:
		if (cinsiyet == 'k' || cinsiyet == 'K')
		{
			kKalori = bmhK * 1.9;
			cout << " Almanız gereken günlük kalori miktarı " << kKalori << " kaloridir. " << endl;
		}
		else if (cinsiyet == 'e' || cinsiyet == 'E')
		{
			eKalori = bmhE * 1.9;
			cout << " Almanız gereken günlük kalori miktarı " << eKalori << " kaloridir. " << endl;
		}
		break;
	}
}
void AdimHedefi()
{
	system("cls");
	cout << " Günlük adım hedefinizi giriniz. " << endl;
	cin >> adim;
	cout << " Adım hedefiniz: " << adim << " adım." << endl;
	fstream adimHedef;
	adimHedef.open("AdımHedefi.txt", ios::out);
	if (!adimHedef.is_open())
		cout << " Adim hedefi dosyası açılamadı. " << endl;
	adimHedef << adim;
	adimHedef.close();
}
void AdimGuncelleme()
{
	system("cls");
	int atilanAdim = 0;
	cout << " Attığınız adım sayısını giriniz. " << endl;
	cin >> atilanAdim;
	toplamAdim += atilanAdim;
	ifstream adimHedef;
	adimHedef.open("AdımHedefi.txt", ios::in);
	if (!adimHedef.is_open())
		cout << " Adim hedefi dosyası açılamadı. " << endl;
	adimHedef >> adim;
	cout << " Attığınız toplam adım sayısı: " << toplamAdim << " adım." << endl;
	if (toplamAdim >= adim)
		cout << " Tebrikler adım hedefinize ulaştınız! " << endl;
	else
		cout << " Adım hedefinize ulaşamadınız. " << endl;
	adimHedef.close();
}

void TansiyonBilgileri()
{
	system("cls");
	string tarih, tansiyon;
	cin.ignore();
	cout << " Tansiyonunuzu ölçtüğünüz tarihi ve tansiyon bilgilerini giriniz. " << endl;
	cout << " Tarih: ";
	getline(cin, tarih);
	cout << " Tansiyon: ";
	getline(cin, tansiyon);
	ofstream tansiyonDosyasi;
	tansiyonDosyasi.open("TansiyonBilgileri.txt", ios::app);
	if (!tansiyonDosyasi.is_open())
		cout << " Tansiyon dosyası açılamadı. " << endl;
	else
		tansiyonDosyasi << tarih << "\t" << tansiyon << endl;
	tansiyonDosyasi.close();
	char cevap;
	do
	{
		cout << " Girdiğiniz bütün tansiyon bilgilerini görmek ister misiniz? (cevabınız evet ise 'e' hayır ise 'h' tuşlayınız) " << endl;
		cin >> cevap;
		if (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H')
		{
			cout << " Yanıtınız geçersiz lütfen 'evet' veya 'hayır' yanıtını giriniz. " << endl;
		}
	} while (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H');
	if (cevap == 'e' || cevap == 'E')
	{
		ifstream tansiyonDosyasi;
		tansiyonDosyasi.open("TansiyonBilgileri.txt", ios::in);
		if (!tansiyonDosyasi.is_open())
			cout << " Tansiyon dosyası açılamadı. " << endl;
		string satir;
		while (getline(tansiyonDosyasi, satir))
		{
			cout << satir << endl;
		}
		tansiyonDosyasi.close();
	}
}
void KanSekeriBilgileri()
{
	system("cls");
	string tarih, kanSekeri;
	cin.ignore();
	cout << " Kan şekerinizi ölçtüğünüz tarihi ve kan şekeri bilgilerini giriniz. " << endl;
	cout << " Tarih: ";
	getline(cin, tarih);
	cout << " Kan şekeri: ";
	getline(cin, kanSekeri);
	ofstream kanSekeriDosyasi;
	kanSekeriDosyasi.open("KanŞekeriBilgileri.txt", ios::app);
	if (!kanSekeriDosyasi.is_open())
		cout << " Kan şekeri dosyası açılamadı. " << endl;
	else
		kanSekeriDosyasi << tarih << "\t" << kanSekeri << endl;
	kanSekeriDosyasi.close();
	char cevap;
	do
	{
		cout << " Girdiğiniz bütün kan şekeri bilgilerini görmek ister misiniz? (cevabınız evet ise 'e' hayır ise 'h' tuşlayınız) " << endl;
		cin >> cevap;
		if (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H')
		{
			cout << " Yanıtınız geçersiz lütfen 'evet' veya 'hayır' yanıtını giriniz. " << endl;
		}
	} while (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H');
	if (cevap == 'e' || cevap == 'E')
	{
		ifstream kanSekeriDosyasi;
		kanSekeriDosyasi.open("KanŞekeriBilgileri.txt", ios::in);
		if (!kanSekeriDosyasi.is_open())
			cout << " Kan şekeri dosyası açılamadı. " << endl;
		string satir;
		while (getline(kanSekeriDosyasi, satir))
		{
			cout << satir << endl;
		}
		kanSekeriDosyasi.close();
	}
}

void NabizBilgileri()
{
	system("cls");
	string tarih, nabiz;
	cin.ignore();
	cout << " Nabzınızı ölçtüğünüz tarihi ve nabız bilgilerini giriniz. " << endl;
	cout << " Tarih: ";
	getline(cin, tarih);
	cout << " Nabız: ";
	getline(cin, nabiz);
	ofstream nabizDosyasi;
	nabizDosyasi.open("NabızBilgileri.txt", ios::app);
	if (!nabizDosyasi.is_open())
		cout << " Nabız dosyası açılamadı. " << endl;
	else
		nabizDosyasi << tarih << "\t" << nabiz << endl;
	nabizDosyasi.close();
	char cevap;
	do
	{
		cout << " Girdiğiniz bütün nabız bilgilerini görmek ister misiniz? (cevabınız evet ise 'e' hayır ise 'h' tuşlayınız) " << endl;
		cin >> cevap;
		if (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H')
		{
			cout << " Yanıtınız geçersiz lütfen 'evet' veya 'hayır' yanıtını giriniz. " << endl;
		}
	} while (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H');
	if (cevap == 'e' || cevap == 'E')
	{
		ifstream nabizDosyasi;
		nabizDosyasi.open("NabızBilgileri.txt", ios::in);
		if (!nabizDosyasi.is_open())
			cout << " Kan şekeri dosyası açılamadı. " << endl;
		string satir;
		while (getline(nabizDosyasi, satir))
		{
			cout << satir << endl;
		}
		nabizDosyasi.close();
	}
}

void IlacTakibi()
{
	system("cls");
	string ilacAdi, tarih, saat, icilenMiktar;
	cin.ignore();
	cout << " İlaç bilgilerini giriniz. " << endl;
	cout << " İlaç adı: ";
	getline(cin, ilacAdi);
	cout << " İçtiğiniz tarih: ";
	getline(cin, tarih);
	cout << " İçtiğiniz saat: ";
	getline(cin, saat);
	cout << " İçtiğiniz miktar: ";
	getline(cin, icilenMiktar);
	ofstream ilacDosyasi;
	ilacDosyasi.open("İlaçTakibi.txt", ios::app);
	if (!ilacDosyasi.is_open())
	{
		cout << " İlaç takip dosyası açılamadı. " << endl;
	}
	ilacDosyasi << ilacAdi << "\t" << tarih << "\t" << saat << "\t" << icilenMiktar << endl;
	ilacDosyasi.close();
	char cevap;
	do
	{
		cout << " Girdiğiniz bütün ilaç bilgilerini görmek ister misiniz? (cevabınız evet ise 'e' hayır ise 'h' tuşlayınız) " << endl;
		cin >> cevap;
		if (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H')
		{
			cout << " Yanıtınız geçersiz lütfen 'evet' veya 'hayır' yanıtını giriniz. " << endl;
		}
	} while (cevap != 'e' && cevap != 'h' && cevap != 'E' && cevap != 'H');
	if (cevap == 'e' || cevap == 'E')
	{
		ifstream ilacDosyasi;
		ilacDosyasi.open("İlaçTakibi.txt", ios::in);
		if (!ilacDosyasi.is_open())
			cout << " İlaç takip dosyası açılamadı. " << endl;
		else
		{
			string satir;
			while (getline(ilacDosyasi, satir))
				cout << satir << endl;
		}
		ilacDosyasi.close();
	}
}

void RandevuTakibi()
{
	system("cls");
	string doktor, hastane, klinik, tarih, saat;
	cout << " Yeni randevu girmek için 'y' eski randevuları görmek için 'e' tuşlayınız.\n";
	char cevap = 0;
	cin >> cevap;
	cin.ignore();
	do {
		if (cevap != 'y' && cevap != 'Y' && cevap != 'e' && cevap != 'Y')
			cout << " Yanıtınız geçersiz. Lütfen geçerli bir yanıt giriniz.\n";
	} while (cevap != 'y' && cevap != 'Y' && cevap != 'e' && cevap != 'Y');
	if (cevap == 'y' || cevap == 'Y')
	{
		cout << " İstenilen bilgileri giriniz.\n";
		cout << " Hastanenin adı : ";
		getline(cin, hastane);
		cout << " Doktorun adı: ";
		getline(cin, doktor);
		cout << " Klinik: ";
		getline(cin, klinik);
		cout << " Tarih: "; 
		getline(cin, tarih);
		cout << " Saat: "; 
		getline(cin, saat);
		ofstream randevu;
		randevu.open("RandevuTakibi.txt", ios::app);
		if (!randevu.is_open())
			cout << " Randevu dosyası açılamadı!\n";
		randevu << hastane << "\t" << doktor << "\t" << klinik << "\t" << tarih << "\t" << saat << "\n";
		randevu.close();
	}
	else
	{
		ifstream randevu;
		randevu.open("RandevuTakibi.txt", ios::in);
		if (!randevu.is_open())
			cout << " Randevu dosyası açılamadı!\n";
		string satir;
		while (getline(randevu, satir))
			cout << satir << endl;
		randevu.close();
	}
}

void VucutKitleİndeksi(double boy,double kilo, int yas)
{
	system("cls");
	cout << " Vücut kitle indeksi, kişinin vücudundaki kilo fazlalığı ve yağ oranı hakkında fikir vermek için kullanılır. Vücut kitle indeksi değerleri aşağıdaki gibidir :\n";
	cout << " 18.5 ve altı: Zayıf\n 18.5 - 24.9: Normal kilolu\n 25.0 - 29.9 : Fazla kilolu\n 30.0 - 34.9 : Obez(1. derece obezite)\n";
	cout << " 35.0 - 39.9 : Aşırı obez(2. derece obezite)\n 40 ve üstü : Morbid obez(3. derece obezite)\n";
	double metreboy = (boy / 100);
	double vki = (kilo / pow(metreboy,2));
	cout << " Vücut kitle indeksiniz: " << vki << " kg/m^2" << endl;
	if (yas <= 18)
		cout << " 18 yaş ve altı için ideal vücut kitle indeksi cinsiyete göre değiştiğinden indeks ölçümünün bir uzman tarafından yapılması önerilir.\n";
	else if (yas >= 19 && yas <=24)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 19 - 24 kg/m^2 arasıdır." << endl;
	else if (yas >= 25 && yas <= 34)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 20 - 25 kg/m^2 arasıdır." << endl;
	else if (yas >= 35 && yas <= 44)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 21 - 26 kg/m^2 arasıdır. " << endl;
	else if (yas >= 45 && yas <= 54)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 22 - 27 kg/m^2 arasıdır. " << endl;
	else if (yas >= 55 && yas <= 64)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 23 - 28 kg/m^2 arasıdır. " << endl;
	else if (yas >= 65)
		cout << " Yaşınıza göre ideal vücut kitle indeksiniz 24 - 29 kg/m^2 arasıdır. " << endl;
}

void IdealVucutAgirligi(char cinsiyet, double boy)
{
	system("cls");
	double iva = 0;
	if (cinsiyet == 'k' || cinsiyet == 'K')
	{
		iva = 45.5 + 2.3 * ((boy / 2.54) - 60);
		cout << " İdeal vücut ağırlığınız: " << iva << " kg\n";
	}
	else if (cinsiyet == 'e' || cinsiyet == 'E')
	{
		iva = 50 + 2.3 * ((boy / 2.54) - 60);
		cout << " İdeal vücut ağırlığınız: " << iva << " kg\n";
	}
}

void VucutYagOraniHesaplama(char cinsiyet,double boy)
{
	system("cls");
	double boyun = 0, bel = 0, kalca = 0;
	double yagOrani = 0;
	cout << " Yağ oranınızın hesaplanabilmesi için bazı bilgilere ihtiyacımız var. Lütfen istenilen bilgileri giriniz.\n";
	if (cinsiyet == 'k' || cinsiyet == 'K')
	{
		cout << " Boyun çevreniz (cm):";
		cin >> boyun;
		cout << " Bel çevreniz (cm):";
		cin >> bel;
		cout << " Kalça çevreniz (cm):";
		cin >> kalca;
		yagOrani = 495 / (1.29579 - 0.35004 * log10(bel + kalca - boyun) + 0.22100 * log10(boy)) - 450;
		cout << " Vücut yağ oranınız: %" << yagOrani << endl;
	}
	else
	{
		cout << " Boyun çevreniz (cm):";
		cin >> boyun;
		cout << " Bel çevreniz (cm):";
		cin >> bel;
		yagOrani = 495 / (1.0324 - 0.19077 * log10(bel - boyun) + 0.15456 * log10(boy)) - 450;
		cout << " Vücut yağ oranınız: %" << yagOrani << endl;
	}
	cout << " Bu tür ölçümler her zaman doğru sonucu vermediğinden kesin bir sonuç almak için profosyenel birine başvurmanız daha\n doğru olacaktır.\n";
}

void HarcananKaloriHesaplama(double kilo)
{
	system("cls");
	unordered_map<string, double> kalori;
	kalori["yuruyus"] = 4.0;
	kalori["kosu"] = 10.0;
	kalori["bisiklet"] = 8.0;
	kalori["yuzme"] = 7.0;
	kalori["tenis"] = 7.0;
	kalori["masa_tenisi"] = 4.0;
	kalori["basketbol"] = 7.5;
	kalori["voleybol"] = 4.0;
	kalori["futbol"] = 8.5;
	kalori["ip_atlama"] = 12.0;
	kalori["dans"] = 5.5;
	kalori["aerobik_dans"] = 7.0;
	kalori["agirlik_kaldirma"] = 6.0;
	kalori["mekik"] = 8.0;
	kalori["sinav"] = 8.0;
	kalori["kardiyo"] = 7.0;
	kalori["boks"] = 10.0;
	kalori["yoga"] = 3.0;
	kalori["kayak"] = 9.0;
	kalori["pilates"] = 3.1;

	string aktivite;
	double süre = 0;
	double kaloriOrani = 0;
	cout << " Eğer yaptığınız aktivite aşağıda bulunmuyorsa '0' bulunuyorsa '1' tuşlayınız.\n";
	cout << " Aktiviteler: yuruyus,kosu,bisiklet,yuzme,tenis,masa_tenisi,basketbol,voleybol,futbol,ip_atlama,dans,\n";
	cout << "aerobik_dans,agirlik_kaldirma,mekik,sinav,kardiyo,boks,yoga,kayak,pilates\n";
	int secim = 0;
	cin >> secim;
	do
	{
		if (secim == 0)
		{
			cout << " Yakılan kaloriyi hesaplayabilmek için yaptığınız aktivitenin MET (Metabolic Equivalent of Task) değerinin bilinmesi \n gerekiyor. MET değeri bir aktivitenin enerji değerini ifade eder.";
			cout << " İnternette 'yaptığınız aktivitenin adı' ve \n 'MET değeri' aratarak yaptığınız aktivitenin MET değerini kolayca bulabilirisiniz.\n";
			cout << " Aktivite MET değeri: ";
			double met = 0;
			cin >> met;
			cout << " Aktivite süresini giriniz (dk): ";
			cin >> süre;
			double yakilanKalori = (met * kilo * süre) / 60;
			cout << " Yakılan kalori: " << yakilanKalori << " kaloridir.\n";
		}
		else if (secim == 1)
		{
			do
			{
				cout << " Yaptığınız aktiviteyi giriniz. ";
				cin >> aktivite;
				if (kalori.find(aktivite) != kalori.end())
				{
					kaloriOrani = kalori[aktivite];
					cout << " Aktivite süresini giriniz (dk): ";
					cin >> süre;
					double yakilanKalori = (kaloriOrani * kilo * süre) / 60;
					cout << " Yakılan kalori: " << yakilanKalori << " kaloridir.\n";
				}
				else
					cout << " Girdiğiniz aktivite geçersiz lütfen aktivitenizi yukarıda yazıldığı gibi yazınız.\n";
			} while (kalori.find(aktivite) == kalori.end());
		}
		else
			cout << " Girdiğiniz aktivite geçersiz lütfen aktivitenizi yukarıda yazıldığı gibi yazınız.\n";
	} while (secim != 0 && secim != 1);
}

void BazalMetabolikHiz(char cinsiyet, double kilo, double boy, int yas)
{
	system("cls");
	cout << " Bazal metabolizma, vücudun dinlenme durumunda iken bile çalışması için ihtiyaç duyduğu enerji miktarını ifade eder.\n";
	cout << " Bazal metabolik hız (BMH), kalori cinsinden ölçülür ve vücut fonksiyonlarının devamı için gerekli olan enerjiyi sağlar.\n";
	double bmh = 0;
	if (cinsiyet == 'k' || cinsiyet == 'K')
		bmh = 447.593 + (9.247 * kilo) + (3.098 * boy) - (4.330 * yas);
	else
		bmh = 88.362 + (13.397 * kilo) + (4.799 * boy) - (5.677 * yas);
	cout << " Bazal metabolik hızınız: " << bmh << " kaloridir." << endl;
	cout << " Bu değer yaklaşık bir değerdir daha kesin sonuçlar elde edebilmek için bir profesyonele danışmanız önerilir.\n";
}

int ProgramdanCikis()
{
	system("cls");
	cout << " Programdan çıkılıyor...";
	exit(0);
}



