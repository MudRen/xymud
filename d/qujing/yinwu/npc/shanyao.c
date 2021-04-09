// created by snowcat on 12/5/1997

inherit NPC;

void create()
{
  set_name("山妖", ({"shan yao","yao"}));
  set("gender", "男性");
  set("age", 40);
  set("long","一个凶相毕露的山妖。\n");
  set("attitude", "aggressive");
  set_level(45);
  
  set("no_nk_reward",1);

  set("per", 15);
  set_skill("parry", 450);
  set_skill("unarmed", 450);
  set_skill("dodge", 450);
  set_skill("blade", 450);
  set_skill("fork", 450);
  set_skill("mace", 450);
  set_skill("spear", 450);
  set_skill("sword", 450);
  set_skill("whip", 450);
  set_skill("axe", 450);
  set_skill("hammer", 450);
  set_skill("rake", 450);
  set_skill("stick", 450);
  set_skill("staff", 450);
  set_skill("dagger", 450);
  set("force_factor",3);
  setup();
  carry_object("/d/qujing/yinwu/obj/cloth")->wear();
}

void die ()
{
  object me = this_object();
  object where = environment (me);
  object bone = present ("bone 4",where);

  if (! bone)
  {
    bone = new ("/d/obj/misc/bone");
    bone->move(where);
  }

  message_vision ("\n$N倒了下去，化为一堆兽骨。\n",me);  
  if (! present("shan yao 3",where) &&
      where->query("short")=="路口")
  {
    object ob = new ("/d/qujing/yinwu/npc/shanyao");
    ob->move(where);
    message_vision ("\n突然，山岩上又蹦下来一个呲牙咧嘴的山妖！\n",me);   
  }
  destruct (me);  
}

void unconcious ()
{
  die();
}