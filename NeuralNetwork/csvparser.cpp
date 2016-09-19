#include "csvparser.h"

namespace CSV {


Item::Item(const std::string &value) : m_value(value) {

}

Item::Item(double value) : m_value(std::to_string(value)) {

}

bool Item::isNumeric() const {
    std::size_t index;

    try {
        std::stod(m_value, &index);
    } catch (...) {
        return false;
    }

    return index == m_value.size();
}

Item::operator double() const {
    return std::stod(m_value);
}

Item::operator std::string() const {
    return m_value;
}


Row::Row(const std::vector<std::string> &items, const std::vector<std::string> &header) : m_header(header) {
    if (items.size() != header.size()) {
        throw std::invalid_argument("Wrong items/header count!");
    }

    for (const auto &item : items) {
        m_items.push_back(Item(item));
    }
}

Item Row::operator[](const std::string &columnName) {
    auto iter = std::find(m_header.begin(), m_header.end(), columnName);

    if (iter == m_header.end()) {
        throw std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
    }

    return *std::next(m_items.begin(), std::distance(m_header.begin(), iter));
}

const std::vector<Item> &Row::getItems() const {
    return m_items;
}

void Row::remove(std::size_t index) {
    if (index >= m_header.size()) {
        throw std::invalid_argument("Index exceedes columns number!");
    }
    m_header.erase(std::next(m_header.begin(), index));
    m_items.erase(std::next(m_items.begin(), index));
}

Column::Column(const std::string &name, const std::vector<Row> &rows, std::size_t index) : m_name(name) {
    for (const auto &row : rows) {
        m_items.push_back(row.getItems().at(index));
    }
}

const std::vector<Item> &Column::getItems() const {
    return m_items;
}

bool Column::isNumeric() const {
    for (const auto &item : getItems()) {
        if (!item.isNumeric()) {
            return false;
        }
    }

    return true;
}

const std::string &Column::getName() const {
    return m_name;
}



std::vector<std::string> Data::split(const std::string &row) {
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

Data::Data(const std::string &filePath) {
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

Data::Data(const Data &) = default;
Data::Data(){}

const std::vector<std::string> Data::getHeader() const {
    return m_header;
}

const std::vector<Row> Data::getRows() const {
    return m_rows;
}

const std::vector<Column> Data::getColumns() const {
    std::vector<Column> columns;

    for (std::size_t i = 0; i < m_header.size(); ++i) {
        columns.push_back(Column(m_header.at(i), m_rows, i));
    }

    return columns;
}

const Column Data::getColumn(const std::string &columnName) const {
    auto iter = std::find(m_header.begin(), m_header.end(), columnName);

    if (iter == m_header.end()) {
        throw std::invalid_argument(std::string("Invalid column name '").append(columnName).append("'"));
    }

    auto index = std::distance(m_header.begin(), iter);

    return Column(*iter, m_rows, index);
}

void Data::addRow(const std::vector<std::string> &row) {
    if (row.size() == m_header.size())
    {
        m_rows.push_back(Row(row, m_header));
    } else
    {
        throw std::invalid_argument(std::string("Invalid row size!"));
    }
}

void Data::setHeader(const std::vector<std::string> &header) {
    if (header.size() != m_header.size() &&
            m_rows.size() > 0)
    {
        throw std::invalid_argument(std::string("Invalid header size!"));
    } else
    {
        m_header = header;
    }
}

void Data::removeColumn(std::size_t columnIndex) {
    m_header.erase(std::next(m_header.begin(), columnIndex));
    for (auto &row : m_rows) {
        row.remove(columnIndex);
    }
}

void Data::removeColumn(const std::string &columnName) {
    auto iter = std::find(m_header.begin(), m_header.end(), columnName);
    removeColumn(std::distance(m_header.begin(), iter));
}

void Data::save(const std::string &filePath)
{
    std::ofstream file(filePath);

    std::string separator = "";
    for (const auto &item : m_header)
    {
        file << separator << item;
        separator = m_itemSeparator;
    }


    for (const auto &row : m_rows)
    {
        file << m_lineSeparator;
        separator = "";
        for (const auto &item : row.getItems())
        {
            file << separator << item;
            separator = m_itemSeparator;
        }
    }

}
}
