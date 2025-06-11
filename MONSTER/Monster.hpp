#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

class Monster{

    public:

        Monster() = default;
        Monster(int, std::string, std::vector<std::string>const);

        int get_frenzy()const;
        std::string get_name()const;
        std::string get_now_place()const;
        std::vector <std::string> get_spawn_place()const;

        void set_now_place(std::string);

    private:

        const int frenzy;
        const std::string name;
        std::string now_place;
        std::vector <std::string> const spawn_place;
};

#endif