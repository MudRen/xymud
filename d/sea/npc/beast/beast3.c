#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name("花斑豹", ({"huaban bao", "bao"}));
  set("race", "野兽");
  set("age", 20);
  set_level(21);
  set("long", "一头身带花斑的金钱大豹，象是要随时扑上来。\n");
  set("daoxing", 150000);
  set("attitude", "aggressive");
  set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 210);
  set_skill("parry", 210);
  set_skill("unarmed", 210);

  set("ride/need_train", 1);
  set("ride/msg", "骑");
  set("ride/dodge", 28);
  set("ride/max_kee", 100);
  set("ride/max_sen", 100);

  set_temp("apply/dodge", 50);
  set_temp("apply/attack", 50);
  set_temp("apply/armor", 50);

  setup();
}

