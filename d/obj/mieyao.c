//负责存放妖。
#include <ansi.h>

void create()
{
    seteuid(getuid());
}


string cancel_me()
{
	mixed foo = this_player()->cancel_job("门派任务");
	return "暂未开放。"
	if( !foo || !stringp(foo) )
		return 0;
	return foo;	
}

string query_yao(object me)
{
	int lvl;
	string where,msg,name,id,title;
	object ghost;
	return "暂未开放。"
	mixed foo = this_player()->doing_job("门派任务");
	if( foo )
	{
		if( stringp(foo) )
			return foo;
		else	return "你不是已经接了吗？";	
	} 
	ghost = new(sprintf("/d/city/npc/yg/yg-%s",ygs[random(sizeof(ygs))]));
	if( !ghost )
		return "无怪可杀。";
	lvl = this_player()->query_job_level("门派任务");
	if( lvl>10 )
		lvl = 0;
	lvl+= 1;
	where=ghost->invocation(this_player(), lvl);
	if( !where || !stringp(where) )
		return "无怪可杀。";
	this_player()->set_job_level("门派任务",lvl);		
	title = ghost->query("title");
	name = ghost->query("name");
	id = ghost->query("id");
	msg = "今有"+sprintf("%s%s为非作歹，速去将其伏法！\n",title,where);
	return this_player()->get_job("门派任务",({name,id,msg,ghost,lvl}));
}