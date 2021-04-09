//Cracked by Roath
// created 12/18/1997 by snowcat

inherit NPC;

void create()
{
  set_name("玉面公主", ({ "yumian gongzhu", "yumian", "gongzhu", "princess" }));
  set_level(89);
  set("title", "积雷山");   
  set("long", "一位娇柔万分的女子，伶俐地扭动着腰肢。\n");
  set("gender", "女性");
  set("age", 16);
  set("attitude", "heroism");
  set("force_factor", 50);
  set("mana_factor", 50);

  set_skill("spells", 890);
  set_skill("moonshentong", 890);
  set_skill("unarmed", 890);
  set_skill("baihua-zhang", 890);
  set_skill("dodge", 890);
  set_skill("moondance", 890);
  set_skill("parry", 890);
  set_skill("force", 890);
  set_skill("moonforce", 890);
  set_skill("mace", 890);
  set_skill("wusi-mace", 890);
  map_skill("spells", "moonshentong");
  map_skill("unarmed", "baihua-zhang");
  map_skill("dodge", "moondance");
  map_skill("mace", "wusi-mace");
  map_skill("parry", "wusi-mace");
  map_skill("force", "moonforce");
  setup();
  carry_object("/d/obj/cloth/skirt")->wear();
  carry_object("/d/qujing/jilei/obj/wufeng")->wield();
  carry_object("/d/obj/fabao/xiang-hebao");
}

void die ()
{
  object me = this_object();
  message_vision ("\n$N翻倒在地现了真身，竟是一只狐狸精。\n",me);
  message_vision ("狐狸精一溜烟跑了。\n\n",me);
  destruct (me); 
}

void unconcious ()
{
  die ();
}

void kill_ob (object ob)
{
  object me = this_object();
  object where = environment (me);
  object niumo = present ("niumo wang", where);

  set_temp("my_killer",ob);
  ::kill_ob(ob);
  if (niumo && !niumo->is_fighting())
    niumo->kill_ob(ob);
}