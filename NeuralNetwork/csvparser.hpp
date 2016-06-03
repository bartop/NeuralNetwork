#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>

namespace CSV {

class Item {
    std::string m_value;
public:
    Item(const std::string &value) : m_value(value) {

    }

    bool isNumeric() const {
        std::size_t index;

        try {
            std::stod(m_value, &index);
        } catch (...) {
            return false;
        }

        return index == m_value.size();
    }

    operator double() const {
        return std::stod(m_value);
    }

    operator std::string() const {
       return m_value;
    }
};

class Row {
    const std::vector<std::string> m_header;
    std::vector<Item> m_items;

public:
    Row(const std::vector<std::string> &items, const std::vector<std::string> &header) : m_header(header) {
        if (items.size() != header.size()) {
            throw new std::invalid_argument("Wrong items/header count!");
        }

        for (const auto &item : items) {
            m_items.push_back(Item(item));
        }
    }

    Item operator[](const std::string &columnName) {
        auto iter = std::find(m_header.begin(), m_header.end(), columnName);

        if (iter == m_header.end()) {
            throw new std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
        }

        return *std::next(m_items.begin(), std::distance(m_header.begin(), iter));
    }

    const std::vector<Item> &getItems() const {
        return m_items;
    }
};

class Data {
    char m_lineSeparator = '\n';
    char m_itemSeparator = ',';

    std::vector<std::string> m_header;
    std::vector<Row> m_rows;

    std::vector<std::string> split(const std::string &row) {
        std::vector<std::string> result;
        std::string item;

        for (const char c : row) {
            if (c == m_itemSeparator) {
                result.push_back(item);
                item.clear();
            } else {
                item.push_back(c);
            }
        }

        result.push_back(item);

        return result;
    }

public:
    Data(const std::string &filePath) {
        std::ifstream file(filePath);

        std::string header;
        std::getline(file,header,m_lineSeparator);

        m_header = split(header);

        while (file) {
            std::string line;
            std::getline(file,line,m_lineSeparator);
            if (line.empty()) {
                continue;
            }
            m_rows.push_back(Row(split(line), m_header));
        }
    }

    const std::vector<std::string> getHeader() const {
        return m_header;
    }

    const std::vector<Row> getRows() const {
        return m_rows;
    }

    const std::vector<Item> getColumn(const std::string &columnName) const {
        auto iter = std::find(m_header.begin(), m_header.end(), columnName);

        if (iter == m_header.end()) {
            throw new std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
        }

        auto index = std::distance(m_header.begin(), iter);

        std::vector<Item> column;

        for (const Row &row : m_rows) {
            column.push_back(row.getItems().at(static_cast<std::size_t>(index)));
        }

        return column;
    }
};
}
