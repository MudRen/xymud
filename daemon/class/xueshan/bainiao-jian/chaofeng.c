//chaofeng.c
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int valid_perform(object me)
{
	if( me->query_level()<10 )
		return notify_fail("你的人物等级不够。\n");
	if(me->query("family/family_name")!="大雪山")
    		return notify_fail("「百鸟朝凤」只有雪山弟子才可以用！\n"); 
	if(me->query_skill_mapped("force")!="ningxie-force")
	        return notify_fail("必须配合冰谷凝血功才能使用。\n");
	if(me->query("force")<200)
    		return notify_fail("你内力不继，难以御剑飞针。\n");   
	if((int)me->query_skill("sword", 1)<100 )
		return notify_fail("你的剑法底子太差。\n");
	if( (int)me->query_skill("bainiao-jian", 1)<100 )
		return notify_fail("你的百鸟剑法不够熟练。\n");
	if( (int)me->query_skill("throwing", 1)<100 )
		return notify_fail("你剑中打暗器的功夫还不到火候！\n");
	return 1;
}	

int perform(object me, object target)
{
	object weapon;
	string msg,anqi_type,b_unit,succ_msg;
	int i,req,num_anqi,num_hit,max_hit,hitt,damage,op,opfa,remain,scc=0;
	int wound=0;
	
	if( !valid_perform(me) )
		return 0;
	if(time()<(me->query_temp("xueshan_chaofeng")+5)) 
		return notify_fail("出奇才能制胜，百鸟朝凤多使就不灵了。\n");
		
	if( !target ) target = offensive_target(me);
	if( !target
 	 || !target->is_character()
 	 || target->is_corpse()
 	 || target==me
 	 || !me->is_fighting(target) )
		return notify_fail("你要攻击谁？\n");
				
	weapon = me->query_temp("weapon");
	req = ((int)me->query_skill("sword", 1)+(int)me->query_skill("bainiao-jian", 1)+(int)me->query_skill("throwing", 1))/3; 
	if( weapon )  
    	{
    		if(weapon->query("anqi/allow") != 1) 
    			num_anqi=0;
		else	num_anqi=weapon->query("anqi/now");
	}
    	
	if(num_anqi <=0) 
	{ 
    		anqi_type="剑气"; 
		damage = me->query("force_factor")/3+1; 
	}
	else if(req < 150)
    	{ 
    		anqi_type=weapon->query("anqi/type"); 
		damage=me->query("force_factor")/3+1+me->query_skill("throwing", 1)/5; 
	}
	else    
	{ 
    		anqi_type=weapon->query("anqi/type")+"加着剑气";
		damage=me->query("force_factor")/3+1+me->query_skill("throwing", 1)/5+(int)me->query_skill("sword")/5; 
	}
	if(num_anqi > 10 || num_anqi == 0) 
    		max_hit=10;
	else 	max_hit=weapon->query("anqi/now");
	num_hit=random(max_hit/2)+(max_hit/2);
	hitt=0; 
	for(i=1;i<num_hit;i++)  
    	{
    		if( random(me->query_level())>target->query_level()/3 )
        		hitt++;
	}	
	if(weapon->query("anqi/type")=="孔雀翎") 
	{
    		b_unit="支";
    		hitt++;
    	}
	else    b_unit="根";
	damage+= 5*hitt;	
	succ_msg = HIW "$n"HIW"躲闪不及，身上"+chinese_number(hitt)+HIW "处中了"+anqi_type+"！\n"NOR;
	succ_msg+= HIW "$n"HIW"对着$N"HIW"高声骂道：好啊，敢放暗器，看"+RANK_D->query_self_rude(me)+"怎么收拾你！\n" NOR;
	msg = HIW"只见$N"HIW"手中$w"HIW"急颤，幻出满天剑芒，无数"+anqi_type+HIW"有如百鸟投林般向$n"HIW"扑来！\n" NOR;
	
	me->set_temp("xueshan_chaofeng",time());
	me->add("force", -100);
	me->set_temp("pfm_msg",1);
	me->add_temp("apply/attack",req);
	me->set_temp("fengwu",1);
	damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg,0,damage);
	me->add_temp("apply/attack",-req);
	me->set_temp("pfm_msg",0);
	me->delete_temp("fengwu");
	
	if( damage<1 )
	{
		message_combatd(HIW "$n"HIW"连忙身行一转，连退数步，闪过了这满天花雨般的一击。\n"NOR, me, target);
		me->add_temp("xueshan_chaofeng",1);
	}
	else
	{
	        if(!target->is_busy())
			target->start_busy(1+random(3));
	}
	if(weapon->query("anqi/now")>0) 
    		remain=weapon->query("anqi/now")-num_hit;
	else   	remain=0;
	if( remain<0 )
		remain = 0;
	weapon->set("anqi/now",remain);
	if(weapon->query("anqi/now") == 0) 
    	{
    		weapon->delete("anqi/type");  
		weapon->set("long",weapon->query("orilong"));
	}
	else    weapon->set("long",weapon->query("orilong")+"里面已经装了"+chinese_number(weapon->query("anqi/now"))+b_unit+weapon->query("anqi/type")+"，想拆掉用uninstall。\n"); 
	if( !target->is_killing(me->query("id")) )
		target->kill_ob(me);
	return 1;
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        外功名称：百鸟朝凤
        外功所属：百鸟剑法
        外功效果：对敌进行带固定伤害的攻击，当武器中装备有暗器时，伤害更高
                  冷却时间5秒，不中则增加 1 秒
        外功条件：
                  雪山弟子
        	  人物等级 10 级
                  内力200点，消耗100点
                  内功激发冰谷凝血功
                  百鸟剑法 100 级
                  暗器使用 100 级
                  基本剑术 100 级
STR;
        me->start_more(str);
        return 1;
}