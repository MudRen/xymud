#include <ansi.h>
inherit SSERVER;

int valid_cast(object me)
{
	if(me->query("family/family_name") != "五庄观")
        	return notify_fail("这是五庄观不传之密！\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");
	if( time()<me->query_temp("last_huicheng")+60 )
		return notify_fail("你刚刚借用过八卦之力。\n");
	return 1;
}	

int cast(object me, object target)
{       
        object soldier;

	if( !valid_cast(me) || me->is_fighting() )
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
	message_vision(HIY"只见一个金光灿灿的八卦图骤现在眼前，$N"HIY"将身一摇，转进八卦图中消失不见了。\n"NOR,me);
	me->set_temp("last_huicheng",time());
        me->move("/d/qujing/wuzhuang/guangchang",2);
        message("vision",HIC"\n\n一个金光灿灿的八卦图骤现在眼前，"+me->name()+HIC"从中钻了出来。。。\n"NOR,environment(me),({me}));
        tell_object(me,HIC"\n你借八卦之力回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：颠倒乾坤
        法术所属：太乙仙法
        法术效果：返回师门
        	  战斗中不能使用
        法术条件：
                  五庄观弟子
        	  人物等级5级
                  法力100点，消耗50点
                  
STR;
        me->start_more(str);
        return 1;
}