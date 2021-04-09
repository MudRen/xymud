inherit __DIR__"n.c";

string *names = ({
        "风","虚","清","华","子","德",
        "道","李","庄","扬",
});

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("male");
	if( !names )
		set_name("弟子",({"dizi","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({"zhuang "+id,id,"zhuang","dizi","di zi"});
		else
			ids = ({"zhuang","dizi","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = "庄"+name;
		set_name(name,ids);
	}	
	set("my_master","master puti");
	set("age", 16+random(20));
	set("class", "taoist");
	set("per", 26);
	set("long", "方寸弟子。\n");

set_skill("literate", 550+random(70)); 
set_skill("unarmed", 550+random(70));
set_skill("dodge", 550+random(70));
set_skill("force", 550+random(70));
set_skill("parry", 550+random(70));
set_skill("stick", 550+random(70));
set_skill("spells", 550+random(70));
set_skill("whip", 550+random(70));
set_skill("dao", 550+random(70));
set_skill("puti-zhi", 550+random(70));
set_skill("wuxiangforce", 550+random(70));
set_skill("qianjun-bang", 550+random(70));
set_skill("jindouyun", 550+random(70));
set_skill("liangyi-sword", 550+random(70));
map_skill("spells", "dao");
map_skill("unarmed", "puti-zhi");
map_skill("force", "wuxiangforce");
map_skill("stick", "qianjun-bang");
map_skill("parry", "qianjun-bang");
map_skill("dodge", "jindouyun");
map_skill("sword", "liangyi-sword");
create_family("方寸山三星洞", 2+random(3), "弟子");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",10800000);
	set("daoxing",10800000);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","liangyi-sword");
		set("gender","女性");
		set("skillmark/liangyi-sword","yes");
	}
	else
	{
		carry_object(0,"stick",1)->wield();
		map_skill("parry","qianjun-bang");
		if( random(2) )
			set("fangcun/panlong_accept","done");
	}
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object *inv,weapon;
	string msg,*msgs;
	int d,i,k;
	remove_call_out("tiaozhan_hit");
	this_object()->stop_busy();	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("jldl") )
		command("exert jldl");
	if( !query_temp("powerup") )
		command("exert shenjia");
	weapon = query_temp("weapon");
	if( !weapon || weapon->query("skill_type")!="sword" )
		QUEST_D->randomPfm(this_object());	
	else
	{
		command("perform sanhuan");
		command("perform yin");
	}	
	call_out("tiaozhan_hit",4,who);
}

void help_kill(object who)
{
        int i,f=0;
        object *inv,npc;
        if( !who )      return;
        inv = all_inventory(environment());
        for(i=0;i<sizeof(inv);i++)
        {
                npc = inv[random(sizeof(inv))]; 
                if( npc && living(npc) && !userp(npc) //玩家或昏迷的
                 && !npc->is_fighting(who)                   //在战斗的
                 && npc!=this_object()                    //..
                 && f< 1
                 && npc->query("my_master") )
                {
                        say( sprintf("%s在旁说道：%s道友，休要惊慌，我来助你一臂之力。\n",npc->name(),this_object()->name(1)[0..1]));
                        npc->set_temp("help_kill",1);
                        npc->kill_ob(who);
                        npc->set_temp("help_kill",0);
                        f++;
                }
        }
        return;       
}

void kill_ob(object who)
{
        if( who && present(who,environment()) && userp(who)
         && !this_object()->is_fighting()
         && !query_temp("help_kill") )
        {       
                powerup(1);
                help_kill(who);
        }       
        ::kill_ob(who);
}

