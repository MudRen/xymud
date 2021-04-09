#include <ansi.h>
inherit __DIR__"shi.c";

void random_type()
{
	if( query("name")=="石块" )
		return;
	set("type","tu");
	set_name("土灵石",({"tu lingshi","jin","shi","lingshi","shi","stone"}));
}	
