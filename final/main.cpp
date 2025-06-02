#include <iostream>
#include "ants.hpp"

int main() {
    Fourmiliere fourmiliere;

    // // Ajout des liaisons
    // fourmiliere.ajouterLiaison("S1", "S1");
    // fourmiliere.ajouterLiaison("S1", "S2");
    // fourmiliere.ajouterLiaison("S1", "S3");
    // fourmiliere.ajouterLiaison("S2", "S4");
    // fourmiliere.ajouterLiaison("S3", "S4");
    // fourmiliere.ajouterLiaison("S4", "S5");
    // fourmiliere.ajouterLiaison("S4", "S6");
    // fourmiliere.ajouterLiaison("S5", "Sd");
    // fourmiliere.ajouterLiaison("S6", "Sd");



    fourmiliere.ajouterLiaison("S1", "S2");
    fourmiliere.ajouterLiaison("S2", "S3");
    fourmiliere.ajouterLiaison("S3", "S4");
    fourmiliere.ajouterLiaison("S4", "Sd");
    fourmiliere.ajouterLiaison("Sv", "S1");
    fourmiliere.ajouterLiaison("S2", "S5");
    fourmiliere.ajouterLiaison("S5", "S4");
    fourmiliere.ajouterLiaison("S13", "Sd");
    fourmiliere.ajouterLiaison("S8", "S12");
    fourmiliere.ajouterLiaison("S12", "S13");
    fourmiliere.ajouterLiaison("S6", "S7");
    fourmiliere.ajouterLiaison("S7", "S9");
    fourmiliere.ajouterLiaison("S9", "S14");
    fourmiliere.ajouterLiaison("S14", "Sd");
    fourmiliere.ajouterLiaison("S7", "S10");
    fourmiliere.ajouterLiaison("S10", "S14");
    fourmiliere.ajouterLiaison("S1", "S6");
    fourmiliere.ajouterLiaison("S6", "S8");
    fourmiliere.ajouterLiaison("S8", "S11");
    fourmiliere.ajouterLiaison("S11", "S13");

    // Capacités
    // fourmiliere.definirCapaciteSalle("Sv", 10);
    // fourmiliere.definirCapaciteSalle("Sd", 10);
    // fourmiliere.definirCapaciteSalle("S1", 2);
    // fourmiliere.definirCapaciteSalle("S4", 2);



    fourmiliere.definirCapaciteSalle("S1", 8);
    fourmiliere.definirCapaciteSalle("S2", 4);
    fourmiliere.definirCapaciteSalle("S3", 2);
    fourmiliere.definirCapaciteSalle("S4", 4);
    fourmiliere.definirCapaciteSalle("S5", 2);
    fourmiliere.definirCapaciteSalle("S6", 4);
    fourmiliere.definirCapaciteSalle("S7", 2);
    fourmiliere.definirCapaciteSalle("S8", 5);
    fourmiliere.definirCapaciteSalle("S13", 4);
    fourmiliere.definirCapaciteSalle("S14", 2);

    int nombreFourmis = 50;

    fourmiliere.simulerFourmis("Sv", "Sd", nombreFourmis);

    return 0;
}
