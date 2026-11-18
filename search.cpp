#include "search.h"
#include <iostream>

using namespace std;

addressList cariSesiBerdasarkanID(List L, string idDicari) {
    addressList P = L.first; 

    while (P != Nil) {
        if (P->info.id == idDicari) {
            return P;
        }
        P = P->next;
    }
    
    return Nil; 
}