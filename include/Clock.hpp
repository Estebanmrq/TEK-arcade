/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
    #define CLOCK_HPP_

    #include <chrono>

class Clock {
    public:
        Clock(double tick) : _tick(tick), _start(std::chrono::system_clock::now()) { }

        int getElapsedTime() const { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _start).count(); }
        double getTick() const { return _tick; }
        void setTick(double tick) { _tick = tick; }    
        
        void restart() { _start = std::chrono::system_clock::now(); }
        
        bool isTick() const { return getElapsedTime() >= _tick; }
        bool updateTick() { if (isTick()) { restart(); return true; } return false; }

    private:
        double _tick;
        std::chrono::time_point<std::chrono::system_clock> _start;

};

#endif /* !CLOCK_HPP_ */
