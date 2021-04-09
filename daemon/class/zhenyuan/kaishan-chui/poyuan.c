#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra,damage;

	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="五庄观")
                return notify_fail("破元一击只有五庄观门人才可以用！\n");
        if(me->query_skill("kaishan-chui",1) < 100)
                return notify_fail("你的开山锤还不够纯熟。\n");
        if(me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("破元一击必须和镇元神功配合。\n");
        if((int)me->query("force") < 1000 )
                return notify_fail("你的内力不够！\n");
        
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("破元一击只能对战斗中的对手使用。\n");

	extra = me->query_skill("kaishan-chui",1) / 10;
        extra += me->query_skill("baguazhen",1) / 15;
        extra += me->query_skill("hammer",1) / 10;
        if( extra<100 )  extra = 100;
        if( extra>800 )  extra = 800;
        me->receive_damage("kee", 150);
        me->add("force",-100);

        me->add_temp("apply/attack", extra);
        msg = HIC"$N"HIC"一抖仙衣，$w"HIC"发出呼啸之声，一式"+HIC"－破－云－一－击 －"HIC+"如急电般砸向$n"HIC"！\n" NOR;
        damage = COMBAT_D->do_attack(me, target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/5);
        if( damage>0 )
        	target->add("force",-(damage/20+1));
        else	me->add("force",-50);
        	
        if( me->query("force")>200 )
        {
        	me->add("force",-100);
                msg = HIC"\n$N"HIC"手中$w"HIC"幻出奇异的光华砸向$n"HIC"！\n" NOR;
	        damage = COMBAT_D->do_attack(me, target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/4);
        	if( damage>0 )
        		target->add("force",-(damage/15+1));
        	else	me->add("force",-30);
	}                
        
	if( me->query("force")>200 && me->query_skill("kaishan-chui",1)>180 )
        {
        	me->add("force",-100);
                msg = HIC"\n$N"HIC"手中$w"HIC"发出摄人心魄的呼啸向$n"HIC"砸去！\n" NOR;
	        damage = COMBAT_D->do_attack(me, target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/3);
        	if( damage>0 )
        		target->add("force",-(damage/10+1));
        	else	me->add("force",-30);
	} 
        
        if( me->query("force")>200 && me->query_skill("kaishan-chui",1)>240 )
        {
        	me->add("force",-100);
                msg = HIC"\n$N"HIC"手中$w"HIC"竟然发出耀人双目的奇光砸向$n"HIC"！\n" NOR;
	        damage = COMBAT_D->do_attack(me, target,me->query_temp("weapon"),TYPE_PERFORM,msg,0,0,extra/2);
        	if( damage>0 )
        		target->add("force",-(damage/5+1));
        	else	me->add("force",-30);
	} 
	if( target && target->query("force")<0 )
		target->set("force",0);	        	
        me->start_busy(3);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：破元一击
        外功所属：开山锤
        外功效果：对敌进行带固定伤害的攻击，最多4击
        	  固定伤害递增
        	  打中能消耗对方的内力，消耗值递增
                  使用后自身busy 3 秒
        外功条件：
                  五庄观弟子
                  人物等级10级
                  内功激发镇元神功
                  内力1000点，消耗100点，每增一击，消耗100点
                  开山锤100级
                  
LONG;
me->start_more(str);
return 1;
}

