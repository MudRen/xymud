#include <armor.h>

inherit CLOTH;

void create()
{
  set_name("厚牛皮盾", ({"houniu pidun", "pidun", "dun"}));
  set("level",1);
  set_weight(4500);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "件");
    set("value", 2000);
    set("material", "leather");
    set("armor_prop/armor", 20);
  }
  setup();
}

