#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    de precizat ca la citire casutele goale contin valoarea 0
 */


typedef struct {
    int i, j, val;
} poz;

typedef struct {
    poz pos[5];
} pentomino;

void afis( int **tabla ) {

    for ( int i = 0; i < 5; i++ ) {
        for ( int j = 0; j < 5; j++ )
            printf("%d", tabla[i][j]);
        printf("\n");
    }
}

bool verificare_acoperire(pentomino *p) {
    int **mat = (int **)malloc(sizeof(int*) * 5);
    for (int i = 0; i < 5; i++) {
        mat[i] = (int *)calloc(5, sizeof(int));
    }

    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            mat[p[k].pos[i].i][p[k].pos[i].j] = 1;
        }
    }

    bool valid = true;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] == 0) {
                valid = false;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        free(mat[i]);
    }
    free(mat);

    return valid;
}

bool e_ok(int posi, int posj, int **tabla, pentomino *p) {
    int val = tabla[posi][posj];
    if (val == 0) return true;

    int cntlinie = 0, cntcoloana = 0;

    for (int i = 0; i < 5; i++) {
        if (tabla[posi][i] == val) cntlinie++;
        if (tabla[i][posj] == val) cntcoloana++;
    }

    if (cntlinie > 1 || cntcoloana > 1) {
        return false;
    }


    int al_catelea = -1;
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            if (p[k].pos[i].i == posi && p[k].pos[i].j == posj) {
                al_catelea = k;
                break;
            }
        }
        if (al_catelea != -1) break;
    }

    int cntpentomino = 0;
    for (int i = 0; i < 5; i++) {
        int r = p[al_catelea].pos[i].i;
        int c = p[al_catelea].pos[i].j;

        if (tabla[r][c] == val) {
            cntpentomino++;
        }
    }

    if (cntpentomino > 1) {
        return false;
    }

    return true;
}

bool bkt(int pas, int **tabla, pentomino *p) {

    if (pas == 25) {
        afis(tabla);
        return true;
    }


    int r = pas / 5;
    int c = pas % 5;


    if (tabla[r][c] != 0) {
        return bkt(pas + 1, tabla, p);
    }

    for (int v = 1; v <= 5; v++) {
        tabla[r][c] = v;
        if (e_ok(r, c, tabla, p)) {
            if (bkt(pas + 1, tabla, p)) {
                return true;
            }
        }
    }
    tabla[r][c] = 0;
    return false;
}

int main(void) {
    pentomino *p = (pentomino *)malloc(5 * sizeof(pentomino));
    int **tabla = (int **)malloc(sizeof(int*) * 5);

    for ( int i = 0; i < 5; i++ ) {
        tabla[i] = (int *)calloc(5, sizeof(int));
    }

    if (p == NULL) {
        printf("alocarea memoriei.\n");
        return -1;
    }

    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            scanf("%d %d %d", &p[k].pos[i].i, &p[k].pos[i].j, &p[k].pos[i].val);
        }
    }

    if (verificare_acoperire(p) == false) {
        printf("piesele date nu acopera toata tabla.\n");
        for(int i = 0; i < 5; i++) free(tabla[i]);
        free(tabla);
        free(p);
        return -1;
    }
    bkt(0, tabla, p);

    for (int i = 0; i < 5; i++) {
        free(tabla[i]);
    }
    free(tabla);

    free(p);

    return 0;
}