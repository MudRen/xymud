inherit ROOM;
#include <ansi.h>

void hear(object me);
void hear_end(object me);

void create()
{
        set ("short", "京兆尹衙门");
        set ("long", @LONG
这里是长安京兆尹的办公衙门，专门负责长安地方的治安。正对面摆着一张高
高的虎头案，京兆尹大人端坐其后，看着案下的百姓。
两边是红衣衙役，手里拿着红漆的水火棍。最边上的衙役手里擎着“肃静”、
“回避”的牌匾。正堂之上高高挂着“明镜高悬”的大匾，不怒而威。
到了此地，有事尽管向大人哭诉(kusu)
LONG);
        set("no_fight", 1);
        set("no_magic", 1);
        set("no_clean_up",1);
        setup();
}

void init ()
{
        object me = this_player();

        add_action("do_none","",1);
        add_action("hear_start","kusu");
        
        if( me->query_temp("衙门/审理") )
                return;
        message_vision("众衙役一声大吼：“威...武......”，众人皆静声不语。\n",me);
        me->set_temp("衙门/审理",1);
        me->save();
        return;
}

int do_none()
{
      string str = query_verb();
    if( !userp(this_player()) )  return 0;
      if( str=="edit" || str=="update" || str=="home" || str=="kusu" || str=="look" || str=="eat" || str=="drink" || str=="chat" || str=="hp" || str=="say" )  return 0;
        write("衙役对你一声大喝：大胆！\n");
        return 1;
}

void dest_obj(object ob)
{
        if( ob ) destruct(ob);
}

int err_msg(string arg)
{
        write(arg);
        return 1;
}

int hear_start(string arg)
{
        object me,*inv;
        int i;
        string msg;

        me = this_player();

        if( me->is_busy() )
                return err_msg("你忙着呢。\n");
        if( time()<me->query_temp("last_kusu")+600 )
                return err_msg("你刚刚哭诉过。\n");                             
        inv = all_inventory();
        reset_eval_cost();
        for(i=0;i<sizeof(inv);i++)
        {
                if( inv[i] && objectp(inv[i]) && !userp(inv[i]) ) 
                { 
                        if( inv[i]->is_character() )
                        {
                                inv[i]->remove_all_killer();
                                all_inventory()->remove_killer(inv[i]);
                        }
                        inv[i]->move("/obj/empty");
                        inv[i]->start_call_out( (: call_other, __FILE__, "dest_obj",inv[i]:), random(5));
                }
        }
        me->start_busy(7);
        me->set_temp("last_kusu",time());
        me->command("say 冤枉啊！！我比窦娥还冤......");
        msg = "京兆尹大人慢慢踱到堂前。\n";
        msg+= "京兆尹一拍惊堂木，道：汝等在堂前喧哗，所为何事？\n";
        msg+= "赌场老板抢步上前，诉说冤情。\n",
        msg+=  CYN"赌场老板说道：大人，此人在小的赌场之内出千，被我等发现，特交大人发落。\n"NOR;
        msg+= "京兆尹大人一拍惊堂木，道：此事属实？\n";
	message_vision(msg,me);
	me->set_temp("block_msg/all", 1);        
        call_out("hear",2+random(3),me);
        return 1;
}

void hear(object me)
{
	string str;
        remove_call_out("hear");        
        if( !me || !present(me,this_object()) )
                return;
	str = CYN"$N"CYN"说道：大人，小的冤枉，小的只是手气好而已。\n"NOR;
	str+= CYN"赌场老板说道：呸，手气好？连赢我五把之多？？\n"NOR;
	str+= CYN"$N"CYN"说道：。。。。\n"NOR;
	str+= CYN"京兆尹大人说道；收声，此事不用查皆已一目了然！\n"NOR;
	me->set_temp("block_msg/all", 0);        
	message_vision(str,me);
	me->set_temp("block_msg/all", 1);        
        call_out("hear_end",1+random(3),me);
}

void hear_end(object me)
{
        int i;
        string value,str,title,zui;
        
        if( !me || !present(me,this_object()) ) 
                return;
	me->set_temp("block_msg/all", 0); 
        title = HIC"【人间界】长安官府(Guan fu)：";

        str = "滋有人告$n"HIC"($i)于赌场扰民滋事，经本官查理：";
        str = replace_string(str,"$n",me->name());
        str = replace_string(str,"$i",capitalize(me->query("id")));

        message_vision("京兆尹大人站将起来，道：众人不必喧哗，听本官宣判。\n");
        i = me->query("赌场/钱");
        if( !i || i<=10000 )
        {
                me->delete("赌场");
                me->set("startroom","/d/city/kezhan");
                me->save();
                zui = "罪名不成立，当即释放。\n"NOR;
                message("channel:chat",title+str+zui,users());
                message_vision("众人听说，唏嘘一番，尽数散去。\n",me);
                message_vision("堂下走来几位官差将$N拎将起来，径往外面去了。\n",me);
                me->move(__DIR__"kezhan",2);
                message_vision("到了，官差将$N往地上一丢，好好告诫了一番，转身离去。\n",me);
                return;
        }
        i = i/20+random(i/10);
        value = MONEY_D->price_str(i);
        if( me->query("balance") >= i || me->query("c_balance") >= i )
        {
                if( random(5)==1 )
                {
                        zui = "证据确凿，判其入监，等候发落！\n"NOR;
                        me->delete_temp("衙门");
                        me->delete("赌场");
                        me->set("startroom","/d/city/dalao");
                        me->set("赌场/钱",i);
                        me->save();   
                        message("channel:chat",title+str+zui,users());
                        message_vision("众人听说，皆大欢喜，尽数散去。\n",me);
                        message_vision("堂下走来几位官差将$N拎将起来，径往大牢去了。\n",me);
                        me->move(__DIR__"dalao",2);
                        message_vision("到了，官差将$N往牢了一丢，转身离去。\n",me);
                        return;
                }
                zui = "证据确凿，判其罚金"+value+"！\n"NOR;
                if( me->query("balance") >= i )
                        me->add("balance",-i);
                else    me->add("c_balance",-i);
                me->delete_temp("衙门");
                me->delete("赌场");
                me->set("startroom","/d/city/kezhan");
                me->save();   
                message("channel:chat",title+str+zui,users());
                message_vision("众人听说，皆大欢喜，尽数散去。\n",me);
                message_vision("$N没甚法子，只得自认倒霉。\n",me);
                me->move(__DIR__"kezhan",2);
                message_vision("$N输掉了官司，灰溜溜的回到客栈。\n",me);
                return;
        }
        else    
        {
                zui = "证据确凿，判其入监，等候发落！\n"NOR;
                message("channel:chat",title+str+zui,users());
                message_vision("众人听说，皆大欢喜，尽数散去。\n",me);
                message_vision("堂下走来几位官差将$N拎将起来，径往大牢去了。\n",me);
                me->delete_temp("衙门");
                me->delete("赌场");
                me->set("startroom","/d/city/dalao");
                me->set("赌场/钱",i);
                me->save();    
                me->move(__DIR__"dalao",2);
                message_vision("到了，官差将$N往牢了一丢，转身离去。\n",me);
                return;
        }
}

