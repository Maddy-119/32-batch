#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int social_security_tax = 10;

class Employee {
private:
    int employeeid;
    string employeename;
    string employeeposition;
    string employeetype;
    string startdate;
    double basicsalary;

public:
    int getEmployeeID() { return employeeid; }
    string getName() { return employeename; }
    string getPosition() { return employeeposition; }
    string getEmployeeType() { return employeetype; }
    string getStartDate() { return startdate; }
    double getBasicSalary() { return basicsalary; }

    Employee() : employeeid(0), employeename(""), employeeposition(""), employeetype(""), startdate(""), basicsalary(0.0) {}

    void inputempdata() {
        cout << "Enter Employee ID: ";
        cin >> employeeid;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, employeename);

        while (true) {
            cout << "Enter Employee Position (Barista, Cashier, Supervisor, Cleaner, Kitchen Staff, Waiter, Waitress): ";
            cin >> employeeposition;

            if (employeeposition == "Barista" || employeeposition == "barista") {
                basicsalary = 1920;
                employeetype = "fulltime";
                break;
            } else if (employeeposition == "Cashier" || employeeposition == "cashier") {
                basicsalary = 1790;
                employeetype = "fulltime";
                break;
            } else if (employeeposition == "Cleaner" || employeeposition == "cleaner") {
                basicsalary = 1400;
                employeetype = "parttime";
                break;
            } else if (employeeposition == "Kitchen Staff" || employeeposition == "kitchen staff") {
                basicsalary = 1850;
                employeetype = "parttime";
                break;
            } else if (employeeposition == "Waiter" || employeeposition == "waiter" || employeeposition == "Waitress" || employeeposition == "waitress") {
                basicsalary = 1700;
                employeetype = "parttime";
                break;
            } else if (employeeposition == "Supervisor" || employeeposition == "supervisor") {
                basicsalary = 2400;
                employeetype = "fulltime";
                break;
            } else {
                cout << "!!! Invalid Employee Position. Please try again !!!" << endl;
            }
        }

        cout << "Enter Employee start date: ";
        cin.ignore();
        getline(cin, startdate);
    }

    void displayempdata() {
        cout << "Employee ID" << setw(15) << "Name" << setw(15) << "Position" << setw(15) << "Type" << setw(15)
             << "Start Date" << setw(15) << "Basic Salary" << endl;
        cout << employeeid << setw(15) << employeename << setw(15) << employeeposition << setw(15)
             << employeetype << setw(15) << startdate << setw(15) << basicsalary << endl;
    }
};

class Fulltime : public Employee {
private:
    int leaveday;
    float overtimehrs;
    double totalamount;
    double netsalary;

public:
    Fulltime() : leaveday(0), overtimehrs(0.0), totalamount(0.0), netsalary(0.0) {}

    void inputfulltimedata() {
        inputempdata();
        cout << "Enter leave day number: ";
        cin >> leaveday;
        cout << "Enter overtime hours: ";
        cin >> overtimehrs;

        calculateFulltimetotalsalary();
    }

    void calculateFulltimetotalsalary() {
        double salary = getBasicSalary();
        double bonus = (leaveday == 0) ? 300 : ((leaveday == 1) ? 200 : ((leaveday == 3) ? 100 : 0));
        double overtimefee = ((salary / 30) / 8) * overtimehrs * 2;

        totalamount = salary + bonus + overtimefee;
        netsalary = totalamount - ((totalamount / 100) * 2) - social_security_tax;
    }

    void getFullTimeData() {
        displayempdata();
        cout << "Net Salary: $" << fixed << setprecision(2) << netsalary << endl;
    }
};

class PartTime : public Employee {
private:
    double workinghrs;
    double hourlywage;
    double totalamount;

public:
    PartTime() : workinghrs(0), hourlywage(0), totalamount(0) {}

    void inputparttimedata() {
        inputempdata();
        cout << "Enter working hours (monthly): ";
        cin >> workinghrs;

        calculateParttimeTotalNetSalary();
    }

    void calculateParttimeTotalNetSalary() {
        hourlywage = (getBasicSalary() / 30) / 8;
        totalamount = (hourlywage * workinghrs) - ((totalamount / 100) * 2) - social_security_tax;
    }

    void getParttimeData() {
        displayempdata();
        cout << "Total Amount: $" << fixed << setprecision(2) << totalamount << endl;
    }
};

vector<Fulltime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main() {
    int choose = 0;
    while (choose != 5) {
        cout << "\n########## Menu ##########" << endl;
        cout << "1. Insert Employee Data" << endl;
        cout << "2. View Full-Time Employees" << endl;
        cout << "3. View Part-Time Employees" << endl;
        cout << "4. View all Employee Salary" <<endl;
        cout << "5. Exit" << endl;

        cout << "Choose an option: ";
        cin >> choose;

        switch (choose) {
        case 1: {
            string type;
            cout << "Enter employee type (fulltime/parttime): ";
            cin >> type;
            if (type == "fulltime") {
                Fulltime emp;
                emp.inputfulltimedata();
                Fulltime_Employees.push_back(emp);
            } else if (type == "parttime") {
                PartTime emp;
                emp.inputparttimedata();
                PartTime_Employees.push_back(emp);
            } else {
                cout << "Invalid type!" << endl;
            }
            break;
        }
        case 2:
            if (Fulltime_Employees.empty()) {
                cout << "No Full-Time Employees Found!" << endl;
            } else {
                for (int i = 0; i < Fulltime_Employees.size(); i++) {
                    cout << "\nFull-Time Employee " << i + 1 << ":" << endl;
                    Fulltime_Employees[i].getFullTimeData();
                }
            }
            break;
        case 3:
            if (PartTime_Employees.empty()) {
                cout << "No Part-Time Employees Found!" << endl;
            } else {
                for (int i = 0; i < PartTime_Employees.size(); i++) {
                    cout << "\nPart-Time Employee " << i + 1 << ":" << endl;
                    PartTime_Employees[i].getParttimeData();
                }
            }
            break;
        case 4:
        
        case 5:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid option, try again!" << endl;
        }
    }
    return 0;
}