// created by snowcat
// 5/22/1997

#include <weapon.h>
#include <armor.h>
#include "hair.h"

inherit HAMMER;

void create()
{
  set_name("绿色毫毛", ({ "green hair", "greenhair", "hair" }) );
  set_weight(100);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "一把油绿色的毫毛，可以用来变成锤类武器（transform）。\n");
    set("unit", "把");
    set("value",10000);
  }
  set("no_drop",1);
  set("no_get",1);
  set("no_sell",1);
  init_hammer(10+random(20));
  setup();
}

string name_suffix()
{
  return "锤";
}


string new_unit()
{
  return "把";
}

int init ()  
{   
  add_action ("do_transform", "transform");
  add_action ("do_wield", "wield");
  return 1;
}

int do_wield (string arg)
{
  object me = this_player();
  object ob = this_object();

  if (!arg || present (arg,environment(ob))!=ob)
    return 0; // to invoke standard function
  if (!ob->query("has_transformed")) {
    tell_object (me,"请先将它变成你所需要的武器。\n");
    return 1;
  }
  return 0; // to invoke standard function
}

