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
    commands["sugar"] = std::move(new Balance());
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

    bot.on_guild_member_add([&bot](const dpp::guild_member_add_t& event) -> dpp::task<void> {
        if(event.adding_guild->id == "1327612626590760971"){
            dpp::embed embed = dpp::embed();
            embed.set_description("_ _\n_ _　✦　　　　.　　　　  ➵　　　　♡\n　(✿ ˃ ˂) 　 ˳ `🥛` 　 ❀ welcome "+ event.added.get_user()->global_name +" to **The Sugar Factory**\n　♩`🍰`　﹒　◍ [01](https://discord.com/channels/1327612626590760971/1327623119447527444) [02](https://discord.com/channels/1327612626590760971/1327615007978033152) [03](https://discord.com/channels/1327612626590760971/1327617948227076177) ‹3\n　♡　﹒ 　 `🎀`✧ **Have a good time here!**\n_ _　✦　　　　.　　　　  ➵　　　　♡\n_ _");
            dpp::message msg(dpp::snowflake("1327612627353866273"), embed);
            bot.message_create(msg);
        }
        co_return;
        /*
_ _
_ _　✦　　　　.　　　　  ➵　　　　♡
　(✿ ˃ ˂) 　 ˳ `🥛` 　 ❀ farewell from **name**
　♩`🍰`　﹒　◍ we hate to see you go :( ‹3
　♡　﹒ 　 `🎀`✧ **We will miss you so much!**
_ _　✦　　　　.　　　　  ➵　　　　♡
_ _
         */
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

            dpp::slashcommand welcomer("welcome", "Welcomer commands.", bot.me.id);
	        welcomer.add_option(
	            dpp::command_option(dpp::co_sub_command, "toggle", "Toggle welcoming on or off.")
	        );
	        welcomer.add_option(
	            dpp::command_option(dpp::co_sub_command, "set", "Sets the welcoming embed.")
	        );

            dpp::slashcommand farewell("farewell", "Fareweller commands.", bot.me.id);
	        farewell.add_option(
	            dpp::command_option(dpp::co_sub_command, "toggle", "Toggle farewells on or off.")
	        );
	        farewell.add_option(
	            dpp::command_option(dpp::co_sub_command, "set", "Sets the farewell embed.")
	        );
            
            bot.global_bulk_command_create({ roleall, clear, ping, help, bal, welcomer, farewell });

            bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_watching, "the chats!"));
	    }

        co_return;
	});

	bot.start(dpp::st_wait);
    
    return 0;
}