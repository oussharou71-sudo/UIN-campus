#include "uincampus/calculs.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

namespace uin {

double somme(std::span<const double> valeurs)
{
    return std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
}

double moyenne(std::span<const double> notes)
{
    assert(!notes.empty() && "moyenne() : aucune note");
    return somme(notes) / static_cast<double>(notes.size());
}

double moyenne(std::span<const double> notes, std::span<const double> coefficients)
{
    assert(!notes.empty() && "moyenne() : aucune note");
    assert(notes.size() == coefficients.size() && "moyenne() : tailles différentes");

    const double sommeCoefficients = somme(coefficients);
    assert(sommeCoefficients > 0.0 && "moyenne() : somme des coefficients nulle");

    const double sommePonderee =
        std::inner_product(notes.begin(), notes.end(), coefficients.begin(), 0.0);
    return sommePonderee / sommeCoefficients;
}

Statistiques calculerStatistiques(std::span<const double> notes)
{
    assert(!notes.empty() && "calculerStatistiques() : aucune note");

    const auto [minimum, maximum] = std::ranges::minmax(notes);
    const double moy = moyenne(notes);
    const double sommeCarres =
        std::accumulate(notes.begin(), notes.end(), 0.0, [moy](double total, double note) {
            return total + (note - moy) * (note - moy);
        });

    return Statistiques{
        .minimum = minimum,
        .maximum = maximum,
        .moyenne = moy,
        .ecartType = std::sqrt(sommeCarres / static_cast<double>(notes.size())),
    };
}

int compterValidees(std::span<const double> notes, double seuil)
{
    return static_cast<int>(
        std::ranges::count_if(notes, [seuil](double note) { return note >= seuil; }));
}

// Les paramètres ont des rôles distincts : le nombre à arrondir puis le nombre de décimales.
double arrondir(double valeur, int decimales) // NOLINT(bugprone-easily-swappable-parameters)
{
    const double facteur = std::pow(10.0, decimales);
    return std::round(valeur * facteur) / facteur;
}

} // namespace uin
