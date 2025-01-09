#include <dpp/dpp.h>
#include <commands/help.hpp>

void addcomp(dpp::message& msg){
    msg.add_component(
	    dpp::component().add_component(
	        dpp::component()
	            .set_type(dpp::cot_selectmenu)
	            .set_placeholder("Choose an option!")
	            .add_select_option(dpp::select_option("Home", "home", "Homepage").set_emoji("🏠"))
	            .add_select_option(dpp::select_option("Commands","cmds", "a list of Commands").set_emoji("📢"))
                .add_select_option(dpp::select_option("The team","team", "The team members!").set_emoji("🔨"))
	            .set_id("helpcmd")
	    )
	);
}

dpp::embed homeEmbed(){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title("Syrup - Help");
    mainmenu.set_description("Hi! i'm Syrup. Probably your new favorite discord bot!");
    mainmenu.set_color(0xd638d8);
    mainmenu.add_field("Commands", "4", true);
    mainmenu.add_field("Servers", std::to_string(dpp::get_guild_cache()->count()), true);
    mainmenu.set_footer("Made with ❤ using D++!", "https://dpp.dev/DPP-Logo.png");
    mainmenu.add_field("Library Version", "[" + std::string(DPP_VERSION_TEXT) + "](https://dpp.dev/)", false);
    return mainmenu;
}

dpp::embed cmdsEmbed(){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title("Syrup - Commands");
    mainmenu.set_description("I Currently have `4` Commands!");
    mainmenu.set_color(0xd638d8);
    mainmenu.add_field("/help", "```\nShows all commands\n```", false);
    mainmenu.add_field("/ping", "```\nReplies with Pong\n```", false);
    mainmenu.add_field("/roleall", "```\nGives all members the specified role\n```", false);
    mainmenu.add_field("/clear", "```\nDelete a set of messages\n```", false);
    mainmenu.set_footer("Made with ❤ using D++!", "https://dpp.dev/DPP-Logo.png");

    return mainmenu;
}

dpp::embed teamEmbed(){
    dpp::embed mainmenu = dpp::embed();
    mainmenu.set_title("Syrup - Team");
    mainmenu.set_description("There are currently `2` Team members!");
    mainmenu.set_color(0xd638d8);
    mainmenu.add_field("Puffy", "```\nThe developer!\n```", false);
    mainmenu.add_field("Carlyn", "```\nBot admin\n```", false);
//    mainmenu.add_field("/roleall", "```\nGives all members the specified role\n```", false);
//    mainmenu.add_field("/clear", "```\nDelete a set of messages\n```", false);
    mainmenu.set_footer("Made with ❤ using D++!", "https://dpp.dev/DPP-Logo.png");

    return mainmenu;
}

dpp::task<void> Help::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event){
    

    dpp::message msg(event.command.channel_id, homeEmbed());
    addcomp(msg);

    co_await event.co_reply(msg);
}

dpp::task<void> help_eventA(dpp::cluster& bot, const dpp::select_click_t & event){
    std::string val = event.values[0];
    dpp::user author = event.command.msg.interaction.usr;
    if(event.command.usr.id != author.id){
        dpp::message msg(event.command.channel_id, "This isn't meant for you!");
        msg.set_flags(dpp::m_ephemeral);

        co_await event.co_reply(msg);
        
        co_return;
    }

    if(val == "home"){
        dpp::message msg(event.command.channel_id, homeEmbed());
        addcomp(msg);

        co_await event.co_reply(dpp::ir_update_message, msg);
    } else if(val == "cmds") {
        dpp::message msg(event.command.channel_id, cmdsEmbed());
        addcomp(msg);

        co_await event.co_reply(dpp::ir_update_message, msg);
    } else if(val == "team") {
        dpp::message msg(event.command.channel_id, teamEmbed());
        addcomp(msg);

        co_await event.co_reply(dpp::ir_update_message, msg);
    }
}