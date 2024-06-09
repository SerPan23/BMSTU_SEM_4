#ifndef FUNCS_H
#define FUNCS_H

#include <map>
#include <string>
#include <vector>

class Funcs
{
public:
    using func_ptr = double (*)(double, double);
    using Iterator = std::map<std::string, func_ptr>::iterator;
    using SaveData = std::pair<std::string, func_ptr>;
    using funcList = std::vector<Funcs::SaveData>;

    Funcs() = default;
    explicit Funcs(std::shared_ptr<funcList> data);

    void add(std::string name, func_ptr func);
    void remove(std::string name);
    func_ptr get(std::string name);

    void clear();

    Iterator begin();
    Iterator end();

private:
    std::map<std::string, func_ptr> funcs;
};

#endif // FUNCS_H
