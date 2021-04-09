#include <armor.h>

inherit HEAD;

void create()
{
  set_name("黑丝帽", ({ "si mao", "mao" }) );
  set("level",1);
  set_weight(500);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "顶");
    set("long","一顶轻便的黑色丝帽。\n");
    set("value", 300);
    set("material", "cloth");
    set("armor_prop/armor", 1);
    set("armor_prop/personality", 1);
  }
  setup();
}

