//stlb.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object me)
{
        if( me )
        {
                me->delete_temp("pfm_action");
                me->set_temp("stlb_end",time());
                me->delete_temp("stlb");
                tell_object(me, HIR"\n你的「三头六臂」施展完毕，身体恢复原状。\n\n"NOR);
        }
}

varargs void stlb(object me,object target,object weapon,int damage)
{
        if( !me ) 
                return;
	if( me->query_temp("stlb")<=0 )
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
	if( time()<me->query_temp("last_pfm_action")+1 )
		return;
	me->set_temp("last_pfm_action",time());		
	message_vision(HIC"\n$N"HIC"晃了晃三头六臂的法身，对着$n"HIC"便是一顿乱打！\n"NOR,me,target);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_QUICK);
	me->add_temp("stlb",-1-random(2));
}        

int cast(object me, object target)
{
        int t;

	if( me->query_level()<45 )
		return notify_fail("你的人物等级不够。\n");
				
	if( !target ) target = me;
	if( target!=me )
		return notify_fail("三头六臂只能对自己使用。\n");
	if( userp(me) && !me->is_knowing("puti_stlb") && !wizardp(me) )
		return notify_fail("你不能使用这项技能！\n"); 	
	if(me->query("family/family_name")!="方寸山三星洞" )
		return notify_fail("此乃方寸秘技！\n"); 
        if((int)me->query_skill("dao",1)<400)
		return notify_fail("你法术修为太低了。\n");
        if( time()<me->query_temp("stlb_end")+10 )
                return notify_fail("你不能频繁使用三头六臂。\n");                
	if( me->query_temp("pfm_action") )
		return notify_fail("你现在已经现了法身了。\n");	
        if((int)me->query("mana") < 500 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("你无法集中精力！\n");
	if( time()<me->query_temp("puti_stlb")+15 )
		return notify_fail("你刚刚念过咒。\n");
	
        message_combatd(HIC"$N"HIC"轻声一笑，潇洒已极，双目精光四射，口中念念有词。\n " NOR, me);
        message_vision(HIC"$N"HIC"将身一晃，立刻现出三头六臂的法身来。\n" NOR, me);
        me->set_temp("pfm_action","stlb");
	me->add("mana", -300);
        me->receive_damage("sen",150);
	t = 3+(int)me->query_skill("dao",1)/9;
	me->set_temp("stlb",t);
	if( me->is_fighting() )
		me->start_busy(1);        
        return 1;
}

int help(object me)
{
	string str;
	if( !me )      
		return 0;
str = @LONG
        法术名称：三头六臂
        法术所属：道家仙法
        法术效果：使自身处于三头六臂的状态下
        	  此状态下，攻击自动追加攻击
        	  支持状态下更换武器
                  状态结束后，冷却时间10秒
        法术条件：
          	  方寸弟子 
        	  人物等级45级
                  精神300点，消耗150点
                  法力500点，消耗300点 
                  道家仙法400级

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
			if( usr[i]->query_temp("stlb") )
			{
				me = usr[i];
                		me->delete_temp("pfm_action");
                		me->set_temp("stlb_end",time());
                		me->delete_temp("stlb");
                		tell_object(me, HIR"\n你的「三头六臂」施展完毕，身体恢复原状。\n\n"NOR);
			}
		}
	}
}
