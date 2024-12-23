#pragma once
#include "../command.hpp"

class Ping : public Command {
    public:
        std::string name;
        std::string description;
        int commands;
        dpp::task<void> Execute(dpp::cluster& bot, const dpp::slashcommand_t& event);
};