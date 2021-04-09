// char.c

#pragma save_binary

#include <action.h>
#include <ansi.h>
#include <command.h>
#include <condition.h>
#include <dbase.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <team.h>
#include <user.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"

inherit F_ACTION;
inherit F_ALIAS;
inherit F_APPRENTICE;
inherit F_ATTACK;
inherit F_ATTRIBUTE;
inherit F_COMMAND;
inherit F_CONDITION;
inherit F_DAMAGE;
inherit F_DBASE;
inherit F_EDIT;
inherit F_FINANCE;
inherit F_MESSAGE;
inherit F_MORE;
inherit F_MOVE;
inherit F_NAME;
inherit F_SKILL;
inherit F_TEAM;

nosave int next_beat;

void create()
{
	seteuid(0); // so LOGIN_D can export uid to us
}

int is_character() { return 1; }

void setup()
{
	seteuid(getuid(this_object()));

	set_heart_beat(1);
	next_beat = time() + 5 + random(10);
	
        enable_player();
        set_max_items(35);

	CHAR_D->setup_char( this_object() );
	powerup(0,1);
}

void heart_beat()
{
	int wimpy_ratio, cnd_flag, t;
    	int period,i;
	mapping my;
    	object ob, room, me,*inv;
	if (!objectp(room=environment()))       
		return;

	me = this_object();
	my = query_entire_dbase();

	if( my["eff_kee"] < 0 || my["eff_sen"] < 0  ) 
	{
		QUEST->quest_kill(this_object());
		remove_all_enemy();
		die();
		return;
	}
	if( my["kee"] < 0 || my["sen"] < 0  ) 
	{
		QUEST->quest_kill(this_object());
		remove_all_enemy();
		if( !living(this_object()) ) die();
		else unconcious();
		return;
	}

	if( is_busy() )
	{
		continue_action();
		return;
	}

	if( is_no_move() ) 
	{
		continue_action();
		return;
	}
	
	if( is_blind() )
	{
		continue_action();
		return;
	}
	 
	else 
	{
		//神通 颠倒阴阳
		if( !environment()->query("no_huicheng") && is_fighting()
		 && !me->is_ghost() && me->query_skill("diandao-yinyang",2)>1
		 && intp(wimpy_ratio = (int)query("env/wimpy"))
		 && wimpy_ratio > 0 && me->query("mana")>50 
		 && ( my["kee"] * 100 / me->query_maxkee()<= wimpy_ratio 
		  || my["sen"] * 100 / me->query_maxsen()<= wimpy_ratio) )
		{
			t = me->query_skill("jiefeng",1);
			t = 60-t/30;
			if( t>3 )
				t = 3;
			if( time()>=me->query_temp("last_huicheng")+t )
			{
				i = me->query_skill("diandao-yinyang",1);
				i = i/100;
				if( i>90 ) i = 90;
				if( wimpy_ratio<i )
				{
					me->add("mana",-50);
					message_vision(YEL"只见$N"YEL"摇身一变，化作一只金翅大鹏径直朝大雪山方向而去！\n"NOR,me);
					me->set_temp("last_huicheng",time());
        				if( me->is_fighting() )
        					me->start_busy(5);
        				me->move(sprintf("/d/xueshan/wuchang-%s",({"w","nw","n","ne","e","se","s","sw","c",})[random(9)]));
        				me->clean_up_enemy();
        				return;
				}
			}	
		}		
		if( is_fighting()
		&& intp(wimpy_ratio = (int)query("env/wimpy"))
		&& wimpy_ratio > 0
		&& ( my["kee"] * 100 / me->query_maxkee()<= wimpy_ratio 
		  || my["sen"] * 100 / me->query_maxsen()<= wimpy_ratio) ) 
			GO_CMD->do_flee(this_object());
		attack();
	}

	if( !userp(this_object()) && living(this_object()) ) 
		this_object()->chat();
	if ((t = time()) < next_beat) 
		return;
        else next_beat = t + 5 + random(10);
        
        if (!room->query("no_time") || this_object()->query_condition("no_pk_time"))
		cnd_flag = update_condition();

	if( ((cnd_flag & CND_NO_HEAL_UP) || !heal_up())
	&&	!is_fighting() 
	&&	!interactive(this_object())) 
	{
		if( environment() ) 
		{
			ob = first_inventory(environment());
			while(ob && !interactive(ob))
				ob = next_inventory(ob);
		}
		if( !ob ) 
			set_heart_beat(0);
	}

        if(!this_object()) return;
		if( !interactive(this_object()) ) return;
        if(!objectp(this_object())) return;

	this_object()->update_age();
	if (living(me))
        {
                period = t - ((int) my["last_save"]);
                if (period < 0 || period > 15 * 60)
                {
                        string msg;
                        msg = HIR "【系统】您的档案已经自动存盘。\n" NOR;;
                        if (! me->save())
                        msg = HIR "【系统】由于数据异常，您的档案本次存盘失败。\n" NOR;
                        set("last_save", t);
                        tell_object(me, msg);
            	}
        }
	if(query_idle(this_object()) > IDLE_TIMEOUT)
		this_object()->user_dump(DUMP_IDLE);
}

// added by snowcat 6/27/1997
int command_function (string arg)
{
	command (arg);
	return 1;
}

int visible(object ob)
{
	int lvl;

	if(wizardp(this_object())) 
		return 1;
	if( ob->query("env/invisibility") )
		return 0;
	if( ob->is_yinshen() )
	{
		if( !this_object()->is_yinshen() )
			return 0;
		else	return 1;
	}
	if( ob->is_ghost() ) {
		if( is_ghost() ) return 1;
		if( query_temp("apply/astral_vision") ) return 1;
		return 0;
	}
	return 1;
}

varargs int eff_skill_level(int level, int usage)
{
   if( query("guild") == "fighter" )  {
	  switch( usage )  {
		 case SKILL_USAGE_ATTACK:
		 case SKILL_USAGE_DEFENSE:
			if( level > 300 )	level += 35 + (level-300)*2/5; 
			else if( level > 200 )	level += 15 + (level-200)/5;
			else if( level > 100 )	level += 5 + (level-100)/10;
			else 				level += level / 20;
			break;
		 case SKILL_USAGE_SPELL:
			level -= level / 10;
			break;
	  }
   }
   else if( query("guild") == "magician" )  {
	  switch( usage )  {
		 case SKILL_USAGE_ATTACK:
		 case SKILL_USAGE_DEFENSE:
			level -= level / 10;
			break;
		 case SKILL_USAGE_SPELL:
			if( level > 300 )	level += 35 + (level-300)*2/5; 
			else if( level > 200 )	level += 15 + (level-200)/5;
			else if( level > 100 )	level += 5 + (level-100)/10;
			else 				level += level / 20;
			break;
	  } 
   }

   return level;
}

int command( string str )
{
	reset_eval_cost();
    	return efun::command(str);
}

int query_max_daoxing()
{
	int lvl,max_dx;
	lvl = this_object()->query_level();
	if( lvl<40 )
		max_dx = lvl*4500;
	else if( lvl<50 )
		max_dx = lvl*5000;
	else if( lvl<60 )
		max_dx = lvl*6000;
	else if( lvl<70 )
		max_dx = lvl*7000;
	else if( lvl<80 )
		max_dx = lvl*8000;
	else if( lvl<90 )
		max_dx = lvl*9000;
	else if( lvl<100 )
		max_dx = lvl*10000;
	else if( lvl<110 )
		max_dx = lvl*20000;
	else if( lvl<120 )
		max_dx = lvl*30000;
	else if( lvl<130 )
		max_dx = lvl*40000;
	else if( lvl<140 )
		max_dx = lvl*50000;
	else if( lvl<150 )
		max_dx = lvl*60000;
	else if( lvl<160 )
		max_dx = lvl*100000;
	else if( lvl<170 )
		max_dx = lvl*150000;
	else if( lvl<180 )
		max_dx = lvl*160000;
	else if( lvl<190 )
		max_dx = lvl*200000;
	else	max_dx = lvl*500000;
	if( max_dx<80000 )
		max_dx = 80000;
	return max_dx;		
}

int query_max_life()
{
	return query_max_daoxing()/1000;
}

int accept_surrender(object who)
{
	if( who->query("env/no_accept_surrender") )
		return 0;
	return 1;
}		