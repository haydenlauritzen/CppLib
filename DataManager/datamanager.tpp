/**
 * @file datamanager.cpp
 * @author Hayden Lauritzen (haydenlauritzen@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

class DataManager {

public:
    /**
     * @brief Writes map contents to file
     * @param data - map of data to write
     * @param id   - filename label
     */
    template <typename K, typename V>
    void write(const std::unordered_map<K, V>& map, const std::string& filename) {

        const std::string path = "./data/" + filename + ".dat";
        std::filesystem::create_directories("./data");
        std::ofstream file(path, std::ios::out | std::ios::binary);

        if (file.good()) {
            std::uint32_t size = map.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(std::uint32_t));
            for (const auto& [key, value] : map) {
                std::uint32_t keySize = std::size(key);
                std::uint32_t valueSize = std::size(value);
                file.write(reinterpret_cast<const char*>(&keySize), sizeof(std::uint32_t));
                file.write(reinterpret_cast<const char*>(&valueSize), sizeof(std::uint32_t));
                file.write(key.data(), keySize);
                file.write(reinterpret_cast<const char*>(&value), valueSize);
            }
        }
        file.close();
    }

    /**
     * @brief Reads map contents from file
     * To be implemented per data type
     * @param filename   - filename label
     * @return std::map<int, T> data from file
     */
    template <typename K, typename V>
    std::unordered_map<K, V> DataManager::read(const std::string& filename) {

        const std::string path = "./data/" + filename + ".dat/";
        std::ifstream ifs(path, std::ios::binary);
        std::size_t mapSize;
        std::unordered_map<K, V> map;

        ifs.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
        for (std::size_t i = 0; i < mapSize; ++i) {
            std::size_t keySize, valueSize;
            ifs.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
            ifs.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));
            K key;
            V value;
            ifs.read(reinterpret_cast<char*>(&key), keySize);
            ifs.read(reinterpret_cast<char*>(&value), valueSize);
            map.emplace(std::move(key), std::move(value));
        }
        ifs.close();
        return map;
    }
};
