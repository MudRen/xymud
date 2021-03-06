//last modify by oukaya 03-10-25 9:25
//snowtu修改2007
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

mapping l_weapons = ([
//      基本技能           激发技能     武器名称        攻击信息        失败信息        成功信息                  
        "dodge" : ({
                "yanxing-steps",
                "雁行阵法",
                HIM"\n【布阵诀．．．．．．．．．．奇门八卦】\n"NOR"$N口中念道：乾生天，坤生地，八卦无形，周转复始．绕着$n越转越快，\n同时在地上不知布了一些什么玄机.地上起了些奇异的变化!!!\n",
                "但是$n却乱闯一通，误打误撞，竟然将$N辛苦布成的阵法破坏了．\n",
                "$n只觉得四周有无形之力向自己压来，身形顿时慢了下来．\n",
                }),
        "unarmed" : ({
                "changquan",
                "双拳",
                HIC"\n【勇气诀．．．．．．．．．．神勇无敌】\n"NOR"$N叫道：“着”同时，双手交换出拳，一拳比一拳快，当真是\n有万夫莫敌之气势，将长拳发挥得淋漓尽致，直朝着$n而去。\n",
                "就在$N的拳头要击中$n的瞬间，$n猛然大叫了一声，$N一受惊，一下收了回来．\n",
                "$n向后急退，最后退无可退，$l硬生生的接了$N一拳，只觉得五脏六腑都移了位．\n",
                }),
        "spear"  : ({
                "bawang-qiang",
                HIG"碧玉枪"NOR,
                HIY"\n【枪字诀．．．．．．．．．．四海平生】\n"NOR"$N将手中$w往空中一抛，手指$n，叫道：去也．只见$w一分二，\n二分四，越分越多，从四面八方直朝着$n射去,$n顿时惊慌失措．\n",
                "哪知$n早已料到这招，凭着一口真气，一越而上，愣是从枪海之中逃了出去\n",                             
                "$n一时慌了神，只听”嗤嗤”几声，原来已经被$w划的身上伤痕累累．\n",        
                }),
        "archery" : ({
                "xuanyuan-archery",
                "轩辕箭",
                HIR"\n【箭字诀．．．．．．．．．．百战百胜】\n"NOR"$N暗暗将咒语附着在$w上，向四周虚劈了几下，所到之处，卷起层层烈焰，\n象是要把$n吞噬一样,$n的脸被火焰映得通红．\n",
                "$n竟然看出身旁的火焰是幻影，丝毫不受$N幻影攻击的影响．\n",                         
                "$n手足无措，被烈火灼伤了胸部，$n心理精神上受到了很大的打击．\n",           
                }),
        "axe"   : ({
                "sanban-axe",
                "宣花斧",
                HIB"\n【斧字诀．．．．．．．．．．力劈山河】"NOR+"\n $N抛起$w,合手念起八卦咒，$n只觉心底烦躁不已。\n",
                "想不到$n反手在自己脸上一掌，愣是靠痛楚稳定了自己心神．\n",
                "$n抵受不了攻击，最后只好运功抵抗，元气大损．\n",
                }),                     
        "mace"  : ({
                "jinglei-mace",
                "惊雷鞭",
                HIW"\n【鞭字诀．．．．．．．．．．横扫千军】"NOR+"\n$N双手举起$w，以雷霆万钧之势向$n砸去，此招看似大拙，实则大巧．\n$w在空中一个转折,向$n飞来,$n脸上写满恐怖!\n",
                "$n以柔克刚，以阴克阳，愣是让$N的雷霆一击之力化为乌有．\n",
                "$n来不及细想，凭感觉躲闪，但来不及了，$l愣是被砸中，顿时行动受损．\n",
                }),
]);  
string begin_msg(object me,object target,int i,string w_name);

int perform(object me,object target)
{
int ap,dp,flag,i,damage,scc=0;
string w_name,msg,*l_weapon,*limbs,limb;
string unarmed,dodge,axe,mace,spear,archery;

return notify_fail("暂未开放。\n");        
if(!target)      target = offensive_target(me);
if((string)me->query("family/family_name") != "将军府" )
        return notify_fail("你不是将军府门下，如何能领悟得了此招「万刃神兵诀」？\n");
if( !target
 || !target->is_character()
 || target->is_corpse()
 || target == me 
 || !me->is_fighting(target) )
        return notify_fail("你准备对谁用这招「万刃神兵诀」？\n");
if( me->query("sen") < 500 )
        return notify_fail("你的精神不足，使用这招「万刃神兵诀」恐怕有危险．\n");
if( me->query("kee") < 500 )
        return notify_fail("你的气血不足，使用这招「万刃神兵诀」恐怕有危险。\n");
if( me->query("max_force") < 800 )
        return notify_fail("你的内力根本不足以使用这招「万刃神兵诀」．\n");
if( me->query("force") < 1500 )
        return notify_fail("你的当前内力太少了，会有危险的．\n");
if( me->query("mana") < 1500 )
        return notify_fail("你的当前法力太低，还无法熟练运用这招。\n");
if( me->query_skill("lengquan-force",1) < 200 )
        return notify_fail("你的冷泉神功级别太低，还用不了这招．\n");
if( me->query_skill("baguazhou",1) < 120 )
        return notify_fail("你的八卦咒级别太低，出不了此招．\n");
if( me->query_skill("spear",1) < 200 )
        return notify_fail("你的基本枪法别太低，使用这招恐怕有危险．\n");
if( me->query_skill("mace",1) < 200 )
        return notify_fail("你的基本锏法级别太低，还用不了这招．\n");
if( me->query_skill("axe",1) < 200 )
        return notify_fail("你的基本斧法级别太低，还用不了这招．\n");
if( me->query_skill("jinglei-mace",1) < 200 )
        return notify_fail("你的惊雷鞭法级别太低，还用不了这招．\n");   
          
unarmed = me->query_skill_mapped("unarmed");
spear = me->query_skill_mapped("spear");
axe = me->query_skill_mapped("axe");
mace = me->query_skill_mapped("mace");
archery = me->query_skill_mapped("archery");
dodge = me->query_skill_mapped("dodge");
        
if( unarmed == "changquan" )  flag = 1;
if( spear == "bawang-qiang" )  flag += 1;
if( axe =="sanban-axe" )    flag += 1;
if( mace == "jinglei-mace" )  flag += 1;
if( archery == "xuanyuan-archery" )   flag += 1;

if( flag < 3 )
        return notify_fail("你本门武功太少，无法使用这招「万刃神兵诀」．\n");
if( me->query_skill_mapped("force") != "lengquan-force" )
        return notify_fail("没有冷泉神功作基础，如何引发这招「万刃神兵诀」？\n");
if( me->query_skill_mapped("spells") != "baguazhou" )
        return notify_fail("没有八卦咒引导，如何将此招「万刃神兵诀」发挥到最大限度？\n");
msg = HIR"\n$N暗念八卦咒，运起澎湃护体真气，脚下是越转越快，出手是越来越狠．．．．\n"NOR;
message_vision(msg,me);
me->set_temp("tian_end",time());
me->start_busy(1+random(2));
me->add("force",-800);
me->add("mana",-50);
l_weapon = keys(l_weapons);        
limbs = target->query("limbs");
for(i=0;i<sizeof(l_weapon);i++)
        {
        reset_eval_cost();
        if ( !me || !target || !me->is_fighting(target) )
                continue;
        if( !me->query_skill_mapped(l_weapon[i])
          || me->query_skill_mapped(l_weapon[i])!=l_weapons[l_weapon[i]][0] 
          || me->query_skill(l_weapon[i],1)<100 
          || me->query_skill(l_weapons[l_weapon[i]][0],1)<100 )
        continue;
        if ( !living(target) )
                break;                  
        w_name = l_weapons[l_weapon[i]][1];
        msg = l_weapons[l_weapon[i]][2];
        ap = COMBAT_D->skill_power(me,l_weapon[i],SKILL_USAGE_ATTACK);
        dp = COMBAT_D->skill_power(target,"parry",SKILL_USAGE_DEFENSE);
        dp+= COMBAT_D->skill_power(target,"dodge",SKILL_USAGE_DEFENSE);
        dp/= 2;
        if ( COMBAT_D->wuxing_restrain(me,target)==1 )
                dp-= random(dp/3);      
        if ( COMBAT_D->wuxing_restrain(me,target)==-1 )
                dp+= random(dp/3);      
        if ( target->is_busy() )
                ap+= random(ap/3);
        if ( random(ap+dp)>dp/2 )     scc = 1;
        else    scc = 0;
        if ( scc==0 )        
                msg+= l_weapons[l_weapon[i]][3];
        else    {
                msg+= l_weapons[l_weapon[i]][4];
                switch(l_weapon[i])
                        {
                        case "dodge" :
                                if ( !me->query_temp("jjf_wanren_dodge_add") )
                                        {
                                        me->set_temp("jjf_wanren_dodge_add",1);
                                        me->set_temp("jjf_wanren_dodge",(int)me->query_skill("dodge",1)/2);
                                        me->set_temp("jjf_wanren_strength",(int)me->query_skill("dodge",1)/2);
                                        me->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/2);
                                        me->add_temp("apply/strength",(int)me->query_skill("dodge",1)/2);
                                        me->start_call_out( (: call_other, __FILE__, "remove_eff",me :),60 );
                                        }
                                break;
                        case "unarmed" : 
                                damage = me->query_skill("unarmed")/(1+random(2));
                                break;
                        default :
                                damage = me->query_skill(l_weapon[i]);
                                damage+= me->query("force_factor");
                                break;
                        }
                }
        limb = limbs[random(sizeof(limbs))];
        msg = replace_string(msg,"$l",limb);
        msg = replace_string(msg,"$w",w_name);                  
        if ( !me->query("env/brief_message") && !target->query("env/brief_message") )
                message_vision(msg,me,target);          
        if ( damage>0 )
                {       
                damage+= me->query_temp("apply/damage");
                damage-= target->query_temp("apply/armor");
                }
        if ( damage>0 )
                {
                damage = damage/2+random(damage/2);
                if(random(5)==1)
                        {
                        damage += me->query_str();
                        message_vision(CYN"\n轰!!轰!!轰!!$N被$n砸得天旋地转,站立不稳,差点去见崔叔叔!!\n"NOR,target,me->query_temp("weapon")); 
                        }
                if ( damage/3>0 && l_weapon[i]!="unarmed" )
                        target->receive_wound("kee",damage/3,me,"perform");
                else if ( l_weapon[i]=="archery" )
                        target->receive_wound("sen",damage,me,"perform");
                else    target->receive_damage("kee",damage,me,"perform");
                if ( userp(target) )
                        target->receive_wound("kee",damage,me,"perform");
                COMBAT_D->report_status(target);
                }       
        }
if( target && !target->is_fighting(me) ) 
        {
        if( living(target) ) 
                {
                if( userp(target) ) target->fight_ob(me);
                else target->kill_ob(me);
                }
       }
me->start_busy(2);
return 1;
}

void remove_eff(object me)
{
if ( me && me->query_temp("jjf_wanren_dodge_add") )
        {
        me->add_temp("apply/dodge",-me->query_temp("jjf_wanren_dodge"));
        me->add_temp("apply/strength",-me->query_temp("jjf_wanren_strength"));
        me->delete_temp("jjf_wanren_dodge");
        me->delete_temp("jjf_wanren_strength");
        me->delete_temp("jjf_wanren_dodge_add");        
        }
}

int help(object me)
{
string str;     
if ( !me )      return 0;
str = @LONG
        外功名称：万刃神兵诀
        外功所属：惊雷鞭法
        外功效果：将军府群修系的绝招，以所学的技能对敌进行狂风暴雨般的攻击
                  使用后自身busy 2 秒
        外功条件：
                  内力修为八年  
                  内力1500点，消耗800点
                  法力1500点，消耗50点
                  精神500点
                  气血500点
                  八 卦 咒200级
                  基本枪法200级
                  基本锏法200级
                  基本斧法200级
                  惊雷鞭法200级
                  冷泉神功200级
                  激发冷泉神功
                  
LONG;
me->start_more(str);
return 1;
}
