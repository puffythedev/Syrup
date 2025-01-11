#pragma once
#include <dpp/dpp.h>

struct GuildGreeterConfig {
	dpp::snowflake ID;
	bool enabled;
	dpp::embed joinEmbed;
	dpp::embed leaveEmbed;
	std::string joinMessage;
	std::string leaveMessage;
	dpp::snowflake joinChannel;
	dpp::snowflake leaveChannel;
};