#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "长思馆");
  	set ("long", @LONG
房中珠帘低垂，案上炉中点着一束沉香，轻烟袅绕。当地放著一张花梨大
理石大案，案上堆著各种名人法帖，并十数方宝砚，各色笔筒；那一边设
著斗大的一个汝窑花囊，插著满满的水晶球的白菊花。书案正中撂着几张
绢纸(paper)，字迹娟秀，似是嫦娥百般无赖之中所涂。
LONG);
	set("item_desc", ([ 
  		"paper" : "纸上反反复复地写着一句话：天不老，情难绝，心似双丝网，中有千千结。",
	]));
  	set("objects", ([
  		__DIR__"npc/change.c" : 1,
  		"/d/obj/flower/juhua.c" : 1,
	]));
  	set("exits", ([
  		"east" : __DIR__"huilang.c",
	]));
	setup();
}
void init()
{
	add_action("do_hear","lianwu");
}

int do_hear()
{
	object me=this_player();
  	if( !query("jiangjing") || (string)me->query("family/family_name")!="月宫" )
     		return 0;
	if(me->is_busy())
      		return err_msg("你正忙着呢。\n");
      	if( me->query("kee")<30 || me->query("sen")<30 )
      		return err_msg("你现在太累了。\n");
	if(me->query("faith")<10 )
		return err_msg("你的师门贡献不够。\n");
	tell_object(me,"你随歌起舞，不禁对月宫仙法有所领悟。\n");
  	me->start_busy(5);
	me->improve_skill("moonshentong",1+random(me->query_spi()+me->query_int())/2);
   	me->improve_skill("moonforce",1+random(me->query_spi()+me->query_int())/2);
	me->add("faith",-10);
	me->receive_damage("kee",20);
   	me->receive_damage("sen",20);
  	return 1;
}