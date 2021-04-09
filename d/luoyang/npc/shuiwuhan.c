// 雪衣神侯水舞寒 Shuiwuhan.c
// Cracked by 凌惊雪 1-17-2003
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string ask_killer();
string ask_join();
string ask_cancel();
string ask_leave();
string change_level(){ return ("/quest/killer/kill.c")->change_level(this_player()); }	

void create()
{
	set_name("水舞寒", ({"shui wuhan", "shui", "wuhan"}));
       	set("long", 
HIG"曾凭借一身独步天下的一气贯日月内功闯荡四方，足迹遍布四洲大陆
每个角落，是个默默无闻的英雄。晚年归隐南部洲大唐洛阳神侯府，
收录手下，运筹帷幄，尽剿天下匪徒。独创独门招式屏风四扇门，取
公门六扇之意。\n"NOR);
       	set("title", HIW"雪衣神侯"NOR);
       	set("gender", "男性");
       	set("age", 44);
       	set("attitude", "friendly");
       	set_level(89);
       	set("force_factor", 125);
       	set("mana_factor", 100);

       	set_skill("literate", 890);
       	set_skill("dodge",390);
       	set_skill("force",390);
       	set_skill("parry",390);
   	set_skill("pingfeng",390);
   	map_skill("unarmed", "pingfeng");
   	map_skill("force", "pingfeng");
   	map_skill("parry", "pingfeng");
   	set("inquiry", ([
		"任务": (: ask_killer :),
          	"kill": (: ask_killer :),
          	"加入": (: ask_join :),
          	"join": (: ask_join :),
          	"失手": (: ask_cancel :),
          	"cancel": (: ask_cancel :),
          	"离开": (: ask_leave :),
          	"噩梦": (: change_level :),
	]));
	set("env/test","HIB");
	set("skill_public",1);
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"unarmed",1)->wield();
	powerup(1,1);	
}

string ask_cancel()
{
	return ("/quest/killer/kill.c")->cancel_me(this_player());
}

string ask_killer()
{
	int i;
	string msg;
	mapping job;
	mixed foo;
	object me = this_player();
	
	if( me->query_level()<30 )
		return RANK_D->query_respect(me)+"实战经验不足，这危险的差使不作也罢。";
	if( me->query("killerside") && me->query("killerside")!="officer" )
		return "你是何人？本府有你这个人么？！";
	i = me->query("mark/luoyang_pingfeng");
	if( i>0 && me->query_skill("pingfeng",2)<i*10 )
		return "你的「"NOR HIY"屏风四扇门"NOR CYN"」等级也太低了，老夫怕不保险，你且下去练习练习(practice)。"NOR;		
	if( !me->query_temp("killerside") )	
		me->set_temp("killerside","officer");	
	foo = me->doing_job("杀手任务");
	if( foo )
	{
		if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	} 
	return ("/quest/killer/kill.c")->query_yao(me);
}

void init()
{
        add_action("do_agree", "agree");
        add_action("do_true", "true");
}

string ask_join()
{
	object me=this_player();
	if(!me->query("killerside")) 
	{
		me->set_temp("killerside", 1);
		return ("你真的愿意(agree)为我神侯府效力？");
	}
	return "呵呵，此事多说无益。";
}

string ask_leave()
{
	object me=this_player();
  	if( me->query("killerside")=="officer" ) 
  	{
        	me->set_temp("killerside_leave", 1);
          	return ("离开神侯府，得损失所学屏风、神侯府称号以及所做任务记录，你真愿意(true)？");
  	}
	return 0;
}

void clear_killjob(object me)
{
	mapping job;
	if( !me )
		return;
	if( mapp(job=me->query_xy_job()) )
	{
		if( !undefinedp(job["杀手任务"]) )
		{
			job = job["杀手任务"];
			job["succ"] = 0;
			job["fail"] = 0;
		}
	}
	if( me->query("mark/luoyang_xuehejue")!=0 )
	{
		me->delete("mark/luoyang_xuehejue");
		tell_object(me,HIR"【系统】你失去了所有的「"HIR"血河诀"HIR"」学习点数。\n"NOR);
	}
	if( me->query_skill("xuehejue",2)>0 )
		me->delete_skill("xuehejue");	
}

int do_agree(string arg)
{
	if(this_player()->query_temp("killerside")
	&& !this_player()->query("killerside") )
	{
		message_vision("$N答道：在下愿意效犬马之劳。\n\n", this_player());
		EMOTE_D->do_emote(this_object(), "great",0,CYN,0,0,0);
		tell_object(this_player(),CYN+name()+CYN"说道：得你之助，东土终将国泰安康，风调雨顺！\n"NOR);
		this_player()->set("killerside", "officer");
		CHANNEL_D->do_channel(this_object(),"rumor","听说"+this_player()->name()+HIM"加入了〖"HIY"洛阳神侯府"HIM"〗。"NOR);
		this_player()->delete_temp("killerside");
		clear_killjob(this_player());
		if( this_player()->is_titles("金衣楼众") 
		 && this_player()->remove_title("金衣楼众",1) )
			tell_object(this_player(),HIY"【系统】由于你转换阵营，你失去了称号：「"HIR"金衣楼众"NOR HIY"」。\n"NOR);
		if( !this_player()->is_titles("雪衣神捕") )
		{
	 		if( this_player()->set_titles("雪衣神捕") )
	 			tell_object(this_player(),HIY"【系统】你获得了称号：「"HIW"雪衣神捕"NOR HIY"」。\n"NOR);
		}
		this_player()->set_job_level("杀手任务",0);
		this_player()->save(1);
		return 1;
	}
	return 0;
}

int do_true(string arg)
{
  	if( this_player()->query_temp("killerside_leave")
	 && this_player()->query("killerside")=="officer" ) 
  	{
		message_vision("$N答道：我愿意。\n\n", this_player());
		EMOTE_D->do_emote(this_object(), "sigh",0,CYN,0,0,0);
  		tell_object(this_player(),CYN+name()+CYN"说道：罢了罢了，强拧的瓜儿也不甜，你且去吧。\n"NOR);
  		this_player()->delete("killerside");
		if( this_player()->is_titles("雪衣神捕") 
		 && this_player()->remove_title("雪衣神捕",1) )
			tell_object(this_player(),HIY"【系统】由于你放弃阵营，你失去了称号：「"HIW"雪衣神捕"NOR HIY"」。\n"NOR);
  		this_player()->delete_temp("killerside_leave");
  		if( this_player()->query("mark/luoyang_pingfeng")!=0 )
		{
			this_player()->delete("mark/luoyang_pingfeng");
			tell_object(this_player(),HIR"【系统】你失去了所有的「"HIY"屏风四扇门"HIR"」学习点数。\n"NOR);
		}
  		this_player()->delete_skill("pingfeng");
  		clear_killjob(this_player());
  		this_player()->set_job_level("杀手任务",0);
  		this_player()->save(1);
  		return 1;
  	}
  	return 0;
}

int recognize_apprentice(object ob){return 1;}

int prevent_learn(object me, string skill)
{
	if( skill=="pingfeng" )
	{
		if( me->query_skill("pingfeng",2)>0 )
		{
  			tell_object(me,CYN+name()+CYN"说道：你难道是来消遣老夫的吗？自己且下去仔细练习(practice)。\n"NOR);
  			return 1;
  		}
  		else
  		{
  			tell_object(me,CYN+name()+CYN"说道：老夫只教你一次，以后就全靠你自己仔细练习(practice)。\n"NOR);
  			return 0;
  		}
  	}
  	tell_object(me,CYN+name()+CYN"冲着你呵呵地笑了几声。\n"NOR);
   	return 1;
}

void kill_ob(object who)
{
	if( !who )
		return;
	tell_object(who,CYN+name()+CYN"冲着你呵呵地笑了几声。\n"NOR);
	this_object()->remove_killer(who);
	who->remove_killer(this_object());
}	