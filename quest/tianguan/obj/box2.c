inherit ITEM;

void create()
{
        set_name("材料匣", ({ "box" }) );
        set_weight(1000);
        set_max_encumbrance(50000);
        if( clonep() ) 
        {
                object a;
                seteuid(getuid());
                if(a=new("/quest/tianguan/obj/box"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/quest/tianguan/obj/box"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/quest/tianguan/obj/box"))
                        a->move(this_object());
                seteuid(getuid());
                if(a=new("/quest/tianguan/obj/box"))
                        a->move(this_object());

                seteuid(getuid());
                if(a=new("/quest/tianguan/obj/box"))
                        a->move(this_object());

                seteuid(getuid());
                if( random(4)==2 && a=new("/quest/tianguan/obj/box") )
                        a->move(this_object());

                seteuid(getuid());
                if( random(3)==2 && a=new("/quest/tianguan/obj/box") )
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

