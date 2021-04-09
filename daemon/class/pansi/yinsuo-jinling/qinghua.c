//windflower.c,盘丝情花阵
//created by foc,30-6-01
//edit by qingniu,2009
//特点说明：防御力与攻击力兼具的pfm
#include <ansi.h>
#include <combat.h> 
inherit SSERVER;

void remove_effect(object me, int damage); 
int perform(object me, object target)
{
        int damage, mywx, yourwx, yourskill, number, num, t;
              object weapon;
	string msg;
	return notify_fail("暂未开放。\n");
        if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || target->is_corpse()
         || target==me)
                return notify_fail("你要对谁使用「盘丝情花阵」？\n");
        if(!me->is_fighting(target))
                return notify_fail("只能在战斗中使用「盘丝情花阵」。\n");
        if( time()<me->query_temp("WF_busy")+5+random(10) )  //这里这么修改参照后面的说明
                return notify_fail("盘丝镇派绝学不可反复使用\n");
        if((int)me->query_skill("yinsuo-jinling",1)<100)
                return notify_fail("你的银索金铃等级不够。\n");
        if((int)me->query_skill("pansi-dafa",1)<100)
                return notify_fail("你的盘丝大法等级不够。\n");
        if((int)me->query_skill("whip",1)<100)
                return notify_fail("你的基本鞭法还不够纯熟。\n");
        if( userp(me) &&!me->query("pansi/zhenfa") )
                return notify_fail("你尚未参悟盘丝绝学，还是先向紫霞仙子问个端详吧。\n");
        if( !userp(me) && !me->query("任务") ) 
                return notify_fail("你尚未参悟盘丝绝学，还是先向紫霞仙子问个端详吧。\n");
   if((int)me->query("max_force")<2000 || (int)me->query("force")<1000 ) 
                return notify_fail("你的内力不足，怎么用这招？\n");
        if((int)me->query("max_mana")<1000 || (int)me->query("mana")<100)
                return notify_fail("使用这招需要一些法力，但是你的法力显然不足。\n");
        damage = (int)me->query_skill("whip",1) + (int)me->query_skill("yinsuo-jinling",1) + (int)me->query_skill("pansi-dafa",1) + (int)me->query_skill("jiuyin-xinjing",1) + (int)me->query_skill("force",1);
        damage-= target->query_temp("apply/armor");  //加上了对def的支持
        damage = COMBAT_D->valid_damage(me,target,damage);
        yourskill = (int)target->query_skill("parry",1) + (int)target->query_skill("dodge",1) + (int)target->query_skill("force",1);
        if(yourskill<1) yourskill=1;
        mywx=(int)me->query("combat_exp")/10000; //这里除以这个是为了防止wx高了，数据会爆 ,因为skills的支持，所以最低wx要求是100*100*10，所以mywx肯定够除
        yourwx=(int)target->query("combat_exp")/10000;
        msg = HIG"$N"HIG"将手中$w"HIG"一抛，那$w"HIG"居然围绕着$N"HIG"旋转起来。\n强大的妖气形成了如刀般的气流，四射而开。\n" NOR;
        weapon = me->query_temp("weapon"); //这个不加，weapon= ???
        msg = replace_string(msg,"$w",weapon->name()); 
        message_vision(msg,me,target);
        me->add("force",-100);
		if( mywx>yourwx*100 && damage>25 )
        {
                message_vision(HIR"结果$n"HIR"惨叫一声，身上已经被划出了几十道深可见骨的伤口。\n" NOR,me,target);
                tell_object (target, "看起来，对手太厉害了，快逃命吧！\n");
				target->receive_wound("kee",damage/5,me,TYPE_PERFORM);
                target->receive_damage("kee",damage/2,me,TYPE_PERFORM); //切记receive_damage receive_wound 必须要加上 伤害者，不然导致好多bug
                COMBAT_D->report_status(target,1); 
                COMBAT_D->report_status(target); 
                me->start_busy(2);
                tell_object(me,"对手太弱了，没必要用这么强的招式。\n");
                return 1;
        }
        message_combatd(HIM "$N"HIM"从头发里拿出一粒种子，运上妖力。那种子立刻变成了一朵漂亮的情花。\n" NOR,me,target);
        me->add("force",-50);
        message_combatd(HIR "$N"HIR"将那情花一甩，无数的花瓣从那情花上分出来，好象无穷无尽一般。\n" NOR,me,target);
        message_combatd(HIR "$N"HIR"大喝一声：“盘丝情花阵！”浑身的妖气发生了变化！\n" NOR,me,target);
        message_combatd(HIW "$N"HIW"的全身放出红色的妖气，旋转加剧，最后变成了围绕着$N"HIW"的白色气流，声势惊人。那些情花花瓣立刻随之旋转着四射而开，带着如刀般的锐利妖气袭向$n"HIW"！\n" NOR,me,target);
        me->add("force",-200);

        //伤害这么大，busy必中的话，不科学，尤其是普通NPC并不能使用这个pfm
        //如果想busy起作用，只能用加入busy就命中增加，但用必中是不合理的
        if( target->is_busy() )
                yourwx-= random(yourwx/3);
        if( random(mywx)>random(mywx+yourwx/5) && damage>0 )
        {
                number = damage-(yourskill/3*2)+(damage/yourskill)*100+random(damage/20)+random(10);
                number-= yourskill/10;
                if( number<300 ) number = 300; //防止number为0或负,偶没仔细算，不过加个判定是习惯
                number = COMBAT_D->valid_damage(me,target,number);
                message_combatd(RED"结果$n"RED"躲闪不及，身上中了"+chinese_number(number)+"处妖气化的情花花瓣！\n" NOR,me,target);
                target->receive_wound("kee",number,me,TYPE_PERFORM);
                target->receive_damage("kee",number,me,TYPE_PERFORM);
                COMBAT_D->report_status(target,1);
    			COMBAT_D->report_status(target);
        }
        else
        {
                number=damage-(yourskill/2);
                num=random(number/100+3)+random(11);
                if( num<100 ) num = 100; //同上
                num = COMBAT_D->valid_damage(me,target,num);
                message_combatd(HIG"但是$n"HIG"连跳带滚，总算躲了过去。不过还是中了"+chinese_number(num)+"处妖气化的情花花瓣。\n" NOR,me,target);
                target->receive_damage("kee",num,me,TYPE_PERFORM);
                COMBAT_D->report_status(target);
        }
        me->set_temp("WF_busy",time()); //这里我还是改成了time(),利用time()判定，比call_out去消除还是好一点，除非像下面那样必须call_out去消其他方面的buff
        if( damage>0 )
        {
                me->add_temp("apply/dodge",damage/2);
                me->add_temp("apply/parry",damage/2);
                me->add_temp("apply/attack",damage*damage/2);
                call_out("remove_effect",10+random(5),me,damage);
        }
        message_vision(HIW "$N将妖气一收，花瓣突地都消失不见了。\n" NOR,me);
        return 1;
}

void remove_effect(object me, int damage)
{
        if( !me )
                return;
        me->add_temp("apply/attack",-damage*damage/2);
        me->add_temp("apply/dodge",-damage/2);
        me->add_temp("apply/parry",-damage/2);
        message_vision(HIG "$N感觉到自己使用特技的力量恢复了。\n" NOR,me);
}    
