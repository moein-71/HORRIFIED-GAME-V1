#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item{

    public:

        Item(std::string, std::string, std::string, int);

        std::string get_name()const;
        std::string get_spawn_place()const;
        std::string get_color()const;
        int get_strength()const;

        void set_name(std::string);
        void set_spawn_place(std::string);
        void set_color(std::string);
        void set_strength(int);

    private:

        std::string name;
        std::string spawn_place;
        std::string color;
        int strength;
};

#endif //ITEM_H