// Room: /changan/southseashore.c
//cglaem...12/12/96.
#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "南海之滨");
        set ("long", @LONG

南海之滨。往北是一条宽阔笔直的官道，足可容得下十马并驰。
往南则是一片汪洋大海，不知通向何方。西南海面上隐隐可见
一小岛。浅海近岸处还有几个游泳的人。
LONG);

        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"broadway5",
                "east" : __DIR__"seashore1",
                "west" : "/d/jz/egate",
        ]));
        set("outdoors", 1);
        setup();
        //remove_call_out("random_item");
//        call_out("random_item",5+random(6));
}

void init()
{
        add_action("do_swim", "swim");
}

int do_swim()
{
        object me;
        me = this_player();
        if( me->is_busy() || me->query_temp("pending") )
                return notify_fail("你现在正忙着呢。\n");
        message_vision(HIY "$N纵身一跃，跳入海中。只见$N使足了全身力气，手足并用，不一会儿就游到了海中小岛上。\n" NOR, me);
        me->move("/d/nanhai/island");
        message_vision(HIY "只见$N浑身湿漉漉地从海里爬了上来。\n" NOR, me);
        me->receive_damage("kee", 20);
        me->receive_damage("sen", 20);
        return 1;
}
/*
void random_item()
{
        mapping dd,data = ([ ]);   
        object item,ding,npc,*it,*o_it;
        string tmp,str;
        int j,k,m,i = 0;      
        int num = 24;

        remove_call_out("random_item");
        call_out("random_item",1000+random(600));
        //清理地图上残存的材料
        o_it = children("/d/newguai/tianguan/obj/item");
        for( m=0;m<sizeof(o_it);m++ )
        {
                if( o_it[m] && environment(o_it[m]) 
                && environment(o_it[m])->is_character()
                && !userp(environment(o_it[m])) )
                        destruct(o_it[m]);
        } //清理完毕

        //清理地图上残存的鼎
        o_it = children("/d/newguai/tianguan/obj/ding");
        for( m=0;m<sizeof(o_it);m++ )
        {
                if( o_it[m] && environment(o_it[m]) 
                && environment(o_it[m])->is_character()
                && !userp(environment(o_it[m])) )
                        destruct(o_it[m]);
        } //清理完毕
        //洗点石                
        if( random(5)==2 )  
        {
                ding = new("/d/newguai/tianguan/obj/clear_stone"); 
                if( !ding )
                        return;
                npc = SDS_D->random_npc(this_object());
                if( !npc || !environment(npc) || !ding->move(npc) )
                {
                        destruct(ding); 
                        return;
                }
                tmp = MISC_D->find_place(environment(npc));
                tmp+= "的"+npc->name();
                message("channel:rumor",HIM"【小道消息】某人：听说远古神器"+ding->name()+HIM"被"+tmp+HIM"得到了。\n"NOR,users());
                return;
        }
        //鼎
        m = random(4)+1;
        str = "";
        for(i=0;i<m;i++)
        {
                ding = new("/d/newguai/tianguan/obj/ding"); 
                if( !ding )
                        continue;
                npc = SDS_D->random_npc(this_object());
                if( !npc || !environment(npc) || !ding->move(npc) )
                {
                        destruct(ding); 
                        continue;
                }
                tmp = MISC_D->find_place(environment(npc));
                if( random(2) )
                        tmp = SDS_D->random_msg(tmp)+"的"+npc->name();
                else    tmp+= "的"+SDS_D->random_msg(npc->name());
                str+= tmp+" ";
        }

        dd = query_temp("宝物");
        if( dd && mapp(dd) )
        {
                it = keys(dd);
                k = sizeof(it);
                while(k--)    
                {
                        if( it[k] && environment(it[k])->is_character() 
                        && !userp(environment(it[k])) )
                                destruct(it[k]);
                }
        }
        num = num/2+random(num/2);
        for(j=0;j<num;j++)
        {
                reset_eval_cost();
                item  = new("/d/newguai/tianguan/obj/item");
                if( !item )  continue;
                npc = SDS_D->random_npc(this_object());
                if( !npc || !living(npc) || !environment(npc) 
                || userp(environment(npc)) )
                        continue;
                if( item->move(npc) )
                {
                        data[item] = npc;
                        i++;
                }
        }
        if( i>0 )
                message("channel:rumor","\n\n 但见天空“轰隆”一声，响起一道炸雷，天空中不知什么炸出"+chinese_number(i)+"道流星，散落到了各地。。。。\n\n",users());
        set_temp("宝物",data);
        CHANNEL_D->do_channel(this_object(),"rumor","听说远古神器"+ding->name()+HIM"被"+str+HIM"分别得到了。");
}

*/
