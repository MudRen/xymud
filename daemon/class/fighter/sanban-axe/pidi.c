//pidi
//辟地
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
	string msg,succ_msg,*limbs,ll;
    	int ap,dp,i,size,damage,t,f=0;
    	object my_w,target_w;
    	
    	if( me->query_level()<20 )
    		return notify_fail("你的人物等级不够。\n");
    	if( (int)me->query_skill("sanban-axe",1) < 200)
        	return notify_fail("你目前功力还使不出「辟地斩」。\n");
    	if( (int)me->query("force") < 100 )
        	return notify_fail("你的内力不够。\n");
	if( me->query("family/family_name")!="将军府" 
 	 && me->query("chushi/chushi_jjf")!="yes")
        	return notify_fail("你不能使用这项技能！\n");         	
    	my_w = me->query_temp("weapon");
    	if( !my_w
	 || ( my_w->query("skill_type")!="axe"
	   && my_w->query("use_apply_skill")!="axe" ) )		
        	return notify_fail("你的斧子呢？\n");
    
    	if( !target ) target = offensive_target(me);
	if( !target
 	|| !target->is_character()
 	|| target->is_corpse()
 	|| target==me
 	|| !me->is_fighting(target) )
                return notify_fail("你要对谁使用「辟地斩」。\n");
    
	target_w = target->query_temp("weapon");
        if( !target_w )
                target_w = target->query_temp("secondary_weapon");
        if( !target_w )
                target_w = 0;   
        if( target_w )
        {    
                msg = HIY"$N"HIY"突然暴吼一声：“我砸！我砸！我砸砸砸！”，手中$w"HIY"恶狠狠砸向$n"HIY"手中$W"HIY"！\n"NOR;
                succ_msg = HIW"结果$W"HIW"被砸个正着，顿时被砸成数段，并且受到$N"HIW"劲气激荡，向$n"HIW"迅速射去！\n"NOR;
        }
        else
	{
		msg = HIY"$N"HIY"突然暴吼一声：“我砸！我砸！我砸砸砸！”，手中$w"HIY"猛的砸向地面！\n"NOR;
		succ_msg = HIY"只见$w"HIY"上冒起腾腾劲气，化作道道金光向$n"HIY"迅速射去！\n"NOR;
	}	
        me->add("force", -100);
        me->set_temp("pfm_msg",1);
        damage = COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_PERFORM,msg,succ_msg);
        me->set_temp("pfm_msg",0);
        me->start_busy(4);
        if( damage<1 )
        {
        	message_combatd(HIC"可是$p急忙腾空闪开，并没有让$N"HIC"这招得逞。\n" NOR,me,target);
        	return 1;
        }
        
        
        if( target_w ) 
        {
        	f = 1;
        	target_w->unequip();
                if( !target_w->is_zhaohuan() )
                {
                	message_vision(HIY+target_w->name()+HIY"给砸成了一堆碎片！\n"NOR,me,target);
                        destruct(target_w);
                }
		else
     		{
     			message_vision(HIY+target_w->name()+HIY"给震得宝光黯淡！\n"NOR,me,target);
     			if( target_w->query("exp")>=500 )
     				target_w->add("exp",-500);
     			else
     			{
     				message_vision(HIY+target_w->name()+HIY"忽然变得死气灰暗，灵气全无！\n"NOR,me,target);
     				target_w->set("breaked",1);	
     			}
		}     				
                target->reset_action();
        }       

	limbs=target->query("limbs");
        size = (int)(me->query_skill("sanban-axe")/30);
        if( size>10 )
                size = 10;
        damage = damage/10+1;
	damage+= me->query_str()/3;
	for(i=0;i<=random(size);i++)
        {
        	ll = limbs[random(sizeof(limbs))];
                if( f>0 )
                	msg =CYN"“嗤”，一道碎片射入$p"+ll+"！";
		else	msg =CYN"“嗤”，一道劲气射入$p"+ll+"！";       
		msg+= COMBAT_D->damage_msg(damage,"刺伤")+NOR;  
                msg = replace_string(msg,"$l",ll);
                msg = replace_string(msg,"$w",f>0?"碎片":"劲气");
                message_combatd(msg,me,target);
                target->receive_damage("kee",damage,me,TYPE_PERFORM);
	}
        COMBAT_D->report_status(target);        
	return 1;
    
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：辟地斩
        外功所属：宣花三斧
        外功效果：对敌一击，造成对方武器的损耗甚至损坏
        	  (非绑定类武器将被销毁)
        	  (绑定类武器需修复后才能重新装备)
        	  使用后自身busy 4 秒
        外功条件：
                  将军府(出师)弟子
                  人物等级20级 
                  内力100点，消耗100点
                  宣花三斧200级
LONG;
me->start_more(str);
return 1;
}

