#ifndef ATLET_H_INCLUDED
#define ATLET_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define Nil NULL

typedef struct elmAtlet *adrAtlet;

struct infotypeAtlet {
    string idAtlet;
    string nama;
    double beratBadan;
    double tinggiBadan;
    double bmi;
    string kategoriBMI;
};

struct elmAtlet {
    infotypeAtlet info;
    adrAtlet next;
};

struct ListAtlet {
    adrAtlet first;
};

void createListAtlet(ListAtlet &L);
/* I.S. sembarang
   F.S. terbentuk list atlet kosong */

adrAtlet alokasiAtlet(infotypeAtlet x);
/* I.S. x terdefinisi
   F.S. mengembalikan alamat elemen atlet baru */

void dealokasiAtlet(adrAtlet &P);
/* I.S. P terdefinisi
   F.S. memori P dikembalikan ke sistem dan P = Nil */

double hitungBMI(double beratBadan, double tinggiBadan);
/* I.S. beratBadan dan tinggiBadan terdefinisi
   F.S. mengembalikan nilai BMI atlet */

string tentukanKategoriBMI(double bmi);
/* I.S. nilai bmi terdefinisi
   F.S. mengembalikan kategori BMI (Kurus/Ideal/Berlebih) */

void insertFirstAtlet(ListAtlet &L, adrAtlet P);
/* I.S. L mungkin kosong, P terdefinisi
   F.S. P menjadi elemen pertama pada list L */

void deleteFirstAtlet(ListAtlet &L, adrAtlet &P);
/* I.S. L mungkin kosong
   F.S. elemen pertama dilepas dan disimpan di P */

void deleteAfterAtlet(ListAtlet &L, adrAtlet Prec, adrAtlet &P);
/* I.S. L tidak kosong, Prec terdefinisi
   F.S. elemen setelah Prec dilepas dan disimpan di P */

void deleteAtletByID(ListAtlet &L, string idAtlet, adrAtlet &P);
/* I.S. L dan idAtlet terdefinisi
   F.S. elemen atlet yang sesuai dilepas ke P, atau P = Nil */

adrAtlet findAtletByID(ListAtlet L, string idAtlet);
/* I.S. L dan idAtlet terdefinisi
   F.S. mengembalikan alamat atlet dengan idAtlet tersebut, atau Nil */

adrAtlet getAtletByNomor(ListAtlet L, int nomor);
/* I.S. L dan nomor >= 1 terdefinisi
   F.S. mengembalikan alamat atlet urutan ke-nomor, atau Nil */

void showAllAtlet(ListAtlet L);
/* I.S. L terdefinisi
   F.S. seluruh data atlet ditampilkan ke layar */

int countAtlet(ListAtlet L);
/* I.S. L terdefinisi
   F.S. mengembalikan jumlah elemen pada list L */

#endif
