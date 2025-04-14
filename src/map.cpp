#include "map.h"
#include <algorithm>

namespace MyProject {

class Map::Impl {
public:
    struct Entry {
        std::string key;
        std::string value;

        bool operator==(const Entry& other) const {
            return key == other.key && value == other.value;
        }

        bool operator<(const Entry& other) const {
            return key < other.key || (key == other.key && value < other.value);
        }
    };

    std::vector<Entry> data;
    static int objectCount;

    ~Impl() {
        --objectCount;
    }

    Impl() {
        ++objectCount;
    }

    Entry* find(const std::string& key) {
        for (auto& e : data) {
            if (e.key == key) return &e;
        }
        return nullptr;
    }

    const Entry* find(const std::string& key) const {
        for (const auto& e : data) {
            if (e.key == key) return &e;
        }
        return nullptr;
    }
};

int Map::Impl::objectCount = 0;

Map::Map() : pImpl(new Impl) {}
Map::Map(const Map& other) : pImpl(new Impl(*other.pImpl)) {}
Map& Map::operator=(const Map& other) {
    if (this != &other) {
        delete pImpl;
        pImpl = new Impl(*other.pImpl);
    }
    return *this;
}
Map::~Map() {
    delete pImpl;
}

void Map::insert(const std::string& key, const std::string& value) {
    if (pImpl->find(key)) throw std::invalid_argument("Key already exists");
    pImpl->data.push_back({key, value});
}

std::string Map::select(const std::string& key) const {
    auto entry = pImpl->find(key);
    if (!entry) throw std::invalid_argument("Key not found");
    return entry->value;
}

void Map::update(const std::string& key, const std::string& value) {
    auto entry = pImpl->find(key);
    if (!entry) throw MyException("Special update error: key not found");
    entry->value = value;
}

void Map::remove(const std::string& key) {
    auto& d = pImpl->data;
    auto it = std::remove_if(d.begin(), d.end(), [&key](const auto& e) { return e.key == key; });
    if (it == d.end()) throw std::invalid_argument("Key not found for deletion");
    d.erase(it, d.end());
}

std::string Map::toString() const {
    std::ostringstream oss;
    oss << "Map with " << pImpl->data.size() << " entries.";
    return oss.str();
}

bool Map::operator==(const Map& other) const {
    return pImpl->data == other.pImpl->data;
}

bool Map::operator!=(const Map& other) const {
    return !(*this == other);
}

bool Map::operator<(const Map& other) const {
    return pImpl->data.size() < other.pImpl->data.size();
}

bool Map::operator>(const Map& other) const {
    return pImpl->data.size() > other.pImpl->data.size();
}

bool Map::operator<=(const Map& other) const {
    return !(*this > other);
}

bool Map::operator>=(const Map& other) const {
    return !(*this < other);
}

Map& Map::operator+=(const std::pair<std::string, std::string>& pair) {
    insert(pair.first, pair.second);
    return *this;
}

Map& Map::operator-=(const std::string& key) {
    remove(key);
    return *this;
}

Map& Map::operator~() {
    for (auto& e : pImpl->data) e.value = "";
    return *this;
}

Map& Map::operator!() {
    pImpl->data.clear();
    return *this;
}

int Map::operator[](const std::string& value) const {
    for (size_t i = 0; i < pImpl->data.size(); ++i) {
        if (pImpl->data[i].value == value) return static_cast<int>(i);
    }
    throw MyException("Value not found");
}

int Map::getObjectCount() {
    return Impl::objectCount;
}


} // namespace MyProject