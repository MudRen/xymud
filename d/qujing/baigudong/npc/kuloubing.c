//modified from pingding/npc/yao1.c 
// created by smile 12/10/1998

inherit NPC;

void create()
{
  int i = 30+random(5);
  set_name("骷髅兵", ({"kulou bing","bing"}));
  set("gender", "男性");
  set("age", 30);
  set_level(i);
  set("attitude","aggressive");
  set("per", 8);
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
  set("chat_chance",10);
  set("chat_msg",({
       "骷髅兵狠狠的说，我被人吃了才变成这样的，我也要吃别人！\n",
       "骷髅兵叫到，我真是冤枉啊！\n",
       "骷髅兵幽幽的叹了一口气，唉，什么时候才能重回人世！\n",
       "骷髅兵嘿嘿冷笑两声，今天叫你来得去不得！\n",
  }));

  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  carry_object("/d/qujing/baigudong/obj/armor")->wear();
  carry_object(sprintf("/d/qujing/baigudong/obj/weapon%d",random(12)))->wield();
}
