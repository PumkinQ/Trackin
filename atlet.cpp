#include "atlet.h"

void createListAtlet(ListAtlet &L) {
    L.first = Nil;
}

adrAtlet alokasiAtlet(infotypeAtlet x) {
    adrAtlet P = new elmAtlet;
    P->info = x;
    P->next = Nil;
    return P;
}

void dealokasiAtlet(adrAtlet &P) {
    delete P;
    P = Nil;
}

double hitungBMI(double beratBadan, double tinggiBadan) {
    double hasil = 0.0;
    if (beratBadan > 0.0 && tinggiBadan > 0.0) {
        double tinggiMeter = tinggiBadan / 100.0;
        hasil = beratBadan / (tinggiMeter * tinggiMeter);
    }
    return hasil;
}

string tentukanKategoriBMI(double bmi) {
    string kategori = "Ideal";
    if (bmi < 18.5) {
        kategori = "Kurus";
    } else if (bmi >= 25.0) {
        kategori = "Berlebih";
    }
    return kategori;
}

void insertFirstAtlet(ListAtlet &L, adrAtlet P) {
    if (P != Nil) {
        P->next = L.first;
        L.first = P;
    }
}

void deleteFirstAtlet(ListAtlet &L, adrAtlet &P) {
    if (L.first == Nil) {
        P = Nil;
    } else {
        P = L.first;
        L.first = L.first->next;
        P->next = Nil;
    }
}

void deleteAfterAtlet(ListAtlet &L, adrAtlet Prec, adrAtlet &P) {
    P = Nil;
    if (L.first != Nil && Prec != Nil && Prec->next != Nil) {
        P = Prec->next;
        Prec->next = P->next;
        P->next = Nil;
    }
}

void deleteAtletByID(ListAtlet &L, string idAtlet, adrAtlet &P) {
    P = Nil;
    if (L.first != Nil) {
        if (L.first->info.idAtlet == idAtlet) {
            deleteFirstAtlet(L, P);
        } else {
            adrAtlet Prec = L.first;
            bool ketemu = false;

            while (Prec->next != Nil && !ketemu) {
                if (Prec->next->info.idAtlet == idAtlet) {
                    ketemu = true;
                } else {
                    Prec = Prec->next;
                }
            }

            if (ketemu) {
                deleteAfterAtlet(L, Prec, P);
            }
        }
    }
}

adrAtlet findAtletByID(ListAtlet L, string idAtlet) {
    adrAtlet P = L.first;
    adrAtlet hasil = Nil;
    bool ketemu = false;

    while (P != Nil && !ketemu) {
        if (P->info.idAtlet == idAtlet) {
            hasil = P;
            ketemu = true;
        } else {
            P = P->next;
        }
    }

    return hasil;
}

adrAtlet getAtletByNomor(ListAtlet L, int nomor) {
    adrAtlet P = L.first;
    adrAtlet hasil = Nil;
    int urutan = 1;
    bool ketemu = false;

    while (P != Nil && !ketemu) {
        if (urutan == nomor) {
            hasil = P;
            ketemu = true;
        } else {
            P = P->next;
            urutan++;
        }
    }

    return hasil;
}

void showAllAtlet(ListAtlet L) {
    if (L.first == Nil) {
        cout << "Belum ada data atlet terdaftar.\n";
    } else {
        cout.setf(ios::fixed);
        cout.precision(2);

        adrAtlet P = L.first;
        int nomor = 1;
        while (P != Nil) {
            cout << nomor << ". " << P->info.nama
                 << " | BB: " << P->info.beratBadan << " kg"
                 << " | TB: " << P->info.tinggiBadan << " cm"
                 << " | BMI: " << P->info.bmi
                 << " (" << P->info.kategoriBMI << ")\n";
            P = P->next;
            nomor++;
        }
    }
}

int countAtlet(ListAtlet L) {
    int jumlah = 0;
    adrAtlet P = L.first;
    while (P != Nil) {
        jumlah++;
        P = P->next;
    }
    return jumlah;
}
