// cracked by snowtu
// jingu.c 金箍
#include <ansi.h>
#include <combat.h>
inherit ITEM;

void create()
{
	set_name(HIR"金箍"NOR, ({ "jin gu","gu" }) );
	set_weight(1);
	if( clonep() )
        set_default_object(__FILE__);
	set("unit", "个");
    set("long","一个金箍。撞见神通广大的妖魔，只依紧箍咒的咒语念一念，管教他入我门来。\n");
    set("material", "steel");       
    set("no_drop",1);
    set("no_get",1);
    set("no_put",1);
    set("no_sell",1);
	set("time",3);        
	setup();
}