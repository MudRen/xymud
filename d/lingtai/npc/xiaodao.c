// worker.c
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("扫地小童", ({"xiao tong"}));
        set_level(10+random(5));
        set("gender", "男性" );
        set("age", 13);
        set("long", "一个小童，正在轻轻的扫地");
        set("combat_exp", 1000);
	set_skill("stick", 120);
	set_skill("dodge", 140);
        set("attitude", "friendly");
        setup();
	carry_object("/d/lingtai/obj/shaoba")->wield();
	carry_object(0,"cloth",random(3))->wear();
}