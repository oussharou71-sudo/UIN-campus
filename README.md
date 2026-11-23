# UIN-Campus

Projet C++23 du cours de programmation orientée objet. Il contient le fil rouge UIN-Campus et les TP 3 (statistiques), 4 (carnet de notes) et 5 (tableau dynamique).

## Prérequis

- CMake 3.25 ou plus récent
- Ninja
- Un compilateur C++23 compatible avec `<format>` et `<print>` (GCC 14+, Clang 18+)

## Construire

```sh
cmake --preset debug
cmake --build --preset debug
```

## Exécuter

```sh
./build/debug/uin-campus
./build/debug/uin-campus-statistiques
./build/debug/uin-campus-carnet
./build/debug/uin-campus-tp5
./build/debug/uin-campus --version
./build/debug/uin-campus --aide
```

La configuration `debug` active AddressSanitizer et UndefinedBehaviorSanitizer. Pour une compilation optimisée :

```sh
cmake --preset release
cmake --build --preset release
```

## Formatage et analyse

```sh
clang-format -i include/uincampus/*.hpp src/*.cpp app/*.cpp
clang-tidy -p build/debug src/*.cpp app/*.cpp
```
