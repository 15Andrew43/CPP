#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

struct PersonInfo {
    std::set<std::string> phones_;
    std::string email_;
};

class PhoneBook {
    std::unordered_map<std::string, PersonInfo> data;
public:
    bool AddPerson(const std::string& name, const std::string& phone = "", const std::string& email = "") {
        if (data.count(name) == 0) {
            data[name].phones_ = std::set<std::string>();
            data[name].email_ = std::string();
            if (phone != "") {
                data[name].phones_.insert(phone);
            }
            if (email != "") {
                data[name].email_ = email;
            }
            return true;
        }
        return false;
    }
    bool AddPhone(const std::string& name, const std::string& phone) {
        if (data.count(name) > 0 && data[name].phones_.count(phone) == 0) {
            data[name].phones_.insert(phone);
            return true;
        }
        return false;
    }
    bool ReplaceEmail(const std::string& name, const std::string& new_email) {
        if (data.count(name) > 0) {
            data[name].email_ = new_email;
            return true;
        }
        return false;
    }
    bool ReplacePhone(const std::string& name, const std::string& old_phone, const std::string& new_phone) {
        if (data.count(name) > 0
            && data[name].phones_.count(old_phone) > 0 && data[name].phones_.count(new_phone) == 0) {
            data[name].phones_.erase(old_phone);
            data[name].phones_.insert(new_phone);
            return true;
        }
        return false;
    }
    bool DeletePerson(const std::string& name) {
        if (data.count(name) > 0) {
            data.erase(name);
            return true;
        }
        return false;
    }
    bool DeletePhone(const std::string& name, const std::string& phone) {
        if (data.count(name) > 0 &&  data[name].phones_.count(phone) > 0) {
            data[name].phones_.erase(phone);
            return true;
        }
        return false;
    }
    bool PrintPerson(const std::string& name)  {
        if (data.count(name) > 0) {
            std::cout << "Name: " << name << ";\n";
            if (data[name].phones_.size() > 0) {
                std::cout << "Phones: ";
                auto it = data[name].phones_.begin();
                for (; it != std::prev(data[name].phones_.end()); ++it) {
                    std::cout << *it << ", ";
                }
                std::cout << *it << ';';
                std::cout << '\n';
            }
            if (data[name].email_ != "")
                std::cout << "Email: " << data[name].email_ << ';' << '\n';
            return true;
        }
        return false;
    }
};

bool IsPhone(const std::string& word) {
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] <= '9' && word[i] >= '0') {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool IsEmail(const std::string& word) {
    bool IsEmail = false;
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] == '@') {
            IsEmail = true;
            break;
        }
    }
    return IsEmail;
}

void parse(std::string& line, std::vector<std::string>& wordsLine, std::string& name, std::string& phone1, std::string& phone2 , std::string& email) {
    std::string word = "";
    line.push_back(' ');
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] != ' ' && line[i] != '\n') {
            word.push_back(line[i]);
        } else {
//            std::cout << "word = " << word << '\n';
            wordsLine.push_back(word);
            word = "";
        }
    }

    for (int i = 1; i < wordsLine.size(); ++i) {
        if (IsPhone(wordsLine[i])) {
            if (phone1 == "")
                phone1 = wordsLine[i];
            else phone2 = wordsLine[i];
        } else if (IsEmail(wordsLine[i])) {
            email = wordsLine[i];
        } else {
            name = wordsLine[i];
        }
    }
}

int main() {
    PhoneBook book;
    std::string operation = "";
    std::string old_operation = "";

    while (true) {
//        std::cout << "====================\n";

        std::string line = "";
        std::string name = "";
        std::string phone1 = "";
        std::string phone2 = "";
        std::string email = "";
        getline(std::cin, line);
        std::vector<std::string> wordsLine;

        parse(line, wordsLine, name, phone1, phone2, email);
//        std::cout << line << '\n';
//        std::cout << wordsLine[0] << ' ' << wordsLine[1] << ' '
//                << wordsLine[2] << ' ' << wordsLine[3] << ' ' << wordsLine[4] << '\n';
        if (wordsLine[0] == "Finish") {
            break;
        }
        else if (wordsLine[0] == "AddPerson") {
            if (book.AddPerson(name, phone1, email)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "AddPhone") {
            if (book.AddPhone(name, phone1)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "ReplaceEmail") {
            if (book.ReplaceEmail(name, email)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "ReplacePhone") {
            if (book.ReplacePhone(name, phone1, phone2)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "DeletePerson") {
            if (book.DeletePerson(name)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "DeletePhone") {
            if (book.DeletePhone(name, phone1)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "FAIL\n";
            }
        }
        else if (wordsLine[0] == "PrintPerson") {
            if (book.PrintPerson(name)) {
                ;
            } else {
                std::cout << "FAIL\n";
            }
        }

        wordsLine.clear();
    }

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}