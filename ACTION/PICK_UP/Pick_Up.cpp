#include "Pick_Up.hpp"
#include <bits/stdc++.h>

using namespace std;

void Pick_Up::Activate(Game& game, Hero* hero){

    string now_place = hero -> get_now_place();
    auto unordered_item = game.Game_map.get_item_of_place(now_place);

    for(auto pair_item: unordered_item){
        cout << "Item name: " << pair_item.first.get_name()
        << setw(10) << "Number item: " << pair_item.second;
    }

    int choose_number;
    string choose_name;
    string exeption_choose_number;

    cout << "You can stop pick_up item by write exit\n";

    while(1){

        cout << "Please enter name of item that you want or write exit to stop pick_up item.\n";
        getline(cin, choose_name);

        if(choose_name == "exit")
            break;

        cout << "Please enter number of item that you want.\n";
        getline(cin, exeption_choose_number);

        istringstream iss(exeption_choose_number);

        if(game.Game_map.Check_Count_Item_Place(now_place, choose_name)){

            if(iss >> choose_number && choose_number > 0 && choose_number <= game.Game_map.get_item_number(now_place, choose_name)){

                for(int i{game.Game_map.get_item_number(now_place, choose_name)}; i > 0; --i){

                    hero ->set_item(game.Game_map.Pickeup_Item(now_place, choose_name));
                }
            }
            else{
                cerr << "Please enter the right value;\n";
            }
        }
        else{
            cerr << "Please enter the right name of item.\n";
        }
    }
}