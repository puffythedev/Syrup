#include <dpp/dpp.h>
#include <greeter.hpp>

dpp::embed makeDefaultGreetingEmbed(){
	dpp::embed em = dpp::embed();
	em.set_title("I'm an embed!");
	em.set_description("This is a description!");
	em.set_color(0x000000);

	return em;
}

dpp::message makeDefaultGreetingMessage(){
	dpp::message he("I'm a message");
	he.add_embed(makeDefaultGreetingEmbed());
	return he;
}

void addSelectMenuEmbedEditingSystem(dpp::message& msg){
    msg.add_component(
	    dpp::component().add_component(
	        dpp::component()
	            .set_type(dpp::cot_selectmenu)
	            .set_placeholder("Choose an option!")
	            .add_select_option(dpp::select_option("Build Mode", "build", "Building the embed").set_emoji("🔨"))
	            .add_select_option(dpp::select_option("Preview Mode","preview", "Showing off the embed").set_emoji("🏠"))
                .add_select_option(dpp::select_option("Export", "export", "Export the embed to your collection!").set_emoji("🔖"))
	            .set_id("helpcmd")
	    )
	);
}

std::map<dpp::snowflake, GuildGreeterConfig> configs;