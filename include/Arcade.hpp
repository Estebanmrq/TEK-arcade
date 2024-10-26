/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** Arcade
*/

#ifndef ARCADE_HPP_
    #define ARCADE_HPP_

    #include <map>
    #include <memory>
    #include <string>
    #include <exception>
    #include <functional>

    #include "IGame.hpp"
    #include "IDisplay.hpp"
    #include "DLLoader.hpp"
    #include "Score.hpp"

    #define RESX this->_gui->getResolution().getX()
    #define RESY this->_gui->getResolution().getY()
    #define WSX this->_gui->getSizeWindow().getX()
    #define WSY this->_gui->getSizeWindow().getY()

/// @brief Arcade class
class Arcade : public std::exception
{
    public:
        /// @brief Build a new Arcade object
        /// @param graphicalLib Path to the graphical library to load at start
        Arcade(const std::string &graphicalLib);
        
        /// @brief Destroy the Arcade object
        ~Arcade();

        
        /// @brief Run the arcade
        void run();

        //
        // Exceptions
        //

        /// @brief Error class
        class Error: public std::exception
        {
            public:
                /// @brief Construct a new Error object
                /// @param message The error message to send
                Error(const std::string &message) : _message("Error: " + message + ".") {};
                /// @brief Get the error message
                /// @return The error message
                const char *what() const throw() { return _message.c_str(); };
            private:
                /// @brief The error message
                std::string _message;
        };

        /// @brief Quit class
        class Quit: public std::exception
        {
            public:
                /// @brief Construct a new Quit object
                Quit(){};
                /// @brief Get the quit message
                const char *what() const throw() { return "Bye, bye ..."; };
        };

    //
    // Functions
    //
    private:
        /// @brief Display the arcade launcher
        void launcher();

        /// @brief Display the arcade menu
        void menu();

        /// @brief Display the game loaded
        void game(const std::string &game);


        /// @brief Display the score of the player
        void displayScore();


        /// @brief Get the user input value
        /// @param event The type of event detected
        /// @return The ascii value of the input
        char getUserInValue(Event::types event);

        /// @brief Get the name of the library or game
        /// @param path path to the library or game
        /// @return The name of the library or game
        std::string getName(const std::string &path);



        /// @brief Set all dll available
        void setAllDllAvailable();

        /// @brief Load the next graphical library
        void cmdNextLib();

        /// @brief Load the next game
        void cmdNextGame();

        /// @brief Restart the game
        void cmdRestart();

        /// @brief Quit the game
        void cmdQuit();

        /// @brief Go back to the menu
        void cmdMenu();

        /// @brief Display the command
        void setCommand(std::vector<Event::types> exclude = {});

        /// @brief Set error message to enlarge the terminal
        void setEnlarge();

    //
    // Variables
    //
    private:
        /// @brief The minimal width of the window
        const int MIN_WIDTH = 85;

        /// @brief The minimal height of the window
        const int MIN_HEIGHT = 40;



        /// @brief The username of the player
        std::string _username;

        /// @brief The path to the graphical library loaded
        std::string _libpath;

        /// @brief The path to the game loaded
        std::string _gamepath;


        /// @brief The gui loader of the arcade
        std::vector<std::unique_ptr<DLLoader<IDisplay>>> _guiLoader;

        /// @brief The game loader of the arcade
        std::vector<std::unique_ptr<DLLoader<IGame>>> _gameLoader;



        /// @brief The gui loaded in the arcade
        std::unique_ptr<IDisplay> _gui;

        /// @brief The game loaded in the arcade
        std::unique_ptr<IGame> _game;


        /// @brief List of display texts in the arcade
        std::vector<Text> _texts;

        /// @brief List of display assets in the arcade
        std::vector<Asset> _assets;


        /// @brief The game loaded in the arcade is playing
        bool _isPlaying;

        /// @brief The arcade is running
        bool _arcadeRunning;

        size_t _sc;
        Score _score;

        /// @brief List of all commands possible
        const std::map<Event::types, std::function<void()>> CMD = {
            {Event::types::F2, [this](){this->cmdNextLib();}},
            {Event::types::F3, [this](){this->cmdNextGame();}},
            {Event::types::F4, [this](){this->cmdQuit();}},
            {Event::types::F5, [this](){this->cmdRestart();}},
            {Event::types::F6, [this](){this->cmdMenu();}},
            {Event::types::QUIT, [this](){this->cmdQuit();}}
        };

        /// @brief List of all GUI possible
        const std::vector<std::string> GUI_L = {
            "lib/arcade_ncurses.so",
            "lib/arcade_sdl2.so",
            "lib/arcade_ndk++.so",
            "lib/arcade_aalib.so",
            "lib/arcade_libcaca.so",
            "lib/arcade_allegro5.so",
            "lib/arcade_xlib.so",
            "lib/arcade_gtk+.so",
            "lib/arcade_sfml.so",
            "lib/arcade_irrlicht.so",
            "lib/arcade_opengl.so",
            "lib/arcade_vulkan.so",
            "lib/arcade_qt5.so"
        };

        /// @brief List of all games possible
        const std::vector<std::string> GAME_L = {
            "lib/arcade_pacman.so",
            "lib/arcade_snake.so",
            "lib/arcade_nibbler.so",
            "lib/arcade_centipede.so",
            "lib/arcade_solarfox.so",
            "lib/arcade_sokoban.so"
        };

        /// @brief indicate to the user to enlarge the window
        const std::string ENLARGE = "Please enlarge the window.";

        /// @brief List of all commands possible
        const std::map<Event::types, std::string> CMD_TITLE = {
            {Event::F2, "F2: next graphical library"},
            {Event::F3, "F3: next game"},
            {Event::F4, "F4: quit"},
            {Event::F5, "F5: restart the game"},
            {Event::F6, "F6: back to the menu"}
        };

    public:
        /// @brief The exit success code
        static const int ARCADE_EXIT_SUCCESS = 0;
        /// @brief The exit failure code
        static const int ARCADE_EXIT_FAILURE = 84;

};

#endif /* !ARCADE_HPP_ */
