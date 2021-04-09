#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
    set_name("挑战券", ({ "seal" }) );
    if(clonep()) 
    set_default_object(__FILE__); 
    set("base_unit", "张");
    set("unit","叠");
    set("long", "可以减少15分钟挑战假死cd的卷轴，撕开(burn)看看。\n");
    set("value",5000000);
        setup();
        set_amount(1);
}

void init()
{
        add_action("do_burn","burn");
}

int do_burn(string arg)
{
        object me = this_player();
        
        if( !arg || !id(arg) )
                return 0;
        if( me->is_busy() || !userp(me) )
                return err_msg("你现在正忙着呢。\n");
        if( 3600-time()+me->query("mark/tiaozhan/last_die")<=0 )
                return err_msg("你现在不需要用。\n");   
        message_vision(RED"$N"RED"小心翼翼的撕开一张$n"RED"。\n"NOR,me,this_object());
        me->add("mark/tiaozhan/last_die",-900);
        message_combatd(HIY"一道金光在$N"HIY"身后一闪而没！\n\n"NOR,me);
        me->save();
        write("你的挑战假死冷却时间为"+FINGER_D->age_string(3600-time()+me->query("mark/tiaozhan/last_die"))+"。\n");
        me->start_busy(2);
        if( query_amount()>1 )
                add_amount(-1);
        else
                destruct(this_object());
        return 1;
}               
                        
