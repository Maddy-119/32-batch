#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include <limits>
using namespace std;
int social_security_tax = 10;
class Employee
{
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

    // Constructor
    Employee() : employeeid(0), employeename(""), employeeposition(""), employeetype(""), startdate(0), basicsalary(0.0) {}

    void inputempdata()
    {
        cout<<"Enter Employee ID: ";
        cin>>employeeid;
        cout<<"Enter Employee Name: ";
        cin>>employeename;

        while (true)
        {
            cout << "Enter Employee Position (Barista, Cashier, Supervisor, Cleaner, Kitchen Staff, Waiter, Waitress): ";
            cin>>employeeposition;

            if (employeeposition == "Barista"||employeeposition =="barista")
            {
                basicsalary = 1920;
                employeetype = "fulltime";
                break;
            }
            else if (employeeposition == "Cashier"||employeeposition =="cashier")
            {
                basicsalary = 1790;
                employeetype = "fulltime";
                break;
            }
            else if (employeeposition == "Cleaner"||employeeposition =="cleaner")
            {
                basicsalary = 1400;
                employeetype = "parttime";
                break;
            }
            else if (employeeposition == "Kitchen Staff"||employeeposition =="kitchen staff")
            {
                basicsalary = 1850;
                employeetype = "parttime";
                break;
            }
            else if (employeeposition == "Waiter" ||employeeposition == "waiter"|| employeeposition == "Waitress"||employeeposition == "waitress")
            {
                basicsalary = 1700;
                employeetype = "parttime";
                break;
            }
            else if (employeeposition == "Supervisor"||employeeposition == "supervisor")
            {
                basicsalary = 2400;
                employeetype = "fulltime";
                break;
            }
            else
            {
                cout <<"!!! Invalid Employee Position. Please try again !!!"<<endl;
            }
        }

        cout<<"Enter Employee start date: ";
        cin>>startdate;
        cout<<endl;
    }

    void displayempdata()
    {
        cout<<"Employee ID"<<setw(10)<<"Employee Name"<<setw(10)<<"Position"<<setw(10)<<"Type"<<setw(10)<<"Start Date"<<setw(10)<<"Basic Salary"<<endl;
        cout<<employeeid<<setw(10)<<employeename<<setw(10)<<employeeposition<<setw(10)<<employeetype<<setw(10)<<startdate<<setw(10)<<basicsalary<<setw(10)<<endl;
    }
};

class Fulltime : public Employee
{
private:
    int leaveday;
    float overtimehrs=0;
    int bonus=0;
    int overtimefee=0;
    int taxsalary=0;
    int netsalary=0;
    int totalamount=0;

public:
    Fulltime() : leaveday(0), overtimehrs(0) {}

    void inputfulltimedata()
    {
        inputempdata();
        cout<<"Enter leave day number: ";
        cin>>leaveday;
        cout<<"Enter overtime (hrs): ";
        cin>>overtimehrs;

        if (leaveday==0)
        {
            bonus=300;
        }
        else if (leaveday==1)
        {
            bonus=200;
        }
        else if (leaveday==3)
        {
            bonus=100;
        }
        else
        {
            bonus=0;
        }
        calculateFulltimetotalsalary();
    }

     double calculateFulltimetotalsalary()
    {
        double salary = getBasicSalary();

        // Calculate overtime fees
        overtimefee = (((salary / 30) / 8) * overtimehrs) * 2;

        // Calculate total amount considering leave days and overtime
        if (leaveday < 4 && overtimehrs >= 0)
        {
            totalamount = salary + bonus + overtimefee;
            // Calculate tax on salary
            taxsalary = (totalamount / 100) * 2;
        }
        else if (leaveday > 4 && overtimehrs > 0)
        {
            totalamount = salary - ((salary / 100) * 1) + overtimefee - bonus;
            // Calculate tax on salary
            taxsalary = (totalamount / 100) * 2;
        }
        else
        {
            totalamount = salary - bonus + overtimefee;
            // Calculate tax on salary
            taxsalary = (totalamount / 100) * 2;
        }

        return totalamount;
    }

    double calculateFulltimetotalnetsalary()
    {
        if (totalamount == 0) // Ensure total_amount is calculated
            calculateFulltimetotalsalary();

        // Calculate net salary after deductions
        netsalary = totalamount - ((totalamount / 100) * 2) - social_security_tax;
        return netsalary;
    }

    void getFullTimeData()
    {
        // Ensure all calculations are up-to-date
        calculateFulltimetotalsalary();
        calculateFulltimetotalnetsalary();

        displayempdata();
        cout << left << setw(20) << "Leave Days" << ": " << setw(20) << leaveday << endl;
        cout << left << setw(20) << "Overtime Hours" << ": " << setw(20) << fixed << setprecision(2) << overtimehrs << endl;
        cout << left << setw(20) << "Overtime Fees" << ": $" << setw(20) << fixed << setprecision(2) << overtimefee << endl;
        cout << left << setw(20) << "Bonus" << ": $" << setw(20) << fixed << setprecision(2) << bonus << endl;
        cout << left << setw(20) << "Tax Deduction" << ": $" << setw(20) << fixed << setprecision(2) << taxsalary << endl;
        cout << left << setw(20) << "Security Deduction" << ": $" << setw(20) << social_security_tax << endl;
        cout << left << setw(20) << "Total Amount" << ": $" << setw(20) << fixed << setprecision(2) << totalamount << endl;
        cout << left << setw(20) << "Total Net Amount" << ": $" << setw(20) << fixed << setprecision(2) << netsalary << endl;
        cout << endl;
    }
};

class PartTime : public Employee
{
private:
    double hourlywage = 0;
    double workinghrs = 0;
    double totalamount = 0;
    double tax_deduction = 0;
    double net_salary = 0;

public:
    PartTime() : workinghrs(0) {}

    void displayParttimeData()
    {
        inputempdata(); // Set common data from Employee
        cout << "Enter working hours (Monthly): ";
        cin >> workinghrs;

        // Calculate salary components after setting data
        calculateParttimeTotalNetSalary();
    }

    double calculateParttimeTotalNetSalary()
    {
        // Calculate hourly wage from basic salary
        double salary = getBasicSalary();
        hourlywage = (salary / 30) / 8;

        // Calculating gross total amount based on working hours
        totalamount = hourlywage * workinghrs;

        // Calculating tax deduction (2% of total amount)
        tax_deduction = (totalamount / 100) * 2;

        // Calculaing net salary after tax and security deduction
        net_salary = totalamount - tax_deduction - social_security_tax;

        return net_salary;
    }

    void inputparttimedata()
    {
        calculateParttimeTotalNetSalary();

        // Display part-time employee data
        inputparttimedata();
        cout << left << setw(20) << "Working Hours" << ": " << setw(20) << fixed << setprecision(2) << workinghrs << endl;
        cout << left << setw(20) << "Hourly Wage" << ": $" << setw(20) << fixed << setprecision(2) << hourlywage << endl;
        cout << left << setw(20) << "Total Amount" << ": $" << setw(20) << fixed << setprecision(2) << totalamount << endl;
        cout << left << setw(20) << "Tax Deduction" << ": $" << setw(20) << fixed << setprecision(2) << tax_deduction << endl;
        cout << left << setw(20) << "Security Deduction" << ": $" << setw(20) << social_security_tax << endl;
        cout << left << setw(20) << "Total Net Amount" << ": $" << setw(20) << fixed << setprecision(2) << net_salary << endl;
        cout << endl;
    }
};

vector<Fulltime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main()
{
    int choose=0;
    cout<<"--------------------------------------------"<<endl;
    cout<<"******* Java Jolt Cafe *******"<<endl;
    cout<<"--------------------------------------------"<<endl;
    while (choose!=5)
    {
        cout<<"########## Menu ##########"<<endl;
        cout<<"1. Insert Employee Data"<<endl;
        cout<<"2. Update Employee Data"<<endl;
        cout<<"3. View Full-time Employee Data"<<endl;
        cout<<"4. View Part-time Employee Data"<<endl;
        cout<<"5. Exit"<<endl;

        cout<<"Choose an option: ";
        cin>>choose;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 6." << endl;
            continue;
        }

        cin.ignore();

        switch (choose)
        {
        case 1:
        {
            int n;
            cout << "Enter the number of employees you want to insert: ";
            cin >> n;
            cin.ignore(); // Clear input buffer

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;
                cin.ignore(); // Clear buffer after reading employee_type

                if (employee_type == "fulltime")
                {
                    Fulltime New_Employee;
                    New_Employee.inputfulltimedata();
                    cout << endl;
                    Fulltime_Employees.push_back(New_Employee);
                }
                else if (employee_type == "parttime")
                {
                    PartTime New_Employee;
                    New_Employee.inputparttimedata();
                    cout << endl;
                    PartTime_Employees.push_back(New_Employee);
                }
                else
                {
                    cout << "!!!Invalid Employee Type!!!" << endl;
                }
            }
            break;
        }
        case 2:
        {
            int num;
            string type;
            bool found = false;

            cout << "Enter The Employee Type to Update Data (fulltime/parttime): ";
            cin >> type;

            if (type == "fulltime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    if (num == Fulltime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Full-Time Employee ID: " << num << endl;
                        Fulltime_Employees[i].inputfulltimedata();
                        Fulltime_Employees[i].calculateFulltimetotalsalary();
                        Fulltime_Employees[i].calculateFulltimetotalnetsalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Full-Time Employee found with ID: " << num << endl;
                }
            }
            else if (type == "parttime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    if (num == PartTime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Part-Time Employee ID: " << num << endl;
                        PartTime_Employees[i].inputparttimedata();
                        PartTime_Employees[i].calculateParttimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Part-Time Employee found with ID: " << num << endl;
                }
            }
            else
            {
                cout << "Invalid Employee Type! Please enter 'fulltime' or 'parttime'." << endl;
            }

            break;
        }
        case 3:
        {
            if (Fulltime_Employees.empty())
            {
                cout << "No Full-Time Employees Found!" << endl;
            }
            else
            {
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    cout << "Full Time Employee Data " << i + 1 << ":" << endl;
                    Fulltime_Employees[i].getFullTimeData();
                }
            }
            break;
        }
        case 4:
        {
            if (PartTime_Employees.empty())
            {
                cout << "No Part-Time Employees Found!" << endl;
            }
            else
            {
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    cout << "Part Time Employee Data " << i + 1 << ":" << endl;
                    PartTime_Employees[i].inputparttimedata();
                }
            }
            break;
        }
        case 5:
        {
            //Adding algorithm with vector
            struct EmployeeInfo
            {
                string type;                 // "FullTime" or "PartTime"
                double net_salary;           // Net salary for sorting
                int employee_id;             // Employee ID
                string employee_name;        // Employee Name
                Employee *employee_instance; // Pointer to original object
            };

            vector<EmployeeInfo> all_employees;

            // Collect full-time employees
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "FullTime";
                info.net_salary = Fulltime_Employees[i].calculateFulltimetotalnetsalary();
                info.employee_id = Fulltime_Employees[i].getEmployeeID();
                info.employee_name = Fulltime_Employees[i].getName();
                info.employee_instance = &Fulltime_Employees[i];
                all_employees.push_back(info);
            }

            // Collect part-time employees
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                EmployeeInfo info;
                info.type = "PartTime";
                info.net_salary = PartTime_Employees[i].calculateParttimeTotalNetSalary();
                info.employee_id = PartTime_Employees[i].getEmployeeID();
                info.employee_name = PartTime_Employees[i].getName();
                info.employee_instance = &PartTime_Employees[i];
                all_employees.push_back(info);
            }

            // Sort all employees by net salary in descending order
            sort(all_employees.begin(), all_employees.end(), [](EmployeeInfo &a, EmployeeInfo &b)
                 { return a.net_salary > b.net_salary; });

            // Display sorted employees
            if (all_employees.empty())
            {
                cout << "No employees found to display!" << endl;
                break;
            }

            cout << "\nEmployees Sorted by Total Net Salary (High to Low):" << endl;
            for (int i = 0; i < all_employees.size(); i++)
            {
                cout << "--------------------------------------------" << endl;
                cout << "NO " << i + 1 << " "<<endl;
                cout << "----------------------------"<< endl;

                // Display full details for the employee
                if (all_employees[i].type == "FullTime")
                {
                    dynamic_cast<Fulltime *>(all_employees[i].employee_instance)->getFullTimeData();
                }1
                else if (all_employees[i].type == "PartTime")
                {
                    dynamic_cast<PartTime *>(all_employees[i].employee_instance)->getParttimeData();
                }
            }
            break;
        }
        case 6:
        {
            cout << "!!Exiting program!!" << endl;
            return 0;
        default:
            cout << "Invalid option, please try again." << endl;
                break;
        }
    }
	}
}