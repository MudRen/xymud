//Cracked by Roath

inherit ITEM;

void create()
{
        set_name("[33måå¾·ç®±[m", ({ "xiang","box" }) );
        set_weight(500);
        set_max_encumbrance(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "å£");
                set("no_get",1);
                set("long", "è¿æ¯ä¸å£æ¥ååæçç®±å­ã\n");
                set("value",900);
        }
}

int is_container() { return 1; }
