inherit ITEM;

void create()
{
        set_name("钥匙", ({ "key", "yaoshi"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
        }
}

