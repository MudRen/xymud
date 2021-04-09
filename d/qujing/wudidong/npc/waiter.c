// waiter.c

inherit F_VENDOR_SALE;
void create()
{
        set_name("张小二", ({ "waiter", "xiao", "xiao er", "vendor" }) );
        set("title", "小店老板");
        set("gender", "男性" );
        set("age", 22);
        set("long", "张小二是个好动的主儿。这当儿他正在不厌其烦地整理他的小店。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "张二哥");
        set("per",25);
        set("vendor_goods", ([
		"jiudai": "/d/moon/obj/jiudai",
		"gourou": "/d/ourhome/obj/gourou",
 		"jitui": "/d/ourhome/obj/jitui",
		"huasheng": "/d/ourhome/obj/huasheng",
	]));
	setup();
}

int accept_money(object who,int v)
{
    if( who->query_temp("rent_paid") ) {
             tell_object(who,name()+"对你一哈腰，你已经给过了。\n");
             return 0;
    }
    if( v<30 ) {
             tell_object(who,name()+"对你一哈腰：旅费3两白银。\n");
             return 0;
    }
    who->set_temp("rent_paid",1);
    tell_object(who,name()+"对你一哈腰：欢迎欢迎。\n");
    return 1;
}
