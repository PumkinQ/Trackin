#include "storage.h"

// primitif simpanData
void simpanData(SesiOlahraga data) {
    ofstream file("riwayat.txt", ios::app); // app = append
    
    if (file.is_open()) {
        file << data.id << "," 
             << data.cabang << "," 
             << data.jarak << "," 
             << data.waktu << "," 
             << data.hasilPace << endl;
        file.close();
        cout << "Data berhasil disimpan permanen" << endl;
    } else {
        cout << "Gagal membuka riwayat" << endl;
    }
}

// primitif muatData
void muatData() {
    ifstream file("riwayat.txt");
    string line;
    
    if (file.is_open()) {
        cout << "Memuat Data Riwayat" << endl;
        while (getline(file, line)) {
            // nanti baris baris ini dimasukkan ke multi linked-list
            cout << line << endl; 
        }
        file.close();
    } else {
        cout << "Belum ada riwayat yang tersimpan." << endl;
    }
}