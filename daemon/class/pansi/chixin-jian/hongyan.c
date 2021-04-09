// jie 2001-2-3
// chixin-jian 红颜白发
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra,lvl;
        int i;
        object weapon,ob;
        
        if( me->query_level()<10 )
        	return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="盘丝洞"
        && me->query("chushi/chushi_pansidong")!="yes")
		return notify_fail("你不能使用这项技能！\n");
	if( me->query_skill("chixin-jian",1)<100 )
		return notify_fail("你需要提高你的痴心情长剑法。\n");	
        if ( (string) me->query_skill_mapped("sword") != "chixin-jian")
		return notify_fail("红颜白发只能和痴心情长剑法配和！\n");
        if (me->query_skill_mapped("dodge")!="yueying-wubu")
		return notify_fail("只有用月影舞步才能运用红颜白发。\n");
        if((int)me->query("force") < 300 )
                return notify_fail("你的内力不够！\n");
        if((int)me->query("kee") < 100 )
                return notify_fail("你的气血不足，没法子施用外功！\n");
	weapon = me->query_temp("weapon");
	if( !weapon )
		return notify_fail("你的剑呢？\n");
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("红颜白发只能对战斗中的对手使用。\n");

        extra = me->query_skill("chixin-jian",1) / 5;
        extra += me->query_skill("yueying-wubu",1) / 5;

        msg = HIM "\n$N"HIM"脚踏「月影舞步」，曼歌轻舞，使出「痴心情长剑法」的精髓－－『"HIR"红颜"HIW"白发"HIM"』！\n"NOR;
        message_vision(msg,me,target);
        me->receive_damage("kee", 100);
        me->add("force",-150);
        
        msg = MAG"只见$N"MAG"长发飘飘，裙裾袂袂，清丽哀怨不可方物，使到动情尽意处，索性抛了手中的$w"MAG"，双指轮弹，无边气韵氤氲般卷向$n"MAG"$l！\n" NOR;
        msg+= HIW"$N"HIW"$w"HIW"光华一闪，犹如长虹浸空，仿佛消失．．．．\n" NOR;
        weapon = me->query_temp("weapon");
        weapon->set("use_apply_skill","unarmed");
	me->reset_action();
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);

        msg = HIY "$N"HIY"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);

        msg = HIC"$N"HIC"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,50);
	weapon = me->query_temp("weapon");
	weapon->delete("use_apply_skill");
	me->reset_action();
        
        if( me->query_skill("chixin-jian",1)>=200 )
        {
                msg = HIM "$N"HIM"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
                COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("sword")/3);
        }                       
        if( me->query_skill("chixin-jian",1)>=300 )
        {
                msg = HIG "$N"HIG"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
                COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("sword")/2);
        }       
        if( me->query_skill("chixin-jian",1)>=400 )
        {
                msg = HIR "$N"HIR"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
                COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,me->query_skill("sword"));
        }       
        me->start_busy(2);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：红颜白发
        外功所属：痴心情长剑
        外功效果：连续对敌进行物理打击
                  最多6次攻击，后4次固定伤害递增
                  自身busy 2 秒
        外功条件：
                  盘丝洞(出师)弟子
        	  人物等级10级
                  内力300点，消耗150点
                  气血100点，消耗100点
                  痴心情长剑100级并激发
                  激发月影舞步
STR;
        me->start_more(str);
        return 1;
}