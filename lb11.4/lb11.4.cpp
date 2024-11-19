#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

// ������� �������� �� ��������� min/max
#define NOMINMAX
#include <windows.h>

// ������� ��� ������������ ��������� ������
static void setupConsole() {
    SetConsoleCP(1251);         // ��� �������� ��������
    SetConsoleOutputCP(1251);   // ��� ��������� ��������
    std::ios_base::sync_with_stdio(false); // ������ ������������ C I/O � C++ streams
}

void displayMenu();
void processTriangles(const std::string& inputFileName, const std::string& outputFileName);
std::string determineTriangleType(double a, double b, double c);
double calculateDistance(double x1, double y1, double x2, double y2);
bool isValidFile(const std::string& fileName);

int main() {
    setupConsole(); // ������������ ������ ��� ������ � ���������

    std::string inputFileName, outputFileName;

    std::cout << "������ ��'� �������� �����: ";
    std::cin >> inputFileName;
    if (!isValidFile(inputFileName)) {
        std::cerr << "�������: ��������� ������� ������� ����.\n";
        return 1;
    }

    std::cout << "������ ��'� ��������� �����: ";
    std::cin >> outputFileName;

    int choice;
    do {
        displayMenu();
        std::cout << "��� ����: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 2) {
            std::cerr << "�������: ������ ��������� ����� � ����.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            processTriangles(inputFileName, outputFileName);
            break;
        case 2:
            std::cout << "���������� ��������.\n";
            break;
        default:
            std::cerr << "������������ ����.\n";
            break;
        }
    } while (choice != 2);

    return 0;
}

void displayMenu() {
    std::cout << "\n����:\n";
    std::cout << "1. �������� ����������\n";
    std::cout << "2. �����\n";
}

void processTriangles(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "�������: �� ������� ������� ������� ����.\n";
        return;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "�������: �� ������� ������� �������� ����.\n";
        inputFile.close();
        return;
    }

    double x1, y1, x2, y2, x3, y3;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
            outputFile << "����������� �����: " << line << '\n';
            continue;
        }

        // ���������� ������ �����
        double a = calculateDistance(x1, y1, x2, y2);
        double b = calculateDistance(x2, y2, x3, y3);
        double c = calculateDistance(x3, y3, x1, y1);

        // ���������� ���� ����������
        std::string triangleType = determineTriangleType(a, b, c);

        // ����� ���������� � �������� ����
        outputFile << line << " -> " << triangleType << '\n';
    }

    std::cout << "������� ���������. ���������� ��������� � ����: " << outputFileName << '\n';

    inputFile.close();
    outputFile.close();
}

std::string determineTriangleType(double a, double b, double c) {
    // �������� �� ��������� ����������
    if (a + b <= c || a + c <= b || b + c <= a) {
        return "�� � �����������";
    }

    // �������� ���� ����������
    if (std::fabs(a * a + b * b - c * c) < 1e-9 ||
        std::fabs(a * a + c * c - b * b) < 1e-9 ||
        std::fabs(b * b + c * c - a * a) < 1e-9) {
        return "�����������";
    }

    if (std::fabs(a - b) < 1e-9 && std::fabs(b - c) < 1e-9) {
        return "������������";
    }

    if (std::fabs(a - b) < 1e-9 || std::fabs(b - c) < 1e-9 || std::fabs(a - c) < 1e-9) {
        return "������������";
    }

    return "������������";
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool isValidFile(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}
