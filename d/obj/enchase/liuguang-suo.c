inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name("流光梭",({"liuguang suo","liuguang","suo"}));
	set("need_mana",300);
	set("armor",([
		"dodge" : 15,
	]));
	set("weapon",([
		"ad_dodge" : 10,
	]));
	set("weapon_level",5);
	set("armor_level",5);
}		