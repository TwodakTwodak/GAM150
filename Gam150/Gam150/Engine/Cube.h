/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Rect.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec3.h"
#include <cmath>

namespace Math {
    struct [[nodiscard]] cube {
        Math::vec3 bottom_behind{ 0.0, 0.0, 0.0 };
        Math::vec3 top_front{ 0.0, 0.0, 0.0 };

        vec3 Size() const noexcept {
            return {
                //using abs beacuse of flip (use scale -1!)
                //Dont need to think about rotation part!
                //Beacuse we will not rotate cube while playing game!
                top_front.x - bottom_behind.x,
                top_front.y - bottom_behind.y,
                top_front.z - bottom_behind.z
            };
        }
    };
}