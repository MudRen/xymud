//yanluo歌舞阎罗
//2001 lestat for zhuihun-sword
//2008 snowtu for Help Func. & checking buff
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void checking(object me, object target,object weapon);
varargs void remove_effect(object me,string str);

int perform(object me, object target)
{
	object weapon;
    	int skill;
    	mapping act,t_act;

	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");
		
    	if( !target ) target = offensive_target(me);

    	if( !target
     	 || !target->is_character()
     	 || !me->is_fighting(target)
     	 || target->is_corpse()
     	 || target->is_ghost()
     	 || target==me )
		return notify_fail("「歌舞阎罗」只能对战斗中的对手使用。\n");
	if( me->query("family/family_name") != "阎罗地府"
	 && me->query("chushi/chushi_hell")!="yes" ) 
    		return notify_fail("「歌舞阎罗」是地府不传之密！\n");
	if( me->query_temp("yunwu") )
    		return notify_fail("你已经使出「歌舞阎罗」了！\n");
	weapon = me->query_temp("weapon");
    	if( !objectp(weapon) 
        || ( weapon->query("skill_type") != "sword" 
       && weapon->query("apply/skill_type") != "sword" ) ) 
		return notify_fail("你手中无剑，如何能施展「歌舞阎罗」？\n");
	if( me->query_skill("dodge") < 200 )
		return notify_fail("你的轻功修为未到，难以施展「歌舞阎罗」的变幻之处！\n");
	if( me->query_skill("sword") < 200 )
    		return notify_fail("你在剑法上的造诣不足以使出「歌舞阎罗」！\n");
	if( me->query("force") < 500 )
    		return notify_fail("你的内力不够施展「歌舞阎罗」！\n");
	if( me->query_skill_mapped("parry")!="zhuihun-sword" )
    		return notify_fail("「歌舞阎罗」是追魂剑的绝技。\n");
	if( time()<me->query_temp("hell_yanluo_end")+8 )
    		return notify_fail("你不能频繁使用「歌舞阎罗」。\n");
	skill = me->query_skill("sword");
    	if( random(target->query_skill("parry")/2)>skill ) 
    	{
    		message_vision(HIR "\n$N"HIR"意欲使出"+HIR"「歌舞阎罗」"+HIR"，但是$n"HIR"严加戒备，全身门户，无不守备綦谨，难以奏效！\n" NOR, me, target);
    		me->start_busy(1);
    		return 1;
	}
	message_vision(HIR "\n但见寒光陡闪，$N"HIR"手中"+weapon->query("name")+HIR"越使越快，如梦如幻，正是追魂剑绝技"+HIR"「歌舞阎罗」"NOR+HIR"！\n" NOR, me, target);
	me->add("force", -200);
	me->set_temp("yunwu", 1);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM);
    	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/2);
	return 1;
}

void remove_effect(object me)
{
	if( me )
    	{
            	message_vision(HIR"\n$N"HIR"剑招渐缓，已将一套「歌舞阎罗」使完！\n" NOR, me);
		me->delete_temp("yunwu");
        	me->set_temp("hell_yanluo_end",time());
        	me->reset_action();
    	}
}

int help(object me)
{
    string str;
    if( !me )       return 0;
    str = @STR
    外功名称：歌舞阎罗
    外功所属：追魂剑
    外功效果：进入歌舞阎罗状态，并向对手连续攻击三次
              状态结束后冷却时间 8 秒
    外功条件：
    	      人物等级20级
    	      地府(出师)弟子
              基本轻功激发100级
              基本剑术激发100级
              基本招架激发追魂剑
              内力500点，消耗200点
STR;
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
			if( usr[i]->query_temp("yunwu") )
			{
				me = usr[i];
            			message_vision(HIR"\n$N"HIR"剑招渐缓，已将一套「歌舞阎罗」使完！\n" NOR, me);
				me->delete_temp("yunwu");
        			me->set_temp("hell_yanluo_end",time());
        			me->reset_action();
			}
		}
	}
}        
