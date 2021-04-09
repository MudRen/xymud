#include <ansi.h>
inherit ROOM;

string boss_file = "/d/maze/tupo10/npc/boss";
    
void create()
{
	set("short","洞内");
	set("long",@LONG
忍着领人窒息的腥气，你钻进一个山洞中。洞口虽不大，里面却还宽敞。
但满地狼籍，到处是动物骨头，还有一些被撕成碎片的尸体。
LONG);	
        set("no_chuqiao",1);
        set("channel_id","为民除害");
        set("alternative_die",1);
        set("任务",1);
        setup();
}

void alternative_die(object who)
{
	int i,lost;
        object target;
        if( !who )
                return;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/tupo10") )
        {
                set("alternative_die",0);
                who->die();
                set("alternative_die",1);
                return;
        }
        if( !userp(who) )
        {
        	if( !who->is_beast() )
        	{
        		message_vision ("\n$N惨叫一声，化作一道青烟散去。\n\n",who);
        		destruct(who);
        		return;
        	}	
                who->dies();
                return;                         
        }
        
        //玩家死亡
        who->add_temp("maze/tupo10_died",1);
        i = who->query_temp("maze/tupo10_died");
        lost = 100;
        lost*= i;
        if( lost>5000 )
        	lost = 5000;
        if( lost>who->query("combat_exp")/100 )
        	lost = who->query("combat_exp")/100;
        if( lost>0 )
        {	
		who->add("combat_exp",-lost);
		tell_object(who,HIR"【副本】为民除害：你损失了"+lost+"点武学经验。\n"NOR);
	}
        lost = 50;
        lost*= i;
        if( lost>1000 )
        	lost = 1000;
        if( lost>who->query("daoxing")/150 )
        	lost = who->query("daoxing")/150;
        if( lost>0 )
        {	
		who->add("daoxing",-lost);
		tell_object(who,HIR"【副本】为民除害：你损失了"+COMBAT_D->chinese_daoxing(lost)+"道行。\n"NOR);
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
		tell_object(who,HIR"【副本】为民除害：副本地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move("/d/aolai/aolai");
		who->start_busy(3);
	}
        return;
}                       

void guai(object who)
{
	object npc;
	if( !query("guai") )
		return;
	npc = new(boss_file);
	npc->move(this_object());
	message_vision("\n$N从洞内深处窜了出来！\n\n",this_object());
	npc->powerup(0,1);
	if( who && present(who,this_object()) )
		npc->kill_ob(who);
}	

void init()
{
	add_action("do_cmds","",1);
	if( userp(this_player()) )
	{
		if( !query("guai") )
		{
			set("guai",1);
			call_out("guai",5,this_player());
		}
	}
}

int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/tupo10") )
        	return notify_fail("你是怎么混进来的？！\n");
        return ::valid_leave(who,dir);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "zhenshens","huhuan","recall","fly","team with",
                "move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}