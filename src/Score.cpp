/*
** EPITECH PROJECT, 2024
** Working
** File description:
** Score
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include "Score.hpp"

Score::Score()
{
    if (!restoreScore())
        _scores.clear();
}

Score::~Score()
{
}

void Score::sortScore(const std::string &game)
{
    std::sort(_scores[game].begin(), _scores[game].end(), [](const User &a, const User &b) {
        return a.getScore() > b.getScore();
    });
    if (_scores[game].size() > 10)
        _scores[game].resize(10);
}

void Score::setScore(const std::string &pathGame, User user)
{
    if (user.getScore() == 0)
        return;
    if (_scores.find(pathGame) == _scores.end()) {
        _scores[pathGame] = std::vector<User>();
    }
    _scores[pathGame].push_back(user);
    sortScore(pathGame);
}

void Score::saveScore()
{
    std::ofstream file(SCORE_PATH);

    if (file.is_open()) {
        for (auto &score : _scores) {
            file << score.first << std::endl;
            for (auto &user : score.second) {
                file << user.getUsername() << " " << user.getScore() << std::endl;
            }
        }
        file.close();
    }
}

bool Score::restoreScore() {
    std::ifstream file(SCORE_PATH);

    if (file.is_open()) {
        std::string line;
        std::string game;

        while (std::getline(file, line)) {
            if (line.empty())
                continue;
            auto line_s = split(line, " ");
            if (line_s.size() == 1) {
                game = line_s[0];
                continue;
            }
            if (line_s.size() != 2)
                continue;
            
            try {
                setScore(game, User(line_s[0], std::stoi(line_s[1])));
            } catch (std::exception &e) {
                continue;
            }
        }
        file.close();
        for (auto &game : _scores) {
            sortScore(game.first);
        }
        return true;
    }
    return false;
}

bool Score::isDeletedChar(const char c, const std::string &deleted) const
{
    for (size_t i = 0; deleted[i]; ++i)
        if (deleted[i] == c)
            return true;
    return false;
}

std::vector<std::string> Score::split(const std::string &str, const std::string &deleted) const
{
    std::vector<std::string> res;
    std::string buf;

    for (size_t i = 0; i < str.size(); ++i) {
        for (; i < str.size() && isDeletedChar(str[i], deleted); ++i);
        for (; i < str.size() && !isDeletedChar(str[i], deleted); ++i)
            buf += str[i];
        if (!buf.empty()) {
            res.push_back(buf);
            buf.clear();
        }
    }
    return res;
}
