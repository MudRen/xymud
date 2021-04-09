#include <armor.h>
inherit HEAD;

void create()
{
  set_name("牛皮帽", ({ "niu pimao", "pimao", "mao" }) );
  set("level",1);
  set_weight(800);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "顶");
    set("material", "leather");
    set("value", 200);
    set("armor_prop/armor", 3);
  }
  setup();
}