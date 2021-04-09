inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
	set_name("孤魂野鬼", ({"ye gui", "gui"}));
       	set_level(5);
       	set("gender", "男性");
       	set("age", 60);
	set("long", "一个看起来相当可怜的老头．\n");
       	set("attitude", "friendly");
       	set("shen_type", 1);
	create_family("阎罗地府", 4, "你好");
	delete("title");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	setup();
}

int accept_fight(object me)
{
        command("say 我已沦落到这个地步了，就可怜可怜我吧！");
        return 0;
}

