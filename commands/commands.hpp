#pragma once
#include <dpp/dpp.h>
#include <map>
typedef dpp::coroutine<void> (*func)(dpp::cluster&, const dpp::slashcommand_t&);

dpp::coroutine<void> c_ping(dpp::cluster& bot, const dpp::slashcommand_t& event);
dpp::coroutine<void> c_roleall(dpp::cluster& bot, const dpp::slashcommand_t& event);