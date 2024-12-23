#pragma once
#include <dpp/dpp.h>

class Command {
    public:
        std::string name;
        std::string description;
        int commands;
        virtual dpp::task<void> Execute(dpp::cluster& bot, const dpp::slashcommand_t& event) = 0;
};
