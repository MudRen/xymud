inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
       	set_name("无头鬼", ({"wutou gui", "gui"}));
       	set_level(15);
       	set("gender", "男性");
	set("long", "一个没有头，只有身子的野鬼．\n");
       	set("attitude", "friendly");
	create_family("阎罗地府", 4, "你好");
	delete("title");
       	set("shen_type", 1);
	set_skill("unarmed",150);
	set_skill("dodge", 150);
	set_skill("parry", 135);
	set_temp("armor_level",2);
	set_temp("weapon_level",2);
	setup();
}


