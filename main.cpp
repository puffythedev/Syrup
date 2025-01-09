#include <syrup.hpp>

std::map<std::string, Command*> commands;
std::string readFile(std::string name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + name);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void collect(){
    commands["ping"] = std::move(new Ping());
    commands["roleall"] = std::move(new Roleall());
    commands["help"] = std::move(new Help());
    commands["clear"] = std::move(new Clear());
    commands["balance"] = std::move(new Balance());
}

int main() {
    std::signal(SIGINT, signalHandler);
    dbInit();
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
            Command* cmd = commands[event.command.get_command_name()];

            co_await cmd->Execute(bot, event);

            co_return;
        } else {
            dpp::message msg("Command not found");
            msg.set_flags(dpp::m_ephemeral);

            co_await event.co_reply(msg);
            co_return;
        }
	});

    bot.on_select_click([&bot](const dpp::select_click_t & event) -> dpp::task<void> {
         if(event.custom_id == "helpcmd")
            co_await help_eventA(bot, event);
        co_return;
    });
	 
	bot.on_ready([&bot](const dpp::ready_t& event) -> dpp::task<void> {
	    if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand roleall("roleall", "give all users a role", bot.me.id);
            roleall.add_option(dpp::command_option(dpp::co_role, "role", "Role to distribute", true));
            
            dpp::slashcommand clear("clear", "Delete a set of messages", bot.me.id);
            clear.add_option(dpp::command_option(dpp::co_string, "amount", "Amount of messages to clear", true));
            
            dpp::slashcommand ping("ping", "Ping pong!", bot.me.id);
            
            dpp::slashcommand help("help", "Show all commands!", bot.me.id);

            dpp::slashcommand bal("sugar", "Get your balance!", bot.me.id);
            bal.add_option(dpp::command_option(dpp::co_user, "user", "User to retrieve info about"));
            
            bot.global_bulk_command_create({ roleall, clear, ping, help, bal });

            bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_watching, "the chats!"));
	    }

        co_return;
	});

	bot.start(dpp::st_wait);
    
    return 0;
}