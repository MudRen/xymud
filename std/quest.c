inherit F_CLEAN_UP;

#include <ansi.h>
#include <dbase.h>
#include <origin.h>

void create()
{
    seteuid(getuid());
}

int quest_give (object me, object who, object ob)
{
	if(QUEST_D->quest_reward(me,who,ob))
        	return 1;
	//if("/d/npc/bigtask/bigtask"->quest_reward(me,who,ob))
	//return 1;
//40突破
	if( ((me->query_level()==39&&me->query("combat_exp")>=16100000)||wizardp(me)) 
	 && me->query("family/family_name")
	 && !interactive(who)
	 && living(who) && !who->is_busy()
	 && !who->is_fighitng() && !me->is_fighting()
	 && interactive(me)
	 && me->query("mark/40tupo")
	 && who->query("family/family_name")==me->query("family/family_name") )
	 	return ("/quest/tupo/40.c")->give_zhuji(me,who,ob);
	 		
    	if( me->query("quest/pending/give/done") )
    		return 0;
    	if( userp(who)) 
    	{
		if( me->query("quest/pending/give/ture_id") != who->query("id") 
	     	|| me->query("quest/pending/give/ture_name")!= COLOR_D->clean_color(who->query("name")) )
            		return 0;
    	} 
    	else 
    	{
        	if( me->query("quest/pending/give/ture_name") != COLOR_D->clean_color(who->query("name")) 
         	 || me->query("quest/pending/give/ture_id")   != who->query("id")
         	 || me->query("quest/pending/give/file") != base_name(who) )
            		return 0;
    	}
	if( me->query("quest/pending/give/object_turename") != COLOR_D->clean_color(ob->query("name"))
     	 || me->query("quest/pending/give/object_tureid") != ob->query("id")
     	 || me->query("quest/pending/give/obj_file")!= base_name(ob) )
        	return 0;
    	me->set("quest/pending/give/done",1);
    	who->set("channel_id","殷温娇(Yin wenjiao)");
    	CHANNEL_D->do_channel(who,"job",COLOR_D->clean_color(me->name())+"救人之急，为"+COLOR_D->clean_color(who->name())+"送去"+COLOR_D->clean_color(ob->name())+"，真是品行可嘉也。");
    	return 1;
}

string quest_ask (object me, object who, string topic)
{
	//30套装
	if( me->query_level()>=30
	 && me->query("family/family_name")
	 && !interactive(who)
	 && living(who) && !who->is_busy()
	 && !who->is_fighitng()
	 && !me->is_fighting()
	 && interactive(me)
	 && topic=="套装"
	 && who->query("family/family_name")==me->query("family/family_name") )
		return ("/quest/family/family_mod.c")->ask_mod(me,who);
	//套装升级
	if( me->query_level()>=30
	 && me->query("family/family_name")
	 && !interactive(who)
	 && living(who) && !who->is_busy()
	 && !who->is_fighitng()
	 && !me->is_fighting()
	 && interactive(me)
	 && topic=="套装升级"
	 && who->query("family/family_name")==me->query("family/family_name") )	
	 	return ("/quest/family/family_mod.c")->ask_mod_level(me,who);
	//40突破
	if( ((me->query_level()==39&&me->query("combat_exp")>=16100000)||wizardp(me)) 
	 && me->query("family/family_name")
	 && !interactive(who)
	 && living(who) && !who->is_busy()
	 && !who->is_fighitng() && !me->is_fighting()
	 && interactive(me)
	 && topic=="筑基"
	 && who->query("family/family_name")==me->query("family/family_name") )
	 	return ("/quest/tupo/40.c")->ask_zhuji(me,who);
	
	//门派法宝
	if( me->query_level()>=40
	 && me->query("family/family_name")
	 //&& !interactive(who)
	 && living(who) && !who->is_busy()
	 && !who->is_fighitng()
	 && !me->is_fighting()
	 && interactive(me)
	 && topic=="法宝"
	 && who->query("family/family_name")==me->query("family/family_name") )
		return ("/quest/family/family_mod.c")->ask_fabao(me,who);
	
			
	if( !me->query("quest/pending/ask") )
		return 0;
	if( me->query("quest/pending/ask/topic") != topic)
        	return 0;
	if( me->query("quest/pending/ask/done") )
		return 0;		
	if( me->query("quest/pending/ask/ture_id") != who->query("id") 
     	 || me->query("quest/pending/ask/ture_name") != COLOR_D->clean_color(who->query("name")) )
		return 0;
    	me->set("quest/pending/ask/done",1);
    	return me->query("quest/pending/ask/acknowledge");
}

void quest_kill(object me)
{
    	object killer = me->query_temp("last_damage_from");
    	if( !killer || userp(me) )
        	return;
	if( killer->query("family/kill_moon_need")>0 
	 && killer->query("class")!="xian" 
	 && !killer->query("family/family_name") )
	{
		if( me->query("family/family_name")=="月宫" && !living(me)
		 && me->query("id")!=killer->query("family/last_kill_moon") )
		{
			killer->add("family/kill_moon",1);
			killer->set("family/last_kill_moon",me->query("id"));
			tell_object(killer,HBBLU"\n百草仙(Baicao xian)告诉你：干的不错，你已经刺杀了"+chinese_number(killer->query("family/kill_moon"))+"个月宫弟子了。\n"NOR);
			if( killer->query("family/kill_moon")>=killer->query("family/kill_moon_need") )
			{
				killer->delete("family/kill_moon");
				killer->delete("family/kill_moon_need");
				tell_object(killer,HBBLU"\n百草仙(Baicao xian)告诉你：恭喜恭喜！你成功完成了本门的门派试炼任务，即可带艺拜师。\n"NOR);
				killer->set_temp("pendding/bhg_class",1);
				tell_object(killer,HIR"注意：门派试炼任务记录下线会自动清除。\n"NOR);
				tell_object(killer,HBBLU"\n百草仙(Baicao xian)告诉你：赶紧去找合适的师傅拜了吧。\n"NOR);
			}
		}
	}
	if( killer->query_temp("family_kill/need")>0 )
	{
		if( me->query("class")!="yaomo" && me->query("class")!="tianmo" )
		{
			if( killer->query_temp("family_kill/killed")>=killer->query_temp("family_kill/need") )
			{
				tell_object(killer,HBBLU"\n鹦鹉将军(Yingwu jiangjun)告诉你：恭喜恭喜！你成功完成了本门的门派试炼任务，即可带艺拜师。\n"NOR);
				tell_object(killer,HBBLU"\n鹦鹉将军(Yingwu jiangjun)告诉你：赶紧回来，我自荐你入我大雪山。\n"NOR);
			}
			else	
			{
				killer->add_temp("family_kill/killed",1);
				tell_object(killer,HBBLU"\n鹦鹉将军(Yingwu jiangjun)告诉你：干得不错，再杀"+chinese_number(killer->query_temp("family_kill/need")-killer->query_temp("family_kill/killed"))+"即可完成投名状。\n"NOR);
			}
		}
		else
		{
			killer->add_temp("family_kill/killed",-1);
			tell_object(killer,HBBLU"\n鹦鹉将军(Yingwu jiangjun)告诉你：呸！你杀错人了！\n"NOR);
		}
	} 
	       	
	if( killer->query("quest/pending/kill/done") )
		return;
    	if( killer->query("quest/pending/kill/ture_name") != COLOR_D->clean_color(me->query("name")) 
     	|| killer->query("quest/pending/kill/ture_id") != me->query("id")
     	|| killer->query("quest/pending/kill/file")!=base_name(me) )
        	return;
    	killer->set("quest/pending/kill/done",1);
    	me->set("channel_id","胡敬德(Hu jingde)");
    	CHANNEL_D->do_channel(me,"job",COLOR_D->clean_color(killer->name())+"劳苦功高，替老胡将"+COLOR_D->clean_color(me->name())+"打入了六道轮回，真是品行可嘉也。");
}
