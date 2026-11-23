#pragma once

#include "uincampus/regles.hpp"

#include <vector>

namespace uin {

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
};

[[nodiscard]] double somme(const std::vector<double>& valeurs);

/// @pre notes n'est pas vide.
[[nodiscard]] double moyenne(const std::vector<double>& notes);

/// @pre notes n'est pas vide, les tailles correspondent et la somme des coefficients est positive.
[[nodiscard]] double moyenne(const std::vector<double>& notes,
                             const std::vector<double>& coefficients);

/// @pre notes n'est pas vide.
[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes);

[[nodiscard]] int compterValidees(const std::vector<double>& notes, double seuil = seuilValidation);

[[nodiscard]] double arrondir(double valeur, int decimales = 2);

} // namespace uin
