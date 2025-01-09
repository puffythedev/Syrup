#include <dpp/dpp.h>
#include <commands/roleall.hpp>

dpp::task<void> Roleall::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    dpp::snowflake channel = event.command.channel_id;
    dpp::channel* c = dpp::find_channel(channel);
	dpp::confirmation_callback_t confirmation = co_await bot.co_guild_get(event.command.guild_id);
	dpp::guild* server;
    
    server = dpp::find_guild(event.command.guild_id);
    if (c && c->get_user_permissions(event.command.member).can(dpp::p_manage_roles)) {
        event.reply("Adding role to members...");
        for(auto& [id, member] : server->members){
            dpp::snowflake role = std::get<dpp::snowflake>(event.get_parameter("role"));
            bool has = false;
            auto roles = member.get_roles();
            for(auto rolea : roles){
                if(rolea == role)
                    has = true;
            }
            if(!has){
                bot.guild_member_add_role(server->id, id, role);
                co_await event.from->creator->co_sleep(1);
            }

        }
        event.co_edit_response("Done adding roles!");
        co_return;
	} else {
        co_await event.co_reply("Not enough perms lil bro.");
        co_return;
    }    
}