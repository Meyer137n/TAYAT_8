#pragma once
#include "Defines.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Scaner
{
private:
    std::string text; // Исходный текст
    size_t uk;        // Указатель текущей позиции в исходном тексте

public:
    void PutUK(size_t uk);                                              // Установить указатель текущей позиции в исходном тексте
    size_t GetUK();                                                     // Получить указатель текущей позиции в исходном тексте
    void PrintError(const std::string &error, const std::string &text); // Вывод ошибки
    int UseScaner(type_lex lex);                                        // Логика работы сканера
    void GetData(const std::string &filename);                          // Получение информации из файла
    Scaner(const std::string &filename);
    std::vector<int> lineBreakPositions;
};