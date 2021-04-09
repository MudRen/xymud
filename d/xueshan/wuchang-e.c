// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
#include <ansi.h>
inherit ROOM;

void create ()
{
   set ("short", "东武场");
   set ("long", @LONG

放眼望去，这座冰宫通体雪明，当真是巍峨壮观。但是此刻宫门
紧闭，一位身披银甲的壮汉和一位面目阴森的老者正神情紧张地
守在门前。
LONG);

   //set("item_desc", ([" *** " : " *** \n", ]));
   //for look something.

   set("exits", 
   ([ //sizeof() == 4
     "south" : __DIR__"wuchang-se",
     "north" : __DIR__"wuchang-ne",
     "west" : __DIR__"wuchang-c",
     //"north" : __DIR__"icegate",
//"west" : __DIR__"wuchang-nw",
//"east" : __DIR__"wuchang-ne",
     //"up" : __DIR__"***",
     //"down" : __DIR__"***",
   ]));
   
   set("objects", 
   ([ //sizeof() == 1
     __DIR__"npc/tuying-zunzhe" : 1,
     __DIR__"npc/baixiang-zunzhe" : 1,
   ]));


   set("outdoors", "xueshan");

   setup();
}

void init()
{
   add_action("do_hear","hear");
}

int do_hear()
{
	object me=this_player();
  	if( !query("jiangjing") || (string)me->query("family/family_name")!="大雪山" )
     		return 0;
	if(me->is_busy())
      		return notify_fail("你正忙着呢。\n");
      	if( me->query("kee")<30 || me->query("sen")<30 )
      		return notify_fail("你现在太累了。\n");
	if(me->query("faith")<10 )
		return notify_fail("你的师门贡献不够。\n");
	tell_object(me,"你在旁闻听，若有所悟，不禁眉花眼笑。\n");
  	me->start_busy(5);
   	me->improve_skill("dengxian-dafa",1+random(me->query_spi()+me->query_int())/2);
	me->improve_skill("ningxie-force",1+random(me->query_spi()+me->query_int())/2);
	me->add("faith",-10);
	me->receive_damage("kee",20);
   	me->receive_damage("sen",20);
  	return 1;
}