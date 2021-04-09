// by snowcat 12/17/1997

#include <ansi.h>
#include <weapon.h>
 
inherit F_UNIQUE;
inherit ITEM;
 
void create()
{
  set_name("金刚琢",({"jingang zhuo", "jingang", "zhuo", "fabao"}));
  set_weight(5000);
  set_max_encumbrance(5000000);
  if(clonep())
    set_default_object(__FILE__);
  else {
    set("unit","只");
    set("value", 100000);
    set("material","jade");
    set("long","一只白森森的圈子。\n");
  }
  set("unique", 1);
  set("no_sell", "金刚琢乃法宝没人敢买也。");
  set("no_drop", "金刚琢乃法宝不可扔弃也。");
  set("no_give", "金刚琢乃法宝不可赠人也。");
  set("replace_file", "/d/qujing/jindou/obj/zhuofake.c");
  set("is_monitored",1);
  setup();
} 