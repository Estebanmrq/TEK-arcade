/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** main
*/

#include <iostream>
#include "Arcade.hpp"

int main(int const ac, char const *const *av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade path_graphical_lib.so" << std::endl;
        return Arcade::ARCADE_EXIT_FAILURE;
    }
    try {
        Arcade arcade(av[1]);
        arcade.run();
    } catch (const Arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        return Arcade::ARCADE_EXIT_FAILURE;
    } catch (const DLLoader<IDisplay>::Error &e) {
        std::cerr << e.what() << std::endl;
        return Arcade::ARCADE_EXIT_FAILURE;
    } catch (const Arcade::Quit &e) {
        std::cout << e.what() << std::endl;
        return Arcade::ARCADE_EXIT_SUCCESS;
    }
    return Arcade::ARCADE_EXIT_SUCCESS;
}
