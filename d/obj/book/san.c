// literate.c

inherit ITEM;

void create()
{
        set_name("〖三字经〗", ({"book"}));
        set_weight(600);
                set("unit", "本");
		set("value", 1000);
        set("material", "paper");
        set("skill", ([
                        "name": "literate",
                        "sen_cost": 20,
                        "difficulty": 20,
                        "max_skill": 20,
]) );
}

