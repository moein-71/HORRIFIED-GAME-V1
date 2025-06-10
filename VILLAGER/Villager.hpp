#ifndef VILLAGER_H
#define VILLAGER_H

#include <string>

class Villager{

    public:

        Villager(std::string, std::string, std::string);

        std::string get_name()const;
        std::string get_safe_place()const;
        std::string get_now_place()const;

        void set_name(std::string);
        void set_safe_place(std::string);
        void set_now_place(std::string);

    private:

        std::string name;
        std::string safe_place;
        std::string now_place;
};

#endif//VILLAGER_H