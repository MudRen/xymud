#include <ansi.h>
inherit __DIR__"shi.c";

void random_type()
{
	if( query("name")=="石块" )
		return;
	set("type","mu");
	set_name("木灵石",({"mu lingshi","jin","shi","lingshi","shi","stone"}));	
}	
