//
#include <ansi.h>
inherit ROOM;
    
void create()
{
	set("short","梅山");
        set("no_chuqiao",1);
        set("channel_id","梅山七圣");
        set("alternative_die",1);
        set("任务",1);
        set("hell",1);
        set("objects",([
        	//"/d/maze/meishan/npc/jing" : random(3),
        	//"/d/maze/meishan/npc/guai" : random(3),
        ]));	
        setup();
}

void alternative_die(object who)
{
	int i,lost;
        object target;
        if( !who )
                return;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/meishan") )
        {
                set("alternative_die",0);
                who->die();
                set("alternative_die",1);
                return;
        }
        if( !userp(who) )
        {
        	if( !who->is_meishan() )
        	{
        		message_vision ("\n$N惨叫一声，化作一道青烟散去。\n\n",who);
        		destruct(who);
        		return;
        	}	
                who->dies();
                return;                         
        }
        
        //玩家死亡
        who->add_temp("maze/meishan_died",1);
        i = who->query_temp("maze/meishan_died");
        lost = 1000;
        lost*= i;
        if( lost>100000 )
        	lost = 100000;
        if( lost>who->query("combat_exp")/100 )
        	lost = who->query("combat_exp")/100;
        if( lost>0 )
        {	
		who->add("combat_exp",-lost);
		tell_object(who,HIR"【副本】梅山七圣：你损失了"+lost+"点武学经验。\n"NOR);
	}
        lost = 800;
        lost*= i;
        if( lost>80000 )
        	lost = 80000;
        if( lost>who->query("daoxing")/150 )
        	lost = who->query("daoxing")/150;
        if( lost>0 )
        {	
		who->add("daoxing",-lost);
		tell_object(who,HIR"【副本】梅山七圣：你损失了"+COMBAT_D->chinese_daoxing(lost)+"道行。\n"NOR);
	}
        who->powerup(0,1);
        who->save(1);
        if( who->query_temp("maze/entry_room") )
        {
        	who->move(who->query_temp("maze/entry_room"),2);
		message_vision("\n$N跌跌撞撞跑了过来。。。。\n",who);
		who->start_busy(3);
	}
	else
	{
		tell_object(who,HIR"【副本】梅山七圣：副本地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move(sprintf("/d/meishan/guanjiang%d",1+random(3)),2);
		who->start_busy(3);
	}
        return;
}                       

void init()
{
        add_action("do_cmds","",1);
}

int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/meishan") )
        	return notify_fail("你是怎么混进来的？！\n");
        return ::valid_leave(who,dir);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "recall","fly","team with","maphere","map","team dismiss",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}
int is_meishan(){ return 1;}