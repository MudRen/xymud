#include <ansi.h>
inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name(HIR"相看白刃血纷纷"NOR,({"po shi","shi"}));
	set("need_mana",1000);
	set("armor",([
		"dodge" : 20,
	]));
	set("weapon",([
		"attack" : 50,
	]));
	set("weapon_level",5);
	set("armor_level",5);
}		