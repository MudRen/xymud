//Cracked by Roath
//mingyue.c

inherit NPC;

int max_tea = 20;
void create()
{
	set_name("明月", ({"ming yue", "mingyue"}));
      set_level(14);
	set("gender", "男性" );
	set("age", 16);
	set("long", "一个讨人喜欢的小仙童。\n");
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