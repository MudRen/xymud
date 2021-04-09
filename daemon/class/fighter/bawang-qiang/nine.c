// huima.c 霸王枪法
//姜家之绝命九枪
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
object weapon,env,*inv,*enemy,ev;
string msg,l,*ls,temp;
int ap,dp,damage,bt,i,k,t;
mixed b_time;
return notify_fail("暂为开放。\n");
if( !target ) target = offensive_target(me);
if( !target
 || !target->is_character()
 || !me->is_fighting(target) )
        return notify_fail("绝命九枪只能对战斗中的对手使用。\n");
if( !me->query("family/jjf_type")
  || me->query("family/jjf_type")!="spear" )
        return notify_fail("你尚未选择枪系作为你的兵器修为，无法领悟此招。\n");
if( me->query("force")<1500 ) 
        return notify_fail("你的内力太少。\n");
if( me->query("family/family_name") != "将军府" )
        return notify_fail("你是哪儿偷学来的武功！\n");
if( (int)me->query_skill("lengquan-force", 1) < 450 )
        return notify_fail("你的冷泉心法还差些火候。\n");
if( (int)me->query_skill("yanxing-steps", 1) < 450 )
        return notify_fail("你的雁行步法无法配合绝命九枪。\n");
if( (int)me->query_skill("bawang-qiang", 1) < 450 )
        return notify_fail("你的霸王枪法不够娴熟，不能采用绝命九枪。\n");
weapon = me->query_temp("weapon");
ls = target->query("limbs");
env = environment(me);
msg = HIR"双方交战多时，$N"HIR"招式陡然一变，"+weapon->name()+HIR"舞动如风，"+env->query("short")+HIR"顿时被一股冲天战气笼罩
住！一干人等皆觉举步唯艰。\n"NOR;        
message_vision(msg,me,target);
me->improve_skill("spear",random(3),1);
me->add("force",-200);
inv = all_inventory(env);
for(i=0;i<sizeof(inv);i++)
        {
        if ( inv[i] && living(inv[i])
          && inv[i]->is_fighting(me) 
          && !inv[i]->is_busy() )
                inv[i]->start_busy(1);
        }
ap = COMBAT_D->skill_power(me,"spear",SKILL_USAGE_ATTACK);
dp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
if ( COMBAT_D->wuxing_restrain(me,target)==1 )
        dp-= random(dp/3);      
if ( COMBAT_D->wuxing_restrain(me,target)==-1 )
        dp+= random(dp/3);      
if ( target->is_busy() )
        ap+= random(ap/3);
if ( time()>me->query_temp("jjf_nian_fail")+5 )
        ap+= random(ap/3);

if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
        message_vision(HIR"\n$N"HIR"暴喝一声，状若怒虎，双把合一，"+weapon->name()+HIR"舞出漫天的枪花，压向全场！\n"NOR,me,target);
me->clean_up_enemy();
enemy = me->query_enemy();
for(i=1;i<3;i++)
        {
        reset_eval_cost();                      
        ev = enemy[random(sizeof(enemy))];      
        if ( ev && living(ev)
          && me->is_fighting(ev) )
                {
                COMBAT_D->perform_attack(me,ev,weapon->query("weapon_prop/damage"));
                COMBAT_D->perform_attack(me,ev,weapon->query("weapon_prop/damage"));
                COMBAT_D->perform_attack(me,ev,weapon->query("weapon_prop/damage"));
                }                       
        }
if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
        message_vision(HIR"\n三枪使完，$N"HIR"枪头一转，"+weapon->name()+HIR"带出风雷之声，抖出五个枪影，狠狠砸向$n"HIR"！\n"NOR,me,target);
for(i=1;i<5;i++)
        {       
        if ( Int_com(ap,dp,100) && me->query("force")>1000 )
                {
damage = me->query_skill("spear")/10;
                damage+= me->query("force_factor");
                damage+= me->query_temp("apply/damage");
                damage-= target->query_temp("apply/armor");
                if ( time()>me->query_temp("jjf_nian_fail")+5 )
                        damage+= random(damage);
                else    damage = damage/2+random(damage);               
                if ( damage<100 ) damage = 100;
                damage = damage+random(damage/2);
                msg = COMBAT_D->damage_msg(damage,"砸伤");
                l = ls[random(sizeof(ls))];     
                msg = replace_string(msg,"$l",l);
                msg = replace_string(msg,"$w",weapon->name());
                target->receive_wound("kee",damage,me,"perform");
                if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
                        message_vision(msg,me,target);
                COMBAT_D->report_status(target,damage);
                me->add("force",-40);
                }
        else    {
                WEAPON_D->bash_weapon(me,target,weapon,RESULT_PARRY);
                me->set_temp("jjf_nian_fail",time());
                target->reset_action();
                }
        }
if ( me->query_skill("spear",1)>800 
  && me->query_skill("literate",1)>800 
  && me->query("bellicosity")<200 
  && me->query("force")>800 )
        {       
        damage = me->query_skill("spear")/30;
        damage+= me->query_temp("apply/damage");
        damage-= target->query_temp("apply/armor");
        if ( damage<500 ) damage = 500;
        if ( time()>me->query_temp("jjf_nian_fail")+5 )
                damage+= random(damage);
        else    damage = damage/2+random(damage);               
        ap = COMBAT_D->skill_power(me,"spear",SKILL_USAGE_ATTACK);
        dp = COMBAT_D->skill_power(target,"dodge",SKILL_USAGE_DEFENSE);
        if ( COMBAT_D->wuxing_restrain(me,target)==1 )
                dp-= random(dp/3);      
        if ( COMBAT_D->wuxing_restrain(me,target)==-1 )
                dp+= random(dp/3);      
        if ( target->is_busy() )
                ap+= random(ap/3);
        if ( time()>me->query_temp("jjf_nian_fail")+8 )
                ap+= random(ap/3);
        msg = HIR"\n$N"HIR"八枪使完，似无续招，猛然思起祖师爷传授此招时说道的最后一式乃是承随心所欲之势，不由
恍然，手中长枪急摆，也不管它什么招势，但凭风指云引。\n"NOR;
        msg+= "$N手腕一抖，$w似乎毒蛇吐信般急点$n名门！\n";
        t = me->query_skill("spear")+me->query_skill("literate",1);
        t/= 10;
        if ( t<30 ) t = 30;
        if ( t>120 ) t = 120;
        me->add("force",-200);
        if ( Int_com(ap,dp,100) )
                {
                msg+= "$n闪避不及，被$w刺了个正着，顿时血流满面！\n";
                if ( !target->query_condition("weapon_hurt") )
                        {               
                        target->set("weapon_hurt",([
                                "time"  : t,
                                "start" : time(),
                                "type"  : "枪",
                                "limb"  : "面门",
                                "target_name" : me->name(1),
                                "target_id"   : me->query("id"),
                                "target"      : me,
                                "damage"      : 500,
                        ]));
                        target->apply_condition("weapon_hurt",t);
                        }
                msg+= COMBAT_D->damage_msg(damage,"刺伤");
                l = ls[random(sizeof(ls))];     
                msg = replace_string(msg,"$l",l);
                msg = replace_string(msg,"$w",weapon->name());
                target->receive_damage("kee",damage,me,"perform");
                if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
                        message_vision(msg,me,target);
                COMBAT_D->report_status(target);
                }
        else if ( Int_com(ap,dp,80) )
                {
                if ( random(2) )  temp = "腿";
                else    temp = "手";    
                msg+= "$n闪避不及，只得堪堪一闪，虽躲过要害，但是"+temp+"上终于还是挨了一枪！\n";
                if ( !target->query_condition("weapon_hurt") )
                        {               
                        target->set("weapon_hurt",([
                                "time"  : t,
                                "start" : time(),
                                "type"  : "枪",
                                "limb"  : temp,
                                "target_name" : me->name(1),
                                "target_id"   : me->query("id"),
                                "target"      : me,
                                "damage"      : 100,
                        ]));
                        target->apply_condition("weapon_hurt",t);
                        }
                damage/= 10;    
                msg+= COMBAT_D->damage_msg(damage,"刺伤");
                l = ls[random(sizeof(ls))];     
                msg = replace_string(msg,"$l",l);
                msg = replace_string(msg,"$w",weapon->name());
                target->receive_damage("kee",damage,me,"perform");
                if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
                        message_vision(msg,me,target);
                COMBAT_D->report_status(target);
                me->add("force",-100);
                }
        else    {
                msg+= "$n不慌不忙，从容闪过。\n";
                if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
                        message_vision(msg,me,target);
                me->add("force",-200);  
                }
        }                               
me->start_busy(2);              
return 1;
}               
                                
int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：绝命九枪
        外功所属：霸王枪法
        外功效果：姜氏绝命九枪，前三枪群攻在场所有敌人
                  后五枪五氏合一猛攻当前敌人，并有可能格飞对方武器      
                  最后一枪给予敌人以重创
                  使后自身busy 2 秒
        外功条件：
                  内力1500点，消耗600-800点
                  将军府枪系传人
                  霸王枪法450级
                  冷泉心法450级
                  雁行步法450级
LONG;
me->start_more(str);
return 1;
}       
