// created by snowcat on 4/11/1997

inherit NPC;

void create()
{
  int i = random(9)+1;
  string str;
  set_name("小妖", ({"xiao yao","yao"}));
  set("gender", "男性");
  set("age", 20);
  i = 40+random(10);
  set_level(i);
  set("attitude","aggressive");
  set("per", 15);
  set_skill("parry", 10*i);
  set_skill("unarmed", 10*i);
  set_skill("dodge", 10*i);
  set_skill("blade", 10*i);
  set_skill("fork", 10*i);
  set_skill("mace", 10*i);
  set_skill("spear", 10*i);
  set_skill("sword", 10*i);
  set_skill("whip", 10*i);
  set_skill("axe", 10*i);
  set_skill("hammer", 10*i);
  set_skill("rake", 10*i);
  set_skill("stick", 10*i);
  set_skill("staff", 10*i);
  set_skill("dagger", 10*i);
  set("force_factor",10*i);
  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  carry_object("/d/qujing/pingding/obj/armor")->wear();
  str = "/d/qujing/pingding/obj/weapon0";
  str[strlen(str)-1] = '0'+random(10);
  carry_object(str)->wield();
}