#include <ansi.h>
inherit __DIR__"shi.c";

void random_type()
{
	if( query("name")=="石块" )
		return;
	set("type","shui");
	set_name("水灵石",({"shui lingshi","jin","shi","lingshi","shi","stone"}));
}	
