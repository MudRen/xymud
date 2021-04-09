//迷宫怪物

#include <ansi.h> 
inherit NPC;
 
void create()
{
	string *ns,name,id,*ids;
	int i;
	mapping nn;
	
	ns = ({
		"澹台","宇文","赫连","端木","夏候","澹台",
	});
	name = ns[random(sizeof(ns))];
	set("long","一个目光阴"+({"鹫","冷","森"})[random(3)]+"的胡人，面目狰狞，充满杀气。\n");
	set("names",name);
	nn = NAME_D->random_name2(0, 0, name, 0, 0);
	name = nn["name"];
	ids = nn["id"];
	ids+= ({"sha shou","sha"});
	set_name(name,ids);      
        set("gender","男性");
        set("age",17+random(20));
        set("con",25+random(10));
        set("per",10);
        set("str",25+random(10));
        set("int",15);
        set("bellicosity",500);
        i = 25+random(6);
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
	set("force_factor",i*5);

        set("water", 200000);
        set("food", 200000);
	
	ns = ({YEL"三花堂供奉"NOR,RED"拜火教徒"NOR,WHT"西域胡人"NOR,});
        set("title",ns[random(sizeof(ns))]);
        set_temp("armor_level",i);
        set_temp("weapon_level",i);
        if( random(i)==25 )
        	set("env/test","HIR");	
        else if( random(i)==10 )
        	set("env/test","HIB");
        else if( random(i)>15 )
        	set("env/test",({"HIB","HIY",})[random(2)]);
        else	set("env/test",({"NOR","NOR","HIB","HIY",})[random(4)]);

 	set("chat_chance_combat", i*5);
 	if( random(5)<2 )
 	{
 		set("chat_msg_combat", ({
			(: perform_action,"blade", "pushi" :),
			(: perform_action,"blade", "cheng" :),
			(: perform_action,"blade", "huwei" :),
        	}));
        }
        else
        {
        	set("chat_msg_combat", ({
			(: perform_action,"blade", "pushi" :),
			(: perform_action,"blade", "cheng" :),
			(: perform_action,"blade", "qihu" :),
        	}));	
        }	
        setup();
        set("max_kee",2000);
        set("max_sen",2000);
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"blade",1)->wield();
        carry_object(0,"pifeng",1)->wear();
        powerup(0,1);
}

void die()
{
        if( !environment() || !environment()->query("mazeobj") )
	{
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
	::die();
}

void reward_ob(object who)
{
	object ob,xin,weapon;
	int i;
	string str,file,*dir;

        if( !who || !userp(who) || !present(who,environment()) 
         || !environment()->query("mazeobj") 
         || !who->query_temp("maze/xiaoyan"))
        {
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
        else
        {
        	message_vision("\n"HIR"$N"HIR"伤势过重，「啪」的一声，挣扎着抽动了几下就死了。\n"NOR,this_object()); 
        	message_vision("早有一干僧人自后上前，收拾尸骸，超度往生去了。\n\n",this_object());
        }
	if( !wizardp(who) && (who->query_level()>30||who->query_level()<25) )
	{
		tell_object(who,HIG"【副本】小雁塔：你在本地图得不到任何奖励。\n"NOR);
		destruct(this_object());
		return;
	}
	
	i = who->query_kar()+random(who->query_per());
	if( random(i)==25 )
        	set("env/test","HIR");	
        else if( random(i)==10 )
        	set("env/test","HIB");
        else if( random(i)>15 )
        	set("env/test",({"HIB","HIY",})[random(2)]);
        else	set("env/test",({"NOR","NOR","HIB","HIY",})[random(4)]);
	
	dir = ({
		"armor","cloth","hand","kui","neck",
		"pifeng","ring","shield","shoes",
		"waist","wrists",
	});	
	file = dir[random(sizeof(dir))];
	if( file )
	{
		ob = new("/d/obj/narmor/"+file);
		ob->set("from","【小雁塔副本】");
		ob->init_armor(this_object());
		if( !ob->move(who) )
		{
			destruct(ob);
			tell_object(who,HIR"【副本】小雁塔：你的背包满了。\n"NOR);
		}
		else	tell_object(who,HIG"【副本】小雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);
	}

	if( random(i)>20 || wizardp(who) )
	{
		if( objectp(weapon=who->query_temp("weapon")) )
			file = weapon->query("skill_type");
		else	file = "unarmed";	
		dir = ({
			"axe","blade","blade","hammer","mace","spear",
			"staff","stick","sword","unarmed","whip","fork",
		});
		if( member_array(file,dir)==-1 )
			file = dir[random(sizeof(dir))];
		if( file )
		{
			ob = new("/d/obj/nweapon/"+file);
			ob->set("from","【小雁塔副本】");
			ob->init_weapon(this_object());
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】小雁塔：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】小雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);	
		}
	}
	destruct(this_object());	
	return;
}

void unconcious()
{
        die();
}

int accept_fight(object who) { return 0; }

void init()
{
        object me = this_player();
        
        if( !this_object()->is_fighting() 
         && userp(me) )
        {
        	if( me->query_level()<28 )
        	{
        		if( random(me->query_per())<30 )
        		{
                		this_object()->kill_ob(me);
                		this_object()->command("follow "+me->parse_command_id_list()[0]);
                	}
		}                        	
        }
        add_action("do_go","go");
}               

int do_go(string arg)
{
        if( !arg || !userp(this_player()) )
                return 0;
        if( living(this_object()) 
         && (is_fighting(this_player())||!this_object()->is_fighting()) )
                return err_msg(query("name")+"嘶牙咧嘴的拉住你。\n");
        return 0;
}       

