#include <ansi.h> 
inherit COMBINED_ITEM;

void setup(){}

void create()
{
        set_name("【秘籍】五毒神掌残卷", ({"duzhang book", "book"}));
        set("base_weight",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        	set("long","岭南五万大山中的毒掌精要，可惜是残卷。\n");
                set("unit", "叠");
                set("base_unit","张");
		set("value", 1);
        	set("material", "paper");
        }
        setup();
        set_amount(1);
}

