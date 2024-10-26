/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Arcade
*/

#include <iostream>
#include "Arcade.hpp"
#include "DLLoader.hpp"

Arcade::Arcade(const std::string &graphicalLib) : _libpath(graphicalLib), _arcadeRunning(true), _sc(0)
{
    setAllDllAvailable();
    this->_gui = nullptr;
    for (size_t i = 0; i < this->_guiLoader.size(); ++i) {
        if (getName(this->_guiLoader[i]->getPath()) == getName(graphicalLib))
            this->_gui = this->_guiLoader[i]->getInstance("getInstance");
    }
    if (this->_guiLoader.size() == 0)
        throw Error("No graphical library available.");
    if (this->_gui == nullptr)
        throw Error("Graphical library not found.");
}

Arcade::~Arcade()
{
}

void Arcade::setAllDllAvailable()
{
    for (auto &game : GAME_L) {
        try {
            DLLoader<IGame> gameLoad(game);
            this->_gameLoader.push_back(std::make_unique<DLLoader<IGame>>(game));
        }
        catch(const DLLoader<IGame>::Error &e) {
            if (std::string(e.what()).find("No such file or directory") == std::string::npos)
                std::cerr << "Load error: " << game << " -> " << e.what() << std::endl;
            continue;
        } catch (const IGame::Error &e) {
            std::cerr << "Instance error: " << game << " -> " << e.what() << std::endl;
            continue;
        }
    }
    for (auto &lib : GUI_L) {
        try {
            this->_guiLoader.push_back(std::make_unique<DLLoader<IDisplay>>(lib));
        }
        catch(const DLLoader<IDisplay>::Error &e) {
            if (std::string(e.what()).find("No such file or directory") == std::string::npos)
                std::cerr << "Load error: " << lib << " -> " << e.what() << std::endl;
            continue;
        } catch (const IDisplay::Error &e) {
            std::cerr << "Instance error: " << lib << " -> " << e.what() << std::endl;
            continue;
        }
    }
}

void Arcade::run()
{
    try {
        this->launcher();
        this->menu();
    } catch (const Quit &e) {
        return;
    } catch (const IDisplay::Error &e) {
        throw Error(e.what());
    } catch (const IGame::Error &e) {
        throw Error(e.what());
    }
}

std::string Arcade::getName(const std::string &path)
{
    std::string name = path;

    name = name.substr(name.find_last_of("/") + 1);
    name = name.substr(name.find_last_of("_") + 1);
    name = name.substr(0, name.find_last_of("."));
    return name;
}


char Arcade::getUserInValue(Event::types event)
{
    switch (event) {
        case Event::types::A:
            return 'a';
        case Event::types::B:
            return 'b';
        case Event::types::C:
            return 'c';
        case Event::types::D:
            return 'd';
        case Event::types::E:
            return 'e';
        case Event::types::F:
            return 'f';
        case Event::types::G:
            return 'g';
        case Event::types::H:
            return 'h';
        case Event::types::I:
            return 'i';
        case Event::types::J:
            return 'j';
        case Event::types::K:
            return 'k';
        case Event::types::L:
            return 'l';
        case Event::types::M:
            return 'm';
        case Event::types::N:
            return 'n';
        case Event::types::O:
            return 'o';
        case Event::types::P:
            return 'p';
        case Event::types::Q:
            return 'q';
        case Event::types::R:
            return 'r';
        case Event::types::S:
            return 's';
        case Event::types::T:
            return 't';
        case Event::types::U:
            return 'u';
        case Event::types::V:
            return 'v';
        case Event::types::W:
            return 'w';
        case Event::types::X:
            return 'x';
        case Event::types::Y:
            return 'y';
        case Event::types::Z:
            return 'z';
        case Event::types::SPACE:
            return ' ';
        default:
            return '\0';
    }
}

void Arcade::setEnlarge()
{
    if (WSX < (MIN_WIDTH * RESX) || WSY < (MIN_HEIGHT * RESY)) {
        this->_texts.clear();
        this->_assets.clear();
        this->_texts.push_back(Text(ENLARGE, Coordinate(WSX / 2 - (ENLARGE.size() * RESX) / 2, WSY / 2)));
    }
}
