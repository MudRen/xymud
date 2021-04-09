inherit __DIR__"n.c";

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("male");
	if( !names )
		set_name("武僧",({"wu seng","seng","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({"shi "+id,id,"seng","shi","di zi"});
		else
			ids = ({"shi","seng","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = "释"+name;
		set_name(name,ids);
	}	
	set("my_master","guanyin pusa");
	create_family("南海普陀山",2+random(3), "行者");
	set("chushi/chushi_putuo","yes");        
	set("class", "bonze");

set_skill("jienan-zhi", 550+random(50));
set_skill("lotusmove", 550+random(50));
set_skill("staff", 550+random(50));
set_skill("lunhui-zhang", 550+random(50));
set_skill("lotusforce", 550+random(50));
set_skill("literate", 800);
set_skill("buddhism", 550+random(50));
set_skill("blade", 550+random(50));
set_skill("cibeidao", 550+random(50));
set_skill("dodge", 550+random(50));
set_skill("force", 550+random(50));
set_skill("spells", 550+random(50));
set_skill("parry", 550+random(50));

map_skill("blade","cibeidao");
map_skill("spells", "buddhism");
map_skill("force", "lotusforce");
map_skill("unarmed", "jienan-zhi");
map_skill("staff", "lunhui-zhang");
map_skill("parry", "lunhui-zhang");
map_skill("dodge", "lotusmove");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",21600000);
	set("daoxing",21600000);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","cibeidao");
	}
	else
	{
		carry_object(0,"staff",1)->wield();
		map_skill("parry","lunhui-zhang");
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
		command("cast yinshen");
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("anti_magic") )
		command("cast lianhua");
	if( !this_object()->is_yinshen() )
		command("cast yinshen");
					
	QUEST_D->randomPfm(this_object());	
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

void heart_beat()
{
	object me = this_object();
	if( me->query("force")>100 && me->is_fighting() )
	{
     	if( query("eff_kee") < query("max_kee") )
        	QUEST_D->addEffKee(me);
        if( query("kee") < query("eff_kee") )
        	QUEST_D->addKee(me);
        if( query("sen") < query("eff_sen") )
        	QUEST_D->addSen(me);
        if( query("eff_sen") < query("max_sen") )
        	QUEST_D->addEffSen(me);
        me->stop_busy();
        QUEST_D->randomPfm(this_object());		
	}
	::heart_beat();
}
