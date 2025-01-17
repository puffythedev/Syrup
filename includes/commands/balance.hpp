#pragma once
#include <command.hpp>
#include <cooldown.hpp>

class Balance : public Command {
    public:
        std::string name;
        std::string description;
        int commands;
        CooldownSystem sys;

        dpp::task<void> Execute(dpp::cluster& bot, const dpp::slashcommand_t& event);
};