#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <string>
#include "sesi.h"

using namespace std;

const int MAX_STACK = 50;

struct StackUndo {
    infotypeSesi info[MAX_STACK];
    int Top;
};

void createStack(StackUndo &S);
/* I.S. sembarang
   F.S. terbentuk stack kosong dengan Top = -1 */

bool isEmpty(StackUndo S);
/* I.S. S terdefinisi
   F.S. mengembalikan true jika stack kosong */

bool isFull(StackUndo S);
/* I.S. S terdefinisi
   F.S. mengembalikan true jika stack penuh */

void push(StackUndo &S, infotypeSesi x);
/* I.S. S dan x terdefinisi
   F.S. jika tidak penuh, x ditambahkan ke puncak stack S */

void pop(StackUndo &S, infotypeSesi &x, bool &berhasil);
/* I.S. S terdefinisi
   F.S. jika tidak kosong, elemen puncak dikeluarkan ke x dan berhasil = true */

void viewStack(StackUndo S);
/* I.S. S terdefinisi
   F.S. menampilkan isi stack dari Top hingga indeks 0 */

#endif
