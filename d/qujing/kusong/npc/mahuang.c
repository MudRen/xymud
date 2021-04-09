//Cracked by Roath
inherit NPC;

void create()
{
  set_name("蚂蟥怪", ({"mahuang guai","guai"}));
  set_level(36);
  set("gender", "男性");
  set("age", 40);
  set("long","一个胖头胖脑的老妖精。\n");

  set("per", 15);
  set_skill("dodge",300);
  set_skill("parry",300);
  set_skill("unarmed",300);
  set_skill("force", 120);
  set_skill("spells", 120);
  set_skill("dagger", 120);
  set("force_factor", 25);
  set("mana_factor", 25);
  
  setup();
  carry_object("/d/qujing/kusong/obj/needle1")->wield();
  carry_object("/d/qujing/kusong/obj/tongjia")->wear();
}