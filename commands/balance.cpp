#include <dpp/dpp.h>
#include <commands/balance.hpp>
#include <utils.hpp>

dpp::embed balEmbed(User &user, std::string username){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title(username + "'s Balance!");
    mainmenu.add_field("Balance", "```\n" + std::to_string(user.balance) + "\n```", false);
    mainmenu.set_color(0xd638d8);
    mainmenu.set_footer("Good job", "");
    return mainmenu;
}

dpp::task<void> Balance::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    if(!sys.isAllowed(event.command.get_issuing_user().id.str())){
        co_await event.co_reply("You're on cooldown...");
        co_return;
    }
    dpp::snowflake user_id = event.get_parameter("user").index() == 0 ? event.command.get_issuing_user().id : std::get<dpp::snowflake>(event.get_parameter("user"));

	dpp::user* usah = dpp::find_user(user_id);

	if(!usah) {
		co_await event.co_reply("I failed to find that user.");
		co_return;
	}

    User user = getUser(user_id);
    if(user.ID == 0){
        createUser(user_id);
        user = getUser(user_id);
    }
    addMoney(user_id, 10);

    co_await event.co_reply(dpp::message(balEmbed(user, usah->username)));
    
    co_return;
}