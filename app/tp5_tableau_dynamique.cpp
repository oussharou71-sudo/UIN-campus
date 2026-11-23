#include <cassert>
#include <cstddef>
#include <print>
#include <vector>

struct TableauDynamique {
    double* donnees{nullptr};
    std::size_t taille{0};
    std::size_t capacite{0};
};

void ajouter(TableauDynamique& tableau, double valeur)
{
    if (tableau.taille == tableau.capacite) {
        const std::size_t nouvelleCapacite = tableau.capacite == 0 ? 4 : tableau.capacite * 2;
        double* nouveau = new double[nouvelleCapacite];
        for (std::size_t i{0}; i < tableau.taille; ++i) {
            nouveau[i] = tableau.donnees[i];
        }
        delete[] tableau.donnees;
        tableau.donnees = nouveau;
        tableau.capacite = nouvelleCapacite;
    }
    tableau.donnees[tableau.taille] = valeur;
    ++tableau.taille;
}

void liberer(TableauDynamique& tableau)
{
    delete[] tableau.donnees;
    tableau.donnees = nullptr;
    tableau.taille = 0;
    tableau.capacite = 0;
}

double& element(TableauDynamique& tableau, std::size_t indice)
{
    assert(indice < tableau.taille && "element() : indice hors limites");
    return tableau.donnees[indice];
}

int main()
{
    std::println("Tableau manuel (new[] / delete[])");
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + static_cast<double>(i));
        std::println("taille {:>2}, capacité {:>2}", notes.taille, notes.capacite);
    }
    element(notes, 0) = 19.5;
    std::println("première valeur après modification : {:.1f}", element(notes, 0));
    liberer(notes);

    std::println("\nMême évolution avec std::vector");
    std::vector<double> notesVecteur;
    for (int i{0}; i < 10; ++i) {
        notesVecteur.push_back(10.0 + static_cast<double>(i));
        std::println("taille {:>2}, capacité {:>2}", notesVecteur.size(), notesVecteur.capacity());
    }
    const std::vector<double> copie = notesVecteur;
    std::println("copie sûre : {} valeurs", copie.size());
}
