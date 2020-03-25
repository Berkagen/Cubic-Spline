
#include <stdio.h>
#include <stdlib.h>

#define MAX_RANGE 21
    int main()          //Degiskenler tanımlandı.
    {
        double x[21] = {0.9, 1.3, 1.9, 2.1, 2.6, 3.0, 3.9, 4.4, 4.7, 5.0, 6.0, 7.0, 8.0, 9.2, 10.5, 11.3, 11.6, 12.0, 12.6, 13.0, 13.3};
        double fx[21] = {1.3, 1.5, 1.85, 2.1, 2.6, 2.7, 2.4, 2.15, 2.05, 2.1, 2.25, 2.3, 2.25, 1.95, 1.4, 0.9, 0.7, 0.6, 0.5, 0.4, 0.25};
        double* a,* h,* alfa ,* l,* m,* z,* c,* d,* b;

        a = (double*)malloc(MAX_RANGE * sizeof(double));        //Hafıza malloc fonksiyonu kullanılarak ayrıldı.
        h = (double*)malloc(MAX_RANGE * sizeof(double));
        m = (double*)malloc(MAX_RANGE * sizeof(double));
        z = (double*)malloc(MAX_RANGE * sizeof(double));
        c = (double*)malloc(MAX_RANGE * sizeof(double));
        d = (double*)malloc(MAX_RANGE * sizeof(double));
        b = (double*)malloc(MAX_RANGE * sizeof(double));
        l = (double*)malloc(MAX_RANGE * sizeof(double));
        alfa = (double*)malloc(MAX_RANGE * sizeof(double));




        for (int i = 0; i < MAX_RANGE; i++)             //natural cubic spline algoritması kullanılarak xj, aj, bj, cj ve dj degerleri bulundu.
        {
            a[i] = fx[i];
        }

        for (int i = 0; i < MAX_RANGE; i++)
        {
            h[i] = x[i + 1] - x[i];
        }
        
        for (int i = 1; i < MAX_RANGE; i++)
        {
            alfa[i] = (3 * (a[i + 1] - a[i]) / h[i]) - (3 * (a[i] - a[i - 1]) / h[i - 1]);
        }

        *l = 1;
        *m = *z = 0;

        for (int i = 1; i < MAX_RANGE; i++)
        {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * m[i - 1];
            m[i] = h[i] / l[i];
            z[i] = (alfa[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[MAX_RANGE-1] = 1;
        z[MAX_RANGE-1] = 0;
        c[MAX_RANGE-1] = 0;

        for (int j = MAX_RANGE - 1; j >= 0; j--)
        {
            c[j] = z[j] - (m[j] * c[j + 1]);
            b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
            d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
        }

        printf("j\t xj\t aj\t bj\t cj\t dj\t\n_____________________________________________\n");

        for (int j = 0; j < MAX_RANGE; j++)
        {
            if (j == 20)
            {
                printf("%d\t %.2lf\t %.2lf\t\n", j, x[j], a[j]);
            }

            else
            {
                printf("%d\t %.2lf\t %.2lf\t %.2lf\t %.2lf\t %.2lf\t\n", j, x[j], a[j], b[j], c[j], d[j]);
            }
        }
        free(a);
        free(h);
        free(m);
        free(z);
        free(c);
        free(d);
        free(b);
        free(l);
        free(alfa);
        return 0;
    }

