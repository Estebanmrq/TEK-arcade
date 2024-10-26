/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Pacman
*/

#include <memory>
#include "Random.hpp"
#include "Pacman.hpp"

Pacman::Pacman() : _player(11, 13), _score(0), _niv(0)
{
    _map = Map(MAPS[_niv]);
    if (_map._mapItems.empty())
        throw IGame::Error("pacman: map is empty.");
    if (_player.getX() >= _map._mapItems[0].size() || _player.getY() >= _map._mapItems.size()
        || _player.getX() < 0 || _player.getY() < 0)
        throw IGame::Error("pacman: player is out of map.");
    if (_map._mapItems[_player.getY()][_player.getX()] != Map::_EMPTY_)
        throw IGame::Error("pacman: player must start on an empty cell.");
    Random::initRandom();
}

Pacman::~Pacman()
{
}

void Pacman::restart()
{
    _map = Map(MAPS[_niv]);
    _player.setPosition(11, 13);
    _player.setDirection(Player::RIGHT);
    if (_niv == 0)
        _score = 0;
    for (auto &ghost : _ghosts) {
        ghost.setPosition(11, 10);
        ghost.setDirection(Ghost::UP);
        ghost.getClock().setTick(10000);
    }
}

int Pacman::getScore()
{
    return _score;
}

bool Pacman::userWin() const
{
    for (size_t y = 0; y < _map._mapItems.size(); y++) {
        for (size_t x = 0; x < _map._mapItems[y].size(); x++) {
            if (_map._mapItems[y][x] == Map::_PACGUM_ || _map._mapItems[y][x] == Map::items::_SUPER_PACGUM_)
                return false;
        }
    }
    return true;
}

bool Pacman::isPortal(const int x, const int y) const
{
    if (x < 0)
        return !isWall(_map._mapItems[y][_map._mapItems[0].size() - 1]);
    if (x >= (int)_map._mapItems[0].size())
        return !isWall(_map._mapItems[y][0]);
    if (y < 0)
        return !isWall(_map._mapItems[_map._mapItems.size() - 1][x]);
    if (y >= (int)_map._mapItems.size())
        return !isWall(_map._mapItems[0][x]);
    return false;
}

void Pacman::movePlayer(Event::types events)
{
    float x, y;

    if (events == Event::types::UP || events == Event::types::DOWN || events == Event::types::LEFT || events == Event::types::RIGHT) {
        x = events == Event::types::RIGHT ? _player.getStep() : events == Event::types::LEFT ? - _player.getStep() : 0;
        y = events == Event::types::DOWN ? _player.getStep() : events == Event::types::UP ? - _player.getStep() : 0;
    } else {
        x = _player.getDirection() == Player::RIGHT ? _player.getStep() : _player.getDirection() == Player::LEFT ? - _player.getStep() : 0;
        y = _player.getDirection() == Player::DOWN ? _player.getStep() : _player.getDirection() == Player::UP ? - _player.getStep() : 0;
    }

    x += _player.getX();
    y += _player.getY();

    if (isWall(_map._mapItems[y][x]) ||
        (y < 0 || y >= (int)_map._mapItems.size()) ||
        (x < 0 || x >= (int)_map._mapItems[0].size())) {
        if (!isPortal(x, y)) {
            return;
        } else {
            if (x < 0) {
                x = _map._mapItems[0].size() - 1;
                _player.setDirection(Player::LEFT);
            } else if (x >= (int)_map._mapItems[0].size()) {
                x = 0;
                _player.setDirection(Player::RIGHT);
            } else if (y < 0) {
                y = _map._mapItems.size() - 1;
                _player.setDirection(Player::UP);
            } else {
                y = 0;
                _player.setDirection(Player::DOWN);
            }
            _player.setPosition(x, y);
            return;
        }
    }

    switch (events) {
        case Event::UP:
            _player.move(Player::UP);
            break;
        case Event::DOWN:
            _player.move(Player::DOWN);
            break;
        case Event::LEFT:
            _player.move(Player::LEFT);
            break;
        case Event::RIGHT:
            _player.move(Player::RIGHT);
            break;
        default:
            _player.move(_player.getDirection());
            break;
    }
}

void Pacman::setNewDirection(Ghost &ghost)
{
    int changeDirection = Random::getRandomInt(0, 100);
    int newDirection = Random::getRandomInt(0, 3);

    if (changeDirection >= 98) {
        ghost.setDirection(static_cast<Ghost::direction>(newDirection));
    }
    if (ghost.getDirection() == Ghost::UP && ghost.getY() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY() - 1][ghost.getX()]))
        moveGhost(ghost, false);
    else if (ghost.getDirection() == Ghost::DOWN && ghost.getY() + 1 < _map._mapItems.size() && !isWall(_map._mapItems[ghost.getY() + 1][ghost.getX()]))
        moveGhost(ghost, false);
    else if (ghost.getDirection() == Ghost::LEFT && ghost.getX() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY()][ghost.getX() - 1]))
        moveGhost(ghost, false);
    else if (ghost.getDirection() == Ghost::RIGHT && ghost.getX() + 1 < _map._mapItems[0].size() && !isWall(_map._mapItems[ghost.getY()][ghost.getX() + 1]))
        moveGhost(ghost, false);
    else
        setNewDirection(ghost);
}

bool Pacman::hasMultiplePaths(Ghost &ghost)
{
    int paths = 0;

    if (ghost.getY() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY() - 1][ghost.getX()]))
        paths++;
    if (ghost.getY() + 1 < _map._mapItems.size() && !isWall(_map._mapItems[ghost.getY() + 1][ghost.getX()]))
        paths++;
    if (ghost.getX() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY()][ghost.getX() - 1]))
        paths++;
    if (ghost.getX() + 1 < _map._mapItems[0].size() && !isWall(_map._mapItems[ghost.getY()][ghost.getX() + 1]))
        paths++;
    return paths > 1;
}

bool Pacman::inSpawn(Ghost &ghost) const
{
    return ghost.getY() >= 9 && ghost.getY() <= 11 && ghost.getX() >= 9 && ghost.getX() <= 13;
}

void Pacman::moveGhost(Ghost &ghost, bool isRandomized)
{
    if (inSpawn(ghost)) {
        ghost.move(Ghost::UP);
    }

    switch (ghost.getDirection()) {
        case Ghost::UP:
            if ((!isRandomized || !hasMultiplePaths(ghost)) && ghost.getY() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY() - 1][ghost.getX()])) {
                ghost.move(Ghost::UP);
            } else {
                setNewDirection(ghost);
            }
            break;
        case Ghost::DOWN:
            if ((!isRandomized || !hasMultiplePaths(ghost)) && ghost.getY() + 1 < _map._mapItems.size() && !isWall(_map._mapItems[ghost.getY() + 1][ghost.getX()])) {
                ghost.move(Ghost::DOWN);
            } else {
                setNewDirection(ghost);
            }
            break;
        case Ghost::LEFT:
            if ((!isRandomized || !hasMultiplePaths(ghost)) && ghost.getX() - 1 >= 0 && !isWall(_map._mapItems[ghost.getY()][ghost.getX() - 1])) {
                ghost.move(Ghost::LEFT);
            } else {
                setNewDirection(ghost);
            }
            break;
        case Ghost::RIGHT:
            if ((!isRandomized || !hasMultiplePaths(ghost)) && ghost.getX() + 1 < _map._mapItems[0].size() && !isWall(_map._mapItems[ghost.getY()][ghost.getX() + 1])) {
                ghost.move(Ghost::RIGHT);
            } else {
                setNewDirection(ghost);
            }
            break;
    }
}

Ghost::direction Pacman::getDirectionToSpawn(Ghost &ghost)
{
    if (ghost.getX() < 11)
        return Ghost::RIGHT;
    if (ghost.getX() > 11)
        return Ghost::LEFT;
    if (ghost.getY() < 10)
        return Ghost::DOWN;
    if (ghost.getY() > 10)
        return Ghost::UP;
    return Ghost::DOWN;
}

void Pacman::handleEvents(Event::types events)
{
    movePlayer(events);

    if (_map._mapItems[_player.getY()][_player.getX()] == Map::_PACGUM_) {
        _map._mapItems[_player.getY()][_player.getX()] = Map::_EMPTY_;
        _score += 10;
    } else if (_map._mapItems[_player.getY()][_player.getX()] == Map::items::_SUPER_PACGUM_) {
        _map._mapItems[_player.getY()][_player.getX()] = Map::_EMPTY_;
        _score += 50;
        for (auto &ghost : _ghosts) {
            ghost.setWeakness();
        }
    } else if (userWin()) {
        _niv = _niv + 1 < MAPS->size() ? _niv + 1 : 0;
        restart();
    }

    for (auto &ghost : _ghosts) {
        if (ghost.getEated() && !inSpawn(ghost)) {
            ghost.move(getDirectionToSpawn(ghost));
            continue;
        } else if (ghost.getEated() && inSpawn(ghost)) {
            ghost.setNormal();
            ghost.getClock().setTick(10000);
        }
        moveGhost(ghost);
        if (ghost.getX() == _player.getX() && ghost.getY() == _player.getY() && !ghost.getWeakness()) {
            _niv = 0;
            restart();
        } else if (ghost.getX() == _player.getX() && ghost.getY() == _player.getY() && ghost.getWeakness()) {
            ghost.setEated();
            _score += 200;
        }
    }
}

std::vector<Asset> Pacman::getAssets(Coordinate windowSize, Coordinate resolution)
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
    assets.push_back(Asset(
        Format('C', RGB(0, 0, 0), _player.getSprite()),
        Coordinate(startX + _player.getX() * resolution.getY(), startY + _player.getY() * resolution.getY()),
        Coordinate(resolution.getY(), resolution.getY())
    ));
    for (auto &ghost : _ghosts) {
        assets.push_back(Asset(
            Format(ghost.getWeakness() ? 'm':ghost.getEated() ? '\"':'M', RGB(0, 0, 0), ghost.getSprite()),
            Coordinate(startX + ghost.getX() * resolution.getY(), startY + ghost.getY() * resolution.getY()),
            Coordinate(resolution.getY(), resolution.getY())
        ));
    }
    return assets;
}


extern "C" std::unique_ptr<IGame> getInstance()
{
    return std::make_unique<Pacman>();
}
