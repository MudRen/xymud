//puti.c
inherit NPC;

void create()
{
       set_name("神荼", ({"shen tu", "tu"}));
       set_level(120);
	set("title", "祀户");
       set("gender", "男性");
	set("long", "一个白脸喜相的勇士，身高足有丈外，站在那里威风凛凛。\n");
       set("age", 30);
       set("attitude", "peaceful");

       set("per", 10);
	set("str", 30);
	set("dex", 30);
	set("cor", 30);
	set("int", 10);
	set("con", 30);

       set("max_kee", 1000);
       set("max_sen", 1000);
       set("force",1800);
       set("max_force", 1000);
       set("force_factor", 60);
       set("max_mana", 800);
	set("mana", 1500);
       set("mana_factor", 40);
       set("combat_exp", 500000);
  set("daoxing", 200000);

       set_skill("unarmed", 1200);
       set_skill("dodge", 1200);
       set_skill("parry", 1200);
	set_skill("staff", 1200);
        set_skill("force", 1000);
	set_skill("spells", 1000);
	set_skill("moshenbu", 1200);
	set_skill("lunhui-zhang", 1200);
	set_skill("changquan", 1000);
	map_skill("unarmed", "changquan");
	map_skill("dodge", "moshenbu");
	map_skill("staff", "lunhui-zhang");
	map_skill("parry", "lunhui-zhang");
	setup();
        carry_object(0,"armor",random(100))->wear();
        carry_object(0,"cloth",random(100))->wear();
        carry_object(0,"pifeng",random(100))->wear();
        carry_object(0,"kui",random(100))->wear();
        carry_object(0,"shoes",random(100))->wear();
        carry_object(0,"staff",random(100))->wield();
}
