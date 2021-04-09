#include <ansi.h> 
inherit SUPER_NPC;
 
void create()
{
	string *ns,name,id,*ids;
	int i;
	mapping nn;
	
	ns = ({
		"卢","段","招","董","万","南",
	});
	name = ns[random(sizeof(ns))];
	set("long","一个目光阴"+({"鹫","冷","森"})[random(3)]+"的汉子，长得短小精悍，黝黑的面上充满杀气。\n");
	nn = NAME_D->random_name2(0, 0, name, 0, 0);
	name = nn["name"];
	ids = nn["id"];
	ids+= ({"sha shou","sha"});
	set_name(name,ids);      
        set("gender","男性");
        set("age",30+random(20));
        set("per",20);
        set("bellicosity",1500);
        i = 39;
        set_level(i);
        set_skill("unarmed",i*10);
        set_skill("dodge",i*10);
        set_skill("lihuo-dodge",i*10);
        set_skill("force",i*10);
        set_skill("fireforce",i*10);
        set_skill("parry",i*10);
        set_skill("blade",i*10);
        set_skill("spells",i*10);
        set_skill("dengxian-dafa",i*10);
        set_skill("wudu-shenzhang",i*10);
        set_skill("wuhu-blade",i*10);
        map_skill("spells", "dengxian-dafa");
        map_skill("unarmed", "wudu-shenzhang");
        map_skill("force", "fireforce");
        map_skill("blade", "wuhu-blade");
        map_skill("parry", "wuhu-blade");
        map_skill("dodge", "lihuo-dodge");
        if( random(2) )
        	set_skill("jiuxi-fuqi",i*10);
        else	set_skill("huitian-fanri",i*10);
        
	set("force_factor",300);
	set("mana_factor",300);
        set("water", 500000);
        set("food", 500000);
	set("env/brief_message",1);
	
        set("title",HIR"拜火教"HIY"护法"NOR);
        set_temp("armor_level",30+random(5));
        set_temp("weapon_level",30+random(5));
        if( random(30)==6 )
        	set("env/test","HIM");
        else if( random(10)>1 )
		set("env/test",({"HIB","HIB","HIB","HIB","HIR",})[random(5)]);
	else	set("env/test",({"HIY","HIY","HIB","HIB","NOR",})[random(5)]);
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"blade",1)->wield();
        add_temp("apply/combat_damage",200);
        add_temp("apply/force_recover",10);
        add_temp("apply/receive_force",50);
        add_temp("apply/receive_kee",100);
        add_temp("apply/fofce_refresh",10);
        add_temp("apply/max_kee",2000);
        add_temp("apply/max_sen",2000);
        add_temp("apply/max_force",500);
        powerup(0,1);
}

void reward_ob(object who)
{
	object ob,npc,weapon;
	int i,wx,k;
	string str,file,*dir;

        if( !who || !userp(who) || !present(who,environment()) 
         || !environment()->query("mazeobj") 
         || !who->query_temp("maze/dayan"))
        {
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }

	if( !wizardp(who) && (who->query_level()>39||who->query_level()<30) )
	{
		tell_object(who,HIG"【副本】大雁塔：你在本地图得不到任何奖励。\n"NOR);
		destruct(this_object());
		return;
	}

	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
	message_vision(HIW"$N"HIW"说道：「不打了，不打了，我投降....。」\n"NOR,this_object());	

	npc = new("/d/maze/dayan-ta/npc/book");
	npc->set_name(this_object()->name(),this_object()->parse_command_id_list());
	npc->set("type","blade");
	npc->move(environment());
	
	message_vision(HIC"$N"HIC"跪地求饶：小人被猪油蒙了眼睛，勾结外贼，小的愿戴罪立功。\n"NOR,this_object());
	message_vision(CYN"$N"CYN"说道：小人在邪教多年，倒也收集了一些珍贵宝贝，今日全部献给大侠，望饶我狗命。\n"NOR,this_object());
	message_vision(CYN"$N"CYN"说道：另外小人对贼人的一些功夫技艺也有些了解，大侠如果有残卷，小人可以帮助换(huan)成秘籍。\n"NOR,this_object());

	
	i = who->query_kar()+random(who->query_per());
	if( random(i)>=25 || wizardp(who) )
	{
		dir = ({ //盔/衣/帽/鞋/披 除外
			"hand","neck","ring","shield","waist","wrists",
		});	
		k = 1+random(3);
		while(k--)
		{
			file = dir[random(sizeof(dir))];
			if( file )
			{
				ob = new("/d/obj/narmor/"+file);
				ob->set("from","【大雁塔副本】");
				ob->init_armor(this_object());
				if( !ob->move(who) )
				{
					destruct(ob);
					tell_object(who,HIR"【副本】大雁塔：你的背包满了。\n"NOR);
				}
				else	tell_object(who,HIG"【副本】大雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);
			}
		}	
	}
	if( random(i)>=30 || wizardp(who) )
	{
		if( objectp(weapon=who->query_temp("weapon")) )
			file = weapon->query("skill_type");
		else	file = "blade";	
		dir = ({
			"axe","blade","fork","hammer","mace",
			"staff","stick","blade","unarmed","whip","fork",
		});
		if( member_array(file,dir)==-1 || random(10)==1 )
			file = dir[random(sizeof(dir))];
		if( file )
		{
			ob = new("/d/obj/nweapon/"+file);
			ob->set("from","【大雁塔副本】");
			ob->init_weapon(this_object());
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】大雁塔：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】大雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);	
		}
	}
	
	i = random(4);
	if( i>0 )
	{
		while(i--)
		{
			ob = new("/d/maze/dayan-ta/obj/bangding");
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】大雁塔：你的背包满了。\n"NOR);
			}
			else	
			{
				tell_object(who,HIG"【副本】大雁塔：你得到了一块"HIY"绑定用的灵石"HIG"。\n"NOR);
				CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+"在"HIY"【大雁塔副本】"HIM"中得到了一块"HIY"绑定石"HIM"，真叫人羡慕嫉妒恨。\n"NOR);
			}
		}
	}
		
	
	destruct(this_object());
	return;
}

/*
void die()
{
       	message_vision (HIY"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
	destruct(this_object());
        return;
}

void unconcious()
{
        die();
}
*/

void init()
{
        object me = this_player();
        ::init();
        if( !this_object()->is_fighting() && userp(me) )
		this_object()->command("follow "+me->parse_command_id_list()[0]);
        add_action("do_go","go");
}               

int do_go(string arg)
{
        if( !arg || !userp(this_player()) )
                return 0;
        if( living(this_object()) 
         && (is_fighting(this_player())||!this_object()->is_fighting()) )
                return err_msg(HIY"\n"+query("name")+HIY"恶狠狠的将你拦住：想走？！先过了俺这一关！！\n"NOR);
        return 0;
}       

void kill_ob(object who)
{
	if( !who || !present(who,environment()) )
		powerup(0,1);
	if( !query_temp("powerup") )		
	{
		if( random(2) )
			command("perform dodge.huo");		
		else	command("perform dodge.lotus");
	}
	::kill_ob(who);
}	

void heart_beat()
{
        if( !environment() )  
                return;
	clean_up_enemy();
	if( !this_object()->is_fighting() )
	{
		powerup(0,1);
		return;		
	}                
	if( this_object()->is_busy() )
		add_temp("busy_time",1);
	if( query_temp("busy_time")>=2 )
	{
		this_object()->stop_busy(1000);
		delete_temp("busy_time");
	}
	::heart_beat();
}