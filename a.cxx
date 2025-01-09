#include <utils.hpp>

int main(){
    std::map<dpp::snowflake, User> users;

    saveUsersToFile("ecnonomy.sugar", users);
}