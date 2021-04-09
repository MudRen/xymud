#include <armor.h>

inherit NECK;

string *names = ({
  "铁护肩",
  "铜护肩",
});

string *ids = ({
  "tie hu jian",
  "tong hu jian",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "hu jian", "jian", "neck"}));
  set("level",6);
  set_weight(2000);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "副");
   set("value", 200);
   set("material", "metal");
//   set("armor_prop/armor", 11);
   set("armor_prop/armor", 2);
   set("armor_prop/dodge", -1);
  }
  set("no_sell",1);
  setup();
}
