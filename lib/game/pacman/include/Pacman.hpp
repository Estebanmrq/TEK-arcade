/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_
    #include "Player.hpp"
    #include "IGame.hpp"
    #include "Map.hpp"
    #include "Ghost.hpp"

class Pacman : public IGame {
    public:
        /// @brief Constructor of the Pacman
        Pacman();

        /// @brief Destructor of the IGame
        virtual ~Pacman();

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
        Ghost _ghosts[4] = {Ghost(Ghost::CYAN, 11, 10, Ghost::UP), Ghost(Ghost::PINK, 11, 10, Ghost::UP), Ghost(Ghost::RED, 11, 10, Ghost::UP), Ghost(Ghost::ORANGE, 11, 10, Ghost::UP)};
        int _score;
        size_t _niv;

        const RGB WALL_COLOR = RGB(0, 39, 216);
        const std::map<Map::items, Format> FORMATS {
            {Map::_EMPTY_, Format(' ', RGB(0, 0, 0), "assets/game/pacman/wall/empty.png")},
            {Map::_WALL_START_TOP_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall01.png")},
            {Map::_WALL_START_LEFT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall02.png")},
            {Map::_WALL_START_RIGHT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall03.png")},
            {Map::_WALL_START_BOTTOM_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall04.png")},
            {Map::_WALL_T_LEFT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall05.png")},
            {Map::_WALL_T_RIGHT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall06.png")},
            {Map::_WALL_T_TOP_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall07.png")},
            {Map::_WALL_T_BOTTOM_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall08.png")},
            {Map::_WALL_L_TOP_RIGHT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall09.png")},
            {Map::_WALL_L_BOTTOM_RIGHT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall10.png")},
            {Map::_WALL_L_BOTTOM_LEFT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall11.png")},
            {Map::_WALL_L_TOP_LEFT_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall12.png")},
            {Map::_WALL_STRAIGHT_HORIZONTALE_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall13.png")},
            {Map::_WALL_STRAIGHT_VERTICALE_, Format('#', WALL_COLOR, "assets/game/pacman/wall/wall14.png")},
            {Map::_DOOR_, Format('_', RGB(0, 0, 0), "assets/game/pacman/wall/door.png")},
            {Map::_PACGUM_, Format('.', RGB(0, 0, 0), "assets/game/pacman/food/pacgum.png")},
            {Map::_SUPER_PACGUM_, Format('o', RGB(0, 0, 0), "assets/game/pacman/food/super_pacgum.png")},
            {Map::_SUPER_PACGUM_MIN_, Format('.', RGB(0, 0, 0), "assets/game/pacman/food/pacgum.png")}
        };

        const std::string MAPS[3] = {
            "assets/game/pacman/maps/map1.txt",
            "assets/game/pacman/maps/map2.txt",
            "assets/game/pacman/maps/map3.txt"
        };


        bool isWall(const Map::items &item) const
        {
            return item != Map::_EMPTY_
                && item != Map::_PACGUM_
                && item != Map::_SUPER_PACGUM_
                && item != Map::_SUPER_PACGUM_MIN_;
        }

        bool isPortal(const int x, const int y) const;

        void movePlayer(Event::types events);
        void moveGhost(Ghost &ghost, bool isRandomized = true);
        void setNewDirection(Ghost &ghost);
        bool hasMultiplePaths(Ghost &ghost);
        bool inSpawn(Ghost &ghost) const;
        Ghost::direction getDirectionToSpawn(Ghost &ghost);

        bool userWin() const;
};

#endif /* !PACMAN_HPP_ */
