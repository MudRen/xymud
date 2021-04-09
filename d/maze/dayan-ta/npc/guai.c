//迷宫怪物
#include <ansi.h> 
inherit SUPER_NPC;
 
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
        i = 30+random(10);
        set_level(i);
        set_skill("unarmed",i*10);
        set_skill("wudu-shenzhang",i*10);
        set_skill("dodge",i*10);
        set_skill("lihuo-dodge",i*10);
        set_skill("force",i*10);
        set_skill("fireforce",i*10);
        set_skill("parry",i*10);
        set_skill("spells",i*10);
        set_skill("sword",i*10);
        set_skill("blade",i*10);
        set_skill("spear",i*10);
        
        set_skill("dengxian-dafa",i*10);
        map_skill("spells", "dengxian-dafa");
        map_skill("force", "fireforce");
        map_skill("dodge", "lihuo-dodge");
	map_skill("unarmed", "wudu-shenzhang");        

	set("force_factor",i*5);

        set("water", 200000);
        set("food", 200000);
	
	ns = ({YEL"三花堂供奉"NOR,RED"拜火教徒"NOR,WHT"西域胡人"NOR,});
        set("title",ns[random(sizeof(ns))]);
        set_temp("armor_level",i);
        set_temp("weapon_level",i);
        if( random(i)==10 )
        	set("env/test","HIB");
        else if( random(i)>15 )
        	set("env/test",({"HIB","HIY",})[random(2)]);
        else	set("env/test",({"NOR","NOR","HIB","HIY",})[random(4)]);
        setup();
	if( random(2) )
	{
		set_skill("wuhu-blade",i*10);	
        	map_skill("blade", "wuhu-blade");
        	map_skill("parry", "wuhu-blade");
        	carry_object(0,"blade",1)->wield();
	}	
	else if( random(2) )
	{
		set_skill("shenghuo-spear",i*10);	
        	map_skill("spear", "shenghuo-spear");
        	map_skill("parry", "shenghuo-spear");
		carry_object(0,"spear",1)->wield();
	}
	else if( random(2) )
	{
		set_skill("lieyang-jian",i*10);	
        	map_skill("sword", "lieyang-jian");
        	map_skill("parry", "lieyang-jian");
		carry_object(0,"sword",1)->wield();
	}
	else	
	{
		map_skill("parry", "wudu-shenzhang");
		carry_object(0,"unarmed",1)->wield();
	}        
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        set("max_kee",2000);
        set("max_sen",2000);
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
	mapping jg;
	string str,file,*dir,data,name,*ks,answer,*ans;

        if( !who || !userp(who) || !present(who,environment()) 
         || !environment()->query("mazeobj") 
         || !who->query_temp("maze/dayan"))
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
	if( !wizardp(who) && (who->query_level()>39||who->query_level()<30) )
	{
		tell_object(who,HIG"【副本】大雁塔：你在本地图得不到任何奖励。\n"NOR);
		destruct(this_object());
		return;
	}
	if( query("no_obj") )
	{
		destruct(this_object());
		return;
	}		

	dir = ({
		"sword","blade","spear","dodge","unarmed",
	});	
	file = dir[random(sizeof(dir))];
	if( file )
	{
		ob = new("/d/maze/dayan-ta/book/"+file+"_0");
		if( !ob->move(who) )
		{
			destruct(ob);
			tell_object(who,HIR"【副本】大雁塔：你的背包满了。\n"NOR);
		}
		else	tell_object(who,HIG"【副本】大雁塔：你得到了 "+ob->name()+HIG" 。\n"NOR);
	}

	if( random(3)==0 )
	{
		xin = new("/d/maze/dayan-ta/obj/xin");
		jg = ([
			"黄铜" : "ht_key",
			"青铜" : "qt_key",
			"钨铜" : "wt_key",
			"黑铁" : "htie_key",
			"钨钢" : "wg_key",
		]);
		ks = keys(jg);
		name = ks[random(sizeof(ks))];
		data = jg[name];
		ans = ({
			who->query_temp("maze/"+data+"1"),
			who->query_temp("maze/"+data+"2"),
			who->query_temp("maze/"+data+"3"),
			who->query_temp("maze/"+data+"4"),
		});
		answer = ans[random(sizeof(ans))];
		str = "";
		for(i=0;i<sizeof(ans);i++)
		{
			if( ans[i]==answer )
				str+= ans[i];
			else	str+= REV+({HIW,WHT,HIR,HIY,HIM,YEL,HIC,HIG,HIB,})[random(9)]+"  "NOR;
			if( i<sizeof(ans)-1)
				str+= "、";	
		}
		str = "今日得头目密信，"+name+"锁的开关密码是：\n"+str+"\n";
		xin->set("long",str);
		if( !xin->move(who) )
		{
			destruct(xin);
			tell_object(who,HIR"【副本】大雁塔：你的背包满了。\n"NOR);
		}
		else	tell_object(who,HIG"【副本】大雁塔：你得到了 一封"HIR"密信"HIG" 。\n"NOR);
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
        ::init();
        if( !this_object()->is_fighting() && userp(me) )
        {
		command("follow "+me->parse_command_id_list()[0]);
		command("kill "+me->parse_command_id_list()[0]);
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

int accept_fight(){return 0;}

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
	if( query_temp("busy_time")>=5 )
	{
		this_object()->stop_busy(1000);
		delete_temp("busy_time");
	}
	::heart_beat();
}