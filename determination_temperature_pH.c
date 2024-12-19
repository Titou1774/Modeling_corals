#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846     // definition of PI approched because my VS-code don't reconise M_PI from <math.h>


#define T_crit_w 32.5                   // critical temperature for wrasses in the Gili Islands
#define T_crit_a 32                     // critical temperature for anemones in the Gili Islands
#define T_crit_acropora 30              // critical temperature for acropora corals in the Gilis Islands
#define T_crit_porites 31               // critical temperature for porites corals in the Gilis Islands
#define T_crit_other_c 31.5             // critical temperature for other, less temperature-sensitive coral types in the Gilis Islands
#define T_crit_s 31.5                   // critical temperature for starfishs in the Gili Islands

#define pH_crit_w 7.8                   // critical pH for wrasses 
#define pH_crit_a 7.85                  // critical pH for anemones
#define pH_crit_acropora 7.9            // critical pH for acropora corals
#define pH_crit_porites 7.8             // critical pH for porites corals
#define pH_crit_other_c 7.85            // critical pH for others types of corals
#define pH_crit_s 7.8                   // critical pH for starfishs



void calcule_regression_lineaire(double *temperatures, double *times, int n, double *coefficients) {
    
    double sum_t = 0, sum_T = 0, sum_tT = 0, sum_t2 = 0 ;
    
    for (int i = 0 ; i < n ; i++) {
        sum_t += times[i] ;
        sum_T += temperatures[i] ;
        sum_tT += times[i] * temperatures[i] ;
        sum_t2 += times[i] * times[i] ;
    }
    
    double a = (n * sum_tT - sum_t * sum_T) / (n * sum_t2 - sum_t * sum_t) ;
    double b = (sum_T - a * sum_t) / n ;
    
    coefficients[0] = a ;   // directing coefficients
    coefficients[1] = b;    // Y-intercepted at origin
}


double temperature(double t, double a, double b, double facteur_climatique) {
    double baseline_temp = a * t + b ;
    double seasonal_variation = 0.5 * sin(2 * M_PI * t / 12) ;                // Annual variations
    double climate_trend = facteur_climatique * t ;                           // Increase due to climate change
    return baseline_temp + seasonal_variation + climate_trend ;
}

// wrasses temperature sensitivity 

double facteur_temperature_w(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_w = 0.0 ;
    if ( T > T_crit_w) {
        gamma_w = fmin((T - T_crit_w)*0.1, 1.0) ;
        if (gamma_w > 1) {
            gamma_w = 1.0 ;
        }
        return gamma_w ;
    } else {
        return 0 ;
    }
}

// anemones temperature sensitivity 

double facteur_temperature_a(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_a = 0.0 ;
    if ( T > T_crit_a) {
        gamma_a = fmin((T - T_crit_a)*0.1,1.0) ;
        if (gamma_a > 1) {
            gamma_a = 1.0 ;
        }
        return gamma_a ;
    } else {
        return 0 ;
    }
}
double facteur_temperature_acropora(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_acropora = 0.0 ;
    if ( T > T_crit_acropora) {
        gamma_acropora = fmin((T - T_crit_acropora)*0.3, 1.0) ;         // Corals very sensitive to temperature, hence the 0.3
        if (gamma_acropora > 1) {
            gamma_acropora = 1.0 ;
        }
        return gamma_acropora ;
    } else {
        return 0 ;
    }
}
double facteur_temperature_porites(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_porites = 0.0 ;
    if ( T > T_crit_porites) {
        gamma_porites = fmin((T - T_crit_porites)*0.2, 1.0) ;                   // Corals sensitive to temperature, hence the 0.2
        if (gamma_porites > 1) {
            gamma_porites = 1.0 ;
        }
        return gamma_porites ;
    } else {
        return 0 ;
    }
}

double facteur_temperature_other_c(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_other_c = 0.0 ;
    if ( T > T_crit_other_c) {
        gamma_other_c = fmin((T - T_crit_other_c)*0.15, 1.0) ;                  // Corals less sensitive to temperature, hence the 0.15
        if (gamma_other_c > 1) {
            gamma_other_c = 1.0 ;
        }
        return gamma_other_c ;
    } else {
        return 0 ;
    }
}

// Starfishs temperature sensitivity 

double facteur_temperature_s(double t, double a, double b, double facteur_climatique) {
    double T = temperature(t, a, b, facteur_climatique) ;
    double gamma_s = 0.0 ;
    if ( T > T_crit_w) {
        gamma_s = fmin((T - T_crit_s)*0.1, 1.0) ;
        if (gamma_s > 1) {
            gamma_s = 1.0 ;
        }
        return gamma_s ;
    } else {
        return 0 ;
    }
}

// Now we do the same thing but applied to the pH sensitivity of differents species

double facteur_pH(double pH, double pH_critique, double sensibilité) {
    double gamma = 0.0;
    if (pH < pH_critique) { 
        gamma = fmin((pH_critique - pH) * sensibilité, 1.0);
        if (gamma > 1.0) {
            gamma = 1.0;
        }
        return gamma;
    } else {
        return 0.0;
    }
}

// wrasses pH sensitivity 

double facteur_pH_w(double pH) {
    return facteur_pH(pH, pH_crit_w, 0.1) ; 
}

// anemones pH sensitivity 

double facteur_pH_a(double pH) {
    return facteur_pH(pH, pH_crit_a, 0.1) ; 
}

double facteur_pH_acropora(double pH) {
    return facteur_pH(pH, pH_crit_acropora, 0.3) ;  // Corals very sensitive to pH, hence the 0.3
}

double facteur_pH_porites(double pH) {
    return facteur_pH(pH, pH_crit_porites, 0.2) ;         // Corals sensitive to pH, hence the 0.2
}

double facteur_pH_other_c(double pH) {
    return facteur_pH(pH, pH_crit_other_c, 0.1) ;         // Corals less sensitive to pH, hence the 0.1
}

// starfishs pH sensitivity 

double facteur_pH_s(double pH) {
    return facteur_pH(pH, pH_crit_s, 0.1) ;         
}



