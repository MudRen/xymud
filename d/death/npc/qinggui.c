inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
	set_name("青面鬼", ({"qingmian gui", "gui"}));
       	set_level(15);
       	set("gender", "男性");
       	set("age", 30);
	set("long", "一个青面鬼，面目狰狞可怕．\n");
	create_family("阎罗地府", 4, "你好");
	delete("title");
       	set("attitude", "heroism");
       	set("shen_type", 1);
	set_skill("unarmed", 145);
	set_skill("dodge", 145);
	set_skill("whip", 145);
	set_skill("parry", 145);
	set("force_factor", 10);
	setup();
}
