// powerup.c
#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;
	
	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="阎罗地府" ) 
        	return notify_fail("你不能使用这项技能！\n");
	skill = me->query_skill("tonsillit",1);
	if( skill>850 ) 
        	skill=850;
	if( !target ) target = me;        	
	if( target != me ) 
        	return notify_fail("你只能用反五行摄气诀提升自己的战斗力。\n");
	if( (int)me->query("force") < 800 )     
        	return notify_fail("你的内力不够。\n");
	if( (int)me->query_temp("powerup") ) 
        	return notify_fail("你已经在运功中了。\n");
	if( (int)me->query("kee") < 200 )     
        	return notify_fail("你的气血不够。\n");
    	if( me->query("bellicosity")>100000 )
        	return notify_fail("你戾气过盛，小心魔心反噬。\n");

	message_vision(HIR"$N"HIR"微一凝神，运起正五行摄气诀，头上冒出一股青气，脸部现出一个鬼形。。。\n" NOR, me);
	me->add("force", -100);
	me->receive_damage("kee", 100);
	me->set_temp("powerup", 1);
	me->set_temp("hell_powerup",skill/2);
	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/combat_damage", skill/2);
	me->add_temp("apply/spells_damage", skill/2);
	me->add("bellicosity",skill);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill);
	if( me->is_fighting() ) 
		me->start_busy(3);
	return 1;
}

void remove_effect(object me, int amount)
{
	if(!me) return;
	me->add_temp("apply/attack", - amount);
	me->add_temp("apply/combat_damage",- amount);
	me->add_temp("apply/spells_damage",- amount);
	me->delete_temp("powerup");
	me->delete_temp("hell_powerup");
	tell_object(me, "你的正五行摄气诀运行一周天完毕，将内力收回丹田。\n");
}

int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        内功名称：正五行摄气诀
        内功所属：摄 气 诀
        内功效果：运用正五行摄气诀加强自身的命中以及伤害，并会增加自身的杀气
                  状态不可叠加
        内功条件：
        	  地府弟子
        	  人物等级20级
        	  杀气小于100000点	
                  内力800点，消耗100点
                  气血200点，消耗100点
LONG;
me->start_more(str);
return 1;
}

void remove()
{
	int amount,i;
	object me,*usr = users();
	if( i=sizeof(usr)>0 )
	{
		while(i--)
		{
			if( !usr[i] || !environment(usr[i])
			 || !objectp(usr[i]) )
				continue;
			if( usr[i]->query_temp("hell_powerup") )
			{
				me = usr[i];
				amount = me->query_temp("hell_powerup");
            			message_vision(HIR"\n$N"HIR"剑招渐缓，已将一套「歌舞阎罗」使完！\n" NOR, me);
				me->add_temp("apply/attack", - amount);
				me->add_temp("apply/combat_damage",- amount);
				me->add_temp("apply/spells_damage",- amount);
				me->delete_temp("powerup");
				me->delete_temp("hell_powerup");
				tell_object(me, "你的正五行摄气诀运行一周天完毕，将内力收回丹田。\n");
			}
		}
	}
}        
