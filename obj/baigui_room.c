#include <ansi.h>
#include <combat.h>
inherit ROOM;

string *gui_act =
({
    "一只獠牙鬼从你身后窜出,张开血盆大口朝你颈部就是一口,眼看你的鲜血如喷泉般激射",
    "一只赤面鬼张牙舞爪的向你冲了过来,鬼手挥动几下,你便如破絮飞散",
    "一只吊死鬼从空中出现用它那长长的爪子直接插进了你的头盖骨,只见你的脑浆飞溅",
    "一只独角鬼朝你猛撞了过来,你还没来得急反应就已经像断线风筝似地陨落",
    "一只无头鬼拖着一柄鬼头刀对着你就是一阵乱舞,你终于明白什么叫乱刀分尸了",
    "一只食人鬼从你脚下冒出,大口大口地吞噬你的身体,一时你便成白骨",
});
string *pass_act =
({
    "一只獠牙鬼从你身后窜出,幻影一般从你身边掠过,转瞬消失在茫茫紫雾之中",
    "一只赤面鬼张牙舞爪的向你冲了过来,转身有融入黑暗中",
    "一只吊死鬼从空中出现,对着你诡异地邪笑,又凭空消失了",
    "一只独角鬼朝你猛撞了过来,却如幽灵般穿过你的身体,消失在你背后",
    "一只无头鬼拖着一柄鬼头刀从你身边路过,无视你的存在",
    "一只食人鬼从你脚下冒出,怪叫了两声又遁入地下",
});

void create()
{
        set("short","雾气开始慢慢变淡了，你忙定睛查看四周。");
        set("long1","    昏暗的%s延伸到无边的黑暗中,几点碧绿的鬼火幽幽地呻吟...\n你只觉得脖子凉嗖嗖的,全身寒战,却又无法动弹\n"NOR);
        set("alternative_die",1);
        setup();
}

void effect2( object me, object target );
void effect3( object me, object target, int times );
void effect4(object me, object target,int lvl);
void remove_effect4(object target,int lvl);
void effect5(object me, object target);
int information(object me,object target);

void alternative_die(object who)
{
        if( !who )
                return;
        if( who==query("owner") 
         && (random(2)==1||wizardp(who)) )
                {
                who->powerup(0,1);
                tell_object(who,HIY"你被"+query("short")+"恢复了全身精力。\n"NOR);
                return;
                }
        else    {
                set("alternative_die",0);
                who->die();
                set("alternative_die",1);
                }
}                       

//实际伤害
void effect2( object me, object target )
{
int times;
remove_call_out("effect2");
if ( !me || !target || !me->is_fighting(target) 
  || !present(me,this_object()) 
  || !present(target,this_object()) )
        {
        remove_call_out("effect5");     
        call_out("effect5",1,me,target);
        return;
        }
reset_eval_cost();
message_vision(HIG"鬼火忽然亮了起来."+MAG"$N的身影却已消失在黑幕中.\n"
+HIB"一群魑魅魍魉在$n身边忽隐忽现.\n"+HIR"$n"
+HIR"恐惧得心跳加速,呼吸急促,但是却又动不了半分.\n"NOR,me,target);
times = me->query_skill("scratmancy",1)/80;
times+= me->query_skill("spells",1)/80;
times+= me->query_skill("zhanbu",1)/80;
times-= target->query_skill("spells",1)/80;
times-= target->query_skill("zhanbu",1)/80;
times = times/2+random(times);
me->start_busy( 1 );
target->start_busy( 1 );
remove_call_out("effect3");
call_out( "effect3", 1, me, target, times );
}

void effect3( object me, object target, int times )
{
int t,i;
object here;
int damage;

remove_call_out("effect3");

if( times <= 0
 || !me
 || !me->is_fighting(target) 
 || !target
 || !living(target)
 || target->query("eff_kee")<0
 || target->query("eff_sen")<0
 || (!living(target) && target->query("kee")<0)
 || (!living(target) && target->query("sen")<0) 
  || !present(me,this_object()) 
  || !present(target,this_object()) )
        {
        remove_call_out("effect5");     
        call_out( "effect5", 1, me, target );
        }
else    {
        target->set_temp("block_msg/all",1);
        t=3+random(3);
        if( t>times ) t=times;
        for( i=0; i<t; i++ )
                {
                if( !me || !target || !me->is_fighting(target) 
                 || !present(me,this_object()) 
                 || !present(target,this_object()) )
                        break;
                damage = COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_QUICK);
                me->add("mana",-me->query("mana_factor"));
                if( me->query("mana") > 0 )
                        damage = damage + me->query("mana_factor") + random(me->query("mana_factor"));
                else    me->set("mana",0);
                damage = damage * (500+me->query("mana_factor")) / (500+(target->query("mana_factor")) );
                target->set_temp("block_msg/all",0);
                if( damage > 200 )
                        {
                        tell_object( target,HIR"突然,"+gui_act[random(sizeof(gui_act))]+"...\n"NOR+COMBAT_D->damage_msg(damage,"伤害") );
                        target->receive_damage("sen", damage, me,"cast");
                        target->receive_wound("sen", damage/2, me,"cast");
                        COMBAT_D->report_sen_status(target);
                        }
                else    tell_object( target,CYN"突然,"+pass_act[random(sizeof(pass_act))]+"...\n"NOR );
                target->set_temp("block_msg/all",1);
                }
        times -= t;
        remove_call_out("effect3");     
        call_out( "effect3", 1, me, target, times );
        }
}


void effect4(object me, object target,int lvl)
{
remove_call_out("effect4");     
if( target && !target->query_temp("baigui/huan") )
        {
        target->add_temp("apply/armor",-lvl/2);
        target->add_temp("apply/damage",-lvl/2);
        target->add_temp("apply/dodge",-lvl/2);
        target->add_temp("apply/attack",-lvl/4);
        target->add_temp("apply/defense",-lvl/4);
        target->set_temp("baigui/huan",1);
        message_vision(HIB"$N全身发抖,手脚不听使唤了...\n"NOR,target);
        remove_call_out( "remove_effect4");
        call_out( "remove_effect4", lvl/50, target, lvl );
        }
}

void remove_effect4(object target,int lvl)
{
remove_call_out("remove_effect4");
if ( !target || !target->query_temp("baigui/huan") )  
        return;
target->add_temp("apply/armor",lvl/2);
target->add_temp("apply/damage",lvl/2);
target->add_temp("apply/dodge",lvl/2);
target->add_temp("apply/attack",lvl/4);
target->add_temp("apply/defense",lvl/4);
target->delete_temp("baigui/huan");
message_vision(HIB"$N一阵剧烈的寒颤,终于回复了过来.\n"NOR,target);
}

void effect5(object me, object target)
{
object here;     
remove_call_out("effect5");
delete("baigui");
here = query("exitRoom");
if ( me )  
        {      
        me->delete("env/invisibility");
        me->delete_temp("baigui/casting");
        if( here && me->move(here,1) )
                {
                set("short",here->query("short"));
                set("long",here->query("long"));
                }       
        message_vision(MAG"紫雾退去,$N依然站在原地,似乎什么也没有发生过...\n"NOR,me);
        me->command("look");        
        me->delete_temp("baigui/old_room");    
        }
if( target )
        {
        target->delete_temp("block_msg/all");
        if( here && target->move(here,1) )  target->command("look");
        }
}

void check()
{
object me,target;
me = query("owner");
target = query("target");
if( me && target && present(me,this_object())
 && present(target,this_object()) 
 && !query("baigui") )
        information(me,target);         
}

void dest_ob(object obj)
{
if( !obj )  return;
if( !present(obj,this_object()) )
         return;
destruct(obj);
}

void init()
{
if( !living(this_player()) && !this_player()->is_character() )  {
          call_out("dest_ob",5+random(10),this_player());
          return;
          }
else if( this_player()!=query("owner") && this_player()!=query("target") )
           {
           MISC_D->random_capture(this_player(),1,random(100));
           return;
           }
remove_call_out("check");
call_out("check",1);
}
        
int information(object me,object target)
{
        int len;
        string short,long,tmp;
        object where,env;
        if( !me || !target 
         || !living(target)
         || !living(me) )
                return 0;
        where = me->query_temp("baigui/old_room");
        env = environment(me);
        if( !where || !present(target,env) )
                return 0;
        if( base_name(where)==base_name(this_object()) )
                return 0;
        short = where->query("short");
        long = where->query("long");
        if( !short )
                short = query("short");
        else    {
                len = strlen(short);
                tmp = sprintf("%s",short[(len-2)..(len-1)]);
                short = replace_string(short,tmp,"鬼"+tmp);
                }
        if( !long ) 
                long = sprintf(query("long1"),short);
        else    long+= sprintf(query("long1"),short);    
        set("short",short);
        set("long",long);
        delete("exits");
        set("exits",where->query("exits"));
        set("baigui",1);
        set("exitRoom",where);
        me->command("look");
        target->command("look");
        effect4(me,target,me->query_skill("zhanbu",1));
        remove_call_out("effect2");
        call_out("effect2", 1, me, target );
        return 1;
}

void valid_move(object who)
{
        if( who && who->query("id")==query("owner_id") )
                {
                who->start_busy(1+random(2));
                who->delete("env/invisibility");
                who->delete_temp("baigui/casting");
                delete("baigui");
                delete("owner");
                return;
                }
}
