// 天女散花 Flower.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

string *pfm_msg =
({
        HIM "\n$N微微一笑，「天女散花」第一重"+HIG"飞花逐月"NOR+HIM"转瞬而出，身子凌空而起，犹如飞花逐月。",
        HIM "\n$N微微一笑，身子凌空而起，「天女散花」第二重"+HIG"漫天花雨"NOR+HIM"转瞬而出，一时花雨纷飞。",
        HIM "\n$N微微一笑，身子凌空而起，最高重的「"+HIG"天女散花"NOR+HIM"」转瞬而出，一时花香缭绕。",
});

int valid_perform(object me)
{
	if( me->query_level()<5 )
		return notify_fail("你的人物等级不够。\n");                
        if( (int)me->query("force")<30 )
                return notify_fail("你的内力不够！\n");
        if( (int)me->query_skill("baihua-zhang", 1)<50 )
                return notify_fail("你的百花掌级别还不够！\n");
        if( time()-(int)me->query_temp("flower_end") < 5 )
                return notify_fail("绝招用多就不灵了！\n");
	return 1;
}

int perform(object me, object target)
{
        string succ_msg,msg,str,type="";
        int i,ch;
        int damage, s_num;
        
	if( !valid_perform(me) )
		return 0;
        
        if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || target->is_corpse()
         || !me->is_fighting(target) )
                return notify_fail("你要对谁施展这一招？\n");
        ch = me->is_knowing("moon_flower");
        if( ch < 1 ) ch = 1;
        if( ch>3 )  ch=3;
        me->add("force", -10);
        me->set_temp("flower_end",time());
        me->set_temp("pfm_msg",1);
	s_num = me->query_skill("baihua-zhang",1)/10+ch*5; 
	succ_msg = HIR "这些花瓣看似柔弱无力，却如疾风骤雨般射向$n,"+HIR+chinese_number(s_num)+HIR"片花瓣深深的嵌入$n"HIR"肉里！\n" NOR;
        
        for(i=0;i<ch;i++)
        {
		msg = pfm_msg[i] + HIM "$n只觉眼前一花，一时竟然不知如何招架，更不用说躲闪了！\n\n" NOR;
		damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,(i+1)*50);
	        if( damage<=0 )
			message_vision(HIG"谁知$n"HIG"竟险中求胜，长袖一摆，已将所有花瓣打落！\n"NOR,me,target); 
	}		
        me->set_temp("pfm_msg",0);
        if( (random(200)>190 || wizardp(me) ) && ch<3 && (me->query("family/family_name") == "月宫") )
        {
        	if( (int)me->query_skill("baihua-zhang", 1)>=100 && ch<2 )
        	{
        		ch = 2;
                	me->set_knowing("moon_flower",ch);
                	tell_object(me,HIR"你心中豁然贯通，领悟到了第"+chinese_number(ch)+"重「天女散花」的用法！\n"NOR);
		}        		
        	else if( (int)me->query_skill("baihua-zhang", 1)>=200 && ch<3 )
        	{
                	ch = 3;
                	me->set_knowing("moon_flower",ch);
                	tell_object(me,HIR"你心中豁然贯通，领悟到了第"+chinese_number(ch)+"重「天女散花」的用法！\n"NOR);
		}                	
        }
        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：天女散花
        外功所属：百 花 掌
        外功效果：凝气以成花攻击对手，共三重。花气越多伤害越大。
                  使用后冷却5秒
        外功条件：
        	  人物等级 5 级
                  内力30点，消耗10点
                  百 花 掌 50 级
STR;
        me->start_more(str);
        return 1;
}
