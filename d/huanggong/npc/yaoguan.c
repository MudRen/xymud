#include <ansi.h>
inherit F_VENDOR_SALE;

void create()
{
reload("yaoguan");
set_name("药官", ({"yao guan","guan"}));
set("shop_id",({"yaoguan","yao","guan"}));
set("shop_title","侍药中郎将");
set("gender", "男性");
set("combat_exp", 1000000);
set("age", 36);
set("per", 24);
set("attitude", "friendly");
set_skill("unarmed", 260);
set("max_price",100);
set("vendor_goods", ([
        "yao1": "/d/obj/drug/jinchuang",
        "yao2": "/d/obj/drug/jinchuang2",
        "yao3": "/d/obj/drug/jinchuang3",
        "dan1": "/d/obj/drug/hunyuandan",       
        "dan2": "/d/obj/drug/hunyuandan2",      
        "dan3": "/d/obj/drug/hunyuandan3",                      
]) );
setup();
carry_object("/d/obj/cloth/gongpao")->wear();
}

void init()
{
::init();
add_action("do_vendor_list", "list");
}


int do_bid(string arg)
{
int amount;
string money;
object who=this_player();
notify_fail("Usage: bid <amount> <gold|silver>\n");
if(!arg) return 0;
if(sscanf(arg,"%d %s", amount, money)!=2) return 0;
if(money=="gold") amount*=10000;
else if(money=="silver") amount*=100;
else return 0;
if(amount<1) return 0;
if(amount<500000) {
         write("你至少需要出"+price_string(500000)+"。\n");
         return 1;
         }
return ::do_bid(arg);
}


