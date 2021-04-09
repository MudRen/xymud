#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

void remove_effect(object me,int p)
{
	if( me )
	{
        	me->add_temp("apply/combat_damage",-p);
        	me->delete_temp("powerup");
        	tell_object(me,HIR"你身上的妖气逐渐平复了下来。\n"NOR,me);
	}
}

int perform(object me, object target)
{       
        int t,p;
        object weapon;
	
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");
        if( !target )
        	target = me;
        if( me!=target )
        	return notify_fail("「天赐神力」只能对自己使用。\n");
        		
	if( me->query("family/family_name")!="火云洞"
	 && me->query("chushi/chushi_kusong")!="yes" )
		return notify_fail("「天赐神力」只有火云洞门人才可以用！\n");
	if((int)me->query_skill("force",1)<50)
		return notify_fail("你的内功太差。\n");
	if((int)me->query_skill("dali-bang",1)<50)
		return notify_fail("你大力棍法火候不够。\n");
	if(me->query("force")<100)
		return notify_fail("你内力不继，难以出招。\n");
	if( me->query("kee")<100 )
		return notify_fail("你状态不佳，难以出招。\n");	
	if( me->query_temp("powerup") )
		return notify_fail("你已经被祝福了，不能再施展「天赐神力」了。\n");
	weapon=me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="stick" && weapon->query("use_apply_skill")!="stick" )
	 || me->query_skill_mapped("stick") != "dali-bang" )
		return notify_fail("你不施展大力棒就没法「天赐神力」。\n");
			  	
		
        me->add("force",-50);
        message_vision(HIY"$N"HIY"咬破舌尖吐在"+weapon->name()+HIY"上，顿时浑身妖气滔天，背后隐现巨角牛头异象！\n"NOR,me);
        me->receive_damage("kee",50,me);

        t = me->query_skill("dali-bang",1);
        p = me->query_skill("dali-bang",1)/10;
        me->add_temp("apply/combat_damage",p);
        me->set_temp("powerup",1);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, p:), t);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：天赐神力
        外功所属：大力棒
        外功效果：一定时间内增强自身的物理攻击
                  不可与其他增益型状态叠加
        外功条件：
        	  火云洞(出师)弟子
        	  人物等级5级	
        	  内力100点，消耗50点
        	  气血100点，消耗50点
                  大力棒 50 级
                  基本内功 50 级
STR;
        me->start_more(str);
        return 1;
}
