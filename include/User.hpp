/*
** EPITECH PROJECT, 2024
** Working
** File description:
** User
*/

#ifndef USER_HPP_
    #define USER_HPP_
    #include <string>

class User {
    public:
        User() = default;
        User(const std::string &username, const size_t &score) : _username(username), _score(score) {}
        ~User() = default;

        std::string getUsername() const { return _username; }
        size_t getScore() const { return _score; }

    private:
        std::string _username;
        size_t _score;
};

#endif /* !USER_HPP_ */
