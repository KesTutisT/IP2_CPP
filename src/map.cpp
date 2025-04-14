#include "map.h"
#include <cstring>

namespace MyProject {

struct Map::Impl {
    struct Entry {
        KeyType key;
        ValueType value;
        bool operator==(const Entry& other) const {
            return key == other.key && value == other.value;
        }
        bool operator<(const Entry& other) const {
            return key < other.key || (key == other.key && value < other.value);
        }
    };

    Entry* data;
    size_t size;
    size_t capacity;

    Impl() : data(new Entry[4]), size(0), capacity(4) {
        ++objectCount;
    }

    Impl(const Impl& other) : data(new Entry[other.capacity]), size(other.size), capacity(other.capacity) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        ++objectCount;
    }

    ~Impl() {
        delete[] data;
        --objectCount;
    }

    Impl& operator=(const Impl& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new Entry[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Entry* find(const std::string& key) {
        for (size_t i = 0; i < size; ++i) {
            if (data[i].key == key) {
                return &data[i];
            }
        }
        return nullptr;
    }

    const Entry* find(const std::string& key) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i].key == key) {
                return &data[i];
            }
        }
        return nullptr;
    }

    void resize() {
        capacity *= 2;
        Entry* newData = new Entry[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    static int objectCount;
};

int Map::Impl::objectCount = 0;

Map::Map() : pImpl(new Impl) {}
Map::Map(const Map& other) : pImpl(new Impl(*other.pImpl)) {}
Map& Map::operator=(const Map& other) {
    if (this != &other) {
        *pImpl = *other.pImpl;
    }
    return *this;
}
Map::~Map() {
    delete pImpl;
}

int Map::getObjectCount() {
    return Impl::objectCount;
}

void Map::insert(const std::string& key, const std::string& value) {
    if (pImpl->find(key)) {
        throw std::invalid_argument("Key already exists");
    }
    if (pImpl->size == pImpl->capacity) {
        pImpl->resize();
    }
    pImpl->data[pImpl->size++] = {key, value};
}

std::string Map::select(const std::string& key) const {
    auto entry = pImpl->find(key);
    if (!entry) {
        throw std::invalid_argument("Key not found");
    }
    return entry->value;
}

void Map::update(const std::string& key, const std::string& value) {
    auto entry = pImpl->find(key);
    if (!entry) {
        throw MyException("Special update error: key not found");
    }
    entry->value = value;
}

void Map::remove(const std::string& key) {
    for (size_t i = 0; i < pImpl->size; ++i) {
        if (pImpl->data[i].key == key) {
            for (size_t j = i; j < pImpl->size - 1; ++j)
                pImpl->data[j] = pImpl->data[j + 1];
            --pImpl->size;
            return;
        }
    }
    throw std::invalid_argument("Key not found for deletion");
}

std::string Map::toString() const {
    std::ostringstream oss;
    oss << "Map with " << pImpl->size << " entries.";
    return oss.str();
}

bool Map::operator==(const Map& other) const {
    if (pImpl->size != other.pImpl->size) {
        return false;
    }
    for (size_t i = 0; i < pImpl->size; ++i) {
        if (!(pImpl->data[i] == other.pImpl->data[i])) {
            return false;
        }
    }
    return true;
}

bool Map::operator!=(const Map& other) const {
    return !(*this == other);
}

bool Map::operator<(const Map& other) const {
    return pImpl->size < other.pImpl->size;
}

bool Map::operator>(const Map& other) const {
    return pImpl->size > other.pImpl->size;
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
    for (size_t i = 0; i < pImpl->size; ++i){
        pImpl->data[i].value = "";
    }
    return *this;
}

Map& Map::operator!() {
    pImpl->size = 0;
    return *this;
}

int Map::operator[](const std::string& value) const {
    for (size_t i = 0; i < pImpl->size; ++i) {
        if (pImpl->data[i].value == value) {
            return static_cast<int>(i);
        }
    }
    throw MyException("Value not found");
}

} // namespace MyProject