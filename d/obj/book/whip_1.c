inherit ITEM;

void create()
{
        set_name("〖鞭法入门〗", ({"whip book", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
		set("value", 1000);
        set("material", "paper");
        set("skill", ([
                        "name": "whip",
                        "exp_required": 100,
                        "sen_cost": 20,
                        "difficulty": 20,
                        "max_skill": 70,
]) );
        }
}

