// by canoe
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short","天牢");
	set("long",@LONG
这里是死牢，一般来到这里的都是十恶不赦的恶棍。地上
散落很多刑具,血迹斑斑!
如果你认为肚子饿了，可以用“jinshi”让狱卒给你食物。
如果你认为你的刑期满了，可以用“out”来离开这里。

LONG
);
	set("valid_startroom",1);
	set("no_fight",1);
	setup();
}

void init ()
{
	object me=this_player();
     	if(!wizardp(me))
	{
 		add_action("block_cmd","",1);      
		add_action("do_jinshi","jinshi"); 
 		me->set("startroom","/d/wiz/dalao.c");
 		me->save(1);
	}
}

int block_cmd()
{
	string verb = query_verb();
   	if (verb=="say") return 0; //allow say
   	if (verb=="help") return 0;
	if (verb=="look") return 0;
  	if (verb=="hp") return 0;
  	if (verb=="out") return 0;
   	if (verb=="jinshi") return 0;
   	return 1;
}

int do_out()
{
	object me=this_player();
	if( me->query_condition("no_pk_time") )
		return err_msg("安心坐牢吧。\n");
	message_vision("$N刑满释放！$N被转移到客栈。\n"NOR,me);
        me->move("/d/city/kezhan");
        me->delete("tongji/pktime");
	if(me->query("combat_exp")>10000) 
		me->add("combat_exp",-10000);
	me->set("startroom","/d/city/kezhan");
	tell_object(me,HIR"【系统】你损失了10000点武学经验。"NOR"\n");
	me->save();
	return 1;
}

int do_jinshi()
{
	object me=this_player();
	if( me->query("combat_exp")<1000 )
		return err_msg("你的武学经验不够。\n");
  	if((int)me->query("food")<100||(int)me->query("water")<100) 
      	{ 
      		message_vision("狱卒看着$N饥肠辘辘的样子，偷偷塞给$N一个包子和一瓶水。\n"NOR,me);
		tell_object(me,HIR"【系统】你损失了1000点武学经验。"NOR"\n");
       		me->set("food",1000);
       		me->set("water",1000);
		me->add("combat_exp",-1000);
      		me->save(1);
      	}
     	else	message_vision("$N向狱卒要东西吃，可惜狱卒不给。\n"NOR,me);
 	return 1;
}
