// ACO: ant colony optimization for solving the traveling salesperson problem

// Haupt & Haupt
// 2003

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double random(double x0, double x1)
{
    return x0 + (x1 - x0 * rand() / ((double)RAND_MAX));
}

int random030()
{
    int randomNumber030 = rand() % 30 + 1;
    return randomNumber030;
}

int main()
{
    int cont, cont2, cont3 = 0;      // Contadores de verificación
    int x, y, it, ic, ia, iq, iz;            // Loop Variables
    int Ncity = 30;       // Number of cities on tour
    int Nants = Ncity;    // Number of ants=number of cities

    // City Locations
    printf("Array xcityArray:\n\n");
    double xcityArray[29];
    for(x = 0; x < 30; x++)
    {
        xcityArray[x] = random(1,0);
        printf("%f\n",xcityArray[x]);
    }

    printf("\nNumero de iteraciones: %i\n",x);

    printf("\nArray ycityArray:\n\n");
    double ycityArray[29];
    for(y = 0; y < 30; y++)
    {
        ycityArray[y] = random(1,0);
        printf("%f\n",ycityArray[y]);
    }

    printf("\nNumero de iteraciones: %i\n",y);
    // Cities are located at (xcity,ycity)


    // Distance between cities
    printf("\nArray dcityArray:\n\n");
    double dcityArray[29][29];
    for(x = 0; x < 30; x++)
    {
        for(y = 0; y < 30; y++)
        {
            dcityArray[x][y]=sqrt(pow((xcityArray[x]-xcityArray[y]),2)+pow((ycityArray[x]-ycityArray[y]),2));
            printf("%f\n",dcityArray[x][y]);
        }
    }

    printf("\nNumero de iteraciones: X:%i & Y:%i",x,y);

    // Visibility equals inverse of distance
    printf("\nArray visArray:\n\n");
    double visArray[29][29];
    for(x = 0; x < 30; x++)
    {
        for(y = 0; y < 30; y++)
        {
            visArray[x][y]=1/dcityArray[x][y];
            printf("%f\n",visArray[x][y]);
        }
    }

    // Initialized pheromones between cities
    printf("\nArray phmoneArray:\n\n");
    double phmoneArray[29][29];
    for(x = 0; x < 30; x++)
    {
        for(y = 0; y < 30; y++)
        {
            phmoneArray[x][y]=0.1;
            printf("%f\n",phmoneArray[x][y]);
        }
    }

    int maxit = 600;    // Max number of iterations

    // a1=0 - closest city is selected
    // be=0 - algorithm only works w/ pheromones and not distance of city
    // Q - close to the lenght of the optimal tour
    // rr - trail decay
    int a = 2;
    int b = 6;
    double rr = 0.5;

    int dbest = 9999999;
    int e = 5;

    // Initialize tours
    printf("\nArray tourArray:\n\n");
    double tourArray[30][29];
    for(x = 0; x < 30; x++)
    {
        for(y = 0; y < 30; y++)
        {
            tourArray[x][y]=random030();
            printf("%f\n",tourArray[x][y]);
        }
    }
    // Tour ends on city it starts with
    printf("\nArray tourArray + 1:\n\n");
    for(y = 0; y < 30; y++)
    {
        tourArray[30][y]=tourArray[0][y];
        printf("%f\n",tourArray[30][y]);
    }

    // Comienza el Super Ciclo
    printf("\nSuper Cycle Start:\n\n");
    int m, n; // Contador para ansArray
    double ansArray[31][29];
    double nxtArray[0][28];
    double probArray[0][28];
    int st; // Variable st
    double sum = 0;
    double rcity;
    double sumProb;
    int newcity;
    int tamanoProbArray = 29;

    for(it = 0; it < 1; it++)
    {
        // Find the city tour for each ant
        // ST is the current city
        // NXT contains the remaining cities to be visited
        for(ia = 0; ia < 1; ia++)
        {
            for(iq = 1; iq < Nants-1; iq++)
            {
                // Resolver el ansArray
                printf("\nArray ansArray:\n\n");
                ansArray[0][0] = iq+1;
                for(m = 0; m < 31; m++)
                {
                    ansArray[0][m+1] = tourArray[0][m];
                    printf("%f\n",ansArray[0][m]);
                }

                // Resolver st
                st = tourArray[ia][iq-2];
                printf("\n\nst: %f",st);
                printf("\n\n");

                // Resolver nxtArray
                printf("\nArray nxtArray:\n\n");
                for(m = 0; m < 28; m++)
                {
                    nxtArray[0][m] = tourArray[0][m+1];
                    printf("%f\n",nxtArray[0][m]);
                }

                //Resolver prob
                printf("\nArray probArray:\n\n");
                for(m = 0; m < 28; m++)
                {
                    probArray[0][m]=((pow(phmoneArray[st-1][m],a))*(pow(visArray[st-1][m],b)));
                    sum += probArray[0][m];
                    printf("%f\n",probArray[0][m]);
                }

                
                //Ultimo Update revisado
//                //Resolver rcity
//                rcity=random(1,0);
//
//                printf("\n\ntamanoProbArray: %i",tamanoProbArray);
//
//                for(iz = 0; iz < tamanoProbArray; iz++)
//                {
//                    for(m = 0; m < iz+1; m++)
//                    {
//                        sumProb += probArray[0][m];
//                        printf("\n\nsumProb: %f",sumProb);
//                    }
//                    if(rcity < sumProb)
//                    {
//                        newcity = iq-1+iz;
//                        printf("\n\nst: %i",newcity);
//                    }
//                } // End of iz
            }// End of iq
        }// End of ia

        tamanoProbArray--;
    }// End of it

    return 0;
}
