
inherit F_VENDOR_SALE;
int random_go(object me, string* dirs);

// #include <norumor.c>
void create()
{
       reload("xiaoer");
       set_name("店小二", ({"xiao er","xiaoer","xiao","waiter","er"}));
       set("shop_id",({"waiter","xiaoer","xiao","er"}));
       set("shop_title","店小二");
       set("gender", "男性");
        set("combat_exp", 1000);
        set_level(3);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 10);
       set("max_price",20);
        set("vendor_goods", ([
                "jiudai": "/d/moon/obj/jiudai",
                "gourou": "/d/ourhome/obj/gourou",
                "jinpai" : "/d/obj/misc/tiaozhanpai",
                //"tu": "/d/city/obj/tu",
		"lengxiangwan": "/d/obj/drug/lengxiangwan",
        	"xmap": "/d/obj/misc/xueshan-map",
                "pmap": "/d/penglai/npc/obj/ditu",
                "pillow": "/d/obj/misc/pillow",
                "jitui": "/d/ourhome/obj/jitui",
                "ball": "/d/obj/misc/crystalball",
                "huasheng": "/d/ourhome/obj/huasheng",
                //"zhinan": "/d/obj/misc/xiaqi-zhinan",
       		"dan": "/d/qujing/tianzhu/obj/dan",
                //"zhengsu":"/d/qujing/chechi/obj/zhengsu",
                "huicheng":"/d/city/obj/huicheng",
                //"tianshi fu":"/d/city/obj/tianshifu",
                //"xigua":"/d/ensign/xigua",
        ]) );

        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
       setup();
	carry_object(0,"cloth",random(2))->wear();
       
}

void init()
{
        add_action("do_vendor_list", "list");
}

int accept_money(object who, int v)
{
   if (v >= 300) 
   {
     tell_object(who, "小二一哈腰，说道：多谢您老，客官请上楼歇息。\n");
     who->set_temp("rent_paid",1);
     return 1;
   }
   return 0;
}
