// jiading.c
#include <ansi.h>
inherit NPC;

void create()
{
       	set_name("小沙弥", ({"shami"}));
       	set_level(10);
	set("long","一个看院的小和尚，到也长得眉清目秀的。\n");
	set("gender", "男性");
       	set("age", 10+random(15));
       	set("attitude", "peaceful");
       	set("shen_type", 1);
        set_skill("unarmed", 100);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	setup();
	carry_object("/d/obj/cloth/sengyi")->wear();
	carry_object("/d/obj/cloth/sengxie")->wear();
}