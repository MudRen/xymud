#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit ITEM;
void init();
int do_play(string arg);
void create()
{
  set_name(HIB "毒" NOR, ({ "du poison","poison","du"})); 
  set_weight(1000);
  set("long","一瓶神秘的毒药，雪山秘传，巨毒无比。\n");
  set("unit", "瓶");
  setup();
}

