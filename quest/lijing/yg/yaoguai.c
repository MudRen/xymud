inherit NPC;
#include <ansi.h>
#include "yaoguai_reward.c"

string _invocation(object who, int level);
int exp_reward, pot_reward;
int announced=0;

string *death_msg= ({
        HIB"\n$N"HIB"喝道：孽畜，与我回天上领罪去吧！$n"HIB"眼见无奈，只好化成股青烟附到了$N"HIB"的手中。"NOR"\n\n",
        HIB"\n$n"HIB"一看不是$N的对手，只得就地一滚，变回原形，打了几个转，老老实实地走开了。"NOR"\n\n",
        HIB"\n$n"HIB"大叫一声“我服了，我服了，我投降。。”乖乖地伏在$N"HIB"脚下不动了。$N手"HIB"一挥，$n"HIB"如蒙大赦，驯服地走开了。"NOR"\n\n",
        HIB"\n$N"HIB"喝道：孽畜，与我回天上领罪去吧！$n"HIB"无可奈何，化做一道青光，直冲云霄去了．．．"NOR"\n\n",
});

string *dirs1 = ({
        "/d/city","/d/westway","/d/kaifeng","/d/lingtai","/d/moon",
        "/d/gao","/d/sea","/d/nanhai","/d/eastway","/d/ourhome/honglou", 
        "/d/qujing/wuzhuang","/d/shushan","/d/sea","/d/jjf",
        "/d/xueshan","/d/qujing/wuzhuang","/d/qujing/baotou","/d/qujing/baoxiang", 
        "/d/qujing/bibotan","/d/qujing/biqiu","/d/qujing/chechi","/d/qujing/dudi",
        "/d/qujing/fengxian","/d/qujing/firemount","/d/qujing/jilei","/d/qujing/jindou",
        "/d/qujing/jingjiling","/d/qujing/jinping","/d/qujing/jisaiguo",
        "/d/qujing/maoying","/d/qujing/nuerguo","/d/qujing/pingding","/d/qujing/pansi",
        "/d/qujing/tongtian","/d/qujing/qilin","/d/qujing/qinfa","/d/qujing/qinglong",
        "/d/qujing/tianzhu","/d/qujing/wudidong","/d/qujing/wuji","/d/qujing/xiaoxitian",
        "/d/qujing/yinwu","/d/qujing/yuhua","/d/qujing/zhujie","/d/qujing/zhuzi",
        "/d/penglai",
        "/d/death","/d/meishan","/d/qujing/lingshan",
        "/d/pansi","/d/luoyang",
        
});

string job_type(){ return "李靖任务";}

int random_place(object me, string* dirs);
void _leave();
void leave();
void leave2();

void setname()
{
	mapping name = NAME_D->random_name("yaoguai");
	set_name(name["name"],name["id"]);
	set("gender",random(2)?"男性":"女性");
}

int cast_chance(int level) 
{
	return 5+level/3;
}

void create()
{
	setname();
	set_level(80);	
	set("chat_chance", 1+this_object()->query_level()/5);
	set("chat_msg", ({
        	(: random_move :)
	}) );
	set("chat_chance_combat",2+this_object()->query_level()/3);
	set("age", 20+random(80));
	set("attitude", "heroism");
	setup();
}

int random_move()
{
	if( this_object()->is_fighting() )
		return 0;
	return ::random_move();	
}

void set_skills(int j){ }

//me=NPC ob=owner lv=job_level
int copy_status(object me,object ob, int lv)
{
	int i, lvl,k,level,v,max_skill;
	int base = 20;
	mapping skill;
	string *skills;
	lvl = lv+base-5;

	if( !ob || !living(ob) )
		return 0;
	level = ob->query_level();
	v = 9-last_num(level);
	if( v>1 )
		level+= random(v);
	me->set_level(level);
	max_skill = level*10;
	max_skill = max_skill*4/5; 
	max_skill = max_skill*lvl/base;
	set_skills(max_skill);	
	set("bellicosity",ob->query("bellicosity")/3*2+1);	
	setup();
	powerup();
	set("force",me->query_maxforce()*2);
	set("mana",me->query_maxmana()*2);
	set("force_factor",me->query_maxforce()/20+1);
	set("mana_factor",me->query_maxmana()/20+1);
	return 1;
}

int random_place(object me, string* dirs)
{
	int i,j,k;
	object newob;
	mixed *file, exit;

	if( !sizeof(dirs) )
        	return 0;
	if( !me || !living(me) )  
		return 0;
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

void _leave()
{
	object me = this_object();
	if( me->is_fighting() || me->is_busy() )
        	return;
	leave();
}

void leave()
{
	if( this_object() ) 
        { 
        	if( environment() )
                	message("vision",HIB"\n" + name() + HIB"身子一晃，变成一股青烟散去了。\n" NOR,environment());
        	this_object()->move("/obj/empty");
        	remove_call_out("leave2");
        	call_out("leave2",5);
        }
}

void leave2()
{
	if( this_object() ) 
        	destruct(this_object());
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

string _invocation(object who, int level)
{       
	object me = this_object(), env;
	string *dirs,where,long; 
	int exp, i, p,lvl;
    
	dirs = dirs1;
	set("owner", who->query("id"));
	set("owner_ob", who);
	{
        	int dx = query("daoxing");
        	long = "一只"+query("name")[0..<3]+"，在"+({"深山中","密林中","野外","草原上","野林中","高山中","莽林中","莽原上","深谷中",})[random(9)];
        	long+= "汲取"+({"日月","天地","万物"})[random(3)]+"精华，颇有了些道行。\n";
        	set("long",long);
        	dx/= 1000;
        	if( dx>=10000 )
                	long="万年";
        	else if( dx>=1000 )
                	long="千年";
        	else if( dx>=100 )
                	long="百年";
        	else if( dx>10000 )
                	long="十年";
        	else    long="小小";
        	set("title",long);
        }
	lvl = level;
	i = random(800);
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
        	set("env/wimpy",50);
        	if( lvl<11 ) 
                	lvl=lvl+1; // as more difficult to kill.
        } 
	else    set("env/wimpy",10);

	me->set("stay_time", time()+1800);
	if( !random_place(me, dirs) ) 
        {
        	leave();
        	return 0;
        }
	exp_reward = 35000;
	exp_reward = exp_reward*(lvl+8)/10;
	exp_reward = exp_reward*9/10+random(exp_reward/10);
	pot_reward = exp_reward/(1+random(2));
        
	env = environment(me);
	where=me->query("name")+"("+capitalize(me->query("id"))+")";
	if( env )
        	where+="在"+MISC_D->find_place(env);
	return where;
}

int accept_money (object who, int v)
{
	object me;
	me = this_object();
	if( v<100000 )
        {
        	message_vision ("$N一瞪眼：就这点东西？不想活了？？？\n", me);
        	return 1;
        }
	who->set_temp("mieyao/allow_to_go", 1);
	message_vision ("$N嘿嘿嘿几声怪笑：算你走运，快滚！"+"可别让我再看见你！\n",me);
	return 1;
}

void check_room()
{
	object me=this_object();
	object env=environment(me);
	if( env && (env->query("no_fight") || env->query("no_magic")) 
	 || living(me) )
        	random_move();
}

void init()
{
	object *bianobj,me=this_object(),who=this_player(),env=environment(me);
	string type,npcid;
	int t;
	
	t = query("stay_time");
	if( t && time()>(t+3600) ) 
        {
        	remove_call_out("leave");
        	call_out("leave",1);
        	return;
        }
	if( t && time()>t ) 
        {
        	remove_call_out("_leave");
        	call_out("_leave",300);
        	return;
        }
	if( !userp(this_player()) ) 
        	return;
	if( !living(this_object()) ) 
        	return;
	::init();        	
	type = query("type");
	switch (type) 
        {
        	case "aggressive": 
                {
                	object leader=query_leader();
                	if( leader && present(leader, environment(me)) ) 
                        {
                        	if( !is_fighting() )   
                        		kill_ob(leader);
                        	break;
                        }
                        if( COMBAT_D->check_level(me,who)==1 )
                        	break;
                	set_follow(who);
                	message_vision("$N盯着$n，馋得直流口水：嘿嘿．．．\n",this_object(), who);
                	kill_ob(who);
                	break;
                }
        	case "aggressive_on_owner1":
                	if( query("owner")==this_player()->query("id") ) 
                        {
                        	if( !announced ) 
                                {
                                	message_vision("$N看见$n，大叫一声：哈哈，送上门来的肉！\n",this_object(), who);
                                	announced=1;
                                }
                        	kill_ob(this_player());
                        	if( random(4)>0 )
                                	set_follow(who);
                        	else    set_follow(0);
                        	this_player()->kill_ob(this_object());
                        }
                	break;
        	case "aggressive_on_owner":
                	if( query("owner")==this_player()->query("id") ) 
                        {
                        	if( !announced ) 
                                {
	                                message_vision("$N看见$n，大叫一声：哈哈，送上门来的肉！\n",this_object(), who);
        	                        announced = 1;
                                }
                	        kill_ob(this_player());
                        	this_player()->kill_ob(this_object());
                        }
                	break;
        	case "blocker": 
                	{
                		add_action("do_block","",1);
                		break;
                	}
        }
	remove_call_out("check_room");
	call_out("check_room",2);
}

int do_block(string arg)
{   
	object me=this_object(),who=this_player();
	string verb=query_verb();
	int t;
    
	if( wizardp(who) && !visible(who) ) 
        	return 0;
	if( me->is_fighting() ) 
        	return 0;
	if( verb!="go" && verb!="fly" 
  	&& !(environment() && environment()->query("exits/" + verb)) )
        	return 0;
	if( who->query_temp("mieyao/allow_to_go") ) 
        {
        	who->delete_temp("mieyao/allow_to_go");
        	who->delete_temp("mieyao/leave_time");
        	return 0;
        }
	t = who->query_temp("mieyao/leave_time");
	if(t>0 && time()>t) 
        {
        	who->delete_temp("mieyao/leave_time");
        	message_vision("$n乘$N一个不注意，急忙溜了过去。\n",me,who);
        	return 0;
        }
	if(t==0) 
        {
        	t=time()+30+random(90);
        	who->set_temp("mieyao/leave_time",t);
        	message_vision("$N猛地跳过来拦在$n面前，高声叫道：\n\t\t此山是我开，此树是我栽！\n\t\t要打此路过，留下买路财！\n\n",me,who);
        } 
	tell_object(who,me->name()+"一把抓住了你！\n");
	return 1;
}

void unconcious()
{
	if( query("kee")<0 || query("sen")<0 ) 
        	die();
	else ::unconcious();
}

void die()
{
	object weapon,owner_ob,me=this_object(),dropitem;
	string owner,skill,str,msg;
	int i,j,lv,exp_r, pot_r,dx_r;

	owner = query("owner");
	if( !owner || !stringp(owner) || !objectp(owner_ob=find_player(owner)) )
        {
        	msg = death_msg[random(sizeof(death_msg))];
        	msg = replace_string(msg,"$N","李靖");
        	msg = replace_string(msg,"$n","$N");
        	message_vision(msg,me);
        	destruct(this_object());
        	return;
        }       
	if( environment(owner_ob)==environment() 
  	&& living(owner_ob) && owner_ob==query_temp("last_damage_from") )
        {
		message_vision(death_msg[random(sizeof(death_msg))],owner_ob,this_object());
                exp_r = exp_reward*5;
        	pot_r = pot_reward;
		dx_r = exp_reward/4;
        } 
	else    
	{
        	message_vision("$N死了。\n",this_object());
        	exp_r=0;
        	pot_r=0;
        	dx_r=0;
        }
        lv = owner_ob->query_job_level(job_type());
	QUEST_D->job_reward_player(owner_ob,"combat_exp",exp_r,job_type());
	QUEST_D->job_reward_player(owner_ob,"daoxing",pot_r,job_type());
	QUEST_D->job_reward_player(owner_ob,"potential",dx_r,job_type());
	tell_object(owner_ob,HIY+owner_ob->finish_job(job_type(),({exp_r,dx_r,pot_r}))+NOR);
	str=" got "+exp_r+"/"+exp_reward+" exp "+pot_r+"/"+pot_reward+" pot "+" dx "+dx_r+" in level "+ lv+".\n";
	if( lv==9 && exp_r>0 ) 
        {
        	skill = give_reward(owner_ob);
        	str+= "and rewarded 1 lvl of "+skill+".\n";
        	if( skill!="none" )
                {
                	msg = "听说"+ owner_ob->query("name")+ HIM"的"HIC+ to_chinese(skill)+ HIM"又有所进境了！\n"NOR;
                	CHANNEL_D->do_channel(me,"rumor",msg);
                }
        }
        if( lv==10 && exp_r>0 ) 
        {
        	owner_ob->add_temp("mark/lijing_job",1);
        	tell_object(owner_ob,HIY"【系统】李靖任务：恭喜，你已经完成了 "HIR+chinese_number(owner_ob->query_temp("mark/lijing_job"))+" 轮李靖任务。"NOR"\n");
        	if( owner_ob->query_level()==109 && random(owner_ob->query_temp("mark/lijing_job"))>30 )
        	{
        		tell_object(owner_ob,HIY"恭喜，你苦战这么久，一直停滞不前的境界好似有了突破的迹象！\n你升级了！\n"NOR);
        		owner_ob->level_up();
        		owner_ob->delete_temp("mark/lijing_job");
        	}
        	if( owner_ob->query_level()==119 && random(owner_ob->query_temp("mark/lijing_job"))>50 )
        	{
        		tell_object(owner_ob,HIY"恭喜，你苦战这么久，一直停滞不前的境界好似有了突破的迹象！\n你升级了！\n"NOR);
        		owner_ob->level_up();
        		owner_ob->delete_temp("mark/lijing_job");
        	}
	}        	
        if( exp_r>0 )
        {
		owner_ob->money_add(8000);
		tell_object(owner_ob,HIY"【系统】李靖任务：你得到了八十两白银的奖励。"NOR"\n");
	}
	destruct(this_object());
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
	int mx;
	if( damage<=0 )
		damage = 0;
	if( !who || who==this_object() )
		return ::receive_wound(type,damage,who,attack_type);
	if( !userp(who) )
	{
		if(objectp(who->query_temp("invoker")))
			who = who->query_temp("invoker");
	}
	if( who!=query("owner_ob") )
		return ::receive_wound(type,damage,who,attack_type);
	if( COMBAT_D->family_restrain(this_object(),who)==-1 )
		return ::receive_wound(type,damage,who,attack_type);
	switch(type)
	{
		case "kee" : mx = this_object()->query_maxkee();break;
		default : mx = this_object()->query_maxsen();break;
	}	
	if( damage>mx/15 )
		damage = mx/15;
	return ::receive_wound(type,damage,who,attack_type);				
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
	int mx;
	if( damage<=0 )
		damage = 0;
	if( !who || who==this_object() )
		return ::receive_damage(type,damage,who,attack_type);
	if( !userp(who) )
	{
		if(objectp(who->query_temp("invoker")))
			who = who->query_temp("invoker");
	}
	if( who!=query("owner_ob") )
		return ::receive_damage(type,damage,who,attack_type);
	if( COMBAT_D->family_restrain(this_object(),who)==-1 )
		return ::receive_damage(type,damage,who,attack_type);
	switch(type)
	{
		case "kee" : mx = this_object()->query_maxkee();break;
		default : mx = this_object()->query_maxsen();break;
	}	
	if( damage>mx/10 )
		damage = mx/10;
	return ::receive_damage(type,damage,who,attack_type);				
}

