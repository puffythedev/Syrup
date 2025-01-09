#include <utils.hpp>

std::map<dpp::snowflake, User> users;
User null = { 0 };

bool dbInit(){
    return loadUsersFromFile("economy.sugar", users);
}

User getUser(dpp::snowflake id){
    if(users.find(id) == users.end())
        return null;
    
    return users[id];
}

bool createUser(dpp::snowflake id){
    if(users.find(id) != users.end())
        return false;
    
    User usr = {
        id,
        0,
        false,
        {}
    };

    users[id] = usr;

    return true;
}

bool deleteUser(dpp::snowflake id){
    if(users.find(id) == users.end())
        return false;
    
    users.erase(id);
    return true;
}

bool banUser(dpp::snowflake id){
    if(users.find(id) == users.end())
        return false;
    
    users[id].banned = true;
    return true;
}

bool unbanUser(dpp::snowflake id){
    if(users.find(id) == users.end())
        return false;
    
    users[id].banned = false;
    return true;
}

bool setMoney(dpp::snowflake id, int money){
    if(users.find(id) == users.end())
        return false;
    
    users[id].balance = money;
    return true;
}
bool resetMoney(dpp::snowflake id){
    if(users.find(id) == users.end())
        return false;
    
    users[id].balance = 0;
    return true;
}
bool addMoney(dpp::snowflake id, int money){
    if(users.find(id) == users.end())
        return false;
    
    users[id].balance += money;
    return true;
}

bool subMoney(dpp::snowflake id, int money){
    if(users.find(id) == users.end())
        return false;
    
    users[id].balance -= money;
    return true;
}

bool setInventory(dpp::snowflake id, std::vector<Item> items){
    if(users.find(id) == users.end())
        return false;
    
    users[id].stuff = items;
    return true;
}

bool resetInventory(dpp::snowflake id){
    if(users.find(id) == users.end())
        return false;
    
    users[id].stuff = {};
    return true;
}

bool addItem(dpp::snowflake id, Item item){
    if(users.find(id) == users.end())
        return false;
    
    users[id].stuff.push_back(item);
    return true;
}

bool remItem(dpp::snowflake id, Item item){
    if(users.find(id) == users.end())
        return false;

    std::vector<Item> its{};

    for(auto& itema : users[id].stuff){
        if(item.id != itema.id){
            its.push_back(itema);
        }
    }
    setInventory(id, its);

    return true;
}

bool saveUsersToFile(const std::string& filename, const std::map<dpp::snowflake, User>& users) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& [id, user] : users) {
        outFile << id << '\n';
        outFile << user.balance << '\n';
        outFile << user.banned << '\n';
        outFile << user.stuff.size() << '\n';

        for (const auto& item : user.stuff) {
            outFile << item.id << '\n';
            outFile << item.confiscated << '\n';
            outFile << item.name << '\n';
            outFile << item.emoji << '\n';
        }
    }

    outFile.close();
    return true;
}

bool loadUsersFromFile(const std::string& filename, std::map<dpp::snowflake, User>& users) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return false;
    }

    users.clear();
    dpp::snowflake id;
    while (inFile >> id) {
        User user;
        user.ID = id;

        inFile >> user.balance;
        inFile >> user.banned;

        size_t itemCount;
        inFile >> itemCount;

        user.stuff.resize(itemCount);
        for (size_t i = 0; i < itemCount; ++i) {
            Item item;
            inFile >> item.id;
            inFile >> item.confiscated;
            inFile.ignore();
            std::getline(inFile, item.name);
            std::getline(inFile, item.emoji);
            user.stuff[i] = item;
        }

        users[id] = user;
    }

    inFile.close();
    return true;
}

void signalHandler(int signum) {
    if (saveUsersToFile("economy.sugar", users)) {
        std::cout << "Users saved successfully.\n";
    } else {
        std::cerr << "Failed to save users.\n";
    }

    exit(signum);
}