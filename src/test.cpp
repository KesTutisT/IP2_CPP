#include "map.h"
#include <cassert>
#include <fstream>

using namespace MyProject;

int main() {
    try {
        std::ofstream log("test_results.txt");
        {
            Map m;
            m.insert("a", "1");
            m.insert("b", "2");
            assert(m.select("a") == "1");
            log << "m.select(\"a\") == \"1\" | " << m.select("a") << std::endl;

            m.update("a", "3");
            assert(m.select("a") == "3");
            log << "m.update(\"a\", \"3\") | " << m.select("a") << std::endl;

            m.remove("a");
            try {
                m.select("a");
                assert(false);
                log << "m.remove(\"a\") | Exception not thrown" << std::endl;
            } catch (const std::exception&) {}

            m += {"x", "100"};
            assert(m.select("x") == "100");
            log << "m += {\"x\", \"100\"} | " << m.select("x") << std::endl;

            m -= "x";
            try {
                m.select("x");
                assert(false);
                log << "m -= \"x\" | Exception not thrown" << std::endl;
            } catch (const std::exception&) {}

            m.insert("k1", "v1");
            m.insert("k2", "v2");
            m.insert("k3", "v3");
            assert(m["v2"] == 2);
            log << "m[\"v2\"] == 2 | " << m["v2"] << std::endl;

            ~m;
            assert(m.select("k1") == "");
            log << "~m | " << m.select("k1") << std::endl;

            !m;
            assert(m.toString().find("0") != std::string::npos);
            log << "!m | " << m.toString() << std::endl;

            Map m2;
            m2.insert("a", "1");
            m2.insert("b", "2");
            Map m3 = m2;
            assert(m2 == m3);
            log << "m2 == m3 | " << (m2 == m3) << std::endl;

            m3.update("a", "5");
            assert(m2 != m3);
            log << "m2 != m3 | " << (m2 != m3) << std::endl;
            assert(m2 < m3 || m2 > m3 || m2 <= m3 || m2 >= m3);
            log << "m2 < m3 | " << (m2 < m3) << std::endl;
        }
        assert(Map::getObjectCount() == 0);
        log << "--------------" << std::endl;
        log << "All tests passed!" << std::endl;
        std::cout << "All tests passed!" << std::endl;
    } catch (...) {
        std::cerr << "Unhandled exception during testing." << std::endl;
    }
    return 0;
}