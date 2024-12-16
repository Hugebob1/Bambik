#include "backsubst.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	 // Sprawdzanie poprawności rozmiarów macierzy
    if (mat->r != mat->c || mat->r != b->r || x->r != b->r || x->c != 1 || b->c != 1) {
        fprintf(stderr, "Nieprawidłowe wymiary macierzy.\n");
        return 2; // Błąd nieprawidłowych rozmiarów
    }

    int n = mat->r; // Liczba wierszy/kolumn macierzy

    // Inicjalizacja macierzy wynikowej x
    for (int i = 0; i < n; i++) {
        x->data[i][0] = 0.0;
    }

    // Wsteczne podstawienie
    for (int i = n - 1; i >= 0; i--) {
        // Sprawdzenie, czy element na przekątnej jest bliski zeru
        if (fabs(mat->data[i][i]) < EPSILON) {
            fprintf(stderr, "Błąd: Dzielenie przez 0 (element na diagonali = 0).\n");
            return 1; // Błąd dzielenia przez zero
        }

        // Obliczenie wartości x[i]
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += mat->data[i][j] * x->data[j][0];
        }
        x->data[i][0] = (b->data[i][0] - sum) / mat->data[i][i];
    }

    return 0; // Sukces
}


