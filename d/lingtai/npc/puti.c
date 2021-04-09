//puti.c
inherit SUPER_NPC;
inherit F_MASTER;
#include <ansi.h>

string begin_go();

void create()
{
	set_name("菩提祖师", ({"master puti","puti", "master"}));
	set_level(168);
	set("long", "大觉金仙没垢姿，西方妙相祖菩提\n");
	set("title", HIC"斜月三星"NOR);
	set("gender", "男性");
	set("age", 100);
	set("class", "taoist");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("rank_info/respect", "老师祖");
	set("looking", "玉面多光润，苍髯颌下飘，金睛飞火焰，长目过眉梢。");
	set("int", 30);
	set("force_factor", 150);
	set("mana_factor", 150);

	set_skill("literate", 1680);
	set_skill("unarmed", 1680);
	set_skill("dodge", 1680);
	set_skill("parry", 1680);
	set_skill("stick", 1600);
	set_skill("sword", 1680);
	set_skill("liangyi-sword", 1680);
	set_skill("spells", 1600);
	set_skill("dao", 1680);
	set_skill("puti-zhi", 1680);
	set_skill("wuxiangforce", 1680);
	set_skill("force", 1680);
	set_skill("qianjun-bang", 1680);
	set_skill("jindouyun", 1680);
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
	map_skill("sword", "liangyi-sword");
	set("inquiry",([
		"灵台观礼": (: begin_go :),
	]));
	create_family("方寸山三星洞", 1, "蓝");
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

int accept_object(object me, object ob)
{
	if( (me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))
	{	 
		if( base_name(ob)=="/d/obj/drug/renshen-guo" 
		 && me->query("family/family_name")=="方寸山三星洞" )
		{
	 		EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
           		tell_object(me,CYN+name()+CYN"说道：呵呵，徒儿真是辛苦了！\n"NOR);
      			me->delete("fangcun/panlong_nowaywzg2");
      			return 1;
		}
	}
	return 0;
}

void inviting()
{
	int i;
   	object *list;

   	if( !query_temp("invite"))
   		return;
  	remove_call_out ("inviting");
	list = users();
   	i = sizeof(list);
   	while (i--)
   	{
		reset_eval_cost();	
     		if( !environment(list[i]) )
        		continue;
    		if( environment(list[i])->query("unit") )
        		continue;
   		if( list[i]->is_fighting() )
        		continue;
    		if( list[i]->is_busy() 
    		 || list[i]->is_nomove()
    		 || list[i]->is_hunluan()
    		 || list[i]->is_blind() )
        		continue;
    		if( !living(list[i]))
        		continue;
    		if( list[i]->query_temp("accept")!=this_object() )
        		continue;
        	list[i]->delete_temp("accept",0);
     		if( environment(list[i])==environment() )
     			continue;
		message_vision("$N的长眉一抖，将手朝虚空一抓。。。。。。\n",this_object());
		message("vision","\n\n一团祥云飘来，云中伸出一只霞光四射的巨手，将$N轻轻一抓，消失在天空。\n\n",environment(list[i]),list[i]);
		tell_object(list[i],"\n天空中伸出一只大手，一把抓起了你。\n\n");
		list[i]->move(environment());
     		message_vision("$N将手轻轻一抖，$n从虚空中露了出来。\n",this_object(),list[i]);
     		break;
   	}
   	call_out ("inviting",4+random(4));
}

void go_back2()
{
	remove_call_out("go_back2");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/lingtai/room" )
		return;
	message_vision(HIC"\n$N"HIC"化作一道清风不见了！\n"NOR,this_object());
	delete_temp("no_return");
	delete("panlong_id");
	delete_temp("invite");
	this_object()->move("/d/lingtai/room");
	message_vision(HIC"\n$N"HIC"随着一道清风出现了在众人的面前！\n"NOR,this_object());
}

void remove_npc()
{
	int i;
	string room;
	object *inv;
	if( !environment()
	 || base_name(environment())!="/d/lingtai/inside1" )
		return;
	inv = all_inventory(environment());
	while(i--)
	{
		if( inv[i]==this_object() 
		 || userp(inv[i]) )
		 	continue;
		room = inv[i]->query("startroom");
		if( room!=base_name(environment()) )
		{
			message_vision("\n$N哈哈一笑，长袖一甩，踏云往而去。\n",inv[i]);
			inv[i]->move(room);
			message_vision("$N从方寸山归来了。\n",inv[i]);
		}
	}
	go_back2();
}

int check_player()
{
	object room,who;
	if( !query("panlong_id") )
		return 0;
	who = find_player(query("panlong_id"));
	if( !who || !living(who) )
		return 0;
	room = find_object("/d/lingtai/inside1");
	if( !room )
		return 0;
	if( !present(this_object(),room) )
		return 0;
	return 1;	
}

string begin_go()
{
	object me,ob;
    	int visite;
    	me=this_player();
	ob=this_object();
	
	if( base_name(environment())!="/d/lingtai/room" )
    		return "此事待回瑶台后再说。";
	if( me->query("family/family_name")!="方寸山三星洞")
      		return 0;
   	if( me->is_knowing("puti_panlong")=="succ" )
		return RANK_D->query_respect(me) + "，你已经领悟了盘龙八式，还来干什么！";
	else if( me->is_knowing("puti_panlong") )	
        	return RANK_D->query_respect(me) + "，你已经浪费了一次机会了！";
	if( me->query("betray/count"))
     		return "徒儿，你判师后来投我方寸山，这盘龙八式你是学不会的。";
	if( !me->query_temp("pendding/fc_visite"))
		return "具体事项，你去问云阳真人吧。";
	if( query("panlong_id") )
	{
		if( check_player() )
			return "现在有你其他师兄弟在有事。";
		else	delete("panlong_id");	
	}	
	visite = 0;
	if( me->query_temp("pendding/fc_visite_pansi") )
		visite++;
	if( me->query_temp("pendding/fc_visite_hell") )
		visite++;
	if( me->query_temp("pendding/fc_visite_bhg") )
		visite++;	
	if( me->query_temp("pendding/fc_visite_wzg") )
		visite++;	
	if( me->query_temp("pendding/fc_visite_jjf") )
		visite++;	
	if( me->query_temp("pendding/fc_visite_moon") )
		visite++;	
	if( me->query_temp("pendding/fc_visite_sea") )
		visite++;
	if( me->query_temp("pendding/fc_visite_putuo") )
		visite++;
	if( visite<=3 )
		return "徒儿，你所邀请到的门派似乎太少！";
	set("panlong_id",me->query("id"));	
	remove_call_out("finish_visite");		
	call_out("finish_visite",1,me);
	return "乖徒儿，事情都办完了，马上到正院来。";
}

int accept_fight(object me)
{
	tell_object(me,CYN+name()+CYN"说道：" + RANK_D->query_rude(me) + "杀心太重，恐祸不久已！\n"NOR);
	return 0;
}

void die()
{
	if( environment() ) 
	{
        	message("sound", "\n\n菩提祖师微皱眉头，道：这厮果是个天成地就的！\n\n", environment());
        	EMOTE_D->do_emote(this_object(), "sigh",0,CYN,0,0,0);
        	message("sound", "\n菩提祖师身形一转，化做青烟走了。。。\n\n", environment());
        }
        destruct(this_object());
}

void check(object ob)
{
	remove_call_out("check");
	if( !ob || !living(ob) || !present(ob,environment()) )
	{
		command("chat* sigh");
		remove_npc();
		return;
	}
	remove_call_out("panlong_accept");
	call_out("panlong_accept",1,ob);
}

void finish_visite(object ob)
{
	if( !ob || !living(ob) )
		return;
	EMOTE_D->do_emote(this_object(), "smile",geteuid(ob),CYN,0,0,0);	
   	message_vision(HIC"\n$N"HIC"说完就化作一道清风不见了！\n"NOR,this_object());
	this_object()->move("/d/lingtai/inside1");
	message_vision(HIC"\n$N"HIC"随着一道清风出现了在众人的面前！\n"NOR,this_object());
	this_object()->set_temp("no_return",1);
	CHANNEL_D->do_channel(this_object(),"chat","我徒儿"+ob->query("name")+"悟出盘龙精要，今日邀请各位仙家道友同来灵台观礼！");
	set_temp("invite","public");
	command("chat 诸位仙贤如愿观礼，使accept master puti便可！\n");
	remove_call_out ("inviting");
	call_out ("inviting",3);
	remove_call_out("go_back2");
	call_out("go_back2",2700);
	remove_call_out("check");
	call_out("check",60,ob);
}

void panlong_accept(object me)
{
	object npc;
 	int pass;
 	remove_call_out("panlong_accept");
 	if( !me || !living(me) || !present(me,environment()) )
	{
		command("chat* sigh");
		remove_npc();
		return;
	}
 	me->delete_temp("fc_visite");
 	pass = 0;
 	if( me->query_temp("pendding/fc_visite_pansi") )
	{
		npc = present("jinling shengmu",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=2;
	}
	if( me->query_temp("pendding/fc_visite_hell") )
	{
		npc = present("dizang pusa",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=1;		
	}
	if( me->query_temp("pendding/fc_visite_bhg") )
	{
		npc = present("ningmou xianzi",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=2;		
	}
	if( me->query_temp("pendding/fc_visite_wzg") )
	{
		npc = present("zhenyuan daxian",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=2;		
	}
	if( me->query_temp("pendding/fc_visite_jjf") )
	{
		npc = present("lao ren",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=1;		
	}
	if( me->query_temp("pendding/fc_visite_moon") )
	{
		npc = present("xi wangmu",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=1;		
	}
	if( me->query_temp("pendding/fc_visite_sea") )
	{
		npc = present("ao guang",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=2;		
	}
	if( me->query_temp("pendding/fc_visite_putuo") )
	{
		npc = present("guanyin pusa",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=1;		
	}
	if( me->query_temp("pendding/fc_visite_shushan") )
	{
		npc = present("jian sheng",environment());
		if( !npc || userp(npc) )
			;
		else	pass+=1;		
	}
 	pass*= 2;
 	if( random(30)>=pass )
		me->set_temp("panlong_nopass",1);
	me->delete_temp("pendding");
	message_vision(HIC"\n众人都向菩提祖师抱拳见礼。\n\n"NOR,me);
	message_vision(HIC"\n菩提祖师转过身来对$N"HIC"道：乖徒儿，盘龙八式旨在悟，而不是学。你注意看好了。。。\n"NOR,me);
	call_out("direct_panlong",5,me);
}

void direct_panlong(object me)
{
	int damage;
	remove_call_out("direct_panlong");
	if( !me || !living(me) || !present(me,environment()) )
	{
		command("chat* sigh");
		say(name()+"说道：这贼孙，临走脱逃了，观礼之事就此打住吧。\n");
		remove_npc();
		return;
	}
	message_vision(HIY"
菩提祖师一摆手中菩提杖，陡然间一股劲气从菩提祖师的道袍中汹涌冲出。

菩提祖师顿时化作一团金光，舞起千均棒法，身形灵动，暗蕴杀机，猛然间一声清啸，震耳欲聋。

啸声初起，菩提祖师竟使菩提杖电光石火般的连攻八招，那金光好似“盘龙出沧海，踏云啸九天”！气势之所及，刹时正院中落叶尽去，石凳石桌被盘龙劲气震碎成无数小块，$N"HIY"内力不及，竟也被盘龙劲气所伤。。。\n"NOR,me);
	
	damage = me->query("eff_kee")/20;
	me->receive_wound("kee",damage,me);
	COMBAT_D->report_status(me,1);
	
	damage = me->query("kee")/10;
	me->receive_damage("kee",damage,me);
	COMBAT_D->report_status(me);

	damage = me->query("eff_sen")/20;
	me->receive_wound("sen",damage,me);
	damage = me->query("sen")/10;
	me->receive_damage("sen",damage,me);
	COMBAT_D->report_sen_status(me);
		
message_vision(HIY"
菩提祖师收住招式，众仙家均赞叹叫好。

"HIR"$N"HIR"受了重伤，支持不住，一下子坐倒在地。。。。
"HIC"
菩提祖师走到$N"HIC"面前和声道：徒儿，你好好体会一下，看看能悟出点什么来。\n"NOR,me);
	call_out("direct_panlong1",10,me);
}

void direct_panlong1(object me)
{
	remove_call_out("direct_panlong1");
	if( !me || !living(me) || !present(me,environment()) )
	{
		command("chat* sigh");
		say(name()+"说道：这贼孙，身娇肉贵吃不住这一棒子。观礼之事就此打住吧。\n");
		remove_npc();
		return;
	}
	message_vision(HIC"
	
菩提祖师与各派掌门一阵密议，诸位仙长皆笑颜不语。\n\n"NOR,me);
	command("chat* haha");
       	message_vision(HIC"
菩提祖师(Master puti)：各位道友，我们暂且不提这猴头，方才所言造化之事，望诸位回去思量思量。

"HIY"众人一同欣然应下。\n"NOR,me);
	remove_npc();	
       	message_vision(HIY"\n$N"HIY"盘腿在地等候师傅示下。\n"NOR,me);
       	tell_object(me,HIR"突然你耳边轻轻传来菩提祖师的声音：
徒儿，你且就地静心潜思，抓住心灵，能否掌握"+HIY"盘龙八式 "+HIR"就在此一举。\n"NOR);
	message_vision(HIC"\n\n$N盘腿闭目静静的回想刚才师傅所使的"+HIY"盘龙八式"+NOR"。\n",me);
	me->start_busy(20);
	call_out("direct_panlong2",15,me);
}

void direct_panlong2(object me)
{
	remove_call_out("direct_panlong2");
	if( !me || !living(me) )
	{
		command("chat* sigh");
		return;
	}
   	if( !me->query_temp("panlong_nopass"))
	{
		message_vision(HIR"\n\n\n
$N"HIR"潜思半日，突觉脑中灵气四起，宛如自己置身于一片空地手持"+HIY"金箍棒"+HIR"，不停歇的使出盘龙八式，直到浑身汗如雨下，半晌$N睁开眼睛，心里如海啸来临前般的平静，终于掌握了"+HIY"盘龙"+HIR"绝技！\n"NOR,me);
		command("chat* great "+me->query("id"));
		CHANNEL_D->do_channel(this_object(),"chat","本派弟子"+me->query("name")+"福如心至，悟得「"HIY"盘龙八式"HIC"」，实乃方寸之福。"NOR);
		me->set_knowing("puti_panlong","succ");
	   	me->delete_temp("panlong_nopass");
	   	me->save();
	   	return;
	}
   	message_vision(HIR"\n\n\n$N潜思半日，头脑中一片混乱，只依稀记住师傅所使的的招式，终不能化为己用。。。。\n"NOR,me);
	command("chat* sigh");
	CHANNEL_D->do_channel(this_object(),"chat","本派弟子"+me->query("name")+"与「"HIY"盘龙八式"HIC"」失之交臂，可惜可惜。"NOR);
	me->set_knowing("puti_panlong","fail");
	me->save();
   	me->delete_temp("panlong_nopass");
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="bonze" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：我们方寸山虽是有教无类，但是偏偏不收秃驴！哼！\n"NOR);
           	return ;
        }
        if( ob->query_level()<90 )
        {
		EMOTE_D->do_emote(this_object(), "sigh",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你还是下去打好基础再来。\n"NOR);
           	return ;
        }
        if( ob->query("class")!="taoist" )
        {
        	if( !ob->query_temp("pendding/fc_class") )
        	{
        		EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
        		tell_object(ob,CYN+name()+CYN"说道：以前并未见门内有"+RANK_D->query_respect(ob)+"，莫非你是散修出身？\n"NOR);
        		tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是先找小天师完成了门派试练再说。奈何如今乃是非常时期，诸多限制还望体谅。\n"NOR);
           		return ;
           	}	
        }
        if( !ob->query("shilian") && ob->query("shilian")!="fc" )
        {
        	EMOTE_D->do_emote(this_object(), "smile",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：入我门下，需得过了本门的「四象八卦阵」才行。\n"NOR);
           	return ;
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
	 {
	 	if( ob->set_titles("菩提祖师亲传弟子") )
		{
	 		tell_object(ob,HIC"【系统】你获得了称号：「"HIC"菩提祖师亲传弟子"NOR HIC"」。\n"NOR);
	 		ob->save();
	 	}
	 }	
} 