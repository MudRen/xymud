#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
   if( !living(me) ) {
      message("vision", HIR""+me->name() + "身中五毒门奇毒，五种毒气突然攻心．\n"NOR, environment(me), me);
   }
   else {
      tell_object(me, HIR "所中五毒发作了。\n" NOR );
      message("vision", HIR""+me->name() + "身中五毒门奇毒，五种毒气突然攻心．\n"NOR,
            environment(me), me);
   }
   me->receive_wound("kee",100);
   me->receive_damage("kee",100);
    if ( !me->is_busy() )
me->start_busy(random(3));
me->set_temp("death_msg","五毒神掌毒发身亡。听说死的时候，面目狰狞可怖！\n");
   me->apply_condition("wudu", duration - 1);

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}
int can_clear() { return 0; }
string name() {return "五毒门奇毒";}

