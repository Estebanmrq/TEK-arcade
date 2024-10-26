/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_
    #include "Player_nibbler.hpp"
    #include "IGame.hpp"
    #include "Map_nibbler.hpp"

class Nibbler : public IGame {
    public:
        /// @brief Constructor of the Nibbler
        Nibbler();

        /// @brief Destructor of the IGame
        virtual ~Nibbler();

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
        int _score;
        size_t _niv;

        Player::Direction getAvailableDirection();

        const std::map<Map::items, Format> FORMATS {
            {Map::_EMPTY_, Format(' ', RGB(0, 0, 0), "assets/game/nibbler/item/Empty.png")},
            {Map::_WALL_, Format('#', RGB(0, 0, 0), "assets/game/nibbler/item/wall.png")},
            {Map::_APPLE_, Format('o', RGB(0, 0, 0), "assets/game/nibbler/item/diamond violet.png")}
        };

        const std::string MAPS[6] = {
            "assets/game/nibbler/maps/map_1.txt",
            "assets/game/nibbler/maps/map_2.txt",
            "assets/game/nibbler/maps/map_3.txt",
            "assets/game/nibbler/maps/map_4.txt",
            "assets/game/nibbler/maps/map_5.txt",
            "assets/game/nibbler/maps/map_6.txt"
        };

        bool isWall(const Map::items &item) const
        {
            return item != Map::_EMPTY_
                && item != Map::_APPLE_;
        }

        bool userWin() const;

        const float SPEED = 200;
};

#endif /* !NIBBLER_HPP_ */
