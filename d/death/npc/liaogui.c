inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
       	set_name("獠牙鬼", ({"liaoya gui", "gui"}));
       	set_level(16);
       	set("gender", "男性");
       	set("age", 30);
	set("long", "一个獠牙鬼，面目狰狞可怕．\n");
       	set("attitude", "heroism");
       	set("shen_type", 1);
	create_family("阎罗地府", 4, "你好");
	delete("title");
	
	set_skill("unarmed", 145);
	set_skill("blade", 145);
	set_skill("dodge", 145);
	set_skill("parry", 155);
	set_skill("force", 150);
	set("force_factor", 10);
        set("mana_factor", 10);
	
	setup();
}