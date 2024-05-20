#include "FileIO.h"
#include "Engine.h"

FileObject arr[100];
FileObject EditorArray[100];
int object_number = 0;
int num = 0;

void FileInput(const std::filesystem::path& sprite_file) {
    if (sprite_file.extension() != ".txt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .txt file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    std::string text;
    in_file >> text;

    while (in_file.eof() == false) {
        if (text == "Number") {
            in_file >> object_number;
            arr[object_number - 1].Number = object_number;
        }
        else if (text == "Room") {
            int room_num;
            in_file >> room_num;
            arr[object_number - 1].Room = room_num;
        }
        else if (text == "Type") {
            std::string get_type;
            in_file >> get_type;
            arr[object_number - 1].Type = get_type;
        }
        else if (text == "Position") {
            double position_x, position_y, position_z;
            in_file >> position_x;
            in_file >> position_y;
            in_file >> position_z;
            arr[object_number - 1].Position = { position_x, position_y, position_z };
        }
        else if (text == "Information") {
            std::string get_information;
            in_file >> get_information;
            arr[object_number - 1].Information = get_information;
        }
        else if (text == "Size") {
            double size_x, size_y, size_z;
            in_file >> size_x;
            in_file >> size_y;
            in_file >> size_z;
            arr[object_number - 1].Size = { size_x, size_y, size_z };
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
}

void FileOutput(const std::filesystem::path& sprite_file)
{
    if(sprite_file.extension() != ".txt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .txt file");
    }
    std::ofstream out_file(sprite_file);

    if (out_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    for (int i = 0; i < 3; i++)
    {
        out_file << "Number ";
        out_file << arr[i].Number;
        out_file << '\n';
        out_file << "Room ";
        out_file << arr[i].Room;
        out_file << '\n';
        out_file << "Type ";
        out_file << arr[i].Type;
        out_file << '\n';
        out_file << "Position ";
        out_file << arr[i].Position.x;
        out_file << ' ';
        out_file << arr[i].Position.y;
        out_file << ' ';
        out_file << arr[i].Position.z;
        out_file << '\n';
        out_file << "Information ";
        out_file << arr[i].Information;
        out_file << '\n';
        out_file << "Size ";
        out_file << arr[i].Size.x;
        out_file << ' ';
        out_file << arr[i].Size.y;
        out_file << ' ';
        out_file << arr[i].Size.z;
        out_file << '\n';
    }
}

void FileOutputEditor(const std::filesystem::path& sprite_file)
{
    if (sprite_file.extension() != ".txt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .txt file");
    }
    std::ofstream out_file(sprite_file);

    if (out_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    
    for (num = 0; EditorArray[num].Number != 0; num++);
    for (int i = 0; i < num; i++)
    {
        out_file << "Number ";
        out_file << EditorArray[i].Number;
        out_file << '\n';
        out_file << "Room ";
        out_file << EditorArray[i].Room;
        out_file << '\n';
        out_file << "Type ";
        out_file << EditorArray[i].Type;
        out_file << '\n';
        out_file << "Position ";
        out_file << EditorArray[i].Position.x;
        out_file << ' ';
        out_file << EditorArray[i].Position.y;
        out_file << ' ';
        out_file << EditorArray[i].Position.z;
        out_file << '\n';
        out_file << "Information ";
        out_file << EditorArray[i].Information;
        out_file << '\n';
        out_file << "Size ";
        out_file << EditorArray[i].Size.x;
        out_file << ' ';
        out_file << EditorArray[i].Size.y;
        out_file << ' ';
        out_file << EditorArray[i].Size.z;
        out_file << '\n';
    }
    std::cout << "editor printing" << std::endl;
    std::cout << num << std::endl;
}
int GetRoom(int number)
{
    return arr[number].Room;
}
std::string GetType(int number)
{
    return arr[number].Type;
}
Math::vec3 GetPosition(int number)
{
    return arr[number].Position;
}
std::string GetInformation(int number)
{
    return arr[number].Information;
}
Math::vec3 GetSize(int number)
{
    return arr[number].Size;
}

int GetRoomEditor(int number)
{
    return EditorArray[number].Room;
}
std::string GetTypeEditor(int number)
{
    return EditorArray[number].Type;
}
Math::vec3 GetPositionEditor(int number)
{
    return EditorArray[number].Position;
}
std::string GetInformationEditor(int number)
{
    return EditorArray[number].Information;
}
Math::vec3 GetSizeEditor(int number)
{
    return EditorArray[number].Size;
}

void SetNumber(int number)
{
    EditorArray[number].Number = number+1;
    std::cout << "editor number" << std::endl;
    std::cout << number << std::endl;
}
void SetRoom(int number, int room)
{
    EditorArray[number].Room = room;
    std::cout << "editor room" << std::endl;
    std::cout << room << std::endl;
}
void SetType(int number, std::string type)
{
    EditorArray[number].Type = type;
}
void SetPosition(int number, Math::vec3 position)
{
    EditorArray[number].Position = position;
}
void SetInformation(int number, std::string information)
{
    EditorArray[number].Information = information;
}
void SetSize(int number, Math::vec3 size)
{
    EditorArray[number].Size = size;
}