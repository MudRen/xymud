#include <weapon.h>
#include <ansi.h>
inherit WHIP;
void create()
{
	set_name(HIC"七定混天索"HIR"("HIY"气血诅咒"HIR")"NOR, ({ "whip","bian"}) );
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
		set("long", "这是一件传说中的神器。\n");
		set("wield_msg", "只听「啪」的一声响，$N的手中闪出一条$n。\n");
		set("unwield_msg", "$N把手中$n缠回腰间．\n");
	}
	init_whip(150+random(50));
	setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("kee",50);
        return HIG "九宫定神斧一震，$N的眼里映着九宫定神斧闪出的诡异光芒．．．\n" NOR;
}