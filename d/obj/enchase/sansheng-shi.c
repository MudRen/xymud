inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("三生石",({"sansheng shi","sansheng","shi"}));
	set("need_mana",300);
	set("armor",([
		"armor" : 25,
		"intelligence" : 10,
	]));
	set("weapon",([
		"damage" : 25,
		"constitution" : 10,
	]));
	set("weapon_level",5);
	set("armor_level",5);
}		