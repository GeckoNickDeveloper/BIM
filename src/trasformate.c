#include "trasformate.h" /*la nostra libreria*/
#include <stdio.h> /*lib standard input*/
#include <math.h> /*f base dell'analisi*/
#include <complex.h> /* manipolazione complessi*/
#include <stdlib.h> /* lib allocazione + tipi di dato*/


void DCT (double x[], int N) /* ciclo for 1: Scorre gli elementi, 2: Esegue la sommatoria 3:*/
{
    double *C = (double*) malloc(sizeof(double) * N);
    int n, k;

    for( k = 0; k < N; k++ )
    {
        for( n = 0, C[k] = 0; n < N; n++ )
        {
            C[k] += x[n] * cos((PI * ((2 * n) +1 )* k )/ (2 * N));
        }

        C[k] *= 2;
    }

    for (k = 0; k < N; k++)
    {
        x[k] = C[k];
    }

    free (C);
}

void IDCT (double C[], int N)
{
    double *x = (double*) malloc(sizeof(double) * N);
    int n, k;

    for( n = 0; n < N; n++ )
    {
        for( k = 1, x[n] = C[0]; k < N; k++ )
        {
            x[n] += 2 * C[k] * cos((PI * ((2 * n) +1 )* k )/ (2 * N));
        }
        x[n] /= 2 * N ;
    }

    for (k = 0; k < N; k++)
    {
        C[k] = x[k];
    }

    free (x);
}

void DFT (double complex x[], int N) /* 2 cicli for*/
{
    double complex z; /*var appoggio*/
    double complex *X = (double complex*) malloc(sizeof(double complex) * N); /* (tipo puntatore*) malloc (tipo dato) * nr campioni*/
    int k, n; /*contatori*/
   
    for(k = 0; k < N; k++)/* il 1° popola l'array dei risultati */
    {   
        for(n = 0, X[k] = 0; n < N; n++)/* il 2° la sommatoria */
        {
            z = ccos((-(2 * PI)/N) * n * k ) + I * csin((-(2 * PI)/N) * n * k ); /*calcolo z complesso*/
            X[k] += x[n] * z;
        }
    }
    
    for (k = 0; k < N; k++) /* preserva il dato*/
    {
        x[k] = X[k];
    }

    free (X);
}

void IDFT (double complex X[], int N)
{
    double complex z;
    double complex *x = (double complex*) malloc(sizeof(double complex) * N);
    int k, n;

    for(n = 0; n < N; n++)
    {
        for(k = 0, x[n] = 0; k < N; k++)/* la sommatoria */
        {
            z = ccos(((2 * PI)/N) * n * k ) + I * csin(((2 * PI)/N) * n * k ); /*calcolo z complesso*/
            x[n] += X[k] * z;
        }

        x[n] /= N; 
    }
    
    for (k = 0; k < N; k++) /* preserva il dato*/
    {
        X[k] = x[k];
    }

    free (x);
}

void _fft(double complex buf[], double complex out[], int n, int step)
{
	int i;
    if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (i = 0; i < n; i += 2 * step) {
			double complex t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void FFT(double complex buf[], int n)
{
	int i;
    double complex out[n];
	for (i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, double complex buf[], int n) 
{
	int i;
    printf("%s", s);
	for (i = 0; i < n; i++)
		if (!cimag(buf[i]))
			printf("(%.4lf) ", creal(buf[i]));
		else
			printf("(%.4lf, %.4lf) ", creal(buf[i]), cimag(buf[i]));
}