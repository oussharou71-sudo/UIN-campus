#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <format>
#include <print>
#include <string>
#include <vector>

namespace {

constexpr std::size_t nbMentions{5};

} // namespace

int main()
{
    const std::string ue = uin::lireTexte("Nom de l'UE : ");
    const int nbEtudiants = uin::lireEntier("Nombre d'étudiants (1 à 200) : ", 1, 200);

    std::vector<double> notes;
    for (int i{1}; i <= nbEtudiants; ++i) {
        notes.push_back(uin::lireNote(std::format("Note de l'étudiant {} : ", i)));
    }

    double minimum{uin::noteMax};
    double maximum{uin::noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double note : notes) {
        minimum = std::min(minimum, note);
        maximum = std::max(maximum, note);
        somme += note;
        if (note >= uin::seuilValidation) {
            ++admis;
        }
        const auto indice = static_cast<std::size_t>(uin::mentionPour(note));
        ++repartition.at(indice);
    }

    const auto taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double note : notes) {
        const double ecart = note - moyenne;
        sommeEcarts += ecart * ecart;
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::println("\nStatistiques — {} ({} étudiants)", ue, nbEtudiants);
    std::println("{:‐<58}", "");
    std::println("{:<18}: {:6.2f}", "Note minimale", minimum);
    std::println("{:<18}: {:6.2f}", "Note maximale", maximum);
    std::println("{:<18}: {:6.2f}", "Moyenne", moyenne);
    std::println("{:<18}: {:6.2f}", "Écart-type", ecartType);
    std::println("{:<18}: {:6} ({:.1f} %)", "Admis", admis, 100.0 * admis / taille);

    std::println("\nRépartition par mention");
    for (std::size_t i{0}; i < nbMentions; ++i) {
        const auto mention = static_cast<uin::Mention>(i);
        const auto nombre = static_cast<std::size_t>(repartition.at(i));
        std::println("{:<12} {} ({})", uin::libelle(mention), std::string(nombre, '*'),
                     repartition.at(i));
    }
}
