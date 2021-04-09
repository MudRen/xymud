#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra,i,lmt;
        object weapon;

	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query_skill("fumo-zhang",1)<100 )
		return notify_fail("你的伏魔杖法还不够纯熟！\n");
	if( me->query_skill("staff",1)<100 )
		return notify_fail("你的基本杖法还不够纯熟！\n");	
        if( me->query("family/family_name") != "五庄观"
         && me->query("chushi/chushi_wzg")!="yes" )
                return notify_fail("「降龙伏虎」是五庄观不传之密！\n"); 
        if(me->query_skill("force",1) < 100)
                return notify_fail("你的内功底子不足，无法运杖如风，施展不出降龙伏虎。\n");
	if((string)me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("「降龙伏虎」必须以镇元神功为底子。\n");
        if(me->query("force") < 500 )
                return notify_fail("你的内力不足，难以随意挥动一把禅杖。\n");        	
        weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="staff"
	  && weapon->query("use_apply_skill")!="staff") )
		return notify_fail("「降龙伏虎」是伏魔杖法的绝技。\n");
			          
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("「降龙伏虎」只能对战斗中的对手使用。\n");

	extra = me->query_skill("fumo-zhang",1)/10+me->query_skill("staff",1)/10;

        msg = HIY"$N"HIY"身型闪动，地面随之起伏一降狂风，手中"+ weapon->name()+HIY"也有如狂风暴雨般地向$n"HIY"卷来！\n" NOR;
        message_vision(msg,me,target);
        me->add("force",-150);
        me->add_temp("apply/attack",extra);
        me->add_temp("apply/combat_damage",extra);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_PERFORM);
        me->add_temp("apply/attack",-extra);
        me->add_temp("apply/combat_damage",-extra);
        me->start_busy(2);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：降龙伏虎
        外功所属：伏魔杖法
        外功效果：短期内提高自身命中与物理攻击，连续攻击对方3次
                  使用后自身busy 2 秒
        外功条件：
                  五庄观(出师)弟子
        	  人物等级10级	
                  内力500点，消耗150点
                  伏魔杖法100级
                  基本杖法100级
                  镇元神功100级
                  内功激发镇元神功
                  杖法激发伏魔杖法
LONG;
me->start_more(str);
return 1;
}
