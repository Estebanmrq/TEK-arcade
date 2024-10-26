/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Snake.cpp
*/

#include <memory>
#include <iostream>
#include "Snake.hpp"
#include "Random.hpp"

Snake::Snake() : _player(Coordinate(11, 11), Coordinate(10, 11), Coordinate(9, 11), Coordinate(9, 10)), _apple(Coordinate(0, 0)), _score(0)
{
    Random::initRandom();
    if (!_map.pointIsInMap(_player.getHead()))
        throw IGame::Error("Snake: player is out of map.");
    _apple = Coordinate(_map.getWidth() - 4, (_map.getHeight() - 1) / 2);
}

Snake::~Snake()
{
}

void Snake::restart()
{
    _score = 0;
    _player = Player(Coordinate(11, 11), Coordinate(10, 11), Coordinate(9, 11), Coordinate(9, 10));
    if (!_map.pointIsInMap(_player.getHead()))
        throw IGame::Error("Snake: player is out of map.");
    _player.getClock().setTick(3000);
    _player.setDirection(Player::Direction::RIGHT);
}

int Snake::getScore()
{
    return _score;
}

void Snake::handleEvents(Event::types events)
{
    if (_player.getClock().getTick() == 3000 && _player.getClock().isTick())
        _player.getClock().setTick(SPEED);

    if (_player.getClock().getTick() == 3000 && !_player.getClock().isTick())
        return;

    if (_player.onPlayer(_player.getHead(), false))
        restart();

    if (_player.getHead().getX() == _apple.getX() && _player.getHead().getY() == _apple.getY()) {
        _player.growSnake();
        _score += 50;
        _player.getClock().setTick(_player.getClock().getTick() - 0.5);
        if (playerWin())
            restart();
        while (_player.onPlayer(_apple))
            _apple = Coordinate(Random::getRandomInt(1, _map.getWidth() - 2), Random::getRandomInt(1, _map.getHeight() - 2));
    }

    switch (events) {
        case Event::types::UP:
            if (_player.getDirection() != Player::Direction::DOWN)
                _player.setNextDirection(Player::Direction::UP);
            break;
        case Event::types::DOWN:
            if (_player.getDirection() != Player::Direction::UP)
                _player.setNextDirection(Player::Direction::DOWN);
            break;
        case Event::types::LEFT:
            if (_player.getDirection() != Player::Direction::RIGHT)
                _player.setNextDirection(Player::Direction::LEFT);
            break;
        case Event::types::RIGHT:
            if (_player.getDirection() != Player::Direction::LEFT)
                _player.setNextDirection(Player::Direction::RIGHT);
            break;
        default:
            break;
    }

    if (_player.getClock().updateTick()) {
        switch (_player.getNextDirection()) {
            case Player::Direction::UP:
                _player.setDirection(Player::Direction::UP);
                _player.moveBody(Coordinate(_player.getHead().getX(), _player.getHead().getY() - 1));
                break;
            case Player::Direction::DOWN:
                _player.setDirection(Player::Direction::DOWN);
                _player.moveBody(Coordinate(_player.getHead().getX(), _player.getHead().getY() + 1));
                break;
            case Player::Direction::LEFT:
                _player.setDirection(Player::Direction::LEFT);
                _player.moveBody(Coordinate(_player.getHead().getX() - 1, _player.getHead().getY()));
                break;
            case Player::Direction::RIGHT:
                _player.setDirection(Player::Direction::RIGHT);
                _player.moveBody(Coordinate(_player.getHead().getX() + 1, _player.getHead().getY()));
                break;
        }
    }

    if (!_map.pointIsInMap(_player.getHead()))
        restart();
}

std::vector<Asset> Snake::getAssets(Coordinate windowSize, Coordinate resolution)
{
    std::vector<Asset> assets;

    size_t startX = (windowSize.getX() - (_map.getWidth()) * resolution.getY()) / 2;
    size_t startY = (windowSize.getY() - (_map.getHeight()) * resolution.getY()) / 2;

    for (size_t y = 0; y < _map.getHeight(); y++) {
        for (size_t x = 0; x < _map.getWidth(); x++) {
            assets.push_back(Asset(
                Format(_map.getMapItem(Coordinate(x, y)) == Map::Items::_WALL_ ? '#' : ' ', RGB(0, 0, 0), _map.getSprite(_map.getMapItem(Coordinate(x, y)))),
                Coordinate(startX + x * resolution.getY(), startY + y * resolution.getY()),
                Coordinate(resolution.getY(), resolution.getY())
            ));
        }
    }
    assets.push_back(Asset(Format('A', RGB(0, 0, 0), "assets/game/snake/food/apple.png"), Coordinate(startX + _apple.getX() * resolution.getY(), startY + _apple.getY() * resolution.getY()), Coordinate(resolution.getY(), resolution.getY())));
    auto sprite = _player.getSprite();
    for (size_t i = 0; i < _player._position.size(); i++) {
        assets.push_back(Asset(Format('o', RGB(0, 0, 0), sprite[i]), Coordinate(startX + _player._position[i].getX() * resolution.getY(), startY + _player._position[i].getY() * resolution.getY()), Coordinate(resolution.getY(), resolution.getY())));
    }
    return assets;
}


extern "C" std::unique_ptr<IGame> getInstance()
{
    return std::make_unique<Snake>();
}
