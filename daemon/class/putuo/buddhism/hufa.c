// invocation.c

inherit SSERVER;

int cast(object me, object target)
{       
        object soldier;

        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能召唤护法！\n");
	if(me->query("family/family_name") != "南海普陀山" )
        	return notify_fail("这是普陀不传之密！\n");
	if( me->query_level()<30 )
		return notify_fail("你的人物等级不够。\n");        
        if( objectp(me->query_temp("invocation")) )
                return notify_fail("你刚叫过天将，他们都被你叫烦了！\n");
        if( (int)me->query("mana") < 150 )
                return notify_fail("你的法力不够了！\n");
        if( (int)me->query("sen") < 80 )
                return notify_fail("你的精神无法集中！\n");
	if( me->query_skill("buddhism",1)<200 )
		return notify_fail("你的大乘佛法等级不够。\n");
        message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -100);
        me->receive_damage("sen", 50);

        if( random(me->query("max_mana")) < 250 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }

        seteuid(getuid());
        soldier = new("/d/nanhai/npc/hufa");
        if( !soldier->invocation(me) ){
                message("vision", "但是什么也没有发生。\n",environment(me));
                if( soldier ) destruct(soldier);
                return 1;
        }
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：召唤护法
        法术所属：大乘佛法
        法术效果：召唤一位护法与自己并肩作战
        	  战斗中护法能替召唤者抵挡部分伤害
                  当召唤者离线或昏迷，护法会消失
		  当召唤者法力小于10时，护法会消失
		  护法会持续消耗召唤者的法力
        法术条件：
                  普陀弟子
        	  人物等级30级
                  法力150点，消耗100点，护法存在期间会持续消耗法力
                  精神80点，消耗50点
                  大乘佛法 200 级
                  
STR;
        me->start_more(str);
        return 1;
}