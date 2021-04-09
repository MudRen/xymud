#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg,succ_msg;
	int damage;

	if( me->query("bellicosity")>300 )
        	return notify_fail("你的杀气太重，无法施展佛门绝技。\n");
        if( me->query_level()<45 )
        	return notify_fail("你的人物等级不够。\n");	
	if( me->query_skill("staff")<600 )
		return notify_fail("你的轮回杖法与基本杖法还不够纯熟，怕是无法运用！\n");
	if(me->query("bonze/class")!="bonze" ) 
		return notify_fail(HIR"你非佛门弟子！\n"NOR);
	if( me->query_skill("force",1)<450 )
		return notify_fail("你的内功底子不足，无法运杖如风，施展不出佛门三渡。\n");
        if( me->query_skill_mapped("staff")!="lunhui-zhang" )
        	return notify_fail("佛门三渡是轮回杖法的绝招。\n");	
	if( me->query("force") < 300 )
        	return notify_fail("你现在的内力不足。\n");
        if( time()<me->query_temp("putuo_sandu")+6 )
        	return notify_fail("绝招用多就不灵了。\n");
        
	if( !target ) 
        	target = offensive_target(me);
	if( !target
  	 || !target->is_character()
  	 || !me->is_fighting(target) )
        	return notify_fail("「佛门三渡」只能对战斗中的对手使用。\n");

	me->add("force",-200);
	me->set_temp("putuo_sandu",time());

	me->set_temp("PERFORM_sandu",7);
	succ_msg = HIR "$n"HIR"心神一慌，一个躲闪不及，被$w"HIR"实实在在的印在胸膛，$n"HIR"的胸膛立刻就塌了下去！\n"NOR;
	damage = me->query_skill("staff")/3;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,succ_msg,"胸口",damage);
	me->delete_temp("PERFORM_sandu");
	
	if( me->query("force")<50 )
		return 1;
	
	me->set_temp("PERFORM_sandu",8);	
	damage = me->query_skill("staff")/2;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,succ_msg,0,damage);
	me->delete_temp("PERFORM_sandu");
	
	if( me->query("force")<50 )
		return 1;	

	me->set_temp("PERFORM_sandu",9);
	succ_msg = HIR "$n"HIR"被这弧形的汹涌劲气一罩，身法全乱，象喝醉了的东倒西歪！\n"NOR;
	damage = me->query_skill("staff");
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,succ_msg,0,damage);
	me->delete_temp("PERFORM_sandu");
		
	if( me->query("force")<500 )
		return 1;
		
	me->set_temp("PERFORM_sandu",10);
        succ_msg = HIR "$n"HIR"似一片枯叶，被「慈光普渡」的劲气包围、卷起、压扁、抛下，似一个破包重重的摔在地上！\n"NOR;
	damage = me->query_skill("staff")*3/2;
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,0,succ_msg,0,damage);
        me->delete_temp("PERFORM_sandu");
        return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：佛门三渡
        外功所属：轮回杖法
        外功效果：对敌进行三次有固定伤害的连续攻击
                  内力充足的情况下再追一击 
                  冷却时间6秒
        外功条件：
                  佛门弟子 
        	  人物等级45级
                  杀气低于300
                  内力300点，消耗200点
                  基本杖法有效等级600级，并激发轮回杖法
                  内功心法450级
LONG;
me->start_more(str);
return 1;
}