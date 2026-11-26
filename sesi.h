#ifndef SESI_H_INCLUDED
#define SESI_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdlib>
#include "atlet.h"
#include "cabang.h"

using namespace std;

#define Nil NULL

typedef struct elmSesi *adrSesi;

struct infotypeSesi {
    string idSesi;
    string cabang;
    string subJenis;
    double targetJarak;
    double targetPace;
    double jarakAktual;
    double waktuAktual;
    double paceAktual;
    string satuanPace;
    string statusEvaluasi;
    double skorBest;
};

struct elmSesi {
    infotypeSesi info;
    adrSesi next;
    adrAtlet parentAtlet;
    adrCabang parentCabang;
};

struct ListSesi {
    adrSesi first;
};

void createListSesi(ListSesi &L);
/* I.S. sembarang
   F.S. terbentuk list sesi kosong */

adrSesi alokasiSesi(infotypeSesi x, adrAtlet atlet, adrCabang cabangNode);
/* I.S. x, atlet, dan cabangNode terdefinisi
   F.S. mengembalikan alamat elemen sesi baru */

void dealokasiSesi(adrSesi &P);
/* I.S. P terdefinisi
   F.S. memori P dikembalikan ke sistem dan P = Nil */

void insertFirstSesi(ListSesi &L, adrSesi P);
/* I.S. L mungkin kosong, P terdefinisi
   F.S. P menjadi elemen pertama pada list L */

void deleteFirstSesi(ListSesi &L, adrSesi &P);
/* I.S. L mungkin kosong
   F.S. elemen pertama dilepas dan disimpan di P */

void deleteAfterSesi(ListSesi &L, adrSesi Prec, adrSesi &P);
/* I.S. L tidak kosong, Prec terdefinisi
   F.S. elemen setelah Prec dilepas dan disimpan di P */

void deleteSesiByID(ListSesi &L, string idSesi, adrSesi &P);
/* I.S. L dan idSesi terdefinisi
   F.S. elemen sesi yang sesuai dilepas ke P, atau P = Nil */

int countSesi(ListSesi L);
/* I.S. L terdefinisi
   F.S. mengembalikan jumlah elemen pada list L */

void putusRelasiAtlet(ListSesi &L, adrAtlet P);
/* I.S. L dan P terdefinisi
   F.S. semua pointer parentAtlet yang menunjuk ke P diubah menjadi Nil */

double hitungPace(double jarakKm, double waktuMenit);
/* I.S. jarakKm dan waktuMenit terdefinisi
   F.S. mengembalikan nilai pace (menit/km) */

double hitungPaceInterval(double jarakMeter, double waktuMenit);
/* I.S. jarakMeter dan waktuMenit terdefinisi
   F.S. mengembalikan nilai pace interval (menit/100m) */

double hitungKecepatan(double jarakKm, double waktuMenit);
/* I.S. jarakKm dan waktuMenit terdefinisi
   F.S. mengembalikan kecepatan (km/jam) */

double hitungPaceRenang(double jarakMeter, double waktuMenit);
/* I.S. jarakMeter dan waktuMenit terdefinisi
   F.S. mengembalikan nilai pace renang (menit/100m) */

double hitungPaceMendayung(double jarakMeter, double waktuMenit);
/* I.S. jarakMeter dan waktuMenit terdefinisi
   F.S. mengembalikan nilai pace mendayung (menit/500m) */

bool validasiKecepatan(string cabang, double kecepatanKmh);
/* I.S. cabang dan kecepatanKmh terdefinisi
   F.S. mengembalikan true jika kecepatan rasional untuk cabang tersebut */

void prediksiTargetRNG(adrAtlet atlet, adrCabang cabangNode, string subJenis,
                       int jumlahSesi, double &targetJarak, double &targetPace, string &satuanPace);
/* I.S. atlet, cabangNode, subJenis, dan jumlahSesi terdefinisi
   F.S. menghasilkan targetJarak, targetPace, dan satuanPace menggunakan RNG */

string evaluasiPerforma(string cabang, double targetJarak, double targetPace,
                        double jarakAktual, double paceAktual);
/* I.S. data target dan aktual terdefinisi
   F.S. mengembalikan status evaluasi (BEST!, ON TARGET, atau KURANG LATIHAN) */

double hitungSkorBest(string cabang, string statusEvaluasi, double targetJarak, double targetPace,
                      double jarakAktual, double paceAktual);
/* I.S. data target, aktual, dan statusEvaluasi terdefinisi
   F.S. mengembalikan skor persentase BEST!, atau 0 jika bukan BEST! */

adrSesi getSesiByNomor(ListSesi L, int nomor);
/* I.S. L dan nomor >= 1 terdefinisi
   F.S. mengembalikan alamat sesi urutan ke-nomor, atau Nil */

void showAllSesi(ListSesi L);
/* I.S. L terdefinisi
   F.S. seluruh riwayat sesi ditampilkan ke layar */

void showSesiByAtlet(ListSesi L, adrAtlet atletTarget);
/* I.S. L dan atletTarget terdefinisi
   F.S. menampilkan riwayat sesi, total jarak, dan jumlah BEST! milik atletTarget */

void showSesiByCabang(ListSesi L, string cabangCari);
/* I.S. L dan cabangCari terdefinisi
   F.S. menampilkan riwayat sesi yang sesuai dengan cabangCari */

bool undoSesiTerakhir(ListSesi &L);
/* I.S. L terdefinisi
   F.S. elemen pertama L dihapus, mengembalikan true jika berhasil */

#endif
