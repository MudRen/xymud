#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name("梅花鹿", ({"meihua lu", "lu"}));
  set("race", "野兽");
  set("age", 20);
  set_level(15);
  set("long", "一头花角褐色梅花鹿，四蹄上似乎有风云滚起。\n");
  set("daoxing", 150000);

  set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 150);
  set_skill("parry", 150);
  set_skill("unarmed", 150);

  set("ride/need_train", 1);
  set("ride/msg", "骑");
  set("ride/dodge", 26);
  set("ride/max_kee", 50);
  set("ride/max_sen", 50);

  set_temp("apply/dodge", 40);
  set_temp("apply/attack", 40);
  set_temp("apply/armor", 40);

  setup();
}

