#include "stack.h"

void createStack(StackUndo &S) {
    S.Top = -1;
}

bool isEmpty(StackUndo S) {
    return (S.Top == -1);
}

bool isFull(StackUndo S) {
    return (S.Top == MAX_STACK - 1);
}

void push(StackUndo &S, infotypeSesi x) {
    if (isFull(S)) {
        cout << "Stack Undo penuh (maksimal " << MAX_STACK << " sesi).\n";
    } else {
        S.Top = S.Top + 1;
        S.info[S.Top] = x;
    }
}

void pop(StackUndo &S, infotypeSesi &x, bool &berhasil) {
    if (isEmpty(S)) {
        berhasil = false;
    } else {
        x = S.info[S.Top];
        S.Top = S.Top - 1;
        berhasil = true;
    }
}

void viewStack(StackUndo S) {
    if (isEmpty(S)) {
        cout << "Stack Undo kosong. Belum ada sesi baru pada sesi aplikasi ini.\n";
    } else {
        cout.setf(ios::fixed);
        cout.precision(2);

        int i = S.Top;
        int nomor = 1;
        while (i >= 0) {
            cout << nomor << ". ";
            if (i == S.Top) {
                cout << "[TOP] ";
            }
            cout << S.info[i].cabang << " (" << S.info[i].subJenis << ")"
                 << " | Jarak: " << S.info[i].jarakAktual << " KM"
                 << " | Hasil: " << S.info[i].paceAktual << " " << S.info[i].satuanPace
                 << " | Status: " << S.info[i].statusEvaluasi << "\n";
            i--;
            nomor++;
        }
    }
}
