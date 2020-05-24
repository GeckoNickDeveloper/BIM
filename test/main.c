#include <stdio.h> 
#include <complex.h>
#include <stdlib.h>
#include <time.h>
#include "../src/trasformate.h"
#include "../src/color.h"
#include "../src/image.h"
#include "../src/ppm.h"

#define LDR				"./img/ldr.ppm"
#define LADYMARIA		"./img/ladymaria.ppm"
#define FORHONOR		"./img/forhonor.ppm"
#define HOLLOWKNIGHT	"./img/hollowknight.ppm"
#define OUTPUT			"./img/output.ppm"

int leggi_range(int min, int max);
int leggi_intero();

int main ()
{
    int c, cnt = 1, d, i, n, elab;
    double* real_seq;
    double complex* cpl_seq;
    char *filename;
    rgb_i *img;

    printf("\n\t (ʘ‿ʘ)╯ \n\nIo sono B.I.M., un Basic Image Manipulator. ");
   do
   {
        printf("Cosa vuoi che faccia? \n\n");
        printf("\t1 - Calcolo di trasformate \n");
        printf("\t2 - Elaborazione immagini \n");
        printf("\t3 - Esci\n>> " );
        c = leggi_range( 1, 3);
        switch (c)
        {
        case 1:
            printf("\nQuale trasformata devo calcolare? \n\n");
            printf("\t1 - DCT: trasformata discreta del coseno \n");
            printf("\t2 - FFT: trasformata di Fourier veloce \n");
            printf("\t3 - DFT: trasformata discreta di Fourier\n>> " );
            d = leggi_range (1, 3);
            printf("\nQuanti campioni devo inserire nella sequenza? \n\n>> ");
            n = leggi_intero();
            srand (time(NULL));
            switch (d)
                {
                    case 1: 
                        real_seq = (double*) malloc(sizeof(double) * n);
                        for ( i = 0; i < n; i++ )
                            {
                                real_seq [i] = (double) (rand()%1001) / 100;
                            }
                        printf("\nLa seq. di partenza è: \t");
                        for ( i = 0; i < n; i++ )
                        {
                            printf("%c", (i == 0) ? '{': ' ' );
                            printf("(%.2lf)", real_seq[i]);
                            printf("%c", (i == n-1) ? '}': ',' );
                        }
                        DCT(real_seq, n);
                        printf("\n\nLa sua DCT è: \t\t");
                        for ( i = 0; i < n; i++ )
                        {
                            printf("%c", (i == 0) ? '{': ' ' );
                            printf("(%.4lf)", real_seq[i]);
                            printf("%c", (i == n-1) ? '}': ',' );
                        }
                        IDCT(real_seq, n);
                        printf("\n\nLa sua IDCT è: \t\t");
                        for ( i = 0; i < n; i++ )
                        {
                            printf("%c", (i == 0) ? '{': ' ' );
                            printf("(%.2lf)", real_seq[i]);
                            printf("%c", (i == n-1) ? '}': ',' );
                        }

                        break;
                        
                    case 2:/*da capire come rappresentare le sequenze complesse*/
                        int pot;
                        for(pot = 1 ; pot < n; )
                        pot *= 2;
                        cpl_seq = (double complex*) malloc(sizeof(double complex) * pot);
                        for ( i = 0; i < pot; i++ )
                            {
                                if ( i < n )
                                cpl_seq [i] = (double complex) (rand()%1001) /100.0;
                                else
                                    cpl_seq[i] = 0;  
                            }
                        printf("\n\t!! ATTENZIONE: Se il nr. di campioni NON è una pot. di 2, devo eseguire un padding a zero !!");
                        show("\n\nLa seq. iniziale è: { ", cpl_seq, pot);
                        printf("}\n\n");
                        FFT(cpl_seq, pot);
                        show("La FFT è: {", cpl_seq, pot);
                        printf("}");
                        IDFT(cpl_seq, pot);
                        show("\n\nLa IFFT è: {", cpl_seq, pot);
                        printf("}");
                        break;
                    case 3:
                        cpl_seq = (double complex*) malloc(sizeof(double complex) * n);
                        for ( i = 0; i < n; i++ )
                            {
                                cpl_seq [i] = (double complex) (rand()%1001) /100.0; 
                            }
                        show("\n\nLa seq. iniziale è: { ", cpl_seq, n);
                        printf("}\n\n");
                        DFT(cpl_seq, n);
                        show("La DFT è: {", cpl_seq, n);
                        printf("}");
                        IDFT(cpl_seq, n);
                        show("\n\nLa IDFT è: {", cpl_seq, n);
                        printf("}");
                }
                printf("\n\n\t٩(^‿^)۶\n\n");
            break;
        case 2:
            printf("\nQuale immagine devo elaborare? \n\n");
            printf("\t1 - ladymaria.ppm\n");
            printf("\t2 - ldr.ppm\n");
            printf("\t3 - forhonor.ppm\n");
            printf("\t4 - hollowknight.ppm\n");
            printf("\t5 - output.ppm\n>> ");
            d = leggi_range(1, 5);
            switch (d)  /* Seleziono il file da caricare */
            {
                case 1:
                    filename = (char*) LADYMARIA;
                    break;
                case 2:
                    filename = (char*) LDR;
                    break;
                case 3:
                    filename = (char*) FORHONOR;
                    break;
                case 4:
                    filename = (char*) HOLLOWKNIGHT;
                    break;
                case 5:
                    filename = (char*) OUTPUT;
                    break;
            }
            img = readPPM(filename);

            printf("\nScegliere un'operazione:\n");
            printf("\t1 - Smoothing\n");
            printf("\t2 - Sharpening\n");
            printf("\t3 - Negativo\n>> ");
            elab = leggi_range(1, 3);
            switch (elab)  /* Eseguo l'elaborazione */
            {
                case 1:
                    printf("\nScegliere la dimensione della maschera (le maschere di dimensione pari verranno incrementate di 1):\n>> ");
                    n = leggi_intero();
                    smooting(img, (uint8_t) n);
                    break;
                case 2:
                    printf("\nScegliere la forza dello sharpening (in percentuale, es. 50 per il 50%%):\n>> ");
                    n = leggi_intero();
                    sharpening(img, ((double) n) / 100.0);
                    break;
                case 3:
                    complementar(img);
                    break;
            }
            writePPM(OUTPUT, img);
            printf("\nImmagine elaborata salvata come \"%s\" in \"./img/output/\"\n", OUTPUT);

            printf("\n\n\t<(^_^)>\n\n");
            break;
        case 3: 
            cnt = 0;
            
            printf("\t...ᕕ( ᐛ )ᕗ...\n");
            break;
        }
   } while (cnt);

    return 0;
}

int leggi_range (int min, int max)
{
    int esito, valore;
   
    do
    {
        esito = scanf("%d", &valore);
        if (esito != 1 || valore < min || valore > max)
            printf("Input non valido...\n>> ");
        while (getchar() != '\n');
    } while (esito != 1 || valore < min || valore > max);

    return valore;
}

int leggi_intero ()
{
    int esito, valore;
   
    do
    {
        esito = scanf("%d", &valore);
        if (esito != 1 || valore <= 0)
            printf("Input non valido...\n>> ");
        while (getchar() != '\n');
    } while (esito != 1 || valore <= 0);

    return valore; 
}


/* SINTASSI DOXYGEN: \fn [firma della f], \brief [breve descrizione], \param [nome parametro] [funzione] , \return [il ritorno della funzione], \detail
ES: 
\fn void fft(double complex buff[], int n)
\param buff Buffer for the fft
\param n Number of samples
\brief this is the fft
*/