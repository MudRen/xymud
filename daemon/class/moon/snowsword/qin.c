#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int valid_perform(object me)
{
	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");        	
	if( me->query("family/family_name") != "月宫")
        	return notify_fail("「倾城倾国」是月宫不传之密！\n");
	if( me->query_skill("moondance",1)<400 )
        	return notify_fail("你目前身形不够轻灵，还使不出「倾城倾国」。\n");
	if( me->query_per()<30 )
        	return notify_fail("你目前容貌不够，使不出「倾城倾国」。\n");
	if( me->query("force") < 800 )
        	return notify_fail("你的内力不够。\n");
	if( !wizardp(me) && userp(me) && me->query("gender")!="女性" )
        	return notify_fail("你是男儿家，如何使得出「倾城倾国」。\n");
	if( me->query_skill("snowsword",1)<400 )
        	return notify_fail("你目前功力还使不出「倾城倾国」。\n");
	return 1;
}
		
int perform(object me, object target)
{
	int def,t,damage=0,skill,i,succ,dodge,per;
	string msg,succ_msg;

	if( !valid_perform(me) )
		return 0;
		
	if( !target ) target = offensive_target(me);
	if( !target || !target->is_character()
	 || target->is_corpse() || target==me
	 || !me->is_fighting(target) )
        	return notify_fail("你只能对战斗中的对手使用「倾城倾国」。\n");

	skill=me->query_skill("snowsword",1);        	
	dodge = me->query_skill("moondance",1)/10;
	per = me->query_per()/5;
        if( time()<me->query_temp("moon_qin")+5 )
        	return notify_fail("绝招用多就不灵了。\n");
        	
        message_vision(HIC"$N"HIC"对着$n"HIC"嫣然一笑，顿时六宫粉黛皆无颜。\n"NOR,me,target);
	me->set_temp("moon_qin",time());
	me->add("force",-200);
	me->set_temp("WX_perform",10);
	me->add_temp("apply/attack",dodge);
	me->add_temp("apply/combat_succ",per);
	succ = COMBAT_D->attack_percent(me,target,TYPE_PERFORM);
	
	if( succ<=0 && COMBAT_D->check_level(me,target)!=1 )
	{
		message_vision(HIG"\n可是$n"HIG"急忙抽身躲开，$N"HIG"这招没有得逞。\n" NOR,me,target);
		me->add_temp("moon_qin",3);
		me->add("force",-50);
	}	
	else	
	{
		msg = HIC"$n"HIC"见状，不禁心神一荡。"NOR;
		if( !target->is_busy() )
        		target->start_busy(1+random(2));
		msg+= HIC"说时迟，那时快！$N"HIC"手中的$w"HIC"在空中划出一道华丽的弧线，顿时映得$n"HIC"的脸如纸样煞白。\n"NOR;
		succ_msg = RED"只见$n"RED"已被$w"NOR RED"切得体无完肤，血如箭般由全身喷射而出！\n"NOR;
		me->set_temp("pfm_msg",1);
		me->set_temp("WX_perform",11);
		me->set_temp("MOON_perform",1);
		damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,(int)me->query_skill("snowsword",1));
		if( damage<1 )
		{
			message_vision(HIG"可是$n"HIG"急忙抽身躲开了这一招。\n" NOR,me,target);
			me->add_temp("moon_qin",1);
		}
	}
		
	if( me && target && me->is_fighting(target) )
	{
		if( skill>=450 && me->query("force")>=300 )
		{
			damage = me->query_skill("sword");
			damage+= random(me->query("force_factor"));

			msg = HIC"\n却见$N"HIC"使完了这一招，再度回眸一笑，$n"HIC"顿时只觉这世上万物皆化为虚有，眼中止留得一个"+me->name()+HIC"。$N"HIC"罗裳轻舞，抚袖藏剑，妩媚一笑。$n"HIC"只觉堕入温柔乡中，心头什么事也不再想。\n寒光一闪！\n"NOR;
			succ_msg = RED"$n"RED"眼带迷离，捂住喷血的伤口，呆对对面的$P。\n"NOR;
			damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage);
			if( damage<1 )
			{
				if( COMBAT_D->check_level(me,target)==-1 )
					msg = HIG"$n"HIG"泥丸宫骤然冲出一道冲天之气，将这一招化险为夷。\n"NOR;
				else	msg = HIG"可惜$n"HIG"有异宝护身，这一招对$p没有造成多大的伤害。\n"NOR;
				message_combatd(msg,me,target);
			}	
		}		
		if( skill>=800 && me->query("force")>=500 )
		{
			msg = HIC"\n出招完毕之后$N"HIC"意犹未尽，娇躯前冲，$w"HIC+"剑尖一颤，抖出朵朵剑花,直刺$n"HIC"$l！\n"NOR;
			succ_msg = HIR"$n"HIR"眼前一花,$l已被划出道道伤口，血流不止。\n"NOR;
			me->add("force",-50);
			me->set_temp("pfm_msg",1);
			me->set_temp("WX_perform",11);
			damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,(int)me->query_skill("snowsword",1)*3/2);
			me->delete_temp("pfm_msg");
			if( damage<1 )
			{
				message_combatd(HIG"\n$n"HIG"身形一展,轻轻巧巧躲过了这招。\n"+NOR, me, target);
				me->add("force",-30);
			}
		}
		if( me->query_temp("powerup") )
		{
			message_combatd(HIW"\n$N"HIW"手腕一回，将"+(me->query_temp("weapon"))->name()+HIW"收将回来，脚下轻移，借着莲步轻舞，单手对着$n"HIW"就是一掌！\n"NOR,me,target);
        		me->set("actions",("/daemon/skill/baihua-zhang.c")->query_action(me,me->query_temp("weapon")));
        		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,0,0,(int)me->query_skill("snowsword",1)*2);
        	}
        }	
        me->delete_temp("WX_perform");	
        me->delete_temp("pfm_msg");
        me->add_temp("apply/attack",-dodge);
        me->delete_temp("MOON_perform");
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：倾城倾国
        外功所属：回风雪舞剑
        外功效果：对敌进行带固定伤害加成的攻击
        	  内力足够下风回雪舞剑达450级增加1次攻击，命中则内力消耗增加100点
        	  内力足够下风回雪舞剑达800级增加1次带固定伤害加成的攻击
        	  满足一定条件有1次追加攻击(隐藏)
                  使用后冷却5秒，第一击不中，冷却追加3秒
        外功条件：
        	  月宫弟子
        	  人物等级40级
        	  后天魅力达到30
                  内力800点，消耗200点，第一击不中，消耗增加50点
                  风回雪舞剑 400 级
                  冷月凝香舞 400 级
                  
STR;
        me->start_more(str);
        return 1;
}