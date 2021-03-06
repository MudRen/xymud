#include <skill.h>
#include <ansi.h>
inherit __DIR__"seal.c";
#include <combat.h>

void create()
{
set_name("神霄雨法符", ({"rain seal", "seal", "paper"}));
set_weight(100);
if(clonep())
        set_default_object(__FILE__);
else    {
        set("long","一张画上了符咒的桃符纸，中央有个大大的“雨”字。\n");
        set("unit", "叠");
        set("base_unit", "张");
        set("value", 0);
        set("no_put",1);
        set("no_sell",1);
        }
set_amount(1);
setup();
}

int ji_ob(object victim)
{
object seal=this_object();
object me=this_player();
object where=environment(me);
int damage, ap, dp,sk;
        
if(me->is_busy())
        return err_msg("你正忙着呢，无法祭神霄雨法符。\n");
if( !victim)
        return err_msg("你想祭的人不在这里。\n");
if( where->query("no_magic"))
        return err_msg("这里不能祭神霄雨法符。\n");
if( !me->is_fighting(victim))
        return err_msg("只有战斗中才能祭神霄雨法符。\n");
if( (int)me->query("mana") < 100 )
        return err_msg("你的法力不能控制神霄雨法符。\n");
if( (int)me->query("sen") < 100 )
        return err_msg("你的精神不足，很难驾驭神霄雨法符。\n");

message_vision(HIC"\n$N"HIC"大喊一声“着”，手一挥，祭出了一张$n"HIC"。。。\n"NOR, me, seal);
message_vision(HIC"$n"HIC"「呼」地一下飞到半空，只见突起狂云，卷出一阵冰雨向$N"HIC"袭去。\n"NOR, victim,seal);

ap= (int)seal->query("ap");
dp= COMBAT_D->skill_power(victim,"spells",SKILL_USAGE_DEFENSE);
if ( victim->is_busy() || !living(victim) )
        dp-= dp/3;
if ( COMBAT_D->wuxing_restrain(me,victim)==1 )
        ap+= random(ap/3);      
if ( COMBAT_D->wuxing_restrain(me,victim)==-1 )
        dp+= random(dp/3);      

if(random(ap+dp) > dp)  
        {
        damage = (int)me->query("max_mana") / 20 +
        random((int)me->query("eff_sen") / 15);
        damage -= (int)victim->query("max_mana") / 20 +random((int)victim->query("eff_sen") / 15);                                 
        damage+=(int)me->query("mana_factor")-random((int)victim->query("mana_factor"));
        if( damage> 0)
                {
                if ( damage<10 ) damage = 10;   
                message_vision(HIC"\n$N"HIC"躲闪不及，被冰雨裹个正着，顿时成了个冰人。\n"NOR,victim);
                victim->start_busy(damage/10);
                } 
        else    message_vision(HIC"\n$N"HIC"猛退几步，躲了过去。\n"NOR,victim);
        }
else    message_vision(HIC"\n谁知被$N"HIC"躲了过去。\n"NOR,victim);
if( !victim->is_fighting(me) ) 
        {
        if( living(victim) ) 
                {
                if( userp(victim) ) victim->fight_ob(me);
                else    victim->kill_ob(me);
                }
        me->kill_ob(victim);
        }
me->add("mana",-50);
me->set_temp("no_cast",time());
me->set_temp("jjf_ji_seal",time());
me->set_temp("no_cast_time",5); 
if ( seal->query_amount()>1 )  seal->add_amount(-1);
else   destruct(seal);
return 1;
}

