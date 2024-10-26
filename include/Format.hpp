/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Format
*/

#ifndef FORMAT_HPP_
    #define FORMAT_HPP_

    #include <string>
    #include "RGB.hpp"

/// @brief Class for the format
class Format {
    public:
        /// @brief Constructor of the format class
        /// @param _char The char of the format
        /// @param _color The RGB color of the format
        /// @param _file The file path of the format
        Format(char _char, RGB _color, std::string _file) : _char(_char), _color(_color), _file(_file) { };

        /// @brief Destructor of the format class
        ~Format() = default;
    

        /// @brief Get the char of the format
        /// @return char The char of the format
        char getChar() const { return _char; }

        /// @brief Get the RGB color of the format
        /// @return RGB The color of the format
        RGB getColor() const { return _color; }

        /// @brief Get the file path of the format
        /// @return std::string The file path of the format
        std::string getFile() const { return _file; }
    private:
        /// @brief The char of the format
        char _char;

        /// @brief The RGB color of the format
        RGB _color;

        /// @brief The file path of the format
        std::string _file;
};

#endif /* !FORMAT_HPP_ */
