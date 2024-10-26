/*
** EPITECH PROJECT, 2024
** nCurses
** File description:
** SFML class
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include "IDisplay.hpp"
    #include <SFML/Graphics.hpp>

class Sfml : public IDisplay {
    public:
         /// @brief Constructor of the Sfml
        Sfml();

        /// @brief Destuctor of the Sfml class
        virtual ~Sfml();
    
        /// @brief Clear the window
        virtual void clearWindow();

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        virtual void displayAssets(std::vector<Text> texts, std::vector<Asset> assets);

        /// @brief Get the size of the window
        /// @return Coordinate The size of the window
        virtual Coordinate getSizeWindow() const;

        /// @brief Return all events detected by the nCurses
        /// @return Event::types The event detected
        virtual Event::types getEvent() const;

        /// @brief Get the resolution of the nCurses
        /// @return Coordinate The resolution of the nCurses
        virtual Coordinate getResolution() const;

    private:
        /// @brief Display text on the display module
        /// @param std::vector<Text> A map of text to display with their position
        virtual void displayText(std::vector<Text> texts);

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        virtual void displaySprite(std::vector<Asset> assets);

        const int RESOLUTION_Y = 16;
        const int RESOLUTION_X = 13;

        /// @brief The deffault window size X
        const unsigned int WINDOW_SIZE_X = 100 * RESOLUTION_X;

        /// @brief The deffault window size Y
        const unsigned int WINDOW_SIZE_Y = 50 * RESOLUTION_Y;
        sf::RenderWindow window;
        sf::View view;
};

#endif /* !SFML_HPP_ */
