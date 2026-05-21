#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

class DataValidator {
public:
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

class AttendanceCalculator {
public:
    static int calculateTotalAttendance(const std::vector<int>& attendance) {
        int total = 0;
        for (int value : attendance) {
            total += value;
        }
        return total;
    }
};

class EmployeeCalculator {
public:
    static int calculateEmployees(int totalAttendance) {
        return totalAttendance / 27;
    }
};

void ValidAttendanceTest()
{
    std::vector<int> attendance(31, 10);
    DataValidator::validateAttendance(attendance);
}

void NegativeValueTest()
{
    std::vector<int> attendance(31, 10);
    attendance[5] = -1;

    try {
        DataValidator::validateAttendance(attendance);
        assert(false);
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }
}

void WrongSizeTest()
{
    std::vector<int> attendance(30, 10);

    try {
        DataValidator::validateAttendance(attendance);
        assert(false);
    }
    catch (const std::invalid_argument&) {
        assert(true);
    }
}

void CalculateTotalAttendanceTest()
{
    std::vector<int> attendance = {
        10,10,10,10,10,10,10,10,10,10,
        10,10,10,10,10,10,10,10,10,10,
        10,10,10,10,10,10,10,0,0,0,0
    };

    int result = AttendanceCalculator::calculateTotalAttendance(attendance);
    assert(result == 270);
}

void ZeroValuesTest()
{
    std::vector<int> attendance(31, 0);
    int result = AttendanceCalculator::calculateTotalAttendance(attendance);
    assert(result == 0);
}

void CalculateEmployeesTest()
{
    assert(EmployeeCalculator::calculateEmployees(270) == 10);
    assert(EmployeeCalculator::calculateEmployees(27) == 1);
    assert(EmployeeCalculator::calculateEmployees(2700) == 100);
}

int main()
{
    setlocale(LC_ALL, "ru");
    ValidAttendanceTest();
    NegativeValueTest();
    WrongSizeTest();
    CalculateTotalAttendanceTest();
    ZeroValuesTest();
    CalculateEmployeesTest();

    std::cout << "Все тесты успешно пройдены!" << std::endl;

    return 0;
}