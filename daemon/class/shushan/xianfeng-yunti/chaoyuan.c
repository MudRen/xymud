//by greenwc 2000.11
#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int c_dmg,int s_dmg,int c_def,int s_def,int hp)
{
	if( !me )
		return;
        me->add_temp("apply/combat_damage",-c_dmg);
	me->add_temp("apply/spells_damage",-s_dmg);
	me->add_temp("apply/combat_def",-c_def);
	me->add_temp("apply/spells_def",-s_def);
	me->add_temp("apply/max_kee",-hp);
	me->add_temp("apply/max_sen",-hp);
	me->delete_temp("shushan_chaoyuan");
	message_vision("$N收起了「五气朝元」。\n"NOR,me);
}			

int exert(object me, object target)
{
	string clr;
	int i,p,p2,t,skill,c_dmg,s_dmg,c_def,s_def,hp;
	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");      
        if(me->query("family/family_name")!="蜀山派")
      		return notify_fail("你不是蜀山弟子，不能使用这项技能！\n");
      	skill = me->query_skill("xianfeng-yunti",1);	
      	if( skill<150 )
      		return notify_fail("你的「仙风云体术」修为太差。\n");	
        if( (int)me->query("force") < 300 )     
                return notify_fail("你的内力不够。\n");
	if( me->query_temp("shushan_chaoyuan") )
		return notify_fail("你已经施展了五气朝元。\n");

	i = (skill-150)/100+1;
	if( i>5 )
		i = 5;
        t = (skill-150)/60+15;   
	p = (skill-150)/100+50;
	p2 = (skill-150)/60+50;
	me->set_temp("shushan_chaoyuan",i);
	if( i==1 )
	{
		c_dmg = p;
		hp = c_def = s_dmg = s_def = 0;
		clr = HIY;
	}
	else if( i==2 )
	{
		c_dmg = p;
		c_def = p;	
		hp = s_dmg = s_def = 0;
		clr = HIC;
	}
	else if( i==3 )
	{
		c_dmg = p;
		c_def = p;
		hp = p2;	
		s_dmg = s_def = 0;
		clr = HIG;
	}
	else if( i==4 )
	{
		c_dmg = p;
		c_def = p;
		hp = p2;	
		s_dmg = p;
		s_def = 0;
		clr = HIM;
	}
	else
	{
		c_dmg = p;
		c_def = p;
		hp = p2;	
		s_dmg = p;
		s_def = p;
		clr = HIW;
	}

	message_vision(clr+"$N"+clr+"体内仙风云体术运转，顿时有"+chinese_number(i)+"股真气运行周天，整个人的气势也变得磅礴起来！\n"NOR,me);
	me->add("force", -150);
	me->add_temp("apply/combat_damage",c_dmg);
	me->add_temp("apply/spells_damage",s_dmg);
	me->add_temp("apply/combat_def",c_def);
	me->add_temp("apply/spells_def",s_def);
	me->add_temp("apply/max_kee",hp);
	me->add_temp("apply/max_sen",hp);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, c_dmg,s_dmg,c_def,s_def,hp :),t);
        if( me->is_fighting() ) 
        	me->start_busy(3);
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        内功名称：五气朝元
        内功所属：仙风云体术
        内功效果：一定时间提升自己的战斗系数
         	  随着仙风云体术等级提升，提升项也增多
                  战斗中使用自身busy 3 秒
        内功条件：
                  蜀山派弟子
        	  人物等级15级	
                  内力300点，消耗150点
                  仙风云体术150级
LONG;
me->start_more(str);
return 1;
} 
