/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include <vector>
    #include "Event.hpp"
    #include "Asset.hpp"
    #include "Text.hpp"

class IGame {
    public:
        /// @brief Destructor of the IGame
        virtual ~IGame() = default;

        /// @brief Restart the game
        virtual void restart() = 0;

        /// @brief Get the score of the game 
        virtual int getScore() = 0;

        /// @brief Handle all events of the game
        /// @param Event::types The events detected by the display module 
        virtual void handleEvents(Event::types events) = 0;

        /// @brief Get the assets of the game
        /// @return std::vector<Asset> The assets of the game
        virtual std::vector<Asset> getAssets(Coordinate windowSize, Coordinate resolution) = 0;

        class Error : public std::exception {
            public:
                Error (const std::string &message) : _message(message) {};
                const char *what() const throw() { return _message.c_str(); };
            private:
                std::string _message;
        };
};

#endif /* !IGAME_HPP_ */
