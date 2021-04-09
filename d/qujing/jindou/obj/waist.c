#include <armor.h>

inherit WAIST;

string *names = ({
  "铁护腰",
  "铜护腰",
});

string *ids = ({
  "tie hu yao",
  "tong hu yao",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ids[i], "hu yao", "yao", "waist"}));
  set_weight(5000);
  set("level",9);
  if ( clonep() )
     set_default_object(__FILE__);
  else {
   set("unit", "件");
   set("value", 200);
   set("material", "metal");
//   set("armor_prop/armor", 14);
   set("armor_prop/armor", 3);
   set("armor_prop/dodge", -1);
  }
  set("no_sell",1);
  setup();
}
