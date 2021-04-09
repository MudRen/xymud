// ningxie.c
//write by yeahsi
//yeahsi@21cn.com
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me);
void ningxie_result(object me,object target,object weapon,int damage);

int perform(object me, object target)
{
	object weapon;
        int t;
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name") != "大雪山" )
        	return notify_fail("只有大雪山弟子才配使用「冰谷凝血」！\n"); 		
	if( me->query_skill("ningxie-force",1)<80 )
		return notify_fail("你的冰谷凝血功修为不够。\n");
	if( me->query_skill("blade",1)<80 )
		return notify_fail("你的基本刀法未够纯熟。\n");	
	if( me->query_skill("bingpo-blade",1)<80 )
		return notify_fail("你的冰魄寒刀未够纯熟。\n");
	if( me->query_temp("ningxie") || me->query_temp("pfm_action") ) 
		return notify_fail("你已经催动了「冰谷凝血」。\n");
	if( me->query("force")<500 )
		return notify_fail("你的内力不足。\n");
	if( time()<me->query_temp("blade_ningxie")+8 )
		return notify_fail("你刚刚催动过寒气。\n");
			
	if( !target ) target = me;
	if( target!=me )
		return notify_fail("你只能对自己使用「冰谷凝血」。\n");
	
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="blade" && weapon->query("use_apply_skill")!="blade" ) )
		return notify_fail("这是冰魄寒刀的绝招。\n");	 
	
	t = me->query_skill("bingpo-blade",1)/4+15;
	
        me->add("force", -200);
        message_combatd(HIW"$N"HIW"把凝血神功在体内运转，然后徐徐注入手中的兵器中，"+weapon->name()+HIW"所到处带起了一阵寒气，方圆几丈内的空气好象都凝聚起来！\n" NOR, me);
        me->set_temp("ningxie", t);
        me->set_temp("pfm_action", (: call_other,"/daemon/class/xueshan/bingpo-blade/ningxie.c", "ningxie_result" :));
	if( me->if_fighting() )
		me->start_busy(2);	
        return 1;
}

void remove_effect(object me)
{
        if( me )
        { 
        	me->delete_temp("ningxie");
        	me->delete_temp("pfm_action");
        	tell_object(me, HIW"你将凝血神功收回丹田。\n"NOR);
        	message_vision(HIW"周围寒气慢慢散开了。\n"NOR,me);
        	me->set_temp("blade_ningxie",time());
        }	
}

void ningxie_result(object me,object target,object weapon,int damage)
{       
	int ap,dp,mod_val;	 
        if( !me || !living(me) ) 
                return;
	if( !weapon || weapon!=me->query_temp("weapon") )
		weapon = me->query_temp("weapon");
	if( !weapon 
    	 || ( weapon->query("skill_type") != "blade" 
    	   && weapon->query("use_apply_skill") != "blade" ) )
	{
		remove_effect(me);
		return;
	}               
	if( me->query_temp("ningxie")<=0 || me->query("force")<10 || !weapon )
	{
		remove_effect(me);
		return;
	}                
	if( !target )  target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) 
 	 || !living(me) )
		return; 
	if( time()<me->query_temp("last_pfm_action")+2 )
		return;
	me->set_temp("last_pfm_action",time());		
	if( target->query_temp("ningxue_at") )
	{
		target->add_temp("ningxue_at",-1);
		return;
	}
	
	me->add_temp("ningxie",-1-random(2));
        message_combatd(HIW"\n随着$N"HIW"手中"+weapon->name()+HIW"的舞动，周围的空气越来越冷了。\n"NOR,me);
            
        ap = COMBAT_D->skill_power(me, "force", SKILL_USAGE_ATTACK);
        if( ap < 1) ap = 1;
        dp = COMBAT_D->skill_power(target, "force", SKILL_USAGE_DEFENSE);
        if( dp < 1 ) dp = 1;
        if( me->query("force_factor") && (me->query("force") > me->query("force_factor")) )   
                mod_val = (100+me->query("force_factor")/10);
        else    mod_val = 100;
        if( ap > 1000000 )     
                mod_val = ap / 100 * (100 + mod_val);
        else    mod_val = (100 + mod_val) * ap / 100;
        if( mod_val < 1 ) mod_val = 1;
        if( random(mod_val + dp) < dp )
                message_combatd(HIC"$N"HIC"运气一转，全不把寒冷放在心上！\n"NOR,target); 
        else
        {      
                me->add("force",-5);
                target->add_temp("ningxue_at",random(3));
		damage = me->query_skill("force");
                damage-= target->query_temp("apply/armor_vs_force");
                if( damage<30 )
                	damage = 30;
                me->add_temp("ningxie",-damage/30);
                switch(random(5))
                {
                        case 0: 
                                message_combatd(WHT"$N"WHT"打了一个寒颤。\n"NOR,target);
                                target->receive_damage("kee",damage,me,TYPE_PERFORM);
                                COMBAT_D->report_status(target);
                                break;
                        
                        case 1: 
                        	message_combatd(WHT"$N"WHT"冷的浑身颤抖！\n"NOR,target);
                                target->receive_wound("kee",damage/2+1,me,TYPE_PERFORM);
                                COMBAT_D->report_status(target,1);
                                break;
                                
                        case 2: 
                                message_combatd(WHT"$N"WHT"冷得脸色惨白！\n"NOR,target);
                                target->receive_damage("sen",damage,me,TYPE_PERFORM);
                                COMBAT_D->report_sen_status(target);
                                break;
                        default:  
                                message_combatd(WHT"$N"WHT"冷得像一条冰棍了！\n"NOR,target);
                                target->receive_wound("sen",damage/2+1,me,TYPE_PERFORM);
                                COMBAT_D->report_sen_status(target,1);
                                break;
                }
        }
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：冰谷凝血 
              外功所属：冰魄寒刀  
              外功效果：以冰谷凝血功增加战斗环境的寒气，进而伤害敌人
              	        效果消失后冷却时间  8 秒 
              	        不支持非刀类型的武器
              外功条件：
              		雪山弟子
              		人物等级8级
              		冰谷凝血功80级以上
                        冰魄寒刀80级以上
LONG; 
me->start_more(str); 
return 1; 
} 

void remove()
{
	int i;
	object me,*usr = users();
	if( i=sizeof(usr)>0 )
	{
		while(i--)
		{
			if( !usr[i] || !environment(usr[i])
			 || !objectp(usr[i]) )
				continue;
			if( usr[i]->query_temp("ningxie") )
			{
				me = usr[i];
        			me->delete_temp("ningxie");
        			me->delete_temp("pfm_action");
        			tell_object(me, HIW"你将凝血神功收回丹田。\n"NOR);
        			message_vision(HIW"周围寒气慢慢散开了。\n"NOR,me);
        			me->set_temp("blade_ningxie",time());
			}
		}
	}
}
