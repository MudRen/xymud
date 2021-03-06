// flowerseller.c 爱花的小枚儿（卖花和送花）
// modified by amy&&jingxue for xycq 2004/4/15

inherit F_VENDOR_SALE;
#include <ansi.h>

int song_msg();
int ask_lipin();
int songhua(string arg);
int do_song(object me, object obj, object who);

void create()
{
        set_name(HIM"小枚儿"NOR, ({"xiao amy","xiao meier","meier"}));
        set("title",HIC"爱花的"NOR);
        set("name_color","HIM");
        set("gender", "女性");
        set("combat_exp", 1000);
        set("age", 26);
        set("per", 40);
        set("attitude", "friendly");
        set("shen_type", 1);
        set_skill("unarmed", 10);
        set("max_price",20);
        set("vendor_goods", ([
                "flower01":     "/d/wiz/flower/obj/flower0",
                "flower02":     "/d/wiz/flower/obj/flower1",
                "flower03":     "/d/wiz/flower/obj/flower2",
                "flower04":     "/d/wiz/flower/obj/flower3",
                "flower05":     "/d/wiz/flower/obj/flower4",
                "flower06":     "/d/wiz/flower/obj/flower5",
                "flower07":     "/d/wiz/flower/obj/flower6",
                "flower08":     "/d/wiz/flower/obj/flower7",
                "flower09":     "/d/wiz/flower/obj/flower8",
                "flower10":     "/d/wiz/flower/obj/flower9",
                "flower11":     "/d/wiz/flower/obj/flower10",
                "flower12":     "/d/wiz/flower/obj/flower11",
                "flower13":     "/d/wiz/flower/obj/flower12",
                "flower14":     "/d/wiz/flower/obj/flower13",
                "flower15":     "/d/wiz/flower/obj/flower14",
        ]) );
        set("inquiry", ([
                "songhua":      (:song_msg:),
                "送花":         (:song_msg:),
            	"节日快乐":    	(:ask_lipin:),
            	"五一礼包":    	(:ask_lipin:),
        ]));
        setup();
}

void init()
{
        ::init();       
        add_action("do_vendor_list", "list");
        add_action("songhua", "songhua");
        add_action("songhua", "送花");
        add_action("do_bid","bid");
}

int song_msg()
{
        object me=this_player();
        if (!userp(me))
        {
                command("qi");
                command("shake");
                return 1;
        }
        tell_object(me, HIW"小枚儿欠身说到：“感谢客官光临小店，您先在这里将花买好，
然后告诉小女要送给谁，小女一定托人为您把花送到。
命令："HIY"songhua flower_id to player_id"HIW"
我们花店收费规则是：送花费用最低十两纹银。
每一朵花收取十两纹银的送花费。”
"NOR);
        return 1;
}

int songhua(string arg)
{
        object me=this_player();
        object who, obj, obj2;
        string target, item;
        int amount, rev_val;
        if (!userp(me))
        {
                command("qi");
                command("shake");
                return 1;
        }
        if (userp(me) && !wizardp(me) )
        {
                if (time()- me->query_temp("last_songhua_time") < 10)
                        return notify_fail(WHT"你没看到本小姐正忙嘛～～～～～\n"NOR);
                me->set_temp("last_songhua_time",time());
        }  
        if( sscanf(arg, "%s to %s", item, target)==2 );
                else return notify_fail("你要送花给谁呢？\n");
        who = LOGIN_D->find_body(target);
        if (!who) 
                return notify_fail("咦．．． 有这个人吗？\n");
        if(who->query("env/no_accept"))
                return notify_fail("对方好象不愿意收下别人的东西。\n");
        if(sscanf(item, "%d %s", amount, item)==2) 
        {
                if( !objectp(obj = present(item, me)) ) 
                        return notify_fail("你身上没有这种花哦。\n");
                if( amount < 1 )
                        return notify_fail("你至少要送一朵" + obj->name() + "。\n");
                if( amount > obj->query_amount() ) 
                        return notify_fail("你没有那么多的" + obj->name() + "。\n");
                if( !obj->query("can_song") ) 
                        return notify_fail("我只送花哦，" + obj->name() + "我可没空代你送。\n");
                else if( amount == (int)obj->query_amount() )
                        return do_song(me, obj, who);
                else    {
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        rev_val = do_song(me, obj2, who);
                        if( rev_val )
                                obj->set_amount( (int)obj->query_amount() - amount );
                        else
                                destruct(obj2);
                        return rev_val; 
                        }
        }
        if(!objectp(obj = present(item, me)))
                return notify_fail("你身上没有这种花哦。\n");
        if( !obj->query("can_song") ) 
                return notify_fail("我只送花哦，" + obj->name() + "我可没空代你送。\n");
        return do_song(me, obj, who);           
}
int do_song(object me, object obj, object who)
{
        int money_amount;
        
        money_amount=obj->query_amount();
        if(obj->query_amount()<10)
                money_amount=10;
        if(obj->query_amount()>1000)
                money_amount=1000;
        
        if (me->query("balance") < (money_amount*100) ) 
                return notify_fail("很抱歉，您的存款不足送花费用("+price_string(money_amount*100)+")了。\n");
        me->add("balance",-money_amount*100);
        message_vision("$N对$n说道：“送花共收您"+price_string(money_amount*100)+"”。\n",this_object(),this_player());
        
        if( obj->move(who) ) 
        {
                string unit;
                unit=obj->query("unit");
                if(strlen(unit)<2) unit="个";
                tell_object(me, "你将身上的"+obj->name()+NOR"拿出交给小枚儿。\n"HIM"小枚儿"NOR"对你说道：“好吧，小女子定会将花送给"+who->name()+NOR"。\n"NOR);
                tell_object(who, "一个"HIM"花仙子"NOR"降临在你旁边，高兴的对你说道：\n“这是"HIG+me->name()+NOR"送给你的"+obj->name()+NOR"，祝你天天开心！”\n"NOR);
                if(!userp(who) && !userp(obj)) destruct(obj); 
                me->start_busy(1);
                return 1;
        }
        else 
                return 0;       
        return 1;
}
string price_string(int v)
{
        if( v%10000 == 0 )
                return chinese_number(v/10000) + "两黄金";
        if( v%100 == 0 )
                return chinese_number(v/100) + "两白银";
        return chinese_number(v) + "文铜板";
}

int ask_lipin()
{ 
        object ob;
        if (!this_player()->query("giftmark/2004-5-1"))
        {
                command("say 恭喜恭喜，节日快乐！\n");
                ob=new("d/wiz/obj/lipin");
                ob->set("onwerid",this_player()->query("id")); 
                ob->move(this_player()); 
                message_vision("\n$N递给$n一个特制的大礼包。\n",  this_object(),this_player());
//                this_player()->set("giftmark/2004-5-1",1); 
                return 1;
        }
        message_vision("\n$N对$n说道：你拿过礼包了吧？不要太贪心哦！\n",  this_object(),this_player());
        return 1;
}
int do_bid(string arg)
{
       object who = this_player();
       message_vision("$N想买店，看看是小枚儿开的，就没敢盘。\n",who);
       return 1;
}
