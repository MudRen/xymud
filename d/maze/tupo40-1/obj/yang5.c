#include <ansi.h>
inherit __DIR__"jin.c";

void create()
{
	set_name(HIY"乾申之心"NOR,({"jin shi","jing","shi"}));
    	set("changed",1);
    	set("level",5);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","颗");
        	set("long","产自川中极金之地"HIY"销金窝"NOR"的一块金精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }