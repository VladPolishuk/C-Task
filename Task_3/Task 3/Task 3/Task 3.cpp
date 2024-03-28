#include <iostream>
#include <string>
#include <fstream>

struct BMPheader {
    uint16_t bfType;         // 0x4d42 | 0x4349 | 0x5450
    int32_t  bfSize;         // размер файла
    int32_t  bfReserved;     // 0
    int32_t  bfOffBits;      // смещение до поля данных,
    int32_t  biSize;         // размер структуры в байтах:
    int32_t  biWidth;        // ширина в точках
    int32_t  biHeight;       // высота в точках
    uint16_t biPlanes;       // всегда должно быть 1
    uint16_t biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
    int32_t  biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
    int32_t  biSizeImage;    // Количество байт в поле данных
    int32_t  biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
    int32_t  biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
    int32_t  biClrUsed;      // Количество используемых цветов
    int32_t  biClrImportant; // Количество существенных цветов.
};

int main()
{
    setlocale(LC_ALL, "rus");

    std::string fileInput;
    std::string fileOutput;

    std::cout << "Введите путь к файлу, который нужно считать: ";
    std::getline(std::cin, fileInput);
    std::cout << "Введите путь к файлу, в который нужно записать: ";
    std::getline(std::cin, fileOutput);

    std::ifstream inputFile("C:\\Users\\Vlad\\Desktop\\Task_3\\Task 3\\x64\\Debug\\" + fileInput + ".bmp", std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cout << "Ошибка! Не удалось прочитать BMP-файл";
        return -1;
    }

    BMPheader bmpheader;
    inputFile.read(reinterpret_cast<char*>(&bmpheader), sizeof(BMPheader));

    std::ofstream outputFile("C:\\Users\\Vlad\\Desktop\\Task_3\\Task 3\\x64\\Debug\\" + fileOutput + ".txt");

    if (!outputFile.is_open()) {
        std::cout << "Ошибка! Не удалось создать или записать в TXT-файл";
        return 1;
    }

    outputFile << "Размер файла " << bmpheader.biSize << std::endl;
    outputFile << "Ширина изображения: " << bmpheader.biWidth << std::endl;
    outputFile << "Высота изображения: " << bmpheader.biHeight << std::endl;
    outputFile << "Количество цветов: " << bmpheader.biClrUsed << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
