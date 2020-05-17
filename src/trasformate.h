#ifndef TRASFORMATE_H
#define TRASFORMATE_H
#include <complex.h> 
#include <math.h>

#define PI 3.1415926535/*8979323846*/

/*f. che calcola la DCT di una sequenza con N campioni*/
extern void DCT (double x[], int N);
/*f. che calcola la IDCT di una sequenza con N campioni*/
extern void IDCT (double C[], int N);
/*f. che calcola la DFT di una sequenza con N campioni*/
extern void DFT (double complex x[], int N); /*firma della f.*/
/*f. che calcola la IDFT di una sequenza con N campioni*/
extern void IDFT (double complex X[], int N);
/*f. che calcola la FFT di una sequenza con N campioni*/
extern void FFT(double complex buf[], int n);
/*stampa la sequenza in output*/
extern void show(const char * s, double complex buf[], int n);

#endif