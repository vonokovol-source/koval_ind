#include <iostream>
#include <vector>
#include <stdexcept>
#include <numeric>
#include <locale>

/// <summary>
/// Устанавливает русскую локаль для корректного отображения сообщений в консоли.
/// </summary>
void setRussianLocale() {
    setlocale(LC_ALL, "Russian");
}

/// <summary>
/// Модуль ввода данных о посещаемости офиса за 31 день.
/// </summary>
class InputHandler {
public:
    /// <summary>
    /// Считывает 31 целое число, каждое из которых показывает количество сотрудников,
    /// пришедших в офис в соответствующий день месяца.
    /// </summary>
    /// <returns>Массив attendance из 31 значения.</returns>
    static std::vector<int> getAttendance() {
        std::vector<int> attendance;
        attendance.reserve(31);

        for (int i = 0; i < 31; ++i) {
            int value;
            std::cin >> value;
            attendance.push_back(value);
        }

        return attendance;
    }
};

/// <summary>
/// Модуль проверки входных данных.
/// </summary>
class DataValidator {
public:
    /// <summary>
    /// Проверяет, что массив содержит 31 неотрицательное значение.
    /// </summary>
    /// <param name="attendance">Массив посещаемости.</param>
    /// <exception cref="std::invalid_argument">Выбрасывается при некорректных данных.</exception>
    static void validateAttendance(const std::vector<int>& attendance) {
        if (attendance.size() != 31) {
            throw std::invalid_argument("Ошибка: необходимо ввести ровно 31 число");
        }

        for (size_t i = 0; i < attendance.size(); ++i) {
            if (attendance[i] < 0) {
                throw std::invalid_argument("Ошибка: количество сотрудников не может быть отрицательным");
            }
        }
    }
};

/// <summary>
/// Модуль подсчёта общей суммы посещений офиса за месяц.
/// </summary>
class AttendanceCalculator {
public:
    /// <summary>
    /// Вычисляет сумму всех значений посещаемости.
    /// </summary>
    /// <param name="attendance">Массив посещаемости за 31 день.</param>
    /// <returns>Общее количество выходов сотрудников на работу за месяц.</returns>
    static int calculateTotalAttendance(const std::vector<int>& attendance) {
        int total = 0;
        for (int value : attendance) {
            total += value;
        }
        return total;
    }
};

/// <summary>
/// Модуль вычисления общего количества сотрудников офиса.
/// </summary>
class EmployeeCalculator {
public:
    /// <summary>
    /// Определяет количество сотрудников по формуле: сумма посещений / 27.
    /// </summary>
    /// <param name="totalAttendance">Общее количество посещений офиса за месяц.</param>
    /// <returns>Количество сотрудников офиса.</returns>
    static int calculateEmployees(int totalAttendance) {
        return totalAttendance / 27;
    }
};

/// <summary>
/// Модуль вывода результата пользователю.
/// </summary>
class ResultPresenter {
public:
    /// <summary>
    /// Выводит количество сотрудников офиса.
    /// </summary>
    /// <param name="employees">Количество сотрудников.</param>
    static void printResult(int employees) {
        std::cout << employees << std::endl;
    }
};

/// <summary>
/// Главная функция программы.
/// </summary>
/// <returns>0 при успешном выполнении, 1 при ошибке.</returns>
int main() {
    setRussianLocale();

    try {
        std::vector<int> attendance = InputHandler::getAttendance();
        DataValidator::validateAttendance(attendance);

        int totalAttendance = AttendanceCalculator::calculateTotalAttendance(attendance);
        int employees = EmployeeCalculator::calculateEmployees(totalAttendance);

        ResultPresenter::printResult(employees);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
