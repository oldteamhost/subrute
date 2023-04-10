#include "input.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "menu.h"


void file_import::import_file(const std::string& filename, std::vector<std::string>& data)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        file_not_found(filename.c_str());
        return;
    }

    std::string line;
    int i = 0;
    while (std::getline(file, line) && i < MAX_LINES) {
        data.push_back(line);
        i++;
    }
}

