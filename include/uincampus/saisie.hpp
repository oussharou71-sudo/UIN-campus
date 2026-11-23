#pragma once

#include <string>
#include <string_view>

namespace uin {

[[nodiscard]] std::string lireTexte(std::string_view invite);
[[nodiscard]] int lireEntier(std::string_view invite, int min, int max);
[[nodiscard]] double lireNote(std::string_view invite);

} // namespace uin
