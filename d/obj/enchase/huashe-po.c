inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("化蛇魄",({"huashe po","huashe","po","shi"}));
	set("need_mana",1500);
	set("armor",([
		"healup_kee" : 3,
		"healup_sen" : 3,
	]));
	set("weapon",([
		"healup_force " : 3,
		"healup_mana " : 3,		
	]));
	set("weapon_level",20);
	set("armor_level",20);
}		