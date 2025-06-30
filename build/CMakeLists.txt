# cmake_minimum_required(VERSION 3.5)

# project(fact)

# #set(CMAKE_CXX_STANDARD 14) for using version 14 compiler and now every one can use it 

# add_executable(app ../src/main.cpp)

# include_directories( ../Game ../Game_turn ../Game_turn/Turn_archaeologist ../Game_turn/Turn_mayor ../Game_turn/Turn_monster 
# ../Monster_action ../Monster_action/Kill ../Monster_action/Move_monster ../Monster_action/Power ../Monster_card ../Monster_card/card 
# ../Perk_card ../Perk_card/card ../ACTION ../ACTION/ADVANCE ../ACTION/DEFEAT ../ACTION/GUIDE ../ACTION/MOVE_HERO ../ACTION/PICK_UP 
# ../ACTION/SPECIAL_ACTION ../HERO ../ITEM ../MAP ../MONSTER ../Programm)

cmake_minimum_required(VERSION 3.5)
project(Game_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# لیست کامل فایل‌های سورس
add_executable(a.out
    # فایل‌های اصلی
    main.cpp
    Programm.cpp
    Game/Game.cpp
    
    # فایل‌های Game_turn
    Game_turn/Turn_archaeologist.cpp
    Game_turn/Turn_mayor.cpp
    Game_turn/Turn_monster.cpp
    
    # فایل‌های HERO
    HERO/Archaologist.cpp
    HERO/Hero.cpp
    HERO/Hero.hpp
    HERO/Mayor.hpp
    
    # فایل‌های ITEM
    ITEM/Item.cpp
    ITEM/Item.hpp
    
    # فایل‌های MAP
    MAP/Map.cpp
    MAP/Map.hpp
    
    # فایل‌های MONSTER
    MONSTER/Dracula.cpp
    MONSTER/Dracula.hpp
    MONSTER/Invisible_man.cpp
    MONSTER/Invisible_man.hpp
    MONSTER/Monster.cpp
    MONSTER/Monster.hpp
    
    # فایل‌های VILLAGER
    VILLAGER/Villager.cpp
    VILLAGER/Villager.hpp
    
    # فایل‌های ACTION
    ACTION/ADVANCE/Advance.cpp
    ACTION/ADVANCE/Advance.hpp
    ACTION/DEFEAT/Defeat.cpp
    ACTION/DEFEAT/Defeat.hpp
    ACTION/GUIDE/Guide.cpp
    ACTION/GUIDE/Guide.hpp
    ACTION/MOVE_HERO/Move_hero.cpp
    ACTION/MOVE_HERO/Move_hero.hpp
    ACTION/PICK_UP/Pick_Up.cpp
    ACTION/PICK_UP/Pick_Up.hpp
    ACTION/SPECIAL_ACTION/Special_Action.cpp
    ACTION/SPECIAL_ACTION/Special_Action.hpp
    ACTION/Hero_Action.hpp
    
    # فایل‌های Monster_card
    Monster_card/Monster_card.hpp
    Monster_card/card/Egyptian_Expert.cpp
    Monster_card/card/Egyptian_Expert.hpp
    Monster_card/card/Form_of_The_Bat.cpp
    Monster_card/card/Form_of_The_Bat.hpp
    Monster_card/card/Former_Employer.cpp
    Monster_card/card/Former_Employer.hpp
    Monster_card/card/Fortune_Teller.cpp
    Monster_card/card/Fortune_Teller.hpp
    Monster_card/card/Hurried_Assistant.cpp
    Monster_card/card/Hurried_Assistant.hpp
    Monster_card/card/Hypnotic_Gaze.cpp
    Monster_card/card/Hypnotic_Gaze.hpp
    Monster_card/card/On_The_Move.cpp
    Monster_card/card/On_The_Move.hpp
    Monster_card/card/Sunrise.cpp
    Monster_card/card/Sunrise.hpp
    Monster_card/card/The_Delivery.cpp
    Monster_card/card/The_Delivery.hpp
    Monster_card/card/The_Ichthyologist.cpp
    Monster_card/card/The_Ichthyologist.hpp
    Monster_card/card/The_Innocent.cpp
    Monster_card/card/The_Innocent.hpp
    Monster_card/card/Thief.cpp
    Monster_card/card/Thief.hpp
    
    # فایل‌های Perk_card
    Perk_card/Perk_card.cpp
    Perk_card/Perk_card.hpp
    Perk_card/card/Break_of_Dawn.cpp
    Perk_card/card/Break_of_Dawn.hpp
    Perk_card/card/Hurry.cpp
    Perk_card/card/Hurry.hpp
    Perk_card/card/Late_into_the_Night.cpp
    Perk_card/card/Late_into_the_Night.hpp
    Perk_card/card/Overstock.cpp
    Perk_card/card/Overstock.hpp
    Perk_card/card/Repel.cpp
    Perk_card/card/Repel.hpp
    Perk_card/card/Visit_from_the_Detective.cpp
    Perk_card/card/Visit_from_the_Detective.hpp
    
    # فایل‌های Monster_action
    Monster_action/Kill/Kill.cpp
    Monster_action/Kill/Kill.hpp
    Monster_action/Move_monster/Move_monster.cpp
    Monster_action/Move_monster/Move_monster.hpp
    Monster_action/Power/Power.cpp
    Monster_action/Power/Power.hpp
    Monster_action/Monster_action.hpp
)

# دایرکتوری‌های شامل
target_include_directories(a.out PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/ACTION
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Game_turn
    ${CMAKE_CURRENT_SOURCE_DIR}/HERO
    ${CMAKE_CURRENT_SOURCE_DIR}/ITEM
    ${CMAKE_CURRENT_SOURCE_DIR}/MAP
    ${CMAKE_CURRENT_SOURCE_DIR}/MONSTER
    ${CMAKE_CURRENT_SOURCE_DIR}/Monster_action
    ${CMAKE_CURRENT_SOURCE_DIR}/Monster_card
    ${CMAKE_CURRENT_SOURCE_DIR}/Monster_card/card
    ${CMAKE_CURRENT_SOURCE_DIR}/Perk_card
    ${CMAKE_CURRENT_SOURCE_DIR}/Perk_card/card
    ${CMAKE_CURRENT_SOURCE_DIR}/VILLAGER
)

# در صورت نیاز کتابخانه‌ها
find_package(Threads REQUIRED)
target_link_libraries(a.out PRIVATE Threads::Threads)