#include <armor.h>

inherit WAIST;


void create()
{
  set_name("护腰", ({"waist"}));
  set("level",1);
  set_weight(5000);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "件");
   set("value", 200);
   set("material", "metal");
   set("armor_prop/armor", 14);
   set("armor_prop/dodge", -1);
  }
  set("no_sell",1);
  setup();
}
