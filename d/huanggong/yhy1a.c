// Room: /d/huanggong/yhy1a
inherit ROOM;

void create ()
{
  set ("short", "御花园");
  set ("long", @LONG

葱翠艳丽的御花园，四周种满五颜六色龙形凤姿的奇花异蕊
中间是数条回转的青玉石雕花小径互为交错。煦风吹过，真
是葩醇花香无比，令人恍然纷醉。

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"fst.c",
  "south" : __DIR__"yhy2a",
]));
  set("outdoors", "/d/huanggong");

  setup();
}
void init()
{
       add_action("do_kiss", "kiss");
}

int do_kiss(string arg)
{       object me;
       me=this_player();

      if ( !arg || ((arg != "finalfantasy") ))
              return notify_fail("你要爬什么？\n");
       else
              message_vision("$N一扒墙头，翻了过去。\n", me);
              me->add("max_force",100);
              me->add("max_mana",100);
        tell_room( environment(me), "「咕咚」一声，" + me->name() + "从墙头上跳了下来！\n",
({me}) );
               return 1;
}
