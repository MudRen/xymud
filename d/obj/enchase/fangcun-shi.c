inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("方寸石",({"fangcun shi","shi","stone"}));
	set("need_mana",250);
	set("armor",([
		"parry" : 10,
	]));
	set("weapon",([
		"ad_stick" : 5,
	]));
	set("weapon_level",4);
	set("armor_level",4);
}		