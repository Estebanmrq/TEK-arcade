/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Map
*/

#include <fstream>
#include <sstream>
#include "Map.hpp"
#include "IGame.hpp"

bool Map::validMap() const
{
    size_t sizeLine;

    if (this->_map.empty())
        return false;
    sizeLine = this->_map[0].size();
    for (auto &line : this->_map) {
        if (line.size() != sizeLine)
            return false;
        for (auto &item : line) {
            if (item != '#' && item != ' ' && item != 'o' && item != '.' && item != '_')
                return false;
        }
    }
    return true;
}

Map::Map(const std::string &mapPath) : _clock(0.1)
{
    std::ifstream fd(mapPath);
    std::string buffer;

    if (!fd.is_open())
        throw IGame::Error("Can't open the map file");
    while (std::getline(fd, buffer)) {
        this->_map.push_back(buffer);
    }
    fd.close();
    if (!validMap())
        throw IGame::Error("Invalid map elements");
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
                    line.push_back(_SUPER_PACGUM_);
                    break;
                case '.':
                    line.push_back(_PACGUM_);
                    break;
                case '_':
                    line.push_back(_DOOR_);
                    break;
                default:
                    identifer.clear();
                    identifer.push_back(y == 0 ? ' ' : this->_map[y - 1][x]);
                    identifer.push_back(this->_map[y][x]);
                    identifer.push_back(y == this->_map.size() - 1 ? ' ' : this->_map[y + 1][x]);
                    identifer.push_back(x == 0 ? ' ' : this->_map[y][x - 1]);
                    identifer.push_back(x == this->_map[y].size() - 1 ? ' ' : this->_map[y][x + 1]);

                    for (auto &c : identifer) {
                        if (c == '_' ) {
                            c = '#';
                            continue;
                        }
                        c = c == '#' ? '#' : ' ';
                    }
                    if (WALLTYPES.find(identifer) == WALLTYPES.end()) {
                        throw IGame::Error("Invalid wall type");
                    }
                    line.push_back(this->WALLTYPES.at(identifer));
                    break;
            }
        }
        _mapItems.push_back(line);
    }
}
