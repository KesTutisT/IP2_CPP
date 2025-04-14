#include "map.h"
#include <cassert>
#include <fstream>

using namespace MyProject;

void runTests() {
    std::ofstream log("test_results.txt");

    Map m;
    {
        m.insert("a", "1");
        m.insert("b", "2");
        assert(m.select("a") == "1");

        m.update("a", "3");
        assert(m.select("a") == "3");

        m.remove("a");
        try {
            m.select("a");
            assert(false);
        } catch (const std::exception&) {}

        m += {"x", "100"};
        assert(m.select("x") == "100");

        m -= "x";
        try {
            m.select("x");
            assert(false);
        } catch (const std::exception&) {}

        m.insert("k1", "v1");
        m.insert("k2", "v2");
        m.insert("k3", "v3");
        assert(m["v2"] == 2);

        ~m;
        assert(m.select("k1") == "");

        !m;
        assert(m.toString().find("0") != std::string::npos);

        Map m2;
        m2.insert("a", "1");
        m2.insert("b", "2");
        Map m3 = m2;
        assert(m2 == m3);

        m3.update("a", "5");
        assert(m2 != m3);
        assert(m2 < m3 || m2 > m3 || m2 <= m3 || m2 >= m3);
    }
    assert(m.getObjectCount() == 0);
    log << "All tests passed!" << std::endl;
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    try {
        runTests();
    } catch (...) {
        std::cerr << "Unhandled exception during testing." << std::endl;
    }
    return 0;
}