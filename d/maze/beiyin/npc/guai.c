//背阴巷迷宫怪物

#include <ansi.h> 
inherit NPC;
 
void create()
{
	string *ns,name,id,*ids;
	int i;
	mapping nn;
	
	ns = ({
		"霸","厄","虎","屠","恨",
	});
	name = ns[random(sizeof(ns))];
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
        set("attitude", "aggressive");
        set("bellicosity",500);
        i = 10+random(16);
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
	set("force_factor",50);

        set("water", 200000);
        set("food", 200000);

        set("title","三花堂杀手");
        set_temp("armor_level",i);
        set_temp("weapon_level",i);
        if( random(i)==10 )
        	set("env/test","HIB");
        else if( random(i)>15 )
        	set("env/test",({"HIB","HIY",})[random(2)]);
        else	set("env/test",({"NOR","NOR","HIB","HIY",})[random(4)]);

 	set("chat_chance_combat", i*5);
 	set("chat_msg_combat", ({
		(: perform_action,"blade", "pushi" :),
		(: perform_action,"blade", "cheng" :),
        }));
        setup();
        set("max_kee", 800+random(100)*i);
        set("max_sen", 800+random(100)*i);
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"blade",1)->wield();
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
	int i,wx;
	string str,file,*dir;

        if( !who || !userp(who) || !present(who,environment()) 
         || !environment()->query("mazeobj") 
         || !who->query_temp("maze/beiyin"))
        {
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
        else
        {
        	message_vision("\n$N见势不妙，慌忙跪倒在地，不迭磕头”这位"+RANK_D->query_respect(who)+"还请手下留情啊，小的愿意伏法“。\n",this_object()); 
        	message_vision("一旁的衙役呵斥几声，上前将之捆绑妥当，推拉着离去。\n",this_object());
        }
	if( !wizardp(who) && who->query_level()>25 )	
	{
		tell_object(who,HIG"【副本】背阴巷：你的修为太高，在本地图得不到任何奖励。\n"NOR);
		destruct(this_object());
		return;
	}
	
	wx = 2500;
	wx = wx*4/5+random(wx/10);
	who->add("combat_exp",wx);
	tell_object(who,HIG"【副本】背阴巷：你得到了"HIR+wx+"点武学经验。\n"NOR);

	i = who->query_kar()+random(who->query_per());
	
	if( random(i)>10 )
	{
		if( !objectp(xin=present("beiyin map",who)) )
		{
			xin = new("/d/maze/beiyin/obj/map");
			str = MAZE_D->query_maze_mainobj(this_object())->display_common_map(environment());
			str = replace_string(str,"★","");
			str = replace_string(str,HBWHT" ","★ ");
			str = replace_string(str,NOR,"");
			str = replace_string(str,GRN,"");
			str = replace_string(str,BGRN,"");
			str = replace_string(str,"        迷宫地图：","  背阴巷地图：(★为起点)");
			str = replace_string(str,"表示迷宫入口；","");
			str = replace_string(str,"表示迷宫出口。","");
			str = COLOR_D->clean_color(str);
			str+= NOR;
			xin->set("long",str);
			if( !xin->move(who) )
			{
				destruct(xin);
				tell_object(who,HIR"【副本】背阴巷：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】背阴巷：你得到了 「"HIY"背阴巷地图"HIG"」。\n"NOR);
		}
		
	}
	
	if( random(i)>20 || wizardp(who) )
	{
		dir = ({
			"armor","cloth","hand","kui","neck",
			"pifeng","ring","shield","shoes",
			"waist","wrists",
		});	
		file = dir[random(sizeof(dir))];
		if( file )
		{
			ob = new("/d/obj/narmor/"+file);
			ob->set("from","【背阴巷副本】");
			ob->init_armor(this_object());
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】背阴巷：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】背阴巷：你得到了 "+ob->short()+HIG" 。\n"NOR);
		}
	}
	else if( random(i)>25 || wizardp(who) )
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
			ob->set("from","【背阴巷副本】");
			ob->init_weapon(this_object());
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】背阴巷：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】背阴巷：你得到了 "+ob->short()+HIG" 。\n"NOR);	
		}
	}
	destruct(this_object());	
	return;
}

void unconcious()
{
        die();
}

void init()
{
        object me = this_player();
        
        if( !this_object()->is_fighting() 
         && userp(me) )
        {
        	if( me->query_level()<20 )
        	{
        		if( random(me->query_per())<20 )
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
                return err_msg(query("name")+"将你拦住。\n");
        return 0;
}       

