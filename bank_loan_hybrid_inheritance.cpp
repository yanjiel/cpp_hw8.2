//https://github.com/aryashah2k/OOP-In-CPlusPlus/tree/main/Lab%20Files%20-%20Code%20%2B%20Manuals/Lab%209%20Programs%20%5BCode%20Plus%20Theory%5D
/*
Analyze it according to the SOLID principles
The SOLID principles are:
1. Single responsibility principle
2. Open/Closed principle
3. Liskov Substitution principle
    Objects of a superclass shall be replaceable with objects of its subclasses without breaking the application. 
    That requires the objects of your subclasses to behave in the same way as the objects of your superclass.
4. Interface Segregation principle
    “Clients should not be forced to depend upon interfaces that they do not use.”
5. Dependency Inversion principle
    High-level modules should not depend on low-level modules. Both should depend on abstractions.
    Abstractions should not depend on details. Details should depend on abstractions.

What does it do well?
It does ok with the single responsibility principle, since it is a relatively simple program. Like insurance premium calculation is defined in insurance classes, 
and cliam settlement is calculated in claim class

It does ok being closed for modification for the open/closed principle, since it all member values and functions are encapsulated in classes.

It does ok with the Liskov substitution principle, the superclass in this case is the bank class, and it's a class with relatively 
simple member function withdraw and deposit, that will not need to be changed by subclasses.


What does it do badly?
It does poorly on being open for extension in the open/closed principle. The claim inherits somewhat "specialized" life_insurance class and car_insurance,
that means if life_insurance needs to change, then claim might also need to change. Moreover, if there is more insurance types, then we need to change 
the signature of claim to inherit more "specialized" insurance classes

It does poorly with the Interface Segregation principle, which requires that "clients should not be forced to depend upon interfaces that they do not use."
However, car_insurance and life_insurance, even though neither requires deposit methods, will both have access to a deposit method by inheriting from the bank class
Similarly, claim does not need a draw method, nor does it need a calculate_premium method, but by inheriting from the insurance class, it is very possible that later  
claim could be impacted by methods that it do not use

It does poorly wit the dependency inversion principle, since claim does not inherit from a more general class, but instead on a more specialized life_insurance and car_insurace, there is dependcy of claim on details of lower level classes


Can you suggest improvements?

*/


#include<iostream>
#include<string.h>
using namespace std;

class bank
{
protected:
    char name[50];
    char address[150];
    int age;
    double account;
    double balance;
public:
    void open_account()
    {
        cout << "Enter the name of Customer:" << endl;
        cin >> name;
        cout << "Enter Age:" << endl;
        cin >> age;
        cout << "Enter Customer Residence Details:" << endl;
        cin >> address;
        cout << "Enter Account Number:" << endl;
        cin >> account;
        cout << "Enter Current Balance:" << endl;
        cin >> balance;

    }
    void withdraw()
    {
        double withdraw;
        cout << "Enter Amount to Withdraw:" << endl;
        cin >> withdraw;
        if (withdraw <= balance)
        {
            balance = balance - withdraw;
            cout << "Amount withdrawn:" << withdraw << endl;
            cout << "Current Balance:" << balance << endl;
        }
        else
        {
            cout << "Withdrawal Amount Exceeded Balance!" << endl;
        }

    }
    void deposit()
    {
        double amount;
        cout << "Enter Amount to be Deposited:" << endl;
        cin >> amount;
        balance = balance + amount;
        cout << "Total Balance after Deposit:" << balance << endl;
    }
    void display()
    {
        cout << "-----Account Details-----" << endl;
        cout << "Name of Customer:" << name << endl;
        cout << "Age:" << age << endl;
        cout << "Residence Details:" << address << endl;
        cout << "Account Number:" << account << endl;
        cout << "Current Balance:" << balance << endl;
    }
};

class life_insurance : virtual public bank
{
protected:
    int policy;
    int term;
    float premium;
    float sum_assured;

public:
    void read_data()
    {
        cout << "Enter Policy Number:" << endl;
        cin >> policy;
        cout << "Enter Term for Insurance:" << endl;
        cin >> term;
        cout << "Enter Assured Sum:" << endl;
        cin >> sum_assured;
    }
    void calculate_premium()
    {
        if (age > 60)
        {
            premium = 0;
        }
        else if (age > 45)
        {
            premium = (5000 * sum_assured / 1000);
        }
        else if (age > 25)
        {
            premium = (4000 * sum_assured / 1000);
        }
        else
        {
            premium = (3000 * sum_assured / 1000);
        }
    }
    void deduction()
    {
        for (int i = 0; i < term; i++)
        {
            calculate_premium();
            balance = balance - premium;
        }
    }
    void display_data()
    {
        deduction();
        cout << "Policy Number:" << policy << endl;
        cout << "Insurance Term:" << term << endl;
        cout << "Per Annum Premium:" << premium << endl;
        cout << "Final Balance with Premium:" << balance << endl;

    }
};

class car_insurance : virtual public bank
{
protected:
    int car_policy;
    int car_term;
    float car_premium;
    int car_number;
    float car_price;
public:
    void car_read()
    {
        cout << "Enter Policy Number:" << endl;
        cin >> car_policy;
        cout << "Enter Car Number:" << endl;
        cin >> car_number;
        cout << "Enter Car Term:" << endl;
        cin >> car_term;
        cout << "Car Price:" << endl;
        cin >> car_price;

    }
    void car_calculate_premium()
    {
        if (car_term > 5)
        {
            car_premium = 2000 * car_price / 1000;
        }
        else if (car_term > 1)
        {
            car_premium = 4000 * car_price / 1000;
        }
        else
        {
            car_premium = 5000 * car_price / 1000;
        }
    }
    void car_deduction()
    {
        for (int i = 0; i < car_term; i++)
        {
            car_calculate_premium();
            balance = balance - car_premium;
        }

    }
    void car_info()
    {
        car_deduction();
        cout << "Policy Number:" << car_policy << endl;
        cout << "Car Number:" << car_number << endl;
        cout << "Car Term:" << car_term << endl;
        cout << " Total Premium:" << car_premium << endl;
        cout << "Final Balance with Premium:" << balance << endl;
    }
};

class claim : public car_insurance, public life_insurance
{
public:
    int i;
    float s;
    void insurance_settlement()
    {
        cout << "-----Insurance Settlement-----" << endl;
        cout << "Enter 1 for Life Insurance" << endl;
        cout << "Enter 2 for Car Insurance" << endl;
        if (i == 1)
        {
            if (term < 5)
            {
                s = 0;
            }
            else if (term < 12 && term>6)
            {
                s = 0.25 * sum_assured;
            }
            else if (term < 20 && term>13)
            {
                s = 0.7 * sum_assured;
            }
            else
            {
                s = 2 * sum_assured;
            }
            cout << "Life Insurance Settlement Amount:" << s << endl;
        }
    }
    void deposit_1()
    {
        balance = balance + s;
        cout << "Total Balance after Settlement:" << balance << endl;

    }
    void display_1()
    {
        cout << "-----DETAILS:-----" << endl;
        cout << "Name of Customer:" << name << endl;
        cout << "Age:" << age << endl;
        cout << "Residential Address:" << address << endl;
        cout << "Account Number:" << account << endl;
        cout << "Total Balance:" << balance << endl;
    }
};

int main()
{
    claim c;
    c.open_account();
    c.withdraw();
    c.deposit();
    c.display();
    c.read_data();
    c.display_data();
    c.car_read();
    c.car_info();
    c.insurance_settlement();
    c.deposit_1();
    c.display_1();
}