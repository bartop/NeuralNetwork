#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>

namespace CSV {

/**
 * @brief Klasa reprezentująca pojedynczą wartość z pliku CSV.
 */
class Item {
    std::string m_value;
public:
    /**
     * @brief Konstruktor inicjalizujący wartość łańcuchem znaków.
     * @param value znakowa reprezentacja wartości z pliku CSV
     */
    Item(const std::string &value);

    /**
     * @brief Konstruktor inicjalizujący wartość wartością liczbową, zmiennoprzecinkową.
     * @param value wartość liczbowa
     */
    Item(double value);

    /**
     * @brief Sprawdza czy dana wartość jest wartością liczbową.
     * @return true jeśli dana wartość jest liczbą, false w przeciwnym wypadku
     */
    bool isNumeric() const;

    /**
     * @brief Operator konwersji na double, nie należy wywoływać jeżeli wartość nie jest wartością liczbową.
     * @return liczbowa reprezentacja wartości
     * @see CSV::Item::isNumeric
     */
    operator double() const;

    /**
     * @brief Zwraca tekstową reprezentację wartości, można wywoływać nawet dla pól będących liczbami.
     * @return tekstowa reprezentacja komórki
     */
    operator std::string() const;
};

/**
 * @brief Klasa reprezentująca pojedynczy rząd w pliku CSV.
 */
class Row {
    std::vector<std::string> m_header;
    std::vector<Item> m_items;

public:
    /**
     * @brief Konstruktor przyjmujący wartości i nagłówek
     * @param items wektor wartości w danym rzędzie
     * @param header nagłówek rzędu (nazwy kolumn)
     */
    Row(const std::vector<std::string> &items, const std::vector<std::string> &header);

    /**
     * @brief Zwraca element pod daną nazwą z nagłówka.
     * @param columnName nazwa kolumny
     * @return znaleziony element
     */
    Item operator[](const std::string &columnName);

    /**
     * @brief Zwraca wszystkie wartości w rzędzie.
     * @return wektor wartości w tym rzędzie
     */
    const std::vector<Item> &getItems() const;

    /**
     * @brief Usuwa wartość pod podanym indeksem.
     * @param index indeks wartości do usunięcia.
     */
    void remove(std::size_t index);
};

/**
 * @brief Klasa reprezentująca kolumnę z pliku CSV.
 */
class Column {
    const std::string m_name;
    std::vector<Item> m_items;

public:
    /**
     * @brief Konstruktor inicjalizujący wszystkie wartości.
     * @param name nazwa kolumny
     * @param rows rzędy, z których odpowiednie wartości zostaną pobrane
     * @param index indeks kolumny w przekazanych rzędach
     */
    Column(const std::string &name, const std::vector<Row> &rows, std::size_t index);

    /**
     * @brief Zwraca wszystkie elementy w tej kolumnie.
     * @return wektor elementów z kolumny
     */
    const std::vector<Item> &getItems() const;

    /**
     * @brief Sprawdza, czy wszystkie elementy w kolumnie jest wartością liczbową.
     * @return true jeśli wszystkie elementy w kolumnie są liczbami, false w przeciwnym wypadku
     */
    bool isNumeric() const;

    /**
     * @brief Zwraca nazwę kolumny.
     * @return nazwa kolumny
     */
    const std::string &getName() const;
};

/**
 * @brief Klasa reprezentująca dane zapisywalne w formacie CSV
 */
class Data {
    char m_lineSeparator = '\n';
    char m_itemSeparator = ',';

    std::vector<std::string> m_header;
    std::vector<Row> m_rows;

    std::vector<std::string> split(const std::string &row);

public:
    /**
     * @brief Konstruktor, wczytujący dane z pliku.
     * @param filePath ścieżka do pliku CSV.
     */
    Data(const std::string &filePath);

    /**
     * @brief Konstruktor kopiujący.
     */
    Data(const Data &);

    /**
     * @brief Konstruktor bezargumentowy, tworzy puste dane.
     */
    Data();

    /**
     * @brief Zwraca nagłówek pliku.
     * @return nagłówek w postaci wektora tekstów
     */
    const std::vector<std::string> getHeader() const;

    /**
     * @brief Zwraca wszystkie rzędy wartości.
     * @return Wektor rzędów.
     */
    const std::vector<Row> getRows() const;

    /**
     * @brief Zwraca wszystkie kolumny wartości.
     * @return wektor kolumn
     */
    const std::vector<Column> getColumns() const;

    /**
     * @brief Zwraca kolumnę o podanej nazwie.
     * @param columnName nazwa kolumny
     * @return znaleziona kolumna
     */
    const Column getColumn(const std::string &columnName) const;

    /**
     * @brief Dodaje ostatni rząd do danych CSV.
     * @param row rząd do dodania.
     */
    void addRow(const std::vector<std::string> &row);

    /**
     * @brief Ustawia nagłówek.
     * @param header nagłówek (nazwy kolumn)
     */
    void setHeader(const std::vector<std::string> &header);

    /**
     * @brief Usuwa kolumnę pod podanym indeksem.
     * @param columnIndex indeks kolumny do usunięcia.
     */
    void removeColumn(std::size_t columnIndex);

    /**
     * @brief Usuwa kolumnę o podanej nazwie.
     * @param columnName nazwa kolumny do usunięcia.
     */
    void removeColumn(const std::string &columnName);

    /**
     * @brief Zapisuje dane do pliku pod wskazaną ścieżką.
     * @param filePath ścieżka do pliku, plik musi być zapisywalny
     */
    void save(const std::string &filePath);
};
}
