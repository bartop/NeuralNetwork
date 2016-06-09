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
    std::vector<std::string> m_header;
    std::vector<Item> m_items;

public:
    Row(const std::vector<std::string> &items, const std::vector<std::string> &header) : m_header(header) {
        if (items.size() != header.size()) {
            throw std::invalid_argument("Wrong items/header count!");
        }

        for (const auto &item : items) {
            m_items.push_back(Item(item));
        }
    }

    Item operator[](const std::string &columnName) {
        auto iter = std::find(m_header.begin(), m_header.end(), columnName);

        if (iter == m_header.end()) {
            throw std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
        }

        return *std::next(m_items.begin(), std::distance(m_header.begin(), iter));
    }

    const std::vector<Item> &getItems() const {
        return m_items;
    }

    void remove(std::size_t index) {
        if (index >= m_header.size()) {
            throw std::invalid_argument("Index exceedes columns number!");
        }
        m_header.erase(std::next(m_header.begin(), index));
        m_items.erase(std::next(m_items.begin(), index));
    }
};

class Column {
    const std::string m_name;
    std::vector<Item> m_items;

public:
    Column(const std::string &name, const std::vector<Row> &rows, std::size_t index) : m_name(name) {
        for (const auto &row : rows) {
            m_items.push_back(row.getItems().at(index));
        }
    }

    const std::vector<Item> &getItems() const {
        return m_items;
    }

    bool isNumeric() const {
        for (const auto &item : getItems()) {
            if (!item.isNumeric()) {
                return false;
            }
        }

        return true;
    }

    const std::string &getName() const {
        return m_name;
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

    const std::vector<Column> getColumns() const {
        std::vector<Column> columns;

        for (std::size_t i = 0; i < m_rows.size(); ++i) {
            columns.push_back(Column(m_header.at(i), m_rows, i));
        }

        return columns;
    }

    const Column getColumn(const std::string &columnName) const {
        auto iter = std::find(m_header.begin(), m_header.end(), columnName);

        if (iter == m_header.end()) {
            throw new std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
        }

        auto index = std::distance(m_header.begin(), iter);

        return Column(*iter, m_rows, index);
    }

    void removeColumn(std::size_t columnIndex) {
        for (auto &row : m_rows) {
            row.remove(columnIndex);
        }
    }

    void removeColumn(const std::string &columnName) {
       auto iter = std::find(m_header.begin(), m_header.end(), columnName);
       removeColumn(std::distance(m_header.begin(), iter));
    }
};
}
