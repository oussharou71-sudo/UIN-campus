#pragma once

#include <cstdint>
#include <string_view>

namespace uin {

inline constexpr double noteMin{0.0};
inline constexpr double noteMax{20.0};
inline constexpr double seuilValidation{10.0};

enum class Mention : std::uint8_t { Ajourne, Passable, AssezBien, Bien, TresBien };

constexpr bool estNoteValide(double note)
{
    return note >= noteMin && note <= noteMax;
}

[[nodiscard]] Mention mentionPour(double moyenne);
[[nodiscard]] std::string_view libelle(Mention mention);

} // namespace uin
