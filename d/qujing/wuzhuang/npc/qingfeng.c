//Cracked by Roath
//qingfeng.c

inherit NPC;
void create()
{
	set_name("清风", ({"qing feng", "qingfeng"}));
      set_level(14);
	set("gender", "男性" );
	set("age", 16);
	set("long", "一个机灵的小仙童，在五庄观上下很是吃得开。\n");
	set("class", "xian");
	set("combat_exp", 10000);
  set("daoxing", 20000);

	set("attitude", "peaceful");
	set("title", "小仙童");
	set_skill("unarmed", 140);
	set_skill("dodge", 140);
	set_skill("parry", 140);

	set("per", 20);
	set("max_kee", 200);
	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();

}
