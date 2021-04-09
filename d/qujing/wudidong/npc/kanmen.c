// kanmen.c, created by mes
// updated 6-20-97 pickle

inherit SUPER_NPC;

void create()
{
  set_name("看门妖", ({"kanmen yao","kanmen","kanmenyao","yao","monster"}));
  set_level(44);
  set("long","一个看门的小妖，张牙舞爪的，挺怕人。\n");
  set("gender", "男性");
  set("cor", 25);
  set("age", 20+random(15));
  set("attitude", "peaceful");
  set("shen_type", 1);

  set_skill("unarmed", 400);
  set_skill("parry", 400);
  set_skill("dodge", 400);
  set_skill("blade", 400);
  set_skill("kugu-blade", 400);
  map_skill("blade", "kugu-blade");
  map_skill("parry", "kugu-blade");
  map_skill("dodge", "kugu-blade");
  setup();
  add_money("silver", 2);
  carry_object(0,"blade",random(2))->wield();
  carry_object(0,"cloth",random(2))->wear();
  carry_object(0,"armor",random(2))->wear();
  carry_object(0,"kui",random(2))->wear();
  carry_object(0,"shoes",random(2))->wear();
  carry_object(0,"pifeng",random(2))->wear();
  carry_object(0,"shield",random(2))->wear();
}