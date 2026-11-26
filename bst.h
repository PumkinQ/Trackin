#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>
#include <string>
#include "sesi.h"

using namespace std;

#define Nil NULL

typedef struct nodeBST *adrBST;

struct nodeBST {
    infotypeSesi info;
    string namaAtlet;
    adrBST left;
    adrBST right;
};

struct TreeBest {
    adrBST root;
};

void createTreeBest(TreeBest &T);
/* I.S. sembarang
   F.S. terbentuk pohon BST kosong */

adrBST alokasiNodeBST(infotypeSesi x, string namaAtlet);
/* I.S. x dan namaAtlet terdefinisi
   F.S. mengembalikan alamat node BST baru */

void dealokasiNodeBST(adrBST &P);
/* I.S. P terdefinisi
   F.S. memori P dikembalikan ke sistem dan P = Nil */

void insertBST(adrBST &root, adrBST P);
/* I.S. root mungkin Nil, P terdefinisi
   F.S. P disisipkan ke BST terurut berdasarkan skorBest */

void dealokasiSemuaBST(adrBST &root);
/* I.S. root terdefinisi
   F.S. seluruh node pada BST didealokasi dan root = Nil */

void sinkronkanBST(ListSesi LS, TreeBest &T);
/* I.S. LS dan T terdefinisi
   F.S. T dibangun ulang berisi seluruh sesi berstatus BEST! dari LS */

adrBST findBestTertinggi(TreeBest T);
/* I.S. T terdefinisi
   F.S. mengembalikan alamat node dengan skorBest tertinggi, atau Nil */

void showLeaderboardBST(adrBST root);
/* I.S. root terdefinisi
   F.S. menampilkan rekor BEST! dari skor tertinggi ke terendah */

void cariBestMinimalSkor(adrBST root, double minSkor, int &jumlahKetemu);
/* I.S. root, minSkor, dan jumlahKetemu terdefinisi
   F.S. menampilkan rekor dengan skorBest >= minSkor dan memperbarui jumlahKetemu */

#endif
