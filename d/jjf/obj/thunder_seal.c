#include <skill.h>
#include <ansi.h>
inherit __DIR__"seal.c";
#include <combat.h>

void create()
{
set_name("神霄雷法符", ({"thunder seal", "seal", "paper"}));
set_weight(100);
if(clonep())
        set_default_object(__FILE__);
else    {
        set("long","一张画上了符咒的桃符纸，中央有个大大的“雷”字。\n");
        set("base_unit","张");
        set("unit", "叠");
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
int success_adj, damage_adj;
success_adj = 75;
damage_adj = 75;

if(me->is_busy())
        return err_msg("你正忙着呢，无法祭神霄雷法符。\n");
if( !victim)
        return err_msg("你想祭的人不在这里。\n");
if( where->query("no_magic"))
        return err_msg("这里不能祭神霄雷法符。\n");
if( !me->is_fighting(victim))
        return err_msg("只有战斗中才能祭神霄雷法符。\n");
if( (int)me->query("mana") < 100 )
        return err_msg("你的法力不能控制神霄雷法符。\n");
if( (int)me->query("sen") < 100 )
        return err_msg("你的精神不足，很难驾驭神霄雷法符。\n");

me->add("mana", -50);
SPELL_D->attacking_cast(
                me, 
                victim, 
                success_adj,    
                damage_adj,     
                "sen",         
                HIC "\n$N"HIC"大喊一声“着”，手一挥，祭出了一张神霄雷法符！\n神霄雷法符「呼」地一下飞到半空，只见风云突变，几声闷雷在$n"HIC"耳边乍起。\n" NOR,
                HIR "\n$n"HIR"被雷声震的眼冒金星，心神不定，差点跌倒在地！\n" NOR, 
                HIC "\n谁知$n"HIC"毫无反应。\n" NOR, 
                HIC "但是$n"HIC"伸指一弹，雷声消隐，神霄雷法符反向$N"HIC"贴去！\n" NOR, 
                HIR "结果扑！地一声神霄雷法符在$n"HIR"身上烧了起来！\n" NOR
        );
me->set_temp("no_cast",time());
me->set_temp("jjf_ji_seal",time());
me->set_temp("no_cast_time",5); 
if (query_amount()>1)   add_amount(-1);
else destruct(this_object());
return 1;
}


