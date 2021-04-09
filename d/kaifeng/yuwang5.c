inherit ROOM;

void create ()
{
        set ("short", "禹王林");
        set ("long", @LONG

禹王林浓密浩瀚如海，远风吹过，林涛阵阵。雾从脚下生，有如一望
无际万里的纱帐飘渺似烟波海上。近处有一巨大的青铜雕花旗杆，有
一旗帜飘扬，上书“天御玉执禹王爷万年妖魔大会”。

LONG);
        set("exits", ([
                "west" : __DIR__"yuwang4",
                "east" : __DIR__"yuwang6",
        ]));
        set("objects", ([
                __DIR__"npc/zu" :  2,
                __DIR__"npc/yuwangye" :  1,
        ]));

        set("no_fight",1);
        set("no_magic",1);
        set("outdoors","kaifeng");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( !wizardp(me) && dir == "east" )
                return notify_fail("禹王卒一把拦住了你。\n");
        return ::valid_leave(me, dir);
}
