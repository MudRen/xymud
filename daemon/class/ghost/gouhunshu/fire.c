//Cracked by Roath
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

int check_damage(object me, object target, int time);
int generate_msg(object me);

int cast(object me, object target)
{
	int time;
	if( me->query_level()<25 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="阎罗地府") 
        	return notify_fail("你不是地府弟子，不能使用这项技能！\n");
	if( !target ) target = offensive_target(me);        	
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me )
        	return notify_fail("你要引地狱火去烧谁？\n");
	if((int)me->query_skill("gouhunshu") < 200 )
        	return notify_fail("你的勾魂术等级还不够。\n");
	if((int)me->query("mana") < 500 )
        	return notify_fail("你的法力不够了！\n");
	if((int)me->query("sen") < 100 )
        	return notify_fail("现在你的精神不足！\n");
	if( (int)me->query("kee") < 100 )
        	return notify_fail("你的气血不足。\n");
	if( random(me->query_maxmana()) < 50 ) 
	{
        	write("这次好象不大灵。\n");
        	return 1;
        }
	time = 2 + (int)me->query_skill("gouhunshu",1) / 50;
	if ( time > 5 ) time=5;

	message_vision(HIB"$N"HIB"双掌一搓，登时燃起一团蓝色的火焰，点点磷光飘向了$n"HIB"！\n"NOR, me,target);
	check_damage(me, target, time);
	return 1+random(4);
}

int check_damage(object me, object target, int time)
{
	int ap,dp,damage,success;

	if( !target
 	 || !me 
 	 || environment(me) != environment(target)) 
        	return 1;
	ap = COMBAT_D->skill_power(me,"spells",SKILL_USAGE_ATTACK);
	ap+= me->query_level()*10;
	dp = COMBAT_D->skill_power(target,"spells",SKILL_USAGE_DEFENSE);
	dp+= target->query_level()*10;
	if( COMBAT_D->wuxing_restrain(me,target)==1 )
        	dp-= random(dp/3);      
	if( COMBAT_D->wuxing_restrain(me,target)==-1 )
        	dp+= random(dp/3);      
	if( target->is_busy() )
        	ap+= random(ap/3);

	damage = me->query_spells_damage();
	damage = damage*9/10+random(damage/10);
	damage = damage*me->query_spi()/60;
	damage+= (me->query_skill("spells",1)-target->query_skill("spells",1))/3;
	damage-= me->query_spells_damage()*target->query_spells_def()/(target->query_spells_def()+target->query_level()*50+360);
	damage+= me->query("mana_factor")/5+random(me->query("mana_factor")/5);
	success=1;

	if( damage < 0 ) success = 0;
	if( random(ap+dp) < dp ) success = 0;
	if( (int)me->query("mana") < 30 ) success = 0;
	if( (int)me->query("kee")  < 30 ) success = 0;
	if( environment(me)->query("no_fight")
 	|| environment(me)->query("no_magic") ) success = 0;

	if( success )
        {
        	message_vision(HIB"\n「啪」地一团蓝色火焰在$N"HIB"脚下燃起，如鬼魅缠身，将$N"HIB"拢在中央。\n"NOR, target);
        	target->receive_damage("kee", random(damage),0,TYPE_CAST);
        	target->receive_wound("kee", damage/3,0,TYPE_CAST);
        	COMBAT_D->report_status(target);
        	me->receive_damage("kee", 25);
        	me->add("mana", -25);
        } 
	else    tell_room(environment(target), "\n四周点点磷火飘荡着………\n");
	time--;
	if( time ) 
        {
        	call_out("generate_msg", 4, me);
        	call_out("check_damage", 8, me, target, time);
        }
	if( !target->is_fighting(me) ) 
        {
        	if( living(target) ) 
                {
                	if( userp(target) ) target->fight_ob(me);
                	else target->kill_ob(me);
                }
        	me->kill_ob(target);
        }
	return 1;
}

int generate_msg(object me)
{
	string *msgs=({
        	"\n「啪」地一道蓝色火焰闪过。\n",
        	"\n点点磷火在空气中飘荡着………\n",
        	"\n一股蓝色火焰从地下冒了出来。\n",
        	"\n火球「啪，啪」地爆燃着………\n",
	});
	if( !me ) return 1;
	tell_room( environment(me), msgs[random(sizeof(msgs))]);
}

int help(object me)
{
string str;
if ( !me )      return 0;
str = @LONG
        法术名称：黄泉鬼火
        法术所属：勾 魂 术
        法术效果：召唤地狱鬼火攻击敌人
                  
        法术条件：
                  地府弟子
                  人物等级25级 
                  勾 魂 术200级
                  法力500点，每次鬼火攻击，消耗25点
                  气血100点，每次鬼火攻击，消耗25点
                  精神100点
LONG;
me->start_more(str);
return 1;
}      

void remove()
{
	remove_call_out("generate_msg");
	remove_call_out("check_damage");
}