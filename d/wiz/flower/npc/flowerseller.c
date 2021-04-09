// flowerseller.c 爱花的小枚儿（卖花和送花）
// modified by amy&&jingxue for xycq 2004/4/15
inherit F_VENDOR_SALE;
#include <ansi.h>

string song_msg();
string ask_lipin();
string ask_lipin1();
string ask_cake();
string xitang();
int songhua(string arg);
int do_song(object me, object obj, object who);
string birthday();
string shuangdan();

void create()
{
       string msg;
        set_name("小枚儿", ({"xiao amy","xiao meier","meier"}));
msg = @LONG;
NORWHT    NORHIC☆.                                 NORREVYEL▍                           ╲/ NOR       NOR　
NORWHT   NORHIC· ★                                NORBYELHIC                              NORREVYEL│ NOR       NOR　
NORWHT  NORHIC.' ~  ﹡                             NORREVYEL▍NORBYELWHT▁                           NORREVYEL│ NOR       NOR
NORWHT        NORHIC☆﹡.                        NORHIW▕REVHIW  NORHBWHTHIW◣ NORBYELWHT◣ NORBYELHIY▁▄▆NORREVHIY      NORBYELHIY▅▄▁    NORYEL▏       NOR　
NORYEL       NORHIC★.                        NORWHT◢NORHIW◣NORREVHIW      NORHBWHTHIW▋NORREVHIY                      NORBYELHIY▅ NORYEL▍NOR　
NORYEL          NORHIC`'★                  NORWHT◢NORHBWHTWHT NORREVHIW    NORHBWHTHIW◥NORREVHIW    NORREVHIY                          NORHIY▍       NOR　
NORHIY       NORHIC‘﹡☆        NORYEL▁▁      NORHBWHTBLK▋NORHBWHTHIW◢NORREVHIW  NORHBWHTHIW◤NORHBWHTHIM●NORHBWHTHIW◢NORREVHIW  NORHBWHTHIY◥NORBYELHIY◤             ◥NORREVHIY        NORHIY◣      NOR　
NORHIY              NORHIC.★     HBYELWHT◣  NORREVYEL  NORREVYEL  NORYEL▅▅NORHBWHTYEL NORREVHIW    NORHBWHTHIW◣NORREVHIW  NORHBWHTHIW◤NORBYELWHT◤                       NORBYELHIY◥NORREVHIY  NOR      NOR　
NORHIY             NORHIC☆      NORWHT▕HBYELWHT▇▂       NORREVHIW    NORHBWHTHIW◤NORBYELHIW◥NORWHT█NORBYELHIW◤                           NORREVYEL◥NOR     NOR　
NORWHT             NORHIC﹡    ,  NORWHT▕NORREVWHT    NORHBYELWHT▂    NORBYELHIW◥NORHIW█NORBYELWHT◤                                   NOR     NOR　
NORWHT              NORHIC‘ .·    NORWHT◥NORREVWHT    NORHBYELWHT▆▃                ▁▄NORHBWHTMAG▅NORBMAGBLK︳HBYELWHT▆▆▅▃         NOR     NOR　
NORWHT                  NORHIC★      NORWHT◥NORHBWHTWHT      NORBMAGWHT◤NORHBWHTMAG▄▂ ▂▂HBYELWHT▄NORREVYEL▄NORWHT◥NORBYELWHT NORBYELWHT▇NORBMAGBLK╱ NORBMAGWHT◢NORWHT◤NORHBWHTBLK▅NORWHT◥NORBMAGWHT▍NORHBWHTMAG▆▃    NOR     NOR　
NORWHT                   NORHIC﹡  .         NORBMAGHIC  NORBMAGBLK◢  /│  NORWHT◤ NORHIW▕▊NORHBWHTHIW NORHBWHTMAG◢NORBMAGWHT◢NORBYELWHT◤NORWHT▌NORHIW▇   NORBMAGBLK◣\ ﹨\NORBMAGYEL◥NORBYELYEL NOR     NOR　
NORWHT                     NORHIC' ﹡      NORBMAGBLK▉NORMAG◤  BMAGMAG  NORBMAGBLK\ \NORBMAGWHT▕█NORWHT   NORHIW◤NORHBWHTBLK▎     NORWHT▋NORWHT◤ NORBMAGBLK▉NORBMAGWHT▎ NORBMAGBLK\ |/ NORWHT█     NOR　
NORWHT     NOR                    NORHIC☆ a        NORBMAGBLK◣/\,'\NORBMAGWHT◥NORWHT◣  NORHBWHTBLK◤       ◥NORWHT NORHIW▕NORBYELWHT◢NORBMAGWHT NORBMAGBLK)│|NORBMAGWHT◢NORWHT◤     NOR　
NORWHT    NOR                          NORHICr █◣    NORBMAGBLK◣╲\NORBYELWHT◤ NORHBWHTRED▃          ▃NORWHT▆NORBYELWHT█NORBMAGBLK/ /NORMAG◤         NOR　
NORMAG    NORHIC                          NORHBCYNHIC t◥█NORWHT      NORBMAGWHT NORREVMAG  NORWHT◥NORHBWHTWHT NORREVWHT  NORHBWHTWHT          NORREVWHT  NORBYELWHT◢NORBMAGWHT◤ NORBMAGBLK/◢NOR          NOR　
NORWHT                 NORHIC~            NORCYN◥NORBCYN█NORHBCYNHIC◥NORWHT      NORMAG◥▏  NORHBWHTBLK▆▃NORHBWHTHIW▂▁▁▂NORHBWHTBLK▅NORBMAGBLK◣ ◢NOR             NOR　
NORWHT                                    NORHIB★       NORWHT▄NORHBWHT  NORHBWHTHIW◢NORHBWHT         NORBYELWHT█◣NORHBWHTBLK◥NOR             NOR　
NORWHT       NORHIW美 丽 NORWHT的 NORWHT魔 NORWHT法                 NORHIY╲NORWHT▅NORYEL  NORBYELYEL NORBYELWHT▄▅NORHBWHT        NORHBWHTHIW█NORHBWHT  NORHBWHTHIW NORWHT◥NORBYELWHT▊ NORWHT▎           NOR　
NORWHT                                      NORHBWHTBLK▍~)NORREVYEL▂▄NORWHT  NORHBWHT              NORHBWHTHIW NORBYELHIW NORHBWHTYEL▅NORHBWHTBLK◢NOR            NOR　
NORWHT            每 NORWHT个 NORWHT人 NORHIW都 有                NORHIY╲  NORWHT▕NORHBWHT                NORYEL◤              NOR　
NORYEL                                             NOR▕HBWHT                  NORHIW  amy          NOR　
NOR 
LONG;
                  msg = COLOR_D->replace_color(msg,1);                  set("long",msg+"\n");
        set("title",HIC"爱花的"NOR);
        set("name_color","HIM");
        set("gender", "女性");
        set("combat_exp", 1000);
        set("age", 26);
        set("per", 400);
        set_level(39);
        set("attitude", "friendly");
        set("shen_type", 1);
        set_skill("unarmed", 10);
        set("max_price",160);
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
/*
        set("inquiry", ([
                "送花":         (:song_msg:),
                "粽子":     (:ask_lipin1:),
                "六一快乐":     (:ask_lipin:),
                "五一快乐":     (:ask_cake:),
                "结婚"  :  ( : xitang :),
                "生日快乐"  :  ( :birthday :),
//                "双蛋礼物" : (: shuangdan :),
        ]));
*/
        setup();
        carry_object("/d/obj/cloth/skirt")->wear();
}

void init()
{
        ::init();       
        if ( !userp(this_player()) )
                return; 
        add_action("do_vendor_list", "list");
        add_action("songhua", "songhua");
        add_action("songhua", "送花");
        add_action("do_bid","bid");
        if( wizardp(this_player()) )
                add_action("do_open","open");
}

int do_open()
{
        if( !wizardp(this_player()) )
                return 0;
        if( query("生日") )
        {
                write("生日模式已经开了。\n");
                if( !query("双蛋") )
                {
                	set("双蛋",1);
                	write("你打开了双蛋模式。\n");
                }
                else	write("双蛋模式已经开了。\n");	
                return 1;
        }
        set("生日",1);
        write("你打开了生日模式。\n");
        return 1;
}
        
string song_msg()
{
        object me = this_player();
        if ( !userp(me) )
                return 0;
        return "感谢客官光临小店，您先在这里将花买好，然后告诉小女要送给谁，小女一定托人为您把花送到。
命令："NOR HIY"songhua flower_id to player_id"NOR CYN"我们花店收费规则是：送花费用最低十两纹银。
每一朵花收取十两纹银的送花费。”"NOR;
}

int err_msg(string arg)
{
        write(arg);
        return 1;
}       

int songhua(string arg)
{
        object who, obj, obj2 ,me = this_player();
        string target, item;
        int amount, rev_val;

        if  ( !userp(me) )
                return 1;
        if  ( userp(me) && !wizardp(me) )
        {
                if (time()- me->query_temp("last_songhua_time") < 10)
                        return err_msg(WHT"你没看到本小姐正忙嘛～～～～～\n"NOR);
                me->set_temp("last_songhua_time",time());
        }  
        if ( !arg || sscanf(arg, "%s to %s", item, target)!=2 )
                return err_msg("你要送花给谁呢？\n");
        who = LOGIN_D->find_body(target);
        if (!who) 
                return err_msg("咦．．． 有这个人吗？\n");
        if(who->query("env/no_accept"))
                return notify_fail("对方好象不愿意收下别人的东西。\n");
        if(sscanf(item, "%d %s", amount, item)==2) 
        {
                if( !objectp(obj = present(item, me)) ) 
                        return err_msg("你身上没有这种花哦。\n");
                if( amount < 1 )
                        return err_msg("你至少要送一朵" + obj->name() + "。\n");
                if( amount > obj->query_amount() ) 
                        return err_msg("你没有那么多的" + obj->name() + "。\n");
                if( !obj->query("can_song") ) 
                        return err_msg("我只送花哦，" + obj->name() + "我可没空代你送。\n");
                else if( amount == (int)obj->query_amount() )
                        return do_song(me, obj, who);
                else    
                {
                        obj2 = new(base_name(obj));
                        obj2->set_amount(amount);
                        rev_val = do_song(me, obj2, who);
                        if( rev_val )
                                obj->set_amount( (int)obj->query_amount() - amount );
                        else    destruct(obj2);
                        return rev_val; 
                }
        }
        if(!objectp(obj = present(item, me)))
                return err_msg("你身上没有这种花哦。\n");
        if( !obj->query("can_song") ) 
                return err_msg("我只送花哦，" + obj->name() + "我可没空代你送。\n");
        return do_song(me, obj, who);           
}

int do_song(object me, object obj, object who)
{
        int money_amount;

        if ( !me || !obj || !who )
                return 0;
        money_amount=obj->query_amount();
        if ( obj->query_amount()<10)
                money_amount=10;
        if(obj->query_amount()>1000)
                money_amount=1000;
        if (me->query("balance") < (money_amount*100) ) 
                return err_msg("很抱歉，您的存款不足送花费用("+price_string(money_amount*100)+")了。\n");
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
        else    return 0;       
}

string price_string(int v)
{
        return MONEY_D->money_str(v,1);
}

string ask_lipin()
{ 
        string str;     
        object ob,me = this_player();
        if (!me->query("giftmark/2005-6-1"))
        {
                ob = new("d/wiz/obj/lipin");
                if ( !ob )
                        return "六一礼物发完了。。。。";
                ob->set("onwerid",this_player()->query("id")); 
                if ( ob->move(me) )
                { 
                        message_vision("\n$N递给$n一个可爱的泡泡。\n",  this_object(),this_player());
                        str = "祝 $M 童心常葆，六一快乐！！\n";
                        str+= 
HIY"\n\n     │  ╱
         ╮
      "HIR"～ ～ "HIY"──"HIC"   ╬╮
       "HIR"︶"HIY"╯     "HIC" ╬╬╯
       │  ╲   "HIC" ║╯☉
       │       
                 "HIM"  ╭╯
                 "HIM"  ╚╬
                 "HIM"  ☉╯╯
             
             "HIW"    ╩
             "HIW"   ╯ ☉
             
             "HIG"    ╰═\n\n"NOR;
                        str = replace_string(str,"$M",me->name(1));
                        set("channel_id","欢乐六一");
                        CHANNEL_D->do_channel(this_object(),"chat",str);
                        delete("channel_id");
                        me->set("giftmark/2005-6-1",1); 
                        me->save();
                        return "恭喜恭喜，节日快乐！";
                }
                return "你身上东西太多了。";    
        }
        return "你拿过礼包了吧？不要太贪心哦！";
}

string ask_lipin1()
{
        object ob,me = this_player();
        if ( !me->query("giftmark/2005-6-11") )
        {
                ob=new("d/wiz/obj/zongzi");
                if ( !ob )
                        return "端午礼物发完了。。。。";
                ob->set("onwerid",this_player()->query("id")); 
                if ( !ob->move(this_player()) )
                        return "你身上东西太多了。";
                me->set("giftmark/2005-6-11",1); 
                me->save();
                set("channel_id","端午龙舟");
                CHANNEL_D->do_channel(this_object(),"chat","祝"+me->query("name")+"节日愉快！天天开心！");
                delete("channel_id");
                message_vision("\n$N递给$n一只大粽子。\n",  this_object(),this_player());
                return "恭喜恭喜，端午节快乐！";
        }
        return "你拿过粽子了吧？不要太贪心哦！";
}

string ask_cake()
{
        object ob,me = this_player();
        if ( !me->query("giftmark/2007-5-1"))
        {
                ob=new("d/wiz/obj/cake1");
                if ( !ob )
                        return "五一礼物发完了。。。。";
                ob->set("onwerid",this_player()->query("id"));
                if ( !ob->move(this_player()) )
                        return "你身上东西太多了。";
                me->set("giftmark/2007-5-1",1);
                me->save();
                message_vision("\n;$N递给$n一块蛋糕。\n",  this_object(),this_player());
                set("channel_id","金色五一");
                CHANNEL_D->do_channel(this_object(),"chat","祝"+me->query("name")+"节日愉快！天天开心！");
                delete("channel_id");
                return "恭喜恭喜，五一快乐！";
        }
        return "你吃过蛋糕了吧？不要太贪心哦！";
}

int do_bid(string arg)
{
        object who = this_player();
        message_vision("$N想买店，看看是小枚儿开的，就没敢盘。\n",who);
        return 1;
}

string xitang()
{
        string *msg;   
        object me = this_player();

        if ( me->query_temp("amy_xitang") )
                return "不是刚刚给你了吗？";
        msg = ({
                "初笄梦桃李，新妆应摽梅。疑逐朝云去，翻随暮雨来。",
                "乌鹊桥成上界通，青鸾飞入合欢宫。水如碧玉山如黛，露似珍珠月似弓。",
                "垂手乱翻雕玉佩，醉吟偏称绿荷筩。已看翡翠兰苕上，四座筵开语笑同。",
                "姓氏今为第几仙，霓裳欲向大罗天。鱼吹细浪摇歌扇，鸟弄新声杂管弦。",
                "解释春风无限恨，可知今夕是何年。酒花荡漾金鸾里，写尽檀郎锦绣篇。",
        });     
        if ( time()<me->query_temp("amy_xitang_talk")+300 )
                return 0;
        me->set_temp("amy_xitang_talk",time());
        QUEST_D->random_emote(this_object(),me->query("id"),(random(3)-1));        
        return msg[random(sizeof(msg))];
}

//amy生日
string birthday()
{
        object cake,me = this_player();
        
        if( !query("生日") || time()<me->query_temp("amy_birthday_talk")+300
          || me->query("giftmark/2010-12-19") )
                return "祝我生日快乐？谢谢，等阿枚女神到时来了发礼物给你哈。";
        me->set_temp("amy_birthday_talk",time());
        cake = new("/d/wiz/obj/amy-cake");
        if( !cake )
                return "祝我生日快乐？谢谢，等阿枚女神到时来了发礼物给你哈。";
        if( cake->move(me) )
        {
                message_vision("$n递给$N一个生日蛋糕。\n",me,this_object());
                return "祝我生日快乐？谢谢，呐，这是阿枚女神给你的礼物哈。";                   
        }
        else
        {
                destruct(cake);
                return "祝我生日快乐？谢谢，不过你背包满了，没法给你蛋糕哦。";
        }
}

//双蛋礼物
string rmsg()
{
	string msg,tmp,*temp,*wizs;
	
	temp = ({
		"圣诞快乐",
		"元旦快乐",
		"心想事成",
		"快乐如意",
		"双蛋吉祥",
		"合家安康",
		"万事如意",
	});	
	wizs = ({
		"阿枚","阿Za","眠兔","囧囧","舞雪","青牛",
	});	
	
	switch(random(10))
	{
		case 0 :
		case 9 :
		case 2 :
			msg = @MSG
   HBBLUHIY		         泥潭无岁月     感谢一路相随                	NOR
   HIR       │       │       │       │       │       │       │       │NORBLINKHIY    .NOR        
   HIR    ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮ ╭┴┴╮NOR
   BLINKHIM  .NORHIR │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NORBLINKHIG     .NOR
   HIR    │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NORBLINKHIY.NORHIR│NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NOR
   BLINKHIY .NORHIR  │NORHBREDHIY $1 NORHIR│ │NORHBREDHIY $2 NORHIR│ │NORHBREDHIY 祝 NORHIR│ │NORHBREDHIY 您 NORHIR│ │NORHBREDHIY &1 NORHIR│ │NORHBREDHIY &2 NORHIR│ │NORHBREDHIY &3 NORHIR│NORBLINKHIB.NORHIR│NORHBREDHIY &4 NORHIR│NOR
   BLINKHIC   .NORHIR│NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NORBLINKHIC . NOR
   HIR    │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NORBLINKHIY.NORHIR│NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│ │NORREVRED    NORHIR│NORBLINKHIM.NORHIR│NORREVRED    NORHIR│ │NORREVRED    NORHIR│NOR
   BLINKHIG  .NORHIR ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯ ╰┬┬╯NOR
   HIR       !!       !!       !!       !!       !!       !!       !!       !!NOR   
   HIR       ;;       ;;       ;;       ;;       ;;       ;;       ;;       ;;NOR
MSG;
			break;
		case 6 :
		case 3 :
msg = @MSG
  	HBBLUHIB╳╳￣╳╳￣╳╳￣NORHIB╳╳￣╳╳￣╳╳￣╳╳￣╳╳￣╳╳￣╳╳NORHBBLUHIB￣╳╳￣╳╳￣╳╳NOR
  	HBBLUHIB  ︳NORHIB╳  ︳╳  ︳╳  ︳NORHIY巫NORHIB  ︳NORHIY师NORHIB  ︳NORHIY$1NORHIB  ︳NORHIY$2NORHIB  ︳NORHIY祝NORHIB  ︳NORHIY您NORHIB  ︳╳  ︳╳  ︳╳  NORHBBLUHIB︳NOR
  	HBBLUHIB╳NORHIB╳  ╳╳  ╳╳  ╳╳  ╳╳  ╳╳  ╳╳  ╳╳__╳╳__╳╳__╳╳__╳╳__╳NORHBBLUHIB╳NOR
  	HBBLUHIB╳NORHIB╳￣╳╳￣╳╳￣╳╳￣╳╳￣╳╳￣╳╳￣╳╳  ╳╳  ╳╳  ╳╳  ╳╳  ╳NORHBBLUHIB╳NOR
  	HBBLUHIB  ︳NORHIB╳  ︳NORHIY&1NORHIB  ︳NORHIY&2NORHIB  ︳NORHIY&3NORHIB  ︳NORHIY&4NORHIB  ︳NORHIY，NORHIB  ︳NORHIY&6NORHIB  ︳NORHIY&7NORHIB  ︳NORHIY&8NORHIB  ︳NORHIY&9NORHIB  ︳NORHIY。NORHIB  ︳╳  NORHBBLUHIB︳NOR
  	HBBLUHIB╳╳__╳╳__╳╳__NORHIB╳╳__╳╳__╳╳__╳╳__╳╳__╳╳__╳╳NORHBBLUHIB__╳╳__╳╳__╳╳NOR
  	    HIY                       泥潭无岁月 感谢一路相随NOR  	
MSG;
			break;		
		case 1 :
		case 5 :
		case 7 :
			msg = @MSG
                     NORBLINKHIM﹡NOR          │       BLINKHIC﹡NOR
                               ◢◣NOR           REVHIM    NOR
                             ◢NORBGRNGRN    NOR◣NOR         HIM▓▓NOR      BLINKWHT﹡NOR
       BLINKHIW﹡NOR                   ◢NORBGRNGRN  NORBGRNHIM∴NORBGRNGRN  NOR◣NOR        REVHIM    NOR
                          ◢NORBGRNGRN  NORBGRNHIM﹡NORBGRNGRN      NOR◣NOR      REVHIM        NORHIM◣NOR
              NORWHT＊NOR         BLINKHIR★NOR◢NORBGRNHIR.NORBGRNGRN    NORBGRNHIW◎HIM.NOR◣BLINKHIR ●NOR    HIM◥NORREVHIM      NORHIM◤NOR
  HIY亲爱的朋友NOR             NOR◢NORBGRNGRN   NORBGRNHIW.NORBGRN    NORBGRNHIC.NORBGRN   NOR◣NOR
                       NOR◢NORBGRNGRN       NORBGRNHIY..NORBGRNGRN       NOR◣NOR
      HIY祝您    NOR       NOR◢NORBGRNGRN         NORBGRNHIR◆NORBGRN   NORBGRNHIC♀NORBGRN    NOR◣NOR       BLINKWHT＊NOR
          NORHIW﹡NOR        HIY★  NOR◢NORBGRNGRN.  ο        .NOR◣NOR  │
  HIY&1&2&3&4NOR            NOR◢NORBGRNHIW   .        ＊.   NOR◣NORHIM●
                    NOR◢NORBGRNWHT       BLINK.NORBGRNWHT      .       NOR◣NOR            BLINKHIW﹡NOR
  HIY&6&7&8&9NOR         NOR◢NORBGRNHIW           .  .     ∶    NOR◣NOR
                NOR◢NORBGRNHIM       ∷     BLINK★NORBGRN              NOR◣NOR
     HIY--by $wNOR    │   NOR◢NORBGRNHIR.          ﹡      .NOR◣NOR    BLINKHIY★NOR
         NORBLINKHIW ＊NORWHT﹡NORHIW●NOR NOR◢NORBGRNHIG        ゞ         ＊   NOR◣NOR                   BLINKHIR＊NOR
HIC泥潭无岁月       NOR◢NORBGRNGRN        .      ∵  .        NOR◣NOR
HIC感谢一路相随   NOR◢NORBGRNHIY      BLINK∵NORBGRNHIR      .  .        ○    NOR◣NOR              
    HIR│NOR       NOR◢NORBGRNGRN   ＊           NORBGRNHIW╭╮NORBGRNGRN                NOR◣NOR
   HIM■■NOR    NOR◢NORBGRNGRN                  NORBGRNHIW╰╯NORBGRNGRN           ﹡     NOR◣NOR       WHT＊NOR   
   HIM■■NOR  BGRNGRN◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◢◣NOR
HIW▁▂▃▄▅NORREVHIW    NORHIW▆▅▄▃NOR  │    │     ║  ⊙HIW▄▂▃▄▅NORREVHIW      NORHIW▅▄▃▂▁NOR
WHT▁▂▃▄▅HBWHT    NORREVWHT        NORHBWHTHIM  △    HIY★GRN     ╩        NORHBWHT                        NORWHT▆▅▄▃NOR
MSG;
			break;						
			
		default :
			msg = @MSG
    HIR       │        ╰─╮   ╮│╭╮│╭ ╮    ───┐ ┬───-╮╭────╮NOR
    HIR     ╱  ╲   ╭────╮╰┼╯╰┼╯ │  │     ╱  │       ││ ╭─╮ │NOR
    HIM   ╱      ╲ │ ╮│╭ │  ╰  ╮╯   ┼─┼   ╱    │_______││ ╰─╯ │NOR
    HIM  │   ┐   │╯ ╰│╯ ╰  ╭╯│╭╯ │  │    │   │       ││╭──╮│NOR
    HIG  │┌-┴-┐│ │      │ ╭┤  │╯   │  │──┼─-│_______│││ │ ││NOR
    HIG  │      ││ │───│ ││╭│     │  │    │   │       │││ │ ││NOR
    HIY  ╯      │╰ │───│ ╯│││   │ ╲╱     │   │       ││ _╱╲_ │NOR
    HIY       __╱    │      │   │╯ ╲_╱  ╱╲ ╲_╱   ╱     __╱ ├────┤NOR
    HIG                      $w祝您元旦快乐，心想事成！NOR
    HIY                       泥潭无岁月 感谢一路相随NOR    
MSG;
	}
	tmp = wizs[random(sizeof(wizs))];
	msg = replace_string(msg,"$w",tmp);
	msg = replace_string(msg,"$1",sprintf("%s",tmp[0..1]));
	msg = replace_string(msg,"$2",sprintf("%s",tmp[2..3]));
	tmp = temp[random(sizeof(temp))];
	msg = replace_string(msg,"&1",sprintf("%s",tmp[0..1]));
	msg = replace_string(msg,"&2",sprintf("%s",tmp[2..3]));
	msg = replace_string(msg,"&3",sprintf("%s",tmp[4..5]));
	msg = replace_string(msg,"&4",sprintf("%s",tmp[6..7]));
	tmp = temp[random(sizeof(temp))];
	msg = replace_string(msg,"&6",sprintf("%s",tmp[0..1]));
	msg = replace_string(msg,"&7",sprintf("%s",tmp[2..3]));
	msg = replace_string(msg,"&8",sprintf("%s",tmp[4..5]));
	msg = replace_string(msg,"&9",sprintf("%s",tmp[6..7]));
	
	msg = COLOR_D->replace_color(msg,1);
	return msg;
}

string shuangdan()
{
	string msg;
	object ob,me = this_player();
	
/*	if( me->query("giftmark/2010shuangdan") )
		return "双蛋快乐，你已经要过了，别做坏蛋，除非你缺蛋。。。。";
	if( time()<me->query("giftmark/2010sd-give")+86400 )
		return "双蛋快乐，你已经要过了，丢了？真不好彩，这样吧，本女侠再给你一次机会，明天再来吧。";
	if( !query("双蛋") )
		return "双蛋快乐，等各位巫师打开双蛋模式，你才能领礼物。";	
	ob = new("/d/wiz/obj/gongzai");
	if( !ob )
		return "双蛋快乐，没有流氓兔公仔了。";
	if( !ob->move(me) )
		return "双蛋快乐，你身上杂七杂八的东西太多了。";
	me->set("giftmark/2010sd-give",time());		*/
	msg = rmsg();
	if( msg )
		message("shout",msg,users());
/*	
	message_vision("$N递给$n一个毛茸茸的流氓兔公仔。\n",this_object(),me);
	write(HIG"小阿枚在你的耳边悄声说道：这个公仔有好多秘密功能哦。\n"NOR);*/
	return "圣诞快乐，预祝元旦快乐，泥潭无岁月，感谢一路相随。";
}
		
			
		
		
		
