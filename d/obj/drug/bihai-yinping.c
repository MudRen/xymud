#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"碧海银瓶"NOR, ({"yin ping", "ping"}));
        set("changed",1);
        set("no_store",1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "海外修士利用海中奇珍炼制的一瓶灵液，喝(drink)了它能补充内力。\n");
                set("value",1000000);
                set("num",100000);
        }
        setup();
}

void init()
{
        if( !query("owner_id") && environment() && userp(environment()) )
                   set("owner_id",environment()->query("id"));
        add_action("do_drink","drink");
}

int do_drink(string arg)
{
        int v;
        object me = this_player();
        
        if( !arg || !id(arg) )
                return 0;
        if( me->query("id")!=query("owner_id")  )   return err_msg("这个"+name()+"不是你买的。\n"); 
        
        if( me->query("force")>=me->query_maxforce() )
                return err_msg("现在不需要。\n");

        v = me->query_maxforce()*2-me->query("force");
        if( v<1 )
                v = 1;
        if( query("num")<v )
                return err_msg("这个"+name()+"已经喝得一干二净了。\n"); 
                
        me->add("force",v);
        message_vision(HIG"$N"HIG"拿起碧海银瓶喝了几口，觉得自己的内力充沛了好多。\n"NOR,me);
        add("num",-v);
        if( query("num")<=0 )
        {
                message_vision(HIG"碧海银瓶已经喝得见底了，$N"HIG"随手将之扔在一旁。\n"NOR,me);
                destruct(this_object());
        }
        return 1;
}



