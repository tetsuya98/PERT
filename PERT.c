//
//  main.c
//  PERT
//
//  Created by Josselin on 17/02/2020.
//  Copyright © 2020 Josselin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Tache Tache;
struct Tache {
    char nom; //Nom de la tâche
    int duree; //Durée de la tâche
    int debuttot; //Début au plus tôt
    int debuttard; //Début au plus tard
    int fintot; //Fin au plus tôt
    int fintard; //Fin au plus tard
    int margeT; //Marge Totale
    int margeL; //Marge Libre
};

void OrdTot(int n, int ASAP[n+1], int liaison[n][n], Tache tache[n]) {
    for (int i = 1; i < n; i++) {
        ASAP[i] = -1;
    }
    
    ASAP[0] = 0;
    int nbc = 1, pj, max;
    tache[0].debuttot = 0;
    
    while (nbc < n) {
        for (int i = 0; i < n; i++) {
            pj = 0;
            for (int j = 0; j < i && pj == 0; j++) {
                if (ASAP[j] == -1) {
                    pj = 1;
                }
            }
            if (ASAP[i] == -1 && pj == 0) {
                max = 0;
                for (int j = 0; j < i; j++) {
                    if (liaison[j][i] > 0 && ASAP[j] + tache[j].duree > max) {
                        max = ASAP[j] + tache[j].duree;
                    }
                }
                ASAP[i] = max;
                tache[i].debuttot = max;
                for (int j = 0; j < i; j++) {
                    if (liaison[j][i] > 0) {
                        tache[j].fintot = max;
                    }
                }
                nbc += 1;
            }
        }
    }
    ASAP[n] = ASAP[n-1] + tache[n-1].duree;
    tache[n-1].fintot = ASAP[n];
}

void OrdTard(int n, int ALAP[n+1], int ASAP[n+1], int liaison[n][n], Tache tache[n]) {
    for (int i = 0; i < n; i++) {
        ALAP[i] = 100; //+ l'infini
        printf("%d", ALAP[i] == 100);
    }
    for (int i = 0; i < n; i++) {
        tache[i].debuttard = 0;
    }
    
    ALAP[n] = ASAP[n];
    ALAP[n-1] = ASAP[n-1];
    tache[n-1].fintard = tache[n-1].fintot;
    
    int nbc = 1, pj, min;
    while (nbc < n) {
        for (int i = n-2; i >= 0; i--) {
            pj = 0;
            for (int j = i; j < n && pj == 0; j++) {
                if (ALAP[j] > 100) {
                    pj = 1;
                }
            }

            if (ALAP[i] == 100 && pj == 0) {
                
                min = 100;
                for (int j = 0; j < n; j++) {
                    if (liaison[i][j] > 0 && (tache[j].fintard - tache[j].duree) < min) {
                        min = tache[j].fintard - tache[j].duree;
                    }
                }
                ALAP[i] = min;
                tache[i].fintard = min;
                for (int j = i; j < n; j++) {
                    if (liaison[i][j] > 0) {
                        tache[j].debuttard = min;
                    }
                }
                nbc += 1;
            }
        }
    }
}

void margeT (int n, Tache tache[n]) { //calcul des marges totales
    for (int i = 0; i < n; i++) {
        tache[i].margeT = tache[i].fintard - tache[i].debuttot - tache[i].duree;
    }
}

void margeL (int n, Tache tache[n]) { //calcul des marges libres
    for (int i = 0; i < n; i++) {
        tache[i].margeL = tache[i].fintot - tache[i].debuttot - tache[i].duree;
    }
}

void tacheC (int n ,Tache tache[n], Tache tachesC[n]) { //calcul des tâches critiques
    for (int i = 0; i < n; i++) {
        if (tache[i].margeT == 0) {
            printf("Tâches Critiques %c\n", tache[i].nom);
        }
    }
}

void cheminC (int n ,Tache tache[n], int liaison[n][n], Tache tachesC[n]) { //calcul du chemin critique
    int i = -1, m = tache[n-1].fintard, flag = 0;
    
    for (int j = 0; j < n && i == -1; j++) {
        if (tache[j].margeT == 0 && tache[j].debuttot == 0) {
            i = j;
        }
    }
    while (tache[i].fintot < m) {
        printf("%c => ", tache[i].nom);
        flag = 0;
        for (int j = i; j < n && flag == 0; j++) {
            if (liaison[i][j] && tache[j].margeT == 0) {
                i = j;
                flag = 1;
            }
        }
    }
    printf("%c\n", tache[i].nom);
}
    

int main(int argc, const char * argv[]) {
    int liaison[12][12];
    Tache tache[12];
    int n = 12;
    int ASAP[13];
    int ALAP[13];
    Tache tachesC[12];
    

    Tache A;
    A.nom='A';
    A.duree=4;
    tache[0]=A;

    Tache B;
    B.nom='B';
    B.duree=8;
    tache[1]=B;

    Tache C;
    C.nom='C';
    C.duree=1;
    tache[2]=C;

    Tache D;
    D.nom='D';
    D.duree=1;
    tache[3]=D;

    Tache E;
    E.nom='E';
    E.duree=6;
    tache[4]=E;

    Tache F;
    F.nom='F';
    F.duree=3;
    tache[5]=F;

    Tache G;
    G.nom='G';
    G.duree=5;
    tache[6]=G;

    Tache H;
    H.nom='H';
    H.duree=3;
    tache[7]=H;

    Tache I;
    I.nom='I';
    I.duree=1;
    tache[8]=I;

    Tache J;
    J.nom='J';
    J.duree=2;
    tache[9]=J;

    Tache K;
    K.nom='K';
    K.duree=2;
    tache[10]=K;

    Tache L;
    L.nom='L';
    L.duree=5;
    tache[11]=L;

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            liaison[i][j]=0;
        }
    }

    liaison[0][4]=1;
    liaison[0][5]=1;
    liaison[1][6]=1;
    liaison[2][3]=1;
    liaison[3][8]=1;
    liaison[4][7]=1;
    liaison[5][7]=1;
    liaison[6][7]=1;
    liaison[7][10]=1;
    liaison[8][9]=1;
    liaison[9][11]=1;
    liaison[10][11]=1;
    
    printf("-------------------Liaisons--------------------\n\n");

    for(int j = 0; j < 12 ;j++) {
        for(int i = 0 ; i < 12 ; i++) {
            printf("%d ", liaison[i][j]);
        }
        printf("\n");
    }
    
    printf("--------------Ordonnancement Tôt---------------\n\n");
    
    OrdTot(n, ASAP, liaison, tache);
    
    for(int i = 0; i < n; i++) {
        printf("%c => debut tot %d et fin tot %d\n", tache[i].nom, tache[i].debuttot, tache[i].fintot);
    }
    
     printf("--------------Ordonnancement Tard--------------\n\n");
    
    OrdTard(n, ALAP, ASAP, liaison, tache);
    
    for(int i = 0; i < n; i++) {
        printf("%c => debut tard %d et fin tard %d\n", tache[i].nom, tache[i].debuttard, tache[i].fintard);
    }
    
     printf("\n------------------Marge Totale------------------\n\n");
    
    margeT(n, tache);
    
    for(int i = 0; i < n; i++) {
        printf("%c => marge total %d\n", tache[i].nom, tache[i].margeT);
    }
    
    printf("\n-------------------Marge Libre-------------------\n\n");
    
    margeL(n, tache);
    
    for(int i = 0; i < n; i++) {
        printf("%c => marge libre %d\n", tache[i].nom, tache[i].margeL);
    }
    
    printf("\n-----------------Tâches Critique------------------\n\n");
    
    tacheC(n, tache, tachesC);
    
    printf("\n-----------------Chemin Critique------------------\n\n");
    
    cheminC(n, tache, liaison, tachesC);
    
    return 0;
}


