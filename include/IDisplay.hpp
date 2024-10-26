/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
    #define IDISPLAY_HPP_

    #include <vector>
    #include <string>

    #include "Text.hpp"
    #include "Event.hpp"
    #include "Asset.hpp"
    #include "Coordinate.hpp"

/// @brief Interface for the display library module
class IDisplay {
    public:
        /// @brief Destructor
        virtual ~IDisplay() = default;

        /// @brief Clear the window
        virtual void clearWindow() = 0;

        /// @brief Display an asset on the display module
        /// @param std::vector<Asset> A map of asset to display with their position
        virtual void displayAssets(std::vector<Text> texts, std::vector<Asset> assets) = 0;

        /// @brief Get the size of the window
        /// @return Coordinate The size of the window
        virtual Coordinate getSizeWindow() const = 0;

        /// @brief Return all events detected by the display module
        /// @return Event::types The event detected
        virtual Event::types getEvent() const = 0;

        /// @brief Get the resolution of the display module
        /// @return Coordinate The resolution of the display module
        virtual Coordinate getResolution() const = 0;

        /// @brief Error class for the display module
        class Error : public std::exception {
            public:
                /// @brief Throw an error with a message
                Error(const std::string &message) : _message(message) {};

                /// @brief Get the error message
                /// @return const char* The error message
                const char *what() const throw() { return _message.c_str(); };
            private:
                /// @brief The error message
                std::string _message;
        };
};

#endif /* !IDISPLAY_HPP_ */
