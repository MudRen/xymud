//changan city

#include <ansi.h>
inherit BANK;

void reset_balance(object me);

void create ()
{
        set ("short", "相记钱庄");
        set ("long", @LONG

这是一家老字号的钱庄，相老板是山西人，这家钱庄从他的爷爷的爷
爷的爷爷的爷爷那辈开始办起，一直传到他手里，声誉非常好，在全
国各地都有分店。它发行的银票通行全国。钱庄的门口挂有一块牌子
(paizi)。
LONG);
        set("item_desc", ([
                "paizi": @TEXT
这里是钱庄，目前我们提供的服务有：

account         查帐。
deposit         存款。
withdraw        取款。

TEXT
        ]) );

        set("exits", 
        ([ //sizeof() == 4
		"north" : __DIR__"baihu-w1",
                   "down" : __DIR__"basement",
//                  "south" : __DIR__"bank_qn",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/tiesuanpan" : 1,
                "/d/wiz/npc/cangku" : 1,
        ]));


//        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
}

/*
void init()
{
    reset_balance(this_player());
    ::init();
}

void reset_balance(object me)
{
int ap,max,removed_gold;
remove_call_out("reset_balance");
if ( !me )      return;

//每1年加100gold上限
max = me->query("daoxing")/1000;
if ( max<100 )  max = 100;
if ( max>15000 ) max = 15000;

ap = me->query("balance");
ap/= 10000;
if ( wizardp(me) )
        tell_object(me,sprintf("\t"HIR"道行%d"HIW"存款%d"HIR"ap=%d"HIW"max=%d\n"NOR,
                                        me->query("daoxing"),
                                        me->query("balance"),
                                        ap,
                                        max,));
if ( ap>max )
        {
        me->set("balance_old", me->query("balance"));
        me->set("balance",max*10000);
        removed_gold = max-ap;
        log_file("money_reset", ctime( time() )+"：魏大人收缴了"+me->query("name")+"("+me->query("id")+")"+removed_gold+"两黄金。\n");
        tell_object(me, NOR"铁算盘在你的耳边悄声说道："+RANK_D->query_respect(me)+"，这、这真不知怎么说是好．．．\n"NOR);
        tell_object(me, NOR"铁算盘在你的耳边悄声说道：昨日魏大人派人前来察案，发觉你老的黄金来路．．．\n"NOR);
        tell_object(me, NOR"铁算盘在你的耳边悄声说道：若不是在下帮你老辩解，你老的钱就全都充公了．．．\n"NOR);
        }
return;
}
*/
