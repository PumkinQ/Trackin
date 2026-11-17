#ifndef TRACKIN_H_INCLUDED
#define TRACKIN_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define Nil NULL

// --- DEKLARASI POINTER ---
typedef struct elmList *addressList;
typedef struct elmStack *addressStack;
typedef struct elmQueue *addressQueue;

struct SesiOlahraga
{
    string id;
    string cabang;
    float jarak; // dalam km
    int waktu;   // dalam menit
    string hasilPace;
};

typedef SesiOlahraga infotype;

// Struk MULTI LINKED LIST (Riwayat)
struct elmList
{
    infotype info;
    addressList next;
};

struct List
{
    addressList first;
};

// Struct STACK
struct elmStack
{
    infotype info;
    addressStack next;
};

struct Stack
{
    addressStack top;
};

// Struct queue
struct elmQueue
{
    infotype info;
    addressQueue next;
};

struct Queue
{
    addressQueue head;
    addressQueue tail;
};

// Deklarasi fungsi
// Fungsi Linked List
void createList(List &L);
addressList alokasiList(infotype x);
void insertLastList(List &L, addressList P);
void deleteLastList(List &L, addressList &P);
void showRiwayat(List L);

// Fungsi Stack
void createStack(Stack &S);
addressStack alokasiStack(infotype x);
void pushStack(Stack &S, addressStack P);
void popStack(Stack &S, addressStack &P);

// Fungsi Queue
void createQueue(Queue &Q);
addressQueue alokasiQueue(infotype x);
void enqueue(Queue &Q, addressQueue P);
void dequeue(Queue &Q, addressQueue &P);

// Fungsi Logika Aplikasi
void catatSesi(List &L, Stack &S, infotype dataBaru);
void undoSesi(List &L, Stack &S);

#endif