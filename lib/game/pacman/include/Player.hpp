/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <map>
    #include <string>
    #include <functional>
    #include "Clock.hpp"
    #include "IGame.hpp"

class Player {
    public:
        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Player(float x, float y, float step = 1) : _x(x), _y(y), _step(step), _sprite(0), _isAlive(true), _clock(180), _direction(RIGHT) {}
        ~Player() = default;

        float getX() const { return _x; }
        float getY() const { return _y; }
        void setPosition(const float x, const float y) { _x = x; _y = y; }
        void setDirection(const Direction direction) { _direction = direction; }
        float getStep() const { return _step; }
        bool isAlive() const { return _isAlive; }
        Direction getDirection() const { return _direction; }

        void move(const Direction direction) {
            if (!_isAlive)
                return;
            _direction = direction;
            if (_clock.updateTick()) {
                _sprites.at(direction)();
            }
        }

        std::string getSprite() const {
            switch (_direction) {
                case UP:
                    return SUP[_sprite];
                case DOWN:
                    return SDOWN[_sprite];
                case LEFT:
                    return SLEFT[_sprite];
                case RIGHT:
                    return SRIGHT[_sprite];
            }
            return "";
        }

    private:

        float _x;
        float _y;
        float _step;
        size_t _sprite;
        bool _isAlive;
        Clock _clock;

        Direction _direction;

        const std::string SUP[3] = {"assets/game/pacman/pacman/pacman002.png", "assets/game/pacman/pacman/top/pacman028.png", "assets/game/pacman/pacman/top/pacman029.png"};
        const std::string SDOWN[3] = {"assets/game/pacman/pacman/pacman002.png", "assets/game/pacman/pacman/bottom/pacman042.png", "assets/game/pacman/pacman/bottom/pacman043.png"};
        const std::string SLEFT[3] = {"assets/game/pacman/pacman/pacman002.png", "assets/game/pacman/pacman/left/pacman014.png", "assets/game/pacman/pacman/left/pacman015.png"};
        const std::string SRIGHT[3] = {"assets/game/pacman/pacman/pacman002.png", "assets/game/pacman/pacman/right/pacman000.png", "assets/game/pacman/pacman/right/pacman001.png"};

        void move_up() { _y -= _step; _direction = UP; _sprite = _sprite == 2 ? 0 : _sprite + 1; }
        void move_down() { _y += _step; _direction = DOWN ; _sprite = _sprite == 2 ? 0 : _sprite + 1;}
        void move_left() { _x -= _step; _direction = LEFT ; _sprite = _sprite == 2 ? 0 : _sprite + 1;}
        void move_right() { _x += _step; _direction = RIGHT; _sprite = _sprite == 2 ? 0 : _sprite + 1;}

        const std::map<Direction, std::function<void ()>> _sprites = {
            {UP, [this](){ move_up(); }},
            {DOWN, [this](){ move_down(); }},
            {LEFT, [this](){ move_left(); }},
            {RIGHT, [this](){ move_right(); }}
        };
};

#endif /* !PLAYER_HPP_ */
