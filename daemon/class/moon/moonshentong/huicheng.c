#include <ansi.h>
inherit SSERVER;

int valid_cast(object me)
{
	int t = me->query_skill("jiefeng",1);
	if(me->query("family/family_name") != "月宫")
        	return notify_fail("这是月宫不传之密！\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");
	t = 60-t/30;
	if( t>3 )
		t = 3;
	if( time()<me->query_temp("last_huicheng")+t )
		return notify_fail("你刚刚借用过太阴之力。\n");
	return 1;
}	

int cast(object me, object target)
{       
        object soldier;

	if( !valid_cast(me) )
		return 0;
	if( me->is_no_move() )
		return notify_fail("你现在动弹不得。\n");
	if( environment(me)->query("no_huicheng") )
		return notify_fail("这里不能使用回城诀。\n");
					
        message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -50);

        if( random(me->query("max_mana")) < 20 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }
	message_vision(HIC"一道月华之光如倒卷星河，从头而降，将$N"HIC"全身裹住，瞬间往西昆仑方向而去！\n\n"NOR,me);
	me->set_temp("last_huicheng",time());
        if( me->is_fighting() )
        	me->start_busy(5);
        me->move("/d/moon/xiaoyuan",2);
        message("vision",HIC"\n\n一道月华之光如倒卷星河，从天而降，"+me->name()+HIC"从中显出了身影。。。\n"NOR,environment(me),({me}));
        tell_object(me,HIC"\n你借月华之力回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：月下独步
        法术所属：月宫仙法
        法术效果：返回师门
        	  战斗中使用自身busy 5 秒
        法术条件：
                  月宫弟子
        	  人物等级5级
                  法力100点，消耗50点
                  
STR;
        me->start_more(str);
        return 1;
}