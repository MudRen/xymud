// 孔方兄, bookseller.
// 5-3-97, pickle

inherit F_VENDOR_SALE;

void create()
{
	reload("city_kongfang");
  	set_name("孔方兄", ({ "kong fang", "kongfang", "kong", "fang", "bookseller", "seller", "vendor" }) );
  	set("shop_id",({"kongfang","kong","fang","bookseller","seller"}));
  	set("gender", "男性" );
  	set("age", 37);
  	set("title", "书店老板");
  	set("long","孔秀才入京赶考落第，盘缠用尽，无法还乡，\n不得已在长安开一家书店。传说他曾遇异人，\n学得一些防身之术。\n");
	set_level(10);
  	set_skill("dodge", 100);
  	set_skill("parry", 100);
  	set_skill("unarmed", 100);
  	set_skill("jinghun-zhang", 100);
  	set_skill("literate", 100);
  	set("attitude", "friendly");
  	map_skill("unarmed", "jinghun-zhang");
	set("rank_info/respect", "孔秀才");
	set("vendor_goods", ([
		"daofa"		: "/d/obj/book/blade_1",
		"quanfa"	: "/d/obj/book/unarmed_1",
		"chunqiu": "/d/obj/book/chunqiu",
    		"shaolin": "/d/obj/book/parrybook2",
    		"mihou": "/d/obj/book/mihou-book",
    		"quanjing" : "/d/obj/book/quanjing",
	]));
  	setup();
  	carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
	add_action("do_vendor_list", "list");
}