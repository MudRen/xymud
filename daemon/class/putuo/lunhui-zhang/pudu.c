// 慈光普渡 Pudu.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{       
	string str,succ_msg,msg="";
	int damage,wound,extra,spi;
	object weapon=me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me 
 	 || !me->is_fighting(target) )
		return notify_fail("你要对谁施展「慈光普渡」？\n");
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");		
	if(me->query("family/family_name") != "南海普陀山" 
	 && me->query("chushi/chushi_putuo")!="yes" )
        	return notify_fail("不是佛门弟子不能用「慈光普渡」！\n");
	if( (int)me->query("bellicosity") > 300 )
        	return notify_fail("你的杀气太重，无法施展佛门绝技。\n");
	if(me->query_skill_mapped("force")!="lotusforce")
        	return notify_fail("「慈光普渡」必须以莲台心法为底子！\n");
	if((int)me->query("max_force") < 500 )
        	return notify_fail("你的内力不够！\n");
	if((int)me->query("force") < 300 )
        	return notify_fail("你的内力不足！\n");
	if((int)me->query("sen") < 300 )
        	return notify_fail("你的精神不足，没法子施用外功！\n");
	if((int)me->query_skill("lotusforce", 1) < 100)
        	return notify_fail("你的莲台心法修为还不够，使用这一招会有困难！\n");
	if((int)me->query_skill("lunhui-zhang", 1) < 100)
        	return notify_fail("你的轮回杖修为还不够，使用这一招会有困难！\n");

	extra = me->query_skill("lunhui-zhang")/2;
	
	message_vision(HIY"$N"HIY"气沉丹田，犹如金刚浑身发金光，招转佛门正宗绝招「慈光普渡」，向$n"HIY"连续发动进攻！\n"NOR,me,target);
	me->add_temp("apply/attack", extra);    
	me->add("force",-200);
	me->receive_damage("sen",50);
	
	msg = HIY"$N"HIY"念道：日华灿灿向天南，刺若利刃冲斗寒。精光四射人惊骇，普陀妙法何其玄。\n" NOR;
    	msg+=  HIY "------日光华------\n"NOR;
	me->set_temp("ciguangpudu", 7);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra);


	msg = HIY"\n$N"HIY"念道：洪波沧海水湍湍，万里波涛使人寒。不二法门能证果，唤来伏魔亦何难？\n" NOR;
    	msg+= HIY "------靛沧海------\n"NOR;
    	me->set_temp("ciguangpudu", 8);
	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra);
	
	
	if((int)me->query_skill("lunhui-zhang", 1)>=150 )
	{
		msg = HIY  "\n$N"HIY"念道：北方玄武有后土，巨岩盘环当空舞。仁者持咒唤其来，力士黄巾由来怒。\n" NOR;
    		msg+= HIY "------巨岩破------\n"NOR;
    		me->set_temp("ciguangpudu", 9);
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra*3/2);
	}
	
	if((int)me->query_skill("lunhui-zhang", 1)>=200 )
    	{
    		msg = HIW"\n只见$N"HIW"喃喃自语道：天地阴阳逆，乾坤有浊清。万世红尘意，一谒黄庭声。慈光普渡第二重转瞬而出。\n" NOR;
        	msg+= HIW"$N"HIW"念道：桃林万里幻无边，神荼郁垒隐其间。普陀法师动诀咒，护法金光是上仙。\n" NOR;
        	msg+= HIW "------苍茫树------\n"NOR;
        	me->set_temp("ciguangpudu", 9);
        	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra*2);
	}
	if((int)me->query_skill("lunhui-zhang", 1)>=250 )
    	{
    		msg = HIR"\n$N"HIR"喃喃自语道：道归法门里，力震妖魔惊。普陀有正果，只在心中生。慈光普渡第三重又接连而出。\n" NOR;
        	msg+= HIR"$N"HIR"念道：烈焰幽冥劫火生，裂地而出鬼神惊。若问因果由何起，普陀高士持咒声。\n" NOR;
        	msg+= HIR "------地裂火------\n"NOR;
        	me->set_temp("ciguangpudu", 9);
        	COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra*5/2);
	}

	msg = HIW"$N"HIW"低吟“阿弥陀佛！”「慈光普渡」用功完毕，身上淡淡的金光慢慢隐去.\n"NOR;
	message_combatd(msg, me, target);
	me->add_temp("apply/attack", -extra);   
	me->delete_temp("ciguangpudu");
	me->start_busy(2+random(2));
	return 1;
}


int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：慈光普渡
        外功所属：轮回杖法
        外功效果：对敌进行两次有固定伤害的连续攻击
        	  轮回杖法每50级增加一击，固定伤害递增
        	  最高5次攻击
                  使用后自身busy 2-3 秒
        外功条件：
                  普陀(出师)弟子 
        	  人物等级10级
                  杀气低于300
                  内力修为五年
                  内力300点，消耗200点
                  精神300点，消耗50点
                  轮回杖法100级
                  莲台心法100级
LONG;
me->start_more(str);
return 1;
}
