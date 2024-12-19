#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "functions_humanimpact.h"



#define taillex 100     // dimensions of water field
#define tailley 100

double randomDomaine = RAND_MAX + 1.0;

double randomNumber(double max) {
    return rand() / randomDomaine * max;
}

//All this part is to collect unique values of pH and health for our dataset
bool valeurExiste(double *valeurs, int taille, double valeur) {
    for (int i = 0; i < taille; i++) {
        if (fabs(valeurs[i] - valeur) < 1e-6) { 
            return true;
        }
    }
    return false;
}


// Fonction pour trouver l'indice d'une valeur dans un tableau
int trouverIndice(double *tableau, int taille, double valeur) {
    for (int i = 0; i < taille; i++) {
        if (fabs(tableau[i] - valeur) < 1e-6) { 
            return i;
        }
    }
    return -1; // Retourne -1 si la valeur n'est pas trouvée
}

// Function to collect unique values and datas associated
int collecterValeursUniquesEtSante(double *ph, double *sante, int taille, 
                                   double *phUniques, double *santeAssociee) {
    int compteur = 0;
    for (int i = 0; i < taille; i++) {
        int indice = trouverIndice(phUniques, compteur, ph[i]);
        if (indice == -1) { // If the ph is unique
            phUniques[compteur] = ph[i];
            santeAssociee[compteur] = sante[i];
            compteur++;
        }
    }
    return compteur; // Return the number of unique values
}


// Function to simulate packages of C02
void simulePollution(int x, int y, double r, double c, double * tableau) {
    for (int i = 0; i < 100; i++) {
        double ventX = 5;
        double ventY = 0.3*(x-2);

        double ax = (randomNumber(6) - 3);
        double ay = (randomNumber(6) - 3);

        r = r + 20 / r;

        x += ventX + ax;
        y += ventY + ay;

        if ((x < 0 || x >= taillex) || (y < 0 || y >= tailley)) {
            break;
        }
        if (c>275){
			c = 275;
		}

        // Propagation of C02 over space

        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < taillex && ny >= 0 && ny < tailley) {
                    double distance = sqrt(dx * dx + dy * dy);
                    if (distance <= r) {
                        tableau[ny * taillex + nx] += c * (1 - distance / r);  // Further we are, further the diffusion is important
                    }
                }
            }
        }

    }
}

//Function to absorbate some C02 (by plants for example)
void absorption(double *tableau, int x_taille, int y_taille, double lambda, double delta_t) {
    double decay_factor = exp(-lambda * delta_t);
    for (int i = 0; i < x_taille; i++) {
        for (int j = 0; j < y_taille; j++) {
            tableau[j * x_taille + i] *= decay_factor;
        }
    }
}

