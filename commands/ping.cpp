#include <dpp/dpp.h>
#include <commands/ping.hpp>

dpp::task<void> Ping::Execute(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    co_await event.co_reply("Pong");
    
    co_return;
}