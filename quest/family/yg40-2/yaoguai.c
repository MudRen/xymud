//噩梦
#include <ansi.h>;
inherit SUPER_NPC;

string job_type(){ return "门派任务";}

string *dirs = ({
        //门派路径
        "/d/baihuagu","/d/jjf","/d/lingtai","/d/moon","/d/nanhai","/d/pansi","/d/sea",
        "/d/shushan","/d/xueshan","/d/qujing/wuzhuang","/d/qujing/wudidong","/d/qujing/kusong",
        //城市
        "/d/ourhome/honglou","/d/aolai","/d/changan","/d/city","/d/eastway","/d/gao",
        "/d/jz","/d/kaifeng","/d/luoyang","/d/meishan","/d/penglai","/d/westway",
        //取经路
        "/d/qujing/baotou","/d/qujing/baoxiang","/d/qujing/bibotan",
        "/d/qujing/biqiu","/d/qujing/chechi","/d/qujing/dudi","/d/qujing/fengxian",
        "/d/qujing/jilei","/d/qujing/jindou","/d/qujing/jingjiling","/d/qujing/jinping",
        "/d/qujing/jisaiguo","/d/qujing/kusong","/d/qujing/maoying","/d/qujing/nuerguo",
        "/d/qujing/pansi","/d/qujing/pingding","/d/qujing/qilin","/d/qujing/qinfa","/d/qujing/qinglong",
        "/d/qujing/tianzhu","/d/qujing/tongtian",
        "/d/qujing/wuji","/d/qujing/wuzhuang","/d/qujing/xiaoxitian","/d/qujing/yinwu","/d/qujing/yuhua",
        "/d/qujing/zhujie","/d/qujing/zhuzi",
});


string *death_msg= ({
        HIW"\n$n"HIW"大叫一声“这次是你赢了，下次我们走着瞧。。。”\n"NOR REV HIG"$n"REV HIG"说完，化做一道青光，直冲云霄去了．．．\n"NOR,
        HIW"\n$N"HIW"喝道：那里走！\n"NOR REV HIW"$n"REV HIW"无可奈何，往地下一钻，就消失了。\n"NOR,
        HIW"\n$N"HIW"念动咒语，搬来附加万钧高山，将$n"HIW"镇于山下。\n"NOR REV HIW"轰鸣声中，$n"REV HIW"犹不甘的叫着“此事未了，你我山水有相逢。。。”\n"NOR,
});

void set_skills(int j, int level){}

int other_kee=0, other_sen=0;
int exp_reward = 0, pot_reward = 0;

void create()
{
	mapping name;
	if( random(2) )
	{
		name = NAME_D->random_name2(0, -1, 0, 0, 0);
		set("gender","男性");
	}
	else
	{
		name = NAME_D->random_name2(1, -1, 0, 0, 0);
		set("gender","女性");
	}
	set_name(name["name"],name["id"]);
	set("age",18+random(30));
	set("age", 20+random(80));
	set("class", "yaomo");
	set("combat_exp", 3000);
	set("attitude", "heroism");
	setup();
}

void leave()
{
	if(this_object()) 
      	{ 
      		if(environment())
          		message("vision",name() + "急急忙忙的离开了。\n",environment());
        	destruct(this_object());
      	}
}

int random_place()
{
	int i,j,k;
	object me,newob;
	mixed *file,exit;

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
	dx = dx*4/5+random(dx/5);
	max_skill = level*10;
	max_skill = max_skill*59/60+random(max_skill/60);
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
	set("force_factor",me->query_maxforce()/30+1);
	set("mana_factor",me->query_maxmana()/30+1);
	delete("env/wimpy");
	add_temp("apply/max_kee",me->query_maxkee()*3/2);
	add_temp("apply/max_sen",me->query_maxsen()*3/2);
	add_temp("apply/combat_def",1000);
	add_temp("apply/spells_def",1000);
	add_temp("apply/combat_damage",1000);
	add_temp("apply/spells_damage",1000);
	add_temp("apply/receive_force",10);
       	add_temp("apply/receive_mana",10);
       	add_temp("apply/receive_kee",20);
       	add_temp("apply/receive_sen",30);
       	add_temp("apply/re_spells_effdamage",5);
	add_temp("apply/re_combat_effdamage",5);
       	add_temp("apply/attack",5);
       	add_temp("apply/defense",5);
       	add_temp("apply/spells_succ",5);
       	add_temp("apply/spells_dodge",5);
       	add_temp("apply/combat_succ",5);
       	add_temp("apply/combat_dodge",5);
       	add_temp("apply/combat_parry",5);
       	add_temp("apply/force_recover",5);
       	add_temp("apply/fofce_refresh",5);
       	add_temp("apply/receive_heal_kee",5);
	add_temp("apply/receive_heal_sen",5);
	add_temp("apply/receive_curing_kee",5);
       	add_temp("apply/receive_curing_sen",5);
       	add_temp("apply/receive_exercise",5);
	add_temp("apply/receive_meditate",5);
	add_temp("apply/re_spells_damage",5);
	add_temp("apply/re_combat_damage",5);	
	powerup(0,1);	
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
        	long = "一位修练了有"+chinese_number((query("daoxing")/1000/10)*10)+"多年道行的妖族，他";
        	set("long",long+"混身上下妖气逼人。\n");
        }
        else
        {
        	long = "出身名家仙山的修道者，修练了有"+chinese_number((query("daoxing")/1000/10)*10)+"多年道行。但他";
        	set("long",long+"通体透出一丝仙气。\n");
        }
	lvl = level;
	if( lvl<1 ) lvl = 1;
       	set("type","aggressive_on_owner");
	if( random(10)==0 ) 
        {
        	if( lvl<11 ) 
                	lvl=lvl+1; // as more difficult to kill.
        } 
	exp_reward = 12000;
	exp_reward = exp_reward*(lvl+8)/10;
	exp_reward = exp_reward*9/10+random(exp_reward/10);
	pot_reward = exp_reward/(8+random(12));
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
	set("force",this_object()->query_maxforce()*2);
	set("mana",this_object()->query_maxmana()*2);		
	return _invocation(who, level);
}

int accept_object (object who, object ob){return 1;}

void die()
{
        object owner_ob;
        object me=this_object();
        string str;
	object silver;
        int lvl,max_kee, max_sen, ratio, exp_r, pot_r,dx_r;

        owner_ob = query("owner_ob");
	if( owner_ob )
	{
		revive();
		message_vision(death_msg[random(sizeof(death_msg))],owner_ob,this_object());
        	max_kee = me->query_maxkee();
		max_sen = me->query_maxsen();
        	ratio=100*(max_kee-other_kee)/max_kee;
        	if(ratio<0)    ratio=0;
        	ratio = ratio*(max_sen-other_sen)/max_sen;
        	if(ratio<0) ratio=0;
                exp_r = exp_reward;
        	pot_r = pot_reward*3;
		dx_r = exp_reward/10+random(exp_reward/15);
                if( exp_r<=0 )
			exp_r = pot_r = dx_r = 0;	
		QUEST_D->job_reward_player(owner_ob,"combat_exp",exp_r,job_type());
		QUEST_D->job_reward_player(owner_ob,"daoxing",dx_r,job_type());
		QUEST_D->job_reward_player(owner_ob,"potential",pot_r,job_type());
		if( exp_r>0 )
		{
			tell_object(owner_ob,HIY+owner_ob->finish_job(job_type(),({exp_r,dx_r,pot_r}))+NOR);
			lvl = owner_ob->query_job_level("门派任务");
			lvl+= 1;
			lvl*= 15;
			owner_ob->add("faith",lvl);
			tell_object(owner_ob,HIY"【师门】你得到了"+lvl+"点门派贡献。\n"NOR);
			lvl = owner_ob->query_job_level("门派任务");
			tell_object(owner_ob,HIY"【噩梦】本轮已经完成 "HIR+lvl+"/10"HIY"个，已完成"HIR+owner_ob->query_temp("mark/evil_family")+HIY"轮。\n"NOR);                    		
                    	if( lvl==10 )
                    	{
                    		tell_object(owner_ob,HIY"恭喜！你完成了一轮噩梦级别的门派任务。\n"NOR);
                    		owner_ob->add_temp("mark/evil_family",1);
                    		owner_ob->add("faith",100);
                    		tell_object(owner_ob,HIY"你得到了100点门派贡献的追加奖励。\n"NOR);
                    	}
		}
	}
	else	message_vision("$N急急忙忙的离开了。\n",this_object());
        destruct(this_object());
}

varargs int receive_wound(string type, int damage, object who)
{
	string owner=query("owner");
	int v;
        if( who && who!=this_object() )
        {
        	if( who->query("family/family_name")=="东海龙宫" )
        		v = 10;
        	else	v = 2;	
		if( type=="kee" )
                {	
                	if( damage>this_object()->query_maxkee()/v )
                		damage = this_object()->query_maxkee()/v;
                }		
		if( type=="sen" )
		{
                	if( damage>this_object()->query_maxsen()/v )
                		damage = this_object()->query_maxsen()/v;
		}
        }
    
	if( who && who!=this_object() )
	{
		if(objectp(who->query_temp("invoker")))
			who = who->query_temp("invoker");
		if( who!=query("owner_ob") )
		{
			switch(type) 
			{
                        	case "kee": other_kee+=damage; break;
                                case "sen": other_sen+=damage; break;
                        }		
		}
	}
	return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
	string owner = query("owner");
	int v;
        if( who && who!=this_object() )
        {
        	if( who->query("family/family_name")=="东海龙宫" )
        		v = 20;
        	else	v = 5;	
		if( type=="kee" )
                {	
                	if( damage>this_object()->query_maxkee()/v )
                		damage = this_object()->query_maxkee()/v;
                }		
		if( type=="sen" )
		{
                	if( damage>this_object()->query_maxsen()/v )
                		damage = this_object()->query_maxsen()/v;
		}
        }
    
	if( who && who!=this_object() )
	{
		if(objectp(who->query_temp("invoker")))
			who = who->query_temp("invoker");
		if( who!=query("owner_ob") )
		{
			switch(type) 
			{
                        	case "kee": other_kee+=damage; break;
                                case "sen": other_sen+=damage; break;
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

varargs void full_me(int v)
{
	powerup(0,0);
	if( v )
		this_object()->clear_condition();
	set("force",this_object()->query_maxforce()*2);
	set("mana",this_object()->query_maxmana()*2);		
}
