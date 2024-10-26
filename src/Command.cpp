/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Command
*/

#include <algorithm>
#include "Arcade.hpp"

void Arcade::cmdNextLib()
{
    if (this->_guiLoader.size() <= 1)
        return;
    for (size_t i = 0; i < this->_guiLoader.size(); i++) {
        if (getName(this->_libpath) == getName(this->_guiLoader[i]->getPath())) {
            this->_gui.reset();
            this->_libpath = i + 1 < this->_guiLoader.size() ? this->_guiLoader[i + 1]->getPath() : this->_guiLoader[0]->getPath();
            this->_gui = i + 1 < this->_guiLoader.size() ? this->_guiLoader[i + 1]->getInstance("getInstance") : this->_guiLoader[0]->getInstance("getInstance");
            break;
        }
    }
}

void Arcade::cmdNextGame()
{
    if (this->_gameLoader.size() <= 1)
        return;
    for (size_t i = 0; i < this->_gameLoader.size(); i++) {
        if (getName(this->_gamepath) == getName(this->_gameLoader[i]->getPath())) {
            _score.setScore(getName(this->_gamepath), User(this->_username, _sc));
            _sc = 0;
            this->_game.reset();
            this->_gamepath = i + 1 < this->_gameLoader.size() ? this->_gameLoader[i + 1]->getPath() : this->_gameLoader[0]->getPath();
            this->_game = i + 1 < this->_gameLoader.size() ? this->_gameLoader[i + 1]->getInstance("getInstance") : this->_gameLoader[0]->getInstance("getInstance");
            break;
        }
    }
}

void Arcade::cmdRestart()
{
    _sc = 0;
    this->_game->restart();
}

void Arcade::cmdQuit()
{
    _arcadeRunning = false;
    this->_gui.reset();
    this->_game.reset();
    for (auto &game : this->_gameLoader) {
        game.reset();
    }
    for (auto &gui : this->_guiLoader) {
        gui.reset();
    }
}

void Arcade::cmdMenu()
{
    _score.setScore(getName(this->_gamepath), User(this->_username, _sc));
    _sc = 0;
    this->_isPlaying = false;
}

void Arcade::setCommand(std::vector<Event::types> exclude)
{
    size_t place = 0;

    for (auto &[cmd, info] : CMD_TITLE) {
        if (std::find(exclude.begin(), exclude.end(), cmd) != exclude.end())
            continue;
        this->_texts.push_back(Text(info, Coordinate(2 * RESX, WSY - ((2 + place) * RESY))));
        place++;
    }
}
