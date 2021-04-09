#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
	set_name(HIC"千手观音锤"HIR"("HIY"招架"HIR")"NOR, ({ "hammer","chui"}) );
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("material", "steel");
		set("value", 100000);
                set("no_put",1);
                set("no_dzm",1);
                set("no_zm",1);
                set("weapon_prop/parry", 50);
		set("long", "这是一件传说中的神器。\n");
                set("wield_msg", "$N拿出一把$n，试了试重量，然后握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
	}
	init_hammer(150+random(50));
	setup();
}
