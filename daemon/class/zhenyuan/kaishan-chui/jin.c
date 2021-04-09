#include <ansi.h>
#include <combat.h>
inherit SSERVER;
inherit F_CLEAN_UP;

void remove_effect(object target,int p)
{
	int t1,t2;
	if( target )
	{
		target->delete_temp("powerup");
		target->add_temp("apply/combat_def",-p);
	
		t1 = target->query_maxkee()-target->query("eff_kee");
		t2 = target->query("eff_kee")-target->query("kee");
		target->add_temp("apply/max_kee",-p*5);
		target->add("eff_kee",-p*5-t1);
		if( target->query("eff_kee")>target->query_maxkee() )
			target->set("eff_kee",target->query_maxkee());
		target->add("kee",-p*5-t2);
		if( target->query("kee")>target->query("eff_kee") )
			target->set("kee",target->query("eff_kee"));
		if( target->query("kee")<0 )
			target->set("kee",0);
		if( target->query("eff_kee")<0 )
			target->set("eff_kee",0);
		message_vision("$N身上的金光渐渐散去。\n",target);		
	}
}

int perform(object me, object target)
{
	object weapon;
        string msg;
        int p,t1,t2;

	if( me->query_level()<20 )
		return notify_fail("你的人物等级不够。\n");
        if(me->query("family/family_name")!="五庄观")
                return notify_fail("「金骨炼真」只有五庄观门人才可以用！\n");
        if(me->query_skill("kaishan-chui",1) < 200)
                return notify_fail("你的开山锤还不够纯熟。\n");
        if((int)me->query("force") < 800 )
                return notify_fail("你的内力不够！\n");
	if( me->query("kee")<300 )
		return notify_fail("你现在体力不支。\n");  
	if( time()<me->query_temp("wzg_jin")+60 )
		return notify_fail("「金骨炼真」不能频繁使用。\n");
				              
	if( !target )
		target = me;
	if( target!=me )
	{
		if( !me->is_knowing("wzg_jin") && userp(me) && !wizardp(me) )
			return notify_fail("你尚未领悟开山锤的真谛。\n");
		if( me->is_fighting(target)
		 || target->is_fighting()
		 || !living(target) )
		 	return notify_fail("这合适吗？\n");
	}
	if( target->query_temp("powerup") )
		return notify_fail((target==me?"你":"对方")+"身上有其他效果。\n");	
	
	weapon = me->query_temp("weapon");
        if( !weapon 
	 || (weapon->query("skill_type")!="hammer"
	  && weapon->query("use_apply_skill")!="hammer") )
		return notify_fail("你的锤子呢？\n"); 	  
		
	msg = HIR"$N"HIR"咬破舌尖，吐了一口鲜血在"+weapon->name()+HIR"上！\n"NOR;
	if( me!=target )
		msg+= HIY"$N"HIY"将"+weapon->name()+HIY"朝$n"HIY"一指，"NOR;	
	if( me==target )
		msg+= HIY"顿时$N"HIY"全身笼罩住一道金光，恍如天神一般！\n"NOR;
	else	msg+= HIY"顿时$n"HIY"全身笼罩住一道金光，恍如天神一般！\n"NOR;
	if( me!=target )
		message_vision(msg,me,target);
	else	message_vision(msg,target);
	me->add("force",-200);
	me->receive_damage("kee", 200,me);
	
	p = me->query_skill("spells");
	p+= me->query_skill("hammer");
	p/= 10;
	p+= 1;
	
	target->set_temp("powerup","wzg_jin");
	target->add_temp("apply/combat_def",p);
	
	t1 = target->query_maxkee()-target->query("eff_kee");
	t2 = target->query("eff_kee")-target->query("kee");
	target->add_temp("apply/max_kee",p*5);
	target->add("eff_kee",p*5-t1);
	if( target->query("eff_kee")>target->query_maxkee() )
		target->set("eff_kee",target->query_maxkee());
	target->add("kee",p*5-t2);
	if( target->query("kee")>target->query("eff_kee") )
		target->set("kee",target->query("eff_kee"));
	target->start_call_out( (: call_other, __FILE__, "remove_effect", target,p:), me->query_skill("hammer")/10);
	if( me->is_fighting() )
		me->start_busy(2);		
        return 1;
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：金骨炼真
        外功所属：开山锤
        外功效果：使对象在一段时间内提高气血上限和物理防御
        	  不能与其他增益性状态叠加
        	  对他人使用需领悟
                  战斗中使用自身busy 2 秒
                  冷却时间1分钟
        外功条件：
                  五庄观弟子
                  人物等级20级
                  内力800点，消耗200点
                  气血300点，消耗200点
                  开山锤200级
                  
LONG;
me->start_more(str);
return 1;
}

