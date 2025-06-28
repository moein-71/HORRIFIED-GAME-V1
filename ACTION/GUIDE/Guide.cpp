#include "Guide.hpp"
#include <bits/stdc++.h>

using namespace std;

void Guide::Activate(Game& game, Hero* hero){

    bool Hozoor = 0;
    string now_place = game.*hero ->get_now_place();
    auto neighbor = game.Game_map.get_connection(now_place);

    auto vector_villager_info = game.Game_map.get_villager(now_place);
    if(!vector_villager_info.empty()){

        Hozoor = 1;
        cout << "Villagers who are in our current location.\n";
        for(auto villager: vector_villager_info){
            cout << "Villager's name: " << villager.get_name() << setw(5);
        }

        cout << "_______________________________________________________\n";
    }
    for(auto neighbor_place_name: neighbor){

        vector_villager_info = game.Game_map.get_villager(neighbor_place_name);
        if(!vector_villager_info.empty()){

            Hozoor = 1;
            cout << "Villagers who are in location " << neighbor_place_name << '\n';
            for(auto villager: vector_villager_info){
                cout << "Villager's name: " << villager.get_name() << setw(5);
            }  
            cout << "_______________________________________________________\n";
        }
    }
    if(!Hozoor){
        cerr << "Unfortunately, there are no villagers in your neighborhood and you cannot use this action.\n";
        return;
    }

    string choose;
    string report;
    string villager_name;
    string choose_place_name;
    while(1){

        cout << "If you want to send the villager from your current location to somewhere, enter the letter A\n"
        << "if you want to bring the villager from a neighbor to your current location, enter the letter B.\n"
        << "or write exit to stop this action.\n";
        getline(cin, choose);

        if(choose == "exit")
            break;
        
        else if(choose == "A"){

            while(1){
                cout << "Please write the name of the place you want to send the villager to or write exit.\n";
                getline(cin, choose_place_name);

                if(choose_place_name == "exit")
                    break;
                

                cout << "Please enter villager's name or write exit.\n";
                getline(cin, villager_name);

                if(villager_name == "exit")
                    break;

                report = send_villager_another_place(now_place, choose_place_name, villager_name, neighbor, game);
                cout << report << '\n';
            }
        } 
        else if(choose == "B"){
            
            while(1){
                cout << "Please write the name of the place where you want to get the village from or write exit.\n";
                getline(cin, choose_place_name);

                if(choose_place_name == "exit")
                    break;

                cout << "Please enter villager's name or write exit.\n";
                getline(cin, villager_name);

                if(villager_name == "exit")
                    break;

                report = take_villager_another_place(now_place, choose_place_name, villager_name, neighbor, game);
                cout << report << '\n';
            }
        }
        else{
            cerr << "Please enter the right command.\n";
        }
    }
}
string Guide::send_villager_another_place(string now_place, string choose_place_name, string villager_name, vector<string> neighbor, Game& game){

    bool Hozoor = 0;
    auto villager_info = game.Game_map.get_villager(now_place);
    for(auto villager: villager_info){
        if(villager.get_name() == villager_name){
            Hozoor = 1;
            break;
        }
    }
    if(!Hozoor)
        return "The villager name you entered does not exist at the current location.(field)";

    Hozoor = 0;
    for(auto place_name: neighbor){
        if(choose_place_name == place_name){
            Hozoor = 1;
            break;
        }
    }
    if(!Hozoor)
    return "The place name you entered does not exist at neighbor of the current location.(field)";

    game.Game_map.set_villager_place(now_place, choose_place_name, villager_name);

}
string Guide::take_villager_another_place(string now_place, string choose_place_name, string villager_name, vector<string> neighbor, Game& game){

    bool Hozoor = 0;
    for(auto place_name: neighbor){
        if(choose_place_name == place_name){
            Hozoor = 1;
            break;
        }
    }
    if(!Hozoor)
    return "The place name you entered does not exist at neighbor of the current location.(field)";

    auto villager_info = game.Game_map.get_villager(choose_place_name);
    for(auto villager: villager_info){
        if(villager.get_name() == villager_name){
            Hozoor = 1;
            break;
        }
    }
    if(!Hozoor)
        return "The villager name you entered does not exist at the current location.(field)";

    game.Game_map.set_villager_place(choose_place_name, now_place, villager_name);
}