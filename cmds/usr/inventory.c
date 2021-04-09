#include <ansi.h>
#define MAX_CARRY 50

string inventory_desc(object ob)
{
        return sprintf("%s%s%10s",
                ob->query("equipped")? HIG "☆" NOR:"  ",
        ob->short(),wizardp(this_player())?HIR+" -> "NOR+WHT+file_name(ob)+NOR: "", 
        );
}

varargs int main( object me, string arg)
{
        object  ob, *inv, *tmp;
        int i, j, found;

        if( wizardp(me) ) 
        {
                if(!arg) ob = me;
                else if(arg == "here") ob = environment(me);
                if(!ob) 
                {
                        arg = lower_case(arg);
                        ob = find_player(arg);
                }
                if( !ob ) ob = find_living(arg);
                if( !ob ) ob = present(arg, environment(me));
                if( !ob ) ob = me;
        }
        else    ob = me;

        inv = all_inventory(ob);
        if( !sizeof(inv) ) 
        {
                write((ob==me)? "目前你身上没有任何东西。\n"
                        : ob->short() + "身上没有携带任何东西。\n");
		if( stringp(ob->query_money()) )
        		printf ("◎%s目前有金钱：%s"NOR"。\n",(ob==me)? "你": ob->short(),(string)ob->query_money());
                return 1;
        }
        
        printf("%s身上带着下列这些东西(负重 %d%%)：\n%s\n%s",
                (ob==me)? "你": ob->name(),
                (int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance(),
                implode(map_array(inv, "inventory_desc", this_object()), "\n"),
                stringp(ob->query_money())?(sprintf ("◎%s目前有金钱：%s"NOR"。\n",(ob==me)? "你": ob->short(),(string)ob->query_money())):"",
                 );
        return 1;
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

