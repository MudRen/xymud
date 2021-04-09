// Zong.c 纵剑
// Cracked by 凌惊雪 5-4-2003
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg; 
        int extra,damage,dodge;
        
        if( me->query_level()<30 )
                return notify_fail("你的人物等级不够。\n");
        if( me->query_temp("pfm_heng_flag") )  return 0;
        if(me->query("family/family_name")!="百花谷")
                return notify_fail("「横剑」只有百花谷门人才可以用！\n");
        if( userp(me) && !wizardp(me) && me->is_knowing("bhg_zongheng")!=2 )  //1为横2为纵
                return notify_fail("你不会这一招的用法!!\n");   
        if((int)me->query("force") < 600 )
                return notify_fail("你的内力不足！\n");
        if((int)me->query_skill("zongheng-sword", 1) <300
         || (string)me->query_skill_mapped("sword")!="zongheng-sword" )
                return notify_fail("你的纵横剑法等级还不够!!\n");
        if((int)me->query_skill("brightjade-force", 1) <300)
                return notify_fail("你的明玉神功等级还不够!!\n");
        if( time()<me->query_temp("bhg_pfm_zong")+5 )
                return notify_fail("你现在的状态不能连续发出三剑。\n");        
                
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) ) 
                return notify_fail("你要对谁施展「纵剑」?\n");
        weapon = me->query_temp("weapon");
        msg = HIY"\n$N"HIY"运起明玉神功，一股劲道传入手中的"+weapon->name()+HIY"，陡然间用出百花谷失传多年的绝技"HIG"「纵剑」"HIY"。\n"NOR;
        message_vision(msg,me,target);
        dodge = me->query_skill("zongheng-sword",1)/10;
        me->add_temp("apply/combat_succ",dodge);
        me->add("force",-200);
        me->set_temp("bhg_pfm_zong",time());
        me->set_temp("ZHJ", 5);
        me->reset_action();
        me->set_temp("pfm_color",HIM);
        damage = me->query_skill("sword");
        if( time()<me->query_temp("bhg_yumei")+5 )
                damage = damage*2;
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,100,"kee");
        me->set_temp("action_flag",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,300,"kee");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_CAST,0,0,0,damage,"kee");
        me->set_temp("pfm_color",0);
        me->set_temp("action_flag",0);
        me->delete_temp("ZHJ"); 
        me->reset_action();
        me->add_temp("apply/combat_succ",-dodge);
        return 1;
}


int help(object me)
{
string str;     
if( !me )      return 0;
str = @LONG
        外功名称：纵剑
        外功所属：纵横剑法
        外功效果：对对手造成三次法术攻击的气血伤害
                  冷却5秒
                  本连击以杀敌为主，损伤对方的气血后限
                  需领悟，「纵剑」与「横剑」只能领悟一种
        外功条件：
                  百花谷弟子
                  人物等级30级
                  内力600点，消耗200点
                  纵横剑法300级并激发
                  明玉神功300级并激发
LONG;
me->start_more(str);
return 1;
}       

