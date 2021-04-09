// watermelon.c 西瓜

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("西瓜", ({"watermelon", "xigua"}));
	set_weight(40);
	if (clonep())
		set_default_object(__FILE__);
	else {
                set("long", "一颗新鲜的西瓜。\n");
                set("unit", "颗");
		set("value", 80);
		set("food_remaining", 4);
		set("food_supply", 30);
	}
}
