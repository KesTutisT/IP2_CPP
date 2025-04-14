#ifndef MAP_H
#define MAP_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>

namespace MyProject {

// Isimties klase
class MyException : public std::exception {
private:
    std::string message;
public:
    explicit MyException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Map klase
/**
 * @author Kęstutis Karneckas
 * @class Map
 * @brief Asociatyvaus masyvo realizacija naudojant PIMPL.
 *
 * CRUD metodai: insert, select, update, delete
 * Papildomi operatoriai: [], !, ~, +=, -=, ==, !=, <, >, <=, >=
 * 
 * Naudojimas:
 * Map m;
 * m.insert("key", "value");
 * std::string value = m.select("key");
 */
class Map {
public:
    using KeyType = std::string;
    using ValueType = std::string;

    Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();

    void insert(const KeyType& key, const ValueType& value);
    ValueType select(const KeyType& key) const;
    void update(const KeyType& key, const ValueType& value);
    void remove(const KeyType& key);

    std::string toString() const;

    bool operator==(const Map& other) const;
    bool operator!=(const Map& other) const;
    bool operator<(const Map& other) const;
    bool operator>(const Map& other) const;
    bool operator<=(const Map& other) const;
    bool operator>=(const Map& other) const;

    Map& operator+=(const std::pair<KeyType, ValueType>& pair);
    Map& operator-=(const KeyType& key);
    Map& operator~();
    Map& operator!();

    int operator[](const ValueType& value) const;

    static int getObjectCount();

private:
    class Impl;
    Impl* pImpl;
};

} // namespace MyProject

#endif // MAP_H