#include <ansi.h>
inherit SSERVER;

int valid_perform(object me)
{
	if(me->query("family/family_name") != "盘丝洞")
        	return notify_fail("这是盘丝洞不传之密！\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("force") < 50 )
                return notify_fail("你的内力不够了！\n");
	if( time()<me->query_temp("last_huicheng")+60 )
		return notify_fail("你刚刚借用过灯芯佛火之力。\n");
	return 1;
}	

int perform(object me, object target)
{       
        object soldier;

	if( !valid_perform(me) || me->is_fighting() )
		return 0;
	if( me->is_no_move() )
		return notify_fail("你现在动弹不得。\n");
	if( environment(me)->query("no_huicheng") )
		return notify_fail("这里不能使用回城诀。\n");
					
        message_vision("$N脚下动了几动。\n", me);
        me->add("force", -30);

        if( random(me->query("max_force")) < 20 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }
	message_vision(HIR"只见$N"HIR"脚下越转越快，整个人影疾如幻影，隐约化作灯芯模样，火光一冒，顿时消失不见了。\n"NOR,me);
	me->set_temp("last_huicheng",time());
        me->move("/d/pansi/damen",2);
        message("vision",HIR"\n\n光火一冲，"+me->name()+HIR"从天而降。。。\n"NOR,environment(me),({me}));
        tell_object(me,HIC"\n你借灯芯佛火之力回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：灯焰穿梭
        外功所属：月影舞步
        外功效果：返回师门
        	  战斗中不能使用
        	  冷却2分钟
        外功条件：
                  盘丝洞弟子
        	  人物等级5级
                  内力50点，消耗30点
                  
STR;
        me->start_more(str);
        return 1;
}