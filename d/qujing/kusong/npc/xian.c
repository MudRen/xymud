//Cracked by Roath
inherit NPC;

void create()
{
  set_name("掀烘兴", ({"xianhong xing","xing"}));
  set_level(46);
  set("gender", "男性");
  set("age", 10);
  set("title", "火云洞健将");
  set("long","一个贼眉鼠眼的小妖精。\n");

  set("per", 15);
  set_skill("dodge",460);
  set_skill("parry",460);
  set_skill("unarmed",460);
  set_skill("force",460);
  set_skill("spells",460);

  setup();

  carry_object("/d/qujing/kusong/obj/tongjia")->wear();
}