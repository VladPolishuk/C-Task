#include <iostream>
#include <string>

using namespace std;

class TeamLead;

class Employee {
public:
    virtual void work() const = 0;
    virtual ~Employee() {}
    friend class TeamLead;
};

class Manager : public Employee {
public:
    void work() const override {
        cout << "Менеджер управляет командой и координирует работу." << endl;
    }
};

class Administrator : public Employee {
public:
    void work() const override {
        cout << "Администратор ведёт документацию и обеспечивает офисные процессы." << endl;
    }
};

class Programmer : public Employee {
public:
    void work() const override {
        cout << "Программист пишет программное обеспечение и занимается разработкой." << endl;
    }
};

class TeamLead {
public:
    void manageEmployee(const Employee& emp) const {
        cout << "TeamLead имеет доступ к работе сотрудника." << endl;
        emp.work();
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    Manager manager;
    Administrator admin;
    Programmer programmer;

    cout << "Работа менеджера: ";
    manager.work();

    cout << "Работа администратора: ";
    admin.work();

    cout << "Работа программиста: ";
    programmer.work();

    TeamLead teamLead;
    teamLead.manageEmployee(manager);

    return 0;
}
