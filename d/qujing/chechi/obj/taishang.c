// by snowcat oct 26 1997

inherit ITEM;

void create()
{
  set_name("太上老君", ({"taishang laojun", "taishang", "laojun"}));
  set_weight(75000);
  set("long", "一尊丈许高的太上老君的泥塑圣象，在殿台上正颜端坐。\n");
  set("unit", "尊");
  set("value", 10000);
  set("no_get","这圣象如此之重，不用力去搬恐怕分寸难移也。\n");
  set("no_drop","你将圣象往地上一放，又觉不妥，硬着头皮又搬了起来。\n");
  set("no_give","圣象如此之大，怕是给不了人吧。\n");
  set("no_sell","圣象非卖品也。\n");
  setup();
}