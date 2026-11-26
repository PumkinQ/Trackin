#include "sesi.h"

void createListSesi(ListSesi &L) {
    L.first = Nil;
}

adrSesi alokasiSesi(infotypeSesi x, adrAtlet atlet, adrCabang cabangNode) {
    adrSesi P = new elmSesi;
    P->info = x;
    P->next = Nil;
    P->parentAtlet = atlet;
    P->parentCabang = cabangNode;
    return P;
}

void dealokasiSesi(adrSesi &P) {
    delete P;
    P = Nil;
}

void insertFirstSesi(ListSesi &L, adrSesi P) {
    if (P != Nil) {
        P->next = L.first;
        L.first = P;
    }
}

void deleteFirstSesi(ListSesi &L, adrSesi &P) {
    if (L.first == Nil) {
        P = Nil;
    } else {
        P = L.first;
        L.first = L.first->next;
        P->next = Nil;
    }
}

void deleteAfterSesi(ListSesi &L, adrSesi Prec, adrSesi &P) {
    P = Nil;
    if (L.first != Nil && Prec != Nil && Prec->next != Nil) {
        P = Prec->next;
        Prec->next = P->next;
        P->next = Nil;
    }
}

void deleteSesiByID(ListSesi &L, string idSesi, adrSesi &P) {
    P = Nil;
    if (L.first != Nil) {
        if (L.first->info.idSesi == idSesi) {
            deleteFirstSesi(L, P);
        } else {
            adrSesi Prec = L.first;
            bool ketemu = false;

            while (Prec->next != Nil && !ketemu) {
                if (Prec->next->info.idSesi == idSesi) {
                    ketemu = true;
                } else {
                    Prec = Prec->next;
                }
            }

            if (ketemu) {
                deleteAfterSesi(L, Prec, P);
            }
        }
    }
}

int countSesi(ListSesi L) {
    int jumlah = 0;
    adrSesi P = L.first;
    while (P != Nil) {
        jumlah++;
        P = P->next;
    }
    return jumlah;
}

void putusRelasiAtlet(ListSesi &L, adrAtlet P) {
    adrSesi Q = L.first;
    while (Q != Nil) {
        if (Q->parentAtlet == P) {
            Q->parentAtlet = Nil;
        }
        Q = Q->next;
    }
}

double hitungPace(double jarakKm, double waktuMenit) {
    double hasil = 0.0;
    if (jarakKm > 0.0 && waktuMenit > 0.0) {
        hasil = waktuMenit / jarakKm;
    }
    return hasil;
}

double hitungPaceInterval(double jarakMeter, double waktuMenit) {
    double hasil = 0.0;
    if (jarakMeter > 0.0 && waktuMenit > 0.0) {
        hasil = waktuMenit / (jarakMeter / 100.0);
    }
    return hasil;
}

double hitungKecepatan(double jarakKm, double waktuMenit) {
    double hasil = 0.0;
    if (jarakKm > 0.0 && waktuMenit > 0.0) {
        hasil = jarakKm / (waktuMenit / 60.0);
    }
    return hasil;
}

double hitungPaceRenang(double jarakMeter, double waktuMenit) {
    double hasil = 0.0;
    if (jarakMeter > 0.0 && waktuMenit > 0.0) {
        hasil = (waktuMenit / jarakMeter) * 100.0;
    }
    return hasil;
}

double hitungPaceMendayung(double jarakMeter, double waktuMenit) {
    double hasil = 0.0;
    if (jarakMeter > 0.0 && waktuMenit > 0.0) {
        hasil = waktuMenit / (jarakMeter / 500.0);
    }
    return hasil;
}

bool validasiKecepatan(string cabang, double kecepatanKmh) {
    bool valid = false;

    if (kecepatanKmh > 0.0) {
        if (cabang == "Lari") {
            valid = (kecepatanKmh <= 30.0);
        } else if (cabang == "Jalan Cepat") {
            valid = (kecepatanKmh <= 16.0);
        } else if (cabang == "Sepeda") {
            valid = (kecepatanKmh <= 100.0);
        } else if (cabang == "Berenang") {
            valid = (kecepatanKmh <= 15.0);
        } else if (cabang == "Mendayung") {
            valid = (kecepatanKmh <= 25.0);
        }
    }

    return valid;
}

double acakRentang(double batasBawah, double batasAtas) {
    int persen = rand() % 101;
    double rasio = persen / 100.0;
    return batasBawah + rasio * (batasAtas - batasBawah);
}

void prediksiTargetRNG(adrAtlet atlet, adrCabang cabangNode, string subJenis,
                       int jumlahSesi, double &targetJarak, double &targetPace, string &satuanPace) {
    int seed = int(atlet->info.beratBadan * 100.0) + int(atlet->info.tinggiBadan) + (jumlahSesi * 17) + 11;
    srand(seed);

    string cabang = cabangNode->info.namaCabang;

    double faktorJarak = 1.0;
    double faktorPace = 1.0;
    double faktorKecepatan = 1.0;

    if (atlet->info.kategoriBMI == "Ideal") {
        faktorJarak = 1.10;
        faktorPace = 0.92;
        faktorKecepatan = 1.08;
    } else if (atlet->info.kategoriBMI == "Kurus") {
        faktorJarak = 0.95;
        faktorPace = 1.02;
        faktorKecepatan = 0.96;
    } else {
        faktorJarak = 0.85;
        faktorPace = 1.12;
        faktorKecepatan = 0.88;
    }

    if (cabang == "Lari") {
        if (subJenis == "Lari Interval") {
            satuanPace = "menit/100m";
            targetJarak = acakRentang(0.4, 1.8) * faktorJarak;
            targetPace = acakRentang(0.35, 0.60) * faktorPace;
        } else if (subJenis == "Lari Trail") {
            satuanPace = "menit/km";
            targetJarak = acakRentang(3.0, 8.0) * faktorJarak;
            targetPace = acakRentang(6.0, 8.5) * faktorPace;
        } else {
            satuanPace = "menit/km";
            targetJarak = acakRentang(3.0, 10.0) * faktorJarak;
            targetPace = acakRentang(5.0, 7.2) * faktorPace;
        }
    } else if (cabang == "Jalan Cepat") {
        satuanPace = "km/jam";
        targetJarak = acakRentang(2.0, 6.0) * faktorJarak;
        targetPace = acakRentang(4.5, 7.5) * faktorKecepatan;
    } else if (cabang == "Sepeda") {
        satuanPace = "km/jam";
        if (subJenis == "Sepeda Aspal") {
            targetJarak = acakRentang(10.0, 32.0) * faktorJarak;
            targetPace = acakRentang(20.0, 30.0) * faktorKecepatan;
        } else {
            targetJarak = acakRentang(8.0, 22.0) * faktorJarak;
            targetPace = acakRentang(14.0, 22.0) * faktorKecepatan;
        }
    } else if (cabang == "Berenang") {
        satuanPace = "menit/100m";
        targetJarak = acakRentang(0.4, 1.5) * faktorJarak;
        targetPace = acakRentang(2.0, 3.5) * faktorPace;
    } else {
        satuanPace = "menit/500m";
        targetJarak = acakRentang(1.0, 4.5) * faktorJarak;
        targetPace = acakRentang(2.0, 3.4) * faktorPace;
    }
}

string evaluasiPerforma(string cabang, double targetJarak, double targetPace,
                        double jarakAktual, double paceAktual) {
    bool jarakTercapai = (jarakAktual >= targetJarak);
    bool paceTercapai = false;
    bool jarakDekat = (jarakAktual >= targetJarak * 0.85);
    bool paceDekat = false;

    if (cabang == "Sepeda" || cabang == "Jalan Cepat") {
        paceTercapai = (paceAktual >= targetPace);
        paceDekat = (paceAktual >= targetPace * 0.85);
    } else {
        paceTercapai = (paceAktual <= targetPace);
        paceDekat = (paceAktual <= targetPace * 1.15);
    }

    string status = "KURANG LATIHAN";
    if (jarakTercapai && paceTercapai) {
        status = "BEST!";
    } else if ((jarakTercapai && paceDekat) || (paceTercapai && jarakDekat)) {
        status = "ON TARGET";
    }

    return status;
}

double hitungSkorBest(string cabang, string statusEvaluasi, double targetJarak, double targetPace,
                      double jarakAktual, double paceAktual) {
    double skor = 0.0;

    if (statusEvaluasi == "BEST!" && targetJarak > 0.0 && targetPace > 0.0) {
        double persenJarak = ((jarakAktual - targetJarak) / targetJarak) * 100.0;
        double persenPace = 0.0;

        if (cabang == "Sepeda" || cabang == "Jalan Cepat") {
            persenPace = ((paceAktual - targetPace) / targetPace) * 100.0;
        } else {
            persenPace = ((targetPace - paceAktual) / targetPace) * 100.0;
        }

        if (persenJarak < 0.0) {
            persenJarak = 0.0;
        }
        if (persenPace < 0.0) {
            persenPace = 0.0;
        }

        skor = (persenJarak + persenPace) / 2.0;
    }

    return skor;
}

adrSesi getSesiByNomor(ListSesi L, int nomor) {
    adrSesi P = L.first;
    adrSesi hasil = Nil;
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

void tampilSatuSesi(adrSesi P, int nomor) {
    cout.setf(ios::fixed);
    cout.precision(2);

    string namaAtlet = "Atlet Dihapus";
    if (P->parentAtlet != Nil) {
        namaAtlet = P->parentAtlet->info.nama;
    }

    string namaCabang = P->info.cabang;
    if (P->parentCabang != Nil) {
        namaCabang = P->parentCabang->info.namaCabang;
    }

    cout << nomor << ". " << namaCabang << " (" << P->info.subJenis << ")"
         << " - Atlet: " << namaAtlet
         << " | Status: " << P->info.statusEvaluasi;
    if (P->info.statusEvaluasi == "BEST!") {
        cout << " (+" << P->info.skorBest << "%)";
    }
    cout << "\n";
    cout << "   Target : Jarak " << P->info.targetJarak << " KM | Target "
         << P->info.targetPace << " " << P->info.satuanPace << "\n";
    cout << "   Aktual : Jarak " << P->info.jarakAktual << " KM | Waktu "
         << P->info.waktuAktual << " menit | Hasil "
         << P->info.paceAktual << " " << P->info.satuanPace << "\n";
}

void showAllSesi(ListSesi L) {
    if (L.first == Nil) {
        cout << "Belum ada data riwayat sesi latihan.\n";
    } else {
        adrSesi P = L.first;
        int nomor = 1;
        while (P != Nil) {
            tampilSatuSesi(P, nomor);
            P = P->next;
            nomor++;
        }
    }
}

void showSesiByAtlet(ListSesi L, adrAtlet atletTarget) {
    adrSesi P = L.first;
    int nomor = 0;
    double totalJarak = 0.0;
    int jumlahBest = 0;

    while (P != Nil) {
        if (P->parentAtlet == atletTarget && atletTarget != Nil) {
            nomor++;
            tampilSatuSesi(P, nomor);
            totalJarak = totalJarak + P->info.jarakAktual;
            if (P->info.statusEvaluasi == "BEST!") {
                jumlahBest++;
            }
        }
        P = P->next;
    }

    if (nomor == 0) {
        if (atletTarget != Nil) {
            cout << "Belum ada sesi latihan untuk atlet " << atletTarget->info.nama << ".\n";
        } else {
            cout << "Data atlet tidak ditemukan.\n";
        }
    } else {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "----------------------------------------\n";
        cout << "Total Sesi   : " << nomor << " sesi\n";
        cout << "Total Jarak  : " << totalJarak << " KM\n";
        cout << "Jumlah BEST! : " << jumlahBest << " sesi\n";
    }
}

void showSesiByCabang(ListSesi L, string cabangCari) {
    adrSesi P = L.first;
    int nomor = 0;

    while (P != Nil) {
        if (P->info.cabang == cabangCari) {
            nomor++;
            tampilSatuSesi(P, nomor);
        }
        P = P->next;
    }

    if (nomor == 0) {
        cout << "Belum ada riwayat untuk cabang olahraga '" << cabangCari << "'.\n";
    }
}

bool undoSesiTerakhir(ListSesi &L) {
    bool berhasil = false;
    adrSesi P = Nil;
    deleteFirstSesi(L, P);

    if (P == Nil) {
        cout << "Tidak ada sesi yang bisa dibatalkan.\n";
    } else {
        cout << "Sesi " << P->info.cabang << " (" << P->info.subJenis
             << ") berhasil dihapus dari riwayat.\n";
        dealokasiSesi(P);
        berhasil = true;
    }

    return berhasil;
}
