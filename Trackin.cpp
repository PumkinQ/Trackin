#include <iostream>
#include "Trackin.h"

using namespace std;

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