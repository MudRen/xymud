inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
	set_name("打更鬼", ({"dageng gui", "gui"}));
       	set_level(6);
       	set("gender", "男性");
       	set("age", 60);
	set("long", "看起来相当的老，手里提着小锣，正在打更。\n");
       	set("attitude", "friendly");
       	set("shen_type", 1);
       	set("per", 10);
	set_skill("unarmed", 50);
	set_skill("dodge", 60);
	set_skill("parry", 40);
	create_family("阎罗地府", 4, "你好");
	delete("title");
	set("chat_chance", 8);
	set("chat_msg", ({
		"打更的喊到：平安无事喽！\n",
		"打更的上上下下打量了你几眼。\n",
	}) );
	setup();
}

