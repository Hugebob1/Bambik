#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int compare(Matrix *a, Matrix *b){
	if(a->r!=b->r || a->c!=b->c) return -1;
	for (int i = 0; i < (a->r)*(a->c); i++) {
        if (fabs(a->data[i][0] - b->data[i][0]) > 0.000001) return 0;
    }
	return 1;
}

int main(int argc, char ** argv) {
	int res = 0;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * expected = readFromFile(argv[3]);
	Matrix * x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A,b);
	if(res==0){
		x = createMatrix(b->r, 1);
		if (x != NULL) {
			res = backsubst(x,A,b);

			printToScreen(x);
			if(compare(x, expected)==1) 
				printf("Test zaliczony wynik poprawny\n");
			else printf("Test niezaliczony wynik niepoprawny!!!!\n");
		freeMatrix(x);
		} else {
						fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
		}
	}
	freeMatrix(A);
	freeMatrix(b);
	return 0;
}
