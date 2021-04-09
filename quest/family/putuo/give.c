//佛门六度-施度
#include <ansi.h>
inherit NPC;

nosave int my_money = 0;

object query_owner()
{
	object who;
	if( !query("owner_id") )
		return 0;
	who = find_player(query("owner_id"));
	if( !who || !living(who) )
		return 0;
	if( !environment() )
		return 0;
	if( !present(who,environment()) )
		return 0;
	if( who->is_knowing("putuo_bighammer") )
		return 0;	
	if( who->query_temp("pending/putuo_bighammer_give1") )
		return 0;	
	if( who->query_temp("pending/putuo_bighammer_fail") )
		return 0;	
	return who;
}				

void create()
{
	set_name("穷汉",({"qiong han","han",}));
	set("long", "一个神态猥琐的中年男子，衣不遮体，贫困潦倒。\n");
	set("gender", "男性");
	set("age", 40);
	set_level(3);
	set("num",5+random(5));
	set("attitude", "friendly");
	set("channel_id","观音菩萨(Guanyin pusa)");	
	setup();
	carry_object("/d/obj/cloth/linen")->wear();
}

void die()
{
	if( !query_owner() )
	{
		if( environment() )
			message("vision",name()+"急急忙忙的离开了。\n",environment());
		destruct(this_object());
		return;	
	}
	if( environment() )
		message_vision("\n\n$N忽的消失了，半空祥云阵阵，露出一位菩萨，朝$n叹了一口气。\n\n",this_object(),query_owner());
	if( random(2) )	
		CHANNEL_D->do_channel(this_object(),"chat","谓菩萨由修布施，能施与众生利乐。看见一切人生受苦，心生慈悲。");
	else	CHANNEL_D->do_channel(this_object(),"chat","人溺己溺，人饥己饥。布施所能，使苦人得乐，迷者受益。");
	tell_object(query_owner(),HIY"【师门】佛门六度：「檀那波罗蜜」任务失败。"NOR"\n");
	query_owner()->set_temp("pending/putuo_bighammer_fail",1);
	destruct(this_object());			
}

void unconcious()
{
	die();
}

void init()
{
	if( query_owner() && this_player()==query_owner() )
	{
		remove_call_out("quest");
		call_out("quest",1+random(3),this_player());
	}
}

void quest(object who)
{
	int damage;
	remove_call_out("quest");
	if( !who || !query_owner() )
	{
		die();
		return;
	}
	if( query("num")<=0 )
	{
		EMOTE_D->do_emote(this_object(), "haha",0,CYN,0,0,0);
		message_vision("\n\n$N忽的消失了，半空祥云阵阵，露出一位菩萨，朝$n哈哈一笑。\n\n",this_object(),who);
		if( random(2) )	
			CHANNEL_D->do_channel(this_object(),"chat","曰菩萨由修布施，能施与众生利乐。看见一切人生受苦，心生慈悲。");
		else	CHANNEL_D->do_channel(this_object(),"chat","曰人溺己溺，人饥己饥。布施所能，使苦人得乐，迷者受益。");
		tell_object(query_owner(),HIY"【师门】佛门六度：「檀那波罗蜜」任务完成。"NOR"\n");
		who->set_knowing("putuo_bighammer",1);
		tell_object(query_owner(),HIY"【师门】你度己先度人，成功领悟了「"HIR"大力降魔杵"HIY"」的奥妙。"NOR"\n");
		destruct(this_object());
		return;
	}
	EMOTE_D->do_emote(this_object(), "beg",geteuid(who),CYN,0,0,0);
	EMOTE_D->do_emote(this_object(), "beg","qiong han",CYN,0,0,0);
	damage = 50+random(200);
	this_object()->receive_wound("kee",damage);
	COMBAT_D->report_status(this_object(),1);
	add("num",-1);
	remove_call_out("quest");
	call_out("quest",5+random(5),this_player());	
}

void do_cure()
{
	if( my_money<=0 )
		return;
	if( query("eff_kee")>=this_object()->query_maxkee() )
	{
		if( query("kee")>=query("eff_kee") )
			return;
		my_money = my_money-1;
		this_object()->receive_heal("kee", 20+random(50));
		message_vision("$N深深吸了几口气，脸色看起来好多了。\n",this_object());	
	}
	else
	{
		if( my_money<3 )
			return;
		this_object()->receive_curing("kee",20+random(30));
		my_money = my_money-3;
		message_vision("$N吃下一些金创药，气色看起来好多了。\n"NOR,this_object());
		if( query("kee")>=query("eff_kee") || my_money<1 )
			return;
		my_money = my_money-1;
		this_object()->receive_heal("kee", 20+random(50));
		message_vision("$N深深吸了几口气，脸色看起来好多了。\n",this_object());	
	}	
}

int accept_money(object who,int v)
{
	if( v<10000 )
		return 0;
	if( !query_owner() || who!=query_owner() )
		return 0;	
	my_money+= v/10000;	
	EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
	call_out("do_cure",1);
	return 1;
}