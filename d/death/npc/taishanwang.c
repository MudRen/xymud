//puti.c
//inherit NPC;
inherit "/d/dntg/hell/wang.c";
inherit F_MASTER;

void create()
{
       set_name("泰山王", ({"taishan wang", "wang", "taishan"}));
       set_level(158);
       create_family("阎罗地府", 2, "你好");
       set("title", "阴间十王之");
	set("class", "youling");
       set("gender", "男性");
       set("age", 100);
       set("attitude", "friendly");
       set("shen_type", 1);
       set("per", 30);
        set("int", 30+random(5));
       set("max_kee", 1000);
       set("max_gin", 1000);
       set("max_sen", 1000);
       set("force", 1150);
       set("max_force", 1000);
       set("force_factor", 50);
       set("max_mana", 1000);
       set("mana", 1000);
       set("mana_factor", 20);
       set("combat_exp", 700000);
  set("daoxing", 600000);

	set_skill("spells", 1500);
       set_skill("unarmed", 1500);
       set_skill("dodge", 1500);
       set_skill("parry", 1500);
        set_skill("spells", 1500);
        set_skill("force", 1500);
	set_skill("gouhunshu", 1500);
	set_skill("tonsillit", 1500);
	map_skill("force", "tonsillit");
	map_skill("spells", "gouhunshu");


setup();

        carry_object("/d/obj/cloth/mangpao")->wear();
        carry_object(0,"unarmed",random(2))->wield();
//        carry_object("/d/lingtai/obj/shoe")->wear();
//        carry_object("/d/lingtai/obj/putibang")->wield();
}