/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Coordinate
*/

#ifndef COORDINATE_HPP_
    #define COORDINATE_HPP_

/// @brief Class for the coordinate
class Coordinate {
    public:
        /// @brief The constructor of the coordinate class
        /// @param x coordinate x
        /// @param y coordinate y
        Coordinate(int const x, int const y) : _x(x), _y(y) {};

        /// @brief Destructor of the coordinate class
        ~Coordinate() = default;


        /// @brief Get the x coordinate
        /// @return int The x coordinate
        int getX() const { return _x; }

        /// @brief Get the y coordinate
        /// @return int The y coordinate
        int getY() const { return _y; }        


        /// @brief Operator + for the coordinate class
        /// @param c The Coordinate to add
        /// @return The new Coordinate result
        Coordinate operator+(const Coordinate &c) const { return Coordinate(_x + c.getX(), _y + c.getY());}

        /// @brief Operator - for the coordinate class
        /// @param c The Coordinate to substract
        /// @return The new Coordinate result
        Coordinate operator-(const Coordinate &c) const { return Coordinate(_x - c.getX(), _y - c.getY());}

        /// @brief Operator * for the coordinate class
        /// @param c The value to multiply
        /// @return The new Coordinate result
        Coordinate operator*(const int c) const { return Coordinate(_x * c, _y * c);}

        /// @brief Operator / for the coordinate class
        /// @param c The value to divide
        /// @return The new Coordinate result
        Coordinate operator/(const int c) const { return Coordinate(_x / c, _y / c);}
    private:
        /// @brief The x coordinate
        int _x;
    
        /// @brief The y coordinate
        int _y;
};

#endif /* !COORDINATE_HPP_ */
