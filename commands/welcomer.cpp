#include <dpp/dpp.h>
#include <commands/welcomer.hpp>

dpp::task<void> Welcomer::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event) {
	dpp::command_interaction cmd_data = event.command.get_command_interaction();

	auto subcommand = cmd_data.options[0];

	if (subcommand.name == "toggle") {
	    if (!subcommand.options.empty()) {
	        dpp::user user = event.command.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
			event.reply(user.get_mention() + " has now been turned into a dog."); 
        } else {
	        event.reply("No user specified");
	    }
	} else if (subcommand.name == "set") {
	    if (!subcommand.options.empty()) {
	        dpp::user user = event.command.get_resolved_user(subcommand.get_value<dpp::snowflake>(0));
	        event.reply(user.get_mention() + " has now been turned into a cat."); 
	    } else {
	        event.reply("No user specified");
	    }
	}

    co_return;
}