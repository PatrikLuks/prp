#include <stdio.h>
#include <stdlib.h>

#define VSTUP "casy.txt"
#define VYSTUP "platby.txt"
#define ZDARMA 2
#define HODINOVA_SAZBA 20

int casNaSekundy(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

int dobaParkovani(int h1, int m1, int s1, int h2, int m2, int s2) {
    return casNaSekundy(h2, m2, s2) - casNaSekundy(h1, m1, s1);
}

int main() {
    FILE *fw, *fr;
    int h1, m1, s1, h2, m2, s2;
    int poradi = 0;
    int poradiSoubor = 0;
    int dobaNadLimit;
    int doba;
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
    fprintf(fw, "Parkoviste - P L A T B Y\n");
    fprintf(fw, "-------------------------\n");
    fprintf(fw, "Pocet hodin parkovani zdarma : %d\n", ZDARMA);
    fprintf(fw, "Hodinova sazba po prekroceni limitu : %d Kc\n", HODINOVA_SAZBA);
    fprintf(fw, "------------------------------------------------------------------\n");
    fprintf(fw, "Poradi  cas vjezdu  cas vyjezdu  doba parkovani  nad limit  platba\n");
    fprintf(fw, "------------------------------------------------------------------\n");
    printf("P A R K O V I S T E\n");
    printf("------------------------------------------\n");
    printf("poradi  cas     cas      doba parkovani\n");
    printf("        vjezdu  vyjezdu  sekundy    cas\n");
    printf("------------------------------------------\n");
    while (fscanf(fr, "%d%d%d%d%d%d", &h1, &m1, &s1, &h2, &m2, &s2) == 6) {
        poradi++;
        doba = dobaParkovani(h1, m1, s1, h2, m2, s2);
        printf("%2d. %02d:%02d:%02d %02d:%02d:%02d %10d %02d:%02d:%02d\n", poradi, h1, m1, s1, h2, m2, s2,
               doba, doba / 3600, (doba - doba / 3600 * 3600) / 60, doba % 60);
        if (doba > ZDARMA * 3600) {
            poradiSoubor++;
            dobaNadLimit = doba - ZDARMA * 3600;
            fprintf(fw, "%5d.    %02d:%02d:%02d     %02d:%02d:%02d        %02d:%02d:%02d    "
                        "%02d:%02d:%02d %5d Kc\n", poradiSoubor, h1, m1, s1,
                    h2, m2, s2, doba / 3600, (doba - doba / 3600 * 3600) / 60, doba % 60,
                    dobaNadLimit / 3600, (dobaNadLimit - dobaNadLimit / 3600 * 3600) / 60, dobaNadLimit % 60,
                    (dobaNadLimit / 3600 + (dobaNadLimit % 3600 > 0 ? 1 : 0)) * HODINOVA_SAZBA);
        }

    }
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
