
#include <weapon.h>
inherit SWORD;
void create()
{
        set_name("木剑", ({"wanju mujian"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100);
                set("material", "wood");
                set("long", "这是一木制的长剑，是练武时用的．\n");
                set("wield_msg", "$N抽出一把$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n插入腰后．\n");
        }
        init_sword(15);
        setup();
}
