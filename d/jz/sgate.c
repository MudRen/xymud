//Cracked by Roath

inherit ROOM;
void create()
{
  set ("short", "[1;33m钓鱼台[m");
  set ("long", @LONG

以前，这是达官贵人们钓鱼享乐的地方，如今江州城衰落了，
这个地方根本就没人看管了，即使这样，也是少有人来。台
的旁边有个小牌子(paizi)，上面好象写些什么内容。
LONG);
        set("exits", ([
        "north":__DIR__"dingan-3",
]));
        set("objects", ([
                __DIR__"npc/waiter": 1,
                ]));
        set("item_desc", ([
                "paizi": @TEXT
………………………………………………………………………………………………
                    钓鱼：鱼竿每付５两白银
………………………………………………………………………………………………
TEXT
        ]) );
  setup();
}
int valid_leave(object me, string dir)
{       if (dir == "north"&& me->query("fish") )
        me->delete("fish"); 
        return 1;
}
/*
void say()
{
        object me=this_player();
         write("卖鱼竿的对你说道：嘘~~不要打扰别人钓鱼。\n");
        return 0;
}
*/
