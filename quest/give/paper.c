#include <ansi.h>
inherit ITEM;
#include "random_npc.h"

void create()
{
	set_name("信笺", ({ "xin jian","xin", }) );
	set_weight(100);
	set("unit", "张");
	set("long", "一张信笺，上面龙飞凤舞的写着一些字。\n");
	set("value", 50);
	set("no_give",1);
	set("no_put",1);
	set("no_get",1);
	set("changed",1);
     set("is_monitored",1);
	setup();
}

string name()
{
	string str,name = ::name();
        if( str=query("xin/msg") )
		name = "给"+str+"的"+query("name");
	return name;
}

string long()
{
	string ss,str = ::long();
	if( ss=query("xin/msg") )
		str+= "将它交给"+ss+"。\n";
	return str;
}

void init()
{
	add_action("do_give","give");
	add_action("do_drop","drop");		
}

int do_drop(string arg)
{
	object obj,me = this_player();	
	if( !present(this_object(),me) )
		return 0;
	if( !arg )
		return 0;
	if( arg!="all" )
	{		
		obj = present(arg,me);
		if( !obj || obj!=this_object() )
			return 0;
	}		
	if( !me->query("Xin/level") )
		return 0;
	if( !query("xin/name") )
		return 0;
	message_vision("$N决定人海茫茫，到哪里去找"+query("xin/name")+"，全无希望，鸭梨很大。\n",me);
	write("你决定放弃找人。\n");
	message_vision("$N丢下一封信。\n",me);
	write("你的送信环任务失败了。\n");
	me->set("Xin/level",0);
	me->add("Xin/num",-1);
	if( me->query("Xin/num")<0 )
		me->set("Xin/num",0);
	me->set("Xin/last_fail",time());
	if( arg=="all" )
	{
		destruct(this_object());
		return 1;
	}
	else
	{
		destruct(this_object());
		return 1;
	}
}

int do_give(string arg)
{
	int k;
	string id,type,env,*ids;
	string *nn,name,file,msg;	
	object ob,who,obj,me = this_player();
	
	if( !present(this_object(),me) )
		return 0;
	if( !arg )
		return 0;	
	if( sscanf(arg,"%s to %s",arg,id)!=2
	 && sscanf(arg,"%s %s",id,arg)!=2 )
		return 0;
	if( wizardp(me) )
		write("sscanf OK,id="+id+" arg="+arg+"\n");			
	obj = present(arg,me);
	if( !obj || obj!=this_object() )
		return 0;
	if( wizardp(me) )
		write("OBJ OK\n");			
		
	who = present(id,environment(me));
	if( !who || !living(who) || who->is_busy()
	 || who->is_fighting() || userp(who) )
		return 0;
	if( !query("xin/id") )
		return 0;
	if( me->is_busy() )
		return err_msg("你现在正忙着。\n");		
	if( who->query("id")!=query("xin/id") )
	{
		write(who->name()+"疑惑的看看你，“给我？你认错人了吧。”\n");
		write("对方不要你的东西。\n");
		return 1;
	}
	if( base_name(who)!=query("xin/file") )
	{
		write(who->name()+"疑惑的看看你，“给我？你认错人了吧，同名同姓的人很多，我不是你要找的那一个。。。。”\n");
		write("对方不要你的东西。\n");
		return 1;
	}
	
	if( random(2) )
		who->command("wow");
	if( random(3) )	
		who->command("thank "+me->query("id"));
		
	
	switch( me->query("Xin/level") )
	{
		case 1 : type = "armor";break;
		case 2 : type = "cloth";break;
		case 3 : type = "hand";break;
		case 4 : type = "kui";break;
		case 5 : type = "neck";break;
		case 6 : type = "pifeng";break;
		case 7 : type = "ring";break;
		case 8 : type = "shield";break;
		case 9 : type = "shoes";break;
		case 10: type = "waist";break;
		case 11: type = "wrists";break;
		default: type = 0;break;
	}
	if( me->query("Xin/level")>=11 )
	{
		write(HIY"恭喜恭喜！你完成了一整环的送信任务，功德无量啊。\n"NOR);
		if( type )
		{
			ob = new("/d/obj/narmor/"+type);
			who->set_skill("force",60+random(50));
			k = me->query("Xin/num")*500+2000;
			if( k>8000 )  k = 8000;
			who->add_temp("apply/karma",k);
			ob->init_armor(who);
			who->add_temp("apply/karma",-k);
			if( ob->move(me) )
			{
				write(who->name()+"神秘的从兜里掏出一件"+ob->name()+"给你。\n");
				CHANNEL_D->do_channel(who,"chat",me->name(1)+"功德无量，得到了"+ob->name()+HIC"！");
			}
			else
			{
				write("你的背包满了！\n");
				if( ob )
					destruct(ob);
			}
		}
		me->add("potential",10000);
		write(HIY"你得到了一万潜能的附加奖励。\n"NOR);				
		me->set("Xin/level",0);
		me->add("Xin/num",1);
		me->set("Xin/last_win",time());
		destruct(this_object());
		return 1;
	}

	nn = keys(Npcs);		
	name = nn[random(sizeof(nn))];		
	if( !name || !stringp(name) )
	{
		write(who->name()+"说道：啊哈，我现在有点忙，稍等稍等。。\n");
		me->start_busy(1);
		return 1;
	}
	id = Npcs[name][0];
	file = Npcs[name][1];
	sscanf(file,"/%s/npc/%*s",env);
	if( !env )
	{
		write(who->name()+"说道：啊哈，我现在有点小忙，稍等稍等。。\n");
		me->start_busy(1);
		return 1;
	}
	message_vision("$N满面笑意的望着$n，就是不说话。。。。\n\n",who,me);
	if( type )
	{
		ob = 0;
		ob = new("/d/obj/narmor/"+type);
		who->set_skill("force",60+random(50));
		k = me->query("Xin/num")*300+1000;
		if( k>8000 )  k = 8000;
		who->add_temp("apply/karma",k);
		ob->init_armor(who);
		who->add_temp("apply/karma",-k);
		if( ob->move(me) )
		{
			write(who->name()+"神秘的从兜里掏出一件"+ob->name()+"给你。\n");
		}
		else
		{
			write("坏了！你的背包满了！\n");
			if( ob )	destruct(ob);
		}
	}
	ob = 0;		 
	msg = sprintf("%s的%s",query_place(env),name);
	ob = new(__DIR__"paper");
	nn = keys(Items);
	if( nn && arrayp(nn) )
	{
		name = nn[random(sizeof(nn))];
		if( name )
		{
                        ids = Items[name][0];
                        ids+= ({"xin jian"});
			ob->set_name(name,ids);
			ob->set("unit",Items[name][1]);
			ob->set("long",Items[name][2]);
		}
	}	
	ob->set("xin",([
		"name" : name,
		"id"   : id,
		"msg"  : msg,
		"file" : file,
	]));
	me->set("Xin/last_give",time());
	if( ob->move(me) )
	{
		write(who->name()+"说道：呵呵，我这里有一"+ob->query("unit")+"给"+msg+"的"+ob->query("name")+"，本来准备亲自给Ta的，可惜我的膝盖中了一箭...\n");
		write(who->name()+"交给你一"+ob->query("unit")+ob->query("name")+"。\n");
		me->add("Xin/level",1);
		me->add("Xin/num",1);
		me->start_busy(1);
		destruct(this_object());
		return 1;
	}
	else
	{
		write("坏了！你的背包满了！\n");
		if( ob )	destruct(ob);
		me->start_busy(1);
		destruct(this_object());
		return 1;
	}
}
	
	
			
