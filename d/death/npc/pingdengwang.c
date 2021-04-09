//puti.c
//inherit NPC;
inherit "/d/dntg/hell/wang.c";
inherit F_MASTER;

void create()
{
  set_name("平等王", ({"pingdeng wang", "wang", "pingdeng"}));
  set_level(155);
  create_family("阎罗地府", 2, "你好");
  set("title", "阴间十王之");
  set("gender", "男性");
  set("age", 70);
  set("class", "youling");
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("int", 30+random(5));
  set("max_kee", 900);
  set("max_gin", 600);
  set("max_sen", 600);
  set("force", 650);
  set("max_force", 1000);
  set("force_factor", 35);
  set("max_mana", 800);
  set("mana", 800);
  set("mana_factor", 40);
  set("combat_exp", 700000);
  set("daoxing", 600000);

  set_skill("unarmed", 1300);
  set_skill("dodge", 1300);
  set_skill("parry", 1300);
  set_skill("spells", 1300);
  set_skill("jinghun-zhang", 1200);
  set_skill("ghost-steps", 1500);
  set_skill("force", 1300);
  set_skill("gouhunshu", 1500);
  set_skill("tonsillit", 1500);
  map_skill("dodge", "ghost-steps");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("force", "tonsillit");
  map_skill("spells", "gouhunshu");
  
  setup();
  
  carry_object("/d/obj/cloth/mangpao")->wear();
  carry_object(0,"unarmed",random(2))->wield();
}
