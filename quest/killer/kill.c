//负责存放妖。
#include <ansi.h>

string *ygs = ({
        "baihuagu","xueshan","shushan","putuo","moon",
	"dragon","hyd","wudidong"
	//"fangcun","hell","jjf","pansi","wzg",
});	

void create()
{
    seteuid(getuid());
}

string cancel_me(object who)
{
	mixed foo;
	if( !who )
		return 0;
	foo = who->cancel_job("杀手任务");
	if( !foo || !stringp(foo) )
		return 0;
	if( foo=="你真是没用，便再给你一次机会吧！" )
	{
		if( who->query("killerside")=="officer" )
			return "真够窝囊的，神侯府的脸都被你丢光了！";
		else if( who->query("killerside")=="killer" )
			return "真够窝囊的，金衣楼的脸都被你丢光了！";
		else	return "唉，你且下去，我另外再找人吧。";
	}
	return "你有接任务吗？";
}

string query_yao(object me)
{
	int lvl;
	string where,msg,name,id,title;
	object ghost;
	mixed foo;
	if( !me )
		return 0;
	foo = me->doing_job("杀手任务");
	if( foo )
	{
		if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	}
	if( me->query_temp("killer_level") )
		ghost = new(sprintf(__DIR__"yg22/yg-%s",ygs[random(sizeof(ygs))]));
	else
	{	
		if( me->query("killerside") )
			ghost = new(sprintf(__DIR__"yg2/yg-%s",ygs[random(sizeof(ygs))]));
		else	ghost = new(sprintf(__DIR__"yg/yg-%s",ygs[random(sizeof(ygs))]));	
	}	
	if( !ghost )
		return "现在没有任务给你。";

	lvl = me->query_job_level("杀手任务");
	if( lvl>=10 )
		lvl = 0;
	lvl+= 1;
	where = ghost->invocation(me,lvl);
	if( !where )
		return "你先下去歇歇。";
	where = COLOR_D->clean_color(where);
	me->set_job_level("杀手任务",lvl);		
	title = ghost->query("title");
	name = ghost->query("name");
	id = ghost->query("id");
	if( me->query_temp("killerside")=="killer" )
	{
		msg = where+"附近损伤了我们不少手下，你去给他点颜色看看，让他知道我们我们也不是好惹的！\n";
		tell_object(me,CYN"狄风後说道：既然"+RANK_D->query_respect(me)+"愿意出手，本座就给你个任务，看你有没有胆量。\n"NOR);
	}
	else 
	{
		msg = where+"一带做些见不得光的勾当，你火速去剿灭他们，杜绝后患！\n";
		tell_object(me,CYN"水舞寒说道：既然"+RANK_D->query_respect(me)+"有心帮忙，本侯在这里就先代天下百姓谢过了。\n"NOR);
	}
	return me->get_job("杀手任务",({name,id,msg,ghost,lvl}));
}

string change_level(object me)
{
	if( !userp(me) || me->query("gin")<3 )
		return "你的活力不够了。";
	me->add("gin",-3);
	if( me->query_temp("killer_level") )
	{
		me->delete_temp("killer_level");
		me->set_job_level("杀手任务",0);
		write("你变更杀死任务为普通级别。\n");
		return "好的。";
	}
	if( time()>=me->query("last_rumor")+3600 )
	{
		me->set("last_rumor",time());
		CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY+me->name()+HIM"将自己的杀手任务难度提升为"NOR RED"噩梦"NOR HIM"级！"NOR);
	}
	me->set_temp("killer_level",1);
	me->set_job_level("杀手任务",0);
	write("你变更杀手任务为噩梦级别。\n");
	return "好的。";	
}
