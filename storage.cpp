#include "storage.h"

int pecahBaris(string baris, char pemisah, string hasil[], int maksBagian) {
    int jumlah = 0;
    int mulai = 0;
    int panjang = int(baris.length());
    int i = 0;

    while (i <= panjang && jumlah < maksBagian) {
        if (i == panjang || baris[i] == pemisah) {
            hasil[jumlah] = baris.substr(mulai, i - mulai);
            jumlah++;
            mulai = i + 1;
        }
        i++;
    }

    return jumlah;
}

bool sesiSudahAda(ListSesi LS, string idSesi) {
    adrSesi P = LS.first;
    bool ketemu = false;

    while (P != Nil && !ketemu) {
        if (P->info.idSesi == idSesi) {
            ketemu = true;
        } else {
            P = P->next;
        }
    }

    return ketemu;
}

void simpanSemuaData(ListAtlet LA, ListSesi LS, string namaFile) {
    ofstream file(namaFile.c_str());

    if (file.is_open()) {
        file.setf(ios::fixed);
        file.precision(2);

        adrAtlet PA = LA.first;
        while (PA != Nil) {
            file << "ATLET|"
                 << PA->info.idAtlet << "|"
                 << PA->info.nama << "|"
                 << PA->info.beratBadan << "|"
                 << PA->info.tinggiBadan << "|"
                 << PA->info.bmi << "|"
                 << PA->info.kategoriBMI << "\n";
            PA = PA->next;
        }

        adrSesi PS = LS.first;
        while (PS != Nil) {
            string idAtlet = "-";
            if (PS->parentAtlet != Nil) {
                idAtlet = PS->parentAtlet->info.idAtlet;
            }

            file << "SESI|"
                 << PS->info.idSesi << "|"
                 << idAtlet << "|"
                 << PS->info.cabang << "|"
                 << PS->info.subJenis << "|"
                 << PS->info.targetJarak << "|"
                 << PS->info.targetPace << "|"
                 << PS->info.jarakAktual << "|"
                 << PS->info.waktuAktual << "|"
                 << PS->info.paceAktual << "|"
                 << PS->info.satuanPace << "|"
                 << PS->info.statusEvaluasi << "|"
                 << PS->info.skorBest << "\n";
            PS = PS->next;
        }

        file.close();
        cout << "[AUTO-SAVE] Data tersimpan otomatis ke '" << namaFile << "'.\n";
    } else {
        cout << "Error: tidak dapat membuka file '" << namaFile << "'.\n";
    }
}

void muatSemuaData(ListAtlet &LA, ListCabang LC, ListSesi &LS, string namaFile) {
    ifstream file(namaFile.c_str());

    if (file.is_open()) {
        string baris;
        int jmlAtlet = 0;
        int jmlSesi = 0;

        while (getline(file, baris)) {
            if (baris.length() > 0) {
                string kolom[16];
                int n = pecahBaris(baris, '|', kolom, 16);

                if (n >= 7 && kolom[0] == "ATLET") {
                    if (findAtletByID(LA, kolom[1]) == Nil) {
                        infotypeAtlet a;
                        a.idAtlet = kolom[1];
                        a.nama = kolom[2];
                        a.beratBadan = atof(kolom[3].c_str());
                        a.tinggiBadan = atof(kolom[4].c_str());
                        a.bmi = hitungBMI(a.beratBadan, a.tinggiBadan);
                        a.kategoriBMI = tentukanKategoriBMI(a.bmi);
                        insertFirstAtlet(LA, alokasiAtlet(a));
                        jmlAtlet++;
                    }
                } else if (n >= 13 && kolom[0] == "SESI") {
                    if (!sesiSudahAda(LS, kolom[1])) {
                        infotypeSesi s;
                        s.idSesi = kolom[1];
                        adrAtlet pAtlet = findAtletByID(LA, kolom[2]);
                        s.cabang = kolom[3];
                        adrCabang pCabang = findCabangByNama(LC, s.cabang);
                        s.subJenis = kolom[4];
                        s.targetJarak = atof(kolom[5].c_str());
                        s.targetPace = atof(kolom[6].c_str());
                        s.jarakAktual = atof(kolom[7].c_str());
                        s.waktuAktual = atof(kolom[8].c_str());
                        s.paceAktual = atof(kolom[9].c_str());
                        s.satuanPace = kolom[10];
                        s.statusEvaluasi = kolom[11];
                        s.skorBest = atof(kolom[12].c_str());

                        insertFirstSesi(LS, alokasiSesi(s, pAtlet, pCabang));
                        jmlSesi++;
                    }
                }
            }
        }

        file.close();
        cout << "[AUTO-LOAD] Memuat '" << namaFile << "': "
             << jmlAtlet << " Atlet, "
             << jmlSesi << " Sesi.\n";
    } else {
        cout << "File '" << namaFile << "' belum ditemukan. Memulai dengan data kosong.\n";
    }
}

void tampilIsiFile(string namaFile) {
    ifstream file(namaFile.c_str());

    if (file.is_open()) {
        cout << "\n===== ISI FILE " << namaFile << " =====\n";
        string baris;
        int nomor = 0;
        while (getline(file, baris)) {
            nomor++;
            cout << nomor << ". " << baris << "\n";
        }
        if (nomor == 0) {
            cout << "(File kosong)\n";
        }
        file.close();
        cout << "=========================================\n";
    } else {
        cout << "File '" << namaFile << "' belum ditemukan.\n";
    }
}
