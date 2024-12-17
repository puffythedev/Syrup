#include "commands/commands.hpp"
#include <dpp/dpp.h>

std::string readFile(std::string name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + name);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::map<std::string, func> commands;

void collect(){
    commands["ping"] = c_ping;
    commands["roleall"] = c_roleall;
}

int main() {
    std::string token = readFile(".token");

	dpp::cluster bot(token, dpp::intents::i_all_intents, 0U, 0U, 1U, false);
    bot.intents = dpp::intents::i_all_intents;
    bot.cache_policy.guild_policy = dpp::cache_policy_setting_t::cp_aggressive;
    bot.cache_policy.user_policy = dpp::cache_policy_setting_t::cp_aggressive;
    bot.cache_policy.role_policy = dpp::cache_policy_setting_t::cp_aggressive;
    //bot.cache_policy.guild_policy = dpp::cache_policy_setting_t::cp_aggressive;
    collect();
	 
	bot.on_log(dpp::utility::cout_logger());
	 
	bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) -> dpp::task<void> {
        if(commands.find(event.command.get_command_name()) != commands.end()){
            co_await commands[event.command.get_command_name()](bot, event);
            co_return;
        } else {
            dpp::message msg("Command not found");
            msg.set_flags(dpp::m_ephemeral);

            co_await event.co_reply(msg);
            co_return;
        }
	});
	 
	bot.on_ready([&bot](const dpp::ready_t& event) {
	    if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand roleall("roleall", "give all users a role", bot.me.id);
            roleall.add_option(dpp::command_option(dpp::co_role, "role", "Role to distribute", true));

            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(roleall);
	    }
	});

	bot.start(dpp::st_wait);
    
    return 0;
}