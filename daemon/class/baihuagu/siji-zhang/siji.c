// Siji.c 四季飞花
// Cracked by 凌惊雪 4-1-2003
// 24节气，春夏秋冬，每季6式
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg;
	int num,i;
	
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query_temp("pfm_action") )
		return notify_fail("四季掌讲究的是心如止水。\n");		
	
	num = me->is_knowing("bhg_siji_spr")+me->is_knowing("bhg_siji_sum")+me->is_knowing("bhg_siji_aut")+me->is_knowing("bhg_siji_win");
	if( !num )
	{
		if( !userp(me) ) 
			num = me->query_level()/6;
		else if( wizardp(me) )
			num = 24;
	}	
	if( num<=0 )
		return notify_fail("你没有领悟四季掌的一招半式，无招可发。\n");
	if( (int)me->query("force") < 800 )
        	return notify_fail("你现在的内力不足！\n");
	if( me->query_skill("unarmed",1)<80 )
		return notify_fail("你的掌法还不到家，无法使用「四季飞花」！\n");
	if( me->query_skill("siji-zhang",1)<80 
	 || (string)me->query_skill_mapped("unarmed")!="siji-zhang" )
	 	return notify_fail("你的四季掌法还不到家，无法使用「四季飞花」！\n");
	if( me->query_skill("brightjade-force",1)<80 )
		return notify_fail("你的明玉心法还不到家，无法使用「四季飞花」！\n");
	if( time()-(int)me->query_temp("bhg_siji")<10 )
        	return notify_fail("绝招用多就不灵了！\n");
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招「四季飞花」？\n");
        	
	msg = HIY "$N"HIY"忽然身形一拧，越在半空，双臂急挥，双掌化十掌、百掌、千掌、万掌，犹如「四季飞花」，把$n"HIY"完全罩在掌风之中。\n"NOR;
	message_vision(msg, me, target);
	me->add("force",-200);
	me->set_temp("bhg_siji",time());
	
	if( me->is_knowing("bhg_siji_spr")>0 
	|| ( num>0 && (!userp(me) || wizardp(me)) ) )
	{
		msg = HIM"                       ------春------\n"NOR;
		message_combatd(msg,me,target);
		me->set_temp("pfm_color",MAG);
		me->set_temp("SJZ",1);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
		me->set_temp("SJZ",0);
	}
	if( me->is_knowing("bhg_siji_spr")>=6 
	|| ( num>=6 && (!userp(me) || wizardp(me)) ) )	
	{
		me->set_temp("SJZ",2+random(5));
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
		me->set_temp("SJZ",0);
	}
	me->set_temp("pfm_color",0);
	
	if( me->is_knowing("bhg_siji_sum")>0 
	|| ( num>6 && (!userp(me) || wizardp(me)) ) )
	{
		msg = HIG"                       ------夏------\n"NOR;
		message_combatd(msg,me,target);
		me->set_temp("pfm_color",NOR);
		me->set_temp("SJZ",7);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
		me->set_temp("SJZ",0);
		if( me->is_knowing("bhg_siji_sum")>=6 
		|| ( num>=12 && (!userp(me) || wizardp(me)) ) )
		{
			me->set_temp("SJZ",8+random(5));
			COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
			me->set_temp("SJZ",0);
		}
		me->set_temp("pfm_color",0);
	}
		
	if( me->is_knowing("bhg_siji_aut")>0 
	|| ( num>12 && (!userp(me) || wizardp(me)) ) )
	{
		msg = HIY"                       ------秋------\n"NOR;
		message_combatd(msg,me,target);
		me->set_temp("pfm_color",YEL);
		me->set_temp("SJZ",13);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
		me->set_temp("SJZ",0);
		if( me->is_knowing("bhg_siji_aut")>=6 
		|| ( num>=18 && (!userp(me) || wizardp(me)) ) )
		{
			me->set_temp("SJZ",14+random(5));
			COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
			me->set_temp("SJZ",0);
		}
		me->set_temp("pfm_color",0);
	}	

	if( me->is_knowing("bhg_siji_win")>0 
	|| ( num>18 && (!userp(me) || wizardp(me)) ) )
	{
		msg = HIW"                       ------冬------\n"NOR;
		message_combatd(msg,me,target);
		me->set_temp("pfm_color",WHT);
		me->set_temp("SJZ",19);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
		me->set_temp("SJZ",0);
		if( me->is_knowing("bhg_siji_win")>=6 
		|| ( num>=24 && (!userp(me) || wizardp(me)) ) )
		{
			me->set_temp("SJZ",20+random(5));
			COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
			me->set_temp("SJZ",0);
		}
		me->set_temp("pfm_color",0);
	}	
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：四季飞花
        外功所属：百花掌
        外功效果：以四季秘技攻击对方
                  共二十四式对应二十四节气
                  需要领悟
                  每一季初期能各出一击
                  每一季领悟完，则本季追加一击
                  最高 8 击
                  使用完冷却 10 秒
        外功条件：
                  人物等级8级
                  扑击格斗80级
                  百花掌80级并激发
                  明玉心法80级
                  内力800点,消耗200点
LONG;
me->start_more(str);
return 1;
}
