// dapeng.c...weiqi, 97.09.27.
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("大鹏明王", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
      	set_level(170);
	set("title", "雪山之祖");
	set("gender", "男性" );
	set("age", 45);
	set("long", "这位大鹏明王的确大有来历，说起来跟佛祖如来也有点亲戚关系，\n算是如来的“舅舅”。他不似其兄孔雀明王作恶多端，却也并非善类，\n且因其兄之故跟佛门结下深仇。生平最讨厌的就是和尚。\n");
	set("class", "yaomo");

	set("attitude", "peaceful");
	create_family("大雪山", 1, "祖师");
	set("rank_info/respect", "明王");
	set_skill("unarmed", 1700);
	set_skill("cuixin-zhang", 1700);
	set_skill("dodge", 1700);
	set_skill("xiaoyaoyou", 1700);
	set_skill("parry", 1700);
	set_skill("sword", 1700);
	set_skill("bainiao-jian", 1700);
	set_skill("blade", 1700);
	set_skill("bingpo-blade", 1700);
	set_skill("throwing", 1700);
	set_skill("force", 1700);   
	set_skill("ningxie-force", 1700);
	set_skill("literate", 1700);
	set_skill("spells", 1700);
	set_skill("dengxian-dafa", 1700);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");

	set_skill("diandao-yinyang",1700);
	set_skill("qisi-huisheng",1700);
	set_skill("qushen",1700);
	
	set("env/wimpy",10);
	set("force_factor", 250);
	set("mana_factor", 200);

	set("env/test","HIR");
	set_temp("weapon_level",100+random(50));
	set_temp("armor_level",100+random(50));      
	setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"armor",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object(0,"sword",random(3))->wield();
}

void _attempt_apprentice(object ob)
{
	if( !ob )
		return;
	if( ob->query_level()>=125 )
	{
		if( ob->query("shilian")!="xueshan" )
		{
			EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
			tell_object(ob,CYN+name()+CYN"说道：你去给我炼来五仙汤，我有大用。"NOR"\n");
			ob->set_temp("xueshan_wxt",1);
			return;
		}
		EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大雪山发扬光大。\n"NOR);
        	command("recruit " + geteuid(ob) );
        	return;
	}	
	else
	{
		EMOTE_D->do_emote(this_object(), "pat",0,CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：嗯，有志不在年高，你先去打好基础再来吧。\n"NOR);
		return;
	}
}

void attempt_apprentice(object ob)
{
	if( ob->query("class") && ob->query("class")!="yaomo" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是先去找将军问问吧。\n"NOR);
		return;
	}
	return _attempt_apprentice(ob);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
		ob->set("class", "yaomo");
		if( ob->query("gender")=="女性" )
		{
			if( !ob->is_titles("镇山凤凰明王") )
	 		{
	 			if( ob->set_titles("镇山凤凰明王") )
	 			{
	 				tell_object(ob,HIC"【系统】你获得了称号：「"HIW"镇山凤凰明王"NOR HIC"」。\n"NOR);
	 				ob->save();
	 			}	
	 		}
	 	}
	 	else
	 	{
			if( !ob->is_titles("无法无天大邪圣") )
	 		{
	 			if( ob->set_titles("无法无天大邪圣") )
	 			{
	 				tell_object(ob,HIC"【系统】你获得了称号：「"HIR"无法无天大邪圣"NOR HIC"」。\n"NOR);
	 				ob->save();
	 			}	
	 		}
	 	}
	}
}

int accept_object(object ob,object obj)
{
	if( ob->query("family/family_name")!="大雪山" )
		return 0;
	if( !ob->query_temp("xueshan_wxt") )
		return 0;
	if( base_name(obj)!="/d/xueshan/obj/tang" )
		return 0;
	if( obj->query("name")!=YEL "五仙汤" NOR )
		return 0;
	if( random(obj->query("prices"))<1500 )
	{
		message_vision("$N端起"+obj->query("name")+"咕嘟咕嘟的喝了下去。\n", this_object());
		EMOTE_D->do_emote(this_object(), "pei",0,CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：什么滋味也没有，你是拿刷锅水来忽悠老夫啊？！"NOR"\n");
		return 0;
	}	
	EMOTE_D->do_emote(this_object(), "young",geteuid(ob),CYN,0,0,0);
	ob->set("shilian","xueshan");
	tell_object(ob,CYN+name()+CYN"说道：你的至诚打动了老夫，老夫看你骨骼精奇，将我大雪山发扬光大的重任就交给你了！"NOR"\n");
	tell_object(ob,CYN+name()+CYN"说道：赶紧的，拜师吧。"NOR"\n");
	ob->save(1);
	return 1;		
}