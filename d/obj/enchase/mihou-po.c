inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("猕猴魄",({"mihou po","po","mihou"}));
	set("need_mana",100);
	set("armor",([
		"dodge" : 10,
	]));
	set("weapon",([
		"attack" : 10,
	]));
	set("weapon_level",2);
	set("armor_level",2);
}		