#include <armor.h>
#include <ansi.h>
inherit ARMOR;
void create()
{
        set_name(HIC"碧色云霞甲"HIR"("HIY"抗魔"HIR")"NOR, ({ "armor","jia" }) );
        set_level(20);
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 50000);
                set("no_put",1);
                set("no_zm",1);
                set("no_dzm",1);
                set("material", "gold");
                set("armor_prop/armor", 120);
		set("armor_prop/armor_vs_spells", 40);
             }
        setup();
}

