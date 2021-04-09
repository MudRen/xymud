#include <ansi.h>
inherit __DIR__"newdrug.c";

void create()
{
	set_name("潜能丹",({"qianneng dan", "dan"}));
	set_weight(90);
        set("base_unit", "颗");
        set("unit","些");
        set("drug_type", "补品");
        set("no_give",1);
        set("no_put",1);
        set("no_sell",1);
	setup();
}

string query_target()
{
	return "menpai";
}

string query_type()
{
	return "potential";
}

int query_time()
{
	return 10800;
}

int query_pot()
{
	return 110;
}       
                                
