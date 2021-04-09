//负责存放妖。
#include <ansi.h>

string *ygs = ({
        "baihuagu","xueshan","shushan","putuo","moon",
	"dragon","hyd","wudidong",
	//"fangcun","hell","jjf","pansi","wzg",
});	

void create()
{
    seteuid(getuid());
}

string cancel_me(object who)
{
	mixed foo,xx;
	if( !who )
		return 0;
	foo = who->cancel_job("门派任务");
	if( !foo || !stringp(foo) )
		return 0;
	if( foo=="你真是没用，便再给你一次机会吧！" )
	{
		if( who->query("faith")>0 )
		{
			who->add("faith",-1);	
			tell_object(who,HIY"【师门】你失去了1点门派贡献。\n"NOR);
		}
		if( objectp(xx=who->query_temp("family_zi")) )
			xx->leave();	
	}
	return foo;	
}

string query_seed(object me)
{
	string msg,where;
	object seed;
	int lvl;
	if( !me )
		return 0;
	lvl = me->query_job_level("门派任务");
	if( lvl>=10 )
		lvl = 0;
	lvl+= 1;
	seed = new(__DIR__"obj/seed");
	where = seed->invocation(me);
	if( !where || !stringp(where) )
		return "无怪可杀。";
	seed->set("stay_time",time());	
	me->set_job_level("门派任务",lvl);	
	msg = "本门长老前些时候云游之际，不慎在"+where+"遗落了一粒「"+seed->query_names()+"」的花籽(Hua zi)，你且前去守候，待其成熟后取(get)回。\n";
	return me->get_job("门派任务",({seed->query("name"),seed->query("id"),msg,seed,lvl}));		
}

string query_yao(object me)
{
	int lvl;
	string where,msg,name,id,title;
	object ghost;
	mixed foo;
	me = this_player();
	if( me->query_level()<20 )
		return "师门任务 20 级 开放。";
	foo = me->doing_job("门派任务");
	if( foo )
	{
		if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	}
        if( me->query_level()<40 || (me->query_level()>=40 && !me->query("fabao") && me->query("faith")<300000) )
	{ 
		if( me->query_temp("family_level") )
			ghost = new(sprintf(__DIR__"yg2/yg-%s",ygs[random(sizeof(ygs))]));
		else	ghost = new(sprintf(__DIR__"yg/yg-%s",ygs[random(sizeof(ygs))]));	
	}
	else
	{
		if( me->query_temp("family_level") )
		{
			if( random(10)>6 || me->query_job_level("门派任务")==9 || me->query("env/test") )
				return query_seed(me);
			else	ghost = new(sprintf(__DIR__"yg40-2/yg-%s",ygs[random(sizeof(ygs))]));				
		}
		else
		{
			if( random(10)>6 || me->query("env/test") )
				return query_seed(me);
			ghost = new(sprintf(__DIR__"yg40/yg-%s",ygs[random(sizeof(ygs))]));
		}
	}	
	if( !ghost )
		return "无怪可杀。";
	lvl = me->query_job_level("门派任务");
	if( lvl>=10 )
		lvl = 0;
	lvl+= 1;
	where=ghost->invocation(this_player(), lvl);
	if( !where || !stringp(where) )
		return "无怪可杀。";
	me->set_job_level("门派任务",lvl);		
	title = ghost->query("title");
	title = COLOR_D->clean_color(title);
	where = "「"+title+"」"+where;
	name = ghost->query("name");
	id = ghost->query("id");
	if( ghost->query("family/family_name")==this_player()->query("family/family_name") )
                msg = "本门"+where+"为非作歹，败坏门派名声，速速前往将之坑杀！\n";
        else    msg = ghost->query("family/family_name")+"的"+where+"妖言惑众，诋毁我派声誉，速速前往将之镇压，以儆效尤！\n";   
	return me->get_job("门派任务",({name,id,msg,ghost,lvl}));
}

string change_level(object me)
{
	if( !userp(me) || me->query("gin")<5 )
		return "你的活力不够了。";
	me->add("gin",-5);
	if( me->query_temp("family_level") )
	{
		me->delete_temp("family_level");
		me->set_job_level("门派任务",0);
		write("你变更门派任务为普通级别。\n");
		return "好的。";
	}
	if( time()>=me->query("last_rumor")+3600 )
	{
		me->set("last_rumor",time());
		CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY+me->name()+HIM"将自己的门派任务难度提升为"NOR RED"噩梦"NOR HIM"级！"NOR);
	}
	me->set_temp("family_level",1);
	me->set_job_level("门派任务",0);
	write("你变更门派任务为噩梦级别。\n");
	return "好的。";	
}
