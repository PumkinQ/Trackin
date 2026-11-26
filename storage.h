#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "atlet.h"
#include "cabang.h"
#include "sesi.h"

using namespace std;

bool sesiSudahAda(ListSesi LS, string idSesi);
/* I.S. LS dan idSesi terdefinisi
   F.S. mengembalikan true jika idSesi sudah ada di LS */

void simpanSemuaData(ListAtlet LA, ListSesi LS, string namaFile);
/* I.S. LA, LS, dan namaFile terdefinisi
   F.S. seluruh data atlet dan sesi disimpan ke file namaFile */

void muatSemuaData(ListAtlet &LA, ListCabang LC, ListSesi &LS, string namaFile);
/* I.S. LA, LC, LS terinisialisasi dan namaFile terdefinisi
   F.S. data dari namaFile dimuat ke dalam LA dan LS beserta relasinya */

void tampilIsiFile(string namaFile);
/* I.S. namaFile terdefinisi
   F.S. isi file namaFile ditampilkan ke layar */

#endif
