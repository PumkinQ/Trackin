#ifndef CABANG_H_INCLUDED
#define CABANG_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define Nil NULL

typedef struct elmCabang *adrCabang;

struct infotypeCabang {
    string kodeCabang;
    string namaCabang;
};

struct elmCabang {
    infotypeCabang info;
    adrCabang next;
    adrCabang prev;
};

struct ListCabang {
    adrCabang first;
    adrCabang last;
};

void createListCabang(ListCabang &L);
/* I.S. sembarang
   F.S. terbentuk list cabang kosong */

adrCabang alokasiCabang(infotypeCabang x);
/* I.S. x terdefinisi
   F.S. mengembalikan alamat elemen cabang baru */

void dealokasiCabang(adrCabang &P);
/* I.S. P terdefinisi
   F.S. memori P dikembalikan ke sistem dan P = Nil */

void insertLastCabang(ListCabang &L, adrCabang P);
/* I.S. L mungkin kosong, P terdefinisi
   F.S. P menjadi elemen terakhir pada list L */

void deleteLastCabang(ListCabang &L, adrCabang &P);
/* I.S. L mungkin kosong
   F.S. elemen terakhir dilepas dan disimpan di P */

adrCabang findCabangByKode(ListCabang L, string kodeCabang);
/* I.S. L dan kodeCabang terdefinisi
   F.S. mengembalikan alamat cabang sesuai kode, atau Nil */

adrCabang findCabangByNama(ListCabang L, string namaCabang);
/* I.S. L dan namaCabang terdefinisi
   F.S. mengembalikan alamat cabang sesuai nama, atau Nil */

void showAllCabangMaju(ListCabang L);
/* I.S. L terdefinisi
   F.S. seluruh cabang ditampilkan dari first ke last */

void showAllCabangMundur(ListCabang L);
/* I.S. L terdefinisi
   F.S. seluruh cabang ditampilkan dari last ke first */

void initCabangOlahraga(ListCabang &LC);
/* I.S. LC kosong
   F.S. LC terisi 5 cabang olahraga utama */

#endif
