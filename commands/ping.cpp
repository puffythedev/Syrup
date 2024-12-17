#include <dpp/dpp.h>

dpp::coroutine<void> c_ping(dpp::cluster& bot, const dpp::slashcommand_t& event){
    co_await event.co_reply("Pong");
    
    co_return;
}