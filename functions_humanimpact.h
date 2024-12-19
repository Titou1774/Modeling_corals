#ifndef FUNCTIONS_HUMANIMPACT_H
#define FUNCTIONS_HUMANIMPACT_H


#include <stdbool.h> // Nécessaire pour le type bool

// Dimensions du champ d'eau
#define taillex 100
#define tailley 100

// Déclaration des constantes
extern double randomDomaine;

// Prototypes des fonctions

/**
 * Génère un nombre aléatoire dans la plage [0, max).
 * 
 * @param max La valeur maximale du nombre généré.
 * @return Un nombre aléatoire dans la plage [0, max).
 */
double randomNumber(double max);

/**
 * Vérifie si une valeur existe déjà dans un tableau donné.
 * 
 * @param valeurs Le tableau contenant les valeurs.
 * @param taille La taille du tableau.
 * @param valeur La valeur à vérifier.
 * @return true si la valeur existe dans le tableau, sinon false.
 */
bool valeurExiste(double *valeurs, int taille, double valeur);

/**
 * Trouve l'indice d'une valeur donnée dans un tableau.
 * 
 * @param tableau Le tableau contenant les valeurs.
 * @param taille La taille du tableau.
 * @param valeur La valeur à trouver.
 * @return L'indice de la valeur si elle est trouvée, sinon -1.
 */
int trouverIndice(double *tableau, int taille, double valeur);

/**
 * Collecte les valeurs uniques de pH et leurs données associées (santé des coraux).
 * 
 * @param ph Le tableau contenant les valeurs de pH.
 * @param sante Le tableau contenant les données associées de santé.
 * @param taille La taille des tableaux.
 * @param phUniques Un tableau pour stocker les valeurs uniques de pH.
 * @param santeAssociee Un tableau pour stocker les données associées à chaque pH unique.
 * @return Le nombre de valeurs uniques collectées.
 */
int collecterValeursUniquesEtSante(double *ph, double *sante, int taille, 
                                   double *phUniques, double *santeAssociee);

/**
 * Simule la pollution par des paquets de C02.
 * 
 * @param x La position x initiale.
 * @param y La position y initiale.
 * @param r Le rayon d'action.
 * @param c La concentration de CO2.
 * @param tableau Le tableau représentant le champ de pollution.
 */
void simulePollution(int x, int y, double r, double c, double *tableau);

/**
 * Applique une absorption (par exemple, par des plantes) sur la pollution.
 * 
 * @param tableau Le tableau représentant le champ de pollution.
 * @param x_taille La largeur du champ.
 * @param y_taille La hauteur du champ.
 * @param lambda Le taux d'absorption.
 * @param delta_t L'intervalle de temps de simulation.
 */
void absorption(double *tableau, int x_taille, int y_taille, double lambda, double delta_t);

#endif // FUNCTIONS_HUMANIMPACT_H

