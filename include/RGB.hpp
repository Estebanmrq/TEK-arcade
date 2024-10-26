/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** RGB
*/

#ifndef RGB_HPP_
    #define RGB_HPP_

/// @brief Class for the RGB
class RGB {
    public:
        /// @brief The constructor of the RGB class
        /// @param r value of red
        /// @param g value of green
        /// @param b value of blue
        RGB(int r, int g, int b) : _r(r), _g(g), _b(b) {};

        /// @brief Destructor of the RGB class
        ~RGB() = default;

        /// @brief Value of red
        int _r;

        /// @brief Value of green
        int _g;

        /// @brief Value of blue
        int _b;
};

#endif /* !RGB_HPP_ */
