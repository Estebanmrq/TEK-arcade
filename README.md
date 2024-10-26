# Arcade - A Retro Plateform 🕹️

## Table of Contents 📍

1. [Overview 💡](#overview-💡)
2. [Key Features 🔑](#key-features-🔑)
3. [Current Libraries & Games 🎲](#current-libraries--games-🎲)
4. [Usage Instructions 🕹️](#usage-instructions-🕹️)
5. [Compilation & Build ⚙️](#compilation--build-⚙️)
6. [Contributors 🤝](#contributors-🤝)


## Overview 💡

**Arcade** is a retro-inspired gaming platform designed to deliver a dynamic, extensible, and nostalgic gaming experience. It's not just a game but a platform that allows users to choose and play multiple retro-style games while switching between different graphic libraries. Designed in `C++`, it offers a modular architecture through dynamic libraries that are loaded at runtime, ensuring flexibility and customizability for both games and graphics.

Whether you're a fan of classic games like Pacman, Snake, or Nibbler, **Arcade** is the perfect platform to relive those retro memories, all while enjoying the freedom to choose your preferred graphical interface—be it `nCurses`, `SDL2`, `SFML`, or `Allegro`.

---

## Key Features 🔑
- **Dynamic Library Integration**: Games and graphic libraries are loaded dynamically, offering flexibility and a plug-and-play experience.
- **Multiple Graphics Libraries**: Switch between various graphical interfaces on-the-fly, such as `Allegro`, `nCurses`, `SDL2`, and `SFML`.
- **Game Variety**: Enjoy different classic arcade games like `Pacman`, `Snake`, and `Nibbler`.
- **High Scores**: Track your progress with an integrated scoring system.
- **Cross-Library Compatibility**: Both games and graphics libraries are treated uniformly, ensuring seamless interaction between different components.


## Current Libraries & Games 🎲

### Graphics Libraries

The following graphic libraries have already been developed:

- `nCurses`: A classic text-based interface for a minimal, retro aesthetic.
- `SDL2`: A powerful 2D engine for modern rendering.
- `SFML`: Simple and Fast Multimedia Library for smooth, high-quality graphics.
- `Allegro`: A versatile multimedia library, ideal for gaming, supporting multiple platforms.

However, the arcade expects to load the following libraries by default (whether developed or not), and will only display valid ones:

nCurses: arcade_ncurses.so
- `SDL2`: `arcade_sdl2.so`
- `NDK++`: `arcade_ndk++.so`
- `aa-lib`: `arcade_aalib.so`
- `libcaca`: `arcade_libcaca.so`
- `Allegro5`: `arcade_allegro5.so`
- `Xlib`: `arcade_xlib.so`
- `GTK+`: `arcade_gtk+.so`
- `SFML`: `arcade_sfml.so`
- `Irrlicht`: `arcade_irrlicht.so`
- `OpenGL`: `arcade_opengl.so`
- `Vulkan`: `arcade_vulkan.so`
- `Qt5`: `arcade_qt5.so`


### Game Libraries

The following game libraries have already been developed:

- `Pacman`: Navigate through mazes, eat pac-dots, and avoid ghosts!
- `Snake`: Feed your snake and grow as long as possible without hitting yourself.
- `Nibbler`: A more complex version of Snake with maze obstacles and a time limit.

However, the arcade expects to load the following libraries by default (whether developed or not), and will only display valid ones:

- `Snake`: `arcade_snake.so`
- `Nibbler`: `arcade_nibbler.so`
- `Pacman`: `arcade_pacman.so`
- `Qix`: `arcade_qix.so`
- `Centipede`: `arcade_centipede.so`
- `Solarfox`: `arcade_solarfox.so`

## Usage Instructions 🕹️

To launch **Arcade**, you need to specify the initial graphic library you'd like to use:

```bash
./arcade ./lib/arcade_ncurses.so
```

Une fois le programme lancé, la plateforme affichera :

1. Les jeux disponibles dans le répertoire `./lib/`.
2. Les bibliothèques graphiques disponibles.
3. Les scores actuels.
4. Une invite pour entrer votre nom pour le tableau des scores.

### Contrôles

- **Prochaine bibliothèque graphique** : Changez d'interface graphique.
- **Prochain jeu** : Chargez le prochain jeu disponible.
- **Redémarrer** : Redémarrez le jeu actuel.
- **Menu** : Retournez au menu principal.
- **Quitter** : Fermez la plateforme.

Assurez-vous que vos bibliothèques dynamiques sont bien stockées dans le répertoire `./lib/`, car elles seront chargées à l'exécution.

## Compilation & Build ⚙️

### Utilisation du Makefile

**ARCADE** peut être compilé en utilisant un Makefile standard avec plusieurs cibles de compilation :

- `make` : Compile le programme principal ainsi que les bibliothèques de jeux et graphiques.
- `make core` : Compile uniquement la plateforme **ARCADE**.
- `make games` : Compile toutes les bibliothèques de jeux.
- `make graphicals` : Compile toutes les bibliothèques graphiques.
- `make clean` : Supprime les fichiers objets.
- `make fclean` : Supprime les fichiers objets et binaires.

## Contributors 👥

- **Main Contributor**: [MARQUES Esteban](https://github.com/Estebanmrq/), [PRIEZ Clement](https://github.com/Warred14/), [RAVALISON Loic](https://github.com/loicrava)
