                 // wine.c 江米酒

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("江米酒", ({"mijiu"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "南方人爱吃的江米酒。\n");
                set("unit", "碗");
                set("value", 1200);
		set("food_remaining",120);
                set("food_supply", 120);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "江米酒",
                "drunk_apply": 10,
        ]));
}
