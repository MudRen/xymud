#include <ansi.h>
inherit __DIR__"jin.c";

void create()
{
	set_name(HIY"坤己土"NOR,({"tu jing","jing","shi"}));
    	set("changed",1);
    	set("level",3);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","块");
        	set("long","产自终南山极土之地"NOR YEL"终南幽谷"NOR"的一块土精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }