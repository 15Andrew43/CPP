#include <iostream>
#include <map>
//#include <fstream>

class Database {
private:
    std::map<std::string, std::map<std::string, size_t >> database_;
public:
    Database() = default;
    void NewPurchase(const std::string& name, const std::string& product, size_t cnt) {
        database_[name][product] += cnt;
    }
    void AllInformation() const {
        for (const auto& [name, basket] : database_) {
            std::cout << name << ":\n";
            for (const auto& [product, cnt] : basket) {
                std::cout << product << ' ' << cnt << '\n';
            }
        }
    }
};


int main() {
    Database database;
//    std::fstream fin("input.txt");
    std::string name;
    std::string product;
    size_t cnt;
    while (std::cin >> name) {
        std::cin >> product >> cnt;
        database.NewPurchase(name, product, cnt);
    }
    database.AllInformation();
//    fin.close();
    return 0;
}