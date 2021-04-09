#include <armor.h>

inherit BOOTS;

string *names = ({
  "铁头靴",
  "铜头靴",
});

string *ids = ({
  "tie tou xue",
  "tong tou xue",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "xue", "shoes"}));
  set_weight(2000);
  set("level",7);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "双");
   set("value", 200);
   set("material", "metal");
//   set("armor_prop/armor", 10);
   set("armor_prop/armor", 2);
   set("armor_prop/dodge", -1);
  }
  set("no_sell",1);
  setup();
}
