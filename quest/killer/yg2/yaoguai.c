#include <ansi.h>;
inherit NPC;

string job_type(){ return "杀手任务";}

string *dirs1 = ({
        "/d/city","/d/westway","/d/kaifeng","/d/lingtai","/d/moon",
        "/d/gao","/d/sea","/d/nanhai","/d/eastway","/d/ourhome/honglou", 
        "/d/qujing/wuzhuang","/d/shushan","/d/sea","/d/jjf","/d/meishan",
        "/d/xueshan","/d/pansi"
});

string *dirs2 = ({
        //门派路径
        "/d/baihuagu","/d/jjf","/d/lingtai","/d/moon","/d/nanhai","/d/pansi","/d/sea",
        "/d/shushan","/d/xueshan","/d/qujing/wuzhuang","/d/qujing/wudidong","/d/qujing/kusong",
        //城市
        "/d/ourhome/honglou","/d/aolai","/d/changan","/d/city","/d/eastway","/d/gao",
        "/d/jz","/d/kaifeng","/d/luoyang","/d/meishan","/d/penglai","/d/westway",
        //取经路
        "/d/qujing/firemount","/d/qujing/baotou","/d/qujing/baoxiang","/d/qujing/bibotan",
        "/d/qujing/biqiu","/d/qujing/chechi","/d/qujing/dudi","/d/qujing/fengxian",
        "/d/qujing/jilei","/d/qujing/jindou","/d/qujing/jingjiling","/d/qujing/jinping",
        "/d/qujing/jisaiguo","/d/qujing/kusong","/d/qujing/maoying","/d/qujing/nuerguo",
        "/d/qujing/pansi","/d/qujing/pingding","/d/qujing/qilin","/d/qujing/qinfa","/d/qujing/qinglong",
        "/d/qujing/tianzhu","/d/qujing/tongtian","/d/qujing/wudidong",
        "/d/qujing/wuji","/d/qujing/wuzhuang","/d/qujing/xiaoxitian","/d/qujing/yinwu","/d/qujing/yuhua",
        "/d/qujing/zhujie","/d/qujing/zhuzi",
});
void set_skills(int j, int level){}

string *death_msg= ({
        "只见$N口中念动有词，忽然双臂一振，空中雷轰电掣黑雾漫漫，但见电光飞闪$N随之消失…… \n",
        "$N撮唇吹了一个响哨，一匹神骏的宝马随声而至，$N纵身上马，绝尘而去…… \n",
        "$N往黑暗处一指，只见所指之处仿佛出现一扇门，$N大步走入，门也随之消失…… \n",
        "$N捻个口诀，口中念动真言，只见祥光万道，白雾紫气，红云腾腾而起,$N纵身跃上，飞驰而去......\n",
        "$N妩媚一笑，欣然起舞，随着一阵花香，已消失在月光中……\n",
        "$N伸手一招，一朵莲花平地而起,$N坐上莲台，转眼而去……\n",
        "$N把口一张，吐出一道七色神光，笼罩其身，但见霞光一闪,$N化作一道彩虹消失的无影无踪……\n",
        "$N大袖一摆，平地起身，只见风起云涌，$N在空中连踏出乾坤八位，几步踏出，身形已然消失……\n",
        "$N随手一挥，阴风簇拥，一派寒雾笼罩真身，旋转而去…… \n",
        "$N口中念着佛号，脚下升起一朵莲花宝座，缓缓离地飞去……  \n",
        "$N口摇身一变，现出原形，正是一条神龙，随即穿云而去…… \n",
        "$N口捻个口诀，口中念动真言,突然“轰”地冒起一团红雾,$N随即隐入红雾中。\n",
        "只见万道霞光散过,$N踏着七朵彩云腾空而去……\n",
        "$N口捻个口诀，扔出一把宝剑，$N飞驰而上，一招「御剑飞行」向远方飞去。。。。\n",
        "只见$N手指一扬，纷纷花瓣有如花雨落下，$N的身形也渐渐消失在花雨中.....\n",
        "$N念了几声咒语，周围冒起一团团火焰，火焰一闪，$N消失在火光之中。\n",
	"$N手一指，招来一道彩虹，小心翼翼的爬了上去。\n",
});

string *kill_shout = ({ 
        "既然你知道了，那可更不能留这个活口了。",
        "你自己找来，倒也省了大爷一番功夫，认命吧！",
        "好，既然你穷追不舍，那就别怪大爷我不客气了！",
        "想杀我？你差的远哪！",
        "不知死活的东西，你道大爷我怕了你不成？",
        "既然如此，那你就准备明年的今天吃蜡烛吧！", 
});

int exp_reward = 0;

void create()
{
	mapping name;
	if( random(2) )
	{
		name = NAME_D->random_name2(0, 0, 0, 0, 0);
		set("gender","男性");
	}
	else
	{
		name = NAME_D->random_name2(1, 0, 0, 0, 0);
		set("gender","女性");
	}
	set_name(name["name"],name["id"]);
	set("age",18+random(20));
	set("attitude", "heroism");
	setup();
}

void leave()
{
	string color;
	if(this_object()) 
      	{ 
		color = ({HIR,HIY,HIC,HIW,HIR,HIM,HIG,HBRED,HBGRN,HBYEL,HBBLU,HBMAG,})[random(12)];
		message_vision(color+COLOR_D->clean_color(death_msg[random(sizeof(death_msg))])+NOR,this_object());
        	destruct(this_object());
      	}
}

int random_place()
{
	int i,j,k;
	object me,newob;
	mixed *file, exit,*dirs;
	
	me=this_object();
	if( me->query_level()<40 )
        	dirs = dirs1;
	else	dirs = dirs2;		
        i = random(sizeof(dirs));    // pick up one directory
	file = get_dir( dirs[i]+"/*.c", -1 );
	if( !sizeof(file) )
        	return 0;
        reset_eval_cost();	
	for(k=0;k<20;k++) 
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
        	                        message_vision(HIB"$N"HIB"缓缓走了过来，脸上带着诡异的笑容。\n",me);
                	                return 1;
                        	}
                        	else if( me )
                        	{
                        		destruct(me);
                        		return 0;
                        	}
			}
                }
        }
	return 0;
}

int copy_status(object me,object ob)
{
	mapping skill;
	string *skills;
	int i,max_skill,level,v;
	if( !ob || !living(ob) )
		return 0;
	level = ob->query_level();
	v = 9-last_num(level);
	if( v>1 )
		level+= random(v)-random(5);
	me->set_level(level);
	max_skill = level*10;
	set_skills(max_skill,level);		
	if( !mapp(skill = me->query_skills()) )
		return 0;	
	skills = keys(skill);
	if( !skills || !arrayp(skills) || sizeof(skills)<1 )
		return 0;
	for(i=0;i<sizeof(skills);i++)
		me->set_skill(skills[i],max_skill);
	set("bellicosity",ob->query("bellicosity")/3*2+1);	
	set("force_factor",me->query_maxforce()/35+1);
	set("mana_factor",me->query_maxmana()/35+1);
	return 1;
}

string _invocation(object who, int level)
{       
	object me = this_object(), env;
	string where,title,*ts; 
	int exp, i, p,lvl;
    
	set("owner_id", who->query("id"));
	set("owner", who);
	lvl = level;
	if( lvl<1 ) 
		lvl = 1;

	switch(random(lvl)) 
	{
        	case 0 :
                case 1 : title = HIW"白衣";break;
                case 2 : title = HIG"绿衣";break;
                case 3 : title = HIB"蓝衣";break;
                case 4 : title = HIR"红衣";break;
                case 5 : title = HIM"紫衣";break;
                case 6 : title = HIC"青衣";break;
                case 7 : title = HIY"金衣";break;
                default: title = CYNBLU"暗影";break;
	}
	if( who->query_temp("killerside")=="officer" )
	{
		ts = ({"人魔","魔头","魔士","妖士","老怪",});
		set("guai_type",2);
	}
	else
	{
		ts = ({"侠客","剑侠","大侠","剑客","上人",});	
		set("guai_type",1);
	}
	title+= ts[random(sizeof(ts))]+NOR;
	
        set("title",title);        
        
        if( this_object()->query_level()<40 )
        	exp_reward = 3000;
        else	exp_reward = 4000;
	exp_reward = exp_reward*9/10+random(exp_reward/10);
	me->set("stay_time", time());
	if( !random_place() ) 
        {
        	leave();
        	return 0;
        }
	env = environment();
	if( !env )
        {
        	leave();
        	return 0;
        }
	where = me->query("name")+"("+capitalize(me->query("id"))+")";
	where+= "在"+MISC_D->find_place(env);
	if(query("guai_type")==2)
		where = "金衣楼的「"+COLOR_D->clean_color(title)+"」"+where;
	else	where = "洛阳神侯府的「"+COLOR_D->clean_color(title)+"」"+where;
	return where;
}

string invocation(object who, int level)
{
	object me = this_object();
	if( !who )  
		return 0;
	if( !copy_status(me,who) )
	{
		leave();
		return 0;
	}
	this_object()->powerup(0,1);
	set("force",this_object()->query_maxforce()*2);
	set("mana",this_object()->query_maxmana()*2);		
	return _invocation(who, level);
}

int accept_object (object who, object ob){return 0;}

void die()
{
        object owner;
        object me=this_object();
        int exp_r, pot_r,dx_r,lvl;

	message_vision(HIW"\n$N"HIW"说道：「不打了，不打了，我投降....。」\n\n"NOR,me);
	message_vision(CYN"$N"CYN"说道："+RANK_D->query_self_rude(me)+"技不如人，奈何奈何，扯呼者也。\n"NOR,me);
	owner = query_temp("last_damage_from");
	if( !owner || !query("owner_id") || owner->query("id")!=query("owner_id") )
	{
		leave();
		return;
	}
	message_vision(({HIR,HIY,HIC,HIW,HIR,HIM,HIG,HBRED,HBGRN,HBYEL,HBBLU,HBMAG,})[random(12)]+COLOR_D->clean_color(death_msg[random(sizeof(death_msg))])+NOR,this_object());		
	exp_r = exp_reward;
	pot_r = exp_reward/(8+random(4))+1;
	dx_r = exp_reward/15+random(exp_reward/15);
	QUEST_D->job_reward_player(owner,"combat_exp",exp_r,job_type());
	QUEST_D->job_reward_player(owner,"daoxing",dx_r,job_type());
	QUEST_D->job_reward_player(owner,"potential",pot_r,job_type());
	tell_object(owner,HIY+owner->finish_job(job_type(),({exp_r,dx_r,pot_r}))+NOR);
	owner->money_add(1000);
	tell_object(owner,"你得到了十两白银的奖励。\n");
	lvl = owner->query_job_level("杀手任务");
	if( lvl==10 )
	{
		tell_object(owner,HIY"恭喜！你完成了一轮普通级别的杀手任务。\n"NOR);
		if( owner->query("killerside")=="officer" )
		{
			owner->add("mark/luoyang_pingfeng",1);
			tell_object(owner,HIY"【系统】你获得了"HIR"1"HIY"点「"HIC"屏风四扇门"HIY"」学习资格。\n"NOR);
			tell_object(owner,HIY"【系统】你的「"HIC"屏风四扇门"HIY"」学习资格已达到"HIR+owner->query("mark/luoyang_pingfeng")+HIY"点。\n"NOR);
		}		
		else if( owner->query("killerside")=="killer" )
		{
			owner->add("mark/luoyang_xuehejue",1);
			tell_object(owner,HIY"【系统】你获得了"HIR"1"HIY"点「"HIC"血河诀"HIY"」学习资格。\n"NOR);
			tell_object(owner,HIY"【系统】你的「"HIC"血河诀"HIY"」学习资格已达到"HIR+owner->query("mark/luoyang_xuehejue")+HIY"点。\n"NOR);
		}		
	}
	destruct(this_object());
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

int accept_fight(object ob)
{
        object me = this_object();
        if ( ob->query("id") != me->query("owner_id") )
	{
                EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
                tell_object(ob,CYN+name()+CYN"说道："+RANK_D->query_rude(ob)+"一边呆着去，"+RANK_D->query_self_rude(me)+"现在没空！\n"NOR);
                return 0;
        }
        else    
        {
                EMOTE_D->do_emote(this_object(), "heihei",geteuid(ob),CYN,0,0,0);
                tell_object(ob,CYN+name()+CYN"说道："+kill_shout[random(sizeof(kill_shout))]+NOR"\n");
                me->kill_ob(ob);
                return 1;
        }
}

void unconcious(){die();}
