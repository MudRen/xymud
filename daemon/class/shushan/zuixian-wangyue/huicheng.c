#include <ansi.h>
inherit SSERVER;

int valid_perform(object me)
{
	int t = me->query_skill("jiefeng",1);
	if(me->query("family/family_name") != "蜀山派")
        	return notify_fail("这是蜀山派不传之密！\n");
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");        
        if( (int)me->query("force") < 100 )
                return notify_fail("你的内力不够了！\n");
	t = 60-t/30;
	if( t>3 )
		t = 3;
	if( time()<me->query_temp("last_huicheng")+t )
		return notify_fail("你刚刚金蝉脱壳过。\n");
	return 1;
}	

int perform(object me, object target)
{       
        object soldier;

	if( !valid_perform(me) )
		return 0;
	if( me->is_no_move() || me->is_fighting() )
		return notify_fail("你现在动弹不得。\n");
	if( environment(me)->query("no_huicheng") )
		return notify_fail("这里不能使用金蝉脱壳。\n");
					
        message_vision("$N暗运内功。\n", me);
        me->add("force", -50);

        if( random(me->query_maxforce()) < 20 ) {
                message("vision", "但是什么也没有发生。\n",environment(me));
                return 1;
        }
	message_vision(HIM"只见$N"HIM"浑身紫气氤氲，足下顿时生风如影，举步之间化作道道残影，一眨眼就无影无踪。\n"NOR,me);
	me->set_temp("last_huicheng",time());
        me->move("/d/shushan/paifang",2);
        message("vision",HIM"\n\n一道紫气腾腾的身影一闪，你眼前一花，不知何时"+me->name()+"已到了你的面前。\n"NOR,environment(me),({me}));
        tell_object(me,"你的身形一聚，再回首，已是万里开外。\n");
        tell_object(me,HIC"\n你借醉仙望月步法瞬回到了师门。\n"NOR);
        return 3;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：金蝉脱壳
        外功所属：醉仙望月步
        外功效果：返回师门
        	  战斗中不能使用
        	  冷却时间1分钟
        外功条件：
                  蜀山派弟子
        	  人物等级5级
                  内力100点，消耗50点
                  
STR;
        me->start_more(str);
        return 1;
}