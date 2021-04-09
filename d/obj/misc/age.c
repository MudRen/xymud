// hunyuandan.c 混元丹 

inherit COMBINED_ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("寿元丹", ({"shouyuan dan", "dan"}));
                set("unit", "些");
                set("base_unit", "颗");
                set("long", "一颗带着浓郁香气的灵丹，吃了可以增加寿元。\n");
                set("value", 0);
                set("no_put",1);
                set("no_give",1);
                set("no_get",1);
                set("drug_type", "良药");
        set_amount(1);
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        
        if( !arg || !id(arg))
                return 0;
        if( !present(this_object(),me) )
                return 0;                
        if( me->query("life/live_forever") )
                return err_msg("你已长生不老了，吃这东西没用。\n");                
        me->add("life/life_time",5);
        message_vision("$N吃下一颗寿元丹，背后浮现出一尊南极仙翁的虚像。\n",me);
        if(query_amount()>1)
                add_amount(-1);
        else    destruct(this_object());
        return 1;
}
