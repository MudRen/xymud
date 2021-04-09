#include <ansi.h>
inherit NPC;

void create()
{
       	set_name("龙表弟", ({"long biaodi", "long", "biaodi"}));
       	set_level(40);
	set("long","龙少爷的表弟和死党。\n");
	set("title","南海龙太子");
       	set("gender", "男性");
       	set("age", 26);
	set("per", 30);
	set("attitude", "peaceful");
       	set("shen_type", 1);
       	create_family("东海龙宫",3, "水族");
        setup();
}

void do_hit()
{
	if( !living(this_object()) 
	 || !this_object()->is_fighting() )
		return;
	if( random(query_temp("surrender"))<3 )
	{
		if( query("eff_kee")<this_object()->query_maxkee() )
		{
			message_vision(HIW"\n$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,this_object());
			message_vision(CYN"$N"CYN"说道：不打了，你们以多欺少，我膝盖受伤了。这么打不公平。\n"NOR,this_object());
			set_temp("no_Kill",CYN"$N"CYN"说道：不打了，你们以多欺少，我膝盖受伤了。这么打不公平。\n"NOR);
			add_temp("surrender",1);
			this_object()->remove_all_killer();
			all_inventory(environment())->remove_killer(this_object());
			return;
		}
		if( query("eff_sen")<this_object()->query_maxsen() )
		{
			message_vision(HIW"\n$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,this_object());
			message_vision(CYN"$N"CYN"说道：不打了，你们以多欺少，我精神很受打击。这么打不公平。\n"NOR,this_object());
			set_temp("no_Kill",CYN"$N"CYN"说道：不打了，你们以多欺少，我精神很受打击。这么打不公平。\n"NOR);
			add_temp("surrender",1);
			this_object()->remove_all_killer();
			all_inventory(environment())->remove_killer(this_object());
			return;
		}
	}	
	if( present("jinchuang yao") )
		command("eat yao");
	if( present("hunyuan dan") )	
		command("eat dan");
	QUEST_D->addKee(this_object());	
	QUEST_D->addSen(this_object());
	command("unwield unarmed");
	command("unwield fork");
	command("wield fork");
	if( !query_temp("pfm_action") )
		command("perform dhwl");
	else	command("perform bibo");
	command("unwield fork");
	command("wield unarmed");
	command("perform sheshen");
	if( random(2) )
		command("perform leidong");			
	if( random(2) )
		command("perform shenglong");	
} 

void set_skills(int level)
{
	int j;
	if( level<40 )
		level = 40;
	level = level-5+random(5);
	set_level(level);
	j = level*10;
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set_skill("fork", j);
        set_skill("fengbo-cha", j);
        set_skill("dragonstep", j);
        set_skill("dragonfight", j);
        set_skill("dragonforce", j);
        set_skill("seashentong", j);
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("spells", "seashentong");
        map_skill("dodge", "dragonstep");
        map_skill("unarmed", "dragonfight");
        set("chat_chance_combat",50);
	set("chat_msg_combat", ({
        	(: do_hit :),
	}));
	set("env/test","HIR");
	set_temp("weapon_level",40+random(15));
	set_temp("armor_level",40+random(15));
        setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"fork",1);
	carry_object(0,"unarmed",1);
	carry_object("/d/obj/drug/jinchuang4")->set_amount(200);
	carry_object("/d/obj/drug/hunyuandan4")->set_amount(200);
	command("enable max");
	command("enchant max");
	powerup(0,1);
}

void kill_ob(object who)
{
	string msg;
	msg = query_temp("no_Kill");
	if( msg && stringp(msg) )
	{
		message_vision(msg,this_object());
		this_object()->remove_all_killer();
		all_inventory(environment())->remove_killer(this_object());
		return;
	}
	else	::kill_ob(who);
}

void die()
{
	if( environment() )
	{
		message_vision(HIW"\n$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,this_object());
		environment()->finish();
	}
	destruct(this_object());
}

void unconcious()
{
	QUEST_D->addKee(this_object());	
	QUEST_D->addSen(this_object());
	if( query("kee")<1 || query("sen")<1 )
	{
		die();
		return;
	}
}

void drug_me(string file)
{
	object ob;
	if( ob=carry_object(file) )
		command("eat "+geteuid(ob));
	if( present("jinchuang yao") )
		command("eat yao");
	if( present("hunyuan dan") )	
		command("eat dan");		
	command("exert recover");
	command("exert refresh");
}

int accept_object(object who,object obj)
{
	string file;
	if( obj->query("name")!="金创药" 
	 && obj->query("name")!="混元丹" )
		return 0;
	EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
	file = base_name(obj);
	call_out("drug_me",2,file);
	return 1;
}