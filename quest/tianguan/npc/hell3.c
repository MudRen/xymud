#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname() 
{
set_name("阎罗王", ({"yanluo wang", "wang","yanluo"}));
set("long","身穿大红蟒袍，头戴黑绸软巾。面如锅底，须若钢针，这就是阎罗王。\n");
set("gender", "男性");
set("age", 56);
set("national","鬼族");
set("title", "阴间十王之首");
set("class","youling");
set("per", 5);
set("int", 100);
set("con", 100);
set("str", 100);
create_family("阎罗地府", 2, "鬼魂");

set_skill("whip", 700);
set_skill("hellfire-whip", 700);
set_skill("stick",700);
set_skill("kusang-bang",700);
set_skill("ghost-steps", 700);
set_skill("jinghun-zhang", 700);
set_skill("tonsillit", 700);
set_skill("gouhunshu", 700);
set_skill("zhuihun-sword", 700);
set_skill("sword", 700);
set_skill("force", 700);
set_skill("spells", 700);
set_skill("literate", 700);
set_skill("parry", 700);
set_skill("dodge", 700);
map_skill("sword","zhuihun-sword");
map_skill("force", "tonsillit");
map_skill("whip", "hellfire-whip");
map_skill("stick","kusang-bang");
map_skill("parry", "kusang-bang");
map_skill("spells", "gouhunshu");
map_skill("dodge", "ghost-steps");
map_skill("unarmed", "jinghun-zhang");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","zhuihun-sword");
	}
	else if( random(2) )
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","hellfire-whip");
	}
	else
	{
		carry_object(0,"stick",1)->wield();
		map_skill("parry","kusang-bang");
	}
}
int is_job(){return 1;}