//jianmang.c
//write by yesi
#include <ansi.h>
inherit SSERVER;
inherit F_CLEAN_UP;
 
void remove_effect(object me);

int perform(object me, object target)
{
        int p;
        object weapon=me->query_temp("weapon");
	if( !weapon 
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") 
	 || me->query_skill_mapped("sword")!="sanqing-jian" )
		return notify_fail("你手里没有剑，如何能发出「剑芒」？\n");
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");	
        if( me->query_temp("jianmang") ) 
                return notify_fail("你正在运功当中。\n");
        if( time()-(int)me->query_temp("jianmang_end") < 5 )
                   return notify_fail("你现在真气不纯。\n");
	if(me->query_skill("zhenyuan-force",1) < 100) 
                return notify_fail("你的镇元神功修为不够，产生不了剑芒。\n");		 
	if(me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("「剑芒」必须配合镇元神功才能使用。\n");
        if( me->query("family/family_name") != "五庄观" )
        	return notify_fail("「剑芒」是五庄观的绝技。\n");
        if((int)me->query_skill("sanqing-jian", 1) < 100)
                return notify_fail("你的三清剑法级别还不够，怎能生成剑芒！\n");	     
	if( (int)me->query("force") < 500 )      
                return notify_fail("你的内力不够。\n");
                                                   
        p = (me->query_skill("sword")+me->query("force"))/10;
        me->add("force", -300);
	message_vision(HIY"$N"HIY"催动真气，同时念动真言，将镇元神功缓缓注入"+weapon->name()+HIY"，渐渐长出五寸剑芒，烁烁生辉。\n" NOR, me);
        me->set_temp("jianmang", 1);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me:),p);
        return 1;
}
 
void remove_effect(object me)
{       
	if( me )
        {
        	me->delete_temp("jianmang");
        	message_vision(HIC"$N"HIC"的剑芒渐渐褪去。\n" NOR, me);
        	me->set_temp("jianmang_end",time());
        }	
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：三清剑芒
        外功所属：三清剑法
        外功效果：在一定时间内使自身宝剑处于剑芒状态下
        	  剑芒状态下，三清剑法的攻击伤害加成	
                  伤害加成随着领悟会增加
                  状态结束后冷却5秒
        外功条件：
        	  五庄观弟子
        	  人物等级10级
        	  内力500点消耗300点
                  镇元神功100级并激发
                  三清剑法100级并激发
LONG;
me->start_more(str);
return 1;
}       

