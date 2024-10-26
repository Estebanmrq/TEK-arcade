/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** LaunchMenu
*/

#include "Arcade.hpp"

void Arcade::launcher()
{
    auto e = Event::UNKNOWN;
    bool isError = false;

    const std::string WELCOME = "Welcome to the arcade.";
    const std::string ENTER_USRN = "Please before to start, enter a username:";
    const std::string USER = "Username: ";
    const std::string USRER_ERR = "Username can't be empty.";

    while (_arcadeRunning) {
        this->_gui->clearWindow();
        this->_texts.clear();
        this->_assets.clear();

        //
        // Display handling
        //
        this->_texts.push_back(Text(WELCOME, Coordinate(WSX / 2 - (WELCOME.size() * RESX) / 2, 2 * RESY)));
        this->_texts.push_back(Text(ENTER_USRN, Coordinate(2 * RESX, 4 * RESY)));
        this->_texts.push_back(Text(USER + this->_username, Coordinate(2 * RESX, 5 * RESY)));
        this->setCommand({Event::F3, Event::F5, Event::F6});
        if (isError) { this->_texts.push_back(Text(USRER_ERR, Coordinate(2 * RESX, 6 * RESY))); }

        this->setEnlarge();
    
        this->_gui->displayAssets(this->_texts, {});

        //
        // Events handling
        //
        e = this->_gui->getEvent();
        if (e == Event::types::BACKSPACE && this->_username.size() > 0) {
            this->_username.pop_back();
            isError = false;
        }
        if (getUserInValue(e) != '\0') {
            isError = false;
            this->_username.push_back(getUserInValue(e));
        }

        if (e == Event::types::ENTER) {
            if (this->_username.size() > 0) {
                break;
            } else {
                isError = true;
            }
        }

        if (CMD.find(e) != CMD.end() && e != Event::types::F3 && e != Event::types::F5 && e != Event::types::F6) {
            CMD.at(e)();
        }
    }
}
