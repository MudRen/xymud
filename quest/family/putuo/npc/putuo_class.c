#include <ansi.h> 
inherit NPC;

int no_heal_up = 0;

void dest_me()
{
	if( environment() )
	{
		all_inventory(environment())->remove_killer(this_object());
		this_object()->remove_all_killer();
	}
	destruct(this_object());	
}

void create()
{
	string *ns,name,id,*ids;
	int i;
	mapping nn;
	
	ns = ({
		"刘","关","张","曹","公孙","孙","袁",
	});
	name = ns[random(sizeof(ns))];
	set("long","一个目光阴"+({"鹫","冷","森"})[random(3)]+"的汉子，面上布满戾气。\n");
	nn = NAME_D->random_name2(0, -1, name, 0, 0);
	name = nn["name"];
	ids = nn["id"];
	ids+= ({"sha shou","sha"});
	set_name(name,ids);
	//set("title",HIR"开封恶霸"NOR);
        set("gender","男性");
        set("age",17+random(20));
        set("con",30+random(10));
        set("per",10);
        set("str",30+random(10));
        set("int",15);
        set("attitude", "aggressive");
        set("bellicosity",1500);
        i = 30;
        set_level(i);
        set_skill("unarmed",i*10);
        set_skill("cuixin-zhang",i*10);
        set_skill("dodge",i*10);
        set_skill("xiaoyaoyou",i*10);
        set_skill("force",i*10);
        set_skill("ningxie-force",i*10);
        set_skill("parry",i*10);
        set_skill("blade",i*10);
        set_skill("spells",i*10);
        set_skill("dengxian-dafa",i*10);
        set_skill("wuhu-blade",i*10);
        map_skill("spells", "dengxian-dafa");
        map_skill("unarmed", "cuixin-zhang");
        map_skill("force", "ningxie-force");
        map_skill("blade", "wuhu-blade");
        map_skill("parry", "wuhu-blade");
        map_skill("dodge", "xiaoyaoyou");
	set("force_factor",300);
	set("mana_factor",400);
        set("water", 200000);
        set("food", 200000);

	set("chat_msg_combat", ({
		(: perform_action,"blade", "pushi" :),
		(: perform_action,"blade", "cheng" :),
		(: perform_action,"blade", "huwei" :),
		(: perform_action,"blade", "qihu" :),
	}));	
        setup();
}

int random_place()
{
	int i,j,k;
	object me,newob;
	mixed *file, exit;

        me=this_object();	
	file = get_dir( "/d/kaifeng/*.c", -1 );
	if( !sizeof(file) )
        	return 0;
	for(k=0;k<60;k++)  // try 20 times
        {
        	j = random(sizeof(file));
        	if( file[j][1]>0 ) 
                {
                	newob=load_object("/d/kaifeng/"+file[j][0]);
                	if( newob ) 
                        {  
                        	if( newob->query("no_fight") || newob->query("no_magic") 
	                          || newob->query("no_mieyao") || !(exit=newob->query("exits")) 
        	                  || sizeof(exit)<1 )
                	                continue;
                        	if( me && me->move(newob,1) ) 
				{
        	                        message_vision("$N走了过来。\n",me);
                	                return 1;
                        	}
			}
                }
        }
	return 0;
}

int information(object who)
{
	int lv;
	if( !who || !living(who) )
		return 0;
	lv = who->query_level();
	lv = last_num(lv);
	lv = 9-lv;
	lv = who->query_level()+random(lv);
	this_object()->set_level(lv);
	set_temp("weapon_level",lv);
	set_temp("armor_level",lv);
	set("env/test","HIB");
	set_skill("unarmed",lv*10);
        set_skill("cuixin-zhang",lv*10);
        set_skill("dodge",lv*10);
        set_skill("xiaoyaoyou",lv*10);
        set_skill("force",lv*10);
        set_skill("ningxie-force",lv*10);
        set_skill("parry",lv*10);
        set_skill("blade",lv*10);
        set_skill("spells",lv*10);
        set_skill("dengxian-dafa",lv*10);
        set_skill("wuhu-blade",lv*10);
	carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"wrists",1)->wear();
        carry_object(0,"shield",1)->wear();
        carry_object(0,"blade",1)->wield();
        set("owner_id",who->query("id"));
        who->set("family/putuo_class_guai",this_object());
	setup();
	powerup(0,1);
	if( random_place() )
		return 1;
	else
	{
		if( objectp(this_object()) )
			destruct(this_object());
		return 0;	
	}	
}

void check_me(object who)
{
	object me = this_object();
	if( !environment() || base_name(environment())=="/obj/void" )
	{
		remove_call_out("check_me");
		remove_call_out("dest_me");
		destruct(me);
		return;		
	}
	if( !who || !objectp(who) || !living(who) )
	{
		remove_call_out("check_me");
		remove_call_out("dest_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		message_vision("$N哈哈一笑，大模大样的离开了。\n\n",me);
		me->move("/obj/void");
		call_out("dest_me",3);
		return;
	}
	if( me->is_fighting(who) )
	{
		if( me->query_temp("be_busy")>=3 )
		{
			remove_call_out("check_me");
			all_inventory(environment())->remove_killer(me);
			me->remove_all_killer();
			message_vision(HIW"$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,me);
			tell_object(who,CYN+name()+CYN"说道：不打了不打了，这么搞，累得劳资一身汗，劳资就是不信佛。"NOR"\n");
			set_temp("last_touxiang",time());
			return;
		}
		else if( !me->is_busy() )
		{
			if( me->query("eff_kee")<me->query_maxkee() )
			{
				if( random(10)>=5 )
				{
					remove_call_out("check_me");
					all_inventory(environment())->remove_killer(me);
					me->remove_all_killer();
					message_vision(HIW"$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,me);
					tell_object(who,CYN+name()+CYN"说道：不打了不打了，出家人慈悲为怀，我现在一身是伤，你得扶我过马路！"NOR"\n");
					set_temp("last_touxiang",time());
					return;
				}
			}
			else if( me->query("sen_kee")<me->query_senkee() )
			{
				if( random(10)>=5 )
				{
					remove_call_out("check_me");
					all_inventory(environment())->remove_killer(me);
					me->remove_all_killer();
					message_vision(HIW"$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,me);
					tell_object(who,CYN+name()+CYN"说道：不打了不打了，出家人慈悲为怀，我现在犯困，你得扶我去看大夫。"NOR"\n");
					set_temp("last_touxiang",time());
					return;
				}
			}
		}
		else	me->add_temp("be_busy",1);
	}
	call_out("check_me",1,who);
}

void kill_ob(object who)
{
	object me = this_object();
	if( !who || !userp(who) || who->query("id")!=query("owner_id") )
	{
		remove_call_out("check_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		tell_object(who,CYN+name()+CYN"说道：劳资认识你吗？！"NOR"\n");
		return;
	}
	if( time()<query_temp("last_touxiang")+3 )
	{
		remove_call_out("check_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		tell_object(who,CYN+name()+CYN"说道：大爷现在太累了，等大爷缓缓气先！"NOR"\n");
		return;
	}
	if( query("kee")<query("eff_kee")
	 || query("eff_kee")<me->query_maxkee() )
	{
		remove_call_out("check_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		tell_object(who,CYN+name()+CYN"说道：。。。偶。。。快。。。死。。。了。。。！"NOR"\n");
		return;
	}
	if( query("sen")<query("eff_sen")
	 || query("eff_sen")<me->query_maxsen() )
	{
		remove_call_out("check_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		tell_object(who,name()+"昏昏沉沉的看着你，像个神经病。\n");
		return;
	}
	if( me->is_fighting(who) )
	{
		tell_object(who,"加油加油。\n");
		return;
	}
	if( query_temp("pending/exercising")
	 || query_temp("pending/respirate") )
	{
		remove_call_out("check_me");
		all_inventory(environment())->remove_killer(me);
		me->remove_all_killer();
		tell_object(who,name()+"大叫：大爷在练功，别烦我！\n");
		return;
	}	 
	remove_call_out("check_me");
	call_out("check_me",1,who);
	::kill_ob(who);
}

void create_danyao(string file,int v)
{
	remove_call_out("do_eat");
	if( v>1 )
		carry_object(file)->set_amount(v);
	else	carry_object(file);	
}

int accept_object(object who,object obj)
{
	string file;
	int v;
	if( obj->is_character() )
		return 0;
	if( this_object()->is_busy() )
	{
		tell_object(who,CYN+name()+CYN"说道：我现在正忙着呢。"NOR"\n");
		return 0;
	}	
	if( obj->query("name")=="金创药" )
	{
		EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
		file = base_name(obj);
		v = obj->query_amount();
		carry_object(base_name(obj))->set_amount(obj->query_amount());
		remove_call_out("create_danyao");
		call_out("create_danyao",3,file,v);
		return 1;
	}
	else if( obj->query("name")=="混元丹" )
	{
		EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
		file = base_name(obj);
		v = obj->query_amount();
		carry_object(base_name(obj))->set_amount(obj->query_amount());
		remove_call_out("create_danyao");
		call_out("create_danyao",3,file,v);
		return 1;
	}
	else	return 0;
}

void die()
{
	object who;
	who = query_temp("last_damage_from");
	if( who && query("owner_id")
	 && who->query("id")==query("owner_id")
	 && present(who,environment()) )
	{
		message_vision(HIW"$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,this_object());
		tell_object(who,CYN+name()+CYN"说道：不打了不打了，这么搞，累得劳资一身汗，算了算了，劳资入佛门罢。"NOR"\n");
		who->delete("family/putuo_class_guai");
		who->set("family/putuo_class_succ",1);
		tell_object(who,HIY"【系统】你成功完成了普陀山的入门任务。"NOR"\n");
	}
	else	message_vision("\n$N大叫一声，撒腿就跑。\n\n",this_object());
	destruct(this_object());
}

void unconcious()
{
	die();
}

int heal_up()
{
	int i;
	if( no_heal_up>0 )
		return 0;
	if( environment() )
	{
		if( !query("stay_time") )
			set("stay_time",time());
		else if( time()>=query("stay_time")+1800
		      || !query("owner_id") )
		{
			no_heal_up = 1;
			remove_call_out("check_me");
			remove_call_out("dest_me");
			call_out("dest_me",1);
			return 0;
		}		      
	}
	if( !living(this_object())
	 || this_object()->is_busy() )
		return ::heal_up();
	if( query_temp("pending/exercising")
	 || query_temp("pending/respirate") )
		::heal_up();
	if( query("eff_kee")<this_object()->query_maxkee() 
	 && present("jinchuang yao") )
	{
		i = 3;
		while(i--)
			command("eat yao");
	}
	if( query("eff_sen")<this_object()->query_maxsen() 
	 && present("hunyuan dan") )
	{
		i = 3;
		while(i--)
			command("eat dan");
	}
	if( query("kee")<query("eff_kee") )
		command("exert recover");
	if( query("sen")<query("eff_sen") )
		command("exert refresh");
	if( !this_object()->is_fighting()
	 && query("force")<500 )
		command("exercise 200");
	return ::heal_up();
}