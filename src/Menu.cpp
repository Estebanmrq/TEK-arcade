/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Menu
*/

#include "Arcade.hpp"


void Arcade::menu()
{
    auto e = Event::UNKNOWN;
    size_t selected = 0;

    const std::string SELECT_G = "Select a game to start playing.";
    const std::string PRESS_E = "Press ENTER to select a game.";

    while (_arcadeRunning) {
        this->_gui->clearWindow();
        this->_texts.clear();
        this->_assets.clear();

        //
        // Display handling
        //
        this->_texts.push_back(Text("Welcome " + this->_username + " to the arcade.", Coordinate(WSX / 2 - ((23 + this->_username.size()) * RESX) / 2, 2 * RESY)));
        this->_texts.push_back(Text(SELECT_G, Coordinate(WSX / 2 - (SELECT_G.size() * RESX) / 2 , 4 * RESY)));
        this->_texts.push_back(Text(PRESS_E, Coordinate(WSX - ((PRESS_E.size() + 2) * RESX), WSY - (2 * RESY))));
        this->setCommand({Event::F5, Event::F6});

        for (size_t i = 0; i < this->_gameLoader.size(); i++)
            this->_texts.push_back(Text("[" + getName(this->_gameLoader[i]->getPath()) + "]", Coordinate(WSX / 2 - (16 * RESX), (7 + i) * RESY), i == selected));
        for (size_t i = 0; i < this->_guiLoader.size(); i++)
            this->_texts.push_back(Text("[" + getName(this->_guiLoader[i]->getPath()) + "]", Coordinate(WSX / 2 + (8 * RESX), (7 + i) * RESY), getName(this->_guiLoader[i]->getPath()) == getName(this->_libpath)));

        this->setEnlarge();

        this->_gui->displayAssets(this->_texts, {});

        //
        // Events handling
        //
        e = this->_gui->getEvent();
        if (e == Event::types::ENTER && this->_gameLoader.size() > 0) { game(this->_gameLoader[selected]->getPath()); }
        
        selected -= (e == Event::types::UP && selected != 0) ? 1 : 0;
        selected += (e == Event::types::DOWN && selected != this->_gameLoader.size() - 1) ? 1 : 0;

        if (CMD.find(e) != CMD.end()) { CMD.at(e)(); }
    }
}
