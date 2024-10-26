/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_
    #include <memory>
    #include <dlfcn.h>
    #include <exception>
    #include <iostream>

class DLEncapsulation {
    public:
        static void *DlOpen(const std::string &path) { return dlopen(path.c_str(), RTLD_LAZY); }
        static void *DlSym(void *handle, const std::string &symbol) { return dlsym(handle, symbol.c_str()); }
        static void DlClose(void *handle) { dlclose(handle); }
        static std::string DlError() { return std::string(dlerror()); }
};

/// @brief Class for the DLLoader
template <typename T>
class DLLoader : public std::exception {
    public:
        /// @brief The constructor of the DLLoader class
        DLLoader() : _isValid(false) {};

        /// @brief The constructor of the DLLoader class
        /// @param dllpath The path of the dll
        DLLoader(const std::string &dllpath) : _path(dllpath)
        {
            _dll = DLEncapsulation::DlOpen(dllpath);
            if (_dll == nullptr) {
                _isValid = false;
                throw Error("impossible to open library: " + DLEncapsulation::DlError());
            } else {
                _isValid = true;
            }
        }

        /// @brief Destructor of the DLLoader class
        ~DLLoader()
        {
            if (_isValid)
                DLEncapsulation::DlClose(_dll);
        }

        
        /// @brief Get the instance of the class
        /// @param function The function to get
        /// @return The instance of the class
        std::unique_ptr<T>getInstance(const std::string &function) const
        {
            std::unique_ptr<T>(*getInstance)() = (std::unique_ptr<T>(*)())DLEncapsulation::DlSym(_dll, function);

            if (!_isValid)
                throw Error("dll not opened");
            if (getInstance == nullptr)
                throw Error("impossible to load dll: " + DLEncapsulation::DlError());
            return getInstance();
        }

        /// @brief Reload the dll
        /// @param dllpath The path of the dll
        void newLoader(const std::string &dllpath)
        {
            if (_isValid) {
                DLEncapsulation::DlClose(_dll);
            }
            _dll = DLEncapsulation::DlOpen(dllpath);
            if (_dll == nullptr) {
                _isValid = false;
                throw Error("impossible to open library: " + DLEncapsulation::DlError());
            } else {
                _isValid = true;
                _path = dllpath;
            }
        }

        /// @brief Error class for the DLLoader
        class Error: public std::exception {
            public:
                /// @brief Throw an error with a message
                /// @param message The message of the error
                Error(const std::string &message) : _message("Error: " + message + ".") {};

                /// @brief Get the error message
                /// @return const char* The error message
                const char *what() const throw() { return _message.c_str(); };
            private:
                /// @brief The error message
                std::string _message;
        };

        std::string getPath() { return _path; };
    private:
        /// @brief The dll pointer
        void *_dll;

        /// @brief The validity of the dll
        bool _isValid;

        /// @brief The path of the dll
        std::string _path;
};

#endif /* !DLLOADER_HPP_ */
