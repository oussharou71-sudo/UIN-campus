#include "uincampus/saisie.hpp"

#include "uincampus/regles.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace uin {
namespace {

bool lireLigne(std::string_view invite, std::string& ligne)
{
    std::cout << invite;
    return static_cast<bool>(std::getline(std::cin, ligne));
}

bool estEntierStrict(const std::string& texte, int& valeur)
{
    std::istringstream flux{texte};
    char reste{};
    return static_cast<bool>(flux >> valeur) && !(flux >> reste);
}

bool estReelStrict(std::string texte, double& valeur)
{
    for (char& caractere : texte) {
        if (caractere == ',') {
            caractere = '.';
        }
    }

    std::istringstream flux{texte};
    char reste{};
    return static_cast<bool>(flux >> valeur) && !(flux >> reste) && std::isfinite(valeur);
}

} // namespace

std::string lireTexte(std::string_view invite)
{
    std::string texte;
    lireLigne(invite, texte);
    return texte;
}

int lireEntier(std::string_view invite, int min, int max)
{
    std::string ligne;
    while (lireLigne(invite, ligne)) {
        int valeur{};
        if (!estEntierStrict(ligne, valeur)) {
            std::cout << "   Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "   La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
    return min;
}

double lireNote(std::string_view invite)
{
    std::string ligne;
    while (lireLigne(invite, ligne)) {
        double note{};
        if (!estReelStrict(ligne, note)) {
            std::cout << "   Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
        } else if (!estNoteValide(note)) {
            std::cout << "   La note doit être comprise entre " << noteMin << " et " << noteMax
                      << ".\n";
        } else {
            return note;
        }
    }
    return noteMin;
}

} // namespace uin
