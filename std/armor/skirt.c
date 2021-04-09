
#include <armor.h>

inherit EQUIP;

void setup()
{
 	int lvl;
	set("female_only", 1);
	set("armor_type", TYPE_SKIRT);
	lvl = this_object()->query("level");
	if( lvl<1 )  lvl = 1;
	if( lvl>20 ) lvl = 20;
	delete("armor_prop/armor");
	set("armor_prop/combat_def",7+lvl);
	set("armor_prop/spells_def",7+lvl);
}


int is_armor_ob()
{
	return 1;
}
