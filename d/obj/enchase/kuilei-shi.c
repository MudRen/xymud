inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("傀儡石",({"kuilei shi","shi","stone"}));
	set("need_mana",300);
	set("armor",([
		"armor" : 10,
		"spirituality" : 1,
	]));
	set("weapon",([
		"damage" : 10,
		"strength" : 1,
	]));
	set("weapon_level",5);
	set("armor_level",5);
}		