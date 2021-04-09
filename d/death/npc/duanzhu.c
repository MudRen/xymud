//puti.c
inherit SUPER_NPC;
#include "lingtai.h"

void create()
{
       	set_name("断足鬼", ({"duanzu gui", "gui"}));
       	set_level(13);
       	set("gender", "男性");
       	set("age", 60);
	set("long", "一个看起来相当可怜的老头。双足却不见了，躺在地下。\n");
       	set("attitude", "friendly");
       	set("shen_type", 1);
       	set("per", 100);
	set_skill("unarmed", 115);
	set_skill("dodge", 115);
	set_skill("parry", 125);
	set_skill("stealing", 130);
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: command, "surrender" :),
        }) );
        create_family("阎罗地府", 4, "你好");
        delete("title");
	setup();
}

int accept_fight(object me)
{
        command("say 我已沦落到这个地步了，就可怜可怜我吧！\n");
        return 0;
}