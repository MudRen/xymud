#include <ansi.h>
inherit COMBINED_ITEM;

void setup()
{
        set("level",1);
}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("松鹤龟苓膏", ({"songgui gao", "gao",}));
        if (clonep())
                set_default_object(__FILE__);
        set("base_unit","瓶");
        set("unit","些");
        set("long", "药香扑鼻的膏药，服用(eat)它能增加%d点活力。\n");
        set("value", 100);
        set("drug_type", "良药");
        set_amount(1);
        setup();
}

string long()
{
        string str = ::long();
        return sprintf(str,query("level"));
}

string query_title(int v)
{
        if( v<=1 )
                return "凡品";
        else if( v<=2 ) 
                return "下品";
        else if( v<=3 ) 
                return "中品";
        else if( v<=4 ) 
                return "上品";
        else    return "珍品";
}

string name()
{
        string msg,str = ::name();
        if( query("level")<=0 )
                return "无效的"+str;
        msg = query_title(query("level"));
        return msg+str;
}

int do_eat(string arg)
{
        int v;
        object me = this_player();
        if( !arg || !id(arg) )
                return 0;
        if( !present(this_object(),me) )
                return 0;
        if( !query("owner_id") || query("owner_id")!=me->query("id") )
                return err_msg("好似没什么效果。\n");           
        if( me->query("gin")>=me->query_maxgin() )
                return err_msg("没有这个必要。\n");
                
        v = query("level");
        if( v<1 )
                return err_msg("好似没什么效果。\n");
        if( v>5 ) 
                v = 5;  
        me->add("gin",v);
        message_vision(HIC"$N"HIC"吃下一瓶松鹤龟苓膏，感觉活力充沛了不少。\n"NOR,me);
        if(query_amount()>1)
                add_amount(-1);
        else    destruct(this_object());
        return 1;
}

