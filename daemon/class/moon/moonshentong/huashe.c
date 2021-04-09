#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void remove_effect(object me,int p)
{
	if( !me )
		return;
	me->delete_temp("is_living");
	me->delete_temp("unit");
	me->delete_temp("is_character");
	me->delete_temp("gender");
	me->delete_temp("age");
	me->delete_temp("spellslevel");
	me->delete_temp("apply/short");
	me->delete_temp("apply/long");
	me->set_temp("moon_huashe",time());
	me->delete_temp("moon_huashen");
	me->delete_temp("no_heal_up/bian",1);
	me->delete_temp("no_bian");
	me->delete_temp("d_mana");
	me->delete_temp("apply/limbs");
	me->add_temp("apply/combat_damage",-p);
	me->add_temp("apply/spells_damage",-p);
	message_vision(HIC"\n$N"HIC"浑身仙气渐渐淡出，晃了几晃，显了真身。\n"NOR,me);	
}

int cast(object me, object target)
{
        string msg,*limbs;
        int spells,num,howlong,p,i;

	if(me->query("family/family_name") != "月宫")
		return notify_fail("「太阴·化蛇」是月宫不传之密！\n");
	if( me->query_level()<50 )
		return notify_fail("你的人物等级不够。\n");
        if((int)me->query("mana") < 1000 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query_skill("spells") < 750 )
                return notify_fail("你的法术修为太差。\n");
	if( me->query("daoxing")<250000 )
		return notify_fail("你的道行还没到"+RANK_D->describe_dx(250000)+"的境界。\n");
	if( me->query_temp("moon_huashen") )
		return notify_fail("你已施展了太阴化身咒。\n");
	if( time()<me->query_temp("moon_huashe")+10 )
		return notify_fail("你不能频繁化蛇。\n");
	if( me->query_temp("d_mana") )
		return notify_fail("你施展了变化之术，还是先还了真身。\n");
	
	spells = me->query_skill("spells");
	num = spells/250;
	if( num>9 )
		num = 9;
	if( num<3 )
		num = 3;
	msg = HIM"\n$N"HIM"妩媚一笑，低头念了几句咒语，但见背后月华之气大胜。一道太阴之气从天而降，光华一闪，$N"HIM"顿时化作"+chinese_number(num)+"丈多长的巨蛇。\n"NOR;
	message_vision(msg,me);
	me->add("mana",-300);
	me->set_temp("is_living",1);
	me->set_temp("unit","只");
	me->set_temp("is_character",1);
	me->set_temp("gender","女性");
	me->set_temp("age",18);
	me->set_temp("spellslevel",spells);
	me->set_temp("apply/short", ({me->short()+HIC"(化蛇)"NOR}));
	me->set_temp("apply/long", ({me->name()+"变化的长蛇，浑身仙气弥漫，传出股股幽香。\n"}));
	me->set_temp("moon_huashen","hu");
	me->set_temp("no_heal_up/bian",1);
	me->set_temp("no_bian",1);
	me->set_temp("d_mana",1);

	limbs = ({
		"头部", "颈部", "胸口", "后心", "腰间", "小腹", "尾巴", "尾巴",
                "尾巴", "尾巴",
	});
	me->set_temp("apply/limbs",limbs);
	
	p = me->query_skill("moonshentong",1)/2;
	
	me->add_temp("apply/combat_damage",p);
	me->add_temp("apply/spells_damage",p);
	
	howlong = spells/6+random(spells/6);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, p:), howlong);

        return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：太阴·化蛇
        法术所属：月宫仙法
        法术效果：化身仙狐，一定时间内增加物理、法术攻击
        	  此状态下绝情鞭攻击加倍
		  状态结束后冷却10秒
        法术条件：
                  月宫弟子
        	  人物等级50级
                  法力1000点，消耗300点
                  道行二百五十年
                  有效法术 750 级
                  
STR;
        me->start_more(str);
        return 1;
}