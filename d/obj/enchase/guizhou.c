inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("鬼咒",({"gui zhou","zhou"}));
	set("need_mana",200);
	set("armor",([
		"intelligence" : 8,
	]));
	set("weapon",([
		"spirituality" : 8,
	]));
	set("weapon_level",3);
	set("armor_level",3);
}		