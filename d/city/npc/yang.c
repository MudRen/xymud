inherit F_VENDOR_SALE;

string heal_me(object me);

void create()
{
	reload("yangzhongshun");
        set_name("杨中顺", ({"yang zhongshun", "yang", "boss"}));
        set("title", "药铺掌柜");
        set("gender", "男性");
        set("age", 37);
        set("long",
"杨老板是长安城里祖传的名医。虽然年轻，却早已名声在外。\n");
        set("kee", 300); 
        set("max_kee", 300);
        set("sen", 200);
        set("max_sen", 200);
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("env/wimpy", 50);

        set("inquiry", ([
                "治伤": (: heal_me :),
                "疗伤": (: heal_me :),
                "开药": (: heal_me :),
        ]) );

        set("vendor_goods", ([
                "yao": "/d/obj/drug/jinchuang",
                "dan": "/d/obj/drug/hunyuandan",
   		"danping" : "/d/city/obj/danping",
   		"yaoping" : "/d/city/obj/yaoping",
      		"shaqi" : "/d/obj/drug/shaqi",
      		"cibei" : "/d/obj/drug/shaqi2",
//                "gao" : "/u/snowtu/obj/gin",
                "force" : "/d/obj/drug/bihai-yinping",
        ]) );
        set_skill("literate", 70);
	set_skill("unarmed", 60);
        set_skill("dodge", 60);
        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
	add_money("gold", 1);
}

string heal_me(object ob)
{
        int ratio;
        object me;
        me = this_player();
        ratio = (int)me->query("eff_kee") * 100 /(int)me->query_maxkee();
        if( ratio >= 100 )
                return "这位" + RANK_D->query_respect(me) +"，您看起来气色很好啊，不像有受伤的样子。";
        if( ratio >= 95 )
                return "哦....我看看....只是些皮肉小伤，您买包金创药回去敷敷就没事了。";
	if( me->query_level()<20 )                
	{
		if( me->query("gin")<5 )
			return "你的活力不足啊。";
		message_vision("$N朝$n点了点头，掏出银针，在$p身上数道要穴扎了几下，效果很明显，$n的脸色渐渐变得红润起来。\n",this_object(),me);
		me->powerup();
		me->add("gin",-5);
		return "好了，你且下去歇歇。";
	}
	return "怎么敢当。";
}

void init()
{
        object ob;

        ::init();
        add_action("do_vendor_list", "list");
}


