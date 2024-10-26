/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_
    #include <map>
    #include <vector>
    #include <string>
    #include "Clock.hpp"

class Map {
    public:        
        Map() : _clock(0.1) {};
        Map(const std::string &mapPath);
        ~Map();

        void operator=(const Map &map) {
            _map = map._map;
            _mapItems = map._mapItems;
            _clock.setTick(map._clock.getTick());
        }

        enum items {
            _EMPTY_,
            _WALL_START_LEFT_,
            _WALL_START_RIGHT_,
            _WALL_START_BOTTOM_,
            _WALL_START_TOP_,
            _WALL_STRAIGHT_HORIZONTALE_,
            _WALL_STRAIGHT_VERTICALE_,
            _WALL_L_TOP_LEFT_,
            _WALL_L_TOP_RIGHT_,
            _WALL_L_BOTTOM_LEFT_,
            _WALL_L_BOTTOM_RIGHT_,
            _WALL_T_TOP_,
            _WALL_T_BOTTOM_,
            _WALL_T_LEFT_,
            _WALL_T_RIGHT_,
            _DOOR_,
            _PACGUM_,
            _SUPER_PACGUM_,
            _SUPER_PACGUM_MIN_
        };

        std::vector<std::string> _map;
        std::vector<std::vector<items>> _mapItems;
    private:
        Clock _clock;
        const std::map<std::string, items> WALLTYPES {
            {"###  ", _WALL_STRAIGHT_VERTICALE_},
            {" # ##", _WALL_STRAIGHT_HORIZONTALE_},
            {"##   ", _WALL_START_TOP_},
            {" ##  ", _WALL_START_BOTTOM_},
            {" # # ", _WALL_START_LEFT_},
            {" #  #", _WALL_START_RIGHT_},
            {"## # ", _WALL_L_TOP_LEFT_},
            {"##  #", _WALL_L_TOP_RIGHT_},
            {" ### ", _WALL_L_BOTTOM_LEFT_},
            {" ## #", _WALL_L_BOTTOM_RIGHT_},
            {"## ##", _WALL_T_TOP_},
            {" ####", _WALL_T_BOTTOM_},
            {"#### ", _WALL_T_LEFT_},
            {"### #", _WALL_T_RIGHT_},
        };

        bool validMap() const;
        void parseMap();
};

#endif /* !MAP_HPP_ */
