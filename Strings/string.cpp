#include <string>
#include <iostream>



int main()
{
    // the usual string construction.
    // out of many many possibilities
    std::string s("This is a string");
    // all the usual common sensical operations are provided.
    s += " with something at the end of it";
    std::cout << s << std::endl;

    // the following will read only till teh first space.
    /*
    std::cout << "Enter a string:";
    std::cin >> s;
    
    std::cout << "You entered" << std::endl << s << std::endl;
    */
    std::cout << "Enter another string:";
    std::getline(std::cin, s);
    
    std::cout << "You entered" << std::endl << s << std::endl;
}
