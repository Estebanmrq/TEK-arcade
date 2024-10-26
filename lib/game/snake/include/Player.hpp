/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Map Snake Player
*/


#ifndef PLAYERSNAKE_HPP_
    #define PLAYERSNAKE_HPP_

    #include <map>
    #include <vector>
    #include <string>
    #include "Clock.hpp"
    #include "Coordinate.hpp"

class Player {
    public:
        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Player(Coordinate head, Coordinate m1, Coordinate m2, Coordinate tail) : _position({head, m1, m2, tail}), _dir(Direction::RIGHT), _nextDir(Direction::RIGHT), _clock(3000) {};
        ~Player() = default;

        Coordinate getHead() const { return _position.front(); }

        Player &operator=(const Player &other)
        {
            _position = other._position;
            return *this;
        }

        void growSnake()
        {
            _position.push_back(Coordinate(_position.back()));
        }

        void moveBody(const Coordinate &coord)
        {
            _position.insert(_position.begin(), coord);
            _position.pop_back();
        }

        std::vector<std::string> getSprite()
        {
            std::vector<std::string> sprites;

            sprites.push_back(SPRITES.at(_dir).at(HEAD));
            for (size_t i = 1; i < _position.size() - 1; i++) {
                Direction front = calculateDirection(_position[i - 1], _position[i]);
                Direction back = calculateDirection(_position[i], _position[i + 1]);
            
                if (i != 1 ? (front != back) : (back != _dir))
                    sprites.push_back(TURNS.at(calculateTurn(i != 1 ? front : _dir, back)));
                else
                    sprites.push_back(SPRITES.at(front).at(BODY));
            }
            sprites.push_back(SPRITES.at(calculateDirection(_position[_position.size() - 2], _position.back())).at(TAIL));
            return sprites;
        }

        bool onPlayer(const Coordinate &coord, bool head = true)
        {
            for (size_t i = head ? 0 : 1; i < _position.size(); i++) {
                if (_position[i].getX() == coord.getX() && _position[i].getY() == coord.getY())
                    return true;
            }
            return false;
        }

        Clock &getClock() { return _clock; }
        Direction getDirection() const { return _dir; }
        Direction getNextDirection() const { return _nextDir; }
        
        void setDirection(Direction dir) { _dir = dir; }
        void setNextDirection(Direction dir) { _nextDir = dir; }

        std::vector<Coordinate> _position;
    private:
        Direction _dir;
        Direction _nextDir;
        Clock _clock;

        enum BType {
            HEAD,
            BODY,
            TAIL
        };

        enum BDirection {
            L_DOWN_RIGHT,
            L_DOWN_LEFT,
            L_UP_RIGHT,
            L_UP_LEFT,
        };

        Direction calculateDirection(const Coordinate &p1, const Coordinate &p2)
        {
            Coordinate tmp = p1 - p2;
    
            if (tmp.getX() == 1)
                return Direction::RIGHT;
            else if (tmp.getX() == -1)
                return Direction::LEFT;
            else if (tmp.getY() == 1)
                return Direction::DOWN;
            else
                return Direction::UP;
        }

        BDirection calculateTurn(const Direction &back, const Direction &front)
        {
            if ((front == Direction::UP && back == Direction::RIGHT) || (front == Direction::LEFT && back == Direction::DOWN))
                return L_DOWN_RIGHT;
            else if ((front == Direction::UP && back == Direction::LEFT) || (front == Direction::RIGHT && back == Direction::DOWN))
                return L_DOWN_LEFT;
            else if ((front == Direction::DOWN && back == Direction::RIGHT) || (front == Direction::LEFT && back == Direction::UP))
                return L_UP_RIGHT;
            else
                return L_UP_LEFT;
        }

        
        const std::map<Direction, std::vector<std::string>> SPRITES = {
            {UP, {{"assets/game/snake/snake/top/head.png", "assets/game/snake/snake/straight/vertical.png", "assets/game/snake/snake/top/tail.png"}}},
            {DOWN, {{"assets/game/snake/snake/bottom/head.png", "assets/game/snake/snake/straight/vertical.png", "assets/game/snake/snake/bottom/tail.png"}}},
            {LEFT, {{"assets/game/snake/snake/left/head.png", "assets/game/snake/snake/straight/horizontal.png", "assets/game/snake/snake/left/tail.png"}}},
            {RIGHT, {{"assets/game/snake/snake/right/head.png", "assets/game/snake/snake/straight/horizontal.png", "assets/game/snake/snake/right/tail.png"}}}
        };

        const std::map<BDirection, std::string> TURNS = {
            {L_DOWN_RIGHT, "assets/game/snake/snake/turn/down_right.png"},
            {L_DOWN_LEFT, "assets/game/snake/snake/turn/down_left.png"},
            {L_UP_RIGHT, "assets/game/snake/snake/turn/up_right.png"},
            {L_UP_LEFT, "assets/game/snake/snake/turn/up_left.png"}
        };

};


#endif /* !PLAYERSNAKE_HPP_ */
