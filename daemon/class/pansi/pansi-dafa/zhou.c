// 清心普善咒
// 专解情毒，这么好，什么时候帮我也解解，呵呵
// xintai 2/3/2001
#include <ansi.h>

int cast(object me, object target)
{
        int i,flag=0;
        object *inv;
        
        if( me->query_level()<35 )
		return notify_fail("你的人物等级不够。\n");
        if( me->is_fighting() )
                return notify_fail("战斗中无法解毒！\n");
        if( !me->is_knowing("psd_zhou") )
                return notify_fail("你还没有学会清心普善咒。\n");
        if( (int)me->query("mana")  <  800 )
                return notify_fail("你的法力不够。\n");
	if( (int)me->query_skill("pansi-dafa") < 350)
                return notify_fail("你的盘丝大法等级不够，不要勉强啦！\n");
                        
        inv = all_inventory(environment(me));
        for(i=0;i<sizeof(inv);i++)
        {
                target = inv[i];
                if( !target || target->is_fighting()
                 || !living(target) )
                        continue;
                if( !target->query_condition("xiangsi") )
                        continue;
                if( me->query("mana")<100 )
                {
                        tell_object(me,"你的法力不足了。\n");
                        break;
                }                                        
                message_vision(HIW"\n$N"HIW"运起清心普善咒，将$n"HIW"身上的相思之毒解去了。\n\n"NOR,me,target);
                target->apply_condition("xiangsi",0);
                me->add("mana", -100);
        }
        me->start_busy(1);       
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：清心普善咒
        法术所属：盘丝大法
        法术效果：解除当前场景中所有非战斗状态者所中的相思之毒
                  每治疗一位，法力消耗100点
		  自身busy 1 秒
		  需领悟 
        法术条件：
        	  人物等级35级
                  法力800点
                  盘丝大法350级
                  
STR;
        me->start_more(str);
        return 1;
}