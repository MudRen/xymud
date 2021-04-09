#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int damage, p;
        object target; 
        string msg;
      
        target = me->query_temp("xueying_hit/target");
        if( !target || !target->is_fighting(me) )
        {
                message_vision(HIR"$N"HIR"沉闷半响，哇的，吐出一口淤血，感觉人舒服了不少。\n"NOR,me);
                return 0;
        }
        damage = me->query_temp("xueying_hit/damage");
        damage = damage/3*2+random(damage);
        if( damage<=0 )
        {
                message_vision(HIR"$N"HIR"沉闷半响，哇的，吐出一口淤血，感觉人舒服了不少。\n"NOR,me);           
                return 0;
        }
        tell_object(me, HIR"突然你感觉胸口疼痛异常，刚才被金龙血影击拍中之处好象骨头要裂开了似的，鲜血也从口中喷了出来！\n"NOR);
        tell_room(environment(me), HIR + me->name()+"突然一言不发，蹬蹬磴倒退了数步，接着哇得一声吐出口鲜血来，脸色顿时变得惨白！\n" NOR,({ me }));
        me->receive_wound("kee", damage,target,"perform");
        COMBAT_D->report_status(me,damage);
        me->apply_condition("xueying_hit",1);
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "hurt";
}


