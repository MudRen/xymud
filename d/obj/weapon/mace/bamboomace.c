#include <weapon.h>

inherit MACE;

void create()
{
        set_name("็ซน่้ญ", ({"bamboo mace", "mace"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "ๆ");
                set("value", 500);
                set("material", "wood");
        }

        init_mace(15);
        setup();
}

