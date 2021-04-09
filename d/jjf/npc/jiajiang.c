// jiading.c 家丁

inherit NPC;

void create()
{
  set_name("家将", ({ "jia jiang", "jia", "jiang"}));
  set_level(10+random(7));
  set("gender", "男性");
  set("age", 19+random(30));
  set("per",10+random(20));
  set("combat_exp", 200000+random(50000));
  set_skill("spear", 100);
  set_skill("dodge", 100);
  set_skill("parry", 100);
  set_skill("unarmed", 100);
  set_skill("force", 100);  
  setup();
  carry_object(0,"spear",random(2))->wield();
  carry_object(0,"cloth",random(2))->wear();
  add_money("silver", 2+random(5));

}
	
