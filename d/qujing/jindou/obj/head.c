#include <armor.h>

inherit HEAD;

string *names = ({
  "铁头盔",
  "铜头盔",
});

string *ids = ({
  "tie tou kui",
  "tong tou kui",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "tou kui", "kui", "head"}));
  set("level",4);
  set_weight(4000);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "件");
   set("value", 200);
   set("material", "metal");
//   set("armor_prop/armor", 12);
   set("armor_prop/armor", 2);
   set("armor_prop/dodge", -1);
  }
  set("no_sell",1);
  setup();
}
