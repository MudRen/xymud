#include <armor.h>

inherit FINGER;

void create()
{
  set_name("钻石戒指", ({ "zuan jie", "zuanjie", "ring" }));
  set("level",4);
  set("weight", 400);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "个");
    set("value", 12000);
    set("material", "diamond");
    set("armor_prop/armor", 1);
    set("armor_prop/personality", 1);
  }
  setup();
}       

