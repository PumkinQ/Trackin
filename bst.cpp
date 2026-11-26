#include "bst.h"

void createTreeBest(TreeBest &T) {
    T.root = Nil;
}

adrBST alokasiNodeBST(infotypeSesi x, string namaAtlet) {
    adrBST P = new nodeBST;
    P->info = x;
    P->namaAtlet = namaAtlet;
    P->left = Nil;
    P->right = Nil;
    return P;
}

void dealokasiNodeBST(adrBST &P) {
    delete P;
    P = Nil;
}

void insertBST(adrBST &root, adrBST P) {
    if (P != Nil) {
        if (root == Nil) {
            root = P;
        } else if (P->info.skorBest < root->info.skorBest) {
            insertBST(root->left, P);
        } else {
            insertBST(root->right, P);
        }
    }
}

adrBST findBestTertinggi(TreeBest T) {
    adrBST P = T.root;

    if (P != Nil) {
        while (P->right != Nil) {
            P = P->right;
        }
    }

    return P;
}

void tampilNodeBST(adrBST P) {
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "- [Skor: +" << P->info.skorBest << "%] "
         << P->namaAtlet << " | " << P->info.cabang;
    if (P->info.subJenis != P->info.cabang) {
        cout << " (" << P->info.subJenis << ")";
    }
    cout << " | Aktual: " << P->info.jarakAktual << " KM ("
         << P->info.paceAktual << " " << P->info.satuanPace << ")\n";
}

void showLeaderboardBST(adrBST root) {
    if (root != Nil) {
        showLeaderboardBST(root->right);
        tampilNodeBST(root);
        showLeaderboardBST(root->left);
    }
}

void cariBestMinimalSkor(adrBST root, double minSkor, int &jumlahKetemu) {
    if (root != Nil) {
        cariBestMinimalSkor(root->right, minSkor, jumlahKetemu);

        if (root->info.skorBest >= minSkor) {
            tampilNodeBST(root);
            jumlahKetemu++;
        }

        if (root->info.skorBest > minSkor) {
            cariBestMinimalSkor(root->left, minSkor, jumlahKetemu);
        }
    }
}

void dealokasiSemuaBST(adrBST &root) {
    if (root != Nil) {
        dealokasiSemuaBST(root->left);
        dealokasiSemuaBST(root->right);
        dealokasiNodeBST(root);
    }
}

void sinkronkanBST(ListSesi LS, TreeBest &T) {
    dealokasiSemuaBST(T.root);

    adrSesi P = LS.first;
    while (P != Nil) {
        if (P->info.statusEvaluasi == "BEST!") {
            string namaAtlet = "Atlet Dihapus";
            if (P->parentAtlet != Nil) {
                namaAtlet = P->parentAtlet->info.nama;
            }
            insertBST(T.root, alokasiNodeBST(P->info, namaAtlet));
        }
        P = P->next;
    }
}
