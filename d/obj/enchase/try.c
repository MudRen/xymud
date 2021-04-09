inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("天神魄",({"tianshen po","po",}));
	set("need_mana",100);
	set("armor",([
		"personality" 	: 5,
		"strength"	: 5,
		"armor"		: 20,
		"dodge"		: 20,
		"ad_parry"	: 10,
		"healup_kee"	: 5,
		"healup_force"	: 10,
	]));
	set("weapon",([
		"courage" 	: 5,
		"karma"		: 5,
		"damage"	: 20,
		"attack"	: 20,
		"ad_dodge"	: 20,
		"redamage_eff_kee" : 5,
		"redamage_kee" : 5,
	]));
	set("weapon_level",15);
	set("armor_level",10);
}		