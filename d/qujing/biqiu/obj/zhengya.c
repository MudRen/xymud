//Cracked by Roath
// by snowcat 11/22/1997
 
inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("香汁蒸鸭", ({ "xiangzhi zhengya", "zhengya", "ya" }) );
  set_weight(180);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "一只蒸得香香的浇汁蒸鸭。\n");
    set("unit", "只");
    set("value", 300);
    set("food_remaining", 4);
    set("food_supply", 45);
  }
}

