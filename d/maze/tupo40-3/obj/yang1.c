#include <ansi.h>
inherit __DIR__"jin.c";

void create()
{
	set_name(WHT"子霜冰"NOR,({"han jing","jing","shi"}));
    	set("changed",1);
    	set("level",1);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","粒");
        	set("long","产自极冰之地"HIW"雪山寒林"NOR"的一块寒精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }