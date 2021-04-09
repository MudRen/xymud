#include <weapon.h>
inherit EQUIP;
varargs void init_allweapon()
{
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "slash", "slice", "thrust", "pierce" }) );
	}
}

int is_weapon(){ return 1;}