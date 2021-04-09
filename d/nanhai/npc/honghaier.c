// honghaier.c 红孩儿
// By Dream Dec. 20, 1996
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("红孩儿", ({ "honghaier" }));
      set_level(120);
	set("title", "南海观音之徒");   
	set("long", @LONG
他本是牛魔王之子，生性好斗；后被南海观音收服，脾气却不见有什么好转。
他使得一手的好枪法，火云枪更是鲜有敌手，寻常人是不敢碰他的。
LONG);
	set("gender", "男性");
	set("age", 15);
	set("attitude", "heroism");
	set("max_kee", 750);
	set("max_gin", 600);
	set("max_sen", 750);
	set("force", 450);
	set("max_force", 300);
	set("force_factor", 20);
	set("max_mana", 350);
	set("mana", 500);
	set("mana_factor", 50);
	set("combat_exp", 240000);
	set("daoxing", 400000);

	set_skill("literate", 1180);
	set_skill("spells", 1200);
	set_skill("buddhism", 1200);
	set_skill("unarmed", 1160);
	set_skill("jienan-zhi", 1160);
	set_skill("dodge", 1180);
	set_skill("lotusmove", 1180);
	set_skill("parry", 1180);
	set_skill("force", 1180);
	set_skill("lotusforce", 1170);
	set_skill("staff", 1150);
	set_skill("lunhui-zhang", 1140);
	set_skill("spear", 1200);
	set_skill("huoyun-qiang", 1150);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "huoyun-qiang");
	map_skill("staff", "lunhui-zhang");
	map_skill("spear", "huoyun-qiang");
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		(: cast_spell, "jingang" :),
	}) );

	create_family("南海普陀山", 2, "弟子");

	setup();
	carry_object("/obj/money/gold");
	carry_object("/obj/money/gold");
	carry_object("/obj/cloth")->wear();
	carry_object("/d/nanhai/obj/jingu2");
	carry_object("/d/nanhai/obj/huojianqiang")->wield();
}
