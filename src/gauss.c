#include "gauss.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9 

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    // Sprawdzenie poprawności wymiarów macierzy
    if (mat->r != mat->c || mat->r != b->r || b->c != 1) {
        fprintf(stderr, "Nieprawidłowe wymiary macierzy.\n");
        return 1; // Zwracamy błąd
    }

    int n = mat->r; // Rozmiar macierzy (kwadratowej)

    for (int k = 0; k < n; k++) {
        // Krok 1: Znajdowanie maksymalnego elementu w kolumnie (pivoting)
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat->data[i][k]) > fabs(mat->data[max_row][k])) {
                max_row = i;
            }
        }

        // Krok 2: Zamiana wierszy, jeśli pivot nie jest w odpowiednim miejscu
        if (fabs(mat->data[max_row][k]) < EPSILON) {
            fprintf(stderr, "Macierz jest osobliwa (element na przekątnej to zero).\n");
            return 1; // Macierz nieodwracalna
        }

        if (max_row != k) {
            double *temp = mat->data[k];
            mat->data[k] = mat->data[max_row];
            mat->data[max_row] = temp;

            // Zamiana także w macierzy b
            double tmp_b = b->data[k][0];
            b->data[k][0] = b->data[max_row][0];
            b->data[max_row][0] = tmp_b;
        }

        // Krok 3: Eliminacja Gaussa
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];
            mat->data[i][k] = 0; // Element poniżej diagonali staje się zerem

            for (int j = k + 1; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // Aktualizacja macierzy b
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // Sukces
}

