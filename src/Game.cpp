/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Game
*/

#include "Arcade.hpp"

void Arcade::displayScore()
{
    if (_score._scores.find(getName(_gamepath)) == _score._scores.end())
        return;
    
    this->_texts.push_back(Text("Score table:", Coordinate(2 * RESX, 5 * RESY)));
    bool found = false;
    for (size_t i = 0; i < this->_score._scores[getName(_gamepath)].size() && i < 5; i++) {
        this->_texts.push_back(Text(
            std::to_string(i + 1) + ": " + this->_score._scores[getName(_gamepath)][i].getUsername() + " : " + std::to_string(this->_score._scores[getName(_gamepath)][i].getScore()),
            Coordinate(2 * RESX, (i + 6) * RESY), this->_score._scores[getName(_gamepath)][i].getUsername() == this->_username && _sc == this->_score._scores[getName(_gamepath)][i].getScore() && !found));
            found = _sc == this->_score._scores[getName(_gamepath)][i].getScore() ? true : found;
    }
}

void Arcade::game(const std::string &game)
{
    _sc = 0;
    this->_game = nullptr;
    this->_gamepath = game;
    for (size_t i = 0; i < this->_gameLoader.size(); ++i) {
        if (this->_gameLoader[i]->getPath() == game)
            this->_game = this->_gameLoader[i]->getInstance("getInstance");
    }
    if (this->_game == nullptr)
        throw Error("Game not found.");

    this->_isPlaying = true;

    const std::string gameTitle = "Game list:";
    const std::string libTitle = "Library list:";

    if (this->_score._scores.find(getName(this->_gamepath)) == this->_score._scores.end())
        this->_score._scores[getName(this->_gamepath)] = std::vector<User>();

    while (_arcadeRunning && this->_isPlaying) {
        this->_gui->clearWindow();
        this->_texts.clear();
        this->_assets.clear();
    
        //
        // Display handling
        //
        if ((size_t)this->_game->getScore() == 0 && _sc != 0) {
            _sc = 0;
        } else if ((size_t)this->_game->getScore() != _sc) {
            for (size_t i = 0; i < _score._scores[getName(this->_gamepath)].size(); i++) {
                if (_score._scores[getName(this->_gamepath)][i].getScore() == _sc && _score._scores[getName(this->_gamepath)][i].getUsername() == this->_username) {
                    _score._scores[getName(this->_gamepath)].erase(_score._scores[getName(this->_gamepath)].begin() + i);
                    break;
                }
            }
            _sc = this->_game->getScore();
            _score.setScore(getName(this->_gamepath), User(this->_username, _sc));
        }
        this->_assets = this->_game->getAssets(this->_gui->getSizeWindow(), this->_gui->getResolution());
        this->_texts.push_back(Text("Username: " + this->_username, Coordinate(2 * RESX, 2 * RESY)));
        this->_texts.push_back(Text("Score: " + std::to_string(_sc), Coordinate(2 * RESX, 3 * RESY)));
        this->setCommand();

        this->displayScore();
        size_t scale = 7;
        this->_texts.push_back(Text(gameTitle, Coordinate(WSX - (gameTitle.size() + 2) * RESX, 6 * RESY)));
        for (size_t i = 0; i < this->_gameLoader.size(); i++, scale++)
            this->_texts.push_back(Text("[" + getName(this->_gameLoader[i]->getPath()) + "]", Coordinate(WSX - ((4 + getName(this->_gameLoader[i]->getPath()).size()) * RESX), scale * RESY), getName(this->_gameLoader[i]->getPath()) == getName(this->_gamepath)));
        scale++;
        this->_texts.push_back(Text(libTitle, Coordinate(WSX - (libTitle.size() + 2) * RESX, scale * RESY)));
        scale++;
        for (size_t i = 0; i < this->_guiLoader.size(); i++, scale++)
            this->_texts.push_back(Text("[" + getName(this->_guiLoader[i]->getPath()) + "]", Coordinate(WSX - ((4 + getName(this->_guiLoader[i]->getPath()).size()) * RESX), scale * RESY), getName(this->_guiLoader[i]->getPath()) == getName(this->_libpath)));


        this->_gui->displayAssets(this->_texts, this->_assets);
        this->setEnlarge();

        //
        // Events handling
        //
        auto e = this->_gui->getEvent();
        this->_game->handleEvents(e);

        if (CMD.find(e) != CMD.end()) {
            CMD.at(e)();
        }
    }
    _score.setScore(getName(this->_gamepath), User(this->_username, _sc));
    _score.saveScore();
}
