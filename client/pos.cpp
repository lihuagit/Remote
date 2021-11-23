#include"my_hook.h"
extern Client client;

int pos(SOCKET sclient)
{
	MyHook::Instance().InstallHook(sclient);
	return MyHook::Instance().Messsages(sclient);
}