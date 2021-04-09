#include <ansi.h>

inherit __DIR__"beast.c";

void create()
{
  set_name("青鸾", ({"qing luan"}));
  set("race", "野兽");
  set("age", 20);
  set_level(30);
  set("long", "一只青色凤鸾鸟。\n");
  set("daoxing", 150000);

  set("limbs", ({ "头部", "身体", "腿部", "翅膀", "尾巴" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 300);
  set_skill("parry", 300);
  set_skill("unarmed", 300);
  set("female_only", 1);
  set("ride/need_train", 1);
  set("ride/msg", "坐");
  set("ride/dodge", 25);
  set("ride/max_kee", 250);
  set("ride/max_sen", 250);
  
  set("bird", 1);
  set_temp("apply/dodge", 40);
  set_temp("apply/attack", 40);
  set_temp("apply/armor", 40);

  setup();
}

