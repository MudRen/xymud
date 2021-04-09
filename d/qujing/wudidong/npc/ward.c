// ward.c

inherit NPC;

void create()
{
  set_name("狱守", ({"ward", "yushou", "monster"}));
  set_level(38);
  set("long","看狱的小妖，膀阔腰圆，张牙舞爪，挺怕人。\n");
  set("gender", "男性");
  set("age", 40+random(15));
  set("attitude", "aggressive");
  set("shen_type", 1);

  set_skill("unarmed",380);
  set_skill("parry",380);
  set_skill("dodge",380);
  set_skill("sword",380);
  set_skill("qixiu-jian",380);
  set_skill("lingfu-steps", 380);
  map_skill("sword", "qixiu-jian");
  map_skill("dodge", "lingfu-steps");
  map_skill("parry", "qixiu-jian");
  
  setup();
  add_money("silver", 20);
  carry_object("/d/obj/weapon/sword/tiejian")->wield();
  carry_object("/d/obj/cloth/linen")->wear();
}