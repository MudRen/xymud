#include <armor.h>

inherit SURCOAT;

void create()
{
  set_name("虎皮大氅", ({ "hupi dachang", "dachang", "chang" }) );
  set("level",4);
  set_weight(1600);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "件");
    set("material", "leather");
    set("value", 1600);
    set("armor_prop/armor", 4);
  }
  setup();
}

