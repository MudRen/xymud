#include <weapon.h>

inherit STICK;

void create()
{
        set_name("降魔棒", ({"xiangmo bang", "bang"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
		set("no_sell", 1);
		set("long", "一把淡青色的短棒，上面有暗红流动，如同一条火蛇般绕在棒上。\n");
                set("value", 20000);
                set("material", "steel");
                set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
        }
        init_stick(60);
        setup();
}

