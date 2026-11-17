#include <iostream>
#include <fstream>
#include <string>
#include "Trackin.h"
#include "storage.h"

using namespace std;

// Fungsi untuk menyimpan data 1 SesiOlahraga ke dalam file teks append
void simpanData(SesiOlahraga data) {
    ofstream file("data_olahraga.txt", ios::app); // app = append
    
    if (file.is_open()) {
        file << data.id << "," //simpan data ke file dengan format CSV dengan pemisah koma
             << data.cabang << "," 
             << data.jarak << "," 
             << data.waktu << "," 
             << data.hasilPace << "\n";
        file.close();
        cout << "Data sesi olahraga berhasil disimpan ke file!" << endl;
    } else {
        cout << "Error: Tidak dapat membuka file untuk menyimpan data." << endl;
    }
}

// Fungsi untuk membaca dan menampilkan data dari file teks
void muatData() {
    ifstream file("data_olahraga.txt");
    string teks;
    
    if (file.is_open()) {
        cout << "Data Riwayat Olahraga" << endl;
        while (getline(file, teks)) {
            cout << teks << endl;
        }
        file.close();
        cout << "----------------------------------" << endl;
    } else {
        cout << "Belum ada riwayat data atau file tidak ditemukan." << endl;
    }
}