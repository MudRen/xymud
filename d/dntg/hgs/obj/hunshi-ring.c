#include <ansi.h>
#include <armor.h>
inherit FINGER;

void create()
{
        set_name("混世戒", ({ "hunshi jie", "jie", "ring","zhi" }));
        set("level",5);
        set("weight", 1500);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "只");
                set("no_steal",1);
                set("no_zm",1);
                set("value", 0);
                set("material", "gold");
                set("armor_prop/armor",3);
                set("armor_prop/personality",-3);
        }
        setup();
}       

void recover_func()
{
        string msg;
        int pot;
        object who = environment();
        if( !who || !living(who) || ( userp(who) && who->is_busy() )  ) //所有者昏迷或busy无效
                return;
        if( !query("equipped") || query("equipped")!="worn" ) //未装备无效      
                return;                 
        if( environment(who) && environment(who)->query("no_magic") )
                return;                 
        if( query_temp("using") )                               
                return;
        pot = 100;
        pot = pot/2+random(pot/2);
        set_temp("using",1);            
        if( who->query("force")/2<who->query("max_force") )
        {
                msg+= sprintf("%s给予你%d点的内力补充。\n",name(),pot);
                who->add("force",pot);
                if( who->query("force")/2>who->query("max_force") )
                        who->set("force",(int)who->query("max_force")*2 );
        }
        who->add_temp("HFring_msg",1);  
        if( who->query_temp("HFring_msg")%5==0 )
                tell_object(who,msg);   
        delete_temp("using");
        return;
}
