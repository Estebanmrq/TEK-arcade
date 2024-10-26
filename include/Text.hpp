/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <string>
    #include "Coordinate.hpp"

/// @brief Class for the text
class Text {
    public:
        /// @brief The constructor of the text class
        /// @param text The text
        /// @param coord The coordinate of the text
        /// @param isSelected The state of the text
        Text(const std::string &text, const Coordinate &coord, const bool isSelected = false) : _text(text), _coord(coord), _isSelected(isSelected) {};
    
        /// @brief Destructor of the text class
        ~Text() = default;


        /// @brief Get the text
        /// @return std::string The text
        const std::string &getText() const { return _text; }

        /// @brief Get the coordinate
        /// @return Coordinate The coordinate
        const Coordinate &getCoord() const { return _coord; }

        /// @brief Get the state of the text
        /// @return bool The state of the text
        const bool &getIsSelected() const { return _isSelected; }
    private:
        /// @brief The text
        const std::string _text;

        /// @brief The coordinate
        const Coordinate _coord;

        /// @brief The state of the text
        const bool _isSelected;
};

#endif /* !TEXT_HPP_ */
