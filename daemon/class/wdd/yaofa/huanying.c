// 妖法－－幻影
#include <ansi.h>
#include <command.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit SSERVER;

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
        "east":         "东",
        "west":         "西",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上",
        "down":         "下",
        "out":          "外",
        "enter":        "里",
]);

int cast(object me, object target)
{
	object env, obj;
	int mymana=me->query("mana"), cost=100, i, n;
	int success;
	string msg;
	string *dirs, target_dir, dest;
	mapping exit;
	
	if( me->query_level()<25 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="陷空山无底洞")
      		return notify_fail("无底洞弟子才可以用！\n");
	if((int)me->query_skill("spells")<250 || (int)me->query_skill("yaofa", 1) < 250 )
		return notify_fail("你还没学会幻影术。\n");
	if((int)me->query("sen") < 200 )
		return notify_fail("你的精神没有办法有效集中！\n");
	if( me->query("mana")<500 )
		return notify_fail("你的法力不够。\n");	

	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展这个法术？\n");
	if( !valid_move(target) )
		return notify_fail(target->name()+"已经动弹不得了！\n");

	env = environment(me);
	exit = env->query("exits");
	if( !exit || !mapp(exit) || sizeof(keys(exit))<1 )
		return notify_fail("你想将"+target->name()+"引到那儿去？\n");

	dirs = keys(exit);
	n = sizeof(exit);
        i = random(n-1);
	if(exit[dirs[i]])
		dest = exit[dirs[i]];
	if( !undefinedp(default_dirs[dirs[i]]) )
                target_dir = default_dirs[dirs[i]];
        else	target_dir = dirs[i];
	if(!(obj = load_object(dest)) )
		return notify_fail("无法走！\n");
	if( !obj->valid_leave(target,dirs[i]) )
		return notify_fail("无法走！\n");
	
	me->add("mana", -200);
	me->receive_damage("sen",100);

	msg = HIC "$N口中念了句咒文，张口喷出一股青烟。\n" NOR;
	msg += HIC "烟雾中只见一条人影向" + target_dir + "逃去。\n" NOR;
	message_vision(msg, me, target);
	
	success = COMBAT_D->attack_percent(me,target,TYPE_CAST);
	if( success==1 && !GO_CMD->main(target, dirs[i], 0) ) 
		success=0; // failed to go.
	if( success == 1 ) 
		msg = HIR +target->name()+HIR"向" + target_dir + "追去。\n" NOR;
	else	msg = HIR "$n"HIR"不为所动，幻影术失败了。\n" NOR;
	message_vision(msg, me, target);
	if(success == 1) 
	{
		msg = HIR "只见"+target->name()+"跑了进来，四处张望，却什么都没发现。\n" NOR;
               	message( "vision", msg, environment(target), ({target}));
		tell_object(target,"你急急忙忙跑了过来，四处张望，却什么都没发现。\n");
               	return 1;
	} 
	else 
	{
		me->start_busy(2);
		return 1;
	}
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：幻影术
        法术所属：妖法
        法术效果：通过召唤幻影来「调虎离山」
        	  失败则自身busy 2 秒
        	  对方如处于束缚状态或当前区域不允许对方离开的情况下无效
        法术条件：
                  无底洞弟子
        	  人物等级25级
                  基本法术250级
                  妖法250级
                  精神200点，消耗100点
                  法力500点，消耗200点
                  
STR;
        me->start_more(str);
        return 1;
}