#include <ansi.h>
inherit __DIR__"jin.c";

void create()
{
	set_name(HIR"离午之焰"NOR,({"huo jing","jing","shi"}));
    	set("changed",1);
    	set("level",5);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","粒");
        	set("long","产自极火之地"HIR"星石巨坑"NOR"的一块火精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }