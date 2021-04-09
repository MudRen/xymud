#include <ansi.h>
inherit __DIR__"jin.c";

void create()
{
	set_name(HIG"东甲木"NOR,({"mu shi","jing","shi"}));
    	set("changed",1);
    	set("level",4);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","块");
        	set("long","产自昆仑之地"HIG"建木遗迹"NOR"的一块木精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }