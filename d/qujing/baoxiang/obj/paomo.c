// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("羊肉泡馍", ({"pao mo", "paomo"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一碗热乎乎的羊肉泡馍。\n");
    set("unit", "碗");
    set("value", 100);
    set("food_remaining", 4);
    set("food_supply", 50);
  }
}
