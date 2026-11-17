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

// Linked List
void createList(List &L)
{
    L.first = Nil;
}

addressList alokasiList(infotype x)
{
    addressList P = new elmList;
    P->info = x;
    P->next = Nil;
    return P;
}

void insertLastList(List &L, addressList P)
{
    if (L.first == Nil)
    {
        L.first = P;
    }
    else
    {
        addressList Q = L.first;
        while (Q->next != Nil)
        {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void deleteLastList(List &L, addressList &P)
{
    if (L.first == Nil)
    {
        P = Nil;
    }
    else if (L.first->next == Nil)
    {
        P = L.first;
        L.first = Nil;
    }
    else
    {
        addressList Q = L.first;
        while (Q->next->next != Nil)
        {
            Q = Q->next;
        }
        P = Q->next;
        Q->next = Nil;
    }
}

void showRiwayat(List L)
{
    if (L.first == Nil)
    {
        cout << "Belum ada data aktivitas.\nSilakan input aktivitas terlebih dahulu.\n";
    }
    else
    {
        addressList P = L.first;
        int i = 1;
        while (P != Nil)
        {
            cout << i << ". [" << P->info.id << "] " << P->info.cabang
                 << " | Jarak: " << P->info.jarak << " KM | Waktu: " << P->info.waktu
                 << " menit | Pace: " << P->info.hasilPace << "\n";
            P = P->next;
            i++;
        }
    }
}

// Stack
void createStack(Stack &S)
{
    S.top = Nil;
}

addressStack alokasiStack(infotype x)
{
    addressStack P = new elmStack;
    P->info = x;
    P->next = Nil;
    return P;
}

void pushStack(Stack &S, addressStack P)
{
    if (S.top == Nil)
    {
        S.top = P;
    }
    else
    {
        P->next = S.top;
        S.top = P;
    }
}

void popStack(Stack &S, addressStack &P)
{
    if (S.top == Nil)
    {
        P = Nil;
    }
    else
    {
        P = S.top;
        S.top = S.top->next;
        P->next = Nil;
    }
}

// Queue
void createQueue(Queue &Q)
{
    Q.head = Nil;
    Q.tail = Nil;
}

addressQueue alokasiQueue(infotype x)
{
    addressQueue P = new elmQueue;
    P->info = x;
    P->next = Nil;
    return P;
}

void enqueue(Queue &Q, addressQueue P)
{
    if (Q.head == Nil && Q.tail == Nil)
    {
        Q.head = P;
        Q.tail = P;
    }
    else
    {
        Q.tail->next = P;
        Q.tail = P;
    }
}

void dequeue(Queue &Q, addressQueue &P)
{
    if (Q.head == Nil)
    {
        P = Nil;
    }
    else if (Q.head == Q.tail)
    {
        P = Q.head;
        Q.head = Nil;
        Q.tail = Nil;
    }
    else
    {
        P = Q.head;
        Q.head = Q.head->next;
        P->next = Nil;
    }
}

// Integrasi Aplikasi
void catatSesi(List &L, Stack &S, infotype dataBaru)
{
    // Alokasi memori untuk List dan Stack
    addressList nodeL = alokasiList(dataBaru);
    addressStack nodeS = alokasiStack(dataBaru);

    // Masukkan data ke List untuk kebutuhan riwatay
    insertLastList(L, nodeL);
    pushStack(S, nodeS);
}

void undoSesi(List &L, Stack &S)
{
    if (S.top == Nil)
    {
        cout << "[INFO] Tidak ada sesi yang bisa dibatalkan (Undo).\n";
        return;
    }

    addressStack P_Stack;
    addressList P_List;

    // Keluarkan dari Stack dan hapus dari List
    popStack(S, P_Stack);
    deleteLastList(L, P_List);

    cout << "[UNDO BERHASIL] Sesi [" << P_Stack->info.cabang << "] telah dihapus dari riwayat.\n";

    // Dealokasi memori agar tidak leak
    delete P_Stack;
    delete P_List;
}