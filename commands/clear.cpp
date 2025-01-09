#include <commands/clear.hpp>

dpp::embed errEmbed(){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title("Clear - Error");
    mainmenu.set_description("Something went Wrong!");
    mainmenu.set_color(0xd638d8);
    mainmenu.set_footer("Made with ❤ using D++!", "https://dpp.dev/DPP-Logo.png");
    return mainmenu;
}

dpp::embed deledEmbed(std::string msgs){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title("Clear - Deleted!");
    mainmenu.set_description("Cleared " + msgs + " Messages!");
    mainmenu.set_color(0xd638d8);
    mainmenu.set_footer("Good job", "");
    return mainmenu;
}

dpp::task<void> Clear::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event){
    dpp::snowflake channel = event.command.channel_id;
    dpp::channel* c = dpp::find_channel(channel);

    if (!c || !c->get_user_permissions(event.command.member).can(dpp::p_manage_messages)){
        co_await event.co_reply(dpp::message(errEmbed()).set_flags(dpp::m_ephemeral));

        co_return;
    }

    std::string str = std::get<std::string>(event.get_parameter("amount"));
    int amount = std::stoi(str);

    auto conf_msgs = co_await bot.co_messages_get(event.command.channel_id, 0, 0, 0, amount);
    
    if(conf_msgs.is_error()){
        co_await event.co_reply(dpp::message("Something went wrong").set_flags(dpp::m_ephemeral));

        co_return;
    }


    dpp::message_map msgs = std::get<dpp::message_map>(conf_msgs.value);
    std::vector<dpp::snowflake> messages;
    for(auto& [id, msg] : msgs){
        messages.push_back(id);
    }
    co_await event.co_thinking();

    co_await bot.co_message_delete_bulk(messages, event.command.channel_id);
    
    co_await event.co_edit_original_response(dpp::message(deledEmbed(std::to_string(messages.size()))));
}