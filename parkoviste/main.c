#include <stdio.h>
#include <stdlib.h>

#define VSTUP "vysky_vahy.txt"
#define VYSTUP "obezita.txt"

float vyskaMetrech(int vyska){
    return (float)vyska / 100; // Převedeno na metry
}

float indexBMI(float vyskaMetrech, int vaha){
    return vaha / (vyskaMetrech * vyskaMetrech); // Opraveno na výpočet BMI
}

int main(){
    FILE *fr, *fw;
    int vaha;
    int vyska;
    int poradi = 0;
    int poradiSoubor = 0;
    float bmi; // Přidána proměnná pro výpočet BMI
    float prumernaVyska = 0.0; // Proměnná pro průměrnou výšku

    fr = fopen(VSTUP, "r");
    if (fr == NULL) {
        printf("Soubor %s nebyl otevren.\n", VSTUP);
        return EXIT_FAILURE;
    }
    fw = fopen(VYSTUP, "w");
    if (fw == NULL) {
        printf("Soubor %s nebyl otevren.\n", VYSTUP);
        return EXIT_FAILURE;
    }
    printf("U D A J E   Z E   S O U B O R U\n");
    printf("-------------------------------\n");
    printf("poradi | vyska | vaha | BMI |  \n");
    printf("-------------------------------\n");
    fprintf(fw, "OBEZNI JEDINCI\n");
    fprintf(fw, "-------------------------------\n");
    fprintf(fw, "poradi | vyska | vaha | BMI |  \n");
    fprintf(fw, "-------------------------------\n");

    while (fscanf(fr, "%d%d", &vyska, &vaha) == 2) {
        poradi++;
        float vyskaVMetrech = vyskaMetrech(vyska);
        bmi = indexBMI(vyskaVMetrech, vaha);

        prumernaVyska += vyskaVMetrech; // Akumulace výšek pro výpočet průměru

        printf("%3d. | %3d|  %3d| %.1f|\n", poradi, vyska, vaha, bmi);

        if (bmi > 30) {
            poradiSoubor++;
            fprintf(fw, "%d. | %d|  %d| %.2f|\n", poradiSoubor, vyska, vaha, bmi);
        }
    }

    // Výpočet a výpis průměru výšek
    prumernaVyska /= poradi;
    printf("Prumerna vyska osob v souboru je %.2f metru\n", prumernaVyska);
    fprintf(fw, "Do %s byly zapsany udaje o %d obeznich osobach\n", VYSTUP, poradiSoubor);

    if (fclose(fr) == EOF) {
        printf("Soubor %s nebyl uspesne zavren.\n", VSTUP);
    }
    if (fclose(fw) == EOF) {
        printf("Soubor %s nebyl uspesne zavren.\n", VYSTUP);
    } else {
        printf("Byl vytvoren soubor %s.\n", VYSTUP);
    }
    return 0;
}
