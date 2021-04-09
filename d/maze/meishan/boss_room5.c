//常昊
#include <ansi.h>
inherit ROOM;

string boss_file = "/d/maze/meishan/npc/jindasheng";
    
void create()
{
	set("short","青仙庙");
	set("long",@LONG
这里是青水大仙的庙宇。这青水大仙也是新近才在梅山
落脚，据说大仙昔日也是梅山人士，后修道有成。最近甚是
灵验了数状百姓祈福。故有本地大户在此立了庙宇，弄些香
火。    
LONG);	
        set("no_chuqiao",1);
        set("channel_id","梅山七圣");
        set("alternative_die",1);
        set("任务",1);
        set("hell",1);
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

void guai()
{
	object npc;
	if( !query("guai") )
		return;
	npc = new(boss_file);
	npc->move(this_object());
	npc->setup();
}	

void init()
{
	add_action("do_cmds","",1);
	if( userp(this_player()) )
	{
		if( !query("guai") )
		{
			set("guai",1);
			call_out("guai",5);
		}
	}
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
                "zhenshens","huhuan","recall","fly","team with",
                "move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}