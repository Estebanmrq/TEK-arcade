/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** NCurses
*/

#include <memory>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include "NCurses.hpp"

NCurses::NCurses()
{
    if (Encapsulation::InitWindow() == nullptr)
        throw IDisplay::Error("Error: nCurses: can't load the window.");
    if (Encapsulation::InitKeyPad(stdscr, TRUE) == ERR) {
        Encapsulation::CloseWindow();
        throw IDisplay::Error("Error: nCurses: impossible to configure keypad.");
    }
    if (Encapsulation::DisableEcho() == ERR) {
        Encapsulation::CloseWindow();
        throw IDisplay::Error("Error: nCurses: impossible to configure noecho.");
    }
    if (Encapsulation::SetCursorVisibility(0) == ERR) {
        Encapsulation::CloseWindow();
        throw IDisplay::Error("Error: nCurses: impossible to configure cur_set.");
    }
    Encapsulation::SetNoDelay(stdscr, TRUE);
}

NCurses::~NCurses()
{
    clearWindow();
    Encapsulation::Refresh();
    Encapsulation::CloseWindow();
}

Coordinate NCurses::getResolution() const
{
    return Coordinate(RESOLUTION_X, RESOLUTION_Y);
}

void NCurses::clearWindow()
{
    Encapsulation::ClearWindow();
}

void NCurses::displayText(std::vector<Text> texts)
{
    for (auto text : texts) {
        if (text.getIsSelected())
            Encapsulation::SetUnderline();
        else
            Encapsulation::UnsetUnderline();
        Encapsulation::DisplayText(text.getCoord().getY(), text.getCoord().getX(), text.getText());
    }
}

Coordinate NCurses::getSizeWindow() const
{
    return Coordinate(COLS, LINES);
}

void NCurses::displaySprite(std::vector<Asset> assets)
{
    std::string disp;

    for (auto asset : assets) {
        disp.clear();
        disp.push_back(asset.getFormat().getChar());
        Encapsulation::DisplayText(asset.getPosition().getY(), asset.getPosition().getX(), disp);
    }
}

void NCurses::displayAssets(std::vector<Text> texts, std::vector<Asset> assets)
{
    displayText(texts);
    displaySprite(assets);
    Encapsulation::Refresh();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

Event::types NCurses::getEvent() const
{
    switch (Encapsulation::GetChar()) {
        case KEY_UP:
            return Event::types::UP;
        case KEY_DOWN:
            return Event::types::DOWN;
        case KEY_LEFT:
            return Event::types::LEFT;
        case KEY_RIGHT:
            return Event::types::RIGHT;
        case '\n':
            return Event::types::ENTER;
        case 27:
            return Event::types::ESCAPE;
        case ' ':
            return Event::types::SPACE;
        case KEY_BACKSPACE:
            return Event::types::BACKSPACE;
        case 'a':
            return Event::types::A;
        case 'b':    
            return Event::types::B;
        case 'c':
            return Event::types::C;
        case 'd':
            return Event::types::D;
        case 'e':
            return Event::types::E;
        case 'f':
            return Event::types::F;
        case 'g':
            return Event::types::G;
        case 'h':
            return Event::types::H;
        case 'i':
            return Event::types::I;
        case 'j':
            return Event::types::J;
        case 'k':
            return Event::types::K;
        case 'l':
            return Event::types::L;
        case 'm':
            return Event::types::M;
        case 'n':
            return Event::types::N;
        case 'o':
            return Event::types::O;
        case 'p':
            return Event::types::P;
        case 'q':
            return Event::types::Q;
        case 'r':
            return Event::types::R;
        case 's':
            return Event::types::S;
        case 't':
            return Event::types::T;
        case 'u':
            return Event::types::U;
        case 'v':
            return Event::types::V;
        case 'w':
            return Event::types::W;
        case 'x':
            return Event::types::X;
        case 'y':
            return Event::types::Y;
        case 'z':
            return Event::types::Z;
        case KEY_F(2):
            return Event::types::F2;
        case KEY_F(3):
            return Event::types::F3;
        case KEY_F(4):
            return Event::types::F4;
        case KEY_F(5):
            return Event::types::F5;
        case KEY_F(6):
            return Event::types::F6;
        default:
            return Event::types::UNKNOWN;
    }
}

extern "C" std::unique_ptr<IDisplay> getInstance()
{
    return std::make_unique<NCurses>();
}
