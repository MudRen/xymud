// bianfu.c 蝙蝠精
#include <ansi.h>
inherit SUPER_NPC;

void mie_kou(object me);
void create_qionghan();
void create_wdd();

mixed about_emeng()
{	
	string msg;
	object me = this_player();
	if( me->query("family/family_name")!="陷空山无底洞")
		return 0;
	if( me->query_level()<10 )
		return 0;		
	msg = ("/quest/family/mieyao.c")->change_level(me);
	if( msg && stringp(msg) )
        	write(CYN+name()+CYN"说道：" + msg + CYN"\n" NOR);
        return 1;	
}

int ask_me()
{
	object me=this_player();

    	if( me->query("family/family_name") == "陷空山无底洞")
    	{
    		EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
    		tell_object(me,CYN+name()+CYN"说道：这你还用问我？！"NOR"\n");
                remove_call_out("create_wdd"); 
                remove_call_out("mie_kou"); 
                remove_call_out("create_qionghan"); 
                create_wdd();
                call_out("create_qionghan",3600);
    		return 1;
    	}
    	if(!query("wudidong_state"))
	{					
		EMOTE_D->do_emote(this_object(), "hehe",0,CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：实话告诉你吧！大爷我就是无底洞的上仙！"NOR"\n");
		set("accept_dizi", 1);
		tell_object(me,CYN+name()+CYN"说道："+me->name()+"，你可愿意入我无底洞？"NOR"\n");
                remove_call_out("create_wdd"); 
                remove_call_out("mie_kou"); 
                remove_call_out("create_qionghan"); 
                create_wdd();
                call_out("create_wdd",5);
		call_out("mie_kou", 60, me);
		tell_object(me,CYN+name()+CYN"说道：嘿嘿，你若是不愿，可莫怪我心狠手辣！"NOR"\n");
		return 1;
    	}
    	tell_object(me,CYN+name()+CYN"说道：若是想拜我无底洞，尽管说！"NOR"\n");
    	tell_object(me,CYN+name()+CYN"说道：否则就别怪我杀人灭口了！"NOR"\n");
    	EMOTE_D->do_emote(this_object(), "heihei",0,CYN,0,0,0);
    	remove_call_out("create_qionghan");
    	call_out("mie_kou", 60, me);
    	return 1;
}

void create()
{
	set("wudidong_state",1);
	create_qionghan();
}

void attempt_apprentice(object ob)
{
	if( !query("wudidong_state") )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		return 0;
	}
        if( ob->query("class")=="xian" || ob->query("class")=="dragon"
         || ob->query("class")=="bonze" || ob->query("class")=="taoist" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你是哪路神仙派来的？！\n"NOR);
           	return ;
        }
        if( ob->query("class") && ob->query("class")!="yaomo" )
        {
        	if( !ob->query("family/wdd_class") )
        	{
        		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
           		tell_object(ob,CYN+name()+CYN"说道：想弃暗投明？还是去问过总管吧。\n"NOR);
           		return ;
        	}
        }
        if( ob->query_level()>75 )
        {
		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你这么厉害了，还是进陷空山找师傅吧。\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们妖族发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","陷空山无底洞又多了一个弟子  "+ob->name(1)+HIW"\n                                 妖族的势力加强了。\n"NOR);
        return;
}

void recruit_apprentice(object ob)
{
	if( !query("wudidong_state") )
		return;
  	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
	return;	
}

void mie_kou(object me)
{
        remove_call_out("create_wdd"); 
	remove_call_out("mie_kou"); 
        remove_call_out("create_qionghan"); 
	call_out("create_qionghan", 300);
	
        if( !me || !environment() )
        	return;
    	if( me->query("family/family_name") == "陷空山无底洞")
    	{
    		EMOTE_D->do_emote(this_object(), "pat",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：不错，识时务者俊杰！"NOR"\n");
		return;
    	}
    	if( !present(me, environment()))
    	{
    		EMOTE_D->do_emote(this_object(), "sneer",0,CYN,0,0,0);	
		tell_object(me,CYN+name()+CYN"说道：幸亏这小子溜得快。否则，哼！哼！哼！"NOR"\n");
		return;
    	}
    	if( !query("wudidong_state") )
		create_wdd();
	tell_object(me,CYN+name()+CYN"说道：你既然执迷不悟，那就纳命来吧！"NOR"\n");
	kill_ob(me);
	me->fight_ob(this_object());
	remove_call_out("create_qionghan"); 
	call_out("create_qionghan", 180);
	return;
}

void kill_ob(object who)
{
	remove_call_out("mie_kou");
	remove_call_out("create_wdd");
	remove_call_out("create_qionghan");
	if( !query("wudidong_state") )
		create_wdd();
	call_out("create_qionghan", 60);
	::kill_ob(who);
}

int accept_fight(object who)
{
	say(HIC+name()+CYN"朝你一瘪嘴：不想死的，滚开！\n"NOR);
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
	return 0;
}	

void create_wdd()
{
	if( query("wudidong_state") )
		return;
	message_vision(HIY"穷汉摇身一变，现了原形。原来是只蝙蝠！\n"NOR, this_object());
	set_name("蝙蝠精", ({"bian fu", "bianfu", "fu", "bat", "monster"}));
	create_family("陷空山无底洞", 2, "弟子");
  	set("title", "上仙");
  	set("long","这明明是一只巨大的蝙蝠，但不知为何竟然会说人话！\n");
	set_level(70);
  	set_skill("unarmed",700);
  	set_skill("dodge",700);
  	set_skill("parry",700);
  	set_skill("spells",700);
  	set_skill("sword",700);
  	set_skill("blade",700);
  	set_skill("kugu-blade",700);
  	map_skill("blade","kugu-blade");
        set_skill("literate",700);
  	set_skill("qixiu-jian", 700);
  	set_skill("yinfeng-zhua", 700);
  	set_skill("lingfu-steps",700);
  	set_skill("force",700);
  	set_skill("yaofa", 700);
  	set_skill("huntian-qigong", 700);
  	map_skill("unarmed","yinfeng-zhua");
  	map_skill("dodge","lingfu-steps");
  	map_skill("spells","yaofa");
  	map_skill("force","huntian-qigong");  
  	map_skill("sword","qixiu-jian");    
  	map_skill("parry","qixiu-jian");   
  	set_skill("tuxing",700); 
  	set("inquiry/噩梦",(: about_emeng :) );
  	set("wudidong_state", 1);
  	setup();
  	if( present("sword") )
  		command("wield sword");
  	else	carry_object(0,"sword",random(2))->wield();
}

void create_qionghan()
{
	if( !query("wudidong_state") )
		return;
	if( environment() && this_object()->is_fighting() )
	{
		remove_call_out("create_qionghan");
		call_out("create_qionghan",60);
		return;
	}
	set_name("穷汉", ({"qiong han", "qiong", "han", "poor man","man"}));
	delete("family");
  	set_level(3);
        delete_skill("unarmed");
        delete_skill("dodge");
        delete_skill("parry");
        delete_skill("spells");
        delete_skill("sword");
        delete_skill("literate");
        delete_skill("qixiu-jian");
        delete_skill("yinfeng-zhua");
        delete_skill("lingfu-steps");
        delete_skill("force");
        delete_skill("yaofa");
        delete_skill("huntian-qigong");
        delete_skill("tuxing"); 
  	set("long",
"他看起来一付穷困潦倒的样子，浑身没一件象样的衣服，瘦骨嶙峋的，\n"
"就象三年没吃过一顿饱饭似的。虽说长安城里这样的人比比皆是，但你\n"
"看他就是觉得不顺眼。仔细端详一番，你发现原来他全身长着一层淡淡\n"
"的茸毛。\n");

	set("attitude", "peaceful");
  	set("gender", "男性");
  	set("age", 39);
  	set("title", "普通百姓");
	set("per", 1);
	set("env/wimpy", 70);
	set("wudidong_state",0);
	set("inquiry", ([
                   "name": "这个……我这穷汉的名字对你又有什么用了？",
                   "here": "这里？你问我我问谁去？",
		   "rumors": "听说最近附近有些老鼠精在长安城出没。唉。",
		   "老鼠精": "我听说他们是个什么什么山什么什么洞的，也不知咋回事。",
		   "陷空山": (: ask_me :),
		   "无底洞": (: ask_me :),
		   "噩梦"  : (: about_emeng :),
        ]) );  
	setup();
	if( !query_temp("armor") )
		carry_object("/d/obj/cloth/pobuyi")->wear();
	if( query_temp("weapon") )
		command("unwield sword");
	if( environment() )
		message_vision(HIY"蝙蝠精摇身一变，变成了一个面目猥琐的穷汉。\n"NOR,this_object());	
}

void init()
{
	add_action("do_ask","ask");
}

int do_ask(string arg)
{
	string sth;
	object me = this_player();
	if( me->query("family/family_name")!="陷空山无底洞" )
		return 0;
	if( !arg || sscanf(arg,"%s about %s",arg,sth)!=2 )
		return 0;
	if( !id(arg) )
		return 0;		
	if( sth=="name" || sth=="here" || sth=="rumors" || sth=="陷空山" || sth=="无底洞" 
	 || sth=="噩梦" )
		return 0;		
	message("vision",me->name()+"鬼鬼祟祟的在"+name()+"耳边说了几句话。\n",environment(),me);	
	if( sth!="kill" && sth!="cancel" && sth!="师门任务" )
	{
		write("你向蝙蝠精打听「"+sth+"」的事宜。\n");
		write("蝙蝠精嘿嘿对你笑道：我只能告诉你「"HIR+"师门任务"+NOR"」一事。\n");
		return 1;
	}	
	if( sth=="cancel" )
	{
		write(CYN"蝙蝠精说道："+("/quest/family/mieyao")->cancel_me(me)+NOR"\n");
		return 1;
	}
	EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(me),CYN,0,0,0);
	write(CYN"蝙蝠精说道："+("/quest/family/mieyao"->query_yao(me))+NOR"\n");
	return 1;		
}

int prevent_learn(object me, string skill)
{
	int mykugu = me->query_skill("kugu-blade",2);
  	if( wizardp(me) && me->query("env/immortal"))
    		return 0;
  	if( skill == "kugu-blade")
  	{
      		if( mykugu<180)
      		{
   			tell_object(me,CYN+name()+CYN"说道：你难道是来消遣本仙的吗？！\n"NOR);
   			return 1;
      		}
	}
  	return 0;
}