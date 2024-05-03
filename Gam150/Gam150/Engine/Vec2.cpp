/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Vec2.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:    March 20, 2024
*/

#include "Vec2.h"

bool Math::vec2::operator==(const vec2& v) {
    return  !(x + y - v.x - v.y);
    //which could be best
}

bool Math::vec2::operator!=(const vec2& v) {
    return  x + y - v.x - v.y;
}

Math::vec2 Math::vec2::operator+(const vec2& v) {
    return { x + v.x, y + v.y };
}

Math::vec2& Math::vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Math::vec2 Math::vec2::operator-(const vec2& v) {
    return { x - v.x, y - v.y };
}

Math::vec2& Math::vec2::operator-=(const vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}
//? why are we typing like this?

Math::vec2 Math::vec2::operator*(double scale) {
    return { x * scale, y * scale };
}

Math::vec2& Math::vec2::operator*=(double scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Math::vec2 Math::vec2::operator/(double scale) {
    return { x / scale, y / scale };
}
//If we have multiply I think this thing is not needed but for user it look easier

Math::vec2& Math::vec2::operator/=(double scale) {
    x /= scale;
    y /= scale;
    return *this;
}

Math::vec2 Math::operator*(double scale, const vec2& v){
    return { scale * v.x, scale * v.y };
}
//Reason why they don't need * for change address to value? (reference thing)

Math::vec2 Math::vec2::operator-() {
    return { -x, -y };
}





//integer

bool Math::ivec2::operator==(const ivec2& v) {
    return  !(x + y - v.x - v.y);
    //which could be best
}

bool Math::ivec2::operator!=(const ivec2& v) {
    return  x + y - v.x - v.y;
}

Math::ivec2 Math::ivec2::operator+(const ivec2& v) {
    return { x + v.x, y + v.y };
}

Math::ivec2& Math::ivec2::operator+=(const ivec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Math::ivec2 Math::ivec2::operator-(const ivec2& v) {
    return { x - v.x, y - v.y };
}

Math::ivec2& Math::ivec2::operator-=(const ivec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}
//? why are we typing like this?

Math::ivec2 Math::ivec2::operator*(int scale) {
    return { x * scale, y * scale };
}

Math::ivec2& Math::ivec2::operator*=(int scale) {
    x *= scale;
    y *= scale;
    return *this;
}

Math::ivec2 Math::ivec2::operator/(int scale) {
    return { x / scale, y / scale };
}
//If we have multiply I think this thing is not needed but for user it look easier

Math::ivec2& Math::ivec2::operator/=(int scale) {
    x /= scale;
    y /= scale;
    return *this;
}

Math::vec2 Math::ivec2::operator*(double scale) {
    return { x * scale, y * scale };
}

Math::vec2 Math::ivec2::operator/(double divisor) {
    return { x / divisor, y / divisor };
}

Math::ivec2 Math::ivec2::operator-(){
    return { -x, -y };
}

//this was the problem!
