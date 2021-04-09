#include <ansi.h>
inherit __DIR__"shi.c";

void random_type()
{
	if( query("name")=="石块" )
		return;
	set("type","huo");
	set_name("火灵石",({"huo lingshi","jin","shi","lingshi","shi","stone"}));
}	
