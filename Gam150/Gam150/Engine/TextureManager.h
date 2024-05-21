/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.h
Project:    




Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Texture.h"
#include <filesystem>
#include <map>

namespace Gam150 {
    class Texture;

    class TextureManager {
    public:
        Texture* Load(const std::filesystem::path& file_name);
        void Unload();

        void StartRenderTextureMode(int width, int height);
        Texture* EndRenderTextureMode();

    private:
        std::map<std::filesystem::path, Texture*> textures;
        std::vector<Texture*> rendered_textures;
    };
}


