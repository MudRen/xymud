inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("化蝶石",({"huadie shi","huadie","shi"}));
	set("need_mana",1200);
	set("armor",([
		"dodge" : 20,
	]));
	set("weapon",([
		"attack" : 50,
	]));
	set("weapon_level",15);
	set("armor_level",15);
}		