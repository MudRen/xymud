// girlbook.c

inherit ITEM;

void create()
{
        set_name("〖女儿经〗", ({"book","nu","shu"}));
        set_weight(1000);
                set("unit", "本");
	set("long",
	"一本小册子。讲的都是三从四德。你虽然不一定喜欢，拿来识字也是好的。\n");
        set("material", "paper");
        set("value", 1000);
        set("skill", ([
                        "name": "literate",
                        "exp_required": 1000,
                        "sen_cost": 10,
                        "difficulty": 10,
                        "max_skill": 70,
]) );
}

