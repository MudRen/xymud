// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string begin_go();
string shilian(){ return "地狱不空，地藏不出。";}
	
void create()
{
	set_name("地藏王菩萨", ({"dizang pusa", "pusa","dizang"}));
  	set_level(180);
  	set("long", "面如朱玉，大耳垂肩，一脸肃静。他便是主管阴曹地府，天下鬼魂的地藏王菩萨。\n");
  	set("gender", "男性");
  	set("class", "ghost");
  	set("age", 1800);
  	set("attitude", "friendly");
  	set("shen_type", 1);
  	set("nkgain",790);
  	set("force_factor", 200);
  	set("mana_factor", 200);
  	set("title",HIR"地狱不空 誓不成佛"NOR);
	create_family("阎罗地府", 1, "你好");
   	set_skill("unarmed", 1800);
  	set_skill("whip", 1800);
  	set_skill("hellfire-whip", 1800);
  	set_skill("dodge", 1800);
   	set_skill("parry", 1800);
   	set_skill("literate", 1800);
   	set_skill("spells", 1800);
  	set_skill("force", 1800);
  	set_skill("tonsillit", 1800);
  	set_skill("ghost-steps", 1800);
     	set_skill("gouhunshu", 1800);
   	set_skill("jinghun-zhang", 1800);
  	set_skill("kusang-bang", 1800);
   	set_skill("zhuihun-sword", 1800);
   	set_skill("sword", 1800);
   	set_skill("stick", 1800);

	map_skill("force", "tonsillit");
  	map_skill("unarmed", "jinghun-zhang");
	map_skill("dodge", "ghost-steps");
	map_skill("spells", "gouhunshu");
	map_skill("parry", "hellfire-whip");
	map_skill("whip", "hellfire-whip");
	map_skill("sword", "zhuihun-sword");
	set("inquiry",([
		"灵台观礼": (: begin_go :),
  		"灵台观礼": (: begin_go :),
		"试炼" : (: shilian :),
	]));
	setup();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
        carry_object(0,"whip",1)->wield();
	carry_object(0,"cloth",1)->wear();
        powerup(0,1);
}

int set_skills(object npc,object who)
{
	int level,j;
	if( !who || !npc || npc->is_fighting()
	 || !living(npc) )
	 	return 0;
	level = who->query_level();
	if( level<40 )
		level = 40;
	j = level*10;
	npc->set_level(level);		
        npc->set_skill("unarmed", j);
        npc->set_skill("dodge", j);
        npc->set_skill("parry", j);
        npc->set_skill("force", j);
        npc->set_skill("spells", j);
 	switch(random(4))
 	{
 		case 0 :
 			npc->set_skill("whip", j);
        		npc->set_skill("hellfire-whip", j);
        		npc->map_skill("whip", "hellfire-whip");
        		npc->map_skill("parry", "hellfire-whip");
        		npc->carry_object(0,"whip",random(10))->wield();	
			break;
		case 1 :	
        		npc->set_skill("stick",j);
        		npc->set_skill("kusang-bang",j);
        		npc->map_skill("stick","kusang-bang");
        		npc->map_skill("parry","kusang-bang");
        		npc->carry_object(0,"whip",random(10))->wield();	
			break;
		default :
			npc->set_skill("sword",j);
			npc->set_skill("zhuihun-sword",j);
        		npc->map_skill("parry","zhuihun-sword");
        		npc->map_skill("sword","zhuihun-sword");
        		npc->carry_object(0,"sword",random(10))->wield();	
			break;
	}				
        npc->set_skill("ghost-steps", j);
        npc->set_skill("jinghun-zhang", j);
        npc->set_skill("tonsillit", j);
        npc->set_skill("gouhunshu", j);
        npc->map_skill("force", "tonsillit");
        npc->map_skill("spells", "gouhunshu");
        npc->map_skill("dodge", "ghost-steps");
        npc->map_skill("unarmed", "jinghun-zhang");
        npc->setup();
	npc->carry_object(0,"armor",random(10))->wear();
	npc->carry_object(0,"cloth",random(10))->wear();
	npc->carry_object(0,"pifeng",random(10))->wear();
	npc->carry_object(0,"kui",random(10))->wear();
	npc->carry_object(0,"shoes",random(10))->wear();
	npc->set("env/wimpy",10);
	npc->set("class","ghost");
	npc->powerup(1);
	npc->set("owner_ob",who);
	return 1;
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/death/cuiyun" )
		return;
	message_vision("\n"HIC"地藏王菩萨道：观礼事毕，本尊这就回转地府，老祖所议之事，容某考虑考虑。\n"NOR,this_object());
        message_vision(HIB"\n$N"HIB"往黑暗处一指，只见所指之处仿佛出现一扇门，$N大步走入，门也随之消失…… \n\n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/death/cuiyun");
	message_vision(HIB"\n悲风四起，杀气漫空，黑暗暗俱是些鬼哭神嚎，伴随着冷森森的笑声，$N漫步从黑暗中出现…… \n\n"NOR,this_object());			
}

string begin_go()
{
	mapping temp;
	mixed *files,*obj;
	object room,gui,me,ob;
	int dx,wx,qn,i;
    	
    	me=this_player();
	ob=this_object();
	
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( base_name(environment())!="/d/death/cuiyun" )
    		return "此事待贫僧回黄泉后再议。";
	if( me->query_temp("pendding/fc_visite_hell") )
	{
        	message_vision("\n"HIC"地藏王菩萨道：" + RANK_D->query_respect(me) + "本座即刻赴灵台之约！\n"NOR,me);
        	message_vision(HIB"\n$N"HIB"往黑暗处一指，只见所指之处仿佛出现一扇门，$N大步走入，门也随之消失…… \n\n"NOR,ob);
        	ob->set_temp("no_return",1);
    		ob->move("/d/lingtai/inside1");
    		message_vision(HIB"\n悲风四起，杀气漫空，黑暗暗俱是些鬼哭神嚎，伴随着冷森森的笑声，$N漫步从黑暗中出现…… \n\n"NOR,ob);
		remove_call_out("go_back");
    		call_out("go_back",2700);
		return "我与老祖正好有事相商。";
	}
	if( me->query_temp("pendding/fc_visite_hellsha")<6 )
	{
		files = ({
			"/d/death/bidouya","/d/death/walk1","/d/death/new-out8",
			"/d/death/new-walk4","/d/death/new-sifang1","/d/death/new-out4"});
		for(i=0;i<sizeof(files);i++)
		{
			room = find_object(files[i]+".c");
			if( !room )
				continue;
			temp = room->query_temp("objects");
			if( !temp || !mapp(temp) )
				continue;
			obj = values(temp);	
			if( !obj || !arrayp(obj) || sizeof(obj)<1 )
				continue;
			gui = obj[random(sizeof(obj))];
			if( !gui || !living(gui) || gui->is_fighting() )
				continue;
			if( !set_skills(gui,me) )
				continue;
			return "近来，地府事多，我看那"+gui->name()+"好似已安奈不住，你前去帮本座灭之。";	
		}
		return "哈哈，地府这些天还算太平，你且下去，待我需要时再来。";
	}
	me->set_temp("pendding/fc_visite_hell",1);
	me->delete_temp("pendding/fc_visite_hellsha");
	me->add_temp("pendding/fc_visited",1);
	CHANNEL_D->do_channel(this_object(),"chat",HIY+me->name()+HIC"助我度灭黄泉野鬼,届时贫僧一定上灵台观礼！"NOR);
	if( !me->query("mark/guanli_hell") )
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
		me->set("mark/guanli_hell",1);
	}	
	tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
	if( me->query("family/family_name")=="方寸山三星洞")
		return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";
	else	return "多谢多谢。";	
}

int accept_object(object me, object ob)
{
	int lv;
	if( (me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin"))
	{	 
		if( base_name(ob)=="/d/sea/obj/longjin" )
		{
	 		EMOTE_D->do_emote(this_object(), "great",geteuid(me),CYN,0,0,0);
     			tell_object(me,CYN+name()+CYN"说道：好，好，本座要的正是这个。有劳"+me->query("name")+ RANK_D->query_respect(me) +"了！\n"NOR);
     			me->set("fangcun/panlong_hell_longjin","done");
	 		if( ob->query_temp("iambaddragon"))
     	 			me->delete("fangcun/panlong_nowayhell");
      			return 1;
		}
	}
	if( me->query("pedding/hell_shilian_level")>0 )
	{
		if( !me->query("pedding/hell_shilian")
		 || me->query("shilian")=="hell" )
			return 0;
		lv = me->query_level();
		if( lv>me->query("pedding/hell_shilian_level") )
		{
			tell_object(me,CYN+name()+CYN"说道：这是你晋级之前的任务吧？\n"NOR);
			return 0;
		}
		if( !me->query("pedding/hell_shilian_obf") )
			return notify_fail(me->query("pedding/hell_shilian"));
		if( base_name(ob)!=me->query("pedding/hell_shilian_obf") )
			return notify_fail(me->query("pedding/hell_shilian"));
		if( !me->query("pedding/hell_shilian_ob") )
			return notify_fail(me->query("pedding/hell_shilian"));
		if( ob->name()!=me->query("pedding/hell_shilian_ob") )
			return notify_fail(me->query("pedding/hell_shilian"));
		 EMOTE_D->do_emote(this_object(), "young",geteuid(me),CYN,0,0,0);
		 me->delete("pedding/hell_shilian_obf");
		 me->delete("pedding/hell_shilian_ob");
		 me->delete("pedding/hell_shilian_level");
		 me->delete("pedding/hell_shilian");
		 me->set("shilian","hell");
		 command("chat* gongxi");
		 tell_object(me,HIY"【师门】你成功完成了地藏菩萨的试炼任务，现在可以拜他老人家为师了，羡慕嫉妒恨啊！\n"NOR);
		 return 1;
	} 
	return 0;
}

void armor_job(object me)
{
	int lv;
	string msg,*files;
	object ob;
	if( !me || !userp(me) || !living(me)
	 || !environment()
	 || me->query_level()<100 
	 || !present(me,environment()) )
	 	return;
	if( me->query("family/master_name")==query("name")
	 && me->query("family/master_id")==query("id")	)
	  	return;
	if( me->query("class")!="ghost"
	 && !me->query_temp("pending/hell_class") )
		return;
	if( me->query("shilian") && me->query("shilian")=="hell" )
		return;
	lv = me->query_level();
	msg = me->query("pedding/hell_shilian");
	if( !msg || lv>me->query("pedding/hell_shilian_level") )
	{
		lv/= 2;
		lv+= random(30);
		set_temp("armor_level",lv);
		set("env/test",({"HIB","HIR","HIB","HIR","HIY"})[random(5)]);
		files = ({"armor","cloth","hand","kui","neck","pifeng","ring","shield","shoes","waist","wrists",});
		ob = new("/d/obj/narmor/"+files[random(sizeof(files))]);
		if( !ob )
			return;
		if( !ob->init_armor(this_object()) )
		{
			if( ob ) destruct(ob);
			return;
		}
		msg = CYN+name()+CYN"说道：所谓我不入地狱谁入地狱，你若诚心拜我，那就替我寻得那"+ob->name()+CYN+"("+ob->query("id")+CYN")来。\n"NOR;
		me->set("pedding/hell_shilian_ob",ob->name());
		me->set("pedding/hell_shilian_obf",base_name(ob));
		if( ob ) destruct(ob);
		tell_object(me,msg);
		me->set("pedding/hell_shilian",msg);
		me->set("pedding/hell_shilian_level",me->query_level());
	}	
	else	tell_object(me,msg);
	return;	
}	 	

void attempt_apprentice(object ob)
{
	if( ob->query_level()<100 )
        {
        	EMOTE_D->do_emote(this_object(), "addoil",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(ob)+"还是去先打好基础。\n"NOR);
           	return ;
        }
        if( ob->query("class")!="ghost" )
	{
		if( !ob->query_temp("pending/hell_class") )
        	{
                	EMOTE_D->do_emote(this_object(), "shake",geteuid(ob),CYN,0,0,0);
                	tell_object(ob,CYN+name()+CYN"说道：吾等不收外门弟子，若诚心想入我门，还是先去帮阎罗核对生死簿。\n"NOR);
                	return ;
                }		
	}  
	if( !ob->query("shilian") && ob->query("shilian")!="hell" )
        {
        	EMOTE_D->do_emote(this_object(), "hmm",geteuid(ob),CYN,0,0,0);
           	armor_job(ob);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们阎罗地府发扬光大。\n"NOR);
	CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY"地藏菩萨"HIM"近日又新收了一门弟子！"NOR);
	command("recruit " + geteuid(ob) );
	return;
}

int recruit_apprentice(object ob)
{
	 if( ::recruit_apprentice(ob) )
	 {
	 	ob->set("class","ghost");
	 	if( ob->set_titles("地藏菩萨亲传弟子") )
		{
	 		tell_object(ob,HIC"【系统】你获得了称号：「"HIB"地藏菩萨亲传弟子"NOR HIC"」。\n"NOR);
	 		ob->save();
	 	}
	 }	
} 

void die()
{
	if( environment() )
		message_vision("\n\n$N脸色忽的一变，朝向黄泉位置皱了皱眉，“事有蹊跷，老衲得去看上一看！”\n$N化作一道金光径往黄泉位置而去。\n\n",this_object());
	destruct(this_object());
}	