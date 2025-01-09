#pragma once
#include <dpp/dpp.h>
#include <vector>

struct Item {
    int id;
    bool confiscated;
    std::string name;
    std::string emoji;
};

struct User {
    dpp::snowflake ID;
    int balance;
    bool banned;
    std::vector<Item> stuff;
};

User getUser(dpp::snowflake id);
bool createUser(dpp::snowflake id);
bool deleteUser(dpp::snowflake id);

bool banUser(dpp::snowflake id);
bool unbanUser(dpp::snowflake id);

bool setMoney(dpp::snowflake id, int money);
bool resetMoney(dpp::snowflake id);
bool addMoney(dpp::snowflake id, int money);
bool setMoney(dpp::snowflake id, int money);
bool subMoney(dpp::snowflake id, int money);

bool setInventory(dpp::snowflake id, std::vector<Item> items);
bool resetInventory(dpp::snowflake id);
bool addItem(dpp::snowflake id, Item item);
bool remItem(dpp::snowflake id, Item item);

bool dbInit();
bool loadUsersFromFile(const std::string& filename, std::map<dpp::snowflake, User>& users);
bool saveUsersToFile(const std::string& filename, const std::map<dpp::snowflake, User>& users);

void signalHandler(int signum);