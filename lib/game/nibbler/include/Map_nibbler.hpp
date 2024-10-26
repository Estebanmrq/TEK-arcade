/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Map
*/

#ifndef MAP_NIBBLER_HPP_
    #define MAP_NIBBLER_HPP
    #include <map>
    #include <vector>
    #include <string>
    #include "Coordinate.hpp"

class Map {
    public:
        Map() {};
        Map(const std::string &mapPath);
        ~Map();

        enum items {
            _EMPTY_,
            _APPLE_,
            _WALL_
        };

        void operator=(const Map &map) {
            _map = map._map;
            _mapItems = map._mapItems;
        }

        std::vector<std::string> _map;
        std::vector<std::vector<items>> _mapItems;
    private:
        bool validMap() const;
        void parseMap();
};

#endif /* !MAP_NIBBLER_HPP */
