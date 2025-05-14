#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

class Company {
    std::string m_name;
    std::string m_profit_tax;
    std::string m_address;

    public:

    Company() {}
    Company(const std::string &_m_name, const std::string &_m_profit_tax, const std::string &_m_address) :
        m_name(_m_name), m_profit_tax(_m_profit_tax), m_address(_m_address) {}

    std::string name() const { return m_name; }
    std::string &name() { return m_name; }
    std::string profit_tax() const { return m_profit_tax; }
    std::string &profit_tax() { return m_profit_tax; }
    std::string address() const { return m_address; }
    std::string &address() { return m_address; }

    friend std::ostream &operator<<(std::ostream &os, const Company &C) {
        return os << C.name() << '|' << C.profit_tax() << '|' << C.address();
    }
};

std::vector<Company> get_company_list(std::ifstream &istr) {
    std::vector<Company> company_list;
    std::string i_string;
    std::getline(istr, i_string);
    while (std::getline(istr, i_string)) {
        int i = std::find(i_string.begin(), i_string.end(), '|') - i_string.begin();
        std::string c_name = i_string.substr(0, i);
        int j = std::find(i_string.begin() + i + 1, i_string.end(), '|') - i_string.begin();
        std::string c_profit_tax = i_string.substr(i + 1, j - (i + 1));
        std::string c_address = i_string.substr(j + 1);
        company_list.push_back(Company(c_name, c_profit_tax, c_address));
    }
    return company_list;
}

int hashString(const std::string &company_name) {
    const int p = 31;
    const int m = 2000;

    std::string s = (company_name.size() >= 20U ? company_name.substr(company_name.length() - 20U) : company_name);

    int hash_value = 0;
    int p_power = 1;

    for (int i = 0; i < (int)s.length(); i++) {
        hash_value = (hash_value + (s[i] * p_power) % m) % m;
        p_power = (p_power * p) % m;
    }

    return hash_value;
}

template<class T> class HashTable {
    std::vector<T*> m;
    int max_size = 0, current_size = 0;

    public:

    HashTable() {}

    HashTable(int _size) : m(_size, nullptr), max_size(_size) {}

    void insert(int key, T obj) {
        if (current_size == max_size)
            return;

        key %= max_size;

        // Linear probing
        while (m.at(key) != nullptr)
            key = (key + 1) % max_size;
            
        m.at(key) = new T(obj), current_size++;
    }

    template<class I> T *query(int key, I identifier) {
        key %= max_size;
        int counter = 1;
        while (counter > 0 && (m.at(key) == nullptr || !identifier(m.at(key)))) {
            if (m.at(key) == nullptr)
                return nullptr;
            key = (key + 1) % max_size;
            counter--;
        }
        return (counter > 0 ? m.at(key) : nullptr);
    }
};

HashTable<Company> *createHashTable(const std::vector<Company> &list_company) {
    HashTable<Company> *hash_table = new HashTable<Company>(2000);
    for (const Company &c : list_company)
        hash_table->insert(hashString(c.name()), c);
    return hash_table;
}

void insert(HashTable<Company> *hash_table, const Company &company) {
    hash_table->insert(hashString(company.name()), company);
}

Company *search(HashTable<Company> *hash_table, const std::string &company_name) {
    return hash_table->query(hashString(company_name), [&](Company *obj) -> bool {
        return obj->name() == company_name;
    });
}

int main(int argc, char *argv[]) {
    if (argc < 4)
        return 1;

    std::ifstream company_list_stream(argv[1]);
    std::ifstream queries_stream(argv[2]);
    if (!company_list_stream.is_open() || !queries_stream.is_open())
        return 2;

    std::ofstream answer_stream(argv[3]);

    std::vector<Company> company_list = get_company_list(company_list_stream);
    HashTable<Company> *H = createHashTable(company_list);

    // answer_stream << company_list.size() << std::endl;

    std::string query_name;
    while (std::getline(queries_stream, query_name)) {
        Company *f = search(H, query_name);
        if (f != nullptr)
            answer_stream << *f << std::endl;
        else
            std::cout << "Search failed!" << std::endl;
    }

    return 0;
}