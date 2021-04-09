#include <ansi.h>
inherit SSERVER;

int valid_cast(object me)
{
	int t = me->query_skill("jiefeng",1);
	if( (string)me->query("family/family_name") != "火云洞" )
		return notify_fail("你并非火云洞弟子，使不了「火遁咒」。\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");
	t = 60-t/30;
	if( t>3 )
		t = 3;
	if( time()<me->query_temp("last_huicheng")+t )
		return notify_fail("你不能频繁施展「火遁咒」。\n");
	return 1;
}	

int cast(object me, object target)
{       
	string str;
	int i;
	
	if( !valid_cast(me) )
		return 0;
	if( me->is_fighting() )
		return notify_fail("战斗中不能使用。\n");
	if( me->is_no_move() )
		return notify_fail("你现在动弹不得。\n");
	if( environment(me)->query("no_huicheng") )
		return notify_fail("这里不能使用回城诀。\n");
	message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -50);
        if( random(me->query_maxmana()) < 20 ) 
        {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }
	message_vision(HIR"只见$N"HIR"将身一摇，顿时火光冲天，$P已随火光一闪而逝！\n"NOR,me);
	me->set_temp("last_huicheng",time());
        if( me->is_fighting() )
        	me->start_busy(5);
        me->move("/d/qujing/kusong/guaishiya",2);
        message("vision",HIR"\n\n天空中落下一团烈焰，“轰”的一声炸开，原来是"+me->name()+HIR"。\n\n"NOR,environment(me),({me}));
        tell_object(me,HIC"\n你借「火遁咒」回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：火遁咒
        法术所属：平天大法
        法术效果：返回师门
        	  战斗中不能使用
        	  冷却时间1分钟
        法术条件：
                  火云洞弟子
        	  人物等级5级
                  法力100点，消耗50点
                  
STR;
        me->start_more(str);
        return 1;
}