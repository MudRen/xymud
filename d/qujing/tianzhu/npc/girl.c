// snowcat 12 9 1997

inherit NPC;

void create()
{
  set_name("宫女", ({"gong nu", "nu", "girl"}));
  set("gender", "女性");
  set_level(1);
  set("age", 15);
  set("per", 30);
  set("attitude", "friendly");
  set("shen_type", 1);
  set_skill("unarmed", 10);

  setup();
  carry_object("/d/obj/cloth/gongpao.c")->wear();
//  carry_object("/d/qujing/tianzhu/obj/jinjie")->wear();
//  carry_object("/d/qujing/tianzhu/obj/fengguan")->wear();
}


