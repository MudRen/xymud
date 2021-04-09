// by snowcat oct 15 1997
#include <armor.h>

inherit CLOTH;

void create()
{
  set_name("战袍", ({"zhan pao", "cloth"}));
  set("level",10);
  set_weight(4000);
  if( clonep() )
    set_default_object(__FILE__);
  else
  {
    set("long", "一件战袍。\n");
    set("material", "cloth");
    set("unit", "件");
    set("value", 600);
    set("armor_prop/armor", 30);
  }
  setup();
}

