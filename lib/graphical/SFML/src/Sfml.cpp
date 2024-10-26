/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** SFML class implementation
*/

#include <memory>
#include <SFML/Graphics.h>
#include <iostream>
#include "Sfml.hpp"

Sfml::Sfml()
{
    window.create(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Arcade");
    view = window.getDefaultView();
}

Sfml::~Sfml()
{
    window.close();
}

Coordinate Sfml::getResolution() const
{
    return Coordinate(RESOLUTION_X, RESOLUTION_Y);
}

void Sfml::clearWindow()
{
    window.clear();
}

void Sfml::displayText(std::vector<Text> texts)
{
    sf::Font font;

    if (!font.loadFromFile("assets/graphical/ARCADE_R.TTF")) {
        std::cerr << "Error: SFML: Unable to load the font from file 'lib/graphical/SFML/assets/ARCADE_R_TTF.TTF'." << std::endl;
        return;
    }

    for (auto text : texts) {
        sf::Text sfText;
        if (text.getIsSelected())
            sfText.setFillColor(sf::Color::Blue);
        else
            sfText.setFillColor(sf::Color::White);
        sfText.setString(text.getText());
        sfText.setFont(font);
        sfText.setPosition(text.getCoord().getX(), text.getCoord().getY());
        sfText.setCharacterSize(12);
        window.draw(sfText);
    }
}

Coordinate Sfml::getSizeWindow() const
{
    return Coordinate(window.getSize().x, window.getSize().y);
}

void Sfml::displaySprite(std::vector<Asset> assets)
{
    sf::Sprite sprite;
    sf::Texture texture;

    for (auto asset : assets) {
        if (!texture.loadFromFile(asset.getFormat().getFile())) {
            std::cerr << "Error: SFML: Unable to load the texture from file '" << asset.getFormat().getFile() << "'." << std::endl;
            return;
        }
        sprite.setTexture(texture);
        sprite.setPosition(asset.getPosition().getX(), asset.getPosition().getY());
        sprite.setScale(asset.getSize().getX() / RESOLUTION_X, asset.getSize().getY() / RESOLUTION_Y);
        window.draw(sprite);
    }
}

void Sfml::displayAssets(std::vector<Text> texts, std::vector<Asset> assets)
{
    displayText(texts);
    displaySprite(assets);
    window.display();
}

Event::types Sfml::getEvent() const
{
    sf::Event event;
    sf::Window& wevent = (sf::Window&)window;

    if (wevent.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return Event::types::QUIT;
        if (event.type == sf::Event::Resized) {
            const_cast<sf::View&>(view).setSize({static_cast<float>(event.size.width), static_cast<float>(event.size.height)});
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Key::Up:
                    return Event::types::UP;
                case sf::Keyboard::Key::Down:
                    return Event::types::DOWN;
                case sf::Keyboard::Key::Left:
                    return Event::types::LEFT;
                case sf::Keyboard::Key::Right:
                    return Event::types::RIGHT;
                case sf::Keyboard::Key::Enter:
                    return Event::types::ENTER;
                case sf::Keyboard::Key::Escape:
                    return Event::types::ESCAPE;
                case sf::Keyboard::Key::Space:
                    return Event::types::SPACE;
                case sf::Keyboard::Key::Backspace:
                    return Event::types::BACKSPACE;
                case sf::Keyboard::Key::A:
                    return Event::types::A;
                case sf::Keyboard::Key::B:
                    return Event::types::B;
                case sf::Keyboard::Key::C:
                    return Event::types::C;
                case sf::Keyboard::Key::D:
                    return Event::types::D;
                case sf::Keyboard::Key::E:
                    return Event::types::E;
                case sf::Keyboard::Key::F:
                    return Event::types::F;
                case sf::Keyboard::Key::G:
                    return Event::types::G;
                case sf::Keyboard::Key::H:
                    return Event::types::H;
                case sf::Keyboard::Key::I:
                    return Event::types::I;
                case sf::Keyboard::Key::J:
                    return Event::types::J;
                case sf::Keyboard::Key::K:
                    return Event::types::K;
                case sf::Keyboard::Key::L:
                    return Event::types::L;
                case sf::Keyboard::Key::M:
                    return Event::types::M;
                case sf::Keyboard::Key::N:
                    return Event::types::N;
                case sf::Keyboard::Key::O:
                    return Event::types::O;
                case sf::Keyboard::Key::P:
                    return Event::types::P;
                case sf::Keyboard::Key::Q:
                    return Event::types::Q;
                case sf::Keyboard::Key::R:
                    return Event::types::R;
                case sf::Keyboard::Key::S:
                    return Event::types::S;
                case sf::Keyboard::Key::T:
                    return Event::types::T;
                case sf::Keyboard::Key::U:
                    return Event::types::U;
                case sf::Keyboard::Key::V:
                    return Event::types::V;
                case sf::Keyboard::Key::W:
                    return Event::types::W;
                case sf::Keyboard::Key::X:
                    return Event::types::X;
                case sf::Keyboard::Key::Y:
                    return Event::types::Y;
                case sf::Keyboard::Key::Z:
                    return Event::types::Z;
                case sf::Keyboard::Key::F2:
                    return Event::types::F2;
                case sf::Keyboard::Key::F3:
                    return Event::types::F3;
                case sf::Keyboard::Key::F4:
                    return Event::types::F4;
                case sf::Keyboard::Key::F5:
                    return Event::types::F5;
                case sf::Keyboard::Key::F6:
                    return Event::types::F6;
                default:
                    return Event::types::UNKNOWN;
            }
        }
    }
    return Event::types::UNKNOWN;
}

extern "C" std::unique_ptr<IDisplay> getInstance()
{
    return std::make_unique<Sfml>();
}
