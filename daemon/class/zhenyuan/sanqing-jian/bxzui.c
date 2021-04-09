//「八仙醉剑」　by qingniu 06/2009
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,succ_msg;
        object weapon;
        int damage,p;

	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");
	weapon=me->query_temp("weapon");
	if( !weapon 
	 || me->query_skill_mapped("sword")!="sanqing-jian"
	 || (weapon->query("skill_type")!="sword"
	  && weapon->query("use_apply_skill")!="sword") )
		return notify_fail("「八仙醉剑」乃是三清剑法的绝技。\n");
        if((me->query("family/family_name") != "五庄观" ) && !wizardp(me))
                return notify_fail("非镇元门生不得使用「「八仙醉剑」」！\n");        
        if((int)me->query_skill("taiyi", 1) < 300)
                return notify_fail("你的太乙仙法修为太浅，无法使用「八仙醉剑」。\n");
        if((int)me->query_skill("sanqing-jian", 1) < 400)
                return notify_fail("你的三清剑法修为太浅，无法使用「八仙醉剑」。\n");
        if((int)me->query("force") < 2000 )
                return notify_fail("你的内力不够，没办法使用「八仙醉剑」。\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("你现在精神不振，使用「八仙醉剑」必须精神集中！\n");     
        if( time()<me->query_temp("wzg_bxzui")+7 )
                return notify_fail(HIR"你忽然觉得酒意已浓，猛然收住攻势！\n"NOR);
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁使用「八仙醉剑」？\n");

        msg = HIG "只见$N"HIG"突然解下腰中的白玉葫芦，于战局之中竟然庞若无人，仰天长饮仙酒飘香之际，向$n"HIG"使出了五庄绝学“「八仙醉剑」”。\n" NOR;
        message_vision(msg, me, target);
        me->add("force", -500);
        me->receive_damage("sen",100,me);
        me->set_temp("wzg_bxzui",time());
        
        msg = HBBLU "「铁拐李旋踵膝撞醉还真」，$N"HBBLU"踉踉跄跄朝$n"HBBLU"撞去！\n" NOR;
        succ_msg = HIR"结果$n"HIR"脚步踉跄，顿时动弹不得。\n" NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/60);
        me->set_temp("pfm_msg",0);
        if( damage>0 && !target->is_busy() )
        	target->start_busy(3);
        else	message_vision(YEL "结果$N"YEL"以静制动，应付自如。\n" NOR,target);
        	
        
        msg = HBBLU"「韩湘子擒腕击胸醉吹箫」，$N"HBBLU"以剑作箫，一缕剑气直刺$n"HBBLU"$l！\n"NOR;
	succ_msg = HIR"$n"HIR"浑噩不觉，只觉心里一酸，不由泪眼迷离。\n" NOR;
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,msg,succ_msg,0,me->query_skill("sword")/50);
        me->set_temp("pfm_msg",0);
        
        
        msg = HBBLU"「汉钟离，跌步抱酲兜心顶」，$N"HBBLU"收剑团身，合身撞向$n"HBBLU"！\n"NOR;
        succ_msg = HIR"$n"HIR"胸口巨震，脚步踉踉跄跄。\n"NOR;
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"胸口",me->query_skill("sword")/45);
        me->set_temp("pfm_msg",0);
        
        msg = HBBLU"「蓝采和，单提敬酒拦腰破」，$N"HBBLU"手中$w"HBBLU"风驰电掣，朝$n"HBBLU"拦腰扫去！\n"NOR;
        succ_msg = HIR"$n"YEL"顿时五脏挪移，感觉疼痛深入骨髓。\n" NOR;
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/40);
        me->set_temp("pfm_msg",0);
        
        if( me->query("force")<100 || me->query_skill("sanqing-jian",1)<450 )
        	return 1;

        msg = HBBLU"「何仙姑，弹腰献酒醉荡步」，$N"HBBLU"手中$w"HBBLU"发出绚烂夺目的光华！\n"NOR;
        succ_msg = HIR"$n"HIR"顿时眼神恍惚，一时难辨方向。\n" NOR;
        me->add("force",-100);
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/35);
        me->set_temp("pfm_msg",0);
        if( damage>0 && !target->is_no_move() )
        	target->start_no_move(3+random(3),"你被"+me->name()+"的剑光闪了眼。\n");
        	
        if( me->query("force")<100 || me->query_skill("sanqing-jian",1)<500 )
        	return 1;
        
        msg = HBBLU"「曹国舅，仙人敬酒锁喉扣」，$N"HBBLU"手中$w"HBBLU"飞舞灵动，如毒蛇般刺向$n"HBBLU"颈部！\n"NOR;
        succ_msg = HIR"$n"HIR"只觉咽喉一紧，剑气透体而入。\n" NOR;
        me->add("force",-100);
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,"颈部",me->query_skill("sword")/30);
        me->set_temp("pfm_msg",0);
        
        if( me->query("force")<100 || me->query_skill("sanqing-jian",1)<550 )
        	return 1;
        msg = HBBLU"「张果老，醉酒抛杯踢连环」，$N"HBBLU"将手一抖，连发数道剑气冲向$n"HBBLU"$l！\n"NOR;
        succ_msg = HIR"$n"HIR"连续受创，已到垂死边缘。\n" NOR;
        me->add("force",-100);
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/25);
        me->set_temp("pfm_msg",0);
        
        if( me->query("force")<100 || me->query_skill("sanqing-jian",1)<600 )
        	return 1;
        
        msg = HBBLU"「吕洞宾 醉酒提壶力千钧」，$N"HBBLU"手中$w"HBBLU"化作一道长虹，直奔$n"HBBLU"$l而去！\n"NOR;
        succ_msg = HIR"$n"HIR"目瞪口呆，被这一剑势惊呆。\n" NOR;
        me->set_temp("SQJ_perform",7);
        me->add("force",-100);
	me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,me->query_skill("sword")/20);
        me->delete_temp("SQJ_perform");
        me->set_temp("pfm_msg",0);
        
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：八仙醉剑
        外功所属：三清剑法
        外功效果：以醉八仙之姿攻击对方多次，固定伤害递增
        	  最多八击，后四击需要三清剑法等级支持
                  冷却时间7秒
        外功条件：
                  五庄观弟子
                  精神300点，消耗100点
                  内力2000点，消耗500点，后四击每击增加100点消耗
                  太乙仙法300级
                  三清剑法400级
LONG;
me->start_more(str);
return 1;
}


