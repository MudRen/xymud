#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"护法袈裟"NOR, ({ "jia sha","cloth" }) );
                set("level",6);
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("armor_prop/armor", 15);

        }
        setup();
}

