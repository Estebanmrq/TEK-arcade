/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Nibbler^
*/

#include <memory>
#include <iostream>
#include "Nibbler.hpp"

Nibbler::Nibbler() : _player(Coordinate(11, 17), Coordinate(10, 17), Coordinate(9, 17), Coordinate(8, 17)), _score(0), _niv(0)
{
    _map = Map(MAPS[_niv]);
    if (_map._mapItems.empty()) {
        throw IGame::Error("nibbler: map is empty");
    }
}

Nibbler::~Nibbler()
{
}

void Nibbler::restart()
{
    _map = Map(MAPS[_niv]);
    _player = Player(Coordinate(11, 17), Coordinate(10, 17), Coordinate(9, 17), Coordinate(8, 17));
    _player.getClock().setTick(3000);
    _player.setDirection(Player::Direction::RIGHT);
    if (_niv == 0) {
        _score = 0;
    }
}

int Nibbler::getScore()
{
    return _score;
}

Player::Direction Nibbler::getAvailableDirection()
{
    Player::Direction dir = _player.getNextDirection();
    size_t count = 0;

    if (_player.getNextDirection() != Player::RIGHT && _map._mapItems[_player.getHead().getY()][_player.getHead().getX() - 1] != Map::_WALL_) {
        dir = Player::Direction::LEFT;
        count += 1;
    }
    if (_player.getNextDirection() != Player::LEFT && _map._mapItems[_player.getHead().getY()][_player.getHead().getX() + 1] != Map::_WALL_) {
        dir = Player::Direction::RIGHT;
        count += 1;
    }
    if (_player.getNextDirection() != Player::DOWN && _map._mapItems[_player.getHead().getY() - 1][_player.getHead().getX()] != Map::_WALL_) {
        dir = Player::Direction::UP;
        count += 1;
    }
    if (_player.getNextDirection() != Player::UP && _map._mapItems[_player.getHead().getY() + 1][_player.getHead().getX()] != Map::_WALL_) {
        dir = Player::Direction::DOWN;
        count += 1;
    }
    return count == 1 ? dir : _player.getNextDirection();
}

void Nibbler::handleEvents(Event::types events)
{
    if (_player.getClock().getTick() == 3000 && _player.getClock().isTick()) {
        _player.getClock().setTick(SPEED);
    }

    if (_player.getClock().getTick() == 3000 && !_player.getClock().isTick()) {
        return;
    }

    if (_player.onPlayer(_player.getHead(), false)) {
        restart();
    }

    if (_map._mapItems[_player.getHead().getY()][_player.getHead().getX()] == Map::_APPLE_){
        _map._mapItems[_player.getHead().getY()][_player.getHead().getX()] = Map::_EMPTY_;
        _player.growSnake();
        _score += 10;
        _player.getClock().setTick(_player.getClock().getTick() - 0.5);
        if (userWin()) {
            _niv = _niv + 1 < MAPS->size() ? _niv + 1 : 0;
            restart();
        }
    }

    switch (events) {
        case Event::types::UP:
            if (_player.getDirection() != Player::Direction::DOWN && _map._mapItems[_player.getHead().getY() - 1][_player.getHead().getX()] != Map::_WALL_) {
                _player.setNextDirection(Player::Direction::UP);
            }
            break;
        case Event::types::DOWN:
            if (_player.getDirection() != Player::Direction::UP && _map._mapItems[_player.getHead().getY() + 1][_player.getHead().getX()] != Map::_WALL_) {
                _player.setNextDirection(Player::Direction::DOWN);
            }
            break;
        case Event::types::LEFT:
            if (_player.getDirection() != Player::Direction::RIGHT && _map._mapItems[_player.getHead().getY()][_player.getHead().getX() - 1] != Map::_WALL_) {
                _player.setNextDirection(Player::Direction::LEFT);
            }
            break;
        case Event::types::RIGHT:
            if (_player.getDirection() != Player::Direction::LEFT && _map._mapItems[_player.getHead().getY()][_player.getHead().getX() + 1] != Map::_WALL_) {
                _player.setNextDirection(Player::Direction::RIGHT);
            }
            break;
        default:
            break;
    }

    if (_player.getClock().updateTick()) {

        int newX = _player.getNextDirection() == Player::Direction::LEFT ? _player.getHead().getX() - 1 : _player.getNextDirection() == Player::Direction::RIGHT ? _player.getHead().getX() + 1 : _player.getHead().getX();
        int newY = _player.getNextDirection() == Player::Direction::UP ? _player.getHead().getY() - 1 : _player.getNextDirection() == Player::Direction::DOWN ? _player.getHead().getY() + 1 : _player.getHead().getY();
    
        if (_map._mapItems[newY][newX] == Map::_WALL_) {
            _player.setNextDirection(getAvailableDirection());
        }

        switch (_player.getNextDirection()) {
            case Player::Direction::UP:
                if (_map._mapItems[_player.getHead().getY() - 1][_player.getHead().getX()] != Map::_WALL_) {
                    _player.setDirection(Player::Direction::UP);
                    _player.moveBody(Coordinate(_player.getHead().getX(), _player.getHead().getY() - 1));
                }
                break;
            case Player::Direction::DOWN:
                if (_map._mapItems[_player.getHead().getY() + 1][_player.getHead().getX()] != Map::_WALL_) {
                    _player.setDirection(Player::Direction::DOWN);
                    _player.moveBody(Coordinate(_player.getHead().getX(), _player.getHead().getY() + 1));
                }
                break;
            case Player::Direction::LEFT:
                if (_map._mapItems[_player.getHead().getY()][_player.getHead().getX() - 1] != Map::_WALL_) {
                    _player.setDirection(Player::Direction::LEFT);
                    _player.moveBody(Coordinate(_player.getHead().getX() - 1, _player.getHead().getY()));
                }
                break;
            case Player::Direction::RIGHT:
                if (_map._mapItems[_player.getHead().getY()][_player.getHead().getX() + 1] != Map::_WALL_) {
                    _player.setDirection(Player::Direction::RIGHT);
                    _player.moveBody(Coordinate(_player.getHead().getX() + 1, _player.getHead().getY()));
                }
                break;
        }
    }
}

std::vector<Asset> Nibbler::getAssets(Coordinate windowSize, Coordinate resolution)
{
    std::vector<Asset> assets;
    size_t startX = (windowSize.getX() - (_map._mapItems[0].size()) * resolution.getY()) / 2;
    size_t startY = (windowSize.getY() - (_map._mapItems.size()) * resolution.getY()) / 2;

    for (size_t y = 0; y < _map._mapItems.size(); y++) {    
        for (size_t x = 0; x < _map._mapItems[y].size(); x++) {
            assets.push_back(Asset(
                    FORMATS.at(_map._mapItems[y][x]),
                    Coordinate(startX + x * resolution.getY(), startY + y * resolution.getY()),
                    Coordinate(resolution.getY(), resolution.getY())
                    )
                );
        }
    }
    auto sprite = _player.getSprite();
    for (size_t i = 0; i < _player._position.size(); i++) {
        assets.push_back(Asset(Format('>', RGB(0, 0, 0), sprite[i]), Coordinate(startX + _player._position[i].getX() * resolution.getY(), startY + _player._position[i].getY() * resolution.getY()), Coordinate(resolution.getY(), resolution.getY())));
    }
    return assets;
}

bool Nibbler::userWin() const
{
    for (size_t y = 0; y < _map._mapItems.size(); y++) {
        for (size_t x = 0; x < _map._mapItems[y].size(); x++) {
            if (_map._mapItems[y][x] == Map::_APPLE_)
                return false;
        }
    }
    return true;
}

extern "C" std::unique_ptr<IGame> getInstance()
{
    return std::make_unique<Nibbler>();
}
