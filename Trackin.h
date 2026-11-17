#ifndef TRACKIN_H_INCLUDED
#define TRACKIN_H_INCLUDED

#define Nil NULL

typedef int infotype;
typedef struct elmQueue *address;

struct SesiOlahraga {
    string id;
    string cabang;
    float jarak; // dalam km
    int waktu; // dalam menit
    string hasilPace;
};