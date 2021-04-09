// jinchuang.c 金创药
inherit COMBINED_ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("金创药", ({"jinchuang yao", "yao", "jinchuang"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("base_unit","包");
                set("unit","些");
                set("long", "这是一包治伤的金创药。\n");
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
        if (this_player()->query("eff_kee") == this_player()->query_maxkee())
        {
                write("你现在不需要用金创药。\n");
                return 1;
        }
        else 
        {
                message_vision("$N吃下一些金创药，气色看起来好多了。\n",me);
                i = me->query("max_kee")-me->query("eff_kee");
                i/= 100;
                amount = query_amount();
                if( amount>i )
                        ef = i;
                else    ef = amount;
                me->receive_curing("kee", ef*100);
                me->receive_heal("kee", ef*100);
                if( ef>amount )
                        add_amount(-ef);
                else    destruct(this_object());        
                return 1;
              }
}
