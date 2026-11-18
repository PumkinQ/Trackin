#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include "Trackin.h"
#include "search.h"

using namespace std;

List L;
Stack S;

void menuLari();
void menuSepeda();
void menuBerenang();
void runningSummary();

int inputAngka()
{
    int pilihan;

    while (!(cin >> pilihan))
    {
        cout << "Input tidak valid! Masukkan angka: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return pilihan;
}

double inputPositif(string pesan)
{
    double angka;
    string sisa;

    while (true)
    {
        cout << pesan;

        if (cin >> angka)
        {
            getline(cin, sisa);

            if (sisa.find_first_not_of(" \t") == string::npos && angka > 0)
            {
                return angka;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
    }
}

string inputNama()
{
    string nama;

    while (true)
    {
        getline(cin, nama);

        if (nama.find_first_not_of(" \t") == string::npos)
        {
            cout << "Nama tidak boleh kosong! Masukkan nama lagi: ";
        }
        else
        {
            return nama;
        }
    }
}

double hitungPace(double jarak, double waktu)
{
    return waktu / jarak;
}

int main()
{
    int pilihan;
    
    createList(L);
    createStack(S);

    do
    {
        cout << "\n";
        cout << "================================\n";
        cout << "          TRACKIN APP           \n";
        cout << "================================\n";
        cout << "1. Lari (Running)\n";
        cout << "2. Sepeda (Cycling)\n";
        cout << "3. Berenang (Swimming)\n";
        cout << "4. Running Summary\n";
        cout << "5. Cari Riwayat Sesi\n";
        cout << "6. Undo Sesi Terakhir\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Pilih menu: ";

        pilihan = inputAngka();

        switch (pilihan)
        {
        case 1:
            menuLari();
            break;

        case 2:
            menuSepeda();
            break;

        case 3:
            menuBerenang();
            break;

        case 4:
            runningSummary();
            break;

        case 5: {
            string cabangCari;
            cout << "\nPENCARIAN SESI\n";
            cout << "Masukkan Cabang (Lari/Sepeda/Berenang/Mendayung): ";
            cin >> cabangCari;

            addressList hasil = cariSesiBerdasarkanCabang(L, cabangCari);

            if (hasil != Nil) {
                cout << "\nDATA DITEMUKAN\n";
                cout << "Cabang   : " << hasil->info.cabang << endl;
                cout << "Jarak    : " << hasil->info.jarak << " KM\n";
                cout << "Waktu    : " << hasil->info.waktu << " menit\n";
                cout << "Pace/Kecepatan : " << hasil->info.hasilPace << "\n";
            } else {
                cout << "\nDATA TIDAK DITEMUKAN\n";
                cout << "Belum ada riwayat untuk olahraga '" << cabangCari << "'.\n";
            }
            break;
        }

        case 6:
            cout << "\nUNDO SESI\n";
            undoSesi(L, S);
            break;

        case 0:
           cout << "\nTerima kasih sudah menggunakan TRACKIN!\n";
            break;

        default:
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    return 0;
}

void menuLari()
{
    int pilihan;
    string nama;
    double jarak = 0, waktu = 0, pace = 0;

    do
    {
        cout << "\n========== MENU LARI ==========\n";
        cout << "1. Lari Aspal\n";
        cout << "2. Lari Gunung / Trail\n";
        cout << "3. Lari Interval\n";
        cout << "4. Jalan Cepat\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";

        pilihan = inputAngka();

        if (pilihan >= 1 && pilihan <= 4)
        {
            cout << "\nMasukkan nama: ";
            nama = inputNama();

            switch (pilihan)
            {
                case 1:
                    cout << "\n===== LARI ASPAL =====\n";
                    jarak = inputPositif("Masukkan jarak (KM): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");

                    pace = waktu / jarak;

                    cout << "\nPace Lari Aspal: "
                         << fixed << setprecision(2)
                         << pace << " menit/km\n";
                    break;

                case 2:
                    cout << "\n===== LARI GUNUNG / TRAIL =====\n";
                    jarak = inputPositif("Masukkan jarak (KM): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");

                    pace = waktu / jarak;

                    cout << "\nPace Lari Trail: "
                         << fixed << setprecision(2)
                         << pace << " menit/km\n";
                    break;

                case 3:
                    cout << "\n===== LARI INTERVAL =====\n";
                    jarak = inputPositif("Masukkan jarak (meter): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");

                    pace = waktu / (jarak / 100.0);
                    jarak = jarak / 1000.0; // konversi ke KM untuk struct

                    cout << "\nPace Lari Interval: "
                         << fixed << setprecision(2)
                         << pace << " menit/100m\n";
                    break;

                case 4:
                {
                    double jumlahLangkah, spm;

                    cout << "\n===== JALAN CEPAT =====\n";
                    jarak = inputPositif("Masukkan jarak (KM): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");
                    jumlahLangkah = inputPositif("Masukkan jumlah langkah: ");

                    spm = jumlahLangkah / waktu;
                    pace = waktu / jarak;

                    cout << "\nPace Jalan Cepat: "
                         << fixed << setprecision(2)
                         << pace << " menit/km\n";
                    cout << "SPM: " << spm << " langkah/menit\n";
                    break;
                }
            }

            cout << "Nama: " << nama << endl;

            // Integrasi ke Linked List dan Stack
            infotype dataBaru;
            dataBaru.id = "-"; 
            dataBaru.cabang = "Lari";
            dataBaru.jarak = jarak;
            dataBaru.waktu = waktu;
            dataBaru.hasilPace = to_string(pace);
            catatSesi(L, S, dataBaru);

            cout << "Data berhasil diinput!\n";
        }
        else if (pilihan == 5)
        {
            cout << "\nKembali ke Menu Utama...\n";
        }
        else
        {
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 5);
}

void menuSepeda()
{
    int pilihan;
    string nama, medan;
    double jarak = 0, waktu = 0, kecepatan = 0;

    do
    {
        cout << "\n========== MENU SEPEDA ==========\n";
        cout << "1. Sepeda Aspal\n";
        cout << "2. Sepeda Gunung\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";

        pilihan = inputAngka();

        if (pilihan == 1 || pilihan == 2)
        {
            cout << "\nMasukkan nama: ";
            nama = inputNama();

            switch (pilihan)
            {
                case 1:
                    cout << "\n===== SEPEDA ASPAL =====\n";
                    jarak = inputPositif("Masukkan jarak (KM): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");

                    kecepatan = jarak / (waktu / 60.0);

                    cout << "\nKecepatan: " << fixed << setprecision(2)
                         << kecepatan << " km/jam\n";
                    break;

                case 2:
                    cout << "\n===== SEPEDA GUNUNG =====\n";
                    jarak = inputPositif("Masukkan jarak (KM): ");
                    waktu = inputPositif("Masukkan waktu (menit): ");

                    cout << "\nPilih tingkat kesulitan medan:\n";
                    cout << "1. Easy\n";
                    cout << "2. Medium\n";
                    cout << "3. Hard\n";
                    cout << "Pilih: ";

                    int tingkat;
                    tingkat = inputAngka();

                    while (tingkat < 1 || tingkat > 3)
                    {
                        cout << "Pilihan tidak tersedia! Pilih 1-3: ";
                        tingkat = inputAngka();
                    }

                    if (tingkat == 1)
                        medan = "Easy";
                    else if (tingkat == 2)
                        medan = "Medium";
                    else
                        medan = "Hard";

                    kecepatan = jarak / (waktu / 60.0);

                    cout << "\nKecepatan: " << fixed << setprecision(2)
                         << kecepatan << " km/jam\n";
                    cout << "Tingkat medan: " << medan << endl;
                    break;
            }

            cout << "Nama: " << nama << endl;

            // Integrasi ke Linked List dan Stack
            infotype dataBaru;
            dataBaru.id = "-"; 
            dataBaru.cabang = "Sepeda";
            dataBaru.jarak = jarak;
            dataBaru.waktu = waktu;
            dataBaru.hasilPace = to_string(kecepatan) + " km/jam";
            catatSesi(L, S, dataBaru);

            cout << "Data berhasil diinput!\n";
        }
        else if (pilihan == 3)
        {
            cout << "\nKembali ke Menu Utama...\n";
        }
        else
        {
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 3);
}

void menuBerenang()
{
    int pilihan;
    string nama;
    double jarak = 0, waktu = 0, pace = 0;

    do
    {
        cout << "\n========== MENU AIR ==========\n";
        cout << "1. Berenang\n";
        cout << "2. Mendayung (Rowing)\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";

        pilihan = inputAngka();

        if (pilihan == 1 || pilihan == 2)
        {
            cout << "\nMasukkan nama: ";
            nama = inputNama();

            if (pilihan == 1)
            {
                cout << "\n===== BERENANG =====\n";
                jarak = inputPositif("Masukkan jarak (meter): ");
                waktu = inputPositif("Masukkan waktu (menit): ");

                pace = waktu / (jarak / 100.0);

                cout << "Pace: " << fixed << setprecision(2)
                     << pace << " menit/100m\n";
            }
            else
            {
                cout << "\n===== MENDAYUNG (ROWING) =====\n";
                jarak = inputPositif("Masukkan jarak (meter): ");
                waktu = inputPositif("Masukkan waktu (menit): ");

                pace = waktu / (jarak / 500.0);

                cout << "Pace: " << fixed << setprecision(2)
                     << pace << " menit/500m\n";
            }

            cout << "Nama: " << nama << endl;

            // Integrasi ke Linked List dan Stack
            infotype dataBaru;
            dataBaru.id = "-"; 
            dataBaru.cabang = (pilihan == 1) ? "Berenang" : "Mendayung";
            dataBaru.jarak = jarak / 1000.0; // konversi meter ke KM
            dataBaru.waktu = waktu;
            dataBaru.hasilPace = to_string(pace);
            catatSesi(L, S, dataBaru);

            cout << "Data berhasil diinput!\n";
        }
        else if (pilihan == 3)
        {
            cout << "\nKembali ke Menu Utama...\n";
        }
        else
        {
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 3);
}

void runningSummary()
{
    cout << "\n================================\n";
    cout << "        RUNNING SUMMARY         \n";
    cout << "================================\n";

    if (L.first == Nil) {
        cout << "Belum ada data aktivitas.\n";
        cout << "Silakan input aktivitas terlebih dahulu.\n";
    } else {
        showRiwayat(L);
    }

    cout << "================================\n";
}