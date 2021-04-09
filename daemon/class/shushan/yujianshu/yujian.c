// 御剑术
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg,*msgs,succ_msg;
	
	if( me->query_level()<10 )
    		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="蜀山派"
    	&& me->query("chushi/chushi_shushan")!="yes")
		return notify_fail("你不能使用这项技能！\n");
	if((int)me->query_skill("yujianshu",1) < 100
	 || me->query_skill_mapped("sword") != "yujianshu" )
        	return notify_fail("你的『御剑术』还不纯熟！\n");
	if((int)me->query("force") < 500 )
        	return notify_fail("你体内的内力不足。\n");
	if((int)me->query_skill("zuixian-wangyue",1) < 100)
        	return notify_fail("你的『醉仙望月步』还不纯熟！\n");
    	if((int)me->query_skill("xianfeng-yunti",1) < 100)
        	return notify_fail("你的『仙风云体术』还不纯熟！\n");
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
        	return notify_fail("你要对谁施展这一招『御剑术』？\n");
    	if(target->query("family/family_name") == "蜀山派")
        	return notify_fail("同室弟子岂能操戈？！\n");

	me->add("force",-150);
	damage = me->query_skill("sword");
	damage/= 15;
	msg = HIY"\n$N"HIY"默念御剑剑诀，将手一指$n"HIY"：”咄“，$w"HIY"上霞光一闪，立即脱手飞出，径直射向$n"HIY"，沿途带出一道食指深浅的划痕！"NOR"\n";
	succ_msg = HIR"结果「嗤」的一声，$w"HIR"从$n"HIR"$l穿体而出，带出一路的血迹。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("perform_YJS",5);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage);
	me->delete_temp("perform_YJS");
	me->delete_temp("pfm_msg");
	if( damage<1 )
	{
		message_combatd(HIC"$n"HIC"不慌不忙，向旁一闪，正好避了开来。\n"NOR,me,target);
		me->start_busy(2);
		return 1;
	}
	
	if( me->query_level()<40
	 || me->query_skill("yujianshu",1)<400 
	 || !objectp(me->query_temp("weapon"))
	 || me->query("force")<100 )
	{
		me->start_busy(1);		       	
		return 1;
	}
	me->add("force",-100);
	msg = HIY"\n$N"HIY"掐诀不断，以仙风云体牵引飞行之剑，"HIY"$w"HIY"又风驰电掣般顺原路返回，直射$n"HIY"后心！\n";
	succ_msg = HIR"结果「嗤」的一声，$n"HIR"被刺得鲜血淋漓，脸色不由一白！\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("perform_YJS",3);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"后心",damage*3/2);
	me->delete_temp("pfm_msg");
	me->delete_temp("perform_YJS");
	me->start_busy(2);		       	
	return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：御剑术
        外功所属：御剑术
        外功效果：以指驭剑，对敌进行带固定伤害的攻击
        	  40级后追加一击 	
		  自身busy 1 秒，失败则自身busy 2 秒
		  不能对蜀山弟子使用
        外功条件：
                  蜀山派(出师)弟子
        	  人物等级10级	
                  内力500点，消耗100-250点
                  御剑术100级并激发
                  醉仙望月步100级
                  仙风云体术100级
LONG;
me->start_more(str);
return 1;
} 
