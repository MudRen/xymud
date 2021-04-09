//modified by bear
inherit ROOM;
#include <ansi.h>

void create ()
{
	set ("short", "龙宫正殿");
	set ("long", @LONG

正殿之上悬一明珠，把诺大一殿照得通亮。两旁桌椅玉石打造而成，　　
当中还嵌着无数珠宝。两边墙上挂了两幅画，看起来相当的陈旧。　　　
南北是两座偏殿。

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "westdown" : __DIR__"inside2.c",
  "east" : __DIR__"inside4",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/longwang" : 1,
]));
        set("water", 1);
	setup();
}

void init()
{
	add_action("do_hear","hear");
}

int do_hear()
{
	object me=this_player();
  	if( !query("jiangjing") || (string)me->query("family/family_name")!="东海龙宫" )
     		return 0;
	if(me->is_busy())
      		return notify_fail("你正忙着呢。\n");
      	if( me->query("kee")<30 || me->query("sen")<30 )
      		return notify_fail("你现在太累了。\n");
	if(me->query("faith")<10 )
		return notify_fail("你的师门贡献不够。\n");
	tell_object(me,"你在旁边听着，听着。不禁对本门的避水之术有所领悟。\n");
  	me->start_busy(5);
	me->improve_skill("seashentong",1+random(me->query_spi()+me->query_int())/2);
   	me->improve_skill("dragonforce",1+random(me->query_spi()+me->query_int())/2);
	me->add("faith",-10);
	me->receive_damage("kee",20);
   	me->receive_damage("sen",20);
  	return 1;
}

int valid_leave()
{
    if(
       (present("dao kan dao", this_player()))
       || (present("jiu gu cha", this_player()))
       || (present("mei hua chui", this_player()))
       || (present("hua gan ji", this_player()))
      )
        return notify_fail("龙宫至宝不能随便带走！\n");
    return ::valid_leave();
}

