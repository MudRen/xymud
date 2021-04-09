//Cracked by Roath
inherit NPC;

void create()
{
  set_name("蝙蝠精", ({"bianfu jing","jing"}));
  set_level(43);
  set("gender", "男性");
  set("age", 40);
  set("long","一个贼眉鼠眼的老妖精。\n");

  set("per", 15);
  set_skill("dodge",430);
  set_skill("parry",430);
  set_skill("unarmed",430);
  set_skill("force",430);
  set_skill("spells",430);
  set_skill("dagger",430);
  set("force_factor", 25);
  set("mana_factor", 25);

  setup();
  carry_object("/d/qujing/kusong/obj/needle0")->wield();
  carry_object("/d/qujing/kusong/obj/tongjia")->wear();
}