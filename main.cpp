#include <iostream>
#include <string>
#include <cstdlib>
#include "atlet.h"
#include "cabang.h"
#include "sesi.h"
#include "bst.h"
#include "stack.h"
#include "storage.h"

using namespace std;

void bersihkanBuffer();
/* I.S. terdapat sisa karakter pada buffer input cin
   F.S. karakter tersisa sampai newline dibuang dari cin */

int inputAngka();
/* I.S. sembarang
   F.S. mengembalikan bilangan bulat valid dari input pengguna */

double inputPositif(string pesan);
/* I.S. pesan terdefinisi
   F.S. mengembalikan bilangan riil > 0 yang valid dari pengguna */

double inputNonNegatif(string pesan);
/* I.S. pesan terdefinisi
   F.S. mengembalikan bilangan riil >= 0 yang valid dari pengguna */

string inputTeksNonKosong(string pesan);
/* I.S. pesan terdefinisi
   F.S. mengembalikan string tidak kosong dari input pengguna */

string intKeString(int angka);
/* I.S. angka >= 0 terdefinisi
   F.S. mengembalikan string hasil konversi angka */

adrAtlet pilihAtletDariDaftar(ListAtlet LA, string pesan);
/* I.S. LA tidak kosong, pesan terdefinisi
   F.S. mengembalikan alamat atlet sesuai nomor urut yang dipilih pengguna */

adrAtlet daftarkanAtletBaru(ListAtlet &LA, ListSesi LS, string namaFile);
/* I.S. LA, LS, dan namaFile terdefinisi
   F.S. atlet baru ditambahkan ke LA, disimpan ke file, dan alamatnya dikembalikan */

void menuMulaiLatihan(ListAtlet &LA, ListCabang LC, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile);
/* I.S. LA, LC, LS, TB, SU, dan namaFile terdefinisi
   F.S. sesi latihan baru dicatat ke LS, SU, TB (jika BEST!), dan disimpan ke file */

void menuKelolaAtlet(ListAtlet &LA, ListSesi &LS, TreeBest &TB, string namaFile);
/* I.S. LA, LS, TB, dan namaFile terdefinisi
   F.S. operasi kelola data atlet dijalankan dan disimpan ke file */

void menuRiwayatAnalitikMLL(ListAtlet LA, ListCabang LC, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile);
/* I.S. LA, LC, LS, TB, SU, dan namaFile terdefinisi
   F.S. riwayat, analitik relasi MLL, atau hapus sesi dijalankan */

void menuBSTRekorBest(TreeBest TB);
/* I.S. TB terdefinisi
   F.S. menampilkan peringkat, rekor tertinggi, atau pencarian skor pada BST */

void menuUndoStack(ListAtlet LA, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile);
/* I.S. LA, LS, TB, SU, dan namaFile terdefinisi
   F.S. menjalankan undo sesi terakhir via Stack atau menampilkan isi Stack */

void bersihkanBuffer() {
    char c = '\0';
    while (cin.get(c) && c != '\n') {
    }
}

int inputAngka() {
    int pilihan = 0;
    bool valid = false;

    while (!valid) {
        if (cin >> pilihan) {
            bersihkanBuffer();
            valid = true;
        } else {
            cin.clear();
            bersihkanBuffer();
            cout << "Input tidak valid! Masukkan angka: ";
        }
    }

    return pilihan;
}

double inputPositif(string pesan) {
    double angka = 0.0;
    bool valid = false;

    while (!valid) {
        cout << pesan;
        if (cin >> angka) {
            bersihkanBuffer();
            if (angka > 0.0) {
                valid = true;
            } else {
                cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
            }
        } else {
            cin.clear();
            bersihkanBuffer();
            cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
        }
    }

    return angka;
}

double inputNonNegatif(string pesan) {
    double angka = 0.0;
    bool valid = false;

    while (!valid) {
        cout << pesan;
        if (cin >> angka) {
            bersihkanBuffer();
            if (angka >= 0.0) {
                valid = true;
            } else {
                cout << "Input tidak valid! Masukkan angka >= 0.\n";
            }
        } else {
            cin.clear();
            bersihkanBuffer();
            cout << "Input tidak valid! Masukkan angka >= 0.\n";
        }
    }

    return angka;
}

string inputTeksNonKosong(string pesan) {
    string teks = "";
    bool valid = false;

    while (!valid) {
        cout << pesan;
        getline(cin, teks);

        if (teks == "") {
            cout << "Input tidak boleh kosong! Silakan masukkan lagi.\n";
        } else {
            valid = true;
        }
    }

    return teks;
}

string intKeString(int angka) {
    string hasil = "";
    if (angka == 0) {
        hasil = "0";
    } else {
        int n = angka;
        while (n > 0) {
            char digit = char('0' + (n % 10));
            hasil = digit + hasil;
            n = n / 10;
        }
    }
    return hasil;
}

adrAtlet pilihAtletDariDaftar(ListAtlet LA, string pesan) {
    int total = countAtlet(LA);
    showAllAtlet(LA);
    cout << pesan << " (1-" << total << "): ";
    int nomor = inputAngka();

    while (nomor < 1 || nomor > total) {
        cout << "Nomor tidak valid! Pilih 1-" << total << ": ";
        nomor = inputAngka();
    }

    return getAtletByNomor(LA, nomor);
}

adrAtlet daftarkanAtletBaru(ListAtlet &LA, ListSesi LS, string namaFile) {
    cout << "\n--- Daftar Atlet Baru ---\n";
    int nomorAtlet = countAtlet(LA) + 1;
    string idAtlet = "AT" + intKeString(nomorAtlet);
    while (findAtletByID(LA, idAtlet) != Nil) {
        nomorAtlet++;
        idAtlet = "AT" + intKeString(nomorAtlet);
    }

    infotypeAtlet data;
    data.idAtlet = idAtlet;
    data.nama = inputTeksNonKosong("Nama Atlet        : ");
    data.beratBadan = inputPositif("Berat Badan (kg)  : ");
    data.tinggiBadan = inputPositif("Tinggi Badan (cm) : ");
    data.bmi = hitungBMI(data.beratBadan, data.tinggiBadan);
    data.kategoriBMI = tentukanKategoriBMI(data.bmi);

    adrAtlet P = alokasiAtlet(data);
    insertFirstAtlet(LA, P);

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "Atlet '" << data.nama << "' berhasil didaftarkan! (BMI: "
         << data.bmi << " - " << data.kategoriBMI << ")\n";

    simpanSemuaData(LA, LS, namaFile);

    return P;
}

void menuMulaiLatihan(ListAtlet &LA, ListCabang LC, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile) {
    cout << "\n========== MULAI LATIHAN ==========\n";

    adrAtlet atletTerpilih = Nil;

    if (LA.first == Nil) {
        cout << "Belum ada atlet terdaftar. Silakan daftar terlebih dahulu.\n";
        atletTerpilih = daftarkanAtletBaru(LA, LS, namaFile);
    } else {
        cout << "1. Pilih Atlet Terdaftar\n";
        cout << "2. Daftar Atlet Baru\n";
        cout << "Pilih: ";
        int opsiAtlet = inputAngka();

        while (opsiAtlet != 1 && opsiAtlet != 2) {
            cout << "Pilihan tidak valid! Pilih 1 atau 2: ";
            opsiAtlet = inputAngka();
        }

        if (opsiAtlet == 1) {
            cout << "\n--- Daftar Atlet ---\n";
            atletTerpilih = pilihAtletDariDaftar(LA, "Pilih nomor atlet");
        } else {
            atletTerpilih = daftarkanAtletBaru(LA, LS, namaFile);
        }
    }

    cout << "\n--- Pilih Cabang Olahraga ---\n";
    showAllCabangMaju(LC);
    cout << "Pilih nomor cabang (1-5): ";
    int pilihCabang = inputAngka();

    while (pilihCabang < 1 || pilihCabang > 5) {
        cout << "Pilihan tidak valid! Pilih 1-5: ";
        pilihCabang = inputAngka();
    }

    string kodeDipilih = "CB" + intKeString(pilihCabang);
    adrCabang cabangTerpilih = findCabangByKode(LC, kodeDipilih);
    string cabang = cabangTerpilih->info.namaCabang;
    string subJenis = "";
    bool inputDalamMeter = false;

    if (pilihCabang == 1) {
        cout << "\nPilih Sub-Jenis Lari:\n";
        cout << "1. Lari Aspal\n";
        cout << "2. Lari Gunung / Trail\n";
        cout << "3. Lari Interval\n";
        cout << "Pilih (1-3): ";
        int sub = inputAngka();
        while (sub < 1 || sub > 3) {
            cout << "Pilihan tidak valid! Pilih 1-3: ";
            sub = inputAngka();
        }

        if (sub == 1) {
            subJenis = "Lari Aspal";
        } else if (sub == 2) {
            subJenis = "Lari Trail";
        } else {
            subJenis = "Lari Interval";
            inputDalamMeter = true;
        }
    } else if (pilihCabang == 2) {
        subJenis = "Jalan Cepat";
    } else if (pilihCabang == 3) {
        cout << "\nPilih Sub-Jenis Sepeda:\n";
        cout << "1. Sepeda Aspal\n";
        cout << "2. Sepeda Gunung\n";
        cout << "Pilih (1-2): ";
        int sub = inputAngka();
        while (sub != 1 && sub != 2) {
            cout << "Pilihan tidak valid! Pilih 1 atau 2: ";
            sub = inputAngka();
        }

        if (sub == 1) {
            subJenis = "Sepeda Aspal";
        } else {
            cout << "\nPilih tingkat kesulitan medan:\n";
            cout << "1. Easy\n";
            cout << "2. Medium\n";
            cout << "3. Hard\n";
            cout << "Pilih (1-3): ";
            int tingkat = inputAngka();
            while (tingkat < 1 || tingkat > 3) {
                cout << "Pilihan tidak valid! Pilih 1-3: ";
                tingkat = inputAngka();
            }

            if (tingkat == 1) {
                subJenis = "Sepeda Gunung (Easy)";
            } else if (tingkat == 2) {
                subJenis = "Sepeda Gunung (Medium)";
            } else {
                subJenis = "Sepeda Gunung (Hard)";
            }
        }
    } else if (pilihCabang == 4) {
        subJenis = "Berenang";
        inputDalamMeter = true;
    } else {
        subJenis = "Mendayung (Rowing)";
        inputDalamMeter = true;
    }

    double targetJarak = 0.0;
    double targetPace = 0.0;
    string satuanPace = "";
    int jumlahSesiSekarang = countSesi(LS);

    prediksiTargetRNG(atletTerpilih, cabangTerpilih, subJenis,
                      jumlahSesiSekarang, targetJarak, targetPace, satuanPace);

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "\n========================================\n";
    cout << "       PREDIKSI TARGET LATIHAN          \n";
    cout << "========================================\n";
    cout << "Atlet          : " << atletTerpilih->info.nama
         << " (BMI: " << atletTerpilih->info.bmi
         << " - " << atletTerpilih->info.kategoriBMI << ")\n";
    cout << "Olahraga       : " << cabang << " - " << subJenis << "\n";
    cout << "Target Jarak   : " << targetJarak << " KM";
    if (inputDalamMeter) {
        cout << " (" << (targetJarak * 1000.0) << " meter)";
    }
    cout << "\n";
    cout << "Target Performa: " << targetPace << " " << satuanPace << "\n";
    cout << "========================================\n";
    cout << "Masukkan hasil latihan aktual:\n";

    double jarakInput = 0.0;
    double jarakKm = 0.0;
    double waktuMenit = 0.0;
    double kecepatanKmh = 0.0;
    bool kecepatanValid = false;

    while (!kecepatanValid) {
        if (inputDalamMeter) {
            jarakInput = inputPositif("Jarak aktual (meter) : ");
            jarakKm = jarakInput / 1000.0;
        } else {
            jarakInput = inputPositif("Jarak aktual (KM)    : ");
            jarakKm = jarakInput;
        }

        waktuMenit = inputPositif("Waktu tempuh (menit) : ");
        kecepatanKmh = jarakKm / (waktuMenit / 60.0);

        if (validasiKecepatan(cabang, kecepatanKmh)) {
            kecepatanValid = true;
        } else {
            cout << "Kecepatan " << kecepatanKmh
                 << " km/jam tidak rasional untuk " << cabang
                 << "! Silakan input ulang.\n";
        }
    }

    double paceAktual = 0.0;

    if (cabang == "Lari") {
        if (subJenis == "Lari Interval") {
            paceAktual = hitungPaceInterval(jarakInput, waktuMenit);
        } else {
            paceAktual = hitungPace(jarakKm, waktuMenit);
        }
    } else if (cabang == "Jalan Cepat") {
        paceAktual = hitungKecepatan(jarakKm, waktuMenit);
    } else if (cabang == "Sepeda") {
        paceAktual = hitungKecepatan(jarakKm, waktuMenit);
    } else if (cabang == "Berenang") {
        paceAktual = hitungPaceRenang(jarakInput, waktuMenit);
    } else {
        paceAktual = hitungPaceMendayung(jarakInput, waktuMenit);
    }

    string status = evaluasiPerforma(cabang, targetJarak, targetPace, jarakKm, paceAktual);
    double skorBest = hitungSkorBest(cabang, status, targetJarak, targetPace, jarakKm, paceAktual);

    int nomorSesi = jumlahSesiSekarang + 1;
    string idSesi = "SS" + intKeString(nomorSesi);
    while (sesiSudahAda(LS, idSesi)) {
        nomorSesi++;
        idSesi = "SS" + intKeString(nomorSesi);
    }

    infotypeSesi dataSesi;
    dataSesi.idSesi = idSesi;
    dataSesi.cabang = cabang;
    dataSesi.subJenis = subJenis;
    dataSesi.targetJarak = targetJarak;
    dataSesi.targetPace = targetPace;
    dataSesi.jarakAktual = jarakKm;
    dataSesi.waktuAktual = waktuMenit;
    dataSesi.paceAktual = paceAktual;
    dataSesi.satuanPace = satuanPace;
    dataSesi.statusEvaluasi = status;
    dataSesi.skorBest = skorBest;

    insertFirstSesi(LS, alokasiSesi(dataSesi, atletTerpilih, cabangTerpilih));
    push(SU, dataSesi);
    if (status == "BEST!") {
        insertBST(TB.root, alokasiNodeBST(dataSesi, atletTerpilih->info.nama));
    }

    cout << "\n========================================\n";
    cout << "          HASIL EVALUASI                \n";
    cout << "========================================\n";
    cout << "Jarak Aktual   : " << dataSesi.jarakAktual << " KM (Target: "
         << dataSesi.targetJarak << " KM)\n";
    cout << "Waktu Tempuh   : " << dataSesi.waktuAktual << " menit\n";
    cout << "Hasil Performa : " << dataSesi.paceAktual << " " << dataSesi.satuanPace
         << " (Target: " << dataSesi.targetPace << " " << dataSesi.satuanPace << ")\n";
    cout << "STATUS         : " << dataSesi.statusEvaluasi << "\n";
    if (dataSesi.statusEvaluasi == "BEST!") {
        cout << "Skor BEST!     : +" << dataSesi.skorBest << "% di atas target\n";
    }
    cout << "========================================\n";

    simpanSemuaData(LA, LS, namaFile);
}

void menuKelolaAtlet(ListAtlet &LA, ListSesi &LS, TreeBest &TB, string namaFile) {
    int pilihan = -1;

    do {
        cout << "\n======= KELOLA DATA ATLET =======\n";
        cout << "1. Tambah Atlet Baru\n";
        cout << "2. Lihat Daftar Atlet\n";
        cout << "3. Hapus Atlet Teratas\n";
        cout << "4. Hapus Atlet Pilihan\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            daftarkanAtletBaru(LA, LS, namaFile);
        } else if (pilihan == 2) {
            cout << "\n--- Daftar Atlet ---\n";
            showAllAtlet(LA);
        } else if (pilihan == 3) {
            adrAtlet P = Nil;
            deleteFirstAtlet(LA, P);
            if (P == Nil) {
                cout << "Daftar atlet masih kosong.\n";
            } else {
                putusRelasiAtlet(LS, P);
                cout << "Atlet '" << P->info.nama << "' berhasil dihapus.\n";
                dealokasiAtlet(P);
                sinkronkanBST(LS, TB);
                simpanSemuaData(LA, LS, namaFile);
            }
        } else if (pilihan == 4) {
            if (LA.first == Nil) {
                cout << "Daftar atlet masih kosong.\n";
            } else {
                cout << "\n--- Pilih Atlet yang Dihapus ---\n";
                adrAtlet target = pilihAtletDariDaftar(LA, "Pilih nomor atlet");
                adrAtlet P = Nil;
                deleteAtletByID(LA, target->info.idAtlet, P);
                if (P != Nil) {
                    putusRelasiAtlet(LS, P);
                    cout << "Atlet '" << P->info.nama << "' berhasil dihapus.\n";
                    dealokasiAtlet(P);
                    sinkronkanBST(LS, TB);
                    simpanSemuaData(LA, LS, namaFile);
                }
            }
        } else if (pilihan != 0) {
            cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilihan != 0);
}

void menuRiwayatAnalitikMLL(ListAtlet LA, ListCabang LC, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile) {
    int pilihan = -1;

    do {
        cout << "\n==== RIWAYAT LATIHAN & ANALITIK ====\n";
        cout << "1. Semua Riwayat Sesi\n";
        cout << "2. Riwayat per Atlet\n";
        cout << "3. Riwayat per Cabang Olahraga\n";
        cout << "4. Daftar Cabang (Maju & Mundur)\n";
        cout << "5. Hapus Riwayat Sesi\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            cout << "\n--- Semua Riwayat Sesi ---\n";
            showAllSesi(LS);
        } else if (pilihan == 2) {
            if (LA.first == Nil) {
                cout << "Belum ada data atlet terdaftar.\n";
            } else {
                cout << "\n--- Pilih Atlet ---\n";
                adrAtlet target = pilihAtletDariDaftar(LA, "Pilih nomor atlet");
                cout << "\n--- Riwayat Sesi: " << target->info.nama << " ---\n";
                showSesiByAtlet(LS, target);
            }
        } else if (pilihan == 3) {
            cout << "\n--- Pilih Cabang Olahraga ---\n";
            showAllCabangMaju(LC);
            cout << "Pilih nomor cabang (1-5): ";
            int pilihCabang = inputAngka();
            while (pilihCabang < 1 || pilihCabang > 5) {
                cout << "Pilihan tidak valid! Pilih 1-5: ";
                pilihCabang = inputAngka();
            }
            string kodeDipilih = "CB" + intKeString(pilihCabang);
            adrCabang cabangDipilih = findCabangByKode(LC, kodeDipilih);
            cout << "\n--- Riwayat Cabang: " << cabangDipilih->info.namaCabang << " ---\n";
            showSesiByCabang(LS, cabangDipilih->info.namaCabang);
        } else if (pilihan == 4) {
            cout << "\n--- Cabang Olahraga (Maju: first -> last) ---\n";
            showAllCabangMaju(LC);
            cout << "\n--- Cabang Olahraga (Mundur: last -> first) ---\n";
            showAllCabangMundur(LC);
        } else if (pilihan == 5) {
            if (LS.first == Nil) {
                cout << "Belum ada data riwayat sesi latihan.\n";
            } else {
                cout << "\n--- Pilih Sesi yang Dihapus ---\n";
                showAllSesi(LS);
                int totalSesi = countSesi(LS);
                cout << "Pilih nomor sesi (1-" << totalSesi << "): ";
                int nomor = inputAngka();
                while (nomor < 1 || nomor > totalSesi) {
                    cout << "Nomor tidak valid! Pilih 1-" << totalSesi << ": ";
                    nomor = inputAngka();
                }

                adrSesi target = getSesiByNomor(LS, nomor);
                adrSesi P = Nil;
                deleteSesiByID(LS, target->info.idSesi, P);
                if (P != Nil) {
                    cout << "Sesi " << P->info.cabang << " (" << P->info.subJenis
                         << ") berhasil dihapus.\n";
                    if (!isEmpty(SU) && SU.info[SU.Top].idSesi == P->info.idSesi) {
                        infotypeSesi buang;
                        bool okPop = false;
                        pop(SU, buang, okPop);
                    }
                    dealokasiSesi(P);
                    sinkronkanBST(LS, TB);
                    simpanSemuaData(LA, LS, namaFile);
                }
            }
        } else if (pilihan != 0) {
            cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilihan != 0);
}

void menuBSTRekorBest(TreeBest TB) {
    int pilihan = -1;

    do {
        cout << "\n======= REKOR BEST! (BST) =======\n";
        cout << "1. Peringkat Rekor BEST! (Tertinggi -> Terendah)\n";
        cout << "2. Rekor BEST! Tertinggi\n";
        cout << "3. Cari Rekor dengan Skor Minimal (%)\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            cout << "\n--- Peringkat Rekor BEST! ---\n";
            if (TB.root == Nil) {
                cout << "Belum ada sesi yang mencapai status BEST!.\n";
            } else {
                showLeaderboardBST(TB.root);
            }
        } else if (pilihan == 2) {
            cout << "\n--- Rekor BEST! Tertinggi ---\n";
            adrBST tertinggi = findBestTertinggi(TB);
            if (tertinggi == Nil) {
                cout << "Belum ada sesi yang mencapai status BEST!.\n";
            } else {
                cout.setf(ios::fixed);
                cout.precision(2);
                cout << "Atlet        : " << tertinggi->namaAtlet << "\n";
                cout << "Olahraga     : " << tertinggi->info.cabang
                     << " (" << tertinggi->info.subJenis << ")\n";
                cout << "Skor BEST!   : +" << tertinggi->info.skorBest << "% di atas target\n";
                cout << "Hasil Aktual : " << tertinggi->info.jarakAktual << " KM | "
                     << tertinggi->info.paceAktual << " " << tertinggi->info.satuanPace << "\n";
            }
        } else if (pilihan == 3) {
            if (TB.root == Nil) {
                cout << "Belum ada sesi yang mencapai status BEST!.\n";
            } else {
                double minSkor = inputNonNegatif("Masukkan skor minimal (%): ");
                cout << "\n--- Rekor BEST! >= " << minSkor << "% ---\n";
                int jumlahKetemu = 0;
                cariBestMinimalSkor(TB.root, minSkor, jumlahKetemu);
                if (jumlahKetemu == 0) {
                    cout << "Tidak ada rekor dengan skor minimal " << minSkor << "%.\n";
                } else {
                    cout << "Total ditemukan: " << jumlahKetemu << " rekor.\n";
                }
            }
        } else if (pilihan != 0) {
            cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilihan != 0);
}

void menuUndoStack(ListAtlet LA, ListSesi &LS, TreeBest &TB, StackUndo &SU, string namaFile) {
    int pilihan = -1;

    do {
        cout << "\n===== UNDO SESI TERAKHIR (STACK) =====\n";
        cout << "1. Undo Sesi Terakhir\n";
        cout << "2. Lihat Tumpukan Stack Undo\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        pilihan = inputAngka();

        if (pilihan == 1) {
            infotypeSesi sesiBatal;
            bool berhasil = false;
            pop(SU, sesiBatal, berhasil);

            if (!berhasil) {
                cout << "Stack Undo kosong, tidak ada sesi yang bisa dibatalkan.\n";
            } else {
                adrSesi P = Nil;
                deleteSesiByID(LS, sesiBatal.idSesi, P);
                if (P != Nil) {
                    dealokasiSesi(P);
                }
                cout << "Sesi " << sesiBatal.cabang << " (" << sesiBatal.subJenis
                     << ") berhasil dibatalkan.\n";
                sinkronkanBST(LS, TB);
                simpanSemuaData(LA, LS, namaFile);
            }
        } else if (pilihan == 2) {
            cout << "\n--- Tumpukan Stack Undo ---\n";
            viewStack(SU);
        } else if (pilihan != 0) {
            cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilihan != 0);
}

int main() {
    ListAtlet LA;
    ListCabang LC;
    ListSesi LS;
    TreeBest TB;
    StackUndo SU;
    string namaFile = "data_olahraga.txt";

    createListAtlet(LA);
    createListCabang(LC);
    createListSesi(LS);
    createTreeBest(TB);
    createStack(SU);

    initCabangOlahraga(LC);
    muatSemuaData(LA, LC, LS, namaFile);
    sinkronkanBST(LS, TB);

    int pilihan = -1;

    do {
        cout << "\n========================================\n";
        cout << "             TRACKIN APP\n";
        cout << "========================================\n";
        cout << "1. Mulai Latihan (Prediksi RNG)\n";
        cout << "2. Kelola Data Atlet\n";
        cout << "3. Riwayat Latihan & Analitik\n";
        cout << "4. Rekor BEST! (BST)\n";
        cout << "5. Undo Sesi Terakhir (Stack)\n";
        cout << "0. Keluar\n";
        cout << "========================================\n";
        cout << "Pilih menu: ";

        pilihan = inputAngka();

        if (pilihan == 1) {
            menuMulaiLatihan(LA, LC, LS, TB, SU, namaFile);
        } else if (pilihan == 2) {
            menuKelolaAtlet(LA, LS, TB, namaFile);
        } else if (pilihan == 3) {
            menuRiwayatAnalitikMLL(LA, LC, LS, TB, SU, namaFile);
        } else if (pilihan == 4) {
            menuBSTRekorBest(TB);
        } else if (pilihan == 5) {
            menuUndoStack(LA, LS, TB, SU, namaFile);
        } else if (pilihan == 0) {
            cout << "\nTerima kasih telah menggunakan TRACKIN APP!\n";
        } else {
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    dealokasiSemuaBST(TB.root);

    return 0;
}
