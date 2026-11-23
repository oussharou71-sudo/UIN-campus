#include "uincampus/saisie.hpp"

#include <algorithm>
#include <cstdint>
#include <print>
#include <ranges>
#include <vector>

namespace carnet {

enum class Ordre : std::uint8_t { Croissant, Decroissant };

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes)
{
    const auto [minimum, maximum] = std::ranges::minmax(notes);
    double somme{0.0};
    int validees{0};
    for (double note : notes) {
        somme += note;
        if (note >= 10.0) {
            ++validees;
        }
    }
    return {minimum, maximum, somme / static_cast<double>(notes.size()), validees};
}

void appliquerBonus(std::vector<double>& notes, double bonus)
{
    std::ranges::for_each(notes,
                          [bonus](double& note) { note = std::clamp(note + bonus, 0.0, 20.0); });
}

void trier(std::vector<double>& notes, Ordre ordre)
{
    if (ordre == Ordre::Croissant) {
        std::ranges::sort(notes);
    } else {
        std::ranges::sort(notes, [](double gauche, double droite) { return gauche > droite; });
    }
}

void afficherNotes(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    for (std::size_t i{0}; i < notes.size(); ++i) {
        std::println("{:>3}. {:6.2f}", i + 1, notes[i]);
    }
}

void ajouter(std::vector<double>& notes)
{
    notes.push_back(uin::lireNote("Note à ajouter : "));
}

void modifier(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à modifier.");
        return;
    }
    afficherNotes(notes);
    const int rang = uin::lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes[static_cast<std::size_t>(rang - 1)] = uin::lireNote("Nouvelle valeur : ");
}

void supprimer(std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note à supprimer.");
        return;
    }
    afficherNotes(notes);
    const int rang = uin::lireEntier("Numéro de la note : ", 1, static_cast<int>(notes.size()));
    notes.erase(notes.begin() + (rang - 1));
}

void afficherStatistiques(const std::vector<double>& notes)
{
    if (notes.empty()) {
        std::println("Aucune note.");
        return;
    }
    const auto [minimum, maximum, moyenne, validees] = calculerStatistiques(notes);
    std::println("Min {:.2f} | Max {:.2f} | Moyenne {:.2f} | Validées {}/{}", minimum, maximum,
                 moyenne, validees, notes.size());
}

[[nodiscard]] int afficherMenu()
{
    std::println("\n=== Carnet de notes ===");
    std::println("1. Ajouter une note\n2. Afficher les notes\n3. Modifier une note");
    std::println("4. Supprimer une note\n5. Trier les notes\n6. Statistiques");
    std::println("7. Appliquer un bonus\n0. Quitter");
    return uin::lireEntier("Votre choix : ", 0, 7);
}

} // namespace carnet

int main()
{
    std::vector<double> notes;
    int choix{};
    while (true) {
        choix = carnet::afficherMenu();
        if (choix == 0) {
            break;
        }
        switch (choix) {
        case 1:
            carnet::ajouter(notes);
            break;
        case 2:
            carnet::afficherNotes(notes);
            break;
        case 3:
            carnet::modifier(notes);
            break;
        case 4:
            carnet::supprimer(notes);
            break;
        case 5: {
            const int sens = uin::lireEntier("1. Croissant     2. Décroissant : ", 1, 2);
            carnet::trier(notes, sens == 1 ? carnet::Ordre::Croissant : carnet::Ordre::Decroissant);
            break;
        }
        case 6:
            carnet::afficherStatistiques(notes);
            break;
        case 7:
            carnet::appliquerBonus(notes, uin::lireNote("Bonus : "));
            break;
        default:
            break;
        }
    }
}
