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
    dpp::snowflake user = std::get<dpp::snowflake>(event.get_parameter("user"));
    User user = getUser(event.command.usr.id);
    if(user.ID == 0){
        createUser(event.command.usr.id);
        user = getUser(event.command.usr.id);
    }

    co_await event.co_reply(dpp::message(balEmbed(user, event.command.usr.username)));
    
    co_return;
}