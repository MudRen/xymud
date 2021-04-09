// invocation.c

inherit SSERVER;

int cast(object me, object target)
{       
        object soldier;

        if( !me->is_fighting() )
                return notify_fail("只有战斗中才能召唤护法！\n");
	if(me->query("family/family_name") != "阎罗地府")
        	return notify_fail("这是地府不传之密！\n");
	if( me->query_level()<8 )
		return notify_fail("你的人物等级不够。\n");        
        if( objectp(me->query_temp("invocation")) )
                return notify_fail("你刚叫过护法，他们都被你叫烦了！\n");
        if( (int)me->query("mana") < 100 )
                return notify_fail("你的法力不够了！\n");
        if( (int)me->query("sen") < 50 )
                return notify_fail("你的精神无法集中！\n");
	if( me->query_skill("gouhunshu",1)<60 )
		return notify_fail("你的勾魂术等级不够。\n");
        message_vision("$N喃喃地念了几句咒语。\n", me);
        me->add("mana", -30);
        me->receive_damage("sen", 20);

        if( random(me->query("max_mana"))<200 ) 
        {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }

        seteuid(getuid());
        soldier = new("/d/death/npc/hufa");
        if( !soldier->invocation(me) )
        {
                message("vision", "但是什么也没有发生。\n",environment(me));
                if( soldier ) destruct(soldier);
                return 1;
        }
        return 5;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：召唤鬼卒
        法术所属：勾魂术
        法术效果：召唤一位鬼卒跟随自己，并可能随时为自己治疗
                  当召唤者离线或昏迷，护法会消失
		  当召唤者法力小于10时，护法会消失
		  护法会持续消耗召唤者的法力
        法术条件：
                  地府弟子
        	  人物等级8级
                  法力100点，消耗30点，护法存在期间会持续消耗法力
                  精神50点，消耗20点
                  勾魂术 60 级
                  
STR;
        me->start_more(str);
        return 1;
}