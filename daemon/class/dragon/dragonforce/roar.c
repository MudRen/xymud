#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_kill.h"
inherit F_CLEAN_UP;

int exert(object me, object target)
{
	object *ob, where,*teams;
	int i, skill, damage, force;
	if( !target ) target = me;
	if( me->query_level()<25 )
		return notify_fail("你的人物等级不够。\n");
	where = environment(me);
	if( where->query("no_fight") )
        	return notify_fail("安全区内不能乱吼乱叫！\n");
	if(me->query("family/family_name")!="东海龙宫")
        	return notify_fail("非龙宫弟子不能用「碧海龙吟」！\n"); 
	if( !me->is_fighting() )
        	return notify_fail("碧海龙吟只能在战斗中使用。\n");
	if( (int)me->query("force") < 500 )
        	return notify_fail("你的内力不够。\n");
	if( (int)me->query("kee") < 200)
        	return notify_fail("你的力气不够了。\n");
	if( me->query_skill("dragonforce",1)<200 )
		return notify_fail("你的龙神心法不够。\n");
		
	skill = me->query_skill("force");
	force = me->query("max_force");
	me->add("force", -300);
	me->receive_damage("kee",150,me);

	me->start_busy(5);
	message_vision(HIR "$N"HIR"退后两步，深深地吸一口气，猛然发出股如山崩海啸般的龙吟！\n"NOR, me);
	ob = all_inventory(environment(me));
	teams = me->query_team();
	for(i=0; i<sizeof(ob); i++) 
        {
        	if( !living(ob[i]) || ob[i]==me ) continue;
        	if(!me->visible(ob[i])) continue;
        	if( skill/2 + random(skill/2) < (int)ob[i]->query("cps") * 2 ) 
                	continue;
		if( teams && arrayp(teams) && sizeof(teams)>0
         	&& member_array(ob[i],teams)!=-1 )
                	continue;
                if( COMBAT_D->check_level(me,ob[i])==-1 )
                        continue; 
                if( me==ob[i]->query_temp("invoker") || ob[i]==me->query_temp("invoker") )
                        continue; 
		if(!valid_kill(me,ob[i],0))
			continue; 
                if( me==ob[i]->query_temp("invoker") )
                        continue; 
		damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_CAST,0,0,0,0,"both");
        	if( damage > 0 ) 
                	tell_object(ob[i], HIR"你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n"NOR);
		if( !ob[i]->is_killing(me->query("id")) )
                	ob[i]->kill_ob(me);
        }
	return 1;
}

int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        内功名称：碧海龙吟
        内功所属：龙神心法
        内功效果：发出龙吟攻击同区域的其他所有非同组人员
                  使用后自身busy 5 秒
                  不与你性命相搏的对象会对你叫杀
        内功条件：
                  龙宫门人
                  人物等级25级
                  内力500点，消耗300点
                  气血200点，消耗150点
                  龙神心法200级
LONG;
me->start_more(str);
return 1;
}

