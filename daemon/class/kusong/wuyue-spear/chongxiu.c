#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        int damage,p;
        string msg,succ_msg;
	object weapon;
	
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");
        if( me->query("family/family_name")!="火云洞") 
        	return notify_fail("「秀冲青天」只有火云洞门人才可以用！\n"); 
	if( (int)me->query_skill("wuyue-spear",1)<300 
	 || me->query_skill_mapped("spear")!="wuyue-spear" )
		return notify_fail("你的「五岳神枪」还不够纯熟！\n");
        if( me->query_skill("huomoforce",1)<300 )
                return notify_fail("你的火魔心法等级不够！\n");
        if( me->query("force") < 500 )
                return notify_fail("你的内力不够！\n");
	weapon = me->query_temp("weapon");
	if( !weapon 
	 || ( weapon->query("skill_type")!="spear" && weapon->query("use_apply_skill")!="spear" ) )
		return notify_fail("你手里都没枪。\n");	
	if( time()-(int)me->query_temp("kusong_chongxiu") <4 )
		return notify_fail("绝招用多就不灵了！\n");
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return notify_fail("「秀冲青天」只能在战斗中使用。\n");

        me->add("force",-100);
        me->add_temp("apply/attack",30);
	me->set_temp("kusong_chongxiu",time());
	msg = HIM "$N"HIM"火魔心法全面运转，强大的冲击波激荡四周，酡红的面容，蓦地一白，继而再转盛红，凄艳地恍若要燃烧起来！$w"HIR"带着炽热的火劲似毒蛇一吐，直刺$n"HIR"$l！\n"NOR;
	succ_msg = HIR"$n"HIR"惨叫一声，$l传出一阵焦臭气味，连退不止。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("CX_perform",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("spear")/3);
	me->delete_temp("CX_perform");
	me->set_temp("pfm_msg",0);
	if( damage<1 )
		message_combatd(HIY"$n"HIY"猛吐一口气，将扑面的火焰吹了个一干二净！\n"NOR,me,target);
		
	if( me->query("kee")<100 )
	{
		me->add_temp("apply/attack",-30);
		message_combatd(HIM"$N"HIM"忽的一个踉跄，停止了攻击。\n",me,target);
		return 1;
	}
	me->receive_damage("kee",100,me);
        msg = HIM"\n$N"HIM"连连催劲，无视于身体各处隐然作痛，将功力提至最顶峰，五岳枪法的沛然气魄，燃起熊熊烽火，炙乾了周围的水气。灼热的火劲，升华成巨大的爆炸力，冲天而起，直似万马奔腾般压向$n"HIM"！\n"NOR;
        succ_msg = HIR"$n"HIR"顿时被这冲天般的气势镇住，胸口好似大铁锤用力击中，喉间一甜，鲜血飞溅，整个人给轰的飞了出去。\n"NOR;
	me->set_temp("pfm_msg",1);
	me->set_temp("CX_perform",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"胸口",me->query_skill("spear")/2);
	me->delete_temp("CX_perform");
	me->set_temp("pfm_msg",0);
        if( damage<1 )
        	message_combatd(HIG"$n"HIG"面对狂风暴雨般的枪击，淡然以对，面对飘忽不定的枪尖,幻出无数身影,避开了这一击！\n"NOR,me,target);
	me->add_temp("apply/attack",-30);
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：秀冲青天
        外功所属：五岳神枪
        外功效果：连续对对方进行两次带固定伤害的物理攻击
                  会减少对方气血后限
		  冷却时间4秒
        外功条件：
        	  火云洞弟子
        	  人物等级30级	
        	  内力500点，消耗100点
                  火魔心法 200 级
                  五岳神枪 200 级并激发
STR;
        me->start_more(str);
        return 1;
}