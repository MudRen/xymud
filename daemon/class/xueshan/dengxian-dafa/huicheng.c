#include <ansi.h>
inherit SSERVER;

int valid_cast(object me)
{
	int t = me->query_skill("jiefeng",1);
	if( (string)me->query("family/family_name") != "大雪山" )
		return notify_fail("你并非雪山弟子，变不了妖身。\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");
	t = 60-t/30;
	if( t>3 )
		t = 3;
	if( time()<me->query_temp("last_huicheng")+t )
		return notify_fail("你刚刚变过妖身。\n");
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
	i = me->query_skill("buddhism",1);
	i/= 15;
	if( i<1 ) i = 1;
	if( i>9 ) i = 9;
	switch(i)
	{
		case 1 : str = "扁头麻雀";break;
		case 2 : str = "黄鹂鸟";break;
		case 3 : str = "红冠鹦鹉";break;
		case 4 : str = "白鹭";break;
		case 5 : str = "丹顶鹤";break;
		case 6 : str = "长尾孔雀";break;
		case 7 : str = "碧眼金雕";break;
		case 8 : str = "金翅大鹏";break;
		default : str = "半天鲲鹏";break;
	}			
        message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -50);
        if( random(me->query("max_mana")) < 20 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }
	message_vision(YEL"只见$N"YEL"摇身一变，化作一只"+str+"径直朝大雪山方向而去！\n"NOR,me);
	me->set_temp("last_huicheng",time());
        if( me->is_fighting() )
        	me->start_busy(5);
        me->move("/d/xueshan/wuchang-c",2);
        message("vision",YEL"\n\n天空中落下一只"+str+"，就地滚了一滚，原来是"+me->name()+YEL"。\n\n"NOR,environment(me),({me}));
        tell_object(me,HIC"\n你借妖身回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：鹏程万里
        法术所属：登仙大法
        法术效果：返回师门
        	  战斗中不能使用
        	  冷却时间1分钟
        法术条件：
                  雪山弟子
        	  人物等级5级
                  法力100点，消耗50点
                  
STR;
        me->start_more(str);
        return 1;
}