#include <ansi.h>
inherit ROOM;

string job_type(){ return "妖魔大会";}
string *ygs = ({
	"baihuagu","dragon","fangcun","hell","hyd",
	"jjf","moon","pansi","putuo","shushan","wudidong",
	"wzg","xueshan",
});	
void switch_on_off();
int check_palyer_level(object who);    
void create()
{
	set("short","妖魔大会");
        set("no_chuqiao",1);
        set("no_huicheng",1);
        set("no_chuqiao",1);
        set("channel_id","禹王爷(Yu wangye)");
        set("alternative_die",1);
        set("任务",1);
        set("hell",1);
        set("yaomo",2+random(3));
        if(random(4)) 
		switch_on_off();
        setup();
}

void init()
{
        add_action("do_cmds","",1);
        add_action("do_go","go");
        add_action("do_kill","kill");
}

int do_kill(string arg)
{ 
	object who,me = this_player();
     	if( !arg ) 
     		return 0;
     	who = present(arg);
     	if( !who || !userp(who) )  
     		return 0;
     	who->kill_ob(me);
     	me->kill_ob(who);
     	return 1;
}

int valid_leave(object who,string dir)
{
	int lvl;
	object ye,mo;
	if( !who->query_temp("maze/ymdh") )
        	return notify_fail("你是怎么混进来的？！\n");
        if( !objectp(ye = who->query_temp("maze/ymdh_ye")) )
        	return notify_fail("禹王爷不见了？！\n");
        if( query("yaomo")>0 )
        {
        	lvl = ye->check_palyer_level(who);
        	if( lvl>0 )
        	{
        		mo = new(sprintf("/d/maze/ymdh/npc/yg-%s",ygs[random(sizeof(ygs))]));
        		if( mo->copy_status(lvl-1) )
        		{
        			if( mo->move(this_object()) )
        			{
        				if( random(4)==1 )
        					message_vision("\n一阵狂风刮来，$N从浓雾中杀将出来！\n\n",mo);
        				else	message_vision("\n$N走了过来。\n\n",mo);
        				mo->kill_ob(who);
        				add("yaomo",-1);
        				return 2;
        			}
        			else	destruct(mo);
        		}
        		else	destruct(mo);
		}        		
        }	
        return ::valid_leave(who,dir);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "recall","fly","team with","maphere","map","team dismiss",
                "follow","quit",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}

int is_ymdh(){ return 1;}

int do_go(string arg)
{
        int no_look=query("no_look");
        if(no_look) 
        {
                tell_object(this_player(),HIR"你在浓雾里踉跄着一头撞了个空。\n"NOR);
                if( random(2) )
                	this_player()->receive_damage("kee",500);
                else	this_player()->receive_damage("sen",500);
        } 
        else
        {
        	if( random(2) )
            		this_player()->receive_damage("kee",200);
            	else	this_player()->receive_damage("sen",200);	
        }
        return 0;
}

int clean_up () { return 0; }

void switch_off ()
{
        set ("long", @LONG

……　禹王林里浓雾遮天，你熏熏晕晕什么也看不清　……

LONG);

        set("outdoors", 0);
        tell_room (this_object(),"一阵浓雾袭来，你什么都看不清了。\n");
}

void switch_on ()
{
        set ("long", @LONG

……　禹王林里飘着淡淡的一层雾气，树木林立，枝叶茂盛　……

LONG);

        set("outdoors", "milin");
        tell_room (this_object(),"风吹来，雾气渐渐地淡了。\n");
}

void switch_on_off()
{
	int no_look = 1-query("no_look");
  
        if( no_look )
        {
		if( random(3) )
			return;
                switch_off();
        } 
        else    switch_on();
        set("no_look",no_look);
}

int check_palyer_level(object who)
{
	if( !who || who->query_level()>=150 
	 || who->query_level()<30 )
		return 0;			
	if( who->query_level()<40 )
		return 1000;
	else if( who->query_level()<50 )
		return 3000;
	else if( who->query_level()<60 )
		return 5000;
	else if( who->query_level()<70 )
		return 8000;
	else if( who->query_level()<80 )
		return 10000;
	else if( who->query_level()<90 )
		return 30000;
	else if( who->query_level()<100 )
		return 50000;
	else if( who->query_level()<110 )
		return 80000;
	else if( who->query_level()<120 )
		return 100000;
	else if( who->query_level()<130 )
		return 200000;
	else if( who->query_level()<140 )
		return 300000;
	else	return 500000;
}

int alternative_die(object who)
{
        string name = who->query("name")+"("+who->query("id")+")";
        string str;
        object ye,killer,*obj;
        mapping players;
        string *nameids;
        int kill_bonus;

        if( !who )
                return 0;
        if( !userp(who) )
        {
        	if( !who->is_ymdh() )
        	{
        		message_vision ("\n$N惨叫一声，化作一道青烟散去。\n\n",who);
        		destruct(who);
        	}	
                else	who->dies();
		return 0;
        }
        if( !who->query_temp("maze/ymdh") )
        {
        	tell_object(who,"no temp data,真死\n");
		return 1;
	}
	kill_bonus = check_palyer_level(who);
	if( kill_bonus<=0 )
	{
		tell_object(who,"no lvl,真死\n");
		return 1;
	}
	ye = who->query_temp("maze/ymdh_ye");
	if( !ye )
	{
		tell_object(who,"no ye,真死\n");
		return 1;
	}	
        players = ye->query_players();
        if( !players || !mapp(players) )
        {
        	tell_object(who,"no Player,真死\n");
        	return 1;
        }	
        nameids = keys(players);
        if( !nameids && !arrayp(nameids) )
        {
        	tell_object(who,"no data size<=0,真死\n");
        	return 1;
        }
        obj=values(players);
        if( !obj && !arrayp(obj) )
        {
        	tell_object(who,"no data size<=0,真死\n");
        	return 1;
        }
        if( member_array(who,obj)==-1 )
        {
        	tell_object(who,"not Player,真死\n");
        	return 1;
        }
        killer = who->query_temp("last_damage_from");
        if( killer ) 
        {
		str = "被"+killer->query("name")+"杀死了";
		
		if( ( userp(killer) || killer->is_rzr() )
                  && member_array(killer, obj)>-1 ) 
		{
                        int multiplier=who->query_temp("ymdh/yaomokilled");
                        int max_mul=killer->query_temp("ymdh/yaomokilled")*3+1;
                        who->delete_temp("ymdh/yaomokilled");
                        if(multiplier>max_mul) 
                        	multiplier=max_mul;
                        if(multiplier<0) 
                        	multiplier=0;
                        if(multiplier>50) 
                        	multiplier=50;
                        kill_bonus*=multiplier;
                        str+="，"+killer->query("name")+"得到"+chinese_number(kill_bonus)+"点武学！\n";
                        QUEST_D->job_reward_player(killer,"combat_exp",kill_bonus,job_type());
                } 
                else    str+="。\n";
        } 
        else 
        {
                if( !stringp(str = who->query_temp("death_msg")) )
                        str = "被杀死了。\n";
        }
        str = "妖魔大会："+name+str;
        ye->announce(str);
        who->powerup(0,1);
        who->remove_all_killer();
        all_inventory()->remove_killer(who);
        message("vision","\n只见"+who->name()+"面如死灰被几位禹王卒七手八脚地从林中抬了出来，从众人前通过。\n",this_object(),who);
        who->move("/d/kaifeng/yuwang6");
        who->delete_temp("maze");
        who->delete_temp("ymdh");
        message_vision ("$N面如死灰被几位禹王卒七手八脚地抬了过来。\n",who);
        ye->remove_player(who->name(1)+"("+who->query("id")+")");
        who->start_busy(2);
}