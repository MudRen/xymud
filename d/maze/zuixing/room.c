#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit ROOM;
    
void create()
{
	set("short","廊间");
	set("long",@LONG
四下里静寂无声，借着月光只见长廊延伸到黑暗之中。小廊上是木
板铺地，打扫的极为干净，走在上面发出吱吱的响声，在这黑夜尤为刺
耳。走廊两面的木格上雕着一些山水人物。

LONG);		
        set("no_chuqiao",1);
        set("no_huicheng",1);
        set("channel_id","【阵法】");
        set("alternative_die",1);
        set("任务",1);
        set("hell",1);
        set("num",1+random(5));
        setup();
}

string query_enter_file()
{
	string str = query("mazeobj");
	int idx;
	idx = strsrch(str, "/", -1);
	str = str[0..idx-1];
	str+= "/enter";
	return str;
}

int alternative_die(object who)
{
	string start;
	int i,lost;
        object target;
        if( !who )
                return 1;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/zuixing")
         || !who->query_temp("pendding/jjf_break") )
                return 1;
        if( !userp(who) )
        {
        	who->set("no_corpse",1);
		return 1;
	}	
        //玩家死亡
        who->add_temp("maze/zuixing_died",1);
        i = who->query_temp("maze/zuixing_died");
        if( i<=0 ) i= 1;
        lost = 100;
        lost*= i;
        if( lost>10000 )
        	lost = 10000;
        if( lost>who->query("combat_exp") )
        	lost = who->query("combat_exp");
        if( lost>0 )
        {	
		who->add("combat_exp",-lost);
		tell_object(who,HIG"【醉星楼】你损失了"+lost+"点武学。\n"NOR);
	}	
        lost = 100;
        lost*= i;
        if( lost>10000 )
        	lost = 10000;
	lost = lost/2;
        if( lost>who->query("daoxing") )
        	lost = who->query("daoxing");
        if( lost>0 )
        {	
		who->add("daoxing",-lost);
		tell_object(who,HIG"【醉星楼】你损失了"+COMBAT_D->chinese_daoxing(lost)+"道行。\n"NOR);
	}
        who->powerup(0,1);
        who->save();
        start = query_enter_file();
        if( !start )
        	start = "/d/jjf/zuixing";
	if( file_size(start+".c")>0 )
        {
        	who->move(start);
		message_vision("\n\n【醉星楼】人声鼎沸，只见一道血肉模糊的人影跌跌撞撞从楼上跑了下来。。。。\n\n",who);
	}
	else
	{
		tell_object(who,HIG"【醉星楼】副本地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move("/d/jjf/zuixing",2);
	}
        return 0;
}                       

int valid_leave(object who,string dir)
{
	int i;
	string *strs,file,arg;
	object npc;
	mapping exit;
	if( wizardp(who) && who->query("env/test") )
		return ::valid_leave(who,dir);
	if( !who->query_temp("maze/zuixing") )
        	return notify_fail("你是怎么混进来的？！\n");
        exit = query("exits");
        if( !exit || !mapp(exit) || undefinedp(exit[dir]) )
        	return ::valid_leave(who,dir);
        if( !valid_move(who) )
        	return ::valid_leave(who,dir);
        if( who->is_fighting() )
        	return notify_fail("亲兵一把拉住了你。\n");	
	if( query("num")>0 )
	{
		npc = new("/d/maze/zuixing/npc/qinbing");
		npc->set_skills(who);
		if( !npc->move(this_object()) )
		{
			destruct(npc);
			return notify_fail("你小心翼翼的向前走着，一不小心脚步声有点大，你感觉放缓脚步，警惕的朝四下望了望。\n");
		}
		add("num",-1);
		npc->kill_ob(who);
		return notify_fail("\n黑暗中闪出一名护卫，拦住了你的去路！\n");
	}
	return ::valid_leave(who,dir);
}