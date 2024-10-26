/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-esteban.marques
** File description:
** Score
*/

#ifndef SCORE_HPP_
    #define SCORE_HPP_
    #include <map>
    #include <vector>
    #include <string>
    #include "User.hpp"

class Score {
    public:
        Score();
        ~Score();

        void setScore(const std::string &game, User user);
        void saveScore();
    
        std::map<std::string, std::vector<User>> _scores;
    private:
        const std::string SCORE_PATH = "scores_arcade.log";

        bool restoreScore();
        void sortScore(const std::string &game);
        bool isDeletedChar(const char c, const std::string &deleted) const;
        std::vector<std::string> split(const std::string &str, const std::string &deleted) const;
};

#endif /* !SCORE_HPP_ */
