#include <ansi.h>
#include <combat.h>
inherit NPC;

void create()
{
	mapping name;
	string id,n,tmp;
	int i;
	
	name = NAME_D->random_name("yaoguai");
	n = name["name"];
	i = strlen(n);
	n = sprintf("%s",n[0..i-3])+"兽";
	id = name["id"][0];
	sscanf(id,"%s %s",id,tmp);
	i = 5+random(10);
	set_level(i);
	i = i*10;
	set_name(n,({id,"yeshou","shou"}));
	set("long","山中奇形怪兽，于山石之间吸取天地元气多年，已快通灵开智。\n");
	set("age", 5);
	set("race", "野兽" );
	set_skill("unarmed",i);
	set_skill("dodge",i);
  	set_skill("parry",i);
  	set_temp("weapon_level",1+random(5));
  	set_temp("armor_level",1+random(5));
  	setup();
        set("max_kee",100);
        set("max_sen",100);
        powerup(0,1);
}

string query_maze_file(){return "tupo10";}

void dies()
{
	int succ;
	string *file,my_weapon;
	object weapon,ob,who = query_temp("last_damage_from");

	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",this_object());
	if( !who || !present(who,environment()) 
	 || !userp(who) || (who->query_level()>10 && !wizardp(who)) )
	{
		destruct(this_object());
		return;	
	}
	
	weapon = who->query_temp("weapon");
	if( !weapon )
		my_weapon = "unarmed";
	else	my_weapon = weapon->query("skill_type");
	succ = who->query_kar();
	succ = succ/2+random(succ/2);
	if( succ>25 )
		this_object()->set("env/test","HIB");
	else if( succ>18 )	
		this_object()->set("env/test","HIY");
	else	this_object()->set("env/test",({"NOR","HIY","NOR","NOR","NOR","HIB","NOR","NOR","HIY"})[random(9)]);	
	
	if( random(4)==0 )
	{
		ob = new("/d/obj/nweapon/"+my_weapon);
		ob->init_weapon(this_object());
		if( ob->move(who) )
			tell_object(who,HIC"【副本】你得到了"+ob->short()+HIC"。\n"NOR);
		else
		{
			if( ob ) destruct(ob);
			tell_object(who,HIY"【系统】你的背包满了。\n"NOR);
		}
		destruct(this_object());
		return;
	}
	if( random(3)==0 )
		file = ({"armor","cloth","pifeng",});	
	else if( random(4)==0 )
		file = ({"neck","ring","hand",});
	else if( random(2)==0 )
		file = ({"armor","cloth","kui","pifeng","shield","shoes",});
	else	file = ({"armor","cloth","hand","kui","neck","pifeng","ring","shield",
			"shoes","waist","wrists",
		});
	ob = new("/d/obj/narmor/"+file[random(sizeof(file))]);
	ob->init_armor(this_object());
	if( ob->move(who) )
		tell_object(who,HIC"【副本】你得到了"+ob->short()+HIC"。\n"NOR);
	else
	{
		if( ob ) destruct(ob);
		tell_object(who,HIY"【系统】你的背包满了。\n"NOR);
	}
	destruct(this_object());
	return;	
}
int is_beast(){ return 1;}

string obj_from(){ return "【10级突破副本】";}
