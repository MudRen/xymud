//Cracked by bear
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "火云堂");
  set ("long", @LONG

这里就是火云洞的中心－火云堂。正前方一把黑虎皮的软椅高高
在上，椅后一把玄色大锦旗，上面绣着“圣婴大王”四个金子。
两旁小妖林立，头顶几十把松油灯把堂上照的雪亮。
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"yongdao7",
  "west" : __DIR__"jin",
  "east" : __DIR__"tu",
  "northeast" : __DIR__"huo",
  "northwest" : __DIR__"mu",
  "north" : __DIR__"shui", 
]));

  set("objects", ([ /* sizeof() == 1*/
  __DIR__"npc/honghaier" : 1,
]));


  setup();
  
//   call_other("/obj/board/kusong_b", "???")
}
void init()
{
	add_action("do_hear","hear");
}

int do_hear()
{
	object me=this_player();
  	if( !query("jiangjing") || (string)me->query("family/family_name")!="火云洞" )
     		return 0;
	if(me->is_busy())
      		return notify_fail("你正忙着呢。\n");
      	if( me->query("kee")<30 || me->query("sen")<30 )
      		return notify_fail("你现在太累了。\n");
	if(me->query("faith")<10 )
		return notify_fail("你的师门贡献不够。\n");
	tell_object(me,"你在旁边听着，听着。不禁对本门心法有所领悟。\n");
  	me->start_busy(5);
	me->improve_skill("huomoforce",1+random(me->query_spi()+me->query_int())/2);
	me->improve_skill("pingtian-dafa",1+random(me->query_spi()+me->query_int())/2);
	me->add("faith",-10);
	me->receive_damage("kee",20);
   	me->receive_damage("sen",20);
  	return 1;
}
