#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string ask_stlb();

void create()
{
        set_name("广筠子", ({"guang yunzi", "guang"}));
        set_level(120);
        set("gender", "男性" );
        set("age", 43);
        set("long", "方寸山三星洞第二代弟子中的杰出人物．\n");
        set("attitude", "friendly");
        create_family("方寸山三星洞", 2, "首徒");
	set("class", "taoist");

        set("eff_dx", 90000);
        set("nkgain", 300);

        set_skill("unarmed",1200);
        set_skill("dodge",1200);
        set_skill("parry",1200);
        set_skill("spells",1200);  
        set_skill("dao",1200);
        set_skill("literate",1200);
        set_skill("stick",1200);  
        set_skill("qianjun-bang",1200);
        set_skill("puti-zhi",1200);  
        set_skill("jindouyun",1200);
        set_skill("dodge",1200);
        set_skill("force",1200);   
        set_skill("wuxiangforce",1200);

        map_skill("spells", "dao");
        map_skill("unarmed", "puti-zhi");
        map_skill("force", "wuxiangforce");
        map_skill("stick", "qianjun-bang");
        map_skill("parry", "qianjun-bang");
        map_skill("dodge", "jindouyun");
        set("force_factor", 40);
	set("mana_factor", 20);
	set("inquiry", ([
		"定身咒" : "此咒最考究人的心神镇定，你可以去大雪山的灵鹫洞修炼(xiulian)一番。",
		"三头六臂" : (: ask_stlb :),
	]));	
        set("env/test","HIB");
	set_temp("armor_level",50+random(50));
	set_temp("weapon_level",50+random(50));
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"stick",1)->wield();
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="bonze" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：我们方寸山虽是有教无类，但是偏偏不收秃驴！哼！\n"NOR);
           	return ;
        }
        if( ob->query_level()<40 )
        {
		EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你还是先练好基本功再来！\n"NOR);
           	return ;
        }
        if( ob->query("class")!="taoist" )
        {
        	if( !ob->query_temp("pendding/fc_class") )
        	{
			EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
           		tell_object(ob,CYN+name()+CYN"说道：你乃带艺拜师，还是先向祖师爷打听师门试炼一事吧。\n");
           		return ;
        	}
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们方寸山发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","三星洞方寸山又多了一个弟子  "+ob->name(1)+HIW"\n                                 方寸山的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "taoist");
}

int job_playing()
{
	string id;
	object who;
	id = query("sltb_id");	
	if( !id )
		return 0;
	who = find_player(id);
	if( !who )
		return 0;
	if( who->is_knowing("puti_stlb") )
		return 0;	
	if( !living(who) )
	{
		if( time()>=who->query("family/stlb_fail")+3600 )
			who->set("family/stlb_fail",time());
		return 0;	 		
	}
	return 1;	
}

void finish_stlb()
{
	remove_call_out("stlb_test1");
	remove_call_out("stlb_test2");
	remove_call_out("stlb_test3");
	if( !environment() 
	 || base_name(environment())=="/d/lingtai/inside5" )
		return;	
	delete("stlb_id");
	delete_temp("no_return");
	message_vision("$N说道：我且回去。\n$N往西边厢房方向离去了。\n\n",this_object());
	this_object()->move("/d/lingtai/inside5",2);
	message_vision("\n\n$N走了过来。\n",this_object());	
}

void stlb_test3(object me)
{
	string str;
	object npc;
	remove_call_out("stlb_test3");
	if( !me )
	{
		finish_stlb();
		return;
	}
	if( !living(me) )
	{
		if( time()>=me->query("family/stlb_fail")+3600 )
			me->set("family/stlb_fail",time());
		finish_stlb();	
		return;
	}
	npc = new(__DIR__"yg_stlb");
	npc->set("guangyun",this_object());
	str = npc->invocation(me);
	if( !str || !stringp(str) )
	{
		destruct(npc);
		message_vision("广筠子手捻口诀，念动真言，摇身一变，结果什么反应也没有。\n$N说道：奇了个怪咧。\n"NOR,this_object());
		finish_stlb();	
		return;
	}
	message_vision(str,me);
	message_vision("$N说道：好好，你便和我这个分身比试(fight)比试。\n",this_object());
	CHANNEL_D->do_channel(this_object(),"chat","今日我派弟子"+me->name()+"在练功室领悟「"HIY"三头六臂"HIC"」的奥妙，欢迎各师兄弟观礼。"NOR);	
}
	
void stlb_test2(object me,int t)
{
	remove_call_out("stlb_test2");
	t = t-1;
	if( !me )
	{
		finish_stlb();
		return;
	}
	if( !living(me) || t<=0 )
	{
		if( time()>=me->query("family/stlb_fail")+3600 )
			me->set("family/stlb_fail",time());
		if( living(me) )
			tell_object(me,"广筠子久等你不来，取消了本次任务。\n");	
		finish_stlb();	
		return;
	}
	if( base_name(environment())!="/d/lingtai/inside7" )
	{
		remove_call_out("stlb_test1");
		call_out("stlb_test1",1,me);
		return;		
	}
	if( !present(me,environment()) )
	{
		call_out("stlb_test2",1,me,t);
		return;
	}
	message_vision("$N对$n点了点头：好，既然如此，我们现在就开始。\n",this_object(),me);
	remove_call_out("stlb_test3");
	call_out("stlb_test3",3,me);
}

void stlb_test1(object me)
{
	remove_call_out("stlb_test1");
	if( !me )
		return;
	if( !living(me) )
	{
		if( time()>=me->query("family/stlb_fail")+3600 )
			me->set("family/stlb_fail",time());
		return;
	}		
	message("vision",name()+"往东边练功室方向离去。\n\n",environment());
	this_object()->move("/d/lingtai/inside7",2);
	message_vision("\n\n$N走了过来。\n",this_object());
	remove_call_out("stlb_test2");
	call_out("stlb_test2",1,me,60);
}

string ask_stlb()
{
	object me = this_player();
	if( me->query("family/family_name")!="方寸山三星洞" )
		return 0;
	if( me->is_knowing("puti_stlb")
	 || base_name(environment())!="/d/lingtai/inside5" )
 		return "此咒原本为西方佛陀所有，然天下大道同源，我三星洞会此咒也不为奇。";
	if( time()<me->query("family/stlb_fail")+3600 
	 || me->query_level()<30 )
		return "你还是下去多练练。";
	if( job_playing() )
		return "你稍微等等，现在有人在领悟。";
	set("stlb_id",me->query("id"));
	remove_call_out("stlb_test1");
	call_out("stlb_test1",5,me);
	set_temp("no_return",1);
	return "好好，随我去东边练功室。";
}