#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
using namespace std;

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

        cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout << "5. Exit\n";
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

        case 5:
            cout << "\nTerima kasih sudah menggunakan TRACKIN!\n";
            break;

        default:
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 5);

    return 0;
}

void menuLari()
{
    int pilihan;
    string nama;
    string rute;
    double jarak = 0;
    double waktu = 0;

    cout << "\n========== MENU LARI ==========\n";
    cout << "1. Input Aktivitas Lari\n";
    cout << "2. Kembali ke Menu Utama\n";
    cout << "Pilih menu: ";

    pilihan = inputAngka();

    if (pilihan == 1)
    {

        cout << "\n===== INPUT AKTIVITAS LARI =====\n";

        cout << "Nama Pelari: ";
        nama = inputNama();

        cout << "Nama Pelari: ";
        nama = inputNama();
        cout << "\nPilih Rute Lari:\n";
        cout << "1. GBK Loop (0.9 KM)\n";
        cout << "2. Sudirman-Thamrin CFD (7 KM)\n";
        cout << "3. Kebun Raya Bogor (3.2 KM)\n";
        cout << "Pilih rute: ";

        int pilihRute = inputAngka();

        switch (pilihRute)
        {
        case 1:
            rute = "GBK Loop";
            jarak = 0.9;
            break;

        case 2:
            rute = "Sudirman-Thamrin CFD";
            jarak = 7.0;
            break;

        case 3:
            rute = "Kebun Raya Bogor";
            jarak = 3.2;
            break;

        default:
            cout << "Pilihan rute tidak tersedia!\n";
            return;
        }

        waktu = inputPositif("\nMasukkan waktu tempuh (menit): ");
        double pace = hitungPace(jarak, waktu);

        cout << "\n===== DATA AKTIVITAS LARI =====\n";
        cout << "Nama Pelari : " << nama << endl;
        cout << "Jenis       : Lari\n";
        cout << "Rute        : " << rute << endl;
        cout << "Jarak       : " << jarak << " KM\n";
        cout << "Waktu       : " << waktu << " menit\n";
        cout << fixed << setprecision(2);
        cout << "Pace        : " << pace << " menit/km\n";

        cout << "\nData berhasil diinput!\n";
    }
    else if (pilihan == 2)
    {
        cout << "\nKembali ke Menu Utama...\n";
    }
    else
    {
        cout << "\nPilihan tidak tersedia!\n";
    }
}

void menuSepeda()
{
    int pilihan;

    do
    {
        cout << "\n===== MENU SEPEDA =====\n";
        cout << "1. Input Aktivitas Sepeda\n";
        cout << "2. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan)
        {
        case 1:
        {
            string nama;
            double jarak, waktu;

            cout << "\n===== INPUT AKTIVITAS SEPEDA =====\n";

            cout << "Masukkan nama: ";
            nama = inputNama();
            nama = inputNama();
            jarak = inputPositif("Masukkan jarak (KM): ");
            waktu = inputPositif("Masukkan waktu (menit): ");

            cout << "\n===== DATA AKTIVITAS SEPEDA =====\n";
            cout << "Nama  : " << nama << endl;
            cout << "Jarak : " << jarak << " KM" << endl;
            cout << "Waktu : " << waktu << " menit" << endl;

            cout << "\nData berhasil diinput!\n";
            break;
        }

        case 2:
            cout << "Kembali ke menu utama...\n";
            break;

        default:
            cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 2);
}

void menuBerenang()
{
    int pilihan;

    do
    {
        cout << "\n===== MENU BERENANG =====\n";
        cout << "1. Input Aktivitas Berenang\n";
        cout << "2. Kembali ke Menu Utama\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan)
        {
        case 1:
        {
            string nama;
            double jarak, waktu;

            cout << "\n===== INPUT AKTIVITAS BERENANG =====\n";

            cout << "Masukkan nama: ";
            nama = inputNama();
            nama = inputNama();
            jarak = inputPositif("Masukkan jarak (meter): ");
            waktu = inputPositif("Masukkan waktu (menit): ");

            cout << "\n===== DATA AKTIVITAS BERENANG =====\n";
            cout << "Nama  : " << nama << endl;
            cout << "Jarak : " << jarak << " meter" << endl;
            cout << "Waktu : " << waktu << " menit" << endl;

            cout << "\nData berhasil diinput!\n";
            break;
        }

        case 2:
            cout << "Kembali ke menu utama...\n";
            break;

        default:
            cout << "Pilihan tidak tersedia!\n";
        }

    } while (pilihan != 2);
}

void runningSummary()
{
    cout << "\n================================\n";
    cout << "        RUNNING SUMMARY         \n";
    cout << "================================\n";

    cout << "Belum ada data aktivitas.\n";
    cout << "Silakan input aktivitas terlebih dahulu.\n";

    cout << "================================\n";
}
