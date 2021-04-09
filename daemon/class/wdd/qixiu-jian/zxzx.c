#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me)
{
	if(!me ) 
		return;
    	me->delete_temp("zxzx");
    	me->delete_temp("zxzx_time");
	me->delete_temp("pfm_action");
    	me->set_temp("zxzx_end",time());
    	tell_object(me, HIR"你将混天气功收回丹田。\n"NOR);
}

void zxzx(object me,object victim,object weapon,int damage)
{   
	string msg;
    	if( !me || !living(me) )
    		return;
    	me->add_temp("zxzx_time",-1);	
    	if( me->query_temp("zxzx_time")<1 || me->query("force")<50 )
    	{
    		remove_effect(me);
    		return;
    	}
    	if( !victim )  victim = offensive_target(me);
	if( !victim
 	 || !victim->is_character()
 	 || victim->is_corpse()
 	 || victim==me 
 	 || !me->is_fighting(victim) )
		return;
	if( random(me->query_cor())<victim->query("cor") )	
		return;
       	me->add("force",-20);
       	msg = "\n$N一击中敌，双目精光四谢，发狂般向$n又攻出一招！\n"NOR;
       	me->set_temp("pfm_color",HIR);
       	damage = COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),TYPE_QUICK,msg);
       	me->set_temp("pfm_color",0);
       	if( damage > 100 )
       	{
               	msg = "$N看到$n伤口上滴着的血，状近疯狂，居然在不可能的情况下又再攻出一招！\n";
               	me->set_temp("pfm_color",HIR);
               	COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),TYPE_QUICK,msg);
               	me->set_temp("pfm_color",0);
               	me->add_temp("zxzx_time",-2);
       	}
       	if( damage<1 )
       		me->add_temp("zxzx_time",-3);
}

int perform(object me)
{
	int skill,sword_skill,qixiu_skill;
	
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");    
    	skill = me->query_skill("huntian-qigong",1);
    	sword_skill= me->query_skill("sword",1);
    	qixiu_skill= me->query_skill("qixiu-jian",1);
        if( !wizardp(me) && skill < 300 )  
        	return notify_fail("你的混天气功修为不够。\n");
    	if( sword_skill < 300 )  
    		return notify_fail("你的基本剑法未够纯熟。\n");
    	if( qixiu_skill < 300 )  
    		return notify_fail("你的七修剑未够纯熟。\n");
	if(me->query_skill_mapped("force")!="huntian-qigong")
        	return notify_fail("「追腥逐血」必须配合混天气功才能使用。\n");
    	if(me->query("family/family_name") != "陷空山无底洞")
        	return notify_fail("「追腥逐血」是陷空山无底洞不传之密！\n");     
    	if( time()-(int)me->query_temp("zxzx_end") < 10 )
        	return notify_fail("你现在真气不纯！\n");       
        if( (int)me->query("force") < 300 )     
        	return notify_fail("你的内力不够。\n");
 	if( me->query_temp("zxzx") ) 
 		return notify_fail("你已经在「追腥逐血」中了。\n");
 		
    	me->add("force", -200);
    	message_vision(HIR "$N"HIR"把混天气功在体内运行一周，只觉浑身杀气腾腾，看谁都不顺眼。\n" NOR, me);
    	me->set_temp("zxzx", 1);
    	skill=random(skill/2)+skill/2;
    	me->set_temp("zxzx_time",skill);
	me->set_temp("pfm_action","wdd_zxzx");
	me->start_call_out( (: call_other, "/daemon/class/wdd/qixiu-jian/zxzx.c","remove_effect", me:),skill/5);
    	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：追腥逐血
        外功所属：七修剑
        外功效果：一定时期内使自身处于追腥逐血状态
        	  战斗中使用将对敌的物理攻击会追加攻击次数
        	  支持其他类型的武器	
                  状态结束后冷却10秒
        外功条件：
                  无底洞弟子
        	  人物等级30级	
                  内力500点，消耗200点，每次追加攻击消耗20点
                  混天气功300级并激发
                  七修剑300级

LONG;
me->start_more(str);
return 1;
}					 
