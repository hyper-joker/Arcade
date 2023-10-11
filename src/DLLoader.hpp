/*
** EPITECH PROJECT, 2023
** IGameModule.h$
** File description:
** IGameModule.h$
*/

#pragma once
#include <array>
#include <string>
#include <dlfcn.h>
#include <memory>

enum LibType {
    GRAPHICAL = 0,
    GAME
};

namespace Arcade {
    template <typename T>
    class DLLoader {
    public:
        DLLoader(const std::string& filename, LibType type) {
            _handle = dlopen(filename.c_str(), RTLD_LAZY);
            if (!_handle) {
                throw std::runtime_error(dlerror());
            }
            _type = type;
            createInstance();
        }

        ~DLLoader() {
            if (_handle) {
                dlclose(_handle);
            }
        }

        T* createInstance() {
            using CreateFunc = T* (*)();
            CreateFunc createFunc = nullptr;

            if (_type == GRAPHICAL)
                createFunc = reinterpret_cast<CreateFunc>(dlsym(_handle, "entryDisplay"));
            else if (_type == GAME)
                createFunc = reinterpret_cast<CreateFunc>(dlsym(_handle, "entryGame"));
            if (!createFunc) {
                throw std::runtime_error(dlerror());
            }
            instance = createFunc();
            return instance;
        }

        T* getInstance() {
           return instance;
        }

    private:
        void* _handle = nullptr;
        T* instance = nullptr;
        LibType _type;
    };
}
