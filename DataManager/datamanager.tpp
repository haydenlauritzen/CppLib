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
#include <string>

template <typename T> class DataManager {

public:
    /**
     * @brief Writes map contents to file
     * @tparam T - map value
     * @param data - map of data to write
     * @param id   - filename label
     */
    template <typename T> void DataManager<T>::write(std::map<int, T> data, std::string id) {

        std::string filename = "./data/" + id + ".dat/";
        std::fstream fs(filename);

        for(std::pair<int, T> entry : data) {
            const auto& [key, value] = entry;
            std::string line;
            line << key << " ";
            for(T value : entry) {
                line << entry;
            }
            line << '\n' line >> fs;
        }
        fs.close();
    }

    /**
     * @brief Reads map contents from file
     * To be implemented per data type
     * @tparam T - map value
     * @param id   - filename label
     * @return std::map<int, T> data from file
     */
    template <typename T> virtual std::map<int, T> DataManager<T>::read(std::string id);
};
