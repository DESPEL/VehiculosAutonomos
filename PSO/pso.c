#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double randfrom();
//void print2DMatrix(int n,int m, double matrix[n][m]);


#define npar 2  //Dimension of the Problem
#define popsize 10  //Size of the swarm
#define maxitt = 100


int main() {

    double mincIter[100];
    double globalIter[100];
    double meancIter[100];

    //C=1; % constriction factor
    double maxit = 100;// Maximum number of iterations
    double c1 = 1;     // c1 = 1; % cognitive parameter
    double c2 = 4 - c1; // c2 = 4-c1; % social parameter
    double c = 1; //C=1; % constriction factor


    //% Initializing swarm and velocities
    //par=rand(popsize,npar); % random population of continuous values
    double par[popsize][npar];
    for(int i = 0; i < popsize; i++){
        for(int j = 0; j > npar; j++){
            par[i][j] = randfrom(0,100);
        }
    }

    //vel = rand(popsize,npar); % random velocities
    double vel[popsize][npar];
    for(int i = 0; i < popsize; i++){
    for(int j = 0; j > npar; j++){
        vel[i][j] = randfrom(0,100);
     }
    }

    //cost=testfunctions(ff,par); % calculates population cost using ff
    double cost[popsize];
    for (int i = 0; i < popsize; i++){
        double x1 = par[i][0];
        double x2 = par[i][1];

        cost[i] = pow(x1,2.0) + pow(x2,2.0);
    }


    //meanc(1)=mean(cost); % mean cost
    //globalmin=minc(1); % initialize global minimum
    // % Initialize local minimum for each particle
    // localpar = par; % location of local minima

    //localcost = cost; % cost of local minima
    double localCost[popsize];

    //minc(1)=min(cost); % min cost
    double min = cost[0];

    double sum = 0;

    int index = 0;

    for(int i = 0; i < popsize; i++){
        if(cost[i] < min){
            index = i;
            min = cost[i];

        }
        localCost[i] = cost[i];
        sum += cost[i];
    }


    double mean = sum / popsize;
    printf("\nmeanc = %f  ", mean);

    double globalmin = min;
    printf("\nminc = %f \n ", globalmin);

    double localpar[popsize][npar];

    for(int i = 0; i < popsize; i++){
        for(int j = 0; j < npar; j++){
            localpar[i][j] = par[i][j];
        }
    }


    //% Finding best particle in initial population
    // [globalcost,indx] = min(cost);
    //  globalpar=par(indx,:);
    double globalpar[npar];
    double globalCost = globalmin;

    printf("\nglobalcost = %f \n", globalCost);


    for (int i = 0 ; i < npar; i++){
        globalpar[i] = par[index][i];
    }

    printf("GlobalParr = %f", globalpar[0]);

    //sdddjlfkkkkkkkkdd
    //% Start iterations

    double iter = 0;

    while (iter < maxit) {
        iter += 1;

        //Update velocity
        //double w = (maxit - iter)/ maxit;  //w=(maxit-iter)/maxit; %inertia weiindxht
        double w = 0.9000f;
        printf("\niter = %f \n", iter);
        printf("\nmaxit = %f \n", maxit);
        printf("\nw = %f \n", w);


        double r1[popsize][npar]; //r1 = rand(popsize,npar); % random numbers
        double r2[popsize][npar]; //r2 = rand(popsize,npar); % random numbers
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j > npar; j++) {
                r1[i][j] = randfrom(0, 100);
                r2[i][j] = randfrom(0, 100);
            }
        }


        //  vel = C*(w*vel + c1 *r1.*(localpar-par) + c2*r2.*(ones(popsize,1)*globalpar-par));
        printf("velo \n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                double velo = vel[i][j];
                double r11 = r1[i][j];
                double r22 = r2[i][j];
                double localparr = localpar[i][j];
                double parr = par[i][j];

                vel[i][j] = velo * w + c1 * (r11 * (localparr - parr)) + c2 * r22 * (1 * globalpar[j] - parr);
                printf("%f \t", vel[i][j]);
            }
            printf("\n");
        }



        //% update particle positions
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                par[i][j] += vel[i][j];        //par = par + vel; % updates particle position
            }
        }

        printf("par\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", par[i][j]);
            }
            printf("\n");

        }
        printf("\n");

        double overlimit[popsize][npar];
        double underlimit[popsize][npar];

        //overlimit=par<=1;
        //underlimit=par>=0;
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                if (par[i][j] <= 1) {
                    overlimit[i][j] = 1;

                } else {
                    overlimit[i][j] = 0;
                }

                if (par[i][j] >= 0) {
                    underlimit[i][j] = 1;
                } else {
                    underlimit[i][j] = 0;
                }


            }

        }

        printf("overlimit\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", overlimit[i][j]);
            }
            printf("\n");

        }
        printf("\n");

        printf("underlimit\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", underlimit[i][j]);
            }
            printf("\n");

        }
        printf("\n");


        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {


                double tempOverlimit;

                if (overlimit[i][j] == 1) {
                    tempOverlimit = 0;
                } else {
                    tempOverlimit = 1;
                }
                par[i][j] = par[i][j] * (overlimit[i][j]) + tempOverlimit;
                par[i][j] = par[i][j] * underlimit[i][j];
            }

        }

        printf("par * overlimit + not(overlimit)\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", par[i][j]);
            }
            printf("\n");

        }
        printf("\n");


        for (int i = 0; i < popsize; i++) {
            double x1 = par[i][0];
            double x2 = par[i][1];

            cost[i] = pow(x1, 2.0) + pow(x2, 2.0);
        }

        printf("new cost\n");
        for (int i = 0; i < popsize; i++) {
            printf("%f  ", cost[i]);
            printf("\n");

        }
        printf("\n");

        printf("local cost\n");
        for (int i = 0; i < popsize; i++) {
            printf("%f  ", localCost[i]);
            printf("\n");

        }
        printf("\n");

        double betterCost[popsize];

        for (int i = 0; i < popsize; i++) {
            if (cost[i] < localCost[i]) {
                betterCost[i] = 1;
            } else {
                betterCost[i] = 0;
            }


        }

        printf("bettercost\n");
        for (int i = 0; i < popsize; i++) {
            printf("%f  ", betterCost[i]);
            printf("\n");

        }
        printf("\n");


        for (int i = 0; i < popsize; i++) {
            double tempBetterCost = 1;

            if (betterCost[i] == 1) {
                tempBetterCost = 0;
            } else {
                tempBetterCost = 1;
            }

            localCost[i] = localCost[i] * tempBetterCost + cost[i] * betterCost[i];
        }

        printf("localcost\n");
        for (int i = 0; i < popsize; i++) {
            printf("%f  ", localCost[i]);
            printf("\n");

        }
        printf("\n");


        for (int i = 0; i < popsize; i++) {
            if (betterCost[i] == 1) {
                for (int j = 0; j < npar; j++) {
                    localpar[i][j] = par[i][j];
                }
            }
        }


        double temp = localCost[0];
        int index2 = 0;

        for (int i = 0; i < popsize; i++) {
            if (localCost[i] < temp) {
                index2 = i;
                temp = localCost[i];
            }
        }


        printf("localpar\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", localpar[i][j]);
            }
            printf("\n");

        }
        printf("\n");


        int tIndex = 0;
        double tempMinGlobalCost = localCost[0];

        for (int i = 0; i < popsize; i++) {
            if (localCost[i] < tempMinGlobalCost) {
                tIndex = i;
                tempMinGlobalCost = localCost[i];
            }
        }


        printf("\n minlocalcost: %f", tempMinGlobalCost);
        printf("\nmin index %d", tIndex);

        printf("\n globalCost: %f", globalCost);

        for (int i = 0; i < npar; i++) {
            printf("\n globapar : %f", globalpar[i]);
        }

        if (tempMinGlobalCost < globalCost) {

            index = tIndex;

            for (int i = 0; i < npar; i++) {
                globalpar[i] = par[index][i];
            }


            globalCost = tempMinGlobalCost;

        }

        printf("\nnew  index %d", tIndex);

        printf("\n newglobalCost: %f", globalCost);

        printf("\npar\n");
        for (int i = 0; i < popsize; i++) {
            for (int j = 0; j < npar; j++) {
                printf("%f  ", par[i][j]);
            }
            printf("\n");

        }
        printf("\n");

        for (int i = 0; i < npar; i++) {
            printf("\n new globapar : %f", globalpar[i]);
        }



    mincIter[0] = min;
    globalIter[0] = globalCost;
    meancIter[0] = mean ;

    }
    
    return 0;
}

double randfrom()
{
    double div = RAND_MAX / 1;
    return  rand() / div;
}


