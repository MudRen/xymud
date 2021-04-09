#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
    	object weapon;
    	int j,skill,dodge;
    	string msg,limb;

	if( me->query_level()<60 )
		return notify_fail("你的人物等级不够。\n");
	if( (userp(me)&&!wizardp(me)) && me->is_knowing("puti_panlong")!="succ" )
		return notify_fail("你还不会这一招。\n");
	if( me->query("family/family_name") != "方寸山三星洞" )
        		return notify_fail("你是哪儿偷学来的武功，也想用「盘龙八式」?\n");
	if( !target ) target = offensive_target(me);
    	if( !target || target->is_ghost()
    	 || !target->is_character()
    	 || !me->is_fighting(target) )
		return notify_fail("「盘龙八式」只能在战斗中使用。\n");
	if( !weapon=me->query_temp("weapon")
	 || ( weapon->query("skill_type")!="stick"
	   && weapon->query("use_apply_skill")!="stick" ) )
		return notify_fail("「盘龙八式」必须用棍棒才能施展。\n");
	if( (int)me->query_skill("qianjun-bang", 1) < 600 )
		return notify_fail("你的「千钧棒」不够娴熟，不会使用「盘龙八打」。\n");
	if( (int)me->query("force") < 800  )
        	return notify_fail("你的内力不够。\n");
	if(time()-me->query_temp("pl_end")<10 ) 
		return notify_fail("你刚使出盘龙，突觉体力不够！\n");

    	if( target->query_temp("jldl") )
	{
		target->delete_temp("jldl");
        	target->set_temp("jldl_end", time() );
        	message_vision(HIY"\n$N"HIY"运起盘龙八式，面对强大的气劲，$n"HIY"的借力打力也失去了作用！\n\n"NOR,me,target);
	}
    
    	msg = HIC"$N"HIC"跳至空中，手中的"+weapon->name(1)+HIC"好似"+HIY"盘龙出沧海"+HIC"顿时化作无数条影子。\n"NOR;
    	message_vision(msg, me, weapon);
    	me->add_temp("apply/baoji",50);
    	me->set_temp("pl_end",time());
    	me->add("force", -300);
    	skill=me->query_skill("qianjun-bang",1);
    	dodge = (me->query_skill("dodge")+150)*2;
    	me->add_temp("apply/attack",dodge);
        me->set_temp("pfm_color",HIY);
        
        limb = ({"胸口","后心","小腹","颈部",})[random(4)];
        j = 1;
	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",10);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill/10);
     
	limb = ({"胸口","后心","小腹",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",20);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill/8);
    
	limb = ({"胸口","后心","小腹","腰间",})[random(4)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",30);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill/6);

	limb = ({"胸口","后心","小腹",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill/4);

	limb = ({"胸口","后心","小腹",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",40);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill/2);
	
	limb = ({"胸口","后心","小腹",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill);

	limb = ({"胸口","后心","小腹",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",50);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill*3/2);

	limb = ({"胸口","后心","头部",})[random(3)];
    	j+= 1;
    	msg = HIY"\n$N"HIY"身形如风，舞起手中$w"HIY"砸出了第"+chinese_number(j)+"棍！\n"NOR;
    	me->set_temp("QJB_perform", 7);
    	me->add_temp("anger",60);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_PERFORM,msg,0,limb,skill*5/4);

    	me->add_temp("apply/attack",-dodge);
    	me->add_temp("apply/baoji",-50);
   	me->delete_temp("pfm_color");
    	me->delete_temp("QJB_perform");
    	me->set_temp("anger",0);
    	me->start_busy(2);
    	return 1;
}