// create by snowcat 10/16/1997

inherit NPC;

void create()
{
  set_name("百花羞", ({"baihua xiu", "baihua" }));
  set("title","三公主");
  set("gender", "女性");
  set("age", 24);
  set("attitude", "peaceful");
  set("shen_type", 1);
  set("per", 30);
  set("int", 30);
  set("max_kee", 600);
  set("max_gin", 600);
  set("max_sen", 600);
  set("force", 700);
  set("max_force", 700);
  set("force_factor", 50);
  set("max_mana", 700);
  set("mana", 700);
  set("mana_factor", 40);
  set("combat_exp", 250000);
  set("daoxing", 100000);

  set_skill("unarmed", 60);
  set_skill("dodge", 60);
  set_skill("parry", 60);
  set_skill("spells", 60);
  set_skill("force", 60);
  setup();
  carry_object("/d/qujing/baoxiang/obj/spqun")->wear();
  
}