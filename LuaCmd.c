/*

	,--.                    ,-----.             ,--.
	|  |   ,--.,--. ,--,--.'  .--./,--,--,--. ,-|  |
	|  |   |  ||  |' ,-.  ||  |    |        |' .-. |
	|  '--.'  ''  '\ '-'  |'  '--'\|  |  |  |\ `-' |
	`-----' `----'  `--`--' `-----'`--`--`--' `---'

	Simple Lua interface for command line.
	LuaCmd.c - main file.
*/


// Vendor
#include <lua.hpp>

// C
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _WIN32
#include <windows.h>
#endif

// Input
#define MAX_INPUT_LENGTH 256

// Colors
#define CMD_COLOR_GREEN 2
#define CMD_COLOR_LIGHTBLUE 3
#define CMD_COLOR_RED 4
#define CMD_COLOR_PINK 5
#define CMD_COLOR_WHITE 7
#define CMD_COLOR_GRAY 8

void SetConsoleColor(uint32_t color)
{
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

int main()
{
	lua_State* L = luaL_newstate();
	if (L == NULL)
	{
		printf("Unable to create a new Lua state.");
		return -1;
	}

	luaL_openlibs(L);

	char* input = (char*)malloc(MAX_INPUT_LENGTH);
	for (;;)
	{
		SetConsoleColor(CMD_COLOR_LIGHTBLUE);
		printf("Lua 5.1> ");

		SetConsoleColor(CMD_COLOR_WHITE);
		fgets(input, MAX_INPUT_LENGTH, stdin);
		input[MAX_INPUT_LENGTH - 1] = 0;

		SetConsoleColor(CMD_COLOR_GRAY);
		printf(">> %s", input);
		SetConsoleColor(CMD_COLOR_WHITE);
		if (luaL_dostring(L, input) != LUA_OK)
		{
			SetConsoleColor(CMD_COLOR_RED);

			const char* errorMessage = lua_tostring(L, -1);
			printf("%s\n", errorMessage);

			lua_pop(L, 1);
		}
	}

	free(input);
	lua_close(L);
	return 0;
}


// The Kumor @ 2023