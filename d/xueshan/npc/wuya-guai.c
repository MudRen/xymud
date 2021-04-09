// wuya-guai.c...weiqi, 97.09.15.
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("乌鸦先生", ({"wuya xiansheng", "wuya", "xiansheng"}));
      	set_level(70);
	set("gender", "男性" );
	set("age", 43);
	set("per", 112);//no rongmao description.

	set("long", "这位乌鸦先生来自遥远的大雪山。乃是大鹏明王座下有名的高手之一。\n他远看还不错，走近了才发现他长着长长的一张乌鸦嘴。\n");
	set("class", "yaomo");

	set("attitude", "peaceful");
	create_family("大雪山", 3, "弟子");
	set_skill("unarmed", 700);
	set_skill("cuixin-zhang", 700);
	set_skill("dodge",700);
	set_skill("xiaoyaoyou",700);
	set_skill("parry",700);
	set_skill("blade",700);
	set_skill("bingpo-blade", 700);
	set_skill("force",700);   
	set_skill("ningxie-force", 700);
	set_skill("literate",700);
	set_skill("spells",700);
	set_skill("dengxian-dafa",700);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "cuixin-zhang");
	set_skill("jiefeng",700);
	set("force_factor", 35);
	set("mana_factor", 20);

	set("eff_dx", -25000);
	set("nkgain", 150);

	set("inquiry", ([
		"name" : "问什么问，张着眼睛是看的，长着脑袋是想的。\n",
		"here" : "这就是我们大雪山。\n",
		"怎么去" : "飞过去最快，走也能到。\n",
		"怎么走" : "从这儿往北走。\n",
		"大雪山" : "你是干嘛的？！快回答(answer)
		1 巡山的  2 过路的  3 捣乱的\n",
	]) );

	set("no_map", 0);

	setup();
	carry_object("/d/obj/cloth/xueshan-pao")->wear();
	carry_object("/d/obj/weapon/blade/iceblade")->wield();
}

void init()
{
   	add_action("do_answer", "answer");
}

int do_answer(string arg)
{       
        object me=this_player();
        string *ans=({"巡山的","过路的","捣乱的",});
        int ans1;

        if( !arg ) 
        	return notify_fail("你说什么？\n");
	if (arg=="0"|| arg=="1"|| arg=="2") 
        {
        	sscanf(arg,"%d",ans1); 
        	arg=ans[ans1];
	}
        message_vision("$N答道：" + arg + "。\n", this_player());
        if( (arg== "巡山" || arg== "巡山的") && present("yao pai", this_player()))
        {
        	command("look " + me->query("id") );
          	EMOTE_D->do_emote(this_object(), "kick",geteuid(me),CYN,0,0,0);
          	command("say 跑哪去啦？大王等你回话都等急了！\n");
          	message_vision("乌鸦先生道：快给我进去！\n", me);
          	message_vision("只见乌鸦先生嘴里念叨了几句，一脚踢中$N的屁股，$N腾云驾雾般飞了出去．．．\n", me);
          	me->move("/d/xueshan/binggu");
          	tell_room( environment(me),"天空中$N狠狠的摔了下来，样子有些狼狈。\n",me);
	} 
        else if( (arg== "护山" || arg== "护山的") && present("yao pai", this_player()))
        {
        	command("look " + me->query("id") );
          	EMOTE_D->do_emote(this_object(), "kick",geteuid(me),CYN,0,0,0);
          	command("say 护山的跑这来干嘛？快回去！\n");
          	message_vision("只见乌鸦先生嘴里念叨了几句，一脚踢中$N的屁股，$N腾云驾雾般飞了出去．．．\n", me);
          	me->move("/d/xueshan/binggu");
          	tell_room( environment(me),"天空中$N狠狠的摔了下来，样子有些狼狈。\n",me);
	} 
        else if(arg== "守山" || arg== "守山的") 
        {
        	EMOTE_D->do_emote(this_object(), "kick",geteuid(me),CYN,0,0,0);
          	command("say 即是守山的，就在这给我老老实实呆着吧！\n");
          	EMOTE_D->do_emote(this_object(), "idle",geteuid(me),CYN,0,0,0);
          	EMOTE_D->do_emote(this_object(), "idle",0,CYN,0,0,0);
        }
        else if( arg=="过路" || arg=="过路的" )
        {
        	EMOTE_D->do_emote(this_object(), "hehe",geteuid(me),CYN,0,0,0);
          	command("say 请吧！\n");
          	me->set_temp("to_xueshan", 1);
        } 
        else 
	{
          	EMOTE_D->do_emote(this_object(), "pei",geteuid(me),CYN,0,0,0);
        }
        return 1;
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()>95 )
	{
		EMOTE_D->do_emote(this_object(), "pa",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：" + RANK_D->query_respect(ob) +"是我的前辈，还是进大雪山去找将军吧。\n"NOR);
		return;
	}
	if( ob->query("class") && ob->query("class")!="yaomo" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是进大雪山去找将军吧。\n"NOR);
		return;
	}
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大雪山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","大雪山又多了一个弟子  "+ob->name(1)+HIW"\n                                 大雪山的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}