#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
    set_name(HIY"三才剑"NOR, ({"jian","sword","sancai" }) );
    set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
        	set("unit", "柄");
                set("no_put",1);
                set("no_zm",1);
                set("no_drop",1);
                set("no_get",1);
                set("title",HIR"纪念品"NOR);
                set("value", 0);
                set("material", "iron");
                set("weapon_prop/intelligence", 4);
        	set("long", HIY"这是小雨西游纪念圣诞和新年特地为玩家做的纪念品，可以增加你的智力哦。\n"NOR);
        	set("wield_msg",HIY"一道金光闪过，$N手中已多了把"NOR+"$n。\n"+HIR"$N觉得自己变得更聪明了！\n"NOR);
        	set("unwield_msg", "$N放下手中的$n。\n");
	}
        init_sword(85);
	setup();
}
