inherit ROOM;
#include <ansi.h>
#include "sea.h"

nosave int *NU = ({1,2,3,4,5,6,7,8});
nosave object tieguaili = 0;
nosave object hanzhongli = 0;
nosave object ludongbin = 0;
nosave object zhangguolao = 0;
nosave object caoguojiu = 0;
nosave object hanxiangzi = 0;
nosave object lancaihe = 0;
nosave object hexiangu = 0;

void create ()
{
	string look;
  	set("short", "东海之滨");
  	set("long", @LONG
面前便是东海，茫茫大海望不到边际。海面上波涛汹涌，
几丈高的浪头此起彼伏，象是要吞灭一切敢于到海上的东西。
也许这里便是路的尽头，面前的大海对一个凡人来说是不可逾
越的。
LONG);
	set("exits", ([
  		"west" : this_object(),
	]));
	look = "
海滨
    
这里没有明显的大道通往内地。而另一面是一片汪洋大海。你
只好沿着海边行走，希望能找出一条大路来。

    这里明显的出口是 "HIG"west"NOR" 和 "HIG"east"NOR"。
  龙王九子之 蒲牢(Pu lao)\n\n";
  	set("item_desc", ([
  		"west" : look,
  	]));	
	setup();
}

int valid_leave(object me,string dir)
{
	if( dir=="west" )
		return notify_fail("还是安心跟随八仙遨游东海吧，免得出了纰漏。\n");
	return ::valid_leave(me,dir);
}

object random_baxian()
{
	switch(random(8))
	{
		case 0 : return tieguaili;
		case 1 : return hanzhongli;
		case 2 : return ludongbin;
		case 3 : return zhangguolao;
		case 4 : return caoguojiu;
		case 5 : return hanxiangzi;
		case 6 : return lancaihe;
		default: return hexiangu;								
	}
}

void start_story3(object npc,object me,object room)
{
	if( !clonep(this_object()) )
		return;
	if( !me || me!=query("owner") )
	{
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}
	npc->donghai();
	npc->move(room);
	if( npc->query_temp("ridee") )
		(npc->query_temp("ridee"))->move(room);
	if( npc==me->query_temp("pendding/wzg_baxianVIP") )
	{
		me->delete_temp("pendding/wzg_baxianVIP");
		me->move(room);	
	}
	REMOVE_D->add_room(this_object(),5);	
}

void start_story2(object me)
{
	object npc,room;
	if( !clonep(this_object()) )
		return;
	if( !me || me!=query("owner") )
	{
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}
	if( !present(me,this_object()) )
	{
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}
	message_vision("\n\n八仙再次来到东海边，仿佛回到了那些无忧无虑快乐的日子，高兴得各施仙法就地开怀畅饮。\n\n"NOR, me);
	npc = random_baxian();
	if( !npc )
	{
		tell_object(me,"出错了！请联系当值巫师。\n");
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}
	message_vision("酒至酣时，$N意犹未尽，说道：都说蓬莱、方丈、瀛洲三神州景致秀丽，我等何不去游玩观赏？\n诸仙激情四溢，齐声附和。\n",me);
	npc = random_baxian();
	message_vision("$N笑道：吾等即为仙人，今番渡海不得乘舟，只凭个人道法，意下如何？\n",npc);
	message_vision("众仙听了，欣然赞同，一齐弃座而起。\n",me);
	npc = random_baxian();
	message_vision("$N面露难色，$n一旁笑道："+RANK_D->query_respect(me)+"便随我来。\n",me,npc);
	me->set_temp("pendding/wzg_baxianVIP",npc);
	room = clone_object(__DIR__"sea2");
	room->set("owner",me);
	REMOVE_D->add_room(room,3600);
	remove_call_out("start_story3");
	if( tieguaili==npc )
		call_out("start_story3",9,tieguaili,me,room);
	else	call_out("start_story3",1,tieguaili,me,room);	

	if( hanzhongli==npc )
		call_out("start_story3",9,hanzhongli,me,room);
	else	call_out("start_story3",2,hanzhongli,me,room);	

	if( ludongbin==npc )
		call_out("start_story3",9,ludongbin,me,room);
	else	call_out("start_story3",3,ludongbin,me,room);	

	if( zhangguolao==npc )
		call_out("start_story3",9,zhangguolao,me,room);
	else	call_out("start_story3",4,zhangguolao,me,room);	

	if( caoguojiu==npc )
		call_out("start_story3",9,caoguojiu,me,room);
	else	call_out("start_story3",5,caoguojiu,me,room);	

	if( hanxiangzi==npc )
		call_out("start_story3",9,hanxiangzi,me,room);
	else	call_out("start_story3",6,hanxiangzi,me,room);	

	if( lancaihe==npc )
		call_out("start_story3",9,lancaihe,me,room);
	else	call_out("start_story3",7,lancaihe,me,room);	

	if( hexiangu==npc )
		call_out("start_story3",9,hexiangu,me,room);
	else	call_out("start_story3",8,hexiangu,me,room);	
}

void start_story(object me,int v)
{
	object npc;
	if( !clonep(this_object()) )
		return;
	if( !me || me!=query("owner") )
	{
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}
	if( !present(me,this_object()) )
	{
		tell_object(me,HIY"【灵台观礼】八仙过海：你中断了任务进程，任务失败了！\n"NOR);
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		REMOVE_D->add_room(this_object(),5);
		return;
	}	
	switch(v)
	{
		case 1 : npc = new(__DIR__"tieguaili");tieguaili = npc;break;
		case 2 : npc = new(__DIR__"hanzhongli");hanzhongli = npc;break;
		case 3 : npc = new(__DIR__"ludongbin");ludongbin = npc;break;
		case 4 : npc = new(__DIR__"zhangguolao");zhangguolao = npc;break;
		case 5 : npc = new(__DIR__"caoguojiu");caoguojiu = npc;break;
		case 6 : npc = new(__DIR__"hanxiangzi");hanxiangzi = npc;break;
		case 7 : npc = new(__DIR__"lancaihe");lancaihe = npc;break;
		case 8 : npc = new(__DIR__"hexiangu");hexiangu = npc;break;
	}
	message_vision(HIB"\n一阵清风吹来，"+npc->name()+HIB"从空中降落…… \n"NOR,me);
	npc->move(this_object());
	npc->set("owner",me);
	me->set_temp("pendding/wzg_baxian"+v,npc);
	if( random(2) )
		EMOTE_D->do_emote(npc, ({"haha","hehe","hoho","hi","hmm","back",})[random(6)],0,CYN,0,0,0);
	else	message_vision("$N朝$n一稽首："+RANK_D->query_respect(me)+"请了。\n",npc,me);
	
	NU-= ({v});
	NU-= ({0});
	if( !NU || !arrayp(NU) || sizeof(NU)<1 )
	{
		remove_call_out("start_story");
		remove_call_out("start_story2");
		remove_call_out("start_story3");
		call_out("start_story2",2+random(3),me);
		return;
	}
	v = NU[random(sizeof(NU))];
	remove_call_out("start_story");
	call_out("start_story",1+random(3),me,v);
}