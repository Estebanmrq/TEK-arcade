/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-esteban.marques
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <map>
    #include <string>
    #include <vector>
    #include "Coordinate.hpp"

class Map {
    public:
        Map(size_t width = 21, size_t height = 21) : _width(width), _height(height)
        {
            for (size_t y = 0; y < _height; y++) {
                std::vector<Items> ligne;
                for (size_t x = 0; x < _width; x++) {
                    if (x == 0 || x == _width - 1 || y == 0 || y == _height - 1)
                        ligne.push_back(_WALL_);
                    else if (y % 2 == 0)
                        ligne.push_back(x % 2 == 0 ? _LIGHT_GREEN_GRASS_ : _DARK_GREEN_GRASS_);
                    else
                        ligne.push_back(x % 2 == 0 ? _DARK_GREEN_GRASS_ : _LIGHT_GREEN_GRASS_);
                }
                _map.push_back(ligne);
            }
        }

        ~Map() = default;

        enum Items {
            _LIGHT_GREEN_GRASS_,
            _DARK_GREEN_GRASS_,
            _WALL_
        };

        Items getMapItem(Coordinate coord) const { return _map[coord.getY()][coord.getX()]; }
        std::string getSprite(Items item) const { return ITEMS_SPRITES.at(item); }
        size_t getWidth() const { return _width; }
        size_t getHeight() const { return _height; }

        bool pointIsInMap(Coordinate coord) const { return coord.getX() > 0 && coord.getX() < static_cast<int>(_width) - 1 && coord.getY() > 0 && coord.getY() < static_cast<int>(_height) - 1; }
    private:
        const std::map<Items, std::string> ITEMS_SPRITES = {
            {_LIGHT_GREEN_GRASS_, "assets/game/snake/map/ground2.png"},
            {_DARK_GREEN_GRASS_, "assets/game/snake/map/ground1.png"},
            {_WALL_, "assets/game/snake/map/wall.png"}
        };

        size_t _width;
        size_t _height;
        std::vector<std::vector<Items>> _map;
};

#endif /* !MAP_HPP_ */
