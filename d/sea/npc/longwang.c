// 写了好久  by take
#include <skill.h>
#include <ansi.h>
inherit SUPER_NPC;

string ask_mieyao();
string ask_cancel();
string begin_go();

void create()
{
       	set_name("敖广", ({"ao guang", "ao","guang","longwang","wang"}));
	set_level(170);
	set("long","敖广是东海的龙王，其兄弟分别掌管东，西，南，北四海。
由余其水族众多，声势浩大，俨然独霸一方。\n");
	create_family("东海龙宫", 1, "水族");
	set("gender", "男性");
	set("age", 66);
	set("title", HIY"东海龙王"NOR);
	set("class","dragon");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("rank_info/respect", "陛下");
	set("per", 20);
	set("force_factor", 120);
	set("mana_factor", 140);

	set_skill("huntian-hammer",1700);
	set_skill("hammer",1700);
        set_skill("literate", 1700);
	set_skill("unarmed",1700);
	set_skill("dodge",1700);
	set_skill("force",1700);
	set_skill("parry",1700);
	set_skill("fork",1700);
	set_skill("spells",1700);
	set_skill("seashentong",1700);
	set_skill("dragonfight",1700);
	set_skill("dragonforce",1700);
	set_skill("fengbo-cha",1700);
	set_skill("dragonstep",1700);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
        set_skill("zhidi-chenggang",1700);
        set_skill("danshan",1700);
        set_skill("qiyu",1700);
        set_skill("duanliu",1700);
        set_skill("jiefeng",1700);
        set_skill("huanyu-hufeng",1700);
	set("inquiry", ([ 
          	"灵台观礼": (: begin_go :),
           	"kill": (: ask_mieyao :),
           	"cancel": (: ask_cancel :),
        ]) );
	set("env/test",({"HIM","HIR","HIB"})[random(3)]);
	set_temp("weapon_level",80);
	set_temp("armor_level",80);
	setup();
        carry_object("/d/sea/obj/longpao")->wear();
        carry_object(0,"unarmed",1)->wield();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"waist",1)->wear();
        powerup(0,1);
}

string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="东海龙宫") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="东海龙宫" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}

void die()
{
	object who = query_temp("last_damage_from");
	if( environment() )
	{
		command("chat* pei");
		if( who )
			CHANNEL_D->do_channel(this_object(),"chat",who->name()+"闹我东海，待老夫携状纸，告上天庭！");
		message("vision","\n\n"+name()+"将身一摇，化作八丈五爪金龙，腾云驾雾直向南天门而去。\n\n",environment());
	}
	destruct(this_object());
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/sea/inside3" )
		return;
	message_vision("\n"HIC"东海龙王道：观礼事毕，老龙这就回转东海水晶宫，老祖所议之事，容我考虑考虑。\n"NOR,this_object());
        message_vision(HIC"\n$N"HIC"口摇身一变，现出原形，正是一条神龙，随即穿云而去…… \n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/sea/inside3");
	message_vision(HIC"\n但见云光缥缈，半空中仿佛冲出一条水柱，$N"HIC"从水柱上稳稳跳落地下……  \n"NOR,this_object());			
}

void sea_saying(object me)
{
	if( !me || !living(me) || !present(me,environment()) )
		return;
	tell_object(me,"龟丞相领着龙太子、龙表弟从殿下走来。\n");
	tell_object(me,CYN+name()+CYN"说道：近日五庄观八位弟子又将东游，尔等这些天慎言慎行，莫生事端！\n"NOR);
	tell_object(me,"龙太子、龙表弟虽有不忿之色，仍是恭恭敬敬行礼答应了下来。\n");
	tell_object(me,CYN+name()+CYN"说道：尔等下去吧。\n"NOR);
	EMOTE_D->do_emote(this_object(), "bow",0,CYN,0,0,0);
	tell_object(me,CYN+name()+CYN"对你说道：届时东游烦请"+RANK_D->query_respect(me)+"与他们同行，出了意外，倒也可以照应。\n"NOR);
	EMOTE_D->do_emote(me, "ok",0,CYN,0,0,0);
	me->set_temp("pendding/fc_visite_seask",1);
	tell_object(me,HIY"【灵台观礼】八仙过海：既然诸事都已商定，还是回去和镇元大仙禀告吧。\n"NOR);
}

string begin_go()
{
	object me,ob;
	string str;
	int dx,wx,qn,i;
    	
    	me=this_player();
	ob=this_object();
	
	if( ob->is_busy() )
		return 0;
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( base_name(environment())!="/d/sea/inside3" )
    		return "此事待本王回龙宫后再说。";
	if( me->query_temp("pendding/fc_visite_sea") )
	{
        	message_vision("\n"HIC"东海龙王道：" + RANK_D->query_respect(me) + "，本王即刻赴灵台之约！\n"NOR,me);
        	message_vision(HIC"\n$N"HIC"口摇身一变，现出原形，正是一条神龙，随即穿云而去…… \n"NOR,ob);
        	ob->set_temp("no_return",1);
    		ob->move("/d/lingtai/inside1");
    		message_vision(HIC"\n但见云光缥缈，半空中仿佛冲出一条水柱，$N"HIC"从水柱上稳稳跳落地下……  \n"NOR,ob);
		remove_call_out("go_back");
    		call_out("go_back",2700);
		return "老夫与老祖正好有事相商。";
	}
	if( !me->query_temp("pendding/fc_visite_baxianguohai") )
	{		
		if( me->query_temp("pendding/fc_wzgask")<8 )
			return "如今四海升平，万物和谐，本王不想动身。";
		if( !me->query_temp("pendding/fc_visite_seask") )
		{
			if( time()<me->query("family/guanli_baxian_fail")+3600 )
				return "唉，可怜我儿，上次劫难尚未痊愈，这般又来，何苦来哉？";
			tell_object(me,"\n你上前将八仙近日即将东游一声向老龙王讲了一遍。\n");
			EMOTE_D->do_emote(this_object(), "sigh",0,CYN,0,0,0);
			tell_object(me,CYN+name()+CYN"说道：何苦来哉？！上次游我东海，就害得我四海不宁，如今又来？！\n"NOR);
			EMOTE_D->do_emote(this_object(), "beg",0,CYN,0,0,0);
			tell_object(me,CYN+name()+CYN"说道：奈何他家祖师爷爷乃天地同寿的人物，本王也是惹不起。\n"NOR);
			EMOTE_D->do_emote(this_object(), "goaway",geteuid(ob),CYN,0,0,0);
			message_vision("$N挥手叫来一旁龟丞相，附耳说了一番。龟丞相点头向下离去。\n",ob);
			ob->start_busy(5);
			remove_call_out("sea_saying");
			call_out("sea_saying",1+random(4),me);
			return "如今只有让我那龙子龙孙多思慎言了。";
		}
		return "届时麻烦"+RANK_D->query_respect(me)+"了。";	
	}
	me->delete_temp("pendding/wzg_sea1");
	me->delete_temp("pendding/wzg_sea2");
	me->delete_temp("pendding/fc_visite_seask");
	me->set_temp("pendding/fc_visite_sea",1);
	if( me->query_temp("pendding/fc_visite_wzg") )
		me->delete_temp("pendding/fc_visite_baxianguohai");
	me->add_temp("pendding/fc_visited",1);
	CHANNEL_D->do_channel(this_object(),"chat",HIY+me->name()+HIC"助我调停「八仙闹东海」一事,届时老龙一定上灵台观礼！"NOR);
	if( !me->query("mark/guanli_sea") )
	{
		dx = ((me->query("daoxing")/1000)/10+1)*1000;
		if( dx>=81000) 
			dx = 81000;
		wx = dx+random(dx);	
		qn = 10000;
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",qn);
		tell_object(me,HIY"【灵台观礼】你得到了"+wx+"点武学经验、"+chinese_number(dx/1000)+"年道行以及"+qn+"点潜能的奖励！\n"NOR);
		me->set("mark/guanli_sea",1);
	}	
	tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
	if( me->query("family/family_name")=="方寸山三星洞")
		return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";
	else	return "多谢多谢。";	
}

void _attempt_apprentice(object ob)
{
	if( !ob )
		return;
	if( ob->query_level()>=125 )
	{
		if( ob->query("shilian")!="sea" )
		{
			EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
			tell_object(ob,CYN+name()+CYN"说道：你去给我集齐九龙灵珠，我有大用。"NOR"\n");
			ob->set_temp("sea_longzhu",1);
			return;
		}
		EMOTE_D->do_emote(this_object(), "nod",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们东海龙宫发扬光大。\n"NOR);
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
	if( ob->query("class") && ob->query("class")!="dragon" )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：你是啥来头啊？带艺拜师，还是先去找我夫人问问吧。\n"NOR);
		return;
	}
	return _attempt_apprentice(ob);
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
        {
		ob->set("class", "dragon");
		if( !ob->is_titles("东海龙王亲传弟子") )
	 	{
	 		if( ob->set_titles("东海龙王亲传弟子") )
	 		{
	 			tell_object(ob,HIC"【系统】你获得了称号：「"HIG"东海龙王亲传弟子"NOR HIC"」。\n"NOR);
	 			ob->save();
	 		}	
	 	}
	}
}
