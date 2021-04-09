#include <ansi.h>
inherit NPC;
#include "random_npc.h"

int ask_newbie()
{
	string *nn,name,id,file,msg,env;
	object ob,who = this_player();
	if( !userp(who) )
		return 0;
	if( time()<who->query("Xin/last_win")+3600*3 )
	{
		tell_object(who,query("name")+"说道：每3小时还能做一个环。\n");
		return 1;
	}
	if( time()<who->query("Xin/last_give")+180 )
	{
		tell_object(who,query("name")+"说道：你刚刚送过信，歇歇吧。\n");
		return 1;
	}			
	if( present("xin jian",who) )
	{
		tell_object(who,query("name")+"说道：你先把身上的信送完再说吧。\n");
		return 1;
	}	
	else
	{
		if( who->query("Xin/level")>0 )
		{
			tell_object(who,query("name")+"咬了咬牙，说道：你真是没用！\n");
			tell_object(who,query("name")+"说道：好吧，再给你一次机会！\n");
			who->set("Xin/level",0);
			who->set("Xin/last_fail",time());
			tell_object(who,query("name")+"说道：你一会再来吧！\n");
			return 1;
		}
	}
	if( time()<who->query("Xin/last_fail")+60 )
	{
		tell_object(who,query("name")+"说道：你刚刚失败过，下去面壁思过，我现在不放心交给你！\n");
		return 1;
	}
	nn = keys(Npcs);					
	name = nn[random(sizeof(nn))];		
	if( !name || !stringp(name) )
	{
		tell_object(who,query("name")+"说道：我正忙，你等等。\n");
		return 1;
	}
	id = Npcs[name][0];
	file = Npcs[name][1];
	sscanf(file,"/%s/npc/%*s",env);

	if( !env )
	{
		tell_object(who,query("name")+"说道：你刚刚送过，先歇歇吧...\n");
		return 1;
	}

	msg = sprintf("%s的%s",query_place(env),name);
					
	ob = new(__DIR__"paper");
	ob->set("xin",([
		"name" : name,
		"id"   : id,
		"msg"  : msg,
		"file" : file,
	]));
	if( ob->move(who) )
	{
		who->set("Xin/level",1);
		tell_object(who,query("name")+"说道：这里有封寄给"+msg+"的信，你找到并交给Ta。\n");
		return 1;
	}
	else
	{	
		if( ob ) destruct(ob);
		tell_object(who,query("name")+"说道：你背包满了吧？！");
		return 1;		
	}
}
	
void create()
{
	set_name("店小二", ({"xiao er","xiaoer","xiao","waiter","er"}));
    set("gender", "男性");
    set("combat_exp", 1000);
    set("age", 26);
    set("per", 14);
    set("attitude", "friendly");
    set("shen_type", 1);
    set_skill("unarmed", 10);
	set("inquiry", ([
		"give" : (: ask_newbie :),
	]));	
    setup();
    carry_object("/d/obj/cloth/linen")->wear();
}
