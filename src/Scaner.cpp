#include "Scaner.h"

/**
* Список допустимых ключевых слов в программе
*/
type_lex keyword[maxKeyword] =
{
    "int", "short", "long", "main", "return", "for", "const"
};

/**
* Список идентификаторов, которые соответствуют допустимым ключевым словам в программе
*/
int indexKeyword[maxKeyword] =
{
    typeInt, typeShort, typeLong, typeMain, typeReturn, typeFor, typeConst
};

//Ошибка если файл пустой
void Scaner::PutUK(size_t uk) 
{
    if (uk < text.size()) 
    {
        this->uk = uk;
    }
    else if(text.size() != 0)
    {
        std::cerr << "Ошибка: индекс выходит за пределы размера текста." << std::endl;
        exit(1);
    }
}

size_t Scaner::GetUK()
{
    return uk;
}

void Scaner::GetData(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        text = buffer.str(); // Сохраняем текст из файла
        text += '\n';

        // Определяем позиции перевода строки
        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == '\n') {
                lineBreakPositions.push_back(i);
            }
        }

        std::cout << "Текст программы:" << std::endl << text << std::endl;
        std::cout << std::endl << "Результат работы сканера:" << std::endl;
    }
    else
    {
        PrintError("Ошибка открытия файла.", filename);
    }
}

void Scaner::PrintError(const std::string& error, const std::string& lexeme)
{
    int line = 1;
    int pos = uk;

    for (size_t i = 0; i < lineBreakPositions.size(); ++i) {
        if (lineBreakPositions[i] < uk) {
            line++;
        }
        else {
            pos = uk - (i == 0 ? 0 : lineBreakPositions[i - 1] + 1);
            break;
        }
    }

    std::cout << "Error: " << "строка " << line << ", " << error;
    if (!lexeme.empty())
    {
        std::cout << "найдено: " << lexeme<<"\n\n";
    }
    exit(1);
}

int Scaner::UseScaner(type_lex lex)
{
    int i = 0;
    lex[0] = '\0';

    while (true)
    {
        // Пропускаем пробелы
        while (uk < text.size() && (text[uk] == ' ' || text[uk] == '\t' || text[uk] == '\n'))
        {
            uk++;
        }

        // Конец программы 
        if (uk >= text.size())
        {
            lex[i] = '\0';
            return typeEnd;
        }

        // Обработка комментариев
        if (text[uk] == '/')
        {
            uk++;
            if (uk < text.size() && text[uk] == '/')
            {
                while (uk < text.size() && text[uk] != '\n')
                {
                    uk++;
                }
                continue;
            }
            else
            {
                // Деление
                lex[i++] = '/';
                lex[i++] = '\0';
                return typeDiv;
            }
        }

        // Обработка чисел
        if (isdigit(text[uk]))
        {
            if (text[uk] == '0')
            {
                lex[i++] = text[uk++];

                if (text[uk] == 'x')
                {
                    lex[i++] = text[uk++];
                    while (uk < text.size() && (isdigit(text[uk]) || (text[uk]>= 'A' && text[uk] <= 'F') || (text[uk] >= 'a' && text[uk] <= 'f')) && i < maxHexNumber - 1)
                    {
                        lex[i++] = text[uk++];
                    }
                    
                    if (i == maxHexNumber - 1 && uk < text.size() && ( isdigit(text[uk]) || (text[uk] >= 'A' && text[uk] <= 'F') || (text[uk] >= 'a' && text[uk] <= 'f')))
                    {
                        while (uk < text.size() && (isdigit(text[uk]) || (text[uk] >= 'A' && text[uk] <= 'F') || (text[uk] >= 'a' && text[uk] <= 'f')))
                        {
                            lex[i++] = text[uk++];
                        }
                        if (uk < text.size() && text[uk] == 'L')
                        {
                            lex[i++] = text[uk++];
                        }
                        lex[i] = '\0';
                        PrintError("Константа превышает максимальную длину, максимум 7 цифр: ", lex);
                        return typeError;
                    }

                    if (uk < text.size() && text[uk] == 'L')
                    {
                        lex[i++] = text[uk++];
                        lex[i] = '\0';
                        return typeConstLongHex;
                    }

                    lex[i] = '\0';
                    return typeConstHex;
                }
            }

            while (uk < text.size() && isdigit(text[uk]) && i < maxNumber - 1)
            {
                lex[i++] = text[uk++];
            }

            if (i == maxNumber - 1 && uk < text.size() && isdigit(text[uk]))
            {
                while (uk < text.size() && isdigit(text[uk]))
                {
                    lex[i++] = text[uk++];
                }
                if (uk < text.size() && text[uk] == 'L')
                {
                    lex[i++] = text[uk++];
                }
                lex[i] = '\0';
                PrintError("Константа превышает максимальную длину, максимум 9 цифр: ", lex);
                return typeError;
            }

            if (uk < text.size() && text[uk] == 'L')
            {
                lex[i++] = text[uk++];
                lex[i] = '\0';
                return typeConstLongInt;
            }

            lex[i] = '\0';
            return typeConstInt;
        }


        // Обработка идентификаторов
        if (isalpha(text[uk]) || text[uk] == '_')
        {
            while (uk < text.size() && (isalnum(text[uk]) || text[uk] == '_') && i < maxLex - 1)
            {
                lex[i++] = text[uk++];
            }
            lex[i] = '\0';

            if (i == maxLex - 1 && (uk < text.size() && (isalnum(text[uk]) || text[uk] == '_')))
            {
                while (uk < text.size() && (isalnum(text[uk]) || text[uk] == '_'))
                {
                    uk++;
                }
                PrintError("Идентификатор превышает максимальную длину лексемы.", lex);
                return typeError;
            }

            // Проверяем, является ли идентификатор ключевым словом
            for (int j = 0; j < maxKeyword; j++)
            {
                if (strcmp(lex, keyword[j]) == 0)
                {
                    return indexKeyword[j];
                }
            }
            return typeId;
        }

        // Обработка специальных символов
        switch (text[uk])
        {
        case ',':
            uk++; lex[i++] = ','; lex[i] = '\0'; return typeComma;
        case ';':
            uk++; lex[i++] = ';'; lex[i] = '\0'; return typeSemicolon;
        case '(':
            uk++; lex[i++] = '('; lex[i] = '\0'; return typeLeftBracket;
        case ')':
            uk++; lex[i++] = ')'; lex[i] = '\0'; return typeRightBracket;
        case '{':
            uk++; lex[i++] = '{'; lex[i] = '\0'; return typeLeftBrace;
        case '}':
            uk++; lex[i++] = '}'; lex[i] = '\0'; return typeRightBrace;
        case '+':
            uk++; lex[i++] = '+'; lex[i] = '\0'; return typePlus;
        case '-':
            uk++; lex[i++] = '-'; lex[i] = '\0'; return typeMinus;
        case '*':
            uk++; lex[i++] = '*'; lex[i] = '\0'; return typeMul;
        case '%':
            uk++; lex[i++] = '%'; lex[i] = '\0'; return typeMod;
        case '=':
            uk++;
            lex[i++] = '=';
            if (uk < text.size() && text[uk] == '=')
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeEq;
            }
            else
            {
                lex[i] = '\0';
                return typeEval;
            }
        case '!':
            uk++;
            lex[i++] = '!';
            if (uk < text.size() && text[uk] == '=')
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeUnEq;
            }
            else
            {
                lex[i] = '\0';
                PrintError("Неожидаемый символ: ", lex);
                return typeError;
            }
        case '>':
            uk++;
            lex[i++] = '>';
            if (uk < text.size() && text[uk] == '=')
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeMoreOrEq;
            }
            else
            {
                lex[i] = '\0';
                return typeMore;
            }
        case '<':
            uk++;
            lex[i++] = '<';
            if (uk < text.size() && text[uk] == '=')
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeLessOrEq;
            }
            else
            {
                lex[i] = '\0';
                return typeLess;
            }
        default:
            lex[i++] = text[uk++];
            lex[i] = '\0';
            PrintError("Лексическая ошибка в строке ", lex);
            return typeError;
        }
    }
}

Scaner::Scaner(const std::string& filename)
{
    GetData(filename);
    PutUK(0);
}