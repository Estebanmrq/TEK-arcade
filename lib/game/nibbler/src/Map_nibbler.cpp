/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** nibbler map
*/

#include <fstream>
#include <sstream>
#include "Map_nibbler.hpp"
#include "IGame.hpp"

bool Map::validMap() const
{
    size_t sizeLine;

    if (this->_map.empty()) {
        return false;
    }
    sizeLine = this->_map[0].size();
    for (auto &line : this->_map) {
        if (line.size() != sizeLine) {
            return false;
        }
        for (auto &item : line) {
            if (item != '#' && item != ' ' && item != 'o' && item != '>') {
                return false;
            }
        }
    }
    return true;
}

Map::Map(const std::string &mapPath)
{
    std::ifstream fd(mapPath);
    std::string buffer;

    if (!fd.is_open()) {
        throw IGame::Error("Can't open the map file");
    }
    while (std::getline(fd, buffer)) {
        this->_map.push_back(buffer);
    }
    fd.close();
    if (!validMap()) {
        throw IGame::Error("Invalid map elements");
    }
    parseMap();
}

Map::~Map()
{
}

void Map::parseMap()
{
    std::string identifer;

    for (size_t y = 0; y < this->_map.size(); y++) {
        std::vector<items> line;
        for (size_t x = 0; x < this->_map[y].size(); x++) {
            switch (this->_map[y][x]) {
                case ' ':
                    line.push_back(_EMPTY_);
                    break;
                case 'o':
                    line.push_back(_APPLE_);
                    break;
                case '#':
                    line.push_back(_WALL_);
                    break;
            }
        }
        _mapItems.push_back(line);
    }
}
