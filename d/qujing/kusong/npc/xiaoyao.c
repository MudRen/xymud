//Cracked by Roath
inherit NPC;

void create()
{
  int i = 30+random(10);	
  set_name("小妖", ({"xiao yao","yao"}));
  set_level(i);
  set("gender", "男性");
  set("age",i*10);
  set("long","一个贼眉鼠眼的小妖精。\n");

  set("per", 15);
  set_skill("dodge",i*10);
  set_skill("parry",i*10);
  set_skill("unarmed",i*10);
  set_skill("spells",i*10);
  set_skill("stick",i*10);
  set("chat_chance",2);
  set("chat_msg",({
        "小妖皱一皱小贼眉。\n",
        "小妖拼命地眨眨一对闪闪发光的小鼠眼。\n",
        "小妖一跳，叭叽一声摔在地上。\n",
        "小妖走到你面前，哇呀咿啊叫了几声。\n",
        "小妖嗖地一声，甩手倒挂在洞岩上。\n",
        "小妖一不小心，呀呀呀从洞岩上失手掉下来。\n",
    }));
  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  carry_object("/d/obj/weapon/stick/shuzhi")->wield();
}