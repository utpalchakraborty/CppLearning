#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

namespace
{
    // define a class Employee
    class Employee
    {
    private:
	string firstname;
	string lastname;
	
    public:

	// default constructor
	Employee() = default;
	
	// constuctor with values.
	Employee(string first, string last) : firstname { first }, lastname { last } {}

	void printA() { std::cout << "Printing A" << std::endl; }

	// virtual method. So can be overridden in a base class.
	virtual void print() 
	    { 
		std::cout << "Name: " << firstname << " " << lastname << std::endl; 
	    }

	// the following method cannot be overriden
	virtual void finalMethod() final { std::cout << "This is the final method." << std::endl; }

	// needs virtual destructor. since there is a virual method.
	virtual ~Employee() {};
    };

    // we also define a pure virtual interface.
    class Perks
    {
    public:
	virtual bool hasOffice() = 0;
	virtual bool hasCar() = 0;

	virtual ~Perks() {};
    };

    // now inherit Employee to make Manager.
    // This is implementation inheritance of employee. 
    // Perks is interface inheritance.
    class Manager : public Employee, public Perks
    {
    private:
	int level;

    public:
	// we can inherit the base's constructor.
	// now manager can be defined with just the base's construcor
	// but level will be undefine.
	using Employee::Employee;
	
	// the constuctors are not automatically inherited. so we define one.
	// and reuse the base class' constructor
	Manager(string first, string last, int l) : Employee {first, last}, level { l } {} 

	// since printA() is defined by Employee. this just hides that in this class.
	void printA() { std::cout << "Printing B" << std::endl; }

	// overriding base::print(). but we also use the base print.
	virtual void print() override 
	    {
		Employee::print();
		std::cout << "level :" << level << std::endl; 
	    }

	// now define the methods of perks
	virtual bool hasOffice() override { return true; }

	virtual bool hasCar() override { return level > 0; }

	virtual ~Manager() {}
    };

    // Here the inheritance is private. So all public members are invisible to 
    // users.
    class RestrictedManager : private Employee
    {
	// however we can bring in and expose individual methods.
	// here we expose the constructors and the print method.
    public:
	using Employee::Employee;
	using Employee::print;
	
    };
}


int main()
{
    Employee a {"Katy", "Kale" };
    Manager b {"David", "King", 1 };
    Manager c {"David", "NotKing" };

    vector<Employee> employees;
    employees.push_back(a);
    // the following should work because 
    // a manager is also an employee
    employees.push_back(b);

    vector<Employee*> e;
    e.push_back(&a);
    // pointers are also implicitly converted
    e.push_back(&b);
    e.push_back(&c);

    // can call member functions of course.
    // we are calling printA() which is not virtual. 
    // hence A->printA() gets called.
    std::for_each(e.begin(), e.end(), [](Employee* p) { p->printA(); });

    // now it prints manager's print.
    std::for_each(e.begin(), e.end(), [](Employee* p) { p->print(); });

    // obviously they can be cast to their interface too, implicitly.
    vector<Manager*> managers;
    managers.push_back(&b);
    managers.push_back(&c);

    std::for_each(managers.begin(), managers.end(), 
		  [](Perks* p) { std::cout << p->hasCar() << std::endl; }); 

    // we can create a RestrictedManager
    RestrictedManager r { "Utpal", "C"};
    r.print(); // we can call the exposed method.

    // but we cannot call the nonexposed method.
    //r.printA(); // compile error.
    

}
