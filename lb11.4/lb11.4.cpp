#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

// Уникаємо конфліктів із макросами min/max
#define NOMINMAX
#include <windows.h>

// Функція для налаштування кодування консолі
static void setupConsole() {
    SetConsoleCP(1251);         // Для введення кирилиці
    SetConsoleOutputCP(1251);   // Для виведення кирилиці
    std::ios_base::sync_with_stdio(false); // Вимикає синхронізацію C I/O з C++ streams
}

void displayMenu();
void processTriangles(const std::string& inputFileName, const std::string& outputFileName);
std::string determineTriangleType(double a, double b, double c);
double calculateDistance(double x1, double y1, double x2, double y2);
bool isValidFile(const std::string& fileName);

int main() {
    setupConsole(); // Налаштування консолі для роботи з кирилицею

    std::string inputFileName, outputFileName;

    std::cout << "Введіть ім'я вхідного файлу: ";
    std::cin >> inputFileName;
    if (!isValidFile(inputFileName)) {
        std::cerr << "Помилка: неможливо відкрити вхідний файл.\n";
        return 1;
    }

    std::cout << "Введіть ім'я вихідного файлу: ";
    std::cin >> outputFileName;

    int choice;
    do {
        displayMenu();
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 2) {
            std::cerr << "Помилка: введіть коректний номер з меню.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            processTriangles(inputFileName, outputFileName);
            break;
        case 2:
            std::cout << "Завершення програми.\n";
            break;
        default:
            std::cerr << "Неправильний вибір.\n";
            break;
        }
    } while (choice != 2);

    return 0;
}

void displayMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Обробити трикутники\n";
    std::cout << "2. Вийти\n";
}

void processTriangles(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Помилка: не вдалося відкрити вхідний файл.\n";
        return;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "Помилка: не вдалося відкрити вихідний файл.\n";
        inputFile.close();
        return;
    }

    double x1, y1, x2, y2, x3, y3;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
            outputFile << "Некоректний рядок: " << line << '\n';
            continue;
        }

        // Обчислення довжин сторін
        double a = calculateDistance(x1, y1, x2, y2);
        double b = calculateDistance(x2, y2, x3, y3);
        double c = calculateDistance(x3, y3, x1, y1);

        // Визначення типу трикутника
        std::string triangleType = determineTriangleType(a, b, c);

        // Запис результату у вихідний файл
        outputFile << line << " -> " << triangleType << '\n';
    }

    std::cout << "Обробка завершена. Результати збережено у файлі: " << outputFileName << '\n';

    inputFile.close();
    outputFile.close();
}

std::string determineTriangleType(double a, double b, double c) {
    // Перевірка на існування трикутника
    if (a + b <= c || a + c <= b || b + c <= a) {
        return "не є трикутником";
    }

    // Перевірка типу трикутника
    if (std::fabs(a * a + b * b - c * c) < 1e-9 ||
        std::fabs(a * a + c * c - b * b) < 1e-9 ||
        std::fabs(b * b + c * c - a * a) < 1e-9) {
        return "прямокутний";
    }

    if (std::fabs(a - b) < 1e-9 && std::fabs(b - c) < 1e-9) {
        return "рівносторонній";
    }

    if (std::fabs(a - b) < 1e-9 || std::fabs(b - c) < 1e-9 || std::fabs(a - c) < 1e-9) {
        return "рівнобедрений";
    }

    return "різносторонній";
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool isValidFile(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}
