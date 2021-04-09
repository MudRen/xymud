#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int damage;
    	string msg,succ_msg;
        
	if( me->query("family/family_name") != "陷空山无底洞")
        	return notify_fail("这是偷出来的功夫吧。\n");
        if( me->query_level()<5 )
        	return notify_fail("你的人物等级不够。\n");	
        if((int)me->query("force") < 50 )
        	return notify_fail("你的内力不足！\n");
	if((int)me->query_skill("yinfeng-zhua", 1) <50)
		return notify_fail("你的阴风爪等级还不够!!\n");
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return notify_fail("你要对谁施展这一招「魔光日无极」?\n");

	msg = HIY "只见$N" HIY "双目微闭，单手托天。掌心顿时腾起一个无比刺眼的气团，正是陷空山奥义！
                         "NOR REV RED"   魔光日无极   "NOR HIY"
霎时金光万道，尘沙四起，空气炽热，几欲沸腾。$N" HIY "随即收拢掌心，气团爆裂开来，向四周电射而出，光芒足以和日月争辉。\n" NOR;
	succ_msg = HIW "$n"HIW"只觉眼前金光万道，周围空气几欲沸腾，光芒便如利箭一般透体而入。\n" NOR;
        me->add("force",-30);
	me->set_temp("pfm_msg",1);
        me->add_temp("apply/attack",20);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,200);
	me->set_temp("pfm_msg",0);
        me->add_temp("apply/attack",-20);
	if( damage<1 )	       
	{         
        	message_combatd(HIY"只见光芒顿敛，$n没有被这招击中。\n"NOR,me,target);
        	me->start_busy(1);
        }
        else	me->start_busy(2);
        return 1;
}
        	
int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：魔光日无极
        外功所属：阴风爪
        外功效果：给予对方固定伤害200点的物理攻击
                  使用后自身busy 2 秒
                  若不中则自身busy 1 秒
        外功条件：
                  无底洞(出师)弟子
        	  人物等级5级	
                  内力50点，消耗30点
                  阴风爪50级
LONG;
me->start_more(str);
return 1;
} 
