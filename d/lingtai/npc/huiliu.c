// worker.c
#include <ansi.h>
inherit NPC;

void create()
{
	int i = 25+random(15);
        set_name("慧琉", ({"hui liu"}));
        set_level(i);
        set("gender", "男性" );
        set("age", 33);
        set("long", "一个相貌堂堂的道士．");
	set("title", "道长");
	set("class", "taoist");
	set("per",20+random(20));
        set("attitude", "peaceful");
        create_family("方寸山三星洞", 4, "弟子");
        set_skill("unarmed", i*10);
        set_skill("dodge", i*10);
        set_skill("parry", i*10);
        set_skill("force", i*10);
        set_skill("wuxiangforce",i*10);
        map_skill("force", "wuxiangforce");
        set("force_factor", 5);
        setup();
        carry_object("/d/lingtai/obj/cloth")->wear();
}
