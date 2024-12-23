#pragma once
#include "../command.hpp"

class Help : public Command {
    public:
        std::string name;
        std::string description;
        int commands;
        dpp::task<void> Execute(dpp::cluster& bot, const dpp::slashcommand_t& event);
};

dpp::task<void> help_eventA(dpp::cluster& bot, const dpp::select_click_t & event);