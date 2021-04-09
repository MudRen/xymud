#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void long_hit(object invoker, object target,int num);

int perform(object me, object target)
{
        string msg;
        
        if( me->query_level()<20 )
                return notify_fail("你的人物等级不够。\n");
        if((string)me->query("family/family_name") != "东海龙宫" ) 
                return notify_fail("你又不是龙宫弟子。\n");
        if((int)me->query_skill("seashentong", 1) < 200)
                return notify_fail("你的碧海神通修为不深，请不动八仙。\n");
        if( me->query("family/family_name") != "东海龙宫" ) 
                return notify_fail("你又不是东海弟子，不会升龙技。\n");
        if( me->query_skill("dragonfight",1)<200 )
                return notify_fail("你的龙形搏击修为不深，施展不出升龙技。\n");
        if( time()-(int)me->query_temp("shenglong_end")<10 )
                return notify_fail("你刚用过「升龙技」,内息还无法调整！\n");
        if( me->query("force")<500 )
                return notify_fail("你的内力不够。\n");
        if( me->query("kee")<200 )
                return notify_fail("你现在气血不畅！\n");
        if( time()<me->query_temp("sea_shenglong")+8 )
                return notify_fail("你正在升龙中呢。\n");
                                
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
         || target->is_corpse()
         || target==me
         || !me->is_fighting(target) )
                return notify_fail("你对谁施展升龙技？\n");
        if((string)target->query("family/family_name") == "东海龙宫" )
                return notify_fail("此招对同门无效。\n");

        me->add("force", -250);
        me->receive_damage("kee",100,me);

        message_combatd(HIY"$N"HIY"咬破舌尖，吐出一口鲜血，背后现出惊涛骇浪幻象，数条巨龙在其他翻腾出入！\n"NOR,me);
        message_vision(HIB"$N"HIB"默运碧海神通，身法一展，竟然使出「升龙技」舍身扑向$n"HIB"！\n"NOR,me,target);
        me->set_temp("sea_shenglong",time());
        if( !target->is_killing(me->query("id")) )
        {
                msg = HIR "$n"HIR"对着$N"HIR"高声骂道：好家伙，一拥而上了，我宰了你！\n" NOR;
                message_vision(msg, me, target);
                target->kill_ob(me);
        }       
        long_hit(me, target,1);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=250 )
                long_hit(me, target,2);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=300 )
                long_hit(me, target,3);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=350 )
                long_hit(me, target,4);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=400 )
                long_hit(me, target,5);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=450 )
                long_hit(me, target,6);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=500 )
                long_hit(me, target,7);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=550 )
                long_hit(me, target,8);
        if( me && target && me->is_fighting(target)
         && me->query_skill("dragonfight",1)>=600 )
                long_hit(me, target,9);
        me->set_temp("sea_shenglong",time());                   
        return 1;
}

void long_hit(object me, object target,int num)
{
        int i;
        string msg,*name1,name;

        if( !me || !target || !living(me) || !me->is_fighting(target)
         || num>9 )
                return;
        name1 = ({
                "花皮", "金角", "金尾","银角","背苍","虬髯","螭虬",
                "蜧金","神通","锦鲤",
        });
        name = chinese_number(num)+"爪"+name1[random(sizeof(name1))]+"龙";      
        msg = HIY"\n只听$N"HIY"背后东海幻象中冲出一条"+name+HIY"，将尾一摇，一道飓风卷向$n"HIY"$l！ \n"NOR;
        me->set_temp("pfm_msg",1);
        COMBAT_D->do_attack(me,target,me->query_temp("weapon"),TYPE_QUICK,msg);
        message_combatd(HIY+name+HIY"将身一摇，又串回$N"HIY"背后的的虚影中去了。。。\n\n"NOR,me);
}

int help(object me)
{
string str;
if( !me )      return 0;
str = @LONG
        外功名称：升龙技
        外功所属：龙形搏击
        外功效果：以东海九龙虚影攻击对手
                  每50级增加一条神龙虚影
                  升龙状态结束后冷却8秒
        外功条件：
                  龙宫弟子
                  人物等级20级
                  内力500点，消耗250点
                  气血200点，消耗100点
                  龙形搏击200级
                  碧海神通200级
LONG;
me->start_more(str);
return 1;
}

