#include "search.h"
#include <iostream>

using namespace std;

addressList cariSesiBerdasarkanCabang(List L, string cabangDicari) {
    addressList P = L.first; 

    while (P != Nil) {
        if (P->info.cabang == cabangDicari) {
            return P;
        }
        P = P->next;
    }
    
    return Nil; 
}