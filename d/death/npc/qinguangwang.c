//puti.c
//inherit NPC;
inherit "/d/dntg/hell/wang.c";
inherit F_MASTER;

void create()
{
  set_name("秦广王", ({"qinguang wang", "wang", "qinguang"}));
  set_level(156);
  create_family("阎罗地府", 2, "你好");
  set("title", "阴间十王之");
  set("gender", "男性");
  set("age", 60);
  set("class", "youling");
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("max_kee", 800);
  set("max_gin", 800);
  set("max_sen", 800);
  set("force", 850);
  set("max_force", 800);
  set("force_factor", 60);
  set("max_mana", 800);
  set("mana", 1000);
  set("mana_factor", 30);
  set("combat_exp", 800000);
  set("daoxing", 700000);

  set_skill("unarmed", 1400);
  set_skill("jinghun-zhang", 1200);
  set_skill("dodge", 1400);
  set_skill("parry", 1400);
  set_skill("gouhunshu", 1500);
  set_skill("tonsillit", 1500);
  set_skill("spells", 1200);
  set_skill("force", 1200);
  set_skill("ghost-steps", 1500);
  map_skill("dodge", "ghost-steps");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("force", "tonsillit");
  map_skill("spells", "gouhunshu");
  
  setup();
  
  carry_object("/d/obj/cloth/mangpao")->wear();
  carry_object(0,"unarmed",random(2))->wield();
}
