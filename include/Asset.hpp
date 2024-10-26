/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Asset
*/

#ifndef ASSET_HPP_
    #define ASSET_HPP_

    #include "Format.hpp"
    #include "Coordinate.hpp"

/// @brief Class for the asset
class Asset {
    public:
        /// @brief Constructor of the asset class
        /// @param Format The format of the asset
        /// @param Coordinate The position of the asset
        /// @param Coordinate The size of the asset
        Asset(Format format, Coordinate position, Coordinate size) : _format(format), _position(position), _size(size) {};

        /// @brief Destructor of the asset class
        ~Asset() = default;


        /// @brief Get the format of the asset
        /// @return Format The format of the asset
        Format getFormat() const { return _format; }

        /// @brief Get the position of the asset
        /// @return Coordinate The position of the asset
        Coordinate getPosition() const { return _position; }

        /// @brief Get the size of the asset
        /// @return Coordinate The size of the asset
        Coordinate getSize() const { return _size; }
    private:
        /// @brief The format of the asset
        Format _format;

        /// @brief The position of the asset
        Coordinate _position;

        /// @brief The size of the asset
        Coordinate _size;
};

#endif /* !ASSET_HPP_ */
