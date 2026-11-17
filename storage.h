#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "Trackin.h" // mengambil struct SesiOlahraga

using namespace std;

// Deklarasi fungsi / Primitif File I/O
void simpanData(SesiOlahraga data);
void muatData();

#endif