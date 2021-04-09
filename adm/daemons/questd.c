//Cracked by Roath
#include <ansi.h>
#include <command.h>
#include <localtime.h>
inherit F_DBASE;
#include <questd.h>

// #pragma save_binary

nosave int now_pot = 100;
nosave int last_jiangjing = 0;

void init_job();
void check_job_gift();
int job_reward_player(object who,string data,int reward,string type);
int set_job_reward(string type,int v);

mapping nn = ([
	"daoxing"	: "道行",	"combat_exp"    : "武学经验",
    	"potential"     : "潜能",
	"str"	   : "膂力",		"cor"	   : "胆识",
    	"int"	   : "悟性",		"spi"	   : "灵性",
    	"cps"	   : "定力",		"per"	   : "魅力",
    	"con"	   : "根骨",		"kar"	   : "福缘",
    	"kee"	   : "气血",		"sen"	   : "精神",
    	"force"	   : "内力",		"mana"	   : "法力",
]);

mapping walks = ([
        "east" : "west",		"west" : "east",
        "north": "south",		"south": "north",
        "up"   : "down",		"down" : "up",
        "enter": "out",			"out"  : "enter",
        "northup" : "southdown",	"southdown" : "northup",
        "northdown" : "southup",	"southup" : "northdown",
        "northwest" : "southeast",	"southeast" : "northwest",
        "northeast" : "southwest",	"southwest" : "northeast",
        "westup"  : "eastdown",		"eastdown": "westup",
]);

mapping F_place = ([
	"百花谷"	: "/d/baihuagu/huahai1",
	//"儒家"		: "/d/city/guozi",
	//"阎罗地府"	: "/d/death/zhengtang",
	//"将军府"	: "/d/jjf/front_yard",
	//"方寸山三星洞"	: "/d/lingtai/jingtang",
	"月宫"		: "/d/moon/change_room",
        "南海普陀山"  : "/d/nanhai/chanfang",
	//"盘丝洞"	: "/d/pansi/hubian",
	"东海龙宫"	: "/d/sea/inside3",
	"蜀山派"	: "/d/shushan/dadian",
	"大雪山"	: "/d/xueshan/wuchang-e",
        "陷空山无底洞"        : "/d/qujing/wudidong/inner-tang",
	"火云洞"	: "/d/qujing/kusong/huoyun",
	//"五庄观"	: "/d/qujing/wuzhuang/chengyun",
]);

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "任务精灵");
	init_job();
	set_heart_beat(1);
}

int clean_up()
{
	return 1;
}

//集成任务系统
//初始化任务奖励基数
mapping Job;
int Job_set = 0;

void init_job()
{
	Job = ([
	    "李靖任务"	     : 100,
	    "解密任务"	     : 100,
	    "门派任务"	     : 100,
	    "袁天罡任务"     : 100,
	    "如来任务"	     : 100,
	    "送信任务"	     : 100,
	    "寻宝任务"	     : 100,
	    "分配任务"	     : 100,
	    "押镖任务"	     : 100,
	    "守城任务"	     : 100,
	    "杀手任务"	     : 100,
	    "妖魔大会"	     : 100,
	    "门派守护"       : 100,
    	]);
    	Job_set = 0;
    	now_pot = 100;
    	message("shout",HIG"【任务系统】各大任务奖励基数初始化完毕。\n"NOR,users());
    	set_heart_beat(1);
}

int query_job_p(){ return now_pot;}

int query_job_reward(string type)
{
	if( !type || undefinedp(Job[type]) )
		return 0;
	return Job[type];
}

int set_job_reward(string type,int v)
{
	if( !type || undefinedp(Job[type]) )
		return 0;
	if( v<5 || v>500 )
		return 0;
	Job[type] = v;
        reset_eval_cost();
	if( v!=100 )
		message("shout",HIG"【任务系统】"HIR+type+HIG"奖励基数"+(v>100?"上调":"下调")+"为正常基数的"HIR+v+"%"HIG"！\n"NOR,users());
	else	CHANNEL_D->do_channel(this_object(),"sys",type+"奖励基数 初始化 完毕！"NOR);
	now_pot	= v;
	return v;
}

int job_reward_player(object who,string data,int reward,string type)
{
	mapping temp;
	string type2;
	int p,pp;
	if( !who )
		return 0;
	if( !type || undefinedp(Job[type]) )
	{
		log_file("job_err","设置任务奖励基数出错>>>>"+(!type?"无任务类型":("错误的任务类型:"+type))+".\n");
		return 0;
	}
	if( data!="combat_exp" && data!="daoxing" && data!="potential"  && data!="money" )
	{
		return 0;
	}
	if( reward<0 )
	{
		log_file("job_err",sprintf("[%s]%O获取%s奖励出错>>>>奖励为负.\n",ctime(time()),who,type));
		return 0;
	}
	if( reward==0 )
	{
		if( data=="combat_exp" )
			tell_object(who,HIG"【系统】你得到了零点武学经验。\n"NOR);
		else if( data=="potential" )
			tell_object(who,HIG"【系统】你得到了零点潜能。\n"NOR);
		else if( data=="money" )
			;
		else    tell_object(who,HIG"【系统】你得到了零点道行。\n"NOR);
		return 1;
	}
	type2 = 0;
	switch(type)
	{
			case "李靖任务"      : type2="lijing";break;
			case "解密任务"      : type2="kaifeng";break;
			case "门派任务"      : type2="menpai";break;
			case "袁天罡任务"    : type2="yuan";break;
			case "如来任务"      : break;
			case "送信任务"      : type2="letter";break;
			case "寻宝任务"      : type2="bigtask";break;
			case "分配任务"      : break;
			case "押镖任务"      : break;
			case "守城任务"      : type2="xue";break;
			case "杀手任务"      : type2="killer";break;
			case "妖魔大会"      : type2="ymdh";break;
			case "门派守护"      : type2="shouhu";break;
	}

	p = query_job_reward(type);
	reward = reward*p/100;
	pp = 0;
	if( type2 && stringp(type2) )
	{
		temp = who->query_temp("ad_apply/"+type2+"/"+data);
		if( temp && mapp(temp) )
		{
			if( time()<=temp["start"]+temp["time"] )
			{
			pp = temp["pot"];
		    if( p>0 )
				{
			if( pp<10 ) pp = 10;
		    if( pp>300 ) pp = 300;
					reward = reward*pp/100;
					tell_object(who,HIY"【系统】由于使用了特殊道具，你所得的"HIR+nn[data]+HIY"为平时的"HIR+pp+"%。\n"NOR);
				}
			}
		else    who->delete_temp("ad_apply/"+type2);
		}
	 }

	if( data=="combat_exp" )
		tell_object(who,HIG"【系统】你得到了"HIY+reward+HIG"点武学经验，奖励基数 "HIY+p+"%"HIG"\n"NOR);
	else if( data=="potential" )
		tell_object(who,HIG"【系统】你得到了"HIY+reward+HIG"点潜能，奖励基数 "HIY+p+"%"HIG"\n"NOR);
	else if( data=="money" )
		tell_object(who,HIG"【系统】你得到了"HIY+MONEY_D->money_str(reward,1)+HIG"，奖励基数 "HIY+p+"%"HIG"\n"NOR);
	else    tell_object(who,HIG"【系统】你得到了"HIY+COMBAT_D->chinese_daoxing(reward)+HIG"道行，奖励基数 "HIY+p+"%"HIG"\n"NOR);
	if( data=="money" )
	{
		who->money_add(reward);
		who->save();
		return reward;
	}
	who->add(data,reward);
	who->save();
	return reward;
}

void check_job_gift()
{
	int mo,we,da,pp;
	int up_time,x,y,i;
	string *jobs,jr,day;
	mixed *local;

	set_heart_beat(3600);

	local = localtime(time());
	da = local[3];
	mo = local[4]+1;
	we = local[6];
	jr = 0;
	pp = 100;
	if( mo==1 && da<4 )
	{
		jr = "元旦期间";
		pp = 400;
	}
        else if( mo==1 && da==30 )
        {
                jr = "除夕";
                pp = 400;
        }
        else if( mo==1 && da==31 )
        {
                jr = "春节假期";
                pp = 400;
        }
        else if( mo==2 && da<=6 )
        {
                jr = "春节假期";
                pp = 300;
        }

	else if( mo==2 && da==14 )
	{
                jr = "元宵节暨情人节";
                pp = 300;
	}
	else if( mo==3 && da==5 )
	{
		jr = "学雷锋日";
		pp = 150;
	}
	else if( mo==3 && da==8 )
	{
		jr = "妇女节";
		pp = 200;
	}
	else if( mo==3 && da==12 )
	{
		jr = "植树节";
		pp = 150;
	}
	else if( mo==3 && da==15 )
	{
		jr = "消费者权益日";
		pp = 200;
	}
	else if( mo==4 && da==1 )
	{
		jr = "愚人节";
		pp = 110;
	}
	else if( mo==4 && da==5 )
	{
		jr = "清明节";
		pp = 110;
	}
	else if( mo==5 && da<4 )
	{
		jr = "劳动节期间";
		pp = 300;
	}
	else if( mo==5 && da==4 )
	{
		jr = "青年节";
		pp = 150;
	}
	else if( mo==5 && da>7 && we==0 && da<20 )
	{
		jr = "母亲节";
		pp = 200;
	}
	else if( mo==6 && da==1 )
	{
		jr = "儿童节";
		pp = 200;
	}
	else if( mo==6 && da>14 && we==0 )
	{
		jr = "父亲节";
		pp = 200;
	}
     else if( mo==6 && da>21 && da<25 )
        {
                jr = "端午节";
                pp = 300;
        }
	else if( mo==7 && da==1 )
	{
		jr = "建党节";
		pp = 150;
	}
	else if( mo==7 && da==7 )
	{
		jr = "抗日纪念日";
		pp = 200;
	}
	else if( mo==8 && da==1 )
	{
		jr = "建军节";
		pp = 200;
	}
	else if( mo==9 && da==10 )
	{
		jr = "教师节";
		pp = 150;
	}
	else if( mo==10 && da<8 )
	{
		jr = "国庆节期间";
		pp = 400;
	}
	else if( mo==12 && da==25 )
	{
		jr = "圣诞节";
		pp = 200;
	}
	else if( we==0 || we==6 )
	{
		jr = "周末";
		pp = 150;
	}
	remove_call_out("check_job_gift");
	if( pp==now_pot )
		return;

	day = " "+chinese_number(mo)+"月"+chinese_number(da)+"日";
	if( jr )
		day+= "("HIR+jr+HIG") ";
	day = "今日是"+day;
	if( jr && stringp(jr) )
	{
		message("shout",HIG"【任务系统】"+day+HIG"，全局奖励基数自动调整为"HIR+pp+"%"HIG"！\n"NOR,users());
		jobs = keys(Job);
		for(i=0;i<sizeof(jobs);i++)
		{
			if( jobs[i]=="妖魔大会" )
				continue;
			set_job_reward(jobs[i],pp);
		}
	}
	else
	{
		pp = 100;
		jobs = keys(Job);
		CHANNEL_D->do_channel(this_object(),"chat",day+HIC"，全局奖励基数维持正常状态！"NOR);
		for(i=0;i<sizeof(jobs);i++)
			set_job_reward(jobs[i],pp);
	}

}

int set_job_reward_flag(int v,int time,object who)
{
	string *jobs;
	int i;
	if( v<50 || v>500 || time<0 || time>86400 )
		return 0;
	if( !who ) return 0;
        if( wizhood(who) != "(admin)" )
		return 0;
	jobs = keys(Job);
	if( userp(who) )
		message("shout",HIG"【任务系统】"HIW+who->query("id")+HIG"将全局奖励基数调整为 "HIR+v+"%"HIG" ，为时 "HIR+CHINESE_D->chtime(time)+" "HIG"！\n"NOR,users());
	else
		message("shout",HIG"【任务系统】"HIW+who->query("channel_id")+HIG"将全局奖励基数调整为 "HIR+v+"%"HIG" ，为时 "HIR+CHINESE_D->chtime(time)+" "HIG"！\n"NOR,users());
	for(i=0;i<sizeof(jobs);i++)
		set_job_reward(jobs[i],v);
	set_heart_beat(time);
	remove_call_out("check_job_gift");
	call_out("check_job_gift",time);
	return 1;
}

//SDS转过来的
void addSen(object me)
{
	int neilineed,diff;
	if( !me || !living(me) || me->query("force")<20 )
		return;
	if( me->query("no_refresh") )
		return;
	diff = me->query("eff_sen")-me->query("sen");
	neilineed = diff*50/(int)me->query_skill("force");
	if( neilineed<1 ) return;
	if( neilineed>me->query("force") ) neilineed = me->query("force");
	diff = neilineed*(int)me->query_skill("force")/50;
	me->receive_heal("sen", diff);
	me->add("force", -neilineed);
	message_vision("$N略一凝神，吸了口气，精神看起来清醒多了。\n", me);
	return;
}

void addKee(object me)
{
	int diff,neilineed;
	if( !me || !living(me) || me->query("force")<20 )
		return;
	if( me->query("no_recover") )
		return;
	diff = me->query("eff_kee")-me->query("kee");
	neilineed = diff*30/(int)me->query_skill("force");
	if( neilineed<1 ) return;
	if( neilineed>200 ) neilineed=200;
	if( neilineed>me->query("force") )
		neilineed = me->query("force");
	diff = neilineed*(int)me->query_skill("force")/20;
	me->receive_heal("kee", diff );
	me->add("force",-neilineed);
	message_vision("$N深深吸了几口气，脸色看起来好多了。\n", me);
	return;
}

void addEffSen(object me)
{
	int addSen;
	if( !me || !living(me) || me->query("no_eatdan") )
		return;
	addSen = me->query("max_sen")-me->query("eff_sen");
	if( addSen<=0 ) return;
	while( me->query("eff_sen")<me->query("max_sen") )
	{
		if( me->query("mana")<200 )
			return;
		me->receive_curing("sen",(200+(int)me->query_skill("spells",1)/2) );
		me->add("mana",-200);
	}
	message_vision("$N吃下一些混元丹，气色看起来好多了。\n"NOR,me);
	return;
}

void addEffKee(object me)
{
	int add_kee;
	if( !me || !living(me) || me->query("no_eatyao") )
		return;
	add_kee = me->query("max_kee")-me->query("eff_kee");
	if( add_kee<=0 ) return;
	while( me->query("eff_kee")<me->query("max_kee") )
	{
		if( me->query("force")<200 )
			return;
		me->receive_curing("kee",(100+(int)me->query_skill("force",1)/2) );
		me->add("force",-200);
	}
	message_vision("$N吃下一些金创药，气色看起来好多了。\n"NOR,me);
	return;
}

int sort_skill(string file)
{
	int i;
	if( !sscanf(file, "%*s.c") )
		return 0;
	i = strlen(file);
	while(i--)
	{
		if( file[i] == '.' ) continue;
		if( file[i] < 'a' || file[i] > 'z' )
			return 0;
	}
	return 1;
}

int max(int a,int b)
{
	if( a>b )  return a;
	return b;
}

string checkSkill(object who,string arg)
{
	int i;
	string *str,sk,exert,*file;
	object newSk;
	mapping skill = who->query_skills();

	if( !skill || !mapp(skill) )
		return 0;
	if( undefinedp(skill[arg]) )
		return 0;
	str = keys(skill);
	for( i=0;i<sizeof(str);i++ )
	{
		if( who->query_skill_mapped(arg)==str[i] )
		{
			sk = str[i];
			break;
		}
	}
	if( !stringp(sk) )
		return 0;
	if(file_size(SKILL_D(sk)+".c") < 1)
		error ("daemon/"+sk+".c文件损坏.\n");
	if( stringp(exert=SKILL_D(sk)->perform_action_file("")) )
	{
		file = get_dir(exert);
		if( sizeof(file)>0 )
			file = filter_array(file, (: sort_skill :) );
	}
	else if( stringp(exert = SKILL_D(sk)->exert_function_file("")) )
	{
		file = get_dir(exert);
		if( sizeof(file)>0 )
			file = filter_array(file, (: sort_skill :) );
	}
	else if( stringp(exert = SKILL_D(sk)->cast_spell_file("")) )
	{
		file = get_dir(exert);
		if( sizeof(file)>0 )
			file = filter_array(file, (: sort_skill :) );
	}
	if( sizeof(file)<=0 )
		return 0;

	i = random(sizeof(file));
	if( !file[i] )  return 0;
	exert = replace_string(file[i],".c","");
	who->set_temp("sdsd/checkskill",exert);
	return exert;
}

//最高的skills
varargs int maxSkill(object who,int flag)
{
	int i,num = 1;
	mapping skills;
	string *skill;

	skills = who->query_skills();
	if( !skills || !mapp(skills) )
		return 0;
	skill = keys(skills);

	if( sizeof(skill)>0 )
	{
		for (i=0;i<sizeof(skill);i++)
		{
			if( flag>0 && skill[i]=="literate" )
				continue;
			if( who->query_skill(skill[i],1)>num )
				num = who->query_skill(skill[i],1);
		}
	}
	else    num = 200+random(300);
	return num;
}

varargs void randomPfm(object who,string arg)
{
	string exert;
	object weapon;
	if( !who || !living(who) )
		return;
	if( !who->is_fighting() || who->query("no_perform") )
		return;
	if( time()<(who->query_temp("no_perform/start")+who->query_temp("no_perform/time")) )
		return;
	if( !arg )
	{
		if( !objectp(weapon=who->query_temp("weapon")) )
			arg = "unarmed";
		else    arg = weapon->query("skill_type");
	}
	if( !arg || !stringp(arg) )   arg = "unarmed";
	exert = checkSkill(who,arg);
        if( !exert || !stringp(exert) || exert=="huicheng" )
		return;
	if( exert=="huifeng" && !who->query("pfm_huifeng")
	 && arg=="sword" && who->query("family/family_name")=="月宫" )
		return;
	if( exert=="heng" && !who->query("pfm_heng")
	 && arg=="sword" && who->query("family/family_name")=="百花谷" )
		return;
	if( exert=="zong" && !who->query("pfm_zong")
	 && arg=="sword" && who->query("family/family_name")=="百花谷" )
		return;
	who->perform_action(arg,exert);
}

void randomCast(object who)
{
	string exert,*noMsg;
	if( !who || !living(who) )
		return;
	if( time()<(who->query_temp("no_cast/start")+who->query_temp("no_cast/time")) )
		return;
	exert = checkSkill(who,"spells");
	noMsg = ({      "shuidun",	       //dragon
			"escape","chongsheng",//emei swordman
			"townportal",	 //hell
			"yin",	       //gumu
			"mysticism",	   //sanxian
			"tuoqiao",	       //shushan
			"bagua",		   //youxia
			"qimen",		    //wzg
			"tudun",		   //wdd
			"chuqiao",	    //all
			"huicheng",	    //all
		});
	if( !who->is_fighting()
   	 || member_array(exert,noMsg)!=-1
   	 || who->query("no_cast") )
		return;
	who->cast_spell(exert);
}

void randomExert(object who)
{
	string exert;
	if( !who || who->query("no_exert") || !living(who) )
		return;
	if( time()<(who->query_temp("no_exert/start")+who->query_temp("no_exert/time")) )
		return;
	exert = checkSkill(who,"force");
	who->exert_function(exert);
}

int sort_user(object ob,string fam)
{
	return ob->query("family/family_name")==fam||wizardp(ob) ;
}

void jiangjing_start(string fname)
{
	string file,msg;
	object room,*ob;
	if( !fname )
		return;
	if( undefinedp(F_place[fname]) )
		return;
	file = F_place[fname];
	room = find_object(file);
	if( !room )
		room = load_object(file);
	if( !room )
		return;
	room->set("jiangjing",1);
	msg = "\n"HIW"【师门授法】";
	switch(fname)
	{
		case "百花谷" :
			msg+= "凝眸仙子：现在开始传授我们蓬莱山百花谷的神功，诸弟子可与花海聆听(hear)。";
			tell_room(room,"凝眸仙子说道：明玉神功以吐纳为根基，可吸收天地之灵气。习之可是神清气明，忘却一切杂念，使身心达到一种超脱凡人的境界。\n");
			break;
		/*
		case "儒家" :
			msg+= "贺知章：大唐国子监开始授课！来读书(dushu)吧！";
			break;
		*/
		case "阎罗地府" :
			msg+= "阎罗王：阎罗小鬼速到阎罗宝殿听经(hear)。	";
			tell_room(room,"阎罗王喊道;小鬼集合开始讲经。\n");
			tell_room(room,"一时鬼气森森,四面阴风煞煞，好不吓人。\n");
			break;
		case "将军府" :
			msg+= "程咬金：大唐将军府众将演武场点兵，众将士集合开始演武(yanwu)。";
			tell_room(room,"战鼓声声,一片将士的呐喊声震耳欲聋。\n");
			break;
		case "方寸山三星洞" :
			msg+= "云阳真人：方寸山三星洞弟子，速回山于讲经堂听(hear)道家仙法了。";
			tell_room(room,"云阳真人说道：道家仙法是菩提祖师所创的法术。\n");
			break;
		case "月宫" :
			msg+= "嫦娥：月宫弟子快回长思馆来练舞(lianwu)。	";
			tell_room(room,"嫦娥说道：回去试试你的仙法进展如何。\n");
			break;
		case "南海普陀山" :
			msg+= "掌禅僧：现在开始讲授我佛如来之无边佛法，普陀弟子速来禅房听经(hear)。";
			tell_room(room,"掌禅僧说道：万机歇罢结禅坛，无字拈来着力参。参到水穷山尽处，自然透得祖师关。\n");
			tell_room(room,"掌禅僧说道：古德云，参禅要透祖师关，妙悟要穷心路绝。祖关不透，心路不绝，尽是依草附木精灵。\n");
			tell_room(room,"掌禅僧说道：且道如何是祖师关？只这一个“无”字，便是一关，禅门目之为“无门关”。\n");
			break;
		case "盘丝洞" :
			msg+= "金灵圣母：现在开始传授我们盘丝洞的仙术，速回金光洞聆听(hear)。";
			tell_room(room,"金灵圣母说道：修炼仙术目的是希望能参透天地间永恒的奥秘，以达到天人合一的境界。\n");
			break;
		case "东海龙宫"	:
			msg+= "敖广：现在开始传授我们龙宫避水之术，龙宫弟子速回正殿聆听(hear)。";
			tell_room(room,"敖广说道：四海龙王乃玉帝遣于凡间，专管降雨。\n");
			tell_room(room,"敖广说道：四海龙王之下又有众多河龙王，井龙王，及各种水族。\n");
			tell_room(room,"敖广说道：我传的武功法术在水中占了极大的优势。\n");
			tell_room(room,"敖广说道：龙宫的宝物对本门弟子的成长也是大有好处。\n");
			break;
		case "蜀山派" :
			msg+= "剑圣：现在开始传授我们蜀山的仙术，蜀山弟子速回大殿聆听(hear)。";
			tell_room(room,"剑圣说道：蜀山仙术能吸取山中灵气，修炼后能突破凡人之躯，御剑飞行，追风逐月，星海飞驰，修炼仙术目的是希望能参透天地间永恒的奥秘，以达到天人合一的境界。\n");
			tell_room(room,"剑圣说道：山外有山，天外有天。\n");
			break;
		case "大雪山" :
			msg+= "白象尊者：雪山弟子，速回东武场听(hear)本尊开始讲授登仙大法。";
			tell_room(room,"白象尊者说道：登仙大法可谓是明王创造出来的奇特的仙法。\n");
			break;
		case "陷空山无底洞" :
			msg+= "玉鼠精：现在开始在大殿传授我们无底洞的宝典，儿郎们，都来听听(hear)。";
			tell_room(room,"地涌夫人说道：这人肉包子的味道可实在是好啊。首先要心狠手辣，不能拖泥带水。\n");
			tell_room(room,"地涌夫人说道：人肉包子吃的就是新鲜，不能放置，砍下肉后，要立即做成包子。要点是：人的心脏附近的肉最为鲜美。\n");
			break;
		case "火云洞" :
			msg+= "红孩儿：现在开始传授我们枯松涧火云洞的真法，速回火云堂聆听(hear)。";
			tell_room(room,"红孩儿说道：火魔心法修炼后，体内三昧真火纵是大罗神仙也难逃一劫！\n");
			break;
		case "五庄观" :
			msg+= "镇元大仙：现在开始在乘云阁传道，五庄弟子速回听(hear)法。";
			tell_room(room,"镇元大仙说道：现在开始传法。\n");
			break;
		default : return;
	}
	ob = filter_array( users(), "sort_user", this_object(), fname );
	if( ob )
		message("shout",msg+NOR"\n",ob);
}

void jiangjing_end()
{
	string *files,f;
	int i;
	object room;

	remove_call_out("jiangjing_start");
	remove_call_out("jiangjing_end");
	files = values(F_place);
	for(i=0;i<sizeof(files);i++)
	{
		f = files[i];
		if( !f || !stringp(f) )
			continue;
		room = find_object(f);
		if( !room )
			room = load_object(f);
		if( !room )
			continue;
		room->delete("jiangjing");
		tell_room(room,"\n\n半空中隐约传来钟呗之声，诸天异象纷纷消散，顿时天地一片寂静。\n\n");
	}
}

void check_jiangjing()
{
	string *files;
	int i;
	if( last_jiangjing<1 )
	{
		last_jiangjing++;
		return;
	}
	if( time()<last_jiangjing+5400 )
		return;
	last_jiangjing = time();
	files = keys(F_place);
	for(i=0;i<sizeof(files);i++)
		call_out("jiangjing_start",i*2+1,files[i]);
	remove_call_out("jiangjing_end");
	call_out("jiangjing_end",900);
}

void heart_beat()
{
	check_jiangjing();
	check_job_gift();
}

int bug_post(string msg,string name)
{
	mapping note,*notes;
	object board = find_object("/obj/board/gift_b.c");
	if( board )
        {
        	note = allocate_mapping(5);
        	note["title"] = HIR"bug举告"NOR;
        	note["sx"] = "◆";
        	note["author"] = name,
        	note["time"] = time();
        	note["ip"] = "系统";
        	note["msg"] = msg;
        	notes = board->query("notes");
        	if( !pointerp(notes) || !sizeof(notes) )
                	notes = ({ note });
        	else    notes += ({ note });
        	board->set("notes", notes);
        	board->save();
        	return 1;
        }
	return 0;
}

int information(object npc,object who)
{
	mapping skill;
	string *skills;
	int i,lvl;
	if( !npc || !who )
        	return 0;
	if( userp(npc) )
        	return 0;
	npc->set_level(who->query_level()*2/3);
	npc->set("daoxing",who->query("daoxing")/3*2);
	lvl = maxSkill(who);
	lvl = lvl*2/3+1;
	skill = npc->query_skills();
	if( skill && mapp(skill) )
	{
		skills = keys(skill);
		if( skills && arrayp(skills) )
		{
			for(i=0;i<sizeof(skills);i++)
				npc->set_skill(skills[i],lvl);
		}
	}
	npc->set("bellicosity",who->query("bellicosity")*2/3);
	npc->set("max_kee",who->query_maxkee()*3/2);
	npc->set("max_sen",who->query_maxsen()*3/2);
	npc->set("max_force",who->query_skill("force")*10);
	npc->set("max_mana",who->query_skill("spells")*10);
	npc->set("mana_factor",who->query_skill("spells"));
	npc->set("env/brief_message",who->query("env/brief_message"));
	npc->setup();
	return 1;
}

varargs void random_emote(object npc,string target,mixed chat)
{
	string *eqs,str;
	mapping channel;
	eqs = EMOTE_D->query_all_emote();
	str = eqs[random(sizeof(eqs))];
	if( !npc || !str || !stringp(str) )
        	return;
	//object me, string verb, string arg, string color, int channel_emote, int rumor_emote, int intermud)
	if( chat )
	{
		channel = CHANNEL_D->query_channels();
		if( !channel || !mapp(channel) )
			return;
		if( !undefinedp(channel[chat]) )
		{
			channel = channel[chat];
			str = EMOTE_D->do_emote(npc,str, target,channel["msg_color"],1,0,0);
		}
		else	str = EMOTE_D->do_emote(npc,str, target,HIC"",1,0,0);
		if( !str || !stringp(str) )
        		return;
        	//varargs int do_channel(object me, string verb, string arg, int emote,int allow_chat)
        	if( intp(chat) )
        		CHANNEL_D->do_channel(npc,"chat",str,1);
        	else if( stringp(chat) )
        		CHANNEL_D->do_channel(npc,chat,str,1);
        }
	else    EMOTE_D->do_emote(npc,str, target,NOR+CYN"",0,0,0);
}

int get_player(object who)
{
	int i,flag = 0;
	object *inv = all_inventory(who);
	for(i=0;i<sizeof(inv);i++)
      	{
      		if( inv[i] && (inv[i])->is_character() )
           		return 1;
      	}
	return 0;
}

object random_place()
{
int  m,n,i, j, k;
object temp,newob;
mapping ex;

mixed*  file, exit;
string *dirs = ({
        "/d/city",
        "/d/jjf",
        "/d/westway",
        "/d/kaifeng",
        "/d/lingtai",
        "/d/moon",
        "/d/gao",
        "/d/sea",
        "/d/nanhai",
        "/d/eastway",
        "/d/xueshan",
        "/d/dntg/hgs",

        "/d/qujing/wuzhuang",
        "/d/qujing/baotou",
        "/d/qujing/baoxiang",
        "/d/qujing/bibotan",
        "/d/qujing/biqiu",
        "/d/qujing/chechi",
        "/d/qujing/dudi",
        "/d/qujing/fengxian",
        "/d/qujing/firemount",
        "/d/qujing/jilei",
        "/d/qujing/jindou",
        "/d/qujing/jingjiling",
        "/d/qujing/jinping",
        "/d/qujing/jisaiguo",
        "/d/qujing/maoying",
        "/d/qujing/nuerguo",
        "/d/qujing/pingding",
        "/d/qujing/pansi",
        "/d/qujing/tongtian",
        "/d/qujing/qilin",
        "/d/qujing/qinfa",
        "/d/qujing/qinglong",
        "/d/qujing/tianzhu",
        "/d/qujing/wudidong",
        "/d/qujing/wuji",
        "/d/qujing/xiaoxitian",
        "/d/qujing/yinwu",
        "/d/qujing/yuhua",
        "/d/qujing/zhujie",
        "/d/qujing/zhuzi",
        "/d/penglai",
        "/d/pantao",
        "/d/death",
        "/d/meishan",
        "/d/qujing/lingshan",
});

n = 0;
i = random(sizeof(dirs));    // pick up one directory
file = get_dir( dirs[i]+"/*.c", -1 );
if( !sizeof(file) )
        return 0;
for(k=0;k<30;k++)
        {
        j = random(sizeof(file));
        if( file[j][1] > 0 )
                {
                newob=load_object(dirs[i]+"/"+file[j][0]);
                if ( !newob )
                        continue;
                if ( newob->query("no_fight")
                  || newob->query("no_magic")
                  || newob->query("no_mieyao")
                  || !(exit=newob->query("exits"))
                  || sizeof(keys(exit))<1
                  || newob->query("alternative_die") )
                        continue;
                if ( !mapp(ex=newob->query("exits")) )
                        continue;
                m = sizeof(keys(ex));
                while(m--)
                        {
                        temp = load_object(ex[keys(ex)[m]]);
                        if ( temp )
                                {
                                if ( temp->query("exits/"+walks[keys(ex)[m]])!=base_name(newob) )
                                        n++;
                                }
                        else    continue;
                        }
                if ( n )
                        continue;
                if ( newob )
                        return newob;
                }
        }
return 0;
}

varargs object random_npc(object obj)
{
object *inv,npc,where = random_place();
int i;
while( !where || sizeof(all_inventory(where))<1 )
        where = random_place();
inv = all_inventory(where);
i = sizeof(inv);
while(i--)
        {
        if ( !inv[i] || !inv[i]->is_character()
          || inv[i]->is_fighting()
          || !living(inv[i])
          || inv[i]->is_busy() )
                continue;
        if ( inv[i] )
                return inv[i];
        }
return random_npc(obj);
}

string random_msg(string arg)
{
        int i,k,j;
        string str,arg1;
        if( !arg || !stringp(arg) )
                return "";
        arg = COLOR_D->clean_color(arg);
        i = strlen(arg);
        if( random(2) ) j= i/2;
        else j = i-2;
        for(j;j>0;j--)
        {
                k = random(i*2)/2;
                while( i>2 && (k==i-2 || k%2!=0) )
                        k = random(i*2)/2;
                str = sprintf("%c%c",arg[k],arg[k+1]);
                arg = replace_string(arg,str,"□");
        }
        return arg;
}

varargs object random_item(string *dirr)
{
        object *inv,npc,obj;
        int i;
	npc=random_npc(0,dirr);
        if( !npc || !living(npc) || sizeof(all_inventory(npc))<1 )
                return 0;
        inv = all_inventory(npc);
        i = sizeof(inv);
        while(i--)
        {
                obj = inv[random(i)];
                if( !obj || obj->is_character() || obj->query("no_get") )
                        continue;
                else    return obj;
        }
        return 0;
}

//全局爆率
int query_item_gitf(){return 1;}
