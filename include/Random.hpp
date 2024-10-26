/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Random
*/

#ifndef RANDOM_HPP_
    #define RANDOM_HPP_
    #include <cstdlib>
    #include <ctime>

class Random {
    public:
        static void initRandom() { srand(time(NULL)); };
        static int getRandomInt(int min, int max) { return rand() % (max - min + 1) + min; } ;
};

#endif /* !RANDOM_HPP_ */