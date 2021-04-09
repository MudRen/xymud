#include <ansi.h>;
inherit NPC;

string job_type(){ return "袁天罡任务";}

string *dirs = ({
        "/d/city","/d/westway","/d/kaifeng","/d/lingtai","/d/moon",
        "/d/gao","/d/sea","/d/nanhai","/d/eastway","/d/ourhome/honglou", 
        "/d/qujing/wuzhuang","/d/shushan","/d/sea","/d/jjf",
        
});

void set_skills(int j, int level){}

int other_kee=0, other_sen=0;
int exp_reward = 0, pot_reward = 0;

void create()
{
	mapping name;
	if( random(2) )
	{
		name = NAME_D->random_name("male");
		set("gender","男性");
	}
	else
	{
		name = NAME_D->random_name("female");
		set("gender","女性");
	}
	set_name(name["name"],name["id"]);
	set("age",18+random(30));
	set("chat_chance_combat",2+this_object()->query("level")/3);
	set("class", "yao");
	set("attitude", "heroism");
	set_temp("weapon_level",1+random(10));
	set_temp("armor_level",1+random(10));
	setup();
}

void leave()
{
	if(this_object()) 
      	{ 
      		if(environment())
          		message("vision",CYN + name() + CYN"鬼鬼祟祟的朝后看了一眼，嘿嘿一笑，窜了几窜就不见了。\n" NOR,environment());
        	destruct(this_object());
      	}
}

int random_place()
{
	int i,j,k;
	object me,newob;
	mixed *file, exit;

	if( !sizeof(dirs) )
        	return 0;
        me=this_object();	
	i = random(sizeof(dirs));    // pick up one directory
	file = get_dir( dirs[i]+"/*.c", -1 );
	if( !sizeof(file) )
        	return 0;
	for(k=0;k<60;k++)  // try 20 times
        {
        	j = random(sizeof(file));
        	if( file[j][1]>0 ) 
                {
                	newob=load_object(dirs[i]+"/"+file[j][0]);
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

//me=NPC ob=owner lv=job_level
int copy_status(object me,object ob, int lv)
{
	int i, lvl,k,level,v,dx,max_skill;
	int base = 10;
	mapping skill;
	string *skills;
	lvl = lv+base-8;

	if( !ob || !living(ob) )
		return 0;
	level = ob->query_level();
	v = 9-last_num(level);
	if( v>1 )
		level+= random(v)-random(5);
	me->set_level(level);
	dx = me->query_max_daoxing();
	dx = dx/2+random(dx/2);
	max_skill = QUEST_D->maxSkill(ob);
	if( max_skill<=0 )
		return 0;
	max_skill = max_skill*lvl/base;
	if( max_skill>level*10 )
		max_skill = level*10;
	set_skills(max_skill, lv);	
	skill = me->query_skills();
	if( !skill || !mapp(skill) )
		return 0;	
	skills = keys(skill);
	if( !skills || !arrayp(skills) || sizeof(skills)<1 )
		return 0;
	for(i=0;i<sizeof(skills);i++)
		me->set_skill(skills[i],max_skill);
	set("bellicosity",ob->query("bellicosity")/3*2+1);	
	setup();
	powerup(0,1);
	if( query("family/family_name")!="月宫" )
		set("force_factor",me->query_maxforce()/35+1);
	set("mana_factor",me->query_maxmana()/35+1);
	return 1;
}

string _invocation(object who, int level)
{       
	object me = this_object(), env;
	string where,long; 
	int exp, i, p,lvl;
    
	set("owner", who->query("id"));
	set("owner_ob", who);
	if( me->query("class")=="yaomo" )
        {
        	long = "一位修魔的散人，修练了有"+chinese_number((query("daoxing")/1000/10)*10)+"多年道行。他";
        	set("long",long+"混身上下妖气逼人。\n");
        }
        else
        {
        	long = "一位修仙的散人，虽也在名家仙山修练了有"+chinese_number((query("daoxing")/1000/10)*10)+"多年道行。但他";
        	set("long",long+"混身上下煞气逼人。\n");
        }
	lvl = level;
	if( lvl<1 ) lvl = 1;
	i = random(1000);
	if( i<10 ) 
        	set("type","aggressive");
	else if( i<20 )
        	set("type","blocker");
	else if(i<220)
        	set("type","aggressive_on_owner");
	else if(i<320)
        	set("type","aggressive_on_owner1");
	else    set("type","normal");
	if( random(10)==0 ) 
        {
        	if( lvl<11 ) 
                	lvl=lvl+1; // as more difficult to kill.
        } 
        exp_reward = 2000;
	exp_reward = exp_reward*(lvl+8)/10;
	exp_reward = exp_reward*9/10+random(exp_reward/10);
	pot_reward = exp_reward/(3+random(2))+1;
	me->set("stay_time", time());
	if( !random_place() ) 
        {
        	leave();
        	return 0;
        }
	env = environment(me);
	where=me->query("name")+"("+capitalize(me->query("id"))+")";
	if( env )
        	where+="在"+MISC_D->find_place(env);
	return where;
}

string invocation(object who, int level)
{
	object me = this_object();
	if( !who )  
		return 0;
	if( !copy_status(me,who, level) )
	{
		leave();
		return 0;
	}
	return _invocation(who, level);
}

int accept_object (object who, object ob){return 1;}

void die()
{
        string owner;
        object owner_ob;
        object me=this_object();
        string str;
	object silver;
        int max_kee, max_sen, ratio, exp_r, pot_r,dx_r;

	message_vision("\n$N惨叫一声，吐了几口"RED"鲜血"NOR"，狠毒的朝四周看了一眼，一蹬腿死了。\n",this_object());
        owner = query("owner");
	if( owner && stringp(owner) && objectp(owner_ob = find_player(owner)) ) 
	{
        	if(environment(owner_ob)==environment())
        	{
        		max_kee = me->query_maxkee();
        		max_sen = me->query_maxsen();
        		ratio=100*(max_kee-other_kee)/max_kee;
        		if(ratio<0)    ratio=0;
        		ratio = ratio*(max_sen-other_sen)/max_sen;
        		if(ratio<0) ratio=0;
                        exp_r = exp_reward;
        		pot_r = pot_reward;
			dx_r = exp_reward*4/5+random(exp_reward/5);
                	
			QUEST_D->job_reward_player(owner_ob,"combat_exp",exp_r,job_type());
			QUEST_D->job_reward_player(owner_ob,"daoxing",pot_r,job_type());
			QUEST_D->job_reward_player(owner_ob,"potential",dx_r,job_type());
			tell_object(owner_ob,HIY+owner_ob->finish_job(job_type(),({exp_r,dx_r,pot_r}))+NOR);
                    	owner_ob->money_add(2000);
                    	tell_object(owner_ob,"你得到了二十两白银的奖励。\n");
		}
	}
        destruct(this_object());
}

varargs int receive_wound(string type, int damage, object who)
{
	string owner=query("owner");
	object inv;
    
	if( owner && who && who->query("id")!=owner ) 
        {
        	if( userp(who) || ((inv=who->query_temp("invoker")) && inv->query("id")!=owner)) 
                {
                	if( damage>0 )  
                        {
                        	switch(type) 
                                {
                                	case "kee": other_kee+=damage; break;
                                	case "sen": other_sen+=damage; break;
                                        default : return 0;
                                }
                        }
                }
        }
	return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
	string owner = query("owner");
	object inv;
    
	if( owner && who && who->query("id")!=owner ) 
        {
        	if( userp(who) || ((inv=who->query_temp("invoker")) && inv->query("id")!=owner) ) 
                {
                	if( damage>0 ) 
                        {
                        	switch(type) 
                                {
                                	case "kee": other_kee+=damage; break;
                                	case "sen": other_sen+=damage; break;
                                }
                        }
                }
        }
	return ::receive_damage(type, damage, who);
}

void init()
{
	object ob = this_object();
	if( ob->is_fighting() )
		return;
	if( time()>query("stay_time")+600 )
	{
		leave();
		return;
	}	
	if( environment()->query("no_fight")
	 || environment()->query("no_magic") )
	{
		random_move();
		return;
	}
	::init();
}	 	
