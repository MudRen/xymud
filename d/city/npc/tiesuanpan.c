inherit NPC;
#include <ansi.h>

void create()
{
	set_name("铁算盘", ({"tie suanpan", "tie", "zhanggui"}));
	set("title", HIY"钱庄掌柜"NOR);
	set_level(9);
	set("gender", "男性");
	set("age", 54);
	set("attitude", "friendly");
	set("env/wimpy", 50);
	set_skill("unarmed", 90);
	set_skill("parry", 90);
	set_skill("dodge", 90);
	set_level(5);
	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	add_money("gold", 1);
	set("max_kee",100000);
	set("max_sen",100000);
	powerup(0,1);
}