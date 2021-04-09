
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name("竹刀", ({"zhu dao","dao", "blade"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 100);
                set("material", "wood");
                set("long", "这是一竹制的单刀，是练武时用的．\n");
                set("wield_msg", "$N抽出一把$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入腰后．\n");
        }
        init_blade(15);
        setup();
}

