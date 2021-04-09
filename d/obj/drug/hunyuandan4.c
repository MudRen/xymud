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
        set_name("混元丹", ({"hunyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                set("base_unit", "颗");
                set("long", "一颗略带香气的药丸．\n");
                set("value", 100);
                                set("drug_type", "良药");
        }
        set_amount(1);
        setup();
}

int do_eat(string arg)
{
        int i,amount,ef;
        object me = this_player();
        if( !arg || !id(arg) )
                return 0;
        if( !present(this_object(),me) )
                return 0;
        if ((int)this_player()->query("eff_sen") >=(int)this_player()->query_maxsen())
        {
                write("你现在不需要用"+name()+"。\n");
                return 1;
        }
        else 
        {
                message_vision("$N吃下一些"+name()+"，气色看起来好多了。\n",me);
                i = me->query("max_sen")-me->query("eff_sen");
                i/= 100;
                amount = query_amount();
                if( amount>i )
                        ef = i;
                else    ef = amount;
                me->receive_curing("sen", ef*100);
                me->receive_heal("sen", ef*100);
                if( ef>amount )
                        add_amount(-ef);
                else    destruct(this_object());        
                return 1;
              }
}
