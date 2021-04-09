// 封喉一剑剑狄风後 Difenghou.c
// Cracked by 凌惊雪 1-17-2003
#include <ansi.h>
inherit SUPER_NPC;

string ask_killer();
string ask_join();
string ask_cancel();
string ask_leave();
string change_level(){ return ("/quest/killer/kill.c")->change_level(this_player()); }	

void create()
{
       	set_name("狄风後", ({"di fenghou", "di", "fenghou"}));
       	set("long", HIG"封喉一剑剑狄风後，神秘杀手，一剑封喉。\n"NOR);
       	set("title", HIR"封喉一剑"NOR);
       	set("gender", "女性");
       	set("age", 33);
       	set_level(59);
       	set("attitude", "friendly");
       	set("force_factor", 125);
       	set("mana_factor", 100);
       	set_skill("literate",590);
       	set_skill("unarmed", 590);
       	set_skill("dodge", 590);
       	set_skill("force",590);
       	set_skill("lengquan-force",590);
       	set_skill("yanxing-steps",590);
       	set_skill("parry", 590);
       	set_skill("blade", 590);
   	set_skill("xuehejue",590);
   	set_skill("baihua-zhang",590);
   	map_skill("parry", "xuehejue");
   	map_skill("blade", "xuehejue");
   	map_skill("force", "lengquan-force");
   	map_skill("dodge", "yanxing-steps");
   	map_skill("unarmed","baihua-zhang");
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
	carry_object(0,"blade",1)->wield();
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
	if( me->query("killerside") && me->query("killerside")!="killer" )
		return "你是何人？！老娘可不记得手下有你这一号！";
	i = me->query("mark/luoyang_xuehejue");
	if( i>0 && me->query_skill("xuehejue",2)<i*10 )
		return "你的「"NOR HIR"血河诀"NOR CYN"」等级也太低了，老娘怕不保险，你且下去练习练习(practice)。"NOR;
	if( !me->query_temp("killerside") )	
		me->set_temp("killerside","killer");	
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
		return ("你真的愿意(agree)入金衣楼？");
	}
	return "你是官府的细作吧？！";
}

string ask_leave()
{
	object me=this_player();
  	if(me->query("killerside")=="killer") 
  	{
        	me->set_temp("killerside_leave", 1);
          	return ("离开金衣楼，得损失所学血河诀、金衣楼称号以及所做任务记录，你真愿意(true)？");
  	}
  	return ("哥恩滚~~~，别来烦老娘。\n");
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
	if( me->query("mark/luoyang_pingfeng")!=0 )
	{
		me->delete("mark/luoyang_pingfeng");
		tell_object(me,HIR"【系统】你失去了所有的「"HIY"屏风四扇门"HIR"」学习点数。\n"NOR);
	}
	if( me->query_skill("pingfeng",2)>0 )
		me->delete_skill("pingfeng");	
}

int do_agree(string arg)
{
	if(this_player()->query_temp("killerside")
	&& !this_player()->query("killerside") )
	{
		message_vision("$N答道：在下愿意效劳。\n\n", this_player());
		EMOTE_D->do_emote(this_object(), "u&me",0,CYN,0,0,0);
		tell_object(this_player(),CYN+name()+CYN"说道：得你之助，金衣楼终将春秋万载，一统江湖！\n"NOR);
		this_player()->set("killerside", "killer");
		CHANNEL_D->do_channel(this_object(),"rumor","听说"+this_player()->name()+HIM"加入了〖"HIR"金衣楼"HIM"〗。"NOR);
		this_player()->delete_temp("killerside");
		clear_killjob(this_player());
		if( this_player()->is_titles("雪衣神捕") 
		 && this_player()->remove_title("雪衣神捕",1) )
			tell_object(this_player(),HIY"【系统】由于你转换阵营，你失去了称号：「"HIW"雪衣神捕"NOR HIY"」。\n"NOR);
		if( !this_player()->is_titles("金衣楼众") )
		{
	 		if( this_player()->set_titles("金衣楼众") )
	 			tell_object(this_player(),HIY"【系统】你获得了称号：「"HIR"金衣楼众"NOR HIY"」。\n"NOR);
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
	 && this_player()->query("killerside")=="killer" ) 
  	{
		message_vision("$N答道：我愿意。\n\n", this_player());
		EMOTE_D->do_emote(this_object(), "sigh",0,CYN,0,0,0);
  		tell_object(this_player(),CYN+name()+CYN"说道：罢了罢了，强拧的瓜儿也不甜，你且去吧。\n"NOR);
  		this_player()->delete("killerside");
		if( this_player()->is_titles("金衣楼众") 
		 && this_player()->remove_title("金衣楼众",1) )
			tell_object(this_player(),HIY"【系统】由于你放弃阵营，你失去了称号：「"HIR"金衣楼众"NOR HIY"」。\n"NOR);
  		this_player()->delete_temp("killerside_leave");
  		if( this_player()->query("mark/luoyang_xuehejue")!=0 )
		{
			this_player()->delete("mark/luoyang_xuehejue");
			tell_object(this_player(),HIR"【系统】你失去了所有的「"HIR"血河诀"HIR"」学习点数。\n"NOR);
		}
  		this_player()->delete_skill("xuehejue");
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
	if( skill=="xuehejue" )
	{
		if( me->query_skill("xuehejue",2)>0 )
		{
  			tell_object(me,CYN+name()+CYN"说道：你难道是来消遣老娘的吗？自己下去仔细练习(practice)去！\n"NOR);
  			return 1;
  		}
  		else
  		{
  			tell_object(me,CYN+name()+CYN"说道：我只教你一次，以后就全靠你自己仔细练习(practice)。\n"NOR);
  			return 0;
  		}
  	}
  	tell_object(me,CYN+name()+CYN"懒洋洋的朝你看了一眼。\n"NOR);
   	return 1;
}

void kill_ob(object who)
{
	if( !who )
		return;
	tell_object(who,CYN+name()+CYN"撇了撇嘴，朝你摇了摇头。\n"NOR);
	this_object()->remove_killer(who);
	who->remove_killer(this_object());
}

