#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name("金眼驼",({"jinyan tuo", "tuo"}));
  set("race", "野兽");
  set("age", 20);
  set_level(19);
  set("long", "一头金眼放光的五云驼，日行一千，夜走八百。\n");
  set("daoxing", 150000);

  set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 190);
  set_skill("parry", 190);
  set_skill("unarmed", 190);

  set("ride/need_train", 1);
  set("ride/msg", "骑");
  set("ride/dodge", 27);
  set("ride/max_kee", 80);
  set("ride/max_sen", 80);

  set_temp("apply/dodge", 45);
  set_temp("apply/attack", 45);
  set_temp("apply/armor", 45);

  setup();
}

