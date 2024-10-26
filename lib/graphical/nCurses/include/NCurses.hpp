/*
** EPITECH PROJECT, 2024
** nCurses
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

    #include "IDisplay.hpp"

class Encapsulation {
    public:
        static WINDOW *InitWindow() { return initscr(); }
        static int InitKeyPad(WINDOW *window, bool state) { return keypad(window, state); }
        static int DisableEcho() { return noecho(); }
        static int SetCursorVisibility(int visibility) { return curs_set(visibility); }
        static int SetNoDelay(WINDOW *window, bool state) { return nodelay(window, state); }
        static void ClearWindow() { clear(); }
        static void RefreshWindow() { refresh(); }
        static int DisplayText(int y, int x, const std::string str) { return mvprintw(y, x, "%s", str.c_str()); }
        static void SetUnderline() { attron(A_UNDERLINE); }
        static void UnsetUnderline() { attroff(A_UNDERLINE); }
        static int Refresh() { return refresh(); }
        static int GetChar() { return getch(); }
        static int CloseWindow() { return endwin(); }
};

class NCurses : public IDisplay {
    public:
        /// @brief Constructor of the nCurses
        NCurses();

        /// @brief Destuctor of the nCurses class
        virtual ~NCurses();
    
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

        /// @brief The resolution of the nCurses
        const int RESOLUTION_Y = 1;
        const int RESOLUTION_X = 1;
};

#endif /* !NCURSES_HPP_ */
