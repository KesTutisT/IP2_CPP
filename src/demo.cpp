#include "map.h"
#include <iostream>
using namespace MyProject;

int main() {
    try {
        Map m;
        {
        m.insert("name", "John");
        m.insert("age", "30");

        std::cout << m.toString() << std::endl;
        std::cout << "name: " << m.select("name") << std::endl;

        m.update("age", "31");
        std::cout << "age updated: " << m.select("age") << std::endl;

        m += {"country", "Lithuania"};
        m -= "name";
        ~m;
        std::cout << "After ~: " << m.toString() << std::endl;

        !m;
        std::cout << "After !: " << m.toString() << std::endl;
        }
        std::cout << "All objects destroyed?: " << (m.getObjectCount() == 0) << std::endl;

    } catch (const MyException& ex) {
        std::cerr << "MyException caught: " << ex.what() << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Standard exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }
    return 0;
}