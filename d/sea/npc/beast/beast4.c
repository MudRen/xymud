#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name("墨麒麟", ({"mo qilin", "qilin"}));
  set("race", "野兽");
  set("age", 20);
  set_level(25);
  set("long", "一头浑身墨绿的麒麟，端是一头神兽。\n");
  set("daoxing", 150000);

  set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 250);
  set_skill("parry", 250);
  set_skill("unarmed", 150);

  set("ride/need_train", 1);
  set("ride/msg", "骑");
  set("ride/dodge", 29);
  set("ride/max_kee", 150);
  set("ride/max_sen", 150);

  set_temp("apply/dodge", 40);
  set_temp("apply/attack", 40);
  set_temp("apply/armor", 40);

  setup();
}

