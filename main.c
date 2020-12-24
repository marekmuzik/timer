//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//sirka v kladnych nenulovych celociselnych nasobcich 15
#define SIRKA 15
//vyska v kladnych nenulovych celociselnych nasobcich 17
#define VYSKA 17
//margin minimalne 2
#define MARGIN 2
//sirka s margin
#define SIRKAMARGIN (SIRKA + (2*MARGIN))
//vyska s margin
#define VYSKAMARGIN (VYSKA + (2*MARGIN))


int* souradniceBodu(int sekundy){

    //[radek][sloupec]
    int cilovyRadek;
    int cilovySloupec;

    //dynamicka alokace
    int* souradnice = (int*) malloc(4*sizeof(int));

    //vychozi bod
    int vychoziRadek = (int) floor((double)VYSKA/2) + MARGIN;
    int vychoziSloupec = (int) floor((double)SIRKA/2) + MARGIN;

    //podminky pro urceni ciloveho bodu
    if (0 <= sekundy && sekundy <= 6) {
        cilovyRadek = MARGIN;
        cilovySloupec = round(SIRKA/15) * (sekundy + 7) + MARGIN;
    } else if (7 <= sekundy && sekundy <= 23) {
        cilovyRadek = round(VYSKA/17) * (sekundy - 7) + MARGIN;
        cilovySloupec = SIRKA + MARGIN - 1;
    } else if (24 <= sekundy && sekundy <= 36) {
        cilovyRadek = VYSKA + MARGIN - 1;
        cilovySloupec = round(SIRKA/15) * (37 - sekundy) + MARGIN;
    } else if (37 <= sekundy && sekundy <= 53) {
        cilovyRadek = round(VYSKA/17) * (53 - sekundy) + MARGIN;
        cilovySloupec = MARGIN;
    } else if (54 <= sekundy && sekundy <= 59) {
        cilovyRadek = MARGIN;
        cilovySloupec = round(SIRKA/15) * (sekundy - 53) + MARGIN;
    }
    
    souradnice [0] = cilovyRadek;
    souradnice [1] = cilovySloupec;
    souradnice [2] = vychoziRadek;
    souradnice [3] = vychoziSloupec;

    return souradnice;
}

void generujCifernik(char** cifernik){

    //nastaveni vsech hodnot v poli na prazdny znak (mezeru)
    for (int i = 0; i < VYSKAMARGIN; i++){
        memset(cifernik[i], ' ' , SIRKAMARGIN * sizeof(char));
    }
    
    //vykresleni okraju ciferniku
    for (int cilovySloupec = MARGIN; cilovySloupec < (SIRKAMARGIN-MARGIN); cilovySloupec++) {
        if (cilovySloupec == MARGIN || cilovySloupec == ((SIRKAMARGIN - MARGIN)-1) ) {
            for (int cilovyRadek = MARGIN; cilovyRadek < (VYSKAMARGIN-MARGIN); cilovyRadek++) {
                cifernik[cilovyRadek][cilovySloupec] = '|';
            }
        } else {
            cifernik[MARGIN][cilovySloupec] = '-';
            cifernik[((VYSKAMARGIN - MARGIN)-1)][cilovySloupec] = '-';
        }
    }

    //vykresleni zakladnich casovych milniku pro orientaci
    int* souradnice; //deklarace pointeru 

    souradnice = souradniceBodu(0);
    cifernik[souradnice[0] - 1][souradnice[1]] = '0';
    cifernik[souradnice[0] - 2][souradnice[1]] = '0';
    free(souradnice); //uvolneni pameti
    souradnice = NULL;

    souradnice = souradniceBodu(15);
    cifernik[souradnice[0]][souradnice[1] + 1] = '1';
    cifernik[souradnice[0]][souradnice[1] + 2] = '5';
    free(souradnice); //uvolneni pameti
    souradnice = NULL;

    souradnice = souradniceBodu(30);
    cifernik[souradnice[0] + 1][souradnice[1]] = '3';
    cifernik[souradnice[0] + 2][souradnice[1]] = '0';
    free(souradnice); //uvolneni pameti
    souradnice = NULL;

    souradnice = souradniceBodu(45);
    cifernik[souradnice[0]][souradnice[1] - 1] = '5';
    cifernik[souradnice[0]][souradnice[1] - 2] = '4';
    free(souradnice); //uvolneni pameti
    souradnice = NULL;
}

void printCifernik(char** cifernik) {

    //vypsani ciferniku do konzole
    for (int cilovyRadek = 0; cilovyRadek < VYSKAMARGIN; cilovyRadek ++){
        for(int cilovySloupec = 0; cilovySloupec < SIRKAMARGIN; cilovySloupec ++){
            printf("%c", cifernik[cilovyRadek][cilovySloupec]);
        }
        printf("\n");
    }
}

void nastavRucicku(char** cifernik, int sekundy){
    
    int* souradnice;//deklarace pointeru
    souradnice = souradniceBodu(sekundy);

    //nacteni souradnic
    int cilovyRadek = souradnice [0];
    int cilovySloupec = souradnice [1];
    int vychoziRadek = souradnice [2];
    int vychoziSloupec = souradnice [3];

    //stred ciferniku
    cifernik [vychoziRadek] [vychoziSloupec] = '+';

    //      [x0]           [y0]
    //[cilovyRadek][cilovySloupec]
    // int cilovyRadek;  (x0)
    // int cilovySloupec; (y0)

    //      [x1]           [y1]
    // [vychoziRadek][vychoziSloupec]
    // int vychoziRadek; (x1)
    // int vychoziSloupec; (y1)

    //Bresenhamuv algoritmus
    int rozdilX = abs(vychoziRadek - cilovyRadek);
    int porovnaniX = cilovyRadek < vychoziRadek ? 1 : -1;
    int rozdilY = -abs(vychoziSloupec - cilovySloupec);
    int porovnaniY = cilovySloupec < vychoziSloupec ? 1 : -1;
    int odchylka = rozdilX + rozdilY;

    while (!(cilovyRadek == vychoziRadek && cilovySloupec == vychoziSloupec)) {
        cifernik [cilovyRadek] [cilovySloupec] = '#';
        int dvojnasobnaOdchylka = 2 * odchylka;

        if (dvojnasobnaOdchylka >= rozdilY) {
            odchylka += rozdilY;
            cilovyRadek += porovnaniX;
        }
        else if (dvojnasobnaOdchylka <= rozdilX) {
            odchylka += rozdilX;
            cilovySloupec += porovnaniY;
        }
    }

    //uvolneni pameti
    free(souradnice);
    souradnice = NULL;
}


int main () {
    int sekundy;
    
    //osetreni
    if (MARGIN < 2) {
        printf("\nNeplana hodnota MARGIN, min 2!\n");
        return -1;
    }

    if (SIRKA%15 != 0 || VYSKA%17 != 0) {
        printf("\nNeplatna hodnota VYSKA nebo SIRKA!\n");
        return -1;
    }

    printf("Zadejte pocet sekund:\n");
    scanf("%d", &sekundy);

    if (!(sekundy >= 0 && sekundy <= 59)) {
        printf("\nNeplatna hodnota sekund! Zadejte pocet sekund v intervalu <0,59>!\n");
        return -1;
    }

    //dynamicka alokace ciferniku
    char** cifernik = (char **) malloc(VYSKAMARGIN * sizeof(char *));
    for (int i = 0; i < VYSKAMARGIN; i++) {
        cifernik[i] = (char *) malloc(SIRKAMARGIN * sizeof(char));
        memset(cifernik[i], ' ' , SIRKAMARGIN * sizeof(char));
    }

    //vypis ciferniku od zadane hodnoty
    for (int i = sekundy; sekundy >= 0; i--) {
        generujCifernik(cifernik);
        nastavRucicku(cifernik, i);
        printf("\n%d. sekunda\n",i);
        printCifernik(cifernik);
    }


    //uvolneni pameti
    for (int i = 0; i < VYSKAMARGIN; i++) {
        free(cifernik[i]);
    }
    free(cifernik);
    cifernik = NULL;

    return 0;
}