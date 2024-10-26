/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
    #define GHOST_HPP_
    #include <map>
    #include <vector>
    #include <string>
    #include <functional>
    #include "Clock.hpp"

class Ghost {
    public:
        enum type {
            CYAN,
            PINK,
            RED,
            ORANGE
        };

        enum direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Ghost(type type, float x, float y, direction direction) : _type(type), _x(x), _y(y), _direction(direction), _sprite(0), _spriteWeak(0), _clock(Ghost::STATE), isWeak(false), isEated(false), _weakClock(0)
        {
            _sprites = RESSOURCES.at(_type);
        };

        ~Ghost() = default;

        float getX() const { return _x; }
        float getY() const { return _y; }
        void setPosition(const float x, const float y) { _x = x; _y = y; }
        void setDirection(const direction direction) { _direction = direction; }
        void setWeakness() { isWeak = true; _weakClock.setTick(STATE); _clock.setTick(WEAK_SPEED); }
        void setNormal() { isWeak = false; isEated = false; _weakClock.setTick(0); _clock.setTick(NORMAL_SPEED); }
        void setEated() { isWeak = false; isEated = true; _clock.setTick(DEAD_SPEED); }
        direction getDirection() const { return _direction; }
        Clock &getClock() { return _clock; }
        bool getEated() const { return isEated; }
        bool getWeakness() const { return isWeak; }

        void move(const direction direction) {
            if (_clock.updateTick()) {
                if (_clock.getTick() == STATE)
                    _clock.setTick(NORMAL_SPEED);
                if (_weakClock.updateTick()) {
                    setNormal();
                }
                MOVES.at(direction)();
            }
        }

        std::string getSprite() const {
            if (isWeak)
                return WEAK[_spriteWeak];
            if (isEated)
                return DEAD.at(_direction);
            return _sprites.at(_direction)[_sprite];
        }

        const int STATE = 10000;
        const int DEAD_SPEED = 50;
        const int NORMAL_SPEED = 180;
        const int WEAK_SPEED = 350;

    private:
        type _type;
        float _x;
        float _y;
        direction _direction;
        size_t _sprite;
        size_t _spriteWeak;
        Clock _clock;
        bool isWeak;
        bool isEated;
        Clock _weakClock;

        std::map<direction, std::vector<std::string>> _sprites;

        const std::string WEAK[4] = {
            "assets/game/pacman/ghosts/weak/weak1.png",
            "assets/game/pacman/ghosts/weak/weak2.png",
            "assets/game/pacman/ghosts/weak/weak3.png",
            "assets/game/pacman/ghosts/weak/weak4.png"
        };

        const std::map<direction, std::string> DEAD = {
            {UP, "assets/game/pacman/ghosts/dead/up.png"},
            {DOWN, "assets/game/pacman/ghosts/dead/down.png"},
            {LEFT, "assets/game/pacman/ghosts/dead/left.png"},
            {RIGHT, "assets/game/pacman/ghosts/dead/right.png"}
        };

        void move_up() { _y -= 1; _direction = UP; _sprite = _sprite + 1 < _sprites.at(_direction).size() ? _sprite + 1 : 0; _spriteWeak = _spriteWeak + 1 < 4 ? _spriteWeak + 1 : 0; }
        void move_down() { _y += 1; _direction = DOWN; _sprite = _sprite + 1 < _sprites.at(_direction).size() ? _sprite + 1 : 0; _spriteWeak = _spriteWeak + 1 < 4 ? _spriteWeak + 1 : 0; }
        void move_left() { _x -= 1; _direction = LEFT; _sprite = _sprite + 1 < _sprites.at(_direction).size() ? _sprite + 1 : 0; _spriteWeak = _spriteWeak + 1 < 4 ? _spriteWeak + 1 : 0; }
        void move_right() { _x += 1; _direction = RIGHT; _sprite = _sprite + 1 < _sprites.at(_direction).size() ? _sprite + 1 : 0; _spriteWeak = _spriteWeak + 1 < 4 ? _spriteWeak + 1 : 0; }

        const std::map<direction, std::function<void ()>> MOVES = {
            {UP, [this](){ move_up(); }},
            {DOWN, [this](){ move_down(); }},
            {LEFT, [this](){ move_left(); }},
            {RIGHT, [this](){ move_right(); }}
        };

        const std::map<type, std::map<direction, std::vector<std::string>>> RESSOURCES = {
            {CYAN,
                {
                    {UP, {"assets/game/pacman/ghosts/cyan/top/top1.png", "assets/game/pacman/ghosts/cyan/top/top2.png"}},
                    {DOWN, {"assets/game/pacman/ghosts/cyan/bottom/bottom1.png", "assets/game/pacman/ghosts/cyan/bottom/bottom2.png"}},
                    {LEFT, {"assets/game/pacman/ghosts/cyan/left/left1.png", "assets/game/pacman/ghosts/cyan/left/left2.png"}},
                    {RIGHT, {"assets/game/pacman/ghosts/cyan/right/right1.png", "assets/game/pacman/ghosts/cyan/right/right2.png"}}
                }
            },
            {PINK,
                {
                    {UP, {"assets/game/pacman/ghosts/pink/top/top1.png", "assets/game/pacman/ghosts/pink/top/top2.png"}},
                    {DOWN, {"assets/game/pacman/ghosts/pink/bottom/bottom1.png", "assets/game/pacman/ghosts/pink/bottom/bottom2.png"}},
                    {LEFT, {"assets/game/pacman/ghosts/pink/left/left1.png", "assets/game/pacman/ghosts/pink/left/left2.png"}},
                    {RIGHT, {"assets/game/pacman/ghosts/pink/right/right1.png", "assets/game/pacman/ghosts/pink/right/right2.png"}}
                }
            },
            {RED,
                {
                    {UP, {"assets/game/pacman/ghosts/red/top/top1.png", "assets/game/pacman/ghosts/red/top/top2.png"}},
                    {DOWN, {"assets/game/pacman/ghosts/red/bottom/bottom1.png", "assets/game/pacman/ghosts/red/bottom/bottom2.png"}},
                    {LEFT, {"assets/game/pacman/ghosts/red/left/left1.png", "assets/game/pacman/ghosts/red/left/left2.png"}},
                    {RIGHT, {"assets/game/pacman/ghosts/red/right/right1.png", "assets/game/pacman/ghosts/red/right/right2.png"}}
                }
            },
            {ORANGE,
                {
                    {UP, {"assets/game/pacman/ghosts/orange/top/top1.png", "assets/game/pacman/ghosts/orange/top/top2.png"}},
                    {DOWN, {"assets/game/pacman/ghosts/orange/bottom/bottom1.png", "assets/game/pacman/ghosts/orange/bottom/bottom2.png"}},
                    {LEFT, {"assets/game/pacman/ghosts/orange/left/left1.png", "assets/game/pacman/ghosts/orange/left/left2.png"}},
                    {RIGHT, {"assets/game/pacman/ghosts/orange/right/right1.png", "assets/game/pacman/ghosts/orange/right/right2.png"}}
                }
            }
        };
};

#endif /* !GHOST_HPP_ */
