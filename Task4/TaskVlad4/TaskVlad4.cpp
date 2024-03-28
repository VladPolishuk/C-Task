#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <codecvt>
#include <locale>
#include <Windows.h>

using namespace std;

#pragma pack(push, 1)
typedef struct
{
    int ID;
    string name;
    string description;
    int hall;
} Museum;
#pragma pack(pop)


void addMuseum(string fileInput, Museum museum)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");
    setlocale(LC_ALL, "rus UTF-8");
    cin.ignore();

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
    int maxID = 0;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string idStr;
        getline(iss, idStr, '|');
        int id = stoi(idStr);
        if (id > maxID) {
            maxID = id;
        }
    }
    inputFile.close();

    museum.ID = maxID + 1;

    cout << "Введите название экспонента: ";
    getline(cin, museum.name);
    cout << "Введите описание экспонента: ";
    cin >> museum.description;
    cout << "Введите зала где находится экспонент: ";
    cin >> museum.hall;

    ofstream outputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt", ios::app);

    if (!outputFile) {
        cout << "Ошибка! Мы не смогли прочитать TXT файл";
        return;
    }
    else {
        outputFile << museum.ID << '|' << museum.name << '|'
            << museum.description << '|'
            << museum.hall << endl;
        cout << "В музей добавлен" << endl;
        outputFile.close();
    }
}

void listMuseum(string fileInput, Museum museum)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");
    setlocale(LC_ALL, "rus UTF-8");

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);

        getline(iss, line, '|');
        museum.ID = stoi(line);
        getline(iss, museum.name, '|');
        getline(iss, museum.description, '|');
        iss >> museum.hall;
        iss.ignore();

        cout << "ID: " << museum.ID << endl;
        cout << "Название: " << museum.name << endl;
        cout << "Описание: " << museum.description << endl;
        cout << "Залл " << museum.hall << endl;
        cout << "-------------------------" << endl;
    }

    inputFile.close();
}


void filterMuseum(string fileInput, Museum museum)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");
    setlocale(LC_ALL, "rus UTF-8");

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    int filterHall;
    cout << "Выбирите залл: ";
    cin >> filterHall;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);

        getline(iss, line, '|');
        museum.ID = stoi(line);
        getline(iss, museum.name, '|');
        getline(iss, museum.description, '|');
        iss >> museum.hall;
        iss.ignore();

        if (museum.hall == filterHall) {
            cout << "ID: " << museum.ID << endl;
            cout << "Название: " << museum.name << endl;
            cout << "Описание: " << museum.description << endl;
            cout << "Залл " << museum.hall << endl;
            cout << "-------------------------" << endl;
        }
    }

    inputFile.close();
}

void deleteMuseum(string fileInput, Museum museum) {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");

    locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка! Не удалось открыть файл." << endl;
        return;
    }

    int museumIDToDelete;
    cout << "Введите ID экспоната, которого хотите удалить: ";
    cin >> museumIDToDelete;
    cin.ignore();

    ofstream tempFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\temp.txt");

    if (!tempFile.is_open()) {
        cout << "Ошибка! Не удалось создать временный файл." << endl;
        inputFile.close();
        return;
    }

    bool museumFound = false;
    int currentID = 1;

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string idStr;
        getline(iss, idStr, '|');
        int id = stoi(idStr);

        if (id == museumIDToDelete) {
            museumFound = true;
            cout << "Студент с ID " << museumIDToDelete << " удален." << endl;
        }
        else {
            string updatedLine = to_string(currentID) + line.substr(idStr.length());
            tempFile << updatedLine << endl;
            currentID++;
        }
    }

    inputFile.close();
    tempFile.close();

    if (!museumFound) {
        cout << "Студент с ID " << museumIDToDelete << " не найден." << endl;
    }
    else {
        ofstream outputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
        ifstream tempFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\temp.txt");

        if (!outputFile.is_open() || !tempFile.is_open()) {
            cout << "Ошибка! Не удалось открыть файлы для записи." << endl;
            return;
        }

        while (getline(tempFile, line)) {
            outputFile << line << endl;
        }

        tempFile.close();
        outputFile.close();
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    setlocale(LC_CTYPE, "Russian");

    string fileInput;

    cout << "Напишите путь к файлу с которго нужно считать это: ";
    getline(cin, fileInput);

    ifstream inputFile("C:\\Users\\ASUS\\Desktop\\Таск\\C++\\TaskVlad4\\x64\\Debug\\" + fileInput + ".txt");
    if (!inputFile.is_open())
    {
        cout << "Ошибка! Мы не смогли прочитать txt";
        return -1;
    }

    Museum museum;

    cout << "-------Программа музей-------" << endl;
    int choise;
    while (true)
    {
        cout << "Выбирите фукцию которую хотите использовать" << endl;
        cout << "1. Вывести список всех экспонатов" << endl;
        cout << "2. Вывести список экспонатов в определенном зале" << endl;
        cout << "3. Добавить новый экспонат" << endl;
        cout << "4. Завершить программу" << endl;
        cout << "5. Завершить программу" << endl;
        cin >> choise;

        switch (choise)
        {
        case 1:
            listMuseum(fileInput, museum);
            break;
        case 2:
            filterMuseum(fileInput, museum);
            break;
        case 3:
            addMuseum(fileInput, museum);
            break;
        case 4:
            deleteMuseum(fileInput, museum);
            break;
        case 5:
            return 0;
        default:
            cout << "Ошибка вода попробуйте еще раз" << endl;
        }
    }
    return 0;
}