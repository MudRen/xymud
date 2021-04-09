#include <armor.h>

inherit BOOTS;

void create()
{
  set_name( "鹿皮鞋", ({ "pi xie", "pixue", "xie" }) );
  set("level",7);
  set_weight(1000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "双");
    set("long", "一双软身硬底的鹿皮鞋。\n");
    set("value", 140);
    set("material", "boots");
    set("armor_prop/dodge", 3);
  }
  setup();
}

