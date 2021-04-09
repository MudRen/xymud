// 无边地狱&&十万诸魔 Diyu.c
// Last updated by 凌惊雪 12-14-2002
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg,succ_msg;
	int damage,t,p;
	object weapon;
	
	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n"); 
	if( (int)me->query("force") < 600 )
 		return notify_fail("你内力不够，无力出招！\n");
	if( me->query_skill("force",1)<200 )
		return notify_fail("你内功修为太差。\n");
	if(me->query_skill("kugu-blade",1)<200) 
		return notify_fail("你刀法修为太差。\n");
	if(me->query_skill("blade",1)<200) 
 		return notify_fail("你的刀法基本功太差。\n");

 	weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )	
		return notify_fail("你手里头木有刀。\n");
		 			
	if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
     		return notify_fail("你要对谁施展这一招？\n");

    	p = me->query_skill("blade")/10;
    	if( weapon->query("id")=="kugu dao" )
    		p+= 30;
    	if( me->query("family/family_name")=="陷空山无底洞" )
    		p = p*3/2;
    		
    	msg = HIM"「$N"HIM"「凝聚起天地间十万妖魔的无边力量，神气贯通，一式十万诸魔急如闪电，一气呵成！\n" NOR;
	message_vision(msg, me, target);
    	me->add_temp("apply/attack", p);
    	me->add("force", -200);
	me->set("pfm_color",RED);
	t = 1;
	msg = HIM"「万魔初醒」"NOR"\n";
	COMBAT_D->do_attack(me,target, weapon, TYPE_QUICK,msg,0,0,me->query_skill("kugu-blade",1)/3);

	msg = HIM"\n「魔光乍现」"NOR"\n";
	COMBAT_D->do_attack(me,target, weapon, TYPE_QUICK,msg,0,0,me->query_skill("kugu-blade",1)/3);

	msg = HIM"\n「魔焰万丈」"NOR"\n";
	COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg);
	t++;
	
	
	if( me->is_knowing("wdd_diyu")>=1 || wizardp(me) || (!userp(me) && me->query_skill("kugu-blade",1)>150) )
	{
		msg = HIM"\n「万刃天魔」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("kugu-blade",1)/2);
	}	
	if( me->is_knowing("wdd_diyu")>=2 || wizardp(me) || (!userp(me) && me->query_skill("kugu-blade",1)>250) )
	{
		msg = HIM"\n「独尊地魔」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("kugu-blade",1)/2);
	}			
	if( me->is_knowing("wdd_diyu")>=3 || wizardp(me) || (!userp(me) && me->query_skill("kugu-blade",1)>350) )
	{
		msg = HIM"\n「如意人魔」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("kugu-blade",1));
		t++;		
	}

	if( me->is_knowing("wdd_diyu")>=4 || wizardp(me) )
	{
		msg = HIM"\n「不食不寝不息  风雨是谒」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("blade")/2);
	}

	if( me->is_knowing("wdd_diyu")>=5 || wizardp(me) )
	{
		msg = HIM"\n「形方如肉柜  浑浑而行  所过处草木尽枯」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("blade"));
	}	

	if( me->is_knowing("wdd_diyu")>=6 || wizardp(me)  )
	{
		msg = HIM"\n「窜三苗于三危  殛鲧于羽山  四罪而天下咸服」"NOR"\n";
		COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("blade"));
		t++;
	}

	msg = HIR"十万诸魔齐在云端隐现，$N"HIR"手中$w"HIR"鬼神莫测，已然割向$n"HIR"的$l！\n" NOR;
	me->set_temp("pfm_color",HIR);
	me->set_temp("pfm_msg",1);
	COMBAT_D->do_attack(me,target, weapon, TYPE_PERFORM,msg,0,0,me->query_skill("blade"));
	me->delete_temp("pfm_color");	
	me->delete_temp("pfm_msg");
	
	me->add_temp("apply/attack", -p);
	me->start_busy(t);
	return 1;
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
              外功名称：无边地狱
              外功所属：枯骨刀法 
              外功效果：对敌进行连续的固定伤害递增的物理攻击
                        最多10击，中间6击需领悟
                        使用枯骨刀，命中增加
                        自身busy 2 秒
                        若领悟了3击，则busy 3 秒
                        若领悟了6击，则busy 4 秒
                        40级方可领悟
              外功条件：
			人物等级20级
			内力600点，消耗200点
			基本内功200级
			基本刀法200级
			枯骨刀法200级 
LONG;
me->start_more(str);
return 1;
}
