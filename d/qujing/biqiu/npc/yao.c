// created by snowcat on 4/12/1997

inherit NPC;

void create()
{
  int i = random(9)+30;
  set_name("小妖", ({"xiao yao","yao"}));
  set("gender", "男性");
  set("age", 20);
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
  set("max_sen",100*i);
  set("max_gee",100*i);
  set("max_gin",100*i);
  set("force",100*i);
  set("max_force",100*i);
  set("max_mana",100*i);
  set("force_factor",10*i);
  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  carry_object("/d/qujing/biqiu/obj/armor")->wear();
  carry_object(sprintf("/d/qujing/biqiu/obj/weapon%d",random(4)))->wield();
}