// lifeheal.c
#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object who)
{
	if( !who )
		return;
	who->delete_temp("bhg_spring");
	who->set_temp("bhg_spring_end",time());
	message_vision(HIC"\n$N"HIC"背后光华一闪，诸多异象顿时消失不见。\n"NOR,who);
}	

void spring(object me)
{
	string msg;
	object *inv;
	int i,f=0;
	
	if( !me || !living(me) || !me->query_temp("bhg_spring") 
	|| !environment(me) || environment(me)->query("no_fight")
	|| environment(me)->query("no_magic") )
		return;
	inv = all_inventory(environment(me));
	msg = "一阵清香传来，";
	for(i=0;i<sizeof(inv);i++)
	{
		if( me->query("force")<10 )
			break;
		if( !inv[i] || !living(inv[i])
		 || inv[i]->is_fighting(me) 
		 || !me->visible(inv[i]) )
		 	continue;
		if( inv[i]->receive_curing("kee", 10+ (int)me->query_skill("force")/10 ) )
		{
			msg+= inv[i]->name()+" ";
			f++;
			me->add("force",-10);
		}
	}
	if( f>0 )
	{
		msg+= "的脸色渐渐变得好看起来。\n";
		message("vision",msg,environment(me));
	}
	if( me->query_temp("bhg_spring") )
		call_out("spring",2+random(3),me);		 			
}

int exert(object me, object target)
{
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query_skill("brightjade-force",1)<100 )
		return notify_fail("你的明玉心法还不到家，无法使用「群疗术」！\n");
	if( (int)me->query("force")<600 )
		return notify_fail("你的真气不够。\n");
	if( (int)me->query("eff_kee") < (int)me->query_maxkee()/20 )
                return notify_fail( "你已经受伤过重，经受不起真气震荡！\n");
	if( me->query_temp("bhg_spring") )
		return notify_fail("你正在施展「群疗术」。\n");
	if( time()<me->query_temp("bhg_spring_end")+6 )
		return notify_fail("你不能频繁使用。\n");
		
	me->add("force", -100);
	message_vision(HIW"\n$N"HIW"就地盘坐，催动明玉心法，背后一株香气郁人的白花一闪，顿时四周清香宜人。\n"NOR,me);
	me->set_temp("bhg_spring",1);
	call_out("spring",0,me);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), me->query_skill("force")/30);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        内功名称：群疗诀
        内功所属：明玉心法
        内功效果：一定时期内治疗在场所有非敌方人员的气血
                  每治疗成功一名人员，消耗自身内力10点
                  治疗完毕后冷却 6 秒
        内功条件：
        	  人物等级 10 级
                  内力600点，最少消耗100点
                  明玉心法100级
STR;
        me->start_more(str);
        return 1;
}

void remove()
{
	int i;
	object who,*usr = users();
	if( i=sizeof(usr)>0 )
	{
		while(i--)
		{
			if( !usr[i] || !environment(usr[i])
			 || !objectp(usr[i]) )
				continue;
			if( usr[i]->query_temp("bhg_spring") )
			{
				who = usr[i];
				who->delete_temp("bhg_spring");
				who->set_temp("bhg_spring_end",time());
				message_vision(HIC"\n$N"HIC"背后光华一闪，诸多异象顿时消失不见。\n"NOR,who);
			}
		}
	}
} 
