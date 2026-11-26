#include "cabang.h"

void createListCabang(ListCabang &L) {
    L.first = Nil;
    L.last = Nil;
}

adrCabang alokasiCabang(infotypeCabang x) {
    adrCabang P = new elmCabang;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void dealokasiCabang(adrCabang &P) {
    delete P;
    P = Nil;
}

void insertLastCabang(ListCabang &L, adrCabang P) {
    if (P != Nil) {
        if (L.first == Nil && L.last == Nil) {
            L.first = P;
            L.last = P;
        } else {
            P->prev = L.last;
            L.last->next = P;
            L.last = P;
        }
    }
}

void deleteLastCabang(ListCabang &L, adrCabang &P) {
    if (L.first == Nil) {
        P = Nil;
    } else if (L.first == L.last) {
        P = L.last;
        L.first = Nil;
        L.last = Nil;
        P->prev = Nil;
        P->next = Nil;
    } else {
        P = L.last;
        L.last = L.last->prev;
        L.last->next = Nil;
        P->prev = Nil;
        P->next = Nil;
    }
}

adrCabang findCabangByKode(ListCabang L, string kodeCabang) {
    adrCabang P = L.first;
    adrCabang hasil = Nil;
    bool ketemu = false;

    while (P != Nil && !ketemu) {
        if (P->info.kodeCabang == kodeCabang) {
            hasil = P;
            ketemu = true;
        } else {
            P = P->next;
        }
    }

    return hasil;
}

adrCabang findCabangByNama(ListCabang L, string namaCabang) {
    adrCabang P = L.first;
    adrCabang hasil = Nil;
    bool ketemu = false;

    while (P != Nil && !ketemu) {
        if (P->info.namaCabang == namaCabang) {
            hasil = P;
            ketemu = true;
        } else {
            P = P->next;
        }
    }

    return hasil;
}

void showAllCabangMaju(ListCabang L) {
    if (L.first == Nil) {
        cout << "Belum ada cabang olahraga terdaftar.\n";
    } else {
        adrCabang P = L.first;
        int nomor = 1;
        while (P != Nil) {
            cout << nomor << ". " << P->info.namaCabang << "\n";
            P = P->next;
            nomor++;
        }
    }
}

void showAllCabangMundur(ListCabang L) {
    if (L.last == Nil) {
        cout << "Belum ada cabang olahraga terdaftar.\n";
    } else {
        adrCabang P = L.last;
        int nomor = 1;
        while (P != Nil) {
            cout << nomor << ". " << P->info.namaCabang << "\n";
            P = P->prev;
            nomor++;
        }
    }
}

void initCabangOlahraga(ListCabang &LC) {
    infotypeCabang c1;
    c1.kodeCabang = "CB1";
    c1.namaCabang = "Lari";
    insertLastCabang(LC, alokasiCabang(c1));

    infotypeCabang c2;
    c2.kodeCabang = "CB2";
    c2.namaCabang = "Jalan Cepat";
    insertLastCabang(LC, alokasiCabang(c2));

    infotypeCabang c3;
    c3.kodeCabang = "CB3";
    c3.namaCabang = "Sepeda";
    insertLastCabang(LC, alokasiCabang(c3));

    infotypeCabang c4;
    c4.kodeCabang = "CB4";
    c4.namaCabang = "Berenang";
    insertLastCabang(LC, alokasiCabang(c4));

    infotypeCabang c5;
    c5.kodeCabang = "CB5";
    c5.namaCabang = "Mendayung";
    insertLastCabang(LC, alokasiCabang(c5));
}
