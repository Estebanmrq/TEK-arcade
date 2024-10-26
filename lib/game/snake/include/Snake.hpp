/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Snake
*/


#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "Map.hpp"
    #include "IGame.hpp"
    #include "Player.hpp"


class Snake : public IGame {
    public:
        /// @brief Constructor of the Snake
        Snake();

        /// @brief Destructor of the IGame
        virtual ~Snake();

        /// @brief Restart the game
        virtual void restart();

        /// @brief Get the score of the game 
        virtual int getScore();

        /// @brief Handle all events of the game
        /// @param Event::types The events detected by the display module 
        virtual void handleEvents(Event::types events);

        /// @brief Get the assets of the game
        /// @return std::vector<Asset> The assets of the game
        virtual std::vector<Asset> getAssets(Coordinate windowSize, Coordinate resolution);
    private:
        Map _map;
        Player _player;
        Coordinate _apple;
        int _score;

        bool playerWin()
        { 
            for (size_t i = 1; i < _map.getWidth() - 1; i++)
                for (size_t j = 1; j < _map.getHeight() - 1; j++)
                    if (!_player.onPlayer(Coordinate(i, j)))
                        return false;
            return true;
         };

        const float SPEED = 200;
};


#endif /* !SNAKE_HPP_ */
