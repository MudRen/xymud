 
inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("油糕", ({ "you gao", "gao" }) );
  set_weight(120);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "一碗炸得金黄的酥油糕。\n");
    set("unit", "碗");
    set("value", 110);
    set("food_remaining", 3);
    set("food_supply", 20);
  }
}

