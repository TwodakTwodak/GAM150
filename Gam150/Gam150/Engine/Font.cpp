/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.h
Project:    


Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Font.h"
#include "Engine.h"

Gam150::Font::Font(const std::filesystem::path& file_name) : texture(file_name) {
    const unsigned int white = 0xFFFFFFFF;

    original_image = LoadImage(file_name.string().c_str());

    //The top left pixel MUST be white (0xFFFFFFFF)
    unsigned int color = GetPixel({ 0, 0 });
    if (color == white) {
        FindCharRects();
    }
    else {
        Engine::GetLogger().LogError("Font " + file_name.string() + " could not be loaded");
        return;
    }
    UnloadImage(original_image);
}

void Gam150::Font::FindCharRects() {
    unsigned int check_color = GetPixel({ 0, 0 });
    unsigned int next_color;

    int height = texture.GetSize().y;

    int x = 1;
    for (int index = 0; index < num_chars; index++) {
        int width = 0;

        do {
            width++;
            next_color = GetPixel({ x + width, 0 });
        } while (check_color == next_color);

        check_color = next_color;

        char_rects[index].top_right = { x + width - 1, 1 };
        char_rects[index].bottom_left = { x, char_rects[index].top_right.y + height - 1 };
        x += width;
    }
}

Math::irect& Gam150::Font::GetCharRect(char c) {
    if (c >= ' ' && c <= 'z') {
        return char_rects[c - ' '];
    }
    else {
        Engine::GetLogger().LogError("Char '" + std::to_string(c) + "' not found");
        return char_rects[0];
    }
}

Math::ivec2 Gam150::Font::MeasureText(std::string text)
{
    Math::ivec2 total_size = { 0, original_image.height};
    for (char c : text) {
        total_size.x += GetCharRect(c).Size().x;
    }
    return total_size;
}

void Gam150::Font::DrawChar(Math::TransformationMatrix& matrix, char c, unsigned int color) {
    const Math::irect& display_rect = GetCharRect(c);
    const Math::ivec2 top_left_texel = { display_rect.bottom_left.x, display_rect.top_right.y };
    if (c != ' ') {
        const auto to_center = Math::TranslationMatrix(Math::vec2(-display_rect.Size().x / 2.0, -display_rect.Size().y / 2.0));
        const auto flip = Math::ScaleMatrix(Math::vec2{ 1, -1 });
        const auto to_bottomleft = Math::TranslationMatrix(Math::vec2(display_rect.Size().x / 2.0, display_rect.Size().y / 2.0));
        const auto flip_quad = to_bottomleft * flip * to_center;
        texture.Draw(matrix * flip_quad, top_left_texel, display_rect.Size(), color);
    }
    matrix *= Math::TranslationMatrix(Math::ivec2{ display_rect.Size().x, 0 });
}

unsigned int Gam150::Font::GetPixel(Math::ivec2 texel)
{
    return ColorToInt(GetImageColor(original_image, texel.x, texel.y));
}
//?????

Gam150::Texture* Gam150::Font::PrintToTexture(const std::string& text, unsigned int color) {
    const Math::ivec2 text_size = MeasureText(text);
    auto& texture_manager = Engine::GetTextureManager();
    texture_manager.StartRenderTextureMode(text_size.x, text_size.y);
    Math::TransformationMatrix matrix;
    for (const char c : text) {
        DrawChar(matrix, c, color);
    }
    return texture_manager.EndRenderTextureMode();
}
