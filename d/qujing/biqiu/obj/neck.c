// by snowcat 11/22/1997

#include <armor.h>

inherit NECK;

void create()
{
  set_name("白金项圈", ({ "baijin xiangquan", "xiangquan", "neck" }));
  set("level",2);
  set("weight", 200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "个");
    set("value", 3500);
    set("material", "gold");
    set("armor_prop/armor", 1);
  }
  setup();
}
