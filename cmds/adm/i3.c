//inventory.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i;
        object *inv, ob;

        if( wizardp(me) && arg ) {
                ob = find_player(arg);
                if( !ob ) ob = find_living(arg);
                if( !ob ) ob = present(arg, environment(me));
        }

        if( !ob ) ob = me;

        inv = all_inventory(ob);
        if( !sizeof(inv) ) {
                write((ob==me)? "目前你身上没有任何东西。\n"
                        : ob->name() + "身上没有携带任何东西。\n");
                return 1;
        }
        printf("%s身上带着下列这些东西(负重 %d%%)：\n%s\n",
                (ob==me)? "你": ob->name(),
                (int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance(),
                implode(map_array(inv, "inventory_desc", this_object()), "\n") );

        return 1;
}

string inventory_desc(object ob)
{
        return sprintf("%s%s%10s",
                ob->query("equipped")? HIG "☆" NOR:"  ",
        ob->short(),wizardp(this_player())?HIR+" -> "NOR+WHT+file_name(ob)+NOR: "", 
        );
}

int help (object me)
{
        write(@HELP
指令格式: inventory
 
可列出你目前身上所携带的所有物品。
 
注 : 此指令可以 " i " 代替。
 
HELP
);
        return 1;
}


