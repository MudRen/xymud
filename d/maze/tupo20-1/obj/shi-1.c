#include <ansi.h>
inherit __DIR__"shi.c";

void random_type()
{
	if( query("name")=="石块" )
		return;
	set("type","jin");
	set_name("金灵石",({"jin lingshi","jin","shi","lingshi","shi","stone"}));
}	
