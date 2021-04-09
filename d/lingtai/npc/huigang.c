// worker.c
#include <ansi.h>
inherit NPC;

void create()
{
	int i = 20+random(20);
        set_name("慧纲", ({"hui gang"}));
        set_level(i);
        set("gender", "男性" );
        set("age", 33);
        set("long", "一个相貌堂堂的道士．");
	set("title", "道长");
	set("class", "taoist");
        set("attitude", "peaceful");
        create_family("方寸山三星洞", 4, "弟子");
        set_skill("unarmed",i*10);
        set_skill("dodge",i*10);
        set_skill("parry",i*10);
        set_skill("literate",i*10);
        set_skill("dodge",i*10);  
        set_skill("force",i*10);   
        set_skill("wuxiangforce",i*10);
        map_skill("force", "wuxiangforce");
	set_skill("dao", i*10);
	set_skill("spells", i*10);
	map_skill("spells", "dao");
        set("per", 30);
        set("force_factor", 5);
	set("mana_factor", 20);
        setup();
        carry_object("/d/lingtai/obj/cloth")->wear();
}
