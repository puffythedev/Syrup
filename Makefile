all:
	g++ main.cpp commands/*.cpp -o bot.out -ldpp -std=c++20 --define DPP_CORO