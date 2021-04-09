//by 龙追魂(lzh) 2009.06.01
//「冰风雪雨」/daemon/class/yaomo/xueshan/bingpo-blade/bingxue.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int damage,num;
        
        if( me->query_level()<30 )
        	return notify_fail("你的人物等级不够。\n");
        if((me->query("family/family_name") != "大雪山" ) && !wizardp(me))
                return notify_fail("非大雪山弟子不得使用「冰风雪雨」！\n");
        if((string)me->query_skill_mapped("force")!="ningxie-force")
                return notify_fail("「冰风雪雨」要以冰谷凝血功为底子。\n");
        if((int)me->query("force") < 800 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query("kee") < 500 )
                return notify_fail("你身体太虚弱了，无法施展「冰风雪雨」!\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("你神情恍惚，无法施展「冰风雪雨」!\n");
        if((int)me->query_skill("blade", 1) < 300 )
                return notify_fail("你的基本刀法还不够纯熟！\n");
        if((int)me->query_skill("bingpo-blade", 1) < 300 )
                return notify_fail("你的冰魄寒刀练得不够纯熟，无法使出这招「冰风雪雨」！\n");
        if((int)me->query_skill("ningxie-force", 1) < 300 )
                return notify_fail("你对冰谷凝血功领悟尚浅，不能使出「冰风雪雨」！\n");
        if((int)me->query_skill("dengxian-dafa", 1) < 300 )
                return notify_fail("你对登仙大法领悟尚浅，不能使出「冰风雪雨」！\n");
        if(time()-(int)me->query_temp("bingxue_end") < 4 )
                return notify_fail("「冰风雪雨」仿佛不受你的召唤……\n");
        
        if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
		return notify_fail("你要对谁施展「冰风雪雨」？\n");
     
        message_vision(MAG "\t☆★☆★"HIC"千里冰风"HIW"漫天雪，"HIY"幻梦冰雪"HIM"落晴空！"NOR""MAG"★☆★☆\n"NOR,me,target);
        me->set_temp("bingxue_end",time());
        me->receive_damage("kee",100,me);
        me->receive_damage("sen",100,me);
        me->add("force",-150);
        msg = HIW "$N"HIW"念了几句咒语，只见原本晴朗的天空随着音符逐渐黯淡......远处，大雪山万兽谷中禁锢了千年的"HIB"「冰风雪雨」"HIW"，却仿佛受到了什么召唤，狂啸着飞奔向$n"HIY"！\n"NOR;
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
	me->set_temp("pfm_msg",0);
        if( damage>0 && me->query("force")>500 )
        {
                msg = WHT "\n\t冰风嚎怒平地起	狂风之怨谁能裁？\n"NOR;
		msg+= HIW "$N"HIW"$w"HIW"高高举过头顶，一声断喝！一股气势惊人的刀气，随着咆哮的冰风一起，朝$n"HIW"席卷而至！\n"NOR;
		me->add("force",-100);
	        me->set_temp("pfm_msg",1);
        	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
		me->set_temp("pfm_msg",0);
                if( damage>0 && me->query("force")>300 
                 && me->query_skill("bingpo-blade",1)>500 
		 && me->query_skill("ningxie-force",1)>500 )
                {
                	msg = WHT "\n\t雪雨纷飞天上来	冰雪碎梦一场空！\n"NOR;
                	msg+= HIR "$N"HIR"低喝一声，忽然原地一个旋转，陡然之间$w"HIR"颤动，朝$n"HIR"$l一连劈出了不知道多少下！\n"NOR;
			me->add("force",-100);
		        me->set_temp("pfm_msg",1);
        		damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg);
			me->set_temp("pfm_msg",0);
			if( damage>0 && me->query_skill("bingpo-blade",1)>600 
			 && me->query_skill("ningxie-force",1)>600 )
			{
				num = me->query_skill("throwing", 1);
				num = 1+num/150;
				damage = (damage/5+1)*num;
				message_combatd( HIW "一片雪花飘到了$n"HIW"的身上，$p猛然一颤，被刀气所伤！\n"NOR, me, target );
				target->receive_wound("kee", damage/2, me,TYPE_PERFORM);
				target->receive_damage("kee", damage, me,TYPE_PERFORM);
                              	COMBAT_D->report_status(target,1);
                              	COMBAT_D->report_status(target);
			}	
		}
	}
	else
	{
 		msg = HIY"$n"HIY"眼神中闪过一丝决然，贴着$N"HIY"一阵猛攻，在一片招架声中，天空慢慢恢复了晴朗。\n"NOR;
         	message_combatd(msg, me, target);
         	me->add("force",-150);
         	if( me->query("force")<0 )
			me->set("force",0);
		me->receive_damage("kee",100,me);
        	me->receive_damage("sen",100,me);
         	me->add_temp("bingxue_end",3);
        } 
	return 1;
}

int help(object me)
{ 
string str; 
if ( !me )      return 0; 
str = @LONG 
              外功名称：冰风雪雨
              外功所属：冰魄寒刀  
              外功效果：召唤大雪山万兽谷中禁锢千年的冰风雪雨攻击敌人
              		最多能给予对方4次物理伤害
              		每增加一次伤害，内力消耗增加100点
              		冷却时间4秒，如果失败，冷却时间增加3秒
              外功条件：
              		雪山弟子
              		人物等级30级
              		基本刀法300级
              		冰魄寒刀300级
              		冰谷凝血功300级
                        登仙大法300级
                        气血500点，消耗100点，失败则加倍
                        精神500点，消耗100点，失败则加倍
                        内力800点，消耗150点，失败则加倍
LONG; 
me->start_more(str); 
return 1; 
} 


