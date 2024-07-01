#include "LinkedHashMap.h"
#include <fstream>

template<typename K, typename V>
void LinkedHashMap<K, V>::put(const K& key, const V& value) {
    auto it = map.find(key);
    if (it != map.end()) {
        it->second.first = value;
    } else {
        order.push_front(key);
        map[key] = {value, order.begin()};
    }
}

template<typename K, typename V>
V LinkedHashMap<K, V>::get(const K& key) {
    auto it = map.find(key);
    if (it == map.end()) {
        throw std::runtime_error("Key not found");
    }
    return it->second.first;
}

template<typename K, typename V>
void LinkedHashMap<K, V>::remove(const K& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        order.erase(it->second.second);
        map.erase(it);
    }
}

template<typename K, typename V>
void LinkedHashMap<K, V>::save_to_file(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    for (const auto& key : order) {
        const auto& value = map[key].first;
        out.write(reinterpret_cast<const char*>(&key), sizeof(key));
        out.write(reinterpret_cast
