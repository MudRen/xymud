
inherit ITEM;

void create()
{
        set_name("材料盒", ({ "box" }) );
        set_weight(50);
        set_max_encumbrance(5000);
        if( clonep() ) 
        {
                object a;
                seteuid(getuid());
                if(a=new("/d/newguai/tianguan/obj/item"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/d/newguai/tianguan/obj/item"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/d/newguai/tianguan/obj/item"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/d/newguai/tianguan/obj/item"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/d/newguai/tianguan/obj/ding2"))
                        a->move(this_object());
                set_default_object(__FILE__);
           }
        else 
        {
                set("unit", "个");
                set("long", "这是一个寻常的盒子，可以放着一些挑战武器的升级材料。\n");
                set("value", 0);
        }
}

int is_container() { return 1; }


