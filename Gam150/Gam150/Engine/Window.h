/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <raylib.h>
#include "Vec2.h"
#include <rlgl.h>

namespace CS230 {
    class Window {
    public:
        void Start(std::string title);
        void Update();
        bool IsClosed() const;
        Math::ivec2 GetSize() const;
        void Clear(unsigned int color);

    private:
        Math::ivec2 size;
        //It is a problem of sequence of main code it update after calling window! 
        //So i should use deligate?
        //But this window class do not have any constructor!
        //Or change the sequnce inside of Engine update?
        // 
        //Or push default at the Start() function? this seems most good!
        static constexpr unsigned int default_background = UINT_MAX;
        static constexpr int default_width = 800;
        static constexpr int default_height = 600;
    };
}


#endif