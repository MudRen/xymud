//puti.c
//inherit NPC;
inherit "/d/dntg/hell/wang.c";
inherit F_MASTER;

void create()
{
	set_name("卞城王", ({"biancheng wang", "wang"}));
	set_level(150);
	create_family("阎罗地府", 2, "你好");
	set("title", "阴间十王之");
	set("gender", "男性");
	set("class", "youling");
	set("age", 50);
	set("attitude", "friendly");
	set("force_factor", 40);
       	set("mana_factor", 20);
  	set("daoxing", 500000);

	set_skill("spells", 1419);
	set_skill("gouhunshu", 1419);
       	set_skill("unarmed", 1419);
       	set_skill("dodge", 1419);
	set_skill("parry", 1419);
	set_skill("force", 1500);
	set_skill("tonsillit", 1500);
	map_skill("force", "tonsillit");
	setup();
        carry_object("/d/obj/cloth/mangpao")->wear();
}