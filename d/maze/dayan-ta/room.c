#include <ansi.h>
inherit ROOM;
   
void create()
{
	set("short","大雁塔副本");
        set("channel_id","大雁塔副本");
        set("alternative_die",1);
        setup();
}

void alternative_die(object who)
{
	int i,lost;
        object target;
        string file;
        if( !who )
                return;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/dayan") )
        {
                set("alternative_die",0);
                who->die();
                set("alternative_die",1);
                return;
        }
//        message_vision ("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n",who);          
        if( !userp(who) )
        {
                target = who->query_temp("last_damage_from");
                who->clear_condition();
                if( target && present(target,this_object()) 
                 && ( wizardp(target)
                   || (target->query_level()>=30&&target->query_level()<40)) ) 
                        who->reward_ob(target);
                if( who )  destruct(who);
                return;                         
        }
        //玩家死亡
        who->powerup(0,1);
        file = sprintf("/data/maze/%s/dayan-ta/enter.c",who->query("id"));
        if( file_size(file)>0 )
        {
        	who->move(file,2);
		message_vision("\n\n一干沙弥七手八脚将血肉模糊的$N抬了过来。一旁的法明长老慌忙赶紧上前，抢救了半天，才把$N从鬼门关救了回来。。。。\n\n",who);
	}
	else
	{
		tell_object(who,HIG"【副本】大雁塔：地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move("/d/eastway/ciensiw",2);
	}
        return;
}                       


int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/dayan") )
        	return notify_fail("你是怎么混进来的？！\n");
       	return ::valid_leave(who,dir);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "zhenshens","huhuan","recall","move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}
