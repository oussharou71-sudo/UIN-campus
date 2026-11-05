<<<<<<< HEAD
# UIN-campus
UIN campus
=======
# UIN-Campus

Système de gestion académique de l'UIN — squelette initial du projet du cours de C++.

## Outils utilisés

- g++ : 14.2.0
- clang++ : 18.1.3
- CMake : 3.28.3
- Ninja : 1.11.1
- GDB : 15.1
- Git : 2.43.0
- clang-format : 18.1.3
- clang-tidy : 18.1.3

## Construire et exécuter (Debug avec ASan/UBSan)

```sh
cmake --preset debug
cmake --build --preset debug
./build/debug/uin-campus
```

Pour faciliter la détection du projet par clangd :

```sh
ln -s build/debug/compile_commands.json .
```

## Qualité du code

```sh
clang-format -i include/uincampus/*.hpp src/*.cpp app/*.cpp
clang-tidy -p build/debug src/*.cpp app/*.cpp
```
>>>>>>> 59aef74 ( UIN-Campus)
