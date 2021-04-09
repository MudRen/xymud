inherit ROOM;
void create()
{
        set("short", "洗礼池");
        set("long", @LONG
这里是大唐兵马征战回来接受洗礼（ｓａｌｕｔｅ）的地方，
以求洗去杀孽之气。布置得很简单，中间一个水池，池中冒出袅
袅水湮。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
        "north" : __DIR__"baodian",
]));
        set("outdoors", "changan");
        setup();
}
void init()
{
       add_action("do_ponder","salute");
}
int do_ponder(string arg)
{
       object who;

       who = this_player();
        if((int) who->query("sen") <=100)
        return notify_fail("你的精神不够。\n");
       message_vision("$N将双手浸入水池中。\n" ,who);
       who->receive_damage("sen",50);
       if( (int)who->query("bellicosity") > 0)
           who->add("bellicosity", - (random((int)who->query("kar")) + 7 ) );
             if( (int)who->query("bellicosity") < 0)
                 who->set("bellicosity", 0);   //增加判断，避免杀气为负  龙追魂2009.06.09
       message_vision("$N身上的杀孽之气似乎轻了。 \n" , who);
       who->start_busy(1);
    return 1;
}

