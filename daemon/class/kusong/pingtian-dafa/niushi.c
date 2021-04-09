// invocation.c
inherit SSERVER;

int valid_cast(object me)
{
	if(me->query("family/family_name") != "火云洞")
        	return notify_fail("这是火云洞不传之密！\n");
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");        
	if( me->query_skill("pingtian-dafa",1)<300 )
		return notify_fail("你的平天大法等级不够。\n");	
        if( (int)me->query("mana") < 150 )
                return notify_fail("你的法力不够了！\n");
        if( (int)me->query("sen") < 80 )
                return notify_fail("你的精神无法集中！\n");
	return 1;
}	

int cast(object me, object target)
{       
        object soldier;

	if( !valid_cast(me) )
		return 0;
		
        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能召唤护法！\n");
        if( objectp(me->query_temp("invocation")) )
                return notify_fail("你刚叫过护法，他们都被你叫烦了！\n");
	if( time()<me->query_temp("last_invocation")+15 )
		return notify_fail("你刚叫过护法，他们都被你叫烦了！\n");	                
        message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -100);
        me->receive_damage("sen", 50);

        if( random(me->query_maxmana()) < 250 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }

        seteuid(getuid());
        soldier = new("/d/qujing/kusong/npc/niushi.c");
        if( !soldier->invocation(me) ){
                message("vision", "但是什么也没有发生。\n",environment(me));
                if( soldier ) destruct(soldier);
                return 1;
        }
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：召唤牛虱
        法术所属：平天大法
        法术效果：召唤一位牛虱与自己并肩作战
                  当召唤者离线或昏迷，牛虱会消失
		  当召唤者法力小于10时，牛虱会消失
		  牛虱会持续消耗召唤者的法力
		  牛虱会将对敌伤害的1/10用于恢复或治疗召唤者的气血
		  当治疗成功，牛虱会加快消失时间
		  牛虱消失后冷却15秒
        法术条件：
                  火云洞弟子
        	  人物等级30级
                  法力150点，消耗100点，护法存在期间会持续消耗法力
                  精神80点，消耗50点
                  平天大法 300 级
                  
STR;
        me->start_more(str);
        return 1;
}