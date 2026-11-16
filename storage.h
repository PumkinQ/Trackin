#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SesiOlahraga {
    string id;
    string cabang;
    float jarak; // dalam km
    int waktu; // dalam menit
    string hasilPace;
};

// Deklarasi fungsi / Primitif File I/O
void simpanData(SesiOlahraga data);
void muatData();

#endif