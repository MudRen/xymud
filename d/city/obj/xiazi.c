#include <ansi.h>
inherit ITEM;
#include "/cmds/std/valid_move.h"

void create()
{
set_name("挂机小匣子",({"xiazi","box"}));
set_weight(5000);
if ( clonep() )
        set_default_object(__FILE__); 
else    {
        set("unit","包");
        set("no_drop",1);
set("value",500);
        set("no_give",1);
        set("no_put",1);
        set("no_put",1);
        set("long","这个是给挂机的玩家准备的神秘的小匣子，你可以拆(chai)开来看看。\n");
        }
setup();
}

void init()
{
add_action("do_chai","chai");
}

int do_chai(string arg)
{
object ob;      
object me = this_player();
if ( !arg || !id(arg) || me!=environment() )
        return 0;
if ( !valid_move(me) )
        return notify_fail("你现在正忙着呢。\n");
        
message_vision(YEL"$N"YEL"小心翼翼的拆开$n"YEL"。\n"NOR,me,this_object());
ob = new("/d/obj/misc/xueshan-map");
if ( ob->move(me) )
        write(YEL"你得到了一张"+ob->name()+YEL"。\n"NOR);
ob = new("/d/penglai/npc/obj/ditu");
if ( ob->move(me) )
        write(YEL"你得到了一张"+ob->name()+YEL"。\n"NOR);
ob = new("/d/obj/magic/bishuizhou");
if ( ob->move(me) )
        {
        message_vision("袁守诚递给$N一本〖无字天书〗。\n",me);
        message_vision("$N撕开无字天书的背页，从里面小心翼翼地取出一张小纸片。\n",me);
        }
me->set_temp("obstacle/jinping_give_hulu",1); 
write(YEL"你得到了一个油葫芦。\n"NOR);
write("你给守门牛精一个油葫芦。\n");
message_vision ("守门牛精说道：谢谢！\n",me); 
ob = new("/d/qujing/pansi/obj/money");
if ( ob->move(me) )
        message_vision ("断肠妇人给$N一张黄钱。\n",me); 
me->set_temp("erlangpass", 1); 
write("庙祝笑道：多谢"  + RANK_D->query_respect(me) + "，二郎真君定会保佑你。\n");
me->start_busy(1);
destruct(this_object());
return 1;
}       

